/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : stac_typ.h
  �� �� ��   : ����
  ��    ��   : luofang
  ��������   : 2012��11��8��
  ����޸�   :
  ��������   : PPPģ��Stac�ṹ�嶨��
  �����б�   :
*
*

  �޸���ʷ   :
  1.��    ��   : 2012��11��8��
    ��    ��   : luofang
    �޸�����   : �����ļ�

******************************************************************************/

#if( VRP_MODULE_STAC == VRP_YES )

#ifndef		_STAC_TYP_H_
#define		_STAC_TYP_H_

#ifdef	__cplusplus
extern "C"{
#endif

/***************************************************************************/
typedef struct tagStacHashMatch
{
    USHORT    m_usLength;                        /*length of match*/
    USHORT    m_usOffset;					     /*offset of match*/
    UCHAR     ucStacHashMatchRev[4];             /*�����ֶ�*/
} STAC_HASH_MATCH_S;
/***************************************************************************/
/*hash��ֲ��Ľṹ*/

typedef struct tagStacHashMinList
{
    struct tagStacHashMinNode * pstHash_Head;         /*          hash��������             */
}STAC_HASH_MINLIST_S;

typedef struct tagStacHashMinNode 
{
	USHORT  m_usSucc;				   /*           hash��ڵ��ǰ��          */
    USHORT  m_usPred;				   /*           hash��ڵ�ĺ��          */
    UCHAR   ucStacHashMinNodeRev[4];             /*�����ֶ�*/
}STAC_HASN_MINNODE_S;

typedef struct tagStacHashNode
{  

	struct tagStacHashMinNode  stHash_Node;            /* Node linkage monkey stuff.           */
	USHORT usHistoryBuf_Offset;          /* Offset in stream of node's data.     */
    UCHAR  ucStacHashNodeRev[6];                /*�����ֶ�*/
    
}STAC_HASH_HASHNODE_S;

typedef struct tagStacHashTable
{
    STAC_HASH_MINLIST_S  * pstHashTable_Lists;			/* Array of lists of hash nodes.        */
    struct tagStacHashNode * pstHashTable_Nodes;  /* Array of all hash nodes.             */
    ULONG             usHashTable_NodeCount;     /* Total number of nodes in pstHashTable_Nodes.   */
    ULONG             ulHashTable_NextNode;      /* Next node index to re-use.           */
    UCHAR             ucHashTable_Recycled;      /* Cycled flag                          */
    UCHAR             ucStacHashTableRev[7];     /*�����ֶ�*/
}STAC_HASH_TABLE_S;


/***************************************************************************/

#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif

#endif	/*end of the *.h file*/
