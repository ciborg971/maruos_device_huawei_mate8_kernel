/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_PUB.H 
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/03/28
 *        Author: luohanjun
 *   Description: 
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/03/28      luohanjun       Create File
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *
 ************************************************************************/

#ifndef _TCPIP_IFPUB_H_
#define _TCPIP_IFPUB_H_

#ifdef  __cplusplus
extern "C"{
#endif


/*�ӿ��࣬����ӿ��๫�����Ժ���ɳ�Ա*/
typedef struct tagIF_Class_S
{
    ULONG   if_ulType ;             /* �ӿ����� */
    ULONG   if_ulProperty;          /* �ӿ����� */
    ULONG   if_ulFlags;
    ULONG   if_ulOpFlag;    /* ֧�ֵ����������ʶ */  

    /* 
     * �ӿڱ�־���ԣ� 
     * &IF_MOVING ��ʾ�ö˿ڿɱ�ɾ��
     * &IF_TEMPIF ��ʱ�ӿڱ�־
     * &IF_NOCONFIG �ӿڲ�������
     * &IF_INVISIBLE �ӿڲ�����ʾ( ������ʾ�ӿ���Ϣ )
     * ȱʡ״̬�� ����ɾ��������ʱ�ӿڡ��ɼ���������
     */
    ULONG   if_ulMoving ;  
    CHAR  if_szIfName[ IF_MAX_INTERFACE_NAME_LEN+1];   /* �ӿ����� */
    CHAR  if_szSimpleName[ IF_MAX_INTERFACE_NAME_LEN+1];   /*�� �ӿ����� */
    CHAR  if_szCmdTemple[ MAX_IFCMD_NAME_LEN+1];      /* �ӿ�����ģʽ�� */

    /*
     * ���±�ȷ������һ��Ĺ����ӿ�ָ��
     * 0:�ϲ㹫���ӿ��麯����ָ�룬����Ϊ��    #define IF_LAYER_IP       0 
     * 1:���IPv6�Ĳ㣬����Ϊ��                #define IF_LAYER_IPV6     1 
     * 2:��·�㹫���ӿ��麯����ָ�룬����Ϊ��  #define IF_LAYER_LINK     2 
     * 3:�豸�㹫���ӿ��麯����ָ�룬����Ϊ��  #define IF_LAYER_PHISICAL 3 
     */
    struct IIF_IFS_IntFunVtbl *if_pstLayer[IF_LAYER_MAX] ;

    IF_PRETREATFUN if_pPreFun;      /* �ӿ�����ģʽ����׺Ԥ���������罫�ӿ�����ת��Ϊport��Ĭ��ΪNULL*/

    /***********************************************
     *                 �������־                  *
     ***********************************************/

    /*
     * VT�ӿڱ�־��
     * 0����ͨ�ӿ����ͣ� #define IF_INTERFACE_NORMAL 0
     * 1��VT�ӿڣ�       #define IF_INTERFACE_VT     1
     * 2��VA�ӿ�         #define IF_INTERFACE_VA     2
     */
    ULONG   if_ulVTFlag;             
    ULONG   if_ulSpoofing;
    ULONG   if_ulPortType;
    ULONG   if_ulLogicFlag;  /*�߼��ӿڱ�ʶVOS_TRUE�����߼��ӿ� VOS_FALSE�����߼�(�豸�ӿ�)*/
    ULONG   if_ulCloneFlag;  /*�߼��ӿ���Ҫ�����нӿڰ��Ϸ����ʶVOS_TRUE����Ҫ����  VOS_FASLE������Ҫ����*/
    ULONG   if_ulResumeLevel;/*�ӿڻָ��ȼ�(0~1)��0Ϊ������1���Ȼָ�����ӦĳЩ�ӿڼ��������ϵ��Ĭ��Ϊ0*/

    /***********************************************
     *       �ӿڰ�����Ϣ��Ϊ�����з���            *
     ***********************************************/   
     
    ULONG   if_ulBeginNum;         /* �ӿ���ʼ���(��) */
    ULONG   if_ulEndNum;           /* �ӿڽ������(��) */
    ULONG   if_ulMaxNum;           /* �ӿ�������� */

    ULONG   if_ulSubIfFlag;        /*�����ӽӿڱ�ʶ VOS_TRUE���������ӽӿ�  VOS_FASLE��������*/
    ULONG   if_ulSubBeginNum;      /* �ӽӿ���ʼ���(��) */
    ULONG   if_ulSubEndNum;        /* �ӽӿڽ������(��) */
    ULONG   if_ulMaxSub;           /* �ӽӿ�������� */

    ULONG   if_ulMinMtu;           /* Mtu ����ֵ */
    ULONG   if_ulMaxMtu;           /* Mtu ����ֵ */

    ULONG   if_ulChannelBeginNum;  /* ��ͨ���ӿ���ʼ���(��) */
    ULONG   if_ulChannelEndNum;    /* ��ͨ���ӿڽ������(��) */
    ULONG   if_ulMaxChannel;       /* ��ͨ��������� */

    ULONG   if_ulHelpIndex;        /* �ӿڵİ������� */
    ULONG   if_usIndexHelpIndex;   /* �ӿڱ�ŵİ������� */
    ULONG   if_ulChannelHelpIndex;   
    
}IF_CLASS_S ;

/********** ��Ʒϵͳ���� ***********/   
typedef struct tagVRPInterface
{
    ULONG       if_ulLevel;             /* �ӿڱ���С�/�������������������ά�ȣ�1 */
    
    ULONG       if_ulBoardNum;          /* ���ӿڰ���Ŀ,Ϊ0����Ϊû�нӿڰ� */
    ULONG       if_ulCardNum;           /* ���µ����ӿڿ��� */
    ULONG       if_ulIfNum;             /* ���ϵ����ӿ��� */

    ULONG       if_ulIfTypeMaxEnum;     /* ϵͳ�Ľӿ������͵����ö��ֵ */
    ULONG       if_ulIfClassMax;        /* ϵͳ�Ľӿ��������ܸ���(>=if_ulIfClassNum) */
    ULONG       if_ulIfClassNum;        /* ��ǰ�Ѿ�ע���ϵͳ�Ľӿ�����Ŀ */
    ULONG       if_ulMainBoardID;       /*����ID add by luohanjun*/
    ULONG       if_ulSelfBoardID;       /*����ID*/
    IF_CLASS_S* if_pstIfClass;          /* �ӿڵ�������������ָ�� */

} VRP_INTERFACE_S;

typedef struct tagIF_SH_CALL_S
{
    CHAR* (*pfIF_Sh_GetMsg_Router_En)(ULONG ulIndex); /* ��ȡӢ��������Ϣ */

    ULONG (*pfIF_Sh_OutStringWait)( ULONG ulExecID, CHAR * szOutString, ULONG * ulCurLine );

    ULONG (*pfIF_Sh_GetLanguageMode)(ULONG ulExecID);
    ULONG (*pfIF_Sh_PPPGetUserName)(IFNET_S *pstIfnet,CHAR *szName);
    ULONG (*pfIF_Sh_PPPGetPeerIPAddr)(IFNET_S *pstIfnet,ULONG *ulIpAddr);

    ULONG (*pfIF_Sh_KRTMsgSend)(VLINKSTATUS_S *pstIFNETMsg);
    ULONG (*pfIF_Sh_KRTMsg6Send)(IFVLINKENTRY6_S *pstIFNETMsg);
} IF_SH_CALL_S;


typedef struct tagIF_MOD_INFO
{
    ULONG    ulIfModID;
    ULONG    ulIf_If_SID;        
    ULONG    ulIfIpcNotifyQueID;
    ULONG   ulIfIPCID;
    ULONG   ulRMIPV6ID;
    ULONG   ulRMIPV6_IID;
    
} IF_MOD_INFO_S;


DECLARE_INTERFACE(IIF_IFNET_ComIntCFG)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIF_Init_Com)();
    METHOD_(ULONG, pfIF_SetModuleInfo)(IF_MOD_INFO_S* pstMInfo);
    METHOD_(ULONG, pfIF_RegisterAll)(IF_SH_CALL_S* pstShellCall);
    METHOD_(ULONG, pfIF_RegisterProductParam)(VRP_INTERFACE_S* pstProduct);
    METHOD_(ULONG, pfIF_Register_IFClass)(IF_CLASS_S* pstIfClass ) ; /*��coreע��ӿ���*/
    METHOD_(IF_CLASS_S*, pfIF_FindClassByType)(ULONG ulType);       /*�������ʹ�core�л�ȡ�ӿ���ָ��*/
    METHOD_( ULONG,pfTCPIP_HA_SetIfnetDbg ) (ULONG ulDbg);
    METHOD_( ULONG,pfIF_HA_GetIfnetDbg ) (ULONG *pulDbg);
    METHOD_(ULONG, pfIF_HA_SetVerboseDbg) (ULONG ulDbg);
    METHOD_(ULONG, pfIF_HA_GetVerboseDbg) (ULONG *pulDbg);
    METHOD_( VOID, pfIF_HA_DebugOutPut)(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);

};


DECLARE_INTERFACE(IIF_IFNET_ComIntSSA)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfIF_SetDevLinkPtr)( ULONG ulType,DEVLINK_S ** ppDev);

    METHOD_(ULONG, pfIF_Init_Com)();
};


#ifdef  __cplusplus
}
#endif

#endif  /* _TCPIP_IFPUB_H_ */

