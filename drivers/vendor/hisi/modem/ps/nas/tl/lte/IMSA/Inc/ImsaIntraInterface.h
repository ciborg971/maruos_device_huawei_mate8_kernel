

#ifndef __IMSAINTRAINTERFACE_H__
#define __IMSAINTRAINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "ImsaErrlogInterface.h"
#endif
/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/


/* the size for intra msg queue */
#define IMSA_INTRA_MSG_MAX_NUM          (6)
#define IMSA_INTRA_MSG_MAX_SIZE         512

#define IMSA_START_SRV_RESULT_CAN_MAKE_CALL                 (0)
#define IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL              (1)
#define IMSA_START_SRV_RESULT_BUFFER_CALL_WAIT_INDICATION   (2)

#define IMSA_CONN_REG_PARA_INVALID      (0)
#define IMSA_CONN_REG_PARA_VALID        (1)

#define IMSA_IPV4_ADDR_LEN      (4)
#define IMSA_IPV6_ADDR_LEN      (16)

#define IMSA_IPV6_ADDR_PREFIX_LEN       (8)

#define IMSA_IPV6_ADDR_PREFIX_BIT_LEN       (64)

#define IMSA_IPV6_STRING_PREFIX_LEN     (46)
#define IMSA_IPV4_STRING_PREFIX_LEN     (15)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
 ö����    : IMSA_CONTROL_CONN_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �ڲ���ϢID����
*****************************************************************************/
enum    IMSA_INTRA_MSG_ID_ENUM
{
    /* CONTROL����REG����Ϣԭ�� */
    ID_IMSA_REG_REG_REQ                 = 0x000,                /* _H2ASN_MsgChoice IMSA_REG_REG_REQ_STRU */
    ID_IMSA_REG_DEREG_REQ               = 0x001,                /* _H2ASN_MsgChoice IMSA_REG_DEREG_REQ_STRU */

    /* REG����CONTROL����Ϣԭ�� */
    ID_IMSA_REG_REG_IND                 = 0x010,                /* _H2ASN_MsgChoice IMSA_REG_REG_IND_STRU */
    ID_IMSA_REG_DEREG_IND               = 0x011,                /* _H2ASN_MsgChoice IMSA_REG_DEREG_IND_STRU */

    /* CONTROL����CONN����Ϣԭ�� */
    ID_IMSA_CONN_SETUP_REQ              = 0x100,                /* _H2ASN_MsgChoice IMSA_CONN_SETUP_REQ_STRU */
    ID_IMSA_CONN_REL_REQ                = 0x101,                /* _H2ASN_MsgChoice IMSA_CONN_REL_REQ_STRU */

    /* CONN����CONTROL����Ϣԭ�� */
    ID_IMSA_CONN_SETUP_IND              = 0x110,                /* _H2ASN_MsgChoice IMSA_CONN_SETUP_IND_STRU */
    ID_IMSA_CONN_REL_IND                = 0x111,                /* _H2ASN_MsgChoice IMSA_CONN_REL_IND_STRU */
    ID_IMSA_CONN_MODIFY_IND             = 0x112,                /* _H2ASN_MsgChoice IMSA_CONN_MODIFY_IND_STRU */


    /* CONTROL��CALLģ�����Ϣ*/
    ID_IMSA_NRM_CALL_SRV_STATUS_IND     = 0x200,                /* _H2ASN_MsgChoice IMSA_NRM_CALL_SRV_STATUS_IND_STRU */
    ID_IMSA_EMC_CALL_SRV_STATUS_IND     = 0x201,                /* _H2ASN_MsgChoice IMSA_EMC_CALL_SRV_STATUS_IND_STRU */

    /* CALLģ���CONTROLģ�����Ϣ */
    ID_IMSA_CALL_RESULT_ACTION_IND      = 0x210,                /* _H2ASN_MsgChoice IMSA_CALL_RESULT_ACTION_IND_STRU */

    /* ����HIDS����ʾNIC PDP INFO */
    ID_IMSA_NIC_PDP_INFO_IND            = 0x220,                /* _H2ASN_MsgChoice IMSA_PRINT_NIC_PDP_INFO_STRU */

    /* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
    /* ����HIDS��ʾHIFI���ƶ������ */
    ID_IMSA_HIFI_DATA_INFO_IND          = 0x221,                /* _H2ASN_MsgChoice IMSA_HIFI_DATA_INFO_IND_STRU */
    /* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */

    ID_IMSA_INTRA_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 IMSA_INTRA_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
    ö����    : IMSA_REG_RESULT_ENUM
    ö��˵��  : IMSע����
*****************************************************************************/
enum IMSA_REG_RESULT_ENUM
{
    IMSA_REG_RESULT_SUCCESS             = 0,    /**< ע��ģ������ִ�гɹ� */
    IMSA_REG_RESULT_FAIL                = 1,    /**< ע��ģ������ִ��ʧ�� */
    IMSA_REG_RESULT_FAIL_REMOTE         = 2,    /**< ���������ܾ�������ܾ�ԭ��ֵ�����Ӧ���ݽṹ�е�Status Code�����ݲ�ͬ��ԭ��ֵ���ܻ�Я��һЩ������ͷ�� */
    IMSA_REG_RESULT_FAIL_TIMEOUT        = 3,    /**< ���ͻ����SIP���ĳ�ʱ�����峬ʱ�Ķ�ʱ�������Ӧ���ݽṹ�е� Timer Id */
    IMSA_REG_RESULT_FAIL_TRANSPORT      = 4,    /**< ���ͻ����SIP����ʱ���ײ㴫�䷢������ */
    IMSA_REG_RESULT_FAIL_SA             = 5,    /**< ע��ɹ��󣬰�ȫ���˷����쳣 */
    IMSA_REG_RESULT_FAIL_MT_DEREG       = 6,    /**< ע��ɹ������෢���ȥע�� */
    IMSA_REG_RESULT_FAIL_NO_ADDR_PAIR   = 7,    /**< û�п�����ʹ�õ�ע���ַ�� */
    IMSA_REG_RESULT_FAIL_LACK_PARAM     = 8,    /**< ע���������û��׼���걸 */
    IMSA_REG_RESULT_BUTT
};
typedef VOS_UINT32 IMSA_REG_RESULT_ENUM_UINT32;

/*****************************************************************************
    ö����    : IMSA_REG_ADDR_PARAM_ENUM
    ö��˵��  : IMSע��ʱʹ�õĵ�ַ����Ϣ
*****************************************************************************/
enum IMSA_REG_ADDR_PARAM_ENUM
{
    IMSA_REG_ADDR_PARAM_NEW,            /**< ע���ַʹ�õ�ַ���еĵ�һ�� */
    IMSA_REG_ADDR_PARAM_SAME,           /**< ʹ�ú͵�ǰ��ͬ�ĵ�ַ�ԣ����û����ע�᷵��ʧ�� */
    IMSA_REG_ADDR_PARAM_NEXT,           /**< ʹ����һ�����õĵ�ַ�ԣ����û����ע�᷵��ʧ�� */
    IMSA_REG_ADDR_PARAM_RESTORATION,    /**< ���������P-CSCF��ַ����ʹ������P-CSCF��ַ�����û�У���ʹ�õ�ǰP-CSCF��ַ */
    IMSA_REG_ADDR_PARAM_BUTT
};
typedef VOS_UINT32 IMSA_REG_ADDR_PARAM_ENUM_UINT32;

/*****************************************************************************
    ö����    : IMSA_REG_TYPE_ENUM
    ö��˵��  : IMSע������
*****************************************************************************/
enum    IMSA_REG_TYPE_ENUM
{
    IMSA_REG_TYPE_NORMAL                = 0,        /**< ��ͨע�� */
    IMSA_REG_TYPE_EMC                   = 1,        /**< ����ע�� */
    IMSA_REG_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_REG_TYPE_ENUM_UINT8;

/*****************************************************************************
    ö����    : IMSA_REG_RETRY_POLICY_ENUM
    ö��˵��  : IMSע���Զ����Բ���
*****************************************************************************/
enum    IMSA_REG_RETRY_POLICY_ENUM
{
    IMSA_REG_RETRY_POLICY_DISABLE,             /**< ���Զ���������ע�᳢�� */
    IMSA_REG_RETRY_POLICY_PERIODIC,            /**< �����Խ�������ע�᳢�� */
    IMSA_REG_RETRY_POLICY_RFC5626,             /**< ����RFC5626��������ע�᳢�� */
    IMSA_REG_RETRY_POLICY_BUTT
};
typedef VOS_UINT32 IMSA_REG_RETRY_POLICY_ENUM_UINT32;

/*****************************************************************************
    ö����    : IMSA_PDP_TYPE_ENUM
    ö��˵��  : IMSA IP��ַ����ö��
*****************************************************************************/
enum IMSA_IP_TYPE_ENUM
{
    IMSA_IP_TYPE_IPV4                   = 0x01,
    IMSA_IP_TYPE_IPV6                   = 0x02,
    IMSA_IP_TYPE_IPV4V6                 = 0x03,

    IMSA_IP_TYPE_BUTT                   = 0xFF
};
typedef VOS_UINT8 IMSA_IP_TYPE_ENUM_UINT8;


enum IMSA_PF_TRANS_DIRECTION_ENUM
{
    IMSA_PF_TRANS_DIRECTION_PRE_REL7     = 0x00,             /* 0 - Pre-Release 7 TFT filter (see 3GPP TS 24.008 [8], table 10.5.162) */
    IMSA_PF_TRANS_DIRECTION_UPLINK       = 0x01,             /* 1 - Uplink */
    IMSA_PF_TRANS_DIRECTION_DOWNLINK     = 0x02,             /* 2 - Downlink */
    IMSA_PF_TRANS_DIRECTION_BIDIRECTION  = 0x03,             /* 3 - Birectional (Up & Downlink) (default if omitted) */

    IMSA_PF_TRANS_DIRECTION_BUTT         = 0xFF
};
typedef VOS_UINT8 IMSA_PF_TRANS_DIRECTION_ENUM_UINT8;


enum IMSA_CONN_TYPE_ENUM
{
    IMSA_CONN_TYPE_NORMAL               = 0,    /* �������� */
    IMSA_CONN_TYPE_EMC                  = 1,    /* �������� */
    IMSA_CONN_TYPE_BUTT
};
typedef VOS_UINT32 IMSA_CONN_TYPE_ENUM_UINT32;

enum IMSA_CALL_SERVICE_STATUS_ENUM
{
    IMSA_CALL_SERVICE_STATUS_NORMAL_SERVICE    = 0,
    IMSA_CALL_SERVICE_STATUS_NO_SERVICE     = 1,
    IMSA_CALL_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 IMSA_CALL_SERVICE_STATUS_ENUM_UINT32;

/*****************************************************************************
    ö����    : IMSA_CALL_RESULT_ENUM
    ö��˵��  : IMS���н��
*****************************************************************************/
enum IMSA_CALL_RESULT_ENUM
{
    IMSA_CALL_RESULT_SUCCESS             = 0,    /**< ��������ִ�гɹ� */
    IMSA_CALL_RESULT_FAIL                = 1,    /**< ע��ģ������ִ��ʧ�� */
    IMSA_CALL_RESULT_FAIL_REMOTE         = 2,    /**< ���������ܾ�������ܾ�ԭ��ֵ�����Ӧ���ݽṹ�е�Status Code�����ݲ�ͬ��ԭ��ֵ���ܻ�Я��һЩ������ͷ�� */
    IMSA_CALL_RESULT_FAIL_TIMEOUT        = 3,    /**< ���ͻ����SIP���ĳ�ʱ�����峬ʱ�Ķ�ʱ�������Ӧ���ݽṹ�е� Timer Id */
    IMSA_CALL_RESULT_NO_SERVICE          = 4,    /**< û�з�����ʧ�� */
    IMSA_CALL_RESULT_BUTT
};
typedef VOS_UINT32 IMSA_CALL_RESULT_ENUM_UINT32;

/*****************************************************************************
    ö����    : IMSA_RESULT_ACTION_ENUM
    ö��˵��  : ע������ʧ�ܺ���Ҫ����ģ��Ҫ���еĲ���
*****************************************************************************/
enum    IMSA_RESULT_ACTION_ENUM
{
    IMSA_RESULT_ACTION_NULL,                            /**< ����Ҫ������������ */
    IMSA_RESULT_ACTION_REG_WITH_FIRST_ADDR_PAIR,        /**< ����ע�Ტ�ӵ�ַ���б��еĵ�һ����ʼ���� */
    IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR,      /**< ����ע�Ტʹ�õ�ǰ��ַ */
    IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR,         /**< ����ע�Ტʹ����һ��δʹ�õ�ַ�� */
    IMSA_RESULT_ACTION_REG_RESTORATION,                 /**< ��Ҫ����ģ�����restoration���� */
    IMSA_RESULT_ACTION_REG_LOCAL_DEREG,                 /**< ���޸�ע��״̬ΪDEREG */
    IMSA_RESULT_ACTION_BUTT
};
typedef VOS_UINT32 IMSA_RESULT_ACTION_ENUM_UINT32;

/*****************************************************************************
    ö����    : IMSA_CONN_RESULT_ENUM
    ö��˵��  : IMS���ӽ��
*****************************************************************************/
enum IMSA_CONN_RESULT_ENUM
{
    IMSA_CONN_RESULT_SUCCESS                    = 0,    /**< CONNģ������ִ�гɹ� */
    IMSA_CONN_RESULT_FAIL_PARA_ERR              = 1,    /**< CONNģ������ִ��ʧ�ܣ����ڲ������� */
    IMSA_CONN_RESULT_FAIL_CN_REJ                = 2,    /**< CONNģ������ִ��ʧ�ܣ����ڱ�����ܾ� */
    IMSA_CONN_RESULT_FAIL_TIMER_EXP             = 3,    /**< CONNģ������ִ��ʧ�ܣ����ڶ�ʱ����ʱ */
    IMSA_CONN_RESULT_FAIL_CONN_RELEASING        = 4,    /**< CONNģ������ִ��ʧ�ܣ����������ͷ����� */
    IMSA_CONN_RESULT_FAIL_PDP_ACTIVATE_LIMIT    = 5,    /**< CONNģ������ִ��ʧ�ܣ����ڼ���ĳ��������� */
    IMSA_CONN_RESULT_FAIL_SAME_APN_OPERATING    = 6,    /**< CONNģ������ִ��ʧ�ܣ�����APS����ִ�в��� */
    IMSA_CONN_RESULT_FAIL_OHTERS                = 7,    /**< CONNģ������ִ��ʧ�ܣ���������ԭ�� */

    IMSA_CONN_RESULT_BUTT
};
typedef VOS_UINT32 IMSA_CONN_RESULT_ENUM_UINT32;

/*****************************************************************************
    ö����    : IMSA_SIP_PDP_TYPE_ENUM
    ö��˵��  : SIP��������
*****************************************************************************/
enum IMSA_CONN_SIP_PDP_TYPE_ENUM
{
    IMSA_CONN_SIP_PDP_TYPE_SIGNAL               = 0,                /**< SIP������� */
    IMSA_CONN_SIP_PDP_TYPE_MEDIA                = 1,                /**< SIPý����� */

    IMSA_CONN_SIP_PDP_TYPE_BUTT
};
typedef VOS_UINT32  IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32;

/*****************************************************************************
    ö����    : IMSA_CONN_MEDIA_PDP_TYPE_ENUM
    ö��˵��  : ý���������
*****************************************************************************/
enum IMSA_CONN_MEDIA_PDP_TYPE_ENUM
{
    IMSA_CONN_MEDIA_PDP_TYPE_VOICE               = 0,                /**< �������� */
    IMSA_CONN_MEDIA_PDP_TYPE_VIDEO               = 1,                /**< ��Ƶ���� */
    IMSA_CONN_MEDIA_PDP_TYPE_OTHERS              = 2,

    IMSA_CONN_MEDIA_PDP_TYPE_BUTT
};
typedef VOS_UINT32  IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32;


/*****************************************************************************
    ö����    : IMSA_CONN_MODIFY_TYPE_ENUM
    ö��˵��  : ����MODIFY����
*****************************************************************************/
enum IMSA_CONN_MODIFY_TYPE_ENUM
{
    IMSA_CONN_MODIFY_TYPE_REG_PARA_INVALID  = 0,                /**< ע�����ʧЧ */
    IMSA_CONN_MODIFY_TYPE_PCSCF_INVALID     = 1,                /**< P-CSCF��ַʧЧ */

    IMSA_CONN_MODIFY_TYPE_BUTT
};
typedef VOS_UINT32  IMSA_CONN_MODIFY_TYPE_ENUM_UINT32;

/*****************************************************************************
    ö����    : IMSA_PCSCF_SRC_TYPE
    ö��˵��  : PCSCF��ַ��Դ����
*****************************************************************************/
enum IMSA_PCSCF_SRC_TYPE
{
    IMSA_PCSCF_SRC_TYPE_PDN,            /**< P-CSCF��ַ��Դ��PDN���ӽ������� */
    IMSA_PCSCF_SRC_TYPE_CARD,           /**< P-CSCF��ַ��Դ��USIM/ISIM */
    IMSA_PCSCF_SRC_TYPE_DISCOVERY       /**< P-CSCF��ַ��Դ��P-CSCF�������� */
};
typedef VOS_UINT8 IMSA_PCSCF_SRC_TYPE_UINT8;

/*****************************************************************************
    ö����    : IMSA_SRV_TYPE_ENUM
    ö��˵��  : IMSA SERVICE ����ö��
*****************************************************************************/
enum IMSA_SRV_TYPE_ENUM
{
    IMSA_SRV_TYPE_NORMAL                = 0,
    IMSA_SRV_TYPE_EMC                   = 1,

    IMSA_SRV_TYPE_BUTT
};
typedef VOS_UINT8  IMSA_SRV_TYPE_ENUM_UINT8;

/*****************************************************************************
    ö����    : IMSA_CALL_TYPE_ENUM
    ö��˵��  : ��������
*****************************************************************************/
enum    IMSA_CALL_TYPE_ENUM
{
    IMSA_CALL_TYPE_VOICE    = 0,      /* Voice only call */
    IMSA_CALL_TYPE_VIDEO_TX = 1,      /* PS Video telephony call: one way TX video,Two way audio */
    IMSA_CALL_TYPE_VIDEO_RX = 2,      /* Video telephony call: ony way RX video,two way audio */
    IMSA_CALL_TYPE_VIDEO    = 3,      /* video call */
    IMSA_CALL_TYPE_EMC      = 9,      /* emergency call */
    IMSA_CALL_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_CALL_TYPE_ENUM_UINT8;

/*****************************************************************************
    ö����    : IMSA_EMC_CALL_TYPE_ENUM
    ö��˵��  : ������������
*****************************************************************************/
enum    IMSA_EMC_CALL_TYPE_ENUM
{
    IMSA_EMC_CALL_TYPE_IN_NORMAL_SRV    = 0,                        /**< ����ͨ�����Ϸ�������� */
    IMSA_EMC_CALL_TYPE_NO_CARD          = 1,                        /**< �޿������� */
    IMSA_EMC_CALL_TYPE_EMC_CONN_EMC_REG = 2,                        /**< �н���ע��Ľ����� */
    IMSA_EMC_CALL_TYPE_BUTT
};
typedef VOS_UINT32 IMSA_EMC_CALL_TYPE_ENUM_UINT32;

/*****************************************************************************
    ö����    : IMSA_CALL_NO_SRV_CAUSE_ENUM
    ö��˵��  : IMSA CALL�޷����ʹԭ��ֵ
*****************************************************************************/
enum    IMSA_CALL_NO_SRV_CAUSE_ENUM
{
    IMSA_CALL_NO_SRV_CAUSE_HIFI_EXCEPTION           = 0,
    IMSA_CALL_NO_SRV_CAUSE_NON_SRVCC_RAT_CHANGE,
    IMSA_CALL_NO_SRV_CAUSE_NW_NOT_SUPPORT_IMS_VOICE,
    IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE,
    IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR,
    IMSA_CALL_NO_SRV_CAUSE_REG_ERR,

    IMSA_CALL_NO_SRV_CAUSE_BUTT
};
typedef VOS_UINT32 IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/

typedef struct
{
    VOS_UINT32                              ulStatusCode;   /**< SIP���������ص�״ֵ̬ */

    // TODO:
    // 1. Retry-After structure
    // 2. ims-3gpp structure
} IMSA_SIP_SERVER_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_REG_REG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_REG_REG_REQ_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                      ulMsgId;
    IMSA_REG_TYPE_ENUM_UINT8                        enRegType;          /**< ע������ */
    VOS_UINT8                                       aucRsv[3];
    IMSA_REG_ADDR_PARAM_ENUM_UINT32                 enAddrType;         /**< ע��ʹ�õĵ�ַ���� */
    //IMSA_REG_RETRY_POLICY_ENUM_UINT32               enRetryPolicy;      /**< ��ʼע��ʱָ�����Բ��� */
} IMSA_REG_REG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_REG_REG_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_REG_REG_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;        /**< ��ϢId */
    IMSA_REG_TYPE_ENUM_UINT8                enRegType;      /**< ע������ */
    VOS_UINT8                               aucRsv[3];
    IMSA_REG_RESULT_ENUM_UINT32             enResult;       /**< ע���� */

    IMSA_RESULT_ACTION_ENUM_UINT32          enResultAction; /**< ��Ҫ����ģ��ִ�еĶ��� */
    // TODO: �ϲ�ģ����ܲ���Ҫ���������صĲ���
    IMSA_SIP_SERVER_RESULT_STRU             stSipResult;    /**< ���������صĲ��� */
} IMSA_REG_REG_IND_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_REG_DEREG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_REG_DEREG_REQ_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgId;           /**< ��ϢId */
    IMSA_REG_TYPE_ENUM_UINT8             enDeRegType;       /**< ȥע���ʵ������ */
    VOS_UINT8                            aucRsv[3];
    VOS_UINT32                           ulLocalFlag;       /**< �Ƿ�Ϊ����ȥע�ᣬ0Ϊ��Ҫ����dereg����, 1Ϊ����ȥע�� */
} IMSA_REG_DEREG_REQ_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_REG_DEREG_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_REG_DEREG_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;        /**< ��ϢId */
    IMSA_REG_TYPE_ENUM_UINT8            enRegType;      /**< ע������ */
    VOS_UINT8                           aucRsv[3];
    IMSA_REG_RESULT_ENUM_UINT32         enResult;       /**< ע���� */

    IMSA_RESULT_ACTION_ENUM_UINT32      enResultAction; /**< ��Ҫ����ģ��ִ�еĶ��� */
    // TODO: �ϲ�ģ����ܲ���Ҫ���������صĲ���
    IMSA_SIP_SERVER_RESULT_STRU         stSipResult;    /**< ���������صĲ��� */
} IMSA_REG_DEREG_IND_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_CONN_SETUP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_CONN_SETUP_REQ_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    VOS_UINT32                              ulReEstablishFlag;  /* �ؽ�����ʶ VOS_TRUE:�ؽ��� VOS_FALSE:��ʼ���� */
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType;
} IMSA_CONN_SETUP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_CONN_SETUP_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_CONN_SETUP_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    IMSA_CONN_RESULT_ENUM_UINT32            enResult;

    IMSA_CONN_TYPE_ENUM_UINT32              enConnType;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType;   /*0���1����*/
    IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32    enMediaPdpType; /* ý����ص����� */

} IMSA_CONN_SETUP_IND_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_CONN_REL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_CONN_REL_REQ_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType;/*0���1����*//* �ݲ�֧��ý����ص������ͷ� */
} IMSA_CONN_REL_REQ_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_CONN_REL_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_CONN_REL_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType;/*0���1����*/
} IMSA_CONN_REL_IND_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_CONN_MODIFY_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_CONN_MODIFY_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;

    VOS_UINT32                              bitOpModifyType         : 1;
    VOS_UINT32                              bitOpMediaModifyType    :1;
    VOS_UINT32                              bitSpare                : 30;

    IMSA_CONN_TYPE_ENUM_UINT32              enConnType;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType;/*0���1����*/
    IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32    enMediaPdpType; /* ý����ص����� */
    IMSA_CONN_MODIFY_TYPE_ENUM_UINT32       enModifyType;
} IMSA_CONN_MODIFY_IND_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_NORMAL_SERVICE_STATUS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_NORMAL_SERVICE_STATUS_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
/**
 *
 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                  ulMsgId;            /**< ��ϢId */
    IMSA_CALL_SERVICE_STATUS_ENUM_UINT32        enCallSrvStatus;    /**< ���з������� */
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32          enNoSrvCause;       /**< ֪ͨ�޷���ʱָʾԭ��  */
} IMSA_NRM_CALL_SRV_STATUS_IND_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_EMERG_SERVICE_STATUS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_EMERG_SERVICE_STATUS_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
/**
 *
 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                  ulMsgId;            /**< ��ϢId */
    IMSA_CALL_SERVICE_STATUS_ENUM_UINT32        enCallSrvStatus;    /**< ���з������� */
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32          enNoSrvCause;       /**< ֪ͨ�޷���ʱָʾԭ��  */
} IMSA_EMC_CALL_SRV_STATUS_IND_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_CALL_RESULT_ACTION_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_CALL_RESULT_ACTION_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
/**
 * \brief ����ʧ������Ҫ����ģ�������������ʱ��ͨ���˽ṹ������Ҫ���еĲ���
 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;            /**< ��ϢId */

    IMSA_CALL_TYPE_ENUM_UINT8               enCallType;         /**< �������� */
    VOS_UINT8                               aucReserved[3];

    IMSA_RESULT_ACTION_ENUM_UINT32          enResultAction;     /**< ����ʧ�ܺ���������ģ��ִ�еĲ��� */
    // TODO: other param
} IMSA_CALL_RESULT_ACTION_IND_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_INTRA_MSG_QUEUE_STRU
 �ṹ˵��  : �ڲ���Ϣ���нṹ
             usHeader   : ָ����һ�����ӵ���Ϣ
             usTail     : ָ����һ����ӵ���Ϣ���������λ�ã���λ�õ�ǰΪ��
                          ��aucMsgBuff[usTail]����ǰΪ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usHeader;                                   /* ��ͷ */
    VOS_UINT16                      usTail;                                     /* ��β */
    VOS_UINT8                       aucMsgBuff[IMSA_INTRA_MSG_MAX_NUM][IMSA_INTRA_MSG_MAX_SIZE];    /* ��Ϣ������� */
}IMSA_INTRA_MSG_QUEUE_STRU;


typedef struct
{
    VOS_UINT32                          ulMsgId;            /*_H2ASN_MsgChoice_Export IMSA_INTRA_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          IMSA_INTRA_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}IMSA_INTRA_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    IMSA_INTRA_MSG_DATA                     stMsgData;
}IMSA_INTRA_MSG;


/* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulDataLoseNum;
    VOS_UINT32                          ulTotalDataLoseNum;
    VOS_UINT32                          ulDataBufferNum;
    VOS_UINT32                          ulTotalDataBufferNum;

}IMSA_HIFI_DATA_INFO_IND_STRU;
/* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/**
 * \brief ���ƹ���ģ���ṩ������ģ���API, Callģ���ڴ���ͨ�绰ʱ����
 *
 * @retval ���ؽ����0����ʾControl�����ṩ��������Call����ֱ�Ӵ�绰
 * @retval ���ؽ����1����ʾ�����ṩ�������񣬴�绰ʧ��
 */
extern VOS_UINT32 IMSA_StartImsNormalService( IMSA_CALL_TYPE_ENUM_UINT8 enCallType);

/**
 * \brief ���ƹ���ģ���ṩ������ģ���API, Callģ���ڴ�����绰ʱ����
 *
 *
 * @param[out]   penEmcCallType                  ����������
 *
 * @retval ���ؽ����0����ʾControl�����ṩ��������Call����ֱ�Ӵ�绰
 * @retval ���ؽ����1����ʾ�����ṩ�������񣬴�����绰ʧ��
 * @retval ���ؽ����2����ʾ��ʱ�����ṩ�����������ڽ�����������Callģ����Ҫ����绰
 */
extern VOS_UINT32 IMSA_StartImsEmergService
(
    IMSA_EMC_CALL_TYPE_ENUM_UINT32     *penEmcCallType
);

/**
 * \brief ����ģ���ṩ������ģ���API, ����ģ�����յ�����ģ���������Ӽ���
 *        ���޸�ʱ����
 */
extern VOS_VOID IMSA_ProcCallResourceIsReady
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32    enMediaPdpType
);

/**
 * \brief ����ģ���ṩ������ģ���API, ����ģ�����յ�����ģ�����������ͷ�ʱ����
 *
 */
extern VOS_VOID IMSA_ProcCallResourceIsNotReady
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType
);


/**
 * \brief �����ڲ���Ϣ�ռ�
 *
 *
 * @param[in]   ulBuffSize                  ������Ϣ�Ŀռ�
 *
 * @retval      VOS_VOID *                  ��ȡ�����ڲ���Ϣ�ռ��ַ
 */
extern VOS_VOID *IMSA_GetIntraMsgBuffAddr( VOS_UINT32 ulBuffSize );

/**
 * \brief �����ڲ���Ϣ
 *
 *
 * @param[in]   pIntraMsg                   ��������Ϣ
 *
 * @retval      VOS_UINT32                  ���ͽ��
 */
extern VOS_UINT32 IMSA_SndIntraMsg(VOS_VOID* pIntraMsg);


/**
 * \brief ���ַ�Թ���ģ���������õ�P-CSCF��ַ
 *
 * �˺���������ģ����е��ã���ַ�Թ���ģ�������趨ֵ��
 * ֮ǰ�Ѿ��е�UE��ַ��Ϣ����һ���Ĺ�����µ�ַ���б�
 *
 * ��ַ���б����ɹ�������:
 *   -# ����IPv4����IPv6���͵�ַʱ��������ѡ��IPv6���͵�IP��ַ
 *   -# UE IP��ַ���ͺ�P-CSCF��ַ������ͬ
 *   -# ���ѡ����IP���͵�P-CSCF��ַ�ж��������ݴ洢˳��ȡP-CSCF��ַ
 *
 * @param[in]   ulRegType       ע������
 * @param[in]   enIpType        ������P-CSCF��ַ����
 * @param[in]   enSrcType       ������P-CSCF��ַ��Դ����
 * @param[in]   paucIpAddr      ������P-CSCF��ַ
 *
 * @retval      VOS_TRUE        ����P-CSCF�ɹ��������ݹ���ˢ���˵�ַ���б�
 * @retval      VOS_FALSE       ����P-CSCFʧ��
 */
extern VOS_UINT32 IMSA_RegAddrPairMgrAddPcscfAddr(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                                  IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                                  IMSA_PCSCF_SRC_TYPE_UINT8 enSrcType,
                                                  const VOS_CHAR *pacIpAddr);

/**
 * \brief �ӵ�ַ�Թ���ģ��ɾ��һ��P-CSCF��ַ
 *
 * �˺���������ģ����е��ã���ַ�Թ���ģ�������趨ֵ��
 * ֮ǰ�Ѿ��е�UE��ַ��Ϣ����һ���Ĺ�����µ�ַ���б�
 *
 * @param[in]   ulRegType       ע������
 * @param[in]   enIpType        ɾ����P-CSCF��ַ����
 * @param[in]   paucIpAddr      ɾ����P-CSCF��ַ
 *
 * @retval      VOS_TRUE        ɾ��P-CSCF�ɹ��������ݹ���ˢ���˵�ַ���б�
 */
extern VOS_UINT32 IMSA_RegAddrPairMgrRmvPcscfAddr(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                                  IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                                  VOS_CHAR *pacIpAddr);

/**
 * \brief ���ַ�Թ���ģ���������õ�UE��ַ
 *
 * �˺���������ģ����е��ã���ַ�Թ���ģ�������趨ֵ��
 * ֮ǰ�Ѿ��е�P-CSCF��ַ��Ϣ����һ���Ĺ�����µ�ַ���б�
 *
 * ��ַ���б����ɹ���ο� #IMSA_RegAddrPairMgrAddPcscfAddr
 *
 * @param[in]   ulRegType       ע������
 * @param[in]   enIpType        ������UE��ַ����
 * @param[in]   paucIpAddr      ������UE��ַ
 *
 * @retval      VOS_TRUE        ����UE�ɹ��������ݹ���ˢ���˵�ַ���б�
 */
extern VOS_UINT32 IMSA_RegAddrPairMgrAddUeAddr(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                               IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                               const VOS_CHAR *pacIpAddr);

/**
 * \brief �ӵ�ַ�Թ���ģ��ɾ��һ��UE��ַ
 *
 * �˺���������ģ����е��ã���ַ�Թ���ģ�������趨ֵ��
 * ֮ǰ�Ѿ��е�P-CSCF��ַ��Ϣ����һ���Ĺ�����µ�ַ���б�
 *
 * @param[in]   ulRegType       ע������
 * @param[in]   enIpType        ɾ����UE��ַ����
 * @param[in]   paucIpAddr      ɾ����UE��ַ
 *
 * @retval      VOS_TRUE        ɾ��UE�ɹ��������ݹ���ˢ���˵�ַ���б�
 */
extern VOS_UINT32 IMSA_RegAddrPairMgrRmvUeAddr(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                               IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                               VOS_CHAR *pacIpAddr);

/**
 * \brief ��ȡע���ϵĲ���
 *
 * @param[in]   ulRegType       ע������
 * @param[out]  paucUeAddr      ��ŷ��ص�UE��ַ
 * @param[in]   paucPcscfAddr   ��ŷ��ص�P-CSCF��ַ
 *
 * @retval      VOS_TRUE        ��ȡ��ǰ����ʹ�õĵ�ַ����Ϣ�ɹ�
 */
extern VOS_UINT32 IMSA_RegGetRegedPara
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    VOS_CHAR                           *pacUeAddr,
    VOS_CHAR                           *pacPcscfAddr,
    IMSA_IP_TYPE_ENUM_UINT8            *penIptype
);


/**
 * \brief �Ƿ�����EMC���ص�NV��
 * @retval      IMSA_TRUE        �����˽���������
 * @retval      IMSA_FALSE       û�ж������������
 */
extern VOS_UINT32 IMSA_CONN_IsEmcPdpDefined( VOS_VOID );

/**
 * \brief ����SRVCC��ʶ
 * @param[in]   ulSrvccFlag       SRVCC��ʶ
 */
extern VOS_VOID IMSA_CallSetSrvccFlag
(
    VOS_UINT32                          ulSrvccFlag
);

/**
 * \brief ��ȡSRVCC��ʶ
 * @retval      IMSA_TRUE        ��SRVCC������
 * @retval      IMSA_FALSE       ����SRVCC������
 */
extern VOS_UINT32 IMSA_CallGetSrvccFlag( VOS_VOID );

/**
 * \brief ���ò��ϱ�ALL RELEASD�¼���ʶ
 * @param[in]   ulNotReportAllReleasdFlag       ���ϱ�ALL RELEASD�¼���ʶ
 */
extern VOS_VOID IMSA_CallSetNotReportAllReleasedFlag
(
    VOS_UINT32                          ulNotReportAllReleasdFlag
);

/**
 * \brief ��ȡ���ϱ�ALL RELEASD�¼���ʶ
 * @retval      IMSA_TRUE        �����ϱ�ALL RELEASED�¼�
 * @retval      IMSA_FALSE       �����ϱ�ALL RELEASED�¼�
 */
extern VOS_UINT32 IMSA_CallGetNotReportAllReleasedFlag( VOS_VOID );

extern VOS_UINT32 IMSA_SRV_IsConningRegState(VOS_UINT8 ucIsEmc);
extern VOS_VOID IMSA_CONN_UpdateNicPdpInfo( VOS_VOID );


extern VOS_UINT32 IMSA_CONN_HasActiveVoicePdp
(
    VOS_VOID
);
extern VOS_UINT32 IMSA_CONN_HasActiveVideoPdp
(
    VOS_VOID
);


extern VOS_UINT32 IMSA_IsCallConnExist(VOS_VOID);
extern VOS_UINT32 IMSA_IsSmsConnExist(VOS_VOID);
extern VOS_UINT32 IMSA_IsSsConnExist(VOS_VOID);

extern VOS_VOID IMSA_CMCCDeregProc(VOS_VOID);

/* zhaochen 00308719 begin for VoLTE 2015-08-26 */
VOS_VOID IMSA_CommonDeregProc(VOS_VOID);
/* zhaochen 00308719 end for VoLTE 2015-08-26 */

extern VOS_UINT32 IMSA_CONN_IsExitPersistentBearer
(
    VOS_VOID
);
extern VOS_UINT32 IMSA_RegAddrPairMgrGetCurrent(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                             VOS_CHAR  *pacUeAddr,
                                             VOS_CHAR  *pacPcscfAddr);
extern VOS_UINT32 IMSA_SRV_IsCurRatSupportIms( VOS_VOID );

#if (FEATURE_ON == FEATURE_PTM)
extern VOS_VOID IMSA_RegErrRecord
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8 enRegFailReason
);
extern VOS_VOID IMSA_PdnRejErrRecord
(
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32   enPdnConnRejCause
);
extern VOS_VOID IMSA_EmcCallErrRecord
(
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM_UINT16   enCallFailReason,
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16    enRegFailReason,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16  enPdnConnNwRej,
    VOS_UINT16                                      usCallSipStatusCode,
    VOS_UINT16                                      usEmcRegSipStatusCode,
    IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8             enCallStatus
);
extern VOS_VOID IMSA_NormInitDeregErrRecord
(
    IMSA_ERR_LOG_INIT_DEREG_REASON_ENUM_UINT32  enInitDeregCause
);
extern VOS_VOID IMSA_NotInitRegErrRecord
(
    VOS_VOID
);
#endif
extern VOS_UINT32 IMSA_IsImsEmcServiceEstablishSucc(VOS_VOID);
extern VOS_VOID IMSA_StopImsEmcService(VOS_VOID);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaIntraInterface.h */

