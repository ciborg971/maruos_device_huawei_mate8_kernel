#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtBasicCmd.h"


//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_AT_BASICCMD_C

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


class Test_CheckIfDCmdValidChar: public ::testing::Test
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


TEST_F(Test_CheckIfDCmdValidChar, Test_CheckIfDCmdValidChar_001)
{
    VOS_UINT8 ucChar = 'A';
    VOS_UINT32 ulRet = 0;
    ulRet = At_CheckIfDCmdValidChar(ucChar);
    EXPECT_EQ(ulRet,AT_SUCCESS);

    ucChar = 'a';
    ulRet = 0;
    ulRet = At_CheckIfDCmdValidChar(ucChar);
    EXPECT_EQ(ulRet,AT_FAILURE);

    GlobalMockObject::verify();
}


class Test_GetFirstBasicCmdAddr: public ::testing::Test
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


TEST_F(Test_GetFirstBasicCmdAddr, Test_GetFirstBasicCmdAddr_001)
{

    VOS_UINT8 *pData=NULL;
    VOS_UINT32 pulLen=0;
    VOS_UINT8 *pcRet=NULL;

    pData=(VOS_UINT8 *)&"c64416";
    pcRet=At_GetFirstBasicCmdAddr(pData, &pulLen);
    EXPECT_EQ((VOS_UINT_PTR)pcRet,NULL);
    EXPECT_EQ(pulLen,0);

    pData=(VOS_UINT8 *)&"wwD123E45";
    pcRet=At_GetFirstBasicCmdAddr(pData, &pulLen);
    EXPECT_EQ((VOS_UINT_PTR)pcRet,(VOS_UINT_PTR)(pData+2));
    EXPECT_EQ(pulLen,4);

    pData=(VOS_UINT8 *)&"wwE123E45";
    pcRet=At_GetFirstBasicCmdAddr(pData, &pulLen);
    EXPECT_EQ((VOS_UINT_PTR)pcRet,(VOS_UINT_PTR)(pData+2));
    EXPECT_EQ(pulLen,1);

    GlobalMockObject::verify();
}
