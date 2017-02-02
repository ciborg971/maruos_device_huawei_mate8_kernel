/********************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmsGmmInterface.h
  Description : SMS��GMM�ӿ�ͷ�ļ�
  History     :
      1.  ��־��   2004.02.24   �°�����
*******************************************************************************/
#ifndef _SMS_GMM_INTERFACE_H_
#define _SMS_GMM_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */


#pragma pack(4)

/* SMS����GMM����Ϣ                         */
#define PMMSMS_EST_REQ                                      1
#define PMMSMS_UNITDATA_REQ                                 5
#define PMMSMS_REL_REQ                                      7

#define GMMSMS_BEGIN_SESSION_NOTIFY                         (9)

/* SMS����GMM��ԭ��                         */
#define GMMSMS_REG_STATE_IND                                0
#define PMMSMS_EST_CNF                                      2
#define PMMSMS_UNITDATA_IND                                 4
#define PMMSMS_ERROR_IND                                    6
#define GMMSMS_SERVICE_STATUS_IND                           8

#define GMMSMS_END_SESSION_NOTIFY                           (10)

/* GMM����ԭ�� */
#define    GMM_SMS_SIGN_NO_EXIST          201
#define    GMM_SMS_SPEC_PROC_ONGOING      202

/* ԭ��GMMSMS_REG_STATE_IND�Ľṹ��         */
typedef struct
{
    MSG_HEADER_STRU            MsgHeader;                                       /* ��Ϣͷ                                   */
#define    GMM_SMS_REG_ATTACHED       0                                         /* �Ѿ�ע��                                 */
#define    GMM_SMS_REG_DETTACHED      1                                         /* û��ע��                                 */
    VOS_UINT32                      ulRegSts;                                        /* ע��״̬                                 */
}GMMSMS_REG_STATE_IND_STRU;


/* ԭ��PMMSMS_EST_REQ�Ľṹ��               */
typedef struct
{
    MSG_HEADER_STRU            MsgHeader;                                       /* ��Ϣͷ                                   */
    VOS_UINT32                      ulEstCause;                                      /* RRC���ӽ���ԭ��                          */
}PMMSMS_EST_REQ_STRU;

/* ԭ��PMMSMS_REL_REQ�Ľṹ��               */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                                          /* ��Ϣͷ                                   */
}PMMSMS_REL_REQ_STRU;

/* ԭ��PMMSMS_EST_CNF�Ľṹ��               */
typedef struct
{
    MSG_HEADER_STRU            MsgHeader;                                       /* ��Ϣͷ                                   */
}PMMSMS_EST_CNF_STRU;

/* ԭ��PMMSMS_UNITDATA_REQ�Ľṹ��          */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */
    NAS_MSG_STRU            SmsMsg;                                             /* SMS MSG                                  */
}PMMSMS_UNITDATA_REQ_STRU;

/* ԭ��PMMSMS_UNITDATA_IND�Ľṹ��          */
typedef struct
{
    MSG_HEADER_STRU     MsgHeader;                                              /* ��Ϣͷ                                   */
    NAS_MSG_STRU        SmsMsg;                                                 /* SMS MSG                                  */
} PMMSMS_UNITDATA_IND_STRU;
typedef struct
{
    VOS_UINT32                          ulNasMsgSize;       
    VOS_UINT8                           aucNasMsg[256];     
}NAS_MSG_TEMP_STRU;

typedef struct
{
    MSG_HEADER_STRU     MsgHeader;                                              /* ��Ϣͷ                                   */
    NAS_MSG_TEMP_STRU   SmsMsg;                                                 /* SMS MSG                                  */
} PMMSMS_UNITDATA_IND_TEMP_STRU;

/* ԭ��PMMSMS_ERROR_IND�Ľṹ��             */
typedef struct
{
    MSG_HEADER_STRU     MsgHeader;                                              /* ��Ϣͷ                                   */
    VOS_UINT32               ulCause;                                                /* ԭ��ֵ                                   */
} PMMSMS_ERROR_IND_STRU;

enum GMMSMS_SERVICE_STATUS_ENUM
{
    GMM_SMS_NO_SERVICE        = 0,
    GMM_SMS_NORMAL_SERVICE    = 1,
    GMM_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 GMMSMS_SERVICE_STATUS_ENUM_UINT32;

/* ԭ��GMMSMS_SERVICE_STATUS_IND�Ľṹ��         */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ                                   */
    GMMSMS_SERVICE_STATUS_ENUM_UINT32   enServiceSts;                           /* ����״̬                                 */
}GMMSMS_SERVICE_STATUS_IND_STRU;
enum GMMSMS_SESSION_TYPE_ENUM
{
    GMMSMS_SESSION_TYPE_MO_SMS,
    GMMSMS_SESSION_TYPE_MT_SMS,
    GMMSMS_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 GMMSMS_SESSION_TYPE_ENUM_UINT8;


typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    GMMSMS_SESSION_TYPE_ENUM_UINT8                  enSessionType;
    VOS_UINT8                                       aucReserved[3];
} GMMSMS_BEGIN_SESSION_NOTIFY_STRU;
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    GMMSMS_SESSION_TYPE_ENUM_UINT8                  enSessionType;
    VOS_UINT8                                       aucReserved[3];
} GMMSMS_END_SESSION_NOTIFY_STRU;


extern VOS_UINT32  NAS_SMS_IsPsDomainIdle(VOS_VOID);

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
