/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MmSelf.h
  Author      : sxbo
  Version     : V200R001
  Date        : 2005-08-15
  Description : ��ͷ�ļ�������MMģ���������ݽṹ���궨��
  History     :
  1. Date:2005-08-15
     Author: sxbo
     Modification:Create
  2.��    ��   : 2006��08��09��
    ��    ��   : ����Ƽj60010247
    �޸�����   : ���ⵥA32D03479����PC����ʵ��ʱ��#pragma pack(0)��#pragma pack()�ӱ��뿪��
************************************************************************/

#ifndef _MM_SELF_H_
#define _MM_SELF_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
 #define MM_ZERO                        0

 #define MM_MSGDISPATCH                 1
 #define MM_SUSPEND                     2
 #define MM_AUTH                        3
 #define MM_GSMDIFMSG                   4
 #define MM_ORIGIN                      5

 #define MM_MAX_MSG_NUM                 10
 #define MM_MAX_MSG_LENGTH              1000


 #define NAS_LOG(ModulePID, SubMod, Level, String)                               PS_NAS_LOG(ModulePID, SubMod, Level, String)
 #define NAS_LOG1(ModulePID, SubMod, Level, String, Para)                        PS_NAS_LOG1(ModulePID, SubMod, Level, String, Para)
 #define NAS_LOG2(ModulePID, SubMod, Level, String, Para1, Para2)                PS_NAS_LOG2(ModulePID, SubMod, Level, String, Para1, Para2)
 #define NAS_LOG3(ModulePID, SubMod, Level, String, Para1, Para2, Para3)         PS_NAS_LOG3(ModulePID, SubMod, Level, String, Para1, Para2, Para3)
 #define NAS_LOG4(ModulePID, SubMod, Level, String, Para1, Para2, Para3, Para4)  PS_NAS_LOG4(ModulePID, SubMod, Level, String, Para1, Para2, Para3, Para4)

 /*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*Identification ��ʶ��MM_SUSPEND_MSG_CELL_ST
Type ���ͣ�
PurposeĿ�ģ����л���С����ѡ״̬�»�����Ϣ��������Ϣ��Ԫ */
typedef struct
{
    VOS_VOID                           *pstMsg;                       /* ������Ϣ���� */
    VOS_UINT8                           ucEventId;                    /* ����Ϣ��Ӧ�¼�ID  */
}MM_SUSPEND_MSG_CELL_ST;

/* Identification ��ʶ��MM_SUSPEND_MSG_BUF_ST
Type ���ͣ�
PurposeĿ�ģ����л���С����ѡ״̬�»�����Ϣ�Ķ��� */
typedef struct
{
    MM_SUSPEND_MSG_CELL_ST              astMsg[MM_MAX_MSG_NUM];
    VOS_UINT8                           ucMsgNum;           /* ������Ϣ����Ŀ     */
    /* ������Ϣ����,����ʱ����ʾ���鵱ǰ����λ�ã��ָ�ʱ����ʾҪ�ָ���Ϣλ�� */
    VOS_UINT8                           ucIndex;
    /* ����ľ�����Ϣ�ṹ */

}MM_SUSPEND_MSG_BUF_ST;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MmSelf.h */
