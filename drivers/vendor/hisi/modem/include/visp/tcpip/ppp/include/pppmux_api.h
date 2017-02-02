/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pppmux_api.h
*
*  Project Code: VISPV100R006C02
*   Module Name: PPPMUX  
*  Date Created: 2008-03-17
*        Author: chenfutian69112
*   Description: PPPMUXģ���ṩ�Ķ������ݽṹ�����API����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/

#ifndef _PPPMUX_API_H_
#define _PPPMUX_API_H_


#ifdef  __cplusplus
extern "C"{
#endif

/**********************************************************************
*                        �����ṩ�����ݽṹ
***********************************************************************/

/* PPPMUX���ò������ݽṹ */
typedef struct tagPPPMUX_CONFIG_STRUCT
{
    ULONG ulMuxEnable;    /*�Ƿ�ʹ��PPPMux*/
    ULONG ulDefaultPID;   /*Default PID*/
    ULONG ulSubFrameLen;  /*�����֡����*/
    ULONG ulFrameLen;     /*��󸴺�֡����*/
    ULONG ulSubFrameCount;/*�����֡����*/
    ULONG ulMuxDelay;     /*��󸴺�ʱ��*/
}PPPMUXCONFIG_S;

/* PPPMUXͳ�������ݽṹ */
typedef struct tagPPPMUX_STAT_STRUCT
{
    ULONG ulSendPackets;         /*���ͱ�������*/
    ULONG ulSendSubFrames;       /*������֡����*/
    ULONG ulSendBytes;           /*�����ֽ�����*/
    ULONG ulSendBytes_PayLoad;   /*�����Ͼ����ֽ���*/
    ULONG ulSendError;           /*���ĸ��ϴ�����*/
    ULONG ulRecvPackets;         /*���ձ�������*/
    ULONG ulRecvSubFrames;       /*������֡����*/
    ULONG ulRecvBytes;           /*�����ֽ�����*/
    ULONG ulRecvBytes_PayLoad;   /*�⸴�Ͼ����ֽ���*/
    ULONG ulRecvError;           /*���Ľ⸴�ϴ�����*/
    ULONG ulSendSingPkt;         /*���͵ĵ�����,�������PPPͷ*/
}PPPMUXSTATS_S;

/* PPPMUXCPЭ�̽�����ݽṹ */
typedef struct tagPPPMUXUP_NEGORESULT_STRUCT
{
    ULONG ulNegoDefaultPID;      /*�Ƿ�Э��PPPMux*/
    ULONG ulDefaultPID;          /*Default PID*/
}PPP_MUXCP_NEGORESULT_S;

/*����ȫ�ֱ��������û���ʵ���Զ����PPPMUX��������Ͷ�ʱ������ʱ���������������Ϣ*/
/*�ϸ�����,VISP��Ӧ�����û�����ȫ�ֱ���, �����ٿ��������Խ������*/
extern ULONG g_ulPPPMUXTaskId;      /* PPPMUX��������ID */
extern ULONG g_ulPPPMUXTimerId;     /* PPPMUX��ʱ��ID */
extern ULONG g_ulPPPMUXQueId;       /* PPPMUX��ʱ����Ϣ����ID */


/**********************************************************************
*                        �����ṩ�����Ͷ�����û�API����
***********************************************************************/

typedef ULONG ( * QOSPacketClass_HOOK_FUNC)(ULONG ulIfIndex,MBUF_S* pstMBuf,UCHAR * pucClass);
typedef ULONG ( * CreatePPPMUXTimer_HOOK_FUNC)(VOID ( *pfTimerFunc )( VOID* ), VOID *pArg);
typedef ULONG ( * DeletePPPMUXTimer_HOOK_FUNC)(VOID);
typedef ULONG ( * PPPMUXTimerOut_HOOK_FUNC)(VOID *pArg );
typedef ULONG ( * PPPMUXSchedule_HOOK_FUNC)(ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);

/*******************************************************************************
*    Func Name: TCPIP_ShowMuxConfig
*  Description: ��ʾָ���ӿڵ�PPPMUX���ܵ����ò���
*        Input: CHAR *pszIfName:�ӿ�����
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowMuxConfig(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowMUXNegoResultByIfName
*  Description: ��ʾָ���ӿڵ�PPPMUXCPЭ�̽��
*        Input: CHAR *pszIfName:�ӿ�����
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowMUXNegoResultByIfName (CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowMuxStat
*  Description: ��ʾָ���ӿڵ�PPPMUXͳ������
*        Input: CHAR *pszIfName:�ӿ�ָ��
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowMuxStat(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_ClrPppMuxStat
*  Description: ͳ����Ϣ����
*        Input: ULONG ulIfIndex:�ӿ�����
*       Output: 
*       Return: VOS_OK                     �ɹ�
*               PPP_IFNETCB_NOEXIST        �ӿڿ��ƿ鲻����
*               PPP_NOENCAP_ERROR          �ӿڲ���PPP��ӿ�
*               PPP_PPPCB_NOEXIST          PPP���ƿ鲻����
*               PPP_WRONGPARA_ERROR        �����Ƿ�
*               PPP_MUX_DISABLE            PPPMUX����δʹ��
*               PPP_MUX_CONTEXT_NOEXIST    PPPMUX�����Ľṹ������
*               PPP_MUXCPCB_NOEXIST        PPPMUX���ƿ鲻����
*               VOS_ERR                    �ӿ������Ƿ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrPppMuxStat(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_MuxcpPid
*  Description: ���ñ���Ĭ��Э���
*        Input: ULONG ulIfIndex:�ӿ�����
*               USHORT usDefaultPid:Ĭ��Э���
*               ULONG ulReset:���ñ�־��1 undo��0 ��undo�������Ƿ�
*       Output: 
*       Return: VOS_OK                              �ɹ�
*               PPP_IFNETCB_NOEXIST                 �ӿڿ��ƿ鲻����
*               PPP_NOENCAP_ERROR                   �ӿڲ���PPP��ӿ�
*               PPP_PPPCB_NOEXIST                   PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST              ���ÿ��ƿ鲻����
*               PPP_WRONGPARA_ERROR                 �����Ƿ�
*               PPP_HA_IS_SMOOTHING                 HA����ƽ��������ֶ���������
*               VOS_ERR                             �ӿ������Ƿ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_MuxcpPid (ULONG ulIfIndex, USHORT usDefaultPid, ULONG ulReset );
/*******************************************************************************
*    Func Name: TCPIP_SetMaxMuxframeLen
*  Description: ����PPP����֡��󳤶�
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulLength:��󸴺�֡���ȣ�ȡֵ��ΧΪ3��1500
*       Output: 
*       Return: VOS_OK                       �ɹ�
*               PPP_HA_IS_SMOOTHING          HA����ƽ��������ֶ���������
*               PPP_WRONGPARA_ERROR          �����Ƿ���ָ������ֵ�����Ϸ���Χ��
*               PPP_IFNETCB_NOEXIST          ָ���ӿڲ�����
*               PPP_NOENCAP_ERROR            ָ���ӿڷ�PPP��·����
*               PPP_PPPCB_NOEXIST            ָ���ӿڵ�PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST       ָ���ӿڵ�PPP���ÿ��ƿ鲻����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMaxMuxframeLen(ULONG ulIfIndex, ULONG ulLength);
/*******************************************************************************
*    Func Name: TCPIP_PppMux
*  Description: ���ýӿ�ʹ��/ȥʹ��PPPMUX����
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulSetYes:ʹ��/ȥʹ�ܱ��(0 ȥʹ�ܣ�1 ʹ��)
*       Output: 
*       Return: VOS_OK                    �ɹ�
*               PPP_IFNETCB_NOEXIST       �ӿڿ��ƿ鲻����
*               PPP_NOENCAP_ERROR         �ӿڲ���PPP��ӿ�
*               PPP_PPPCB_NOEXIST         PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST    ���ÿ��ƿ鲻����
*               PPP_WRONGPARA_ERROR       �����Ƿ�
*               PPP_HA_IS_SMOOTHING       HA����ƽ��������ֶ���������
*               VOS_ERR                   �ӿ������Ƿ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_PppMux ( ULONG ulIfIndex, ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_GetMuxConfig
*  Description: ��ѯPPPMUX������ص����ò���
*        Input: ULONG ulIfIndex:�ӿ�����
*               PPPMUXCONFIG_S* pstMuxConfig:PPPMUX���ò�����ѯ���
*       Output: PPPMUXCONFIG_S* pstMuxConfig:PPPMUX���ò�����ѯ���
*       Return: VOS_OK                    �ɹ�
*               PPP_IFNETCB_NOEXIST       �ӿڿ��ƿ鲻����
*               PPP_NOENCAP_ERROR         �ӿڲ���PPP��ӿ�
*               PPP_PPPCB_NOEXIST         PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST    ���ÿ��ƿ鲻����
*               PPP_WRONGPARA_ERROR       �����Ƿ�
*               PPP_HA_IS_SMOOTHING       HA����ƽ��������ֶ���������
*               VOS_ERR                   �ӿ������Ƿ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetMuxConfig(ULONG ulIfIndex, PPPMUXCONFIG_S* pstMuxConfig);
/*******************************************************************************
*    Func Name: TCPIP_SetMuxOverTime
*  Description: ���ñ��ĸ��ϵ����ʱ��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulTime:���ĸ���ʱ��(1��1000ms)
*       Output: 
*       Return: VOS_OK                          �ɹ�
*               PPP_IFNETCB_NOEXIST             �ӿڿ��ƿ鲻����
*               PPP_NOENCAP_ERROR               �ӿڲ���PPP��ӿ�
*               PPP_PPPCB_NOEXIST               PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST          ���ÿ��ƿ鲻����
*               PPP_WRONGPARA_ERROR             �����Ƿ�
*               PPP_HA_IS_SMOOTHING             HA����ƽ��������ֶ���������
*               VOS_ERR                         �ӿ������Ƿ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMuxOverTime(ULONG ulIfIndex, ULONG ulTime);
/*******************************************************************************
*    Func Name: TCPIP_GetPppMuxStat
*  Description: ��ȡ�ӿڵ�PPPMUXͳ����Ϣ
*        Input: ULONG ulIfIndex:�ӿ�����
*               PPPMUXSTATS_S*  pstMuxStat:ͳ����Ϣ��ѯ���
*       Output: PPPMUXSTATS_S*  pstMuxStat:ͳ����Ϣ��ѯ���
*       Return: VOS_OK                   �ɹ�
*               PPP_IFNETCB_NOEXIST      �ӿڿ��ƿ鲻����
*               PPP_NOENCAP_ERROR        �ӿڲ���PPP��ӿ�
*               PPP_PPPCB_NOEXIST        PPP���ƿ鲻����
*               PPP_WRONGPARA_ERROR      �����Ƿ�
*               PPP_MUX_DISABLE          PPPMUX����δʹ��
*               PPP_MUXCPCB_NOEXIST      PPPMUX���ƿ鲻����
*               PPP_MUX_CONTEXT_NOEXIST  PPPMUX�����Ľṹ������
*               VOS_ERR                  �ӿ������Ƿ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPppMuxStat(ULONG ulIfIndex, PPPMUXSTATS_S*  pstMuxStat);
/*******************************************************************************
*    Func Name: TCPIP_GetMuxNegoResult
*  Description: ��ѯPPPMUXCPЭ��Э�̽��
*        Input: ULONG ulIfIndex:�ӿ�����
*               PPP_MUXCP_NEGORESULT_S *pstOur:����Э�̽��
*               PPP_MUXCP_NEGORESULT_S *pstHis:�Զ�Э�̽��
*       Output: PPP_MUXCP_NEGORESULT_S *pstOur:����Э�̽��
*               PPP_MUXCP_NEGORESULT_S *pstHis:�Զ�Э�̽��
*       Return: VOS_OK                    �ɹ�
*               PPP_IFNETCB_NOEXIST       �ӿڲ�����
*               PPP_NOENCAP_ERROR         ָ���ӿڷ�PPP���ͽӿ�
*               PPP_PPPCB_NOEXIST         ָ���ӿڵ�PPP���ƿ鲻����
*               PPP_WRONGPARA_ERROR       �����Ƿ�
*               PPP_MUXCPCB_NOEXIST       PPPMUX���ƿ鲻����
*               PPP_FSMSTATE_ERR          MuxЭ��״̬����û��ͨ��Э�̣�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetMuxNegoResult(ULONG ulIfIndex, PPP_MUXCP_NEGORESULT_S *pstOur, PPP_MUXCP_NEGORESULT_S *pstHis);
/*******************************************************************************
*    Func Name: TCPIP_SetMuxSubFrameCount
*  Description: ����һ�����ϱ���������������֡��Ŀ
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulSubFrameCount:�����֡��(1~15)
*       Output: 
*       Return: VOS_OK                  �ɹ�
*               PPP_IFNETCB_NOEXIST     �ӿڿ��ƿ鲻����
*               PPP_NOENCAP_ERROR       �ӿڲ���PPP��ӿ�
*               PPP_PPPCB_NOEXIST       PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST  ���ÿ��ƿ鲻����
*               PPP_WRONGPARA_ERROR     �����Ƿ�
*               PPP_HA_IS_SMOOTHING     HA����ƽ��������ֶ���������
*               VOS_ERR                 �ӿ������Ƿ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMuxSubFrameCount(ULONG ulIfIndex, ULONG ulSubFrameCount);
/*******************************************************************************
*    Func Name: TCPIP_SetMuxMaxSubframeLen
*  Description: ������֡��󳤶�
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulLength:��֡����(1~512)
*       Output: 
*       Return: VOS_OK                    �ɹ�
*               PPP_IFNETCB_NOEXIST       �ӿڿ��ƿ鲻����
*               PPP_NOENCAP_ERROR         �ӿڲ���PPP��ӿڡ�
*               PPP_PPPCB_NOEXIST         PPP���ƿ鲻����
*               PPP_CONFIGINFO_NOEXIST    ���ÿ��ƿ鲻����
*               PPP_WRONGPARA_ERROR       �����Ƿ�
*               PPP_HA_IS_SMOOTHING       HA����ƽ��������ֶ���������
*               VOS_ERR                   �ӿ������Ƿ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMuxMaxSubframeLen(ULONG ulIfIndex, ULONG ulLength);

ULONG TCPIP_SetMuxMaxSubframeLenEx(ULONG ulIfIndex, ULONG ulLength);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncQOSPacketClassHook
*  Description: ���ݱ��Ļ�ȡMC Class��ע��ӿ�,�˹������û�����ע���,��PPPMUXģ�����
*        Input: QOSPacketClass_HOOK_FUNC pfHookFunc:��������ָ��
*       Output: ��
*       Return: �ɹ�VOS_OK,ʧ��VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncQOSPacketClassHook(QOSPacketClass_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncCreatePPPMUXTimerHook
*  Description: ����PPPMUX���϶�ʱ������
*        Input: CreatePPPMUXTimer_HOOK_FUNC pfHookFunc:��������
*       Output: 
*       Return: VOS_OK                      �ɹ�
*      Caution: VRP_EVENT_TIMERREQ ��Ʒ��VISPд���¼���g_ulPppmuxTimerID ��ʱ��ID;g_ulTaskID ����ID.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncCreatePPPMUXTimerHook(CreatePPPMUXTimer_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDeletePPPMUXTimer
*  Description: ɾ��PPPMUX���϶�ʱ������
*        Input: DeletePPPMUXTimer_HOOK_FUNC pfHookFunc:��������
*       Output: 
*       Return: VOS_OK                         �ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDeletePPPMUXTimer(DeletePPPMUXTimer_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncPPPMUXTimerOutHook
*  Description: PPPMUX��ʱ����ʱ����
*        Input: PPPMUXTimerOut_HOOK_FUNC pfHookFunc:��������
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPPPMUXTimerOutHook(PPPMUXTimerOut_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncPPPMUXScheduleHook
*  Description: PPPMUX���������������
*        Input: PPPMUXSchedule_HOOK_FUNC pfHookFunc:��������
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPPPMUXScheduleHook(PPPMUXSchedule_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_ScanAndSendMuxPacket
*  Description: ɨ������δ���͵�PPP���ϱ��ģ�������ĳ�����󸴺�ʱ�ӣ����ͱ���
*        Input: ��
*       Output: ��
*       Return: VOID
*      Caution: ��PPPMUX��ʱ����ʱ����������
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-07-01   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_ScanAndSendMuxPacket(VOID);

#ifdef __cplusplus
}
#endif


#endif

