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

#ifndef _WAITLIST_H_
#define _WAITLIST_H_

#ifdef    __cplusplus
extern "C"{
#endif

#define        VOS_WAITLIST_SUCCESS             0
#define        ERR_WAITLIST_INVALID_MAINTYPE    1
#define        ERR_WAITLIST_INVALID_SUBTYPE     2
#define        ERR_WAITLIST_NOMEM               3
#define        ERR_WAITLIST_INVALID_HANDLE      4

/* �õ���һ������ָ��ĺ��� */
typedef VOID * (*WAITLIST_GETNEXTFUNC)(VOID *pParam,VOID **pNewParam);

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
typedef struct VOS_WAITLIST_HANDLE
{
    VOID        *pData;                          /* ����������ָ��            */
    WAITLIST_GETNEXTFUNC    pfGetNextFunc;       /* �õ���һ������ָ��ĺ���  */
    VOID        *pParamOfGetNext;                /* ����pGetNextFunc�Ĳ���    */
    struct VOS_WAITLIST_HANDLE    *pstRBrother;  /* ���ֵ�ָ��                */
    struct VOS_WAITLIST_MAIN_TYPE    *pstParent; /* ���ڵ�ָ��                */
}VOS_WAITLIST_HANDLE_S;

/****************************************************************************
*                        main type�ṹ                                        
****************************************************************************/
typedef struct VOS_WAITLIST_MAIN_TYPE
{
    ULONG                 ulMainID;                  /* main type �ڵ�ID    */
    struct VOS_WAITLIST_MAIN_TYPE    *pstRBrother;   /* ���ֵ�ָ��          */
    struct VOS_WAITLIST_HANDLE    *pstFirstSon;      /* ��һ�����ӵ�ָ��    */
}VOS_WAITLIST_MAIN_TYPE_S;

ULONG VOS_WaitListRegister(ULONG ulMainType, UINTPTR *pulHandle, WAITLIST_GETNEXTFUNC pfGetNextFunc );

ULONG VOS_WaitListSet(UINTPTR ulHandle, VOID *pListData, VOID *pParamOfGetNext );

ULONG VOS_WaitListGet(UINTPTR ulHandle,VOID **ppListData );

ULONG VOS_WaitListGetParam(UINTPTR ulHandle, VOID **ppRetParam);

ULONG VOS_WaitListDelFromList(ULONG ulMainType, VOID *pDataToDel );

ULONG VOS_WaitListUnregister( UINTPTR ulHandle );


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _WAITLIST_H_ */


