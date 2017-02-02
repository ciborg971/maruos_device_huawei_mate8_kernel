/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : cpm.c
  �� �� ��   : ����
  ��    ��   : ���� 47350
  ��������   : 2011��9��29��
  ����޸�   :
  ��������   : ʵ��OAMͨ���Ĺ�����,channel port manager.
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��9��29��
    ��    ��   : ���� 47350
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_CPM_C


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "cpm.h"
#include "NVIM_Interface.h"
#include "mdrv.h"
#include "diag_api.h"
#include "SOCPInterface.h"

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

CPM_PHY_PORT_CFG_STRU                   g_astCPMPhyPortCfg[CPM_PORT_BUTT - CPM_IND_PORT];
CPM_LOGIC_PORT_CFG_STRU                 g_astCPMLogicPortCfg[CPM_COMM_BUTT];

/* �˿�����ȫ�ֱ��� */
OM_CHANNLE_PORT_CFG_STRU                g_stPortCfg;

/* �߼��˿ڷ��ʹ���ͳ�� */
CPM_COM_PORT_SND_ERR_INFO_STRU          g_stCPMSndErrInfo = {0};

/* ����˿ڷ��ʹ���ͳ�� */
CPM_COM_PORT_RCV_ERR_INFO_STRU          g_stCPMRcvErrInfo = {0};

/*****************************************************************************
  3 ����������
*****************************************************************************/

/*****************************************************************************
  4 �����嶨��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : CPM_PhySendReg
 ��������  : �ṩ���ⲿ��ע�ắ������������ͨ�����յ����ݵĴ���
 �������  : enPhyPort��  ע�������ͨ����
             pRecvFunc��  ���ݽ��պ���
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID CPM_PhySendReg(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, CPM_SEND_FUNC pSendFunc)
{
    if (CPM_PORT_BUTT > enPhyPort)
    {
        CPM_PHY_SEND_FUNC(enPhyPort - CPM_IND_PORT) = pSendFunc;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CPM_LogicRcvReg
 ��������  : ���߼�ͨ��ע����պ���
 �������  : enLogicPort�� ע����߼�ͨ����
             pRecvFunc��   ���ݽ��պ���
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID CPM_LogicRcvReg(CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort, CPM_RCV_FUNC pRcvFunc)
{
    if (CPM_COMM_BUTT > enLogicPort)
    {
        CPM_LOGIC_RCV_FUNC(enLogicPort) = pRcvFunc;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CPM_QueryPhyPort
 ��������  : ��ѯ��ǰ�߼�ͨ��ʹ�õ�����˿�
 �������  : enLogicPort��  �߼�ͨ����
 �������  : ��
 �� �� ֵ  : ����ͨ����

*****************************************************************************/
CPM_PHY_PORT_ENUM_UINT32 CPM_QueryPhyPort(CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort)
{
    return CPM_LOGIC_PHY_PORT(enLogicPort);
}

/*****************************************************************************
 �� �� ��  : CPM_ConnectPorts
 ��������  : ������ͨ�����߼�ͨ��������
 �������  : enPhyPort��    ����ͨ����
             enLogicPort��  �߼�ͨ����
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID CPM_ConnectPorts(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort)
{
    if ((CPM_PORT_BUTT <= enPhyPort) || (CPM_COMM_BUTT <= enLogicPort))
    {
        return;
    }

    /* ���ӷ���ͨ�� */
    CPM_LOGIC_SEND_FUNC(enLogicPort)= CPM_PHY_SEND_FUNC(enPhyPort - CPM_IND_PORT);

    /* ���ӽ���ͨ�� */
    CPM_PHY_RCV_FUNC(enPhyPort - CPM_IND_PORT) = CPM_LOGIC_RCV_FUNC(enLogicPort);

    /* �������ͺ���ע����߼�ͨ�� */
    CPM_LOGIC_PHY_PORT(enLogicPort) = enPhyPort;

    return;
}

/*****************************************************************************
 �� �� ��  : CPM_DisconnectPorts
 ��������  : �Ͽ�����ͨ�����߼�ͨ������
 �������  : enPhyPort��    ����ͨ����
             enLogicPort��  �߼�ͨ����
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID CPM_DisconnectPorts(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort)
{
    if ((CPM_PORT_BUTT <= enPhyPort) || (CPM_COMM_BUTT <= enLogicPort))
    {
        return;
    }

    /* ���統ǰ�߼�ͨ����û��ʹ�ô�����ͨ�������ô��� */
    if (enPhyPort != CPM_LOGIC_PHY_PORT(enLogicPort))
    {
        return;
    }

    /* �Ͽ�����ͨ�� */
    CPM_PHY_RCV_FUNC(enPhyPort - CPM_IND_PORT) = VOS_NULL_PTR;

    /* �Ͽ�����ͨ�� */
    CPM_LOGIC_SEND_FUNC(enLogicPort)= VOS_NULL_PTR;
    CPM_LOGIC_PHY_PORT(enLogicPort) = CPM_PORT_BUTT;

    return;
}


/*****************************************************************************
 �� �� ��  : CPM_PortAssociateInit
 ��������  : ���ݶ˿����͹�������˿ں��߼��˿�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_OK:�ɹ�������Ϊʧ��
*****************************************************************************/
VOS_UINT32 CPM_PortAssociateInit(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i < CPM_COMM_BUTT; i++)
    {
        g_astCPMLogicPortCfg[i].enPhyPort = CPM_PORT_BUTT;
    }

#if (VOS_OS_VER == VOS_WIN32)
    g_stPortCfg.enPortNum = CPM_OM_PORT_TYPE_WIFI;
#else
    /* ��Ʒ֧��HSIC���ԣ�ֱ�ӷ��سɹ��������˿ڹ��� */
    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC))
    {
        return VOS_OK;
    }

    /* ��ȡOM���������ͨ�� */
    if (NV_OK != NV_Read(en_NV_Item_Om_Port_Type, &g_stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
    {
        return VOS_ERR;
    }
#endif

    /* ������*/
    if (CPM_OM_PORT_TYPE_USB == g_stPortCfg.enPortNum)
    {
        CPM_ConnectPorts(CPM_CFG_PORT, CPM_OM_CFG_COMM);
        CPM_ConnectPorts(CPM_IND_PORT, CPM_OM_IND_COMM);
    }
    else if (CPM_OM_PORT_TYPE_VCOM == g_stPortCfg.enPortNum)
    {
        CPM_ConnectPorts(CPM_VCOM_CFG_PORT, CPM_OM_CFG_COMM);
        CPM_ConnectPorts(CPM_VCOM_IND_PORT, CPM_OM_IND_COMM);
    }
    else if (CPM_OM_PORT_TYPE_WIFI == g_stPortCfg.enPortNum)
    {
        CPM_ConnectPorts(CPM_WIFI_AT_PORT,     CPM_AT_COMM);
        CPM_ConnectPorts(CPM_WIFI_OM_IND_PORT, CPM_OM_IND_COMM);
        CPM_ConnectPorts(CPM_WIFI_OM_CFG_PORT, CPM_OM_CFG_COMM);
    }
    /* NV���ȷʱ��USB������� */
    else
    {
        CPM_ConnectPorts(CPM_CFG_PORT, CPM_OM_CFG_COMM);
        CPM_ConnectPorts(CPM_IND_PORT, CPM_OM_IND_COMM);

        g_stPortCfg.enPortNum = CPM_OM_PORT_TYPE_USB;
    }

    /*�����ǰ����ΪUSB�������Ҫ����SOCPĬ�ϳ�ʱ*/
    if(g_stPortCfg.enPortNum == CPM_OM_PORT_TYPE_USB)
    {
        mdrv_socp_set_log_int_default_timeout();
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : CPM_ComSend
 ��������  : �������ݺ������ṩ���߼�ͨ��ʹ��
 �������  : enLogicPort���߼�ͨ����
             pucVirData:  ���������ַ
             pucPHYData:  ���������ַ
             pucData��    �������ݵ�ָ��
             ulLen:       �������ݵĳ���

 �������  : ��
 �� �� ֵ  : VOS_OK:�ɹ�������Ϊʧ��

*****************************************************************************/
VOS_UINT32 CPM_ComSend(CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort, VOS_UINT8 *pucVirData, VOS_UINT8 *pucPHYData, VOS_UINT32 ulLen)
{
    if(CPM_OM_CFG_COMM == enLogicPort)
    {
        diag_PTR(EN_DIAG_PTR_CPM_COMSEND);
    }

    /* ������� */
    if (CPM_COMM_BUTT <= enLogicPort)
    {
        g_stCPMSndErrInfo.ulPortErr++;

        return CPM_SEND_PARA_ERR;
    }

    if ((VOS_NULL_PTR == pucVirData) || (0 == ulLen))
    {
        g_stCPMSndErrInfo.astCPMSndErrInfo[enLogicPort].ulParaErr++;

        return CPM_SEND_PARA_ERR;
    }

    if (VOS_NULL_PTR == CPM_LOGIC_SEND_FUNC(enLogicPort))
    {
        g_stCPMSndErrInfo.astCPMSndErrInfo[enLogicPort].ulNullPtr++;

        return CPM_SEND_FUNC_NULL;
    }

    return CPM_LOGIC_SEND_FUNC(enLogicPort)(pucVirData, pucPHYData, ulLen);
}

/*****************************************************************************
 �� �� ��  : CPM_ComRcv
 ��������  : �������ݺ������ṩ������ͨ��ʹ��
 �������  : enPhyPort��  ����ͨ����
             pucData��    �������ݵ�ָ��
             ulLen:       �������ݵĳ���
 �������  : ��
 �� �� ֵ  : VOS_OK:�ɹ�������Ϊʧ��

*****************************************************************************/
VOS_UINT32 CPM_ComRcv(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    /* ������� */
    if (CPM_PORT_BUTT <= enPhyPort)
    {
        g_stCPMRcvErrInfo.ulPortErr++;
        diag_PTR(EN_DIAG_PTR_CPM_ERR1);

        return VOS_ERR;
    }

    if ((VOS_NULL_PTR == pucData) || (0 == ulLen))
    {
        g_stCPMRcvErrInfo.astCPMRcvErrInfo[enPhyPort - CPM_IND_PORT].ulParaErr++;
        diag_PTR(EN_DIAG_PTR_CPM_ERR2);

        return VOS_ERR;
    }

    if (VOS_NULL_PTR == CPM_PHY_RCV_FUNC(enPhyPort - CPM_IND_PORT))
    {
        /*lint -e534*/
        LogPrint1("\r\nCPM_ComRcv The Phy Port %d Rec Func is NULL", (VOS_INT)enPhyPort);
        /*lint +e534*/

        g_stCPMRcvErrInfo.astCPMRcvErrInfo[enPhyPort - CPM_IND_PORT].ulNullPtr++;
        diag_PTR(EN_DIAG_PTR_CPM_ERR3);

        return VOS_ERR;
    }

    diag_PTR(EN_DIAG_PTR_CPM_COMRCV);

    return CPM_PHY_RCV_FUNC(enPhyPort - CPM_IND_PORT)(pucData, ulLen);
}

/*****************************************************************************
 �� �� ��  : CPM_Show
 ��������  : ��ʾ��ǰ���߼�������˿ڶ�Ӧ��ϵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID CPM_Show(VOS_VOID)
{
    CPM_PHY_PORT_ENUM_UINT32    enPhyPort;
    CPM_LOGIC_PORT_ENUM_UINT32  enLogicPort;

    /*lint -e534*/
    vos_printf("\r\nCPM_Show The Logic and Phy Relation is :");
    /*lint +e534*/

    for(enLogicPort=CPM_AT_COMM; enLogicPort<CPM_COMM_BUTT; enLogicPort++)
    {
        enPhyPort = CPM_QueryPhyPort(enLogicPort);

        /*lint -e534*/
        vos_printf("\r\nThe Logic Port %d is connnect PHY Port %d.", enLogicPort, enPhyPort);
        /*lint +e534*/
    }

    /*lint -e534*/
    vos_printf("\r\nCPM_Show The Phy Info is :");
    /*lint +e534*/

    for(enPhyPort=0; enPhyPort<(CPM_PORT_BUTT - CPM_IND_PORT); enPhyPort++)
    {
        /*lint -e534*/
        vos_printf("\r\nThe Phy %d Port's Rec Func is 0x%x, Send Func is 0x%x",
                        enPhyPort,
                        g_astCPMPhyPortCfg[enPhyPort].pRcvFunc,
                        g_astCPMPhyPortCfg[enPhyPort].pSendFunc);
        /*lint +e534*/
    }

    for(enLogicPort=0; enLogicPort<CPM_COMM_BUTT; enLogicPort++)
    {
        /*lint -e534*/
        vos_printf("\r\nThe Logic %d Port's Rec Func is 0x%x, Send Func is 0x%x",
                        enLogicPort,
                        g_astCPMLogicPortCfg[enLogicPort].pRcvFunc,
                        g_astCPMLogicPortCfg[enLogicPort].pSendFunc);
        /*lint +e534*/
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CPM_ComErrShow
 ��������  : ��ʾ��ǰ���߼�������˿ڴ�����ʾ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID CPM_ComErrShow(VOS_VOID)
{
    CPM_LOGIC_PORT_ENUM_UINT32  enLogicPort;
    CPM_PHY_PORT_ENUM_UINT32    enPhyPort;

    /*lint -e534*/
    vos_printf("\r\nCPM_ComErrShow:");

    vos_printf("\r\nLogic Port Err Times: %d", g_stCPMSndErrInfo.ulPortErr);
    /*lint +e534*/

    for (enLogicPort = 0; enLogicPort < CPM_COMM_BUTT; enLogicPort++)
    {
        /*lint -e534*/
        vos_printf("\r\nLogic %d Port Para Err Times: %d", enLogicPort, g_stCPMSndErrInfo.astCPMSndErrInfo[enLogicPort].ulParaErr);
        vos_printf("\r\nLogic %d Port Null Ptr Times: %d", enLogicPort, g_stCPMSndErrInfo.astCPMSndErrInfo[enLogicPort].ulNullPtr);
        /*lint +e534*/
    }

    /*lint -e534*/
    vos_printf("\r\nPhy Port Err Times: %d", g_stCPMRcvErrInfo.ulPortErr);
    /*lint +e534*/

    for (enPhyPort = 0; enPhyPort < (CPM_PORT_BUTT - CPM_IND_PORT); enPhyPort++)
    {
        /*lint -e534*/
        vos_printf("\r\nPhy %d Port Para Err Times: %d", enPhyPort, g_stCPMRcvErrInfo.astCPMRcvErrInfo[enPhyPort].ulParaErr);
        vos_printf("\r\nPhy %d Port Null Ptr Times: %d", enPhyPort, g_stCPMRcvErrInfo.astCPMRcvErrInfo[enPhyPort].ulNullPtr);
        /*lint +e534*/
    }

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
