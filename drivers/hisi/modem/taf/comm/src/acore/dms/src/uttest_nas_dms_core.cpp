#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "dms.h"
#include "dms_core.h"
#include "ImmInterface.h"

#define    THIS_FILE_ID        PS_FILE_ID_DMS_CORE_C
//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

VOS_VOID STUB_DMS_ChanEvtCB(DMS_OM_CHAN_ENUM_UINT32 enChan, DMS_CHAN_EVT_ENUM_UINT32 enEvt)
{
	return;
}

VOS_UINT32 STUB_DMS_ChanDataReadCB(DMS_OM_CHAN_ENUM_UINT32 enChan, VOS_UINT8 *pucData, VOS_UINT32 ulLength)
{
	return VOS_OK;
}

unsigned char *UT_skb_put(struct sk_buff *skb, unsigned int len)
{
	unsigned char *tmp = skb->tail;

	return tmp;
}

extern "C" int nlmsg_msg_size(int payload)
{
	return NLMSG_HDRLEN + payload;
}

extern "C" struct nlmsghdr * UT_nlmsg_put(struct sk_buff *skb, u32 portid, u32 seq, int type, int len, int flags)
{
	struct nlmsghdr *nlh;
	int size = nlmsg_msg_size(len);

	nlh = (struct nlmsghdr*)UT_skb_put(skb, NLMSG_ALIGN(size));
	nlh->nlmsg_type = type;
	nlh->nlmsg_len = size;
	nlh->nlmsg_flags = flags;
	nlh->nlmsg_pid = portid;
	nlh->nlmsg_seq = seq;

	return nlh;
}

void UT_kfree_skb(struct sk_buff *skb)
{
	if (NULL == skb)
	{
		return;
	}

	if (MEM_TYPE_SYS_DEFINED == skb->private_mem.enType)
	{
		free(skb->head);
	}
	else if(MEM_TYPE_USER_DEFINED == skb->private_mem.enType)
	{
		;
	}

	free(skb);
	skb = NULL;
}

extern "C" void *nlmsg_data(const struct nlmsghdr *nlh)
{
	return (unsigned char *) nlh + NLMSG_HDRLEN;
}

extern "C" int nlmsg_total_size(int payload)
{
	return NLMSG_ALIGN(nlmsg_msg_size(payload));
}

extern "C" struct sk_buff *nlmsg_new(size_t payload, gfp_t flags)
{
	//return IMM_ZcStaticAlloc(nlmsg_total_size(payload));
	IMM_ZC_STRU    *pstImmZc;
	unsigned char  *pucData;
	unsigned int    ulAllignlen;

	ulAllignlen = nlmsg_total_size(payload);

	pstImmZc = (IMM_ZC_STRU*)malloc(sizeof(IMM_ZC_STRU));
	if(VOS_NULL_PTR == pstImmZc)
	{
		return VOS_NULL_PTR;
	}
	pucData = (unsigned char*)malloc(((ulAllignlen +31)&(~31)) + 64  +288 );
	if(VOS_NULL_PTR == pucData)
	{
		free(pstImmZc);
		return VOS_NULL_PTR;
	}

	memset(pstImmZc, 0x0, sizeof(IMM_ZC_STRU));

	pstImmZc->head               = pucData;
	pstImmZc->len                = ulAllignlen;
	pstImmZc->data               = pucData + 64;
	pstImmZc->tail               = pstImmZc->data;
	ulAllignlen                  = (ulAllignlen +31)&(~31);
	pstImmZc->end                = pstImmZc->data + ulAllignlen;
	pstImmZc->private_mem.enType = MEM_TYPE_SYS_DEFINED;
	pstImmZc->private_mem.pMem   = (void*)pstImmZc;
	return (struct sk_buff *)pstImmZc;
}

IMM_ZC_STRU *IMM_ZcStaticAlloc_Debug(unsigned short usFileID, unsigned short usLineNum, unsigned int ulLen)
{
	IMM_ZC_STRU    *pstImmZc;
	unsigned char  *pucData;
	unsigned int    ulAllignlen;

	ulAllignlen = ulLen;

	pstImmZc = (IMM_ZC_STRU*)malloc(sizeof(IMM_ZC_STRU));
	if(VOS_NULL_PTR == pstImmZc)
	{
		return VOS_NULL_PTR;
	}
	pucData = (unsigned char*)malloc(((ulLen +31)&(~31)) + 64  +288 );
	if(VOS_NULL_PTR == pucData)
	{
		free(pstImmZc);
		return VOS_NULL_PTR;
	}

	memset(pstImmZc, 0x0, sizeof(IMM_ZC_STRU));

	pstImmZc->head               = pucData;
	pstImmZc->len                = ulLen;
	pstImmZc->data               = pucData + 64;
	pstImmZc->tail               = pstImmZc->data;
	ulLen                       = (ulAllignlen +31)&(~31);
	pstImmZc->end                = pstImmZc->data + ulLen;
	pstImmZc->private_mem.enType = MEM_TYPE_SYS_DEFINED;
	pstImmZc->private_mem.pMem   = (void*)pstImmZc;
	return pstImmZc;
}

extern "C" struct nlmsghdr *nlmsg_hdr(const struct sk_buff *skb)
{
	return (struct nlmsghdr *)skb->data;
}


/*****************************************************************************
 ����       : Test_DMS_RegOmChanDataReadCB
 ��������   : Test_DMS_RegOmChanDataReadCB UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_RegOmChanDataReadCB: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 �����������   : Test_DMS_RegOmChanDataReadCB_001
 ������������   : ͨ���Ŵ���
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_RegOmChanDataReadCB, Test_DMS_RegOmChanDataReadCB_001)
{
    //��������
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pFunc = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    pFunc = STUB_DMS_ChanDataReadCB;
    enChan = DMS_OM_CHAN_BUTT;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����

    //���ñ��⺯��
    ulRslt = DMS_RegOmChanDataReadCB(enChan, pFunc);

    //ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_RegOmChanDataReadCB_002
 ������������   : �ص�����ָ��Ϊ��
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_RegOmChanDataReadCB, Test_DMS_RegOmChanDataReadCB_002)
{
    //��������
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pFunc = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    enChan = DMS_OM_CHAN_LTE_CTRL;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����

    //���ñ��⺯��
    ulRslt = DMS_RegOmChanDataReadCB(enChan, pFunc);

    //ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_RegOmChanDataReadCB_003
 ������������   : ע��ɹ�
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_RegOmChanDataReadCB, Test_DMS_RegOmChanDataReadCB_003)
{
    //��������
    DMS_NLK_OM_CHAN_PROPERTY_STRU      *pstOmChanProp = VOS_NULL_PTR;
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pFunc = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    pFunc = STUB_DMS_ChanDataReadCB;
    enChan = DMS_OM_CHAN_LTE_CTRL;
    pstOmChanProp = DMS_GET_NLK_OM_CHAN_PROP(enChan);

    //���ȫ�ֱ�����ʼ��

    //MOCKER����

    //���ñ��⺯��
    ulRslt = DMS_RegOmChanDataReadCB(enChan, pFunc);

    //ִ�м��
    EXPECT_EQ(STUB_DMS_ChanDataReadCB, pstOmChanProp->pDataFunc);
    EXPECT_EQ(VOS_OK, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*****************************************************************************
 ����       : Test_DMS_RegOmChanEventCB
 ��������   : Test_DMS_RegOmChanEventCB UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_RegOmChanEventCB: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 �����������   : Test_DMS_RegOmChanEventCB_001
 ������������   : ͨ���Ŵ���
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_RegOmChanEventCB, Test_DMS_RegOmChanEventCB_001)
{
    //��������
    DMS_OM_CHAN_EVENT_CB_FUNC           pFunc = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    pFunc = STUB_DMS_ChanEvtCB;
    enChan = DMS_OM_CHAN_BUTT;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����

    //���ñ��⺯��
    ulRslt = DMS_RegOmChanEventCB(enChan, pFunc);

    //ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_RegOmChanEventCB_002
 ������������   : �ص�����ָ��Ϊ��
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_RegOmChanEventCB, Test_DMS_RegOmChanEventCB_002)
{
    //��������
    DMS_OM_CHAN_EVENT_CB_FUNC           pFunc = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    enChan = DMS_OM_CHAN_LTE_CTRL;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����

    //���ñ��⺯��
    ulRslt = DMS_RegOmChanEventCB(enChan, pFunc);

    //ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_RegOmChanEventCB_003
 ������������   : ע��ɹ�
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_RegOmChanEventCB, Test_DMS_RegOmChanEventCB_003)
{
    //��������
    DMS_NLK_OM_CHAN_PROPERTY_STRU      *pstOmChanProp = VOS_NULL_PTR;
    DMS_OM_CHAN_EVENT_CB_FUNC           pFunc = VOS_NULL_PTR;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    pFunc = STUB_DMS_ChanEvtCB;
    enChan = DMS_OM_CHAN_LTE_CTRL;
    pstOmChanProp = DMS_GET_NLK_OM_CHAN_PROP(enChan);

    //���ȫ�ֱ�����ʼ��

    //MOCKER����

    //���ñ��⺯��
    ulRslt = DMS_RegOmChanEventCB(enChan, pFunc);

    //ִ�м��
    EXPECT_EQ(pFunc, pstOmChanProp->pEvtFunc);
    EXPECT_EQ(VOS_OK, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*****************************************************************************
 ����       : Test_DMS_NLK_InitEntity
 ��������   : Test_DMS_NLK_InitEntity UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_NLK_InitEntity: public ::testing::Test
{
public:

    void SetUp()
    {
    }
    void TearDown()
    {
    }
};

/*******************************************************************
 �����������   : Test_DMS_NLK_InitEntity_001
 ������������   : netlink ��ʼ��
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_InitEntity, Test_DMS_NLK_InitEntity_001)
{
    //��������

    //������ʼ��

    //���ȫ�ֱ�����ʼ��

    //MOCKER����

    //���ñ��⺯��
    DMS_NLK_InitEntity();

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*****************************************************************************
 ����       : Test_DMS_NLK_CfgOpen
 ��������   : Test_DMS_NLK_CfgOpen UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_NLK_CfgOpen: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 �����������   : Test_DMS_NLK_CfgOpen_001
 ������������   : ������غŴ���
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_CfgOpen, Test_DMS_NLK_CfgOpen_001)
{
    //��������
    struct nlmsghdr                     stNlkHdr;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_BUTT;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����

    //���ñ��⺯��
    ulRslt = DMS_NLK_CfgOpen(&stNlkHdr, enPhyBear);

    //ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_CfgOpen_002
 ������������   : ���������������ע��Ļص�����
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_CfgOpen, Test_DMS_NLK_CfgOpen_002)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    struct nlmsghdr                     stNlkHdr;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    DMS_CHAN_EVT_ENUM_UINT32            enEvt;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    stNlkHdr.nlmsg_pid = 1;
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enChan    = DMS_OM_CHAN_LTE_CTRL;
    enEvt     = DMS_CHAN_EVT_OPEN;

    //���ȫ�ֱ�����ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->astOmChanProp[enChan].pEvtFunc = STUB_DMS_ChanEvtCB;

    //MOCKER����
    MOCKER(STUB_DMS_ChanEvtCB)
	    .expects(exactly(1))
        .with(eq(enChan), eq(enEvt));

    //���ñ��⺯��
    ulRslt = DMS_NLK_CfgOpen(&stNlkHdr, enPhyBear);

    //ִ�м��
    EXPECT_EQ(stNlkHdr.nlmsg_pid, pstNlkEntity->astPhyBearProp[enPhyBear].lPid);
    EXPECT_EQ(VOS_OK, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*****************************************************************************
 ����       : Test_DMS_NLK_CfgClose
 ��������   : Test_DMS_NLK_CfgClose UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_NLK_CfgClose: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 �����������   : Test_DMS_NLK_CfgClose_001
 ������������   : ������غŴ���
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_CfgClose, Test_DMS_NLK_CfgClose_001)
{
    //��������
    struct nlmsghdr                     stNlkHdr;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_BUTT;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����

    //���ñ��⺯��
    ulRslt = DMS_NLK_CfgClose(&stNlkHdr, enPhyBear);

    //ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_CfgOpen_002
 ������������   : ���������������ע��Ļص�����
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_CfgClose, Test_DMS_NLK_CfgClose_002)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    struct nlmsghdr                     stNlkHdr;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    DMS_CHAN_EVT_ENUM_UINT32            enEvt;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    stNlkHdr.nlmsg_pid = 1;
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enChan    = DMS_OM_CHAN_LTE_CTRL;
    enEvt     = DMS_CHAN_EVT_CLOSE;

    //���ȫ�ֱ�����ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->astOmChanProp[enChan].pEvtFunc = STUB_DMS_ChanEvtCB;

    //MOCKER����
    MOCKER(STUB_DMS_ChanEvtCB)
	    .expects(exactly(1))
        .with(eq(enChan), eq(enEvt));

    //���ñ��⺯��
    ulRslt = DMS_NLK_CfgClose(&stNlkHdr, enPhyBear);

    //ִ�м��
    EXPECT_EQ(DMS_NLK_INVALID_PID, pstNlkEntity->astPhyBearProp[enPhyBear].lPid);
    EXPECT_EQ(VOS_OK, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*****************************************************************************
 ����       : Test_DMS_NLK_ProcLteCfgMsg
 ��������   : Test_DMS_NLK_ProcLteCfgMsg UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_NLK_ProcLteCfgMsg: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 �����������   : Test_DMS_NLK_ProcLteCfgMsg_001
 ������������   : �˿ڴ�
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteCfgMsg, Test_DMS_NLK_ProcLteCfgMsg_001)
{
    //��������
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_CFG_STRU));
    pstMsg = (DMS_NLK_CFG_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->enCfg = DMS_NLK_CFG_TYPE_OPEN;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(DMS_NLK_CfgOpen)
	    .expects(exactly(1))
        .with(any(), eq(enPhyBear))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //���ñ��⺯��
    DMS_NLK_ProcLteCfgMsg(pstNlkHdr);
    free(pstNlkHdr);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_CfgOpen_002
 ������������   : �˿ڹر�
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteCfgMsg, Test_DMS_NLK_ProcLteCfgMsg_002)
{
    //��������
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_CFG_STRU));
    pstMsg = (DMS_NLK_CFG_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->enCfg = DMS_NLK_CFG_TYPE_CLOSE;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(DMS_NLK_CfgClose)
	    .expects(exactly(1))
        .with(any(), eq(enPhyBear))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //���ñ��⺯��
    DMS_NLK_ProcLteCfgMsg(pstNlkHdr);
    free(pstNlkHdr);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_CfgOpen_002
 ������������   : ��Ч����
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteCfgMsg, Test_DMS_NLK_ProcLteCfgMsg_003)
{
    //��������
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;

    //������ʼ��
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_CFG_STRU));
    pstMsg = (DMS_NLK_CFG_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->enCfg = DMS_NLK_CFG_TYPE_BUTT;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(DMS_NLK_CfgOpen)
        .expects(never());

    MOCKER(DMS_NLK_CfgClose)
        .expects(never());

    //���ñ��⺯��
    DMS_NLK_ProcLteCfgMsg(pstNlkHdr);
    free(pstNlkHdr);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*****************************************************************************
 ����       : Test_DMS_NLK_ProcGuCfgMsg
 ��������   : Test_DMS_NLK_ProcGuCfgMsg UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_NLK_ProcGuCfgMsg: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 �����������   : Test_DMS_NLK_ProcGuCfgMsg_001
 ������������   : �˿ڴ�
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcGuCfgMsg, Test_DMS_NLK_ProcGuCfgMsg_001)
{
    //��������
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_GU;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_CFG_STRU));
    pstMsg = (DMS_NLK_CFG_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->enCfg = DMS_NLK_CFG_TYPE_OPEN;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(DMS_NLK_CfgOpen)
	    .expects(exactly(1))
        .with(any(), eq(enPhyBear))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //���ñ��⺯��
    DMS_NLK_ProcGuCfgMsg(pstNlkHdr);
    free(pstNlkHdr);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_ProcGuCfgMsg_002
 ������������   : �˿ڹر�
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcGuCfgMsg, Test_DMS_NLK_ProcGuCfgMsg_002)
{
    //��������
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_GU;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_CFG_STRU));
    pstMsg = (DMS_NLK_CFG_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->enCfg = DMS_NLK_CFG_TYPE_CLOSE;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(DMS_NLK_CfgClose)
	    .expects(exactly(1))
        .with(any(), eq(enPhyBear))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //���ñ��⺯��
    DMS_NLK_ProcGuCfgMsg(pstNlkHdr);
    free(pstNlkHdr);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_ProcGuCfgMsg_003
 ������������   : ��Ч����
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcGuCfgMsg, Test_DMS_NLK_ProcGuCfgMsg_003)
{
    //��������
    DMS_NLK_CFG_STRU                   *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;

    //������ʼ��
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_CFG_STRU));
    pstMsg = (DMS_NLK_CFG_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->enCfg = DMS_NLK_CFG_TYPE_BUTT;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(DMS_NLK_CfgOpen)
    .expects(never());

    MOCKER(DMS_NLK_CfgClose)
    .expects(never());

    //���ñ��⺯��
    DMS_NLK_ProcGuCfgMsg(pstNlkHdr);
    free(pstNlkHdr);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*****************************************************************************
 ����       : Test_DMS_NLK_ProcLteCtrlMsg
 ��������   : Test_DMS_NLK_ProcLteCtrlMsg UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_NLK_ProcLteCtrlMsg: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 �����������   : Test_DMS_NLK_ProcLteCtrlMsg_001
 ������������   : ͸������
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteCtrlMsg, Test_DMS_NLK_ProcLteCtrlMsg_001)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulDataLen;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enChan    = DMS_OM_CHAN_LTE_CTRL;
    ulDataLen = 10;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen);
    pstMsg = (DMS_NLK_PAYLOAD_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->ulLength = ulDataLen;

    //���ȫ�ֱ�����ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->astOmChanProp[enChan].pDataFunc = STUB_DMS_ChanDataReadCB;

    //MOCKER����
    MOCKER(STUB_DMS_ChanDataReadCB)
	    .expects(exactly(1))
        .with(eq(enChan), any(), eq(ulDataLen))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //���ñ��⺯��
    DMS_NLK_ProcLteCtrlMsg(pstNlkHdr);
    free(pstNlkHdr);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_ProcLteCtrlMsg_002
 ������������   : ��������
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteCtrlMsg, Test_DMS_NLK_ProcLteCtrlMsg_002)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    VOS_UINT32                          ulDataLen;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    ulDataLen = 10;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen);
    pstMsg = (DMS_NLK_PAYLOAD_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->ulLength = ulDataLen;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(STUB_DMS_ChanDataReadCB)
    .expects(never());

    //���ñ��⺯��
    DMS_NLK_ProcLteCtrlMsg(pstNlkHdr);
    free(pstNlkHdr);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*****************************************************************************
 ����       : Test_DMS_NLK_ProcLteDataMsg
 ��������   : Test_DMS_NLK_ProcLteDataMsg UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_NLK_ProcLteDataMsg: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 �����������   : Test_DMS_NLK_ProcLteDataMsg_001
 ������������   : ͸������
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteDataMsg, Test_DMS_NLK_ProcLteDataMsg_001)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulDataLen;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enChan    = DMS_OM_CHAN_LTE_DATA;
    ulDataLen = 10;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen);
    pstMsg = (DMS_NLK_PAYLOAD_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->ulLength = ulDataLen;

    //���ȫ�ֱ�����ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->astOmChanProp[enChan].pDataFunc = STUB_DMS_ChanDataReadCB;

    //MOCKER����
    MOCKER(STUB_DMS_ChanDataReadCB)
	    .expects(exactly(1))
        .with(eq(enChan), any(), eq(ulDataLen))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //���ñ��⺯��
    DMS_NLK_ProcLteDataMsg(pstNlkHdr);
    free(pstNlkHdr);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_ProcLteDataMsg_002
 ������������   : ��������
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcLteDataMsg, Test_DMS_NLK_ProcLteDataMsg_002)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    VOS_UINT32                          ulDataLen;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    ulDataLen = 10;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen);
    pstMsg = (DMS_NLK_PAYLOAD_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->ulLength = ulDataLen;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(STUB_DMS_ChanDataReadCB)
    .expects(never());

    //���ñ��⺯��
    DMS_NLK_ProcLteDataMsg(pstNlkHdr);
    free(pstNlkHdr);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*****************************************************************************
 ����       : Test_DMS_NLK_ProcGuDataMsg
 ��������   : Test_DMS_NLK_ProcGuDataMsg UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_NLK_ProcGuDataMsg: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 �����������   : Test_DMS_NLK_ProcGuDataMsg_001
 ������������   : ͸������
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcGuDataMsg, Test_DMS_NLK_ProcGuDataMsg_001)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_OM_CHAN_ENUM_UINT32             enChan;
    VOS_UINT32                          ulDataLen;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_GU;
    enChan    = DMS_OM_CHAN_GU_DATA;
    ulDataLen = 10;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen);
    pstMsg = (DMS_NLK_PAYLOAD_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->ulLength = ulDataLen;

    //���ȫ�ֱ�����ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->astOmChanProp[enChan].pDataFunc = STUB_DMS_ChanDataReadCB;

    //MOCKER����
    MOCKER(STUB_DMS_ChanDataReadCB)
	    .expects(exactly(1))
        .with(eq(enChan), any(), eq(ulDataLen))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //���ñ��⺯��
    DMS_NLK_ProcGuDataMsg(pstNlkHdr);
    free(pstNlkHdr);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_ProcGuDataMsg_002
 ������������   : ��������
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_ProcGuDataMsg, Test_DMS_NLK_ProcGuDataMsg_002)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    DMS_NLK_PAYLOAD_STRU               *pstMsg = VOS_NULL_PTR;
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    VOS_UINT32                          ulDataLen;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_GU;
    ulDataLen = 10;
    pstNlkHdr = (struct nlmsghdr *)malloc(NLMSG_HDRLEN + sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen);
    pstMsg = (DMS_NLK_PAYLOAD_STRU *)nlmsg_data(pstNlkHdr);
    pstMsg->ulLength = ulDataLen;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(STUB_DMS_ChanDataReadCB)
        .expects(never());

    //���ñ��⺯��
    DMS_NLK_ProcGuDataMsg(pstNlkHdr);
    free(pstNlkHdr);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*****************************************************************************
 ����       : Test_DMS_NLK_Send
 ��������   : Test_DMS_NLK_Send UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_NLK_Send: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();

		MOCKER(nlmsg_put)
			.defaults()
			.will(invoke(UT_nlmsg_put));
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 �����������   : Test_DMS_NLK_Send_001
 ������������   : socket ����
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Send, Test_DMS_NLK_Send_001)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                          ulDataLen;
    VOS_INT                             lRslt;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    pucData = (VOS_UINT8 *)malloc(ulDataLen);

    //���ȫ�ֱ�����ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = VOS_NULL_PTR;

    //MOCKER����

    //���ñ��⺯��
    lRslt = DMS_NLK_Send(enPhyBear, enMsgType, pucData, ulDataLen);
    free(pucData);

    //ִ�м��
    EXPECT_EQ(-EIO, lRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_Send_002
 ������������   : pid ����
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Send, Test_DMS_NLK_Send_002)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulSock;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                          ulDataLen;
    VOS_INT                             lRslt;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    pucData = (VOS_UINT8 *)malloc(ulDataLen);

    //���ȫ�ֱ�����ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = (struct sock *)&ulSock;
    pstNlkEntity->astPhyBearProp[enPhyBear].lPid = DMS_NLK_INVALID_PID;

    //MOCKER����

    //���ñ��⺯��
    lRslt = DMS_NLK_Send(enPhyBear, enMsgType, pucData, ulDataLen);
    free(pucData);

    //ִ�м��
    EXPECT_EQ(-EINVAL, lRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_Send_003
 ������������   : ���� netlink ��Ϣʧ��
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Send, Test_DMS_NLK_Send_003)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulSock;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                          ulDataLen;
    VOS_INT                             lRslt;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    pucData = (VOS_UINT8 *)malloc(ulDataLen);

    //���ȫ�ֱ�����ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = (struct sock *)&ulSock;
    pstNlkEntity->astPhyBearProp[enPhyBear].lPid = 1;

    //MOCKER����
    MOCKER(nlmsg_new)
        .stubs()
        .will(returnValue((sk_buff *)VOS_NULL_PTR));

    //���ñ��⺯��
    lRslt = DMS_NLK_Send(enPhyBear, enMsgType, pucData, ulDataLen);
    free(pucData);

    //ִ�м��
    EXPECT_EQ(-ENOBUFS, lRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_Send_004
 ������������   : ��� netlink ��Ϣʧ��
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Send, Test_DMS_NLK_Send_004)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulSock;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                          ulDataLen;
    VOS_INT                             lRslt;

	MOCKER(kfree_skb)
		.defaults()
		.will(invoke(UT_kfree_skb));

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    pucData = (VOS_UINT8 *)malloc(ulDataLen);

    //���ȫ�ֱ�����ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = (struct sock *)&ulSock;
    pstNlkEntity->astPhyBearProp[enPhyBear].lPid = 1;

    //MOCKER����
    MOCKER(nlmsg_put)
        .stubs()
        .will(returnValue((struct nlmsghdr *)VOS_NULL_PTR));

    //���ñ��⺯��
    lRslt = DMS_NLK_Send(enPhyBear, enMsgType, pucData, ulDataLen);
    free(pucData);

    //ִ�м��
    EXPECT_EQ(-EMSGSIZE, lRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_Send_005
 ������������   : ���� netlink ��Ϣʧ��
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Send, Test_DMS_NLK_Send_005)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulSock;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                          ulDataLen;
    VOS_INT                             lRslt;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    pucData = (VOS_UINT8 *)malloc(ulDataLen);

    //���ȫ�ֱ�����ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = (struct sock *)&ulSock;
    pstNlkEntity->astPhyBearProp[enPhyBear].lPid = 1;

    //MOCKER����
    MOCKER(netlink_unicast)
        .stubs()
        .will(returnValue((VOS_INT)-1));

	MOCKER(kfree_skb)
		.defaults()
		.will(invoke(UT_kfree_skb));

	MOCKER(nlmsg_put)
		.defaults()
		.will(invoke(UT_nlmsg_put));

    //���ñ��⺯��
    lRslt = DMS_NLK_Send(enPhyBear, enMsgType, pucData, ulDataLen);
    free(pucData);

    //ִ�м��
    EXPECT_EQ(-1, lRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_Send_006
 ������������   : ���� netlink ��Ϣ�ɹ�
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Send, Test_DMS_NLK_Send_006)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType;
    VOS_UINT32                          ulSock;
    VOS_UINT32                          ulDataLen;
    VOS_INT                             lRslt;

    //������ʼ��
    enPhyBear = DMS_NLK_PHY_BEAR_LTE;
    enMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    pucData = (VOS_UINT8 *)malloc(ulDataLen);

    //���ȫ�ֱ�����ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = (struct sock *)&ulSock;
    pstNlkEntity->astPhyBearProp[enPhyBear].lPid = 1;

    //MOCKER����
	MOCKER(netlink_unicast)
		.stubs()
		.will(returnValue((VOS_INT)0));

    //���ñ��⺯��
    lRslt = DMS_NLK_Send(enPhyBear, enMsgType, pucData, ulDataLen);
    free(pucData);

    //ִ�м��
    EXPECT_EQ(0, lRslt);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*****************************************************************************
 ����       : Test_DMS_NLK_Input
 ��������   : Test_DMS_NLK_Input UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_NLK_Input: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();

		MOCKER(nlmsg_put)
			.defaults()
			.will(invoke(UT_nlmsg_put));

		MOCKER(kfree_skb)
			.defaults()
			.will(invoke(UT_kfree_skb));
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 �����������   : Test_DMS_NLK_Input_001
 ������������   : netlink ��Ϣ����
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_001)
{
    //��������
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;

    //������ʼ��
    pstSkb = nlmsg_new(sizeof(DMS_NLK_CFG_STRU), GFP_ATOMIC);
    pstNlkHdr = nlmsg_hdr(pstSkb);
    pstNlkHdr->nlmsg_len = 0;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(DMS_NLK_ProcLteCfgMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcLteCtrlMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcLteDataMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcGuCfgMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcGuDataMsg)
        .expects(never());

	MOCKER(kfree_skb)
		.defaults()
		.will(invoke(UT_kfree_skb));

    //���ñ��⺯��
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_Input_002
 ������������   : DMS_NLK_MSG_TYPE_LTE_CFG��Ϣ
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_002)
{
    //��������
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_UINT                            ulMsgType;

    //������ʼ��
    ulMsgType = DMS_NLK_MSG_TYPE_LTE_CFG;
    ulPayloadSize = sizeof(DMS_NLK_CFG_STRU);
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);
    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)ulMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(DMS_NLK_ProcLteCfgMsg)
	    .expects(exactly(1));

    //���ñ��⺯��
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_Input_003
 ������������   : DMS_NLK_MSG_TYPE_LTE_CTRL��Ϣ
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_003)
{
    //��������
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_UINT                            ulMsgType;

    //������ʼ��
    ulMsgType = DMS_NLK_MSG_TYPE_LTE_CTRL;
    ulDataLen = 10;
    ulPayloadSize = sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen;
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);
    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)ulMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(DMS_NLK_ProcLteCtrlMsg)
	    .expects(exactly(1));

    //���ñ��⺯��
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_Input_004
 ������������   : DMS_NLK_MSG_TYPE_LTE_DATA��Ϣ
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_004)
{
    //��������
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_UINT                            ulMsgType;

    //������ʼ��
    ulMsgType = DMS_NLK_MSG_TYPE_LTE_DATA;
    ulDataLen = 10;
    ulPayloadSize = sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen;
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);
    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)ulMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(DMS_NLK_ProcLteDataMsg)
	    .expects(exactly(1));

    //���ñ��⺯��
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_Input_005
 ������������   : DMS_NLK_MSG_TYPE_GU_CFG��Ϣ
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_005)
{
    //��������
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_UINT                            ulMsgType;

    //������ʼ��
    ulMsgType = DMS_NLK_MSG_TYPE_GU_CFG;
    ulPayloadSize = sizeof(DMS_NLK_CFG_STRU);
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);
    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)ulMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(DMS_NLK_ProcGuCfgMsg)
	    .expects(exactly(1));

    //���ñ��⺯��
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_Input_006
 ������������   : DMS_NLK_MSG_TYPE_GU_DATA��Ϣ
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_006)
{
    //��������
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_UINT                            ulMsgType;

    //������ʼ��
    ulMsgType = DMS_NLK_MSG_TYPE_GU_DATA;
    ulDataLen = 10;
    ulPayloadSize = sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen;
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);
    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)ulMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(DMS_NLK_ProcGuDataMsg)
	    .expects(exactly(1));

    //���ñ��⺯��
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}
#if 0
/*******************************************************************
 �����������   : Test_DMS_NLK_Input_007
 ������������   : ��Ч��Ϣ
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Input, Test_DMS_NLK_Input_007)
{
    //��������
    struct nlmsghdr                    *pstNlkHdr = VOS_NULL_PTR;
    struct sk_buff                     *pstSkb = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT                            ulMsgSize;
    VOS_UINT                            ulPayloadSize;
    VOS_UINT                            ulMsgType;

    //������ʼ��
    ulMsgType = DMS_NLK_MSG_TYPE_BUTT;
    ulDataLen = 10;
    ulPayloadSize = sizeof(DMS_NLK_PAYLOAD_STRU) + ulDataLen;
    ulMsgSize = NLMSG_SPACE(ulPayloadSize);
    pstSkb = nlmsg_new(ulPayloadSize, GFP_ATOMIC);
    pstNlkHdr = nlmsg_put(pstSkb, 0, 0, (VOS_INT)ulMsgType,
                    (VOS_INT)(ulMsgSize - sizeof(struct nlmsghdr)), 0);

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(DMS_NLK_ProcLteCfgMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcLteCtrlMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcLteDataMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcGuCfgMsg)
        .expects(never());

    MOCKER(DMS_NLK_ProcGuDataMsg)
        .expects(never());

    //���ñ��⺯��
    DMS_NLK_Input(pstSkb);
    kfree_skb(pstSkb);

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}
#endif
/*****************************************************************************
 ����       : Test_DMS_NLK_Init
 ��������   : Test_DMS_NLK_Init UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_NLK_Init: public ::testing::Test
{
public:

    void SetUp()
    {
    }
    void TearDown()
    {
    }
};

/*******************************************************************
 �����������   : Test_DMS_NLK_Input_001
 ������������   : ���� netlink ʧ��
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Init, Test_DMS_NLK_Init_001)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;

    //������ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(netlink_kernel_create)
        .stubs()
        .will(returnValue((struct sock *)NULL));

    //���ñ��⺯��
    DMS_NLK_Init();

    //ִ�м��
    EXPECT_EQ(VOS_NULL_PTR, pstNlkEntity->pstSock);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*******************************************************************
 �����������   : Test_DMS_NLK_Init_002
 ������������   : ���� netlink �ɹ�
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Init, Test_DMS_NLK_Init_002)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulSock;

    //������ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(netlink_kernel_create)
        .stubs()
        .will(returnValue((struct sock *)&ulSock));

    //���ñ��⺯��
    DMS_NLK_Init();

    //ִ�м��
    EXPECT_EQ((struct sock *)&ulSock, pstNlkEntity->pstSock);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}

/*****************************************************************************
 ����       : Test_DMS_NLK_Exit
 ��������   : Test_DMS_NLK_Exit UT������
 �޸���ʷ   :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : ��������
*****************************************************************************/
class Test_DMS_NLK_Exit: public ::testing::Test
{
public:

    void SetUp()
    {
        DMS_NLK_InitEntity();
    }
    void TearDown()
    {
        DMS_NLK_InitEntity();
    }
};

/*******************************************************************
 �����������   : Test_DMS_NLK_Exit_001
 ������������   : �ͷ� netlink
 Ԥ�ڽ��       :
 �޸���ʷ       :
 1.��   ��  : 2014-07-17
   ��   ��  : A00165503
   �޸����� : �½�CASE
*******************************************************************/
TEST_F(Test_DMS_NLK_Exit, Test_DMS_NLK_Exit_001)
{
    //��������
    DMS_NLK_ENTITY_STRU                *pstNlkEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulSock;

    //������ʼ��
    pstNlkEntity = DMS_GET_NLK_ENTITY();
    pstNlkEntity->pstSock = (struct sock *)&ulSock;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
	MOCKER(netlink_kernel_release)
	    .expects(exactly(1));

    //���ñ��⺯��
    DMS_NLK_Exit();

    //ִ�м��
    EXPECT_EQ(VOS_NULL_PTR, pstNlkEntity->pstSock);

    //������ʱ, ��Ҫ����������λ�ü������
	GlobalMockObject::verify();
}
