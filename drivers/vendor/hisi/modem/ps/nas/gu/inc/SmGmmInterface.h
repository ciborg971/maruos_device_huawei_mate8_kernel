

/*******************************************************************************
**************************  GMM��SM ԭ���ʶ  **********************************
*******************************************************************************/

#ifndef _SM_GMM_INTERFACE_H_
#define _SM_GMM_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
#pragma pack(4)


/* SM����GMM����Ϣ */
#define GMMSM_ESTABLISH_REQ                                 0
#define GMMSM_DATA_REQ                                      2
#define GMMSM_PDP_DEACTIVATED_IND                           (8)
#define GMMSM_PDP_MODIFY_IND                                (0x0A)

#define GMMSM_BEGIN_SESSION_NOTIFY                          (14)
#define GMMSM_END_SESSION_NOTIFY                            (16)

/* SM����GMM��ԭ�� */
#define GMMSM_ESTABLISH_CNF                                 1
#define GMMSM_DATA_IND                                      3
#define GMMSM_STATUS_IND                                    5
#define GMMSM_SERVICE_REJ                                   7
#define GMMSM_SYS_INFO_IND                                  9
#define GMMSM_REL_IND                                       11
/* SM��GMM֮���˫��ԭ�� */
#define GMMSM_PDP_STATUS_IND                                4 /* GMM�յ���ԭ����±���PDP״̬;
                                                                 ����ָʾPDP״̬ʱGMMͨ����ԭ��֪ͨSM*/
#define GMMSM_ABORT_REQ                                     12

#define GMMSM_SIG_CONN_IND                                  13

#define GMM_SM_CAUSE_GMM_SECTION_BEGIN      (0x0000)
#define GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN   (0x0100)

#define GMM_SM_CAUSE_GMM_NW_CAUSE_OFFSET    GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN



enum GMM_SM_CAUSE_ENUM
{
    /*----------------------------------------------------------------------
       GMM�ϱ����ڲ�ԭ��ֵ, ȡֵ��Χ[0x0000, 0x00FF]
       ����: GMM -> SM
       ˵��: UNKNOWNΪ������ֶε����һ��������
    *---------------------------------------------------------------------*/
    GMM_SM_CAUSE_SUCCESS                                = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 0),
    GMM_SM_CAUSE_GPRS_NOT_SUPPORT                       = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 1),
    GMM_SM_CAUSE_ATTACH_MAX_TIMES                       = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 2),
    GMM_SM_CAUSE_FORBID_LA                              = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 3),
    GMM_SM_CAUSE_AUTHENTICATION_FAIL                    = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 4),
    GMM_SM_CAUSE_AUTHENTICATION_REJ                     = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 5),
    GMM_SM_CAUSE_PS_DETACH                              = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 6),
    GMM_SM_CAUSE_RRC_EST_FAIL                           = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 7),
    GMM_SM_CAUSE_ACCESS_BARRED                          = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 8),
    GMM_SM_CAUSE_SIM_PS_DOMAIN_REG_INVALID              = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 9),
    GMM_SM_CAUSE_T3310_EXPIRED                          = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 10),
    GMM_SM_CAUSE_T3317_EXPIRED                          = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 11),
    GMM_SM_CAUSE_TIMER_SIGNALING_PROTECT_EXPIRED        = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 12),
    GMM_SM_CAUSE_STARTUP                                = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 13),
    GMM_SM_CAUSE_NULL                                   = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 14),
    GMM_SM_CAUSE_GMM_RESET                              = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 15),
    GMM_SM_CAUSE_LTE_MO_DETACH                          = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 16),
    GMM_SM_CAUSE_RAU_ACCEPT                             = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 17),
    GMM_SM_CAUSE_SERVICE_ACCEPT                         = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 18),
    GMM_SM_CAUSE_UNKNOWN                                = (GMM_SM_CAUSE_GMM_SECTION_BEGIN + 255),

    /*----------------------------------------------------------------------
       GMM�ϱ�������ԭ��ֵ, ȡֵ��Χ[0x0100, 0x01FF]
       ����: GMM -> SM
       ����3GPPЭ���Ѿ������˾����GMM����ԭ��ֵ, GMM�ϱ���ȡֵΪЭ�鶨��
       ��ԭ��ֵ����ƫ����(0x100),
       Gmm Cause: Refer to TS 24.008 section 10.5.5.14
    *---------------------------------------------------------------------*/
    GMM_SM_CAUSE_IMSI_UNKNOWN_IN_HLR                    = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 2),
    GMM_SM_CAUSE_ILLEGAL_MS                             = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 3),
    GMM_SM_CAUSE_IMSI_NOT_ACCEPTED                      = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 5),
    GMM_SM_CAUSE_ILLEGAL_ME                             = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 6),
    GMM_SM_CAUSE_GPRS_SERV_NOT_ALLOW                    = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 7),
    GMM_SM_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW  = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 8),
    GMM_SM_CAUSE_MS_ID_NOT_DERIVED                      = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 9),
    GMM_SM_CAUSE_IMPLICIT_DETACHED                      = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 10),
    GMM_SM_CAUSE_PLMN_NOT_ALLOW                         = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 11),
    GMM_SM_CAUSE_LA_NOT_ALLOW                           = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 12),
    GMM_SM_CAUSE_ROAMING_NOT_ALLOW_IN_LA                = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 13),
    GMM_SM_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN            = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 14),
    GMM_SM_CAUSE_NO_SUITABL_CELL                        = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 15),
    GMM_SM_CAUSE_MSC_UNREACHABLE                        = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 16),
    GMM_SM_CAUSE_NETWORK_FAILURE                        = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 17),
    GMM_SM_CAUSE_MAC_FAILURE                            = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 20),
    GMM_SM_CAUSE_SYNCH_FAILURE                          = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 21),
    GMM_SM_CAUSE_PROCEDURE_CONGESTION                   = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 22),
    GMM_SM_CAUSE_GSM_AUT_UNACCEPTABLE                   = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 23),
    GMM_SM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG            = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 25),
    GMM_SM_CAUSE_NO_PDP_CONTEXT_ACT                     = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 40),
    GMM_SM_CAUSE_RETRY_UPON_ENTRY_CELL                  = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 60),
    GMM_SM_CAUSE_SEMANTICALLY_INCORRECT_MSG             = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 95),
    GMM_SM_CAUSE_INVALID_MANDATORY_INF                  = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 96),
    GMM_SM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE             = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 97),
    GMM_SM_CAUSE_MSG_TYPE_NOT_COMPATIBLE                = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 98),
    GMM_SM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED             = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 99),
    GMM_SM_CAUSE_CONDITIONAL_IE_ERROR                   = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 100),
    GMM_SM_CAUSE_MSG_NOT_COMPATIBLE                     = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 101),
    GMM_SM_CAUSE_PROTOCOL_ERROR                         = (GMM_SM_CAUSE_GMM_NW_SECTION_BEGIN + 111),

    GMM_SM_CAUSE_BUTT
};
typedef VOS_UINT16 GMM_SM_CAUSE_ENUM_UINT16 ;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ     */    /* _H2ASN_Skip */

} GMMSM_ABORT_REQ_STRU;
#define GMMSM_PDP_STATE_INACTIVE                            (0)                 /* PDP�����ķǼ���״̬ */
#define GMMSM_PDP_STATE_ACTIVE                              (1)                 /* PDP�����ļ���״̬ */
#define GMMSM_PDP_STATE_ACTIVE_PENDING                      (2)                 /* PDP�����ļ��������״̬ */
#define GMMSM_PDP_STATE_INACTIVE_PENDING                    (3)               /* PDP������ȥ���������״̬ */
#define GMMSM_MAX_NSAPI_NUM                                 (11)                /* NSAPI�����ֵ */
/* ԭ��GMMSM_ESTABLISH_REQ�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */
}GMMSM_ESTABLISH_REQ_STRU;

/* ԭ��GMMSM_ESTABLISH_CNF�Ľṹ�� */
/* ulEstResult ȡֵ */
#define    GMM_SM_EST_SUCCESS       1                                           /* ע��ɹ�                                 */
#define    GMM_SM_EST_FAILURE       0                                           /* ע��ʧ��                                 */


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ              */

    VOS_UINT32                          ulEstResult ;       /* ע����            */
    GMM_SM_CAUSE_ENUM_UINT16            enCause;            /* GMM�ϱ���ʧ��ԭ��ֵ */
    VOS_UINT8                           aucRsv[2];          /* ���ֽڶ���          */
} GMMSM_ESTABLISH_CNF_STRU;

/* ԭ��GMMSM_STATUS_IND�Ľṹ�� */
/* ulGmmStatus ȡֵ */
#define  GMM_SM_STATUS_DETACHED              0                                           /* GMM״̬Ϊdetached                        */
#define  GMM_SM_STATUS_ATTACHED              1                                           /* GMM״̬Ϊattached                        */
/* GMM״̬Ϊattached,���յ������緵�ص�SERVICE_REJ_MSG,����
    Reject cause = "No PDP context activated"*/
#define  GMM_SM_SER_REJ_CAUSE_PDP_NOEXIT     2


enum GMM_SM_STATUS_IND_CAUSE_ENUM
{
    GMM_SM_STATUS_IND_CAUSE_LTE_MO_DETACH,       /* LTE mo detach */
    GMM_SM_STATUS_IND_CAUSE_BUTT
};
typedef VOS_UINT8 GMM_SM_STATUS_IND_CAUSE_ENUM_UINT32;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ                                   */

    VOS_UINT32                          ulGmmStatus;        /* GMM״̬ 0 : detached; 1 : attached       */
    GMM_SM_CAUSE_ENUM_UINT16            enCause;            /* GMM�ϱ���ʧ��ԭ�� */
    VOS_UINT8                           aucRsv[2];          /* ���ֽڶ��� */
} GMMSM_STATUS_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ                                   */

    /*ulPdpContextStatusȡֵ:��16λ��Ч����16λȡֵ����*/
    /*  7            6            5            4           3           2           1           0           bit                 */
    /*  NSAPI(12)    NSAPI(11)    NSAPI(10)    NSAPI(9)    NSAPI(8)    NSAPI(7)    NSAPI(6)    NSAPI(5)    octet 1             */
    /*  NSAPI(22)    NSAPI(19)    NSAPI(18)    NSAPI(17)   NSAPI(16)   NSAPI(15)   NSAPI(14)   NSAPI(13)   octet 2             */

    VOS_UINT8                           aucPdpContextStatus[GMMSM_MAX_NSAPI_NUM];  /* PDP context״̬                          */
    VOS_UINT8                           aucRsv1[1];
    GMM_SM_CAUSE_ENUM_UINT16            enCause ;           /* GMM�ϱ�ԭ��ֵ */
    VOS_UINT8                           aucRsv2[2];
} GMMSM_PDP_STATUS_IND_STRU;

/* ԭ��GMMSM_DATA_REQ�Ľṹ�� */
/* ulEstCause ȡֵ */
#define   GMM_SM_RRC_EST_CAUSE_ORG_ST_CALL      0                               /* Originating Subscribed traffic Call      */
#define   GMM_SM_RRC_EST_CAUSE_ORG_CONV_CALL    1                               /* Originating Conversational Call          */
#define   GMM_SM_RRC_EST_CAUSE_ORG_STM_CALL     2                               /* Originating Streaming Call               */
#define   GMM_SM_RRC_EST_CAUSE_ORG_INTER_CALL   3                               /* Originating Interactive Call             */
#define   GMM_SM_RRC_EST_CAUSE_ORG_BG_CALL      4                               /* Originating Background Call              */
#define   GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL    5                               /* Originating High Priority Signalling     */

#define   GMM_PDP_ACT_ERR_CODE_NULL             (0)                             /* ������Ϊ�� */


typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */
    VOS_UINT32              ulEstCause;                                         /* RRC Connection Setupԭ��                 */
    NAS_MSG_STRU            SmMsg;                                              /* SM MSG                                   */
}GMMSM_DATA_REQ_STRU;

/* ԭ��GMMSM_DATA_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */
    NAS_MSG_STRU            SmMsg;                                              /* SM MSG                                   */
}GMMSM_DATA_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */

    GMM_SM_CAUSE_ENUM_UINT16            enCause ;           /* GMM�ϱ�ԭ��ֵ */
    VOS_UINT8                           aucRsv[2];         /* ���ֽڶ��� */
} GMMSM_SERVICE_REJ_STRU;


/* ԭ��GMMSM_SYS_INFO_IND�Ľṹ�� */
enum
{
    GMMSM_SGSN_RELEASE98_OR_OLDER        = 0,
    GMMSM_SGSN_RELEASE99_ONWARDS         = 1,
    GMMSM_SGSN_REL_VER_BUTT
};
typedef VOS_UINT8   GMMSM_SGSN_REL_VER_ENUM;

typedef struct
{
    MSG_HEADER_STRU             MsgHeader;                  /* ��Ϣͷ */
    GMMSM_SGSN_REL_VER_ENUM     ucSgsnRelVer;               /* SGSN�汾��Ϣ */
    VOS_UINT8                   aucRsv[3];                  /* �ֽڶ��� */
}GMMSM_SYS_INFO_IND_STRU;

/* ��GMMĳЩ�������յ�PDP�������󣬻Ὣ��Ϣ���棬�ȴ�������ɺ��ͼ������󣬵����ܳ�����Ϣ����
   ��ȥ������಻��Ӧ���ͷ����ӵ����������T3380��ʱ��30�볬ʱ����ط�PDP���������û����鲻��*/
typedef struct
{
    MSG_HEADER_STRU             MsgHeader;                  /* ��Ϣͷ */
}GMMSM_REL_IND_STRU;

#define  GMM_SM_PDP_CONTEXT_NOT_EXIST        (0)
/* ԭ��GMMSM_PDP_DEACTIVATED_IND_STRU�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */

    /* ulPdpContextStatusȡֵ:��16λ��Ч����16λȡֵ���� */
    /*  8           7           6           5           4           3           2           1           bit                 */
    /*  NSAPI(7)    NSAPI(6)    NSAPI(5)    NSAPI(4)    NSAPI(3)    NSAPI(2)    NSAPI(1)    NSAPI(0)    octet 1             */
    /*  NSAPI(15)   NSAPI(14)   NSAPI(13)   NSAPI(12)   NSAPI(11)   NSAPI(10)   NSAPI(9)    NSAPI(8)    octet 2             */
    VOS_UINT32              ulPdpContextStatus;                                 /* PDP context״̬                          */
}GMMSM_PDP_DEACTIVATED_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU         stMsgHeader;                                        /* ��Ϣͷ */
    VOS_UINT8               ucNsapi;                                            /* ָ����NSAPI */
    VOS_UINT8               aucReserved[3];
}GMMSM_PDP_MODIFY_IND_STRU;




typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */
}GMMSM_SIG_CONN_IND_STRU;
enum GMMSM_SESSION_TYPE_ENUM
{
    GMMSM_SESSION_TYPE_CONVERSAT_CALL,
    GMMSM_SESSION_TYPE_STREAM_CALL,
    GMMSM_SESSION_TYPE_INTERACT_CALL,
    GMMSM_SESSION_TYPE_BACKGROUND_CALL,
    GMMSM_SESSION_TYPE_SUBSCRIB_TRAFFIC_CALL,
    GMMSM_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 GMMSM_SESSION_TYPE_ENUM_UINT8;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    GMMSM_SESSION_TYPE_ENUM_UINT8       enSessionType;
    VOS_UINT8                           aucReserved[3];
} GMMSM_BEGIN_SESSION_NOTIFY_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    GMMSM_SESSION_TYPE_ENUM_UINT8       enSessionType;
    VOS_UINT8                           aucReserved[3];
} GMMSM_END_SESSION_NOTIFY_STRU;


/*****************************************************************************
 ö����    : GMMSM_DATA_REQ_MSGTYPE_ENUM_UINT32
 Э����  :
 ö��˵��  : SM��GMMͨ��GMMSM_DATA_REQ����ʱ�������Ϣ����
*****************************************************************************/
enum GMMSM_DATA_REQ_MSGTYPE_ENUM
{
    SM_ACT_PDP_CONTEXT_REQ              = 0x41,
    SM_ACT_PDP_CONTEXT_ACC              = 0x42,
    SM_ACT_PDP_CONTEXT_REJ              = 0x43,
    SM_REQ_PDP_CONTEXT_ACT              = 0x44,
    SM_REQ_PDP_CONTEXT_REJ              = 0x45,
    SM_DEACT_PDP_CONTEXT_REQ            = 0x46,
    SM_DEACT_PDP_CONTEXT_ACC            = 0x47,
    SM_MOD_PDP_CONTEXT_REQ_N2M          = 0x48,
    SM_MOD_PDP_CONTEXT_ACC_M2N          = 0x49,                                 /* Modify PDP context accept (MS to network direction) */
    SM_MOD_PDP_CONTEXT_REQ_M2N          = 0x4A,                                 /* Modify PDP context request(MS to network direction)  */
    SM_MOD_PDP_CONTEXT_ACC_N2M          = 0x4B,                                 /* Modify PDP context accept (Network to MS direction) */
    SM_MOD_PDP_CONTEXT_REJ              = 0x4C,                                 /* Modify PDP context reject  */
    SM_ACT_SEC_PDP_CONTEXT_REQ          = 0x4D,                                 /* Activate secondary PDP context request   */
    SM_ACT_SEC_PDP_CONTEXT_ACC          = 0x4E,                                 /* Activate secondary PDP context accept    */
    SM_ACT_SEC_PDP_CONTEXT_REJ          = 0x4F,                                 /* SM_Activate secondary PDP context reject */
    SM_STATUS                           = 0x55,                                 /* SM_stasus */
    SM_DATA_REQ_MSGTYPE_BUTT
};
typedef VOS_UINT32 GMMSM_DATA_REQ_MSGTYPE_ENUM_UINT32;


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
