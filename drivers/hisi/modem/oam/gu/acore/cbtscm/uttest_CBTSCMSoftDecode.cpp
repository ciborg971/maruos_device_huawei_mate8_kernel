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
	extern int OM_RingBufferFreeBytes( void * ringId);
	extern int OM_RingBufferPut( void * rngId, char *buffer, int nbytes );
	extern unsigned int VOS_SmV( unsigned long Sm_ID );
	extern unsigned int uttest_CBTSCM_SoftDecodeDataRcvProc_case1(void);
	extern unsigned int uttest_CBTSCM_SoftDecodeDataRcvProc_case2(void);
	extern unsigned int uttest_CBTSCM_SoftDecodeDataRcvProc_case3(void);
	extern unsigned int uttest_CBTSCM_SoftDecodeDataRcv_case1(void);
	extern unsigned int uttest_CBTSCM_SoftDecodeAcpuRcvData_case1(void);
	extern unsigned int uttest_CBTSCM_SoftDecodeAcpuRcvData_case2(void);
	extern unsigned int Om_HdlcDecap( void *pstHdlc, char ucChar );
	extern void spin_lock(void *lock);
	extern void spin_unlock(void *lock);
	extern void spin_lock_init(void *lock);
	extern unsigned int CBTSCM_SoftDecodeDataRcvProc(unsigned char *pucBuffer, unsigned int ulLen);
	extern void * V_MemAlloc( unsigned int ulInfo, unsigned char ucPtNo, unsigned int ulSize,
		unsigned int ulRebootFlag, unsigned int ulFileID, int usLineNo  );
	extern void Om_HdlcInit( void *pstHdlc );
	extern unsigned int uttest_CBTSCM_SoftDecodeHdlcInit_case1(void);
	extern unsigned char VOS_RegisterSelfTaskPrio( unsigned int             ulFID ,
		void *       pfnSelfTask,
		unsigned int                ulTaskRealPri,
		unsigned int                ulStackSize);

	extern void * V_MemSet( void * ToSet, unsigned char Char, unsigned int Count,
		unsigned int ulFileID, int usLineNo );

	extern unsigned int  VOS_SmCCreate( unsigned char acSmName[4],
		unsigned int ulSmInit,
		unsigned int ulFlags,
		void  *pSmID );

	extern void * OM_RingBufferCreate( int nbytes );
    extern unsigned int uttest_CBTSCM_SoftDecodeReqRcvTaskInit_case1(void);

	extern unsigned int CBTSCM_SoftDecodeHdlcInit(void *pstHdlc);

	extern unsigned int V_MemFree( unsigned int ulInfo, void **ppAddr,
		unsigned int ulFileID, int usLineNo );
#ifdef __cplusplus
}
#endif

#ifndef VOS_OK
#define VOS_OK                          0
#endif

#ifndef VOS_ERR
#define VOS_ERR                         1
#endif



TEST(CBTSCM_SoftDecodeDataRcvProc1, UT)
{
	MOCKER(OM_RingBufferFreeBytes)
		.stubs()
		.will(returnValue((unsigned int)500));

	EXPECT_EQ(VOS_ERR, uttest_CBTSCM_SoftDecodeDataRcvProc_case1());

	GlobalMockObject::reset();
}


TEST(CBTSCM_SoftDecodeDataRcvProc2, UT)
{
	MOCKER(OM_RingBufferFreeBytes)
		.stubs()
		.will(returnValue((unsigned int)1024));

	MOCKER(OM_RingBufferPut)
		.stubs()
		.will(returnValue((unsigned int)500));

	EXPECT_EQ(VOS_ERR, uttest_CBTSCM_SoftDecodeDataRcvProc_case2());

	GlobalMockObject::reset();
}


TEST(CBTSCM_SoftDecodeDataRcvProc3, UT)
{
	MOCKER(OM_RingBufferFreeBytes)
		.stubs()
		.will(returnValue((unsigned int)1024));

	MOCKER(OM_RingBufferPut)
		.stubs()
		.will(returnValue((unsigned int)1000));

	MOCKER(VOS_SmV)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	EXPECT_EQ(VOS_OK, uttest_CBTSCM_SoftDecodeDataRcvProc_case3());

	GlobalMockObject::reset();
}


TEST(CBTSCM_SoftDecodeDataRcv1, UT)
{
	MOCKER(spin_lock)
		.expects(once());

	MOCKER(spin_unlock)
		.expects(once());

	MOCKER(CBTSCM_SoftDecodeDataRcvProc)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	EXPECT_EQ(VOS_OK, uttest_CBTSCM_SoftDecodeDataRcv_case1());

	GlobalMockObject::reset();
}


TEST(CBTSCM_SoftDecodeAcpuRcvData1, UT)
{
	MOCKER(Om_HdlcDecap)
		.stubs()
		.will(returnValue((unsigned int)2));

	MOCKER(Om_HdlcDecap)
		.stubs()
		.will(returnValue((unsigned int)1));

	MOCKER(Om_HdlcDecap)
		.stubs()
		.will(returnValue((unsigned int)0));

	EXPECT_EQ(VOS_OK, uttest_CBTSCM_SoftDecodeAcpuRcvData_case1());

	GlobalMockObject::reset();
}


TEST(CBTSCM_SoftDecodeAcpuRcvData2, UT)
{
	MOCKER(Om_HdlcDecap)
		.stubs()
		.will(returnValue((unsigned int)0));

	EXPECT_EQ(VOS_OK, uttest_CBTSCM_SoftDecodeAcpuRcvData_case2());

	GlobalMockObject::reset();
}


TEST(CBTSCM_SoftDecodeHdlcInit1, UT)
{
	MOCKER(V_MemAlloc)
		.stubs()
		.will(returnValue((void *)0));

	EXPECT_EQ(VOS_ERR, uttest_CBTSCM_SoftDecodeHdlcInit_case1());

	GlobalMockObject::reset();
}


TEST(CBTSCM_SoftDecodeHdlcInit2, UT)
{
	char  aucData[100];

	MOCKER(V_MemAlloc)
		.stubs()
		.will(returnValue((void *)aucData));

	MOCKER(Om_HdlcInit)
		.expects(once());

	EXPECT_EQ(VOS_OK, uttest_CBTSCM_SoftDecodeHdlcInit_case1());

	GlobalMockObject::reset();
}


TEST(CBTSCM_SoftDecodeReqRcvTaskInit1, UT)
{
	MOCKER(VOS_RegisterSelfTaskPrio)
		.stubs()
		.will(returnValue((unsigned int)0xff));

	EXPECT_EQ(VOS_ERR, uttest_CBTSCM_SoftDecodeReqRcvTaskInit_case1());

	GlobalMockObject::reset();
}


TEST(CBTSCM_SoftDecodeReqRcvTaskInit2, UT)
{
	MOCKER(VOS_RegisterSelfTaskPrio)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(V_MemSet)
		.stubs()
		.will(returnValue((void *)0));

	MOCKER(VOS_SmCCreate)
		.stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_ERR, uttest_CBTSCM_SoftDecodeReqRcvTaskInit_case1());

	GlobalMockObject::reset();
}


TEST(CBTSCM_SoftDecodeReqRcvTaskInit3, UT)
{
	MOCKER(VOS_RegisterSelfTaskPrio)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(V_MemSet)
		.stubs()
		.will(returnValue((void *)0));

	MOCKER(VOS_SmCCreate)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(CBTSCM_SoftDecodeHdlcInit)
		.stubs()
		.will(returnValue((unsigned int)VOS_ERR));

	EXPECT_EQ(VOS_ERR, uttest_CBTSCM_SoftDecodeReqRcvTaskInit_case1());

	GlobalMockObject::reset();
}


TEST(CBTSCM_SoftDecodeReqRcvTaskInit4, UT)
{
	MOCKER(VOS_RegisterSelfTaskPrio)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(V_MemSet)
		.stubs()
		.will(returnValue((void *)0));

	MOCKER(VOS_SmCCreate)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));
		

	MOCKER(CBTSCM_SoftDecodeHdlcInit)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(OM_RingBufferCreate)
		.stubs()
		.will(returnValue((void *)0));

	MOCKER(V_MemFree)
		.expects(once())
	    .will(returnValue((unsigned int)VOS_OK));

	EXPECT_EQ(VOS_ERR, uttest_CBTSCM_SoftDecodeReqRcvTaskInit_case1());

	GlobalMockObject::reset();
}


TEST(CBTSCM_SoftDecodeReqRcvTaskInit5, UT)
{
	char     cBuf[100];

	MOCKER(VOS_RegisterSelfTaskPrio)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(V_MemSet)
		.expects(once())
		.will(returnValue((void *)0));

	MOCKER(VOS_SmCCreate)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(CBTSCM_SoftDecodeHdlcInit)
		.stubs()
		.will(returnValue((unsigned int)VOS_OK));

	MOCKER(OM_RingBufferCreate)
		.stubs()
		.will(returnValue((void *)cBuf));

	MOCKER(spin_lock_init)
		.expects(once());

	EXPECT_EQ(VOS_OK, uttest_CBTSCM_SoftDecodeReqRcvTaskInit_case1());

	GlobalMockObject::reset();
}