/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "gtest/gtest.h"
#include "llt_mockcpp.h"

using namespace testing;

/* ʹ�õ�C�к�����ȫ�ֱ���������� */
#ifdef __cplusplus
extern "C"
{
#endif

extern void *g_pstIpsToOmMsg;
extern unsigned char g_aucTraceData[];

extern unsigned int IPS_MNTN_TransMsg
(
    unsigned char               *pucTransMsg,
    unsigned int                 ulTransMsgContentLen,
    unsigned short               enMsgName
);
extern void OM_Log(char *, unsigned int,
                   int , int ,int, char *);
extern void OM_AcpuAddSNTime(unsigned int *, unsigned int *);
extern unsigned int NFExt_AddDataToRingBuf(void *);
extern int test_IPS_MNTN_TransMsg_002(void);
extern void* V_AllocMsg(unsigned int, unsigned int,
                        unsigned int, int);
extern void test_IPS_MNTN_SndCfgCnf2Om_001(void);
extern unsigned int OM_GetSlice(void);
extern unsigned int Ps_SendMsg(char *, unsigned int, unsigned int, void *);
extern void test_init_IPS_MNTN(void);
extern void test_recover_IPS_MNTN(void);
extern int test_IPS_MNTN_SndCfgCnf2Om_002(void);
extern int test_IPS_MNTN_SndCfgCnf2Om_003(void);
extern unsigned int test_IPS_MNTN_GetPktLenByTraceCfg_001(void);
extern int test_IPS_MNTN_GetPktLenByTraceCfg_002(void);
extern int test_IPS_MNTN_GetPktLenByTraceCfg_003(void);
extern int test_IPS_MNTN_GetPktLenByTraceCfg_004(void);
extern int test_IPS_MNTN_GetPktLenByTraceCfg_005(void);
extern int test_IPS_MNTN_GetPktLenByTraceCfg_006(void);
extern void IPS_MNTN_CtrlPktInfoCB(unsigned char *,
    unsigned char *,
    unsigned short,
    unsigned short);
extern int test_IPS_MNTN_CtrlPktInfoCB_002(void);
extern void * V_MemAlloc(unsigned int, unsigned char, unsigned int ,
                        unsigned int, unsigned int, int);
extern void *kmalloc(size_t size, unsigned int flags);
extern int test_IPS_MNTN_CtrlPktInfoCB_003(void);
extern void test_IPS_MNTN_CtrlPktInfoCB_004(void);
extern void IPS_MNTN_PktInfoCB
(
    unsigned char                        *pucNetIfName,
    unsigned char                        *pucPktData,
    unsigned short                              usPktLen,
    unsigned short     usType
);
extern void OM_AddSNTime(unsigned int *, unsigned int *);
extern void test_IPS_MNTN_PktInfoCB_003(void);
extern void test_IPS_MNTN_PktInfoCB_005(void);
extern void test_IPS_MNTN_PktInfoCB_006(void);
extern void test_IPS_MNTN_PktInfoCB_007(void);
extern void IPS_MNTN_BridgePktInfoCB
(
    unsigned char                        *pucSrcPort,
    unsigned char                        *pucDestPort,
    unsigned char                              *pucPktData,
    unsigned short                              usPktLen,
    unsigned short     usType
);
extern void test_IPS_MNTN_BridgePktInfoCB_003(void);
extern void test_IPS_MNTN_BridgePktInfoCB_004(void);
extern void test_IPS_MNTN_BridgePktInfoCB_005(void);
extern unsigned char test_IPS_MNTN_BridgeTraceCfgChkParam_002(void);
extern unsigned char test_IPS_MNTN_BridgeTraceCfgChkParam_001(void);
extern unsigned char test_IPS_MNTN_TraceCfgChkParam_001(void);
extern unsigned char test_IPS_MNTN_TraceCfgChkParam_002(void);
extern unsigned char test_IPS_MNTN_TraceCfgChkParam_003(void);
extern unsigned char test_IPS_MNTN_TraceAdvancedCfgChkParam_001(void);
extern unsigned char test_IPS_MNTN_TraceAdvancedCfgChkParam_002(void);
extern unsigned char test_IPS_MNTN_TraceAdvancedCfgChkParam_003(void);
extern unsigned char NFExt_ConfigEffective(void *pRcvMsg);
extern int test_IPS_MNTN_TraceAdvancedCfgReq_001(void);
extern int test_IPS_MNTN_TraceAdvancedCfgReq_002(void);
extern int test_IPS_MNTN_TraceAdvancedCfgReq_003(void);
extern unsigned int test_IPS_MNTN_IPInfoCfgChkParam_001(void);
extern unsigned int test_IPS_MNTN_IPInfoCfgChkParam_002(void);
extern unsigned int test_IPS_MNTN_IPInfoCfgChkParam_003(void);
//extern unsigned int test_sizeof_IPS_MNTN_TRACE_CONFIG_CNF_STRU();
extern void IPS_MNTN_SndCfgCnf2Om
(
    unsigned short      usPrimId,
    unsigned int        ulTransMsgContentLen,
    void               *pTransMsgContent
);
extern void test_IPS_MNTN_IPInfoCfgReq_001(void);
extern void test_IPS_MNTN_IPInfoCfgReq_002(void);
extern void test_IPS_MNTN_IPInfoCfgReq_003(void);
extern int test_IPS_MNTN_Ipv4DataParse_001(void);
extern int test_IPS_MNTN_Ipv4DataParse_002(void);
extern int test_IPS_MNTN_Ipv4DataParse_003(void);
extern int test_IPS_MNTN_Ipv4DataParse_004(void);
extern int test_IPS_MNTN_Ipv4DataParse_005(void);
extern int test_IPS_MNTN_Ipv4DataParse_006(void);
extern int test_IPS_MNTN_Ipv4DataParse_007(void);
extern int test_IPS_MNTN_Ipv4DataParse_008(void);
extern int test_IPS_MNTN_GetIPInfoCfg_001(void);
extern int test_IPS_MNTN_GetIPInfoCfg_002(void);
extern void IPS_MNTN_Ipv4DataParse(void *, void *);
extern void IPS_MNTN_Ipv6DataParse(void *, void *);
extern void test_IPS_MNTN_TraceIpInfo_001(void);
extern void test_IPS_MNTN_TraceIpInfo_002(void);
extern void test_IPS_MNTN_TraceIpInfo_003(void);
extern void test_IPS_MNTN_TraceIpInfo_004(void);
extern void test_IPS_MNTN_TraceIpInfo_005(void);
extern unsigned int OM_AcpuSendData(void *, unsigned short);
extern void test_IPS_MNTN_TraceIpInfo_006(void);
extern void test_IPS_MNTN_TraceIpInfo_007(void);
extern void test_IPS_MNTN_TraceIpInfo_008(void);
extern int BSP_MNTN_SystemError();
extern int BSP_USB_RegIpsTraceCB();

extern int _raw_spin_lock_irqsave();
extern int _raw_spin_unlock_irqrestore();
extern int add_preempt_count();
extern int BSP_MNTN_ExchMemMalloc();
extern int BSP_MNTN_SystemError();

//IPS_MNTN_TRACE_MAX_BYTE_LEN + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN == 1548
unsigned char    g_aucTempData[1548];


#ifdef __cplusplus
}
#endif

/* ���������� */
void test_init_IPS_MNTN_CPP()
{
    test_init_IPS_MNTN();
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
}

void test_recover_IPS_MNTN_CPP()
{
    test_recover_IPS_MNTN();
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
}


TEST(test_IPS_MNTN_TransMsg, IPS_MNTN_TransMsg_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned int                 ulDataLen;
    unsigned int                 result;
    const char                  *str = "IPS, IPS_MNTN_TransMsg, ERROR, pucTransMsg is NULL ";

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    ulDataLen   = 6;

    /* check�쳣��� */
    MOCKER(OM_Log)
        .stubs()
        .with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    result = IPS_MNTN_TransMsg(0L, ulDataLen, 0xD021);//ID_IPS_TRACE_MNTN_INFO

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(1, result);//VOS_ERR

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
 ���⺯��   : test_IPS_MNTN_TransMsg_002
 ���⹦��   : ��׮test_IPS_MNTN_TransMsg����
 ��������   : ��Ϣָ��Ϊ��

 �޸���ʷ       :
 1.��    �� : 2014��5��20��
   ��    �� : liukai
   �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TransMsg, IPS_MNTN_TransMsg_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned int ulSn        = 10;
    unsigned int ulTimeStamp = 20;
    int          result;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(OM_AcpuAddSNTime).expects(once()).with(outBoundP(&ulSn), outBoundP(&ulTimeStamp));
    MOCKER(NFExt_AddDataToRingBuf).expects(once()).will(returnValue(0UL));

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    result = test_IPS_MNTN_TransMsg_002();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, result);

    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  Test_IPS_MNTN_SndCfgCnf2Om
��������:��OM��������ȷ����Ϣ�������ڴ�ʧ��
���Ա��:Test_IPS_MNTN_SndCfgCnf2Om_001
���Ա���:��OM��������ȷ����Ϣ�������ڴ�ʧ��
Ԥ�ڽ��:

1.��    ��   : 2014��5��21��
  ��    ��   : liukai
  �޸�����   : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_SndCfgCnf2Om_001, IPS_MNTN_SndCfgCnf2Om_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    const char *str = "IPS, IPS_MNTN_SndCfgCnf2Om, ERROR, Call PS_ALLOC_MSG_WITH_HEADER_LEN \
            fail!";

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(V_AllocMsg).stubs().will(returnValue((void *)NULL));//VOS_NULL_PTR
    /* check �쳣��� */
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));

	MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));
    //MOCKER(add_preempt_count).stubs().will(returnValue(0));
    //MOCKER(BSP_MNTN_ExchMemMalloc).stubs().will(returnValue(0));
    //MOCKER(BSP_MNTN_SystemError).stubs().will(returnValue(0));
    //MOCKER(sub_preempt_count).stubs().will(returnValue(0));

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_SndCfgCnf2Om_001();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  Test_IPS_MNTN_SndCfgCnf2Om
��������:��OM��������ȷ����Ϣ��������Ϣ�ɹ�
���Ա��:Test_IPS_MNTN_SndCfgCnf2Om_002
���Ա���:��OM��������ȷ����Ϣ��������Ϣ�ɹ�
Ԥ�ڽ��:

1.��    �� : 2014��5��21��
   ��    �� : liukai
   �޸����� : ������linux WinGDB UT����

*****************************************************************************/
TEST(test_test_IPS_MNTN_SndCfgCnf2Om_002, IPS_MNTN_SndCfgCnf2Om_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int rslt;
    test_init_IPS_MNTN();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(V_AllocMsg).expects(once()).will(returnValue((void *)(g_pstIpsToOmMsg)));
    MOCKER(OM_GetSlice).expects(once()).will(returnValue(100));
    MOCKER(Ps_SendMsg).stubs().will(returnValue(0));//VOS_OK
    MOCKER(BSP_MNTN_SystemError).stubs().will(returnValue(0));

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    rslt = test_IPS_MNTN_SndCfgCnf2Om_002();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_SndCfgCnf2Om_003
��������:��OM��������ȷ����Ϣ��������Ϣʧ��
���Ա��:IPS_MNTN_SndCfgCnf2Om_003
���Ա���:��OM��������ȷ����Ϣ��������Ϣʧ��
Ԥ�ڽ��:

1.��    �� : 2014��5��21��
   ��    �� : liukai
   �޸����� : ������linux WinGDB UT����

*****************************************************************************/
TEST(test_test_IPS_MNTN_SndCfgCnf2Om_003, IPS_MNTN_SndCfgCnf2Om_003)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int rslt;
    const char *str = "IPS, IPS_MNTN_SndCfgCnf2Om, ERROR, Call PS_SEND_MSG fail!";
    test_init_IPS_MNTN();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(V_AllocMsg).expects(once()).will(returnValue((void *)(g_pstIpsToOmMsg)));
    MOCKER(OM_GetSlice).expects(once()).will(returnValue(100));
    MOCKER(Ps_SendMsg).stubs().will(returnValue(0));//VOS_OK
    /* check �쳣��� */
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));
    MOCKER(BSP_MNTN_SystemError).stubs().will(returnValue(0));

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    rslt = test_IPS_MNTN_SndCfgCnf2Om_003();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_GetPktLenByTraceCfg_001
��������:�������ĵ����
���Ա��:test_IPS_MNTN_GetPktLenByTraceCfg_001
���Ա���:�������ĵ����
Ԥ�ڽ��:

1.��    �� : 2014��5��21��
   ��    �� : liukai
   �޸����� : ������linux WinGDB UT����

*****************************************************************************/
TEST(test_test_IPS_MNTN_GetPktLenByTraceCfg, IPS_MNTN_GetPktLenByTraceCfg_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned int                       rslt;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/


    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    rslt = test_IPS_MNTN_GetPktLenByTraceCfg_001();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, rslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_GetPktLenByTraceCfg_002
��������:
���Ա��:test_IPS_MNTN_GetPktLenByTraceCfg_002
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��21��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����

*****************************************************************************/
TEST(test_test_IPS_MNTN_GetPktLenByTraceCfg, IPS_MNTN_GetPktLenByTraceCfg_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int                       rslt;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    rslt = test_IPS_MNTN_GetPktLenByTraceCfg_002();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_GetPktLenByTraceCfg_003
��������:
���Ա��:test_IPS_MNTN_GetPktLenByTraceCfg_003
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��22��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����

*****************************************************************************/
TEST(test_test_IPS_MNTN_GetPktLenByTraceCfg, IPS_MNTN_GetPktLenByTraceCfg_003)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int                       rslt;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    rslt = test_IPS_MNTN_GetPktLenByTraceCfg_003();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_GetPktLenByTraceCfg_004
��������:
���Ա��:test_IPS_MNTN_GetPktLenByTraceCfg_004
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��22��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����

*****************************************************************************/
TEST(test_test_IPS_MNTN_GetPktLenByTraceCfg, IPS_MNTN_GetPktLenByTraceCfg_004)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int                       rslt;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    rslt = test_IPS_MNTN_GetPktLenByTraceCfg_004();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_GetPktLenByTraceCfg_005
��������:
���Ա��:test_IPS_MNTN_GetPktLenByTraceCfg_005
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��22��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����

*****************************************************************************/
TEST(test_test_IPS_MNTN_GetPktLenByTraceCfg, IPS_MNTN_GetPktLenByTraceCfg_005)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int                       rslt;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    rslt = test_IPS_MNTN_GetPktLenByTraceCfg_005();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_GetPktLenByTraceCfg_006
��������:
���Ա��:test_IPS_MNTN_GetPktLenByTraceCfg_006
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��22��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����

*****************************************************************************/
TEST(test_test_IPS_MNTN_GetPktLenByTraceCfg, IPS_MNTN_GetPktLenByTraceCfg_006)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int                       rslt;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    rslt = test_IPS_MNTN_GetPktLenByTraceCfg_006();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}


TEST(test_IPS_MNTN_CtrlPktInfoCB, IPS_MNTN_CtrlPktInfoCB_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char                           aucNetIfName[16];//IPS_IFNAMSIZ
    const char *str = "IPS, IPS_MNTN_CtrlPktInfoCB, ERROR, pucPktData is NULL ";

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    /* check �쳣�����ȷ */
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    IPS_MNTN_CtrlPktInfoCB(aucNetIfName, (unsigned char *)0L, 0, 0xD01A);//ID_IPS_TRACE_RECV_ARP_PKT

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_CtrlPktInfoCB_002
��������:
���Ա��:test_IPS_MNTN_CtrlPktInfoCB_002
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��22��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����

*****************************************************************************/
TEST(test_test_IPS_MNTN_CtrlPktInfoCB, IPS_MNTN_CtrlPktInfoCB_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int                       rslt;

    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
	MOCKER(OM_AcpuAddSNTime).expects(never());
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
    MOCKER(NFExt_AddDataToRingBuf).stubs().will(returnValue(0U));//VOS_OK
    MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    rslt = test_IPS_MNTN_CtrlPktInfoCB_002();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_CtrlPktInfoCB_003
��������:
���Ա��:test_IPS_MNTN_CtrlPktInfoCB_003
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��26��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����

*****************************************************************************/
TEST(test_test_IPS_MNTN_CtrlPktInfoCB, IPS_MNTN_CtrlPktInfoCB_003)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int rslt;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
#if 0
    /* kmalloc�Ѿ���UT���̴�׮�����Խű���Ҫ�ٴ�׮��������ɹ��̲��ȶ� */
    /* MOCKER(kmalloc).expects(once()).will(returnValue((void *)0L)); */
    /* malloc��׮����runʱ���ֹ�ס������ִ�� */
    /* MOCKER(malloc).expects(once().will(returnValue((void *)0L)); */
    MOCKER(V_MemAlloc).expects(once()).will(returnValue((void *)0L));
#else
    /* ��׮�������������������׮��������Ч */
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)0L));
#endif
    MOCKER(OM_AddSNTime).expects(never());
    MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    rslt = test_IPS_MNTN_CtrlPktInfoCB_003();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_CtrlPktInfoCB_004
��������:
���Ա��:test_IPS_MNTN_CtrlPktInfoCB_004
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��26��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����

*****************************************************************************/
TEST(test_test_IPS_MNTN_CtrlPktInfoCB, IPS_MNTN_CtrlPktInfoCB_004)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
    test_init_IPS_MNTN();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(OM_AcpuAddSNTime).expects(never());
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_CtrlPktInfoCB_004();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
    test_recover_IPS_MNTN();
    GlobalMockObject::reset();
}


TEST(test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char              aucNetIfName[16];//IPS_IFNAMSIZ
    const char *str = "IPS, IPS_MNTN_PktInfoCB, ERROR, paucPktData is NULL ";
    unsigned short             usMsgType = 0xD017;//ID_IPS_TRACE_INPUT_DATA_INFO

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    /* check �쳣��� */
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));
	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    IPS_MNTN_PktInfoCB(aucNetIfName, (unsigned char *)0L, 0, usMsgType);

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}


TEST(test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char                           aucNetIfName[16];//IPS_IFNAMSIZ
    unsigned char                           aucPktData[40];
    unsigned short                          usPktLen;
    unsigned char                          *paucPktData;
    unsigned short                      	usMsgType = 0xD019;//ID_IPS_TRACE_BRIDGE_DATA_INFO

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    usPktLen        = 40;
    paucPktData     = (unsigned char *)aucPktData;

	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    IPS_MNTN_PktInfoCB(aucNetIfName, paucPktData, usPktLen, usMsgType);

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_PktInfoCB_003
��������:
���Ա��:test_IPS_MNTN_PktInfoCB_003
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��26��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����

*****************************************************************************/
TEST(test_test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_003)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)0L));
	MOCKER(IPS_MNTN_TransMsg).expects(never());

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_PktInfoCB_003();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}


TEST(test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_004)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char                           aucNetIfName[16];//IPS_IFNAMSIZ
    unsigned char                          *paucPktData;
    unsigned short                          usPktLen;
    const char *str = "IPS, IPS_MNTN_PktInfoCB : ERROR : usType is not Expectes!";
    unsigned char                           aucPktData[40];
    unsigned short                          usMsgType;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    usPktLen        = 40;
    paucPktData     = (unsigned char *)aucPktData;
    usMsgType       = 0xD02E;//ID_IPS_TRACE_MSG_TYPE_BUTT
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));
	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).expects(never());

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    IPS_MNTN_PktInfoCB(aucNetIfName, paucPktData, usPktLen, usMsgType);

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������: Test_IPS_MNTN_PktInfoCB
��������:���ò�������ձ���
���Ա��:Test_IPS_MNTN_PktInfoCB_005
���Ա���:���ò�������ձ���
Ԥ�ڽ��:

1.��    �� : 2014��5��26��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_005)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
    MOCKER(IPS_MNTN_TransMsg).expects(never());

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_PktInfoCB_005();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������: Test_IPS_MNTN_PktInfoCB
��������:
���Ա��:Test_IPS_MNTN_PktInfoCB_006
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��26��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_006)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(OM_AcpuAddSNTime).expects(never());
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_PktInfoCB_006();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
    GlobalMockObject::reset();
}

/*****************************************************************************
������: Test_IPS_MNTN_PktInfoCB
��������:���ò�������ձ���
���Ա��:Test_IPS_MNTN_PktInfoCB_007
���Ա���:���ò�������ձ���
Ԥ�ڽ��:

1.��    �� : 2014��5��26��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_PktInfoCB, IPS_MNTN_PktInfoCB_007)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(OM_AcpuAddSNTime).expects(never());
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_PktInfoCB_007();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    memset(&g_aucTempData, 0x0, sizeof(g_aucTempData));
    GlobalMockObject::reset();
}


TEST(test_IPS_MNTN_BridgePktInfoCB, IPS_MNTN_BridgePktInfoCB_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char                           aucSrcPort[16];//IPS_END_NAME
    unsigned char                           aucDestPort[16];//IPS_END_NAME
    const char *str = "IPS, IPS_MNTN_BridgePktInfoCB, ERROR, paucPktData is NULL ";
    unsigned short                      usMsgType;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    usMsgType = 0xD019;//ID_IPS_TRACE_BRIDGE_DATA_INFO

    /* check �쳣��� */
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));
	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    IPS_MNTN_BridgePktInfoCB(aucSrcPort, aucDestPort, (unsigned char *)0L, 0, usMsgType);

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}


TEST(test_IPS_MNTN_BridgePktInfoCB, IPS_MNTN_BridgePktInfoCB_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char                           aucSrcPort[16];//IPS_END_NAME
    unsigned char                           aucDestPort[16];//IPS_END_NAME
    unsigned char                          *paucPktData;
    unsigned short                          usPktLen;
    const char *str = "IPS, IPS_MNTN_BridgePktInfoCB : ERROR : usType is not Expectes!";
    unsigned short                          usMsgType;
    unsigned char                           aucPktData[40];

    usPktLen        = 40;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    paucPktData = aucPktData;
    usMsgType = 0xD02E;//ID_IPS_TRACE_MSG_TYPE_BUTT

    /* check �쳣��� */
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));
	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).expects(never());

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    IPS_MNTN_BridgePktInfoCB(aucSrcPort, aucDestPort, paucPktData, usPktLen, usMsgType);

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_BridgePktInfoCB_003
��������:���ò�������ձ���
���Ա��:test_IPS_MNTN_BridgePktInfoCB_003
���Ա���:���ò�������ձ���
Ԥ�ڽ��:

1.��    �� : 2014��5��27��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_BridgePktInfoCB, IPS_MNTN_BridgePktInfoCB_003)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    test_init_IPS_MNTN();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
    MOCKER(IPS_MNTN_TransMsg).expects(never());

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_BridgePktInfoCB_003();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_BridgePktInfoCB_004
��������:���ò�������ձ���
���Ա��:test_IPS_MNTN_BridgePktInfoCB_004
���Ա���:���ò�������ձ���
Ԥ�ڽ��:

1.��    �� : 2014��5��27��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_BridgePktInfoCB, IPS_MNTN_BridgePktInfoCB_004)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned int                          ulSn;
    unsigned int                          ulTimeStamp;

    ulSn        = 10;
    ulTimeStamp = 20;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
	MOCKER(OM_AcpuAddSNTime).expects(never());
	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTempData));
	MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_BridgePktInfoCB_004();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_BridgePktInfoCB_005
��������:���ò�������ձ���
���Ա��:test_IPS_MNTN_BridgePktInfoCB_005
���Ա���:���ò�������ձ���
Ԥ�ڽ��:

1.��    �� : 2014��5��27��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_BridgePktInfoCB, IPS_MNTN_BridgePktInfoCB_005)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned int                          ulSn;
    unsigned int                          ulTimeStamp;

    ulSn        = 10;
    ulTimeStamp = 20;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(OM_AddSNTime).expects(never());
	MOCKER(V_MemAlloc).stubs().will(returnValue((void *)NULL));
    MOCKER(IPS_MNTN_TransMsg).stubs().will(returnValue(0U));//VOS_OK


    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_BridgePktInfoCB_005();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_BridgeTraceCfgChkParam_001
��������:
���Ա��:test_IPS_MNTN_BridgeTraceCfgChkParam_001
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��28��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_BridgeTraceCfgChkParam, IPS_MNTN_BridgeTraceCfgChkParam_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    ucRslt = test_IPS_MNTN_BridgeTraceCfgChkParam_001();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, ucRslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_BridgeTraceCfgChkParam_002
��������:
���Ա��:test_IPS_MNTN_BridgeTraceCfgChkParam_002
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��27��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_BridgeTraceCfgChkParam, IPS_MNTN_BridgeTraceCfgChkParam_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    ucRslt = test_IPS_MNTN_BridgeTraceCfgChkParam_002();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(1, ucRslt);//PS_TRUE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceCfgChkParam_001
��������:
���Ա��:test_IPS_MNTN_TraceCfgChkParam_001
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��28��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceCfgChkParam, IPS_MNTN_TraceCfgChkParam_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    ucRslt = test_IPS_MNTN_TraceCfgChkParam_001();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, ucRslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceCfgChkParam_002
��������:
���Ա��:test_IPS_MNTN_TraceCfgChkParam_002
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��28��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceCfgChkParam, IPS_MNTN_TraceCfgChkParam_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    ucRslt = test_IPS_MNTN_TraceCfgChkParam_002();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, ucRslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceCfgChkParam_003
��������:
���Ա��:test_IPS_MNTN_TraceCfgChkParam_003
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��28��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceCfgChkParam, IPS_MNTN_TraceCfgChkParam_003)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    ucRslt = test_IPS_MNTN_TraceCfgChkParam_003();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(1, ucRslt);//PS_TRUE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceAdvancedCfgChkParam_001
��������:
���Ա��:test_IPS_MNTN_TraceAdvancedCfgChkParam_001
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��28��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceAdvancedCfgChkParam, IPS_MNTN_TraceAdvancedCfgChkParam_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/

	MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));

    ucRslt = test_IPS_MNTN_TraceAdvancedCfgChkParam_001();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, ucRslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceAdvancedCfgChkParam_002
��������:
���Ա��:test_IPS_MNTN_TraceAdvancedCfgChkParam_002
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��28��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceAdvancedCfgChkParam, IPS_MNTN_TraceAdvancedCfgChkParam_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
	MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));

    ucRslt = test_IPS_MNTN_TraceAdvancedCfgChkParam_002();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, ucRslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceAdvancedCfgChkParam_003
��������:
���Ա��:test_IPS_MNTN_TraceAdvancedCfgChkParam_003
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��28��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceAdvancedCfgChkParam, IPS_MNTN_TraceAdvancedCfgChkParam_003)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned char    ucRslt;

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));

    ucRslt = test_IPS_MNTN_TraceAdvancedCfgChkParam_003();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(1, ucRslt);//PS_TRUE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceAdvancedCfgReq_001
��������:
���Ա��:test_IPS_MNTN_TraceAdvancedCfgReq_001
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��28��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceAdvancedCfgReq, IPS_MNTN_TraceAdvancedCfgReq_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int Rslt;
    const char *str = "Warning: IPS_MNTN_TraceAdvancedCfgReq check fail";

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(NFExt_ConfigEffective).expects(never());
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));//check log
	MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));
    /* V_AllocMsg�ѱ�UT���̴�׮�������߲���IPS_MNTN_SndCfgCnf2Om, ͨ���������
       �жϴ���ִ�з�֧ */
    //MOCKER(V_AllocMsg).will(returnValue(pstIpsToOmMsg));
    MOCKER(IPS_MNTN_SndCfgCnf2Om).stubs().will(ignoreReturnValue());//VOS_OK

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    Rslt = test_IPS_MNTN_TraceAdvancedCfgReq_001();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, Rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceAdvancedCfgReq_002
��������:
���Ա��:test_IPS_MNTN_TraceAdvancedCfgReq_002
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��28��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceAdvancedCfgReq, IPS_MNTN_TraceAdvancedCfgReq_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int Rslt;
    const char *str = "Warning: NFExt_ConfigEffective fail";

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(NFExt_ConfigEffective).stubs().will(returnValue(0));//PS_FALSE
    MOCKER(OM_Log).stubs().with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));//check log
	MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));
    /* V_AllocMsg�ѱ�UT���̴�׮�������߲���IPS_MNTN_SndCfgCnf2Om, ͨ���������
       �жϴ���ִ�з�֧ */
    //MOCKER(V_AllocMsg).will(returnValue(pstIpsToOmMsg));
    MOCKER(IPS_MNTN_SndCfgCnf2Om).stubs().will(ignoreReturnValue());//VOS_OK

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    Rslt = test_IPS_MNTN_TraceAdvancedCfgReq_002();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, Rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceAdvancedCfgReq_003
��������:
���Ա��:test_IPS_MNTN_TraceAdvancedCfgReq_003
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��28��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceAdvancedCfgReq, IPS_MNTN_TraceAdvancedCfgReq_003)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int Rslt;
    const char *str = "Warning: NFExt_ConfigEffective fail";

    test_init_IPS_MNTN_CPP();

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(NFExt_ConfigEffective).stubs().will(returnValue(1));//PS_TRUE
    MOCKER(OM_Log).expects(never());
	MOCKER(_raw_spin_lock_irqsave).stubs().will(returnValue(0));
	MOCKER(_raw_spin_unlock_irqrestore).stubs().will(returnValue(0));
    /* V_AllocMsg�ѱ�UT���̴�׮�������߲���IPS_MNTN_SndCfgCnf2Om, ͨ���������
       �жϴ���ִ�з�֧ */
    //MOCKER(V_AllocMsg).will(returnValue(pstIpsToOmMsg));
    MOCKER(IPS_MNTN_SndCfgCnf2Om).stubs().will(ignoreReturnValue());//VOS_OK

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    Rslt = test_IPS_MNTN_TraceAdvancedCfgReq_003();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, Rslt);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    test_recover_IPS_MNTN_CPP();
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_IPInfoCfgChkParam_001
��������:
���Ա��:test_IPS_MNTN_IPInfoCfgChkParam_001
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��28��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_IPInfoCfgChkParam, IPS_MNTN_IPInfoCfgChkParam_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned int Rslt;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(BSP_USB_RegIpsTraceCB).stubs().will(returnValue(0));

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    Rslt = test_IPS_MNTN_IPInfoCfgChkParam_001();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(1, Rslt);//PS_TRUE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_IPInfoCfgChkParam_002
��������:
���Ա��:test_IPS_MNTN_IPInfoCfgChkParam_002
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��28��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_IPInfoCfgChkParam, IPS_MNTN_IPInfoCfgChkParam_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned int Rslt;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    Rslt = test_IPS_MNTN_IPInfoCfgChkParam_002();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, Rslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_IPInfoCfgChkParam_003
��������:
���Ա��:test_IPS_MNTN_IPInfoCfgChkParam_003
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��28��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_IPInfoCfgChkParam, IPS_MNTN_IPInfoCfgChkParam_003)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    unsigned int Rslt;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    Rslt = test_IPS_MNTN_IPInfoCfgChkParam_003();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, Rslt);//PS_FALSE
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_IPInfoCfgReq_001
��������:
���Ա��:test_IPS_MNTN_IPInfoCfgReq_001
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��29��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_IPInfoCfgReq, IPS_MNTN_IPInfoCfgReq_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(OM_Log).expects(never());
    MOCKER(IPS_MNTN_SndCfgCnf2Om).expects(once());
    MOCKER(BSP_USB_RegIpsTraceCB).stubs().will(returnValue(0));

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_IPInfoCfgReq_001();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_IPInfoCfgReq_002
��������:
���Ա��:test_IPS_MNTN_IPInfoCfgReq_002
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��29��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_IPInfoCfgReq, IPS_MNTN_IPInfoCfgReq_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(OM_Log).expects(never());
    MOCKER(IPS_MNTN_SndCfgCnf2Om).expects(once());
    MOCKER(BSP_USB_RegIpsTraceCB).stubs().will(returnValue(0));

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_IPInfoCfgReq_002();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_IPInfoCfgReq_003
��������:
���Ա��:test_IPS_MNTN_IPInfoCfgReq_003
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��29��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_IPInfoCfgReq, IPS_MNTN_IPInfoCfgReq_003)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    const char  *str = "Warning: IPS_MNTN_IPInfoCfgReq check fail";

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(IPS_MNTN_SndCfgCnf2Om).expects(once());
    /* check�쳣��� */
    MOCKER(OM_Log)
        .stubs()
        .with(any(),any(),any(),any(),any(),mirror(str,strlen(str)+1));

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_IPInfoCfgReq_003();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_Ipv4DataParse_001
��������:
���Ա��:test_IPS_MNTN_Ipv4DataParse_001
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��29��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_001();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_Ipv4DataParse_002
��������:
���Ա��:test_IPS_MNTN_Ipv4DataParse_002
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��29��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_002();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_Ipv4DataParse_003
��������:
���Ա��:test_IPS_MNTN_Ipv4DataParse_003
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��29��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_003)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_003();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_Ipv4DataParse_004
��������:
���Ա��:test_IPS_MNTN_Ipv4DataParse_004
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��29��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_004)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_004();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_Ipv4DataParse_005
��������:
���Ա��:test_IPS_MNTN_Ipv4DataParse_005
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��29��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_005)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_005();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_Ipv4DataParse_006
��������:
���Ա��:test_IPS_MNTN_Ipv4DataParse_006
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��29��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_006)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_006();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_Ipv4DataParse_007
��������:
���Ա��:test_IPS_MNTN_Ipv4DataParse_007
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��29��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_007)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_007();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_Ipv4DataParse_008
��������:
���Ա��:test_IPS_MNTN_Ipv4DataParse_008
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��29��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_Ipv4DataParse, IPS_MNTN_Ipv4DataParse_008)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_Ipv4DataParse_008();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_GetIPInfoCfg_001
��������:
���Ա��:test_IPS_MNTN_GetIPInfoCfg_001
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��30��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_GetIPInfoCfg, IPS_MNTN_GetIPInfoCfg_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int result;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    result = test_IPS_MNTN_GetIPInfoCfg_001();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, result);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_GetIPInfoCfg_002
��������:
���Ա��:test_IPS_MNTN_GetIPInfoCfg_002
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��30��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_GetIPInfoCfg, IPS_MNTN_GetIPInfoCfg_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/
    int result;

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    result = test_IPS_MNTN_GetIPInfoCfg_002();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    EXPECT_EQ(0, result);
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceIpInfo_001
��������:
���Ա��:test_IPS_MNTN_TraceIpInfo_001
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��30��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_001)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(never());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(never());

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_001();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceIpInfo_002
��������:
���Ա��:test_IPS_MNTN_TraceIpInfo_002
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��30��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_002)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(never());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(never());

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_002();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceIpInfo_003
��������:
���Ա��:test_IPS_MNTN_TraceIpInfo_003
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��30��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_003)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(never());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(never());

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_003();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceIpInfo_004
��������:
���Ա��:test_IPS_MNTN_TraceIpInfo_004
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��30��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_004)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(never());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(never());

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_004();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceIpInfo_005
��������:
���Ա��:test_IPS_MNTN_TraceIpInfo_005
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��30��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_005)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTraceData));
    MOCKER(OM_AcpuSendData).expects(once()).will(returnValue(0U));//VOS_OK
    MOCKER(OM_AcpuAddSNTime).expects(once());
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(once());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(never());

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_005();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceIpInfo_006
��������:
���Ա��:test_IPS_MNTN_TraceIpInfo_006
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��30��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_006)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTraceData));
    MOCKER(OM_AcpuSendData).expects(once()).will(returnValue(0U));//VOS_OK
    MOCKER(OM_AcpuAddSNTime).expects(once());
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(never());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(once());

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_006();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceIpInfo_007
��������:
���Ա��:test_IPS_MNTN_TraceIpInfo_007
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��31��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_007)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTraceData));
    MOCKER(OM_AcpuSendData).expects(once()).will(returnValue(0U));//VOS_OK
    MOCKER(OM_AcpuAddSNTime).expects(once());
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(once());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(never());

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_007();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}

/*****************************************************************************
������:  test_IPS_MNTN_TraceIpInfo_008
��������:
���Ա��:test_IPS_MNTN_TraceIpInfo_008
���Ա���:
Ԥ�ڽ��:

1.��    �� : 2014��5��31��
  ��    �� : liukai
  �޸����� : ������linux WinGDB UT����
*****************************************************************************/
TEST(test_test_IPS_MNTN_TraceIpInfo, IPS_MNTN_TraceIpInfo_008)
{
    /*************************************************************************
      (1)��ʼ�����Ի���
    *************************************************************************/

    /*************************************************************************
      (2)���ñ��⺯���β�
    *************************************************************************/
    MOCKER(V_MemAlloc).stubs().will(returnValue((void *)g_aucTraceData));
    MOCKER(OM_AcpuSendData).expects(once()).will(returnValue(0U));//VOS_OK
    MOCKER(OM_AcpuAddSNTime).expects(once());
    MOCKER(IPS_MNTN_Ipv4DataParse).expects(never());
    MOCKER(IPS_MNTN_Ipv6DataParse).expects(once());

    /*************************************************************************
      (3)ִ�б��⺯��
    *************************************************************************/
    test_IPS_MNTN_TraceIpInfo_008();

    /*************************************************************************
      (4)�����Խ��
    *************************************************************************/
    GlobalMockObject::verify();

    /*************************************************************************
      (5)������Ի���
    *************************************************************************/
    GlobalMockObject::reset();
}




