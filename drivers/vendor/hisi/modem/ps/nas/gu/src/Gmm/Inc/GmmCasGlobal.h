/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmCasGlobal.h
  Author      : Roger Leo
  Version     : V200R001
  Date        : 2005-08-25
  Description : ������GMMģ�鹫�������ȫ�ֹ�������ݽṹ
  History     :
  1. Date:2005-08-25
     Author: Roger Leo
     Modification:update
  2.��    ��   : 2006��08��09��
    ��    ��   : ����Ƽj60010247
    �޸�����   : ���ⵥA32D03479����PC����ʵ��ʱ��#pragma pack(0)��#pragma pack()�ӱ��뿪��
  3.��    ��   : 2007��05��15��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ�ţ�A32D10978
************************************************************************/

#ifndef _GMM_CAS_GLOBAL_H_
#define _GMM_CAS_GLOBAL_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "GmmCasDef.h"


#pragma pack(4)         /* 1�ֽڶ��룬���ݽṹ���屣֤4�ֽڶ��� */
                        /* ����include�󣬲�Ӱ������ͷ�ļ���pack���� */
/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ��ӡ��������� */
#define GMM_PRINT_INFO                      PS_LOG_LEVEL_INFO
#define GMM_PRINT_NORMAL                    PS_LOG_LEVEL_NORMAL
#define GMM_PRINT_WARNING                   PS_LOG_LEVEL_WARNING
#define GMM_PRINT_ERROR                     PS_LOG_LEVEL_ERROR


/* ��ӡ����궨�� */
#ifndef SUBMOD_NULL
#define SUBMOD_NULL                         0
#endif


#define GMM_LOG_INFO(String)      \
            PS_NAS_LOG(WUEPS_PID_GMM, SUBMOD_NULL, GMM_PRINT_INFO, String)
#define GMM_LOG_NORM(String)      \
            PS_NAS_LOG(WUEPS_PID_GMM, SUBMOD_NULL, GMM_PRINT_NORMAL, String)
#define GMM_LOG_WARN(String)      \
            PS_NAS_LOG(WUEPS_PID_GMM, SUBMOD_NULL, GMM_PRINT_WARNING, String)
#define GMM_LOG_ERR(String)       \
            PS_NAS_LOG(WUEPS_PID_GMM, SUBMOD_NULL, GMM_PRINT_ERROR, String)


/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
/* ָ�룫ȫ�ֱ�ʶ�����ͣ�ģ�������������� */
/* GMM�ڲ����õ�ȫ�ֱ������� */
extern GMM_CAS_CTRL_STRU        gstGmmCasGlobalCtrl;        /* GMM CASȫ�ֿ��ƽṹ���� */
extern GMM_CAS_MSG_BUFFER_STRU  gstGmmCasMsgBuf;            /* ������Ϣ�������� */

/*extern VOS_UINT8                gaucGmmNasMsgTmp[GMM_NAS_MSG_DATA_MAX];*/          /* ����NAS��Ϣ����ʱ������ */
/*extern VOS_UINT8                gaucGmmLlcDataReq[GMM_LLC_MSG_PDULEN_MAX];*/      /* ��LLC����data req����Ϣ�������� */
/*extern const GMM_CELL_FUN_TYPE* apfGmmCasStateTable[GMM_MATRIX_EVENT_MAX];*/


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

#endif /* end of GmmCasGlobal.h*/
