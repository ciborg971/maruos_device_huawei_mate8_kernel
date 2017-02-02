/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_VAR.H
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/03/28 
 *        Author: luohanjun
 *   Description: Ifnetȫ�ֱ�������ͷ�ļ�
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/03/28      luohanjun       Create
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *
 ************************************************************************/

#ifndef _IF_VAR_H_
#define _IF_VAR_H_


#ifdef  __cplusplus
extern "C"{
#endif


/*******************��ʼ��ʹ�ñ��� begin***********************************/
extern IF_SH_CALL_S* gpstShCallCenter ;               /*shell�ص�����ָ��*/

extern IF_LMSG_FUNLINK_S* gpstLinkMsgNotifyHead ;   /*��Ϣ֪ͨ������ͷ*/
extern IF_MSG_FUNLINK_S* gpstDevMsgNotifyHead ;     /*��Ϣ֪ͨ������ͷ*/
extern IF_PTR_FUNLINK_S* gpstAddIfNotifyHead ;      /*�ӿڴ���֪ͨ������ͷ*/
extern IF_PTR_FUNLINK_S* gpstAddSubIfNotifyHead ;   /*�ӽӿڴ���֪ͨ������ͷ*/
extern IF_PTR_FUNLINK_S* gpstDelIfNotifyHead;       /*�ӿ�ɾ��֪ͨ������ͷ*/
extern IF_PTR_FUNLINK_S* gpstShutIfNotifyHead ;     /*�ӿ�shutdown֪ͨ������ͷ*/
extern IF_VLANCHECKFN gpstVlanCheck; /* �ӿ�VLAN���ò�ѯ */

/*******************��ʼ��ʹ�ñ��� end***********************************/


/******************* IPCʹ�ñ��� begin***********************************/
extern UCHAR*  gucBoardList;                           /* ����ϵͳ����λ״̬��ͬʱ��������塢�߼���״̬ */

extern ULONG   gulMaxBoardNum;
/******************* IPCʹ�ñ��� end***********************************/


/******************* Devʹ�ñ��� begin***********************************/
/*ָ��shell���豸��ͷ����β ��ʵ�����ڴ湲��  add by luohanjun*/
extern DEVLINK_S **gppstDevHead;
extern DEVLINK_S **gppstDevTail;
extern DEVLINK_S **gppstTempDevHead;
extern DEVLINK_S **gppstTempDevTail;

/******************* Devʹ�ñ��� end***********************************/


/******************* ����ʹ�ñ��� begin***********************************/
extern IFNET_S *g_pstIfConfigNet;
extern IFNET_S *g_pstIfConfigNetTail;

/* extern IFNET_S         gstDefaultIf; */

/*-----------------------------------------------------------------------*\
*                    ·����Ӳ���ṹ����ָ��                               *
*                    ָ��stIfInfo                                         *
\*-----------------------------------------------------------------------*/
extern VRP_INTERFACE_S     * gpstIfInfo;
extern IF_MOD_INFO_S  gstIFModInfo;
/*-----------------------------------------------------------------------*\
*                   ���ֽ������������ָ��                       *
\*-----------------------------------------------------------------------*/
extern PIF_ANAL_VECTOR_S    gpstIfTreeManage;

extern ULONG           gulIfIndexNum[IFNET_MAX_BOARD_NUM] ;    /* ��¼���������С */
extern ULONG           gulIfIndexInsert[IFNET_MAX_BOARD_NUM];  /* ��¼��ǰ�ɷ���ĵ�һ������ */
extern ULONG           gulIfIndexMaxUsed[IFNET_MAX_BOARD_NUM]; /* ��¼��ǰ�Ѿ�ʹ�õ����������±� */
extern IFINDEX_S       *gpIfIndexArray[IFNET_MAX_BOARD_NUM];

/*-----------------------------------------------------------------------*\
*            �ڽӿڰ������ڷ���VA������ȫ�����ݽṹ                      *
\*-----------------------------------------------------------------------*/
extern ULONG           gulVAIfIndexNum[IFNET_MAX_BOARD_NUM] ;
extern ULONG           gulVAIfIndexInsert[IFNET_MAX_BOARD_NUM];
extern IFINDEX_S       *gpVAIfIndexArray[IFNET_MAX_BOARD_NUM];

extern ULONG   gulVAIfNum[MAXVTNum] ;
extern ULONG   gulVAIfInsert[MAXVTNum];
extern UCHAR   *gpVAIfArray[MAXVTNum];

extern NotifyIfState_HOOK_FUNC    g_pfNotifyIfState;

extern struct IIF_IFNET_ComIntFUNVtbl* g_pstIfFunVtbl;   /* ���ܺ����� */
extern struct IIF_IFNET_ComIntCFGVtbl* g_pstIfCfgVtbl;   /* ���ú����� */
extern struct IIF_IFNET_ComIntSSAVtbl* g_pstIfSSAVtbl;   /* ϵͳ֧�ֺ����� */

/* VISP1.8.1 ֧��1AG��׼Э�鿪��*/
extern UCHAR   g_ucIf1agDefaultVersion;

extern DEVLINK_S * DevLinkHead[VRP_MAX_BOARD_NUM];     /* �豸��ͷ���� */
extern DEVLINK_S * DevLinkTail[VRP_MAX_BOARD_NUM];     /* �豸��β���� */
extern DEVLINK_S * TempDevLinkHead[VRP_MAX_BOARD_NUM]; /* ��ʱ�豸��ͷ���� */
extern DEVLINK_S * TempDevLinkTail[VRP_MAX_BOARD_NUM]; /* ��ʱ�豸��β����*/

extern TCPIP_CreateLogicIf_HookFunc g_pfTCPIP_CreateLogicIf;
extern TCPIP_ADDR_HOOK_S g_stAddrHook;

#ifdef  __cplusplus
}
#endif

#endif  /* _IF_VAR_H_ */

