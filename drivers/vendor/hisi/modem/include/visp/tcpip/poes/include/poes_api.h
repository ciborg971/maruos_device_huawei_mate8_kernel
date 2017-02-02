/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poes_api.h
*
*  Project Code: VISPV100R007
*   Module Name: POES
*  Date Created: 2008-03-17
*        Author: luowentong105073
*   Description: �û�API
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-17   luowentong105073        Create
*
*******************************************************************************/
#ifndef __POES_API_H__
#define __POES_API_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define POES_MAC_LEN 6                  /* physical��ַ���� */
#define POES_ACNAME_MAX_LEN 58          /* ACName�ַ������С,����'\0' */
#define POES_SERVICENAME_MAX_LEN 128    /* Service Name�ַ������С,����'\0' */

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN 47       /* ���ӿ������� */
#endif

/* POESģ��Ĵ����� */
enum enPoesErrorCode
{
    POES_OK = 0,
    POES_ERR,
    POES_PARAM_ERR,                 /* 2������������Ϸ� */
    POES_IF_NULL,                   /* 3�����ݽӿ�������ȡ�ӿ�ָ��Ϊ�� */
    POES_IF_TYPE_ERR,               /* 4���ӿ����ʹ��� */
    POES_ISNOT_SERVER,              /* 5���ӿ�û��ʹ��PPPoE Server */
    POES_IS_SERVER,                 /* 6����̫�ӿ���ʹ��PPPoE Server */
    POES_IS_CLIENT,                 /* 7����̫�ӿ���ʹ��PPPoE Client */
    POES_ETH_IS_TRUNKPORT,          /* 8����̫�ӿ���Trunk�ӿڵĳ�Ա�˿� */
    POES_VT_ISNOT_USABLED,          /* 9��VT�ӿڲ����� */
    POES_MEM_MALLOC_FAILED,         /* 10�������ڴ�ʧ�� */    
    POES_HAVE_NO_SESSION,           /* 11����̫�ӿ�û��Session */
    POES_SESSIONID_ERR,             /* 12������Session ID���� */
    POES_GET_SESSION_INFO_FAILED,   /* 13�����Session��Ϣʧ�ܣ�����session�����Ч��*/
    POES_SERVICENAME_TOOLONG,       /* 14�������ַ���̫�� */
    POES_GET_END,                   /* 15����ȡwaitlist�ڵ���� */
    POES_HA_IS_SMOOTHING,           /* 16��HA�����ֶ�������ƽ������*/
    POES_HAVE_NO_HISMAC,            /* 17��û�и�physical��ַ */
    POES_SERVICE_NAME_ERR,          /* 18��PADR��service name ����*/
    POES_NOTINIT,                   /* 19��POESģ��δ��ʼ�� */    
    POES_IS_VIRTUAL_PORT,           /* 20, ��ά����ӿ� */   
    POES_CTRL_BLOCK_NULL,           /* 21, POES���ƿ�ΪNULL */
    POES_HIS_MAC_NULL,              /* 22, his macΪ�� */
    POES_MAX_ERR                    /* */
};



/* ������Ϣ�������ݽṹ */
typedef struct tagPoesDebugInfo
{
    UCHAR ucDbgPoesData;    /* PPPOEģ�����ݱ��ĵ��Կ��� */
    UCHAR ucDbgPoesNego;    /* PPPOEģ��Э�̱��ĵ��Կ��� */
    UCHAR ucDbgPoesEvents;  /* PPPOEģ���¼����Կ��� */
    UCHAR ucDbgPoesErrors;  /* PPPOEģ��Э�鼰���������Կ��� */
} POES_DEBUG_INFO_S;

/*POES�ӿ�������Ϣ*/
typedef struct tagPoesIfCfgInfo
{
    ULONG ulEthIfIndex;     /* ETH�ӿ�����ֵ */
    ULONG ulVTIfIndex;      /* �󶨵�VT�ӿ�����ֵ */
    UCHAR szServiceName[POES_SERVICENAME_MAX_LEN];  /* Service name */
} POES_IF_CFG_INFO_S;

/*Session�Ļ�����Ϣ*/
typedef struct tagPoesSessionInfo
{
    USHORT usSessionId;         /* session id */
    USHORT usSessionState;      /* session ״̬ */
    ULONG  ulVTIfIndex;         /* VT�ӿ����� */
    UCHAR  szVAIfName[IF_MAX_INTERFACE_NAME_LEN + 1];  /* VA��ͨ������ */
    UCHAR  aucLocalMac[POES_MAC_LEN];   /* ����physical��ַ */
    UCHAR  aucRemoteMac[POES_MAC_LEN];  /* Զ��physical��ַ */
} POES_SESSION_INFO_S;

/*Session�ı���ͳ����Ϣ*/
typedef struct tagPoesSesPktStatInfo
{
    USHORT usSessionId;     /* session id */
    UCHAR  aucLocalMac[POES_MAC_LEN];   /* ����physical��ַ */
    UCHAR  aucRemoteMac[POES_MAC_LEN];  /* Զ��physical��ַ */
    UCHAR  ucPadding[2];    /* ����ֶ� */
    ULONG  ulInPackets;     /* �յ��İ��� */
    ULONG  ulInOctets;      /* �յ����ֽ��� */
    ULONG  ulInDiscards;    /* ����ʱ�����İ��� */
    ULONG  ulOutPackets;    /* ���͵İ��� */
    ULONG  ulOutOctets;     /* ���͵��ֽ��� */
    ULONG  ulOutDiscards;   /* ����ʱ�����İ��� */
} POES_SES_PKT_STAT_INFO_S;

/*��̫�ӿڵ�Sessionͳ����Ϣ*/
typedef struct tagPoesStatInfo
{
    ULONG ulOurMacCurtSessions;     /* ��̫�ӿڵ�ǰSession��Ŀ */
    ULONG ulCurrentEstablishRate;   /* ��̫�ӿڵ�ǰSeesion�����ٶ� */
    ULONG ulBurstEstablishRate;     /* ��̫�ӿ����Session�����ٶ� */
    ULONG ulFailedCount;            /* ����Sessionʧ�ܴ��� */
} POES_SESSION_STAT_INFO_S;

/*POESϵͳ������Ϣ*/
typedef struct tagPoesSystemCfgInfo
{
    CHAR   szAcName[POES_ACNAME_MAX_LEN];/* AC NAME */
    USHORT usSessionNum;       /* ��ǰȫ��session�� */
    USHORT usMaxSesLimit;       /* ȫ��Session������ */
    USHORT usOurMacMaxSesLimit; /* ����MAC Session������ */
    USHORT usHisMacMaxSesLimit;    /* �Զ�MAC Session������ */
    UCHAR  ucPadding[2];    /* ����ֶ� */
} POES_SYS_CFG_INFO_S;

/* ͳ����Ϣ���� */
enum enumPoesStatType
{
    STAT_ALL = 0,
    STAT_PKT,
    STAT_SES
};


/* ������Ϣ���� */
enum enumPoesDbgType
{
    DBG_ALL = 0,
    DBG_DATAPKT,
    DBG_NEGOPKT,
    DBG_EVENTS,
    DBG_ERRORS
};



typedef VOID (*GetACName_HOOK_FUNC)(UCHAR* pszAcName);

/*******************************************************************************
*    Func Name: TCPIP_ClearPoesStatInfo
*  Description: �������ͳ�Ƽ�������̫�ӿ��µ�Sessionͳ�Ƽ���
*        Input: ULONG ulEthIfIndex:��̫�ӿڵ�����ֵ,���Ϊ0������нӿڵ�ͳ����Ϣ
*               ULONG ulType:���������
*               0������ͳ����Ϣ��1������ͳ�Ƽ�����2��sessionͳ����Ϣ,������Ч
*       Output: 
*       Return: VOS_OK: ����ɹ�
*               POES_PARAM_ERR: ����������Ϸ�
*               POES_IF_NULL: ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               POES_ISNOT_SERVER: ��̫�ӿ�δʹ��PPPoE Server
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_ClearPoesStatInfo(ULONG ulEthIfIndex, ULONG ulType);
/*******************************************************************************
*    Func Name: TCPIP_DisablePoes
*  Description: ����̫�ӿ�ȥʹ��PPPoE Server����
*        Input: ULONG ulEthIfIndex:��̫�ӿ�����
*       Output: 
*       Return: VOS_OK: ����ɹ�
*               POES_IF_NULL: ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               POES_ISNOT_SERVER: �ӿ�û��ʹ��PPPoE Server
*               POES_HA_IS_SMOOTHING: HA�����ֶ�������ƽ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_DisablePoes (ULONG ulEthIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_EnablePoes
*  Description: ����̫�ӿ�ʹ��PPPoE Server����
*        Input: ULONG ulEthIfIndex:��̫�ӿ�����
*               ULONG ulVTIfIndex:VT�ӿ�����
*       Output: 
*       Return: VOS_OK: ����ɹ�
*               POES_IF_NULL: ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               POES_IF_TYPE_ERR: �ӿ����ʹ���
*               POES_IS_SERVER: ��̫�ӿ���ʹ��PPPoE Server
*               POES_IS_CLIENT: ��̫�ӿ���ʹ��PPPoE Client
*               POES_ETH_IS_TRUNKPORT: ��̫�ӿ���Trunk�ӿڵĳ�Ա�˿�
*               POES_VT_ISNOT_USABLED: VT�ӿڲ�����
*               POES_MEM_MALLOC_FAILED: �����ڴ�ʧ��
*               POES_HA_IS_SMOOTHING: HA�����ֶ�������ƽ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_EnablePoes(ULONG ulEthIfIndex, ULONG ulVTIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesDbgSwitch
*  Description: ��ȡ������Ϣ����
*        Input: ULONG ulEthIfIndex:��̫�ӿ�����(Ϊ0��ʾ���ȫ�ֵ�����Ϣ����)
*       Output: POES_DEBUG_INFO_S *pstDbgInfo:������Ϣ���� ����ȡֵ 0���أ�1����
*       Return: VOS_OK: ����ɹ�
*               POES_PARAM_ERR: ����������Ϸ�
*               POES_IF_NULL: ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               POES_ISNOT_SERVER: ��̫�ӿ�δʹ��PPPoE Server
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesDbgSwitch(ULONG ulEthIfIndex, POES_DEBUG_INFO_S *pstDbgInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesHADbg
*  Description: Get poes ha debug switch
*        Input: None
*       Output: ULONG *pulRet: Poes ha debug switch
*       Return: VOS_OK(0): Success, VOS_ERR(1): Fail
*      Caution: None
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesHADbg(ULONG *pulRet);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesHisMacSessions
*  Description: ��ȡ�Զ�mac��session��
*        Input: UCHAR *pucHisMac: �Զ�physical��ַ
*       Output: USHORT *pusSesNum: ����Զ�mac��session��,ʧ�������0xffff
*       Return: POES_PARAM_ERR: ��������
*               POES_HAVE_NO_HISMAC: û�и�physical��ַ
*               VOS_OK: ��ȡ�ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesHisMacSessions(UCHAR *pucHisMac, USHORT *pusSesNum);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesIfCfgInfo
*  Description: ��ȡ��̫�ӿڵ�PPPoE Server������Ϣ����������̫�ӿ��������󶨵�VT�ӿ���
*               ����Service Name�����127���ַ�����
*        Input: ULONG ulEthIfIndex:��̫�ڵ�����
*       Output: POES_IF_CFG_INFO_S *pstIfCfgInfo:��ȡ��PPPoE Server������Ϣ
*       Return: VOS_OK: ����ɹ�
*               POES_PARAM_ERR: ����������Ϸ�
*               POES_IF_NULL: ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               POES_ISNOT_SERVER: ��̫�ӿ�δʹ��PPPoE Server
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesIfCfgInfo(ULONG ulEthIfIndex, POES_IF_CFG_INFO_S *pstIfCfgInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesSesInfo
*  Description: ����̫�ӿڻ�ȡSession������Ϣ
*        Input: ULONG ulEthIfIndex:��̫�ӿ�����
*               USHORT *pusSessionID:Session ID(Ϊ0��ʾ�����һ��Session)
*       Output: USHORT *pusSessionID:��һ�������Session��ID(Ϊ0xFFFF��ʾ��û��Session�����)
*               POES_SESSION_INFO_S *pstSesInfo:���Session������Ϣ
*       Return: VOS_OK: ����ɹ�
*               POES_PARAM_ERR: ����������Ϸ�
*               POES_IF_NULL: ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               POES_ISNOT_SERVER: ��̫�ӿ�δʹ��PPPoE Server
*               POES_HAVE_NO_SESSION: ��̫�ӿ�û��Session
*               POES_SESSIONID_ERR: ����Session IDΪ0xFFFF��ID�Ƿ�
*               POES_GET_SESSION_INFO_FAILED: ���Session��Ϣʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesSesInfo(ULONG ulEthIfIndex, USHORT *pusSessionID, POES_SESSION_INFO_S *pstSesInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesSesPktStatInfo
*  Description: ����̫�ӿڻ�ȡ����ͳ����Ϣ
*        Input: ULONG ulEthIfIndex:��̫�ӿ�����
*               USHORT *pusSessionID: Session ID(Ϊ0��ʾ�����һ��Session)
*       Output: USHORT *pusSessionID:��һ�������Session��ID(Ϊ0xFFFF��ʾû��Session�����)
*               POES_SES_PKT_STAT_INFO_S *pstPktStatInfo: �������ͳ����Ϣ
*       Return: VOS_OK: ����ɹ�
*               POES_PARAM_ERR: ����������Ϸ�
*               POES_IF_NULL: ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               POES_ISNOT_SERVER: ��̫�ӿ�δʹ��PPPoE Server
*               POES_HAVE_NO_SESSION: ��̫�ӿ�û��Session
*               POES_SESSIONID_ERR: ����Session IDΪ0xFFFF��ID�Ƿ�
*               POES_GET_SESSION_INFO_FAILED: ���Session��Ϣʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesSesPktStatInfo(ULONG ulEthIfIndex, USHORT *pusSessionID,
                                         POES_SES_PKT_STAT_INFO_S * pstPktStatInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesSesStatInfo
*  Description: ������̫�ӿڻ�ȡSessionͳ����Ϣ:
*               ��̫�ӿ��µ�Session ������ǰSession�������ʣ����Session�������ʣ�Session����ʧ�ܴ���
*        Input: ULONG ulEthIfIndex: ��̫�ӿڵ�����ֵ
*       Output: POES_SESSION_STAT_INFO_S *pstSesStatInfo:��ȡ��ͳ����Ϣ
*       Return: VOS_OK: ����ɹ�
*               POES_PARAM_ERR: ����������Ϸ�
*               POES_IF_NULL: ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               POES_ISNOT_SERVER: ��̫�ӿ�δʹ��PPPoE Server
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesSesStatInfo(ULONG ulEthIfIndex, POES_SESSION_STAT_INFO_S *pstSesStatInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesSysCfgInfo
*  Description: ��ȡȫ�ֵ�PPPoE Server������Ϣ��������AC Name�����57���ַ�����ȫ��Session������
*               ����MAC Session�����ƣ��Զ�MAC Session������
*        Input: 
*       Output: POES_SYS_CFG_INFO_S *pstSysCfgInfo  ��¼��ȡ��������Ϣ
*       Return: VOS_OK: ����ɹ�
*               POES_PARAM_ERR: ����������Ϸ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesSysCfgInfo(POES_SYS_CFG_INFO_S *pstSysCfgInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPoesWarningSwitch
*  Description: ��ȡPPPoE����LCPUP/DOWN�澯����
*        Input: 
*       Output: ULONG *pulSwitch:����澯����0: �� 1: ��
*       Return: VOS_OK: ����ɹ�
*               POES_PARAM_ERR: ����������Ϸ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPoesWarningSwitch(ULONG *pulSwitch);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesDbgSwitch
*  Description: ���õ�����Ϣ����
*        Input: ULONG ulEthIfIndex:��̫�ӿ�����(Ϊ0��ʾ����ȫ�ֵ�����Ϣ����)
*               ULONG ulType:������Ϣ�������� 0�����п��أ�1�����ݱ��ģ�2��Э�̱��ģ�3���¼����ģ�
*               4��Э�鼰���Ĵ��������Ϣ
*               ULONG ulValue:����ȡֵ 0���أ�1����
*       Output: 
*       Return: VOS_OK: ����ɹ�
*               POES_PARAM_ERR: ����������Ϸ�
*               POES_IF_NULL: ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               POES_ISNOT_SERVER: ��̫�ӿ�δʹ��PPPoE Server
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesDbgSwitch(ULONG ulEthIfIndex, ULONG ulType, ULONG ulValue);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesHADbg
*  Description: Set poes ha debug switch
*        Input: ULONG ulDbg: 1: Set, 0: Clear
*       Output: 
*       Return: VOS_OK(0): Success, VOS_ERR(1): Fail
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesHisSesLimit
*  Description: ���öԶ�MAC���Session�����ƣ�Ĭ����100�������÷�ΧΪ0��65534
*        Input: ULONG ulSesLimit:����Ҫ���õĶԶ�MAC���Session��
*       Output: 
*       Return: VOS_OK: ����ɹ�
*               POES_PARAM_ERR: ����������Ϸ�
*               POES_HA_IS_SMOOTHING: HA�����ֶ�������ƽ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesHisSesLimit(ULONG ulSesLimit);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesOurSesLimit
*  Description: ���ñ���Mac���Session�����ƣ�Ĭ����1000�������÷�ΧΪ0��65534
*        Input: ULONG ulSesLimit:Ҫ���õı���MAC���Session��
*       Output: 
*       Return: VOS_OK: ����ɹ�
*               POES_PARAM_ERR: ����������Ϸ�
*               POES_HA_IS_SMOOTHING: HA�����ֶ�������ƽ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesOurSesLimit(ULONG ulSesLimit);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesServiceName
*  Description: ����PPPoE Server��Service Name
*        Input: ULONG ulEthIfIndex:��̫�ӿ�����
*               CHAR *pszName:Ҫ���õ�ServiceName�ַ���
*       Output: 
*       Return: VOS_OK: ����ɹ�
*               POES_IF_NULL:    ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               POES_ISNOT_SERVER:    ��̫�ӿ�δʹ��PPPoE Server
*               POES_SERVICENAME_TOOLONG:    �����ַ���̫��
*               POES_HA_IS_SMOOTHING:    HA�����ֶ�������ƽ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesServiceName(ULONG ulEthIfIndex, CHAR *pszName);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesSesLimit
*  Description: ����ȫ�����Session�����ƣ�Ĭ����1000�������÷�ΧΪ0��65534
*        Input: ULONG ulSesLimit:Ҫ���õ�ȫ�����Session��
*       Output: 
*       Return: VOS_OK: ����ɹ�
*               POES_PARAM_ERR: ����������Ϸ�
*               POES_HA_IS_SMOOTHING: HA�����ֶ�������ƽ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesSesLimit(ULONG ulSesLimit);
/*******************************************************************************
*    Func Name: TCPIP_SetPoesWarningSwitch
*  Description: ����PPPoE����LCP UP/DOWN�澯����
*        Input: ULONG ulWarnSw:��������
*               0��ʾ�أ�1��ʾ����������Ч
*       Output: 
*       Return: VOS_OK: ����ɹ�
*               POES_PARAM_ERR: ����������Ϸ�
*      Caution: ��ͨPPP������LCP UP/DOWNʱ�������Ǹ澯����POES��PPPoE���ӿ���ͨ�����ؿ�
*               �ơ����ص�����ȫ����Ч��Ĭ���ǲ��Ǹ澯��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPoesWarningSwitch(ULONG ulWarnSw);
/*******************************************************************************
*    Func Name: TCPIP_ShowPoesSessionInfo
*  Description: ��ʾVISP������PPPOE����˻Ự��Ϣ
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   luowentong105073        Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowPoesSessionInfo(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowPoesStatistic
*  Description: ��ӡ�ýӿ�������Session��ͳ����Ϣ
*        Input: CHAR *pszIfName:�ӿ�����
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
extern VOID  TCPIP_ShowPoesStatistic(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetACNameHook
*  Description: ע���ȡAC NAME�Ĺ��Ӻ���
*        Input: GetACName_HOOK_FUNC pfHookFunc:Ҫע��ĺ�����ַ
*       Output: 
*       Return: �ɹ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetACNameHook(GetACName_HOOK_FUNC pfHookFunc);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __POES_API_H__ */

