
/*暂不修改为_UTLDLL_H, 因为目前VISP代码中有些地方同时包含了utldll.h和vrp_dll.h*/
//#ifndef __VRP_SLL_H__  /* 升级DopraV2后vrp_sll.h改了预编译宏为__VRP_SLL_H__, */

#ifndef _VRP_SLL_H
#ifndef __VRP_SLL_H__
#define _VRP_SLL_H
#define __VRP_SLL_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */



/* Type Definition for SLL_NODE */
typedef struct SLL_NODE
{
    struct SLL_NODE  *pNext;      /* Points to The Next Node In The List  */
    UINTPTR       ulHandle;    /* Only used by user to store user data */
}SLL_NODE_S;


/* Type Definition For SLL Structure */
/* List is Organised as Singly Linked Cicular List */
typedef struct SLL
{
   SLL_NODE_S  Head;              /* Header List Node        */
   SLL_NODE_S  *Tail;             /* Tail Node               */
   VOS_UINT32  u4_Count;          /* Number Of Nodes In List */
}SLL_S;


/* This Macro get the handle value of SLL node */
#define SLL_GET_HANDLE( pNode ) \
        ((pNode)->ulHandle)


/* This Macro set the handle value of SLL node */
#define SLL_SET_HANDLE( pNode, ulValue ) \
        ((pNode)->ulHandle = (VOS_UINT32)(ulValue))


/* This Macro Initialises the SLL Structure */
#define SLL_Init( pList ) \
{\
    (pList)->Head.pNext = &(pList)->Head; \
    (pList)->Tail       = &(pList)->Head; \
    (pList)->u4_Count   = 0;\
}


/* This Macro Initialises the SLL Node */
#define SLL_Init_Node( pNode ) \
        (pNode)->pNext = 0;

/* This Macro Appends a Node to end of the List */
#define SLL_Add(pList,pNode) \
        SLL_Insert_In_Middle( (pList), (pList)->Tail, (pNode), &(pList)->Head )


/* This Macro Gives the Count of Number of Elements in the List */
#define SLL_Count( pList ) \
        ((pList)->u4_Count)


/* This Macro returns the First Element in the List */
#define SLL_First( pList ) \
        ((SLL_Count((pList)) == 0) ? VOS_NULL_PTR: (pList)->Head.pNext)


/* This Macro returns the Last Element in the List */
#define SLL_Last( pList ) \
        ((SLL_Count((pList)) == 0) ? VOS_NULL_PTR : (pList)->Tail)


/* This Macro returns the Element Next To `pNode` in the List */
#define SLL_Next( pList, pNode ) \
        (((pNode) == VOS_NULL_PTR) ? SLL_First(pList) : \
        (((pNode)->pNext == &(pList)->Head) ? VOS_NULL_PTR : (pNode)->pNext))


/* This mocro check if the node is in the list */
#define SLL_Is_Node_In_List( pNode ) \
        (pNode->pNext != VOS_NULL_PTR)


/* This Macro Is Useful For Scanning Through The Entire List */
/* pList -  List TO BE Scanned                               */
/* pNode -  Pointer To A Variable of Type `TypeCast` In      */
/*          Which The Nodes Are Returned One By One          */
/* Cast  -  Appropriate Cast(e.g. t_NODE *,When Ptr Is A     */
/*          Pointer To t_NODE Type).                         */
#define SLL_Scan( pList, pNode, TypeCast ) \
        for( pNode = (TypeCast)(SLL_First((pList))); \
             pNode != VOS_NULL_PTR; \
             pNode = (TypeCast)SLL_Next((pList),((SLL_NODE_S *)(pNode))) )
extern SLL_NODE_S* SLL_Find( SLL_S *pList, VOS_VOID *pKey, VOS_INT32 (*fnValCmp)(VOS_VOID *, SLL_NODE_S *) );

extern VOS_VOID    SLL_Insert_In_Middle( SLL_S *pList, SLL_NODE_S *pPrev, SLL_NODE_S *pMid, SLL_NODE_S *pNext );

extern VOS_VOID    SLL_Delete_In_Middle( SLL_S *pList, SLL_NODE_S *pPrev, SLL_NODE_S *pNode, SLL_NODE_S *pNext );

extern VOS_VOID    SLL_Delete( SLL_S *pList, SLL_NODE_S *pNode );

extern SLL_NODE_S* SLL_Get( SLL_S *pList );

extern VOS_VOID    SLL_Insert( SLL_S *pList, SLL_NODE_S *pPrev, SLL_NODE_S *pNode );

extern SLL_NODE_S* SLL_Previous( SLL_S *pList, SLL_NODE_S *pNode );

extern VOS_VOID    SLL_FreeAll( SLL_S *pList, VOS_VOID (*fnFree)(VOS_VOID *) );

extern VOS_INT32   SLL_Walk( SLL_S *pList, VOS_VOID (*fnVisit)(SLL_NODE_S *) );




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VRP_SLL_H__ */
#endif /* _VRP_SLL_H */


