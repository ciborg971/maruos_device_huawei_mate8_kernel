/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmCasTimer.h
  Author      : Roger Leo
  Version     : V200R001
  Date        : 2005-11-17
  Description : GmmCasTimerģ����ڲ�ͷ�ļ�
  History     :
  1. Date:2005-11-17
     Author: Roger Leo
     Modification:update
  2.��    ��   : 2006��08��09��
    ��    ��   : ����Ƽj60010247
    �޸�����   : ���ⵥA32D03479����PC����ʵ��ʱ��#pragma pack(0)��#pragma pack()�ӱ��뿪��
************************************************************************/

#ifndef _GMM_CAS_TIMER_H_
#define _GMM_CAS_TIMER_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#pragma pack(4)         /* 1�ֽڶ��룬���ݽṹ���屣֤4�ֽڶ��� */
                        /* ����include�󣬲�Ӱ������ͷ�ļ���pack���� */
/*****************************************************************************
  2 �궨��
*****************************************************************************/

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

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

VOS_UINT32 GMM_CasCellS4E1(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS11E1(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS14E1(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E1(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS8E2(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E2(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS4E3(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS9E3(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E3(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS9E4(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS12E4(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E4(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E5(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E5(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS20E6(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E6(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E7(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E7(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E8(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E8(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS16E9(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS18E9(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E9(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS19E10(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E10(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS1E11(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E11(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E12(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E12(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E13(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS22E13(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS0E14(VOS_VOID *pRcvMsg);
VOS_VOID   GMM_CasCellS0E15(VOS_VOID);
VOS_VOID   GMM_CasCellS9E15(VOS_VOID);
VOS_UINT32 GMM_CasCellS22E15(VOS_VOID *pRcvMsg);
VOS_UINT32 GMM_CasCellS23E15(VOS_VOID *pRcvMsg);

VOS_VOID   GMM_TimReadyExpired(VOS_VOID);
VOS_VOID   GMM_TimRauRspExpired(VOS_VOID);

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

#endif /* end of GmmCasTimer.h*/
