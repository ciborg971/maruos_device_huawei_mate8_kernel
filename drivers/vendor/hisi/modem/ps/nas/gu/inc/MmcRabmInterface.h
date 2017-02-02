/******************************************************************************

                  ��Ȩ���� (C), 2005-2007, ��Ϊ�������޹�˾


  �� �� ��   : MmcRabmInterface.h
  �� �� ��   : ����
  ��    ��   : liuyang id:48197
  ��������   : 2006��5��4��
  ����޸�   :
  ��������   : MMC��RABM�ӿ��ļ�
  �����б�   :
      ---
      ---
      ---
  �޸���ʷ   :
  1.��    ��   : 2006��5��4��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ļ�
  2.��    ��   : 2006��5��4��
    ��    ��   : ---
    �޸�����   : Add function ... ���ⵥ��:
  3.��    ��  : 2006��12��4��
    ��    ��  : luojian id:60022475
    �޸�����  : ���� #pragma pack(4)�����ⵥ��:A32D07779
******************************************************************************/

#ifndef _MMC_RABM_INTERFACE_H_
#define _MMC_RABM_INTERFACE_H_


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/******************************************************************************
   1 ͷ�ļ�����
 *****************************************************************************/
#include "vos.h"
/*****************************************************************************
   2 �ڲ�����ԭ��˵��
 *****************************************************************************/

/*****************************************************************************
   3 ȫ�ֱ�������
 *****************************************************************************/

/*****************************************************************************
   4 ģ�鼶����
 *****************************************************************************/

/*****************************************************************************
   5 ��������
 *****************************************************************************/

/*****************************************************************************
   6 �궨��
 *****************************************************************************/
#pragma pack(4)
/* MMC->RABM */
#define MMCRABM_SUSPEND_IND                                   2
#define MMCRABM_RESUME_IND                                    4

/* RABM->MMC */
#define MMCRABM_SUSPEND_RSP                                   1

/***********************�����ӿ�MMC��>RABM***************************/
/* ��Ϣ MMCRABM_SUSPEND_IND �ṹ�� */
/* ucSuspendCause ȡֵ */
#define MMCRABM_SUSPEND_CAUSE_HANDOVER                  0x00
#define MMCRABM_SUSPEND_CAUSE_CELLRESELECT              0x01
#define MMCRABM_SUSPEND_CAUSE_CELLCHANGE                0x02

/* ucSuspendOrigen/ucResumeOrigen ȡֵ */
#define MMCRABM_SUSPEND_ORIGEN_GSM                      0x00
#define MMCRABM_SUSPEND_ORIGEN_WCDMA                    0x01

typedef enum
{
    MMCRABM_2G_TO_3G_ENUM = 0,
    MMCRABM_3G_TO_2G_ENUM,

    MMCRABM_SYS_CHANGE_ENUM_BUTT
}MMCRABM_SYS_CHANGE_DIR_ENUM;

typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;
    MMCRABM_SYS_CHANGE_DIR_ENUM     SysChangeDir;
}MMCRABM_SUSPEND_IND_ST;


/* ��Ϣ MMCRABM_RESUME_IND �ṹ�� */
/* ResumeResult ȡֵ */
#define MMCRABM_RESUME_RESULT_SUCCESS    0x00
#define MMCRABM_RESUME_RESULT_FAILURE    0x01
#define MMCRABM_RESUME_GPRS_SUSPENSION   0x02

/* ucResumeOrigen ȡֵ */
#define MMCRABM_RESUME_ORIGEN_GSM        0x00
#define MMCRABM_RESUME_ORIGEN_WCDMA      0x01

typedef enum
{
    MMCRABM_3G_ENUM = 0,
    MMCRABM_2G_ENUM
}MMCRABM_CUR_NET_ENUM;

typedef enum
{
    MMCRABM_SUCC_ENUM = 0,
    MMCRABM_FAIL_ENUM
}MMCRABM_SYS_CHANGE_RESULT_ENUM;

typedef struct
{
    MSG_HEADER_STRU                   MsgHeader;
    MMCRABM_SYS_CHANGE_DIR_ENUM       SysChangeDir;     /* ֪ͨRABM�л�״̬�ı䷽�� */
    MMCRABM_CUR_NET_ENUM              CurNet;           /* ��ǰRABM����״̬ */
    VOS_UINT32                        ulPsResumeResult; /* PS���л���� */
}MMCRABM_RESUME_IND_ST;

/***********************�����ӿ�RABM��>MMC***************************/
/*��Ϣ MMCRABM_SUSPEND_RSP �ṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;
    VOS_UINT32              ulReserved;                     /* ����*/
}MMCRABM_SUSPEND_RSP_ST;


/*****************************************************************************
   7 ���⺯���ӿ�˵��
 *****************************************************************************/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

#endif


