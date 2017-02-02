#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "AtCheckFunc.h"

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
 

TEST(atCheckBasicCmdName,atCheckBasicCmdName_001)
{
    // ��������
    VOS_UINT8                           uchar;
    VOS_UINT32                          ulRst;

    // ������ʼ��
    uchar = 's';

    // ���ȫ�ֱ�����ʼ��


    // MOCKER����;


    // ���ñ��⺯��
    ulRst = atCheckBasicCmdName(uchar);

    // ִ�м��
    EXPECT_EQ(ulRst,AT_SUCCESS);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST(atCheckBasicCmdName,atCheckBasicCmdName_002)
{
    // ��������
    VOS_UINT8                           uchar;
    VOS_UINT32                          ulRst;

    // ������ʼ��
    uchar = 'S';

    // ���ȫ�ֱ�����ʼ��


    // MOCKER����;


    // ���ñ��⺯��
    ulRst = atCheckBasicCmdName(uchar);

    // ִ�м��
    EXPECT_EQ(ulRst,AT_SUCCESS);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST(atCheckBasicCmdName,atCheckBasicCmdName_003)
{
    // ��������
    VOS_UINT8                           uchar;
    VOS_UINT32                          ulRst;

    // ������ʼ��
    uchar = 'o';

    // ���ȫ�ֱ�����ʼ��


    // MOCKER����;


    // ���ñ��⺯��
    ulRst = atCheckBasicCmdName(uchar);

    // ִ�м��
    EXPECT_EQ(ulRst,AT_SUCCESS);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST(atCheckBasicCmdName,atCheckBasicCmdName_004)
{
    // ��������
    VOS_UINT8                           uchar;
    VOS_UINT32                          ulRst;

    // ������ʼ��
    uchar = 'S';

    // ���ȫ�ֱ�����ʼ��


    // MOCKER����;


    // ���ñ��⺯��
    ulRst = atCheckBasicCmdName(uchar);

    // ִ�м��
    EXPECT_EQ(ulRst,AT_SUCCESS);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST(atCheckBasicCmdName,atCheckBasicCmdName_005)
{
    // ��������
    VOS_UINT8                           uchar;
    VOS_UINT32                          ulRst;

    // ������ʼ��
    uchar = 'm';

    // ���ȫ�ֱ�����ʼ��


    // MOCKER����;


    // ���ñ��⺯��
    ulRst = atCheckBasicCmdName(uchar);

    // ִ�м��
    EXPECT_EQ(ulRst,AT_FAILURE);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


#if 0


TEST(Test_AT_CheckMacAddrFormat,���MAC��ַ��ʽ�Ƿ�Ϸ����ڷǷ��ַ�)
{
    // ��������
	VOS_UINT8                          *pucDateStr;
    VOS_UINT32                          ulDateStrLen;
	VOS_UINT8                           auData[30]="00:1E:10:12:FG:16";
	VOS_UINT32                          ulRst;

    // ������ʼ��
    pucDateStr = auData;
	ulDateStrLen = AT_GNA_E5_MAC_ADDR_LEN;

    // ���ȫ�ֱ�����ʼ��


    // MOCKER����;


	// ���ñ��⺯��
    ulRst = AT_CheckMacAddrFormat(pucDateStr,ulDateStrLen);

    // ִ�м��
    EXPECT_EQ(ulRst,AT_FAILURE);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST(Test_AT_CheckMacAddrFormat,���MAC��ַ��ʽ�Ƿ�Ϸ�ð�Ÿ�����Ϊ5)
{
    // ��������
	VOS_UINT8                          *pucDateStr;
    VOS_UINT32                          ulDateStrLen;
	VOS_UINT8                           auData[30]="01";
	VOS_UINT32                          ulRst;

    // ������ʼ��
    pucDateStr = auData;
	ulDateStrLen = strlen((const char*)auData);

    // ���ȫ�ֱ�����ʼ��


    // MOCKER����;


	// ���ñ��⺯��
    ulRst = AT_CheckMacAddrFormat(pucDateStr,ulDateStrLen);

    // ִ�м��
    EXPECT_EQ(ulRst,AT_FAILURE);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST(Test_AT_CheckMacAddrFormat,���MAC��ַ��ʽ�Ƿ�Ϸ�ð�ż��ַ���Ϊ2��)
{
    // ��������
	VOS_UINT8                          *pucDateStr;
    VOS_UINT32                          ulDateStrLen;
	VOS_UINT8                           auData[30]="0:E:0:2:F:6";
	VOS_UINT32                          ulRst;

    // ������ʼ��
    pucDateStr = auData;
	ulDateStrLen = strlen((const char*)auData);

    // ���ȫ�ֱ�����ʼ��


    // MOCKER����;


	// ���ñ��⺯��
    ulRst = AT_CheckMacAddrFormat(pucDateStr,ulDateStrLen);

    // ִ�м��
    EXPECT_EQ(ulRst,AT_SUCCESS);
	EXPECT_EQ(strcmp((const char *)pucDateStr,"00:0E:00:02:0F:06"),0);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST(Test_AT_CheckMacAddrFormat,���MAC��ַ��ʽ�Ƿ�Ϸ���ʽ�Ϸ�)
{
    // ��������
	VOS_UINT8                          *pucDateStr;
    VOS_UINT32                          ulDateStrLen;
	VOS_UINT8                           auData[30]="01:EF:ac:52:Bb:96";
	VOS_UINT32                          ulRst;

    // ������ʼ��
    pucDateStr = auData;
	ulDateStrLen = strlen((const char*)auData);

    // ���ȫ�ֱ�����ʼ��


    // MOCKER����;


	// ���ñ��⺯��
    ulRst = AT_CheckMacAddrFormat(pucDateStr,ulDateStrLen);

    // ִ�м��
    EXPECT_EQ(ulRst,AT_SUCCESS);
	EXPECT_EQ(strcmp((const char *)pucDateStr,"01:EF:ac:52:Bb:96"),0);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



#endif