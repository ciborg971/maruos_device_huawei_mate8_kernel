/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : cpm.h
  �� �� ��   : ����
  ��    ��   : ���� 47350
  ��������   : 2011��9��29��
  ����޸�   :
  ��������   : cpm.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��9��29��
    ��    ��   : ���� 47350
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CPM_H__
#define __CPM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "omnvinterface.h"
#include "msp_debug.h"


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define CPM_LOGIC_PHY_PORT(enLogicPort)     (g_astCPMLogicPortCfg[enLogicPort].enPhyPort)
#define CPM_LOGIC_SEND_FUNC(enLogicPort)    (g_astCPMLogicPortCfg[enLogicPort].pSendFunc)
#define CPM_LOGIC_RCV_FUNC(enLogicPort)     (g_astCPMLogicPortCfg[enLogicPort].pRcvFunc)

#define CPM_PHY_SEND_FUNC(enPhyPort)        (g_astCPMPhyPortCfg[enPhyPort].pSendFunc)
#define CPM_PHY_RCV_FUNC(enPhyPort)         (g_astCPMPhyPortCfg[enPhyPort].pRcvFunc)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum
{
    CPM_AT_COMM,
    CPM_OM_IND_COMM,        /* OM��ά�ɲ�˿� */
    CPM_OM_CFG_COMM,        /* OM���ö˿� */
    CPM_DIAG_COMM,
    CPM_PCVOICE_COMM,
    CPM_COMM_BUTT
};
typedef VOS_UINT32  CPM_LOGIC_PORT_ENUM_UINT32;

enum
{
    CPM_SEND_OK,
    CPM_SEND_FUNC_NULL,
    CPM_SEND_PARA_ERR,
    CPM_SEND_ERR,
    CPM_SEND_AYNC,
    CPM_SEND_BUTT
};
typedef VOS_UINT32 CPM_SEND_RESULT_ENUM_UINT32;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef VOS_UINT32 (*CPM_RCV_FUNC)(VOS_UINT8 *pucData, VOS_UINT32 ulLen);

typedef VOS_UINT32 (*CPM_SEND_FUNC)(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulLen);

/* ��������ͨ�������� */
typedef struct
{
    CPM_SEND_FUNC               pSendFunc;
    CPM_RCV_FUNC                pRcvFunc;
}CPM_PHY_PORT_CFG_STRU;

/* �����߼�ͨ�������� */
typedef struct
{
    CPM_PHY_PORT_ENUM_UINT32    enPhyPort;
    CPM_SEND_FUNC               pSendFunc;
    CPM_RCV_FUNC                pRcvFunc;
}CPM_LOGIC_PORT_CFG_STRU;


typedef struct
{
    VOS_UINT32                  ulParaErr;
    VOS_UINT32                  ulNullPtr;
}CPM_COM_PORT_ERR_INFO_STRU;

/* ����˿ڽ��մ���ͳ�� */
typedef struct
{
    VOS_UINT32                          ulPortErr;
    CPM_COM_PORT_ERR_INFO_STRU          astCPMRcvErrInfo[CPM_PORT_BUTT - CPM_IND_PORT];
}CPM_COM_PORT_RCV_ERR_INFO_STRU;


/* �߼��˿ڷ��ʹ���ͳ�� */
typedef struct
{
    VOS_UINT32                          ulPortErr;
    CPM_COM_PORT_ERR_INFO_STRU          astCPMSndErrInfo[CPM_COMM_BUTT];
}CPM_COM_PORT_SND_ERR_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID   CPM_PhySendReg(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, CPM_SEND_FUNC pSendFunc);
VOS_VOID   CPM_LogicRcvReg(CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort, CPM_RCV_FUNC pRcvFunc);
CPM_PHY_PORT_ENUM_UINT32 CPM_QueryPhyPort(CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort);
VOS_VOID   CPM_ConnectPorts(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort);
VOS_VOID   CPM_DisconnectPorts(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort);
VOS_UINT32 CBTCPM_NotifyChangePort(AT_PHY_PORT_ENUM_UINT32 enPhyPort);
VOS_VOID CPM_PnpAppPortCB(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, VOS_BOOL bPortState);
VOS_UINT32 CPM_PortAssociateInit(VOS_VOID);
VOS_UINT32 CPM_ComSend(CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort, VOS_UINT8 *pucVirData, VOS_UINT8 *pucPHYData, VOS_UINT32 ulLen);
VOS_UINT32 CPM_ComRcv(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, VOS_UINT8 *pucData, VOS_UINT32 ulLen);

/*AT�ṩ��OMע��˿ڽ��պ����Ľӿ�*/
extern VOS_VOID AT_RcvFuncReg(AT_PHY_PORT_ENUM_UINT32 ulPhyPort, CPM_RCV_FUNC pRcvFunc);

/*AT�ṩ��OM��ѯ�������ݵĺ����ӿ�*/
extern CPM_SEND_FUNC AT_QuerySndFunc(AT_PHY_PORT_ENUM_UINT32 ulPhyPort);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of cpm.h */
