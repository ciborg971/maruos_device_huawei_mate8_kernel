#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "MnMsgTs.h"
#include "MnErrorCode.h"
#include "mnmsgcbencdec.h"
#include "TafStdlib.h"
#include "Taf_MmiStrParse.h"



//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_ENCODE_C

extern VOS_UINT32 MSG_EncodeUserData(
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding,
    MN_MSG_USER_DATA_STRU               *pstUserData,
    VOS_UINT8                           *pucUserData,
    VOS_UINT32                          *pucLen
);

extern VOS_UINT32 MN_MSG_DecodeDcsIf01(
    VOS_UINT8                           ucDcs,
    MN_MSG_CBDCS_CODE_STRU              *pstDcsInfo
);

extern MN_MSG_CBLANG_ENUM_U8 MN_MSG_Iso639LangToDef(
    MN_MSG_ISO639_LANG_ENUM_U16         enIso639Lang
);

extern VOS_BOOL MMI_DecodeScAndSi(
                           VOS_CHAR                            *pInMmiStr,
                           MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
                           MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
                           VOS_CHAR                            **ppOutMmiStr
);

extern VOS_BOOL MMI_MatchSsOpTbl(
    VOS_CHAR                            *pInMmiStr,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    MN_MMI_SC_SI_PARA_STRU              *pstScSiPara,
    VOS_CHAR                            **ppOutRestMmiStr,
    VOS_UINT32                          *pulErrCode,
    VOS_UINT8                           *pucNetSsCode
);

extern void UT_STUB_INIT(void);

#ifdef  __cplusplus
  #if  __cplusplus
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


class Test_MN_MSG_EncodeTpRd: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
    }
    void TearDown()
    {

    }
protected:
};


TEST_F(Test_MN_MSG_EncodeTpRd, Test_MN_MSG_EncodeTpRd_001)
{
    /*��������*/
    VOS_BOOL                            bRejectDuplicates;
    VOS_UINT8                           ucTpFo;
    VOS_UINT8                           ucTpCmpFo;

    /* ��ʼ������ */
    ucTpFo = 33;
    bRejectDuplicates = VOS_TRUE;

    /* ȫ�ֱ�����ֵ */

    /* ������Ϣ��ں��� */
    MN_MSG_EncodeTpRd(bRejectDuplicates, &ucTpFo);

    /* �����֤*/
    ucTpCmpFo = ucTpFo | 0x04;
    EXPECT_EQ(ucTpCmpFo, ucTpFo);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}


TEST_F(Test_MN_MSG_EncodeTpRd, Test_MN_MSG_EncodeTpRd_002)
{
    /*��������*/
    VOS_BOOL                            bRejectDuplicates;
    VOS_UINT8                           ucTpFo;
    VOS_UINT8                           ucTpCmpFo;

    /* ��ʼ������ */
    ucTpFo = 33;
    bRejectDuplicates = VOS_FALSE;

    /* ȫ�ֱ�����ֵ */

    /* ������Ϣ��ں��� */
    MN_MSG_EncodeTpRd(bRejectDuplicates, &ucTpFo);

    /* �����֤*/
    ucTpCmpFo = ucTpFo;
    EXPECT_EQ(ucTpCmpFo, ucTpFo);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}



class Test_MN_MSG_EncodeAddress: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
    }
    void TearDown()
    {

    }
protected:
};


TEST_F(Test_MN_MSG_EncodeAddress, Test_MN_MSG_EncodeAddress_001)
{
    /*��������*/
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;
    VOS_UINT8                           aucAddr[255];
    VOS_UINT32                          ulLen;
    VOS_UINT8                           aucAsciiNum[] = {0x80, 0x31};
    VOS_UINT32                          ulRet;

    /* ��ʼ������ */

    /* ȫ�ֱ�����ֵ */

    /* ������Ϣ��ں��� */
    PS_MEM_SET(&stAsciiAddr, 0, sizeof(stAsciiAddr));
    stAsciiAddr.enNumPlan = MN_MSG_NPI_SC_SPECIFIC1;
    stAsciiAddr.enNumType = MN_MSG_TON_ALPHANUMERIC;
    stAsciiAddr.ulLen     = 2;
    PS_MEM_CPY(stAsciiAddr.aucAsciiNum, aucAsciiNum, sizeof(aucAsciiNum));
    PS_MEM_SET(aucAddr, 0, sizeof(aucAddr));
    ulRet = MN_MSG_EncodeAddress(&stAsciiAddr, VOS_FALSE, aucAddr, &ulLen);

    /* �����֤*/
    EXPECT_EQ(MN_ERR_CLASS_INVALID_TP_ADDRESS, ulRet);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}


class Test_MSG_EncodeUserData: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
    }
    void TearDown()
    {

    }
protected:
};


TEST_F(Test_MSG_EncodeUserData, Test_MSG_EncodeUserData_001)
{
    /*��������*/
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding = MN_MSG_MSG_CODING_7_BIT;
    MN_MSG_USER_DATA_STRU               stUserData;
    VOS_UINT8                           aucUserData[255];
    VOS_UINT8                           aucOrigUserData[] = {0x80, 0x31};
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulRet;

    /* ��ʼ������ */

    /* ȫ�ֱ�����ֵ */

    /* ������Ϣ��ں��� */
    PS_MEM_SET(&stUserData, 0, sizeof(stUserData));
    stUserData.ulLen = sizeof(aucOrigUserData);
    ulLen   = 0;
    PS_MEM_CPY(stUserData.aucOrgData, aucOrigUserData, sizeof(aucOrigUserData));
    ulRet = MSG_EncodeUserData(enMsgCoding, &stUserData, aucUserData, &ulLen);

    /* �����֤*/
    EXPECT_EQ(MN_ERR_CLASS_INVALID_TP_UD, ulRet);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}




class Test_MN_MSG_DecodeCbsDcs: public ::testing::Test
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


TEST_F(Test_MN_MSG_DecodeCbsDcs, Test_MN_MSG_DecodeCbsDcs_001)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucDcs;
    VOS_UINT8                           aucContent[TAF_MSG_CBA_LANG_LENGTH] = {0};
    VOS_UINT32                          ulContentLength;
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo = {0};

    // ������ʼ��
    ulContentLength = TAF_MSG_CBA_LANG_LENGTH - 1;
    ucDcs           = 0x10;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRet = MN_MSG_DecodeCbsDcs(ucDcs, aucContent, ulContentLength, &stDcsInfo);

    // ִ�м��
    EXPECT_EQ(MN_ERR_CLASS_SMS_INVALID_MSG_LANG, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_MN_MSG_DecodeCbsDcs, Test_MN_MSG_DecodeCbsDcs_002)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucDcs;
    VOS_UINT8                           aucContent[TAF_MSG_CBA_LANG_LENGTH] = {0};
    VOS_UINT32                          ulContentLength;
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo = {0};

    // ������ʼ��
    ulContentLength = TAF_MSG_CBA_LANG_LENGTH;
    ucDcs           = 0x10;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(MN_MSG_DecodeDcsIf01)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    MOCKER(TAF_STD_UnPack7Bit)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(MN_MSG_Iso639LangToDef)
        .expects(exactly(1))
        .will(returnValue((MN_MSG_CBLANG_ENUM_U8)MN_MSG_CBLANG_ENGLISH));

    // ���ñ��⺯��
    ulRet = MN_MSG_DecodeCbsDcs(ucDcs, aucContent, ulContentLength, &stDcsInfo);

    // ִ�м��
    EXPECT_EQ(MN_ERR_NO_ERROR, ulRet);

    GlobalMockObject::verify();
}



