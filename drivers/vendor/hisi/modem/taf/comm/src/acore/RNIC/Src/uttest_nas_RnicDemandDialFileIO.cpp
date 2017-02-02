#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_RnicDemandDialFileIO.h"


//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;


//˵��: ����������gtest+�������׺Ͳ����������ֲ�����Ϊ��
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


class Test_RNIC_DemandDialFileIO: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();

        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

    }
};


TEST_F( Test_RNIC_DemandDialFileIO, RNIC_TransferStringToInt_001)
{
    VOS_CHAR *pcSting = "5";


    EXPECT_EQ(5, RNIC_TransferStringToInt(pcSting));

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F( Test_RNIC_DemandDialFileIO, RNIC_TransferStringToInt_002)
{
    VOS_CHAR *pcSting = "50";


    EXPECT_EQ(50, RNIC_TransferStringToInt(pcSting));

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F( Test_RNIC_DemandDialFileIO, RNIC_TransferStringToInt_003)
{
    VOS_CHAR *pcSting = "0";


    EXPECT_EQ(0, RNIC_TransferStringToInt(pcSting));

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

#if 0
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_ReadOnDemandFile_001)
{
    struct file    *pstFile;
    char           *pcSrc;
    ssize_t         len;
    VOS_UINT32      ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 5;

    MOCKER(copy_to_user)
        .expects(never());

    RNIC_ReadOnDemandFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_ReadOnDemandFile_002)
{
    struct file    *pstFile;
    char           *pcSrc;
    ssize_t         len;
    VOS_UINT32      ulCnt;
    RNIC_DIAL_MODE_STRU *pstDialMode;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 4;

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode     = RNIC_GetDialModeAddr();

    pstDialMode->enDialMode = RNIC_ALLOW_EVENT_REPORT;

    MOCKER(copy_to_user)
        .with(any(),eq(1),any())
        .expects(exactly(1));

    RNIC_ReadOnDemandFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif

TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteOnDemandFile_001)
{
    struct file    *pstFile;
    char           *pcSrc;
    ssize_t         len;
    VOS_UINT32      ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 5;

    MOCKER(copy_from_user)
        .expects(never());

    RNIC_WriteOnDemandFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#if 0
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteOnDemandFile_002)
{
    struct file    *pstFile;
    char           *pcSrc;
    ssize_t         len;
    VOS_UINT32      ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 4;

    PS_MEM_SET(pstFile, 0x00, 4);


    RNIC_WriteOnDemandFile(pstFile, pcSrc, 4, VOS_NULL_PTR);

    /* ����ƥ�� */
    EXPECT_EQ(1, RNIC_GetDialModeAddr()->enDialMode);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteOnDemandFile_003)
{
    struct file                        *pstFile;
    char                               *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 2;
    pcSrc           = (char *)&ulCnt;
    len             = 4;
    pstPdpAddr      = RNIC_GetPdpCtxAddr();

    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    PS_MEM_SET(pstFile, 0x00, 4);

    RNIC_WriteOnDemandFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* ����ƥ�� */
    EXPECT_EQ(2, RNIC_GetDialModeAddr()->enDialMode);
    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif


TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteOnDemandFile_004)
{
    struct file                        *pstFile;
    char                               *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 0;
    pcSrc           = (char *)&ulCnt;
    len             = 4;
    pstPdpAddr      = RNIC_GetPdpCtxAddr(0);

    PS_MEM_SET(pstFile, 0x00, 4);


    RNIC_WriteOnDemandFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* ����ƥ�� */
    EXPECT_EQ(0, RNIC_GetDialModeAddr()->enDialMode);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#if 0

TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_ReadIdleTimerOutFile_001)
{
    struct file    *pstFile;
    char           *pcSrc;
    ssize_t         len;
    VOS_UINT32      ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 5;

    MOCKER(copy_to_user)
        .expects(never());

    RNIC_ReadIdleTimerOutFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_ReadIdleTimerOutFile_002)
{
    struct file                         *pstFile;
    char                                *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;
    RNIC_DIAL_MODE_STRU                 *pstDialMode;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 4;

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode     = RNIC_GetDialModeAddr();

    pstDialMode->ulIdleTime = 65550;

    MOCKER(copy_to_user)
        .with(any(),eq(65550),any())
        .expects(exactly(1));


    RNIC_ReadIdleTimerOutFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif
#if 0

TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteIdleTimerOutFile_001)
{
    struct file                         *pstFile;
    char                                *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 5;

    MOCKER(copy_from_user)
        .expects(never());

    RNIC_WriteIdleTimerOutFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif
#if 0
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteIdleTimerOutFile_002)
{
    struct file                        *pstFile;
    char                               *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_DIAL_MODE_STRU                *pstDialMode;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 2;
    pcSrc           = (char *)&ulCnt;
    len             = 4;
    pstPdpAddr      = RNIC_GetPdpCtxAddr();

     /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode     = RNIC_GetDialModeAddr();

    pstDialMode->enDialMode               = AT_RNIC_DIAL_MODE_DEMAND;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    PS_MEM_SET(pstFile, 0x00, 4);

    RNIC_WriteIdleTimerOutFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* ����ƥ�� */
    EXPECT_EQ(2, RNIC_GetDialModeAddr()->enDialMode);
    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif
#if 0
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_ReadDialEventReportFile_001)
{
    struct file    *pstFile;
    char           *pcSrc;
    ssize_t         len;
    VOS_UINT32      ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 5;

    MOCKER(copy_to_user)
        .expects(never());

    RNIC_ReadDialEventReportFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_ReadDialEventReportFile_002)
{
    struct file                         *pstFile;
    char                                *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 4;



    MOCKER(copy_to_user)
        .expects(exactly(1));

    RNIC_ReadDialEventReportFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteDialEventReportFile_001)
{
    struct file                         *pstFile;
    char                                *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt            = 1;
    pcSrc           = (char *)&ulCnt;
    len             = 5;

    MOCKER(copy_from_user)
        .expects(never());

    RNIC_WriteDialEventReportFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

#if 0
TEST_F( Test_RNIC_DemandDialFileIO, TEST_RNIC_WriteDialEventReportFile_002)
{
    struct file                        *pstFile;
    char                               *pcSrc;
    ssize_t                             len;
    VOS_UINT32                          ulCnt;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_DIAL_MODE_STRU                *pstDialMode;

    pstFile         = (struct file    *)PS_MEM_ALLOC(ACPU_PID_RNIC, 4);
    ulCnt           = 2;
    pcSrc           = (char *)&ulCnt;
    len             = 4;
    pstPdpAddr      = RNIC_GetPdpCtxAddr();

     /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode     = RNIC_GetDialModeAddr();

    pstDialMode->enDialMode               = AT_RNIC_DIAL_MODE_DEMAND;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_ACTIVE;

    PS_MEM_SET(pstFile, 0x00, 4);

    RNIC_WriteDialEventReportFile(pstFile, pcSrc, len, VOS_NULL_PTR);

    /* ����ƥ�� */
    EXPECT_EQ(2, RNIC_GetDialModeAddr()->enEventReportFlag);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif
class Test_RNIC_InitDemandDialFile: public ::testing::Test
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



TEST_F( Test_RNIC_InitDemandDialFile, Test_RNIC_InitDemandDialFile_001)
{
    MOCKER(kern_path)
        .stubs()
        .will(returnValue(1));

    MOCKER(proc_mkdir)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(proc_create)
        .expects(never());

    EXPECT_EQ(VOS_ERR, RNIC_InitDemandDialFile());

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
TEST_F( Test_RNIC_InitDemandDialFile, Test_RNIC_InitDemandDialFile_002)
{
    struct proc_dir_entry              stProcEntry;



    MOCKER(proc_mkdir)
        .stubs()
        .will(returnValue(&stProcEntry));

    MOCKER(proc_create)
        .expects(never())
        .will(returnValue(VOS_NULL_PTR));

    EXPECT_EQ(VOS_ERR, RNIC_InitDemandDialFile());

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
#if 0
TEST_F( Test_RNIC_InitDemandDialFile, Test_RNIC_InitDemandDialFile_003)
{
    struct proc_dir_entry              stProcEntry;



    MOCKER(proc_mkdir)
        .stubs()
        .will(returnValue(&stProcEntry));

    MOCKER(proc_create)
        .expects(exactly(1))
        .will(returnValue(&stProcEntry));

    MOCKER(proc_create)
        .expects(never())
        .will(returnValue(VOS_NULL_PTR));


    EXPECT_EQ(VOS_ERR, RNIC_InitDemandDialFile());

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
TEST_F( Test_RNIC_InitDemandDialFile, Test_RNIC_InitDemandDialFile_004)
{
    struct proc_dir_entry              stProcEntry;



    MOCKER(proc_mkdir)
        .stubs()
        .will(returnValue(&stProcEntry));

    MOCKER(proc_create)
        .expects(exactly(2))
        .will(returnValue(&stProcEntry));



    MOCKER(proc_create)
        .will(returnValue(VOS_NULL_PTR))
        .expects(never());


    EXPECT_EQ(VOS_ERR, RNIC_InitDemandDialFile());

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
TEST_F( Test_RNIC_InitDemandDialFile, Test_RNIC_InitDemandDialFile_005)
{
    struct proc_dir_entry              stProcEntry;



    MOCKER(proc_mkdir)
        .stubs()
        .will(returnValue(&stProcEntry));



    MOCKER(proc_create)
        .stubs()
        .will(returnValue(&stProcEntry));


    EXPECT_EQ(VOS_OK, RNIC_InitDemandDialFile());

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
#endif

#endif
