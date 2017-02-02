#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include <stdio.h>
#include <stdlib.h>

//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#ifdef __cplusplus
extern "C"
{
#endif
    extern int mdrv_edma_bbp_sample_reboot(void);


    extern void uttest_Om_AcpuBbpConfigMsgProc_case1(void);
    extern void uttest_Om_AcpuBbpConfigMsgProc_case2(void);
    extern void uttest_Om_AcpuBbpConfigMsgProc_case3(void);
    extern unsigned int uttest_Om_AcpuDumpReboot_case1(void);
    extern unsigned int Om_AcpuDumpReboot(void *pstAppToOmMsg, unsigned short usReturnPrimId);
    extern void OM_AcpuSendResultChannel(unsigned int enChannel, unsigned char ucFuncType,
        unsigned int ulResult, unsigned short usReturnPrimId);
#ifdef __cplusplus
}
#endif

#ifndef VOS_OK
#define VOS_OK                          0
#endif

#ifndef VOS_ERR
#define VOS_ERR                         1
#endif



TEST(Om_AcpuBbpConfigMsgProc1, UT)
{
	MOCKER(Om_AcpuDumpReboot)
	    .stubs()
		.will(returnValue((unsigned int)VOS_OK));

	uttest_Om_AcpuBbpConfigMsgProc_case1();

    GlobalMockObject::reset();
}


TEST(Om_AcpuBbpConfigMsgProc2, UT)
{
	MOCKER(OM_AcpuSendResultChannel)
        .expects(once());

	uttest_Om_AcpuBbpConfigMsgProc_case2();

    GlobalMockObject::reset();
}


TEST(Om_AcpuBbpConfigMsgProc3, UT)
{
	MOCKER(Om_AcpuDumpReboot)
	    .stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	uttest_Om_AcpuBbpConfigMsgProc_case3();

	GlobalMockObject::reset();
}


TEST(Om_AcpuDumpReboot, UT)
{
    MOCKER(mdrv_edma_bbp_sample_reboot)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

	EXPECT_EQ(VOS_OK, uttest_Om_AcpuDumpReboot_case1());

    GlobalMockObject::reset();
}

