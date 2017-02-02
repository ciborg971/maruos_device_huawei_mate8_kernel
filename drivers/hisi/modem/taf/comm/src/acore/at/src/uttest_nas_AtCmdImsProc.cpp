#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "ATCmdProc.h"
#include "AtCmdImsProc.h"

using namespace testing;


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_IMS_PROC_C

extern TAF_VOID At_MsgProc(MsgBlock* pMsg);

extern void UT_STUB_INIT(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)
/******************************************************************************
����     : Test_AT_ProcImsaMsg
�������� : AT_AT_ProcImsaMsg UT������
�޸���ʷ :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ������
******************************************************************************/
class Test_AT_ProcImsaMsg: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
�����������: TAT_ProcImsaMsg_001
������������: δ��IMSA��Ϣ��Ӧ�����ҶԶ�Ӧ�Ĵ�����
Ԥ�ڽ��    : ��ӡlog
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_ProcImsaMsg, AT_ProcImsaMsg_001)
{
    // ��������
    AT_IMSA_MSG_STRU                    stImsaMsg;

    // ������ʼ��
    PS_MEM_SET(&stImsaMsg, 0, sizeof(AT_IMSA_MSG_STRU));
    stImsaMsg.ulSenderPid   = PS_PID_IMSA;
    stImsaMsg.ulMsgId       = ID_AT_IMSA_MSG_BUTT;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    At_MsgProc((MsgBlock *)&stImsaMsg);

    // ִ�м��
    GlobalMockObject::verify();
}

/******************************************************************************
����     : Test_AT_RcvImsaCiregSetCnf
�������� : AT_RcvImsaCiregSetCnf UT������
�޸���ʷ :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ������
******************************************************************************/
class Test_AT_RcvImsaCiregSetCnf: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
�����������: Test_AT_RcvImsaCiregSetCnf_001
������������: ID_IMSA_AT_CIREG_SET_CNF��Ϣ��Я����clientId����
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCiregSetCnf, Test_AT_RcvImsaCiregSetCnf_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    IMSA_AT_CIREG_SET_CNF_STRU          stCiregCnf;

    // ������ʼ��
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_SET_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_SET_CNF;
    stCiregCnf.usClientId               = 0;
    stCiregCnf.ulResult                 = VOS_OK;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].ucUsed = AT_CLIENT_USED;

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_FormatResultData)
        .expects(never());

    // ���ñ��⺯��
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // ִ�м��
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCiregSetCnf_002
������������: �㲥��Ϣ�ϱ�
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCiregSetCnf, Test_AT_RcvImsaCiregSetCnf_002)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_SET_CNF_STRU          stCiregCnf;

    // ������ʼ��
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_SET_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_SET_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(TAF_UINT8)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(never());

    // ���ñ��⺯��
    ulRslt = AT_RcvImsaCiregSetCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCiregSetCnf_003
������������: �������ʹ���
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCiregSetCnf, Test_AT_RcvImsaCiregSetCnf_003)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_SET_CNF_STRU          stCiregCnf;

    // ������ʼ��
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_SET_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_SET_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CURRENT_OPT_BUTT;
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(never());

    // ���ñ��⺯��
    ulRslt = AT_RcvImsaCiregSetCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCiregSetCnf_004
������������: +CIREG���óɹ�
Ԥ�ڽ��    : ����VOS_OK
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCiregSetCnf, Test_AT_RcvImsaCiregSetCnf_004)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_SET_CNF_STRU          stCiregCnf;

    // ������ʼ��
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_SET_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_SET_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;
    ulRslt                              = AT_OK;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREG_SET;
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)ulRslt));

    // ���ñ��⺯��
    ulRslt = AT_RcvImsaCiregSetCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCiregSetCnf_005
������������: +CIREG����ʧ��
Ԥ�ڽ��    : ����VOS_OK
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCiregSetCnf, Test_AT_RcvImsaCiregSetCnf_005)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_SET_CNF_STRU          stCiregCnf;

    // ������ʼ��
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_SET_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_SET_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_ERR;
    ulRslt                              = AT_ERROR;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREG_SET;
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)ulRslt));

    // ���ñ��⺯��
    ulRslt = AT_RcvImsaCiregSetCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

/******************************************************************************
����     : Test_AT_RcvImsaCirepSetCnf
�������� : AT_RcvImsaCirepSetCnf UT������
�޸���ʷ :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ������
******************************************************************************/
class Test_AT_RcvImsaCirepSetCnf: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
�����������: Test_AT_RcvImsaCirepSetCnf_001
������������: ID_IMSA_AT_CIREP_SET_CNF��Ϣ��Я����clientId����
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirepSetCnf, Test_AT_RcvImsaCirepSetCnf_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    IMSA_AT_CIREP_SET_CNF_STRU          stCirepCnf;

    // ������ʼ��
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_SET_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_SET_CNF;
    stCirepCnf.usClientId               = 0;
    stCirepCnf.ulResult                 = VOS_OK;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].ucUsed = AT_CLIENT_USED;

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_FormatResultData)
        .expects(never());

    // ���ñ��⺯��
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // ִ�м��
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCirepSetCnf_002
������������: �㲥��Ϣ�ϱ�
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirepSetCnf, Test_AT_RcvImsaCirepSetCnf_002)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_SET_CNF_STRU          stCirepCnf;

    // ������ʼ��
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_SET_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_SET_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(TAF_UINT8)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(never());

    // ���ñ��⺯��
    ulRslt = AT_RcvImsaCirepSetCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCirepSetCnf_003
������������: �������ʹ���
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirepSetCnf, Test_AT_RcvImsaCirepSetCnf_003)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_SET_CNF_STRU          stCirepCnf;

    // ������ʼ��
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_SET_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_SET_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CURRENT_OPT_BUTT;
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(never());

    // ���ñ��⺯��
    ulRslt = AT_RcvImsaCirepSetCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCirepSetCnf_004
������������: +CIREG���óɹ�
Ԥ�ڽ��    : ����VOS_OK
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirepSetCnf, Test_AT_RcvImsaCirepSetCnf_004)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_SET_CNF_STRU          stCirepCnf;

    // ������ʼ��
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_SET_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_SET_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;
    ulRslt                              = AT_OK;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREP_SET;
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)ulRslt));

    // ���ñ��⺯��
    ulRslt = AT_RcvImsaCirepSetCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCirepSetCnf_005
������������: +CIREG����ʧ��
Ԥ�ڽ��    : ����VOS_OK
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirepSetCnf, Test_AT_RcvImsaCirepSetCnf_005)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_SET_CNF_STRU          stCirepCnf;

    // ������ʼ��
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_SET_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_SET_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_ERR;
    ulRslt                              = AT_ERROR;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREP_SET;
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT32)ulRslt));

    // ���ñ��⺯��
    ulRslt = AT_RcvImsaCirepSetCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

/******************************************************************************
����     : Test_AT_RcvImsaCiregQryCnf
�������� : AT_RcvImsaCiregQryCnf UT������
�޸���ʷ :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ������
******************************************************************************/
class Test_AT_RcvImsaCiregQryCnf: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
�����������: Test_AT_RcvImsaCiregQryCnf_001
������������: ID_IMSA_AT_CIREG_QRY_CNF��Ϣ��Я����clientId����
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCiregQryCnf, Test_AT_RcvImsaCiregQryCnf_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    IMSA_AT_CIREG_QRY_CNF_STRU          stCiregCnf;

    // ������ʼ��
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_QRY_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_QRY_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;
    stCiregCnf.bitOpExtInfo             = VOS_TRUE;
    stCiregCnf.enCireg                  = AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT;
    stCiregCnf.ulRegInfo                = VOS_TRUE;
    stCiregCnf.ulExtInfo                = 5;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_FormatResultData)
        .expects(never());

    // ���ñ��⺯��
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // ִ�м��
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCiregQryCnf_002
������������: �㲥��Ϣ�ϱ�
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCiregQryCnf, Test_AT_RcvImsaCiregQryCnf_002)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_QRY_CNF_STRU          stCiregCnf;

    // ������ʼ��
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_QRY_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_QRY_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;
    stCiregCnf.bitOpExtInfo             = VOS_TRUE;
    stCiregCnf.enCireg                  = AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT;
    stCiregCnf.ulRegInfo                = VOS_TRUE;
    stCiregCnf.ulExtInfo                = 5;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (VOS_UINT32)sizeof(TAF_UINT8)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));


    MOCKER(At_FormatResultData)
        .expects(never());

    // ���ñ��⺯��
    ulRslt =  AT_RcvImsaCiregQryCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // ִ�м��
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCiregQryCnf_003
������������: �������ʹ���
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCiregQryCnf, Test_AT_RcvImsaCiregQryCnf_003)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_QRY_CNF_STRU          stCiregCnf;

    // ������ʼ��
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_QRY_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_QRY_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;
    stCiregCnf.bitOpExtInfo             = VOS_TRUE;
    stCiregCnf.enCireg                  = AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT;
    stCiregCnf.ulRegInfo                = VOS_TRUE;
    stCiregCnf.ulExtInfo                = 5;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CURRENT_OPT_BUTT;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(never());

    // ���ñ��⺯��
    ulRslt =  AT_RcvImsaCiregQryCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // ִ�м��
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCiregQryCnf_004
������������: +CIREG��ѯ�ɹ�
Ԥ�ڽ��    : ����AT_OK
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCiregQryCnf, Test_AT_RcvImsaCiregQryCnf_004)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_QRY_CNF_STRU          stCiregCnf;
    VOS_CHAR                            acExpectedStr[] = "+CIREG: 2,1,5";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CIREG,
        AT_SetCiregPara,     AT_SET_PARA_TIME,   AT_QryCiregPara,       AT_QRY_PARA_TIME,   AT_TestCiregPara,   AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_NO_LIMITED,
        (VOS_UINT8 *)"+CIREG",   (VOS_UINT8 *)"(0-2)"};

    // ������ʼ��
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_QRY_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_QRY_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_OK;
    stCiregCnf.bitOpExtInfo             = VOS_TRUE;
    stCiregCnf.enCireg                  = AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT;
    stCiregCnf.ulRegInfo                = VOS_TRUE;
    stCiregCnf.ulExtInfo                = 5;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREG_QRY;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // ���ñ��⺯��
    ulRslt =  AT_RcvImsaCiregQryCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCiregQryCnf_005
������������: +CIREG��ѯʧ��
Ԥ�ڽ��    : ����AT_ERROR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCiregQryCnf, Test_AT_RcvImsaCiregQryCnf_005)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREG_QRY_CNF_STRU          stCiregCnf;

    // ������ʼ��
    PS_MEM_SET(&stCiregCnf, 0, sizeof(IMSA_AT_CIREG_QRY_CNF_STRU));
    stCiregCnf.ulMsgId                  = ID_IMSA_AT_CIREG_QRY_CNF;
    stCiregCnf.usClientId               = ucIndex;
    stCiregCnf.ulResult                 = VOS_ERR;
    stCiregCnf.bitOpExtInfo             = VOS_TRUE;
    stCiregCnf.enCireg                  = AT_IMSA_IMS_REG_STATE_ENABLE_EXTENDED_REPROT;
    stCiregCnf.ulRegInfo                = VOS_TRUE;
    stCiregCnf.ulExtInfo                = 5;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREG_QRY;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // ���ñ��⺯��
    ulRslt =  AT_RcvImsaCiregQryCnf((AT_IMSA_MSG_STRU *)&stCiregCnf);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

/******************************************************************************
����     : Test_AT_RcvImsaCirepQryCnf
�������� : AT_RcvImsaCirepQryCnf UT������
�޸���ʷ :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ������
******************************************************************************/
class Test_AT_RcvImsaCirepQryCnf: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
�����������: Test_AT_RcvImsaCirepQryCnf_001
������������: ID_IMSA_AT_CIREP_QRY_CNF��Ϣ��Я����clientId����
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirepQryCnf, Test_AT_RcvImsaCirepQryCnf_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    IMSA_AT_CIREP_QRY_CNF_STRU          stCirepCnf;

    // ������ʼ��
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_QRY_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_QRY_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;
    stCirepCnf.enReport                 = AT_IMSA_CIREP_REPORT_ENABLE;
    stCirepCnf.enImsvops                = AT_IMSA_NW_SUPORT_IMSVOPS;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].ucUsed     = AT_CLIENT_USED;

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_FormatResultData)
        .expects(never());

    // ���ñ��⺯��
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // ִ�м��
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCirepQryCnf_002
������������: �㲥��Ϣ�ϱ�
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirepQryCnf, Test_AT_RcvImsaCirepQryCnf_002)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_QRY_CNF_STRU          stCirepCnf;

    // ������ʼ��
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_QRY_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_QRY_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;
    stCirepCnf.enReport                 = AT_IMSA_CIREP_REPORT_ENABLE;
    stCirepCnf.enImsvops                = AT_IMSA_NW_SUPORT_IMSVOPS;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .with(any(), outBoundP((TAF_UINT8 *)&ucIndex, (TAF_UINT32)sizeof(TAF_UINT8)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));


    MOCKER(At_FormatResultData)
        .expects(never());

    // ���ñ��⺯��
    ulRslt =  AT_RcvImsaCirepQryCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // ִ�м��
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCirepQryCnf_003
������������: �������ʹ���
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirepQryCnf, Test_AT_RcvImsaCirepQryCnf_003)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_QRY_CNF_STRU          stCirepCnf;

    // ������ʼ��
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_QRY_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_QRY_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;
    stCirepCnf.enReport                 = AT_IMSA_CIREP_REPORT_ENABLE;
    stCirepCnf.enImsvops                = AT_IMSA_NW_SUPORT_IMSVOPS;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CURRENT_OPT_BUTT;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(never());

    // ���ñ��⺯��
    ulRslt =  AT_RcvImsaCirepQryCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // ִ�м��
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCirepQryCnf_004
������������: +CIREG��ѯ�ɹ�
Ԥ�ڽ��    : ����AT_OK
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirepQryCnf, Test_AT_RcvImsaCirepQryCnf_004)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_QRY_CNF_STRU          stCirepCnf;
    VOS_CHAR                            acExpectedStr[] = "+CIREP: 1,1";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CIREP,
        AT_SetCirepPara,     AT_SET_PARA_TIME,   AT_QryCirepPara,       AT_QRY_PARA_TIME,   AT_TestCirepPara,   AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_NO_LIMITED,
        (VOS_UINT8 *)"+CIREP",   (VOS_UINT8 *)"(0,1)"};

    // ������ʼ��
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_QRY_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_QRY_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_OK;
    stCirepCnf.enReport                 = AT_IMSA_CIREP_REPORT_ENABLE;
    stCirepCnf.enImsvops                = AT_IMSA_NW_SUPORT_IMSVOPS;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREP_QRY;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_OK));

    // ���ñ��⺯��
    ulRslt =  AT_RcvImsaCirepQryCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCirepQryCnf_005
������������: +CIREG��ѯʧ��
Ԥ�ڽ��    : ����AT_ERROR
�޸���ʷ    :
 1.��   ��  : 2013-10-12
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirepQryCnf, Test_AT_RcvImsaCirepQryCnf_005)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREP_QRY_CNF_STRU          stCirepCnf;

    // ������ʼ��
    PS_MEM_SET(&stCirepCnf, 0, sizeof(IMSA_AT_CIREP_QRY_CNF_STRU));
    stCirepCnf.ulMsgId                  = ID_IMSA_AT_CIREP_QRY_CNF;
    stCirepCnf.usClientId               = ucIndex;
    stCirepCnf.ulResult                 = VOS_ERR;
    stCirepCnf.enReport                 = AT_IMSA_CIREP_REPORT_ENABLE;
    stCirepCnf.enImsvops                = AT_IMSA_NW_SUPORT_IMSVOPS;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].ucUsed         = AT_CLIENT_USED;
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CIREP_QRY;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // ���ñ��⺯��
    ulRslt =  AT_RcvImsaCirepQryCnf((AT_IMSA_MSG_STRU *)&stCirepCnf);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
    GlobalMockObject::verify();
}

/******************************************************************************
����     : Test_AT_RcvImsaCirephInd
�������� : AT_RcvImsaCirephInd UT������
�޸���ʷ :
 1.��   ��  : 2013-10-17
   ��   ��  : Y00213812
   �޸����� : ������
******************************************************************************/
class Test_AT_RcvImsaCirephInd: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
�����������: Test_AT_RcvImsaCirephInd_001
������������: ID_IMSA_AT_CIREPH_IND��Ϣ��Я����clientId����
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-17
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirephInd, Test_AT_RcvImsaCirephInd_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    IMSA_AT_CIREPH_IND_STRU             stCirephInd;

    // ������ʼ��
    PS_MEM_SET(&stCirephInd, 0, sizeof(IMSA_AT_CIREPH_IND_STRU));
    stCirephInd.ulMsgId                  = ID_IMSA_AT_CIREPH_IND;
    stCirephInd.usClientId               = ucIndex;
    stCirephInd.enHandover               = AT_IMSA_SRVCC_HANDOVER_SUCCESS;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_SendResultData)
        .expects(never());

    // ���ñ��⺯��
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCirephInd);

    // ִ�м��
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCirephInd_002
������������: ID_IMSA_AT_CIREPH_IND��Ϣ��Я����clientId����
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-17
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirephInd, Test_AT_RcvImsaCirephInd_002)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREPH_IND_STRU             stCirephInd;
    VOS_CHAR                            acExpectedStr[] = "\r\n+CIREPH: 1\r\n";

    // ������ʼ��
    PS_MEM_SET(&stCirephInd, 0, sizeof(IMSA_AT_CIREPH_IND_STRU));
    stCirephInd.ulMsgId                  = ID_IMSA_AT_CIREPH_IND;
    stCirephInd.usClientId               = AT_BROADCAST_CLIENT_ID_MODEM_0;
    stCirephInd.enHandover               = AT_IMSA_SRVCC_HANDOVER_SUCCESS;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)acExpectedStr, sizeof(acExpectedStr) -1), eq(VOS_UINT16(sizeof(acExpectedStr) - 1)));

    // ���ñ��⺯��
    ulRslt = AT_RcvImsaCirephInd((AT_IMSA_MSG_STRU *)&stCirephInd);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
����     : Test_AT_RcvImsaCirepiInd
�������� : AT_RcvImsaCirepiInd UT������
�޸���ʷ :
 1.��   ��  : 2013-10-17
   ��   ��  : Y00213812
   �޸����� : ������
******************************************************************************/
class Test_AT_RcvImsaCirepiInd: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
�����������: Test_AT_RcvImsaCirepiInd_001
������������: ID_IMSA_AT_CIREPI_IND��Ϣ��Я����clientId����
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-17
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirepiInd, Test_AT_RcvImsaCirepiInd_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    IMSA_AT_CIREPI_IND_STRU             stCirepiInd;

    // ������ʼ��
    PS_MEM_SET(&stCirepiInd, 0, sizeof(IMSA_AT_CIREPI_IND_STRU));
    stCirepiInd.ulMsgId                 = ID_IMSA_AT_CIREPI_IND;
    stCirepiInd.usClientId              = ucIndex;
    stCirepiInd.enImsvops               = AT_IMSA_NW_SUPORT_IMSVOPS;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_SendResultData)
        .expects(never());

    // ���ñ��⺯��
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCirepiInd);

    // ִ�м��
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCirepiInd_002
������������: ID_IMSA_AT_CIREPI_IND��Ϣ��Я����clientId����
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-17
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCirepiInd, Test_AT_RcvImsaCirepiInd_002)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREPI_IND_STRU             stCirepiInd;
    VOS_CHAR                            acExpectedStr[] = "\r\n+CIREPI: 1\r\n";

    // ������ʼ��
    PS_MEM_SET(&stCirepiInd, 0, sizeof(IMSA_AT_CIREPI_IND_STRU));
    stCirepiInd.ulMsgId                 = ID_IMSA_AT_CIREPI_IND;
    stCirepiInd.usClientId              = AT_BROADCAST_CLIENT_ID_MODEM_0;
    stCirepiInd.enImsvops               = AT_IMSA_NW_SUPORT_IMSVOPS;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)acExpectedStr, sizeof(acExpectedStr) -1), eq(VOS_UINT16(sizeof(acExpectedStr) - 1)));

    // ���ñ��⺯��
    ulRslt = AT_RcvImsaCirepiInd((AT_IMSA_MSG_STRU *)&stCirepiInd);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}

/******************************************************************************
����     : Test_AT_RcvImsaCireguInd
�������� : AT_RcvImsaCireguInd UT������
�޸���ʷ :
 1.��   ��  : 2013-10-17
   ��   ��  : Y00213812
   �޸����� : ������
******************************************************************************/
class Test_AT_RcvImsaCireguInd: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};
/******************************************************************************
�����������: Test_AT_RcvImsaCireguInd_001
������������: ID_IMSA_AT_CIREGU_IND��Ϣ��Я����clientId����
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-17
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCireguInd, Test_AT_RcvImsaCireguInd_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    IMSA_AT_CIREGU_IND_STRU             stCireguInd;

    // ������ʼ��
    PS_MEM_SET(&stCireguInd, 0, sizeof(IMSA_AT_CIREGU_IND_STRU));
    stCireguInd.ulMsgId                 = ID_IMSA_AT_CIREGU_IND;
    stCireguInd.usClientId              = ucIndex;
    stCireguInd.bitOpExtInfo            = VOS_TRUE;
    stCireguInd.ulRegInfo               = VOS_TRUE;
    stCireguInd.ulExtInfo               = 5;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    MOCKER(At_SendResultData)
        .expects(never());

    // ���ñ��⺯��
    AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)&stCireguInd);

    // ִ�м��
    GlobalMockObject::verify();
}
/******************************************************************************
�����������: Test_AT_RcvImsaCireguInd_002
������������: ID_IMSA_AT_CIREGU_IND��Ϣ��Я����clientId����
Ԥ�ڽ��    : ����VOS_ERR
�޸���ʷ    :
 1.��   ��  : 2013-10-17
   ��   ��  : Y00213812
   �޸����� : ��������
******************************************************************************/
TEST_F(Test_AT_RcvImsaCireguInd, Test_AT_RcvImsaCireguInd_002)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    VOS_UINT32                          ulRslt;
    IMSA_AT_CIREGU_IND_STRU             stCireguInd;
    VOS_CHAR                            acExpectedStr[] = "\r\n+CIREGU: 1,5\r\n";

    // ������ʼ��
    PS_MEM_SET(&stCireguInd, 0, sizeof(IMSA_AT_CIREGU_IND_STRU));
    stCireguInd.ulMsgId                 = ID_IMSA_AT_CIREGU_IND;
    stCireguInd.usClientId              = AT_BROADCAST_CLIENT_ID_MODEM_0;
    stCireguInd.bitOpExtInfo            = VOS_TRUE;
    stCireguInd.ulRegInfo               = VOS_TRUE;
    stCireguInd.ulExtInfo               = 5;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_SendResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), mirror((VOS_UINT8 *)acExpectedStr, sizeof(acExpectedStr) -1), eq(VOS_UINT16(sizeof(acExpectedStr) - 1)));

    // ���ñ��⺯��
    ulRslt = AT_RcvImsaCireguInd((AT_IMSA_MSG_STRU *)&stCireguInd);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);
    GlobalMockObject::verify();
}


#endif


