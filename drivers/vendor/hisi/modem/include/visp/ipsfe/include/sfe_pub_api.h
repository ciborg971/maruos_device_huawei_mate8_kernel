/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_pub_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2009-8-31
*        Author: wuhailan
*   Description: �����湫��ģ����ض���API�ṹ����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-8-31    wuhailan         Create the first version.
*
*******************************************************************************/

#ifndef _SFE_PUB_API_H_
#define _SFE_PUB_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ������PUBģ������붨�� */
typedef enum enumSfePubErrCode
{
    SFE_PUB_OK = SFE_OK,                                /* �����ɹ� */
    SFE_PUB_ERR_BEGIN = SFE_PUB_BEGIN_RET_CODE,         /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_PUB_ERR_ACLFILTERHOOK_POINTNULL,                /* 1  ACL���˹���ע�ắ��ָ��Ϊ�� */
    SFE_PUB_ERR_FWDHOOK_POINTNULL,                      /* 2  FWD���͹���ע�ắ��ָ��Ϊ�� */
    SFE_PUB_SET_SRCIPADDR_VRF_ERR,                      /* 3  ����Src ip��VRF�Ƿ� */
    SFE_PUB_SRCIPADDR_SHARE_NULL,                       /* 4  ����Src ipȫ�ֱ���Ϊ��,��ʼ��û�гɹ���û�г�ʼ����� */
    SFE_PUB_GET_SRCIPADDR_SHARE_NULL,                   /* 5  ��ȡSrc ipȫ�ֱ���Ϊ��,��ʼ��û�гɹ���û�г�ʼ����� */
    SFE_PUB_GET_SRCIPADDR_VRF_ERR,                      /* 6  ��ȡSrc ipʱ��VRF�Ƿ� */
    SFE_PUB_GET_SRCIPADDR_NULL_POINT,                   /* 7  ��ȡSrc ipʱ������Ϊ�� */
    SFE_PUB_SHAREVAR_NULL_SET_ACLFAKEREASSSWITCH,       /* 8  ����ACL�����Ƿ���Ҫ��������м����鿪��ʱ,�������ָ��ΪNULL */
    SFE_PUB_SWITCH_INVALID_SET_ACLFAKEREASSSWITCH,      /* 9  ����ACL�����Ƿ���Ҫ��������м����鿪��ʱ,����ֵ�Ƿ� */
    SFE_PUB_SHAREVAR_NULL_GET_ACLFAKEREASSSWITCH,       /* 10 ��ȡACL�����Ƿ���Ҫ��������м����鿪��ʱ,�������ָ��ΪNULL */
    SFE_PUB_SWITCH_PONITERNULL_GET_ACLFAKEREASSSWITCH,  /* 11 ��ȡACL�����Ƿ���Ҫ��������м����鿪��ʱ,����ָ��ΪNULL */
    SFE_PUB_SHAREVAR_NULL_SET_AUTOFAKEREASSSWITCH,      /* 12 �����Զ������鿪��ʱ,�˼乲�����ΪNULL */

    SFE_PUB_ERR_CREATEBOX_FAIL,                         /* 13 ������ϻ��ʧ�� */
    SFE_PUB_ERR_SETBOXPARSE_FAIL,                       /* 14 ���ú�ϻ�ӽ�������ʧ�� */
    SFE_PUB_ERR_SETBOXRECORD_MANUALSTAT_FAIL,           /* 15 ���ü�¼�ֶ�ͳ����Ϣ����ϻ��ʧ�� */
    SFE_PUB_ERR_SETBOXRECORD_AUTOSTAT_FAIL,             /* 16 ���ü�¼�Զ�ͳ����Ϣ����ϻ��ʧ�� */
    SFE_PUB_ERR_SETBOXRECORD_MANUALSIZE_FAIL,           /* 17 ��ϻ��ʱ�ռ䲻�� */
    SFE_PUB_ERR_GETVLANIDHOOK_POINTNULL,                /* 18 ��ȡVLAN ID����ע�ắ��ָ��Ϊ�� */
    SFE_PUB_ERR_IPPKTPROCPOLICY_POINTNULL,              /* 19 ��ȡ���㱨�Ĵ�����Թ���ע�ắ��ָ��Ϊ�� */
    SFE_PUB_ERR_IPPKTPSNDINFO_POINTNULL,                /* 20 ��ȡ����IP���ĵĳ��ӿں�Ŀ��MAC����Ϣ����ע�ắ��ָ��Ϊ�� */
    SFE_PUB_ERR_PKTRCVUSERPREPROC_POINTNULL,            /* 21 �������û�̬���Ľ�����ڲ�ƷԤ������ע�ắ��ָ��Ϊ�� */
    SFE_PUB_ERR_PKTSNDUSERPREPROC_POINTNULL,            /* 22 �������û�̬���ķ�����ڲ�ƷԤ������ע�ắ��ָ��Ϊ�� */
    SFE_PUB_ERR_GETSOCKETID_POINTNULL,                  /* 23 �������û�̬���ݲ�Ʒ����ID�ͱ����������������Ʒ��ȡsocket id�ĺ�������ע�ắ��ָ��Ϊ�� */
    SFE_PUB_ERR_STATINFONOTIFY_POINTNULL,               /* 24 �������û�̬ע��ͳ����Ϣ֪ͨ����ע�ắ��ָ��Ϊ�� */

    SFE_PUB_ERR_INPUT_POINTNULL_NAKESENDPKT,            /* 25 �����û�ָ����Ϣֱ�ӷ���MUBFʱ�����MBUFָ��Ϊ�� */
    SFE_PUB_ERR_INPUT_IFID_NULL_NAKESENDPKT,            /* 26 �����û�ָ����Ϣֱ�ӷ���MUBFʱ�����IFIDָ��Ϊ�� */
    SFE_PUB_ERR_SEND_FAILED_NAKESENDPKT,                /* 27 �����û�ָ����Ϣֱ�ӷ���MUBFʱ������Ϣʧ�� */
    SFE_PUB_ERR_CALL_NAKESENDPKT_BEFORE_INIT,           /* 28 ��ϵͳ��ʼ��֮ǰ���ö���API */

}SFE_PUB_ERR_CODE_E;

/* IPFWDģ������� */
typedef enum enumSfeIPFwdRetCode
{
    SFE_IPFWD_OK = SFE_OK,
    SFE_IPFWD_ERR_BEGIN = SFE_IPFWD_BEGIN_RET_CODE, /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_IPFWD_MALLOC_IPID_ERR,                      /* 1 ����IPIDȫ�ֱ���ʧ�� */
    SFE_IPFWD_MALLOC_ROUTEID_ERR,                   /* 2 ����Src ipȫ�ֱ���ʧ�� */
    SFE_IPFWD_MALLOC_FAIL_AUTOFAKEREASS,            /* 3 �����Զ������鿪�غ˼乲���ڴ�ʧ�� */
    SFE_IPFWD_MALLOC_FAIL_ACLNEEDFAKEREASS,         /* 4 ����ACL�����Ƿ���Ҫ��������м����鿪�غ˼乲���ڴ�ʧ�� */
    SFE_IPFWD_GETSENDIFO_FAIL,                      /* 5 ���Ĳ�ת�����ͱ���ʱ���Ʒ��ȡ���ķ�����Ϣʧ�� */
    SFE_IPFWD_GETIFIFO_FAIL,                        /* 6 ���Ĳ�ת������ʱ�������Ʒ��ȡ�Ľӿ�ID��ȡ�ӿ���Ϣʧ�� */
    SFE_IPFWD_NO_GETSENDINFO_HOOK,                  /* 7 ��Ʒû��ע���ȡ���ķ�����Ϣ�Ĺ��Ӻ��� */
    SFE_IPFWD_MBUFBACKWARD_FAIL,                    /* 8 ���Ĳ�ת������ʱ,MBUFָ���λ����̫ͷʧ��*/
    SFE_IPFWD_SENDIPPKT_MTOD_FAIL,                  /* 9 ����IP���Ļ�ȡ��̫ͷʧ�� */
    SFE_IPFWD_PKTSND_USERPREPROC_FAIL,              /* 10 ����IP����ʱ��ƷԤ����ʧ�� */
    SFE_IPFWD_SENDTO_DRIVER_FAIL,                   /* 11 ���ͱ��ĵ��ײ�ʧ�� */
    SFE_IPFWD_GETIPHDR_FAIL,                        /* 12 ���ͱ���,��ȡMbuf��IPͷʧ�� */
    SFE_IPFWD_MBUFFRAG_FAIL,                        /* 13 ���ͱ���,�Ա��Ľ���IP��Ƭʧ�� */
    SFE_IPFWD_FRAG_NOT_ALLOWED,                     /* 14 ���ͱ���,IP������Ҫ��Ƭ,���Ƿ�Ƭ��־Ϊ�������Ƭ */
    SFE_IPFWD_MBUFBACKWARD_IPHDR_FAIL,              /* 15 ���ͱ���,MBUFָ��ָ��IPͷʧ�� */
    SFE_IPFWD_MBUFFORWARD_IPHDR_FAIL,               /* 16 ���ͱ���,MBUFָ������IPͷָ��IP��������ʧ�� */
    SFE_IPFWD_MTU_ERR,                              /* 17 ���ͱ���,MTU̫С */
    SFE_IPFWD_FRAG_FAIL,                            /* 18 ���ͱ���,��IP���Ľ��з�Ƭʧ�� */
    SFE_IPFWD_MBUF_BACKWARD_FAIL,                   /* 19 ���ͱ���,��Mbufͷ���ƫ��ʧ�� */
    SFE_IPFWD_FIRST_MBUF_CREATE_FAIL,               /* 20 ���ͱ���,��Mbuf��Ƭʱ������Ƭ��Mbufʧ�� */
    SFE_IPFWD_OTHER_MBUF_CREATE_FAIL,               /* 21 ���ͱ���,��Mbuf��Ƭʱ������Ƭ���Mbufʧ�� */
    SFE_IPFWD_MTU_LESS_THAN_IPHEADER_LENGTH,        /* 22 MTUС��IPͷ����,��Ƭʧ�� */
    SFE_IPFWD_MBUFFORWARD_FIRST_FRAG_FAIL,          /* 23 ���ͱ���,MBUFָ��������һƬָ��ڶ�ƬIP��������ʧ�� */
    SFE_IPFWD_MBUFFRAG_EITH_OLDMBUF_FAIL,           /* 24 ���ͱ���,��ԭʼ���Ľ���IP��Ƭʧ�� */

}SFE_IPFWD_ERR_CODE_E;

/* ACL������Ҫ��������м����鴦�� */
#define SFE_ACL_NEED_FAKEREASS_SWITCH_ON    1
/* ACL������Ҫ��������м����鴦�� */
#define SFE_ACL_NEED_FAKEREASS_SWITCH_OFF   0


/* ���Ӻ�������ֵ����˵��:
   ACL��ȫ���˹���ֻ�ܷ�����������ֵ:SFE_MBUF_NOTHANDLE��SFE_MBUF_REQUIREDROP;
   FWD���ر��Ĺ��˹��Ӻ�������ֵֻ�������¼���,������ֵ������������; */
#define SFE_MBUF_HAVEHANDLE     0     /* ��ʾMBUF�ѱ����Ӵ���,���ڸ÷���ֵVISP��ֱ�ӷ���UID_STATE_TOHW״̬���б��ķ��� */
#define SFE_MBUF_NOTHANDLE      1     /* ��ʾMBUFδ�����Ӵ���,VISP����������ԭ���������̽��б��Ĵ��� */
#define SFE_MBUF_REQUIREDROP    2     /* ��ʾMBUF��Ҫ�ͷ�,�����VISP��ֱ�ӷ���MCUP_UID_STATE_SFE_ERROR״̬���ͷű��� */

/* ACL���˹��� */
typedef UINT32 (*g_pfSfePktAclFilterHook)(SFE_MBUF_S * pstMbuf);
/*******************************************************************************
*    Func Name: SFE_RegFuncAclFilterHook
* Date Created: 2009-09-12
*       Author: wuhailan103194
*  Description: ACL��ȫ���˹���
*        Input: g_pfSfePktAclFilterHook pfRegFunc:����ָ��
*       Output: 
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-12   wuhailan103194          Create
*
*******************************************************************************/
extern UINT32 SFE_RegFuncAclFilterHook(g_pfSfePktAclFilterHook pfRegFunc);


typedef UINT32 (*g_pfSfeLocalPktHook)(SFE_MBUF_S *pstMbuf);

extern UINT32 SFE_RegFuncLocalPkt(g_pfSfeLocalPktHook pfRegFunc);


extern UINT32 SFE_SetAclNeedFakeReassSwitch(UINT32 u32Switch);


extern UINT32 SFE_GetAclNeedFakeReassSwitch(UINT32 *pu32Switch);


extern VOID SFE_ShowAclNeedFakeReassSwitch(VOID);

/*******************************************************************************
*    Func Name: SFE_BoxRecordShow
* Date Created: 2009-10-31
*       Author: wuhailan103194
*  Description: ������ʾ��ϻ���еļ�¼����ʾ��˳��Ϊ���򣬼�����ʾ���д�뵽��ϻ���еļ�¼��
*        Input: UINT32 u32Begin:�������ļ�¼����
*               UINT32 u32RecNum:��Ҫ��ʾ�ļ�¼������Ϊ0ʱ����ʾ��ʾ�����ϻ�ӵ����м�¼��
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-31   wuhailan103194          Create
*
*******************************************************************************/
extern VOID SFE_BoxRecordShow(UINT32 u32Begin, UINT32 u32RecNum);

/*******************************************************************************
*    Func Name: SFE_BoxRecordWrite
* Date Created: 2009-10-28
*       Author: wuhailan103194
*  Description: ���ϻ�Ӽ�¼��Ҫ��¼����Ϣ
*        Input: 
*       Output: 
*       Return: �ɹ�SFE_OK����������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-28   wuhailan103194          Create
*
*******************************************************************************/
extern UINT32 SFE_BoxRecordWrite(VOID);

/* g_pfSfePktRcvUserPreProcHook���Ӻ�������ֵ����˵��:
   ���Ӻ�������ֵֻ�������¼���,������ֵ������������; */
/* ������VISP����,VISP����������ԭ���������̽��б��Ĵ��� */
#define SFE_PKT_STACK_HANDLE     0
/* �����ɲ�Ʒ����,��Ʒ��Ҫ�����ͷű��� */
#define SFE_PKT_USER_HANDLE      1


typedef UINT32 (*g_pfSfePktRcvUserPreProcHook)(SFE_MBUF_S * pstMbuf, UINT32 *pu32RcvPolicy);


extern UINT32 SFE_RegFuncPktRcvUserPreProcHook(g_pfSfePktRcvUserPreProcHook pfRegFunc);


typedef UINT32 (*g_pfSfePktSndUserPreProcHook)(SFE_MBUF_S * pstMbuf);


extern UINT32 SFE_RegFuncPktSndUserPreProcHook(g_pfSfePktSndUserPreProcHook pfRegFunc);

/* IP���Ľ��մ������,��Ʒֻ�ܷ������¼��ֲ���ȡֵ */
typedef enum enumSfeIpPktRcvPolicy
{
    SFE_IPPKTRCV_POLICY_NORMAL = 0,                  /* VISP�����������̴���(��·�ɺ�ARP��������ת���ͱ��ؽ��մ���) */
    SFE_IPPKTRCV_POLICY_PROXY,                       /* VISP����͸�������� */
    SFE_IPPKTRCV_POLICY_REORDER,                     /* VISP�������Ŵ��� */
    SFE_IPPKTRCV_POLICY_LOCALRCV,                    /* VISPֱ�ӽ��б��ؽ��մ���(��:��ʾ����),������·�ɺ��ж��Ƿ��Ǳ������ձ��� */
    SFE_IPPKTRCV_POLICY_DROP,                        /* VISP�������Ĵ��� */
    SFE_IPPKTRCV_POLICY_MAX,                         /* �߽�ֵ,�Ƿ���Чֵ */
}SFE_IPPKTRCV_POLICY_E;
typedef UINT32 (*g_pfSfeIpPktRcvProcPolicyHook)(SFE_MBUF_S * pstMbuf);


extern UINT32 SFE_RegFuncIpPktRcvProcPolicyHook(g_pfSfeIpPktRcvProcPolicyHook pfRegFunc);


typedef UINT32 (*g_pfSfeGetIpPktSndInfoHook)(SFE_MBUF_S *pstMbuf, SFE_MBUF_IFID_S *pstIfId,
                                                   UINT8 *pu8DstMac, UINT32 *pu32VlanId);


extern UINT32 SFE_RegFuncGetIpPktSndInfoHook(g_pfSfeGetIpPktSndInfoHook pfRegFunc);

/* ͳ����Ϣ���� */
typedef enum enumSfeUserStatisticType
{
    SFE_USTAT_TYPE_UNCLASSIFY = 0,                    /* ����Ҫ��ע���͵�ͳ�� */
    SFE_USTAT_TYPE_DROP,                              /* Э��ջ�������Ľ��е�ͳ�� */
    SFE_USTAT_TYPE_SEND,                              /* Э��ջ�������ͽ��е�ͳ�� */
    SFE_USTAT_TYPE_FORWARD,                           /* Э��ջ��TCP��������ת����ͳ�� */
    SFE_USTAT_TYPE_RXMT,                              /* Э��ջ��������ʱ�ش���ͳ�� */
    SFE_USTAT_TYPE_MAX,                               /* ͳ�����ͱ߽���Чֵ */
}SFE_USER_STATISTIC_TYPE_E;

/* ͳ��ԭ�� */
typedef enum enumSfeUserStatisticReason
{
    SFE_USTAT_REASON_UNCLASSIFY = 0,                     /* 00����Ҫ��עԭ���ͳ�� */
    SFE_USTAT_REASON_DROP_PRODUCT_POLICY,                /* 01��������ͳ��,ԭ��:��ƷӦ�ö���,ͳһʹ�ø�ֵ,�ڲ�����ʹ�� */

    SFE_USTAT_REASON_DROP_TCP_HDRDATALEN_ERROR,          /* 02��������ͳ��,ԭ��:TCPͷ�м�¼�����ݳ��ȴ���,L7����ΪL3���� */
    SFE_USTAT_REASON_DROP_TCP_CHKSUM_ERROR,              /* 03��������ͳ��,ԭ��:TCPУ��ʹ��� */
    SFE_USTAT_REASON_DROP_TCP_FLAGS_ERROR,               /* 04��������ͳ��,ԭ��:TCP flags���� */
    SFE_USTAT_REASON_DROP_TCP_DATALEN_ERROR,             /* 05��������ͳ��,ԭ��:IP������С��mbuf�ܳ���,ɾ��mbufβ������ʧ�� */
    SFE_USTAT_REASON_DROP_TCP_REORDERESTABLISH_ERROR,    /* 06��������ͳ��,ԭ��:TCP���Ž���ʧ�� */
    SFE_USTAT_REASON_DROP_TCP_REORDERRST_ERROR,          /* 07��������ͳ��,ԭ��:TCP�����յ�RST���� */
    SFE_USTAT_REASON_DROP_TCP_REORDERFIN_ERROR,          /* 08��������ͳ��,ԭ��:TCP�����յ�FIN���� */
    SFE_USTAT_REASON_DROP_TCP_REORDERMBUFFORWARD_ERROR,  /* 09��������ͳ��,ԭ��:TCP����ǰ��MBUFʧ�� */
    SFE_USTAT_REASON_DROP_TCP_REORDERRCVSEQNUM_ERROR,    /* 10��������ͳ��,ԭ��:TCP�����յ�������Ŵ��� */
    SFE_USTAT_REASON_DROP_TCP_REORDEROVERWND_ERROR,      /* 11��������ͳ��,ԭ��:TCP�����յ��ı��ĳ������� */
    SFE_USTAT_REASON_DROP_TCP_REORDERMBUFBACKWARD_ERROR, /* 12��������ͳ��,ԭ��:TCP���ŷ��ͱ��ĺ���MBUFʧ�� */
    SFE_USTAT_REASON_DROP_TCP_REORDERREASSMBUFFWD_ERROR, /* 13��������ͳ��,ԭ��:TCP�������鷢�ͱ���ǰ��MBUFʧ�� */
    SFE_USTAT_REASON_DROP_TCP_SYNDATA,                   /* 14��������ͳ��,ԭ��:TCP����SYN�����ݽ��� */
    SFE_USTAT_REASON_DROP_TCP_REORDER_REASS_CACHE_FULL,  /* 15��������ͳ��,ԭ��:TCP�������������ظ������б��ĸ����������� */
    SFE_USTAT_REASON_DROP_TCP_MBUF_CONTINUOUS_ERROR,     /* 16��������ͳ��,ԭ��:��TCP����ʱ�����ж��DB��MBUF������ʧ��,L7����Ϊmbuf���� */
    SFE_USTAT_REASON_DROP_TCP_REORDER_INVALID_FIN,       /* 17��������ͳ��,ԭ��:TCP������Ч����FIN״̬�յ���FIN���С��������� */
    SFE_USTAT_REASON_DROP_TCP_REPTDATA,                  /* 18��������ͳ��,ԭ��:TCP�����в����ظ�����ɾ��(L3L7����Ϊ�����������ݳ���) */

    SFE_USTAT_REASON_DROP_UDP_HDRDATALEN_ERROR,          /* 19��������ͳ��,ԭ��:UDPͷ�м�¼�����ݳ��ȴ��� */
    SFE_USTAT_REASON_DROP_UDP_DATALEN_ERROR,             /* 20��������ͳ��,ԭ��:IP���ĳ���С��mbuf�ܳ���cut����ʧ�� */
    SFE_USTAT_REASON_DROP_UDP_CHKSUM_ERROR,              /* 21��������ͳ��,ԭ��:UDPУ��ʹ��� */
    SFE_USTAT_REASON_DROP_UDP_NEWSOCKNODE_ERROR,         /* 22��������ͳ��,ԭ��:UDP�����յ�ʱ����sock�ڵ���Դʧ�� */
    SFE_USTAT_REASON_DROP_UDP_SOCKCREATENOTIFY_ERROR,    /* 23��������ͳ��,ԭ��:UDP���Ŵ���sock�ڵ�֪ͨʧ�� */
    SFE_USTAT_REASON_DROP_UDP_SOCKNOFIND_ERROR,          /* 24��������ͳ��,ԭ��:UDP��׼ʱ����sock�ڵ�ʧ�� */
    SFE_USTAT_REASON_DROP_UDP_MBUFBACKWARD_ERROR,        /* 25��������ͳ��,ԭ��:UDP���ŷ��ͱ��ĺ���MBUFʧ�� */
    SFE_USTAT_REASON_DROP_UDP_FORWARD_ERROR,             /* 26��������ͳ��,ԭ��:UDPƫ�Ƶ�ͷ��ʧ�� */
    SFE_USTAT_REASON_DROP_UDP_MBUF_CONTINUOUS_ERROR,     /* 27��������ͳ��,ԭ��:��UDP����ʱ�����ж��DB��MBUF������ʧ��,L7����Ϊmbuf���� */

    SFE_USTAT_REASON_DROP_IP_REASSOFFSET_ERROR,          /* 28��������ͳ��,ԭ��:IP����ƫ��������,L7����ΪL3-IP�ײ��� */
    SFE_USTAT_REASON_DROP_IP_REASSPKTLEN_ERROR,          /* 29��������ͳ��,ԭ��:IP���鱨�ĳ��ȴ���,L7����ΪL3-IP�ײ��� */
    SFE_USTAT_REASON_DROP_IP_REASSLOCK_ERROR,            /* 30��������ͳ��,ԭ��:IP������ʧ��,L7����ΪL3-IP�ײ��� */
    SFE_USTAT_REASON_DROP_IP_REASSNODE_ERROR,            /* 31��������ͳ��,ԭ��:IP�����ȡHASH�ڵ�ʧ��,L7����ΪL3-IP�ײ��� */
    SFE_USTAT_REASON_DROP_IP_REASSMAXPKTNUM_ERROR,       /* 32��������ͳ��,ԭ��:IP����ﵽ����Ƭ��ʧ��,L7����ΪL3-IP�ײ��� */
    SFE_USTAT_REASON_DROP_IP_REASSPRENODECOVER_ERROR,    /* 33��������ͳ��,ԭ��:IP�����ظ�ǰ�汨��ʧ��,L7����ΪL3-IP�ײ��� */
    SFE_USTAT_REASON_DROP_IP_REASSFOLLOWNODECOVER_ERROR, /* 34��������ͳ��,ԭ��:IP�����ظ����汨��ʧ��,L7����ΪL3-IP�ײ��� */
    SFE_USTAT_REASON_DROP_IP_REASSHASH_TIMEOUT,          /* 35��������ͳ��,ԭ��:IP���鳬ʱ�ͷŶ���,L7����ΪL3-IP�ײ��� */
    SFE_USTAT_REASON_DROP_IP_GETSENDIFO_ERROR,           /* 36��������ͳ��,ԭ��:IPת���������Ʒ��ȡ���ķ��͵������Ϣʧ�� */
    SFE_USTAT_REASON_DROP_IP_GETIFIFO_ERROR,             /* 37��������ͳ��,ԭ��:IPת����ȡ���ͱ��Ľӿڿ��ƿ��ַʧ�� */
    SFE_USTAT_REASON_DROP_IP_GETIPHDR_ERROR,             /* 38��������ͳ��,ԭ��:IPת����ȡ���ͱ���IP����ͷʧ�� */
    SFE_USTAT_REASON_DROP_IP_TTL_ERROR,                  /* 39��������ͳ��,ԭ��:IPת������TTLֵ�ľ� */
    SFE_USTAT_REASON_DROP_IP_PKT_CHECK_ERROR,            /* 40��������ͳ��,ԭ��:IP���ձ��ļ��ʧ��,L3L7����Ϊmbuf�ܳ� */
    SFE_USTAT_REASON_DROP_IP_BROADCAST_PKT,              /* 41��������ͳ��,ԭ��:IP���չ㲥���ĵ�ǰ��������,L3L7����Ϊmbuf�ܳ� */
    SFE_USTAT_REASON_DROP_IP_MULTICAST_PKT,              /* 42��������ͳ��,ԭ��:IP���նಥ���ĵ�ǰ��������,L3L7����Ϊmbuf�ܳ� */
    SFE_USTAT_REASON_DROP_IP_NON_TCPUDP_PKT,             /* 43��������ͳ��,ԭ��:IP���ղ�֧�ַ�TCP/UDP�������Ŵ�����,L3L7����Ϊmbuf�ܳ� */
    SFE_USTAT_REASON_DROP_IP_POLICY_DROP_PKT,            /* 44��������ͳ��,ԭ��:IP���ղ�Ʒ���Թ��ӷ��ض�������,L3L7����Ϊmbuf�ܳ� */
    SFE_USTAT_REASON_DROP_IP_PKT_REASS_PREOVERLAP,       /* 45��������ͳ��,ԭ��:IP����ʱǰ�������ظ�,L3L7����Ϊ�����������ݳ��� */
    SFE_USTAT_REASON_DROP_IP_PKT_REASS_NXTOVERLAP,       /* 46��������ͳ��,ԭ��:IP����ʱ�������ظ�,L3L7����Ϊ�����������ݳ��� */
    SFE_USTAT_REASON_DROP_IP_MBUFBACKWARD_ERROR,         /* 47��������ͳ��,ԭ��:IP������ĺ���MBUFʧ�� */

    SFE_USTAT_REASON_DROP_SOCK_BUFFULL_ERROR,            /* 48��������ͳ��,ԭ��:socket��buf�� */
    SFE_USTAT_REASON_DROP_SOCK_CACHEPKT_ERROR,           /* 49��������ͳ��,ԭ��:socketɾ��ʱ�������ı��� */
    SFE_USTAT_REASON_DROP_SOCK_REASSPKT_ERROR,           /* 50��������ͳ��,ԭ��:socketɾ��ʱ��������еı��� */
    SFE_USTAT_REASON_DROP_SOCK_REASSCACHEPKT_ERROR,      /* 51��������ͳ��,ԭ��:socketɾ��ʱ���黺������еı��� */
    SFE_USTAT_REASON_DROP_SOCK_RCVCACHEPKT_ERROR,        /* 52��������ͳ��,ԭ��:socketɾ��ʱ���ջ������еı��� */
    SFE_USTAT_REASON_DROP_SOCK_SNDCACHEPKT_ERROR,        /* 53��������ͳ��,ԭ��:socketɾ��ʱ���ͻ������еı��� */

    SFE_USTAT_REASON_DROP_FASTPASS_NET_PKTCHK_ERR,       /* 54��������ͳ��,ԭ��:��ͨ��У��IP��ʧ��,L3L7����Ϊmbuf�ܳ� */
    SFE_USTAT_REASON_DROP_FASTPASS_NOT_PROC_BROADCAST,   /* 55��������ͳ��,ԭ��:��ͨ��������㲥��,L3L7����Ϊmbuf�ܳ� */
    SFE_USTAT_REASON_DROP_FASTPASS_NOT_PROC_MULTICAST,   /* 56��������ͳ��,ԭ��:��ͨ��������ಥ��,L3L7����Ϊmbuf�ܳ� */
    SFE_USTAT_REASON_DROP_FASTPASS_NON_TCPUDP_PKT,       /* 57��������ͳ��,ԭ��:��ͨ���������TCP��UDP����,L3L7����Ϊmbuf�ܳ� */
    SFE_USTAT_REASON_DROP_FASTPASS_POLICY_DROP_PKT,      /* 58��������ͳ��,ԭ��:��ͨ����ȡ����Ϊ�������ʱ,��������,L3L7����Ϊmbuf�ܳ� */
    SFE_USTAT_REASON_DROP_FASTPASS_NON_PROC_POLICY,      /* 59��������ͳ��,ԭ��:��ͨ����ȡ���Ĵ������ʧ��,L3L7����Ϊmbuf�ܳ� */

    SFE_USTAT_REASON_STACK_PROC_END,                     /* 60Э��ջֱ��ת���ı��� */

    SFE_USTAT_REASON_DROP_TCP_REORDER_REDIRECTION_RCV,               /* 61��������ͳ��,ԭ��:�����������ض���,�������б����ս� */
    SFE_USTAT_REASON_SEND_TCP_REORDER_REDIRECTION_AOXRXMT,           /* 62���ͱ���ͳ��,ԭ��:�����������ض���,�������ش�AOX���� */
    SFE_USTAT_REASON_SEND_TCP_REORDER_REDIRECTION_RST,               /* 63���ͱ���ͳ��,ԭ��:�����������ض���,�������������͵�RST���� */
    SFE_USTAT_REASON_DROP_IP_PKT_REASS_OTHERIPHD ,                   /* 64��������ͳ��,ԭ��:IP����ʱ��Ƭ���ĵ�IP�ײ�ֻ����һ��,L3L7����Ϊ������IP�ײ����� */
    SFE_USTAT_REASON_DROP_R2P_REASSPKT_ERROR,                        /* 65��������ͳ��,ԭ��:����ת͸�������ж������л��汨�� */
    SFE_USTAT_REASON_DROP_TCP_RDR_DUPPKT_BFR_POLICY_SURE,            /* 66��������ͳ��,ԭ��:����ģʽ��δ��ȷ�Ƿ�Ҫת͸������,�յ��ش����� */
    SFE_USTAT_REASON_DROP_UDP_SOCKMODE_NOTMATCH,                     /* 67��������ͳ��,ԭ��:UDP���Ż����ģʽ���յ��ı��Ĳ��Ժ�socket��ƥ�� */
    SFE_USTAT_REASON_DROP_TCP_RDR_SOCKMODE_NOTMATCH,                 /* 68��������ͳ��,ԭ��:TCP����ģʽ���յ��ı��Ĳ��Ժ�socket��ƥ�� */  
    SFE_USTAT_REASON_DROP_TCP_PROXY_NOTCPCB,                         /* 69��������ͳ��,ԭ��:������,TCP���ƿ�Ϊ��*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_POLICY_NOT_MATCH,                /* 70��������ͳ��,ԭ��:������,�յ����Բ�ƥ��ı���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_TCP_CLOSED,                      /* 71��������ͳ��,ԭ��:������,�û��ѹرգ����յ�����*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCV_NODATA_FIN,                  /* 72��������ͳ��,ԭ��:������,�յ��������ݵ�FIN����*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_OTHER_CONTROLPKT,                /* 73��������ͳ��,ԭ��:������,�ڽ�������ʱ�ս�����ݷ�FIN�Ŀ��Ʊ���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCV_PURE_ACK,                    /* 74��������ͳ��,ԭ��:������,�յ��Ϸ��Ĵ�ACK���� */    
    SFE_USTAT_REASON_DROP_TCP_PROXY_RECV_RETRAN_PKT,                 /* 75��������ͳ��,ԭ��:������,�յ��ش�����,L3L7����Ϊ�ش����ݳ���*/        
    SFE_USTAT_REASON_DROP_TCP_PROXY_RECV_OVERWINDOW_PKT,             /* 76��������ͳ��,ԭ��:������,�յ���������,L3L7����Ϊ�������ݳ��� */  
    SFE_USTAT_REASON_DROP_TCP_PROXY_REASS_RCV_HDR_COMPLETELY_DUP,    /* 77��������ͳ��,ԭ��:����ʱ,�յ�����ǰ���������������ȫ�ظ��ı���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_REASS_RCV_HDR_DUPPKT,            /* 78��������ͳ��,ԭ��:����ʱ,�յ�����ǰ��������������ظ�,L3L7����Ϊ�ظ����ݳ���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_REASS_RCV_TAIL_DUPPKT,           /* 79��������ͳ��,ԭ��:����ʱ,�յ����ĺ��������������ظ�,L3L7����Ϊ�ظ����ݳ��� */
    SFE_USTAT_REASON_DROP_TCP_PROXY_REASS_RCV_TAIL_COMPLETELY_DUP,   /* 80��������ͳ��,ԭ��:����ʱ,�յ����ĺ���������������ȫ�ظ��ı���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_REASS_CANTRCVMORE,               /* 81��������ͳ��,ԭ��:����ʱ,�ϲ�socket�޷��ٽ�������*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCV_DUPSYN_BUT_EXPECTSEQ,        /* 82��������ͳ��,ԭ��:������,�յ��ظ���SYN,�����Ϊ��������� */
    SFE_USTAT_REASON_SEND_HAVE_COMPLETELY_DUP_PKT,                   /* 83���ͱ���ͳ��,ԭ��:���ͱ���ʱ,������ȫ�ظ�����,L3L7����Ϊ�ش����ĳ��� */
    SFE_USTAT_REASON_SEND_HAVE_PART_DUP_PKT,                         /* 84���ͱ���ͳ��,ԭ��:���ͱ���ʱ,���ڲ����ظ�����,,L3L7����Ϊ�ش����� */
    SFE_USTAT_REASON_DROP_TCP_PROXY_RECV_OVERWINDOW_PKT_AT_RCVSYN,   /* 85��������ͳ��,ԭ��:�ڴ�������ݵ�SYN����ʱ,���ݴ��ڳ���,L3L7Ϊ�������ݳ��� */
    SFE_USTAT_REASON_DROP_TCP_PROXY_ESTABLISHED_RCVDUPSYN,           /* 86��������ͳ��,ԭ��:�����ӽ�����ɺ��յ�SYN����ֱ�ӻ�ACK����*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_DUPLICATE_RCVRST,                /* 87��������ͳ��,ԭ��:ֱ�Ӷ����ظ���RST����,��RST�����е����
                                                                               �ȵ�ǰ�������յ����С���ұ�����ȫ�ظ���ֱ�Ӷ�������*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_NOTEXPECT_PARTDUPLICATE_RCVRST,  /* 88��������ͳ��,ԭ��:�������ظ����ݵ�RST����,ֻҪRST���Ĳ��������Ľ������ֱ�ӻ�ACK����*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_ALREADY_CLOSE_RCVPKT,            /* 89��������ͳ��,ԭ��:�û��Ѿ�����������close�����ر�socket.
                                                                               ���˵ľͲ����ٽ���������,�����ʱ���յ��Զ˷���������������ֱ�ӻظ�RST�����*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_EXCEED_WINDOW_RCVPKT,            /* 90��������ͳ��,ԭ��:������ȫ�������մ��ڵı��Ļ�ӦACK��ֱ�Ӷ���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_EXCEED_WINDOW_RCVPKT_ESTABLISHED,/* 91��������ͳ��,ԭ��:���ӽ�����ɺ����ȫ�������մ��ڵı���ֱ�ӻ�ӦACK����*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_LISTEN_RCVRST,                   /* 92��������ͳ��,ԭ��:��LISTENʱ���յ�RST���ģ�ֱ�Ӷ���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_LISTEN_RCVACK,                   /* 93��������ͳ��,ԭ��:��LISTENʱ���յ�ACK���ģ���ֹ�ñ��ģ���RST*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_LISTEN_RCVNOTSYN,                /* 94��������ͳ��,ԭ��:��LISTENʱ���յ���SYN���ģ�ֱ�Ӷ���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_LISTEN_RCVDSTMULTICAST,          /* 95��������ͳ��,ԭ��:��LISTENʱ���յ�TCP���ӱ��ĵ�Ŀ�ĵ�ַ�����Ƕಥ��ַ�͹㲥��ַ*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_SYNSEND_RCVERRACK,               /* 96��������ͳ��,ԭ��:��SYNSENDʱ�����������������յ��Զ˵�SYN/ACKʱ,
                                                                               �յ������е�ACK��Ų��Ϸ����RST��������*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_SYNSEND_RCVRST,                  /* 97��������ͳ��,ԭ��:��SYNSENDʱ���յ�RST���ģ�ֱ�Ӷ���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_SYNSEND_RCVNOTSYN,               /* 98��������ͳ��,ԭ��:��SYNSENDʱ���յ���SYN���ģ�ֱ�Ӷ���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_NOTLISTEN_RCVNOTACK,             /* 99��������ͳ��,ԭ��:ֻ��LISTEN��SYN_SENT״̬�ı��Ŀ��Բ�Я��ACK,�����Ѿ������,
                                                                                ������յ�ACK���ģ�ֱ�Ӷ���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_SYNRECEIVED_RCVERRACK,           /* 100��������ͳ��,ԭ��:���ӽ���������ACK��Ų��Ϸ�Ӧ������������*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_ESTABLISHED_RCVDUPACK,           /* 101��������ͳ��,ԭ��:�յ��ظ���ACK���ģ�ֱ�Ӷ���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_ESTABLISHED_RCVDUPACK_GTREXMTTHRESH,/* 102��������ͳ��,ԭ��:���������ش��㷨���յ��ظ���ACK���ģ�ֱ�Ӷ���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_ESTABLISHED_RCVOLDACK,           /* 103��������ͳ��,ԭ��:�����ǵ�ǰ����������ŵĺ��ϵ�ACK����.
                                                                                �����ACK�����ԶԶС�ڵ�ǰ�������յ�ACK��Ų��ұ��ĵ���Ų��ǵ�ǰ�������յ����,
                                                                                ���ǿ�����Ϊ����һ���������ϱ��ӳٺܾõ��ظ�����. ֱ�Ӷ���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_LASTACK_FINISACKED,              /* 104��������ͳ��,ԭ��:�����������,֪ͨ��Ʒ������ɲ��ͷ���Դ������������*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_TIMEWAIT_RCVPKT,                 /* 105��������ͳ��,ԭ��:��TIMEWAIT�£��յ����ģ��ظ�ACK����*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCVERRRST,                       /* 106��������ͳ��,ԭ��:�յ��Ƿ���RST���ģ��ظ�ACK����*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCVRST,                          /* 107��������ͳ��,ԭ��:�յ��Ϸ���RST���ģ�����󣬶���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_CREATECHILDSOCKET_FAILED,        /* 108��������ͳ��,ԭ��:������socketʧ�ܣ�ֱ�Ӷ�������*/    
    SFE_USTAT_REASON_DROP_TCP_PROXY_NOSOCKET_RCVPKT,                 /* 109��������ͳ��,ԭ��:û��socket���ոñ��ģ�ֱ�ӷ���RST����*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_ESTABLISHED_RCVSYN,              /* 110��������ͳ��,ԭ��:���ӽ�����ɺ��յ���SYN��־�ı��Ĳ������������ֱ�Ӷ�������*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCVDUPPKT,                       /* 111��������ͳ��,ԭ��:�յ��ظ��ı��ģ��ظ�ACK�󣬶���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_OTHERSTATE_RCVSYN,               /* 112��������ͳ��,ԭ��:������ɺ�����״̬(�����״̬)���յ�SYN����ֱ�Ӷ���*/
    SFE_USTAT_REASON_DROP_TCP_PROXY_RCV_ACK_TOOMUCH,                 /* 113��������ͳ��,ԭ��:�յ���δ�������ݵ�ACK���ظ�ACK��������*/
    SFE_USTAT_REASON_SIACK_PROC_END,                                 /* 114Э��ջֱ�ӷ��͵ı��� */
    SFE_USTAT_REASON_DROP_TCP_PROXY_REASS_FIN_PKT,                   /* 115 ��������ͳ��,ԭ��:�յ������FIN����*/
    SFE_USTAT_REASON_SEND_TCP_REORDER_REASSRXMT,

    SFE_USTAT_REASON_NO_MAX,                                         /* ͳ��ԭ��߽���Чֵ */
}SFE_USER_STATISTIC_REASON_E;

/* �û�ͳ�Ʋ����Ľ��շ��� */
#define SFE_USER_STAT_NO_DIRECTION    0
/* ���ձ���,�ڱ��Ľ������ͳһ����Ϊ��ֵ */
#define SFE_USER_STAT_RCV    1
/* ���ͱ���,���û��������÷��ͽӿڻ��Ʒ�������챨��ʱͳһ����Ϊֵ */
#define SFE_USER_STAT_SND    2

/* ͳ��֪ͨ��Ϣ */
typedef struct tagSFE_STATISTIC_NOTIFY_INFO
{
    UINT32 u32InOut;            /* ͳ�Ʒ���:���ձ���ͳ��;���ͱ���ͳ��,��ǰ���ֶβ�Ʒ�ɲ��� */
    UINT32 u32ConnectionId;     /* ����ID */
    UINT32 u32Direction;        /* ���ӷ���:����,���� */
    UINT32 u32SrcIP;            /* �����е�Դ��ַ(�����ֽ���),�޷���ȡ��ַ��ʱ����Ϊ0 */
    UINT32 u32DstIP;            /* �����е�Ŀ�ĵ�ַ(�����ֽ���),�޷���ȡ��ַ��ʱ����Ϊ0 */
    UINT32 u32StatType;         /* ͳ������ */
    UINT32 u32StatReason;       /* ͳ��ԭ�� */
    UINT32 u32StatIpPktLen;     /* L3��ͳ��,��ͳ�Ƶ�IP���ĳ���(ͷ�������ݳ���,����һ�����������ĳ���)
                                   ,���޷���ȡIP���ĳ���ʱ��дΪ��������MBUF����. */
    UINT32 u32StatPktDataLen;   /* L7��ͳ��,��ͳ�Ƶı����еĴ����ݳ���(����IP�ʹ����ͷ�ĳ���,����һ�����������ݳ���)
                                   ,���޷���ȡ���ݳ���ʱ��дΪ��������MBUF����.*/
    UINT16 u16VrfIndex;         /* VPN ID */
    UINT8  u8Reserved[2];       /* ���2�ֽڱ�֤��64λ��8�ֽڶ��� */
}SFE_STATISTIC_NOTIFY_INFO_S;


typedef UINT32 (*g_pfSfeStatisticInfoNotifyHook)(SFE_MBUF_S *pstMbuf,
                                                 SFE_STATISTIC_NOTIFY_INFO_S *pstStatNotifyInfo);


extern UINT32 SFE_RegFuncStatisticInfoNotifyHook(g_pfSfeStatisticInfoNotifyHook pfRegFunc);


typedef UINT32 (*g_pfSfeGetVlanIdHook)(SFE_MBUF_S *pstMbuf, UINT32 *pu32VlanId);


extern UINT32 SFE_RegFuncGetVlanIdHook(g_pfSfeGetVlanIdHook pfHook);


extern UINT32 SFE_NakeSendPkt(SFE_MBUF_S *pstMBuf, SFE_MBUF_IFID_S *pstIfId);

#ifdef  __cplusplus
}
#endif

#endif


