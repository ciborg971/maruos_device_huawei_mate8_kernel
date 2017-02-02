/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poec_api.h
*
*  Project Code: VISPV100R007
*   Module Name: POEC
*  Date Created: 2008-03-22
*        Author: luowentong105073
*   Description: poec api ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-22   luowentong105073        Create
*
*******************************************************************************/
#ifndef _POEC_API_H_
#define _POEC_API_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*ע��:
����޸Ĵ����룬��ͬ���޸�poec_sh_err.c �ļ��е�
char * Inf_PPPOE_Client_En[]������Ϣ*/
typedef enum tagPOEC_EXEC_INFO_INDEX
{
    PPPOE_CLIENT_OK = 0,                /* 0.�ɹ� */
    PPPOE_CLIENT_ERR,                   /* 1.ʧ�� */
    PPPOE_CLIENT_NO_SESSION_ON_ETH,     /* 2.��ǰ����̫��û�п�ɾ���ĻỰ */
    PPPOE_CLIENT_NO_SUCH_SESSION,       /* 3.û��ָ����session���� */
    PPPOE_CLIENT_BUNDLE_NUMBER_USED,    /* 4.ָ����Bundle���Ѿ���ʹ��, ��ѡ��������Bundle�� */
    PPPOE_CLIENT_DEBUG_NO_ETH_ERROR,    /* 5.û����̫�� */
    PPPOE_CLIENT_DEBUG_NOT_ETH_TYPE,    /* 6.������̫���� */
    PPPOE_CLIENT_NO_SESSSION_RESET,     /* 7.û�п������ĻỰ */
    PPPOE_CLIENT_CONFIG_RUNNING_SERVER, /* 8.�ӿ���������POES����������POEC */
    PPPOE_CLIENT_CONFIG_NOPVC_ATTACHED, /* 9.������̫��û�к�pvc������ */
    PPPOE_CLIENT_SESSION_NUMBER_MAX,    /* 10.�Ự������ */
    PPPOE_CLIENT_CONFIG_NO_NUMBER,      /* 11.û�п��õİ󶨺� */
    PPPOE_CLIENT_CREATE_SESSION_FAIL,   /* 12.����POEC�Ựʧ�� */
    PPPOE_CLIENT_NO_DIALER,             /* 13.�ýӿڲ���Dialer�� */
    PPPOE_CLIENT_NO_PPPINFO_EXIST,      /* 14. ��Ӧ��ppp���ƿ鲻����"*/
    PPPOE_CLIENT_BUNDLE_NUMBER_EXIST,   /* 15.Dialer���Ѿ�������BundleNumber */   
    PPPOE_CLIENT_BUNDLENUM_BEYOND,      /* 16.�����õ�BundleNumberֵԽ���� */

    PPPOE_CLIENT_PAPA_NULLPOINTER,      /* 17.�������Ϊ��ָ�� */
    PPPOE_CLIENT_BUNDLE_INTNUM_DISACCORD,/*18.��ϵͳ����û������PPPoE��Dialer�ӿ�ʱ�����е�Dialer�ӿڱ����󶨲�һ�� */
    PPPOE_CLIENT_INTF_INVALID,          /* 19.ָ���Ľӿ�������Ч */
    PPPOE_CLIENT_HA_IS_SMOOTHING,       /* 20.HA����ƽ��������ֶ��������� */

    PPPOE_CLIENT_IS_SERVER,             /* 21.�ӿ��Ѿ�ʹ����PPPoE Server */
    PPPOE_CLIENT_IS_TRUNKPORT,          /* 22.�ӿ���Trunk��Ա�˿� */ 

    PPPOE_CLENET_NOTINIT,               /* 23.POECģ��δ��ʼ�� */
    
    PPPOE_CLIENT_IS_VIRTUAL_PORT,       /* 24.��ά����ӿ� */
    
    PPPOE_CLIENT_ERR_DIALER_DOWN,       /* 25.PPPOE Dialer�ӿ�DOWN*/
    PPPOE_CLIENT_ERR_NO_BUNDNUM,        /* 26.��Ӧ�Ľӿ����������ڶ�Ӧ�İ󶨺� */
    PPPOE_CLIENT_ERR_NO_SESSION,        /* 27.��ȡSession���ƿ�*/
    PPPOE_CLIENT_ERR_NO_ETHIF,          /* 28.û�ж�Ӧ��PPPOE�Ự��Ϣ*/

    PPPOE_CLIENT_DEBUG_NO_DIALER_ERROR, /* 29.û��Dialer�� */
    PPPOE_CLIENT_DEBUG_NOT_DIALER_TYPE, /* 30 .����Dialer �ӿ����� */

    PPPOE_CLIENT_IS_L2ETHORVLAN_TYPE,   /* 31.����˿����ͻ�VLANIF�ӿ��ݲ�֧��POEC */
    PPPOE_CLIENT_COPY_SESSIONINFO_FAIL, /* 32.�����Ự��Ϣʧ�� */
    PPPOE_CLIENT_GR_STATE,              /* 33.PPPOEȫ�ֱ���ģʽ����ȷ������������ */
    PPPOE_CLIENT_SESSION_CFG_GR_STATE,  /* 34.���õ�PPPOE�Ự����ģʽ����ȷ������������ */
    PPPOE_CLIENT_SESSION_CFG_NEGO_STATE,/* 35.���õ�PPPOE�ỰЭ��״̬�����㣬���������� */
    PPPOE_CLIENT_SESSION_NEGO_STATE,    /* 36.�ӵײ�NP��ȡ����PPPOE�ỰЭ��״̬�����㣬���������� */
    PPPOE_CLIENT_PPI_HOOK_NULL,         /* 37.δע��PPI���� */
    PPPOE_CLIENT_ETHIF_PHY_NOTUP,       /* 38.��̫�ӿڵ�����״̬����UP�� */
    PPPOE_CLIENT_SAME_SESSION,          /* 39.�Ѿ�������ͬ��PPPOE�Ự */
    PPPOE_CLIENT_NP_MAC_INVALID,        /* 40.�ײ�ĻỰ��Ϣ�б����physical��ַ�Ƿ� */
    PPPOE_CLIENT_NP_MAC_DIFF,           /* 41.�ײ�ĻỰ��Ϣ�б���ı���MAC�غ��ϲ�Eth�ӿڵ�physical��ַ��һ�� */
    PPPOE_CLIENT_CREATE_VA_FAIL,        /* 42.����VA�ӿ�ʧ�� */
    PPPOE_CLIENT_CB_NULL,               /* 43.Client CBΪ�� */
    PPPOE_CLIENT_WRITE_QUE,             /* 44.д����ʧ�� */
    PPPOE_CLIENT_NO_ETH_CB,             /* 45.ָ����ETH����ETH���ƿ� */
    PPPOE_CLIENT_PARA_INVALID,          /* 46.�����Ч */
    PPPOE_CLIENT_MALLOC_FAIL,           /* 47.�����ڴ�ʧ�� */
    PPPOE_CLIENT_GET_NP_INFO_FAIL,      /* 48.��NP��ȡ�Ự��Ϣʧ�� */
    PPPOE_CLIENT_SUBIF,                 /* 49.�ӽӿڲ�֧�ָò��� */
    PPPOE_CLIENT_NUMBER_BEYOND,         /* 50.ָ���Ķ˿ںų������ֵ */
    
    PPPOE_CLIENT_EXEC_INFO_INDEX_MAX
    
}POEC_EXEC_INFO_INDEX_EN;
/*ע��:
����޸Ĵ����룬��ͬ���޸�poec_sh_err.c �ļ��е�
char * Inf_PPPOE_Client_En[]������Ϣ*/




/*ethernet mac ��ַ����*/
#define PPPOE_MAC_LEN           6

typedef struct tagPOECSTAT_S
{
    USHORT usSessionId;
    UCHAR  ucSessionPhase;
    UCHAR  ucPad;
    UCHAR  aucLocalMac[PPPOE_MAC_LEN];
    UCHAR  aucRemoteMac[PPPOE_MAC_LEN];
    ULONG  ulSendPkt;
    ULONG  ulRecvPkt;
    ULONG  ulSendFlow;
    ULONG  ulRecvFlow;
} POECSTAT_S;

/* ��ȡ��PPPOE session��Ϣ */
typedef struct tagPPPOE_C_SESSION_S
{
    ULONG   ulEthIfIndex;                 /* PPPOE�ӿڶ�Ӧ����̫�ӿ�����*/
    ULONG   ulSessionId;                  /* PPPOE Session��ID */
    UCHAR   szOurMacAddr[PPPOE_MAC_LEN];  /*Client physical��ַ */
    UCHAR   szHisMacAddr[PPPOE_MAC_LEN];  /*Server physical��ַ */
}TCPIP_PPPOE_C_SESSION_S;

/* PPPOE client�ڽ���/�˳�session�׶�ʱ���ù��Ӻ���֪ͨ��Ʒ
   ���˵��:
   ulDialerIfIndex: dialer�ӿ�����
    ulSessionPhase: 0 ����session�׶�  1 �˳�session�׶�
    pstSessionInfo: PPPOE�Ự��Ϣ, ָ��ָ����ڴ���VISP������ͷ�
   ����ֵ˵��:
     0  ���Ӻ�������ɹ�
   ���� ���Ӻ�������ʧ��, VISP��¼��־ */
typedef ULONG (*POEC_PHASE_NOTIFY)(ULONG ulDialerIfIndex, ULONG ulSessionPhase, TCPIP_PPPOE_C_SESSION_S *pstSessionInfo);

/*******************************************************************************
*    Func Name: TCPIP_ClrPoecIntfStat
*  Description: Clear the statistical information of the appointed session
*        Input: ULONG ulPoecIfIndex:dialer������
*       Output:
*       Return: �ɹ�����VOS_OK�����򷵻ش�����
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrPoecIntfStat(ULONG ulPoecIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_CreatePoecIntf
*  Description: ����PPPoE Client�ӿ�
*        Input: 
*       Output: pulPoecIfIndex: ���洴���Ľӿڵ�����
*       Return: SUCCESS     VOS_OK, FAILURE     error code
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_CreatePoecIntf(ULONG *pulPoecIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_CreatePoecIntfByNum
* Date Created: 2011-04-21
*       Author: zhaoyue00171897
*  Description: ���ݽӿںŴ���PPPoE Client�ӿ�
*        Input: ULONG ulPortNo: ָ����Dialer�˿ں�(�������ʾ��Ĭ�Ϸ�ʽ����)
*       Output: pulPoecIfIndex: ���洴���Ľӿڵ�����
*       Return: SUCCESS     VOS_OK, FAILURE     error code
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-04-21   zhaoyue00171897         Create
*
*******************************************************************************/
extern ULONG TCPIP_CreatePoecIntfByNum(ULONG *pulPoecIfIndex, ULONG ulPortNo);
/*******************************************************************************
*    Func Name: TCPIP_DebugPoecAll
*  Description: �����е��Կ���
*        Input: 
*       Output: 
*       Return: VOS_OK: ����ɹ�
*               POECNOTINIT:POEC���δ��ʼ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_DebugPoecAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_DelPoecIntf
*  Description: ɾ��PPPoE Client�ӿڣ��й������ݻ��Ᵽ��
*        Input: ulPoecIfIndex: Ҫɾ���Ľӿڵ�����
*       Output: None
*       Return: SUCCESS     VOS_OK,
*               FAILURE     error code
*      Caution: None
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_DelPoecIntf(ULONG ulPoecIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetPoecHADbg
*  Description: ��ȡPPPoE HA���Կ���״̬
*        Input:
*       Output: ULONG *pulRet: ���Կ���״̬
*       Return: VOS_OK(0)        �ɹ�
*               VOS_ERR(1)       ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoecHADbg(ULONG *pulRet);
/*******************************************************************************
*    Func Name: TCPIP_GetPoecIntfStat
*  Description: ���Poec��ӿ��ϵ�ͳ����Ϣ
*        Input : ulPoecIfIndex��PPPOE��ӿ�����
*       Output : *pstStat��PPPOE��ӿڵ�ͳ����Ϣ
*       Return : �ɹ�����VOS_OK
*              : ʧ�ܷ��ء������롱
*      Caution:  POECSTAT_S�ṹ�������£�
*              : typedef struct tagPOECSTAT_S
*              : {
*              :     USHORT usSessionId;
*              :     UCHAR ucSessionPhase;
*              :     UCHAR ucReserve;
*              :     UCHAR aucLocalMac[6];
*              :     UCHAR aucRemoteMac[6];
*              :     ULONG ulSendPkt;
*              :     ULONG ulRecvPkt;
*              :     ULONG ulSendFlow;
*              :     ULONG ulRecvFlow;
*              : } POECSTAT_S;
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoecIntfStat(ULONG ulPoecIfIndex, POECSTAT_S *pstStat);
/*******************************************************************************
*    Func Name: TCPIP_NoDebugPoecAll
*  Description: �ر����е��Կ���
*        Input: 
*       Output: 
*       Return: VOS_OK: ����ɹ�
*               POECNOTINIT:POEC���δ��ʼ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_NoDebugPoecAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ResetPoecSession
*  Description: �������е����������ĳһ��PPPoE Client�Ự
*        Input: ULONG ulPoecIfIndex:PPP�ӿ�����
*       Output: 
*       Return: �ɹ�����VOS_OK�����򷵻ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_ResetPoecSession(ULONG ulPoecIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_ResetPoecSessionAll
*  Description: �������е��������������PPPoE Client�Ự
*        Input: 
*       Output: 
*       Return: �ɹ�����VOS_OK�����򷵻ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_ResetPoecSessionAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_SetPoecHADbg
*  Description: ����PPPoEģ��HA�ĵ��Կ���״̬
*        Input: ULONG ulDbg: ����״̬   1����    0���ر�
*       Output:
*       Return: VOS_OK��0��        �ɹ�
*               VOS_ERR��1��       ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoecHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_ShowPOECInfoByIfName
*  Description: ͨ����װ���к���ʵ��PPPOE Client Session��Ϣ�Ĳ�ѯ����PPPOE Client Session���⡣
*        Input: CHAR *pszIfName:�ӿ���
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowPOECInfoByIfName(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowPoecSessionInfo
*  Description: ��ʾ���е�PPPoE client�Ự��Ϣ�ӿ�
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   luowentong105073        Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowPoecSessionInfo(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowPoecStatistic
*  Description: ��ӡPOECģ��ͳ����Ϣ
*        Input: CHAR *pName:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   luowentong105073        Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowPoecStatistic(CHAR *pName);
/*******************************************************************************
*    Func Name: TCPIP_StartPoecSession
*  Description: ����̫��������PPPOE�Ự
*        Input: ULONG ulEthIfIndex: ��̫���ӿ�����
*               ULONG ulPoecIfIndex: PPPoE Client�ӿ�����
*       Output: None
*       Return: SUCCESS     VOS_OK, FAILURE     error code
*      Caution: None
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_StartPoecSession(ULONG ulEthIfIndex, ULONG ulPoecIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_StopPoecSession
*  Description: ����̫���Ϲر�PPPOE�Ự���й������ݻ��Ᵽ��
*        Input: ULONG ulEthIfIndex: ��̫���ӿ�����
*               ULONG ulPoecIfIndex: PPPoE Client�ӿ�����
*       Output: None
*       Return: SUCCESS     VOS_OK, FAILURE     error code
*      Caution: None
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_StopPoecSession(ULONG ulEthIfIndex, ULONG ulPoecIfIndex);

extern ULONG TCPIP_GetPoecSessionInfo (ULONG ulPoecIfIndex, TCPIP_PPPOE_C_SESSION_S *pstSessionInfo );

/*******************************************************************************
*    Func Name: TCPIP_RegFuncPoecPhaseNotify
*  Description: ע�ṳ�Ӻ���, PPPOE client�ڽ���/�˳�session�׶�ʱ���ù��Ӻ���֪ͨ��Ʒ
*        Input: POEC_PHASE_NOTIFY pfHook: ���Ӻ���ָ��
*       Output: 
*       Return: VOS_OK   �ɹ�
*               VOS_ERR  ���Ӻ���ָ��Ϊ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-24  wujie(61195)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPoecPhaseNotify(POEC_PHASE_NOTIFY pfHook);


extern ULONG TCPIP_SetPoecDebugFlag(ULONG ulDialerIfIndex, ULONG ulEthIfIndex, ULONG ulFlag);


extern ULONG TCPIP_GetPoecDebugFlag(ULONG ulDialerIfIndex, ULONG ulEthIfIndex, ULONG *pulFlag);


extern ULONG TCPIP_GR_POECRestore(VOID);


extern ULONG TCPIP_GR_POECSmooth(VOID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _POEC_API_H_ */

