/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafSmInterface.h
  �� �� ��   : ����
  ��    ��   : A00165503/L47619
  ��������   : 2013��04��23��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��04��23��
    ��    ��   : A00165503/L47619
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __TAF_SM_INTERFACE_H__
#define __TAF_SM_INTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define SM_TAF_MAX_PDP_ADDR_LEN             (20)            /* IPV4V6��󳤶� */
#define SM_TAF_MAX_QOS_LEN                  (16)            /* QOS��󳤶� */
#define SM_TAF_MAX_APN_LEN                  (100)           /* �����APN��ַ��󳤶� */
#define SM_TAF_MAX_TFT_LEN                  (255)           /* TFT��󳤶� */
#define SM_TAF_MAX_PCO_LEN                  (251)           /* PCO��󳤶� */

#define SM_TAF_CAUSE_SM_SECTION_BEGIN       (0x0000)
#define SM_TAF_CAUSE_SM_NW_SECTION_BEGIN    (0x0100)
#define SM_TAF_CAUSE_GMM_SECTION_BEGIN      (0x0200)
#define SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN   (0x0300)

#define SM_TAF_SM_NW_CAUSE_OFFSET           SM_TAF_CAUSE_SM_NW_SECTION_BEGIN

#define TAF_SM_MSG_ID_HEADER                (0x0000)
#define SM_TAF_MSG_ID_HEADER                (0x1000)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 �ṹ����: SM_TAF_MSG_ID_ENUM
 �ṹ˵��: TAF(APS)��SM֮���ԭ��
*****************************************************************************/
enum SM_TAF_MSG_ID_ENUM
{
    /*------------------------------------------------------------------
                        APS--->SM
    *-----------------------------------------------------------------*/
    ID_SMREG_PDP_ACTIVATE_REQ           = TAF_SM_MSG_ID_HEADER + 0x0001,        /* _H2ASN_MsgChoice SMREG_PDP_ACTIVATE_REQ_STRU */
    ID_SMREG_PDP_ACTIVATE_SEC_REQ       = TAF_SM_MSG_ID_HEADER + 0x0002,        /* _H2ASN_MsgChoice SMREG_PDP_ACTIVATE_SEC_REQ_STRU */
    ID_SMREG_PDP_ACTIVATE_REJ_RSP       = TAF_SM_MSG_ID_HEADER + 0x0003,        /* _H2ASN_MsgChoice SMREG_PDP_ACTIVATE_REJ_RSP_STRU */
    ID_SMREG_PDP_DEACTIVATE_REQ         = TAF_SM_MSG_ID_HEADER + 0x0004,        /* _H2ASN_MsgChoice SMREG_PDP_DEACTIVATE_REQ_STRU */
    ID_SMREG_PDP_MODIFY_REQ             = TAF_SM_MSG_ID_HEADER + 0x0005,        /* _H2ASN_MsgChoice SMREG_PDP_MODIFY_REQ_STRU */
    ID_SMREG_PDP_MODIFY_RSP             = TAF_SM_MSG_ID_HEADER + 0x0006,        /* _H2ASN_MsgChoice SMREG_PDP_MODIFY_RSP_STRU */
    ID_SMREG_PDP_MODIFY_REJ_RSP         = TAF_SM_MSG_ID_HEADER + 0x0007,        /* _H2ASN_MsgChoice SMREG_PDP_MODIFY_REJ_RSP_STRU */


    ID_SMREG_PDP_ABORT_REQ              = TAF_SM_MSG_ID_HEADER + 0x0100,        /* _H2ASN_MsgChoice SMREG_PDP_ABORT_REQ_STRU */
    ID_SMREG_PDP_LOCAL_DEACTIVATE_REQ   = TAF_SM_MSG_ID_HEADER + 0x0101,        /* _H2ASN_MsgChoice SMREG_PDP_LOCAL_DEACTIVATE_REQ_STRU */

    /*------------------------------------------------------
                        ��ģ���������ԭ��
    *-----------------------------------------------------*/
#if (FEATURE_ON == FEATURE_LTE)
    ID_SMREG_BEARER_ACTIVATE_IND        = TAF_SM_MSG_ID_HEADER + 0x0102,        /* _H2ASN_MsgChoice SMREG_BEARER_ACTIVATE_IND_STRU */
    ID_SMREG_BEARER_MODIFY_IND          = TAF_SM_MSG_ID_HEADER + 0x0103,        /* _H2ASN_MsgChoice SMREG_BEARER_MODIFY_IND_STRU */
    ID_SMREG_BEARER_DEACTIVATE_IND      = TAF_SM_MSG_ID_HEADER + 0x0104,        /* _H2ASN_MsgChoice SMREG_BEARER_DEACTIVATE_IND_STRU */
#endif
    /*------------------------------------------------------------------
                        SM--->APS
    *-----------------------------------------------------------------*/
    ID_SMREG_PDP_ACTIVATE_CNF           = SM_TAF_MSG_ID_HEADER + 0x0001,        /* _H2ASN_MsgChoice SMREG_PDP_ACTIVATE_CNF_STRU */
    ID_SMREG_PDP_ACTIVATE_REJ           = SM_TAF_MSG_ID_HEADER + 0x0002,        /* _H2ASN_MsgChoice SMREG_PDP_ACTIVATE_REJ_STRU */
    ID_SMREG_PDP_ACTIVATE_SEC_CNF       = SM_TAF_MSG_ID_HEADER + 0x0003,        /* _H2ASN_MsgChoice SMREG_PDP_ACTIVATE_SEC_CNF_STRU */
    ID_SMREG_PDP_ACTIVATE_SEC_REJ       = SM_TAF_MSG_ID_HEADER + 0x0004,        /* _H2ASN_MsgChoice SMREG_PDP_ACTIVATE_SEC_REJ_STRU */
    ID_SMREG_PDP_ACTIVATE_IND           = SM_TAF_MSG_ID_HEADER + 0x0005,        /* _H2ASN_MsgChoice SMREG_PDP_ACTIVATE_IND_STRU */
    ID_SMREG_PDP_DEACTIVATE_CNF         = SM_TAF_MSG_ID_HEADER + 0x0006,        /* _H2ASN_MsgChoice SMREG_PDP_DEACTIVATE_CNF_STRU */
    ID_SMREG_PDP_DEACTIVATE_IND         = SM_TAF_MSG_ID_HEADER + 0x0007,        /* _H2ASN_MsgChoice SMREG_PDP_DEACTIVATE_IND_STRU */
    ID_SMREG_PDP_MODIFY_CNF             = SM_TAF_MSG_ID_HEADER + 0x0008,        /* _H2ASN_MsgChoice SMREG_PDP_MODIFY_CNF_STRU */
    ID_SMREG_PDP_MODIFY_REJ             = SM_TAF_MSG_ID_HEADER + 0x0009,        /* _H2ASN_MsgChoice SMREG_PDP_MODIFY_REJ_STRU */
    ID_SMREG_PDP_MODIFY_IND             = SM_TAF_MSG_ID_HEADER + 0x000A,        /* _H2ASN_MsgChoice SMREG_PDP_MODIFY_IND_STRU */

    ID_SMREG_PDP_ABORT_CNF              = SM_TAF_MSG_ID_HEADER + 0x0100,        /* _H2ASN_MsgChoice SMREG_PDP_ABORT_CNF_STRU */


    ID_SMREG_MSG_ID_BUTT
};
typedef VOS_UINT32 SM_TAF_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 �ṹ����: PCP_TA_CAUSE_ENUM
 �ṹ˵��:
*****************************************************************************/
enum PCP_TA_CAUSE_ENUM
{
    EN_PTC_PDP_ADD_INCOMPATIBLE = 0,
    EN_PTC_APN_INCOMPATIBLE,
    EN_PTC_QOS_INCOMPATIBLE,
    EN_PTC_CALL_REJ,
    EN_PTC_CONN,
    EN_PTC_NORMAL,
    EN_PTC_NOT_SUPPT,
    EN_PTC_TE_NOT_CONN,
    EN_PTC_PCP_TIMEOUT,
    EN_PTC_MSG_ERR,
    EN_PTC_IE_ERR,
    EN_PTC_OTHER_REASON,
    EN_PTC_OPERATOR_MATTER1,
    EN_PTC_OPERATOR_MATTER2
    /* ... */
};
typedef VOS_UINT8  PCP_TA_CAUSE_ENUM_UINT8;

/*****************************************************************************
 ö����  : SM_TAF_CAUSE_ENUM
 ö��˵��: SM�ϱ���ԭ��ֵ

 �޸���ʷ      :
  1.��    ��   : 2012��8��22��
    ��    ��   : A00165503
    �޸�����   : ����ö��
  2.��    ��   : 2013��4��23��
    ��    ��   : L47619
    �޸�����   : V9R1 IPv6&TAF/SM�ӿ��Ż���Ŀ�޸�
*****************************************************************************/
enum SM_TAF_CAUSE_ENUM
{
    /*----------------------------------------------------------------------
       SM���ڲ�ԭ��ֵ, ȡֵ��Χ[0x0000, 0x00FF]
       ����: SM -> APS
       ˵��: UNKNOWNΪ������ֶε����һ��������
    *---------------------------------------------------------------------*/
    SM_TAF_CAUSE_SM_CONN_ESTABLISH_MAX_TIME_OUT             = (SM_TAF_CAUSE_SM_SECTION_BEGIN + 1),
    SM_TAF_CAUSE_SM_MAX_TIME_OUT                            = (SM_TAF_CAUSE_SM_SECTION_BEGIN + 2),
    SM_TAF_CAUSE_SM_INVALID_NSAPI                           = (SM_TAF_CAUSE_SM_SECTION_BEGIN + 3),
    SM_TAF_CAUSE_SM_MODIFY_COLLISION                        = (SM_TAF_CAUSE_SM_SECTION_BEGIN + 4),
    SM_TAF_CAUSE_SM_DUPLICATE                               = (SM_TAF_CAUSE_SM_SECTION_BEGIN + 5),
    SM_TAF_CAUSE_SM_RAB_SETUP_FAIL                          = (SM_TAF_CAUSE_SM_SECTION_BEGIN + 6),
    SM_TAF_CAUSE_SM_SGSN_VER_PRE_R99                        = (SM_TAF_CAUSE_SM_SECTION_BEGIN + 7),
    SM_TAF_CAUSE_SM_UNKNOWN                                 = (SM_TAF_CAUSE_SM_SECTION_BEGIN + 255),

    /*----------------------------------------------------------------------
       SM������ԭ��ֵ, ȡֵ��Χ[0x0100, 0x01FF]
       ����: SM <-> APS
       ����3GPPЭ���Ѿ������˾����SM����ԭ��ֵ, SM�ϱ���ȡֵΪЭ�鶨���
       ԭ��ֵ����ƫ����(0x100),
       SM Cause: Refer to TS 24.008 section 10.5.6.6
    *---------------------------------------------------------------------*/
    SM_TAF_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING          = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 8),
    SM_TAF_CAUSE_SM_NW_MBMS_BC_INSUFFICIENT                 = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 24),
    SM_TAF_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE                 = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 25),
    SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES               = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 26),
    SM_TAF_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN                = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 27),
    SM_TAF_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE             = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 28),
    SM_TAF_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL             = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 29),
    SM_TAF_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN_SGW_OR_PGW = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 30),
    SM_TAF_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED      = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 31),
    SM_TAF_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED         = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 32),
    SM_TAF_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED     = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 33),
    SM_TAF_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER        = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 34),
    SM_TAF_CAUSE_SM_NW_NSAPI_ALREADY_USED                   = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 35),
    SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION                 = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 36),
    SM_TAF_CAUSE_SM_NW_QOS_NOT_ACCEPTED                     = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 37),
    SM_TAF_CAUSE_SM_NW_NETWORK_FAILURE                      = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 38),
    SM_TAF_CAUSE_SM_NW_REACTIVATION_REQUESTED               = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 39),
    SM_TAF_CAUSE_SM_NW_FEATURE_NOT_SUPPORT                  = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 40),
    SM_TAF_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT                  = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 41),
    SM_TAF_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT                 = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 42),
    SM_TAF_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT                   = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 43),
    SM_TAF_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER        = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 44),
    SM_TAF_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER      = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 45),
    SM_TAF_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED    = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 46),
    SM_TAF_CAUSE_SM_NW_MULTICAST_GROUP_MEMBERHHSHIP_TIMEOUT = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 47),
    SM_TAF_CAUSE_SM_NW_REQUEST_REJECTED_BCM_VIOLATION       = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 48),
    SM_TAF_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED           = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 50),
    SM_TAF_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED           = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 51),
    SM_TAF_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED     = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 52),
    SM_TAF_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST  = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 56),
    SM_TAF_CAUSE_SM_NW_BEARER_HANDLING_NOT_SUPPORTED        = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 60),
    SM_TAF_CAUSE_SM_NW_INVALID_TI                           = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 81),
    SM_TAF_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE       = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 95),
    SM_TAF_CAUSE_SM_NW_INVALID_MANDATORY_INFO               = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 96),
    SM_TAF_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT                = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 97),
    SM_TAF_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE              = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 98),
    SM_TAF_CAUSE_SM_NW_IE_NON_EXISTENT                      = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 99),
    SM_TAF_CAUSE_SM_NW_CONDITIONAL_IE_ERR                   = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 100),
    SM_TAF_CAUSE_SM_NW_MSG_NOT_COMPATIBLE                   = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 101),
    SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED             = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 111),
    SM_TAF_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE         = (SM_TAF_CAUSE_SM_NW_SECTION_BEGIN + 112),

    /*----------------------------------------------------------------------
       GMM���ڲ�ԭ��ֵ, ȡֵ��Χ[0x0200, 0x02FF]
       ����: GMM -> SM -> APS
       ˵��: UNKNOWNΪ������ֶε����һ��������
    *---------------------------------------------------------------------*/
    SM_TAF_CAUSE_GMM_GPRS_NOT_SUPPORT                       = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 1),
    SM_TAF_CAUSE_GMM_ATTACH_MAX_TIMES                       = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 2),
    SM_TAF_CAUSE_GMM_FORBID_LA                              = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 3),
    SM_TAF_CAUSE_GMM_AUTHENTICATION_FAIL                    = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 4),
    SM_TAF_CAUSE_GMM_AUTHENTICATION_REJ                     = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 5),
    SM_TAF_CAUSE_GMM_PS_DETACH                              = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 6),
    SM_TAF_CAUSE_GMM_RRC_EST_FAIL                           = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 7),
    SM_TAF_CAUSE_GMM_ACCESS_BARRED                          = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 8),
    SM_TAF_CAUSE_GMM_SIM_PS_DOMAIN_REG_INVALID              = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 9),
    SM_TAF_CAUSE_GMM_T3310_EXPIRED                          = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 10),
    SM_TAF_CAUSE_GMM_T3317_EXPIRED                          = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 11),
    SM_TAF_CAUSE_GMM_TIMER_SIGNALING_PROTECT_EXPIRED        = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 12),
    SM_TAF_CAUSE_GMM_STARTUP                                = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 13),
    SM_TAF_CAUSE_GMM_NULL                                   = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 14),
    SM_TAF_CAUSE_GMM_RESET                                  = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 15),
    SM_TAF_CAUSE_GMM_RAU_ACCEPT                             = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 16),
    SM_TAF_CAUSE_GMM_SERVICE_ACCEPT                         = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 17),
    SM_TAF_CAUSE_GMM_UNKNOWN                                = (SM_TAF_CAUSE_GMM_SECTION_BEGIN + 255),

    /*----------------------------------------------------------------------
       GMM������ԭ��ֵ, ȡֵ��Χ[0x0300, 0x03FF]
       ����: GMM -> SM -> APS
       ����3GPPЭ���Ѿ������˾����GMM����ԭ��ֵ, GMM�ϱ���ȡֵΪЭ�鶨��
       ��ԭ��ֵ����ƫ����(0x300)
       GMM Cause ��� TS 24.008 section 10.5.5.14
    *---------------------------------------------------------------------*/
    SM_TAF_CAUSE_GMM_NW_IMSI_UNKNOWN_IN_HLR                 = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 2),
    SM_TAF_CAUSE_GMM_NW_ILLEGAL_MS                          = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 3),
    SM_TAF_CAUSE_GMM_NW_IMSI_NOT_ACCEPTED                   = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 5),
    SM_TAF_CAUSE_GMM_NW_ILLEGAL_ME                          = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 6),
    SM_TAF_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW                 = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 7),
    SM_TAF_CAUSE_GMM_NW_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 8),
    SM_TAF_CAUSE_GMM_NW_MS_ID_NOT_DERIVED                   = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 9),
    SM_TAF_CAUSE_GMM_NW_IMPLICIT_DETACHED                   = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 10),
    SM_TAF_CAUSE_GMM_NW_PLMN_NOT_ALLOW                      = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 11),
    SM_TAF_CAUSE_GMM_NW_LA_NOT_ALLOW                        = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 12),
    SM_TAF_CAUSE_GMM_NW_ROAMING_NOT_ALLOW_IN_LA             = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 13),
    SM_TAF_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW_IN_PLMN         = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 14),
    SM_TAF_CAUSE_GMM_NW_NO_SUITABL_CELL                     = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 15),
    SM_TAF_CAUSE_GMM_NW_MSC_UNREACHABLE                     = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 16),
    SM_TAF_CAUSE_GMM_NW_NETWORK_FAILURE                     = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 17),
    SM_TAF_CAUSE_GMM_NW_MAC_FAILURE                         = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 20),
    SM_TAF_CAUSE_GMM_NW_SYNCH_FAILURE                       = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 21),
    SM_TAF_CAUSE_GMM_NW_PROCEDURE_CONGESTION                = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 22),
    SM_TAF_CAUSE_GMM_NW_GSM_AUT_UNACCEPTABLE                = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 23),
    SM_TAF_CAUSE_GMM_NW_NOT_AUTHORIZED_FOR_THIS_CSG         = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 25),
    SM_TAF_CAUSE_GMM_NW_NO_PDP_CONTEXT_ACT                  = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 40),
    SM_TAF_CAUSE_GMM_NW_RETRY_UPON_ENTRY_CELL               = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 60),
    SM_TAF_CAUSE_GMM_NW_SEMANTICALLY_INCORRECT_MSG          = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 95),
    SM_TAF_CAUSE_GMM_NW_INVALID_MANDATORY_INF               = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 96),
    SM_TAF_CAUSE_GMM_NW_MSG_NONEXIST_NOTIMPLEMENTE          = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 97),
    SM_TAF_CAUSE_GMM_NW_MSG_TYPE_NOT_COMPATIBLE             = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 98),
    SM_TAF_CAUSE_GMM_NW_IE_NONEXIST_NOTIMPLEMENTED          = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 99),
    SM_TAF_CAUSE_GMM_NW_CONDITIONAL_IE_ERROR                = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 100),
    SM_TAF_CAUSE_GMM_NW_MSG_NOT_COMPATIBLE                  = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 101),
    SM_TAF_CAUSE_GMM_NW_PROTOCOL_ERROR                      = (SM_TAF_CAUSE_GMM_NW_SECTION_BEGIN + 111),

    SM_TAF_CAUSE_BUTT                                       = 0xFFFF
};
typedef VOS_UINT16 SM_TAF_CAUSE_ENUM_UINT16;


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
 �ṹ��    : SM_TAF_PROT_CFG_OPT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDP PCO�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPcoLen;
    VOS_UINT8                           aucProtCfgOpt[SM_TAF_MAX_PCO_LEN];
    VOS_UINT8                           aucReserved[1];

} SM_TAF_PROT_CFG_OPT_STRU;

/*****************************************************************************
 �ṹ��    : SM_TAF_TFT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDP TFT�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTftLen;
    VOS_UINT8                           aucNewtft[SM_TAF_MAX_TFT_LEN];
    VOS_UINT8                           aucReserved[1];

} SM_TAF_TFT_STRU;

/*****************************************************************************
 �ṹ��    : SM_TAF_PACKET_FLOW_ID_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDP PACKET FLOW ID�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPFILen;
    VOS_UINT8                           ucPacketFlowId;
    VOS_UINT8                           aucReserved[3];

} SM_TAF_PACKET_FLOW_ID_STRU;

/*****************************************************************************
 �ṹ��    : SM_TAF_PDP_ADDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDP ADDRESS�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPdpAddrLen;
    VOS_UINT8                           aucPdpAddr[SM_TAF_MAX_PDP_ADDR_LEN + 2];
    VOS_UINT8                           aucReserved[2];     /* ���ֽڶ��� */

} SM_TAF_PDP_ADDR_STRU;

/*****************************************************************************
 �ṹ��    : SM_TAF_APN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : APN�ṹ, ��TS 24.008 section 10.5.6.1 APNΪЭ���ʽ(�����APN)
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulApnLen;
    VOS_UINT8                           aucApnAddr[SM_TAF_MAX_APN_LEN];

} SM_TAF_APN_STRU;

/*****************************************************************************
 �ṹ��    : SM_TAF_QOS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : QOS�ṹ, ��TS 24.008 section 10.5.6.5 QOSΪ�����ֽ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulQosLen;
    /* Ϊ�˿��Ǽ����ԣ�Qos���鳤�ȶ�Ϊ16(R7)�������������ְ汾�ķ�ʽ���� */
    VOS_UINT8                           aucQos[SM_TAF_MAX_QOS_LEN];

} SM_TAF_QOS_STRU;


/*****************************************************************************
 �ṹ��    : SM_TAF_TRANS_ID_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTiFlag;
    VOS_UINT8                           ucTiValue;
    VOS_UINT8                           aucReserved[2];      /* ���ֽڶ��� */

} SM_TAF_TRANS_ID_STRU;


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �ṹ��   : SMREG_BEARER_ACTIVATE_IND_STRU
 �ṹ˵�� : ԭ��ID_MN_SM_BEARER_ACTIVATE_IND�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ         *//* _H2ASN_Skip */

    VOS_UINT32                          bitOpLinkedNsapi    : 1;
    VOS_UINT32                          bitOpRadioPriority  : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpPdpQos         : 1;
    VOS_UINT32                          bitOpSpare          : 28;

    SM_TAF_TRANS_ID_STRU                stTransId;          /* TI             */
    VOS_UINT8                           ucConnectId;        /* PDP INDEX      */
    VOS_UINT8                           ucNsapi;            /* NSAPI          */
    VOS_UINT8                           ucLinkedNsapi;      /* LINKED NAAPI   */
    VOS_UINT8                           ucRadioPriority;    /* RADIO PRIORITY */

    SM_TAF_PDP_ADDR_STRU                stPdpAddr;          /* PDP ADDRESS    */
    SM_TAF_APN_STRU                     stApn;              /* PDP APN        */
    SM_TAF_QOS_STRU                     stNegQos;           /* PDP QOS        */

} SMREG_BEARER_ACTIVATE_IND_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_BEARER_MODIFY_IND_STRU
 �ṹ˵�� : ԭ��ID_MN_SM_BEARER_MODIFY_IND�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ         *//* _H2ASN_Skip */

    VOS_UINT32                          bitOpRadioPriority  : 1;
    VOS_UINT32                          bitOpPdpQos         : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    SM_TAF_TRANS_ID_STRU                stTransId;          /* TI             */
    VOS_UINT8                           ucConnectId;        /* PDP INDEX      */
    VOS_UINT8                           ucRadioPriority;    /* RADIO PRIORITY */
    VOS_UINT8                           aucReserved[2];     /* ���ֽڶ���     */

    SM_TAF_PDP_ADDR_STRU                stPdpAddr;          /* PDP ADDRESS    */
    SM_TAF_QOS_STRU                     stNegQos;           /* PDP QOS        */

} SMREG_BEARER_MODIFY_IND_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_BEARER_DEACTIVATE_IND_STRU
 �ṹ˵�� : ԭ��ID_MN_SM_BEARER_DEACTIVATE_IND�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ     */    /* _H2ASN_Skip */

    SM_TAF_TRANS_ID_STRU                stTransId;          /* TI         */
    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           aucReserved[3];     /* ���ֽڶ��� */
} SMREG_BEARER_DEACTIVATE_IND_STRU;
#endif

/*****************************************************************************
 �ṹ��   : SMREG_PDP_ABORT_REQ_STRU
 �ṹ˵�� : ԭ��ID_APS_SM_PDP_ABORT_REQ�Ľṹ��
  1.��    ��   : 2011��12��20��
    ��    ��   : A00165503
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ     */    /* _H2ASN_Skip */

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           aucReserved[3];     /* ���ֽڶ��� */

} SMREG_PDP_ABORT_REQ_STRU;

/*****************************************************************************
 �ṹ��   : SMREG_PDP_ABORT_CNF_STRU
 �ṹ˵�� : ԭ��ID_APS_SM_PDP_ABORT_CNF�Ľṹ��
  1.��    ��   : 2011��12��20��
    ��    ��   : A00165503
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ     */    /* _H2ASN_Skip */

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           aucReserved[3];     /* ���ֽڶ��� */
} SMREG_PDP_ABORT_CNF_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_LOCAL_DEACTIVATE_REQ_STRU
 �ṹ˵�� : ԭ��ID_APS_SM_PDP_LOCAL_DEACTIVATE_REQ�Ľṹ��
  1.��    ��   : 2011��12��20��
    ��    ��   : A00165503
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ     */    /* _H2ASN_Skip */

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           aucReserved[3];     /* ���ֽڶ��� */

} SMREG_PDP_LOCAL_DEACTIVATE_REQ_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_ACTIVATE_REQ_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpAcsPointName   : 1;
    VOS_UINT32                          bitOpProtCfgOpt     : 1;
    VOS_UINT32                          bitOpSapi           : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           aucReserved[2];     /* ���ֽڶ��� */
    SM_TAF_QOS_STRU                     stReqQos;
    SM_TAF_PDP_ADDR_STRU                stReqPdpAddr;
    SM_TAF_APN_STRU                     stAcsPointName;
    SM_TAF_PROT_CFG_OPT_STRU            stProtCfgOpt;

} SMREG_PDP_ACTIVATE_REQ_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_ACTIVATE_CNF_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpPdpAddr        : 1;
    VOS_UINT32                          bitOpProtCfgOpt     : 1;
    VOS_UINT32                          bitOpPacketFlowId   : 1;
    VOS_UINT32                          bitOpNsapi          : 1;
    VOS_UINT32                          bitOpSapi           : 1;
    VOS_UINT32                          bitOpRadioPriority  : 1;
#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT32                          bitOpSmCause        : 1;
    VOS_UINT32                          bitOpSpare          : 25;
#else
    VOS_UINT32                          bitOpSpare          : 26;
#endif

    SM_TAF_TRANS_ID_STRU                stTransId;          /* TI             */
    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;
    SM_TAF_QOS_STRU                     stNegoQos;
    SM_TAF_PDP_ADDR_STRU                stPdpAddr;
    SM_TAF_PROT_CFG_OPT_STRU            stProtCfgOpt;
    SM_TAF_PACKET_FLOW_ID_STRU          stPacketFlowId;
#if (FEATURE_ON == FEATURE_IPV6)
    SM_TAF_CAUSE_ENUM_UINT16            enCause;
    VOS_UINT8                           aucReserved2[2];    /* ���ֽڶ��� */
#endif

} SMREG_PDP_ACTIVATE_CNF_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_ACTIVATE_REJ_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpProtCfgOpt     : 1;
    VOS_UINT32                          bitOpNsapi          : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucExpiredCount;
    SM_TAF_CAUSE_ENUM_UINT16            enCause;
    SM_TAF_PROT_CFG_OPT_STRU            stProtCfgOpt;
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           aucReserved[3];

} SMREG_PDP_ACTIVATE_REJ_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_ACTIVATE_IND_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpAcsPointName   : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    SM_TAF_TRANS_ID_STRU                stTransId;          /* TI             */
    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           aucReserved[3];     /* ���ֽڶ��� */
    SM_TAF_PDP_ADDR_STRU                stOfferPdpAddr;
    SM_TAF_APN_STRU                     stAcsPointName;

} SMREG_PDP_ACTIVATE_IND_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_ACTIVATE_REJ_RSP_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpPcpTaCause     : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    PCP_TA_CAUSE_ENUM_UINT8             enPcpTaCause;
    SM_TAF_CAUSE_ENUM_UINT16            enCause;

} SMREG_PDP_ACTIVATE_REJ_RSP_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_ACTIVATE_SEC_REQ_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpTft            : 1;

    /* Add SAPI for 2G */
    VOS_UINT32                          bitOpSapi           : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucPrimNsapi;
    VOS_UINT8                           aucReserved[1];     /* ���ֽڶ��� */
    SM_TAF_QOS_STRU                     stRequestedQos;
    SM_TAF_TFT_STRU                     stTft;

} SMREG_PDP_ACTIVATE_SEC_REQ_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_ACTIVATE_SEC_CNF_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpNsapi          : 1;
    VOS_UINT32                          bitOpPacketFlowId   : 1;
    VOS_UINT32                          bitOpSapi           : 1;
    VOS_UINT32                          bitOpRadioPriority  : 1;
    VOS_UINT32                          bitOpSpare          : 28;

    SM_TAF_TRANS_ID_STRU                stTransId;          /* TI             */
    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;
    SM_TAF_QOS_STRU                     stNegotiatedQos;
    SM_TAF_PACKET_FLOW_ID_STRU          stPacketFlowId;

} SMREG_PDP_ACTIVATE_SEC_CNF_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_ACTIVATE_SEC_REJ_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpNsapi          : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucNsapi;
    SM_TAF_CAUSE_ENUM_UINT16            enCause;            /* SM�ϱ�APS SECONDRAY PDP�����ԭ��ֵ */

} SMREG_PDP_ACTIVATE_SEC_REJ_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_DEACTIVATE_REQ_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpTearDownInd    : 1;
    VOS_UINT32                          bitOpNsapi          : 1;
    VOS_UINT32                          bitOpPcpTaCause     : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucNsapi;
    SM_TAF_CAUSE_ENUM_UINT16            enCause;
    VOS_UINT8                           ucTearDownInd;
    PCP_TA_CAUSE_ENUM_UINT8             enPcpTaCause;
    VOS_UINT8                           aucReserved[2];     /* ���ֽڶ��� */

} SMREG_PDP_DEACTIVATE_REQ_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_DEACTIVATE_CNF_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct {
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpNsapi          : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           aucReserved[2];     /* ���ֽڶ��� */

} SMREG_PDP_DEACTIVATE_CNF_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_DEACTIVATE_IND_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct {
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpTearDownInd    : 1;
    VOS_UINT32                          bitOpNsapi          : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucNsapi;
    SM_TAF_CAUSE_ENUM_UINT16            enCause;
    VOS_UINT8                           ucTearDownInd;
    VOS_UINT8                           aucReserved[3];     /* ���ֽڶ��� */

} SMREG_PDP_DEACTIVATE_IND_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_MODIFY_REQ_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpRequestedNewQos: 1;
    VOS_UINT32                          bitOpNsapi          : 1;
    VOS_UINT32                          bitOpNewtft         : 1;
    VOS_UINT32                          bitOpSapi           : 1;
    VOS_UINT32                          bitOpSpare          : 28;

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           aucReserved[1];     /* ���ֽڶ��� */
    SM_TAF_QOS_STRU                     stRequestedNewQos;
    SM_TAF_TFT_STRU                     stNewtft;

} SMREG_PDP_MODIFY_REQ_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_MODIFY_CNF_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpNegotiatedQos  : 1;
    VOS_UINT32                          bitOpPacketFlowId   : 1;
    VOS_UINT32                          bitOpNsapi          : 1;
    VOS_UINT32                          bitOpSapi           : 1;
    VOS_UINT32                          bitOpRadioPriority  : 1;
    VOS_UINT32                          bitOpSpare          : 27;

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;
    SM_TAF_QOS_STRU                     stNegotiatedQos;
    SM_TAF_PACKET_FLOW_ID_STRU          stPacketFlowId;

} SMREG_PDP_MODIFY_CNF_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_MODIFY_REJ_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpNsapi          : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucNsapi;
    SM_TAF_CAUSE_ENUM_UINT16            enCause;

} SMREG_PDP_MODIFY_REJ_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_MODIFY_IND_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct {
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpPdpAddr        : 1;
    VOS_UINT32                          bitOpPacketFlowId   : 1;
    VOS_UINT32                          bitOpNsapi          : 1;
    VOS_UINT32                          bitOpSapi           : 1;
    VOS_UINT32                          bitOpRadioPriority  : 1;
#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT32                          bitOpProtCfgOpt     : 1;
    VOS_UINT32                          bitOpSpare          : 26;
#else
    VOS_UINT32                          bitOpSpare          : 27;
#endif

    SM_TAF_TRANS_ID_STRU                stTransId;          /* TI             */
    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;
    SM_TAF_QOS_STRU                     stNewQos;
    SM_TAF_PDP_ADDR_STRU                stPdpAddr;
    SM_TAF_PACKET_FLOW_ID_STRU          stPacketFlowId;
#if (FEATURE_ON == FEATURE_IPV6)
    SM_TAF_PROT_CFG_OPT_STRU            stProtCfgOpt;
#endif

} SMREG_PDP_MODIFY_IND_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_MODIFY_RSP_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpNsapi          : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           aucReserved[2];     /* ���ֽڶ��� */

} SMREG_PDP_MODIFY_RSP_STRU;


/*****************************************************************************
 �ṹ��   : SMREG_PDP_MODIFY_REJ_RSP_STRU
 �ṹ˵�� :
*****************************************************************************/
typedef struct {
    MSG_HEADER_STRU                     stMsgHdr;           /* ��Ϣͷ */        /* _H2ASN_Skip */

    VOS_UINT32                          bitOpNsapi          : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucConnectId;        /* PDP INDEX  */
    VOS_UINT8                           ucNsapi;
    SM_TAF_CAUSE_ENUM_UINT16            enCause;

} SMREG_PDP_MODIFY_REJ_RSP_STRU;




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
    SM_TAF_MSG_ID_ENUM_UINT32           enMsgId;            /* _H2ASN_MsgChoice_Export SM_TAF_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          SM_TAF_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} SM_TAF_INTERFACE_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    SM_TAF_INTERFACE_MSG_DATA           stMsgData;
} TafSmInterface_MSG;


/*****************************************************************************
  10 ��������
*****************************************************************************/




#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
