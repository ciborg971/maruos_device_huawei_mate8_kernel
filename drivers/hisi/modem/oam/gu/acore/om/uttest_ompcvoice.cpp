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
    extern unsigned int OM_PcvInitRBuf(void *pstRingId, void *pstAddrInfo);
    extern void CBTCPM_PortRcvReg(void * pRcvFunc);
    extern void * V_MemSet( void * ToSet, unsigned char Char, unsigned int Count,
        unsigned int ulFileID, int usLineNo );
    extern unsigned int VOS_SmP( unsigned long Sm_ID, unsigned int ulTimeOutInMillSec );
    extern unsigned int OM_GetSlice(void);
    extern int udi_ioctl(int handle, unsigned int u32Cmd, void* pParam);
    extern void BSP_MNTN_SystemError(int modId, int arg1, int arg2, char * arg3, int arg3Length);
    extern unsigned int VOS_SmBCreate( unsigned char Sm_Name[4],
        unsigned int Sm_Init,
        unsigned int Flags,
        unsigned long * Sm_ID );
    extern void *VOS_UnCacheMemAlloc(unsigned int ulSize, unsigned long *pulRealAddr);

    extern unsigned int uttest_OM_PcvOpen_case1(void);
    extern unsigned int uttest_OM_PcvOpen_case2(void);
    extern void uttest_OM_PcvReleaseAll_case1(void);
    extern void uttest_OM_PcvReleaseAll_case2(void);
    extern unsigned int uttest_OM_PcvSendData_case1(void);
    extern unsigned int uttest_OM_PcvSendData_case2(void);
    extern unsigned int uttest_OM_PcvSendData_case3(void);
    extern unsigned int uttest_OM_PcvSendData_case4(void);
    extern unsigned int uttest_OM_PcvSendData_case5(void);
    extern unsigned int uttest_OM_PcvSendData_case6(void);
    extern void uttest_OM_PcvTransmitTaskEntry_case1(void);
    extern void uttest_OM_PcvTransmitTaskEntry_case2(void);
    extern unsigned int uttest_OM_PcvPidInit_case1(void);
    extern unsigned int uttest_OM_PcvPidInit_case2(void);
    extern unsigned int uttest_OM_PcvPidInit_case3(void);
    extern unsigned int uttest_OM_PcvPidInit_case4(void);

#ifdef __cplusplus
}
#endif

#ifndef VOS_OK
#define VOS_OK                          0
#endif

#ifndef VOS_ERR
#define VOS_ERR                         1
#endif

#ifndef MDRV_OK
#define MDRV_OK                          (0)
#endif

#ifndef MDRV_ERROR
#define MDRV_ERROR                       (-1)
#endif

/*******************************************************************
*������: OM_PcvOpen1
*���⺯����������:g_ulPcvStatus״̬��Ϊ�ر�
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvOpen1, UT)
{
    EXPECT_EQ(VOS_ERR, uttest_OM_PcvOpen_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvOpen2
*���⺯����������:g_ulPcvStatus״̬Ϊ�ر�
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvOpen2, UT)
{
    MOCKER(OM_PcvInitRBuf)
        .expects(exactly(2))
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(CBTCPM_PortRcvReg)
        .expects(exactly(1));

    EXPECT_EQ(VOS_OK, uttest_OM_PcvOpen_case2());

    GlobalMockObject::reset();
}


/*******************************************************************
*������: OM_PcvReleaseAll1
*���⺯����������:g_ucPcvComPort��ΪVOS_NULL_BYTE
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvReleaseAll1, UT)
{
    MOCKER(CBTCPM_PortRcvReg)
        .expects(exactly(1))
        .with(eq((void *)0));

    MOCKER(V_MemSet)
        .expects(exactly(1))
        .will(returnValue((void *)0));

    uttest_OM_PcvReleaseAll_case1();

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvReleaseAll2
*���⺯����������:g_ucPcvComPortΪVOS_NULL_BYTE
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvReleaseAll2, UT)
{
    MOCKER(CBTCPM_PortRcvReg)
        .expects(exactly(0))
        .with(eq((void *)0));

    MOCKER(V_MemSet)
        .expects(exactly(1))
        .will(returnValue((void *)0));

    uttest_OM_PcvReleaseAll_case2();

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvSendData1
*���⺯����������:pucVirAddrΪ��ָ��
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvSendData1, UT)
{
    EXPECT_EQ(VOS_ERR, uttest_OM_PcvSendData_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvSendData2
*���⺯����������:pucPhyAddrΪ��ָ��
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvSendData2, UT)
{
    EXPECT_EQ(VOS_ERR, uttest_OM_PcvSendData_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvSendData3
*���⺯����������:���ͳɹ�������ȡ�ź���ʧ��
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvSendData3, UT)
{
    MOCKER(udi_ioctl)
        .stubs()
        .will(returnValue((int)MDRV_OK));

    MOCKER(OM_GetSlice)
        .stubs()
        .will(returnObjectList((unsigned int)20, (unsigned int)10));

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    EXPECT_EQ(VOS_ERR, uttest_OM_PcvSendData_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvSendData4
*���⺯����������:���ͳɹ�����ȡ�ź����ɹ�
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvSendData4, UT)
{
    MOCKER(udi_ioctl)
        .stubs()
        .will(returnValue((int)MDRV_OK));

    MOCKER(OM_GetSlice)
        .stubs()
        .will(returnObjectList((unsigned int)10, (unsigned int)20));

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    EXPECT_EQ(VOS_OK, uttest_OM_PcvSendData_case4());

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvSendData5
*���⺯����������:����ʧ�ܣ�������ΪBSP_ERROR
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvSendData5, UT)
{
    MOCKER(udi_ioctl)
        .stubs()
        .will(returnValue((int)MDRV_ERROR));

    MOCKER(OM_GetSlice)
        .stubs()
        .will(returnObjectList((unsigned int)10, (unsigned int)20, (unsigned int)30));

    EXPECT_EQ(VOS_ERR, uttest_OM_PcvSendData_case5());

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvSendData6
*���⺯����������:����ʧ�ܣ�������Ϊ��������
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvSendData6, UT)
{
    MOCKER(udi_ioctl)
        .stubs()
        .will(returnValue((int)2));

    MOCKER(OM_GetSlice)
        .stubs()
        .will(returnObjectList((unsigned int)10, (unsigned int)20));

    MOCKER(BSP_MNTN_SystemError)
        .expects(exactly(1));

    EXPECT_EQ(VOS_ERR, uttest_OM_PcvSendData_case6());

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvTransmitTaskEntry1
*���⺯����������:g_ulPcvTransmitSem�ź�������ʧ��
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvTransmitTaskEntry1, UT)
{
    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((unsigned int)VOS_ERR));

    uttest_OM_PcvTransmitTaskEntry_case1();

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvTransmitTaskEntry2
*���⺯����������:����uncache�ڴ�ʧ��
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvTransmitTaskEntry2, UT)
{
    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((unsigned int)VOS_OK));

    MOCKER(VOS_UnCacheMemAlloc)
        .stubs()
        .will(returnValue((void *)0));

    MOCKER(BSP_MNTN_SystemError)
        .expects(exactly(1));

    uttest_OM_PcvTransmitTaskEntry_case2();

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvPidInit1
*���⺯����������:phase��ΪVOS_IP_LOAD_CONFIG
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvPidInit1, UT)
{
    EXPECT_EQ(VOS_OK, uttest_OM_PcvPidInit_case1());

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvPidInit2
*���⺯����������:����g_stPcvOmToDspAddr uncache�ڴ�ʧ��
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvPidInit2, UT)
{
    MOCKER(VOS_UnCacheMemAlloc)
        .stubs()
        .will(returnObjectList((void *)0, (void *)0));

    MOCKER(BSP_MNTN_SystemError)
        .expects(exactly(1));

    EXPECT_EQ(VOS_ERR, uttest_OM_PcvPidInit_case2());

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvPidInit3
*���⺯����������:����g_stPcvDspToOmAddr uncache�ڴ�ʧ��
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvPidInit3, UT)
{
    MOCKER(VOS_UnCacheMemAlloc)
        .stubs()
        .will(returnObjectList((void *)1, (void *)0));

    MOCKER(BSP_MNTN_SystemError)
        .expects(exactly(1));

    EXPECT_EQ(VOS_ERR, uttest_OM_PcvPidInit_case3());

    GlobalMockObject::reset();
}

/*******************************************************************
*������: OM_PcvPidInit4
*���⺯����������:PID��ʼ���ɹ�
*Ԥ�ڽ����
************************* �޸ļ�¼ *************************
#  1.��    ��: 2014��6��16��
#    ��    ��: L00256032
#    �޸�����: �½�CASE
*******************************************************************/
TEST(OM_PcvPidInit4, UT)
{
    MOCKER(VOS_UnCacheMemAlloc)
        .stubs()
        .will(returnObjectList((void *)1, (void *)1));

    EXPECT_EQ(VOS_OK, uttest_OM_PcvPidInit_case4());

    GlobalMockObject::reset();
}

