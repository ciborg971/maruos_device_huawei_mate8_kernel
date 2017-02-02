

#ifndef _GAS_RR_WRR_H_
#define _GAS_RR_WRR_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include  "GUCommInterface.h"

#pragma pack(4)

extern VOS_UINT32 g_ulWasHoInfoR3Stub ;


/*====================== RR-WRRC֮����Ϣ�ĺ궨�� ============================*/
enum RR_WRRC_MSG_TYPE_ENUM
{
    /* ����GToW�л�ԭ��궨�� */
    RRWRRC_CELL_CHANGE_REQ                                  = 0x9901,       /* _H2ASN_MsgChoice RRWRRC_CELL_CHANGE_REQ_ST */
    RRWRRC_CELL_CHANGE_CNF                                  = 0x9902,       /* _H2ASN_MsgChoice RRWRRC_CELL_CHANGE_CNF_ST */
    RRWRRC_HANDOVER_REQ                                     = 0x9903,       /* _H2ASN_MsgChoice RRWRRC_HANDOVER_REQ_ST */
    RRWRRC_HANDOVER_CNF                                     = 0x9904,       /* _H2ASN_MsgChoice RRWRRC_HANDOVER_CNF_ST */
    RRWRRC_CELL_RESEL_REQ                                   = 0x9905,       /* _H2ASN_MsgChoice RRWRRC_CELL_RESEL_REQ_ST */
    RRWRRC_CELL_RESEL_CNF                                   = 0x9906,       /* _H2ASN_MsgChoice RRWRRC_CELL_RESEL_CNF_ST */

    /* ����WToG�л�ԭ��궨�� */
    WRRCRR_CELL_CHANGE_REQ                                  = 0x9907,       /* _H2ASN_MsgChoice WRRCRR_CELL_CHANGE_REQ_ST */
    WRRCRR_CELL_CHANGE_CNF                                  = 0x9908,       /* _H2ASN_MsgChoice WRRCRR_CELL_CHANGE_CNF_ST */
    WRRCRR_CELL_CHANGE_TIMER_EXPIRED_REQ                    = 0x9909,       /* _H2ASN_MsgChoice WRRCRR_CELL_CHANGE_TIMER_EXPIRED_REQ_ST */
    WRRCRR_CELL_CHANGE_TIMER_EXPIRED_CNF                    = 0x9910,       /* _H2ASN_MsgChoice WRRCRR_CELL_CHANGE_TIMER_EXPIRED_CNF_ST */
    WRRCRR_HANDOVER_REQ                                     = 0x9911,       /* _H2ASN_MsgChoice WRRCRR_HANDOVER_REQ_ST */
    WRRCRR_HANDOVER_CNF                                     = 0x9912,       /* _H2ASN_MsgChoice WRRCRR_HANDOVER_CNF_ST */
    WRRCRR_CELL_RESEL_REQ                                   = 0x9913,       /* _H2ASN_MsgChoice WRRCRR_CELL_RESEL_REQ_ST */
    WRRCRR_CELL_RESEL_CNF                                   = 0x9914,       /* _H2ASN_MsgChoice WRRCRR_CELL_RESEL_CNF_ST */
    RRWRRC_CELL_CHANGE_TIMER_EXPIRED_REQ                    = 0x9915,       /* _H2ASN_MsgChoice RRWRRC_CELL_CHANGE_TIMER_EXPIRED_REQ_ST */
    RRWRRC_CELL_CHANGE_TIMER_EXPIRED_CNF                    = 0x9916,       /* _H2ASN_MsgChoice RRWRRC_CELL_CHANGE_TIMER_EXPIRED_CNF_ST */
    WRRCRR_CELL_RESEL_TIMER_EXPIRED_REQ                     = 0x9917,       /* _H2ASN_MsgChoice WRRCRR_CELL_RESEL_TIMER_EXPIRED_REQ_ST */
    WRRCRR_CELL_RESEL_TIMER_EXPIRED_CNF                     = 0x9918,       /* _H2ASN_MsgChoice WRRCRR_CELL_RESEL_TIMER_EXPIRED_CNF_ST */

    WRRCRR_PLMN_SEARCH_REQ                                  = 0x9919,       /* _H2ASN_MsgChoice WRRCRR_PLMN_SEARCH_REQ_ST */
    WRRCRR_PLMN_SEARCH_CNF                                  = 0x9920,       /* _H2ASN_MsgChoice WRRCRR_PLMN_SEARCH_CNF_ST */
    WRRCRR_PLMN_SEARCH_STOP_REQ                             = 0x9921,       /* _H2ASN_MsgChoice WRRCRR_PLMN_SEARCH_STOP_REQ_ST */
    WRRCRR_PLMN_SEARCH_STOP_CNF                             = 0x9922,       /* _H2ASN_MsgChoice WRRCRR_PLMN_SEARCH_STOP_CNF_ST */

    /* ��ȡinter rat info �Ķ��� */
    RRWRRC_INTER_RAT_HANDOVER_INFO_REQ      = 0x9923,       /* _H2ASN_MsgChoice RRWRRC_INTER_RAT_HANDOVER_INFO_REQ_ST */
    RRWRRC_INTER_RAT_HANDOVER_INFO_CNF      = 0x9924,       /* _H2ASN_MsgChoice RRWRRC_INTER_RAT_HANDOVER_INFO_CNF_ST */

    RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_REQ                 = 0x9925,         /* _H2ASN_MsgChoice RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_REQ_ST */
    RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_CNF                 = 0x9926,         /* _H2ASN_MsgChoice RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_CNF_ST */

    RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_REQ   = 0x9927,         /*_H2ASN_MsgChoice RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_REQ_ST */
    RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_CNF   = 0x9928,         /*_H2ASN_MsgChoice RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_CNF_ST */

    WRRCRR_CELL_SEL_REDIRECTION_REQ                       = 0x9929,         /* _H2ASN_MsgChoice WRRCRR_CELL_SEL_REDIRECTION_REQ_ST */
    WRRCRR_CELL_SEL_REDIRECTION_CNF                       = 0x992A,         /* _H2ASN_MsgChoice WRRCRR_CELL_SEL_REDIRECTION_CNF_ST */

    WRRCRR_CELL_SEL_REDIRECTION_ABORT_REQ                 = 0x992B,         /*_H2ASN_MsgChoice WRRCRR_CELL_SEL_REDIRECTION_ABORT_REQ_ST */
    WRRCRR_CELL_SEL_REDIRECTION_ABORT_CNF                 = 0x992C,         /*_H2ASN_MsgChoice WRRCRR_CELL_SEL_REDIRECTION_ABORT_CNF_ST */

    RRWRRC_CLASSMARK_CHANGE_IND                           = 0x992D,         /*_H2ASN_MsgChoice RRWRRC_CLASSMARK_CHANGE_IND_ST */

    RRWRRC_CELL_RESEL_STOP_REQ                              = 0x992E,       /*_H2ASN_MsgChoice RRWRRC_CELL_RESEL_STOP_REQ_ST */
    RRWRRC_CELL_RESEL_STOP_CNF                              = 0x992F,       /*_H2ASN_MsgChoice RRWRRC_CELL_RESEL_STOP_CNF_ST */

    WRRCRR_INTERRAT_PLMN_SEARCH_REQ                         = 0x9930,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_REQ_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_CNF                         = 0x9931,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_CNF_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_IND                         = 0x9951,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_IND_ST */

    WRRCRR_INTERRAT_PLMN_SEARCH_STOP_REQ                    = 0x9932,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_STOP_REQ_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_STOP_CNF                    = 0x9933,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_STOP_CNF_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_REQ                 = 0x9934,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_REQ_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_CNF                 = 0x9935,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_CNF_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_REQ                  = 0x9936,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_REQ_ST */
    WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_CNF                  = 0x9937,       /*_H2ASN_MsgChoice WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_CNF_ST */
    WRRCRR_INTER_RAT_HANDOVER_INFO_REQ                      = 0x9938,       /*_H2ASN_MsgChoice WRRCRR_INTER_RAT_HANDOVER_INFO_REQ_ST */
    WRRCRR_INTER_RAT_HANDOVER_INFO_CNF                      = 0x9939,       /*_H2ASN_MsgChoice WRRCRR_INTER_RAT_HANDOVER_INFO_CNF_ST */

    RRWRRC_INTERRAT_PLMN_SEARCH_REQ                       = 0x9942,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_REQ_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_CNF                       = 0x9943,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_CNF_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_IND                       = 0x9952,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_IND_ST */

    RRWRRC_INTERRAT_PLMN_SEARCH_STOP_REQ                  = 0x9944,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_STOP_REQ_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_STOP_CNF                  = 0x9945,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_STOP_CNF_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_SUSPEND_REQ               = 0X9946,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_SUSPEND_REQ_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_SUSPEND_CNF               = 0X9947,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_SUSPEND_CNF_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_RESUME_REQ                = 0X9948,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_RESUME_REQ_ST */
    RRWRRC_INTERRAT_PLMN_SEARCH_RESUME_CNF                = 0X9949,       /*_H2ASN_MsgChoice RRWRRC_INTERRAT_PLMN_SEARCH_RESUME_CNF_ST */

    RRWRRC_SLAVE_MEAS_REQ                                 = 0x9953,       /*_H2ASN_MsgChoice RRWRRC_SLAVE_MEAS_REQ_STRU */
    RRWRRC_SLAVE_MEAS_CNF                                 = 0x9954,       /*_H2ASN_MsgChoice RRWRRC_SLAVE_MEAS_CNF_STRU */
    RRWRRC_SLAVE_MEAS_IND                                 = 0x9955,       /*_H2ASN_MsgChoice RRWRRC_SLAVE_MEAS_IND_STRU */

    WRRCRR_SLAVE_MEAS_REQ                                 = 0x9960,       /*_H2ASN_MsgChoice WRRCRR_SLAVE_MEAS_REQ_STRU */
    WRRCRR_SLAVE_MEAS_CNF                                 = 0x9961,       /*_H2ASN_MsgChoice WRRCRR_SLAVE_MEAS_CNF_STRU */
    WRRCRR_SLAVE_MEAS_IND                                 = 0x9962,       /*_H2ASN_MsgChoice WRRCRR_SLAVE_MEAS_IND_STRU */

    /* W -> G  Gsm Cell Bsic Verify  */
    WRRCRR_BSIC_VERIFIED_REQ                              = 0x9970,       /* _H2ASN_MsgChoice WRRCRR_BSIC_VERIFIED_REQ_STRU */
    WRRCRR_BSIC_VERIFIED_CNF                              = 0x9971,       /* _H2ASN_MsgChoice WRRCRR_BSIC_VERIFIED_CNF_STRU */
    WRRCRR_BSIC_VERIFIED_IND                              = 0x9972,       /* _H2ASN_MsgChoice WRRCRR_BSIC_VERIFIED_IND_STRU */

    /* W -> G  rel all  */
    WRRCRR_RELEASE_ALL_REQ                                = 0x9975,       /* _H2ASN_MsgChoice WRRCRR_RELEASE_ALL_REQ_STRU */
    WRRCRR_RELEASE_ALL_CNF                                = 0x9976,       /* _H2ASN_MsgChoice WRRCRR_RELEASE_ALL_CNF_STRU */

    RRWRRC_HANDOVER_STOP_REQ                              = 0x9977,       /* _H2ASN_MsgChoice RRWRRC_HANDOVER_STOP_REQ_STRU */
    RRWRRC_HANDOVER_STOP_CNF                              = 0x9978,       /* _H2ASN_MsgChoice RRWRRC_HANDOVER_STOP_CNF_STRU */
    WRRCRR_HANDOVER_STOP_REQ                              = 0x9979,       /* _H2ASN_MsgChoice WRRCRR_HANDOVER_STOP_REQ_STRU */  
    WRRCRR_HANDOVER_STOP_CNF                              = 0x997A,       /* _H2ASN_MsgChoice WRRCRR_HANDOVER_STOP_CNF_STRU */  
    
    RR_WRRC_MSG_TYPE_BUTT
};
typedef VOS_UINT16 RR_WRRC_MSG_TYPE_ENUM_UINT16;

/*================== RR ģ����WRRģ��֮�����Ϣ�ṹ ==========================*/

/*****************************************************************************
 ��Ϣ����  : RRWRRC_CELL_CHANGE_REQ
 ��������  : RR���յ����緢�͵�С�����������Ϣ��ͨ����ԭ��ָʾWRRC����С�����
 �޸���ʷ  :
  1.��    ��   : 2005��09��09��
    ��    ��   : Zhangyanzhong(47368)
    �޸�����   : �����ɽṹ
*****************************************************************************/
#define BANDWIDTH_EXIST       1
#define BANDWIDTH_NOEXIST     0
/* GERAN SI�������� */
#define WRRC_RR_MAX_GERAN_SI_CNT                (8)

/* ÿ��SI���ݵ���󳤶� */
#define WRRC_RR_MAX_GERAN_SI_LEN                (23)

#define WRRC_RR_MAX_FORBLA_NUM                  (32)

/* W��G֮������͸����Ϣ��󳤶� */
#define RRWRRC_RR_PHY_MAX_MSG_SIZE              (80) /* ͨ��WAS͸����GAS�������֮����Ϣ����󳤶� */

#define WRRCRR_RRC_PHY_MAX_MSG_SIZE             (230)/* ͨ��GAS͸����WRRC�������֮����Ϣ����󳤶� */

#define RRWRR_INVALID_RXLEV                     (0X00FF)

/* W��G֮��NET SCAN����С�������� */
#define WRRC_RR_MAX_NET_SCAN_CELL_NUM            (20)

/* W����֧�ֵ����Ƶ����� */
#define WRRC_RR_MAX_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM  (3)

/* UTRAN ����Ƶ��֧��С�������Ŀ */
#define WRRC_RR_MAX_UTRAN_CELL_PER_FREQ_NUM            (32)

/* W��G��С�������Ŀ */
#define WRRC_RR_MAX_SLAVE_GSM_CELL_NUM                 (64)

/* G���ϱ�������BSICС������ */
#define WRRC_RR_MAX_SLAVE_GSM_BSIC_RPT_CELL_NUM        (8)

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT16                          usUarfcn;           /* UTRAN����������Ƶ��*/
    VOS_UINT8                           ucDiversity;        /* 1��ʾWС��ʹ��Diversity, 0 ��ʾû��ʹ��Diversity */
    VOS_UINT8                           ucBandwidthFlag;    /* ������Ϣ�����Ƿ��ʶ */
    VOS_UINT8                           ucBandwidth;        /*  WС���ŵ����� */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT16                          usScramblingCode;   /* WС�������� */

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucResv[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}RRWRRC_CELL_CHANGE_REQ_ST;


#define WRRC_RR_CELL_RESEL_ACCESS_NOT_PERMIT_TIMER_LEN          100  /*100s*/

typedef enum
{
    EN_SUCCESS    = 0,                                          /* �л��ɹ�                         */
    EN_FAILURE,                                                 /* �л�ʧ��                         */
    EN_MESSAGE_INVALID,                                         /* ���յ���Ϣ��Ч                   */
    EN_PROTOCOL_ERROR,                                          /* ��ϢЭ���                       */
    EN_UNSUPORTED_CONFIGURATION,                                /* ��Ϣ�а�����֧�ֵ�����           */
    EN_PHY_CHANNEL_FAILURE,                                     /* ������·ʧ��                     */
    EN_CELL_REG_REJED_FAIL,                                     /* ��ѡС������ϵͳ��ע��ʧ��       */

    /* ����ԭ��ֵ������ѡʱ */
    EN_CELL_RESEL_FAIL_REASON_CELL_BAR,                         /* С����Bar                        */
    EN_CELL_RESEL_FAIL_REASON_PLMN_CHECK_FAIL            ,      /* PLMN�ж�ʧ��                     */
    EN_CELL_RESEL_FAIL_REASON_NOT_SUITABLE_S_CRITERION   ,      /* ������S׼��                      */
    EN_CELL_RESEL_FAIL_REASON_OTHERS                     ,      /* ����ԭ��                         */

    EN_CELL_CHANGE_RRC_CONN_REJ                          ,      /* RRC���ӱ��� */
    EN_CELL_RESEL_FAIL_REASON_ACCESS_NOT_PERMIT          ,      /* ����ȼ�������                   */

    
    EN_CELL_RESEL_FAIL_REASON_NON_NCELL_NOT_AVAILABLE    ,      /* ������С��������, GAS �ڲ�ת��ʹ��, WRR ��ʹ�ø�ֵ */

    EN_CELL_RESEL_FAIL_REASON_S_OR_C1_CHECK_FAIL         ,     /* GW֮����ѡ������W��S׼����߲�����G��C1׼�����ڷ�ֹƹ����ѡ  */
    
    EN_CELL_RESEL_FAIL_REASON_BUTT
}RRC_RR_CNF_ENUM;
typedef VOS_UINT32     RRC_RR_CNF_ENUM_UINT32;

typedef enum
{
    EN_RRC_RR_RESEL_NORMAL    = 0,                  /* W2G������ѡ����ҪGAS�жϵ�Чplmn�б��Լ�forbid la��Ϣ*/
    EN_RRC_RR_RESEL_ANYCELL_CAMP,                   /* W��anycellפ��������ҪGAS�жϵ�Чplmn�б��Լ�forbid la��Ϣ*/
    EN_RRC_RR_RESEL_BUTT
}RRC_RR_RESEL_TYPE_ENUM;
typedef VOS_UINT32     RRC_RR_RESEL_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_RR_MEAS_CMD_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GU֮��MEAS ����
*****************************************************************************/
enum RRC_RR_MEAS_CMD_ENUM
{
    EN_RRC_RR_MEAS_CMD_RELEASE                             = 0,
    EN_RRC_RR_MEAS_CMD_SETUP                                  ,

    EN_RRC_RR_MEAS_CMD_BUTT
};
typedef VOS_UINT8 RRC_RR_MEAS_CMD_ENUM_UINT8;


/*****************************************************************************
 ö����    : RRC_RR_MEAS_GAS_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS��ģ����ʱ��GASĿǰ��״̬����WRRC;
*****************************************************************************/
enum RRC_RR_MEAS_GAS_STATUS_ENUM
{
    EN_RRC_RR_MEAS_GAS_STATUS_IDLE                           = 0,               /* IDLE̬ */
    EN_RRC_RR_MEAS_GAS_STATUS_CONNECT                           ,               /* CONNECT̬ */

    EN_RRC_RR_MEAS_GAS_STATUS_BUTT
};
typedef VOS_UINT8 RRC_RR_MEAS_GAS_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_RR_WAS_STATUS_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : WAS��Э��״̬
*****************************************************************************/
enum RRC_RR_WAS_STATUS_ENUM
{
    EN_RRC_RR_WAS_STATUS_IDLE                             = 0,                  /* _H2ASN_MsgChoice RRC_RR_DRX_BSIC_TIMER_PARA_STRU */
    EN_RRC_RR_WAS_STATUS_URA_PCH                             ,                  /* _H2ASN_MsgChoice RRC_RR_DRX_BSIC_TIMER_PARA_STRU */
    EN_RRC_RR_WAS_STATUS_CELL_PCH                            ,                  /* _H2ASN_MsgChoice RRC_RR_DRX_BSIC_TIMER_PARA_STRU */
    EN_RRC_RR_WAS_STATUS_FACH                                ,                  /* _H2ASN_MsgChoice RRC_RR_FACH_BSIC_TIMER_PARA_STRU */
    EN_RRC_RR_WAS_STATUS_DCH                                 ,                  /* _H2ASN_MsgChoice RRC_RR_DCH_BSIC_TIMER_PARA_STRU */

    EN_RRC_RR_WAS_STATUS_BUTT
};
typedef VOS_UINT8 RRC_RR_WAS_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_RR_REL_REASON_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GU֮��REL ALL������ͷ�ԭ��ֵ
*****************************************************************************/
enum RRC_RR_REL_REASON_ENUM
{
    EN_RRC_RR_REL_REASON_SYSHO                             = 0,
    EN_RRC_RR_REL_REASON_OTHER                                  ,

    EN_RRC_RR_REL_REASON_BUTT
};
typedef VOS_UINT8 RRC_RR_REL_REASON_ENUM_UINT8;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_CNF_ENUM_UINT32              enResult;        /* �л���� */
}RRWRRC_CELL_CHANGE_CNF_ST;



typedef struct
{
    VOS_UINT8                           ucNCC;
    VOS_UINT8                           ucBCC;
}RRC_BSIC_INFO_ST;

typedef struct
{
    VOS_UINT32                                  ulCnt;            /* ָʾ���鳤��1-23*//* ��ЧֵΪ1~23 */
    VOS_UINT8                                   aucGeranSysInfoBlock[WRRC_RR_MAX_GERAN_SI_LEN];
    VOS_UINT8                                   aucReserved[1];
}RRC_GSM_GREAN_SYS_INFO_ST;

typedef struct
{
    VOS_UINT8                                   aucReserved[2];
    RRC_GSM_GERAN_SYS_INFO_ENUM_UINT8           enGeranInfoInd;     /* ucGeranSysInfoCntΪ0ʱ����ֵ��Ч */
    VOS_UINT8                                   ucGeranSysInfoCnt;                     /* ��ЧֵΪ 0~ 8 */
    RRC_GSM_GREAN_SYS_INFO_ST                   stGeranSysInfor[WRRC_RR_MAX_GERAN_SI_CNT];
}RRC_CELL_CHANGE_GSM_CELL_SYS_INFO_BLOCK_ST;

typedef struct
{
    RRC_BSIC_INFO_ST                    stBsicInfo;

    VOS_INT16                           sRxlev;              /* GС���źŵ�ƽ����λ��dBm,û�в⵽�źŵ�ƽʱ��ֵΪRRWRR_INVALID_RXLEV */

    /*�����·�cellchangefromutran��WASʱ��WAS��һ��ά����G�����б����Ƶ�㡢BCC��NCC�������·���һ�£���ulSyncFlagֵ��дVOS_TRUE��bcc��ncc��Timealignment��fnoffset����ά��ֵ��д��
      ��Ƶ�㡢BCC��NCC�κ�һ��ֵ�뱾��ά���Ĳ�һ�£���ulSyncValidֵ��дVOS_FALSE */
    VOS_UINT32                          ulSyncFlag;              /* 0:��ʾͬ����Ч 1: ��ʾͬ����Ч */
    VOS_INT32                           lFNOffset;
    VOS_UINT32                          ulTimeAlignmt;

    RRC_GSM_BAND_INDICATOR_ENUM_UINT32  enBandIndictor;
    VOS_UINT16                          usBcchArfcn;
    VOS_UINT8                           ucNCmodeFlag;        /* NCMode���ڱ�־ */
    VOS_UINT8                           ucNCmode;
    RRC_CELL_CHANGE_GSM_CELL_SYS_INFO_BLOCK_ST stGeranSysInfo;
}RRC_CELL_CHANGE_GSM_CELL_INFO_ST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_CELL_CHANGE_GSM_CELL_INFO_ST    stGsmCellInfo; /* GSMС����Ϣ */

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucResv[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}WRRCRR_CELL_CHANGE_REQ_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_CNF_ENUM_UINT32              enResult;      /* CELL CHANGE�л���� */
}WRRCRR_CELL_CHANGE_CNF_ST;

/*****************************************************************************
 ��Ϣ����  : RRWRRC_HANDOVER_REQ
 ��������  : RR���ʹ�ԭ��ָʾWRRC����ϵͳ���л�����
 �޸���ʷ  :
  1.��    ��   : 2005��09��09��
    ��    ��   : Zhangyanzhong(47368)
    �޸�����   : �����ɽṹ
*****************************************************************************/
enum RRC_RAT_TYPE_ENUM
{
    RRC_RAT_WCDMA_FDD               = 0,                /* only WCDMA    */
    RRC_RAT_WCDMA_GSM               = 1,                /* WCDMA and GSM */
    RRC_RAT_GSM                     = 2,                /* only GSM      */
    RRC_RAT_TYPE_BUTT
};
typedef VOS_UINT32  RRC_RAT_TYPE_ENUM_UINT32;

typedef enum
{
    EN_RRC_RR_SEARCH_RESULT_SUCC                 = 0,       /* �ɹ� */
    EN_RRC_RR_SEARCH_RESULT_FAIL                    ,       /* ʧ�� */
    EN_RRC_RR_SEARCH_RESULT_ABNORMAL                ,       /* �쳣 */
    EN_RRC_RR_SEARCH_RESULT_STATE_NOT_ALLOWED       ,       /* ��ǰ״̬������ */
    EN_RRC_RR_SEARCH_RESULT_FREQ_LOCK               ,       /* ��Ƶ */
    EN_RRC_RR_SEARCH_RESULT_PARA_ERROR              ,       /* �������� */

    EN_RRC_RR_SEARCH_RESULT_BUTT
}RRC_RR_SEARCH_RESULT_ENUM;
typedef VOS_UINT32 RRC_RR_SEARCH_RESULT_ENUM_UINT32;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_SINGAL_INFO_ENUM_UINT32         enSignalInfo;       /* �������ӵ����� */
    RRC_CIPHER_ACTIVE_ENUM_UINT32       enCipherActiveFlg;  /* ָʾGSM�����Ƿ񼤻� */
    VOS_UINT32                          ulMcc;              /* ������ */
    
    PS_BOOL_ENUM_UINT8                  enLteOriginatedFlg; /* ��ǰҵ���Ƿ��� L �·���� */
    VOS_UINT8                           aucRsv[3];

    VOS_UINT16                          usHandOverInfoLen;               /* �л�ʱ�տ���Ϣ�а�������Ϣ�ĳ��� */
    VOS_UINT8                           aucHandOverInfo[2];              /* �л�ʱ�տ���Ϣ�а�������Ϣ�ĵ�ַ */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RRWRRC_HANDOVER_REQ_ST;


/*****************************************************************************
 ��Ϣ����  : RRWRRC_HANDOVER_CNF
 ��������  : WRRC�ô���ϢӦ��RR���͵�RRWRRC_HANDOVER_REQ��Ϣ
 �޸���ʷ  :
  1.��    ��   : 2005��09��09��
    ��    ��   : Zhangyanzhong(47368)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_CNF_ENUM_UINT32              enResult;
    VOS_UINT8                           ucDataFlag;      /* �л�ʱWRRC�ظ�����Ϣ�д������ݵı�־ */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT16                          usDataLen;       /* WRRC�ظ�����Ϣ�ĳ��� */
    VOS_UINT8                           aucData[2];      /* WRRC�ظ�����Ϣ������ */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}RRWRRC_HANDOVER_CNF_ST;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[4];      /* ����λ */
}RRWRRC_HANDOVER_STOP_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[4];      /* ����λ */
}RRWRRC_HANDOVER_STOP_CNF_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[4];      /* ����λ */
}WRRCRR_HANDOVER_STOP_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[4];      /* ����λ */
}WRRCRR_HANDOVER_STOP_CNF_STRU;

/*****************************************************************************
 ��Ϣ����  : WRRCRR_HANDOVER_REQ
 ��������  : WRRC���ʹ�ԭ��ָʾRR����ϵͳ���л�����
 �޸���ʷ  :
  1.��    ��   : 2005��09��09��
    ��    ��   : Zhangyanzhong(47368)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_HANDOVER_GSM_GPRS_INFO_ST       struGsmGprsCellInfo;
    RRC_SINGAL_INFO_ENUM_UINT32         enSignalInfo;
    VOS_UINT32                          ulMcc;              /* ������ */
    
    PS_BOOL_ENUM_UINT8                  enLteOriginatedFlg; /* ��ǰҵ���Ƿ��� L �·���� */
    VOS_UINT8                           aucRsv[3];
}WRRCRR_HANDOVER_REQ_ST;

/*****************************************************************************
 ��Ϣ����  : WRRCRR_HANDOVER_CNF
 ��������  : RR�ô�ԭ��Ӧ��WRRC���͵�WRRCRR_HANDOVER_REQ��Ϣ
 �޸���ʷ  :
  1.��    ��   : 2005��09��09��
    ��    ��   : Zhangyanzhong(47368)
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_CNF_ENUM_UINT32              enResult;
    VOS_UINT8                           ucDataFlag;
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucData[2];
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}WRRCRR_HANDOVER_CNF_ST;


typedef struct
{
    VOS_UINT32                          ulMcc;              /* MCC,3 bytes      */
    VOS_UINT32                          ulMnc;              /* MNC,2 or 3 bytes */
}WRRCRR_PLMN_ID_STRU;

#define     WRRCRR_MAX_HIGH_PLMN_NUM           (16)                 /* ��������PLMN�������� */
#define     WRRCRR_MAX_LOW_PLMN_NUM            (16)                 /* ��������PLMN�������� */
#define     WRRCRR_MAX_AVAIL_PLMN_NUM          (18)                 /*out of serviceʱ,was����GAS���PLMN�����W*/
#define     WRRCRR_MAX_EQUAL_PLMN_NUM          (16)                  /*�ض���ʱ,was����GAS���EPLMN�����W*/



typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          ulGsmCellCnt;       /* �����GSM��������ֻ��Ҫ�ҵ���Щ������PLMN����,ȡֵ��Χ 0 ~ 32,0��ʾû����������ҪGAS��ȫƵ������ */
    RRC_SAVE_CELL_INFO_FOR_GAS_ST       astGsmCellInfo[RRC_MAX_INTER_GSM_CELL_NUM];   /* ÿ��GSMС����Ϣ */

    VOS_UINT32                          ulAvailPlmnIdNum;        /* PLMN ID���� */
    WRRCRR_PLMN_ID_STRU                 astAvailPlmnIdList[WRRCRR_MAX_AVAIL_PLMN_NUM];       /* PlMN��ʶ */
}WRRCRR_PLMN_SEARCH_REQ_ST;
typedef struct
{
    WRRCRR_PLMN_ID_STRU                 stPlmnId;             /* PLMN ID    */
    RRC_RAT_TYPE_ENUM_UINT32            lRat;               /* ���뼼�� */
}WRRCRR_PLMN_ID_WITH_RAT_STRU;

typedef struct
{
    WRRCRR_PLMN_ID_STRU                 stPlmnId;             /* PLMN ID    */
    VOS_INT32                           lRscp;              /* RSCP����ֵ */
}WRRCRR_LOW_PLMN_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulHighPlmnNum;                          /* ������PLMN�ĸ��� */
    VOS_UINT32                          ulLowPlmnNum;                           /* ������PLMN�ĸ��� */
    WRRCRR_PLMN_ID_STRU                 astHighPlmnList[WRRCRR_MAX_HIGH_PLMN_NUM];   /* ������PLMN�б�   */
    WRRCRR_LOW_PLMN_INFO_STRU           astLowPlmnList[WRRCRR_MAX_LOW_PLMN_NUM];     /* ������PLMN�б�   */
}WRRCRR_PLMN_ID_LIST_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */

    RRC_RR_SEARCH_RESULT_ENUM_UINT32    enResult;           /* ��ʹ�����е�����ԭ��ֵ:EN_SUCCESS or EN_FAILURE */

    /* enResultԭ��ֵΪEN_SUCCESSʱ,����Ҫ�����Ƿ���PLMN�����û��PLMN������ΪҲ��ʧ�� */
    WRRCRR_PLMN_ID_LIST_STRU            PlmnIdList;         /* �ϱ���PLMN ID�б� */
}WRRCRR_PLMN_SEARCH_CNF_ST;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_PLMN_SEARCH_STOP_REQ_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_PLMN_SEARCH_STOP_CNF_ST;

/*****************************************************************************
 ��Ϣ����  : RR_RRC_RESEL_TYPE_ENUM
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2010��9��7��
    ��    ��   : Chenwenfeng 59720
    �޸�����   : ������ö��
*****************************************************************************/
typedef enum
{
    EN_RR_RRC_RESEL_NORMAL        = 0,                                          /* G2W������ѡ����ҪWAS�жϵ�Чplmn�б��Լ�forbid la��Ϣ*/
    EN_RR_RRC_RESEL_ANYCELL_CAMP     ,                                          /* G��anycellפ��������ҪwAS�жϵ�Чplmn�б��Լ�forbid la��Ϣ*/
    EN_RR_RRC_RESEL_BUTT
}RR_RRC_RESEL_TYPE_ENUM;
typedef VOS_UINT32 RR_RRC_RESEL_TYPE_ENUM_UINT32;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT16                          usFreqInfo;                             /* Ƶ�� */
    VOS_UINT16                          usPrimaryScramCode;                     /* С������ */
    VOS_UINT8                           ucDiversity;                            /* �ּ�ָʾ */
    VOS_UINT8                           aucReserve1[3];                         /* 4�ֽڶ��룬���� */
    RRC_SINGAL_INFO_ENUM_UINT32         enSignalInfo;
    RR_RRC_RESEL_TYPE_ENUM_UINT32       enReselType;                            /* ��ҪĿ��С���ǰ���ANYCELL����SUITABLEפ��׼�����פ�� */

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucResv[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}RRWRRC_CELL_RESEL_REQ_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_CNF_ENUM_UINT32              enCnf;
    VOS_UINT32                          ulTBarLen;      /* ��λΪS������enCnfΪEN_CELL_RESEL_FAIL_REASON_CELL_BARʱ��Ч */

    /* ��GW��ѡ�޷�פ��ʱ����д��sQrxLevValueΪ����Э�������ʵ������ֵ */
    /* �˲���ֻ����EN_CELL_RESEL_FAIL_REASON_S_OR_C1_CHECK_FAILͬʱʹ�� */
    VOS_INT16                           sQrxlevMin;   /* RSRP��ͽ������ޣ���λ1/8dB*/

    VOS_INT16                           sQqualMin;    /* Ec/No��ͽ������ޣ���λ1/8dB*/
}RRWRRC_CELL_RESEL_CNF_ST;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_SAVE_CELL_INFO_FOR_GAS_ST       stGsmCellInfo;
    RRC_SINGAL_INFO_ENUM_UINT32         enSignalInfo;
    RRC_RR_RESEL_TYPE_ENUM_UINT32         enReselType;   /* W2G��ѡGAS�費��Ҫ�жϵ�Чplmn��forbid LA ��־*/

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucResv[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}WRRCRR_CELL_RESEL_REQ_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_CNF_ENUM_UINT32              enResult;

    /* ��usResult ԭ��ֵΪEN_CELL_RESEL_FAIL_REASON_S_OR_C1_CHECK_FAILʱ�� sC1Param������Ч
        ��ʾ��C1ֵ������صĲ�����WAS���㹫ʽC1= sRxlev- sC1Param, RxlevΪһ����   */
    VOS_INT16                                               sC1Param;
    
    VOS_UINT8                                               aucReserved[2];     
}WRRCRR_CELL_RESEL_CNF_ST;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];     /* 4�ֽڶ��룬���� */
}RRWRRC_CELL_CHANGE_TIMER_EXPIRED_REQ_ST;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];     /* 4�ֽڶ��룬���� */
}RRWRRC_CELL_CHANGE_TIMER_EXPIRED_CNF_ST;



typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];     /* 4�ֽڶ��룬���� */
}WRRCRR_CELL_CHANGE_TIMER_EXPIRED_REQ_ST;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];     /* 4�ֽڶ��룬���� */
}WRRCRR_CELL_CHANGE_TIMER_EXPIRED_CNF_ST;

/*****************************************************************************
 ��Ϣ����  : WRRCRR_CELL_RESEL_TIMER_EXPIRED_REQ
 ��������  : WRR�ô�ԭ��֪ͨ��ѡ��ʱ
 �޸���ʷ  :
  1.��    ��   : 2006��12��25��
    ��    ��   : Jinying
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];     /* 4�ֽڶ��룬���� */
}WRRCRR_CELL_RESEL_TIMER_EXPIRED_REQ_ST;

/*****************************************************************************
 ��Ϣ����  : WRRCRR_CELL_RESEL_TIMER_EXPIRED_CNF
 ��������  : RR�ô�ԭ��Ӧ��WRRCRR_CELL_RESEL_TIMER_EXPIRED_REQ_ST
 �޸���ʷ  :
  1.��    ��   : 2006��12��25��
    ��    ��   : Jinying
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];     /* 4�ֽڶ��룬���� */
}WRRCRR_CELL_RESEL_TIMER_EXPIRED_CNF_ST;

#define RR_WRRC_INTER_RAT_HANDOVER_INFO_LEN                (250)                /* INTER_RAT_HANDOVER_INFO ����, �250�ֽ� */


/*******************************************************************************
 �ṹ��    : RRWRRC_INTER_RAT_HANDOVER_INFO_REQ_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ RRWRRC_INTER_RAT_HANDOVER_INFO_REQ �Ľṹ
             ����Ϣ������WRR��ȡinter rat hand over info��
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    PS_BOOL_ENUM_UINT8                  enNeedCmprVer;                          /* �Ƿ���Ҫѹ���汾����Ϣ */
    VOS_UINT8                           aucReserve1[3];                         /* �����ֶ�,���ڽ�����չ */
    VOS_UINT32                          ulMcc;                                  /* ��ǰפ�������룬�й�PLMN */
}RRWRRC_INTER_RAT_HANDOVER_INFO_REQ_ST;

/*******************************************************************************
 �ṹ��    : RRWRRC_INTER_RAT_HANDOVER_INFO_CNF_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ RRWRRC_INTER_RAT_HANDOVER_INFO_CNF �Ľṹ
             ����Ϣ������GAS�ظ� inter rat hand over info��
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                    MsgHeader;          /* ��Ϣͷ */         /*_H2ASN_Skip*/
    VOS_UINT16                         usDataLen;
    VOS_UINT8                          aucData[RR_WRRC_INTER_RAT_HANDOVER_INFO_LEN];
}RRWRRC_INTER_RAT_HANDOVER_INFO_CNF_ST;

/*******************************************************************************
 �ṹ��    : WRRCRR_INTER_RAT_HANDOVER_INFO_REQ_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ WRRCRR_INTER_RAT_HANDOVER_INFO_REQ �Ľṹ
             ����Ϣ������GAS��ȡGSM������Ϣ��
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulMcc;                                  /* ��ǰפ�������룬�й�PLMN */
}WRRCRR_INTER_RAT_HANDOVER_INFO_REQ_ST;

/*******************************************************************************
 �ṹ��    : WRRCRR_INTER_RAT_HANDOVER_INFO_CNF_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ WRRCRR_INTER_RAT_HANDOVER_INFO_CNF �Ľṹ
             ����Ϣ������WAS�ظ� GSM������Ϣ��
*******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                    MsgHeader;          /* ��Ϣͷ */         /*_H2ASN_Skip*/
    VOS_UINT8                          ucClassmark2Len;                        /* Classmark2 ���� */
    VOS_UINT8                          aucClassmark2[GSM_CLASSMARK2_MAX_LEN];  /* Classmark2 ���� */
    VOS_UINT8                          ucClassmark3Len;                        /* Classmark3 ���� */
    VOS_UINT8                          aucClassmark3[GSM_CLASSMARK3_MAX_LEN];  /* Classmark3 ���� */
    VOS_UINT8                          aucReserve1[2];                         /* 4�ֽڶ��룬���� */
}WRRCRR_INTER_RAT_HANDOVER_INFO_CNF_ST;

#define RR_WRRC_MAX_3GNCELL_NUM          96                              /* channel release GAS���Я��96��С�� */

/*****************************************************************************
 ��Ϣ����  : RRC_CELL_SEL_3GNCELL_ST
 ��������  : channel releaseЯ����3GС���б�
 �޸���ʷ  :
  1.��    ��   : 2010��03��08��
    ��    ��   :
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                  usFreq;                             /* Ƶ�� */
    VOS_UINT16                  usScramblingCode;                   /* ���������Чʹ��0xFFFFֵ */
    VOS_UINT8                   ucDiversity;                        /* С���Ƿ�ʹ�÷ּ�ָʾ,���������Ч���ּ�ָʾҲ��Ч */
    VOS_UINT8                   ucBandWidth;                        /*  WС���ŵ����� *//* W��ʱ���� */
    VOS_UINT8                   aucReserve1[2];                     /* 4�ֽڶ��룬���� */

}RRC_CELL_SEL_3GNCELL_ST;

/*****************************************************************************
 ��Ϣ����  : RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_REQ_ST
 ��������  : G channel release�󣬸�W������Ϣ
 �޸���ʷ  :
  1.��    ��   : 2010��03��08��
    ��    ��   :
    �޸�����   : �����ɽṹ
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[3];                         /* 4�ֽڶ��룬���� */
    VOS_UINT8                           uc3GNCellCnt;                           /* total valid cell number */
    RRC_CELL_SEL_3GNCELL_ST             ast3GNCell[RR_WRRC_MAX_3GNCELL_NUM];

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucResv[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_REQ_ST;

/*****************************************************************************
 ��Ϣ����  : RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_CNF_ST
 ��������  : ��RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_REQ�Ļظ�
 �޸���ʷ  :
  1.��    ��   : 2010��03��08��
    ��    ��   :
    �޸�����   : �����ɽṹ
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    RRC_RR_CNF_ENUM_UINT32              enResult;                               /* ��ѡ��� */
}RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_CNF_ST;

/*****************************************************************************
 ��Ϣ����  : RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_REQ_ST
 ��������  : ��RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_REQ��ʱ����Ϣ
 �޸���ʷ  :
  1.��    ��   : 2010��03��08��
    ��    ��   :
    �޸�����   : �����ɽṹ
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];                         /* 4�ֽڶ��룬���� */
}RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_REQ_ST;


/*****************************************************************************
 ��Ϣ����  : RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_CNF_ST
 ��������  : ��RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_REQ_ST��Ϣ�Ļظ�
              ����Ϣ����Ҫԭ��ֵ�����ܳɹ�ʧ��,Gas����һ��
 �޸���ʷ  :
  1.��    ��   : 2010��03��08��
    ��    ��   :
    �޸�����   : �����ɽṹ
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];     /* 4�ֽڶ��룬���� */
}RRWRRC_CELL_SEL_AFTER_CHANNEL_REL_TIMER_EXPIRED_CNF_ST;



typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          ulGsmCellCnt;
    RRC_SAVE_CELL_INFO_FOR_GAS_ST       astGsmCellInfo[RRC_MAX_INTER_GSM_CELL_NUM];   /* ÿ��GSMС����Ϣ */
    VOS_UINT32                          ulEquPlmnIdNum;                              /* PLMN ID���� ,PLMN NUM = 0��ʾ����פ��*/
    WRRCRR_PLMN_ID_STRU                 astEquPlmnIdList[WRRCRR_MAX_EQUAL_PLMN_NUM];  /* PlMN��ʶ��ֻ��EPLMN*/
    VOS_UINT32                          ulWaitTimeLen;                          /* wait timeʱ�䣬��λ��ms */

    /* ר�����ȼ���Ϣ, 0: ��ʾ�����ڣ�1 ��ʾ����*/
    GURRC_VALID_FLAG_ENUM_UINT8                             enDPriInfoPresent;
    VOS_UINT8                                               ucResv[3];
    GURRC_DEDICATED_PRI_INFO_STRU                           stDPriInfo;
}WRRCRR_CELL_SEL_REDIRECTION_REQ_ST;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    RRC_RR_CNF_ENUM_UINT32              enResult;                               /* ����С����� */
}WRRCRR_CELL_SEL_REDIRECTION_CNF_ST;



typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];                         /* 4�ֽڶ��룬���� */
}WRRCRR_CELL_SEL_REDIRECTION_ABORT_REQ_ST;




typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];     /* 4�ֽڶ��룬���� */
}WRRCRR_CELL_SEL_REDIRECTION_ABORT_CNF_ST;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           ucClassmark2Len;                        /* Classmark2 ���� */
    VOS_UINT8                           aucClassmark2[GSM_CLASSMARK2_MAX_LEN];  /* Classmark2 ���� */

    VOS_UINT8                           ucClassmark3Len;                        /* Classmark3 ���� */
    VOS_UINT8                           aucClassmark3[GSM_CLASSMARK3_MAX_LEN];  /* Classmark3 ���� */

    VOS_UINT8                           aucReserve1[2];                         /* 4�ֽڶ��룬���� */

}RRWRRC_CLASSMARK_CHANGE_IND_ST;


typedef enum
{
    EN_RRC_RR_SEARCH_BG                 = 0,                                    /* WAS/GAS֪ͨGAS/WAS�������� */
    EN_RRC_RR_SEARCH_PLMN_LIST             ,                                    /* WAS/GAS֪ͨGAS/WAS��PLMN LIST��  */
    EN_RRC_RR_SEARCH_NET_SCAN              ,                                    /* WAS/GAS֪ͨGAS/WAS��NET SCAN��  */
    EN_RRC_RR_SEARCH_BG_HIGH_RAT           ,                                    /* �����ȼ�RAT BG�� */
    EN_RRC_RR_SEARCH_BUTT
}RRC_RR_SEARCH_TYPE_ENUM;

typedef VOS_UINT32 RRC_RR_SEARCH_TYPE_ENUM_UINT32;

typedef struct
{
    WRRCRR_PLMN_ID_STRU                 PlmnId;             /* PlMN��ʶ       */
    VOS_UINT32                          ulForbLac;          /* ��ֹע������Ϣ */
}WRRCRR_FORB_LA_STRU;


typedef struct
{
    VOS_UINT16                          usCellInfoNum;                          /* Ҫ���ϱ���С����������Χ1~20 */
    VOS_INT16                           sCellPwrThreshold;                      /* С���ϱ��������ޣ�ȡֵ��ΧΪ-110~-47 */
    VOS_UINT32                          ulBand;                                 /* Ҫ������BAND��Ϣ�������Ҫ��������֧��Ƶ������Ϊ0xFFFFFFFF */
}WRRCRR_NET_SCAN_REQ_INFO_STRU;
typedef struct
{
    VOS_UINT16                                  usArfcn;                        /* ����Ƶ�� */
    VOS_UINT16                                  usC1;                           /* cell reselection coefficient,W�ϱ�0 */
    VOS_UINT16                                  usC2;                           /* cell reselection coefficient,W�ϱ�0 */
    VOS_UINT16                                  usLocAreaCode;                  /* LAC */
    VOS_UINT32                                  ulMcc;                          /* MCC,3 bytes      */
    VOS_UINT32                                  ulMnc;                          /* MNC,2 or 3 bytes */
    VOS_UINT16                                  usBsic;                         /* W�ϱ�0 */
    VOS_INT16                                   sRxlev;                         /* W���ϱ�RSCP */
    VOS_INT16                                   sRssi;                          /* W���ϱ�RSCP */
    VOS_UINT16                                  usPSC;                          /* GС���ϱ�0xFFFF��W�ϱ�PSC */
    VOS_UINT32                                  ulCellId;                       /* С��ID */
    VOS_UINT32                                  ulBand;                         /* С��BAND��Ϣ */
}WRRCRR_CELL_INFO_STRU;


typedef struct
{
    VOS_UINT16                          usCellInfoNum;                          /* ʵ���ϱ���С������ */
    VOS_UINT8                           aucRsv[2];

    WRRCRR_CELL_INFO_STRU               astCellInfoList[WRRC_RR_MAX_NET_SCAN_CELL_NUM];    /* �ϱ�������������С����Ϣ */
}WRRCRR_NET_SCAN_INFO_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_TYPE_ENUM_UINT32      enSearchType;                           /* WAS֪ͨGAS���������ѻ���PLMN LIST�� */
    WRRCRR_PLMN_ID_STRU                 stPlmnId;                               /* PlMN��ʶ��ֻ�ڱ�������Ч */
    VOS_UINT32                          ulForbLaNum;                            /* ��ֹע�����ĸ��� */
    WRRCRR_FORB_LA_STRU                 aForbLaList[WRRC_RR_MAX_FORBLA_NUM];    /* ��ֹע�����б� */
    WRRCRR_NET_SCAN_REQ_INFO_STRU       stNetScanReqInfo;                       /* NET SCAN������Ϣ */
}WRRCRR_INTERRAT_PLMN_SEARCH_REQ_ST;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_RESULT_ENUM_UINT32    enResult;                               /* �����ѳɹ���ʧ�ܣ�NET SCAN��GAS����Я���ɹ���ʧ�ܣ��������ʧ�� */
}WRRCRR_INTERRAT_PLMN_SEARCH_CNF_ST;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_RESULT_ENUM_UINT32    enResult;                               /* �����ѳɹ���ʧ�ܣ�NET SCAN��GASֻЯ���ɹ� */
    RRC_RR_SEARCH_TYPE_ENUM_UINT32      enSearchType;                           /* WAS֪ͨGAS���������ѻ���PLMN LIST�� */
    WRRCRR_PLMN_ID_LIST_STRU            stPlmnIdList;                           /* �ϱ���PLMN ID�б� */
    WRRCRR_NET_SCAN_INFO_STRU           stNetScanInfo;                          /* �ϱ���NET SCAN�Ľ�� */

}WRRCRR_INTERRAT_PLMN_SEARCH_IND_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_INTERRAT_PLMN_SEARCH_STOP_REQ_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_TYPE_ENUM_UINT32      enSearchType;                           /*�����ѣ�PLMN LIST�ѻ���NET SCAN */
    WRRCRR_NET_SCAN_INFO_STRU           stNetScanInfo;                          /* �ϱ���NET SCAN�Ľ�� */
}WRRCRR_INTERRAT_PLMN_SEARCH_STOP_CNF_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_REQ_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_INTERRAT_PLMN_SEARCH_SUSPEND_CNF_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_REQ_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}WRRCRR_INTERRAT_PLMN_SEARCH_RESUME_CNF_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_TYPE_ENUM_UINT32      enSearchType;                           /* GAS֪ͨWAS���������ѻ���PLMN LIST�� */
    WRRCRR_PLMN_ID_STRU                 stPlmnId;                               /* PlMN��ʶ */
    VOS_UINT32                          ulForbLaNum;                            /* ��ֹע�����ĸ��� */
    WRRCRR_FORB_LA_STRU                 aForbLaList[WRRC_RR_MAX_FORBLA_NUM];    /* ��ֹע�����б�                           */
    WRRCRR_NET_SCAN_REQ_INFO_STRU       stNetScanReqInfo;                       /* �����NET SCAN����Ϣ */
}RRWRRC_INTERRAT_PLMN_SEARCH_REQ_ST;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_RESULT_ENUM_UINT32    enResult;                               /* �����ѳɹ���ʧ�� */
}RRWRRC_INTERRAT_PLMN_SEARCH_CNF_ST;



typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_RESULT_ENUM_UINT32    enResult;                               /* �����ѳɹ���ʧ�� */
    RRC_RR_SEARCH_TYPE_ENUM_UINT32      enSearchType;                           /* GAS֪ͨWAS���������ѻ���PLMN LIST�� */
    WRRCRR_PLMN_ID_LIST_STRU            PlmnIdList;                             /* �ϱ���PLMN ID�б� */
    WRRCRR_NET_SCAN_INFO_STRU           stNetScanInfo;                          /* �ϱ���NET SCAN�Ľ�� */
}RRWRRC_INTERRAT_PLMN_SEARCH_IND_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}RRWRRC_INTERRAT_PLMN_SEARCH_STOP_REQ_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_SEARCH_TYPE_ENUM_UINT32      enSearchType;                           /* �����ѣ�PLMN LIST�ѻ���NET SCAN */
    WRRCRR_NET_SCAN_INFO_STRU           stNetScanInfo;                          /* �ϱ���NET SCAN�Ľ�� */
}RRWRRC_INTERRAT_PLMN_SEARCH_STOP_CNF_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}RRWRRC_INTERRAT_PLMN_SEARCH_SUSPEND_REQ_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}RRWRRC_INTERRAT_PLMN_SEARCH_SUSPEND_CNF_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}RRWRRC_INTERRAT_PLMN_SEARCH_RESUME_REQ_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT8                           aucReserve1[4];
}RRWRRC_INTERRAT_PLMN_SEARCH_RESUME_CNF_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];
}RRWRRC_CELL_RESEL_STOP_REQ_ST;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];
}RRWRRC_CELL_RESEL_STOP_CNF_ST;
typedef struct
{
    VOS_UINT16                              usArfcn;                            /* Ƶ����Ϣ [0��16383] */
    PS_BOOL_ENUM_UINT8                      enDetectedCellMeasInd;              /* �Ƿ���Ҫ����DetectedС�� */
    VOS_UINT8                               aucReserve1[3];
    VOS_UINT16                              usCellNum;                          /* һ��Ƶ���µ�С����Ŀ,[1��32] */
    VOS_UINT16                              ausPrimaryScramCode[WRRC_RR_MAX_UTRAN_CELL_PER_FREQ_NUM];
} RRWRRC_WCELL_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : WRRC_UTRAN_CELL_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UTRAN��ϵͳ��Ϣ�б�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqNum;                              /* �������WCDMAƵ����Ŀ��[0��3] */
    VOS_UINT8                           aucRsv[2];
    RRWRRC_WCELL_INFO_LIST_STRU         astFreqInfo[WRRC_RR_MAX_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM];
}RRWRRC_UTRAN_CELL_INFO_LIST_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    RRC_RR_MEAS_CMD_ENUM_UINT8          enMeasCmd;
    RRC_RR_MEAS_GAS_STATUS_ENUM_UINT8   enGasStatus;                        /* G��ģ�Ƿ��ǿ���״̬�ı�� */
    RRWRRC_UTRAN_CELL_INFO_LIST_STRU    stUtranCellInfoLst;
}RRWRRC_SLAVE_MEAS_REQ_STRU;

/*****************************************************************************
 ö����    : RR_WRRC_MEAS_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : G2W��ģ�������ý��
*****************************************************************************/
enum RR_WRRC_MEAS_RESULT_ENUM
{
    RR_WRRC_MEAS_RESULT_SUCC                             = 0,
    RR_WRRC_MEAS_RESULT_FAIL                                ,
    RR_WRRC_MEAS_RESULT_BUTT
};
typedef VOS_UINT32  RR_WRRC_MEAS_RESULT_ENUM_UINT32;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve1[2];
    RR_WRRC_MEAS_RESULT_ENUM_UINT32     enResult;
}RRWRRC_SLAVE_MEAS_CNF_STRU;
typedef struct
{
    VOS_UINT16                                              usPrimaryCode;
    VOS_UINT8                                               aucReserved[2];
    VOS_INT16                                               sRscp;              /* ����1/8 */
    VOS_INT16                                               sEcN0;              /* ����1/8 */
}RRWRRC_WCELL_MEAS_RESULT_STRU;


typedef struct
{
    VOS_UINT16                                              usArfcn;
    VOS_INT16                                               sRssi;              /* ����1/8 */
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT16                                              usCellNum;
    RRWRRC_WCELL_MEAS_RESULT_STRU                           astUtranCellInfo[WRRC_RR_MAX_UTRAN_CELL_PER_FREQ_NUM];
} RRWRRC_WCELL_FREQ_MEAS_RESULT_STRU;
typedef struct
{
    VOS_UINT16                          usFreqNum;
    RRWRRC_WCELL_FREQ_MEAS_RESULT_STRU  astFreqMeasResult[WRRC_RR_MAX_UTRAN_PHY_MAX_SUPPORT_CARRIER_NUM];
} RRWRRC_SLAVE_MEAS_RESULT_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    RRWRRC_SLAVE_MEAS_RESULT_STRU       stMeasResult;
}RRWRRC_SLAVE_MEAS_IND_STRU;

/*****************************************************************************
 �ṹ��    : WRRCRR_GSM_CELL_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM С����Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCellID;                               /* С����ID */
    VOS_UINT8                           aucReserve1[1];
    VOS_UINT16                          usBcchArfcn;                            /*GSM����Ƶ��*/
    RRC_GSM_BAND_INDICATOR_ENUM_UINT32  enFreqBandInd;                          /*Ƶ��ָʾ*/
}WRRCRR_GCELL_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : WRRCRR_GSM_CELL_INFO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GSM С����Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCellNum;                              /*��Ҫ������С������*/
    VOS_UINT8                           aucReserve1[2];
    WRRCRR_GCELL_INFO_LIST_STRU         astGSMCellInfo[WRRC_RR_MAX_SLAVE_GSM_CELL_NUM];
}WRRCRR_GSM_CELL_INFO_LIST_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    RRC_RR_WAS_STATUS_ENUM_UINT8        enWasStatus;
    RRC_RR_MEAS_CMD_ENUM_UINT8          enMeasCmd;
    WRRCRR_GSM_CELL_INFO_LIST_STRU      stGsmCellInfoLst;
}WRRCRR_SLAVE_MEAS_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve1[2];
    RR_WRRC_MEAS_RESULT_ENUM_UINT32     enResult;
}WRRCRR_SLAVE_MEAS_CNF_STRU;

/*****************************************************************************
 �ṹ��    : WRRCRR_SLAVE_GCELL_MEAS_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ÿ��GSMС���������
 *****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCellID;                               /* С����ID */
    VOS_UINT8                           aucReserve1[3];
    VOS_INT16                           sCarrierRSSI;                           /* GSM���ز�ǿ�� */
    VOS_UINT16                          usBcchArfcn;                            /* GSM�ľ�����Ƶ�� */
    RRC_GSM_BAND_INDICATOR_ENUM_UINT32  enFreqBandInd;                          /* GSM��Ƶ��ָʾ */
} WRRCRR_SLAVE_GCELL_MEAS_RESULT_STRU;


typedef struct
{
    VOS_UINT16                            usGsmCellNum;      /*���������õ�GSM�ز�������*/
    VOS_UINT8                             aucReserve1[2];
    WRRCRR_SLAVE_GCELL_MEAS_RESULT_STRU   astGsmCellResult[WRRC_RR_MAX_SLAVE_GSM_CELL_NUM];   /*GSMС���Ĳ������*/
}WRRCRR_SLAVE_GCELL_MEAS_RESULT_LIST_STRU;


typedef struct
{
    MSG_HEADER_STRU                            MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT16                                 usOpId;
    VOS_UINT8                                  aucReserve1[2];
    WRRCRR_SLAVE_GCELL_MEAS_RESULT_LIST_STRU   stGsmCellResultList;             /*GSMС���Ĳ������*/
}WRRCRR_SLAVE_MEAS_IND_STRU;

/*****************************************************************************
 �ṹ��    : WRRCRR_GSM_CARRIER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BSIC Verify �����е�GSMС������Ƶ��Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCellID;                               /* С����ID */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT16                          usBcchArfcn;
    RRC_BSIC_INFO_ST                    stInitBsicInfo;                         /* ��ʼ��BSIC��Ϣ */
    RRC_GSM_BAND_INDICATOR_ENUM_UINT32  enFreqBandInd;
}WRRCRR_GSM_CARRIER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_DRX_BSIC_TIMER_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DRX״̬(IDLE̬����PCH̬)GPHY����BSIC��֤�ʱ��Ĳ���
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPeriodT;
    VOS_UINT8                           ucReserve1[2];
}RRC_RR_DRX_BSIC_TIMER_PARA_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_FACH_BSIC_TIMER_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : FACH״̬GPHY����BSIC��֤�ʱ��Ĳ���
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usMREP;                         /* [2��4096] frame FACHOccasion���� */
    VOS_UINT16                                  usNTTI;                         /* Sccpch�����TTI����,{1,2,4,8}frame */
    PS_BOOL_ENUM_UINT8                          enInterFreqMeasExistFlag;       /* ��Ƶ�����Ƿ���ڵı�� */
    VOS_UINT8                                   ucReserve1[3];
}RRC_RR_FACH_BSIC_TIMER_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RR_DCH_BSIC_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCH״̬GPHY����BSIC��֤�ʱ��Ĳ���
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTGL1;                                 /* ��һ��Transmission Gap�ĳ��Ȱ���TGP�Ͽ�ʱ*/
    VOS_UINT16                          usTGL2;                                 /* �ڶ���Transmission Gap�ĳ��Ȱ���TGP PATTERN*/
    VOS_UINT16                          usTGD;                                   /* Transmission gap distance                */
    VOS_UINT16                          usTGPL1;                                /* TGP1�ĳ���                               */
}RRC_RR_DCH_BSIC_PARA_STRU;

/*****************************************************************************
 �ṹ��    : PHYITF_DCH_BSIC_TIMER_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCH״̬GPHY����BSIC��֤�ʱ��Ĳ���
 *****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                 enReConfirmParaValidFlag;                /* ��ȷ��ѹģ�����Ƿ���ڵı�� */
    VOS_UINT8                          ucReserve1[3];
    RRC_RR_DCH_BSIC_PARA_STRU          stInitBsicTimerPara;                     /* D̬��ʼȷ��GPHY����BSIC��֤�ʱ��Ĳ��� */ 
    RRC_RR_DCH_BSIC_PARA_STRU          stReConfirmBsicTimerPara;                /* D̬��ȷ��GPHY����BSIC��֤�ʱ��Ĳ��� */ 
}RRC_RR_DCH_BSIC_TIMER_PARA_STRU;
typedef struct
{
    MSG_HEADER_STRU                         MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                               ucReserve1[2];
    VOS_UINT16                              usGsmCarrierNum;
    WRRCRR_GSM_CARRIER_INFO_STRU            astGSMCarrierInfo[WRRC_RR_MAX_SLAVE_GSM_BSIC_RPT_CELL_NUM];
    RRC_RR_WAS_STATUS_ENUM_UINT8            enWasStatus;                        /* _H2ASN_IeChoice_Export RRC_RR_WAS_STATUS_ENUM_UINT8 */
    VOS_UINT8                               ucReserve2[3];
    union                                                                       /*_H2ASN_Skip*/
    {                                                                           /*_H2ASN_Skip*/
        RRC_RR_DRX_BSIC_TIMER_PARA_STRU          stDrxBsicTimerPara;            /*_H2ASN_Skip*//* DRX״̬(IDLE̬����PCH̬)GPHY����BSIC��֤�ʱ��Ĳ��� */ 
        RRC_RR_FACH_BSIC_TIMER_PARA_STRU         stFachBsicTimerPara;           /*_H2ASN_Skip*//* FACH״̬GPHY����BSIC��֤�ʱ��Ĳ��� */ 
        RRC_RR_DCH_BSIC_TIMER_PARA_STRU          stDchBsicTimerPara;            /* DCH״̬GPHY����BSIC��֤�ʱ��Ĳ��� */ 
        /******************************************************************************************************
            _H2ASN_IeChoice_When        RRC_RR_WAS_STATUS_ENUM_UINT8
        ******************************************************************************************************/
    } u;                                                                        /*_H2ASN_Skip*/
}WRRCRR_BSIC_VERIFIED_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];
}WRRCRR_BSIC_VERIFIED_CNF_STRU;

/*****************************************************************************
 �ṹ��    : WRRCRR_BSIC_VERIFIED_RESULT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BSIC Verify ָʾ�е�GSM��Ƶ�������
 *****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCellID;                               /* С����ID */
    VOS_UINT8                           aucReserve1[1];
    VOS_UINT16                          usBcchArfcn;
    RRC_GSM_BAND_INDICATOR_ENUM_UINT32  enFreqBandInd;
    RRC_BSIC_INFO_ST                    stBsic;
    VOS_UINT8                           aucReserve2[2];
    VOS_UINT16                          usObservedTimeDiffToGSMCell;            /* ����Ƿ���Ҫliuyin */
    VOS_UINT16                          usTimeAlignmt;
    VOS_INT32                           lFNOffset;
} WRRCRR_BSIC_VERIFIED_RESULT_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT16                          usGsmCarrierNum;
    VOS_UINT8                           aucReserve1[2];
    WRRCRR_BSIC_VERIFIED_RESULT_STRU    astGSMCarrierResult[WRRC_RR_MAX_SLAVE_GSM_BSIC_RPT_CELL_NUM];
}WRRCRR_BSIC_VERIFIED_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    RRC_RR_REL_REASON_ENUM_UINT8        enRelReason;                            /* �ͷ�ԭ�� */ 
    VOS_UINT8                           aucReserve1[3];
}WRRCRR_RELEASE_ALL_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[4];
}WRRCRR_RELEASE_ALL_CNF_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    RR_WRRC_MSG_TYPE_ENUM_UINT16        enMsgID;    /*_H2ASN_MsgChoice_Export RR_WRRC_MSG_TYPE_ENUM_UINT32*/
                                                    /* Ϊ�˼���GAS����Ϣͷ���壬����ת��ASN.1ʹ��GAS_RRC_MSG_TYPE_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RR_WRRC_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}RR_WRRC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    RR_WRRC_MSG_DATA                    stMsgData;
}GasRrWrr_MSG;

#define RRWRR_INVALID_SCRAMBLING_CODE            0xFFFF
/*****************************************************************************
  10 ��������
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

#endif /* end of GasRrWrr.h*/
