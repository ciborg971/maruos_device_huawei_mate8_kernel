/******************************************************************************

                  ��Ȩ���� (C), 2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : BST_PAL_LIST_LIB.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2015��07��14��
  ����޸�   :
  ��������   : BST_PAL_LIST_LIB.c��ͷ�ļ�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��07��14��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __BST_LIB_List_H__
#define __BST_LIB_List_H__

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Typedefine.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define lstFirst              BST_ListFirst
#define lstGet                BST_ListGet
#define lstNext               BST_ListNext
#define lstCount              BST_ListCount
#define lstAdd                BST_ListAdd
#define lstDelete             BST_ListDelete
#define lstFree               BST_ListFree
#define lstInit               BST_ListInit
/*****************************************************************************
  3 ��/�ṹ����
*****************************************************************************/
typedef struct BST_node
{
    struct BST_node *next;
    struct BST_node *previous;
} BST_NODE;

typedef struct
{
    BST_NODE    node;
    BST_INT16   count;
}BST_LIST;

typedef BST_NODE NODE;
typedef BST_LIST LIST;

/*****************************************************************************
  4 ��������
*****************************************************************************/
extern NODE *       BST_ListFirst (LIST *pList);
extern NODE *       BST_ListGet (LIST *pList);
extern NODE *       BST_ListNext (NODE *pNode);
extern BST_INT16    BST_ListCount (LIST *pList);
extern BST_VOID     BST_ListAdd (LIST *pList, NODE *pNode);
extern BST_VOID     BST_ListDelete (LIST *pList, NODE *pNode);
extern BST_VOID     BST_ListFree (LIST *pList);
extern BST_VOID     BST_ListInit (LIST *pList);

#ifdef __cplusplus
}
#endif

#endif
