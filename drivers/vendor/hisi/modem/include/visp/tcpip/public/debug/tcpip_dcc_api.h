/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_pcap_api.h
*
*  Project Code: VISPV1R8C01
*   Module Name: DCC Debug
*  Date Created: 2009-04-11
*        Author: zhangchunyu62474
*   Description: DCC ����ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-04-11   zhangchunyu62474          Create
*
*******************************************************************************/
#ifndef __TCPIP_DCC_API_H__
#define __TCPIP_DCC_API_H__

#ifdef __cplusplus
extern "C"{
#endif

#define MAX_VRFNAME_LEN    47
#define MAX_INTFNAME_LEN   31

#define DCC_TCP            6         
#define DCC_UDP            17

/* ������ͨ��DCC�û��������ݽṹ */
typedef struct tagDccInfo
{
    ULONG   ulSipAddr;                               /* Դ��ַ,������ */
    ULONG   ulDipAddr;                               /* Ŀ�ĵ�ַ,������ */
    USHORT  usSport;                                 /* Դ�˿ں� */
    USHORT  usDport;                                 /* Ŀ�Ķ˿ں� */
    ULONG   ulSocketID;                              /* Socket ID*/
    ULONG   ulTaskID;                                /* Socket��������,����ȫ��socket���Բ�ָ�� */
    ULONG   ulProType;                               /* Э������ */
    CHAR    ucVrfName[MAX_VRFNAME_LEN+1];            /* ʵ������ */
    CHAR    ucIntfName[MAX_INTFNAME_LEN+1];          /* �ӿ��� */
}TCPIP_DCC_S;

/* ������ͨ��DCC����ֵ */
typedef enum enumDccErrCode
{
    DCC_SUCCESS = VOS_OK,           /* 0, �ɹ�*/
    DCC_FAILED,                     /* 1, ʧ��*/
    DCC_ERR_NULLPOINT,              /* 2, �û�����ָ��Ϊ�� */
    DCC_ERR_GETCOMVTBL,             /* 3, ��ȡ���ʧ�� */
    DCC_ERR_IPALL,                  /* 4, ָֻ��Դ��Ŀ��IP,ԴIP��Ŀ��IP���붼ָ�� */
    DCC_ERR_WRITEQUE,               /* 5, д����ʧ��,�������� */
    DCC_ERR_NOVRF,                  /* 6, VRF������*/
    DCC_ERR_NOINTF,                 /* 7,�ӿڲ����� */
    DCC_ERR_INIT,                   /* 8,DCC��ʼ��ʧ�� */
    DCC_ERR_SIP,                    /* 9,Դ��ַ���Ϸ� */
    DCC_ERR_DIP,                    /* 10,Ŀ�ĵ�ַ���Ϸ� */
    DCC_ERR_DIPISLOC,               /* 11,Ŀ�ĵ�ַ�����Ǳ�����ַ */
    DCC_ERR_SIPNOTLOC,              /* 12,Դ��ַ���Ǳ�����ַ */
    DCC_ERR_INTFTYPR,               /* 13,��֧�ֽӿ�����,ֻ֧��PPP ETH MP */
    DCC_ERR_RUNNING,                /* 14,DCC������������ */
    DCC_ERR_CREATETIMER,            /* 15,������ʱ��ʧ��*/
    DCC_ERR_CREATETASK,             /* 16,����DCC����ʧ��*/
    DCC_ERR_CREATEQUE,              /* 17,����DCC QUE����ʧ��*/
    DCC_ERR_NORUNNING,              /* 18,û��DCC���������� */
    DCC_ERR_TASKPRI,                /* 19,DCC�������ȼ�����255 */
    DCC_ERR_L2TYPR,                 /* 20,��֧�ֶ���ETH�ӿ� */
    DCC_ERR_TRUNKPORT,              /* 21,��֧��TRUNK��Ա�Ӷ˿� */
    DCC_ERR_DATATIME,               /* 22,����ͳ��ʱ�����600 */
    DCC_ERR_EXECID,                 /* 23,�û�ִ��ID����Ϊ0 */
    DCC_ERR_NOSUCHEXECID,           /* 24,���������ִ��ID��DCC */
    DCC_ERR_ISHEALTHCHECK,          /* 25,DCC�������ڲ�������� */
    DCC_ERR_3DVIRTUALINTF,          /* 26,��֧��3ά��ӿڼ�� */
    
    DCC_ERR_MAX,                    /*����ֵ */
}TCPIP_DCC_ERR_CODE_E;

/* ������� */
typedef enum enumDiagnoseTypeID
{
    DCC_DIAGNOSE_NA = 0,               /* 0 �޴��������������Ϣ */
    DCC_START,                         /* 1 DCC��Ͽ�ʼ�ֶ� */
    DCC_END,                           /* 2 DCC��Ͻ������ */
    
    DCC_DIAGNOSE_PHYDOWN,              /* 3 �ײ�״̬��Down */
    DCC_DIAGNOSE_NOARP,                /* 4 ARPѧϰ���ɹ� */
    DCC_DIAGNOSE_ETHLINEDOWN,          /* 5 ETH�ӿ�Э��DOWN */
    DCC_DIAGNOSE_LCPDOWN,              /* 6 LCP����OPEN״̬ */
    DCC_DIAGNOSE_IPCPDOWN,             /* 7 IPCP����OPEN״̬ */
    DCC_DIAGNOSE_NOFIB,                /* 8·�ɲ��Ҳ��ɹ� */
    DCC_DIAGNOSE_TRUNKLINEDOWN,        /* 9 TRUNK�ӿ�Э��״̬����UP */
    DCC_DIAGNOSE_INNERERR,             /* 10 �ڲ��쳣 */    
    DCC_DIAGNOSE_TCP_NOINPCB,          /* 11 INPCB������ */
    DCC_DIAGNOSE_TCP_NOTCPCB,          /* 12 TCPCB������ */
    DCC_DIAGNOSE_TCP_NOSOCKETCB,       /* 13 SOCKETCB������ */
    DCC_DIAGNOSE_NOSOCKET,             /* 14 ����socket id�Ҳ���socket,���߸�socket�������û�ָ���Ĳ�ƥ�� */
    DCC_DIAGNOSE_NONTCP_NOSOCKETCB,    /* 15 ��TCP SOCKET���ƿ鲻����,�ڲ��쳣 */
    DCC_DIAGNOSE_CREATEDCCDATATIME,    /* 16 ����DCC����ͳ�ƶ�ʱ��ʧ�� */
    DCC_DIAGNOSE_MISMATCHPROTOTYPE,    /* 17 �û�����ͼ�鵽��Э�����Ͳ�һ�� */
    DCC_DIAGNOSE_DELETE_INTF,          /* 18 ��Ϲ���ʱ,�ӿڱ�ɾ�� */
    
    DCC_DIAGNOSE_MAX,                  /*  ����������ֵ */
    
}TCPIP_DCC_DIAGNOSEINFO_TYPE_E;


/*******************************************************************************
*    Func Name: TCPIP_DCC
* Date Created: 2009-3-26
*       Author: zhangchunyu(62474)
*  Description: ������ͨ�Լ���û��ӿ�
*        Input: ULONG ulExecID: �û�ִ��ID,�������᷵�ظ��û�
*               ULONG ulTaskPri:DCC�������ȼ�,0��ʾ��sock�������ȼ�һ��
*               ULONG ulDataStatTime: ����ͳ��ʱ��,��λs,�����0,��ʾĬ��30s
*               TCPIP_DCC_S *pstDcc: �û�����������ͨ�Բ���
*       Output: 
*       Return: DCC_SUCCESS:�ɹ�, ����:ʧ��
*      Caution: ������ͨ�Լ�����������������ͳ��
*               ���������Ҫ������������VISP�ܷ�����,����MAC PING��IP PING,
*                   ������������ռ��20s.
*               ����ͳ���ڽ������֮��,ͳ��ʱ�����û�ָ��,��ʱ�䵽,����ͳ����Ϣ
*                   �������������Э��ջ����ͳ����Ϣ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-3-26    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DCC(ULONG ulExecID, ULONG ulTaskPri, ULONG ulDataStatTime, TCPIP_DCC_S *pstDcc);

/*******************************************************************************
*    Func Name: TCPIP_StopDCC
* Date Created: 2009-3-27
*       Author: zhangchunyu(62474)
*  Description: ȡ������������ͨ�Լ��
*        Input: ULONG ulExecID: 
*       Output: 
*       Return: DCC_SUCCESS �ɹ�;DCC_FAILED û��������������ͨ̽��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-3-27    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_StopDCC(ULONG ulExecID);
/*******************************************************************************
*    Func Name: TCPIP_ShowDCCCfgInfo
* Date Created: 2009-4-22
*       Author: zhangchunyu(62474)
*  Description: ��ʾDCC����������õ������Ϣ
*        Input: ULONG ulExecID: �û�ִ��ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-4-22    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowDCCCfgInfo(ULONG ulExecID);

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif /* __TCPIP_PCAP_API_H__ */


