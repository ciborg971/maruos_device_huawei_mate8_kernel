#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "v_typdef.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "TafStdlib.h"

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

#define    THIS_FILE_ID        PS_FILE_ID_TAF_STD_LIB_C

extern void UT_STUB_INIT(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


class TEST_TAF_STD_AsciiNum2HexString: public ::testing::Test
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

TEST_F(TEST_TAF_STD_AsciiNum2HexString, TEST_TAF_STD_AsciiNum2HexString_001)
{
    VOS_UINT8               aucDigit[] = "12gf";
    VOS_UINT16              usLength;
    VOS_UINT32              ulRet;

    ulRet = TAF_STD_AsciiNum2HexString(aucDigit, &usLength);

    
    EXPECT_EQ(VOS_FALSE, ulRet);

    // ִ�м��
    GlobalMockObject::verify();

}


TEST_F(TEST_TAF_STD_AsciiNum2HexString, TEST_TAF_STD_AsciiNum2HexString_002)
{
    VOS_UINT8               aucDigit[] = "12fg";
    VOS_UINT16              usLength;
    VOS_UINT32              ulRet;

    ulRet = TAF_STD_AsciiNum2HexString(aucDigit, &usLength);

    
    EXPECT_EQ(VOS_FALSE, ulRet);

    // ִ�м��
    GlobalMockObject::verify();

}


class TEST_TAF_STD_UnPack7Bit: public ::testing::Test
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


TEST_F(TEST_TAF_STD_UnPack7Bit, TEST_TAF_STD_UnPack7Bit_001)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucOrgChar[2];

    ulRet = TAF_STD_UnPack7Bit(VOS_NULL_PTR, 0, 0, VOS_NULL_PTR);

    EXPECT_EQ(VOS_ERR, ulRet);

    PS_MEM_SET(aucOrgChar, 0, sizeof(aucOrgChar));
    ulRet = TAF_STD_UnPack7Bit(aucOrgChar, 0, 0, VOS_NULL_PTR);

    EXPECT_EQ(VOS_ERR, ulRet);

    // ִ�м��
    GlobalMockObject::verify();

}


class TEST_TAF_STD_Pack7Bit: public ::testing::Test
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


TEST_F(TEST_TAF_STD_Pack7Bit, TEST_TAF_STD_Pack7Bit_001)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucOrgChar[] = {0x80, 0x31};
    VOS_UINT8                           aucPackedChar[2];
    VOS_UINT32                          ulLen;

    ulRet = TAF_STD_Pack7Bit(aucOrgChar, sizeof(aucOrgChar), 0, aucPackedChar, &ulLen);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(TEST_TAF_STD_Pack7Bit, TEST_TAF_STD_Pack7Bit_002)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucOrgChar[] = {0x80, 0x31};
    VOS_UINT8                           aucPackedChar[2];
    VOS_UINT32                          ulLen;

    ulRet = TAF_STD_Pack7Bit(aucOrgChar, sizeof(aucOrgChar), 0, aucPackedChar, VOS_NULL_PTR);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}



