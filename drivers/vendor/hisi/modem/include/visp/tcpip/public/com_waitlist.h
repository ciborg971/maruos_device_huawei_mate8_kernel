/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              waitlist.h
*
*  Project Code: VISPV1R5
*   Module Name: WaitList  
*  Date Created: 2000/06/24 
*        Author: 19742
*   Description: WaitListģ���ṩ�Ľӿں���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2000/06/24  19742         Creat the first version.
*
*******************************************************************************/

#ifndef _COM_WAITLIST_H_
#define _COM_WAITLIST_H_

#ifdef    __cplusplus
extern "C"{
#endif

#define        COM_FILTER_WAITLIST_SUCCESS             0
#define        ERR_COM_FILTER_WAITLIST_INVALID_MAINTYPE    1
#define        ERR_COM_FILTER_WAITLIST_INVALID_SUBTYPE     2
#define        ERR_COM_FILTER_WAITLIST_NOMEM               3
#define        ERR_COM_FILTER_WAITLIST_INVALID_HANDLE      4
#define        ERR_COM_FILTER_WAITLIST_NOENTRY      5

#define COM_WAITLIST_BFD_OSPF_RELATION 1
#define COM_WAITLIST_BFD_OSPF_RULE 2
#define COM_WAITLIST_BFD_STATIC_RELATION 3
#define COM_WAITLIST_BFD_SESSION 4
#define COM_WAITLIST_VLAN_ENTRY 5
/*Begin Add 2008-08-25 liangjicheng*/
#define COM_WAITLIST_ETHARP_ENTRY 6
#define COM_WAITLIST_ACL_ENTRY 7
#define COM_WAITLIST_IPOA_ENTRY 8
/*End Add 2008-08-25 liangjicheng*/

/* Added by hanna55555, VISPV1R8C01 for ACL6, 2009/4/8 */
#define COM_WAITLIST_ACL6_ENTRY 9
/*End of Added by hanna55555, 2009/4/8 */

#define COM_WAITLIST_VLINK_RTNODE 10
#define COM_WAITLIST_VRF_ENTRY 11

#define COM_WAITLIST_NB_ENTRY 12

/* Begin: Added by a00900892. DTS modify for vrf6 show bind info */
#define COM_WAITLIST_VRF6_ENTRY 13
/* End: Added by a00900892. DTS modify for vrf6 show bind info */


typedef VOID * (*COM_WAITLIST_GETNEXTFUNC)(VOID *pFilter,VOID *pCurEntry);

/****************************************************************************
* subtype�ṹ��main type�ṹ��ͬ���һ���������:                           
*                     HEAD                                                  
*                        \                                                  
*            Main type    �ϡ��ϡ���                                        
*                        /     \                                            
*            handle       ��-�ϡ���-��-��                                   
****************************************************************************/

/****************************************************************************
*                        Handle�ṹ                                         
****************************************************************************/
typedef struct COM_FILTER_WAITLIST_HANDLE
{
    VOID        *pData;                          /* ����������ָ��            */
    VOID        *pFilterPoint;                /* ����pGetNextFunc�Ĳ���    */
    ULONG      ulPrivData;                  /*�û��Զ����˽�в���*/
    COM_WAITLIST_GETNEXTFUNC pfGetNextFunc;
    struct COM_FILTER_WAITLIST_HANDLE    *pstRBrother;  /* ���ֵ�ָ��                */
    struct COM_FILTER_WAITLIST_MAIN_TYPE    *pstParent; /* ���ڵ�ָ��                */
}COM_FILTER_WAITLIST_HANDLE_S;

/****************************************************************************
*                        main type�ṹ                                        
****************************************************************************/
typedef struct COM_FILTER_WAITLIST_MAIN_TYPE
{
    ULONG                 ulMainID;                  /* main type �ڵ�ID    */
    struct COM_FILTER_WAITLIST_MAIN_TYPE    *pstRBrother;   /* ���ֵ�ָ��          */
    struct COM_FILTER_WAITLIST_HANDLE    *pstFirstSon;      /* ��һ�����ӵ�ָ��    */
}COM_FILTER_WAITLIST_MAIN_TYPE_S;

typedef struct COM_WAITLIST_REG
{
    ULONG ulMainType;
    VOID *pFilter;                   /*������ָ�룬��ʹ�ù�����ʱ����ΪNULL*/
    ULONG ulSizeOfFilter;           /*�������ṹ��С�������ڴ�ʱʹ��*/
    ULONG ulPrivData;                /*�û��Զ����˽�в���*/
    COM_WAITLIST_GETNEXTFUNC pfGetNextFunc; /*֧�ֹ������Ļ�ȡ���������û�ʵ��*/
}COM_WAITLIST_REG_S;

ULONG COM_FilterWaitListRegister(UINTPTR *pulHandle,COM_WAITLIST_REG_S stWaitListReg,VOID *pFstEntry);

ULONG COM_FilterWaitListSet(UINTPTR ulHandle, VOID *pListData);

ULONG COM_FilterWaitListGet(UINTPTR ulHandle,VOID **ppListData );

ULONG COM_FilterWaitListGetParam(UINTPTR ulHandle, VOID **ppRetParam, ULONG *pulPrivData);

ULONG COM_FilterWaitListUnregister( UINTPTR ulHandle );

ULONG COM_FilterWaitListDelFromList(ULONG ulMainType, VOID *pDataToDel);
ULONG COM_FilterWaitListSetParam(UINTPTR ulHandle, ULONG ulPrivData);
    
#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _COM_WAITLIST_H_ */


