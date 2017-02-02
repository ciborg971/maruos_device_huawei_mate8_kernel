#include "gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_AdsFilter.h"

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




class Test_ADS_FILTER_InitCtx: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        UT_IMM_STUB_INIT();

    }
    void TearDown()
    {

    }
};


TEST_F(Test_ADS_FILTER_InitCtx, Test_ADS_FILTER_InitCtx_001)
{
    // ��������
    VOS_UINT32                          ulTimeLen;
    VOS_UINT16                          usNvID;

    // ������ʼ��
    usNvID      = en_NV_Item_SHARE_PDP_INFO;
    ulTimeLen   = ADS_FILTER_SECOND_TRANSFER_JIFFIES * ADS_FILTER_DEFAULT_AGING_TIMELEN;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(usNvID), any(), any())
        .will(returnValue(NV_ID_NOT_EXIST));

    MOCKER(ADS_FILTER_InitListsHead)
        .expects(exactly(1));

    MOCKER(ADS_FILTER_ResetIPv6Addr)
        .expects(exactly(1));

    // ���ñ��⺯��
    ADS_FILTER_InitCtx();

    // ִ�м��
    EXPECT_EQ(ulTimeLen, ADS_FILTER_GET_AGING_TIME_LEN());

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_InitCtx, Test_ADS_FILTER_InitCtx_002)
{
    // ��������
    VOS_UINT32                          ulTimeLen;
    VOS_UINT16                          usNvID;
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdp = {0};

    // ������ʼ��
    usNvID      = en_NV_Item_SHARE_PDP_INFO;
    ulTimeLen   = ADS_FILTER_SECOND_TRANSFER_JIFFIES * 10;
    stSharePdp.ucEnableFlag     = VOS_TRUE;
    stSharePdp.usAgingTimeLen   = 10;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(usNvID), outBoundP((void *)&stSharePdp, sizeof(stSharePdp)), any())
        .will(returnValue(NV_OK));

    MOCKER(ADS_FILTER_InitListsHead)
        .expects(exactly(1));

    MOCKER(ADS_FILTER_ResetIPv6Addr)
        .expects(exactly(1));

    // ���ñ��⺯��
    ADS_FILTER_InitCtx();

    // ִ�м��
    EXPECT_EQ(ulTimeLen, ADS_FILTER_GET_AGING_TIME_LEN());

    GlobalMockObject::verify();
}


class Test_ADS_FILTER_HeapAlloc: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        UT_IMM_STUB_INIT();

    }
    void TearDown()
    {

    }
};


TEST_F(Test_ADS_FILTER_HeapAlloc, Test_ADS_FILTER_HeapAlloc_001)
{
    // ��������
    VOS_VOID                           *pPointer = VOS_NULL_PTR;

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    pPointer = ADS_FILTER_HeapAlloc(-1);

    // ִ�м��
    EXPECT_EQ(VOS_NULL_PTR, pPointer);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_HeapAlloc, Test_ADS_FILTER_HeapAlloc_002)
{
    // ��������
    VOS_VOID                           *pPointer = VOS_NULL_PTR;

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    pPointer = ADS_FILTER_HeapAlloc(1025);

    // ִ�м��
    EXPECT_EQ(VOS_NULL_PTR, pPointer);

    GlobalMockObject::verify();
}


class Test_ADS_FILTER_HeapFree: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        UT_IMM_STUB_INIT();

    }
    void TearDown()
    {

    }
};


TEST_F(Test_ADS_FILTER_HeapFree, Test_ADS_FILTER_HeapFree_001)
{
    // ��������

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ADS_FILTER_HeapFree(VOS_NULL_PTR);

    // ִ�м��

    GlobalMockObject::verify();
}


class Test_ADS_FILTER_AddFilter: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* ��ʼ�����˱�ͷ�ڵ� */
        ADS_FILTER_InitListsHead();

    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* ���ù��˱� */
        ADS_FILTER_ResetLists();

         GlobalMockObject::verify();

    }
};


TEST_F(Test_ADS_FILTER_AddFilter, Test_ADS_FILTER_AddFilter_001)
{
    // ��������
    VOS_UINT8                           ucIndex;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // ������ʼ��
    stFilter.enPktType              = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.stIPHeader.ulSrcAddr   = 0x6400A8C0;   //192.168.0.100
    stFilter.stIPHeader.ulDstAddr   = 0x3B31520A;   //10.82.49.59
    stFilter.stIPHeader.ucProtocol  = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x5000;   //80

    ucIndex = stFilter.unFilter.stTcpFilter.usSrcPort & 0xFF;

    // ��ʼ��ȫ�ֱ���
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);

    // MOCKER����
    MOCKER(ADS_FILTER_HeapAlloc)
        .expects(exactly(1))
        .will(returnValue((void *)VOS_NULL_PTR));

    // ���ñ��⺯��
    ADS_FILTER_AddFilter(&stFilter);

    // ִ�м��
    EXPECT_EQ(pstListHead, pstListHead->next);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_AddFilter, Test_ADS_FILTER_AddFilter_002)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    ADS_FILTER_NODE_STRU                stNode          = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter       = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // ������ʼ��
    pstFilter   = &stNode.stFilter;
    pstFilter->enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    pstFilter->ulTmrCnt                 = 1000;
    pstFilter->stIPHeader.ulSrcAddr     = 0x6400A8C0;   //192.168.0.100
    pstFilter->stIPHeader.ulDstAddr     = 0x3B31520A;   //10.82.49.59
    pstFilter->stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    pstFilter->unFilter.stTcpFilter.usSrcPort = 0x5000; //80
    pstFilter->unFilter.stTcpFilter.usDstPort = 0x5000; //80

    ucIndex = (pstFilter->unFilter.stTcpFilter.usSrcPort & 0xFF00) >> 8;

    // ��ʼ��ȫ�ֱ���
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);

    // MOCKER����

    // ���ñ��⺯��
    ADS_FILTER_AddFilter(pstFilter);

    // ִ�м��
    pstNode = msp_list_entry(pstListHead->next, ADS_FILTER_NODE_STRU, stList);
    ulRet = PS_MEM_CMP(&pstNode->stFilter, pstFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));
    EXPECT_EQ(0, ulRet);

    GlobalMockObject::verify();
}


class Test_ADS_FILTER_IsInfoMatch: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* ��ʼ�����˱�ͷ�ڵ� */
        ADS_FILTER_InitListsHead();

    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /* ���ù��˱� */
        ADS_FILTER_ResetLists();

         GlobalMockObject::verify();

    }
};


TEST_F(Test_ADS_FILTER_IsInfoMatch, Test_ADS_FILTER_IsInfoMatch_001)
{
    // ��������
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter1 = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilter2 = {0};

    // ������ʼ��
    stFilter1.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter1.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter1.stIPHeader.ucProtocol     = ADS_IPPROTO_UDP;

    stFilter2.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter2.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter2.stIPHeader.ucProtocol     = ADS_IPPROTO_TCP;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_IsInfoMatch(&stFilter1, &stFilter2);

    // ִ�м��
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_IsInfoMatch, Test_ADS_FILTER_IsInfoMatch_002)
{
    // ��������
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter1 = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilter2 = {0};

    // ������ʼ��
    stFilter1.enPktType                 = ADS_FILTER_PKT_TYPE_TCP;
    stFilter1.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter1.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter1.stIPHeader.ucProtocol     = ADS_IPPROTO_TCP;
    stFilter1.unFilter.stTcpFilter.usSrcPort = 0x5000;  //80
    stFilter1.unFilter.stTcpFilter.usDstPort = 0x5000;  //80

    stFilter2   = stFilter1;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_IsInfoMatch(&stFilter1, &stFilter2);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_IsInfoMatch, Test_ADS_FILTER_IsInfoMatch_003)
{
    // ��������
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter1 = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilter2 = {0};

    // ������ʼ��
    stFilter1.enPktType                 = ADS_FILTER_PKT_TYPE_UDP;
    stFilter1.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter1.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter1.stIPHeader.ucProtocol     = ADS_IPPROTO_UDP;
    stFilter1.unFilter.stUdpFilter.usSrcPort = 0x5000;  //80
    stFilter1.unFilter.stUdpFilter.usDstPort = 0x901F;  //8080

    stFilter2   = stFilter1;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_IsInfoMatch(&stFilter1, &stFilter2);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_IsInfoMatch, Test_ADS_FILTER_IsInfoMatch_004)
{
    // ��������
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter1 = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilter2 = {0};

    // ������ʼ��
    stFilter1.enPktType                 = ADS_FILTER_PKT_TYPE_ICMP;
    stFilter1.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter1.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter1.stIPHeader.ucProtocol     = ADS_IPPROTO_ICMP;
    stFilter1.unFilter.stIcmpFilter.usIdentifier    = 0x1806;   //1560
    stFilter1.unFilter.stIcmpFilter.usSeqNum        = 0x0F00;   //15

    stFilter2   = stFilter1;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_IsInfoMatch(&stFilter1, &stFilter2);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_IsInfoMatch, Test_ADS_FILTER_IsInfoMatch_005)
{
    // ��������
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter1 = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilter2 = {0};

    // ������ʼ��
    stFilter1.enPktType                 = ADS_FILTER_PKT_TYPE_FRAGMENT;
    stFilter1.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter1.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter1.stIPHeader.ucProtocol     = ADS_IPPROTO_UDP;
    stFilter1.unFilter.stFragmentFilter.usIdentification = 0xFB00; //251

    stFilter2   = stFilter1;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_IsInfoMatch(&stFilter1, &stFilter2);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_IsInfoMatch, Test_ADS_FILTER_IsInfoMatch_006)
{
    // ��������
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter1 = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilter2 = {0};

    // ������ʼ��
    stFilter1.enPktType                 = ADS_FILTER_PKT_TYPE_BUTT;
    stFilter1.stIPHeader.ulSrcAddr      = 0x6400A8C0;   //192.168.0.100
    stFilter1.stIPHeader.ulDstAddr      = 0x3B31520A;   //10.82.49.59
    stFilter1.stIPHeader.ucProtocol     = ADS_IPPROTO_IGMP;

    stFilter2   = stFilter1;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_IsInfoMatch(&stFilter1, &stFilter2);

    // ִ�м��
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


class Test_ADS_FILTER_Match: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* ��ʼ�����˱�ͷ�ڵ� */
        ADS_FILTER_InitListsHead();

    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* ���ù��˱� */
        ADS_FILTER_ResetLists();

        GlobalMockObject::verify();
    }
};


TEST_F(Test_ADS_FILTER_Match, Test_ADS_FILTER_Match_001)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_IPV4_INFO_STRU           stFilterTmp     = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // ������ʼ��
    jiffies     = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;   //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;   //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x5000;   //80

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME() - 1000;
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;   //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3C31520A;   //10.82.49.60
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;   //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3C31520A;   //10.82.49.60
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stUdpFilter.usDstPort = 0x1500;   //21

    stFilterTmp = stFilter;

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;   //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3D31520A;    //10.82.49.61
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    // ��ʼ��ȫ�ֱ���
    ADS_FILTER_SET_AGING_TIME_LEN(2000);
    jiffies     = 9000;

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_Match(&stFilterTmp);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, ulRet);
    ucIndex     = ADS_FILTER_GET_INDEX(&stFilter);
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);
    pstNode     = msp_list_entry(pstListHead->next->next, ADS_FILTER_NODE_STRU, stList);
    EXPECT_EQ(9000, pstNode->stFilter.ulTmrCnt);
    EXPECT_EQ(0x1500, pstNode->stFilter.unFilter.stUdpFilter.usDstPort);

    GlobalMockObject::verify();
}


class Test_ADS_FILTER_SaveIPAddrInfo: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        ADS_FILTER_ResetIPv6Addr();

    }
    void TearDown()
    {

    }
};


TEST_F(Test_ADS_FILTER_SaveIPAddrInfo, Test_ADS_FILTER_SaveIPAddrInfo_001)
{
    // ��������
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr  = {0};
    ADS_IPV6_ADDR_UN                    unIPv6Addr      = {0};
    VOS_UINT8                           ucRslt;

    // ������ʼ��
    stFilterIpAddr.bitOpIpv6Addr    = VOS_TRUE;
    stFilterIpAddr.aucIpv6Addr[0]   = 200;
    stFilterIpAddr.aucIpv6Addr[1]   = 10;
    stFilterIpAddr.aucIpv6Addr[2]   = 20;
    stFilterIpAddr.aucIpv6Addr[3]   = 30;
    stFilterIpAddr.aucIpv6Addr[10]  = 11;
    stFilterIpAddr.aucIpv6Addr[11]  = 120;
    stFilterIpAddr.aucIpv6Addr[12]  = 130;
    stFilterIpAddr.aucIpv6Addr[13]  = 140;
    stFilterIpAddr.aucIpv6Addr[14]  = 1;
    stFilterIpAddr.aucIpv6Addr[15]  = 2;
    memcpy(unIPv6Addr.aucIpAddr, stFilterIpAddr.aucIpv6Addr, ADS_IPV6_ADDR_LEN);

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ADS_FILTER_SaveIPAddrInfo(&stFilterIpAddr);

    // ִ�м��
    ucRslt = ADS_FILTER_IS_IPV6_ADDR_IDENTICAL(&unIPv6Addr, ADS_FILTER_GET_IPV6_ADDR()) ? 0 : 1;
    EXPECT_EQ(0, ucRslt);

    GlobalMockObject::verify();
}


class Test_ADS_FILTER_ProcUlPacket: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /* ���ÿ�ά�ɲ���Ϣ */
        ADS_FILTER_ResetStatisticInfo();

        /* ��ʼ�����˱�ͷ�ڵ� */
        ADS_FILTER_InitListsHead();
    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* ���ù��˱� */
        ADS_FILTER_ResetLists();
        GlobalMockObject::verify();
    }
};
TEST_F(Test_ADS_FILTER_ProcUlPacket, Test_ADS_FILTER_ProcUlPacket_001)
{
    // ��������
    IMM_ZC_STRU                         stZcData = {0};

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV6);

    // ִ�м��
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV6_PKT));

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcUlPacket, Test_ADS_FILTER_ProcUlPacket_002)
{
    // ��������
    IMM_ZC_STRU                         stZcData    = {0};
    VOS_UINT8                           aucData[]   =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02,
        0xBA, 0x2D, 0xC0, 0xA8, 0x01, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x11, 0x00, 0x0D, 0xFD, 0xE0, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    // ������ʼ��
    stZcData.data = aucData;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(ADS_FILTER_Match)
        .expects(never());

    // ���ñ��⺯��
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT));

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcUlPacket, Test_ADS_FILTER_ProcUlPacket_003)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData    = {0};
    VOS_UINT8                           aucData[]   =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
        0xBB, 0x29, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x00, 0x50, 0x1F, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           ucIndex;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // ������ʼ��
    stZcData.data   = aucData;
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    // ��ʼ��ȫ�ֱ���
    ADS_FILTER_SET_AGING_TIME_LEN(2000);

    // MOCKER����

    // ���ñ��⺯����һ��
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    ucIndex     = ADS_FILTER_GET_INDEX(&stFilter);
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);
    pstNode     = msp_list_entry(pstListHead->next, ADS_FILTER_NODE_STRU, stList);
    ulRet       = memcmp(&stFilter, &pstNode->stFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_TCP));
    EXPECT_EQ(0, ulRet);

    // ���ñ��⺯���ڶ���
    jiffies     = 9000;
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    stFilter.ulTmrCnt   = ADS_GET_CURR_KERNEL_TIME();
    ulRet               = memcmp(&stFilter, &pstNode->stFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));
    EXPECT_EQ(2, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_TCP));
    EXPECT_EQ(0, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcUlPacket, Test_ADS_FILTER_ProcUlPacket_004)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData    = {0};
    VOS_UINT8                           aucData1[]   =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x00, 0x00, 0x4D, 0xC1, 0x00, 0x9C, 0x00, 0x0F, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           aucData2[]   =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x08, 0x00, 0x45, 0xC1, 0x00, 0x9C, 0x00, 0x0F, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           ucIndex;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // ������ʼ��
    stZcData.data   = aucData1;
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_ICMP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_ICMP;
    stFilter.unFilter.stIcmpFilter.usIdentifier = 0x9C00;   //156
    stFilter.unFilter.stIcmpFilter.usSeqNum     = 0x0F00;   //15

    // ��ʼ��ȫ�ֱ���
    ADS_FILTER_SET_AGING_TIME_LEN(2000);

    // MOCKER����

    // ���ñ��⺯����һ��
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    ucIndex     = ADS_FILTER_GET_INDEX(&stFilter);
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT));
    EXPECT_EQ((VOS_UINT_PTR)pstListHead, (VOS_UINT_PTR)pstListHead->next);

    // ���ñ��⺯���ڶ���
    stZcData.data   = aucData2;
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    pstNode     = msp_list_entry(pstListHead->next, ADS_FILTER_NODE_STRU, stList);
    ulRet       = memcmp(&stFilter, &pstNode->stFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_ECHOREQ));
    EXPECT_EQ(0, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcUlPacket, Test_ADS_FILTER_ProcUlPacket_005)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData    = {0};
    VOS_UINT8                           aucData[]   =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x11,
        0xBB, 0x1E, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x00, 0x44, 0x00, 0x44, 0x00, 0x1E, 0x50, 0xFD, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           ucIndex;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // ������ʼ��
    stZcData.data   = aucData;
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x4400;   //68
    stFilter.unFilter.stUdpFilter.usDstPort = 0x4400;   //68

    // ��ʼ��ȫ�ֱ���
    ADS_FILTER_SET_AGING_TIME_LEN(2000);

    // MOCKER����

    // ���ñ��⺯��
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    ucIndex     = ADS_FILTER_GET_INDEX(&stFilter);
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);
    pstNode     = msp_list_entry(pstListHead->next, ADS_FILTER_NODE_STRU, stList);
    ulRet       = memcmp(&stFilter, &pstNode->stFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_UDP));
    EXPECT_EQ(0, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcUlPacket, Test_ADS_FILTER_ProcUlPacket_006)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData    = {0};
    VOS_UINT8                           aucData[]   =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x01, 0x03, 0x11,
        0xBB, 0x1E, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x00, 0x44, 0x00, 0x44, 0x00, 0x1E, 0x50, 0xFD, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           ucIndex;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // ������ʼ��
    stZcData.data   = aucData;
    jiffies         = 8000;

        // ��ʼ��ȫ�ֱ���
    ADS_FILTER_SET_AGING_TIME_LEN(2000);

    // MOCKER����

    // ���ñ��⺯��
    ADS_FILTER_ProcUlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��

    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_FIRST_FRAGMENT));

    GlobalMockObject::verify();
}


class Test_ADS_FILTER_ProcDlPacket: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* ���ÿ�ά�ɲ���Ϣ */
        ADS_FILTER_ResetStatisticInfo();

        /* ��ʼ�����˱�ͷ�ڵ� */
        ADS_FILTER_InitListsHead();
    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        /* ���ù��˱� */
        ADS_FILTER_ResetLists();
        GlobalMockObject::verify();
    }
};
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_001)
{
    // ��������
    VOS_UINT32                          ulRet;
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr  = {0};
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x60, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x06, 0xFF, 0x20, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5E, 0xFE,
        0xC0, 0xA8, 0x01, 0x01, 0x20, 0x02, 0xD3, 0x01, 0x01, 0x01,
        0x00, 0x01, 0x02, 0xE0, 0xDD, 0xFF, 0xFE, 0xE0, 0xE0, 0xE1,
        0x00, 0x50, 0x1F, 0x90, 0x00, 0x00, 0xCF, 0x3C, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x3C, 0xCF, 0x00, 0x00
    };

    // ������ʼ��
    stZcData.data   = aucData;
    stFilterIpAddr.bitOpIpv6Addr    = VOS_TRUE;

    /* IPv6: 2002:D301:0101:0001:02E0:DDFF:FEE0:E0E2 */
    stFilterIpAddr.aucIpv6Addr[0]   = 0x20;
    stFilterIpAddr.aucIpv6Addr[1]   = 0x02;
    stFilterIpAddr.aucIpv6Addr[2]   = 0xD3;
    stFilterIpAddr.aucIpv6Addr[3]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[4]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[5]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[6]   = 0x00;
    stFilterIpAddr.aucIpv6Addr[7]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[8]   = 0x02;
    stFilterIpAddr.aucIpv6Addr[9]   = 0xE0;
    stFilterIpAddr.aucIpv6Addr[10]  = 0xDD;
    stFilterIpAddr.aucIpv6Addr[11]  = 0xFF;
    stFilterIpAddr.aucIpv6Addr[12]  = 0xFE;
    stFilterIpAddr.aucIpv6Addr[13]  = 0xE0;
    stFilterIpAddr.aucIpv6Addr[14]  = 0xE0;
    stFilterIpAddr.aucIpv6Addr[15]  = 0xE2;

    // ��ʼ��ȫ�ֱ���
    ADS_FILTER_SaveIPAddrInfo(&stFilterIpAddr);

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV6);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_002)
{
    // ��������
    VOS_UINT32                          ulRet;
    ADS_FILTER_IP_ADDR_INFO_STRU        stFilterIpAddr  = {0};
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x60, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x06, 0xFF, 0x20, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5E, 0xFE,
        0xC0, 0xA8, 0x01, 0x01, 0x20, 0x02, 0xD3, 0x01, 0x01, 0x01,
        0x00, 0x01, 0x02, 0xE0, 0xDD, 0xFF, 0xFE, 0xE0, 0xE0, 0xE1,
        0x00, 0x50, 0x1F, 0x90, 0x00, 0x00, 0xCF, 0x3C, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x3C, 0xCF, 0x00, 0x00
    };

    // ������ʼ��
    stZcData.data   = aucData;
    stFilterIpAddr.bitOpIpv6Addr    = VOS_TRUE;

    /* IPv6: 2002:D301:0101:0001:02E0:DDFF:FEE0:E0E2 */
    stFilterIpAddr.aucIpv6Addr[0]   = 0x20;
    stFilterIpAddr.aucIpv6Addr[1]   = 0x02;
    stFilterIpAddr.aucIpv6Addr[2]   = 0xD3;
    stFilterIpAddr.aucIpv6Addr[3]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[4]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[5]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[6]   = 0x00;
    stFilterIpAddr.aucIpv6Addr[7]   = 0x01;
    stFilterIpAddr.aucIpv6Addr[8]   = 0x02;
    stFilterIpAddr.aucIpv6Addr[9]   = 0xE0;
    stFilterIpAddr.aucIpv6Addr[10]  = 0xDD;
    stFilterIpAddr.aucIpv6Addr[11]  = 0xFF;
    stFilterIpAddr.aucIpv6Addr[12]  = 0xFE;
    stFilterIpAddr.aucIpv6Addr[13]  = 0xE0;
    stFilterIpAddr.aucIpv6Addr[14]  = 0xE0;
    stFilterIpAddr.aucIpv6Addr[15]  = 0xE1;

    // ��ʼ��ȫ�ֱ���
    ADS_FILTER_SaveIPAddrInfo(&stFilterIpAddr);

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV6);
    ADS_FILTER_ShowIPv6Addr();

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV6_PKT));

    GlobalMockObject::verify();
}
TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_003)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_BUTT);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_004)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02,
        0xBB, 0x2D, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x11, 0x00, 0x0D, 0xFD, 0xE0, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    // ������ʼ��
    stZcData.data   = aucData;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_005)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
        0xBB, 0x29, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x1F, 0x90, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // ������ʼ��
    stZcData.data   = aucData;

    // ��ʼ��ȫ�ֱ���
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_TCP));

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_006)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
        0xBB, 0x29, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x1F, 0x90, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // ������ʼ��
    stZcData.data   = aucData;

    // ��ʼ��ȫ�ֱ���
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3C31520A;     //10.82.49.60
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_TCP));

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_007)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x11,
        0xBB, 0x1E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x43, 0x00, 0x44, 0x00, 0x1E, 0x1F, 0x30, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // ������ʼ��
    stZcData.data   = aucData;

    // ��ʼ��ȫ�ֱ���
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x4400;   //68
    stFilter.unFilter.stUdpFilter.usDstPort = 0x4300;   //67

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_UDP));

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_008)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x11,
        0xBB, 0x1E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x43, 0x00, 0x44, 0x00, 0x1E, 0x1F, 0x30, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // ������ʼ��
    stZcData.data   = aucData;

    // ��ʼ��ȫ�ֱ���
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3C31520A;     //10.82.49.60
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x4400;   //68
    stFilter.unFilter.stUdpFilter.usDstPort = 0x4300;   //67

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_UDP));

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_009)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x00, 0x33, 0x46, 0x00, 0x9C, 0x00, 0x0F, 0x01, 0x01,
        0x00, 0x01, 0x02, 0xE0, 0xDD, 0xFF, 0xFE, 0xE0, 0xE0, 0xE1,
        0x81, 0x00, 0x89, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // ������ʼ��
    stZcData.data   = aucData;

    // ��ʼ��ȫ�ֱ���
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_ICMP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_ICMP;
    stFilter.unFilter.stIcmpFilter.usIdentifier = 0x9C00;   //156
    stFilter.unFilter.stIcmpFilter.usSeqNum     = 0x0F00;   //15

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_ECHOREPLY));

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_010)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x10, 0x00, 0x23, 0x46, 0x00, 0x9C, 0x00, 0x0F, 0x01, 0x01,
        0x00, 0x01, 0x02, 0xE0, 0xDD, 0xFF, 0xFE, 0xE0, 0xE0, 0xE1,
        0x81, 0x00, 0x89, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // ������ʼ��
    stZcData.data   = aucData;

    // ��ʼ��ȫ�ֱ���
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_ICMP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_ICMP;
    stFilter.unFilter.stIcmpFilter.usIdentifier = 0x9C00;   //156
    stFilter.unFilter.stIcmpFilter.usSeqNum     = 0x0F00;   //15

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_011)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x0B, 0x00, 0x33, 0x46, 0x00, 0x9C, 0x00, 0x0F,

        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
        0xBB, 0x29, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x00, 0x50, 0x1F, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // ������ʼ��
    stZcData.data   = aucData;

    // ��ʼ��ȫ�ֱ���
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR));

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_012)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x0B, 0x00, 0x33, 0x46, 0x00, 0x9C, 0x00, 0x0F,

        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x11,
        0xBB, 0x1E, 0xC0, 0xA8, 0x00, 0x64, 0x0A, 0x52, 0x31, 0x3B,
        0x00, 0x44, 0x00, 0x43, 0x00, 0x1E, 0x50, 0xFD, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x61, 0x93, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // ������ʼ��
    stZcData.data   = aucData;

    // ��ʼ��ȫ�ֱ���
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x4400;   //68
    stFilter.unFilter.stUdpFilter.usDstPort = 0x4300;   //67

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR));

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_013)
{
    // ��������
    VOS_UINT32                          ulRet;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x0B, 0x00, 0x33, 0x46, 0x00, 0x9C, 0x00, 0x0F,

        0x45, 0x04, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01,
        0xBB, 0x2E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x00, 0x33, 0x46, 0x00, 0x9C, 0x00, 0x0F, 0x01, 0x01,
        0x00, 0x01, 0x02, 0xE0, 0xDD, 0xFF, 0xFE, 0xE0, 0xE0, 0xE1,
        0x81, 0x00, 0x89, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // ������ʼ��
    stZcData.data   = aucData;

    // ��ʼ��ȫ�ֱ���
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_ICMP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_ICMP;
    stFilter.unFilter.stIcmpFilter.usIdentifier = 0x9C00;   //156
    stFilter.unFilter.stIcmpFilter.usSeqNum     = 0x0F00;   //15

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_014)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData1[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0xC0, 0x20, 0x00, 0x03, 0x06,
        0xBA, 0x29, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x1F, 0x90, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           aucData2[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0xC0, 0x20, 0x3F, 0x03, 0x06,
        0xB9, 0xEA, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // ������ʼ��
    stZcData.data   = aucData1;

    // ��ʼ��ȫ�ֱ���
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_FRAGMENT;
    stFilter.unFilter.stFragmentFilter.usIdentification = 0xC000;   //192
    stFilter.unFilter.stFragmentFilter.aucReserved[0]   = 0;
    stFilter.unFilter.stFragmentFilter.aucReserved[1]   = 0;

    // MOCKER����

    // ���ñ��⺯�� ��Ƭ
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    ucIndex     = ADS_FILTER_GET_INDEX(&stFilter);
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);
    pstNode     = msp_list_entry(pstListHead->next, ADS_FILTER_NODE_STRU, stList);
    ulRslt      = memcmp(&stFilter, &pstNode->stFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT));
    EXPECT_EQ(0, ulRslt);

    // ���ñ��⺯�� ����Ƭ
    stZcData.data   = aucData2;
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_NOT_FIRST_FRAGMENT));

    ADS_FILTER_ShowStatisticInfo();

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_015)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData1[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0xC0, 0x20, 0x00, 0x03, 0x11,
        0xBB, 0x1E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x43, 0x00, 0x44, 0x00, 0x1E, 0x1F, 0x30, 0x00, 0x00,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    VOS_UINT8                           aucData2[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x00, 0xC0, 0x20, 0x3F, 0x03, 0x11,
        0xB9, 0x1E, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x93, 0x61, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;

    // ������ʼ��
    stZcData.data   = aucData1;

    // ��ʼ��ȫ�ֱ���
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x4400;   //68
    stFilter.unFilter.stUdpFilter.usDstPort = 0x4300;   //67

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_FRAGMENT;
    stFilter.unFilter.stFragmentFilter.usIdentification = 0xC000;   //192
    stFilter.unFilter.stFragmentFilter.aucReserved[0]   = 0;
    stFilter.unFilter.stFragmentFilter.aucReserved[1]   = 0;

    // MOCKER����

    // ���ñ��⺯�� ��Ƭ
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    ucIndex     = ADS_FILTER_GET_INDEX(&stFilter);
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);
    pstNode     = msp_list_entry(pstListHead->next, ADS_FILTER_NODE_STRU, stList);
    ulRslt      = memcmp(&stFilter, &pstNode->stFilter, sizeof(ADS_FILTER_IPV4_INFO_STRU));

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT));
    EXPECT_EQ(0, ulRslt);

    // ���ñ��⺯�� ����Ƭ
    stZcData.data   = aucData2;
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(1, ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_NOT_FIRST_FRAGMENT));

    GlobalMockObject::verify();
}


TEST_F(Test_ADS_FILTER_ProcDlPacket, Test_ADS_FILTER_ProcDlPacket_016)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    IMM_ZC_STRU                         stZcData        = {0};
    VOS_UINT8                           aucData[]       =
    {
        0x45, 0x04, 0x00, 0x32, 0x0C, 0x00, 0x20, 0x00, 0x03, 0x02,
        0xAD, 0x2D, 0x0A, 0x52, 0x31, 0x3B, 0xC0, 0xA8, 0x00, 0x64,
        0x11, 0x00, 0x0D, 0xFD, 0xE0, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    // ������ʼ��
    stZcData.data   = aucData;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯�� ��Ƭ
    ulRet = ADS_FILTER_ProcDlPacket(&stZcData, ADS_PKT_TYPE_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


class Test_ADS_Ipv4AddrItoa: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

    }
    void TearDown()
    {

    }
};


TEST_F(Test_ADS_Ipv4AddrItoa, Test_ADS_Ipv4AddrItoa_001)
{
    // ��������
    VOS_UINT32                          ulRet;

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRet = ADS_Ipv4AddrItoa(VOS_NULL_PTR, VOS_NULL_PTR);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRet);

    GlobalMockObject::verify();
}


class Test_ADS_FILTER_ShowFilterLists: public ::testing::Test
{
public:
    void SetUp()
	{
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* ��ʼ�����˱�ͷ�ڵ� */
        ADS_FILTER_InitListsHead();
    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();
        /* ���ù��˱� */
        ADS_FILTER_ResetLists();
        GlobalMockObject::verify();
    }
};


TEST_F(Test_ADS_FILTER_ShowFilterLists, Test_ADS_FILTER_ShowFilterLists_001)
{
    // ��������
    VOS_UINT32                          ulRet;
    ADS_FILTER_IPV4_INFO_STRU           stFilter        = {0};

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    jiffies         = 8000;

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_TCP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3C31520A;     //10.82.49.60
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_UDP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3C31520A;     //10.82.49.60
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_UDP;
    stFilter.unFilter.stUdpFilter.usSrcPort = 0x4400;   //68
    stFilter.unFilter.stUdpFilter.usDstPort = 0x4300;   //67

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_ICMP;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_ICMP;
    stFilter.unFilter.stIcmpFilter.usIdentifier = 0x9C00;   //156
    stFilter.unFilter.stIcmpFilter.usSeqNum     = 0x0F00;   //15

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_FRAGMENT;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    stFilter.enPktType                = ADS_FILTER_PKT_TYPE_BUTT;
    stFilter.ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();
    stFilter.stIPHeader.ulSrcAddr     = 0x6400A8C0;     //192.168.0.100
    stFilter.stIPHeader.ulDstAddr     = 0x3B31520A;     //10.82.49.59
    stFilter.stIPHeader.ucProtocol    = ADS_IPPROTO_TCP;
    stFilter.unFilter.stTcpFilter.usSrcPort = 0x5000;   //80
    stFilter.unFilter.stTcpFilter.usDstPort = 0x901F;   //8080

    ADS_FILTER_AddFilter(&stFilter);

    // MOCKER����

    // ���ñ��⺯��
    ADS_FILTER_ShowFilterLists();

    // ִ�м��

    GlobalMockObject::verify();
}


