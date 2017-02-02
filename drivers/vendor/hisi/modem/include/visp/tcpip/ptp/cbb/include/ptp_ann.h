/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                                 ptp_ann.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP
*  Date Created: 2008-06-02
*        Author: ̷ǿ
*   Description: Announce��Ϣ���պͷ��ʹ���h�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME               DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-06-02    ̷ǿ        Create
*
*******************************************************************************/
#ifndef _PTP_ANN_H_
#define _PTP_ANN_H_

#include "tcpip/public/tcpip_config.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "ptp/cbb/include/ptp_base_inc.h"
#include "ptp/cbb/include/ptp_inc.h"


/******************************************************************************
*Func Name   : PTP_ANN_RcvMsg
*Description : announce��Ϣ���մ���
*Input       : UCHAR              *pucBuffer        ��������
*              PTP_SRCIPUDPINFO_S *pstSrcAddrInfo   ����Դ��ַ��Ϣ
*Output      : .
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
ULONG PTP_ANN_RcvMsg (UCHAR *pucBuffer, ULONG ulPktLen,PTP_ADDRINFO_S *pstAddrInfo);

/******************************************************************************
*Func Name   : PTP_ANN_SndMsg
*Description : announce��Ϣ���մ���
*Input       : PTP_PORT_S     *pstPtpPort     ʱ�Ӷ˿ڿ��ƿ�
*              PTP_ADDRINFO_S *pstAddrInfo    ����/���ͱ��ĵĵ�ַ�Լ�UDP��Ϣ
*              PTP_PORT_ID_S  *pstDstPortId   Ŀ�Ķ˿�
*Output      : .
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
ULONG PTP_ANN_SndMsg( PTP_PORT_S *pstPtpPort, PTP_UNI_SLAVE_NODE_S *pstUnicastSlave);

/******************************************************************************
*Func Name   : PTP_PKT_PrintHeader
*Description : �¼���Ϣ���Ĵ�ӡ�ӿ�
*Input       : PTP_MSGHEADER_S *pstMsgHeader ��Ϣͷ
*              ULONG           ulFlag        ���:0-���ͱ���;��0-���ձ���
*Output      : .
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����                             
*Caution     : 
*Calls       : 
*Called by   : 
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-16            wangchengyang  Create
*******************************************************************************/
VOID PTP_ANN_PrintAnn(PTP_ANNOUNCE_MSG_S *pstAnnMsg, PTP_ADDRINFO_S *pstAddrInfo, ULONG ulFlag);

/******************************************************************************
*Func Name   : PTP_ANN_ResetAnnRecvTimer
*Description : ˢ��ANN���ն�ʱ��
*Input       : PTP_PORT_S *pstPtpPort:ʱ�Ӷ˿�
*              PTP_ADDRINFO_S *pstAddrInfo:��ַ��Ϣ
*Output      : .
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����                             
*Caution     : 
*Calls       : 
*Called by   : 
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-18           yaochengliang   Create
*******************************************************************************/
ULONG PTP_ANN_ResetAnnRecvTimer(PTP_PORT_S *pstPtpPort,PTP_ADDRINFO_S *pstAddrInfo);
/*******************************************************************************
*    Func Name: PTP_WarningOut
* Date Created: 2009-08-13
*       Author: xujun57575
*  Description: 
*        Input: ULONG ulWarnID:
*               VOID *pWarnParam:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-13   xujun57575              Create
*
*******************************************************************************/
VOID PTP_WarningOut(ULONG ulWarnID, VOID *pWarnParam);

extern VOID PTP_ANN_ClassBuild(PTP_ANNOUNCE_MSG_S *pstAnnMsg, PTP_UNI_SLAVE_NODE_S *pstUnicastSlave,UCHAR ucLocalClass);

#ifdef __cplusplus
}
#endif

#endif 
