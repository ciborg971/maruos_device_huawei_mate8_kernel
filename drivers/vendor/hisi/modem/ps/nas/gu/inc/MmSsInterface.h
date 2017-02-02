/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MmSsInterface.h
  Description : Ss��Mm�ӿ�ͷ�ļ�
  History     :
      1. ��־��      2004.02.27   �°�����
      2.��    ��  : 2006��12��4��
        ��    ��  : luojian id:60022475
        �޸�����  : ���� #pragma pack(4)�����ⵥ��:A32D07779
*******************************************************************************/

#ifndef _MM_SS_INTERFACE_H_
#define _MM_SS_INTERFACE_H_

#include "MmCmInterface.h"
#include "ExtAppCmInterface.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
#pragma pack(4)

/* ԭ�����Ͷ��� */

/* MM-->SS */
#define MMSS_EST_CNF                                        1
#define MMSS_EST_IND                                        3
#define MMSS_DATA_IND                                       5
#define MMSS_REL_IND                                        7

/* SS-->MM */
#define MMSS_EST_REQ                                        0
#define MMSS_DATA_REQ                                       2
#define MMSS_REL_REQ                                        4
/* Added by cxd for 20050201 begin */
#define MMSS_ABORT_REQ                                      6
/* Added by cxd for 20050201 end   */

#define MMSS_BEGIN_SESSION_NOTIFY                           (8)
#define MMSS_END_SESSION_NOTIFY                             (10)
#define MMSS_SS_STATUS_NOTIFY                               (12)

/* SS_MSG_STRU�ṹ */
typedef struct
{
    VOS_UINT32                   ulSsMsgSize;                                        /* [1,MMCC_MAX_SIZE_SS_MSG],Byte           */
    VOS_UINT8                   aucSsMsg[4];                                        /* ��Ϣ��ǰ�ĸ��ֽ�����                       */
}SS_MSG_STRU;

/* MMSS_EST_REQ��Ϣ�ṹ */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ                                   */
    VOS_UINT32                          ulTi;                                   /* Transaction Id                          */
    VOS_UINT8                           ucRedialFlg;                            /* �ز���־ */
    VOS_UINT8                           aucReserve[3];
}MMSS_EST_REQ_STRU;

/* MMSS_EST_CNF��Ϣ�ṹ */
#define     MMSS_EST_SUCCESS     0
#define     MMSS_EST_FAIL        1
typedef struct
{
    MSG_HEADER_STRU       MsgHeader;                                            /* ��Ϣͷ                                   */
    VOS_UINT32                 ulTi;                                                 /* Transaction Id                          */
    VOS_UINT32                 ulResult;                                             /* �������                                 */
}MMSS_EST_CNF_STRU;

/* MMSS_EST_IND��Ϣ�ṹ */
typedef struct
{
    MSG_HEADER_STRU       MsgHeader;                                            /* ��Ϣͷ                                  */
    VOS_UINT32                 ulTi;                                                 /* Transaction Id                         */
    SS_MSG_STRU           SsMsg;                                                /* SS�տ���Ϣ����                           */
}MMSS_EST_IND_STRU;

/* MMSS_DATA_REQ��Ϣ�ṹ */
typedef struct
{
    MSG_HEADER_STRU       MsgHeader;                                            /* ��Ϣͷ                                  */
    VOS_UINT32                 ulTi;                                                 /* Transaction Id                         */
    SS_MSG_STRU           SsMsg;                                                /* SS�տ���Ϣ����                           */
}MMSS_DATA_REQ_STRU;

/* MMSS_DATA_IND��Ϣ�ṹ */
typedef struct
{
    MSG_HEADER_STRU       MsgHeader;                                            /* ��Ϣͷ                                  */
    VOS_UINT32                 ulTi;                                                 /* Transaction Id                         */
    SS_MSG_STRU           SsMsg;                                                /* SS�տ���Ϣ����                          */
}MMSS_DATA_IND_STRU;

/* MMSS_REL_REQ��Ϣ�ṹ */
typedef struct
{
    MSG_HEADER_STRU       MsgHeader;                                            /* ��Ϣͷ                                  */
    VOS_UINT32                 ulTi;                                                 /* Transaction Id                         */
}MMSS_REL_REQ_STRU;

/* MMSS_REL_IND��Ϣ�ṹ */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ                                  */
    VOS_UINT32                          ulTi;                                   /* Transaction Id                         */

    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmssRelCause;
}MMSS_REL_IND_STRU;


enum MMSS_SESSION_TYPE_ENUM
{
    MMSS_SESSION_TYPE_MO_SS,
    MMSS_SESSION_TYPE_MT_SS,
    MMSS_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 MMSS_SESSION_TYPE_ENUM_UINT8;


typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMSS_SESSION_TYPE_ENUM_UINT8                    enSessionType;
    VOS_UINT8                                       aucReserved[3];
} MMSS_BEGIN_SESSION_NOTIFY_STRU;
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMSS_SESSION_TYPE_ENUM_UINT8                    enSessionType;
    VOS_UINT8                                       aucReserved[3];
} MMSS_END_SESSION_NOTIFY_STRU;



typedef SSA_SS_STATUS_ENUM_UINT8 MMSS_STATUS_ENUM_UINT8;
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMSS_STATUS_ENUM_UINT8                          enSsStatus;
    VOS_UINT8                                       aucReserved[3];
} MMSS_STATUS_NTY_STRU;

/* Added by cxd for 20050201 begin */
/* ԭ��MMSS_ABORT_REQ�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                    */
    VOS_UINT32                   ulTransactionId;                                    /* TI                                       */
}MMSS_ABORT_REQ_STRU;
/* Added by cxd for 20050201 end   */
#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
