/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ptp_main.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2008��5��4��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   :2008-06-19
    ��    ��   :tanqiang
    �޸�����   :����̹淶����ļ�ͷע�ͣ�������ͷ�ļ���δ����ĺ�������

******************************************************************************/
#ifndef __ptp__main__h__
#define __ptp__main__h__

#ifdef __cplusplus
extern "C" {
#endif


/*PTP���г���*/
#define PTP_QDEPTH                  2048

/*PTP�������ͱ�־*/
#define PTP_QMODE                   VOS_Q_FIFO | VOS_Q_SYN

/*PTP�ڲ����ƺ����õ��¼�*/
#define PTP_EVT_CTROL_Q             0x00010000

/*PTP�������Ϣ����*/
typedef enum tagPTP_TMSG_TYPE_E
{
    PTP_TMSG_ANN_REQ,                /*  0 ����ANNЭ��������Ϣ���� */
    PTP_TMSG_SYNC_REQ,               /*  1 ����SYNCЭ��������Ϣ���� */
    PTP_TMSG_ANN_CANCEL,             /*  2 ����ANNЭ��ȡ����Ϣ���� */
    PTP_TMSG_ANN_CANCELED,           /*  3 ANN����Э����ȡ�� */
    PTP_TMSG_DELAY_RESP_SYNC_CANCEL, /*  4 ����delay resp/pdelay resp ��syncЭ��ȡ��������Ϣ���� */
    PTP_TMSG_DELAY_RESP_REQ,         /*  5 �ಥ�յ�ann��ʱ������������� */
    PTP_TMSG_ACCEPT_MASTER_DEL,      /*  6 ɾ���ɽ���master���еĽڵ� */

    PTP_TMSG_FSM_INIT,               /*  7 ��ʼ��PTP״̬����Ϣ���� */
    PTP_TMSG_FSM_DISABLE,            /*  8 ȥʹ��PTP״̬����Ϣ���� */
    PTP_TMSG_FSM_ENABLE,             /*  9 ʹ��PTP״̬����Ϣ���� */
    PTP_TMSG_FSM_LOCKED,             /* 10 ��PTP״̬������LOCKED�¼���Ϣ���� */
    PTP_TMSG_FSM_STATE_DECISION,     /* 11 �ı��ֶ�ѡԴ�Զ�ѡԴ��ʱ����ܴ������¼� */
    /*Added by wangchengyang-xujun62830-57575 for VISPV1R8C01-201, 2009/5/8 */
    PTP_TMSG_ACCEPT_MASTER_ENABLE,   /* 12 ʹ�ܿɽ���Master�б� */
    PTP_TMSG_ACCEPT_MASTER_DISABLE,  /* 13 ȥʹ�ܿɽ���Master�б� */
    /* End of Added by wangchengyang-xujun62830-57575, 2009/5/8 */
}PTP_TMSG_TYPE_E;


/*PTP��������Ϣ�����ݽṹ*/
typedef struct tagPTP_TMSG_S
{
   ULONG   ulMsgType       ;   /* ��Ϣ���� */
   ULONG   ulPortNumber;       /* �˿ں�*/
   PTP_PORT_ADDR_S stDstAddr;  /* ���𵥲�Э�̵�Ŀ�ĵ�ַ*/
   ULONG   ulVrfIndex;
}PTP_TMSG_S;

/*����PTP ģ��ϵͳ����Ϣ���ݽṹ����Shell���ʱʹ��*/
typedef struct tagPTP_SYS_INFO_S
{
    ULONG ulPtpTaskId;      /*PTP����Id*/
    ULONG ulPtpTimerQId;    /*PTP��ʱ������Id*/
    ULONG ulPtpPktQId;      /*PTP����*/
    ULONG ulPtpCtrolQId;    /*�ڲ����ƺ����ö���Id*/
}PTP_SYS_INFO_S;


/******************************************************************************
*Func Name   : PTP_InitPtpClock
*Description : ��ʼ��OC/BC PTPʱ��ʵ��
*Input       : 
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_Init
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_InitPtpClock();

/******************************************************************************
*Func Name   : PTP_InitTcPtpClock
*Description : ��ʼ��TCʱ��ʵ��
*Input       : 
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_Init
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_InitTcPtpClock();

/******************************************************************************
*Func Name   : PTP_InitPtpPort
*Description : ��ʼ��OC/BCʱ�Ӷ˿�
*Input       : 
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_InitPtpClock
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_InitPtpPort(PTP_PORT_S * pstPtpPort);

/******************************************************************************
*Func Name   : PTP_InitTcPtpClock
*Description : ��ʼ��TCʱ�Ӷ˿�
*Input       : 
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_InitTcPtpClock
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_InitTcPtpPort(PTP_TC_PORT_DS_S* pstTcPtpPort);

/******************************************************************************
*Func Name   : PTP_SetPtpPktRcvEventId
*Description : ����PTP������ձ��ĵ��¼�ID��ע���û�����ʱ��ҪPTP�ڲ��ĳ�ͻ��
*Input       : 
*Output      : PTP_SYS_INFO_S* pstPtpSysInfo: PTPϵͳ��Դ��Ϣ;
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_Init
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_SetPtpPktRcvEventId(ULONG ulEventId);

/******************************************************************************
*Func Name   : PTP_GetPtpSysInfo
*Description : ��ȡPTPģ���ϵͳ��Դ��Ϣ������Χ��Shellģ��ʵ�ֱ����շ�ʹ�á�
*Input       : 
*Output      : PTP_SYS_INFO_S* pstPtpSysInfo: PTPϵͳ��Դ��Ϣ;
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_Init
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_GetPtpSysInfo(PTP_SYS_INFO_S* pstPtpSysInfo);

/******************************************************************************
*Func Name   : PTP_StartAnnReq
*Description : ����PTP_TMSG_ANN_REQ�������ann����Э������
*Input       : ulPtpPortNumber:  �˿ں�
               *pstUnicastMaster: ��Է���Ľڵ�
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartAnnReq(ULONG ulPtpPortNumber, PTP_UNI_MASTER_NODE_S *pstUnicastMaster);


ULONG PTP_StartSendAnnReq(ULONG ulPtpPortNumber, PTP_UNI_MASTER_NODE_S *pstUnicastMaster);


ULONG PTP_PreSendAnnReq(PTP_UNI_MASTER_NODE_S *pstUnicastMaster);


/******************************************************************************
*Func Name   : PTP_StartSyncReq
*Description : ����PTP_TMSG_SYNC_REQ�������SYNC����Э������
*Input       : ulPtpPortNumber:  �˿ں�
               *pstUnicastMaster: ��Է���Ľڵ�
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartSyncReq(ULONG ulPtpPortNumber, PTP_UNI_MASTER_NODE_S *pstUnicastMaster);

/******************************************************************************
*Func Name   : PTP_StartMultiDelayRespReq
*Description : �ಥģʽ�·���delay resp����Э������
*Input       : ulPtpPortNumber:  �˿ں�
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartMultiDelayRespReq(ULONG ulPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr);


/*******************************************************************************
*    Func Name: PTP_StartMasterDelayCancel
* Date Created: 2012-09-19
*       Author: limin00188004
*  Description: 1588 PTP֧�ֶ�TLV�����Э����·����ɾ��
*        Input: USHORT usPortNumber:
*               PTP_UNI_SLAVE_NODE_S *pstUnicastSlave:
*               PTP_PPI_S *pstPtpPpi:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-19   limin00188004           Create
*
*******************************************************************************/
ULONG PTP_StartMasterDelayCancel(USHORT usPortNumber, 
    PTP_UNI_SLAVE_NODE_S *pstUnicastSlave, PTP_PPI_S *pstPtpPpi);

/*******************************************************************************
*    Func Name: PTP_StartMasterSyncCancel
* Date Created: 2012-09-19
*       Author: limin00188004
*  Description: 1588 PTP֧�ֶ�TLV�����Э����·����ɾ��
*        Input: USHORT usPortNumber:
*               PTP_UNI_SLAVE_NODE_S *pstUnicastSlave:
*               PTP_PPI_S *pstPtpPpi:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-19   limin00188004           Create
*
*******************************************************************************/
ULONG PTP_StartMasterSyncCancel(USHORT usPortNumber, 
    PTP_UNI_SLAVE_NODE_S *pstUnicastSlave, PTP_PPI_S *pstPtpPpi);

/******************************************************************************
*Func Name   : PTP_StartSlaveDelaySyncCancel
*Description : SLAVE �� ����PTP_TMSG_DELAY_RESP_SYNC_CANCEL�������delay resp/pdelay resp��sync�ĵ���ȡ��
*Input       : ulPtpPortNumber:  �˿ں�
               *pstUnicastMaster: ��Է���Ľڵ�
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartSlaveDelaySyncCancel(ULONG ulPtpPortNumber, PTP_UNI_MASTER_NODE_S *pstUnicastMaster);

/******************************************************************************
*Func Name   : PTP_StartMasterDelaySyncCancel
*Description : Master �� ����PTP_TMSG_DELAY_RESP_SYNC_CANCEL�������delay resp/pdelay resp��sync�ĵ���ȡ��
*Input       : ulPtpPortNumber:  �˿ں�
               *pstUnicastSlave: ��Է���Ľڵ�
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartMasterDelaySyncCancel(ULONG ulPtpPortNumber, PTP_UNI_SLAVE_NODE_S *pstUnicastSlave);

/******************************************************************************
*Func Name   : PTP_StartSlaveAnnCancel
*Description : SLAVE�෢�𵥲�ȡ�� ����PTP_TMSG_ANN_CANCE����
*Input       : ulPtpPortNumber:  �˿ں�
               *pstUnicastMaster: ��Է���Ľڵ�
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartSlaveAnnCancel(ULONG ulPtpPortNumber, PTP_UNI_MASTER_NODE_S *pstUnicastMaster);

/******************************************************************************
*Func Name   : PTP_StartMasterDelaySyncCancel
*Description :  MASTER �ⷢ�𵥲�ȡ��, ����PTP_TMSG_ANN_CANCE�������ann����Э��ȡ��
*Input       : ulPtpPortNumber:  �˿ں�
               *pstUnicastSlave: ��Է���Ľڵ�
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
ULONG PTP_StartMasterAnnCancel(ULONG ulPtpPortNumber, PTP_UNI_SLAVE_NODE_S *pstUnicastSlave);

/******************************************************************************
*Func Name   : PTP_ProcCtrolMsgAnnReq
*Description : ����Control ��Ϣ��ann req
*Input       : *pstPtpRcvMsg  �������Ϣ����
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
ULONG PTP_ProcCtrolMsgAnnReq(PTP_TMSG_S *pstPtpRcvMsg);

/******************************************************************************
*Func Name   : PTP_ProcCtrolMsgSyncReq
*Description : ����Control ��Ϣ��sync req
*Input       : *pstPtpRcvMsg  �������Ϣ����
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
ULONG PTP_ProcCtrolMsgSyncReq(PTP_TMSG_S *pstPtpRcvMsg);

/******************************************************************************
*Func Name   : PTP_ProcCtrolMsgAnnCancel
*Description : ����Control ��Ϣ��announce cancel
*Input       : *pstPtpRcvMsg  �������Ϣ����
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
ULONG PTP_ProcCtrolMsgAnnCancel(PTP_TMSG_S *pstPtpRcvMsg);

/******************************************************************************
*Func Name   : PTP_ProcCtrolMsgSyncCancel
*Description : ����Control ��Ϣ��sync cancel
*Input       : *pstPtpRcvMsg  �������Ϣ����
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
ULONG PTP_ProcCtrolMsgSyncCancel(PTP_TMSG_S *pstPtpRcvMsg);

/******************************************************************************
*Func Name   : PTP_ProcControlEvent
*Description : ����Control �¼�
*Input       : 
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
ULONG PTP_ProcControlEvent();


/******************************************************************************
*Func Name   : PTP_TaskMain
*Description : PTP������
*Input       : 
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_Init
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME		   DESCRIPTION
*
*******************************************************************************/
VOID PTP_TaskMain(UINTPTR ul1, UINTPTR ul2, UINTPTR ul3, UINTPTR ul4);

/******************************************************************************
*Func Name   : PTP_InitPtpDev
*Description : �����豸�ڴ�,����ʼ��
*Input       : ulPtpDevType:  �豸���Ͳ���
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
ULONG PTP_InitPtpDev(ULONG ulPtpDevType);

/******************************************************************************
*Func Name   : PTP_FreeRes
*Description : �ͷŶ����Լ��豸,������ص���Դ
*Input       : 
*Output      : 
*Return      : 
*Caution     :
*Calls       :
*Called by   : PTP_TaskMain
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-06-17            lishenchuan            create
*******************************************************************************/
VOID PTP_FreeRes();

/*******************************************************************************
*    Func Name: PTP_FreeAllSlaveTbl
* Date Created: 2011-11-14
*       Author: jijianhua00169178
*  Description: 
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: �ͷ����е�slaveTbl. �������������е�slave �ڵ��Ѿ��ͷ������µ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-14   jijianhua00169178       Create
*
*******************************************************************************/
VOID PTP_FreeAllSlaveTbl();

/******************************************************************************
*Func Name   : PTP_FreeAllSlaves
*Description : �ͷ�����SLAVE�ڵ���Դ
*Input       : 
*Output      : 
*Return      : 
*Caution     :
*Calls       :
*Called by   : PTP_UnInit
*-----------------------------------------------------------------------------
*  Modification History
*     DATE                 NAME             DESCRIPTION
* 2008-07-21            lishenchuan            create
*******************************************************************************/
VOID PTP_FreeAllSlaves();

ULONG PTP_StartDelayReq(ULONG ulPtpPortNumber, PTP_UNI_MASTER_NODE_S *pstUnicastMaster);



VOID PTP_FreeAllAddrVrfNodes(USHORT usPortNum);


VOID PTP_FreeAllVrfSockNodes();


#ifdef __cplusplus
}
#endif

#endif


