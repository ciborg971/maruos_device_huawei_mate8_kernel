/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
/* systemic header files are here */
#include <linux/skbuff.h>
/* below my header files */
#include "product_config.h"
#include "skbuff.h"
#include "om.h"
#include "IpsMntn.h"
#include "NetfilterEx.h"
#include "PsCommonDef.h"
#include "OmApp.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#define     THIS_FILE_ID                    (0)


/* copy from old IpsMntn.h */
#define OM_TRANS_DATA_OFFSET_LEN        offsetof(OM_APP_TRACE_STRU, aucPara)

#define PS_OM_TRANS_DATA_OFFSET_LEN     offsetof(PS_OM_TRANS_IND_STRU, aucData)

#define PS_OM_TRANS_OM_HEADER_LEN       offsetof(PS_OM_TRANS_IND_STRU, ulSn)

#define MNTN_PKT_INFO_OFFSET_LEN        offsetof(IPS_MNTN_PKT_INFO_STRU, aucData)

#define MNTN_BRIDGE_PKT_INFO_OFFSET_LEN offsetof(IPS_MNTN_BRIDGE_PKT_INFO_STRU, aucData)

#define MNTN_APP_CMD_INFO_OFFSET_LEN    offsetof(IPS_MNTN_APP_CMD_INFO_STRU, aucData)


#define     MAC_HEADER_SIZE     (14)
#define     IP_HEADER_SIZE      (20)


extern IPS_MNTN_TRACE_CONFIG_REQ_STRU           g_stIpsTraceMsgCfg;
extern IPS_MNTN_IP_INFO_CONFIG_REQ_STRU         g_stIpsMntnIPInfoCfg;


PS_OM_TRANS_IND_STRU                        g_stIpsToOmMsg;
PS_OM_TRANS_IND_STRU                       *g_pstIpsToOmMsg = VOS_NULL_PTR;
VOS_UINT8                                   g_aucPktData[IPS_MNTN_TRACE_MAX_BYTE_LEN];
VOS_UINT8                                   g_aucCmpData[IPS_MNTN_TRACE_MAX_BYTE_LEN + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN];
VOS_UINT8           g_aucTraceData[MNTN_IP_INFO_LEN + OM_TRANS_DATA_OFFSET_LEN];


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
�����������������ڳ�ʼ�����Ի����׶�

1.��    ��   : 2014��5��21��
  ��    ��   : liukai
  �޸�����   : created
*****************************************************************************/
void test_init_IPS_MNTN(void)
{
    VOS_UINT8               *pucData;
    VOS_UINT32               ulLoop;

    g_pstIpsToOmMsg     = &g_stIpsToOmMsg;
    pucData             = (VOS_UINT8 *)g_pstIpsToOmMsg;
    for (ulLoop = 0; ulLoop < sizeof(PS_OM_TRANS_IND_STRU); ulLoop++)
    {
        *pucData = 0x0;
    }

    memset(g_aucPktData, 0x0, sizeof(g_aucPktData));
    memset(g_aucCmpData, 0x0, sizeof(g_aucCmpData));

    memset(&g_stIpsTraceMsgCfg, 0x0, sizeof(g_stIpsTraceMsgCfg));

    memset(&g_aucTraceData, 0x0, sizeof(g_aucTraceData));
}

/*****************************************************************************
�����������������ڻָ����Ի����׶�

1.��    ��   : 2014��5��21��
  ��    ��   : liukai
  �޸�����   : created
*****************************************************************************/
void test_recover_IPS_MNTN(void)
{
    test_init_IPS_MNTN();
    g_pstIpsToOmMsg = VOS_NULL_PTR;
}


void test_IPS_MNTN_SndCfgCnf2Om_001(void)
{
    IPS_MNTN_TRACE_CONFIG_CNF_STRU         *pstIpsMntnCfgCnf;
    IPS_MNTN_TRACE_CONFIG_CNF_STRU          stIpsMntnCfgCnf;

    pstIpsMntnCfgCnf        = &stIpsMntnCfgCnf;

    IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_MNTN_TRACE_CONFIG_CNF_STRU), pstIpsMntnCfgCnf);
}


int test_IPS_MNTN_SndCfgCnf2Om_002(void)
{
    IPS_MNTN_TRACE_CONFIG_CNF_STRU                  *pstIpsMntnCfgCnf;
    PS_OM_TRANS_IND_STRU                             stCmpMsg;
    int                                              lCmp;

    IPS_MNTN_TRACE_CONFIG_CNF_STRU                   stIpsMntnCfgCnf;
    VOS_UINT8                                       *pucData;
    VOS_UINT32                                       ulLoop;
    PS_OM_TRANS_IND_STRU                            *pstIpsToOmMsg = VOS_NULL_PTR;

    pstIpsToOmMsg           = &g_stIpsToOmMsg;
    pstIpsMntnCfgCnf        = &stIpsMntnCfgCnf;
    pstIpsMntnCfgCnf->enRslt= PS_FAIL;

    pucData                 = (VOS_UINT8 *)(&stCmpMsg);
    for (ulLoop = 0; ulLoop < sizeof(PS_OM_TRANS_IND_STRU); ulLoop++)
    {
        *(pucData + ulLoop)       = 0x0;
    }

    /*�Ա������Ϣ*/
    IPS_FILL_MSG_HEADER(&stCmpMsg, ACPU_PID_OM);
    stCmpMsg.usTransPrimId    = OM_TRANS_PRIMID;          /*͸����Ϣ�̶���Ϊ0x5001*/
    stCmpMsg.ucFuncType       = OM_TRANS_FUNC;            /*͸������*/
    stCmpMsg.usAppLength      = sizeof(PS_OM_TRANS_IND_STRU) - PS_OM_TRANS_OM_HEADER_LEN; /*��ȥusAppLength����֮ǰ��ie����*/
    stCmpMsg.ulSn             = 0;                        /*��ʱ��0*/
    stCmpMsg.ulTimeStamp      = 100;
    stCmpMsg.usPrimId         = ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF;                 /*����������ϢID��д*/
    stCmpMsg.usToolsId        = 0;                        /*����ID,Ŀǰ��û��ʹ��*/

    IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_MNTN_TRACE_CONFIG_CNF_STRU), pstIpsMntnCfgCnf);

    /* check �ظ�OM����Ϣ����
    ����UT������V_MEMCPY��׮���ʰ��ϴ�����PS_OM_TRANS_IND_STRU��aucData�������ݣ�
    ��δ����ִ�С���ֻ���OmMsg��ͷ��
    lCmp = memcmp(&stCmpMsg, pstIpsToOmMsg, sizeof(PS_OM_TRANS_IND_STRU));
    */
    lCmp = memcmp(&stCmpMsg, pstIpsToOmMsg, PS_OM_TRANS_DATA_OFFSET_LEN);
    if (lCmp != 0)
    {
        return -1;  /* ����ʧ�� */
    }

    return 0;   /* ���سɹ� */
}


int test_IPS_MNTN_SndCfgCnf2Om_003(void)
{
    IPS_MNTN_TRACE_CONFIG_CNF_STRU                  *pstIpsMntnCfgCnf;
    PS_OM_TRANS_IND_STRU                             stCmpMsg;
    int                                              lCmp;

    IPS_MNTN_TRACE_CONFIG_CNF_STRU                   stIpsMntnCfgCnf;
    VOS_UINT8                                       *pucData;
    VOS_UINT32                                       ulLoop;
    PS_OM_TRANS_IND_STRU                            *pstIpsToOmMsg = VOS_NULL_PTR;

    pstIpsToOmMsg            = &g_stIpsToOmMsg;
    pstIpsMntnCfgCnf         = &stIpsMntnCfgCnf;
    pstIpsMntnCfgCnf->enRslt = PS_FAIL;

    pucData                 = (VOS_UINT8 *)(&stCmpMsg);
    for (ulLoop = 0; ulLoop < sizeof(PS_OM_TRANS_IND_STRU); ulLoop++)
    {
        *(pucData + ulLoop)       = 0x0;
    }

    /*�Ա������Ϣ*/
    IPS_FILL_MSG_HEADER(&stCmpMsg, ACPU_PID_OM);
    stCmpMsg.usTransPrimId    = OM_TRANS_PRIMID;          /*͸����Ϣ�̶���Ϊ0x5001*/
    stCmpMsg.ucFuncType       = OM_TRANS_FUNC;            /*͸������*/
    stCmpMsg.usAppLength      = sizeof(PS_OM_TRANS_IND_STRU) - PS_OM_TRANS_OM_HEADER_LEN; /*��ȥusAppLength����֮ǰ��ie����*/
    stCmpMsg.ulSn             = 0;                        /*��ʱ��0*/
    stCmpMsg.ulTimeStamp      = 100;
    stCmpMsg.usPrimId         = ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF;                 /*����������ϢID��д*/
    stCmpMsg.usToolsId        = 0;                        /*����ID,Ŀǰ��û��ʹ��*/

    IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_MNTN_TRACE_CONFIG_CNF_STRU), pstIpsMntnCfgCnf);

    /* check �ظ�OM����Ϣ����
    ����UT������V_MEMCPY��׮���ʰ��ϴ�����PS_OM_TRANS_IND_STRU��aucData�������ݣ�
    ��δ����ִ�С���ֻ���OmMsg��ͷ��
    lCmp = memcmp(&stCmpMsg, pstIpsToOmMsg, sizeof(PS_OM_TRANS_IND_STRU));
    */
    lCmp = memcmp(&stCmpMsg, pstIpsToOmMsg, PS_OM_TRANS_DATA_OFFSET_LEN);
    if (lCmp != 0)
    {
        return -1;  /* ����ʧ�� */
    }

    return 0;   /* ���سɹ� */
}


int test_IPS_MNTN_TransMsg_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT8                          *pucTraceData;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                          *pucCmpData;
    VOS_UINT8                          *pucDataCur;
    OM_APP_TRACE_STRU                  *pstAppTrace;
    VOS_UINT32                          ulResult;
    VOS_INT32                           lCmp;
    VOS_UINT8                           aucTraceData[256];
    VOS_UINT8                           aucCmpData[256];
    VOS_UINT32                          ulLoop;

    ulDataLen   = 6;
    /* initial */
    for (ulLoop = 0; ulLoop < 256; ulLoop++)
    {
        aucTraceData[ulLoop] = 0x0;
        aucCmpData[ulLoop] = 0x0;
    }
    pucTraceData    = &aucTraceData[0];
    pucCmpData      = &aucCmpData[0];

    pucDataCur      = pucTraceData + OM_TRANS_DATA_OFFSET_LEN;
    for (ulLoop = 0; ulLoop < ulDataLen; ulLoop++)
    {
        (*pucDataCur) = 0x1;
    }

    pstAppTrace     = (OM_APP_TRACE_STRU *)pucCmpData;
    pstAppTrace->stAppHeader.ucFuncType = OM_TRANS_FUNC;
    pstAppTrace->stAppHeader.usLength   = (VOS_UINT16)(ulDataLen + OM_TRANS_DATA_OFFSET_LEN - VOS_OM_HEADER_LEN);
    pstAppTrace->stAppHeader.ulSn       = 10;
    pstAppTrace->stAppHeader.ulTimeStamp= 20;
    pstAppTrace->usPrimId               = ID_IPS_TRACE_MNTN_INFO;
    pucDataCur      = pucCmpData + OM_TRANS_DATA_OFFSET_LEN;
    for (ulLoop = 0; ulLoop < ulDataLen; ulLoop++)
    {
        (*pucDataCur) = 0x1;
    }

    ulResult = IPS_MNTN_TransMsg(pucTraceData, ulDataLen, ID_IPS_TRACE_MNTN_INFO);

    if (VOS_OK != ulResult)
    {
        return -1;  /* ����ʧ�� */
    }

    /* check �ظ�OM����Ϣ���� */
    lCmp = memcmp(pucTraceData, pucCmpData, ulDataLen + OM_TRANS_DATA_OFFSET_LEN);
    if (lCmp != 0)
    {
        return -1;  /* ����ʧ�� */
    }
#endif

    return 0;   /* ���سɹ� */
}
unsigned int test_IPS_MNTN_GetPktLenByTraceCfg_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    IPS_MNTN_TRACE_CONFIG_STRU      stTraceCfg;
    VOS_UINT32                      ulDataLen = 0;
    VOS_UINT32                      ulRst;
    VOS_UINT16                      usPktLen = 100;

    stTraceCfg.ulChoice =   IPS_MNTN_TRACE_NULL_CHOSEN;

    ulRst = IPS_MNTN_GetPktLenByTraceCfg(&stTraceCfg, usPktLen, &ulDataLen);

    return ulRst;
#else
    return 0;
#endif
}


int test_IPS_MNTN_GetPktLenByTraceCfg_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT32                      ulRst;
    IPS_MNTN_TRACE_CONFIG_STRU      stTraceCfg;
    VOS_UINT32                      ulDataLen;

    ulDataLen           =   100;
    stTraceCfg.ulChoice =   IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;

    ulRst = IPS_MNTN_GetPktLenByTraceCfg(&stTraceCfg, 100, &ulDataLen);

    if (0 != ulDataLen)
    {
        return -1;  /* ����ʧ�� */
    }

    if (PS_TRUE != ulRst)
    {
        return -1;  /* ����ʧ�� */
    }
#endif

    return 0;   /* ���سɹ� */
}
int test_IPS_MNTN_GetPktLenByTraceCfg_003(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT32                      ulRst;
    IPS_MNTN_TRACE_CONFIG_STRU      stTraceCfg;
    VOS_UINT32                      ulDataLen;

    ulDataLen           =   0;
    stTraceCfg.ulChoice =   IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN;
    stTraceCfg.ulTraceDataLen   = 99;

    ulRst = IPS_MNTN_GetPktLenByTraceCfg(&stTraceCfg, 100, &ulDataLen);

    if (PS_TRUE != ulRst)
    {
        return -1;
    }

    if (99 != ulDataLen)
    {
        return -1;
    }
#endif

    return 0;
}


int test_IPS_MNTN_GetPktLenByTraceCfg_004(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT32                      ulRst;
    IPS_MNTN_TRACE_CONFIG_STRU      stTraceCfg;
    VOS_UINT32                      ulDataLen;

    ulDataLen           =   0;
    stTraceCfg.ulChoice =   IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN;
    stTraceCfg.ulTraceDataLen   = 101;

    ulRst = IPS_MNTN_GetPktLenByTraceCfg(&stTraceCfg, 100, &ulDataLen);

    if (PS_TRUE != ulRst)
    {
        return -1;
    }

    if (100 != ulDataLen)
    {
        return -1;
    }
#endif

    return 0;
}


int test_IPS_MNTN_GetPktLenByTraceCfg_005(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT32                      ulRst;
    IPS_MNTN_TRACE_CONFIG_STRU      stTraceCfg;
    VOS_UINT32                      ulDataLen;

    ulDataLen           =   0;
    stTraceCfg.ulChoice =   IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN;
    stTraceCfg.ulTraceDataLen   = 101;

    ulRst = IPS_MNTN_GetPktLenByTraceCfg(&stTraceCfg, 120, &ulDataLen);

    if (PS_TRUE != ulRst)
    {
        return -1;
    }

    if (120 != ulDataLen)
    {
        return -1;
    }
#endif

    return 0;
}


int test_IPS_MNTN_GetPktLenByTraceCfg_006(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT32                      ulRst;
    IPS_MNTN_TRACE_CONFIG_STRU      stTraceCfg;
    VOS_UINT32                      ulDataLen;

    ulDataLen           =   0;
    stTraceCfg.ulChoice =   IPS_MNTN_TRACE_MSG_CHOSEN_BUTT;
    stTraceCfg.ulTraceDataLen   = 101;

    ulRst = IPS_MNTN_GetPktLenByTraceCfg(&stTraceCfg, 120, &ulDataLen);

    if (PS_FALSE != ulRst)
    {
        return -1;
    }
#endif

    return 0;
}


int test_IPS_MNTN_CtrlPktInfoCB_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT8                          *paucPktData;
    VOS_UINT16                          usPktLen;
    VOS_UINT16                          ulTraceMsgLen;
    VOS_UINT8                           aucNetIfName[IPS_IFNAMSIZ];
    VOS_UINT8                          *pucCmpData;
    OM_APP_TRACE_STRU                  *pstAppTrace;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                          ulSn;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT8                           aucPktData[40];
    VOS_UINT8                           aucCmpData[40+MNTN_PKT_INFO_OFFSET_LEN+OM_TRANS_DATA_OFFSET_LEN];

    usPktLen    = 40;
    ulSn        = 10;
    ulTimeStamp = 20;
    ulTraceMsgLen = usPktLen + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN;
    paucPktData    = (VOS_UINT8 *)aucPktData;
    pucCmpData      = (VOS_UINT8 *)aucCmpData;

    memset(aucNetIfName, 1, IPS_IFNAMSIZ);
    memset(paucPktData, 2, usPktLen);
    memset(pucCmpData, 0x7F, ulTraceMsgLen);

    pstAppTrace     = (OM_APP_TRACE_STRU *)pucCmpData;
    pstAppTrace->stAppHeader.ucFuncType = OM_TRANS_FUNC;
    pstAppTrace->stAppHeader.usLength   = (VOS_UINT16)ulTraceMsgLen;
    pstAppTrace->stAppHeader.ulSn       = 10;
    pstAppTrace->stAppHeader.ulTimeStamp= 20;
    pstAppTrace->usToolId               = 0;
    pstAppTrace->usPrimId               = ID_IPS_TRACE_RECV_ARP_PKT;

    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN, aucNetIfName, IPS_IFNAMSIZ);
    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN + MNTN_PKT_INFO_OFFSET_LEN, paucPktData, usPktLen);
    pstTraceMsg = (IPS_MNTN_PKT_INFO_STRU *)(pucCmpData + OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen = usPktLen;

    IPS_MNTN_CtrlPktInfoCB(aucNetIfName, paucPktData, usPktLen, ID_IPS_TRACE_RECV_ARP_PKT);
#endif

    return 0;
}


int test_IPS_MNTN_CtrlPktInfoCB_003(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT8                          *paucPktData;
    VOS_UINT16                          usPktLen;
    VOS_UINT16                          ulTraceMsgLen;
    VOS_UINT8                           aucNetIfName[IPS_IFNAMSIZ];
    VOS_UINT8                          *pucCmpData;
    OM_APP_TRACE_STRU                  *pstAppTrace;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                          ulSn;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT8                           aucPktData[40];
    VOS_UINT8                           aucCmpData[40 + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN];
    VOS_UINT32                          ulLastValue;
    VOS_UINT32                          ulCurrValue;

    usPktLen    = 40;
    ulSn        = 10;
    ulTimeStamp = 20;
    ulTraceMsgLen = usPktLen + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN;
    paucPktData    = (VOS_UINT8 *)aucPktData;
    pucCmpData      = (VOS_UINT8 *)aucCmpData;

    memset(aucNetIfName, 1, IPS_IFNAMSIZ);
    memset(paucPktData, 2, usPktLen);
    memset(pucCmpData, 0x7F, ulTraceMsgLen);

    pstAppTrace     = (OM_APP_TRACE_STRU *)pucCmpData;
    pstAppTrace->stAppHeader.ucFuncType  = OM_TRANS_FUNC;
    pstAppTrace->stAppHeader.usLength    = (VOS_UINT16)(usPktLen + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN - VOS_OM_HEADER_LEN);
    pstAppTrace->stAppHeader.ulSn        = 10;
    pstAppTrace->stAppHeader.ulTimeStamp = 20;
    pstAppTrace->usToolId                = 0;
    pstAppTrace->usPrimId                = ID_IPS_TRACE_RECV_ARP_PKT;

    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN, aucNetIfName, IPS_IFNAMSIZ);
    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN + MNTN_PKT_INFO_OFFSET_LEN, paucPktData, usPktLen);
    pstTraceMsg = (IPS_MNTN_PKT_INFO_STRU *)(pucCmpData + OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen = usPktLen;

    ulLastValue = g_stNfExtStats.aulStats[NF_EXT_STATS_ALLOC_MEM_FAIL];
    IPS_MNTN_CtrlPktInfoCB(aucNetIfName, paucPktData, usPktLen, ID_IPS_TRACE_RECV_ARP_PKT);
    ulCurrValue = g_stNfExtStats.aulStats[NF_EXT_STATS_ALLOC_MEM_FAIL];

    if (ulCurrValue == 1 + ulLastValue)
    {
        return 0;   /* �ɹ� */
    }
    else
    {
        return -1;  /* ʧ�� */
    }
#else
    return 0;
#endif
}


void test_IPS_MNTN_CtrlPktInfoCB_004(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT8                          *paucPktData;
    VOS_UINT16                          usPktLen;
    VOS_UINT16                          ulTraceMsgLen;
    VOS_UINT8                           aucNetIfName[IPS_IFNAMSIZ];
    VOS_UINT8                          *pucCmpData;
    OM_APP_TRACE_STRU                  *pstAppTrace;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                          ulSn;
    VOS_UINT32                          ulTimeStamp;


    usPktLen    = IPS_MNTN_TRACE_MAX_BYTE_LEN;
    ulSn        = 10;
    ulTimeStamp = 20;
    ulTraceMsgLen = IPS_MNTN_TRACE_MAX_BYTE_LEN + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN;

    paucPktData    = (VOS_UINT8 *)g_aucPktData;
    pucCmpData      = (VOS_UINT8 *)g_aucCmpData;

    memset(aucNetIfName, 1, IPS_IFNAMSIZ);
    memset(paucPktData, 2, usPktLen);
    memset(pucCmpData, 0x7F, usPktLen + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN);

    pstAppTrace     = (OM_APP_TRACE_STRU *)pucCmpData;
    pstAppTrace->stAppHeader.ucFuncType  = OM_TRANS_FUNC;
    pstAppTrace->stAppHeader.usLength    = (VOS_UINT16)(IPS_MNTN_TRACE_MAX_BYTE_LEN + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN - VOS_OM_HEADER_LEN);
    pstAppTrace->stAppHeader.ulSn        = 10;
    pstAppTrace->stAppHeader.ulTimeStamp = 20;
    pstAppTrace->usToolId                = 0;
    pstAppTrace->usPrimId                = ID_IPS_TRACE_SEND_DHCPC_PKT;

    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN, aucNetIfName, IPS_IFNAMSIZ);
    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN + MNTN_PKT_INFO_OFFSET_LEN, paucPktData, IPS_MNTN_TRACE_MAX_BYTE_LEN);
    pstTraceMsg = (IPS_MNTN_PKT_INFO_STRU *)(pucCmpData + OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen = usPktLen;

    IPS_MNTN_CtrlPktInfoCB(aucNetIfName, paucPktData, usPktLen, ID_IPS_TRACE_SEND_DHCPC_PKT);
#endif
}


void test_IPS_MNTN_PktInfoCB_003(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT8                          *paucPktData;
    VOS_UINT16                          usPktLen;
    VOS_UINT16                          ulTraceMsgLen;
    VOS_UINT8                           aucNetIfName[IPS_IFNAMSIZ];
    VOS_UINT8                          *pucCmpData;
    OM_APP_TRACE_STRU                  *pstAppTrace;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                          ulSn;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT8                           aucPktData[40];
    VOS_UINT8                           aucCmpData[40 + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN];

    usPktLen      = 40;
    ulSn          = 10;
    ulTimeStamp   = 20;
    ulTraceMsgLen = usPktLen + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN;

    paucPktData   = (VOS_UINT8 *)aucPktData;
    pucCmpData    = (VOS_UINT8 *)aucCmpData;

    memset(aucNetIfName, 1, IPS_IFNAMSIZ);
    memset(paucPktData, 2, usPktLen);
    memset(pucCmpData, 0x7F, ulTraceMsgLen);

    g_stIpsTraceMsgCfg.stPreRoutingTraceCfg.ulChoice = IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN;

    pstAppTrace     = (OM_APP_TRACE_STRU *)pucCmpData;
    pstAppTrace->stAppHeader.ucFuncType = OM_TRANS_FUNC;
    pstAppTrace->stAppHeader.usLength   = (VOS_UINT16)(ulTraceMsgLen - VOS_OM_HEADER_LEN);
    pstAppTrace->stAppHeader.ulSn       = 10;
    pstAppTrace->stAppHeader.ulTimeStamp= 20;
    pstAppTrace->usToolId               = 0;
    pstAppTrace->usPrimId               = ID_IPS_TRACE_INPUT_DATA_INFO;

    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN, aucNetIfName, IPS_IFNAMSIZ);
    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN + MNTN_PKT_INFO_OFFSET_LEN, paucPktData, usPktLen);
    pstTraceMsg = (IPS_MNTN_PKT_INFO_STRU *)(pucCmpData + OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen = usPktLen;

    IPS_MNTN_PktInfoCB(aucNetIfName, paucPktData, usPktLen, ID_IPS_TRACE_INPUT_DATA_INFO);
#endif
}


void test_IPS_MNTN_PktInfoCB_005(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT8                           aucNetIfName[IPS_IFNAMSIZ];
    VOS_UINT8                          *paucPktData;
    VOS_UINT16                          usPktLen;
    VOS_UINT8                           aucPktData[40];

    usPktLen        = 40;
    paucPktData     = (VOS_UINT8 *)aucPktData;

    g_stIpsTraceMsgCfg.stPreRoutingTraceCfg.ulChoice = IPS_MNTN_TRACE_NULL_CHOSEN;

    IPS_MNTN_PktInfoCB(aucNetIfName, paucPktData, usPktLen, ID_IPS_TRACE_INPUT_DATA_INFO);
#endif
}


void test_IPS_MNTN_PktInfoCB_006(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT8                          *paucPktData;
    VOS_UINT16                          usPktLen;
    VOS_UINT16                          ulTraceMsgLen;
    VOS_UINT8                           aucNetIfName[IPS_IFNAMSIZ];
    VOS_UINT8                          *pucCmpData;
    OM_APP_TRACE_STRU                  *pstAppTrace;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                          ulSn;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT8                           aucPktData[40];
    VOS_UINT8                           aucCmpData[40 + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN];

    usPktLen    = 40;
    ulSn        = 10;
    ulTimeStamp = 20;
    ulTraceMsgLen = usPktLen + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN;
    /*Ϊģ��ʵ�������ڴ�*/
    paucPktData    = (VOS_UINT8 *)aucPktData;
    pucCmpData      = (VOS_UINT8 *)aucCmpData;

    memset(aucNetIfName, 1, IPS_IFNAMSIZ);
    memset(paucPktData, 2, usPktLen);
    memset(pucCmpData, 0x7F, ulTraceMsgLen);

    g_stIpsTraceMsgCfg.stPreRoutingTraceCfg.ulChoice = IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN;

    pstAppTrace     = (OM_APP_TRACE_STRU *)pucCmpData;
    pstAppTrace->stAppHeader.ucFuncType = OM_TRANS_FUNC;
    pstAppTrace->stAppHeader.usLength   = (VOS_UINT16)(ulTraceMsgLen - VOS_OM_HEADER_LEN);
    pstAppTrace->stAppHeader.ulSn       = 10;
    pstAppTrace->stAppHeader.ulTimeStamp= 20;
    pstAppTrace->usToolId               = 0;
    pstAppTrace->usPrimId               = ID_IPS_TRACE_INPUT_DATA_INFO;

    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN, aucNetIfName, IPS_IFNAMSIZ);
    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN + MNTN_PKT_INFO_OFFSET_LEN, paucPktData, usPktLen);
    pstTraceMsg = (IPS_MNTN_PKT_INFO_STRU *)(pucCmpData + OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen = usPktLen;

    IPS_MNTN_PktInfoCB(aucNetIfName, paucPktData, usPktLen, ID_IPS_TRACE_INPUT_DATA_INFO);
#endif
}
void test_IPS_MNTN_PktInfoCB_007(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT8                          *paucPktData;
    VOS_UINT16                          usPktLen;
    VOS_UINT16                          ulTraceMsgLen;
    VOS_UINT8                           aucNetIfName[IPS_IFNAMSIZ];
    VOS_UINT8                          *pucCmpData;
    OM_APP_TRACE_STRU                  *pstAppTrace;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                          ulSn;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT8                           aucPktData[40];
    VOS_UINT8                           aucCmpData[40 + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN];

    usPktLen    = 40;
    ulSn        = 10;
    ulTimeStamp = 20;
    ulTraceMsgLen = 20 + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN;

    /*Ϊģ��ʵ�������ڴ�*/
    paucPktData    = (VOS_UINT8 *)aucPktData;
    pucCmpData      = (VOS_UINT8 *)aucCmpData;

    memset(aucNetIfName, 1, IPS_IFNAMSIZ);
    memset(paucPktData, 2, usPktLen);
    memset(pucCmpData, 0x7F, usPktLen + MNTN_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN);

    g_stIpsTraceMsgCfg.stPostRoutingTraceCfg.ulChoice = IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN;
    g_stIpsTraceMsgCfg.stPostRoutingTraceCfg.ulTraceDataLen = 20;

    pstAppTrace     = (OM_APP_TRACE_STRU *)pucCmpData;
    pstAppTrace->stAppHeader.ucFuncType = OM_TRANS_FUNC;
    pstAppTrace->stAppHeader.usLength   = (VOS_UINT16)(ulTraceMsgLen - VOS_OM_HEADER_LEN);
    pstAppTrace->stAppHeader.ulSn       = 10;
    pstAppTrace->stAppHeader.ulTimeStamp= 20;
    pstAppTrace->usToolId               = 0;
    pstAppTrace->usPrimId               = ID_IPS_TRACE_OUTPUT_DATA_INFO;

    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN, aucNetIfName, IPS_IFNAMSIZ);
    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN + MNTN_PKT_INFO_OFFSET_LEN, paucPktData, 20);
    pstTraceMsg = (IPS_MNTN_PKT_INFO_STRU *)(pucCmpData + OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen = usPktLen;

    IPS_MNTN_PktInfoCB(aucNetIfName, paucPktData, usPktLen, ID_IPS_TRACE_OUTPUT_DATA_INFO);
#endif
}
void test_IPS_MNTN_BridgePktInfoCB_003(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT8                           aucSrcPort[IPS_END_NAME];
    VOS_UINT8                           aucDestPort[IPS_END_NAME];
    VOS_UINT8                          *paucPktData;
    VOS_UINT16                          usPktLen;
    VOS_UINT8                           aucPktData[40];


    usPktLen        = 40;
    paucPktData     = aucPktData;

    g_stIpsTraceMsgCfg.stBridgeArpTraceCfg.ulChoice = IPS_MNTN_TRACE_NULL_CHOSEN;

    IPS_MNTN_BridgePktInfoCB(aucSrcPort, aucDestPort, paucPktData, usPktLen, ID_IPS_TRACE_BRIDGE_DATA_INFO);
#endif
}


void test_IPS_MNTN_BridgePktInfoCB_004(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT8                          *paucPktData;
    VOS_UINT16                          usPktLen;
    VOS_UINT16                          ulTraceMsgLen;
    VOS_UINT8                           aucSrcPort[IPS_END_NAME];
    VOS_UINT8                           aucDestPort[IPS_END_NAME];
    VOS_UINT8                          *pucCmpData;
    OM_APP_TRACE_STRU                  *pstAppTrace;
    IPS_MNTN_BRIDGE_PKT_INFO_STRU      *pstTraceMsg;
    VOS_UINT32                          ulSn;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT8                           aucPktData[40];
    VOS_UINT8                           aucCmpData[40 + MNTN_BRIDGE_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN];

    usPktLen    = 40;
    ulSn        = 10;
    ulTimeStamp = 20;
    ulTraceMsgLen = usPktLen + MNTN_BRIDGE_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN;

    paucPktData    = (VOS_UINT8 *)aucPktData;
    pucCmpData     = (VOS_UINT8 *)aucCmpData;

    memset(aucSrcPort, 1, IPS_END_NAME);
    memset(aucDestPort, 2, IPS_END_NAME);
    memset(paucPktData, 3, usPktLen);
    memset(pucCmpData, 0x7F, usPktLen + MNTN_BRIDGE_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN);

    g_stIpsTraceMsgCfg.stBridgeArpTraceCfg.ulChoice = IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN;

    pstAppTrace     = (OM_APP_TRACE_STRU *)pucCmpData;
    pstAppTrace->stAppHeader.ucFuncType = OM_TRANS_FUNC;
    pstAppTrace->stAppHeader.usLength   = (VOS_UINT16)(ulTraceMsgLen - VOS_OM_HEADER_LEN);
    pstAppTrace->stAppHeader.ulSn       = 10;
    pstAppTrace->stAppHeader.ulTimeStamp= 20;
    pstAppTrace->usToolId               = 0;
    pstAppTrace->usPrimId               = ID_IPS_TRACE_BRIDGE_DATA_INFO;

    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN + MNTN_BRIDGE_PKT_INFO_OFFSET_LEN, paucPktData, usPktLen);
    pstTraceMsg = (IPS_MNTN_BRIDGE_PKT_INFO_STRU *)(pucCmpData + OM_TRANS_DATA_OFFSET_LEN);
    memcpy(pstTraceMsg->aucSrcPort, aucSrcPort, IPS_END_NAME);
    memcpy(pstTraceMsg->aucDestPort, aucDestPort, IPS_END_NAME);
    pstTraceMsg->usLen = usPktLen;

    IPS_MNTN_BridgePktInfoCB(aucSrcPort, aucDestPort, paucPktData, usPktLen, ID_IPS_TRACE_BRIDGE_DATA_INFO);
#endif
}


void test_IPS_MNTN_BridgePktInfoCB_005(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    VOS_UINT8                          *paucPktData;
    VOS_UINT16                          usPktLen;
    VOS_UINT16                          ulTraceMsgLen;
    VOS_UINT8                           aucSrcPort[IPS_END_NAME];
    VOS_UINT8                           aucDestPort[IPS_END_NAME];
    VOS_UINT8                          *pucCmpData;
    OM_APP_TRACE_STRU                  *pstAppTrace;
    IPS_MNTN_BRIDGE_PKT_INFO_STRU      *pstTraceMsg;
    VOS_UINT32                          ulSn;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT8                           aucPktData[40];
    VOS_UINT8                           aucCmpData[40 + MNTN_BRIDGE_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN];

    usPktLen    = 40;
    ulSn        = 10;
    ulTimeStamp = 20;
    ulTraceMsgLen = usPktLen + MNTN_BRIDGE_PKT_INFO_OFFSET_LEN + OM_TRANS_DATA_OFFSET_LEN;

    paucPktData    = (VOS_UINT8 *)aucPktData;
    pucCmpData     = (VOS_UINT8 *)aucCmpData;

    memset(aucSrcPort, 1, IPS_END_NAME);
    memset(aucDestPort, 2, IPS_END_NAME);
    memset(paucPktData, 3, usPktLen);
    memset(pucCmpData, 0x7F, ulTraceMsgLen);

    g_stIpsTraceMsgCfg.stBridgeArpTraceCfg.ulChoice = IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN;

    pstAppTrace     = (OM_APP_TRACE_STRU *)pucCmpData;
    pstAppTrace->stAppHeader.ucFuncType  = OM_TRANS_FUNC;
    pstAppTrace->stAppHeader.usLength    = (VOS_UINT16)(ulTraceMsgLen - VOS_OM_HEADER_LEN);
    pstAppTrace->stAppHeader.ulSn        = 10;
    pstAppTrace->stAppHeader.ulTimeStamp = 20;
    pstAppTrace->usToolId                = 0;
    pstAppTrace->usPrimId                = ID_IPS_TRACE_BRIDGE_DATA_INFO;

    memcpy(pucCmpData + OM_TRANS_DATA_OFFSET_LEN + MNTN_BRIDGE_PKT_INFO_OFFSET_LEN, paucPktData, usPktLen);
    pstTraceMsg = (IPS_MNTN_BRIDGE_PKT_INFO_STRU *)(pucCmpData + OM_TRANS_DATA_OFFSET_LEN);
    memcpy(pstTraceMsg->aucSrcPort, aucSrcPort, IPS_END_NAME);
    memcpy(pstTraceMsg->aucDestPort, aucDestPort, IPS_END_NAME);
    pstTraceMsg->usLen = usPktLen;

    IPS_MNTN_BridgePktInfoCB(aucSrcPort, aucDestPort, paucPktData, usPktLen, ID_IPS_TRACE_BRIDGE_DATA_INFO);
#endif
}


unsigned char test_IPS_MNTN_BridgeTraceCfgChkParam_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    PS_BOOL_ENUM_UINT8              enRslt;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU  stCfgReq;

    stCfgReq.stBridgeArpTraceCfg.ulChoice   =   IPS_MNTN_TRACE_MSG_CHOSEN_BUTT;

    enRslt = IPS_MNTN_BridgeTraceCfgChkParam(&stCfgReq);

    return enRslt;
#else
    return 0;
#endif
}


unsigned char test_IPS_MNTN_BridgeTraceCfgChkParam_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    PS_BOOL_ENUM_UINT8              enRslt;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU  stCfgReq;

    stCfgReq.stBridgeArpTraceCfg.ulChoice   =   IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;

    enRslt = IPS_MNTN_BridgeTraceCfgChkParam(&stCfgReq);

    return enRslt;
#else
    return 1;
#endif
}


unsigned char test_IPS_MNTN_TraceCfgChkParam_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    PS_BOOL_ENUM_UINT8              enRslt;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU  stCfgReq;

    stCfgReq.stPreRoutingTraceCfg.ulChoice  =   IPS_MNTN_TRACE_MSG_CHOSEN_BUTT;

    enRslt = IPS_MNTN_TraceCfgChkParam(&stCfgReq);

    return enRslt;
#else
    return 0;
#endif
}


unsigned char test_IPS_MNTN_TraceCfgChkParam_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    PS_BOOL_ENUM_UINT8              enRslt;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU  stCfgReq;

    stCfgReq.stPreRoutingTraceCfg.ulChoice  =   IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN;
    stCfgReq.stPostRoutingTraceCfg.ulChoice =   IPS_MNTN_TRACE_MSG_CHOSEN_BUTT;

    enRslt = IPS_MNTN_TraceCfgChkParam(&stCfgReq);

    return enRslt;
#else
    return 0;
#endif
}


unsigned char test_IPS_MNTN_TraceCfgChkParam_003(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    PS_BOOL_ENUM_UINT8              enRslt;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU  stCfgReq;

    stCfgReq.stPreRoutingTraceCfg.ulChoice  =   IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN;
    stCfgReq.stPostRoutingTraceCfg.ulChoice =   IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN;

    enRslt = IPS_MNTN_TraceCfgChkParam(&stCfgReq);

    return enRslt;
#else
    return 1;
#endif
}


unsigned char test_IPS_MNTN_TraceAdvancedCfgChkParam_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    PS_BOOL_ENUM_UINT8              enRslt;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU  stCfgReq;

    stCfgReq.stBridgeArpTraceCfg.ulChoice   =   IPS_MNTN_TRACE_MSG_CHOSEN_BUTT;

    enRslt = IPS_MNTN_TraceAdvancedCfgChkParam(&stCfgReq);

    return enRslt;
#else
    return 0;
#endif
}


unsigned char test_IPS_MNTN_TraceAdvancedCfgChkParam_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    PS_BOOL_ENUM_UINT8              enRslt;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU  stCfgReq;

    stCfgReq.stBridgeArpTraceCfg.ulChoice   =   IPS_MNTN_TRACE_NULL_CHOSEN;
    stCfgReq.stPreRoutingTraceCfg.ulChoice  =   IPS_MNTN_TRACE_NULL_CHOSEN;
    stCfgReq.stPostRoutingTraceCfg.ulChoice =   IPS_MNTN_TRACE_MSG_CHOSEN_BUTT;

    enRslt = IPS_MNTN_TraceAdvancedCfgChkParam(&stCfgReq);

    return enRslt;
#else
    return 0;
#endif
}


unsigned char test_IPS_MNTN_TraceAdvancedCfgChkParam_003(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    PS_BOOL_ENUM_UINT8              enRslt;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU  stCfgReq;

    stCfgReq.stBridgeArpTraceCfg.ulChoice   =   IPS_MNTN_TRACE_NULL_CHOSEN;
    stCfgReq.stPreRoutingTraceCfg.ulChoice  =   IPS_MNTN_TRACE_NULL_CHOSEN;
    stCfgReq.stPostRoutingTraceCfg.ulChoice =   IPS_MNTN_TRACE_NULL_CHOSEN;

    enRslt = IPS_MNTN_TraceAdvancedCfgChkParam(&stCfgReq);

    return enRslt;
#else
    return 1;
#endif
}


int test_IPS_MNTN_TraceAdvancedCfgReq_001(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    OM_PS_PARAM_REQ_STRU                           *pstOmMsg;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU                 *pstIpsMntnCfgReq;
    //PS_OM_TRANS_IND_STRU                           *pstIpsToOmMsg;
    //IPS_MNTN_TRACE_CONFIG_CNF_STRU                 *pstIpsMntnCfgCnf;//�ظ�OM����Ϣ����
    VOS_UINT8                                       aucOmMsg[offsetof(OM_PS_PARAM_REQ_STRU, aucData) + sizeof(IPS_MNTN_TRACE_CONFIG_REQ_STRU)];
    PS_OM_TRANS_IND_STRU                            stIpsToOmMsg;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU                  stIpsMntnCfgReq;
    //IPS_MNTN_TRACE_CONFIG_CNF_STRU                  stIpsMntnCfgCnf;
    VOS_UINT8                                      *pucDst;
    VOS_UINT32                                      aulChoice[3];

    memset(&stIpsMntnCfgReq, 0x0, sizeof(stIpsMntnCfgReq));
    memset(aucOmMsg, 0x0, sizeof(aucOmMsg));

    pstIpsMntnCfgReq = (IPS_MNTN_TRACE_CONFIG_REQ_STRU *)(&stIpsMntnCfgReq);
    pstIpsMntnCfgReq->stBridgeArpTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_CHOSEN_BUTT;
    pstIpsMntnCfgReq->stPreRoutingTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;
    pstIpsMntnCfgReq->stPostRoutingTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;

    pstOmMsg = (OM_PS_PARAM_REQ_STRU *)(aucOmMsg);
    pucDst = pstOmMsg->aucData;

#if 0
    memset(&g_stIpsTraceMsgCfg, 0x0, sizeof(IPS_MNTN_TRACE_CONFIG_REQ_STRU));
    printf("\n001 [%u][%u][%u]\n", g_stIpsTraceMsgCfg.stBridgeArpTraceCfg.ulChoice,
        g_stIpsTraceMsgCfg.stPreRoutingTraceCfg.ulChoice,
        g_stIpsTraceMsgCfg.stPostRoutingTraceCfg.ulChoice);
#else
    /* memset����Ч�����±߲���aulChoice���� */
    aulChoice[0] = g_stIpsTraceMsgCfg.stBridgeArpTraceCfg.ulChoice;
    aulChoice[1] = g_stIpsTraceMsgCfg.stPreRoutingTraceCfg.ulChoice;
    aulChoice[2] = g_stIpsTraceMsgCfg.stPostRoutingTraceCfg.ulChoice;
#endif

    memcpy((void *)pucDst, (void *)pstIpsMntnCfgReq, sizeof(IPS_MNTN_TRACE_CONFIG_REQ_STRU));

#if 0
    pstIpsToOmMsg            = (PS_OM_TRANS_IND_STRU *)&stIpsToOmMsg;
    pstIpsMntnCfgCnf         = (IPS_MNTN_TRACE_CONFIG_CNF_STRU *)&stIpsMntnCfgCnf;
    pstIpsMntnCfgCnf->enRslt = PS_FAIL;
#endif

    IPS_MNTN_TraceAdvancedCfgReq(pstOmMsg);

#if 0
    /* �޷�check�ظ�OM����Ϣ���ݣ��������ʹ���亯��ջ�ϱ������������ﹹ��ı���
       �˳�����ʱ����ṹ�Ѿ��������޷���ΪԴ�����ϱ߹���ı������бȽ�
       cpp����Ϊ�޷����ʰ��ϴ�������ݽṹ���಻����Ƚϡ�cpp�Ѿ�ʹ��log��
       NFExt_ConfigEffective�Դ���
       �����˷�֧��� */
    result = memcmp(pstIpsToOmMsg->aucData, pstIpsMntnCfgCnf, sizeof(IPS_MNTN_TRACE_CONFIG_CNF_STRU));
    if (0 != result)
    {
        return -1;    /* FAIL */
    }
#endif

    if ((aulChoice[0] != g_stIpsTraceMsgCfg.stBridgeArpTraceCfg.ulChoice)
        || (aulChoice[1] != g_stIpsTraceMsgCfg.stPreRoutingTraceCfg.ulChoice)
        || (aulChoice[2] != g_stIpsTraceMsgCfg.stPostRoutingTraceCfg.ulChoice))
    {
        return -1;    /* FAIL */
    }
#endif

    return 0;    /* SUCC */
}
int test_IPS_MNTN_TraceAdvancedCfgReq_002(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    OM_PS_PARAM_REQ_STRU                            *pstOmMsg;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU                  *pstIpsMntnCfgReq;
    //PS_OM_TRANS_IND_STRU                            *pstIpsToOmMsg;
    //IPS_MNTN_TRACE_CONFIG_CNF_STRU                  *pstIpsMntnCfgCnf;//�ظ�OM����Ϣ����
    VOS_UINT8                                        aucOmMsg[sizeof(OM_PS_PARAM_REQ_STRU) + sizeof(IPS_MNTN_TRACE_CONFIG_REQ_STRU) -4];
    IPS_MNTN_TRACE_CONFIG_REQ_STRU                   stIpsMntnCfgReq;
    //PS_OM_TRANS_IND_STRU                             stIpsToOmMsg;
    //IPS_MNTN_TRACE_CONFIG_CNF_STRU                   stIpsMntnCfgCnf;
    int                                              result;
    VOS_UINT32                                       aulChoice[3];

    pstOmMsg = (OM_PS_PARAM_REQ_STRU *)aucOmMsg;
    pstIpsMntnCfgReq = (IPS_MNTN_TRACE_CONFIG_REQ_STRU *)&stIpsMntnCfgReq;

    pstIpsMntnCfgReq->stBridgeArpTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;
    pstIpsMntnCfgReq->stPreRoutingTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;
    pstIpsMntnCfgReq->stPostRoutingTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;

    memcpy(pstOmMsg->aucData, pstIpsMntnCfgReq, sizeof(IPS_MNTN_TRACE_CONFIG_REQ_STRU));

    /* memset����Ч�����±߲���aulChoice���� */
    aulChoice[0] = g_stIpsTraceMsgCfg.stBridgeArpTraceCfg.ulChoice;
    aulChoice[1] = g_stIpsTraceMsgCfg.stPreRoutingTraceCfg.ulChoice;
    aulChoice[2] = g_stIpsTraceMsgCfg.stPostRoutingTraceCfg.ulChoice;

#if 0
    pstIpsToOmMsg            = (PS_OM_TRANS_IND_STRU *)&stIpsToOmMsg;
    pstIpsMntnCfgCnf         = (IPS_MNTN_TRACE_CONFIG_CNF_STRU *)&stIpsMntnCfgCnf;
    pstIpsMntnCfgCnf->enRslt = PS_FAIL;
#endif

    IPS_MNTN_TraceAdvancedCfgReq(pstOmMsg);

#if 0
    /* �޷�check�ظ�OM����Ϣ���ݣ��������ʹ���亯��ջ�ϱ������������ﹹ��ı���
       �˳�����ʱ����ṹ�Ѿ��������޷���ΪԴ�����ϱ߹���ı������бȽ�
       cpp����Ϊ�޷����ʰ��ϴ�������ݽṹ���಻����Ƚϡ�cpp�Ѿ�ʹ��log��
       NFExt_ConfigEffective�Դ���
       �����˷�֧��� */
    result = memcmp(pstIpsToOmMsg->aucData, pstIpsMntnCfgCnf, sizeof(IPS_MNTN_TRACE_CONFIG_CNF_STRU));
    if (0 != result)
    {
        return -1;    /* FAIL */
    }
#endif

    if ((aulChoice[0] != g_stIpsTraceMsgCfg.stBridgeArpTraceCfg.ulChoice)
        || (aulChoice[1] != g_stIpsTraceMsgCfg.stPreRoutingTraceCfg.ulChoice)
        || (aulChoice[2] != g_stIpsTraceMsgCfg.stPostRoutingTraceCfg.ulChoice))
    {
        return -1;    /* FAIL */
    }
#endif

    return 0;    /* SUCC */
}
int test_IPS_MNTN_TraceAdvancedCfgReq_003(void)
{
#if (FEATURE_ON == FEATURE_NFEXT)
    OM_PS_PARAM_REQ_STRU                            *pstOmMsg;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU                  *pstIpsMntnCfgReq;
    PS_OM_TRANS_IND_STRU                            *pstIpsToOmMsg;
    IPS_MNTN_TRACE_CONFIG_CNF_STRU                  *pstIpsMntnCfgCnf;//�ظ�OM����Ϣ����
    VOS_UINT8                                        aucOmMsg[sizeof(OM_PS_PARAM_REQ_STRU) + sizeof(IPS_MNTN_TRACE_CONFIG_REQ_STRU) -4];
    IPS_MNTN_TRACE_CONFIG_REQ_STRU                   stIpsMntnCfgReq;
    VOS_UINT32                                       aulChoice[3];

    pstOmMsg = (OM_PS_PARAM_REQ_STRU *)aucOmMsg;
    pstIpsMntnCfgReq = (IPS_MNTN_TRACE_CONFIG_REQ_STRU *)&stIpsMntnCfgReq;

    memset(pstIpsMntnCfgReq, 0x0, sizeof(*pstIpsMntnCfgReq));

    pstIpsMntnCfgReq->stBridgeArpTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;
    pstIpsMntnCfgReq->stPreRoutingTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;
    pstIpsMntnCfgReq->stPostRoutingTraceCfg.ulChoice = IPS_MNTN_TRACE_MSG_HEADER_CHOSEN;

    memcpy(pstOmMsg->aucData, pstIpsMntnCfgReq, sizeof(IPS_MNTN_TRACE_CONFIG_REQ_STRU));

    aulChoice[0] = pstIpsMntnCfgReq->stBridgeArpTraceCfg.ulChoice;
    aulChoice[1] = pstIpsMntnCfgReq->stPreRoutingTraceCfg.ulChoice;
    aulChoice[2] = pstIpsMntnCfgReq->stPostRoutingTraceCfg.ulChoice;

#if 0
    pstIpsToOmMsg           = (PS_OM_TRANS_IND_STRU *)PS_MEM_ALLOC(ACPU_PID_NFEXT, sizeof(PS_OM_TRANS_IND_STRU));
    pstIpsMntnCfgCnf        = (IPS_MNTN_TRACE_CONFIG_CNF_STRU *)PS_MEM_ALLOC(ACPU_PID_NFEXT, sizeof(IPS_MNTN_TRACE_CONFIG_CNF_STRU));
    pstIpsMntnCfgCnf->enRslt= PS_SUCC;
#endif

    IPS_MNTN_TraceAdvancedCfgReq(pstOmMsg);

#if 0
    /* �޷�check�ظ�OM����Ϣ���ݣ��������ʹ���亯��ջ�ϱ������������ﹹ��ı���
       �˳�����ʱ����ṹ�Ѿ��������޷���ΪԴ�����ϱ߹���ı������бȽ�
       cpp����Ϊ�޷����ʰ��ϴ�������ݽṹ���಻����Ƚϡ�cpp�Ѿ�ʹ��log��
       NFExt_ConfigEffective�Դ���
       �����˷�֧��� */
    result = memcmp(pstIpsToOmMsg->aucData, pstIpsMntnCfgCnf, sizeof(IPS_MNTN_TRACE_CONFIG_CNF_STRU));
    if (0 != result)
    {
        return -1;    /* FAIL */
    }
#endif

    if ((aulChoice[0] != g_stIpsTraceMsgCfg.stBridgeArpTraceCfg.ulChoice)
        || (aulChoice[1] != g_stIpsTraceMsgCfg.stPreRoutingTraceCfg.ulChoice)
        || (aulChoice[2] != g_stIpsTraceMsgCfg.stPostRoutingTraceCfg.ulChoice))
    {
        return -1;    /* FAIL */
    }
#endif

    return 0;    /* SUCC */
}

/*****************************************************************************
������:  Test_IPS_MNTN_IPInfoCfgChkParam
��������:���յ��������ã����óɹ�
���Ա��:Test_IPS_MNTN_IPInfoCfgChkParam
���Ա���:�������1
Ԥ�ڽ��:

1.��    ��   : 2014��5��28��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
unsigned int test_IPS_MNTN_IPInfoCfgChkParam_001(void)
{
    IPS_MNTN_IP_INFO_CONFIG_REQ_STRU stIpInfoCfg;
    VOS_UINT32                       ulRst;

    stIpInfoCfg.enAdsIPConfig = PS_TRUE;
    stIpInfoCfg.enUsbIPConfig = PS_FALSE;

    ulRst = IPS_MNTN_IPInfoCfgChkParam(&stIpInfoCfg);

    return ulRst;
}

/*****************************************************************************
������:  Test_IPS_MNTN_IPInfoCfgChkParam
��������:���յ��������ã����óɹ�
���Ա��:Test_IPS_MNTN_IPInfoCfgChkParam
���Ա���:�������2
Ԥ�ڽ��:

1.��    ��   : 2014��5��28��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
unsigned int test_IPS_MNTN_IPInfoCfgChkParam_002(void)
{
    IPS_MNTN_IP_INFO_CONFIG_REQ_STRU stIpInfoCfg;
    VOS_UINT32                       ulRst;

    stIpInfoCfg.enAdsIPConfig = PS_TRUE;
    stIpInfoCfg.enUsbIPConfig = 100;

    ulRst = IPS_MNTN_IPInfoCfgChkParam(&stIpInfoCfg);

    return ulRst;
}

/*****************************************************************************
������:  Test_IPS_MNTN_IPInfoCfgChkParam
��������:���յ��������ã����óɹ�
���Ա��:Test_IPS_MNTN_IPInfoCfgChkParam
���Ա���:�������3
Ԥ�ڽ��:

1.��    ��   : 2014��5��28��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
unsigned int test_IPS_MNTN_IPInfoCfgChkParam_003(void)
{
    IPS_MNTN_IP_INFO_CONFIG_REQ_STRU stIpInfoCfg;
    VOS_UINT32                       ulRst;

    stIpInfoCfg.enAdsIPConfig = 100;
    stIpInfoCfg.enUsbIPConfig = 100;

    ulRst = IPS_MNTN_IPInfoCfgChkParam(&stIpInfoCfg);

    return ulRst;
}

/*****************************************************************************
������:  Test_IPS_MNTN_IPInfoCfgReq
��������:���յ��������ã����óɹ�
���Ա��:Test_IPS_MNTN_IPInfoCfgReq
���Ա���:�յ���������
Ԥ�ڽ��:

1.��    ��   : 2014��5��29��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
void test_IPS_MNTN_IPInfoCfgReq_001(void)
{
    IPS_MNTN_IP_INFO_CONFIG_REQ_STRU   *pstCfgReq;
    VOS_UINT8                           aucMsgData[offsetof(OM_PS_PARAM_REQ_STRU, aucData) + sizeof(IPS_MNTN_IP_INFO_CONFIG_REQ_STRU)];
    OM_PS_PARAM_REQ_STRU               *pMsg = (OM_PS_PARAM_REQ_STRU *)aucMsgData;

    memset(&g_stIpsMntnIPInfoCfg, 0x0, sizeof(IPS_MNTN_IP_INFO_CONFIG_REQ_STRU));
    memset(aucMsgData, 0x0, sizeof(aucMsgData));

    pstCfgReq = (IPS_MNTN_IP_INFO_CONFIG_REQ_STRU *)(pMsg->aucData);

    pstCfgReq->enAdsIPConfig = PS_TRUE;
    pstCfgReq->enUsbIPConfig = PS_TRUE;

    IPS_MNTN_IPInfoCfgReq((VOS_VOID *)pMsg);

#if 0
    /* UT���̽�v_memcpy��׮����˰��ϴ����v_memcpyδ����ִ��
       g_stIpsMntnIPInfoCfg�޷�ֱ�ӱȽ�
       ͨ��OM_Log���жϷ�֧ */
    ret = memcmp(pstCfgReq, &g_stIpsMntnIPInfoCfg, sizeof(IPS_MNTN_IP_INFO_CONFIG_REQ_STRU));

    if (0 != ret)
    {
        return -1;  /* FAIL */
    }
    else
    {
        return 0;   /* SUCC */
    }
 #endif
}

/*****************************************************************************
������:  Test_IPS_MNTN_IPInfoCfgReq
��������:�յ���������ΪFALSE
���Ա��:Test_IPS_MNTN_IPInfoCfgReq
���Ա���:�յ���������ΪFALSE
Ԥ�ڽ��:

1.��    ��   : 2014��5��29��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
void test_IPS_MNTN_IPInfoCfgReq_002(void)
{
    IPS_MNTN_IP_INFO_CONFIG_REQ_STRU   *pstCfgReq;
    VOS_UINT8                           aucMsgData[offsetof(OM_PS_PARAM_REQ_STRU, aucData) + sizeof(IPS_MNTN_IP_INFO_CONFIG_REQ_STRU)];
    OM_PS_PARAM_REQ_STRU               *pMsg = (OM_PS_PARAM_REQ_STRU *)aucMsgData;

    memset(aucMsgData, 0x0, sizeof(aucMsgData));
    pstCfgReq = (IPS_MNTN_IP_INFO_CONFIG_REQ_STRU *)(pMsg->aucData);

    pstCfgReq->enAdsIPConfig = PS_FALSE;
    pstCfgReq->enUsbIPConfig = PS_FALSE;

    IPS_MNTN_IPInfoCfgReq((VOS_VOID *)pMsg);

    /* UT���̽�v_memcpy��׮����˰��ϴ����v_memcpyδ����ִ��
       g_stIpsMntnIPInfoCfg�޷�ֱ�ӱȽ�
       ͨ��OM_Log���жϷ�֧ */
}

/*****************************************************************************
������:  Test_IPS_MNTN_IPInfoCfgReq
��������:�յ����������������
���Ա��:Test_IPS_MNTN_IPInfoCfgReq
���Ա���:�յ����������������
Ԥ�ڽ��:

1.��    ��   : 2014��5��29��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
void test_IPS_MNTN_IPInfoCfgReq_003(void)
{
    IPS_MNTN_IP_INFO_CONFIG_REQ_STRU   *pstCfgReq;
    VOS_UINT8                           aucMsgData[offsetof(OM_PS_PARAM_REQ_STRU, aucData) + sizeof(IPS_MNTN_IP_INFO_CONFIG_REQ_STRU)];
    OM_PS_PARAM_REQ_STRU               *pMsg = (OM_PS_PARAM_REQ_STRU *)aucMsgData;


    memset(aucMsgData, 0x0, sizeof(aucMsgData));
    pstCfgReq = (IPS_MNTN_IP_INFO_CONFIG_REQ_STRU *)(pMsg->aucData);

    pstCfgReq->enAdsIPConfig = 100;
    pstCfgReq->enUsbIPConfig = 100;

    IPS_MNTN_IPInfoCfgReq((VOS_VOID *)pMsg);
}

/*****************************************************************************
������:  Test_IPS_MNTN_Ipv4DataParse
��������:IPv4_TCP���ݽ���
���Ա��:Test_IPS_MNTN_Ipv4DataParse
���Ա���:IPv4_TCP���ݽ���
Ԥ�ڽ��:

1.��    ��   : 2014��5��29��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
int test_IPS_MNTN_Ipv4DataParse_001(void)
{
    IPS_MNTN_IP_INFO_STRU stIpInfo;
    VOS_UINT8             aucData[] = {
        0x45, 0x00, 0x04, 0x1C, 0xA8, 0x52, 0x00, 0x00,
        0x80, 0x06, 0xCD, 0xAB, 0xC0, 0xA8, 0x38, 0x80,
        0xC0, 0xA8, 0x07, 0x02, 0xFF, 0x98, 0x13, 0x88,
        0x04, 0x08, 0x23, 0xEA, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00
    };

    memset(&stIpInfo, 0, sizeof(IPS_MNTN_IP_INFO_STRU));

    stIpInfo.ucL4Proto = IP_IPV4_PROTO_TCP;

    IPS_MNTN_Ipv4DataParse(&stIpInfo, aucData);

    if (0xff98 != stIpInfo.usSrcPort)
    {
        return -1;  /* FAIL */
    }

    if (0x1388 != stIpInfo.usDstPort)
    {
        return -1;  /* FAIL */
    }

    if (0x040823ea != stIpInfo.ulL4Id)
    {
        return -1;  /* FAIL */
    }

    if (0x0 != stIpInfo.ulTcpAckSeq)
    {
        return -1;  /* FAIL */
    }

    return 0;   /* SUCC */
}

/*****************************************************************************
������:  Test_IPS_MNTN_Ipv4DataParse
��������:IPv4_UDP���ݽ���
���Ա��:Test_IPS_MNTN_Ipv4DataParse
���Ա���:IPv4_UDP���ݽ���
Ԥ�ڽ��:

1.��    ��   : 2014��5��29��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
int test_IPS_MNTN_Ipv4DataParse_002(void)
{
    IPS_MNTN_IP_INFO_STRU stIpInfo;
    VOS_UINT8             aucData[] = {
        0x45, 0x00, 0x04, 0x1C, 0xA8, 0x52, 0x00, 0x00,
        0x80, 0x11, 0xCD, 0xAB, 0xC0, 0xA8, 0x38, 0x80,
        0xC0, 0xA8, 0x07, 0x02, 0xFF, 0x98, 0x13, 0x88,
        0x04, 0x08, 0x23, 0xEA, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00
    };

    memset(&stIpInfo, 0, sizeof(IPS_MNTN_IP_INFO_STRU));

    stIpInfo.ucL4Proto = IP_IPV4_PROTO_UDP;

    IPS_MNTN_Ipv4DataParse(&stIpInfo, aucData);

    if (0xff98 != stIpInfo.usSrcPort)
    {
        return -1;  /* FAIL */
    }

    if (0x1388 != stIpInfo.usDstPort)
    {
        return -1;  /* FAIL */
    }

    if (0x0 != stIpInfo.ulL4Id)
    {
        return -1;  /* FAIL */
    }

    if (0x0 != stIpInfo.ulTcpAckSeq)
    {
        return -1;  /* FAIL */
    }

    return 0;   /* SUCC */
}

/*****************************************************************************
������:  Test_IPS_MNTN_Ipv4DataParse
��������:IPv4_ICMP���ݽ���
���Ա��:Test_IPS_MNTN_Ipv4DataParse
���Ա���:IPv4_ICMP���ݽ���
Ԥ�ڽ��:

1.��    ��   : 2014��5��29��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
int test_IPS_MNTN_Ipv4DataParse_003(void)
{
    IPS_MNTN_IP_INFO_STRU stIpInfo;
    VOS_UINT8             aucData[] = {
        0x45, 0x00, 0x04, 0x1C, 0xA8, 0x52, 0x00, 0x00,
        0x80, 0x01, 0xCD, 0xAB, 0xC0, 0xA8, 0x38, 0x80,
        0xC0, 0xA8, 0x07, 0x02, 0x08, 0x98, 0x13, 0x88,
        0x04, 0x08, 0x23, 0xEA, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00
    };

    memset(&stIpInfo, 0, sizeof(IPS_MNTN_IP_INFO_STRU));

    stIpInfo.ucL4Proto = IP_IPV4_PROTO_ICMP;

    IPS_MNTN_Ipv4DataParse(&stIpInfo, aucData);

    if (0 != stIpInfo.usSrcPort)
    {
        return -1;  /* FAIL */
    }

    if (0 != stIpInfo.usDstPort)
    {
        return -1;  /* FAIL */
    }

    if (0x40823EA != stIpInfo.ulL4Id)
    {
        return -1;  /* FAIL */
    }

    return 0;   /* SUCC */
}

/*****************************************************************************
������:  Test_IPS_MNTN_Ipv4DataParse
��������:IPv4_����Э�����ݽ���
���Ա��:Test_IPS_MNTN_Ipv4DataParse
���Ա���:IPv4_����Э�����ݽ���
Ԥ�ڽ��:

1.��    ��   : 2014��5��29��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
int test_IPS_MNTN_Ipv4DataParse_004(void)
{
    IPS_MNTN_IP_INFO_STRU stIpInfo;
    VOS_UINT8             aucData[] = {
        0x45, 0x00, 0x04, 0x1C, 0xA8, 0x52, 0x00, 0x00,
        0x80, 0x01, 0xCD, 0xAB, 0xC0, 0xA8, 0x38, 0x80,
        0xC0, 0xA8, 0x07, 0x02, 0x08, 0x98, 0x13, 0x88,
        0x04, 0x08, 0x23, 0xEA, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00
    };

    memset(&stIpInfo, 0, sizeof(IPS_MNTN_IP_INFO_STRU));

    stIpInfo.ucL4Proto = 100;

    IPS_MNTN_Ipv4DataParse(&stIpInfo, aucData);

    if (0 != stIpInfo.usSrcPort)
    {
        return -1;  /* FAIL */
    }

    if (0 != stIpInfo.usDstPort)
    {
        return -1;  /* FAIL */
    }

    if (0 != stIpInfo.ulL4Id)
    {
        return -1;  /* FAIL */
    }

    return 0;   /* SUCC */
}

/*****************************************************************************
������:  Test_IPS_MNTN_Ipv4DataParse
��������:IPv6_TCP���ݽ���
���Ա��:Test_IPS_MNTN_Ipv4DataParse
���Ա���:IPv6_TCP���ݽ���
Ԥ�ڽ��:

1.��    ��   : 2014��5��29��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
int test_IPS_MNTN_Ipv4DataParse_005(void)
{
    IPS_MNTN_IP_INFO_STRU stIpInfo;
    VOS_UINT8             aucData[] = {
        0x65, 0x00, 0x04, 0x1C, 0xA8, 0x52, 0x00, 0x00,
        0x80, 0x01, 0xCD, 0xAB, 0xC0, 0xA8, 0x38, 0x80,
        0xC0, 0xA8, 0x07, 0x02, 0x08, 0x98, 0x00, 0x04,
        0x1C, 0xA8, 0x52, 0x00, 0x00, 0x80, 0x01, 0xCD,
        0xAB, 0xC0, 0xA8, 0x38, 0x80, 0xC0, 0xA8, 0x07,
        0x02, 0x08, 0x98, 0x13, 0x88, 0x04, 0x08, 0x23,
        0xEA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    memset(&stIpInfo, 0x0, sizeof(IPS_MNTN_IP_INFO_STRU));
    stIpInfo.ucL4Proto = IP_IPV6_PROTO_TCP;

    IPS_MNTN_Ipv6DataParse(&stIpInfo, aucData);

    if (0x0208 != stIpInfo.usSrcPort)
    {
        return -1;  /* FAIL */
    }

    if (0x9813 != stIpInfo.usDstPort)
    {
        return -1;  /* FAIL */
    }

    if (0x88040823 != stIpInfo.ulL4Id)
    {
        return -1;  /* FAIL */
    }

    if (0xEA000000 != stIpInfo.ulTcpAckSeq)
    {
        return -1;  /* FAIL */
    }

    return 0;   /* SUCC */
}

/*****************************************************************************
������:  Test_IPS_MNTN_Ipv4DataParse
��������:IPv6_UDP���ݽ���
���Ա��:Test_IPS_MNTN_Ipv4DataParse
���Ա���:IPv6_UDP���ݽ���
Ԥ�ڽ��:

1.��    ��   : 2014��5��29��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
int test_IPS_MNTN_Ipv4DataParse_006(void)
{
    IPS_MNTN_IP_INFO_STRU stIpInfo;
    VOS_UINT8             aucData[] = {
        0x65, 0x00, 0x04, 0x1C, 0xA8, 0x52, 0x00, 0x00,
        0x80, 0x01, 0xCD, 0xAB, 0xC0, 0xA8, 0x38, 0x80,
        0xC0, 0xA8, 0x07, 0x02, 0x08, 0x98, 0x00, 0x04,
        0x1C, 0xA8, 0x52, 0x00, 0x00, 0x80, 0x01, 0xCD,
        0xAB, 0xC0, 0xA8, 0x38, 0x80, 0xC0, 0xA8, 0x07,
        0x02, 0x08, 0x98, 0x13, 0x88, 0x04, 0x08, 0x23,
        0xEA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    memset(&stIpInfo, 0, sizeof(IPS_MNTN_IP_INFO_STRU));
    stIpInfo.ucL4Proto = IP_IPV6_PROTO_UDP;

    IPS_MNTN_Ipv6DataParse(&stIpInfo, aucData);

    if (0x0208 != stIpInfo.usSrcPort)
    {
        return -1;  /* FAIL */
    }

    if (0x9813 != stIpInfo.usDstPort)
    {
        return -1;  /* FAIL */
    }

    if (0 != stIpInfo.ulL4Id)
    {
        return -1;  /* FAIL */
    }

    if (0 != stIpInfo.ulTcpAckSeq)
    {
        return -1;  /* FAIL */
    }

    return 0;   /* SUCC */
}

/*****************************************************************************
������:  Test_IPS_MNTN_Ipv4DataParse
��������:IPv6_ICMP���ݽ���
���Ա��:Test_IPS_MNTN_Ipv4DataParse
���Ա���:IPv6_ICMP���ݽ���
Ԥ�ڽ��:

1.��    ��   : 2014��5��29��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
int test_IPS_MNTN_Ipv4DataParse_007(void)
{
    IPS_MNTN_IP_INFO_STRU stIpInfo;
    VOS_UINT8             aucData[] = {
        0x65, 0x00, 0x04, 0x1C, 0xA8, 0x52, 0x00, 0x00,
        0x80, 0x01, 0xCD, 0xAB, 0xC0, 0xA8, 0x38, 0x80,
        0xC0, 0xA8, 0x07, 0x02, 0x08, 0x98, 0x00, 0x04,
        0x1C, 0xA8, 0x52, 0x00, 0x00, 0x80, 0x01, 0xCD,
        0xAB, 0xC0, 0xA8, 0x38, 0x80, 0xC0, 0xA8, 0x07,
        0x80, 0x08, 0x98, 0x13, 0x88, 0x04, 0x08, 0x23,
        0xEA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    memset(&stIpInfo, 0, sizeof(IPS_MNTN_IP_INFO_STRU));
    stIpInfo.ucL4Proto = IP_IPV6_PROTO_ICMP;

    IPS_MNTN_Ipv6DataParse(&stIpInfo, aucData);

    if (0 != stIpInfo.usSrcPort)
    {
        return -1;  /* FAIL */
    }

    if (0 != stIpInfo.usDstPort)
    {
        return -1;  /* FAIL */
    }

    if (0x88040823 != stIpInfo.ulL4Id)
    {
        return -1;  /* FAIL */
    }

    if (0 != stIpInfo.ulTcpAckSeq)
    {
        return -1;  /* FAIL */
    }

    return 0;   /* SUCC */
}

/*****************************************************************************
������:  Test_IPS_MNTN_Ipv4DataParse
��������:IPv6_����Э�����ݽ���
���Ա��:Test_IPS_MNTN_Ipv4DataParse
���Ա���:IPv6_����Э�����ݽ���
Ԥ�ڽ��:

1.��    ��   : 2014��5��29��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
int test_IPS_MNTN_Ipv4DataParse_008(void)
{
    IPS_MNTN_IP_INFO_STRU stIpInfo;
    VOS_UINT8             aucData[] = {
        0x65, 0x00, 0x04, 0x1C, 0xA8, 0x52, 0x00, 0x00,
        0x80, 0x01, 0xCD, 0xAB, 0xC0, 0xA8, 0x38, 0x80,
        0xC0, 0xA8, 0x07, 0x02, 0x08, 0x98, 0x00, 0x04,
        0x1C, 0xA8, 0x52, 0x00, 0x00, 0x80, 0x01, 0xCD,
        0xAB, 0xC0, 0xA8, 0x38, 0x80, 0xC0, 0xA8, 0x07,
        0x80, 0x08, 0x98, 0x13, 0x88, 0x04, 0x08, 0x23,
        0xEA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    memset(&stIpInfo, 0, sizeof(IPS_MNTN_IP_INFO_STRU));
    stIpInfo.ucL4Proto = 100;

    IPS_MNTN_Ipv6DataParse(&stIpInfo, aucData);

    if (0 != stIpInfo.usSrcPort)
    {
        return -1;  /* FAIL */
    }

    if (0 != stIpInfo.usDstPort)
    {
        return -1;  /* FAIL */
    }

    if (0 != stIpInfo.ulL4Id)
    {
        return -1;  /* FAIL */
    }

    if (0 != stIpInfo.ulTcpAckSeq)
    {
        return -1;  /* FAIL */
    }

    return 0;   /* SUCC */
}

/*****************************************************************************
������:  Test_IPS_MNTN_GetIPInfoCfg
��������:��ȡADS���ÿ���
���Ա��:Test_IPS_MNTN_GetIPInfoCfg
���Ա���:��ȡADS���ÿ���
Ԥ�ڽ��:

1.��    ��   : 2014��5��30��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
int test_IPS_MNTN_GetIPInfoCfg_001(void)
{
    VOS_UINT32      ulRst = PS_FALSE;

    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_TRUE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_FALSE;

    ulRst = IPS_MNTN_GetIPInfoCfg(ID_IPS_TRACE_IP_ADS_UL);

    /* �ָ�ȫ�ֱ��� */
    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.aucRsv[0] = 0x0;
    g_stIpsMntnIPInfoCfg.aucRsv[1] = 0x0;

    if (PS_TRUE != ulRst)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/*****************************************************************************
������:  Test_IPS_MNTN_GetIPInfoCfg
��������:��ȡUSB���ÿ���
���Ա��:Test_IPS_MNTN_GetIPInfoCfg
���Ա���:��ȡUSB���ÿ���
Ԥ�ڽ��:

1.��    ��   : 2014��5��30��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
int test_IPS_MNTN_GetIPInfoCfg_002(void)
{
    VOS_UINT32      ulRst = PS_TRUE;

    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_TRUE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_FALSE;


    ulRst = IPS_MNTN_GetIPInfoCfg(ID_IPS_TRACE_IP_USB_UL);

    /* �ָ�ȫ�ֱ��� */
    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.aucRsv[0] = 0x0;
    g_stIpsMntnIPInfoCfg.aucRsv[1] = 0x0;

    if (PS_FALSE != ulRst)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/*****************************************************************************
������:  Test_IPS_MNTN_TraceIpInfo
��������:USB��ץ������
���Ա��:Test_IPS_MNTN_TraceIpInfo
���Ա���:USB��ץ������
Ԥ�ڽ��:

1.��    ��   : 2014��5��30��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
void test_IPS_MNTN_TraceIpInfo_001(void)
{
    struct sk_buff skb;
    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_TRUE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_FALSE;

    IPS_MNTN_TraceIpInfo(&skb, ID_IPS_TRACE_IP_USB_UL, 0, 0, 0, 0);

    /* �ָ�ȫ�ֱ��� */
    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.aucRsv[0] = 0x0;
    g_stIpsMntnIPInfoCfg.aucRsv[1] = 0x0;
}

/*****************************************************************************
������:  Test_IPS_MNTN_TraceIpInfo
��������:�����ڵ�ץ���㲻����ץ��
���Ա��:Test_IPS_MNTN_TraceIpInfo
���Ա���:�����ڵ�ץ���㲻����ץ��
Ԥ�ڽ��:

1.��    ��   : 2014��5��30��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
void test_IPS_MNTN_TraceIpInfo_002(void)
{
    struct sk_buff skb;
    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_TRUE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_TRUE;

    IPS_MNTN_TraceIpInfo(&skb, 0xff, 0, 0, 0, 0);

    /* �ָ�ȫ�ֱ��� */
    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.aucRsv[0] = 0x0;
    g_stIpsMntnIPInfoCfg.aucRsv[1] = 0x0;
}

/*****************************************************************************
������:  Test_IPS_MNTN_TraceIpInfo
��������:skbΪ�ղ�����ץ��
���Ա��:Test_IPS_MNTN_TraceIpInfo
���Ա���:skbΪ�ղ�����ץ��
Ԥ�ڽ��:

1.��    ��   : 2014��5��30��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
void test_IPS_MNTN_TraceIpInfo_003(void)
{
    struct sk_buff *skb = VOS_NULL_PTR;
    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_TRUE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_TRUE;

    IPS_MNTN_TraceIpInfo(skb, ID_IPS_TRACE_IP_USB_UL, 0, 0, 0, 0);

    /* �ָ�ȫ�ֱ��� */
    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.aucRsv[0] = 0x0;
    g_stIpsMntnIPInfoCfg.aucRsv[1] = 0x0;
}

/*****************************************************************************
������:  Test_IPS_MNTN_TraceIpInfo
��������:skb����Ϊ�ղ�����ץ��
���Ա��:Test_IPS_MNTN_TraceIpInfo
���Ա���:skb����Ϊ�ղ�����ץ��
Ԥ�ڽ��:

1.��    ��   : 2014��5��30��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
void test_IPS_MNTN_TraceIpInfo_004(void)
{
    struct sk_buff skb;

    skb.data = VOS_NULL_PTR;

    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_TRUE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_TRUE;

    IPS_MNTN_TraceIpInfo(&skb, ID_IPS_TRACE_IP_USB_UL, 0, 0, 0, 0);

    /* �ָ�ȫ�ֱ��� */
    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.aucRsv[0] = 0x0;
    g_stIpsMntnIPInfoCfg.aucRsv[1] = 0x0;
}

/*****************************************************************************
������:  Test_IPS_MNTN_TraceIpInfo
��������:IPv4����ץ��
���Ա��:Test_IPS_MNTN_TraceIpInfo
���Ա���:IPv4����ץ��
Ԥ�ڽ��:

1.��    ��   : 2014��5��30��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
void test_IPS_MNTN_TraceIpInfo_005(void)
{
    struct sk_buff               skb;
    VOS_UINT8             aucData[] = {
        0x45, 0x00, 0x00, 0x31, 0xA8, 0x52, 0x00, 0x00,
        0x80, 0x11, 0xCD, 0xAB, 0xC0, 0xA8, 0x38, 0x80,
        0xC0, 0xA8, 0x07, 0x02, 0xFF, 0x98, 0x13, 0x88,
        0x04, 0x08, 0x23, 0xEA, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00
    };

    test_init_IPS_MNTN();
    memset(&skb, 0x0, sizeof(skb));

    skb.data = aucData;
    skb.len  = sizeof(aucData);
    skb.head = aucData;

#ifdef NET_SKBUFF_DATA_USES_OFFSET
    skb.network_header     = 0;
    skb.transport_header   = skb.network_header + IP_HEADER_SIZE;
#else
    skb.network_header     = skb.head;
    skb.transport_header   = skb.network_header + IP_HEADER_SIZE;
#endif

    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_TRUE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_TRUE;

    IPS_MNTN_TraceIpInfo(&skb, ID_IPS_TRACE_IP_USB_UL, 0, 0, 0, 0);

    test_recover_IPS_MNTN();
    /* �ָ�ȫ�ֱ��� */
    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.aucRsv[0] = 0x0;
    g_stIpsMntnIPInfoCfg.aucRsv[1] = 0x0;
}

/*****************************************************************************
������:  Test_IPS_MNTN_TraceIpInfo
��������:IPv6����ץ��
���Ա��:Test_IPS_MNTN_TraceIpInfo
���Ա���:IPv6����ץ��
Ԥ�ڽ��:

1.��    ��   : 2014��5��30��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
void test_IPS_MNTN_TraceIpInfo_006(void)
{
    struct sk_buff               skb;
    VOS_UINT8             aucData[] = {
        0x60, 0x00, 0x04, 0x1C, 0x00, 0x31, 0x00, 0x00,
        0x80, 0x11, 0xCD, 0xAB, 0xC0, 0xA8, 0x38, 0x80,
        0xC0, 0xA8, 0x07, 0x02, 0xFF, 0x98, 0x13, 0x88,
        0x04, 0x08, 0x23, 0xEA, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00
    };

    test_init_IPS_MNTN();
    memset(&skb, 0x0, sizeof(skb));

    skb.data = aucData;
    skb.len  = sizeof(aucData);
    skb.head = aucData;

#ifdef NET_SKBUFF_DATA_USES_OFFSET
    skb.network_header     = 0;
    skb.transport_header   = skb.network_header + IP_HEADER_SIZE;
#else
    skb.network_header     = skb.head;
    skb.transport_header   = skb.network_header + IP_HEADER_SIZE;
#endif

    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_TRUE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_TRUE;

    IPS_MNTN_TraceIpInfo(&skb, ID_IPS_TRACE_IP_USB_UL, 0, 0, 0, 0);

    test_recover_IPS_MNTN();
    /* �ָ�ȫ�ֱ��� */
    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.aucRsv[0] = 0x0;
    g_stIpsMntnIPInfoCfg.aucRsv[1] = 0x0;
}

/*****************************************************************************
������:  Test_IPS_MNTN_TraceIpInfo
��������:USB��MACͷ��IPv4����ץ��
���Ա��:Test_IPS_MNTN_TraceIpInfo
���Ա���:USB��MACͷ��IPv4����ץ��
Ԥ�ڽ��:

1.��    ��   : 2014��5��31��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
void test_IPS_MNTN_TraceIpInfo_007(void)
{
    struct sk_buff               skb;
    VOS_UINT8             aucData[] = {
        0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x22, 0x22,
        0x22, 0x22, 0x22, 0x22, 0x08, 0x00, 0x45, 0x00,
        0x00, 0x31, 0xA8, 0x52, 0x00, 0x00, 0x80, 0x11,
        0xCD, 0xAB, 0xC0, 0xA8, 0x38, 0x80, 0xC0, 0xA8,
        0x07, 0x02, 0xFF, 0x98, 0x13, 0x88, 0x04, 0x08,
        0x23, 0xEA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    test_init_IPS_MNTN();
    memset(&skb, 0x0, sizeof(skb));

    skb.data = aucData;
    skb.len  = sizeof(aucData);
    skb.head = aucData;

#ifdef NET_SKBUFF_DATA_USES_OFFSET
    skb.network_header     = MAC_HEADER_SIZE;
    skb.transport_header   = skb.network_header + IP_HEADER_SIZE;
#else
    skb.network_header     = skb.head + MAC_HEADER_SIZE;
    skb.transport_header   = skb.network_header + IP_HEADER_SIZE;
#endif

    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_TRUE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_TRUE;

    IPS_MNTN_TraceIpInfo(&skb, ID_IPS_TRACE_IP_USB_UL, 0, 0, 0, 0);

    test_recover_IPS_MNTN();
    /* �ָ�ȫ�ֱ��� */
    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.aucRsv[0] = 0x0;
    g_stIpsMntnIPInfoCfg.aucRsv[1] = 0x0;
}

/*****************************************************************************
������:  Test_IPS_MNTN_TraceIpInfo
��������:USB��MACͷ��IPv6����ץ��
���Ա��:Test_IPS_MNTN_TraceIpInfo
���Ա���:USB��MACͷ��IPv6����ץ��
Ԥ�ڽ��:

1.��    ��   : 2014��5��31��
  ��    ��   : liukai
  �޸�����   : ���쵽WinGDB
*****************************************************************************/
void test_IPS_MNTN_TraceIpInfo_008(void)
{
    struct sk_buff               skb;
    VOS_UINT8             aucData[] = {
        0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x22, 0x22,
        0x22, 0x22, 0x22, 0x22, 0x08, 0x00, 0x65, 0x00,
        0x04, 0x1C, 0x00, 0x31, 0x00, 0x00, 0x80, 0x11,
        0xCD, 0xAB, 0xC0, 0xA8, 0x38, 0x80, 0xC0, 0xA8,
        0x07, 0x02, 0xFF, 0x98, 0x13, 0x88, 0x04, 0x08,
        0x23, 0xEA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    test_init_IPS_MNTN();
    memset(&skb, 0x0, sizeof(skb));

    skb.data = aucData;
    skb.len  = sizeof(aucData);
    skb.head = aucData;

#ifdef NET_SKBUFF_DATA_USES_OFFSET
    skb.network_header     = MAC_HEADER_SIZE;
    skb.transport_header   = skb.network_header + IP_HEADER_SIZE;
#else
    skb.network_header     = skb.head + MAC_HEADER_SIZE;
    skb.transport_header   = skb.network_header + IP_HEADER_SIZE;
#endif

    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_TRUE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_TRUE;

    IPS_MNTN_TraceIpInfo(&skb, ID_IPS_TRACE_IP_USB_UL, 0, 0, 0, 0);

    test_recover_IPS_MNTN();
    /* �ָ�ȫ�ֱ��� */
    g_stIpsMntnIPInfoCfg.enAdsIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.enUsbIPConfig = PS_FALSE;
    g_stIpsMntnIPInfoCfg.aucRsv[0] = 0x0;
    g_stIpsMntnIPInfoCfg.aucRsv[1] = 0x0;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



