

#ifndef _ARPGUARD_API_H_
#define _ARPGUARD_API_H_


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifndef MACADDRLEN
#define MACADDRLEN       6       /*physical��ַ����*/
#endif

/* ARP�������澯���� */
#define ARPGUARD_ARPCONFLICT_WARNING_THRESHOLD    1024

/* ARP�������澯���� */
#define ARPGUARD_ARPCONFLICT_WARNING_BEGIN  1
/* ARP�������澯���� */
#define ARPGUARD_ARPCONFLICT_WARNING_END  0


typedef struct tagARPGuardArpConflictWarning
{
    ULONG ulWarningType;        /* �澯���� */
    ULONG ulIfIndex;            /* �ӿ����� */    
    ULONG ulNeighbourIPAddr;    /* �ھ�IP, ������ */ 
    /* Add by zhaoyue00171897, at 2011-10-08. �޸�ԭ��: �澯��Ϣ����ˢ��MAC�Ĵ��� */
    ULONG ulAttackCount;        /* ��ͼˢ��MAC�Ĵ��� */
    UCHAR ucMac[MACADDRLEN];    /* ��¼�����������Ǳ�ڹ����ߵ�physical��ַ,���һ������ȡ���һ�γ��ֵĹ�����*/
    UCHAR ucRes[2];
}ARPGUARD_ARPCONFLICT_WARNING_S;

/* ������������ */
#define ARP_GUARD_MAXBLACKNUM  10

/* һ��ARP�������ڵ�����������Ǳ�ڹ����߸��� */
#define ARP_GUARD_ATTACK_NODE_MAX_NUM            3


/*��¼���й�����(���Ϸ��û�)������*/
#define ARP_GUARD_ATK_NODE_MAX_NUM           10 

/*���й�����(���Ϸ��û�)�ϱ��澯�û�����*/
#define ARP_GUARD_ATK_NODE_WARN_LOW_NUM      2 

/* Ǳ�ڹ�������Ϣ,�û��ɲ��ع�ע */
typedef struct tagETHARP_GUARD_ATTACK_INFO
{
    ULONG  ulPktCount;           /* һ��ʱ�����յ���MAC�ļ��� */
    UCHAR  ucMac[MACADDRLEN];    /* physical��ַ */
    UCHAR  ucPadding[2];         /* ���λ */ 
}ETHARP_GUARD_ATTACK_INFO_S;

/* ���ظ��û��ĺ����� */
typedef struct tagETHARP_GUARD_BLACKLIST
{
    ULONG ulIpAddr;                                            /* ��ַ */
    ULONG ulVrfIndex;                                          /* VRF���� */
    ULONG ulIfIndex;                                           /* �ӿ����� */
    ULONG ulBlackNum;                                          /* ��������Ŀ */
    UCHAR ucBlackMac[ARP_GUARD_MAXBLACKNUM][MACADDRLEN];       /* �����������ʮ��,�û�Ӧ����ulBlackNum��ȡ���MAC */
    ULONG ulState;                                             /* �û��ɲ��ع�ע,�ýڵ�ARP״̬ */
    UCHAR szCurMac[MACADDRLEN];                                /* �û��ɲ��ع�ע,��ǰ�ڵ�MAC */
    UCHAR szTrustMac[MACADDRLEN];                              /* �û��ɲ��ع�ע,��ǰ����MAC */

    ULONG ulAttackCount;                                       /* �û��ɲ��ع�ע, ��������,��ͼ�ı�MAC�Ĵ���,�ڲ���Ϣ����ʹ�� */
    UCHAR ucAttackWarningFlag;                                 /* �û��ɲ��ع�ע,ARP�����澯��־,1��ʾ�Ѿ��ϱ��澯��0��ʾ��ǰ�޸澯 */
    UCHAR ucWarningFlag;                                       /* �û��ɲ��ع�ע,�澯��־,1��ʾ�Ѿ��ϱ��澯��0��ʾ�ָ��澯 */
    UCHAR ucPadd[2];
    ULONG ulAttackNodeCount;                                   /* �û��ɲ��ع�ע, Ǳ�ڹ����߽ڵ����,�ڲ���Ϣ����ʹ�� */
    ETHARP_GUARD_ATTACK_INFO_S stAttackNode[ARP_GUARD_ATTACK_NODE_MAX_NUM];/* �û��ɲ��ع�ע, Ǳ�ڹ�������Ϣ,�ڲ���Ϣ����ʹ�� */
}ETHARP_GUARD_BLACKLIST_S;


/*******************************************************************************
*    Func Name: TCPIP_AddARPGuardStaticBlackNode
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: ��Ӿ�̬������,һ����ַ����ӦARP_GUARD_ONEIP_BLACKNUM��������
*        Input: ULONG ulIpAddr: ��ַ
*               ULONG ulVrfIndex: VRF
*               UCHAR *pszMac: physical��ַ
*       Output:
*       Return: �ɹ�:VOS_OK
*               ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_AddARPGuardStaticBlackNode(ULONG ulIpAddr, ULONG ulVrfIndex, UCHAR *pszMac);

/*******************************************************************************
*    Func Name: TCPIP_DelARPGuardStaticBlackNode
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: ɾ����̬������
*        Input: ULONG ulIpAddr: ��ַ
*               ULONG ulVrfIndex: VRF����
*               UCHAR *pszMac: physical��ַ
*       Output:
*       Return: �ɹ�:VOS_OK
*               ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DelARPGuardStaticBlackNode(ULONG ulIpAddr, ULONG ulVrfIndex, UCHAR *pszMac);


/*******************************************************************************
*    Func Name: TCPIP_OpenARPGuardDynamicBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: Open��̬Guard�ڵ�waitlist
*        Input: ULONG *pulWaitListHandle: �������,waitlist���
*       Output:
*       Return: �ɹ�:VOS_OK
*               ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_OpenARPGuardDynamicBlack(ULONG *pulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_GetARPGuardDynamicBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: ��ȡ��̬Guard�ڵ�
*        Input: ULONG ulWaitListHandle: waitlist���
*               ETHARP_GUARD_BLACKLIST_S *pstEntry:�������,��ȡ�������б�
*       Output:
*       Return: �ɹ�:VOS_OK
*               ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetARPGuardDynamicBlack(ULONG ulWaitListHandle, ETHARP_GUARD_BLACKLIST_S *pstEntry);


/*******************************************************************************
*    Func Name: TCPIP_CloseARPGuardBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: �رջ�ȡ����������waitlist,�ú������Թرվ�̬��Ҳ���Թرն�̬��
*        Input: ULONG ulWaitListHandle: ���
*       Output:
*       Return: �ɹ�:VOS_OK
*               ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_CloseARPGuardBlack(ULONG ulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_OpenARPGuardStaticBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: �򿪾�̬������waitlist
*        Input: ULONG *pulWaitListHandle: waitlist���
*       Output:
*       Return: �ɹ�:VOS_OK
*               ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_OpenARPGuardStaticBlack(ULONG *pulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_GetARPGuardStaticBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: ��ȡwaitlist��һ��guard�ڵ�����к�����
*        Input: ULONG ulWaitListHandle: waitlist���
*               ETHARP_GUARD_BLACKLIST_S *pstEntry: �������,�������б�
*       Output:
*       Return: �ɹ�:VOS_OK
                ��ȡ��β��:ETHARP_GUARD_GET_BLACKNUMM_FINISH
*               ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetARPGuardStaticBlack(ULONG ulWaitListHandle, ETHARP_GUARD_BLACKLIST_S *pstEntry);

/*******************************************************************************
*    Func Name: TCPIP_SetARPGuardSwitch
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: ����Guard���ܿ���
*        Input: ULONG ulValue: ����ֵ
*       Output:
*       Return: �ɹ�:VOS_OK
*               ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetARPGuardSwitch(ULONG ulValue);

/*******************************************************************************
*    Func Name: TCPIP_GetARPGuardSwitch
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description:��ȡGuard���ܿ���
*        Input: ULONG *pulValue: �������,��ȡ����ֵ
*       Output:
*       Return: �ɹ�:VOS_OK
*               ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetARPGuardSwitch(ULONG *pulValue);

/*******************************************************************************
*    Func Name: TCPIP_SetARPGuardCheatDetectCount
* Date Created: 2009-9-18
*       Author: zhangchunyu(62474)
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: ���÷���ƭ��ⷢ��ARP���Ĵ���,ȡֵ��Χ��5��15
*        Input: ULONG ulCount: ����
*       Output:
*       Return: �ɹ�:VOS_OK
*               ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetARPGuardCheatDetectCount(ULONG ulValue);

/*******************************************************************************
*    Func Name: TCPIP_GetARPGuardCheatDetectCount
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: ��ȡ����ƭ��ⷢ��ARP���Ĵ���
*        Input: ULONG *pulCount: �������
*       Output:
*       Return: �ɹ�:VOS_OK
*               ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetARPGuardCheatDetectCount(ULONG *pulValue);


/*******************************************************************************
*    Func Name: TCPIP_ShowARPGuardDynamicBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: ��ʾ���ж�̬������
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18   zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowARPGuardDynamicBlack(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowARPGuardStaticBlack
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: ��ʾ���о�̬������
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18   zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowARPGuardStaticBlack(VOID);

/*******************************************************************************
*    Func Name: TCPIP_DelARPGuardlAllStaticBlackNode
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: ɾ�����о�̬������
*        Input: VOID
*       Output:
*       Return: VOS_OK:�ɹ�
*               ETHARP_NOT_INIT:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18   zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DelARPGuardlAllStaticBlackNode(VOID);

/*******************************************************************************
*    Func Name: TCPIP_DelARPGuardlAllDynamicBlackNode
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)/zhangchunyu(62474)
*  Description: ɾ�����ж�̬������
*        Input: VOID
*       Output:
*       Return: VOS_OK:�ɹ�
*               ETHARP_NOT_INIT:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-18    zengshaoyang(62531)/zhangchunyu(62474)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DelARPGuardlAllDynamicBlackNode(VOID);

/*******************************************************************************
*    Func Name: TCPIP_DelDynamicBlackNode
* Date Created: 2009-9-18
*       Author: zengshaoyang(62531)
*  Description: ɾ��һ����������¼
*        Input: ULONG ulIpAddr:��ַ
*               ULONG ulVrfIndex:VRF����
*               UCHAR *pszMac:physical��ַ
*       Output: 
*       Return: �ɹ�VOS_OK;ʧ�ܴ�����
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-4    zengshaoyang(62531)      Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_DelDynamicBlackNode(ULONG ulIpAddr, ULONG ulVrfIndex, UCHAR *pszMac);


ULONG TCPIP_SetARPGuardWarningThreshold(ULONG ulValue);


ULONG TCPIP_GetARPGuardWarningThreshold(ULONG *pulValue);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ETHARP_API_H_ */

