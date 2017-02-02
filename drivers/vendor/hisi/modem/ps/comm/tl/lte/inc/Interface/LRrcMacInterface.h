

#ifndef __LRRCLMACINTERFACE_H__
#define __LRRCLMACINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "LPSCommon.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define PS_MAX_UE_ID_LENGTH             6
#define PS_MAX_BCCH_MSG_LEN             1024
#define PS_MAX_PCCH_MSG_LEN             1024

#define ELRRC_LMAC_MSG_HDR                (PS_MSG_ID_RRC_TO_MAC_BASE)
#define LMAC_ELRRC_MSG_HDR                (PS_MSG_ID_MAC_TO_RRC_BASE)
#define ELRMM_LMAC_MSG_HDR                (PS_MSG_ID_RRC_TO_MAC_BASE + 0x40)
#define LMAC_ELRMM_MSG_HDR                (PS_MSG_ID_MAC_TO_RRC_BASE + 0x40)

#define LRRC_LMAC_SCELL_MAX_NUM              8
#define LRRC_LMAC_TAG_NUM                    4
#define LRRC_LMAC_TAG_ID_MAX_VALUE           3
#define LRRC_LMAC_SCELL_CONFIG               1
#define LRRC_LMAC_SCELL_NOT_CONFIG           0
#define LRRC_LMAC_SCELL_NUM_ZERO             0

/*****************************************************************************
  3 Message Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_MSG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC��MAC��Ľӿ���Ϣ
*****************************************************************************/
enum LRRC_LMAC_MSG_TYPE_ENUM
{
    ID_LRRC_LMAC_BCCH_CONFIG_REQ          = (ELRMM_LMAC_MSG_HDR + 0x00),            /* _H2ASN_MsgChoice LRRC_LMAC_BCCH_CONFIG_REQ_STRU */         /* RRC����MAC��BCCH���ŵ�*/
    ID_LRRC_LMAC_BCCH_CONFIG_CNF          = (LMAC_ELRMM_MSG_HDR + 0x00),            /* _H2ASN_MsgChoice LRRC_LMAC_BCCH_CONFIG_CNF_STRU */         /* RRC����MAC��BCCH����Ӧ*/

    ID_LRRC_LMAC_BCCH_DATA_IND            = (LMAC_ELRMM_MSG_HDR + 0x01),            /* _H2ASN_MsgChoice LRRC_LMAC_BCCH_DATA_IND_STRU */           /* MAC�ϴ���RRC��BCCH�ŵ�������*/

    ID_LRRC_LMAC_PCCH_CONFIG_REQ          = (ELRRC_LMAC_MSG_HDR + 0x01),            /* _H2ASN_MsgChoice LRRC_LMAC_PCCH_CONFIG_REQ_STRU */         /* RRC����MAC��PCCH���ŵ�*/
    ID_LRRC_LMAC_PCCH_CONFIG_CNF          = (LMAC_ELRRC_MSG_HDR + 0x02),            /* _H2ASN_MsgChoice LRRC_LMAC_PCCH_CONFIG_CNF_STRU */         /* RRC����MAC��PCCH����Ӧ*/

    ID_LRRC_LMAC_PCCH_DATA_IND            = (LMAC_ELRRC_MSG_HDR + 0x03),            /* _H2ASN_MsgChoice LRRC_LMAC_PCCH_DATA_IND_STRU */           /* MAC��RRC��PCCH�ϵ����� */

    ID_LRRC_LMAC_RACH_CONFIG_REQ          = (ELRRC_LMAC_MSG_HDR + 0x02),            /* _H2ASN_MsgChoice LRRC_LMAC_RACH_CONFIG_REQ_STRU */         /* RRC����MAC��RACH���ŵ�*/
    ID_LRRC_LMAC_RACH_CONFIG_CNF          = (LMAC_ELRRC_MSG_HDR + 0x04),            /* _H2ASN_MsgChoice LRRC_LMAC_RACH_CONFIG_CNF_STRU */         /* RRC����MAC��RACH����Ӧ*/

    ID_LRRC_LMAC_RA_REQ                   = (ELRRC_LMAC_MSG_HDR + 0x03),            /* _H2ASN_MsgChoice LRRC_LMAC_RA_REQ_STRU */                  /* RRCҪ��MAC�����漴��������� */
    ID_LRRC_LMAC_RA_CNF                   = (LMAC_ELRRC_MSG_HDR + 0x05),            /* _H2ASN_MsgChoice LRRC_LMAC_RA_CNF_STRU */                  /* �漴����������CNF */

    ID_LRRC_LMAC_CONFIG_REQ               = (ELRRC_LMAC_MSG_HDR + 0x04),            /* _H2ASN_MsgChoice LRRC_LMAC_CONFIG_REQ_STRU */              /* RRC����MAC��ʵ����ŵ�*/
    ID_LRRC_LMAC_CONFIG_CNF               = (LMAC_ELRRC_MSG_HDR + 0x06),            /* _H2ASN_MsgChoice LRRC_LMAC_CONFIG_CNF_STRU */              /* RRC����MAC��ʵ�����Ӧ*/

    ID_LRRC_LMAC_RELEASE_REQ              = (ELRRC_LMAC_MSG_HDR + 0x05),            /* _H2ASN_MsgChoice LRRC_LMAC_RELEASE_REQ_STRU */             /* RRC�ͷ�MAC*/
    ID_LRRC_LMAC_RELEASE_CNF              = (LMAC_ELRRC_MSG_HDR + 0x07),            /* _H2ASN_MsgChoice LRRC_LMAC_RELEASE_CNF_STRU */             /* RRC�ͷ�MAC����Ӧ*/

    ID_LRRC_LMAC_RESET_REQ                = (ELRRC_LMAC_MSG_HDR + 0x06),            /* _H2ASN_MsgChoice LRRC_LMAC_RESET_REQ_STRU */               /* RRC�ؽ�MAC������*/
    ID_LRRC_LMAC_RESET_CNF                = (LMAC_ELRRC_MSG_HDR + 0x08),            /* _H2ASN_MsgChoice LRRC_LMAC_RESET_CNF_STRU */               /* RRC�ؽ�MAC����Ӧ*/

    ID_LRRC_LMAC_ERROR_IND                = (LMAC_ELRRC_MSG_HDR + 0x09),            /* _H2ASN_MsgChoice LRRC_LMAC_ERROR_IND_STRU */               /* MAC֪ͨRRC,MAC��������*/

    ID_LRRC_LMAC_PUCCH_SRS_RELEASE_IND    = (LMAC_ELRRC_MSG_HDR + 0x0a),            /* _H2ASN_MsgChoice LRRC_LMAC_PUCCH_SRS_RELEASE_IND_STRU */   /* MAC֪ͨRRC�ͷ�SRS��  PUCCH��Դ*/
    ID_LRRC_LMAC_PUCCH_SRS_RELEASE_RSP    = (ELRRC_LMAC_MSG_HDR + 0x07),            /* _H2ASN_MsgChoice LRRC_LMAC_PUCCH_SRS_RELEASE_RSP_STRU */   /* RRC�ͷ�SRS��PUCCH��Դ���MAC ��ָʾ*/

    ID_LRRC_LMAC_TDD_CONFIG_REQ           = (ELRRC_LMAC_MSG_HDR + 0x08),            /* _H2ASN_MsgChoice LRRC_LMAC_TDD_CONFIG_REQ_STRU */          /* RRC����MAC����TDD �����Ϣ*/
    ID_LRRC_LMAC_TDD_CONFIG_CNF           = (LMAC_ELRRC_MSG_HDR + 0x0b),            /* _H2ASN_MsgChoice LRRC_LMAC_TDD_CONFIG_CNF_STRU */          /* RRC����MAC����TDD �����Ϣȷ��ָʾ*/

    ID_LRRC_LMAC_CRNTI_IND                = (LMAC_ELRRC_MSG_HDR + 0x0c),            /* _H2ASN_MsgChoice LRRC_LMAC_CRNTI_IND_STRU */          /*MAC�ϱ�CRNTIֵ */

    ID_LRRC_LMAC_RA_SUCC_IND              = (LMAC_ELRRC_MSG_HDR + 0x0d),            /* _H2ASN_MsgChoice LRRC_LMAC_RA_SUCC_IND_STRU */              /* MAC�ϱ��������ɹ�ָʾ */

    ID_LRRC_LMAC_RELEASE_SCELL_REQ        = (LMAC_ELRRC_MSG_HDR + 0x0e),            /* _H2ASN_MsgChoice LRRC_LMAC_RELEASE_SCELL_REQ_STRU */        /* RRCɾ��ָ��ĳ��SCELL�Ͷ��SCELL������ */
    ID_LRRC_LMAC_RELEASE_SCELL_CNF        = (ELRRC_LMAC_MSG_HDR + 0x09),            /* _H2ASN_MsgChoice LRRC_LMAC_RELEASE_SCELL_CNF_STRU */         /* MAC�ظ�RRCɾ��SCELL����Ļظ���Ϣ */
    ID_LRRC_LMAC_MSG_TYPE_END
};
typedef VOS_UINT32 LRRC_LMAC_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_CFG_MODE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC����MAC����������
*****************************************************************************/
enum LRRC_LMAC_CFG_MODE_ENUM
{
    LRRC_LMAC_CFG_MODE_SETUP                  = 0,                                    /* ��ʼ���� */
    LRRC_LMAC_CFG_MODE_RECFG                  = 1,                                    /* ������ */
    LRRC_LMAC_CFG_MODE_BUTT
};
typedef VOS_UINT8 LRRC_LMAC_CFG_MODE_ENUM_UINT8;

/* modify by lishangfeng begin 20140211 begin */
/*****************************************************************************
 �ṹ��    : LRRC_LMAC_CFG_MODE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC����MAC����������
*****************************************************************************/
enum LRRC_LMAC_CFG_RAT_MODE_ENUM
{
    LRRC_LMAC_CFG_RAT_MODE_FDD                  = 0,                                    /* ��ʼ���� */
    LRRC_LMAC_CFG_RAT_MODE_TDD                  = 1,                                    /* ������ */
    LRRC_LMAC_CFG_RAT_MODE_BUTT
};
typedef VOS_UINT8 LRRC_LMAC_CFG_RAT_MODE_ENUM_UINT8;
/* modify by lishangfeng begin 20140211 end */

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RA_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC����MAC�������������
*****************************************************************************/
enum LRRC_LMAC_RA_TYPE_ENUM
{
    LRRC_LMAC_RA_TYPE_CONTENTION              = 0,                                    /* �������� */
    LRRC_LMAC_RA_TYPE_NON_CONTENTION          = 1,                                    /* �Ǿ����� */
    LRRC_LMAC_RA_TYPE_BUTT
};
typedef VOS_UINT8 LRRC_LMAC_RA_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RA_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC����MAC��������ԭ��
*****************************************************************************/
enum LRRC_LMAC_RA_CAUSE_ENUM
{
    LRRC_LMAC_RA_CAUSE_CONN                   = 0,                                    /* ���ӽ����� */
    LRRC_LMAC_RA_CAUSE_HO                     = 1,                                    /* �л��� */
    LRRC_LMAC_RA_CAUSE_REEST                  = 2,                                    /* RRC�����ؽ����� */
    LRRC_LMAC_RA_CAUSE_WAITTA_TIMEOUT         = 3,                                    /* �ȴ�TA��ʱ */
    LRRC_LMAC_RA_CAUSE_SENDSR                 = 4,                                    /* ����������뷢��SR��Ϣ */
    LRRC_LMAC_RA_CAUSE_BUTT
};
typedef VOS_UINT8 LRRC_LMAC_RA_CAUSE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_ERR_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
enum LRRC_LMAC_ERR_TYPE_ENUM
{
    LRRC_LMAC_ERR_FATAL                        = 0,                                   /*MAC���������ɻָ��Դ���*/
    LRRC_LMAC_RA_ERR_MAX_TX_NUM                = 1,                                   /*�����������Preamble�ﵽ������*/
    LRRC_LMAC_RA_ERR_MAX_HARQ_NUM              = 2,                                   /*���������̷�����Ϣ3�ﵽ������*/
    LRRC_LMAC_ERR_NO_RF_RA                     = 3,                                   /*�������ʱû��RF*/
    LRRC_LMAC_ERR_NO_RF_TIMEROUT               = 4,                                   /*RF������ʱ����ʱ*/
    LRRC_LMAC_ERR_RF_RESUME_SYNC               = 5,                                   /*RF�ָ����ֹ�����಻ͬ��*/
    LRRC_LMAC_ERR_BUTT
};
typedef VOS_UINT8 LRRC_LMAC_ERR_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RSLT_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC�����õĽ��:�ɹ�����ʧ��
*****************************************************************************/
enum LRRC_LMAC_RSLT_ENUM
{
    LRRC_LMAC_SUCC                            = 0,
    LRRC_LMAC_FAIL                            = 1,
    LRRC_LMAC_RSLT_BUTT
};
typedef VOS_UINT8   LRRC_LMAC_RSLT_ENUM_UINT8;

/*****************************************************************************
�ṹ��    : LRRC_LMAC_PATH_LOSS_CHANGE_ENUM
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
enum LRRC_LMAC_PATH_LOSS_CHANGE_ENUM
{
    LRRC_LMAC_PATH_LOSS_CHANGE_1DB            = 0,
    LRRC_LMAC_PATH_LOSS_CHANGE_3DB               ,
    LRRC_LMAC_PATH_LOSS_CHANGE_6DB               ,
    LRRC_LMAC_PATH_LOSS_CHANGE_INFINITY          ,
    LRRC_LMAC_PATH_LOSS_CHANGE_BUTT
};
typedef VOS_UINT8   LRRC_LMAC_PATH_LOSS_CHANGE_ENUM_UINT8;

/*****************************************************************************
�ṹ��    : LRRC_LMAC_PWR_OFFSET_GROUPB_ENUM
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
enum LRRC_LMAC_PWR_OFFSET_GROUPB_ENUM
{
    LRRC_LMAC_PWR_OFFSET_GROUPB_MINUSINFINIT  = 0,
    LRRC_LMAC_PWR_OFFSET_GROUPB_0DB              ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_5DB              ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_8DB              ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_10DB             ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_12DB             ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_15DB             ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_18DB             ,
    LRRC_LMAC_PWR_OFFSET_GROUPB_BUTT
};
typedef VOS_UINT8   LRRC_LMAC_PWR_OFFSET_GROUPB_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_CHANNEL_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC���չ㲥��Ϣʱ��Ӧ�������ŵ�����
*****************************************************************************/
enum LRRC_LMAC_CHANNEL_TYPE_ENUM
{
    LRRC_LMAC_CHANNEL_TYPE_PBCH               = 0,                                    /* PBCH�ŵ����յ���Ϣ */
    LRRC_LMAC_CHANNEL_TYPE_PDSCH                 ,                                    /* PDSCH�ŵ����յ���Ϣ */
    LRRC_LMAC_CHANNEL_TYPE_BUTT
};
typedef VOS_UINT8 LRRC_LMAC_CHANNEL_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : LTE_PROTOCOL_VER_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : Э��汾����
*****************************************************************************/
enum    LTE_PROTOCOL_VER_ENUM
{
    LTE_PROTOCOL_VER_V8  = 0x01,
    LTE_PROTOCOL_VER_V9  = 0x02,
    LTE_PROTOCOL_VER_V10 = 0x04,
    LTE_PROTOCOL_VER_V11 = 0x08,
    LTE_PROTOCOL_VER_BUTT
};
typedef VOS_UINT8   LTE_PROTOCOL_VER_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : LRRC_LMAC_BCCH_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :��ԭ�ﱣ������ʱ��ʹ��
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    /*�㲥��Ϣ���̺�*/
    VOS_UINT8                           ucHarqProcNum;
    VOS_UINT8                           aucRev[1];

    /*�㲥��Ϣ�޸�����ϵ��*/
    VOS_UINT32                          ulModifyPeriodCoeff;

} LRRC_LMAC_BCCH_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_BCCH_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :��ԭ�ﱣ������ʱ��ʹ��
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    LRRC_LMAC_RSLT_ENUM_UINT8                 enRslt;
    VOS_UINT8                           aucRev[1];

} LRRC_LMAC_BCCH_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_BCCH_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucAntennaPortsCount;

    VOS_UINT8                           ucSubFrame;
    VOS_UINT16                          usFrame;

    LRRC_LMAC_CHANNEL_TYPE_ENUM_UINT8         enMacChannelType;
    VOS_UINT8                           aucRev[3];

    /*��󳤶���PS_MAX_BCCH_MSG_LENȷ������λ�ֽ�*/
    VOS_UINT32                          ulDataLength;
    VOS_UINT8                           aucData[4];
} LRRC_LMAC_BCCH_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_PCCH_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵�� :��ԭ�ﱣ������ʱ��ʹ��
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];

    /*����ϵͳ��Ϣ�޸�ʱ������*/
    VOS_UINT32                          ulDefaultPagingCycle;

} LRRC_LMAC_PCCH_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_PCCH_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��   :��ԭ�ﱣ������ʱ��ʹ��
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_PCCH_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_PCCH_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucSubFrame;
    VOS_UINT8                           ucRev;

    VOS_UINT16                          usFrame;

    /*��󳤶���PS_MAX_PCCH_MSG_LENȷ����λ�ֽ�*/
    VOS_UINT32                          ulDataLength;
    VOS_UINT8                           aucData[4];

} LRRC_LMAC_PCCH_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_GROUPA_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPblGrpASize;                          /*Group A����Ӧ��Preamble����:����տ�û�У������ó� 0 */
    LRRC_LMAC_PWR_OFFSET_GROUPB_ENUM_UINT8    enMessagePowerOffsetGroupB;             /*Э��36.321�Ĳ���MESSAGE_POWER_OFFSET_GROUP_B,ȡֵЭ�����*/

    VOS_UINT16                          usMessageSizeGroupA;                    /*Э��36.321�Ĳ���MESSAGE_SIZE_GROUP_A*/

} LRRC_LMAC_GROUPA_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RACH_COMM_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RACH-ConfigCommon�����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitGroupAValid  :1;                     /*Group A��Ϣ�Ƿ���Ч��־��0:��Ч��1:��Ч*/
    VOS_UINT32                          bitSpare        :31;

    LRRC_LMAC_GROUPA_CONFIG_STRU              stGroupAConfig;

    VOS_UINT8                           ucPblNum;                               /*Group A��B����Ӧ����Preamble����*/
    VOS_UINT8                           ucPblPwrStep;                           /*Preamble������������*/
    VOS_INT16                           sPblInitTargetPwr;                      /*Preamble��eNB���������չ���*/

    VOS_UINT8                           ucPblMaxTxNum;                          /*�������Preamble����ʹ���*/
    VOS_UINT8                           ucRarWindowSize;                        /*�������������Ӧ��Ϣ�Ĵ���*/
    VOS_UINT8                           ucContentTimer;                         /*���������ʱ��*/
    VOS_UINT8                           ucMaxHarqMsg3Tx;                        /*Msg3����HARQ������ʹ���*/

    VOS_INT8                            cPMax;                                  /*����书�ʣ�ȱʡʱʹ��UE�����е�����书��*/
    VOS_INT8                            cDeltaPblMsg3;                          /*Preamble��Msg3֮���OFFSET*/
    VOS_UINT8                           ucUlBandwidth;                           /*ϵͳ����*/
    VOS_UINT8                           aucRev1[1];

    VOS_UINT32                          ulCellTaTimer;                          /*С������TA��ʱ��*/


} LRRC_LMAC_RACH_COMM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_PRACH_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  :PRACH-Configuration
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrachConfigIndex;                          /*�Ѿ�ȷ��:Prach-ConfigurationIndex,0-63*/
    VOS_UINT8                           aucRev[3];
}LRRC_LMAC_PRACH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RACH_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LRRC_LMAC_CFG_MODE_ENUM_UINT8             enConfigType;
    LRRC_LMAC_CFG_RAT_MODE_ENUM_UINT8         enFddOrTddRatMod;                          /* 0��FDD; 1 TDD */

    LRRC_LMAC_RACH_COMM_INFO_STRU             stRachCommInfo;                         /*36.331 6.3.2��RACH-ConfigCommon*/

    LRRC_LMAC_PRACH_INFO_STRU                 stPrachInfo;                            /*36.331 6.3.2��PRACH-Configuration*/

    /*UE���ȣ��ݶ��ֽ�Ϊ��λ*/
    VOS_UINT8                           ucUeIdLength;
    VOS_UINT8                           aucRev2[1];
    VOS_UINT8                           aucUeId[PS_MAX_UE_ID_LENGTH];           /*ue id�ĸ�ʽ������*/
} LRRC_LMAC_RACH_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RACH_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_RACH_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LRRC_LMAC_RA_TYPE_ENUM_UINT8              enRaType;

    LRRC_LMAC_RA_CAUSE_ENUM_UINT8             enRaCause;

    VOS_UINT8                           ucDediPreambleId;
    VOS_UINT8                           ucPrachMaskIndex;
    VOS_UINT8                           aucRev[2];

    VOS_INT16                           sPathLoss ;                             /*ȡֵ���������ʱ��������ѡ��Group A��B��ʵ��·�𣬸�ֵ��Ҫȷ�ϻ�ȡ��ʽ */
    VOS_UINT16                          usMsg3Size;                             /* ����ѡ��Group A��B����Ϣ3��Сֵ ����ֵʹ�õĵ�λȷ��:byte */
} LRRC_LMAC_RA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RA_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_RA_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_PHR_CONFIG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPeriodPhrTimer;
    VOS_UINT16                          usProhibitPhrTimer;

    LRRC_LMAC_PATH_LOSS_CHANGE_ENUM_UINT8     enDlPathLossChange;
    /* V7R2 RRC-L2 INTF BEGIN add extendPHR here, indicate true or false */
    PS_BOOL_ENUM_UINT8                        enExtendPhr;
    PS_BOOL_ENUM_UINT8                        enSimulPUCCH_PUSCH;
    VOS_UINT8                                 aucRev[1];
    /* V7R2 RRC-L2 INTF END */
}LRRC_LMAC_PHR_CONFIG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_SR_CONFIG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSrConfigIndex;                        /*SR������������*/
    VOS_UINT8                           ucSrTransMaxNum;                        /*SR������������Э��36.321 ��DSR_TRANS_MAX*/
    VOS_UINT8                           aucRev[2];
}LRRC_LMAC_SR_CONFIG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_UL_SCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPeriodBsrTimer;
    VOS_UINT32                          ulRetxBsrTimer;

    /* V7R2 RRC-L2 INTF BEGIN add extendBSR here, indicate true or false */
    PS_BOOL_ENUM_UINT8                  enExtendBsrSize;
    /* V7R2 RRC-L2 INTF END */
    VOS_UINT8                           ucUlMaxHarqTxNum;
    PS_BOOL_ENUM_UINT8                  enTtiBundling;
    /* V7R2 RRC-L2 INTF BEGIN add extendBSR here, indicate true or false */
    VOS_UINT8                           aucRev[1];
    /* V7R2 RRC-L2 INTF END */
} LRRC_LMAC_UL_SCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_DL_SCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucRev[4];
} LRRC_LMAC_DL_SCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_SPS_DL_CONFIG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSpsIntervalDL;
    VOS_UINT8                           aucRev[2];

}LRRC_LMAC_SPS_DL_CONFIG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_SPS_UL_CONFIG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSpsIntervalUL;
    VOS_UINT8                           ucImplicitReleaseAfter;
    VOS_UINT8                           aucRev[1];

}LRRC_LMAC_SPS_UL_CONFIG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_SPS_CONFIG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitSpsDlValid:1;
    VOS_UINT32                          bitSpsUlValid:1;
    VOS_UINT32                          bitSpare:30;

    LRRC_LMAC_SPS_DL_CONFIG_INFO_STRU         stSpsDlConfig;
    LRRC_LMAC_SPS_UL_CONFIG_INFO_STRU         stSpsUlConfig;
}LRRC_LMAC_SPS_CONFIG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_SCELL_RACH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SCELL��rach��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucPblPwrStep;                          /*Preamble������������*/
    VOS_UINT8                            ucPblMaxTxNum;                         /*�������Preamble����ʹ���*/
    VOS_INT16                            sPblInitRxTargetPwr;                   /*Preamble��eNB���������չ��� */

    VOS_UINT8                            ucRarWindowSize;                       /*�������������Ӧ��Ϣ�Ĵ��� */
    VOS_UINT8                            aucResv[3];                           /*Ԥ��*/
} LRRC_LMAC_SCELL_RACH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_SCELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SCELL��������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           bitScellRachValid : 1;                 /*scell rach��Ϣ��Чָʾ��0:��Ч��1:��Ч*/
    VOS_UINT32                           bitSpare          : 31;

    VOS_UINT8                            ucScellIndex;                          /*Scell ����*/
    VOS_UINT8                            ucConfigUlValid;                       /*ScellС����������״̬  1:���ã�0:δ����*/
    VOS_UINT8                            ucConfigDlValid;                       /*ScellС����������״̬  1:���ã�0:δ����*/
    VOS_UINT8                            ucTagId;                               /*TAG��ʶ������ָʾ��SCELL������TAG*/

    LRRC_LMAC_CFG_RAT_MODE_ENUM_UINT8    enFrameType;                           /*LTE ֡����*/
    VOS_UINT8                            ucSubFrameAssig;                       /*������֡���*/
    VOS_UINT8                            aucResv[2];
    LRRC_LMAC_SCELL_RACH_INFO_STRU       stScellRachInfo;                       /*Scell��rach��Ϣ*/
}LRRC_LMAC_SCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_CA_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CA�������. ��usServCellIdxBmpΪ0��enScellDeactTimer������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulScellDeactTimer;                     /*Scellȥ���ʱ��*/
    VOS_UINT32                           ulScellNum;                            /*Scell����*/
    LRRC_LMAC_SCELL_INFO_STRU            astScellInfo[LRRC_LMAC_SCELL_MAX_NUM]; /*Scell��״̬��Ϣ*/
} LRRC_LMAC_CA_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_TAG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAG������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucTagId;                               /*TAG��ʶ*/
    VOS_UINT8                            aucResv[3];

    VOS_UINT32                           ulTagTimerLen;                         /*TAG��ʱ������*/
} LRRC_LMAC_TAG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_TAG_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAG�������.
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulTagNum;                              /*����TAG����*/
    LRRC_LMAC_TAG_INFO_STRU              astTagInfo[LRRC_LMAC_TAG_NUM];         /*���õ�TAG��Ϣ*/
} LRRC_LMAC_TAG_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    LRRC_LMAC_CFG_MODE_ENUM_UINT8       enConfigType;
    LTE_PROTOCOL_VER_ENUM_UINT8         enProtoType;
    VOS_UINT32                          bitCrntiValid   : 1;                    /*C-RNTI�Ƿ���Чָʾ*/
    VOS_UINT32                          bitSrProhbTimerValid   :1;              /*sr-ProhibitTimer-r9�Ƿ���Чָʾ*/
    VOS_UINT32                          bitTaTimerValid : 1;                    /*TATimer��Ϣ�Ƿ���Чָʾ*/
    VOS_UINT32                          bitUlSCHValid   : 1;                    /*����SCH��Ϣ�Ƿ���Чָʾ*/
    VOS_UINT32                          bitDlSCHValid   : 1;                    /*����SCH��Ϣ�Ƿ���Чָʾ*/
    VOS_UINT32                          bitPhrCfgValid  : 1;
    VOS_UINT32                          bitSrCfgValid   : 1;
    VOS_UINT32                          bitSpsCfgValid  : 1;
    VOS_UINT32                          bitCaCfgValid   : 1;                    /*CA��Ϣ�Ƿ���Чָʾ, �ͷ�SCELL��ͨ���˱�־��Ч���� */
    VOS_UINT32                          bitTagCfgValid  :1;
    VOS_UINT32                          bitSpare        : 22;
    /*C-RNTI*/
    VOS_UINT16                          usCrnti;

    VOS_UINT8                           ucSrProhbTimer;                         /* sr-ProhibitTimer-r9 (0..7) */
    VOS_UINT8                           ucReserved;

    /*TA��ʱ��ʱ��*/
    VOS_UINT32                          ulTaTimer;

    /*���д����ŵ���Ϣ*/
    LRRC_LMAC_UL_SCH_INFO_STRU                stUlSCHInfo;

    /*���д����ŵ���Ϣ*/
    LRRC_LMAC_DL_SCH_INFO_STRU                stDlSCHInfo;

    /* PHR��ز�����Ϣ */
    LRRC_LMAC_PHR_CONFIG_INFO_STRU        stPhrConfigInfo;

    /* ����������ز�����Ϣ */
    LRRC_LMAC_SR_CONFIG_INFO_STRU         stSrConfigInfo;


    /*�뾲̬������Ϣ*/
    LRRC_LMAC_SPS_CONFIG_INFO_STRU        stSpsConfigInfo;

    LRRC_LMAC_CA_CONFIG_STRU              stCaConfig;
    LRRC_LMAC_TAG_CONFIG_STRU             stTagConfig;
} LRRC_LMAC_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RELEASE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    VOS_UINT8                           aucRev[2];

} LRRC_LMAC_RELEASE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RELEASE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_RELEASE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RESET_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    VOS_UINT8                           aucRev[2];

} LRRC_LMAC_RESET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RESET_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_RESET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_ERROR_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                            /*_H2ASN_Skip*/

    LRRC_LMAC_ERR_TYPE_ENUM_UINT8         enErrorType;
    VOS_UINT8                             ucPblSentNum;                         /*Preamble���ʹ���*/
    PS_BOOL_ENUM_UINT8                    enMaxTxPowerReached;                  /*����ָʾPreamble�Ƿ�ﵽ����͹���,1:�ﵽ��0:û�ﵽ*/
    PS_BOOL_ENUM_UINT8                    enContentionDetected;                 /*�Ƿ��о�����0:�Ǿ���������룬1:�����������*/

} LRRC_LMAC_ERROR_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_PUCCH_SRS_RELEASE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32      enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucTagId;
    VOS_UINT8                           aucRev[1];
} LRRC_LMAC_PUCCH_SRS_RELEASE_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_PUCCH_SRS_RELEASE_RSP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    VOS_UINT8                           aucRev[2];

} LRRC_LMAC_PUCCH_SRS_RELEASE_RSP_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_TDD_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;

    VOS_UINT8                           ucSubFrameAssig;

    VOS_UINT8                           aucRev[1];

} LRRC_LMAC_TDD_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_TDD_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef LRRC_LMAC_BCCH_CONFIG_CNF_STRU LRRC_LMAC_TDD_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_CRNTI_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usCrnti;

    VOS_UINT8                           aucRev[2];

} LRRC_LMAC_CRNTI_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RA_SUCC_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����֪ͨRRC MAC�������ɹ�
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32      enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucPblSentNum;                           /*MAC�������ɹ����ϱ�Preambles���ʹ��� */
    PS_BOOL_ENUM_UINT8                  enContentionDetected;                   /*����ָʾMAC���͵�Preamble���Ƿ��о�����ʽ 1:�У�0:û��*/
    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           ucRsv;
} LRRC_LMAC_RA_SUCC_IND_STRU;

typedef struct
{
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export LRRC_LMAC_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_LMAC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LRRC_LMAC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    LRRC_LMAC_MSG_DATA                    stMsgData;
}RrcMacInterface_MSG;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RELEASE_SCELL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC����֪ͨMACɾ��SCELL��������Ϣ
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32      enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucResv[2];

    VOS_UINT32                          ulCellNum;                              /*��Ҫɾ����scell����*/

    VOS_UINT8                           aucScellIndex[8];                       /*��Ҫɾ����scellIndex*/

} LRRC_LMAC_RELEASE_SCELL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LMAC_RELEASE_SCELL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC�����ظ�RRCɾ��SCELL�Ļ�Ӧ��Ϣ
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LMAC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucResult;                               /* 0:�ɹ���1:ʧ�� */
    VOS_UINT8                           aucResv;

} LRRC_LMAC_RELEASE_SCELL_CNF_STRU;


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
