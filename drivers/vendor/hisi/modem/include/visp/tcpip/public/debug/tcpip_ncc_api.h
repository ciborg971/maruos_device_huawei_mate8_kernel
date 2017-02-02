

#ifndef _TCPIP_NCC_API_H_
#define _TCPIP_NCC_API_H_

#ifdef  __cplusplus
extern "C"{
#endif

/*******************************�궨��*****************************************/



/*******************************ö�ٶ���***************************************/
/* NCC �����붨�� */
typedef enum enTCPIP_NCC_ERR_CODE
{
    NCC_OK = VOS_OK,                /* 0  OK                                */
    NCC_ERR,                        /* 1  ERR                               */
    NCC_ERR_EXECID_INVALID,         /* 2  NCC�û�ִ��ID���Ϸ�               */
    NCC_ERR_EXECID_NOTEXIST,        /* 3  NCC��ϲ�����                     */
    NCC_ERR_EXECID_INUSE,           /* 4  NCC�û�ִ��ID��ʹ��               */
    NCC_ERR_TYPE_INVALID,           /* 5  NCC������Ͳ��Ϸ�                 */
    NCC_ERR_TASKPRI_INVALID,        /* 6  NCC�������ȼ����Ϸ�               */
    NCC_ERR_POINT_NULL,             /* 7  ָ��ΪNULL                        */
    NCC_ERR_TIME_INVALID,           /* 8  NCC���ʱ�䲻�Ϸ�                 */
    NCC_ERR_IFNET_NULL,             /* 9  �ӿڲ�����                        */
    NCC_ERR_IFTYPE_INVALID,         /* 10 �ӿ����Ͳ��Ϸ�                    */
    NCC_ERR_ALREADY_START,          /* 11 ��NCC���������                   */
    NCC_ERR_CREATE_QUE,             /* 12 ����NCC��Ϣ��Ϣ����ʧ��           */
    NCC_ERR_CREATE_TIMER_QUE,       /* 13 ����NCC��ʱ����Ϣ����ʧ��         */
    NCC_ERR_CREATE_TIMER,           /* 14 ����NCC��ʱ��ʧ��                 */
    NCC_ERR_CREATE_TASK,            /* 15 ����NCC����ʧ��                   */
    NCC_ERR_IF_COMINIT,             /* 16 ��ȡIFNET���ʧ��                 */
    NCC_ERR_PPP_COMINIT,            /* 17 ��ȡPPP���ʧ��                   */
    NCC_ERR_PPP_MAX_NUM,            /* 18 PPP�������е������Ŀ�Ѵﵽ���ֵ */
    NCC_ERR_TIMEBASE_INVALID,       /* 19 ѭ����ʱ��ʱ�����ֵ���Ϸ�        */
    NCC_ERR_VIRTUAL_IFTYPE_INVALID, /* 20 �ӿ���������ά��ӿڲ��Ϸ�        */
    
    NCC_ERR_MAXCODE,                /* NCC���������ֵ,�Ժ���Ӵ������밴˳������ڴ�֮ǰ */
}TCPIP_NCC_ERR_CODE_E;

/* NCC����Э������������ */
typedef enum enTCPIP_NCC_TYPE
{
    NCC_TYPE_PPP = 0,               /* 0  PPPЭ������NCC���                */
    NCC_TYPE_3AH,                   /* 1  3AHЭ������NCC���                */
    NCC_TYPE_TRUNK,                 /* 2  TRUNKЭ������NCC���              */
    NCC_TYPE_TCP,                   /* 3  TCPЭ������NCC���                */
    NCC_TYPE_BFD,                   /* 4  BFDЭ������NCC���                */
    NCC_TYPE_DHCP,                  /* 5  DHCPЭ������NCC���               */
    NCC_TYPE_END,                   /* ���NCCЭ������ֵ,�Ժ�����Э���������ʱ�밴˳������ڴ�֮ǰ */
}TCPIP_NCC_TYPE_E;

/* NCC��������Ϣ����ID(��Ͻ������ID) */
typedef enum enTCPIP_NCC_DIAGNOSEINFO_TYPE
{
    NCC_INFO_RESULT_INFO = 0,           /* 0 ��Ϲ����еĲο���Ϣ���ID */

    NCC_INFO_TYPE_NCC_START,            /* 1 ��Ͽ�ʼ */
    NCC_INFO_TYPE_NCC_END,              /* 2 ����һ��NCC���:��NCC���������ɽ��������û�ֹͣ����� */
    NCC_INFO_TYPE_NCC_END_ALL,          /* 3 ��������NCC��ϱ�־:�û�ֹͣ�˵�ǰ������NCC��� */

    /* �����Ǹ�NCC���������Ͻ�����ԭ��,�����Ƿ���������Ͻ���ԭ��,��󶼻������ϵ���Ͻ�����־��� */
    NCC_INFO_RESULT_PPP_OK = 100,               /* PPP��Ͻ��ID */
    
    NCC_INFO_RESULT_PPP_NO_INTERFACE,           /* 101 PPP������Ͻӿڲ����� */
    NCC_INFO_RESULT_PPP_NO_PPPCTL,              /* 102 û�нӿڶ�Ӧ��PPP���ƿ� */
    NCC_INFO_RESULT_PPP_NO_CONFIG,              /* 103 û�нӿڶ�Ӧ��PPP���ÿ��ƿ� */
    NCC_INFO_RESULT_PPP_NO_USEDCONFIG,          /* 104 û�нӿڶ�Ӧ��PPP��Ч���ÿ��ƿ� */

    NCC_INFO_RESULT_PPP_SHUTDOWN,               /* 105 PPP������Ͻӿڱ�shutdown */

    NCC_INFO_RESULT_PPP_PHY_DOWN,               /* 106 PPP������Ͻӿ�����״̬DOWN */
    NCC_INFO_RESULT_PPP_MP_PHY_DOWN,            /* 107 PPP�������MP�ӿ�����״̬DOWN */    
    NCC_INFO_RESULT_PPP_PHY_UPDOWN_REPEAT,      /* 108 PPP������Ͻӿ�����״̬����UP/DOWN */
    NCC_INFO_RESULT_PPP_MP_PHY_UPDOWN_REPEAT,   /* 109 PPP�������MP�ӿ�����״̬����UP/DOWN */

    NCC_INFO_RESULT_PPP_LINE_UP,                /* 110 PPP������Ͻӿ�Э��״̬UP,�ӿ�״̬���� */

    NCC_INFO_RESULT_PPP_LCP_UP,                 /* 111 PPP�������LCP UP,MP�ӽӿ�״̬���� */
    NCC_INFO_RESULT_PPP_LCP_DOWN,               /* 112 PPP�������LCP DOWN */
    NCC_INFO_RESULT_PPP_LCP_UPDOWN_REPEAT,      /* 113 PPP�������LCP ����UP/DOWN */

    NCC_INFO_RESULT_PPP_IPCP_UP,                /* 114 PPP�������IPCP UP,�ӿ�״̬���� */
    NCC_INFO_RESULT_PPP_IPCP_DOWN,              /* 115 PPP�������IPCP DOWN */
    NCC_INFO_RESULT_PPP_IPCP_UPDOWN_REPEAT,     /* 116 PPP�������IPCP ����UP/DOWN */

    NCC_INFO_RESULT_PPP_LOCAL_NOBINDTOMP,       /* 117 ����δ����MP,�Զ��Ѽ���MP */
    NCC_INFO_RESULT_PPP_LOCAL_BINDTOMP_NORESET, /* 118 �����Ѽ���MP,����δ��Ч,�Զ��Ѽ���MP */
    NCC_INFO_RESULT_PPP_REMOTE_NOBINDTOMP,      /* 119 �Զ�δ����MP,�����Ѽ���MP */
    NCC_INFO_RESULT_PPP_LOCAL_NOBINDTOMP_NORESET,/* 120 �Զ�δ����MP,�������Ƴ�MP,����δ��Ч */

    NCC_INFO_RESULT_PPP_DISCR_NEG_FAIL,         /* 121 ����ϣ��Э���ն�������,�����ն�������Э��ʧ��,
                                                       Э�̽���������˶�Э���ն�������,���±���LCPЭ�̲��� */
    NCC_INFO_RESULT_PPP_DISCR_CONSISTENT_DADDR, /* 122 ���ӽӿ�Э�̵��ĶԶ˵��ն�����������MP���ӿڵĶ�
                                                       �˵��ն�������ֵ����ͬ */

    NCC_INFO_RESULT_PPP_MHF_PREFIX_CLASS_INVALID, /* 123 �Զ�������Э��ǰ׺ʡ��,���Ǳ������õ�ǰ׺ʡ�����ȼ����ڶ�
                                                         �˵�MHF���ȼ�����Э�̲���.(ԭ��:MHFѡ����Э�̵�class�ȼ���
                                                         �������ǰ׺ʡ����֧�ֵ����ȼ�) */

    NCC_INFO_RESULT_PPP_LCPNEG_NOPAP,                   /* 124 ����ʹ����PAP��֤,��Ϊ��֤��,����û��Э��ͨ��,
                                                               ���ܶԶ�û�������û�����pwd */
    NCC_INFO_RESULT_PPP_LCP_PAP_AUTH_FAIL_MALLOC_PAP,   /* 125 PAP��֤������,��ʼ��֤ʱ����PAP���ƿ�ʧ�� */
    NCC_INFO_RESULT_PPP_LCP_PAP_AUTH_SERVER_FAIL,       /* 126 PAP��֤������,��Ϊ��֤��Server��֤ʧ�� */
    NCC_INFO_RESULT_PPP_LCP_PAP_AUTH_CLIENT_FAIL,       /* 127 PAP��֤������,��Ϊ����֤��Client��֤ʧ�� */

    NCC_INFO_RESULT_PPP_PPP_LCPNEG_NOCHAP,              /* 128 ����ʹ����CHAP��֤,��Ϊ��֤��,����û��Э��ͨ��,
                                                               ���ܶԶ�û��������������pwd */
    NCC_INFO_RESULT_PPP_LCP_CHAP_AUTH_FAIL_MALLOC_CHAP, /* 129 CHAP��֤������,��ʼ��֤ʱ����CHAP���ƿ�ʧ�� */
    NCC_INFO_RESULT_PPP_LCP_CHAP_AUTH_SERVER_FAIL,      /* 130 CHAP��֤������,��Ϊ��֤��Server��֤ʧ�� */
    NCC_INFO_RESULT_PPP_LCP_CHAP_AUTH_CLIENT_FAIL,      /* 131 CHAP��֤������,��Ϊ����֤��Client��֤ʧ�� */
    

    NCC_INFO_RESULT_PPP_MP_NOUPTOLOWLIMIT,          /* 132 MP�󶨵�����·��δ�ﵽ�û�ָ������С�����δ����NCP��Э��*/
    NCC_INFO_RESULT_PPP_NOCONFIGIP,                 /* 133 �ӿ���δ���õ�ַ����IPCPЭ�̲��� */
    NCC_INFO_RESULT_PPP_IPCPNEG_GOTIP_ZERO,         /* 134 ��������ΪЭ�̻�ȡ��ַ,����Э�̻�õĵ�ַΪ0 */
    NCC_INFO_RESULT_PPP_IPCPNEG_GOTIP_INVALID,      /* 135 ��������ΪЭ�̻�ȡ��ַ,����Э�̻�õĵ�ַ�Ƿ�(��ЧIP) */
    NCC_INFO_RESULT_PPP_IPCPNEG_HISIP_INVALID,      /* 136 �Զ�����ΪЭ�̻�ȡ��ַ,���ǶԶ�Э�̻�õĵ�ַ�Ƿ�(��ЧIP)*/
    NCC_INFO_RESULT_PPP_IPCPNEG_IPCONFLICT_LOCALSAME,/* 137 ��������ΪЭ�̻�ȡ��ַ,����Э�̻�õĵ�ַ�뱾������IP��ͬ
                                                            (��ͻ) */
    NCC_INFO_RESULT_PPP_IPCPNEG_IPCONFLICT_PEERSAME, /* 138 ��������ΪЭ�̻�ȡ��ַ,����Э�̻�õ�����IP��ͬ(��ͻ),
                                                            �������˶�����IP����IP��ͻ*/
    NCC_INFO_RESULT_PPP_IPCPNEG_GOTIPMODE_CONFLIT,  /* 139 ���������Լ���IP,���Զ���Ȼ�����˷���IP���³�ͻ */
    NCC_INFO_RESULT_PPP_IPCPNEG_HISIPMODE_CONFLIT,  /* 140 �Զ������Լ���IP,��������Ȼ���Զ˷���IP���³�ͻ */

    NCC_INFO_RESULT_PPP_IPCPNEG_IPHCINIT_FAIL,      /* 141 IPHCģ���ʼ��ʧ�ܵ���IPCPЭ��ʧ�� */  

    NCC_INFO_RESULT_PPP_RCV_NO_NEGPKT,   /* 142 �����з�������,����û���յ��Զ˵��κ�����,����Ϊ�ײ㲻ͨ,
                                                ���߶Զ�����Ϊ��Э��LCP/IPCP */
    NCC_INFO_RESULT_PPP_RCV_WRONG_PKTID, /* 143 �յ�ID��ƥ��ı���,���ܵ�ԭ��:�ײ����ͱ��Ĳ���ʱ,
                                                �ײ��շ�ʱ������PPP��·����,�ײ��յ�����ʱ���� */

    NCC_INFO_RESULT_PPP_NOT_CONSISTENT_MP, /*144, Inconsistencies in the Group and Member link parameters*/
    NCC_INFO_RESULT_PPP_RECEIVE_TR,                 /*145, Recived termination request caused the link to go down */
    NCC_INFO_RESULT_PPP_ECHO_TIMEOUT,           /*146, Echo packet timed out */
    NCC_INFO_RESULT_PPP_RECEIVE_CR,                 /*147, Recieved the Configuration request packet when the link is in open state and which resulted in link to go dwon.*/
    NCC_INFO_RESULT_PPP_IPCP_RECEIVE_TR,    /* 148, IPCP Recived termination request caused the link to go down */
    NCC_INFO_RESULT_PPP_IPCP_RECEIVE_CR,    /* 149, IPCP Recieved the Configuration request packet when the link is in open state and which resulted in link to go dwon.*/
  
    NCC_INFO_RESULT_PPP_NO_REASON = 299, /* 299 û����ϳ�����ԭ��,����ݱ��˺ͶԶ˵Ĳο���Ϣ���ж�λ */
    
    NCC_INFO_RESULT_3AH_OK = 300,             /* PPP��Ͻ��ID */
    
    NCC_INFO_RESULT_TRUNK_OK = 500,           /* PPP��Ͻ��ID */
    
    NCC_INFO_RESULT_TCP_OK = 700,             /* PPP��Ͻ��ID */
    
    NCC_INFO_RESULT_BFD_OK = 900,             /* PPP��Ͻ��ID */
    
    NCC_INFO_RESULT_DHCP_OK = 1100,           /* PPP��Ͻ��ID */
    
    NCC_INFO_RESULT_END = 1300,               /* ���NCC��Ͻ��ID,�Ժ�����NCC��������IDʱ�밴���ͺ�˳������ڴ�֮ǰ */
}TCPIP_NCC_DIAGNOSEINFO_TYPE_E;

/*******************************�ṹ���Ͷ���***********************************/



/*******************************ȫ�ֱ�������***********************************/

/*******************************************************************************
*    Func Name: TCPIP_NCC
* Date Created: 2009-04-13
*       Author: wangmingxia/wuhailan
*  Description: NCC��Ϲ�����������
*        Input: ULONG ulExecID:�û�ID,����Ϊ0,����Ҫ������NCC���Ψһ
*               ULONG ulTaskPri:�������ȼ�,����0��ʾʹ��Ĭ��ֵ(ͬSOCK�������ȼ�),ȡֵ��Χ[1,255]
*               ULONG ulDetectTime:Э�̼��ʱ��,����0��ʾʹ��Ĭ��ֵ30s,ȡֵ��Χ[10s,600s]
*               ULONG ulType:���õ�NCC�������,�μ�TCPIP_NCC_TYPE_Eö�ٶ���
*               VOID * pstPara:���������Ͷ�Ӧ�Ĳ���,��ǰPPPЭ�����Ͷ�Ӧ�Ĳ���ֵΪULONG�Ľӿ�����
*       Output: 
*       Return: �ɹ�VOS_OK,�������ش�����
*      Caution: ʵ����NCC��������ȼ�ʹ�õ��ǵ�һ������NCCʱ��������ȼ�,֮��������ȼ�ֵ��ʹ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   wangmingxia/wuhailan    Create
*
*******************************************************************************/
extern ULONG TCPIP_NCC(ULONG ulExecID, ULONG ulTaskPri, ULONG ulDetectTime, ULONG ulType, VOID * pstPara);

/*******************************************************************************
*    Func Name: TCPIP_StopNCC
* Date Created: 2009-04-13
*       Author: wangmingxia/wuhailan
*  Description: �����û�ID�ر���ϼ��,���ulExecIDΪ0,���ʾ�ر�����NCC��ϼ��
*        Input: ULONG ulExecID:�û�ID
*       Output: 
*       Return: �ɹ�VOS_OK,�������ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   wangmingxia/wuhailan    Create
*
*******************************************************************************/
extern ULONG TCPIP_StopNCC(ULONG ulExecID);

/*******************************************************************************
*    Func Name: TCPIP_ShowNCCCfgInfo
* Date Created: 2009-04-20
*       Author: wangmingxia/wuhailan
*  Description: �����û�ID��ʾNCC������Ϣ,���IDֵΪ0���ʾ��ʾ���е�ǰ��ϵ���Ϣ
*        Input: ULONG ulExecID:�û�ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-20   wangmingxia/wuhailan    Create
*
*******************************************************************************/
extern VOID TCPIP_ShowNCCCfgInfo(ULONG ulExecID);


#ifdef  __cplusplus 
}
#endif

#endif /* _TCPIP_NCC_API_H_ */


