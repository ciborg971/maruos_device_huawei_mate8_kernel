#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include  "vos.h"
#include  "Taf_MmiStrParse.h"
#include  "TafAppSsa.h"
#include  "MnErrorCode.h"
/* A�˺�C�˱���붼Ҫ�õ� */
#include  "MnMsgTs.h"

//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  3 �궨��
*****************************************************************************/
#define MN_MMI_MIN_USSD_LEN             2

#define MN_MMI_DONT_CARE_CHAR           '?'
#define MN_MMI_START_SI_CHAR            '*'
#define MN_MMI_STOP_CHAR                '#'

#define MN_MMI_isdigit(c)               (((c) >= '0') && ((c) <= '9'))

#define MN_MMI_STR_PTR_IS_VALID(pcFrom, pcTo)   ((VOS_NULL_PTR == (pcTo)) || ((VOS_NULL_PTR != (pcTo)) && ((pcFrom) <= (pcTo))))

#define MN_MMI_MAX(a, b)                (((a) > (b)) ? (a) : (b))

#define MN_MMI_MAX_SC_LEN               3                                       /* Ŀǰ��˵����󳤶�Ϊ3*/
#define MN_MMI_MAX_SIA_LEN              30                                      /* �����ں��볤�ȵ�������� */
#define MN_MMI_MAX_SIB_LEN              8                                       /* PWD��PIN�ĳ��� */
#define MN_MMI_MAX_SIC_LEN              8                                       /* PWD��PIN�ĳ��� */

#define MN_MMI_MAX_BUF_SIZE             64
#define MN_MMI_MAX_PARA_NUM             4


#define MN_MMI_SC_MAX_ENTRY (sizeof(f_stMmiScInfo)/sizeof(MN_MMI_SC_TABLE_STRU))

#define MN_MMI_BS_MAX_ENTRY (sizeof(f_stMmiBSInfo)/sizeof(MN_MMI_BS_TABLE_STRU))


/*****************************************************************************
  4 ���Ͷ���
*****************************************************************************/

extern VOS_UINT32 MMI_AtoI(
           const VOS_CHAR                      *pcSrc
       );
extern VOS_BOOL MMI_DecodeScAndSi(
           VOS_CHAR                            *pInMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           VOS_CHAR                            **ppOutMmiStr
       );
extern VOS_UINT32 MMI_FillInActivateSSPara(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_UINT8                           ucNetSsCode
       );
extern VOS_UINT32 MMI_FillInCallOrigPara(
           VOS_CHAR                            *pcMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
           VOS_CHAR                            **ppOutRestMmiStr
       );
extern VOS_UINT32 MMI_FillInDeactivateCCBSPara(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_UINT8                           ucNetSsCode
       );
extern VOS_UINT32 MMI_FillInDeactivateSSPara(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_UINT8                           ucNetSsCode
       );
extern VOS_UINT32 MMI_FillInEraseSSPara(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
           VOS_UINT8                           ucNetSsCode
       );
extern VOS_UINT32 MMI_FillInInterrogateSSPara(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
           VOS_UINT8                           ucNetSsCode
       );
extern VOS_UINT32 MMI_FillInProcessUssdReqPara(
           VOS_CHAR                            *pcInMmiStr,
           VOS_CHAR                            **ppcOutRestMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam
       );
extern VOS_UINT32 MMI_FillInRegisterSSPara(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_UINT8                           ucNetSsCode
       );
extern VOS_BOOL MMI_JudgeChldOperation(
           VOS_CHAR                            *pcInMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam,
           VOS_UINT32                          *pulErrCode
       );
extern VOS_BOOL MMI_JudgeImeiOperation(
           VOS_CHAR                            *pcInMmiStr,
           VOS_CHAR                            **ppcOutRestMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pstMmiOpParam
       );
extern VOS_VOID MMI_JudgeMmiOperationType(
           VOS_CHAR                            *pInMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           VOS_CHAR                            **ppOutRestMmiStr,
           VOS_UINT32                          *pulErrCode,
           VOS_UINT8                           ucNetSsCode
       );
extern  VOS_BOOL MMI_JudgePinOperation(
           VOS_CHAR                            *pMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_CHAR                            **ppOutRestMmiStr,
           VOS_UINT32                          *pulErrCode
       );
extern  VOS_BOOL MMI_JudgePwdOperation(
           VOS_CHAR                            *pMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_CHAR                            **ppOutRestMmiStr,
           VOS_UINT32                          *pulErrCode
       );
extern  VOS_BOOL MMI_JudgeSsOperation(
           VOS_CHAR                            *pInMmiStr,
           VOS_CHAR                            **ppOutRestMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           VOS_UINT32                          *pulErrCode
       );
extern  VOS_BOOL MMI_JudgeTmpModeClirOp(
           VOS_CHAR                            *pInMmiStr,
           VOS_CHAR                            **ppOutRestMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam
       );
extern  VOS_BOOL MMI_JudgeUssdOperation(
           VOS_CHAR                            *pcMmiStr
       );
extern  VOS_BOOL MMI_MatchSsOpTbl(
           VOS_CHAR                            *pInMmiStr,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           VOS_CHAR                            **ppOutRestMmiStr,
           VOS_UINT32                          *pulErrCode,
           VOS_UINT8                           *pucNetSsCode
       );
extern VOS_UINT32 MMI_Max(const VOS_UINT32 ulNumbera, const VOS_UINT32 ulNumberb);
extern VOS_CHAR* MMI_StrChr(
           const VOS_CHAR                      *pcFrom,
           const VOS_CHAR                      *pcTo,
           VOS_INT                              ichar
       );
extern VOS_UINT32 MMI_TransMmiBsCodeToNetBsCode(
           VOS_UINT8                           ucNetSsCode,
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           VOS_UINT8                           *pucNetBsCode,
           VOS_UINT8                           *pucNetBsType
       
       );
extern VOS_UINT32 MMI_TransMmiSsCodeToNetSsCode(
           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
           VOS_UINT8                           *pucNetSsCode
       );
extern TAF_UINT32 MN_MmiStringParse(
           TAF_CHAR                            *pInMmiStr,
           TAF_BOOL                            inCall,
           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
           TAF_CHAR                            **ppOutRestMmiStr
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


#if (NAS_FEATURE_CCBS == FEATURE_ON)

class Test_MMI_FillInDeactivateCCBSPara: public ::testing::Test
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
/*******************************************************************
*������:           ��дDeactivate CCBS������Ҫ�Ĳ���,����Ccbsindex����
*���⺯����������: ��дDeactivate CCBS������Ҫ�Ĳ���,����Ccbsindex�����Ĵ���
*Ԥ�ڽ����        ���سɹ�
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_FillInDeactivateCCBSPara,Test_MMI_FillInDeactivateCCBSPara_01)
{
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT8                           ucNetSsCode = TAF_CCBS_A_SS_CODE;

    MOCKER(MMI_AtoI)
        .stubs()
        .will(returnValue(0));

    ASSERT_EQ(MMI_FillInDeactivateCCBSPara(&stScSiPara,&stMmiOpParam,ucNetSsCode),MN_ERR_NO_ERROR);

    EXPECT_EQ(stMmiOpParam.stCcbsEraseReq.OP_CcbsIndex, VOS_FALSE);
    EXPECT_EQ(stMmiOpParam.stCcbsEraseReq.SsCode,TAF_CCBS_A_SS_CODE);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           ��дDeactivate CCBS������Ҫ�Ĳ���,���Ϸ�Ccbsindex����
*���⺯����������: ��дDeactivate CCBS������Ҫ�Ĳ���,���Ϸ�Ccbsindex�����Ĵ���
*Ԥ�ڽ����        ���سɹ�
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_FillInDeactivateCCBSPara,Test_MMI_FillInDeactivateCCBSPara_02)
{
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT8                           ucNetSsCode = TAF_CCBS_A_SS_CODE;


    MOCKER(MMI_AtoI)
        .stubs()
        .will(returnValue(1));

    ASSERT_EQ(MMI_FillInDeactivateCCBSPara(&stScSiPara,&stMmiOpParam,ucNetSsCode),MN_ERR_NO_ERROR);

    EXPECT_EQ(stMmiOpParam.stCcbsEraseReq.OP_CcbsIndex, VOS_TRUE);
    EXPECT_EQ(stMmiOpParam.stCcbsEraseReq.SsCode,TAF_CCBS_A_SS_CODE);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           ��дDeactivate CCBS������Ҫ�Ĳ���,��Ccbsindex��ȡֵ���Ϸ�>5
*���⺯����������: ��дDeactivate CCBS������Ҫ�Ĳ���,��Ccbsindex��ȡֵ���Ϸ�����5�Ĵ���
*Ԥ�ڽ����        ���سɹ�
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_FillInDeactivateCCBSPara,Test_MMI_FillInDeactivateCCBSPara_03)
{
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT8                           ucNetSsCode = TAF_CCBS_A_SS_CODE;


    MOCKER(MMI_AtoI)
        .stubs()
        .will(returnValue(6));

    ASSERT_EQ(MMI_FillInDeactivateCCBSPara(&stScSiPara,&stMmiOpParam,ucNetSsCode),MN_ERR_INVALIDPARM);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           ��дDeactivate CCBS������Ҫ�Ĳ���,��Ccbsindex��ȡֵ���Ϸ�<1
*���⺯����������: ��дDeactivate CCBS������Ҫ�Ĳ���,��Ccbsindex��ȡֵ���Ϸ�С��1�Ĵ���
*Ԥ�ڽ����        ���سɹ�
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_FillInDeactivateCCBSPara,Test_MMI_FillInDeactivateCCBSPara_04)
{
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT8                           ucNetSsCode = TAF_CCBS_A_SS_CODE;


    MOCKER(MMI_AtoI)
        .stubs()
        .will(returnValue(-1));

    ASSERT_EQ(MMI_FillInDeactivateCCBSPara(&stScSiPara,&stMmiOpParam,ucNetSsCode),MN_ERR_INVALIDPARM);

    GlobalMockObject::verify();

}

#endif


class Test_MMI_MatchSsOpTbl: public ::testing::Test
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
/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����MMI�ִ���Sc��Siʧ��
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����MMI�ִ���Sc��Siʧ�ܵĴ���
*Ԥ�ڽ����        ��������VOS_FALSE,ulErrCodeΪMN_ERR_INVALIDPARM
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_MatchSsOpTbl,Test_MMI_MatchSsOpTbl_01)
{
    VOS_CHAR                            inMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    VOS_UINT32                          ulErrCode;
    VOS_UINT8                           ucNetSsCode;

    pOutRestMmiStr = &outRestMmiStr;

    MOCKER(MMI_DecodeScAndSi)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ASSERT_EQ((MMI_MatchSsOpTbl(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,&ucNetSsCode)),VOS_FALSE);

    EXPECT_EQ(ulErrCode,MN_ERR_INVALIDPARM);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,��Mmi�ִ��е�Ss Codeת�������綨���Ss Codeʧ��,�Ҳ���USSD����
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,��Mmi�ִ��е�Ss Codeת�������綨���Ss Codeʧ��,�Ҳ���USSD�����Ĵ���
*Ԥ�ڽ����        ��������VOS_FALSE,ulErrorCodeΪMN_ERR_INVALIDPARM
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_MatchSsOpTbl,Test_MMI_MatchSsOpTbl_02)
{
    VOS_CHAR                            inMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    VOS_UINT32                          ulErrCode;
    VOS_UINT8                           ucNetSsCode;

    pOutRestMmiStr = &outRestMmiStr;

    MOCKER(MMI_DecodeScAndSi)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_TransMmiSsCodeToNetSsCode)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(MMI_JudgeUssdOperation)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    ASSERT_EQ((MMI_MatchSsOpTbl(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,&ucNetSsCode)),VOS_FALSE);

    EXPECT_EQ(ulErrCode,MN_ERR_INVALIDPARM);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,��Mmi�ִ��е�Ss Codeת�������綨���Ss Codeʧ��,����USSD����
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,��Mmi�ִ��е�Ss Codeת�������綨���Ss Codeʧ��,����USSD�����Ĵ���
*Ԥ�ڽ����        ��������VOS_TRUE
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_MatchSsOpTbl,Test_MMI_MatchSsOpTbl_03)
{
    VOS_CHAR                            inMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    VOS_UINT32                          ulErrCode;
    VOS_UINT8                           ucNetSsCode;

    pOutRestMmiStr = &outRestMmiStr;

    MOCKER(MMI_DecodeScAndSi)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_TransMmiSsCodeToNetSsCode)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(MMI_JudgeUssdOperation)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    ASSERT_EQ((MMI_MatchSsOpTbl(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,&ucNetSsCode)),VOS_TRUE);

    EXPECT_EQ(stMmiOpParam.MmiOperationType,TAF_MMI_PROCESS_USSD_REQ);

    GlobalMockObject::verify();

}
#if(NAS_FEATURE_CCBS == FEATURE_ON)
/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,��ȥ����CCBS�Ĳ���
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,��ȥ����CCBS�Ĳ�������
*Ԥ�ڽ����        ��������VOS_TRUE
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_MatchSsOpTbl,Test_MMI_MatchSsOpTbl_04)
{
    VOS_CHAR                            inMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    VOS_UINT32                          ulErrCode;
    VOS_UINT8                           ucNetSsCode;

    pOutRestMmiStr = &outRestMmiStr;

    ucNetSsCode = TAF_CCBS_A_SS_CODE;
    stMmiOpParam.MmiOperationType = TAF_MMI_DEACTIVATE_SS;

    MOCKER(MMI_DecodeScAndSi)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_TransMmiSsCodeToNetSsCode)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    ASSERT_EQ((MMI_MatchSsOpTbl(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,&ucNetSsCode)),VOS_TRUE);

    EXPECT_EQ(stMmiOpParam.MmiOperationType,TAF_MMI_DEACTIVATE_CCBS);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,�ǲ�ѯCCBS�Ĳ���
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,�ǲ�ѯCCBS�Ĳ�������
*Ԥ�ڽ����        ��������VOS_TRUE
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_MatchSsOpTbl,Test_MMI_MatchSsOpTbl_05)
{
    VOS_CHAR                            inMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    VOS_UINT32                          ulErrCode;
    VOS_UINT8                           ucNetSsCode;

    pOutRestMmiStr = &outRestMmiStr;

    ucNetSsCode = TAF_CCBS_A_SS_CODE;
    stMmiOpParam.MmiOperationType = TAF_MMI_INTERROGATE_SS;

    MOCKER(MMI_DecodeScAndSi)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_TransMmiSsCodeToNetSsCode)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    ASSERT_EQ((MMI_MatchSsOpTbl(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,&ucNetSsCode)),VOS_TRUE);

    EXPECT_EQ(stMmiOpParam.MmiOperationType,TAF_MMI_INTERROGATE_CCBS);

    GlobalMockObject::verify();

}
#endif
/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,�Ƿ�CCBS��ز���
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,�Ƿ�CCBS��صĲ�������
*Ԥ�ڽ����        ��������VOS_TRUE
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_MatchSsOpTbl,Test_MMI_MatchSsOpTbl_06)
{
    VOS_CHAR                            inMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    VOS_UINT32                          ulErrCode;
    VOS_UINT8                           ucNetSsCode;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_DEACTIVATE_SS;

    MOCKER(MMI_DecodeScAndSi)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_TransMmiSsCodeToNetSsCode)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    ASSERT_EQ((MMI_MatchSsOpTbl(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,&ucNetSsCode)),VOS_TRUE);

    EXPECT_EQ(stMmiOpParam.MmiOperationType,TAF_MMI_DEACTIVATE_SS);

    GlobalMockObject::verify();

}


class Test_MMI_JudgeSsOperation: public ::testing::Test
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
/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,SsOpTbl���ҵ���Ӧ����,��CHLD����
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,SsOpTbl���ҵ���Ӧ����,��CHLD�����Ĵ���
*Ԥ�ڽ����        ��������VOS_TRUE
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeSsOperation,Test_MMI_JudgeSsOperation_01)
{
    VOS_CHAR                            inMmiStr = '0';
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;

    pOutRestMmiStr = &outRestMmiStr;
    MOCKER(VOS_MemCmp)
        .stubs()
        .will(returnValue(0));

    MOCKER(MMI_MatchSsOpTbl)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_JudgeMmiOperationType)
        .expects(exactly(1));
    ASSERT_EQ((MMI_JudgeSsOperation(&inMmiStr,&pOutRestMmiStr,&stMmiOpParam,&ulErrCode)),VOS_TRUE);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,SsOpTbl���ҵ���Ӧ����,����CHLD����
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,SsOpTbl���ҵ���Ӧ����,����CHLD�����Ĵ���
*Ԥ�ڽ����        ��������VOS_FALSE
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeSsOperation,Test_MMI_JudgeSsOperation_02)
{
    VOS_CHAR                            inMmiStr = '0';
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;

    pOutRestMmiStr = &outRestMmiStr;
    MOCKER(VOS_MemCmp)
        .stubs()
        .will(returnValue(0));

    MOCKER(MMI_MatchSsOpTbl)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(MMI_JudgeMmiOperationType)
        .expects(never());
    ASSERT_EQ((MMI_JudgeSsOperation(&inMmiStr,&pOutRestMmiStr,&stMmiOpParam,&ulErrCode)),VOS_FALSE);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,SsOpTbl��δ�ҵ���Ӧ����,����USSD����
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,SsOpTbl��δ�ҵ���Ӧ����,����USSD�����Ĵ���
*Ԥ�ڽ����        ��������VOS_FALSE
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeSsOperation,Test_MMI_JudgeSsOperation_03)
{
    VOS_CHAR                            inMmiStr = '0';
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;

    pOutRestMmiStr = &outRestMmiStr;
    MOCKER(VOS_MemCmp)
        .stubs()
        .will(returnValue(1));

    MOCKER(MMI_JudgeUssdOperation)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(MMI_JudgeMmiOperationType)
        .expects(never());
    ASSERT_EQ((MMI_JudgeSsOperation(&inMmiStr,&pOutRestMmiStr,&stMmiOpParam,&ulErrCode)),VOS_FALSE);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,SsOpTbl��δ�ҵ���Ӧ����,��USSD����
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,SsOpTbl��δ�ҵ���Ӧ����,��USSD�����Ĵ���
*Ԥ�ڽ����        ��������VOS_FALSE
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeSsOperation,Test_MMI_JudgeSsOperation_04)
{
    VOS_CHAR                            inMmiStr = '0';
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;

    pOutRestMmiStr = &outRestMmiStr;
    MOCKER(VOS_MemCmp)
        .stubs()
        .will(returnValue(1));

    MOCKER(MMI_JudgeUssdOperation)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    MOCKER(MMI_JudgeMmiOperationType)
        .expects(exactly(1));
    ASSERT_EQ((MMI_JudgeSsOperation(&inMmiStr,&pOutRestMmiStr,&stMmiOpParam,&ulErrCode)),VOS_TRUE);

    EXPECT_EQ(stMmiOpParam.MmiOperationType,TAF_MMI_PROCESS_USSD_REQ);

    GlobalMockObject::verify();

}


class Test_MMI_JudgeMmiOperationType: public ::testing::Test
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
/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_REGISTER_SS
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_REGISTER_SS�Ĵ���
*Ԥ�ڽ����        ����MMI_FillInRegisterSSPara()���سɹ�
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_01)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_REGISTER_SS;

    MOCKER(MMI_FillInRegisterSSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_ERASE_SS
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_ERASE_SS�Ĵ���
*Ԥ�ڽ����        ����MMI_FillInEraseSSPara()���سɹ�
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_02)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_ERASE_SS;

    MOCKER(MMI_FillInEraseSSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_ACTIVATE_SS
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_ACTIVATE_SS�Ĵ���
*Ԥ�ڽ����        ����MMI_FillInEraseSSPara()���سɹ�
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_03)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_ACTIVATE_SS;

    MOCKER(MMI_FillInActivateSSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_DEACTIVATE_SS
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_DEACTIVATE_SS�Ĵ���
*Ԥ�ڽ����        ����MMI_FillInDeactivateSSPara()���سɹ�
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_04)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_DEACTIVATE_SS;

    MOCKER(MMI_FillInDeactivateSSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_INTERROGATE_SS
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_INTERROGATE_SS�Ĵ���
*Ԥ�ڽ����        ����MMI_FillInInterrogateSSPara()���سɹ�
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_05)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_INTERROGATE_SS;

    MOCKER(MMI_FillInInterrogateSSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_INTERROGATE_CCBS
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_INTERROGATE_CCBS�Ĵ���
*Ԥ�ڽ����        ����MMI_FillInInterrogateSSPara()���سɹ�
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_06)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_CCBS_A_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_INTERROGATE_CCBS;

    MOCKER(MMI_FillInInterrogateSSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}

/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_PROCESS_USSD_REQ
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_PROCESS_USSD_REQ�Ĵ���
*Ԥ�ڽ����        ����MMI_FillInProcessUssdReqPara()���سɹ�
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_07)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_ALL_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_PROCESS_USSD_REQ;

    MOCKER(MMI_FillInProcessUssdReqPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}
#if (NAS_FEATURE_CCBS == FEATURE_ON)
/*******************************************************************
*������:           �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_DEACTIVATE_CCBS
*���⺯����������: �ж��Ƿ��Ǻ����޹ز���ҵ����صĲ���,����������TAF_MMI_DEACTIVATE_CCBS�Ĵ���
*Ԥ�ڽ����        ����MMI_FillInProcessUssdReqPara()���سɹ�
************************* �޸ļ�¼ *************************
#  1.��    ��: 2009��12��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST_F(Test_MMI_JudgeMmiOperationType,Test_MMI_JudgeMmiOperationType_08)
{
    VOS_CHAR                            inMmiStr;
    VOS_CHAR                            *pOutRestMmiStr,outRestMmiStr;
    MN_MMI_OPERATION_PARAM_STRU         stMmiOpParam;
    VOS_UINT32                          ulErrCode;
    MN_MMI_SC_SI_PARA_STRU              stScSiPara;
    VOS_UINT8                           ucNetSsCode = TAF_CCBS_A_SS_CODE;

    pOutRestMmiStr = &outRestMmiStr;

    stMmiOpParam.MmiOperationType = TAF_MMI_DEACTIVATE_CCBS;

    MOCKER(MMI_FillInDeactivateCCBSPara)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MMI_JudgeMmiOperationType(&inMmiStr,&stMmiOpParam,&stScSiPara,&pOutRestMmiStr,&ulErrCode,ucNetSsCode);

    EXPECT_EQ(ulErrCode,MN_ERR_NO_ERROR);

    GlobalMockObject::verify();

}
#endif
