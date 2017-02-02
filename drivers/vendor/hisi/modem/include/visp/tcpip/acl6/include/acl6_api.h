/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              acl6_api.h
*
*  Project Code: VISP V1R8
*   Module Name: ACL6
*  Date Created: 6
*        Author: 6
*   Description: ACL6��VISP����(��������ʹ��ACL6 CBB)ʱ�����ṩ�����ݽṹ���û�API����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------

*
*******************************************************************************/
#ifndef _ACL6_API_H_
#define _ACL6_API_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/* ��visp����ʱ,�û�������ʹ��acl6_api.h�е����ݽṹ���û�API������,
   ������ʹ�� acl6_cbb_api.h�����ݽṹ���û�API����*/  
#include "tcpip/acl6/include/acl6_cbb_api.h"

/*�ӿ�ƥ��������Ϣ*/
typedef struct tagAcl6ShClassifyByIfIn
{
    MBUF_S *pstMbuf;     
    ULONG ulIfType;      /*�ӿ�ƥ������:
                           1. ֻƥ����ӿ�
                           2. ֻƥ����ӿ�
                           3. ƥ����ͳ����ֽӿ�*/
    ULONG ulGroupIndex;
} ACL6_SH_CLASSIFY_IF_IN_S;

/*Mbufƥ��������Ϣ*/
typedef struct tagAcl6ShClassifyByIpIn
{
    MBUF_S *pMBuf;
    ULONG ulGroupIndex;    /* ����������*/
    ULONG ulIgnoreByte;
} ACL6_SH_CLASSIFY_IP_IN_S;

/* PPI������ƥ���ͳ����Ϣ */
typedef struct tagAcl6PpiMatchCount
{
    ULONG ulCount;    /* ����ƥ��Ĵ���:
                         ����ƥ��ܾ��Ĵ�����ƥ������Ĵ���*/
}ACL6_PPI_MATCH_COUNT_S;


/* ACL6 �·�PPI���ݽṹ/��NP��ȡƥ����� */
typedef struct tagAcl6PpiMsg
{
    ULONG   ulGroupIndex;       /* ���������� */
    ULONG   ulRuleIndex;        /* �������� */
    union
    {
        ACL6_BASIC_CONTENT_INFO_S stBasicContentInfo;     /*����������Ϣ*/
        ACL6_ADVANCE_CONTENT_INFO_S stAdvContentInfo;     /*�߼�������Ϣ*/
        ACL6_IFBASED_CONTENT_INFO_S stIfBasedContentInfo; /*���ڽӿڹ�����Ϣ*/
        ACL6_PPI_MATCH_COUNT_S stPpiMatchCount; /*���ڴ�NP��ȡƥ�����*/
    } stContent;
}ACL6_PPI_MSG_S;

/* PPIͳ����Ϣ */
typedef struct tagAcl6PpiCount
{
    ULONG ulAcl6UpdateTotal;   /* ACL6����֪ͨ�ܴ��� */
    ULONG ulAcl6UpdateFailure; /* ACL6����֪ͨʧ�ܴ��� */
}ACL6_PPI_COUNT_S;

/* ACL6 PPI��������, �޸Ĵ�ö����Ҫͬ���޸�ACL6_PPI_OprType_En����*/
typedef enum enumAcl6PpiMsgType
{
    PPI_ACL6RULE_CREATE,   /* �������� */
    PPI_ACL6RULE_UPDATE,   /* ���¹��� */
    PPI_ACL6RULE_DEL,      /* ɾ������ */
    PPI_ACL6RULE_DELALL,   /* ɾ�����й���*/
    PPI_ACL6GROUP_CREATE,  /* ���������� */
    PPI_ACL6GROUP_DEL,     /* ɾ�������� */
    PPI_ACL6_GETMATCHCOUNT,/* ��ȡ������ƥ���ͳ����Ϣ */

    /*Start: ACLFW6 intreface security policy PPI operation type*/
    PPI_ACL6RULE_IF_CREATE,
    PPI_ACL6RULE_IF_DEL,
    /*End: ACLFW6 intreface security policy PPI operation type*/
    ACL6_PPI_MSG_MAX
}ACL6_PPI_MSG_TYPE_E;

typedef ULONG (*ACL6_PPI_HOOK_FUNC) (ULONG ulOprType, ULONG ulTypeId, ACL6_PPI_MSG_S* pstPpiMsg);
/*******************************************************************************
*    Func Name: ACL6_PPI_HookRegister
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: ACL6 PPI��Ϣ�·�����ע��ӿ�
*        Input: ACL6_PPI_HOOK_FUNC pfAcl6PpiHook:ACL6 PPI��Ϣ�·����Ӻ���ָ��
*       Output: 
*       Return: Help_ACL6_OK:�ɹ�
*                   �������մ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_PPI_HookRegister(ACL6_PPI_HOOK_FUNC pfAcl6PpiHook);
/*******************************************************************************
*    Func Name: ACL6_PPI_SetDebugSwitch
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: ����ACL6 PPI���Կ���
*        Input: ULONG ulSwitch:����,1��,0�ر�
*       Output: 
*       Return: Help_ACL6_OK:�ɹ�
*                   �������մ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_PPI_SetDebugSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: ACL6_PPI_GetDebugSwitch
* Date Created: 2009-06-02
*       Author: hanna55555
*  Description: ��ȡACL6 PPI���Կ���״̬
*        Input: 
*       Output: ULONG *pulSwitch:ACL6 PPI���Կ���״̬
*       Return: Help_ACL6_OK:�ɹ�
*                   �������մ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-02   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_PPI_GetDebugSwitch(ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: ACL6_PPI_ShowDebugSwitch
* Date Created: 2009-06-02
*       Author: hanna55555
*  Description: ��ʾACL6 PPI���Կ���״̬
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-02   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_PPI_ShowDebugSwitch(VOID);

/*******************************************************************************
*    Func Name: ACL6_PPI_Count_Get
*  Description: ��ȡACL6 PPI�·�ͳ����Ϣ
*        Input: ��
*       Output: ACL6_PPI_COUNT_S *pstCount:ACL PPI�·����ص�ͳ��ָ��
*       Return: �ɹ�VOS_OK,ʧ��VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern ULONG ACL6_PPI_Count_Get(ACL6_PPI_COUNT_S *pstCount);
/*******************************************************************************
*    Func Name: ACL6_PPI_Count_Reset
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: ���ACL6 PPI�·�ͳ����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_PPI_Count_Reset(VOID);
/*******************************************************************************
*    Func Name: ACL6_PPI_ShowCount
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: ��ʾACL6 PPI�·�ͳ����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_PPI_ShowCount(VOID);

/*******************************************************************************
*    Func Name: ACL6_PPI_SetUpdateCostDebug
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: ʹ��/ȥʹ�ܼ���ACL6 PPI�·�ʱ�ӿ���
*        Input: ULONG ulSwitch:ʹ�ܿ���:1ʹ��,0ȥʹ��
*       Output: 
*       Return: Help_ACL6_OK:�ɹ�
*                   �������մ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_PPI_SetUpdateCostDebug(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: ACL6_PPI_GetUpdateCostDebug
* Date Created: 2009-06-02
*       Author: hanna55555
*  Description: ��ȡACL6 PPI�·�ʱ�ӵ��Կ���״̬
*        Input: 
*       Output: ULONG *pulSwitch:ACL6 PPI�·�ʱ�ӵ��Կ���״̬
*       Return: Help_ACL6_OK:�ɹ�
*                   �������մ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-02   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_PPI_GetUpdateCostDebug(ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: ACL6_PPI_ShowUpdateCostDebug
* Date Created: 2009-06-02
*       Author: hanna55555
*  Description: ��ʾACL6 PPI�·�ʱ�ӵ��Կ���״̬
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-02   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_PPI_ShowUpdateCostDebug(VOID);

/*******************************************************************************
*    Func Name: ACL6_PPI_ShowACLUpdateCost
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: ��ʾACL6 PPI�·���ʱ��Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_PPI_ShowACLUpdateCost(VOID);
/*******************************************************************************
*    Func Name: ACL6_PPI_GetMatchCount
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: �����û�����Ĺ����������͹���������ȡPPI
*                     ������Ĺ���ƥ��ͳ����Ϣ
*        Input: ACL6_FILTER_S *pstACL6Filter:������,������������������͹�������
*       Output: ACL6_PPI_MATCH_COUNT_S *pstMatchCount:����ƥ��ͳ�ƴ���
*       Return: Help_ACL6_OK:�ɹ�
*                   �������մ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_PPI_GetMatchCount(ACL6_FILTER_S *pstACL6Filter,ACL6_PPI_MATCH_COUNT_S *pstMatchCount);
/*******************************************************************************
*    Func Name: ACL6_PPI_ShowMatchCount
*  Description: ��ʾPPI������Ĺ���ƥ��ͳ����Ϣ
*        Input:ACL6_FILTER_S *pstACL6Filter:�����������͹�������
*       Output: 
*       Return: VOID
*      Caution: ����������������ƥ���ͳ����Ϣ,������ʾʧ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern VOID ACL6_PPI_ShowMatchCount(ULONG ulGroupIndex,ULONG ulRuleIndex);
/*******************************************************************************
*    Func Name: ACL6_SH_ClassifyByIfInfo
*  Description: ���ݽӿڽ��б���ƥ��
*        Input: pstAcl6_ClassifyIn   ��ƥ����Ϣ
*       Output: pstAcl6_ClassifyOut->ulRuleIndex    ƥ���ACL6����ĵڼ����ڵ�
 *       Return: ACL_PERMIT      ƥ���Ҹ�ƥ��ڵ�Ķ���Ϊ"permit"
*               ACL_DENY        ƥ���Ҹ�ƥ��ڵ�Ķ���Ϊ"deny"
*               ACL_NOTFOUND    �͸�ACL��������нڵ㶼��ƥ��, pulSubitem������
*       Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern ULONG ACL6_SH_ClassifyByIfInfo(ACL6_SH_CLASSIFY_IF_IN_S *pstAcl6_ClassifyIn,
                                             ACL6_CLASSIFY_IF_OUT_S *pstAcl6_ClassifyOut);
/*******************************************************************************
*    Func Name: ACL6_SH_ClassifyByIpInfo
*  Description: �ж�һ������(MBUF)�Ƿ�����һ��ACL6 Group����������
*        Input: pstAcl6_ClassifyIn   ��ƥ����Ϣ
*                  ULONG ulFlag :VRP_YES��ʾ����ƥ�䣬VRP_NO��ʾ����ƥ��        
*       Output: pstAcl6_ClassifyOut->ulRuleIndex    ƥ���ACL6����ĵڼ����ڵ�
 *       Return: ACL_PERMIT  ƥ���Ҹ�ƥ��ڵ�Ķ���Ϊ"permit"
*               ACL_DENY    ƥ���Ҹ�ƥ��ڵ�Ķ���Ϊ"deny"
*               ACL_NOTFOUND    �͸�ACL��������нڵ㶼��ƥ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern ULONG ACL6_SH_ClassifyByIpInfo(ACL6_SH_CLASSIFY_IP_IN_S *pstAcl6_ClassifyIn,
                                              ACL6_CLASSIFY_IP_OUT_S *pstAcl6_ClassifyOut,
                                              ULONG ulFlag);

/*******************************************************************************
*    Func Name: ACL6_SH_OpenRuleTable
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: ��
*        Input: ACL6_FILTER_S* pstACL6Filter:������
*                  pstACL6Filter->ulGroupIndex:����������������ָ��
*                  pstACL6Filter->ulRuleIndex:��������������ָ����ָ��
*                                                               ��ָ��ʱ��дACL6_INVALID_RULE_INDEX(ֵΪ0xffffffff)
*       Output: ULONG* pulACL6Handle:��ȡ����Ĵ�Ŵ�
*       Return: 
*      Caution: ʹ��ʱ����Ҫ������ACL6_SH_CloseRuleTable���ͷž��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_SH_OpenRuleTable(UINTPTR* pulACL6Handle, ACL6_FILTER_S* pstACL6Filter);
/*******************************************************************************
*    Func Name: ACL6_SH_GetNextRuleInfo
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: ��ȡ������Ϣ
*        Input: ULONG ulACL6Handle:���
*       Output: ACL6_RULE_INFO_OUT_S* pstACL6Info:������Ϣ
*       Return: Help_ACL6_OK:�ɹ�
*                    �����μӴ�����
*      Caution: �ȵ���ACL6_SH_OpenRuleTable��ȡ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_SH_GetNextRuleInfo(UINTPTR ulACL6Handle, ACL6_RULE_INFO_OUT_S* pstACL6Info);
/*******************************************************************************
*    Func Name: ACL6_SH_CloseRuleTable
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: �رվ��
*        Input: ULONG ulACL6Handle:���
*       Output: 
*       Return: Help_ACL6_OK:�ɹ�
*                    �����μӴ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_SH_CloseRuleTable(UINTPTR ulACL6Handle);
/*******************************************************************************
*    Func Name: ACL6_SH_OpenGroupTable
* Date Created: 2009-04-13
*       Author: hanna55555
*  Description: ��Waitlist�������ȡϵͳ���й�����Ļ�����Ϣ
*        Input: ULONG* pulAcl6Handle:
*                  ACL6_FILTER_S *pstGroupFilter: ����������
*                                               1.��ָ����������NULL��
*                                               2.ָ��������Ź��ˣ���ʱ�������Ч��
*       Output:  pulAcl6Handle Waitlist���
*       Return:  Help_ACL6_NotInit : ACL CBBδ�ɹ���ʼ��
*                    Help_ACL6_NullPoint : ����ָ��Ϊ��
*                    Help_ACL6_END : ��������ʱ�������һ������
*                    Help_ACL6_WAITLIST_OpenFail : ��waitlistʧ�� 
*                    Help_ACL6_OK : �ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_SH_OpenGroupTable(UINTPTR* pulAcl6Handle,ACL6_FILTER_S *pstGroupFilter);
/*******************************************************************************
*    Func Name: ACL6_SH_GetNextGroupInfo
* Date Created: 2009-04-13
*       Author: hanna55555
*  Description: ��ȡϵͳ���õĹ����������Ϣ
*        Input: ULONG ulAcl6Handle:Waitlist���
*       Output: ACL6_GET_GROUP_INFO_S* pstGroupInfo:�����������Ϣ
*       Return:  Help_ACL6_NotInit : ACL CBBδ�ɹ���ʼ��
*                    Help_ACL6_NullPoint : ����ָ��Ϊ��
*                    Help_ACL6_WAITLIST_GetFail : ��ȡwaitlist�ڵ�ʧ��
*                    Help_ACL6_END : ��������ʱ�������һ������ 
*                    Help_ACL6_OK : �ɹ�
*      Caution: ���øú���ǰ�ȵ���ACL6_SH_OpenGroupTable������ȡWaitlist���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_SH_GetNextGroupInfo(UINTPTR ulAcl6Handle,ACL6_GET_GROUP_INFO_S* pstGroupInfo);
/*******************************************************************************
*    Func Name: ACL6_SH_CloseGroupTable
* Date Created: 2009-04-13
*       Author: hanna55555
*  Description: �ر�Waitlist���
*        Input: ULONG ulAcl6Handle:Waitlist���
*       Output: 
*       Return:  Help_ACL6_NotInit : ACL CBBδ�ɹ���ʼ��
*                    Help_ACL6_NullPoint : ����ָ��Ϊ��
*                    Help_ACL6_WAITLIST_CloseFail : �ر�waitlistʧ��
*                    Help_ACL6_OK : �ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_SH_CloseGroupTable(UINTPTR ulAcl6Handle);
/*******************************************************************************
*    Func Name: ACL6_ShowGroupInfo
* Date Created: 2009-04-13
*       Author: hanna55555
*  Description: ��ʾ���л�ָ����������Ϣ
*        Input: ULONG ulGroupIndex:����������
*               1.Ϊ0��ʾ��ָ���������ѯ��
*               2.��0��ʾָ���������ѯ��
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_ShowGroupInfo(ULONG ulGroupIndex);

/*******************************************************************************
*    Func Name: ACL6_ShowRuleInfo
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: ��ʾָ���������µ�ָ����������й�����Ϣ
*        Input: ULONG ulGroupIndex:����������
*                  ULONG ulRuleIndex:��������
*                           1.ulRuleIndexΪACL6_INVALID_RULE_INDEX(ֵΪ:0xffffffff)
*                              ��ʾĳ�����������й����ѯ��
*                           2.ulRuleIndexΪ��ACL6_INVALID_RULE_INDEX(ֵΪ:0xffffffff)
*                              ��ʾĳ��������ָ�������ѯ��
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_ShowRuleInfo(ULONG ulGroupIndex,ULONG ulRuleIndex);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

