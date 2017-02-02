/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmCasSuspend.h
  Author      : Roger Leo
  Version     : V200R001
  Date        : 2005-10-21
  Description : GmmCasSuspendģ����ڲ�ͷ�ļ�
  History     :
  1. Date:2005-11-25
     Author: Roger Leo
     Modification:update
  2.��    ��   : 2006��08��09��
    ��    ��   : ����Ƽj60010247
    �޸�����   : ���ⵥA32D03479����PC����ʵ��ʱ��#pragma pack(0)��#pragma pack()�ӱ��뿪��
************************************************************************/

#ifndef _GMM_CAS_SUSPEND_H_
#define _GMM_CAS_SUSPEND_H_

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

VOS_UINT32 GMM_BufferMsgQueueIn(VOS_VOID);
VOS_UINT32 GMM_BufferMsgQueueOut(VOS_VOID);
VOS_UINT32 GMM_BufferMsgSend(VOS_VOID);
VOS_VOID GMM_BufferMsgResume(VOS_VOID);
VOS_VOID GMM_BufferMsgDump(VOS_VOID);
VOS_VOID GMM_BufferMsgReceive(struct MsgCB* pMsgIn);
VOS_VOID NAS_GMM_ClearMsgFromBuff(
        VOS_UINT32                     ulMsgName,
        VOS_UINT32                     ulSenderPid,
        VOS_UINT32                     ulReceiverPid
);
/*VOS_UINT8 GMM_IsExistMsgHold(VOS_UINT32 ulMask);*/
VOS_VOID  GMM_FreeCasMsgHoldBuf (VOS_VOID);
/*VOS_VOID  GMM_ResumeMsgHold(VOS_UINT32 ulMask, GMM_CAS_STATE CasType);*/

VOS_VOID GMM_RcvMmcSuspendInd(VOS_VOID* pRcvMsg);
VOS_VOID GMM_RcvMmcResumeInd(VOS_VOID* pRcvMsg);
VOS_VOID GMM_ResumeSuccess(VOS_VOID);
VOS_VOID GMM_ResumeFailure(VOS_VOID);

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

#endif /* end of GmmCasSuspend.h*/
