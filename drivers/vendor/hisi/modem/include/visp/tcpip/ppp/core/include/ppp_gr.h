/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ppp_gr.h
*
*  Project Code: VISPV100R006C02
*   Module Name: PPP GR
*  Date Created: 2008-08-15
*        Author: zhangchunyu
*   Description: PPPģ�鱣��ָ�ģ��ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-08-15  zhangchunyu        Create

*******************************************************************************/

#ifndef _PPP_GR_H_
#define _PPP_GR_H_

#ifdef  __cplusplus
extern "C"{
#endif
#include "tcpip/public/tcpip_gr.h"

enum enumPppGRERR
{
    GR_SUCCESS,                                            /* 0 �ָ��ɹ� */ 
    GR_FAIL,                                               /* 1 ʧ�� */
    GR_ERR_NOT_PPP_COM,                                    /* 2 û��ע��PPP��� */
    GR_ERR_NULL_POINT,                                     /* 3 ָ��Ϊ�� */
    GR_ERR_NORMOL_REBOOT,                                  /* 4 ����������ʽ���������ƽ������ */
    GR_ERR_WRITE_QUE,                                      /* 5 д����ʧ�� */
    GR_ERR_OPEN_IFENTRY,                                   /* 6 ��IFNET ����ʧ�� */
    GR_ERR_GETNP_LCP,                                      /* 7 ��NP��ȡLCP��Ϣʧ�� */
    GR_ERR_GETNP_IPCP,                                     /* 8 ��NP��ȡIPCP��Ϣʧ�� */
    GR_ERR_MEM_MALLOC,                                     /* 9 �����ڴ�ʧ�� */
    GR_ERR_MP_CONF_NP,                                     /* 10 ���ú�NP�õ�����Ϣ��һ�� */
    GR_ERR_CHECK_NP_LCP,                                   /* 11 ��NP��ȡLCP��Ϣ���� */
    GR_ERR_CHECK_NP_IPCP,                                  /* 12 ��NP��ȡIPCP��Ϣ���� */
    GR_ERR_NULL_CB,                                        /* 13 ���ƿ�Ϊ��, �ڲ����ƿ�,Ϊ��PC-Lint�澯 */
    GR_ERR_LCP_NOT_OPEN,                                   /* 14 IPCP�ָ�, LCP����OPEN״̬ */
    GR_ERR_LCP_NULL_CB,                                    /* 15 IPCP�ָ�, LCP���ƿ�ΪNULL */
    GR_ERR_IPCP_MP_LOW,                                    /* 16 MP�ָ�IPCP�ָ�ǰΪOPEN,�ָ���������ֵ�������� */
    GR_ERR_IP_ALLF,                                        /* 17 �ӿڵ�ַΪȫ1 */
    GR_ERR_CHECK_LCP_MRU,                                  /* 18 MRU���Ϸ� */
    GR_ERR_CHECK_LCP_MRRU,                                 /* 19 MRRU���Ϸ� */
    GR_ERR_CHECK_LCP_NEGMP,                                /* 20 һ��Э��MP,��һ�˲�Э��MP */
    GR_ERR_CHECK_GOTNP_NOMHF,                              /* 21 ��ʶ�𱾶�MHFЭ�̵�codeֵ */
    GR_ERR_CHECK_GOTNP_MHF_LCLASS,                         /* 22 ����MHFЭ�̵� Length class�Ƿ�*/
    GR_ERR_CHECK_GOTNP_MHF_SCLASS,                         /* 23 ����MHFЭ�̵� Short class�Ƿ�*/
    GR_ERR_CHECK_HISNP_NOMHF,                              /* 24 ��ʶ��Զ�MHFЭ�̵�codeֵ */
    GR_ERR_CHECK_HISNP_MHF_LCLASS,                         /* 25 �Զ�MHFЭ�̵� Length class�Ƿ�*/
    GR_ERR_CHECK_HISNP_MHF_SCLASS,                         /* 26 �Զ�MHFЭ�̵� Short class�Ƿ�*/
    GR_ERR_CHECK_LCP_DISCRCLASS,                           /* 27 Discr class�Ƿ� */
    GR_ERR_CHECK_LCP_MHFSSNHF,                             /* 28 MHF��SSNHF��ͻ */
    GR_ERR_CHECK_LCP_MAGICNUM,                             /* 29 ���˺ͶԶ�ħ������ͬ */
    GR_ERR_CHECK_LCP_DISCRLEN,                             /* 30 Discr Len�Ƿ�*/
    GR_ERR_CHECK_IPCP_NOT_ADDR,                            /* 31 ������ַ�͵ײ��ȡ�ĵ�ַ����ͬ */
    GR_ERR_CHECK_IPCP_ADDR,                                /* 32 ���˺ͶԶ˵�Э�̵��ı˴˵�ַ��һ�� */
    GR_ERR_MP_ED_NULL,                                     /* 33 �ӽӿڻָ�ʱ, MP�ӿ��ն���������0*/
    GR_ERR_ED_MISMATCH,                                    /* 34 PPP�ӿ�LCP�ָ�Got Opetion�ն���������MP�ӿڵ��ն���������һ��*/
    GR_ERR_NOT_REGISTERPPI,                                /* 35 û��ע��PPP NP�·���ȡ���Ӻ��� */
    GR_ERR_GETNP_OSICP,                                    /* 36 ��NP��ȡOSICP��Ϣʧ�� */
    GR_ERR_OSICP_DISABLE,                                  /* 37 �ӿ���ȥʹ��OSICP */
    GR_ERR_CHECK_NP_OSICP,                                 /* 38 ��NP��ȡOSICP��Ϣ���� */

    GR_ERR_MAX,                                            /*  �ָ��������ֵ */    
};

/* ����ģʽ */
#define PPP_NORMAL_REBOOT        MODE_NORMAL
#define PPP_KEEPALIVE_REBOOT     MODE_KEEPALIVE

#define PPP_GET_PPI_LCPOPTION    1
#define PPP_GET_PPI_IPCPOPTION   2
#define PPP_GET_PPI_OSICPOPTION  3

#define PPP_GR_SMOOTH_LCPOPTION     1
#define PPP_GR_SMOOTH_IPCPOPTION    2
#define PPP_GR_SMOOTH_OSICPOPTION   3

#define PPP_GR_DEBUG_ON    1
#define PPP_GR_DEBUG_OFF   0

#define PPP_RESTORE_SUCCESS 0
#define PPP_RESTORE_FAIL    1


/* PTN��Ʒû������ǰ׺ʡ��,�����ݲ��ָ�ǰ׺ʡ�� */
#define PPP_RESTORE_LCPOPTION_FROM_PPI(pstLcpOption, pstPpiInfo)\
{\
    VOS_DBGASSERT(PPI_MC_PREFIX_MAX_NUM >= MC_PREFIXE_MAX_NUM);\
    VOS_DBGASSERT(PPI_MC_PREFIX_MAX_LEN >= MC_PREFIXE_MAX_STR);\
    (pstLcpOption)->neg_discr = (pstPpiInfo)->neg_discr;\
    (pstLcpOption)->neg_magicnumber = (pstPpiInfo)->neg_magicnumber;\
    (pstLcpOption)->neg_prefixE = (pstPpiInfo)->neg_prefix;\
    (pstLcpOption)->neg_mhf = (pstPpiInfo)->neg_mhf;\
    (pstLcpOption)->neg_ssnhf = (pstPpiInfo)->neg_ssnhf;\
    (pstLcpOption)->neg_mrru = (pstPpiInfo)->neg_mrru;\
    (pstLcpOption)->neg_mru = (pstPpiInfo)->neg_mru;\
    (pstLcpOption)->neg_asyncmap = (pstPpiInfo)->neg_asyncmap;\
    (pstLcpOption)->neg_accompression = (pstPpiInfo)->neg_accompression;\
    (pstLcpOption)->neg_pcompression = (pstPpiInfo)->neg_pcompression;\
    (pstLcpOption)->mru = (pstPpiInfo)->usMru;\
    (pstLcpOption)->mrru = (pstPpiInfo)->usMrru;\
    (pstLcpOption)->asyncmap = (pstPpiInfo)->ulAsyncmap;\
    (pstLcpOption)->ucMhfCode = (pstPpiInfo)->ucCode;\
    (pstLcpOption)->ucMhfClass = (pstPpiInfo)->ucClass;\
    if(pstPpiInfo->neg_mrru)\
    {\
        (pstLcpOption)->discr_len = (pstPpiInfo)->ucDiscr_len;\
        (pstLcpOption)->discr_class = (pstPpiInfo)->ucDiscr_class;\
        (VOID)TCPIP_Mem_Copy((pstLcpOption)->discr_addr, PPP_MP_DISCR_MAX_LENGTH, \
               (pstPpiInfo)->discr_addr, PPP_MP_DISCR_MAX_LENGTH);\
    }\
    (pstLcpOption)->magicnumber = (pstPpiInfo)->ulMagicnumber;\
}

/* Ŀǰû���õ�ѹ�������Բ��ָ�ѹ�� */
#define PPP_RESTORE_IPCPOPTION_FROM_PPI(pstIpcpOption,pstPpiInfo)\
{\
     (pstIpcpOption)->neg_vj  = (pstPpiInfo)->neg_vj;\
     (pstIpcpOption)->neg_iphc = (pstPpiInfo)->neg_iphc;\
     (pstIpcpOption)->ouraddr = VOS_NTOHL((pstPpiInfo)->ulOurAddr);\
     (pstIpcpOption)->hisaddr = VOS_NTOHL((pstPpiInfo)->ulHisAddr);\
}

#define PPP_GET_NPINFO_FROM_PPI(pstIf, pstOption, ulPpiMsgType, optionType, ulPpiRet)\
{\
    (VOID)TCPIP_Mem_Set(pstOption, 0, sizeof(optionType));\
    ulPpiRet = g_pfTCPIP_PPI_PPP_Update(pstIf->if_ulIfIndex, ulPpiMsgType, pstOption);\
    TCPIP_PPI_LogPppMsg(ulPpiRet, pstIf, ulPpiMsgType, pstOption);\
}

#define PPP_RESTORE_OSICPOPTION_FROM_PPI(pstOsicpOption,pstPpiInfo)\
{\
     (pstOsicpOption)->neg_Align_NPDU  = (pstPpiInfo)->neg_Align_NPDU;\
     (pstOsicpOption)->ucAlign_NPDU = (pstPpiInfo)->ucAlign_NPDU;\
}

extern ULONG g_ulPPPRebootMode; 

VOID PPP_GR_DealMsg(UINTPTR aulMsg[4]);
ULONG PPP_GR_Smooth(VOID);
ULONG PPP_GR_Restore(VOID);

ULONG PPP_GR_RestoreByCase(IFNET_S *pstIf, PPPINFO_S *pstPppInfo, ULONG ulCaseType);
ULONG PPP_GR_SmoothByCase(IFNET_S *pstIf, ULONG ulCaseType);
ULONG PPP_LCPSmooth(IFNET_S *pstIfnet);
ULONG PPP_IPCPSmooth(IFNET_S *pstIfnet);
struct tagNpPppOsicpOption;
ULONG PPP_OSICPRestore(IFNET_S *pstIfnet, struct tagNpPppOsicpOption *pstNPGotOsicpOption,
    struct tagNpPppOsicpOption *pstNPHisOsicpOption);
ULONG PPP_OSICPSmooth(IFNET_S *pstIfnet);
ULONG PPP_LCPRestore(IFNET_S *pstIfnet, 
                     struct tagNpPppLcpOption *pstNPGotLcpInfo, 
                     struct tagNpPppLcpOption *pstNPHisLcpInfo);
ULONG PPP_IPCPRestore(IFNET_S *pstIfnet, 
                      struct tagNpPppIpcpOption *pstNPGotIpcpOption,
                      struct tagNpPppIpcpOption *pstNPHisIpcpOption);
ULONG PPP_CBRestore(PPPINFO_S *pstPPPInfo, ULONG ulPhyStauts);
ULONG PPP_CheckPpiPara(IFNET_S * pstIfNet, VOID * pstPpiGotInfo, VOID * pstPpiHisInfo,ULONG ulPppType);
ULONG PPP_GetNPInfo(IFNET_S *pstIf, ULONG ulCmd, VOID *pstPPIGotOption, VOID *pstPPIHisOption);
ULONG PPP_GR_GetMPDisc(IFNET_S *pstIfnet, UCHAR *pucDiscr_addr);
ULONG GR_SetDebug(ULONG ulDebugSwitch);
ULONG GR_GetDebug(ULONG *pulDebugSwitch);

/*******************************************************************************
*    Func Name: TCPIP_PPP_GR_SetDebug
* Date Created: 2008-8-16
*       Author: zhangchunyu(62474)
*  Description: ����PPP GR���Կ���
*        Input: ULONG ulDebugSwitch: 1: �� 0: �ر� ����: ��Ч
*       Output: 
*       Return: GR_SUCCESS: �ɹ�, GR_FAIL: ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-8-16    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_PPP_GR_SetDebug(ULONG ulDebugSwitch);


/*******************************************************************************
*    Func Name: TCPIP_PPP_GR_GetDebug
* Date Created: 2008-8-16
*       Author: zhangchunyu(62474)
*  Description: ��ȡPPP GR���Կ���
*        Input: ULONG *pulDebugSwitch: �������, ���Կ���ֵ
*       Output: pulDebugSwitch���Կ���
*       Return: GR_SUCCESS: �ɹ�, GR_FAIL: ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-8-16    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_PPP_GR_GetDebug(ULONG *pulDebugSwitch);



#ifdef  __cplusplus
}
#endif
#endif


