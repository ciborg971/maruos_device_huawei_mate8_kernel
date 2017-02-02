

#ifndef __LRRCPDCPINTERFACE_H__
#define __LRRCPDCPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "LPSCommon.h"
#include "PsTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/

/* ���RB�ĸ��� */
#define PS_MAX_RB_NUM                   (16)

/* �ܹ����͵����AM���ݵĳ��� */
#define PS_MAX_AM_MSG_LEN               (1024 * 2)

/* �ܹ����͵����UM���ݵĳ��� */
#define PS_MAX_UM_MSG_LEN               (1024)

/* �ܹ����͵����TM���ݵĳ��� */
#define PS_MAX_TM_MSG_LEN               (1024)

#define LRRC_LPDCP_MSG_HDR                (PS_MSG_ID_RRC_TO_PDCP_BASE)
#define LPDCP_LRRC_MSG_HDR                (PS_MSG_ID_PDCP_TO_RRC_BASE)

/*ROHC�����㷨����*/
#define LRRC_LPDCP_MAX_PROFILE_NUM        (16)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_MSG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC��PDCP��Ľӿ���Ϣ
*****************************************************************************/
enum LRRC_LPDCP_MSG_TYPE_ENUM
{
    ID_LRRC_LPDCP_CONFIG_REQ              = (LRRC_LPDCP_MSG_HDR + 0x00),            /* _H2ASN_MsgChoice LRRC_LPDCP_CONFIG_REQ_STRU */       /* ����PDCP  */
    ID_LRRC_LPDCP_CONFIG_CNF              = (LPDCP_LRRC_MSG_HDR + 0x00),            /* _H2ASN_MsgChoice LRRC_LPDCP_CONFIG_CNF_STRU */       /* ����PDCP��confirm  */

    ID_LRRC_LPDCP_RELEASE_REQ             = (LRRC_LPDCP_MSG_HDR + 0x01),            /* _H2ASN_MsgChoice LRRC_LPDCP_RELEASE_REQ_STRU */      /* �ͷ�PDCP  */
    ID_LRRC_LPDCP_RELEASE_CNF             = (LPDCP_LRRC_MSG_HDR + 0x01),            /* _H2ASN_MsgChoice LRRC_LPDCP_RELEASE_CNF_STRU */      /* �ͷ�PDCP��confirm*/

    ID_LRRC_LPDCP_STOP_REQ                = (LRRC_LPDCP_MSG_HDR + 0x02),            /* _H2ASN_MsgChoice LRRC_LPDCP_STOP_REQ_STRU */         /* ֹͣ�û������ݵĴ���  */
    ID_LRRC_LPDCP_STOP_CNF                = (LPDCP_LRRC_MSG_HDR + 0x02),            /* _H2ASN_MsgChoice LRRC_LPDCP_STOP_CNF_STRU */         /* ֹͣ�û������ݵĴ����confirm*/

    ID_LRRC_LPDCP_CONTINUE_REQ            = (LRRC_LPDCP_MSG_HDR + 0x03),            /* _H2ASN_MsgChoice LRRC_LPDCP_CONTINUE_REQ_STRU */     /* ���¿�ʼ�û������ݵĴ���  */
    ID_LRRC_LPDCP_CONTINUE_CNF            = (LPDCP_LRRC_MSG_HDR + 0x03),            /* _H2ASN_MsgChoice LRRC_LPDCP_CONTINUE_CNF_STRU */     /* ���¿�ʼ�û������ݵĴ����confirm*/

    ID_LRRC_LPDCP_SECU_CONFIG_REQ         = (LRRC_LPDCP_MSG_HDR + 0x04),            /* _H2ASN_MsgChoice LRRC_LPDCP_SECU_CONFIG_REQ_STRU */  /* ���ܺ������Ա������㷨 */
    ID_LRRC_LPDCP_SECU_CONFIG_CNF         = (LPDCP_LRRC_MSG_HDR + 0x04),            /* _H2ASN_MsgChoice LRRC_LPDCP_SECU_CONFIG_CNF_STRU */  /* ���ܺ������Ա�����������Ӧ */

    ID_LRRC_LPDCP_COUNTER_CHECK_REQ       = (LRRC_LPDCP_MSG_HDR + 0x05),            /* _H2ASN_MsgChoice LRRC_LPDCP_COUNTER_CHECK_REQ_STRU */  /* RRC����Counter Check���� */
    ID_LRRC_LPDCP_COUNTER_CHECK_CNF       = (LPDCP_LRRC_MSG_HDR + 0x05),            /* _H2ASN_MsgChoice LRRC_LPDCP_COUNTER_CHECK_CNF_STRU */  /* PDCP����Counter Check��Ӧ */

    ID_LRRC_LPDCP_AM_DATA_REQ             = (LRRC_LPDCP_MSG_HDR + 0x06),            /* _H2ASN_MsgChoice LRRC_LPDCP_AM_DATA_REQ_STRU */      /* RRC����AM���ݵ�����     */
    ID_LRRC_LPDCP_UM_DATA_REQ             = (LRRC_LPDCP_MSG_HDR + 0x07),            /* _H2ASN_MsgChoice LRRC_LPDCP_UM_DATA_REQ_STRU */      /* RRC����UM���ݵ�����     */
    ID_LRRC_LPDCP_DATA_CNF                = (LPDCP_LRRC_MSG_HDR + 0x06),            /* _H2ASN_MsgChoice LRRC_LPDCP_DATA_CNF_STRU */         /* RRC����AM��TM���ݵ�ȷ�� */

    ID_LRRC_LPDCP_AM_DATA_IND             = (LPDCP_LRRC_MSG_HDR + 0x07),            /* _H2ASN_MsgChoice LRRC_LPDCP_AM_DATA_IND_STRU */      /*  PDCP��RRC���ͽ��յ�AM����   */
    ID_LRRC_LPDCP_UM_DATA_IND             = (LPDCP_LRRC_MSG_HDR + 0x08),            /* _H2ASN_MsgChoice LRRC_LPDCP_UM_DATA_IND_STRU */      /*  RPDCP��RRC���ͽ��յ�UM����  */

    ID_LRRC_LPDCP_SMC_CMP_REQ             = (LRRC_LPDCP_MSG_HDR + 0x08),            /* _H2ASN_MsgChoice LRRC_LPDCP_SMC_CMP_REQ_STRU */  /* RRC����RRC_SMC_CMP���� */

    ID_LRRC_LPDCP_ERROR_IND               = (LPDCP_LRRC_MSG_HDR + 0x09),            /* _H2ASN_MsgChoice LRRC_LPDCP_ERROR_IND_STRU */        /* PDCP�㷢�����󱨸�    */
/* gaojishan-fast-dorm-cfg */
    ID_LRRC_LPDCP_FAST_DORMANCY_REQ       = (LRRC_LPDCP_MSG_HDR + 0x09),            /* _H2ASN_MsgChoice LRRC_LPDCP_FAST_DORMANCY_REQ_STRU */ /* RRC��PDCP����FAST_DORMANCY����*/
    ID_LRRC_LPDCP_FAST_DORMANCY_CNF       = (LPDCP_LRRC_MSG_HDR + 0x0a),            /* _H2ASN_MsgChoice LRRC_LPDCP_FAST_DORMANCY_CNF_STRU */ /* PDCP��RRC�ظ�FAST_DORMANCY��Ӧ*/

    ID_LRRC_LPDCP_FAST_DORMANCY_IND       = (LPDCP_LRRC_MSG_HDR + 0x0b),            /* _H2ASN_MsgChoice LRRC_LPDCP_FAST_DORMANCY_IND_STRU */ /* PDCP��RRC����FAST_DORMANCYָʾ*/

    ID_LRRC_LPDCP_REQ_END                 = (LRRC_LPDCP_MSG_HDR + 0x0a),
    ID_LRRC_LPDCP_IND_END                 = (LPDCP_LRRC_MSG_HDR + 0x0c)
};
typedef VOS_UINT32 LRRC_LPDCP_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_CFG_MODE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC����PDCP����������
*****************************************************************************/
enum LPDCP_CFG_MODE_ENUM
{
    LPDCP_CFG_MODE_SETUP                 = 0,                                    /* ��ʼ���� */
    LPDCP_CFG_MODE_RECFG                 = 1,                                    /* ������ */
    LPDCP_CFG_MODE_BUTT
};
typedef VOS_UINT8 LPDCP_CFG_MODE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LRLC_MODE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
enum LRLC_MODE_ENUM
{
    LRLC_MODE_AM                         = 0,                                    /* AM */
    LRLC_MODE_UM                         = 1,                                    /* UM */
    LRLC_MODE_TM                         = 2,                                    /* TM */
    LRLC_MODE_BUTT
};
typedef VOS_UINT8 LRLC_MODE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LPDCP_STOP_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
enum LPDCP_STOP_CAUSE_ENUM
{
    LPDCP_STOP_CAUSE_HO                  = 0,                                    /* HO ��ɵ�PDCPֹͣ���� */
    LPDCP_STOP_CAUSE_REEST               = 1,                                    /* RRC�����ؽ�����ɵ�PDCPֹͣ���� */
    LPDCP_STOP_CAUSE_RSVED               = 2,                                    /* ���� */

    LPDCP_STOP_CAUSE_BUTT
};
typedef VOS_UINT8 LPDCP_STOP_CAUSE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LPDCP_CONTINUE_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
enum LPDCP_CONTINUE_CAUSE_ENUM
{
    LPDCP_CONTINUE_CAUSE_HO              = 0,                                    /* HO�ɹ� ��ɵ�PDCP�ָ����� */
    LPDCP_CONTINUE_CAUSE_REEST           = 1,                                    /* RRC�����ؽ����ɹ�����ɵ�PDCP�ָ����� */
    LPDCP_CONTINUE_CAUSE_RSVED           = 2,                                    /* ���� */

    LPDCP_CONTINUE_CAUSE_BUTT
};
typedef VOS_UINT8 LPDCP_CONTINUE_CAUSE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LPDCP_ERROR_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
enum LPDCP_ERROR_ENUM
{
    LPDCP_ERROR_INTEGRITY_VERIFY         = 0,                                    /*��������֤����*/
    LPDCP_ERROR_OTHER                    = 1,

    LPDCP_ERROR_BUTT
};
typedef VOS_UINT8 LPDCP_ERROR_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LPDCP_SN_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
enum LPDCP_SN_TYPE_ENUM
{
    LPDCP_SN_TYPE_7_BITS                 = 0,                                    /* UMģʽ��PDCP SNռ��7bits */
    LPDCP_SN_TYPE_12_BITS                = 1,                                    /* AM/UMģʽ��PDCP SNռ��12bits */
    LPDCP_SN_TYPE_15_BITS                = 2,                                    /* AMģʽ��PDCP SNռ��15bits */
    LPDCP_SN_TYPE_BUTT
};
typedef VOS_UINT8 LPDCP_SN_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LPDCP_RSLT_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP�����õĽ��:�ɹ�����ʧ��
*****************************************************************************/
enum LPDCP_RSLT_ENUM
{
    LPDCP_SUCC                           = 0,
    LPDCP_FAIL                           = 1,
    LPDCP_RSLT_BUTT
};
typedef VOS_UINT8   LPDCP_RSLT_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_SECU_CFG_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP�㰲ȫ����ģʽ
*****************************************************************************/
enum LRRC_LPDCP_SECU_CFG_ENUM
{
    LRRC_LPDCP_SECU_CFG_INTE_CIPH         = 0,               /*ͬʱ���������ԡ��ӽ���*/
    LRRC_LPDCP_SECU_CFG_FAIL,                                /* SMC CMD��������֤ʧ�� */

    LRRC_LPDCP_SECU_CFG_BUTT
};
typedef VOS_UINT8   LRRC_LPDCP_SECU_CFG_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_CIPHER_ALG_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LPDCP������㷨
*****************************************************************************/
enum LRRC_LPDCP_CIPHER_ALG_ENUM
{
    LRRC_LPDCP_CIPHER_ALG_NULL            = 0,                /*������*/
    LRRC_LPDCP_CIPHER_ALG_SNOW_3G         = 1,                /*SNOW 3G�㷨����*/
    LRRC_LPDCP_CIPHER_ALG_AES             = 2,                /*AES �㷨����*/
    LRRC_LPDCP_CIPHER_ALG_ZUC             = 3,                /*ZUC �㷨����*/

    LRRC_LPDCP_CIPHER_ALG_BUTT
};
typedef VOS_UINT8   LRRC_LPDCP_CIPHER_ALG_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_INTEGRITY_ALG_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������㷨
*****************************************************************************/
enum LRRC_LPDCP_INTEGRITY_ALG_ENUM
{
    LRRC_LPDCP_INTEGRITY_ALG_NULL         = 0,
    LRRC_LPDCP_INTEGRITY_ALG_SNOW_3G      = 1,
    LRRC_LPDCP_INTEGRITY_ALG_AES          = 2,
    LRRC_LPDCP_INTEGRITY_ALG_ZUC          = 3,

    LRRC_LPDCP_INTEGRITY_ALG_BUTT
};
typedef VOS_UINT8   LRRC_LPDCP_INTEGRITY_ALG_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_ROHC_PROFILE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͷѹ���㷨
*****************************************************************************/
enum LRRC_LPDCP_ROHC_PROFILE_ENUM
{
    LRRC_LPDCP_ROHC_PROFILE_NULL          = 0x0000,
    LRRC_LPDCP_ROHC_PROFILE_RTP_UDP_IP    = 0x0001,
    LRRC_LPDCP_ROHC_PROFILE_UDP_IP        = 0x0002,
    LRRC_LPDCP_ROHC_PROFILE_ESP_IP        = 0x0003,
    LRRC_LPDCP_ROHC_PROFILE_IP            = 0x0004,
    LRRC_LPDCP_ROHC_PROFILE_TCP_IP        = 0x0006,
    LRRC_LPDCP_ROHC_PROFILE_RTP_UDP_IP_V2 = 0x0101,
    LRRC_LPDCP_ROHC_PROFILE_UDP_IP_V2     = 0x0102,
    LRRC_LPDCP_ROHC_PROFILE_ESP_IP_V2     = 0x0103,
    LRRC_LPDCP_ROHC_PROFILE_IP_V2         = 0x0104,

    LRRC_LPDCP_ROHC_PROFILE_BUTT
};
typedef VOS_UINT16   LRRC_LPDCP_ROHC_PROFILE_ENUM_UINT16;

/*****************************************************************************
 ö����    : LRRC_LPDCP_ENTITY_REL_FALG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ָʾPDCPʵ���Ƿ��ͷ�
*****************************************************************************/
enum LRRC_LPDCP_ENTITY_REL_FALG_ENUM
{
    LRRC_LPDCP_ENTITY_REL_NOT_NEED         = 0,                                    /* ����Ҫ�ͷ� */
    LRRC_LPDCP_ENTITY_REL_NEED,                                                    /* ��Ҫ�ͷ� */
    LRRC_LPDCP_ENTITY_REL_BUTT
};
typedef VOS_UINT8 LRRC_LPDCP_ENTITY_REL_FALG_ENUM_UINT8;
/* gaojishan-fast-dorm-cfg */
/*****************************************************************************
 ö����    : LRRC_LPDCP_FAST_DORMANCY_CMD_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ָʾPDCP������ֹͣFAST_DORMANCY
*****************************************************************************/
enum LRRC_LPDCP_FAST_DORMANCY_CMD_ENUM
{
    LRRC_LPDCP_FAST_DORMANCY_STOP         = 0,                                  /* ֹͣFAST_DORMANCY */
    LRRC_LPDCP_FAST_DORMANCY_START,                                             /* ����FAST_DORMANCY */
    LRRC_LPDCP_FAST_DORMANCY_BUTT
};
typedef VOS_UINT8 LRRC_LPDCP_FAST_DORMANCY_CMD_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : LPDCP_UM_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    LPDCP_SN_TYPE_ENUM_UINT8             enPdcpSnLgthType;
    VOS_UINT8                           aucRsv[3];
} LPDCP_UM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LPDCP_AM_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enStatusRptReq;
    LPDCP_SN_TYPE_ENUM_UINT8             enPdcpSnLgthType;
    VOS_UINT8                            aucRsv[2];
} LPDCP_AM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LPDCP_CFG_INFO_CHOICE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    LRLC_MODE_ENUM_UINT8                 enRlcMode;
    VOS_UINT8                           aucRsv[3];

    union
    {
        LPDCP_UM_INFO_STRU               stUmPdcpInfo;
        LPDCP_AM_INFO_STRU               stAmPdcpInfo;
    }u;

} LPDCP_CFG_INFO_CHOICE_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_ROHC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͷѹ��/��ѹ�����ò����ṹ
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enCompressFlag;
    VOS_UINT8                           aucRev[3];
    VOS_UINT16                          usMaxUlCid;
    VOS_UINT16                          usUsedProfileNum;
    LRRC_LPDCP_ROHC_PROFILE_ENUM_UINT16   ausProfile[LRRC_LPDCP_MAX_PROFILE_NUM];
}LRRC_LPDCP_ROHC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LPDCP_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbId;
    /* ָʾPDCPʵ���Ƿ���Ҫ���ͷ�������,0:����Ҫ�ͷ�,1:��Ҫ���ͷ�,Ȼ��������²�����������  */
    LRRC_LPDCP_ENTITY_REL_FALG_ENUM_UINT8 enRelInd;
    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           aucRsv[1];
    VOS_UINT32                          ulDiscardTimer;

    LRRC_LPDCP_ROHC_INFO_STRU             stRohcInfo;
    LPDCP_CFG_INFO_CHOICE_STRU           stPdcpCfgChoice;
} LPDCP_INFO_STRU;

/*============================= RRC��PDCP��Ľӿ� =============================*/
/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LPDCP_CFG_MODE_ENUM_UINT8            enConfigMode;

    VOS_UINT8                           ucPdcpNum;

    LPDCP_INFO_STRU                      stPdcpInfo[PS_MAX_RB_NUM];
} LRRC_LPDCP_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LPDCP_RSLT_ENUM_UINT8                enResult;
    VOS_UINT8                           aucRsv[1];
} LRRC_LPDCP_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_RELEASE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    VOS_UINT8                           aucRsv[1];
    VOS_UINT8                           ucPdcpNum;

    VOS_UINT8                           aucPdcpRbId[PS_MAX_RB_NUM];
} LRRC_LPDCP_RELEASE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_RELEASE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LPDCP_RSLT_ENUM_UINT8                enResult;
    VOS_UINT8                           aucRsv[1];
} LRRC_LPDCP_RELEASE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LPDCP_STOP_CAUSE_ENUM_UINT8          enStopCause;

    VOS_UINT8                           ucPdcpNum;
    VOS_UINT8                           aucPdcpRbId[PS_MAX_RB_NUM];
    VOS_UINT8                           ucUmDrbContRohcFlg;
    VOS_UINT8                           aucResv[3];
} LRRC_LPDCP_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef LRRC_LPDCP_CONFIG_CNF_STRU LRRC_LPDCP_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_CONTINUE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LPDCP_CONTINUE_CAUSE_ENUM_UINT8      enContinueCause;

    VOS_UINT8                           ucPdcpNum;
    VOS_UINT8                           aucPdcpRbId[PS_MAX_RB_NUM];
} LRRC_LPDCP_CONTINUE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_CONTINUE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef LRRC_LPDCP_CONFIG_CNF_STRU LRRC_LPDCP_CONTINUE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_AM_DATA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usSeqNum;

    VOS_UINT8                           ucRbId;

    /* ��AM RLCʵ��ȷ�϶Զ˽��յ�RLC SDU��,�Ƿ���Ҫʹ��PDCP_CNFԭ����߲㷢��ȷ��
        1:��ʾRRC��Ҫ�ȴ�CNF��Ϣ�� 0:��ʾRRC����Ҫ��CNF��Ϣ */
    PS_BOOL_ENUM_UINT8                  enCnfIndFlg;

    VOS_UINT32                          ulDataLength;
    VOS_UINT8                           aucData[4];
} LRRC_LPDCP_AM_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PDCP_SMC_CMP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef LRRC_LPDCP_AM_DATA_REQ_STRU LRRC_LPDCP_SMC_CMP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_DATA_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usSeqNum;

    LPDCP_RSLT_ENUM_UINT8                enResult;
    VOS_UINT8                           aucRsv[1];
} LRRC_LPDCP_DATA_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_UM_DATA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usSeqNum;

    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRsv[1];

    VOS_UINT32                          ulDataLength;
    VOS_UINT8                           aucData[4];
} LRRC_LPDCP_UM_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_AM_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;
    VOS_UINT8                           ucPdcpHdr;
    VOS_UINT8                           aucRsv[2];

    VOS_UINT32                          ulDataLength;
    VOS_UINT32                          ulCount;
    VOS_UINT8                           aucData[4];
} LRRC_LPDCP_AM_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_UM_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRsv[3];

    VOS_UINT32                          ulDataLength;
    VOS_UINT32                          ulCount;
    VOS_UINT8                           aucData[4];
} LRRC_LPDCP_UM_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_ERROR_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    LPDCP_ERROR_ENUM_UINT8               enErrInd;
    VOS_UINT8                           aucRsv[3];

} LRRC_LPDCP_ERROR_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_SECU_CONFIG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    LRRC_LPDCP_INTEGRITY_ALG_ENUM_UINT8   enIntegrityProtAlg;
    LRRC_LPDCP_CIPHER_ALG_ENUM_UINT8      enCipherAlg;
    LRRC_LPDCP_SECU_CFG_ENUM_UINT8        enConfigMode;
    VOS_UINT8                           ucRev;
} LRRC_LPDCP_SECU_CONFIG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_SECU_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
    LRRC_LPDCP_SECU_CONFIG_INFO_STRU      stSecuConfigInfo;
} LRRC_LPDCP_SECU_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_SECU_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef LRRC_LPDCP_CONFIG_CNF_STRU LRRC_LPDCP_SECU_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_COUNTER_CHECK_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LRRC_LPDCP_COUNTER_CHECK_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PDCP_COUNTER_CHECK_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRev[3];
    VOS_UINT32                          ulUlCount;
    VOS_UINT32                          ulDlCount;
} LRRC_LPDCP_COUNTER_CHECK_CNF_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_COUNTER_CHECK_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRsv[1];
    VOS_UINT8                           ucPdcpNum;

    LRRC_LPDCP_COUNTER_CHECK_CNF_INFO_STRU     stCounterCheckCnfInfo[PS_MAX_RB_NUM];
} LRRC_LPDCP_COUNTER_CHECK_CNF_STRU;
/* gaojishan-fast-dorm-cfg */
/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_FAST_DORMANCY_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32          enMsgName;                         /*_H2ASN_Skip*/

    VOS_UINT16                               usOpId;

    LRRC_LPDCP_FAST_DORMANCY_CMD_ENUM_UINT8  enFastDormancyCmd;
    VOS_UINT8                                aucRsv[1];

    VOS_UINT32                               ulFastDormancyTimer;               /*��ʱ��ʱ����msΪ��λ*/
} LRRC_LPDCP_FAST_DORMANCY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_FAST_DORMANCY_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                            /*_H2ASN_Skip*/

    VOS_UINT16                            usOpId;

    LPDCP_RSLT_ENUM_UINT8                 enResult;
    VOS_UINT8                             aucRsv[1];
} LRRC_LPDCP_FAST_DORMANCY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LPDCP_FAST_DORMANCY_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;                            /*_H2ASN_Skip*/

} LRRC_LPDCP_FAST_DORMANCY_IND_STRU;

typedef struct
{
    LRRC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgID;            /*_H2ASN_MsgChoice_Export LRRC_LPDCP_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_LPDCP_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LRRC_LPDCP_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    LRRC_LPDCP_MSG_DATA                    stMsgData;
}LRrcPdcpInterface_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

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

#endif
