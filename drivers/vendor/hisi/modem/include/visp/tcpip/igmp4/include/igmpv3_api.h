/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              igmpv3_api.h
*
*  Project Code: VISPV100R007
*   Module Name: igmp  
*  Date Created: 2008-03-16
*        Author: zengshaoyang62531
*   Description: igmpģ�����ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-16   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IGMPV3_API_H
#define _IGMPV3_API_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define IGMP_TIMER_URI 1    /*��ʱ������:������������*/
typedef enum tagIGMPERRCODE
{
    IGMP_OK = 0,                
    IGMP_ERR_TIMERNAME,          /* ��ʱ����ز��������Ͳ��ԣ���ǰ(VR7)ֻ֧��������������([1, 5]) */
    IGMP_ERR_TIMERVALUE,         /* ��ʱ���ĳ�ʱʱ�䳬�����÷�Χ */
    IGMP_ERR_NULLPOINTER,        /* ָ��Ϊ�� */
    IGMP_ERR_IFNETTYPE,          /* ����Ľӿ����� */
    IGMP_ERR_NOTLOCALIF,         /* �Ǳ���ӿ� */   
    IGMP_ERR_IFNULL,             /* �ӿ�Ϊ�� */
    IGMP_ERR_DEBUGFLAG,          /* flagֵ���� */
    IGMP_COMP_NULL,              /* igmp������Ϊ�� */
    IGMP_ERR_HAISSMOOTHING,      /* �����ֶ�������ƽ�������� */ 
    IGMP_ERR_IPCTLBLK_INVALID,   /* IP���ƿ���Ч */
    IGMP_ERR_NOGROUP,             /* �ӿ�δ�����κζಥ�� */
    IGMP_ERR_IF_NOT_EXIST,    		/* Interface does not exist */
    IGMP_ERR_OPENWAITLIST_FAIL, 	/* Open IGMP mlticast group table failed*/
    IGMP_ERR_GETWAITLIST_FAIL,		/* Get from IGMP table failed*/
    IGMP_ERR_NO_MG_FOR_IF,			/* No Multicast group for the interface */
    IGMP_ERR_NO_IP_CTRLBLK,			/* IP control block is NULL for interface*/
    IGMP_ERR_WAITLISTEND,			/* Set IGMP mlticast group table pointer failed*/
    IGMP_ERR_WAITLIST_SET_FAILED,	/* Set IGMP mlticast group table pointer failed*/
    IGMP_ERR_WAITLIST_CLOSE_FAILED	/*Open IGMP mlticast group table failed*/
}IGMPERRCODE_E;

typedef struct tagIGMPSTAT
{
    ULONG   ulIgmpv1RecvGenQuery;       /* ���շ���igmpv1ͨ�ò�ѯ����ͳ�� */
    ULONG   ulIgmpv1RecvMemRpt;         /* ���շ���igmpv1��Ա���汨��ͳ�� */
    ULONG   ulIgmpv1RecvErr;            /* ���շ���igmpv1����ʧ�ܵı���ͳ�� */
    ULONG   ulIgmpv1SendSuc;            /* ���ͷ���igmpv1����ɹ��ı���ͳ�� */ 
    ULONG   ulIgmpv1SendErr;            /* ���ͷ���igmpv1����ʧ�ܵı���ͳ�� */
    ULONG   ulIgmpv2RecvGenQuery;       /* ���շ���igmpv2ͨ�ò�ѯ����ͳ�� */
    ULONG   ulIgmpv2RecvSpeGrpQuery;    /* ���շ���igmpv2�ض����ѯ����ͳ�� */
    ULONG   ulIgmpv2RecvMemRpt;         /* ���շ���igmpv2��Ա���汨��ͳ�� */
    ULONG   ulIgmpv2RecvErr;            /* ���շ���igmpv2����ʧ�ܵı���ͳ�� */
    ULONG   ulIgmpv2SendSuc;            /* ���ͷ���igmpv2����ɹ��ı���ͳ�� */ 
    ULONG   ulIgmpv2SendLeaveRpt;       /* ���ͷ���igmpv2�뿪�鱨�汨��ͳ�� */
    ULONG   ulIgmpv2SendErr;            /* ���ͷ���igmpv2����ʧ�ܵı���ͳ�� */
    ULONG   ulIgmpv3RecvGenQuery;       /* ���շ���igmpv3ͨ�ò�ѯ����ͳ�� */
    ULONG   ulIgmpv3RecvSpeGrpQuery;    /* ���շ���igmpv3�ض����ѯ����ͳ�� */
    ULONG   ulIgmpv3RecvSpeGrpSrcQuery; /* ���շ���igmpv3�ض���Դ��ѯ����ͳ�� */
    ULONG   ulIgmpv3RecvErr;            /* ���շ���igmpv3����ʧ�ܵı���ͳ��(��igmpv3��Ա����) */
    ULONG   ulIgmpv3SendSuc;            /* ���ͷ���igmpv3����ɹ��ı���ͳ�� */ 
    ULONG   ulIgmpv3SendErr;            /* ���ͷ���igmpv3����ʧ�ܵı���ͳ�� */    
    ULONG   ulIgmpUnknowErr;            /* δ֪�����IGMPͳ����Ϣ */
}IGMPSTAT_S;

typedef struct tagHAIGMPSTAT
{
    ULONG   ulOutPackets;       /* ���巢�ͳɹ�������Ϣ������ */
    ULONG   ulOutDropPackets;   /* ���巢��ʧ�ܱ�����Ϣ������ */
    ULONG   ulInPackets;        /* ������ղ�����ɹ�������Ϣ������ */
    ULONG   ulInDropPackets;    /* ������ա�����ʧ�ܱ�����Ϣ������ */
}HAIGMPSTAT_S;

/*This structure is used in callback function to fill the source address. */
typedef struct tagIGMPGETSRCIP
{
    ULONG ulSrcIp;              /*IGMP packet source address (host order), output parameter*/
}IGMPGETSRCIP_S;


/*Registeres hook function to get the source address for the outgoing IGMP packet
* Input: pstMbuf is input to the product.
* Output: pstData, The callback function has to update the src address */
typedef ULONG (*IGMP_GET_SRC_IP_HOOK)( MBUF_S *pstMbuf,IGMPGETSRCIP_S *pstData);


/*This structure is used in TCPIP_GetMGInfo to get the address for a particular interface.*/
typedef struct tagIGMPMGINFO
{
    ULONG   ulIfIndex;       /* �ӿ�����*/
    ULONG   ulIpAddr;        /* �鲥��ַ��������*/
}IGMPMGINFO_S;


/* This structure is used in TCPIP_OpenMGInfoTable as a filter parameter */
typedef struct tagIGMPMGFILTER
{
    ULONG   ulIfIndex;       /* Interface index */
}IGMPMGFILTER_S;
extern ULONG TCPIP_ClearIgmpStat (ULONG  ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetIgmpDebug
* Description: Get the igmp module debug flag
* Input:
* Output: ULONG * pulDbg: to save the debug flag
* 	ULONG * pulVerboseDbg: used to save the verbose debugging
* Return: IGMP_COMP_NULL: igmp component is empty
* 	IGMP_ERR_NULLPOINTER: null pointer
* 	VOS_OK: success
* Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIgmpDebug (ULONG *pulDbg, ULONG *pulVerboseDbg);
/*******************************************************************************
* Func Name: TCPIP_GetIgmpHADebug
* Description: Get the igmp ha debugging value
* Input:
* Output: ULONG * pulDbg: to save the igmp ha debugging value
* Return: IGMP_COMP_NULL: igmp component is empty
* 	IGMP_ERR_NULLPOINTER: pointer is empty
* 	VOS_OK: success
* Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIgmpHADebug(ULONG *pulDbg);

extern ULONG TCPIP_GetIgmpStat(ULONG  ulIfIndex, IGMPSTAT_S *pstIgmpStat);
/*******************************************************************************
* Func Name: TCPIP_GetIgmpTimer
* Description: Get the timer timeout value
* Input: ULONG ulTimerType: the type of timing values
* Output: ULONG * pulTimerVal: returns the timer value time
* Return: IGMP_ERR_NULLPOINTER: pointer is empty
* 	IGMP_COMP_NULL: components of the virtual table is empty
* 	IGMP_ERR_TIMERNAME: timer type is incorrect
* VOS_OK: success
* Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIgmpTimer(ULONG ulTimerType, ULONG *pulTimerVal);

extern ULONG TCPIP_IGMP_ClearHaStat(VOID);

extern ULONG TCPIP_IGMP_GetHaStat(HAIGMPSTAT_S *pstHaIgmpStat);
/*******************************************************************************
* Func Name: TCPIP_SetIgmpDebug
* Description: set igmp module debug switch value
* Input: ULONG ulFlag: switch,0 --- Close 1 --- Open
* ULONG ulVerboseFlag: verbose debugging,0 --- Close 1 --- Open
* Output:
* Return: IGMP_ERR_DEBUGFLAG: switch value error
* 	IGMP_COMP_NULL: components of the virtual table is empty
* 	VOS_OK: success
* Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIgmpDebug (ULONG ulFlag, ULONG ulVerboseFlag);
/*******************************************************************************
* Func Name: TCPIP_SetIgmpHADebug
* Description: set igmp ha debugging value
* Input: ULONG ulDbg :0 --- close, 1 --- Open
*       Output: 
* Return: IGMP_ERR_DEBUGFLAG: debugging value error
* 	VOS_OK: success
* 	IGMP_COMP_NULL: igmp components of the virtual table is empty
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIgmpHADebug(ULONG ulDbg);
/*******************************************************************************
* Func Name: TCPIP_SetIgmpTimer
* Description: Set the IGMP timer configuration information
* Input: ULONG ulTimerType: timer type
* ULONG ulTimerVal: Timer time
* Output:
* Return: IGMP_ERR_HAISSMOOTHING: manual switching or smoothing processing in
* 	IGMP_ERR_TIMERNAME: timer wrong type
* 	IGMP_ERR_TIMERVALUE: timer timeout time exceeds the configured range
* 	IGMP_COMP_NULL: components of the virtual table is empty
* 	VOS_OK: success
*Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIgmpTimer(ULONG ulTimerType, ULONG ulTimerVal);
/*******************************************************************************
* Func Name: TCPIP_ShowIgmpDebug
* Description: display the igmp module debug switch
*        Input: 
*       Output: 
*       Return: VOID               
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   zengshaoyang62531       Create
*
*******************************************************************************/
extern VOID TCPIP_ShowIgmpDebug (VOID);

extern VOID TCPIP_ShowIgmpStat (CHAR *pszIfName);

extern VOID TCPIP_ShowMGInfoByIfName (CHAR *pszIfName);



/*******************************************************************************
* Func Name: TCPIP_RegIgmpHookToGetSrcIP
* Description: This function is used to register the callback function to get the source 
* address for outgoing IGMP packets.
* Input: IGMP_GET_SRC_IP_HOOK pstHook: Callback function to be registered.
*       Output: 
*       Return: VOS_OK success,Other failure of type IGMPERRCODE_E
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         	           NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07           s72256                   Create
*
*******************************************************************************/
ULONG TCPIP_RegIgmpHookToGetSrcIP (IGMP_GET_SRC_IP_HOOK pstHook);

/*******************************************************************************
* Func Name: TCPIP_OpenMGInfoTable
* Description: Open handle query multicast group filter conditions in the interface
*                   index must be filled. Does not support query system-wide information.
* Input: 		pstFilter��Filter conditions. Currently supports based on interface index filter.
* Output: 	pulHandle��Query handle
*       Return: VOS_OK success,Other failure of type IGMPERRCODE_E
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         	           NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07           s72256                   Create
*
*******************************************************************************/
ULONG TCPIP_OpenMGInfoTable (UINTPTR *pulHandle, IGMPMGFILTER_S *pstFilter);

/*******************************************************************************
* Func Name: TCPIP_GetMGInfo
* Description: This function is used to get the multicast group information.
* Input: 		pulHandle��Query handle
* Output: 	pstMgInfo: Multicast group information
*       Return: VOS_OK success,Other failure of type IGMPERRCODE_E
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         	           NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07           s72256                   Create
*
*******************************************************************************/
ULONG TCPIP_GetMGInfo (UINTPTR ulHandle, IGMPMGINFO_S *pstMgInfo);


/*******************************************************************************
* Func Name: TCPIP_CloseMGInfoTable
* Description: This function is used to close the query handle.
* Input: 		pulHandle��Query handle
* Output: 	
*       Return: VOS_OK success,Other failure of type IGMPERRCODE_E
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         	           NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07           s72256                   Create
*
*******************************************************************************/
ULONG TCPIP_CloseMGInfoTable (UINTPTR ulHandle);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
