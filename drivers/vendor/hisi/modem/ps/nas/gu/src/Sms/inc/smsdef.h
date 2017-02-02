
#ifndef _SMS_MACRO_DEFINE_H_
#define _SMS_MACRO_DEFINE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */


#pragma pack(4)

/*****************************************************************************
 ö����    : NAS_SMS_TI_FLAG_ENUM
 �ṹ˵��  : TI flag����
             �ο�Э��24007 11.2.3.1.3
                0  The message is sent from the side that originates the TI
                1  The message is sent to the side that originates the TI
*****************************************************************************/
enum NAS_SMS_TI_FLAG_ENUM
{
    NAS_SMS_TI_FLAG_MSG_SEND_FROM_ORIG = 0,
    NAS_SMS_TI_FLAG_MSG_SEND_TO_ORIG   = 1,
    NAS_SMS_TI_FLAG_BUTT
};
typedef VOS_UINT8 NAS_SMS_TI_FLAG_ENUM_UINT8;



enum NAS_SMS_OM_MSG_ID_ENUM
{
    /* CC���͸�OM����Ϣ */
    SMSOM_LOG_STATE_INFO_IND                       = 0x1000,      /*_H2ASN_MsgChoice  NAS_SMS_LOG_STATE_INFO_STRU */

    SMSOM_LOG_BUTT
};
typedef VOS_UINT32 NAS_SMS_OM_MSG_ID_ENUM_U32;

#define SMS_TRUE            1
#define SMS_FALSE           0

/* ָ����Ч */
#define SMS_POINTER_NULL    0

/* CN DOMAIN */
#define SMS_CN_PS               0
#define SMS_CN_CS               1
#define SMS_CN_PS_PREFERRED     2
#define SMS_CN_CS_PREFERRED     3

/* TIMER״̬ */
#define SMS_TIMER_STATUS_RUN        0
#define SMS_TIMER_STATUS_STOP       1
/* TIMER EXPIRE */

#define SMC_TC1M_EXP_PROTOCOL_MIN_TIMES (1)
#define SMC_TC1M_EXP_PROTOCOL_MAX_TIMES (3)
/* CP-DATA��Ϣ���͵���С����Ϊ�ش�1��ʱ���͵�CP-DATA���� */
#define SMC_CP_DATA_MIN_TIMES           (SMC_TC1M_EXP_PROTOCOL_MIN_TIMES + 1)
/* CP-DATA��Ϣ���͵�������Ϊ�ش�3��ʱ���͵�CP-DATA���� */
#define SMC_CP_DATA_MAX_TIMES           (SMC_TC1M_EXP_PROTOCOL_MAX_TIMES + 1)

/* SMC�궨�� */

/* SMC MOʵ��״̬ */
#define SMC_MO_IDLE   0
#define SMC_MO_GMM_CONN_PENDING    1
#define SMC_MO_WAIT_FOR_CP_ACK     2
#define SMC_MO_WAIT_FOR_CP_DATA    3
#define SMC_MO_MM_CONN_PENDING     4
#define SMC_MO_MM_CONN_EST         5
#define SMC_MO_WAIT_TO_SND_CP_ACK  6

/* SMC MTʵ��״̬ */
#define SMC_MT_IDLE                 0
#define SMC_MT_WAIT_FOR_RP_ACK      1
#define SMC_MT_WAIT_FOR_CP_ACK      2
#define SMC_MT_MM_CONN_EST          3

/* CP-ERROR��Ϣ�е�ԭ��,                    */
#define   SMC_MSG_VALID                     255
#define   SMC_CP_ERR_MSG_INVALID            254
#define   SMC_CP_ERR_CAUSE_INIT             253
#define   SMC_CP_ERR_CAUSE_TIMRE_EXP        252
#define   SMS_CP_ERR_NETW_FAIL              17                                  /* Network failure                                      */
#define   SMS_CP_ERR_CONGEST                22                                  /* Congestion                                           */
#define   SMS_CP_ERR_INVALID_TI             81                                  /* Invalid Transaction Identifier value                 */
#define   SMS_CP_ERR_INCORR_MSG             95                                  /* Semantically incorrect message                       */
#define   SMS_CP_ERR_MANDA_INFO_ELEM_ERR    96                                  /* Mandatory information element error                  */
#define   SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT         97                          /* Message type non-existent or not implemented         */
#define   SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA       98                          /* Message not compatible with the SM protocol state    */
#define   SMS_CP_ERR_IE_NON_EXIS_OR_NOT_IMPLEMENT   99                          /* Information element non-existent or not implemented  */
#define   SMS_CP_ERR_PROT_ERR_UNSPEC                111                         /* Protocol error,unspecified                           */

/* data type */
#define SMC_DATA_TYPE_CP_DATA   1
#define SMC_DATA_TYPE_CP_ACK    4
#define SMC_DATA_TYPE_CP_ERR    16

/* SMC��Ϣͷ���� */
#define SMC_MSG_HDR_LEN         2
/* SMC������Ϣ����С���� */
#define SMC_SND_MSG_MIN_LEN     2
/* SMC����CP-ERR�ĳ��� */
#define SMC_CP_ERR_LEN          3
/* SMC����CP-ACK�ĳ��� */
#define SMC_CP_ACK_LEN          2
/* SMC������Ϣ����С���� */
#define SMC_RCV_MSG_CP_DATA_MIN_LEN   4


/* SMR�궨�� */

/* SMRʵ��״̬ */
#define SMR_IDLE                    0
#define SMR_WAIT_FOR_RP_ACK         1
#define SMR_WAIT_TO_SND_RP_ACK      2
#define SMR_WAIT_FOR_RETRANS_TIMER  3

/* RP ERROR CAUSE */
#define  SMR_ERR_CAUSE_MTI_MO_RP_ERROR                     4
#define  SMR_ERR_CAUSE_NET_OUT_OF_ORDER                    38
#define  SMR_ERR_CAUSE_TEMP_FAILURE                        41
#define  SMR_ERR_CAUSE_CONGESTION                          42
#define  SMR_ERR_CAUSE_RES_UNAVAIL                         47
#define  SMR_ERR_CAUSE_VALUE_INVALID_MR                    81
#define  SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR              96
#define  SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST            97
#define  SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE           98
#define  SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR                  111
#define  SMR_MSG_CHK_SUCCESS                               255
#define  SMR_MSG_TOO_SHORT_ERROR                           254
#define  SMR_ERR_UPPER_ABORT                               253
/* retrans define */
#define SMR_RETRANS_PERMIT      0
#define SMR_RETRANS_NO_PERMIT   1
#define SMR_RETRANS_PROCESS     2
#define SMR_RETRANS_ABORT       3

/* ��Ϣ���� */
#define SMR_NTM_DATA_TYPE_RP_DATA 1
#define SMR_NTM_DATA_TYPE_RP_ACK  3
#define SMR_NTM_DATA_TYPE_RP_ERR  5

#define SMR_MTN_DATA_TYPE_RP_DATA  0
#define SMR_MTN_DATA_TYPE_RP_ACK   2
#define SMR_MTN_DATA_TYPE_RP_ERR   4
#define SMR_MTN_DATA_TYPE_RP_SMMA  6

/* SMR AND SMC API MACRO DEFINE */

/* mm�����ͷ�ԭ�� */


#define SMR_SMC_REL_CAUSE_NORMAL     0
#define SMR_SMC_REL_CAUSE_DATA_ERR   1
#define SMR_SMC_REL_CAUSE_TR1M_EXP   2
#define SMR_SMC_REL_CAUSE_TR2M_EXP   3
#define SMR_SMC_REL_CAUSE_PS_MULTI   0xff       /* PS���������� */
#define SMR_SMC_ABORT_CAUSE_TR1M_EXP   0
#define SMR_SMC_ABORT_CAUSE_TR2M_EXP   1

/* #define SMS_SND_AUTO        0 */
/* #define SMS_SND_CS          1 */
/* #define SMS_SND_PS          2 */
#define SMS_SEND_DOMAIN_PS      0
#define SMS_SEND_DOMAIN_CS      1
#define SMS_SEND_DOMAIN_NO      4

#define  SMS_MM_COM_SRVDOMAIN_CS                       1/*��MM_COM_SRVDOMAIN_CS��Ӧ����ע��ͬ������*/
#define  SMS_MM_COM_SRVDOMAIN_PS                       2/*��MM_COM_SRVDOMAIN_PS��Ӧ����ע��ͬ������*/

#define NAS_SMS_MSG_SND_TO_SIDE_THAT_ORIGINATES_THE_TI      (0x08)
#define NAS_SMS_MSG_SND_FROM_SIDE_THAT_ORIGINATES_THE_TI    (0xF0)
#define NAS_SMS_TI_MASK                                     (0XF7)
#define NAS_SMS_MAX_MSG_SIZE                                (255)
#define LMM_SMS_SIGN_NO_EXIST                               (201)                                   /* �յ�LMM_SMS_ERR_IND��ϢĬ�ϵ�ʧ��ԭ��ֵ:�������Ӳ����� */

typedef struct
{
    VOS_UINT16                          usTc1mLength;
    VOS_UINT16                          usTr1mLength;
    VOS_UINT16                          usTr2mLength;
    VOS_UINT16                          usTramLength;
}SMS_TIMER_LENGTH_STRU;

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
