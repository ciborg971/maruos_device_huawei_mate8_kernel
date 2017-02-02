/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4r_api.h
*
*  Project Code: VISPV1R6
*   Module Name:   
*  Date Created: 2008-3-8
*        Author: LY(57500)
*   Description: dhcp4rģ������ṩ��ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-3-8  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _DHCP4R_API_H_
#define _DHCP4R_API_H_

#ifdef __cplusplus
extern "C"{
#endif

/* �����û��ӿڴ�����;��Ӵ�����ʱע��ͬ������ g_aszDhcp4rErrInfo */
enum enDHCP4RErrInfo
{
    DHCP4R_OK = VOS_OK,
    DHCP4R_ERR = VOS_ERR,
    DHCP4R_ERR_PARAM,               /*  2  �������Ϸ�                  */
    DHCP4R_ERR_NOMEM,               /*  3  �ڴ����ʧ��                */
    DHCP4R_ERR_NULL_IF,             /*  4  �ӿڲ�����                  */
    DHCP4R_ERR_NULL_POINTER,        /*  5  ָ�����Ϊ��                */
    DHCP4R_ERR_NOSUPPORT_IF,        /*  6  �ӿڲ�֧��DHCP4R            */
    DHCP4R_ERR_BORROW_IP_IF,        /*  7  ���õ�ַ�ӿ�                */
    DHCP4R_ERR_TRUNKPORT_IF,        /*  8  TRUNK��Ա�˿ڲ�֧��RELAY    */
    DHCP4R_ERR_MODE_NO_MATCH,       /*  9  ����ģʽ��ƥ��              */
    DHCP4R_ERR_NO_CFG,              /*  10 û�����ÿ��ƿ�              */
    DHCP4R_ERR_SERVER_EXIST,        /*  11 �Ѿ������������ַ          */
    DHCP4R_ERR_SERVER_NOEXIST,      /*  12 û�������������ַ          */
    DHCP4R_ERR_SERVER_INVALID,      /*  13 ���õ�server��ַ�Ƿ�        */
    DHCP4R_ERR_MAX_SERVER,          /*  14 �ﵽ���SERVER����          */
    DHCP4R_ERR_NO_OPERATE,          /*  15 ���������                  */
    DHCP4R_ERR_82_SUBCODE,          /*  16 82��ѡ��������            */
    DHCP4R_ERR_82_SUBLEN,           /*  17 82��ѡ��Ȳ�������        */
    DHCP4R_ERR_82_SUB_NOCFG,        /*  18 û�����ô�82��ѡ��          */   
    DHCP4R_ERR_HA_IS_SMOOTHING,     /*  19 HA�����ֶ�������ƽ������    */  
    DHCP4R_ERR_INVALID_VRF,         /*  20 VRF����                     */
    DHCP4R_ERR_CFG_MODE_NOMATCH,    /*  21 ģʽ����                    */
    DHCP4R_ERR_NOT_REGISTER,        /*  22 DHCP4R ģ��δע��           */
    DHCP4R_ERR_MALLOC_VRFCFG,       /*  23 ����Relay���ƿ�ʧ��         */
    DHCP4R_ERR_MODE_DIS,            /*  24 ȥʹ��ģʽ��ʹ��ģʽ��һ��  */
    DHCP4R_ERR_NO_CFG_VRF,          /*  25 û�и�VRF�µ����ÿ��ƿ�     */
    DHCP4R_ERR_NO_DBG_VRF,          /*  26 û�и�VRF�µĵ��Կ��ƿ�     */
    DHCP4R_ERR_IF_EXC_VRF,          /*  27 �ӿڲ��ڸ�VRFʵ����         */
    DHCP4R_ERR_VRF_WAITLIST,        /*  28 WAITLIST�Ĵ���              */
    
    DHCP4R_ERR_MAX,                 /*  ���������ֵ,�Ժ���Ӵ������밴˳����ӵ���ǰ */
};
/* �����û��ӿڴ�����;��Ӵ�����ʱע��ͬ������ g_aszDhcp4rErrInfo */

#define DHCP4R_82_SUB_MAXLEN        24      /* ��ѡ����󳤶�   */
#define DHCP4R_SERVER_MAX_NUM       8
#define DHCP4R_82_SUB_NUM           2       /* ��ѡ�����       */
#define DHCP4R_AGENT_MAX_NUM        8


/* define dhcp relay 82ѡ��ģʽ Ĭ��Ϊ0*/
#define DHCP4R_OPT82_MODE_HOLD          0  /*����client��82ѡ�����*/
#define DHCP4R_OPT82_MODE_MODIFY        1  /*�޸Ļ������ client ��82ѡ�����*/


/* 82��ѡ�����ÿ��ƿ� */
typedef struct tagDHCP4RSubOption82
{
    ULONG       ulSubCode;          /* ��ѡ�����   */
    ULONG       ulSubLen;           /* ��ѡ���   */
    UCHAR       aucSubVar[DHCP4R_82_SUB_MAXLEN];  /* ��ѡ��ֵ */
}DHCP4R_SUBOPTION82_S;

/* ����������õĿ��ƿ� */
typedef struct tagDHCP4RCfg
{
    ULONG   ulIfIndex;          /* �ӿ�����,ȫ������ģʽ������Ϊ0   */
    ULONG   ulEnableStatus;     /* ʹ��״̬,1-ʹ��;0-ȥʹ��         */
    ULONG   ulServerNum;        /* ���õ��м̵�ַ��Ŀ               */
    ULONG   aulServer[DHCP4R_SERVER_MAX_NUM];   /* ���õ��м̵�ַ����,��˳��洢    */ 
    DHCP4R_SUBOPTION82_S astSubOption82[DHCP4R_82_SUB_NUM]; /* ���õ�82��ѡ������   */
    ULONG   ulVrfIndex;         /* ʵ����,0��ʾ����                 */
    ULONG   ulOpt82Mode;        /* option82 ģʽ */
}DHCP4R_CFG_INFO_S;

/* Relayͳ����Ϣ�ṹ */
typedef struct tagDHCP4RStatInfo
{
    ULONG ulRxServerPkt;            /* Relay�յ���Server�����ı�����        */
    ULONG ulTxServerPkt;            /* Relay���͵�Server�ı�����            */

    ULONG ulRxClientPkt;            /* Relay�յ���Client�������ı�������    */
    ULONG ulTxClientUnicast;        /* Relay��Client���͵�DHCP����������    */
    ULONG ulTxClientBroadcast;      /* Relay��Client���͵�DHCP�㲥������    */
    ULONG ulTxClientPkt;            /* Relay���͵�Client�ı�����            */

    ULONG ulRxClientDiscoverPkt;    /* Relay�յ���DISCOVER������            */
    ULONG ulRxClientRequestPkt;     /* Relay�յ���REQUEST������             */
    ULONG ulRxClientDeclinePkt;     /* Relay�յ���DECLINE������             */
    ULONG ulRxClientReleasePkt;     /* Relay�յ���RELEASE������             */
    ULONG ulRxClientInformPkt;      /* Relay�յ���INFORM������              */
    ULONG ulRxServerOfferPkt;       /* Relay�յ���OFFER������               */
    ULONG ulRxServerAckPkt;         /* Relay�յ���ACK������                 */
    ULONG ulRxServerNakPkt;         /* Relay�յ���NAK������                 */

    /* �쳣���ļ��� */
    ULONG ulRxBadPkt;               /* Relay�յ����쳣������                    */
    ULONG ulBorrowDropPkt;          /* Relay�ӽ��ýӿڽ��������ı���Ӧ����      */
    ULONG ulAdd82TooLongPkt;        /* Relay��82ѡ����ĳ��ȳ�������Ӧ����    */

    ULONG ulTxRelayPkt;            /* Relay���͵�Relay(����Relay)�ı�����            */

}DHCP4R_STATINFO_S;

/*���ݽӿ�������Relay ��ַ��ȡRelay������Դ��ַ�ص����� 
  �������: ulIfIndex:�ӿ�����������֧�ֶ���ӿ�ʹ��DHCP Relay�����
            ulRelayIP: ���ص�ַ(������)�����û��������ַʱ������ʹ�øõ�ַ��Ϊ���ĵ�Դ��ַ
  ����ֵ:   Դ��ַ(������)��������ص�Դ��ַΪ0����ָ���ĵ�ַ�Ǳ���IP��ʹ�����ص�ַ��ΪԴ��ַ
*/
typedef ULONG (*DHCP4R_GET_SRCADDR_HOOK)(ULONG ulIfIndex, ULONG ulOutIfIndex, ULONG ulRelayIP);

/* Modified by likaikun00213099 for secondary Relay Src IP at 2014-04-10 */
typedef struct tagDHCP4R_GET_SRCADDR
{
    UCHAR  *pPacket;        /* DHCP���ģ�����IP��UDP�ײ�����ʣ��DHCP�ײ���ԭʼ���ģ�*/
    ULONG  ulInputIfIndex;  /* ��ӿ�����           */
    ULONG  ulVrfIndex;      /* VRF����              */
    ULONG  ulServerIp;      /* ������, dhcp������IP */
}DHCP4R_GET_SRCADDR_S;

/*���ݽӿ�������server ��ַ��ȡRelay������Դ��ַ�ص����� 
  �������: DHCP4R_GET_SRCADDR_S *pstInfo ͨ��dhcp���ģ���ӿڣ�vrf��server ip��Ϣ��ȡԴ��ַ
  ����ֵ:   Դ��ַ(������)��������ص�Դ��ַΪ0����ָ���ĵ�ַ�Ǳ���IP��ʹ�����ص�ַ��ΪԴ��ַ
*/
typedef ULONG (*DHCP4R_GET_SRCADDR_BY_SVRIP_HOOK)(DHCP4R_GET_SRCADDR_S *pstInfo);
/* End of Modified by likaikun00213099 for secondary Relay Src IP at 2014-04-10 */

typedef ULONG (*DHCP4R_PROC_REQUEST_HOOK)(ULONG ulIfIndex, UCHAR* pPacket, ULONG ulDhcpServerIp);

typedef struct tagDHCP4R_GET_GIADDR
{
    UCHAR  *pPacket; 
    ULONG  ulInputIfIndex; /* ��ӿ����� */
    ULONG  ulVrfIndex;     /* ��վĿǰֻ��Ϊ0����Ʒ���Բ���ע */
    ULONG  ulServerIp;     /* ��������ַ�������� */
    USHORT usVlanInfo;     /*VLAN Tag��Ϣ�������򣬺�12bitΪVLAN ID����ǰ�в��ܻ�ȡ���ȼ���TRANû�ϴ����ȼ���Ϣ */
    USHORT usRes;  
    ULONG  ulGiaddr[DHCP4R_AGENT_MAX_NUM]; /*Giaddr�б�������Ϊ0��ʾ��Ч������Ҫ��֤��Ч�ض�����ǰ��*/
}DHCP4R_GET_GIADDR_S;
typedef ULONG (*DHCP4R_GET_GIADDR_HOOK)(DHCP4R_GET_GIADDR_S *pInfo);


typedef ULONG (*DHCP4R_PROC_REPLY_HOOK)(ULONG ulIfIndex, UCHAR *pPacket, ULONG *pulRecLen);

typedef struct tagDHCP4R_GET_CLIENTIF
{
    UCHAR *pPacket;         /* ���,DHCP����,����IP��UDP�ײ�,��ʱ��Giaddr�ֶ�Ϊ������ */ 
    ULONG  ulOutIfIndex;    /* ����,ת���Ľӿ����� */
    ULONG  ulSrcIp;         /* ����,ת�����ĵ�Դ��ַ(������) */
}DHCP4R_GET_CLIENTIF_S;

typedef struct tagDHCP4R_GET_CLIENTIF_BYVRF
{
    UCHAR *pPacket;         /* ���,DHCP����,����IP��UDP�ײ�,��ʱ��Giaddr�ֶ�Ϊ������ */ 
    ULONG  ulOutIfIndex;    /* ����,ת���Ľӿ����� */
    ULONG  ulSrcIp;         /* ����,ת�����ĵ�Դ��ַ(������) */
    ULONG ulVrfIndex;
}DHCP4R_GET_CLIENTIF_BYVRF_S;


typedef ULONG (*DHCP4R_GET_CLIENTIF_HOOK)(DHCP4R_GET_CLIENTIF_S *pstInfo);


typedef ULONG (*DHCP4R_GET_CLIENTIF_BYVRF_HOOK)(DHCP4R_GET_CLIENTIF_BYVRF_S *pstInfo);

/* ע��DHCP Relayģ�鱨��Ԥ�����ӣ��ɲ�Ʒ���ݱ������ݣ�����Option82��ѡ�� */
typedef struct tagDHCP4R_FORM_OPTION82
{
    ULONG ulIfIndex;   /*��Σ��յ���DHCP������ӿ�*/
    ULONG ulGiaddr;    /*��Σ�����������Giaddr��������*/
    DHCP4R_SUBOPTION82_S astSubOption82[2]; /*���Σ�Option82���ݣ�Option82��2����ѡ�����Ҫ���õ���ѡ���ulSubLen�ֶα�������Ϊ0��*/
}DHCP4R_FORM_OPTION82_S;


typedef ULONG (*DHCP4R_OPTION82_HOOK)(DHCP4R_FORM_OPTION82_S *pstInfo);



/* API declare */
/*******************************************************************************
*    Func Name: TCPIP_DhcpRelay
*  Description: ʹ��DHCP Relay
*        Input: ULONG ulIfIndex: �ӿ�����(֧��DHCP Relay�ĺϷ��ӿ�����)��0(Ԥ����ȫ������ģ��)
*               ULONG ulSetYes:  ʹ��/ȥʹ�� 0- ȥʹ�� 1- ʹ��
*       Output: 
*       Return: DHCP4R_OK 0                 �ɹ�
*               DHCP4R_ERR_NOMEM            �ڴ����ʧ��
*               DHCP4R_ERR_NO_OPERATE       ���������
*               DHCP4R_ERR_MODE_NO_MATCH    ����ģʽ��ƥ��
*               DHCP4R_ERR_NULL_IF          �ӿ�Ϊ��
*               DHCP4R_ERR_NOSUPPORT_IF     ������Ӧ�ӿڲ�֧��DHCP Relay
*               DHCP4R_ERR_TRUNKPORT_IF     TRUNK��Ա�˿ڲ�֧��DHCP Relay
*               DHCP4R_ERR_BORROW_IP_IF     ���õ�ַ�ӿڲ���ʹ��/����DHCP Relay
*               DHCP4R_ERR_HA_IS_SMOOTHING  ��ƽ�����ֶ�����
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DhcpRelay( ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_CfgDhcprServer
*  Description: ����RELAY�м̵�ַ
*        Input: ULONG ulOperate: ����/ɾ���м̵�ַ
*               ULONG ulIndex:   �ӿ�����(֧��DHCP Relay�ĺϷ��ӿ�����)��0(Ԥ����ȫ������ģ��)
*               ULONG ulServerIP: �м̵�ַ
*       Output: 
*       Return: DHCP4R_OK 0                 �ɹ�
*               DHCP4R_ERR_NOMEM            �ڴ����ʧ��
*               DHCP4R_ERR_NO_OPERATE       ���������
*               DHCP4R_ERR_MODE_NO_MATCH    ����ģʽ��ƥ��
*               DHCP4R_ERR_NULL_IF          �ӿ�Ϊ��
*               DHCP4R_ERR_SERVER_INVALID   �Ƿ��м̵�ַ
*               DHCP4R_ERR_NOSUPPORT_IF     ������Ӧ�ӿڲ�֧��DHCP Relay
*               DHCP4R_ERR_BORROW_IP_IF     ���õ�ַ�ӿڲ���ʹ��/����DHCP Relay
*               DHCP4R_ERR_TRUNKPORT_IF     TRUNK��Ա�˿ڲ�֧��DHCP Relay
*               DHCP4R_ERR_MAX_SERVER       �ﵽ���SERVER����
*               DHCP4R_ERR_NO_CFG           û�н��й�����
*               DHCP4R_ERR_SERVER_EXIST     �Ѿ����������IP
*               DHCP4R_ERR_SERVER_NOEXIST   û�����ô�IP
*               DHCP4R_ERR_HA_IS_SMOOTHING  ��ƽ�����ֶ�����
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_CfgDhcprServer(ULONG ulOperate, ULONG ulIndex, ULONG ulServerIP);
/*******************************************************************************
*    Func Name: TCPIP_CfgOption82
*  Description: ����82ѡ��
*        Input: ULONG ulOperate: ����/ɾ��82ѡ��
*               ULONG ulIndex:   �ӿ�����(֧��DHCP Relay�ĺϷ��ӿ�����)��0(Ԥ����ȫ������ģ��)
*               ULONG ulSubCode: ��ѡ��ID(1/2�Ϸ�;ɾ��82ѡ��ʱ0Ҳ�Ϸ�,��ʾɾ��������ѡ��)
*               ULONG ulSubLen:  ��ѡ���
*               UCHAR *szSubVar: ��ѡ��ֵ
*       Output: 
*       Return: DHCP4R_OK  0                �ɹ�
*               DHCP4R_ERR_PARAM            �����Ƿ�
*               DHCP4R_ERR_NO_OPERATE       ���������
*               DHCP4R_ERR_MODE_NO_MATCH    ����ģʽ��ƥ��
*               DHCP4R_ERR_NULL_IF          �ӿ�Ϊ��
*               DHCP4R_ERR_NULL_POINTER     ָ�����Ϊ��
*               DHCP4R_ERR_NO_CFG           û�н��й�����
*               DHCP4R_ERR_NOSUPPORT_IF     ������Ӧ�ӿڲ�֧��DHCP Relay
*               DHCP4R_ERR_BORROW_IP_IF     ���õ�ַ�ӿڲ���ʹ��/����DHCP Relay
*               DHCP4R_ERR_TRUNKPORT_IF     TRUNK��Ա�˿ڲ�֧��DHCP Relay
*               DHCP4R_ERR_82_SUBCODE       82��ѡ��������
*               DHCP4R_ERR_82_SUBLEN        82��ѡ��Ȳ�������
*               DHCP4R_ERR_82_SUB_NOCFG     û�����ô�82��ѡ�� 
*               DHCP4R_ERR_HA_IS_SMOOTHING  ��ƽ�����ֶ�����
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_CfgOption82(ULONG ulOperate, ULONG ulIndex, ULONG ulSubCode, ULONG ulSubLen, UCHAR *szSubVar);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcprCfg
*  Description: ��ȡDHCP RELAY�������������ʹ��״̬���м̵�ַ���м���Ŀ��OPTION82����
*        Input: ULONG ulIndex: �ӿ�������0��������Ч����   
*               DHCP4R_CFG_INFO_S *pstDhcprCfg   
*       Output: DHCP4R_CFG_INFO_S *pstDHCP4RCfg: ���������Ϣ
*       Return: DHCP4R_OK 0                 �ɹ�
*               DHCP4R_ERR_MODE_NO_MATCH    ����ģʽ��ƥ��
*               DHCP4R_ERR_NULL_IF          �ӿ�Ϊ��
*               DHCP4R_ERR_NOSUPPORT_IF     ������Ӧ�ӿڲ�֧��DHCP4R
*               DHCP4R_ERR_TRUNKPORT_IF     TRUNK��Ա�˿ڲ�֧��DHCP Relay
*               DHCP4R_ERR_BORROW_IP_IF     ���õ�ַ�ӿڲ���ʹ��/����DHCP Relay
*               DHCP4R_ERR_NULL_POINTER     ָ�����Ϊ��
*               DHCP4R_ERR_NO_CFG           û��������ӿ�������
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprCfg(ULONG ulIndex, DHCP4R_CFG_INFO_S *pstDhcprCfg);
/*******************************************************************************
*    Func Name: TCPIP_SetDhcprFwdMode
*  Description: �����м̷�ʽ
*        Input: ULONG ulFwdMode: �м̷�ʽ 0-�ֵ���ʽ,1-�㲥��ʽ
*       Output: 
*       Return: DHCP4R_OK 0                 �ɹ�
*               DHCP4R_ERR_PARAM            �����Ƿ�
*               DHCP4R_ERR_HA_IS_SMOOTHING  ��ƽ�����ֶ�����
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprFwdMode(ULONG ulFwdMode);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcprFwdMode
*  Description: ��ȡDHCP Relay�м̷�ʽ
*        Input: ULONG *pulFwdMode: �����м̷�ʽ
*       Output: 
*       Return: DHCP4R_OK                   �ɹ�
*               DHCP4R_ERR_NULL_POINTER     ָ�����Ϊ��
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprFwdMode(ULONG *pulFwdMode);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcprStat
*  Description: ��ȡrelayͳ����Ϣ
*        Input: DHCP4R_STATINFO_S *pstDhcprStat: ���������ͳ����Ϣ
*       Output: 
*       Return: DHCP4R_OK                   �ɹ�
*               DHCP4R_ERR_NULL_POINTER     ָ�����Ϊ��
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprStat(DHCP4R_STATINFO_S *pstDhcprStat);
/*******************************************************************************
*    Func Name: TCPIP_ClrDhcprStat
*  Description: ����Relay��ͳ����Ϣ
*        Input: VOID
*       Output: 
*       Return: DHCP4R_OK                   �ɹ�
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_ClrDhcprStat(VOID);
/*******************************************************************************
*    Func Name: TCPIP_SetDhcprMaxHops
*  Description: ����relay����м�����
*        Input: ULONG ulhops: ����,1~16
*       Output: 
*       Return: DHCP4R_OK 0                 �ɹ�
*               DHCP4R_ERR_PARAM            �����Ƿ�
*               DHCP4R_ERR_HA_IS_SMOOTHING  ��ƽ�����ֶ�����
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprMaxHops(ULONG ulhops);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcprMaxHops
*  Description: ��ȡ����м�����
*        Input: ULONG *pulhops: ����������м�����
*       Output: 
*       Return: DHCP4R_OK                   �ɹ�
*               DHCP4R_ERR_NULL_POINTER     ָ�����Ϊ��
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprMaxHops(ULONG *pulhops);
/*******************************************************************************
*    Func Name: TCPIP_SetDhcprTos
*  Description: ����relay socket TOS
*        Input: UCHAR ucTos: tosֵ��ֵ����Ч
*       Output: 
*       Return: DHCP4R_OK 0                 �ɹ�
*               DHCP4R_ERR_HA_IS_SMOOTHING  ��ƽ�����ֶ�����
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprTos(UCHAR ucTos);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcprTos
*  Description: ��ȡtos
*        Input: UCHAR *pucTos: ���������tos
*       Output: 
*       Return: DHCP4R_OK                   �ɹ�
*               DHCP4R_ERR_NULL_POINTER     ָ�����Ϊ��
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprTos(UCHAR *pucTos);
/*******************************************************************************
*    Func Name: TCPIP_SetDhcpDebug
*  Description: ����RELAY���Կ���
*        Input: ULONG ulOperate:  0��1��0��ʾ������Կ��أ�1��ʾ���õ��Կ���
*               ULONG ulIndex: 0����Ч�ӿ�����,0��ʾ����ȫ�ֵ��Կ���;������ʾ���ö�Ӧ�ӿڵĵ��Կ���
*               ULONG ulDebugLevel: ���Լ���1��packet���Կ���,2��err���Կ���,3��all(packet��err���Կ���)
*       Output: 
*       Return: DHCP4R_OK 0                 �ɹ�
*               DHCP4R_ERR_PARAM            �����Ƿ�
*               DHCP4R_ERR_NOMEM            û���ڴ�
*               DHCP4R_ERR_NO_OPERATE       ���������
*               DHCP4R_ERR_NULL_IF          �ӿ�Ϊ��
*               DHCP4R_ERR_NOSUPPORT_IF     ������Ӧ�ӿڲ�֧��DHCP4R
*               DHCP4R_ERR_TRUNKPORT_IF     TRUNK��Ա�˿ڲ�֧��DHCP Relay
*               DHCP4R_ERR_BORROW_IP_IF     ���õ�ַ�ӿ�
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpDebug(ULONG ulOperate, ULONG ulIndex, ULONG ulDebugLevel);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcpDebug
*  Description: ��ȡ���Կ���״̬
*        Input: ULONG ulIndex: �ӿ�������0��������Ч����
*       Output: ULONG *pulDebug: ������Բ����ı���ָ��
*       Return: DHCP4R_OK 0                 �ɹ�
*               DHCP4R_ERR_NULL_IF          �ӿ�Ϊ��
*               DHCP4R_ERR_NOSUPPORT_IF     ������Ӧ�ӿڲ�֧��DHCP4R
*               DHCP4R_ERR_TRUNKPORT_IF     TRUNK��Ա�˿ڲ�֧��DHCP Relay
*               DHCP4R_ERR_BORROW_IP_IF     ���õ�ַ�ӿڲ���ʹ��/����DHCP Relay
*               DHCP4R_ERR_NULL_POINTER     ָ�����Ϊ��
*               DHCP4R_ERR_NO_CFG           û������
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpDebug(ULONG ulIndex, ULONG *pulDebug);
/*******************************************************************************
*    Func Name: TCPIP_SetDhcprHADbg
*  Description: ����DHCP4R ha���Կ���
*        Input: ULONG ulDbg: ����״̬ 1-open;0-close
*       Output: 
*       Return: VOS_OK                      ���óɹ�
*               VOS_ERR                     ����ʧ��
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcprHADbg
*  Description: ��ȡdhcp4r ha���Կ���״̬
*        Input: ULONG* pulDbg: ���������ha���Կ���״̬
*       Output: 
*       Return: VOS_OK                      ��ȡ�ɹ�
*               VOS_ERR                     ��ȡʧ��(ָ�����Ϊ��)
*               DHCP4R_ERR_NOT_REGISTER     DHCP4Rģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprHADbg(ULONG* pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_ShowDhcp4rStatistic
*  Description: ��ʾDHCP4Rģ��ͳ����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern VOID  TCPIP_ShowDhcp4rStatistic(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowDhcp4rStatisticByVrf
* Date Created: 2008-3-8
*       Author: LY(57500)
*  Description: ��ʾDHCP4Rģ��ͳ����Ϣ
*        Input: ULONG ulVrfIndex:vrf����
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
VOID TCPIP_ShowDhcp4rStatisticByVrf(ULONG ulVrfIndex);


extern ULONG TCPIP_RegFuncDHCP4RGetSrcAddrHook(DHCP4R_GET_SRCADDR_HOOK pfHook);

/*******************************************************************************
*    Func Name: TCPIP_RelayEnableByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ʹ��VRF��VRFʵ���µĽӿ�Relay����
*        Input: ULONG ulVrfIndex:VRF����ֵ
*               ULONG ulIfIndex:�ӿ�����(0:����VRF��ȫ��ʵ��)
*               ULONG ulEnable:1:ʹ�ܣ�0:ȥʹ��
*       Output: 
*       Return: �ɹ���ʧ��(������)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_RelayEnableByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, ULONG ulEnable);

/*******************************************************************************
*    Func Name: TCPIP_CfgServerByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ����RELAY�м̵�ַ
*        Input: ULONG ulVrfIndex:VRF����ֵ
*               ULONG ulOperate:����/ɾ���м̵�ַ
*               ULONG ulIfIndex:�ӿ�����(֧��DHCP Relay�ĺϷ��ӿ�����)��0(Ԥ����ȫ������ģ��)
*               ULONG ulServerIP:�м̵�ַ
*       Output: 
*       Return: �ɹ���ʧ��(������)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_CfgDhcprServerByVrf(ULONG ulVrfIndex, ULONG ulOperate, ULONG ulIfIndex, ULONG ulServerIP);

/*******************************************************************************
*    Func Name: TCPIP_CfgOption82ByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ����82ѡ��
*        Input: ULONG ulVrfIndex:VRF����ֵ
*               ULONG ulOperate:����/ɾ��82ѡ��
*               ULONG ulIfIndex:�ӿ�����(֧��DHCP Relay�ĺϷ��ӿ�����)��0(Ԥ����ȫ������ģ��)
*               ULONG ulSubCode:��ѡ��ID(1/2�Ϸ�;ɾ��82ѡ��ʱ0Ҳ�Ϸ�,��ʾɾ��������ѡ��)
*               ULONG ulSubLen:��ѡ���
*               UCHAR *szSubVar:��ѡ��ֵ
*       Output: 
*       Return: �ɹ���ʧ��(������)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_CfgDhcprOption82ByVrf(ULONG ulVrfIndex, ULONG ulOperate, ULONG ulIfIndex, 
                                  ULONG ulSubCode, ULONG ulSubLen, UCHAR *szSubVar);

/*******************************************************************************
*    Func Name: TCPIP_GetCfgByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ��ȡDHCP RELAY�������������VRF����ֵ��ʹ��״̬���м̵�ַ��
*               �м���Ŀ��OPTION82����
*        Input: ULONG ulVrfIndex:VRF����ֵ
*               ULONG ulIfIndex:�ӿ�������0��������Ч����
*               
*       Output: DHCP4R_CFG_INFO_S *pstDHCP4RCfg:���������Ϣ
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprCfgByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, DHCP4R_CFG_INFO_S *pstDHCP4RCfg);

/*******************************************************************************
*    Func Name: TCPIP_SetFwdModeByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ����VRF����ֵ�����м̷�ʽ
*        Input: ULONG ulVrfIndex:VRF����ֵ
*               ULONG ulFwdMode:�м̷�ʽ 0-�ֵ���ʽ,1-�㲥��ʽ
*       Output: 
*       Return: �ɹ���ʧ��(������)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprFwdModeByVrf(ULONG ulVrfIndex, ULONG ulFwdMode);

/*******************************************************************************
*    Func Name: TCPIP_GetFwdModeByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ����VRF��ȡ�м̷�ʽ
*        Input: ULONG ulVrfIndex:VRF����ֵ
*               ULONG *pulMode:�м̷�ʽ 0-�ֵ���ʽ,1-�㲥��ʽ
*       Output: 
*       Return: �ɹ���ʧ��(������)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprFwdModeByVrf(ULONG ulVrfIndex, ULONG *pulFwdMode);

/*******************************************************************************
*    Func Name: TCPIP_GetStatisticsByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ����VRF����ֵ��ȡͳ����Ϣ
*        Input: ULONG ulVrfIndex:VRF����ֵ
*               DHCP4R_STATINFO_S *pstDHCP4RStat:��ȡͳ����Ϣ
*       Output: DHCP4R_STATINFO_S *pstDHCP4RStat:��ȡͳ����Ϣ
*       Return: �ɹ���ʧ��(������)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprStatisticsByVrf(ULONG ulVrfIndex, DHCP4R_STATINFO_S *pstDHCP4RStat);

/*******************************************************************************
*    Func Name: TCPIP_ClearStatisticsByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ����VRF���Relayͳ����Ϣ
*        Input: ULONG ulVrfIndex:VRF����ֵ
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern VOID TCPIP_ClearDhcprStatisticsByVrf(ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SetMaxHopsByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ����VRF����ֵ����relay����м�����
*        Input: ULONG ulVrfIndex:VRF����ֵ
*               ULONG ulhops:����,1~16
*       Output: 
*       Return: �ɹ���ʧ��(������)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprMaxHopsByVrf(ULONG ulVrfIndex, ULONG ulMaxHops);

/*******************************************************************************
*    Func Name: TCPIP_GetMaxHopsByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ����VRF����ֵ��ȡRelay����м�����
*        Input: ULONG ulVrfIndex:VRF����ֵ
*       Output: ULONG *pulhops:�������
*       Return: �ɹ���ʧ��(������)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprMaxHopsByVrf(ULONG ulVrfIndex, ULONG *pulMaxHops);

/*******************************************************************************
*    Func Name: TCPIP_SetTosByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ����VRF����ֵ����TOSֵ
*        Input: ULONG ulVrfIndex:VRF����ֵ
*               UCHAR ucTos:���õ�TOSֵ
*       Output: 
*       Return: �ɹ���ʧ��(������)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprTosByVrf(ULONG ulVrfIndex, UCHAR ucTos);

/*******************************************************************************
*    Func Name: TCPIP_GetTosByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ����VRF����ֵ��ȡ��Ӧ��TOSֵ
*        Input: ULONG ulVrfIndex:VRF����ֵ
*               
*       Output: UCHAR *pucTos:��ȡ��TOSֵ
*       Return: �ɹ���ʧ��(������)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprTosByVrf(ULONG ulVrfIndex, UCHAR *pucTos);

/*******************************************************************************
*    Func Name: TCPIP_SetDebugByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ����VRF����ֵ���õ��Կ���
*        Input: ULONG ulVrfIndex:VRF����ֵ
*               ULONG ulOperate:0��1��0��ʾ������Կ��أ�1��ʾ���õ��Կ���
*               ULONG ulIfIndex:0����Ч�ӿ�����,0��ʾ����ȫ�ֵ��Կ���;������ʾ���ö�Ӧ�ӿڵĵ��Կ���
*               ULONG ulDebugLevel: ���Լ���1��packet���Կ���,2��err���Կ���,3��all(packet��err���Կ���)
*       Output: 
*       Return: �ɹ���ʧ��(������)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcprDebugByVrf(ULONG ulVrfIndex, ULONG ulOperate, ULONG ulIfIndex, ULONG ulDebugLevel);

/*******************************************************************************
*    Func Name: TCPIP_GetDebugByVrf
* Date Created: 2009-04-25
*       Author: mafeng(59090)
*  Description: ����VRF����ֵ��ȡ���Կ���״̬
*        Input: ULONG ulVrfIndex: VRF����ֵ
*               ULONG ulIfIndex: �ӿ�������0��������Ч����
*       Output: ULONG *pulDebug: ������Բ����ı���ָ��
*       Output: 
*       Return: �ɹ���ʧ��(������)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcprDebugByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, ULONG *pulDbgLevel);


extern ULONG TCPIP_RegFuncDHCP4RProcRequestHook(DHCP4R_PROC_REQUEST_HOOK pfHook);


ULONG TCPIP_RegFuncDHCP4RGetGiaddrListHook(DHCP4R_GET_GIADDR_HOOK pfHook);


extern ULONG TCPIP_RegFuncDHCP4RProcReplyHook(DHCP4R_PROC_REPLY_HOOK pfHook);


extern ULONG TCPIP_RegFuncDHCP4RGetClientIfHook(DHCP4R_GET_CLIENTIF_HOOK  pfHook);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncDHCP4ROption82Hook
* Date Created: 2011-06-28
*       Author: y00176567y00176567
*      Purpose: 
*  Description: ע��DHCP Relayģ�鱨��Ԥ������,�ɲ�Ʒ���ݱ�������,����Option82��ѡ��
*        Input: DHCP4R_OPTION82_HOOK  pfHook: �ص�����ָ��
*       Output: 
*       Return: VOS_OK          ע��ɹ�
*               ����            ʧ��
*      Caution: ��Э��ջ����֮ǰע��,��֧�ֽ�ע��
*        Since: V2R3C05
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-28   y00176567y00176567      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDHCP4ROption82Hook(DHCP4R_OPTION82_HOOK pfHook);
/*******************************************************************************
*    Func Name: TCPIP_SetDHCP4RMultiRelaySwitch
* Date Created: 2011-07-03
*       Author: zhaoyue00171897/yangheng00176567
*  Description: ���ö༶Relay����,�Խ����Ʒ���ƵĶ���Relay��������
*        Input: ULONG ulSwitch:����״̬ 0 �ر�  ���� ��
*       Output: 
*       Return: DHCP4R_OK   �ɹ�
*               ����        ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-03   z171897/y176567         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDHCP4RMultiRelaySwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetDHCP4RMultiRelaySwitch
* Date Created: 2011-07-03
*       Author: zhaoyue00171897/yangheng00176567
*  Description: ��ȡ��DHCP Relay�϶༶Relay���ص�״̬
*        Input: 
*       Output: ULONG *pulSwitch:����״̬
*       Return: DHCP4R_OK   �ɹ�
*               ����        ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-07-03   z171897/y176567         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDHCP4RMultiRelaySwitch(ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcp4rOpt82ModeByVrf
* Date Created: 2011-04-17
*       Author: luogaowei61496
*  Description: ���ʹ��DHCP Relay�Ľӿ�����82ѡ��Ĵ���ģʽ
*               ���޸�DHCP Client ��82ѡ�� �����滻Ϊ Relay ��ѡ��
*        Input: ULONG ulVrfIndex:VRF����ֵ
*               ULONG ulIfIndex: ʹ��DHCP Relay�Ľӿ�����ֵ
*               ULONG ulMode:  82ѡ��Ĵ���ģʽ
*                     (0:���޸�Client 82ѡ�1:�滻 client 82ѡ��)
*       Output: 
*       Return: 
*               DHCP4R_OK  0                �ɹ�
*               ����������
*      Caution: Ĭ��Ϊ����client��82ѡ��
*              #define DHCP4R_OPT82_MODE_HOLD    0  ����client��82ѡ�����
*              #define DHCP4R_OPT82_MODE_MODIFY  1  �޸Ļ������ client ��82ѡ�����
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-04-17   luogaowei61496          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcp4rOpt82ModeByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, 
                                                ULONG ulMode);


/*******************************************************************************
*    Func Name: TCPIP_GetDhcp4rOpt82ModeByVrf
* Date Created: 2011-04-17
*       Author: luogaowei61496
*  Description: ��ȡָ���ӿ�����82ѡ��Ĵ���ģʽ
*        Input: ULONG ulVrfIndex:VRF����ֵ
*               ULONG ulIfIndex: ʹ��DHCP Relay�Ľӿ�����ֵ
*                     (0:���޸�Client 82ѡ�1:�滻 client 82ѡ��)
*       Output: ULONG *pulMode:  82ѡ��Ĵ���ģʽ
*       Return: 
*               DHCP4R_OK  0                �ɹ�
*               ����������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-04-17   luogaowei61496          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcp4rOpt82ModeByVrf(ULONG ulVrfIndex, ULONG ulIfIndex, 
                                                ULONG   *pulMode);


extern ULONG TCPIP_RegFuncDHCP4RGetClientIfByVrfHook(DHCP4R_GET_CLIENTIF_BYVRF_HOOK  pfHook);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncDHCP4RGetSrcAddrBySvrIpHook
* Date Created: 2014-04-16
*       Author: likaikun213099
*  Description: ע���ȡRelay������Դ��ַ�ص�����
*        Input: DHCP4R_GET_SRCADDR_BY_SVRIP_HOOK pfHook: �ص�����ָ��
*       Output: 
*       Return: VOS_OK                  ע��ɹ�
*               DHCP4R_ERR_NULL_POINTER ����ָ��Ϊ��
*      Caution: ע�����ע������TCPIP_RegFuncDHCP4RGetSrcAddrHook��ȣ�
*               ��Ҫsever IP��Ϣ
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-16   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDHCP4RGetSrcAddrBySvrIpHook(DHCP4R_GET_SRCADDR_BY_SVRIP_HOOK pfHook);

/*******************************************************************************
*    Func Name: TCPIP_SetDHCP4RTaskScheduleTime
* Date Created: 2014-05-21
*       Author: likaikun213099
*  Description: ����DHCP4R�ĵ��ȿ��ؼ�����ʱ�����
*        Input: ULONG ulSwitch:
*               ULONG ulPacketProCount:
*               ULONG ulDR4DelayTime:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-21   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDHCP4RTaskScheduleTime(ULONG ulSwitch, ULONG ulPacketProCount,ULONG ulDR4DelayTime);

/*******************************************************************************
*    Func Name: TCPIP_GetDHCP4RTaskScheduleTime
* Date Created: 2014-06-7
*       Author: fengjing209023
*  Description: ��ȡDHCP4R�ĵ��ȿ��ؼ�����ʱ�����
*       Output: ULONG *pulSwitch: ����
*               ULONG *pulPacketProCount:ÿ�δ����ĸ���
*               ULONG *pulDR4DelayTime:�����ӳ�ʱ��
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-06-7   fengjing209023          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDHCP4RTaskScheduleTime(ULONG *pulSwitch, ULONG *pulPacketProCount,ULONG *pulDR4DelayTime);

#ifdef __cplusplus
}
#endif      /* end of _cplusplus        */

#endif      /* end of _DHCP4R_API_H_    */

