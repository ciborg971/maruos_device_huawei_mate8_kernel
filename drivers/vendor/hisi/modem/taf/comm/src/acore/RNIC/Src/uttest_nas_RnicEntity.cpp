/*****************************************************************************
1 ͷ�ļ�����
*****************************************************************************/
#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_RnicEntity.h"


//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;


#if 0
/*****************************************************************************
2 ����ʵ��
*****************************************************************************/


class Test_RNIC_StopNetCard: public ::testing::Test
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


TEST_F(Test_RNIC_StopNetCard, Test_RNIC_StopNetCard_001)
{
    VOS_INT                             lRst;
    struct net_device                   *pstNetDev = VOS_NULL_PTR;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(never());

    MOCKER(netif_stop_queue)
        .expects(never());

    /* �������� */

    /* ������ں��� */
    lRst = RNIC_StopNetCard(pstNetDev);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_ERROR, lRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_RNIC_StopNetCard, Test_RNIC_StopNetCard_002)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(netif_stop_queue)
        .expects(never());

    /* �������� */

    /* ������ں��� */
    lRst = RNIC_StopNetCard(&stNetDev);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_ERROR, lRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}



TEST_F(Test_RNIC_StopNetCard, Test_RNIC_StopNetCard_003)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(&stPriv));

    MOCKER(netif_stop_queue)
        .expects(exactly(1));

    /* �������� */

    /* ������ں��� */
    lRst = RNIC_StopNetCard(&stNetDev);

    /* ��ȡ��� */
    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(&stNetDev);

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_OK, lRst);
    EXPECT_EQ(RNIC_NETCARD_STATUS_CLOSED, pstPriv->enStatus);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_RNIC_OpenNetCard: public ::testing::Test
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


TEST_F(Test_RNIC_OpenNetCard, Test_RNIC_OpenNetCard_001)
{
    VOS_INT                             lRst;
    struct net_device                   *pstNetDev = VOS_NULL_PTR;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(never());

    /* �������� */

    /* ������ں��� */
    lRst = RNIC_OpenNetCard(pstNetDev);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_ERROR, lRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_RNIC_OpenNetCard, Test_RNIC_OpenNetCard_002)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    lRst = RNIC_OpenNetCard(&stNetDev);

    /* ��ȡ��� */
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, lRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_RNIC_OpenNetCard, Test_RNIC_OpenNetCard_003)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    stPriv.enStatus = RNIC_NETCARD_STATUS_OPENED;
    ucIndex = 0;

    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(&stPriv));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    lRst = RNIC_OpenNetCard(&stNetDev);

    /* ��ȡ��� */
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_BUSY, lRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_RNIC_OpenNetCard, Test_RNIC_OpenNetCard_004)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    stPriv.enStatus = RNIC_NETCARD_STATUS_CLOSED;
    ucIndex = 0;

    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(&stPriv));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    lRst = RNIC_OpenNetCard(&stNetDev);

    /* ��ȡ��� */
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OK, lRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
class Test_RNIC_StartXmit: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));

        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};


TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_001)
{
    netdev_tx_t                         enRst;
    struct sk_buff                     *pstSkb;
    struct net_device                  *pstNetDev = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    pstSkb = IMM_ZcStaticAlloc(4);
    ucIndex = 0;

    /* ׮���� */

    /* �������� */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,pstNetDev);

    /* ��ȡ��� */
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_002)
{
    netdev_tx_t                         enRst;
    struct sk_buff                     *pstSkb    = VOS_NULL_PTR;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;

    /* ׮���� */

    /* �������� */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_003)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;

    VOS_sprintf(stNetDev.name, "RNIC");

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xFFFFFFFF;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));

    pstPriv->enRmNetId  = RNIC_NET_ID_MAX_NUM;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlNetIdDiscardNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();}
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_004)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;
    RNIC_CTX_STRU                      *pstRnicCtx;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstRnicCtx = RNIC_GetRnicCtxAddr();
    pstRnicCtx->astSpecCtx[ucIndex].enFlowCtrlStatus = RNIC_FLOW_CTRL_STATUS_START;

    aulIpHeader[0] = 0x00;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_INSIDE;


    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
#if (0)
    MOCKER(ADS_UL_IsSendPermit)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));
#endif

    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ����ƥ�� */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlFlowCtrlDiscardNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_005)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ������ʼ�� */
    ucIndex = 0;

    VOS_sprintf(stNetDev.name, g_astRnicManageTbl[ucIndex].pucRnicNetCardName);
    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_INSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    pstDialMode = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode = AT_RNIC_DIAL_MODE_DEMAND_DISCONNECT;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xFFFFFFFF;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlIpv4BrdcstPktNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    //EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_006)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTiStatus;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ������ʼ�� */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_INSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    pstDialMode = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode       = AT_RNIC_DIAL_MODE_DEMAND_DISCONNECT;
    pstDialMode->enEventReportFlag = RNIC_ALLOW_EVENT_REPORT;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
    MOCKER(device_event_report)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    MOCKER(V_GetRelTmRemainTime)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_PROTECT);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);
    enTiStatus                          = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_PROTECT);


    /* ����ƥ�� */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlSendAppDialUpSucc);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, enTiStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_007)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_UINT8                           ucIndex;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTiStatus;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ������ʼ�� */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_INSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    pstDialMode = RNIC_GetDialModeAddr();
    pstDialMode->enDialMode       = AT_RNIC_DIAL_MODE_DEMAND_DISCONNECT;
    pstDialMode->enEventReportFlag = RNIC_ALLOW_EVENT_REPORT;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
    MOCKER(device_event_report)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);
    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_PROTECT);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);
    enTiStatus                          = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_PROTECT);


    /* ����ƥ�� */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlSendAppDialUpFail);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, enTiStatus);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_008)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ������ʼ�� */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_INSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    aulIpHeader[0] = 0x00;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlRecvErrPktNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_009)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ������ʼ�� */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_OUTSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = 1;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    MOCKER(SDIO_UL_SendPacket)
        .expects(exactly(1))
        .will(returnValue(SDIO_OK));


    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlSendPktNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_010)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ������ʼ�� */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_OUTSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucPdnId       = 1;

    aulIpHeader[0] = 0x60;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    MOCKER(SDIO_UL_SendPacket)
        .expects(exactly(1))
        .will(returnValue(SDIO_OK));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlSendPktNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_011)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ������ʼ�� */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_OUTSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = 1;

    aulIpHeader[0] = 0x60;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlPdnIdErr);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_012)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ������ʼ�� */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_OUTSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucPdnId       = 1;

    aulIpHeader[0] = 0x60;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    MOCKER(SDIO_UL_SendPacket)
        .expects(exactly(1))
        .will(returnValue(SDIO_ERR));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_013)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ������ʼ�� */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_OUTSIDE;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = 1;

    aulIpHeader[0] = 0x00;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(RNIC_SendULIpv6Data)
        .expects(never());

    MOCKER(SDIO_UL_SendPacket)
        .expects(never());

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx                            = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlRecvErrPktNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif
TEST_F(Test_RNIC_StartXmit, Test_RNIC_StartXmit_014)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;

    /* ������ʼ�� */
    ucIndex = 0;
    VOS_sprintf(stNetDev.name, "eth_x");

    pstSpecNetCardCtx   = RNIC_GetSpecNetCardCtxAddr(RNIC_RM_NET_ID_0);
    pstSpecNetCardCtx->enModemType  = RNIC_MODEM_TYPE_BUTT;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucPdnId       = 1;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xF0F0F0F0;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(pstPriv));

    MOCKER(RNIC_RcvInsideModemUlData)
        .expects(never());

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    MOCKER(RNIC_RcvOutsideModemUlData)
        .expects(never());
#endif

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ����ƥ�� */
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}



class Test_RNIC_SendULIpv6Data: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;
    IMM_ZC_STRU                        *pstImmZc;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    struct sk_buff                     *pstSkb;

    void SetUp()
	{
		UT_STUB_INIT();
        /* ����A�˹����ڴ� */
        pstImmZc = IMM_ZcStaticAlloc(20);

        /* ����˽�����ݿռ� */
        pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
        VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
        pstPriv->enRmNetId  = RNIC_RM_NET_ID_0;

        /* ����SKBUF�ڴ� */
        pstSkb = (struct sk_buff *)IMM_ZcStaticAlloc(20);
        /* ����IPͷ�ڴ� */


        /* ��ʼ��RNIC������ */
        pstRnicCtx  = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
    void TearDown()
    {
        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));

        if (VOS_NULL_PTR != pstPriv)
        {
            free(pstPriv);
        }
    }
};
TEST_F(Test_RNIC_SendULIpv6Data, Test_RNIC_SendULIpv6Data_001)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 0xff;

    /* ���IPЭ������ */
    aulIpHeader[0] = 0x60;
    /* ���Ŀ�ĵ�ַ */
    aulIpHeader[4] = 0x0;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_USER_DEFINED;

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULDataInPdpActive)
        .expects(never());

    MOCKER(ADS_UL_SendPacketEx)
        .expects(never());

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb, &stNetDev);

    /* ��ȡ��� */
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlRabIdErr);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}

#if(0)
TEST_F(Test_RNIC_SendULIpv6Data, Test_RNIC_SendULIpv6Data_002)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv6PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 12;

    /* ���IPЭ������ */
    aulIpHeader[0] = 0x60;
    /* ���Ŀ�ĵ�ַ */
    aulIpHeader[4] = 0x0;

    pstSkb->len = sizeof(VOS_UINT32)*5;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(RNIC_SendULDataInPdpActive)
        .expects(never());

    MOCKER(IMM_ZcStaticCopy_Debug)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(RNIC_SendULIpv4Data)
        .expects(never());

    MOCKER(ADS_UL_SendPacketEx)
        .expects(never())
        .will(returnValue(VOS_OK));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(1, pstPriv->stStats.tx_dropped);
    EXPECT_EQ(0, pstPriv->stStats.tx_packets);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlImmzcFailPktNum);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
TEST_F(Test_RNIC_SendULIpv6Data, Test_RNIC_SendULIpv6Data_003)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 8;

    aulIpHeader[0] = 0x60;
    aulIpHeader[4] = 0x0;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(0, pstPriv->stStats.tx_dropped);
    EXPECT_EQ(1, pstPriv->stStats.tx_packets);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(0, g_astRnicStats[ucIndex].ulUlModemIdDiscardNum);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
#else
TEST_F(Test_RNIC_SendULIpv6Data, Test_RNIC_SendULIpv6Data_004)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex    = 0;
    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = 8;

    aulIpHeader[0] = 0x60;
    aulIpHeader[4] = 0x0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(0, pstPriv->stStats.tx_dropped);
    EXPECT_EQ(1, pstPriv->stStats.tx_packets);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(0, g_astRnicStats[ucIndex].ulUlModemIdDiscardNum);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
#endif
class Test_RNIC_SendULIpv4Data: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;
    IMM_ZC_STRU                        *pstImmZc;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    struct sk_buff                     *pstSkb;

    void SetUp()
	{
		UT_STUB_INIT();
        /* ����A�˹����ڴ� */
        pstImmZc = IMM_ZcStaticAlloc(sizeof(struct sk_buff));

        /* ����˽�����ݿռ� */
        pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)malloc(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
        VOS_MemSet(pstPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));

        /* ����SKBUF�ڴ� */
        pstSkb = (struct sk_buff *)IMM_ZcStaticAlloc(sizeof(struct sk_buff));
        /* ����IPͷ�ڴ� */



        /* ��ʼ��RNIC������ */
        pstRnicCtx  = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
    void TearDown()
    {
        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));

        if (VOS_NULL_PTR != pstPriv)
        {
            free(pstPriv);
        }

    }
};
TEST_F(Test_RNIC_SendULIpv4Data, Test_RNIC_SendULIpv4Data_001)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4v6PdpInfo.enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 0xff;

    /* ���IPЭ������ */
    aulIpHeader[0] = 0x40;
    /* ���Ŀ�ĵ�ַ */
    aulIpHeader[4] = 0x0;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_USER_DEFINED;

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(skb_copy_exp)
        .expects(never());

    MOCKER(RNIC_SendULDataInPdpActive)
        .expects(never());

    MOCKER(ADS_UL_SendPacketEx)
        .expects(never());

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlRabIdErr);
    EXPECT_EQ(NETDEV_TX_OK, enRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
#if(0)
TEST_F(Test_RNIC_SendULIpv4Data, Test_RNIC_SendULIpv4Data_002)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    IMM_MEM_STRU                        stImmMem = {0};
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 12;

    stImmMem.enPoolId = IMM_MEM_POOL_ID_EXT;

    /* ���IPЭ������ */
    aulIpHeader[0] = 0x40;
    /* ���Ŀ�ĵ�ַ */
    aulIpHeader[4] = 0x0;

    pstSkb->len = sizeof(VOS_UINT32)*5;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_USER_DEFINED;

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.pMem = &stImmMem;

    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(RNIC_SendULDataInPdpActive)
        .expects(never());

    MOCKER(IMM_ZcStaticCopy_Debug)
        .stubs()
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(never())
        .will(returnValue(VOS_OK));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(1, pstPriv->stStats.tx_dropped);
    EXPECT_EQ(0, pstPriv->stStats.tx_packets);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlImmzcFailPktNum);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
TEST_F(Test_RNIC_SendULIpv4Data, Test_RNIC_SendULIpv4Data_003)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTimerStatus;
    IMM_MEM_STRU                        stImmMem = {0};
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.enRegStatus   = RNIC_PDP_REG_STATUS_ACTIVE;
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 12;

    stImmMem.enPoolId = IMM_MEM_POOL_ID_EXT;

    /* ���IPЭ������ */
    aulIpHeader[0] = 0x40;
    /* ���Ŀ�ĵ�ַ */
    aulIpHeader[4] = 0x0;

    pstSkb->len = sizeof(VOS_UINT32)*5;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_USER_DEFINED;

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.pMem = &stImmMem;

    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(RNIC_SendULDataInPdpActive)
        .expects(exactly(1));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(never())
        .will(returnValue(VOS_OK));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(0, pstPriv->stStats.tx_dropped);
    EXPECT_EQ(0, pstPriv->stStats.tx_packets);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULPeriodSndPkts);
    EXPECT_EQ(0, g_astRnicStats[ucIndex].ulUlImmzcFailPktNum);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_SendULIpv4Data, Test_RNIC_SendULIpv4Data_004)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    IMM_MEM_STRU                        stImmMem = {0};
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    stImmMem.enPoolId = IMM_MEM_POOL_ID_SHARE;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0x0;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.enType = MEM_TYPE_USER_DEFINED;

    pstSkb->private_mem.pMem = &stImmMem;

    /* ׮���� */
    MOCKER(netdev_priv)
        .will(returnValue(pstPriv));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulUlSendPktFailNum);
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
#else

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
TEST_F(Test_RNIC_SendULIpv4Data, Test_RNIC_SendULIpv4Data_005)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    IMM_MEM_STRU                        stImmMem = {0};
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex    = 3;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    stImmMem.enPoolId = IMM_MEM_POOL_ID_SHARE;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0x0;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    pstSkb->private_mem.pMem = &stImmMem;

	pstPriv->enRmNetId = ucIndex;


    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(0, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif
TEST_F(Test_RNIC_SendULIpv4Data, Test_RNIC_SendULIpv4Data_006)
{
    netdev_tx_t                         enRst;
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct net_device                   stNetDev;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    IMM_MEM_STRU                        stImmMem = {0};
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex    = 0;

    g_stRnicCtx.astSpecCtx[ucIndex].enModemType = RNIC_MODEM_TYPE_INSIDE;

    VOS_sprintf(stNetDev.name, "eth_x");
    stImmMem.enPoolId = IMM_MEM_POOL_ID_SHARE;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId       = 8;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0x0;

    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    VOS_MemCpy(pstImmZc->data, aulIpHeader, 20);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    pstSkb->private_mem.pMem = &stImmMem;

    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(pstPriv));

    MOCKER(ADS_UL_SendPacketEx)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(pstPriv, ucIndex);

    /* ������ں��� */
    enRst = RNIC_StartXmit(pstSkb,&stNetDev);

    /* ��ȡ��� */
    pstUlCtx      = RNIC_GetUlCtxAddr(ucIndex);
    pstPriv       = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(NETDEV_TX_OK, enRst);
    EXPECT_EQ(1, pstUlCtx->stULDataStats.ulULTotalDroppedPkts);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif
class Test_RNIC_RcvAdsDlData: public ::testing::Test
{
public:
    IMM_ZC_STRU                        *pstImmZc;
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* ����A�˹����ڴ� */
        pstImmZc = IMM_ZcStaticAlloc(20);

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
    void TearDown()
    {
        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
};
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_001)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;
    ucRabid = 6;
    enPktType = ADS_PKT_TYPE_IPV4;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId = 5;

    /* ׮���� */

    /* �������� */
    RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, ucIndex);

    /* ������ں��� */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* ��ȡ��� */
    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_NULL_PTR, pstPriv);
    EXPECT_EQ(RNIC_INVAL, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_002)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 3;
    ucRabid = 0x45;
    enPktType = ADS_PKT_TYPE_IPV4;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId = 5;

    /* ׮���� */

    /* �������� */
    RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, ucIndex);

    /* ������ں��� */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* ��ȡ��� */
    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_NULL_PTR, pstPriv);
    EXPECT_EQ(RNIC_INVAL, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_003)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;
    ucRabid = 5;
    enPktType = ADS_PKT_TYPE_IPV4;
    stPriv.enStatus = RNIC_NETCARD_STATUS_CLOSED;

    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId = 5;

    g_stRnicCtx.astRabIdInfo[ucIndex].aucRmNetId[pstPdpAddr->stIpv4PdpInfo.ucRabId - RNIC_RAB_ID_OFFSET] = RNIC_RM_NET_ID_0;

    /* ׮���� */

    /* �������� */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* ��ȡ��� */
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OK, ulRst);
    EXPECT_EQ(1, pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_004)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;
    ucRabid = 5;
    enPktType = ADS_PKT_TYPE_IPV4;
    stPriv.enStatus = RNIC_NETCARD_STATUS_OPENED;
    pstImmZc->len = RNIC_MAX_PACKET * 2;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId = 5;

    g_stRnicCtx.astRabIdInfo[ucIndex].aucRmNetId[pstPdpAddr->stIpv4PdpInfo.ucRabId - RNIC_RAB_ID_OFFSET] = RNIC_RM_NET_ID_0;

    /* ׮���� */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
     MOCKER(netif_rx_ni)
        .expects(never())
        .will(returnValue(NET_RX_DROP));
#else
    MOCKER(netif_rx_ni_balong)
        .expects(never())
        .will(returnValue(NET_RX_DROP));
#endif

    /* �������� */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* ��ȡ��� */
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OK, ulRst);
    EXPECT_EQ(1, pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts);
    EXPECT_EQ(1, g_astRnicStats[ucIndex].ulDlRecvBigPktNum);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_005)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;
    ucRabid = 5;
    enPktType = ADS_PKT_TYPE_IPV4;
    stPriv.enStatus = RNIC_NETCARD_STATUS_OPENED;
    pstImmZc->len = RNIC_MAX_PACKET;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId = 5;

    g_stRnicCtx.astRabIdInfo[ucIndex].aucRmNetId[pstPdpAddr->stIpv4PdpInfo.ucRabId - RNIC_RAB_ID_OFFSET] = RNIC_RM_NET_ID_0;

    /* ׮���� */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(netif_rx_ni)
        .expects(exactly(1))
        .will(returnValue(NET_RX_DROP));
#else
    MOCKER(netif_rx_ni_balong)
        .expects(exactly(1))
        .will(returnValue(NET_RX_DROP));
#endif

    MOCKER(RNIC_AddMacHead)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* �������� */
     RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* ��ȡ��� */
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, ulRst);
    EXPECT_EQ(1, pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_006)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;
    ucRabid = 5;
    enPktType = ADS_PKT_TYPE_IPV6;
    stPriv.enStatus = RNIC_NETCARD_STATUS_OPENED;
    pstImmZc->len = RNIC_MAX_PACKET;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv6PdpInfo.ucRabId = 5;

    g_stRnicCtx.astRabIdInfo[ucIndex].aucRmNetId[pstPdpAddr->stIpv6PdpInfo.ucRabId - RNIC_RAB_ID_OFFSET] = RNIC_RM_NET_ID_0;

    /* ׮���� */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
     MOCKER(netif_rx_ni)
         .expects(exactly(1))
         .will(returnValue(NET_RX_SUCCESS));
#else
     MOCKER(netif_rx_ni_balong)
         .expects(exactly(1))
         .will(returnValue(NET_RX_SUCCESS));
#endif

     MOCKER(RNIC_AddMacHead)
         .expects(exactly(1))
         .will(returnValue(VOS_OK));

     /* �������� */
     RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* ��ȡ��� */
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OK, ulRst);
    EXPECT_EQ(0, pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts);
    EXPECT_EQ(pstImmZc->len, pstDlCtx->stDLDataStats.ulDLPeriodRcvBytes);
    EXPECT_NE(0, pstDlCtx->stDLDataStats.ulDLTotalRcvBytes);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_007)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;
    ucRabid = 5;
    enPktType = ADS_PKT_TYPE_BUTT;
    stPriv.enStatus = RNIC_NETCARD_STATUS_OPENED;
    pstImmZc->len = RNIC_MAX_PACKET;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv6PdpInfo.ucRabId = 5;

    g_stRnicCtx.astRabIdInfo[ucIndex].aucRmNetId[pstPdpAddr->stIpv6PdpInfo.ucRabId - RNIC_RAB_ID_OFFSET] = RNIC_RM_NET_ID_0;

    /* ׮���� */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(netif_rx_ni)
        .expects(never())
        .will(returnValue(NET_RX_SUCCESS));
#else
    MOCKER(netif_rx_ni_balong)
        .expects(never())
        .will(returnValue(NET_RX_SUCCESS));
#endif

    /* �������� */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* ��ȡ��� */
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_RcvAdsDlData, Test_RNIC_RcvAdsDlData_008)
{
    VOS_UINT8                           ucRabid;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT32                          ulRst;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    RNIC_DL_CTX_STRU                   *pstDlCtx;
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;
    ucRabid = 5;
    enPktType = ADS_PKT_TYPE_IPV4;
    stPriv.enStatus = RNIC_NETCARD_STATUS_OPENED;
    pstImmZc->len = RNIC_MAX_PACKET;
    pstPdpAddr = RNIC_GetPdpCtxAddr(ucIndex);
    pstPdpAddr->stIpv4PdpInfo.ucRabId = 5;

    g_stRnicCtx.astRabIdInfo[ucIndex].aucRmNetId[pstPdpAddr->stIpv4PdpInfo.ucRabId - RNIC_RAB_ID_OFFSET] = RNIC_RM_NET_ID_0;

    /* ׮���� */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(netif_rx_ni)
        .expects(never())
        .will(returnValue(NET_RX_DROP));
#else
    MOCKER(netif_rx_ni_balong)
        .expects(never())
        .will(returnValue(NET_RX_DROP));
#endif

    MOCKER(RNIC_AddMacHead)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    /* �������� */
     RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    ulRst = RNIC_RcvAdsDlData(ucRabid, pstImmZc, enPktType);

    /* ��ȡ��� */
    pstDlCtx                            = RNIC_GetDlCtxAddr(ucIndex);
    pstPriv                             = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, ulRst);
    EXPECT_EQ(0, pstDlCtx->stDLDataStats.ulDLTotalDroppedPkts);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
class Test_RNIC_SetMacAddress: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
    void TearDown()
    {
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};


TEST_F(Test_RNIC_SetMacAddress, Test_RNIC_SetMacAddress_001)
{
    VOS_INT                             lRst;
    struct sockaddr                     stMacAddr;
    struct net_device                  *pstNetDev = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;

    /* ׮���� */
    MOCKER(is_valid_ether_addr)
        .expects(never());

    /* �������� */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    lRst = RNIC_SetMacAddress(pstNetDev, (void *)&stMacAddr);

    /* ��ȡ��� */
    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, lRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_SetMacAddress, Test_RNIC_SetMacAddress_002)
{
    VOS_INT                             lRst;
    struct sockaddr                     stMacAddr;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;

    /* ׮���� */
    MOCKER(is_valid_ether_addr)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    lRst = RNIC_SetMacAddress(&stNetDev, (void *)&stMacAddr);

    /* ��ȡ��� */
    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ADDR_INVALID, lRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_SetMacAddress, Test_RNIC_SetMacAddress_003)
{
    VOS_INT                             lRst;
    struct sockaddr                     stMacAddr;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;

    stNetDev.dev_addr = VOS_NULL_PTR;

    /* ׮���� */
    MOCKER(is_valid_ether_addr)
        .expects(exactly(1))
        .will(returnValue(VOS_TRUE));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    lRst = RNIC_SetMacAddress(&stNetDev, (void *)&stMacAddr);

    /* ��ȡ��� */
    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, lRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_SetMacAddress, Test_RNIC_SetMacAddress_004)
{
    VOS_INT                             lRst;
    VOS_UINT8                           ucAddr;
    struct sockaddr                     stMacAddr;
    struct net_device                  *pstNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;
    pstNetDev = (struct net_device *)malloc(sizeof(struct net_device));
    VOS_MemSet(pstNetDev, 0, sizeof(struct net_device));
    pstNetDev->dev_addr = &ucAddr;

    /* ׮���� */
    MOCKER(is_valid_ether_addr)
        .expects(exactly(1))
        .will(returnValue(VOS_TRUE));

    /* �������� */
    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    lRst = RNIC_SetMacAddress(pstNetDev, (void *)&stMacAddr);

    /* ��ȡ��� */
    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OK, lRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
class Test_RNIC_ChangeMtu: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
    void TearDown()
    {
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};


TEST_F(Test_RNIC_ChangeMtu, Test_RNIC_ChangeMtu_001)
{
    VOS_INT                             lRst;
    VOS_INT                             lNewMtu;
    struct net_device                  *pstNetDev = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;
    lNewMtu = 1;

    /* ׮���� */

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    lRst = RNIC_ChangeMtu(pstNetDev, lNewMtu);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_ERROR, lRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_ChangeMtu, Test_RNIC_ChangeMtu_002)
{
    VOS_INT                             lRst;
    VOS_INT                             lNewMtu;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;
    lNewMtu = RNIC_MAX_PACKET + 1;

    /* ׮���� */

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    lRst = RNIC_ChangeMtu(&stNetDev, lNewMtu);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OUT_RANGE, lRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_ChangeMtu, Test_RNIC_ChangeMtu_003)
{
    VOS_INT                             lRst;
    VOS_INT                             lNewMtu;
    struct net_device                   *pstNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;
    lNewMtu = RNIC_MAX_PACKET;
    pstNetDev = (struct net_device *)malloc(sizeof(struct net_device));
    VOS_MemSet(pstNetDev, 0, sizeof(struct net_device));
    pstNetDev->mtu = 1000;

    /* ׮���� */

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    lRst = RNIC_ChangeMtu(pstNetDev, lNewMtu);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);
    EXPECT_EQ(RNIC_OK, lRst);
    EXPECT_EQ(RNIC_MAX_PACKET, pstNetDev->mtu);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
class Test_RNIC_ProcTxTimeout: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
    void TearDown()
    {
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};


TEST_F(Test_RNIC_ProcTxTimeout, Test_RNIC_ProcTxTimeout_001)
{
    struct net_device                  *pstNetDev = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;

    /* ׮���� */

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    RNIC_ProcTxTimeout(pstNetDev);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_ProcTxTimeout, Test_RNIC_ProcTxTimeout_002)
{
    struct net_device                   stNetDev ;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;

    /* ׮���� */

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    RNIC_ProcTxTimeout(&stNetDev);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
class Test_RNIC_Ioctrl: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
    void TearDown()
    {
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};


TEST_F(Test_RNIC_Ioctrl, Test_RNIC_Ioctrl_001)
{
    struct net_device                   stNetDev;
    struct ifreq                        stIfr;
    VOS_INT                             lCmd;
    VOS_INT                             lRst;

    /* ������ʼ�� */
    lCmd = 1;

    /* ׮���� */

    /* �������� */

    /* ������ں��� */
    lRst = RNIC_Ioctrl(&stNetDev, &stIfr, lCmd);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_NOTSUPP, lRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
class Test_RNIC_DeinitNetCard: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
    void TearDown()
    {
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};

TEST_F(Test_RNIC_DeinitNetCard, Test_RNIC_DeinitNetCard_001)
{
    struct net_device                  *pstNetDev = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;

    /* ׮���� */
    MOCKER(netif_carrier_off)
        .expects(never());

    MOCKER(netif_stop_queue)
        .expects(never());

    MOCKER(unregister_netdev)
        .expects(never());

    MOCKER(free_netdev)
        .expects(never());

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    RNIC_DeinitNetCard(pstNetDev);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_DeinitNetCard, Test_RNIC_DeinitNetCard_002)
{
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;

    stPriv.enRmNetId = RNIC_NET_ID_MAX_NUM;

    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(&stPriv));

    MOCKER(netif_carrier_off)
        .expects(never());

    MOCKER(netif_stop_queue)
        .expects(never());

    MOCKER(unregister_netdev)
        .expects(never());

    MOCKER(free_netdev)
        .expects(never());

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    RNIC_DeinitNetCard(&stNetDev);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv, pstPriv);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_DeinitNetCard, Test_RNIC_DeinitNetCard_003)
{
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv;
    VOS_UINT8                           ucIndex;

    /* ������ʼ�� */
    ucIndex = 0;

    VOS_MemSet(&stNetDev, 0, sizeof(struct net_device));
    VOS_sprintf(stNetDev.name, "eth_x");

    stPriv.enRmNetId = RNIC_RM_NET_ID_0;

    /* ׮���� */
    MOCKER(netdev_priv)
        .stubs()
        .will(returnValue(&stPriv));

    MOCKER(netif_carrier_off)
        .expects(exactly(1));

    MOCKER(netif_stop_queue)
        .expects(exactly(1));

    MOCKER(unregister_netdev)
        .expects(exactly(1));

    MOCKER(free_netdev)
        .expects(exactly(1));

    RNIC_SetSpecNetCardPrivate(&stPriv, ucIndex);

    /* ������ں��� */
    RNIC_DeinitNetCard(&stNetDev);

    pstPriv = RNIC_GetSpecNetCardPrivateAddr(ucIndex);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_NULL_PTR, pstPriv);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
class Test_RNIC_GetNetCardStats: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
    void TearDown()
    {
        RNIC_SetSpecNetCardPrivate(VOS_NULL_PTR, 0);
    }
};


TEST_F(Test_RNIC_GetNetCardStats, Test_RNIC_GetNetCardStats_001)
{
    struct net_device_stats            *pstStats;
    struct net_device                  *pstNetDev = VOS_NULL_PTR;

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(never());

    /* ������ں��� */
    pstStats = RNIC_GetNetCardStats(pstNetDev);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_NULL_PTR, pstStats);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}


TEST_F(Test_RNIC_GetNetCardStats, Test_RNIC_GetNetCardStats_002)
{
    struct net_device_stats            *pstStats;
    struct net_device                   stNetDev;

    VOS_MemSet(&stNetDev, 0, sizeof(struct net_device));

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    /* ������ں��� */
    pstStats = RNIC_GetNetCardStats(&stNetDev);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_NULL_PTR, pstStats);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}


TEST_F(Test_RNIC_GetNetCardStats, Test_RNIC_GetNetCardStats_003)
{
    struct net_device_stats            *pstStats;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    struct net_device_stats             stStats;

    VOS_MemSet(&stNetDev, 0, sizeof(struct net_device));
    VOS_MemSet(&stPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
    VOS_MemSet(&stStats, 0, sizeof(struct net_device_stats));

    VOS_MemCpy(&stPriv.stStats, &stStats, sizeof(stStats));

    /* ׮���� */
    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(&stPriv));

    /* ������ں��� */
    pstStats = RNIC_GetNetCardStats(&stNetDev);

    /* ����ƥ�� */
    EXPECT_EQ(&stPriv.stStats, pstStats);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}


class Test_RNIC_InitNetCard: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* ��ʼ��RNIC������ */
        pstRnicCtx  = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
    void TearDown()
    {
        /* ��ʼ��RNIC������ */
        pstRnicCtx  = RNIC_GetRnicCtxAddr();
        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
};


TEST_F(Test_RNIC_InitNetCard, Test_RNIC_InitNetCard_001)
{
    VOS_INT                             lRst;

    /* ׮���� */
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(netif_carrier_off)
        .expects(never());

    MOCKER(netif_stop_queue)
        .expects(never());

    MOCKER(register_netdev)
        .expects(never());

    MOCKER(netif_carrier_on)
        .expects(never());

    MOCKER(netif_start_queue)
        .expects(never());

    /* ������ں��� */
    lRst = RNIC_InitNetCard();

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_NOMEM, lRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}


TEST_F(Test_RNIC_InitNetCard, Test_RNIC_InitNetCard_002)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;

    stNetDev.dev_addr = VOS_NULL_PTR;

    /* ׮���� */
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev));

    MOCKER(netif_carrier_off)
        .expects(never());

    MOCKER(netif_stop_queue)
        .expects(never());

    MOCKER(register_netdev)
        .expects(never());

    MOCKER(free_netdev)
        .expects(exactly(1));

    MOCKER(netif_carrier_on)
        .expects(never());

    MOCKER(netif_start_queue)
        .expects(never());

    /* ������ں��� */
    lRst = RNIC_InitNetCard();

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_NOMEM, lRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}



TEST_F(Test_RNIC_InitNetCard, Test_RNIC_InitNetCard_003)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
    VOS_UINT8                           aucAddr[RNIC_MAC_ADDR_LEN] = {0x58,0x02,0x03,0x04,0x05,0x06};

    stNetDev.dev_addr = aucAddr;

    /* ׮���� */
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev));

    MOCKER(netif_carrier_off)
        .expects(exactly(1));

    MOCKER(netif_stop_queue)
        .expects(exactly(1));

    MOCKER(register_netdev)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    MOCKER(netdev_priv)
        .expects(exactly(1))
        .will(returnValue(&stPriv));

    MOCKER(free_netdev)
        .expects(exactly(1));

    MOCKER(netif_carrier_on)
        .expects(never());

    MOCKER(netif_start_queue)
        .expects(never());

    /* ������ں��� */
    lRst = RNIC_InitNetCard();

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_STATE, lRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}


TEST_F(Test_RNIC_InitNetCard, Test_RNIC_InitNetCard_004)
{
    VOS_INT                             lRst;
    struct net_device                   stNetDev0;
    struct net_device                   stNetDev1;
    struct net_device                   stNetDev2;
    struct net_device                   stNetDev3;
    struct net_device                   stNetDev4;
    RNIC_NETCARD_DEV_INFO_STRU          stPriv;
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    VOS_UINT8                           aucAddr[RNIC_NET_ID_MAX_NUM][RNIC_MAC_ADDR_LEN] = {
                                                {0x58,0x02,0x03,0x04,0x05,0x06},
                                                {0x58,0x02,0x03,0x04,0x05,0x07},
                                                {0x58,0x02,0x03,0x04,0x05,0x08},
                                                {0x58,0x02,0x03,0x04,0x05,0x09},
                                                {0x58,0x02,0x03,0x04,0x05,0x0a}
                                            };
#else
    VOS_UINT8                           aucAddr[RNIC_NET_ID_MAX_NUM][RNIC_MAC_ADDR_LEN] = {
                                                {0x58,0x02,0x03,0x04,0x05,0x06},
                                                {0x58,0x02,0x03,0x04,0x05,0x07},
                                                {0x58,0x02,0x03,0x04,0x05,0x08}
                                            };
#endif

    VOS_MemSet(&stNetDev0, 0, sizeof(struct net_device));
    VOS_MemSet(&stNetDev1, 0, sizeof(struct net_device));
    VOS_MemSet(&stNetDev2, 0, sizeof(struct net_device));
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    VOS_MemSet(&stNetDev3, 0, sizeof(struct net_device));
    VOS_MemSet(&stNetDev4, 0, sizeof(struct net_device));
    VOS_MemSet(&stPriv, 0, sizeof(RNIC_NETCARD_DEV_INFO_STRU));
#endif
    stNetDev0.dev_addr = aucAddr[0];
    stNetDev1.dev_addr = aucAddr[1];
    stNetDev2.dev_addr = aucAddr[2];
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    stNetDev3.dev_addr = aucAddr[3];
    stNetDev4.dev_addr = aucAddr[4];
#endif
    /* ׮���� */
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev0));
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev1));
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev2));
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev3));
    MOCKER(alloc_etherdev_mq)
        .expects(exactly(1))
        .will(returnValue(&stNetDev4));
#endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    MOCKER(netif_carrier_off)
        .expects(exactly(5));

    MOCKER(netif_stop_queue)
        .expects(exactly(5));

    MOCKER(register_netdev)
        .expects(exactly(5))
        .will(returnValue(VOS_OK));

    MOCKER(netdev_priv)
        .expects(exactly(5))
        .will(returnValue(&stPriv));

    MOCKER(netif_carrier_on)
        .expects(exactly(5));

    MOCKER(netif_start_queue)
        .expects(exactly(5));

#else
    MOCKER(netif_carrier_off)
        .expects(exactly(3));

    MOCKER(netif_stop_queue)
        .expects(exactly(3));

    MOCKER(register_netdev)
        .expects(exactly(3))
        .will(returnValue(VOS_OK));

    MOCKER(netdev_priv)
        .expects(exactly(3))
        .will(returnValue(&stPriv));

    MOCKER(netif_carrier_on)
        .expects(exactly(3));

    MOCKER(netif_start_queue)
        .expects(exactly(3));
#endif
    MOCKER(free_netdev)
        .expects(never());

    /* ������ں��� */
    lRst = RNIC_InitNetCard();

    /* ����ƥ�� */
    EXPECT_EQ(RNIC_OK, lRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}


class Test_RNIC_ConfigRmnetStatus: public ::testing::Test
{
public:
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();

    }
    void TearDown()
    {

    }
};


TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_001)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_BUTT;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = 1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* �������� */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_002)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 1;
    stConfigInfo.ucRmNetId      = 1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* �������� */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_003)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_OUTSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 0;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = 1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* �������� */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_004)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_BUTT;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = 1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* �������� */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_005)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_BUTT;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = 1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* �������� */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_006)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = 1;
    stConfigInfo.usModemId      = MODEM_ID_1;

    /* �������� */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_007)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = RNIC_RMNET_ID_BUTT;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* �������� */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_008)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;
    RNIC_RMNET_CONFIG_REQ_STRU          stSndMsg;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = RNIC_RM_NET_ID_1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* ��׮ */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(&stSndMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* �������� */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_009)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;
    RNIC_RMNET_CONFIG_REQ_STRU          stSndMsg;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = RNIC_RM_NET_ID_1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* ��׮ */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(&stSndMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(&stSndMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* �������� */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_010)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    RNIC_RMNET_CONFIG_REQ_STRU          stSndMsg;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = RNIC_RM_NET_ID_1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* ��׮ */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(&stSndMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    /* �������� */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_011)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;
    RNIC_RMNET_CONFIG_REQ_STRU          stSndMsg;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = RNIC_RM_NET_ID_1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* ��׮ */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(&stSndMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(&stSndMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));


    /* �������� */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST_F(Test_RNIC_ConfigRmnetStatus, Test_RNIC_ConfigRmnetStatus_012)
{
    /* ������ʼ�� */
    RNIC_RMNET_CONFIG_STRU              stConfigInfo;
    VOS_UINT32                          ulRet;

    stConfigInfo.enIpType       = RNIC_IP_TYPE_IPV4;
    stConfigInfo.enModemType    = RNIC_MODEM_TYPE_INSIDE;
    stConfigInfo.enRmnetStatus  = RNIC_RMNET_STATUS_UP;
    stConfigInfo.ucPdnId        = 1;
    stConfigInfo.ucRabId        = 5;
    stConfigInfo.ucRmNetId      = RNIC_RM_NET_ID_1;
    stConfigInfo.usModemId      = MODEM_ID_0;

    /* �������� */
    ulRet = RNIC_ConfigRmnetStatus(&stConfigInfo);

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
class Test_RNIC_RcvSdioDlData: public ::testing::Test
{
public:
    IMM_ZC_STRU                        *pstImmZc;
    RNIC_CTX_STRU                      *pstRnicCtx;

    void SetUp()
	{
		UT_STUB_INIT();
        /* ����A�˹����ڴ� */
        pstImmZc = IMM_ZcStaticAlloc(20);

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
    void TearDown()
    {
        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);

        memset(g_astRnicStats, 0, sizeof(g_astRnicStats));
    }
};
TEST_F(Test_RNIC_RcvSdioDlData, Test_RNIC_RcvSdioDlData_001)
{
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucPdnId;

    aulIpHeader[0] = 0x00;
    aulIpHeader[4] = 0xF0F0F0F0;
    ucPdnId        = 1;

    RNIC_SaveNetIdByPdnId(ucPdnId, RNIC_RM_NET_ID_0);

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    EXPECT_EQ(RNIC_ERROR, RNIC_RcvSdioDlData(ucPdnId, pstSkb));

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_RcvSdioDlData, Test_RNIC_RcvSdioDlData_002)
{
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucPdnId;

    aulIpHeader[0] = 0x40;
    aulIpHeader[4] = 0xF0F0F0F0;
    ucPdnId        = 1;

    RNIC_SaveNetIdByPdnId(ucPdnId, RNIC_RM_NET_ID_0);

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    MOCKER(RNIC_SendDlData)
        .will(returnValue(RNIC_OK))
        .with(eq(RNIC_RM_NET_ID_0), any(), eq(ADS_PKT_TYPE_IPV4));


    EXPECT_EQ(RNIC_OK, RNIC_RcvSdioDlData(ucPdnId, pstSkb));

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_RNIC_RcvSdioDlData, Test_RNIC_RcvSdioDlData_003)
{
    VOS_UINT32                          aulIpHeader[5] = {0};
    struct sk_buff                     *pstSkb;
    RNIC_SPEC_CTX_STRU                 *pstSpecNetCardCtx;
    VOS_UINT8                           ucPdnId;

    aulIpHeader[0] = 0x60;
    aulIpHeader[4] = 0xF0F0F0F0;
    ucPdnId        = 1;

    RNIC_SaveNetIdByPdnId(ucPdnId, RNIC_RM_NET_ID_0);

    pstSkb = (struct sk_buff *)malloc(sizeof(struct sk_buff));
    VOS_MemSet(pstSkb, 0, sizeof(struct sk_buff));

    pstSkb->data = (VOS_UINT8 *)malloc(sizeof(VOS_UINT32)*5);
    VOS_MemCpy(pstSkb->data, aulIpHeader, sizeof(VOS_UINT32)*5);

    pstSkb->private_mem.enType = MEM_TYPE_SYS_DEFINED;

    MOCKER(RNIC_SendDlData)
        .with(eq(RNIC_RM_NET_ID_0), any(), eq(ADS_PKT_TYPE_IPV6))
        .will(returnValue(RNIC_OK));

    EXPECT_EQ(RNIC_OK, RNIC_RcvSdioDlData(ucPdnId, pstSkb));

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
#endif

#endif