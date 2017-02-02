/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : RrcMacInterface.h
  �� �� ��   : ����
  ��    ��   : Jinying
  ��������   : 2006��9��5��
  ����޸�   :
  ��������   : RrcMacInterface.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2006��9��5��
    ��    ��   : Jinying
    �޸�����   : �����ļ�

  2.��    ��   : 2007��12��21��
    ��    ��   : �����塢�¹�
    �޸�����   : �޸�HSUPA�ӿ�

  3.��    ��   : 2009��7��6��
   ��    ��   : ����ɺ���߲ơ�������
   �޸�����   : �޸�HSPA+ MAC-ehs�ӿ�

******************************************************************************/

#ifndef __RRCMACINTERFACE_H__
#define __RRCMACINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
/* WCDMAЭ��ջ������ϵͳ���������ݽṹ */
#include  "product_config.h"
#include "PsTypeDef.h"
#include "WUe.h"
#include "WUeL2L3.h"
#include "WUeSpec.h"

#pragma pack(4)

/*****************************************************************************
  1 ��Ϣͷ����
*****************************************************************************/
enum RRC_MAC_MSG_TYPE_ENUM
{
    ID_MAC_RRC_ACTIVE_IND               = 0x0000,           /* _H2ASN_MsgChoice MAC_RRC_ACTIVE_IND_STRU */

    ID_MAC_RRC_STATUS_IND               = 0x0001,           /* _H2ASN_MsgChoice MAC_RRC_STATUS_IND_STRU */
                                                            /* RB0�������ݷ��ͳɹ�ָʾ */

    ID_RRC_MAC_C_CONFIG_REQ             = 0x0002,           /* _H2ASN_MsgChoice RRC_MAC_C_CONFIG_REQ_STRU */
    ID_MAC_RRC_C_CONFIG_CNF             = 0x0003,           /* _H2ASN_MsgChoice MAC_RRC_C_CONFIG_CNF_STRU */

    ID_RRC_MAC_D_CONFIG_REQ             = 0x0004,           /* _H2ASN_MsgChoice RRC_MAC_D_CONFIG_REQ_STRU */
    ID_MAC_RRC_D_CONFIG_CNF             = 0x0005,           /* _H2ASN_MsgChoice MAC_RRC_D_CONFIG_CNF_STRU */

    ID_RRC_MAC_E_VIRTUAL_CONFIG_REQ     = 0x0006,           /* _H2ASN_MsgChoice RRC_MAC_E_VIRTUAL_CONFIG_REQ_STRU */
    ID_MAC_RRC_E_VIRTUAL_CONFIG_CNF     = 0x0007,           /* _H2ASN_MsgChoice MAC_RRC_E_VIRTUAL_CONFIG_CNF_STRU */

    ID_RRC_MAC_HS_CONFIG_REQ            = 0x0008,           /* _H2ASN_MsgChoice RRC_MAC_HS_CONFIG_REQ_STRU */
    ID_MAC_RRC_HS_CONFIG_CNF            = 0x0009,           /* _H2ASN_MsgChoice MAC_RRC_HS_CONFIG_CNF_STRU */

    ID_RRC_MAC_HS_RESET_REQ             = 0x000C,           /* _H2ASN_MsgChoice RRC_MAC_HS_RESET_REQ_STRU */
    ID_MAC_RRC_HS_RESET_CNF             = 0x000D,           /* _H2ASN_MsgChoice MAC_RRC_HS_RESET_CNF_STRU */

    ID_RRC_MAC_RELEASE_REQ              = 0x000E,           /* _H2ASN_MsgChoice RRC_MAC_RELEASE_REQ_STRU */
    ID_MAC_RRC_RELEASE_CNF              = 0x000F,           /* _H2ASN_MsgChoice MAC_RRC_RELEASE_CNF_STRU */

    ID_RRC_MAC_TFC_CONTROL_REQ          = 0x0010,           /* _H2ASN_MsgChoice RRC_MAC_TFC_CONTROL_REQ_STRU */
                                                            /* RRC�յ� TRANSPORT FORMAT COMBINATION CONTROL������MAC */
    ID_MAC_RRC_TFC_CONTROL_IND          = 0x0011,           /* _H2ASN_MsgChoice MAC_RRC_TFC_CONTROL_IND_STRU */
                                                            /* ��AMRҵ����Ҫ�ı����������ģ���AMR���� */

    ID_RRC_MAC_CIPHER_CONFIG_REQ        = 0x0012,           /* _H2ASN_MsgChoice RRC_MAC_CIPHER_CONFIG_REQ_STRU */
                                                            /* RRC����MAC������Ϣ */
    ID_MAC_RRC_CIPHER_CONFIG_CNF        = 0x0013,           /* _H2ASN_MsgChoice MAC_RRC_CIPHER_CONFIG_CNF_STRU */

    ID_MAC_RRC_CIPHER_ACTIVE_IND        = 0x0014,           /* _H2ASN_MsgChoice MAC_RRC_CIPHER_ACTIVE_IND_STRU */
                                                            /* RRC�յ�����Ϣ�󣬿�ʼ����STARTֵ */

    ID_RRC_MAC_MEAS_CONFIG_REQ          = 0x0015,           /* _H2ASN_MsgChoice RRC_MAC_MEAS_CONFIG_REQ_STRU */
                                                            /* RRC�յ�����ҵ�����������ƺ�����MAC */
    ID_MAC_RRC_MEAS_CONFIG_CNF          = 0x0016,           /* _H2ASN_MsgChoice MAC_RRC_MEAS_CONFIG_CNF_STRU */

    ID_MAC_RRC_MEAS_IND                 = 0x0017,           /* _H2ASN_MsgChoice MAC_RRC_MEAS_IND_STRU */

    ID_RRC_MAC_MEAS_REL_REQ             = 0x0018,           /* _H2ASN_MsgChoice RRC_MAC_MEAS_REL_REQ_STRU */
                                                            /* RRC�յ�ֹͣҵ�����������ƺ�����MAC */
    ID_MAC_RRC_MEAS_REL_CNF             = 0x0019,           /* _H2ASN_MsgChoice MAC_RRC_MEAS_REL_CNF_STRU */

    ID_MAC_RRC_PCCH_DATA_IND            = 0x001A,           /* _H2ASN_MsgChoice MAC_RRC_PCCH_DATA_IND_STRU */
                                                            /* PCH�����ŵ����յ�����Ϣ���ϱ���RRC */

    ID_MAC_RRC_BCCH_DATA_IND            = 0x001B,           /* _H2ASN_MsgChoice MAC_RRC_BCCH_DATA_IND_STRU */
                                                            /* FACH�����ŵ���MAC�յ�SYSTEM INFORMATION CHANGE INDICATION*/

    ID_MAC_RRC_ERROR_IND                = 0x001C,           /* _H2ASN_MsgChoice MAC_RRC_ERROR_IND_STRU */


    ID_RRC_MAC_COMPRESS_MODE_CFG_REQ    = 0x001D,           /* _H2ASN_MsgChoice RRC_MAC_COMPRESS_MODE_CFG_REQ_STRU */
    ID_RRC_MAC_COMPRESS_MODE_CFG_CNF    = 0x001E,           /* _H2ASN_MsgChoice RRC_MAC_COMPRESS_MODE_CFG_CNF_STRU */

    ID_RRC_MAC_TFC_SLOT_CFG_REQ         = 0x0020,           /* _H2ASN_MsgChoice RRC_MAC_TFC_SLOT_CFG_REQ_STRU */
    ID_RRC_MAC_TFC_SLOT_CFG_CNF         = 0x0021,           /* _H2ASN_MsgChoice RRC_MAC_TFC_SLOT_CFG_CNF_STRU */

    ID_RRC_MAC_STOP_UL_TX_REQ           = 0x0022,           /* _H2ASN_MsgChoice RRC_MAC_STOP_UL_TX_REQ_STRU */
    ID_MAC_RRC_STOP_UL_TX_CNF           = 0x0023,           /* _H2ASN_MsgChoice MAC_RRC_STOP_UL_TX_CNF_STRU */

    ID_RRC_MAC_CONTINUE_UL_TX_REQ       = 0x0024,           /* _H2ASN_MsgChoice RRC_MAC_CONTINUE_UL_TX_REQ_STRU */
    ID_MAC_RRC_CONTINUE_UL_TX_CNF       = 0x0025,           /* _H2ASN_MsgChoice MAC_RRC_CONTINUE_UL_TX_CNF_STRU */

    ID_RRC_MAC_TGPS_PRE_CHK_REQ         = 0x0026,           /* _H2ASN_MsgChoice RRC_MAC_TGPS_PRE_CHK_REQ_STRU */
    ID_MAC_RRC_TGPS_PRE_CHK_CNF         = 0x0027,           /* _H2ASN_MsgChoice MAC_RRC_TGPS_PRE_CHK_CNF_STRU */

    /*V3 R7_7C1 Start */

    /*Add for MAC-ehs*/
    ID_RRC_MAC_EHS_CONFIG_REQ           = 0x0028,           /* _H2ASN_MsgChoice RRC_MAC_EHS_CONFIG_REQ_STRU */
    ID_MAC_RRC_EHS_CONFIG_CNF           = 0x0029,           /* _H2ASN_MsgChoice MAC_RRC_EHS_CONFIG_CNF_STRU */

    ID_RRC_MAC_EHS_RESET_REQ            = 0x002A,           /* _H2ASN_MsgChoice RRC_MAC_EHS_RESET_REQ_STRU */
    ID_MAC_RRC_EHS_RESET_CNF            = 0x002B,           /* _H2ASN_MsgChoice MAC_RRC_EHS_RESET_CNF_STRU */


    ID_RRC_MAC_BCBD_CALCULATE_REQ       = 0x002C,           /* _H2ASN_MsgChoice RRC_MAC_BCBD_CALCULATE_REQ_STRU */
    ID_MAC_RRC_BCBD_CALCULATE_CNF       = 0x002D,           /* _H2ASN_MsgChoice MAC_RRC_BCBD_CALCULATE_CNF_STRU  */


    ID_RRC_MAC_BHS_CALCULATE_REQ        = 0x002E,           /* _H2ASN_MsgChoice RRC_MAC_BHS_CALCULATE_REQ_STRU */
    ID_MAC_RRC_BHS_CALCULATE_CNF        = 0x002F,           /* _H2ASN_MsgChoice MAC_RRC_BHS_CALCULATE_CNF_STRU */

    ID_RRC_MAC_CIPHER_RESERVE_REQ       = 0x0030,           /* _H2ASN_MsgChoice  RRC_MAC_CIPHER_RESERVE_REQ_STRU */
    ID_MAC_RRC_CIPHER_RESERVE_CNF       = 0x0031,           /* _H2ASN_MsgChoice  MAC_RRC_CIPHER_RESERVE_CNF_STRU */

    ID_RRC_MAC_C_CONFIG_REQ_MNTN_COMM_PARAM = 0x0032,       /* _H2ASN_MsgChoice RRC_MAC_C_CONFIG_REQ_MNTN_COMM_PARAM_STRU */
    ID_RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH1     = 0x0033,       /* _H2ASN_MsgChoice RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH1_STRU */
    ID_RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH2     = 0x0034,       /* _H2ASN_MsgChoice RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH2_STRU */

    ID_MAC_RRC_EHS_RX_DATA_IND              = 0x0035,       /* _H2ASN_MsgChoice MAC_RRC_EHS_RX_DATA_IND_STRU */

    ID_RRC_MAC_I_VIRTUAL_CONFIG_REQ         = 0x0036,           /* _H2ASN_MsgChoice RRC_MAC_I_VIRTUAL_CONFIG_REQ_STRU */
    ID_MAC_RRC_I_VIRTUAL_CONFIG_CNF         = 0x0037,           /* _H2ASN_MsgChoice MAC_RRC_I_VIRTUAL_CONFIG_CNF_STRU */

    /* ���ڽ���SIB7�����ӿ� */
    ID_RRC_MAC_ASC_CONFIG_IND               = 0x0038,           /* _H2ASN_MsgChoice RRC_MAC_ASC_CONFIG_STRU */

    ID_RRC_MAC_AS_ACTIVE_DSDS_STATUS_IND    = 0x0039,           /* _H2ASN_MsgChoice RRC_MAC_AS_ACTIVE_DSDS_STATUS_IND_STRU */

    /* MAC_D_CONFIG_REQ��MAC_C_CONFIG_REQ����ṹ������L2 ST����ʹ�ã�������ʵ�ʽӿ��� */
    ID_RRC_MAC_C_CONFIG_REDUCE_REQ          = 0x8002,           /* _H2ASN_MsgChoice RRC_MAC_C_CONFIG_REDUCE_REQ_STRU */
    ID_RRC_MAC_D_CONFIG_REDUCE_REQ          = 0x8004,           /* _H2ASN_MsgChoice RRC_MAC_D_CONFIG_REDUCE_REQ_STRU */

    ID_WTTF_MEM_TEST_REQ                    = 0x8005,           /* _H2ASN_MsgChoice WTTF_MEM_TEST_REQ_STRU */
    ID_WTTF_MEM_TEST_CNF                    = 0x8006,           /* _H2ASN_MsgChoice WTTF_MEM_TEST_CNF_STRU */
    /* V3 R7_7C1 End */

    ID_RRC_MAC_QUIT_REQ                     = 0x8007,

    ID_RRC_MAC_MSG_TYPE_BUTT                = 0xFFFF
};
typedef VOS_UINT16 RRC_MAC_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ����ASC��PIʱͳһ����10000������֤���ȣ�MAC�����漴��ʱҲʹ������� */
#define    MACITF_ASC_PI_MULTIPLE       (10000)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*V3 R7_7C1 Start */
/* �ظ�RRC����ָʾʱ�Ĵ������� */
enum MACITF_RRC_ERR_CODE_ENUM
{
    MACITF_RRC_ERR_CODE_EHS_ACT_FAIL        = 0,   /* ��MAC�ڼ���ʱ�䵽ʱ�������ó����˴���ͨ������Ϣ֪ͨRRC */
    MACITF_RRC_ERR_CODE_BCBD_ACT_FAIL       = 1,   /* RRC���õ�BCBDֵ���ִ���ͨ������Ϣ֪ͨRRC */
    MACITF_RRC_ERR_CODE_AMRRATES_CALC_FAIL  = 2,   /* RRC���õ�AMR���ʳ��ִ���ͨ������Ϣ֪ͨRRC */
    MACITF_RRC_ERR_CODE_MAC_STATE_ERR       = 3,   /* MAC״̬�쳣��ͨ������Ϣ֪ͨRRC */

    MACITF_RRC_ERR_CODE_BUTT
};
typedef VOS_UINT32 MACITF_RRC_ERR_CODE_ENUM_UINT32;
/* V3 R7_7C1 End */


/* �¼������Ĳ����Ľṹ�� */
/* ���������¼�ID */
enum MACITF_TRAF_VOL_EVT_TYPE_ENUM
{
    MACITF_TRAF_VOL_EVT_4A              = 0,
    MACITF_TRAF_VOL_EVT_4B              = 1,
    MACITF_TRAF_VOL_EVT_BUTT
};
typedef VOS_UINT8 MACITF_TRAF_VOL_EVT_TYPE_ENUM_UINT8;

/* ��ϢMAC_RRC_TFC_CONTROL_IND�Ľṹ�� */
enum MACITF_TFC_CTRL_ENUM
{
    MACITF_TFC_CTRL_BEGIN               = 0,
    MACITF_TFC_CTRL_END                 = 1,
    MACITF_TFC_CTRL_BUTT
};
typedef VOS_UINT8 MACITF_TFC_CTRL_ENUM_UINT8;

/* ��ϢRRC_MAC_RELEASE_REQ�Ľṹ�� */
enum MACITF_REL_MODE_ENUM
{
    MACITF_REL_MAC_C                    = 0,
    MACITF_REL_MAC_D                    = 1,                /* ����ͷ�MAC-D����MAC-E/MAC-HS���ͷ� */
    MACITF_REL_VIRTUAL_MAC_E            = 2,                /* MAC-E,MAC-ESһ���ͷ� */
    MACITF_REL_MAC_HS                   = 3,                /* �ͷ�MAC-HSʵ�� */
    MACITF_REL_MAC_ALL                  = 4,                /* �ͷ����е�MACʵ�� */

    /*V3 R7_7C1 Start */
    MACITF_REL_MAC_EHS                  = 5,                /*add for MAC-ehs*/
    MACITF_REL_VIRTUAL_MAC_I            = 6,                /* MAC-I,MAC-ISһ���ͷ� */

    MACITF_REL_MODE_BUTT
};
typedef VOS_UINT8 MACITF_REL_MODE_ENUM_UINT8;

/* �����ŵ����� */
enum MACITF_TRCH_TYPE_ENUM
{
    MACITF_FACH_TYPE                    = 0,
    MACITF_PCH_TYPE                     = 1,

    MACITF_TRCH_TYPE_BUTT
};
typedef VOS_UINT8 MACITF_TRCH_TYPE_ENUM_UINT8;

/* TTI���壬��10msΪ��λ�� */
enum MACITF_TTI_ENUM
{
    MACITF_TTI_NULL                     = 0,                /*Ϊ����IT����ʱ����Ϣ�����Ӹ������������ */
    MACITF_TTI_10MS                     = 1,
    MACITF_TTI_20MS                     = 2,
    MACITF_TTI_40MS                     = 4,
    MACITF_TTI_80MS                     = 8,
    MACITF_TTI_BUTT
};
typedef VOS_UINT8   MACITF_TTI_ENUM_UINT8;

enum MACITF_CRC_SIZE_ENUM
{
    MACITF_CRC_SIZE_0BIT                = 0,
    MACITF_CRC_SIZE_8BIT                = 8,
    MACITF_CRC_SIZE_12BIT               = 12,
    MACITF_CRC_SIZE_16BIT               = 16,
    MACITF_CRC_SIZE_24BIT               = 24,
    MACITF_CRC_SIZE_BUTT
};
typedef VOS_UINT8   MACITF_CRC_SIZE_ENUM_UINT8;

enum MACITF_RSLT_ENUM
{
    MACITF_SUCC                         = 0,
    MACITF_FAIL                         ,
    MACITF_RSLT_BUTT
};
typedef VOS_UINT32   MACITF_RSLT_ENUM_UINT32;

/* RRC���õ�ѹģ���е�״̬���� */
enum MACITF_TGPS_CFG_STATUS_ENUM
{
    MACITF_TGPS_CFG_CHANGED_ACTIVED         = 0 ,
    MACITF_TGPS_CFG_CHANGED_INACTIVED       = 1 ,
    MACITF_TGPS_CFG_UNCHANGED_ACTIVED       = 2 ,
    MACITF_TGPS_CFG_UNCHANGED_INACTIVED     = 3 ,
    MACITF_TGPS_CFG_BUTT
};
typedef VOS_UINT16 MACITF_TGPS_CFG_STATUS_ENUM_UINT16;

/* ͬƵӲ�л�������ϵͳ�л����ܻ��˵ļ���״̬���� */
enum MACITF_CIPHER_STATUS_ENUM
{
    MACITF_CIPHER_STA_BACKUP                       = 0,      /*֪ͨMAC����cipher��ز���*/
    MACITF_CIPHER_STA_REVERT                       = 1,  /* ֪ͨMAC���¼���������� */
    MACITF_CIPHER_STA_BUTT
};
typedef VOS_UINT16 MACITF_CIPHER_STATUS_ENUM_UINT16;

/*****************************************************************************
 ö����    : MACITF_RNTI_CFG_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : ָʾ��ǰUE������H-RNTI�����DL_E_CELLFACH����
*****************************************************************************/
enum MACITF_RNTI_CFG_ENUM
{
    MACITF_RNTI_CFG_COMM_HRNTI      = 0,    /* UE��ǰ������COMMON H-RNTI */
    MACITF_RNTI_CFG_DEDICATE_HRNTI  = 1,    /* UE��ǰǰ������DEDICATE H-RNTI */
    MACITF_RNTI_CFG_NO_HRNTI        = 2,    /* UE��ǰδ���� H-RNTI,DL_E_CELLFACHä��ⳡ�� */
    MACITF_RNTI_CFG_BUTT
};
typedef VOS_UINT8 MACITF_RNTI_CFG_ENUM_UINT8;

/*****************************************************************************
 ö����    : MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ������AM RBΪ����sizeʱ, ����LI��ʹ��7-bit, ����15-bit
*****************************************************************************/
enum   MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM
{
    MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_7_BIT  = 7,
    MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_15_BIT = 15,
    MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_BUTT
};
typedef VOS_UINT16   MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16;

/*****************************************************************************
 ö����    : MACITF_EDCH_FLOW_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : ��������һ���߼��ŵ��ǳ����ڵ�������, ���Ƿǵ�������
*****************************************************************************/
enum   MACITF_EDCH_FLOW_TYPE_ENUM
{
    MACITF_EDCH_FLOW_SCHED_TYPE     = 0,
    MACITF_EDCH_FLOW_NON_SCHED_TYPE = 1,
    MACITF_EDCH_FLOW_TYPE_BUTT
};
typedef VOS_UINT8   MACITF_EDCH_FLOW_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : MACITF_RLC_PDU_SIZE_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : ��������һ���߼��ŵ���ʹ�õ���size, ���Ǳ䳤size
*****************************************************************************/
enum   MACITF_RLC_PDU_SIZE_TYPE_ENUM
{
    MACITF_RLC_PDU_SIZE_FIXED_SIZE_TYPE     = 0,
    MACITF_RLC_PDU_SIZE_FLEX_SIZE_TYPE      = 1,
    MACITF_RLC_PDU_SIZE_TYPE_BUTT
};
typedef VOS_UINT8   MACITF_RLC_PDU_SIZE_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : MACITF_LOCH_DATA_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : ��������һ���߼��ŵ��ϳ��ص�ҵ�����
*****************************************************************************/
enum MACITF_LOCH_DATA_TYPE_ENUM
{
    MACITF_LOCH_DATA_TYPE_CCCH          = 0,
    MACITF_LOCH_DATA_TYPE_SRB              ,
    MACITF_LOCH_DATA_TYPE_CS               ,
    MACITF_LOCH_DATA_TYPE_PS               ,
    MACITF_LOCH_DATA_TYPE_BUTT
};
typedef VOS_UINT8   MACITF_LOCH_DATA_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : MACITF_EDCH_TTI_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : HSUPA ��EDCH TTI
*****************************************************************************/

enum    MACITF_EDCH_TTI_ENUM
{
    MACITF_EDCH_TTI_10MS                = 0,
    MACITF_EDCH_TTI_2MS                 = 1,

    MACITF_EDCH_TTI_BUTT

};
typedef VOS_UINT16 MACITF_EDCH_TTI_ENUM_UINT16;

enum MACITF_STATUS_ENUM
{
    MACITF_UP_TX_DATA_START             = 0,   /* ���п�ʼ���� */
    MACITF_UP_TX_DATA_END                  ,   /* ���з������� */
    MACITF_UP_TX_DATA_FAIL                 ,   /* ���з���ʧ�� */
    MACITF_STATUS_BUTT
};
typedef VOS_UINT32   MACITF_STATUS_ENUM_UINT32;
enum MACITF_MAC_EHS_TSN_BIT_LEN_ENUM
{
    MACITF_MAC_EHS_TSN_BIT_LEN_6_ENUM             = 6,   /* MAC-ehs TSN=6bits */
    MACITF_MAC_EHS_TSN_BIT_LEN_14_ENUM            = 14,  /* MAC-ehs TSN=14bits */
    MACITF_MAC_EHS_TSN_BIT_LEN_BUTT
};
typedef VOS_UINT8    MACITF_MAC_EHS_TSN_BIT_LEN_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDchTrchId;        /* [1,32] */
    VOS_UINT8                           ucDschTrchId;
}MACITF_CH_ID_DCH_DSCH_STRU;

typedef struct
{
    VOS_UINT8                           ucDchTrchId;        /* [1,32] */
    VOS_UINT8                           ucHsdschMacDFlowId; /* [0,7] */
}MACITF_MACD_FLOW_ID_DCH_HSDSCH_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_UL_TRCH_ID_CHOICE_STRU
 Э����  : 10.3.7.69 Traffic volume measurement event results
 ASN.1���� : UL_TrCH_Identity
             UL_TransportChannelType
 �ṹ˵��  : ���д����ŵ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulChoice;

    #define    MACITF_UL_TRCH_DCH_CHOSEN            0
    #define    MACITF_UL_TRCH_RACH_CHOSEN           1
    #define    MACITF_UL_TRCH_E_DCH_CHOSEN          2       /* �������������� */

    union
    {
        VOS_UINT8                       ucUlDchId;          /* [PS_WUE_MIN_TRCH_ID,PS_WUE_MAX_TRCH_ID] */
        PS_NULL_STRU                    stRach;
        PS_NULL_STRU                    stEDch;
    }u;
}MACITF_UL_TRCH_ID_CHOICE_STRU;



/*****************************************************************************
 �ṹ��    : MACITF_UL_PER_LOCH_MAPP_CHOICE_STRU
 Э����  : 10.3.4.21  RB mapping info
 ASN.1���� : UL_LogicalChannelMapping_r6
 �ṹ˵��  : RACH,DCH�߼��ŵ��봫���ŵ��Ķ�Ӧ��ϵ���Լ��߼��ŵ����õ�RLC SIZE
*****************************************************************************/
typedef struct
{
    MACITF_UL_TRCH_ID_CHOICE_STRU       stTrchId;
    VOS_UINT8                           ucLochLabel;        /* �߼��ŵ��ڲ�ʵ��ͳһ��ʶ��[0,[0,34*2-1]] */
    VOS_UINT8                           ucLochId;           /* �߼��ŵ�ID��[1,15]��0��ʾ��Ч */
    VOS_UINT8                           ucLochPrio;         /* �߼��ŵ����ȼ���[1,8] */
    /* ASN.1 �ı� : RLC_SizeExplicitList */
    VOS_UINT8                           ucRlcSizeCnt;       /* ���õ�RLC Size ���� */
    /* ��ӦastTfPerRlcSize[PS_WUE_MAX_TF_NUM]�����±�����,Э��ֵΪ[1,PS_WUE_MAX_TF_NUM],����ʵ��ֵΪ[0,PS_WUE_MAX_TF_NUM-1] */
    VOS_UINT8                           aucRlcSizeIdx[PS_WUE_MAX_TF_NUM];
}MACITF_RACH_DCH_LOCH_MAPP_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_RLC_PDU_FIXED_SIZE_STRU
 Э����  :
 ASN.1���� : ASN.1 �ı� : RLC_PDU_SizeList
 �ṹ˵��  : RLC_PDU�̶�SIZE�Ĳ���
*****************************************************************************/
typedef struct
{
   VOS_UINT8                           aucReserve[3];
   VOS_UINT8                           ucRlcSizeCnt;                            /* [1,32] */
   VOS_UINT16                          ausRlcSize[PS_WUE_MAX_RLC_PDU_SIZE_NUM_PER_LOCH];/* [16,5000],by step of 8, unit: bit */
}MACITF_RLC_PDU_FIXED_SIZE_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_EDCH_RLC_PDU_SIZE_FIXED_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC_PDU�̶�SIZEʱ, EDCH���õĲ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucDdi;                          /* [0,62] */
    VOS_UINT8                                   aucReserve1[3];                 /* 4�ֽڶ��룬���� */
    MACITF_RLC_PDU_FIXED_SIZE_STRU              stFixedSize;                    /* Fixed Size */
}MACITF_EDCH_RLC_PDU_SIZE_FIXED_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_RLC_PDU_FLEX_SIZE_STRU
 Э����  :
 ASN.1���� : ASN.1 �ı� : RLC-PDU-SizeConstraint
 �ṹ˵��  : RLC_PDU�ɱ�SIZE�Ĳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      ucReserve;
    MACITF_FLEX_RLC_PDU_SIZE_LI_SIZE_ENUM_UINT16    enLenIndSize;               /* ENUMERATED  OPTIONAL,����û��Я����ʱ����дBUTT */
    VOS_UINT16                                      usMinRlcPduSize;            /* Integer (16..12040 by step of 8), unit: bit, �տ�����*8 */
    VOS_UINT16                                      usLargestRlcPduSize;        /* Integer (16..12040 by step of 8), unit: bit, �տ�����*8 */
}MACITF_RLC_PDU_FLEX_SIZE_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_EDCH_RLC_PDU_SIZE_FLEX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC_PDU�ɱ�SIZEʱ, EDCH���õĲ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   aucExt[8];                      /* ����8�ֽڴ������չʹ�� */
    MACITF_RLC_PDU_FLEX_SIZE_STRU               stFlexSize;                     /*Flexible Size*/
}MACITF_EDCH_RLC_PDU_SIZE_FLEX_STRU;


/*****************************************************************************
 �ṹ��    : MACITF_EDCH_LOCH_MAPP_STRU
 Э����  : 10.3.4.21  RB mapping info
 ASN.1���� : UL_LogicalChannelMapping_r6
 �ṹ˵��  : EDCH�߼��ŵ��봫���ŵ��Ķ�Ӧ��ϵ���Լ��߼��ŵ����õ�RLC SIZE
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucLochLabel;                    /* �߼��ŵ��ڲ�ʵ��ͳһ��ʶ��[0,[0,34*2-1]] */
    VOS_UINT8                                   ucLochId;                       /* INTEGER(1..15),0��ʾ��Ч */
    VOS_UINT8                                   ucEdchMacdFlowId;               /* [0,7] */
    PS_BOOL_ENUM_UINT8                          enIncSI;                        /* ��MAC-d����Ӧ���߼��ŵ��Ƿ�������SI��bIncludeInSchedulInfo*/
    VOS_UINT8                                   ucLochPrio;                     /* �߼��ŵ����ȼ���[1,8] */

    VOS_UINT8                                   aucReserve1[3];                 /* 4�ֽڶ��룬���� */

    #define    MACITF_EDCH_RLC_PDU_SIZE_FIXED_SIZE   0                          /* Fixed size*/
    #define    MACITF_EDCH_RLC_PDU_SIZE_FLEX_SIZE    1                          /* Flexible size*/

    VOS_UINT32                                  ulChoice;

    union
    {
        MACITF_EDCH_RLC_PDU_SIZE_FIXED_STRU     stEdchFixedSize;                /* Fixed size */
        MACITF_EDCH_RLC_PDU_SIZE_FLEX_STRU      stEdchFlexSize;                 /* Flexible Size */
    } u;
}MACITF_EDCH_LOCH_MAPP_STRU;

/******************************* ������Ϣ�����ݽṹ ***********************************/
/* ��Ҫ�����Ĵ����ŵ��б� */
typedef struct
{
    VOS_UINT8                           aucReserve1[3];                         /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucTrchCnt;                              /* ��DCH����:
                                                                                �������δ����Traffic volume measurement Object,��RRC����ucTrchCnt = 0,MAC��RLCʵ�������ú󣬽���ǰ����DCH����ΪMAC MEASUREMENT OBJECT;
                                                                                �������������Traffic volume measurement Object,�򽫱��ṹ���õ�DCH ID��ΪMAC MEASUREMENT OBJECT,MAC��RLCʵ�������ú󲻽����κθ���
                                                                                ��RACH/EDCH����:ucTrchCnt;һ��Ϊ1 */
    MACITF_UL_TRCH_ID_CHOICE_STRU       astTrchId[PS_WUE_MAX_MEAS_TRCH_NUM];    /* ��Ҫ�����Ĵ����ŵ��ı��*/
}MACITF_MEAS_OBJ_LIST_STRU;

/* �����Ա���Ĳ����Ľṹ�� */
/* Э���� : 10.3.7.53 Periodical reporting criteria  */
/* ASN.1 �ı� : PeriodicalReportingCriteria */
typedef struct
{
    VOS_UINT16                          usRptInterval;      /*��λms,(250, 500, 1000, 2000, 3000, 4000, 6000, 8000, 12000, 16000, 20000, 24000, 28000, 32000, 64000),���ڱ����ʱ���� */
    /* ASN.1 �ı� : ReportingIntervalLong */
    VOS_UINT8                           ucRepAmount;        /* ���ڱ����������,(1, 2, 4, 8, 16, 32, 64, Infinity = 0)   */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
}MACITF_PERIOD_RPT_CRTR_STRU;

/* Э���� : 10.3.7.72 Traffic volume measurement reporting criteria  */
/* ASN.1 �ı� : TrafficVolumeEventParam */
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    MACITF_TRAF_VOL_EVT_TYPE_ENUM_UINT8 enEvtType;          /* �¼��ı�ʶ */
    /* ���������Я��Trigger Time��Ĭ��Ϊ����������ulTriggerTime����Ϊ0��
       ���������Я��Pending After Trigger,Ĭ��Ϊ����������ulPendTimeAftTrig����Ϊ0,
       ���������Я��Tx interruption after trigger,,Ĭ��Ϊ��ֹͣ����DTCH/RACH���ݣ�ulPendTimeAftTrig����Ϊ0.
       �ο�25.331 14.4.2    Traffic Volume reporting triggers */
    VOS_UINT16                          usTriggerTime;      /* ��λms,(0, 10, 20, 40, 60, 80, 100, 120, 160, 200, 240, 320, 640, 1280, 2560, 5000)trigger time */
    VOS_UINT16                          usPendTimeAftTrig;  /* ��λms,(0, 250, 500, 1000, 2000, 4000, 8000, 16000)���β�������֮�����Сʱ���� */
    VOS_UINT16                          usTxIntrrptAftTrig; /* ��λms,(0, 250, 500, 1000, 2000, 4000, 8000, 16000)Time in milliseconds.
                                                               Indicates how long the UE shall block DTCH transmissions on the RACH after a measurement report is triggered.
                                                               �������ǿCELL_FACH(UL)��, TxIntrrptAftTrig����Ϊ0 */
    /* ASN.1 �ı� : TrafficVolumeThreshold */
    VOS_UINT32                          ulRptThresh;        /* ��λbyte,(8,16,32,64,128,256,512,1024,2K,3K,4K,6K,8K,12K,16K,24K,32K,48K,64K,96K,128K,192K,256K,384K,512K,768K)�¼���������ֵ */

}MACITF_MAC_EVT_PARA_STRU;


/* ÿ��TRCH���¼������Ĳ��� */
/* ASN.1 �ı� : TransChCriteria */
typedef struct
{
    MACITF_UL_TRCH_ID_CHOICE_STRU       stTrchId;
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucEvtNum;           /* �¼������ĸ�������Ȼ��Ч */
    MACITF_MAC_EVT_PARA_STRU            astEvtPara[PS_WUE_MAX_MEAS_PAR_EV_NUM];
}MACITF_TRAF_VOL_RPT_INFO_STRU;

/* �¼���������Ĳ����Ľṹ�� */
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucTrchCnt;          /* �����¼�������TrCH��,
                                                               ��DCH���в���ʱ:
                                                                   �������û������event trig ��DCH ID,RRC������ucTrchCnt = 0������ astTrafVolRptInfo[0]����һ�״�����׼��
                                                                   MAC��RLCʵ�������ú�,��MACITF_MEAS_OBJ_LIST_STRU����Ч��DCH��ΪMAC MEASUREMENT OBJECT������DCH��ش���������ʹ��astTrafVolRptInfo[0]�е�����;
                                                                   �������������event trig ��DCH ID����ʹ�����õ�DCH ID,MAC��RLCʵ�������ú�,�������κθ���
                                                               ��RACH/EDCH����ʱ:
                                                                   ucTrchCntһ����1
                                                               */
    MACITF_TRAF_VOL_RPT_INFO_STRU       astTrafVolRptInfo[PS_WUE_MAX_MEAS_TRCH_NUM];/* ÿ��TRCH���¼������Ĳ��� */
}MACITF_TRAF_VOL_RPT_CRTR_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_PERIOD_RPT_RSLT_STRU
 Э����  : 14.4.2    Traffic Volume reporting triggers
 ASN.1���� : TrafficVolumeMeasuredResults
 �ṹ˵��  : MAC�ϱ��������,���ڴ�������Ĳ����Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpVarBO          : 1;
    VOS_UINT32                          bitOpAveBO          : 1;
    VOS_UINT32                          bitOpBO             : 1;
    VOS_UINT32                          bitSpare            : 29;

    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucRbId;             /* [1,32],RB��ID */
    VOS_UINT16                          usVarBO;            /* ��λ:�ֽڣ�(0, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2K, 4K, 8K, 16K),N Kbytes = N*1024 bytes,RLC���صķ��� */
    VOS_UINT32                          ulAveBO;            /* ��λ:�ֽڣ�(0, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2K, 4K, 8K, 16K, 32K, 64K, 128K, 256K, 512K, 1024K),N Kbytes = N*1024 bytes,RLC���صľ�ֵ */
    VOS_UINT32                          ulBO;               /* ��λ:�ֽڣ�(0, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2K, 4K, 8K, 16K, 32K, 64K, 128K, 256K, 512K, 1024K),N Kbytes = N*1024 bytes,RLC���� */
}MACITF_PERIOD_RPT_RB_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_PERIOD_RPT_RSLT_STRU
 Э����  : 14.4.2    Traffic Volume reporting triggers
 ASN.1���� : TrafficVolumeMeasuredResultsList
 �ṹ˵��  : MAC�ϱ��������,���ڴ�������Ĳ����Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucRbCnt;            /*[0,32],�����RB���� */
    MACITF_PERIOD_RPT_RB_RESULT_STRU    astRbRslt[PS_WUE_MAX_RB_NUM];/* RB�Ĳ������ */
} MACITF_MEAS_RSLT_STRU;


/*****************************************************************************
 �ṹ��    : MACITF_EVENT_RPT_RSLT_STRU
 Э����  : 14.4.2    Traffic Volume reporting triggers
 ASN.1���� : TrafficVolumeEventResults
 �ṹ˵��  : MAC�ϱ��������,�¼�
*****************************************************************************/
/* �¼���������Ĳ����Ľṹ�� */
typedef struct
{
    /*ASN.1:measuredResults                MeasuredResults*/
    MACITF_MEAS_RSLT_STRU               stMeasRslt;

    /*ASN.1:eventResults                EventResults*/
    MACITF_UL_TRCH_ID_CHOICE_STRU       stUlTrchId;         /* �����ŵ���ʶ */
    MACITF_TRAF_VOL_EVT_TYPE_ENUM_UINT8 enEvtId;            /* �¼��ı�ʶ */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
}MACITF_EVENT_RPT_RSLT_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_RACH_TRANS_PARAMS_STRU
 Э����  : 10.3.6.67 RACH transmission parameters
 ASN.1���� : RACH_TransmissionParameters
 �ṹ˵��  : �漴������ش���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmax;             /* [1,32],preamble part����ʹ��� */
    VOS_UINT8                           ucNB01Min;          /* [0,50],���ڲ��������NBO1������ֵ�� 0 <= NBO1min <= NBO1 <= NBO1max */
    VOS_UINT8                           ucNB01Max;          /* [0,50],���ڲ��������NBO1������ֵ�� 0 <= NBO1min <= NBO1 <= NBO1max */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
}MACITF_RACH_TRANS_PARAMS_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_RACH_ASC_INFO_STRU
 Э����  : 10.3.6.48    Persistence scaling factors
             10.3.6.1    AC-to-ASC mapping
 ASN.1���� : PRACH_SystemInformation
             AC_To_ASC_MappingTable
             PersistenceScalingFactorList
 �ṹ˵��  : RACH�Ľ�����Ϣ
             P(N) = 2^[-(N - 1)]��N����SIB5,SIB6��WAS_DYN_PERSIST_LEV_LIST_STRU��
             ֵ��Ϊ1..8��
             Si = Persistence scaling factors,Real(0.9..0.2, by step of 0.1)
             Pi = si * P(N)��
             ������С�����Ϊ��N = 8��Si = 0.2,
              Pi = 0.2 * 0.0078125 = 0.0015625
             �����������Ϊ��N = 1, ����������
              Pi = 1 * 1 = 1��
             �ӿ���AscPi = Pi * MACITF_ASC_PI_MULTIPLE����֤���ȡ�
             [ע]CCB���е�WAS_PERSIST_SCALING_FACTOR_LIST_STRUֵ�ڱ���ʱ�Ѿ�
                 ������MACITF_ASC_PI_MULTIPLE��.
*****************************************************************************/
typedef struct
{
    /* ��UEû������URNTIʱ��WAS����AC���ucAscWithoutURnti */
    VOS_UINT8                           ucAscWithoutURnti;

    /* ucAscCnt = ucNumAsc+1,ucNumAsc�ķ�Χ0..7��ASC��ʵ��ȡֵi:0 <= i <= NumASC <= 7,��IDEL��PCH̬��RRC���õ�ucAscCnt=0 */
    VOS_UINT8                           ucAscCnt;
    /* ��UE�Ѿ�����URNTIʱʹ�ã������±���ASCֵ������Ԫ��ֵΪASC��Ӧ��Piֵ */
    VOS_UINT16                          ausAscPi[PS_WUE_MAX_ASC_NUM];
}MACITF_RACH_ASC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_RACH_ACCESS_INFO_STRU
 Э����  : 10.2.48.8.8 System Information Block type 5
 ASN.1���� : SysInfoType5
             PRACH_SystemInformation
 �ṹ˵��  : RACH�Ľ�����Ϣ
*****************************************************************************/
typedef struct
{
    MACITF_RACH_TRANS_PARAMS_STRU       stRachTransParams;  /* RACH ���Ͳ��� */
    MACITF_RACH_ASC_INFO_STRU           stRachAscInfo;      /* RACH ASC��Ϣ */
}MACITF_RACH_ACCESS_INFO_STRU;

/* ASN.1 �ı� : MAC_d_FlowIdentityDCHandHSDSCH */
typedef struct {
    VOS_UINT8                           ucDchId;            /* INTEGER(1..32) */
    VOS_UINT8                           ucHsdschMacDFlowId; /* INTEGER(0..7) */
}MACITF_MACD_FLOW_ID_DCH_HSDSCH;

/*V3 R7_7C1 Start */
typedef struct {
    VOS_UINT8                           ucDchId;            /* INTEGER(1..32) */
    VOS_UINT8                           ucHsdschMacEhsQueueId;/*INTEGER(0..7),for MAC-ehs*/
}MACITF_MACEHS_QUEUE_ID_DCH_HSDSCH;

/* V3 R7_7C1 End */

/*****************************************************************************
 �ṹ��    : MACITF_UL_PER_LOCH_MAPP_CHOICE_STRU
 Э����  : 10.3.4.21    RB mapping info
 ASN.1���� : UL_LogicalChannelMappingList_r6
 �ṹ˵��  : ����TRCH��LOCH��ӳ���ϵ������RACH,DCH,EDCH
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulChoice;

    #define      MACITF_UL_D_RACH_DCH_MAPP_CHOSEN                 0
    #define      MACITF_UL_D_EDCH_MAPP_CHOSEN                     1

    union
    {
        MACITF_RACH_DCH_LOCH_MAPP_STRU  stRachDchMapp;
        MACITF_EDCH_LOCH_MAPP_STRU      stEdchMapp;
    }u;
}MACITF_UL_PER_LOCH_MAPP_CHOICE_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_DL_TRCH_TYPE_CHOICE_STRU
 Э����  : 10.3.4.21    RB mapping info
 ASN.1���� : DL_TransportChannelType_r5
 �ṹ˵��  : ���д����ŵ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulChoice;

    #define      MACITF_TRCH_TYPE_DCH_CHOSEN                  0
    #define      MACITF_TRCH_TYPE_FACH_CHOSEN                 1
    #define      MACITF_TRCH_TYPE_DSCH_CHOSEN                 2
    #define      MACITF_TRCH_TYPE_DCH_AND_DSCH_CHOSEN         3
    #define      MACITF_TRCH_TYPE_HSDSCH_CHOSEN               4
    #define      MACITF_TRCH_TYPE_DCH_HSDSCH_CHOSEN           5
    /*V3 R7_7C1 Start */
    #define      MACITF_TRCH_TYPE_MACEHS_QUEUE_CHOSEN         6    /* for MAC-ehs */
    #define      MACITF_TRCH_TYPE_DCH_MACEHS_QUEUE_CHOSEN     7    /* for MAC-ehs multi mapping */
    /* V3 R7_7C1 End */


    /* The IE "Downlink transport channel type" values " DSCH" and
       "DCH+DSCH " should not be used for FDD. If received the UE
       behaviour is unspecified. */
    union
    {
        VOS_UINT8                           ucDchId;            /* [PS_WUE_MIN_TRCH_ID,PS_WUE_MAX_TRCH_ID] */
        PS_NULL_STRU                        stFach;             /* FACHʱ��MACͨ��CT����ӳ���ϵ */
        PS_NULL_STRU                        stDschId;           /* TDD */
        PS_NULL_STRU                        stDchDschId;        /* TDD */
        VOS_UINT8                           ucHsdschMacDFlowId; /* INTEGER(0..7) */
        MACITF_MACD_FLOW_ID_DCH_HSDSCH      stDchHsdschId;
        /*V3 R7_7C1 Start */
        VOS_UINT8                           ucHsdschMacEhsQueueId;/*INTEGER(0..7),for MAC-ehs*/
        MACITF_MACEHS_QUEUE_ID_DCH_HSDSCH   stDchMacEhsHsdschId;    /* for MAC-ehs */
        /* V3 R7_7C1 End */

    }u;
}MACITF_DL_TRCH_TYPE_CHOICE_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_DL_PER_LOCH_MAPP_STRU
 Э����  : 10.3.4.21    RB mapping info
 ASN.1���� : DL_LogicalChannelMappingList_r5
 �ṹ˵��  : �����߼��ŵ��봫���ŵ���ӳ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucLochLabel;        /* �߼��ŵ��ڲ�ʵ��ͳһ��ʶ��[0,[0,34*2-1]] */
    VOS_UINT8                           ucLochId;           /* INTEGER(1..15),0��ʾ��Ч */
    MACITF_DL_TRCH_TYPE_CHOICE_STRU     stTrchInfo;
}MACITF_DL_PER_LOCH_MAPP_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_DL_LOCH_MAPP_STRU
 Э����  : 10.3.4.21    RB mapping info
 ASN.1���� : DL_LogicalChannelMappingList_r5
 �ṹ˵��  : �����߼��ŵ��봫���ŵ���ӳ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucDlPerRlcLochCnt;  /* [1,2] */
    MACITF_DL_PER_LOCH_MAPP_STRU        astDlLochInfo[PS_WUE_MAX_LOCH_PER_RLC_NUM];/*���������ŵ�������Ҫ�߼��ŵ����ȼ�*/
}MACITF_DL_LOCH_MAPP_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_UL_LOCH_MAPP_STRU
 Э����  : 10.3.4.21    RB mapping info
 ASN.1���� : UL_LogicalChannelMappingList_r6
 �ṹ˵��  : �����߼��ŵ��봫���ŵ���ӳ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucUlPerRlcLochCnt;  /* [1,2] */
    MACITF_UL_PER_LOCH_MAPP_CHOICE_STRU astUlLochInfo[PS_WUE_MAX_LOCH_PER_RLC_NUM];
}MACITF_UL_LOCH_MAPP_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_RB_MAPP_STRU
 Э����  : 10.3.4.21    RB mapping info
 ASN.1���� : RB_MappingOption_r6
 �ṹ˵��  : ���У������߼��ŵ��봫���ŵ���ӳ��
*****************************************************************************/
typedef struct
{
    MACITF_UL_LOCH_MAPP_STRU            stUlLochMapp;       /* �����߼��ŵ���Ϣ */
    MACITF_DL_LOCH_MAPP_STRU            stDlLochMapp;       /* �����߼��ŵ���Ϣ */
}MACITF_RB_MAPP_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_RB_MAPP_INFO_STRU
 Э����  : 10.3.4.21    RB mapping info
 ASN.1���� : RB_MappingInfo
 �ṹ˵��  : �߼��ŵ��봫���ŵ���ӳ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucRbId;             /* RB ID */
    WUE_CN_DOMAIN_TYPE_ENUM_UINT8       enCnDomain;         /* ���ڼ���,���������RB������:WUE_CN_DOMAIN_TYPE_BUTT */
    WUE_TRAFFIC_TYPE_ENUM_UINT8         enTrafficType;      /* ��enCnDomain = WUE_CS_DOMAINʱ��Ч����������AMR��CSDҵ�� */
    MACITF_RB_MAPP_STRU                 stRbMapp;
}MACITF_RB_MAPP_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_RB_MAPPING_INFO_STRU
 Э����  : 10.3.4.24 Signalling RB information to setup
             10.3.4.20 RB information to setup
             10.3.4.19 RB information to release
 ASN.1���� : RB_InformationReconfig_r6
             RB_InformationAffected_r6
             SRB_InformationSetup
             RB_InformationSetup
 �ṹ˵��  : �������޸ģ��ͷţ��߼��ŵ��봫���ŵ���ӳ����Ϣ��
             WASÿ��ʹ��ȫ����������MAC��MACֻ��Ҫ�Ը��������������Ĳ�����飬
             ����Ҫ��ǰһ��������У�顣
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucRbCnt;            /* 0��ʾ��ѡ�� */
    MACITF_RB_MAPP_INFO_STRU            astRbInfoSetup[PS_WUE_MAX_RB_NUM];/* UU_MAX_LCH-->PS_WUE_MAX_RB_NUM */
}MACITF_RB_MAPP_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_TB_CNT_INFO_STRU
 Э����  : 10.3.5.2a  Additional Dynamic Transport Format Information for CCCH
             Dynamic Transport Format Information
 ASN.1���� : NumberOfTransportBlocks
 �ṹ˵��  : ÿ��RLCSIZE��Ӧ��TB CNT��Ϣ
             2> consider the first instance of the parameter Number of TBs
             and TTI List within the Dynamic transport format information to
             correspond to transport format 0 for this transport channel,
             the second to transport format 1 and so on;
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucTfi;              /* �����ʽָʾ */
    VOS_UINT16                          usTbCnt;            /*[0��512],TB��Ŀ,HI4131 ������32*/
} MACITF_TB_CNT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_TF_INFO_STRU
 Э����  : 10.3.5.2a  Additional Dynamic Transport Format Information for CCCH
             Dynamic Transport Format Information
 ASN.1���� : DedicatedDynamicTF_Info
             CommonDynamicTF_Info
 �ṹ˵��  : �����ʽ��Ϣ
             TF��Ϣ,TFI��Ӧ�ľ�������ṹ�������±꣬����TB�ĸ�������
*****************************************************************************/
typedef struct
{
    /* ����ר���ŵ���RLC size��ӳ����RLC PDU�Ĵ�С��
       ���ڹ����ŵ���RLC size��ӳ��ʵ�ʵ�TB��С��
       �ο�8.6.5.1  Transport Format Set��� */

    VOS_UINT16                          usRlcSize;          /* ��λ��Bit */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucTbCntInfoNum;     /* ÿ��RLC SIZE�µ�TF����*/
    MACITF_TB_CNT_INFO_STRU             astTbCntInfo[PS_WUE_MAX_TF_NUM]; /* Tb��Ŀ��0��512��*/
}MACITF_TF_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_DCH_TFI_LIST_STRU
 Э����  : 10.3.5.13    TFCS Explicit Configuration
 ASN.1���� : TFCS��Ӧ��TFI���б�
 �ṹ˵��  : DCH�Ĵ����ʽ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTfiNum;           /* ucTfiNum = TrchNum */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT8                           aucTfi[PS_WUE_MAX_DCH_NUM];/*�������±������˳����MACITF_UL_DCH_INFO_LIST_STRU��astUlDchInfo[PS_WUE_MAX_DCH_NUM]���±�����˳����ȫһ��*/
}MACITF_DCH_TFI_LIST_STRU;


/*****************************************************************************
 �ṹ��    : MACITF_UL_DCH_TFC_INFO_STRU
 Э����  : 10.3.5.13    TFCS Explicit Configuration
 ASN.1���� : TFCS
 �ṹ˵��  : ����DCH�Ĵ����ʽ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCtfc;             /* ���ܵ�BIT��Χ��2,4,6,8,12,16,24 BIT */
    PS_BOOL_ENUM_UINT8                  enTfcMinSetInd;     /* Ԥ���ӿڣ�Ŀǰ��ʹ�ñ�־��TFC�Ƿ�������С����minimum set of TFC��Ȼ����set of valid TFCs����ΪMAC TFCѡ���ݲ����ǹ������أ������С�������ݲ���Ҫʹ�ã�RRC����MAC�Ľӿ��д���enTfcMinSetInd�������Ժ���չʵ���� */
    PS_BOOL_ENUM_UINT8                  enTfcValidInd;      /*��TFC�Ƿ���Ч��ǣ�������ܻ�ɾ��ĳ��TFC����ʱ�ñ����ΪPS_FALSE*/
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
    MACITF_DCH_TFI_LIST_STRU            stTfiList;
} MACITF_UL_DCH_TFC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_UL_DCH_TFCS_STRU
 Э����  : 10.3.5.13    TFCS Explicit Configuration
 ASN.1���� : TFCS
 �ṹ˵��  : ����DCH�Ĵ����ʽ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
    VOS_UINT16                          usUlTfcCnt;         /* UL TFC���� */
    MACITF_UL_DCH_TFC_INFO_STRU         astUlTfc[PS_WUE_MAX_UL_TFC_NUM]; /*�����±����TFCI*/
}MACITF_UL_DCH_TFCS_STRU;

typedef struct
{
    VOS_UINT16                          usTfcSubSetCnt;     /* ultfc cnt is less than dl tfc */                                                         /* TFC����                                  */
    VOS_UINT16                          ausTfcSubSetIdx[PS_WUE_MAX_TFC_SUB_NUM];/* [0...MAX_TFC_SUB],Э����1024,���Զ���UINT16������չ�������TFCI
                                                                                   ������Ԫ�ص�ֵ��Ӧ����astUlTfc[PS_WUE_MAX_UL_TFC_NUM]���±꣬����TFCI*/
}MACITF_UL_DCH_TFC_SUBSET_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_UL_DCH_COMM_INFO_STRU
 Э����  : 10.3.5.13    TFCS Explicit Configuration
 ASN.1���� : TFCS
 �ṹ˵��  : ����DCH�Ĵ����ʽ���
*****************************************************************************/
typedef struct
{
    MACITF_UL_DCH_TFCS_STRU             stUlTfcs;
    MACITF_UL_DCH_TFC_SUBSET_STRU       stUlTfcsSubset;
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}MACITF_UL_DCH_COMM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_RACH_TFC_INFO_STRU
 Э����  : 10.3.6.55    PRACH system information list
 ASN.1���� : PRACH_SystemInformation
             rach_TFCS  TFCS
 �ṹ˵��  : ���й����ŵ��Ĵ����ʽ���
*****************************************************************************/
typedef struct
{
    /* ���ܵ�BIT��Χ��2,4,6,8,12,16,24 BIT */
    VOS_UINT32                          ulCtfc;
    VOS_UINT8                           ucTfi;              /* [0,31] */
    PS_BOOL_ENUM_UINT8                  enTfcMinSetInd;     /* Ԥ���ӿڣ�Ŀǰ��ʹ�ñ�־��TFC�Ƿ�������С����minimum set of TFC��Ȼ����set of valid TFCs����ΪMAC TFCѡ���ݲ����ǹ������أ������С�������ݲ���Ҫʹ�ã�RRC����MAC�Ľӿ��д���enTfcMinSetInd�������Ժ���չʵ���� */
    VOS_INT8                            cPwrOffsetPpM;      /* ����4121�ӿڣ������������IE��MAC�ӿڣ�INTEGER(-5..10)  OPTIONAL */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
}MACITF_RACH_TFC_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucTfi;              /* [0,31] */
    VOS_INT8                            cPwrOffsetPpM;      /* ����4121�ӿڣ������������IE��MAC�ӿڣ�INTEGER(-5..10)  OPTIONAL */
}MACITF_RACH_CCCH_TFC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_RACH_COMM_INFO_STRU
 Э����  : 10.3.6.55    PRACH system information list
 ASN.1���� : PRACH_SystemInformation
             rach_TFCS
 �ṹ˵��  : ���й����ŵ��Ĵ����ʽ��ϼ�
             ��ӦRACH��һ��PRACH��Ӧһ��RACH�����Բ���ҪTRCH ID��
             TFC�ĸ�������TF�ĸ���
*****************************************************************************/
typedef struct
{
    /*  1>  if the IE "Additional Dynamic Transport Format Information for CCCH"    */
    /*      is included for the selected PRACH:                                     */
    /*  2>  use this transport format for transmission of the CCCH.                 */
    /*  1>  else:                                                                   */
    /*  2>  use the first instance of the list of transport formats as in the       */
    /*      IE "RACH TFS" for the used RACH received in the IE                      */
    /*      "PRACH system information list" when using the CCCH.                    */
    PS_BOOL_ENUM_UINT8                  enAddCcchTfcExist;              /* stCcchTfc�Ƿ���� */
    MACITF_RACH_CCCH_TFC_INFO_STRU      stCcchTfc;                      /* AdditionalPRACH_TF_and_TFCS_CCCH_IEsʱ���ã�������������� */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */

    VOS_UINT16                          usUlTfcCnt;                     /* UL TFC���� */
    MACITF_RACH_TFC_INFO_STRU           astRachTfc[PS_WUE_CAP_MAX_TF_UL];   /* ��AdditionalPRACH��TFC���� */
}MACITF_RACH_COMM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_REF_E_TFCI_STRU
 Э����  : 10.3.6.99    E-DPDCH Info
             E-DCH minimum set E-TFCI
 ASN.1���� : E_DPDCH_Reference_E_TFCI
 �ṹ˵��  : EDCH��TFCI
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRefETfci;         /* [0,127] */
    VOS_UINT8                           ucRefETfciPo;       /* [0,31] */
}MACITF_REF_E_TFCI_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_EDCH_TFCS_STRU
 Э����  : 10.3.6.99    E-DPDCH Info
 ASN.1���� : E_DPDCH_Info
 �ṹ˵��  : EDCH��TFCS
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucETfciTblIdx;     /* 0:E-DCH Transport Block Size Table 0;1:Table 1 */
    VOS_UINT8                           ucMinSetETfci;     /* [0,127]���������δ���ã�����PS_NULL_UINT8����ʾ��Ч */
    /* ASN.1 �ı� : E_DPDCH_Reference_E_TFCIList */
    VOS_UINT8                           ucRefETfciCnt;     /* [0,8],0��ʾ��ѡ�� */
    MACITF_REF_E_TFCI_STRU              astRefETfci[PS_WUE_MAX_REF_E_TFCI_NUM];
}MACITF_EDCH_TFCS_STRU;

/* MAC_D_CONFIG_REQ �� MAC_C_CONFIG_REQ ����ṹ ����L2 ST����ʹ�ã�������ʵ�ʽӿ��� */
/*========================*/            /* RRC_MAC_D_CONFIG_REDUCE_REQ_STRU */
typedef struct
{
    VOS_UINT8                           ucTfi;
    VOS_UINT8                           ucRlcSizeIdx;
    VOS_UINT16                          usTbCnt;
}MACITF_TF_INFO_REDUCE_STRU;


/*****************************************************************************
 �ṹ��    : MACITF_TRCH_INFO_STRU
 Э����  : 10.3.5.2    Added or Reconfigured UL TrCH information
 ASN.1���� : CommonDynamicTF_Info
             DedicatedTransChTFS
 �ṹ˵��  : ���д����ŵ������ʽ�������ŵ���ר���ŵ�ͨ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTrchId;                           /* [PS_WUE_MIN_TRCH_ID,PS_WUE_MAX_TRCH_ID] */
    MACITF_TTI_ENUM_UINT8               enTti;                              /* ��λ10ms,����ʵ��ȡֵ����MAC */
    MACITF_CRC_SIZE_ENUM_UINT8          enCrcSize;                          /* CRC bit����: 0��8��12��16��24��TEST LOOP MODE2��TM RLCʱ�� */

    VOS_UINT8                           ucRlcSizeNum;                       /*[0,PS_WUE_MAX_TF_NUM],�ô����ŵ�RLC SIZE�ĸ��� */
    VOS_UINT16                          astRlcSize[PS_WUE_MAX_TF_NUM];      /* ÿ��RLC SIZE�µ�TF��Ϣ,�����±��Ӧһ��RLC SIZE������ */
    VOS_UINT8                           ucTfNum;                            /*[0,PS_WUE_CAP_MAX_TF_DL],�ô����ŵ�TF�ĸ��� */
    VOS_UINT8                           aucRsv[3];
    MACITF_TF_INFO_REDUCE_STRU          astTfs[PS_WUE_CAP_MAX_TF_DL];       /* ÿ�ִ����ŵ��µ�TF��Ϣ,�����±��Ӧһ��TF������ */
}MACITF_TRCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_UL_DCH_INFO_LIST_STRU
 Э����  : 10.3.5.2    Added or Reconfigured UL TrCH information
 ASN.1���� : UL_AddReconfTransChInformation
 �ṹ˵��  : �������е�ר�ô����ŵ������ʽ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucUlDchCnt;                     /* 0..PS_WUE_MAX_DCH_NUM - 1 */
    MACITF_TRCH_INFO_STRU               astUlDchInfo[PS_WUE_MAX_DCH_NUM];
}MACITF_UL_DCH_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_NON_SCHED_GRANT_STRU
 Э����  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1���� : transmissionGrantType
 �ṹ˵��  : �ǵ�����Ȩ
*****************************************************************************/
typedef struct
{
    /* ASN.1 : maxMAC_e_PDUContents */
    VOS_UINT16                          usEFlowMaxMacEPduSize;          /* [1...19982] bit */
    /* ASN.1 : ms2_NonSchedTransmGrantHARQAlloc */
    VOS_UINT8                           uc2msNonSchedGrantProcAlloc;    /* BITMAP,2ms TTI,�ǵ�����Ȩ�������ã�
                                                                           bitλֵΪ1ʱ������Ч
                                                                           Bit 0 corresponds to HARQ process 0, bit 1 corresponds to HARQ process 1...
                                                                           ���粻Я������ʾȫ�䣬Default value is: transmission in all HARQ processes is allowed. */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
}MACITF_NON_SCHED_GRANT_STRU ;

/*****************************************************************************
 �ṹ��    : MACITF_EFLOW_TRANS_GRANT_INFO_STRU
 Э����  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1���� : transmissionGrantType
             E_DPDCH_SchedulingTransmConfiguration
             ms2_SchedTransmGrantHARQAlloc
 �ṹ˵��  : E DCH��������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulChoice;

    #define      MACITF_NON_SCHED_GRANT_INFO_CHOSEN                0
    #define      MACITF_SCHED_GRANT_INFO_CHOSEN                    1

    union
    {
        MACITF_NON_SCHED_GRANT_STRU     stNonSchedGrant;           /*ֻ�е�ucEFlowTransGrantType��0ʱ���ýṹ����Ч��*/
        /* ASN.1 : E_DPDCH_SchedulingTransmConfiguration */
        VOS_UINT8                       uc2msSchedGrantProcAlloc;  /*BITMAP,2ms TTI,������Ȩ��������,��MAC-d��������
                                                                     ֻ����BITλȡֵΪ1�Ľ����Ϸ���,Bit0��Ӧ����0��Bit1��Ӧ����1���Դ�����...
                                                                     ���粻Я����ʾȫѡ��Default value is: transmission in all HARQ processes is allowed.*/
    }u;
}MACITF_EFLOW_TRANS_GRANT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_EDCH_FLOW_STRU
 Э����  : 10.3.5.1b    Added or reconfigured E-DCH MAC-d flow
 ASN.1���� : E_DCH_AddReconf_MAC_d_Flow
 �ṹ˵��  : E DCH��������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEFlowId;                  /* [0,7] */
    VOS_UINT8                           ucEFlowPwrOffset;           /* [0,6],dB ������ʱ������ܲ�Я��������WAS�̶����ø�MAC */
    VOS_UINT8                           ucEFlowMaxReTrans;          /* [0,15] ������ʱ������ܲ�Я��������WAS�̶����ø�MAC */
    VOS_UINT8                           ucEFlowMuxlist;             /* BITMAP,Bit0��ӦMAC-d��0��Bit1��ӦMAC-d��1��
                                                                       �Դ����ƣ�BITֵΪ1������Ӧ��MAC-d�������뵱ǰMAC-d��������ͬһMAC-e PDU�з���;
                                                                       �������ȫ0����ʾû�и��� */
    MACITF_EFLOW_TRANS_GRANT_INFO_STRU  stEFlowTransGrantInfo;      /* Only allowed to be absent when already defined for this E-DCH MAC-d flow
                                                                       WASÿ�ζ����ø�MAC */
}MACITF_EDCH_FLOW_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_DL_CCH_INFO_STRU
 Э����  : 10.3.5.23    Transport Format Set
             Dynamic Transport Format Information
 ASN.1���� : FACH_PCH_Information
 �ṹ˵��  : ���й����ŵ������ʽ��
*****************************************************************************/
typedef struct
{
    MACITF_TRCH_TYPE_ENUM_UINT8         enTrchType;             /* FACH,PCH */
    PS_BOOL_ENUM_UINT8                  enCtchInd;              /* ctch_Indicator BOOLEAN */
    MACITF_TRCH_INFO_STRU               stDlCchInfo;            /* ÿ��TF����Ϣ */
}MACITF_DL_CCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_DL_CCH_INFO_LIST_STRU
 Э����  : 10.3.5.23    Transport Format Set
 ASN.1���� : FACH_PCH_InformationList CommonTransChTFS
 �ṹ˵��  : �������еĹ��������ŵ��Ĵ����ʽ��
             ÿ��SCCPCHֻ�ܳ���һ��PCH��������SCCPCH��ӳ����PCH��
             �����SCCPCH��Ϣ��Я��PICH INFO��ͬʱPCH��TFS����Ϊ
             MACITF_FACH_PCH_TFS_LIST_STRU�ĵ�һ��Ԫ�ء�
             �ο�25.304 8.1   Paging Channel selection
             25.331 10.3.6.72    Secondary CCPCH system information
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCctrchIndex;                          /* ����ϴ����ŵ����� */
    VOS_UINT8                           ucDlCchCnt;                      /* FACH��PCH���ŵ�����֮�� */
    MACITF_DL_CCH_INFO_STRU             astDlCchInfo[PS_WUE_MAX_FACH_PCH_NUM];  /* ÿ��FACH/PCH����Ϣ */
}MACITF_DL_CCH_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_DL_DCH_INFO_LIST_STRU
 Э����  : 10.3.5.1    Added or Reconfigured DL TrCH information
  ASN.1���� : DL_AddReconfTransChInfo2List
  �ṹ˵��  : ר���ŵ��Ĵ����ʽ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucDlDchCnt;                      /* DL DCH�� */
    MACITF_TRCH_INFO_STRU               astDlDchInfo[PS_WUE_MAX_DCH_NUM];  /* ÿ��DL DCH����Ϣ */
}MACITF_DL_DCH_INFO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_HS_PDU_SIZE_INFO_STRU
 Э����  : 10.3.5.1a    Added or reconfigured MAC-d flow
 ASN.1���� : MAC_d_PDU_SizeInfo_List
 �ṹ˵��  : MAC D PDU��С
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMacdPduSize;  /* [1,5000]bit */
    VOS_UINT8                           ucHsPduSizeIdx; /* [0,7] ,��ӦMAC-hs PDU HEADER�е�SID*/
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
}MACITF_HS_PDU_SIZE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_HS_QUEUE_INFO_STRU
 Э����  : 10.3.5.1a    Added or reconfigured MAC-d flow
 ASN.1���� : MAC_hs_AddReconfQueue
 �ṹ˵��  : HS�Ķ�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHsQueueId;    /* [0,7] */
    VOS_UINT8                           ucHsFlowId;     /* [0,7] */
    VOS_UINT16                          usT1;           /* Integer(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 140, 160, 200, 300, 400)ms */
    VOS_UINT8                           ucHsWinSize;    /* Integer(4, 6, 8, 12, 16, 24, 32) */


    VOS_UINT8                           ucMacdPduSizeCnt;/* 1..PS_WUE_MAX_MAC_D_PDU_SIZES_NUM */
    MACITF_HS_PDU_SIZE_INFO_STRU        astHsPduSizeInfo[PS_WUE_MAX_MAC_D_PDU_SIZES_NUM];
}MACITF_HS_QUEUE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_DCH_INFO_STRU
 Э����  : 10.3.5.1    Added or Reconfigured DL TrCH information
             10.3.5.2    Added or Reconfigured UL TrCH information
             10.3.5.4    Deleted DL TrCH information
             10.3.5.5    Deleted UL TrCH information
 ASN.1���� : UL_AddReconfTransChInfoList
             DL_AddReconfTransChInfo2List
             UL_DeletedTransChInfoList
             DL_DeletedTransChInfoList
 �ṹ˵��  : ר���ŵ��Ĵ����ʽ�������ɾ�������ŵ���
             WAS����ͬʱ����MACD����ӳ������������ŵ��ϵ��߼��ŵ�Ҳɾ����
             WASÿ��ʹ��ȫ����������MAC��MACֻ��Ҫ�Ը��������������Ĳ�����飬
             ����Ҫ��ǰһ��������У�顣
*****************************************************************************/
typedef struct
{
    MACITF_UL_DCH_INFO_LIST_STRU            stUlDchInfoList;
    MACITF_DL_DCH_INFO_LIST_STRU            stDlDchInfoList;
}MACITF_DCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_HS_DSCH_INFO_STRU
 Э����  : 10.3.6.23a    Downlink HS-PDSCH Information
 ASN.1���� : HSDSCH_Info
             DL_DeletedTransChInfoList_r5
 �ṹ˵��  : HS DSCH����Ϣ
             25.321 11.6.1.1    Scheduler
             Each MAC-d flow contains HS-DSCH MAC-d PDUs for one or more priority queues.
             25.331 10.3.5.1a    Added or reconfigured MAC-d flow
             The MAC-hs queue ID is unique across all MAC-d flows.
             ����һ��FLOW���԰������QUEUE������һ��QUEUE�������ڶ��FLOW��
             �������ͨ��DL-DeletedTransChInfoList_r5����һ��FLOW��ɾ����
             WAS��������Ҫ�ͷŵ�QUEUE��ͨ���ͷ�QUEUE�ͷ�MAC��
             �������������WAS����ͬʱ����MACD����ӳ����߼��ŵ�Ҳɾ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucMacHsQueueCnt;       /* [1,PS_WUE_MAX_QUEUE_NUM] */
    MACITF_HS_QUEUE_INFO_STRU           astHsQueueInfo[PS_WUE_MAX_QUEUE_NUM];
}MACITF_HS_DSCH_INFO_STRU;


/*****************************************************************************
 �ṹ��    : MACITF_CCTRCH_INFO_STRU
 Э����  :
 ASN.1���� : SysInfoType5
 �ṹ˵��  : ����ϴ����ŵ��б�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCnt;                                  /* ����ϴ����ŵ��� */
    VOS_UINT8                           aucReserve1[1];                         /* 4�ֽڶ��룬���� */
    MACITF_DL_CCH_INFO_LIST_STRU        stDlCchInfoList[PS_WUE_MAX_SCCPCH_CCTRCH_NUM];  /*  */
}MACITF_CCTRCH_INFO_STRU;


/*****************************************************************************
 �ṹ��    : MACITF_CCH_INFO_STRU
 Э����  :
 ASN.1���� : SysInfoType5
 �ṹ˵��  : ���������ŵ��Ĵ����ʽ��
*****************************************************************************/
typedef struct
{
    MACITF_TRCH_INFO_STRU               stRachInfo;       /* RRCȫ���� */
    MACITF_CCTRCH_INFO_STRU             stCctrchInfo;  /* RRCȫ���� */
}MACITF_CCH_INFO_STRU;


/* Э���� : 10.3.7.68 Traffic volume measurement  */
/* ASN.1 �ı� : TrafficVolumeReportCriteria */
typedef struct
{
    #define     MACITF_TRAF_VOL_RPT_CRTR_CHOSEN         0
    #define     MACITF_PERIOD_RPT_CRTR_CHOSEN           1
    #define     MACITF_NO_RPT_CHOSEN                    2

    VOS_UINT32                          ulChoice;           /* �����ı���ģʽ:���ڻ��¼�  */
    union
    {
        MACITF_TRAF_VOL_RPT_CRTR_STRU   stTrafVolRptCrtr;   /* �¼���������Ĳ��� */
        MACITF_PERIOD_RPT_CRTR_STRU     stPeriodRptCrtr;    /* ���ڱ���Ĳ��� */
        PS_NULL_STRU                    stNoRpt;            /* MAC�������ϱ�RRC�������,�ݶ�����8000ms*/
    }u;
}MACITF_TRAF_MEAS_RPT_CRTR_CHOICE_STRU;


/*****************************************************************************
 �ṹ��    : MACITF_TRAF_MEAS_RSLT_CHOICE_STRU
 Э����  : 14.4.2    Traffic Volume reporting triggers
 ASN.1���� : TrafficVolumeMeasuredResults
 �ṹ˵��  : MAC�ϱ��������
*****************************************************************************/
typedef  struct
{
    #define     MACITF_EVENT_RPT_RSLT_CHOSEN            0
    #define     MACITF_PERIOD_RPT_RSLT_CHOSEN           1
    VOS_UINT32                          ulRptTypeChoice;     /* �����ģʽ:���ڻ��¼����� */

    union
    {
        MACITF_EVENT_RPT_RSLT_STRU      stEvtRptRslt;       /* �¼������� */
        MACITF_MEAS_RSLT_STRU           stPeriodRptRslt;    /* ���ڱ����� */
    }u;

}MACITF_TRAF_MEAS_RSLT_CHOICE_STRU;


/*****************************************************************************
 �ṹ��    : MACITF_UE_ID_INFO_STRU
 Э����  :
 ASN.1���� : U_RNTI
             C_RNTI
 �ṹ˵��  : MAC Cʹ�õ�UE ID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpURnti          : 1;    /* URNTI��CRNTI����ͬʱ���� */
    VOS_UINT32                          bitOpCRnti          : 1;
    VOS_UINT32                          bitSpare            : 30;

    VOS_UINT32                          ulURnti;                    /* 32 bit */
    VOS_UINT16                          usCRnti;                    /* 16 bit */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}MACITF_UE_ID_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_HSUPA_INFO_STRU
 Э����  : 10.3.6.99    E-DPDCH Info
                        Scheduling Information Configuration
 ASN.1���� : E_DPDCH_SchedulingInfoConfiguration
 �ṹ˵��  : ������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usNoGrantPeriodic;  /* ��λms, (everyEDCHTTI = 0xffff,4,10,20,50,100,200,500,1000),Default value is "no report"��0��ʾ */
    VOS_UINT16                          usGrantPeriodic;    /* ��λms, (everyEDCHTTI = 0xffff,4,10,20,50,100,200,500,1000),Default value is "no report"��0��ʾ */
    VOS_UINT8                           ucSIPowOffset;      /* [0,6] */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
}MACITF_SCHED_INFO_CONFIG_STRU;

/*******************************************************************************
 �ṹ��    : RRC_MAC_D_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ϢRRC_MAC_C_CONFIG_REQ�Ľṹ��
             ����MAC Cʵ�壬MACʵ���ϰ������������ŵ�ӳ�䣬�Լ�CCCH,CTCH���߼��ŵ�ӳ�����ã�
             DTCH,DCCH���߼��ŵ�ӳ���������MAC D�У�ͨ��MAC D��MAC C��ӳ�������
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */

    VOS_UINT32                          bitTrchInfo         : 1;                /* �Ƿ����TRCH INFO */
    VOS_UINT32                          bitRachTfcs         : 1;                /* �Ƿ����tfcs */
    VOS_UINT32                          bitSpare            :30;
    VOS_INT16                           sActTime;           /*[0,255],���ܼ���ʱ��CFN,PS_NEG_ONE��ʾ�������� */

    MACITF_CCH_INFO_STRU                stTrchInfo;         /* �����ŵ���ز���(TFS) */

    MACITF_RACH_COMM_INFO_STRU          stRachTfcs;         /* RACH��TFC��Ϣ*/

    MACITF_UE_ID_INFO_STRU              stUeIdInfo;         /* UE ID��ز��� */

    MACITF_RACH_ACCESS_INFO_STRU        stRachAcsInfo;      /* RACH ������ز��� */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_MAC_C_CONFIG_REQ_STRU;

/*******************************************************************************
 �ṹ��    : RRC_MAC_C_CONFIG_REQ_MNTN_COMM_PARAM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ϢRRC_MAC_C_CONFIG_REQ�Ľṹ��
             ��ά�ɲ���Ϣ�ṹPART1,��CCTRCH����������
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */

    VOS_INT16                           sActTime;           /*[0,255],���ܼ���ʱ��CFN,PS_NEG_ONE��ʾ�������� */
    VOS_UINT8                           ucCctrchCnt;        /* ����ϴ����ŵ��� */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */

    MACITF_TRCH_INFO_STRU               stRachInfo;         /* RRCȫ���� */
    MACITF_RACH_COMM_INFO_STRU          stRachTfcs;         /* RACH��TFC��Ϣ*/
    MACITF_UE_ID_INFO_STRU              stUeIdInfo;         /* UE ID��ز��� */
    MACITF_RACH_ACCESS_INFO_STRU        stRachAcsInfo;      /* RACH ������ز��� */
    VOS_UINT8                           aucReserve2[2];     /* 4�ֽڶ��룬���� */
}RRC_MAC_C_CONFIG_REQ_MNTN_COMM_PARAM_STRU;


/*******************************************************************************
 �ṹ��    : RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH1_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ϢRRC_MAC_C_CONFIG_REQ�Ľṹ��
             ��ά�ɲ���Ϣ�ṹPART2,��һ��DLCCH����
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */

    MACITF_DL_CCH_INFO_LIST_STRU        stDlCchInfoList;   /*  */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH1_STRU;

/*******************************************************************************
 �ṹ��    : RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH2_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ϢRRC_MAC_C_CONFIG_REQ�Ľṹ��
             ��ά�ɲ���Ϣ�ṹPART2,�ڶ���DLCCH����
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */

    MACITF_DL_CCH_INFO_LIST_STRU        stDlCchInfoList;   /*  */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_MAC_C_CONFIG_REQ_MNTN_DLCCH2_STRU;


/*******************************************************************************
 �ṹ��    : MAC_RRC_C_CONFIG_CNF
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ϢRRC_MAC_C_CONFIG_REQ����Ӧ��Ϣ
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */
    MACITF_RSLT_ENUM_UINT32             enRslt;
}MAC_RRC_C_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_UL_SCHED_INFO_STRU
 Э����  : 10.3.6.99    E-DPDCH Info
                        Scheduling Information Configuration
             10.3.6.98    E-DPCCH Info
 ASN.1���� : E_DPCCH_Info
             E_DPDCH_SchedulingInfoConfiguration
 �ṹ˵��  : MAC���е�����Ϣ
*****************************************************************************/
typedef struct
{
    /* E_DPCCH_Info�а���HappyBit_DelayCondition */
    VOS_UINT16                          usHappyBitDelayCond;/* (2ms, 10ms,20ms,50ms, 100ms, 200ms, 500ms, 1000ms) */
    /* E_DPDCH_SchedulingInfoConfiguration */
    MACITF_SCHED_INFO_CONFIG_STRU       stSchedInfoConfig;
}MACITF_UL_SCHED_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_MAC_D_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ϢRRC_MAC_D_CONFIG_REQ�Ľṹ��
             ����MAC Dʵ�壬DTCH,DCCH���߼��ŵ�ӳ���������MAC D�У�
             DCH��TRCHӳ��������MAC D�У�
             HS-DSCH,E DCH�Ĵ����ŵ�ӳ��ֱ�������MAC HS,MAC E��
             RACH,FACH��ӳ��������MAC C�У�ͨ��MAC D��MAC C�����߼��ŵ��봫���ŵ���ӳ�䡣
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */

    VOS_INT16                           sActTime;           /*[0,255],���ܼ���ʱ��CFN,PS_NEG_ONE��ʾ�������� */
    VOS_INT8                            cMaxUeTxPwr;        /* [-50��33],������·����书��= min(Maximum allowed UL TX Power=�������õ������, PMAX =UE������ʹ��),dbm */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */

    VOS_UINT32                          bitOpTrchInfo       : 1;    /* 1:stTrchInfo���ڣ�    0:������,��CELL_PCH/URA_PCH��CELL_FACH̬����MAC_Dʱ����Ҫ��bitOpTrchInfo��Ϊ0����CELL_DCH״̬�£��������ר�ô����ŵ�ֻ��E-DCH������ר�������ŵ�ֻ��F-DPCHʱ��Ҳ��Ҫ��bitOpTrchInfo��Ϊ0 */
    VOS_UINT32                          bitOpUlTrchTfcs     : 1;    /* 1:bitOpUlTrchTfcs���ڣ�0:������,��CELL_PCH/URA_PCH��CELL_FACH̬����MAC_Dʱ����Ҫ��bitOpUlTrchTfcs��Ϊ0����CELL_DCH״̬�£��������ר�ô����ŵ�ֻ��E-DCH��Ҳ��Ҫ��bitOpUlTrchTfcs��Ϊ0 */
    VOS_UINT32                          bitSpare            : 30;

    MACITF_RB_MAPP_INFO_LIST_STRU       stRbMappInfoList;   /* RBӳ����ز��� */

    MACITF_DCH_INFO_STRU                stTrchInfo;         /* �����ŵ���ز���(TFS) */

    MACITF_UL_DCH_COMM_INFO_STRU        stUlTrchTfcs;       /* ����DCH��TFC��Ϣ*/

}RRC_MAC_D_CONFIG_REQ_STRU;


/* ��ϢMAC_RRC_D_CONFIG_CNF�Ľṹ�� */
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_D_CONFIG_CNF_STRU;


/*******************************************************************************
 �ṹ��    : MACITF_MAC_E_VIRTUAL_LOCH_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����MAC_E�ϸ��õ��߼��ŵ�����
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLochId;                               /* ��Χ:[1..15],�����߼��ŵ��ı�ʶ������Ҫ֪��RB ID����ΪE-DCH����Ҫ����ҵ���������ϱ� */
    VOS_UINT8                           ucLochLabel;                            /* ��Χ:[2..65],MAC��RLC���ڲ�ͨ��ֻʹ��ucLochLabel,�����Ҫ����ID��Label���ӳ���ϵ */
    VOS_UINT8                           ucEFlowId;                              /* [0,7] */
    MACITF_EDCH_FLOW_TYPE_ENUM_UINT8    enEdchMacdFlowType;                     /* MAC-d�����: ������, �ǵ����� */
    MACITF_RLC_PDU_FIXED_SIZE_STRU      stFixedSize;                            /* ��enRlcPduSizeTypeΪfix sizeʱ, ��Ч */
    MACITF_LOCH_DATA_TYPE_ENUM_UINT8    enLochDataType;                         /* ָʾ��LOCH��Ӧ��RB���������� */
    VOS_UINT8                           aucReserve[3];
} MACITF_MAC_E_VIRTUAL_LOCH_INFO;

/*******************************************************************************
 �ṹ��    : RRC_MAC_E_VIRTUAL_CONFIG_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����MAC_E����ʵ�����
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */
    VOS_INT16                           sActTime;           /* [0,255],���ܼ���ʱ��CFN,PS_NEG_ONE��ʾ�������� */
    MACITF_EDCH_TTI_ENUM_UINT16         enEDCHTTI;          /* Edch TTI */
    PS_BOOL_ENUM_UINT8                  enFlushVBO;         /* �Ƿ���Ҫ���VirtualBO��־��PS_TRUE: �����PS_FALSE: �����*/
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           ucLochCnt;          /* ӳ�䵽E-DCH�ϵ��߼��ŵ����� */
    MACITF_MAC_E_VIRTUAL_LOCH_INFO      astVirtualLochInfo[PS_WUE_MAX_E_DCH_LOCH_NUM]; /* VIRTUAL MAC_e/esʵ���߼��ŵ���Ϣ */
} RRC_MAC_E_VIRTUAL_CONFIG_REQ_STRU;

typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_E_VIRTUAL_CONFIG_CNF_STRU;


/*******************************************************************************
 �ṹ��    : RRC_MAC_I_VIRTUAL_CONFIG_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����MAC_I����ʵ�����
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLochId;                               /* ��Χ:[1..15],�����߼��ŵ��ı�ʶ������Ҫ֪��RB ID,15��ʾCCCH */
    VOS_UINT8                           ucLochLabel;                            /* ��Χ:[0..65],MAC��RLC���ڲ�ͨ��ֻʹ��ucLochLabel,�����Ҫ����ID��Label���ӳ���ϵ, CCCH����0 */
    VOS_UINT8                           ucEFlowId;                              /* [0,7] */
    MACITF_EDCH_FLOW_TYPE_ENUM_UINT8    enEdchMacdFlowType;                     /* MAC-d�����: ������, �ǵ����� */
    MACITF_LOCH_DATA_TYPE_ENUM_UINT8    enLochDataType;                         /* ָʾ��LOCH��Ӧ��RB���������� */
    MACITF_RLC_PDU_SIZE_TYPE_ENUM_UINT8 enRlcPduSizeType;                       /* Fixed size or Flexible size */
    VOS_UINT8                           aucReserve[2];
    MACITF_RLC_PDU_FIXED_SIZE_STRU      stFixedSize;                            /* ��enRlcPduSizeTypeΪfix sizeʱ, ��Ч */
} MACITF_MAC_I_VIRTUAL_LOCH_INFO;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;                              /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;                                 /* ������ʶ */
    VOS_INT16                           sActTime;                               /* [0,255],���ܼ���ʱ��CFN,PS_NEG_ONE��ʾ�������� */
    MACITF_EDCH_TTI_ENUM_UINT16         enEDCHTTI;                              /* Edch TTI */
    PS_BOOL_ENUM_UINT8                  enFlushVBO;                             /* �Ƿ���Ҫ���VirtualBO��־��PS_TRUE: �����PS_FALSE: �����*/
    VOS_UINT8                           ucLochCnt;                              /* ӳ�䵽E-DCH�ϵ��߼��ŵ����� ������CCCHʱ, ucLochCnt����һ��Ϊ1 */
    VOS_UINT8                           aucReserve[2];
    MACITF_MAC_I_VIRTUAL_LOCH_INFO      astVirtualLochInfo[PS_WUE_MAX_E_DCH_LOCH_NUM]; /* VIRTUAL MAC_i/isʵ���߼��ŵ���Ϣ */
} RRC_MAC_I_VIRTUAL_CONFIG_REQ_STRU;

typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_I_VIRTUAL_CONFIG_CNF_STRU;

/*******************************************************************************
 �ṹ��    : RRC_MAC_HS_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ϢRRC_MAC_HS_CONFIG_REQ_STRU�Ľṹ��
             RRCÿ�ζ�ȫ����MSC_HS��Ϣ,�����������á�
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */

    VOS_INT16                           sActTime;           /*[0,255], CFN,PS_NEG_ONE��ʾ�������� */
    MACITF_HS_DSCH_INFO_STRU            stHsDschInfo;       /*HS-DSCH��Ϣ*/
}RRC_MAC_HS_CONFIG_REQ_STRU;

typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_HS_CONFIG_CNF_STRU;

/* ��ϢMAC_RRC_D_CONFIG_CNF�Ľṹ�� */
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_E_RESET_CNF_STRU;

/* ��ϢMAC_RRC_HS_RESET_CNF_STRU�Ľṹ�� */
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_HS_RESET_CNF_STRU;
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_CONFIG_CNF_STRU;

/*******************************************************************************
 �ṹ��    : RRC_MAC_RELEASE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ͷ�MACʵ��
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */
    MACITF_REL_MODE_ENUM_UINT8          enRelMode;          /* [0,1]���ͷ�ģʽ */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ���, ���� */
    VOS_INT16                           sActTime;           /* [0,255], �ͷ�MACʵ�弤��ʱ��CFN, PS_NEG_ONE��ʾ�������� */
}RRC_MAC_RELEASE_REQ_STRU;

typedef RRC_MAC_RELEASE_REQ_STRU RRC_MAC_QUIT_REQ_STRU ;
/* ��ϢMAC_RRC_RELEASE_CNF�Ľṹ�� */
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_RELEASE_CNF_STRU;

/*******************************************************************************
 �ṹ��    : RRC_MAC_TFC_CONTROL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TFC CONTROL ����ֻ����DCH
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpID;             /* ������ʶ*/
    VOS_INT16                           sActTime;           /*[0,255],���ܼ���ʱ��CFN,PS_NEG_ONE��ʾ�������� */
    VOS_UINT16                          usDuration;         /* ��λms,10,20,40,80,160,240,320,480,640,1280,1920,2560,5120;0��ʾһֱ����*/
    MACITF_UL_DCH_TFC_SUBSET_STRU       stTfcsSubSet;
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_MAC_TFC_CONTROL_REQ_STRU;

/*******************************************************************************
 �ṹ��    : MAC_RRC_TFC_CONTROL_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TFC CONTROL IND��MACָʾRRC��ʼʹ��TFC�Ӽ���
             ����duration��ʱ
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpID;             /* ������ʶ*/
    MACITF_TFC_CTRL_ENUM_UINT8          enTfcCtrlFlag;      /* TFC�Ӽ�ʹ����Ϣ:
                                                               MAC_TFC_CTL_BEGIN:����ʱ�䵽����ʼʹ��CURRENT TFCS;
                                                               MAC_TFC_CTL_END:  duration��ʱ��ʹ�ý������ָ�DEFAULT TFCS���� */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
}MAC_RRC_TFC_CONTROL_IND_STRU;


/* ��ϢRRC_MAC_CIPHER_CONFIG_REQ�Ľṹ�� */
typedef struct
{
    WUEL2L3_CIPHER_ALGO_ENUM_UINT8      enCipherAlgo;       /* [0,1],�����㷨 0�� MAC_CIPHER_UEA0��1��MAC_CIPHER_UEA1 */
    PS_BOOL_ENUM_UINT8                  enHfnChangFlag;     /* PS_FALSE��Hfn����Cfn�ĸ�λ���仯��PS_TRUE��Cfnÿ�η�����λ��Hfn��1 */
    PS_BOOL_ENUM_UINT8                  enHfnAddOneInd;     /* PS_TRUE��RRC��ʼ���õ�HFNҪ����1��MAC������ά��,��μ�25.331 (8.3.6.3)��(8.6.4.3)��(8.6.6.28)
                                                               increment the HFN component of the COUNT-C variable by one even if the "COUNT-C activation time" is set to zero*/
    VOS_UINT8                           ucCsRBCnt;          /* [0,4]��CS��RB����,���в�����SRB,ucCsRbCnt=0������CS����Ҫ���� */
    VOS_UINT8                           aucCsRBId[PS_WUE_MAX_CS_RB_NUM];/* [5,32],CS��ҵ��RB�б�*/
    VOS_UINT8                           aucCsCk[PS_WUE_CIPHER_KEY_LEN];/* 128bit,CS�������Կ*/
    VOS_INT16                           sCsActTimeCfn;      /* ����ʱ�䣬[0,255], -1��ʾ�������� */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
    VOS_UINT32                          ulCsRbCountCMsb;    /* ����TM RLC: ulCsRbCountCMsb(20BIT MSB) + 0000 + CFN(8BIT LSB)ֱ�������γɶ�ӦRB��CS��COUNT_C; */

    VOS_UINT8                           aucReserve2[2];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucPsRBCnt;          /* [0,2],PS��RB����,���в�����SRB�����ǵĹ�����ͬʱ֧��2��PS��ҵ��RB */
    VOS_UINT8                           aucPsRBId[PS_WUE_MAX_PS_RB_NUM];/* [5,32],PS��ҵ��RB�б� */
    VOS_UINT8                           aucPsCk[PS_WUE_CIPHER_KEY_LEN];/* 128bit,PS�������Կ */

    VOS_INT16                           sPsActTimeCfn;         /* ����ʱ�䣬[0,255], -1��ʾ��������*/
    PS_BOOL_ENUM_UINT8                  enActPrevCipherCfgFlag;/*�ڶ�ʱ��ʼ��Ӳ�л����߷�D2D���յ���rb setup��Ϣʱ,����mac����ʱ�������һ�μ��ܵļ���ʱ��û����ֱ�Ӹ��ǵ�һ�μ��ܲ���*/
    VOS_UINT8                           aucReserve3;           /* 4�ֽڶ��룬���� */
    VOS_UINT32                          ulPsRbCountCMsb;       /* ����TM RLC: ulPsRbCountCMsb(20BIT MSB) + 0000 + CFN(8BIT LSB)ֱ�������γɶ�ӦRB��PS��COUNT_C; */
}MACITF_CIPHER_CONFIG_INFO_STRU;

/*******************************************************************************
 �ṹ��    : RRC_MAC_CIPHER_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC��������
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpID;             /* ������ʶ*/
    MACITF_CIPHER_CONFIG_INFO_STRU      stCipherInfo;
}RRC_MAC_CIPHER_CONFIG_REQ_STRU;


/*******************************************************************************
 �ṹ��    : MAC_RRC_CIPHER_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC����������Ӧ
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpID;             /* ������ʶ */
    MACITF_RSLT_ENUM_UINT32             enRslt;
}MAC_RRC_CIPHER_CONFIG_CNF_STRU;


/*******************************************************************************
 �ṹ��    : MAC_RRC_CIPHER_ACTIVE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC���ܼ���ʱ��
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */
    WUE_CN_DOMAIN_TYPE_ENUM_UINT8       enCnDomainId;       /* [0,1],���ܼ���ĺ��������ʶ,MAC_CS_DOMAIN:CS��;MAC_PS_DOMAIN,PS�� */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
}MAC_RRC_CIPHER_ACTIVE_IND_STRU;

/*****************************************************************************
 �ṹ��    : MACITF_TRAF_MEAS_QUANT_CHOICE_STRU
 Э����  : 10.3.7.71 Traffic volume measurement quantity
             10.3.7.74    Traffic volume reporting quantity
 ASN.1���� : TrafficVolumeMeasQuantity ����Average��Variance���ϱ������CHOICE���ԡ�
             ���ͬʱ������Average��Variance��������һ���ġ�
             TrafficVolumeReportingQuantity ��ʾ�ϱ�ʲô���ݡ�
 �ṹ˵��  : ҵ������������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    PS_BOOL_ENUM_UINT8                  enRlcBufPayload;        /* �Ƿ���Ҫʹ��RlcBufPayload��ʽ�ϱ� */
    VOS_UINT16                          usAvgRlcBufPayload;     /* ��λms,0��ʾ��ʹ��AvgRlcBufPayload��ʽ�ϱ���(20, 40, ..260, by steps of 20) */
    VOS_UINT16                          usVarRlcBufPayload;     /* ��λms,0��ʾ��ʹ��VarRlcBufPayload��ʽ�ϱ���(20, 40, ..260, by steps of 20) */
}MACITF_TRAF_RPT_QUANT_STRU;

/*****************************************************************************
 �ṹ��    : RRC_MAC_MEAS_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� : TrafficVolumeMeasurement
 �ṹ˵��  : ҵ��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /* ��Ϣͷ  */   /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;          /* ��Ϣ��ʶ*/   /* _H2ASN_Skip */
    VOS_UINT16                              usOpId;             /* ������ʶ*/

    VOS_UINT8                               aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                               ucMeasId;           /* INTEGER(1..16) */
    MACITF_MEAS_OBJ_LIST_STRU               stMeasObjList;      /* ��Ҫ����TrCH���б� */
    MACITF_TRAF_RPT_QUANT_STRU              stMeasQuant;
    VOS_UINT8                               aucReserve2[2];     /* 4�ֽڶ��룬���� */
    MACITF_TRAF_MEAS_RPT_CRTR_CHOICE_STRU   stMeasRptCrtr;
}RRC_MAC_MEAS_CONFIG_REQ_STRU;


/*******************************************************************************
 �ṹ��    : MAC_RRC_MEAS_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MACҵ��������������Ӧ
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ  */       /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ��ʶ*/       /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ*/

    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
    /* Traffic Volume Indicator ָʾ ��ΪTRUEʱ:4A�¼��Ҳ���IDΪ4��
       BO��������ֵ��������������F_RB0̬�л���D̬������ΪFALSE.
       ��������Ŀ��: UE��Ҫͨ��"uplink data transmission"����CUʱ,
       �ж�һ��4a�Ƿ�����, ����֪����, ���������ܹ�ֱ����CU_CNFʱ�����㹻����Դ
       ��EDCH����ʱ���ڲ�ͨ��CU���л�״̬, ֱ����дFALSE */
    PS_BOOL_ENUM_UINT8                  enTrVolumeInd;
    VOS_UINT8                           ucMeasId;           /* ������ʶ */
    MACITF_RSLT_ENUM_UINT32             enRslt;
}MAC_RRC_MEAS_CONFIG_CNF_STRU;

/*******************************************************************************
 �ṹ��    : MAC_RRC_MEAS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ϱ�ҵ�����������
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ  */       /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��ϢID  */       /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;

    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucMeasId;           /* ������ʶ */
    MACITF_TRAF_MEAS_RSLT_CHOICE_STRU   stTrafMeasInd;

}MAC_RRC_MEAS_IND_STRU;


/*******************************************************************************
 �ṹ��    : RRC_MAC_MEAS_REL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ͷ�ҵ��������
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ  */       /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��ϢID  */       /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;

    VOS_UINT8                           ucMeasCnt;          /* ���� */
    VOS_UINT8                           aucMeasId[PS_WUE_MAX_NO_OF_MEAS_NUM];
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
}RRC_MAC_MEAS_REL_REQ_STRU;

/*******************************************************************************
 �ṹ��    : RRC_MAC_MEAS_REL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ͷ�ҵ����������Ӧ
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ  */       /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��ϢID  */       /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ  */

    MACITF_RSLT_ENUM_UINT32             enRslt;
}MAC_RRC_MEAS_REL_CNF_STRU;

/*******************************************************************************
 �ṹ��    : MAC_RRC_PCCH_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PCCH��Ϣ
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
    VOS_UINT32                          ulBitLen;           /* ��bitΪ��λ�����ݳ��� */
    VOS_UINT8                           aucData[4];         /* ���ݲ��֣���ǰ���ֽ�һ��������������Ϣ�ڴ�ռ� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}MAC_RRC_PCCH_DATA_IND_STRU;


/*******************************************************************************
 �ṹ��    : MAC_RRC_BCCH_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BCCH(system information change indication)
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
    VOS_UINT32                          ulBitLen;           /* ��bitΪ��λ�����ݳ��� */
    VOS_UINT8                           aucData[4];         /* ���ݲ��֣���ǰ���ֽ�һ��������������Ϣ�ڴ�ռ� */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}MAC_RRC_BCCH_DATA_IND_STRU;


/*******************************************************************************
 �ṹ��    : MAC_RRC_ACTIVE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC���û�λ���ͷż���ʱ��ָʾ
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */
    VOS_INT16                           sActTime;           /*[0,255],���ü���ʱ��CFN,PS_NEG_ONE��ʾ�������� */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}MAC_RRC_ACTIVE_IND_STRU;


/*******************************************************************************
 �ṹ��    : MAC_RRC_STATUS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RB0����������ϱ�
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
    MACITF_STATUS_ENUM_UINT32           enStatus;

}MAC_RRC_STATUS_IND_STRU;


/*******************************************************************************
 �ṹ��    : MAC_RRC_ERROR_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC�����쳣��ָʾRRC�ͷ�
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
    MACITF_RRC_ERR_CODE_ENUM_UINT32     enErrCode;          /* ��������ָʾ */
}MAC_RRC_ERROR_IND_STRU;

/*******************************************************************************
 �ṹ��    : RRC_MAC_HS_RESET_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RESET MAC HSʵ��
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */
    VOS_INT16                           sActTime;           /*[0,255], CFN,PS_NEG_ONE��ʾ�������� */

    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_MAC_HS_RESET_REQ_STRU;


/*****************************************************************************
 �ṹ��    : RRC_MAC_COMPRESS_MODE_TGPS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ĳ�� TGPS ��Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usTGPSI;                        /* TGPS��ʶ       */
    MACITF_TGPS_CFG_STATUS_ENUM_UINT16          enTGPSCfgStausFlag;             /* TGPS״̬��־   */
    VOS_INT16                                   sTGCFN;                         /* ��TGPS�ļ���ʱ��, [0,255],��TGPS״̬����CHANGED_ACTIVED, ����ʱ������Ϊ-1 */
    VOS_UINT16                                  usReserve1;
    VOS_UINT16                                  usTGPRC;                        /* TGPS������TGP������[0, 511]��0��ʾ������ */
    VOS_UINT16                                  usTGPL1;                        /* TGP�ĳ���ʱ�䣬��֡Ϊ��λ��[1,144] */
    VOS_UINT8                                   aucFrameTxSlots[PS_WUE_MAX_TGPL];   /* TGP��ÿ֡�ܷ��͵�ʱ϶�� */
}RRC_MAC_TGPS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_MAC_COMPRESS_MODE_CFG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ѹģ��Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;                          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                              usOpId;                             /* ������ʶ */
    VOS_INT16                               sTgpsRecfgCfn;                      /* ��һ��ѹģ����ȥ����ʱ��,[0,255],-1��ʾû����һ�ε�ѹģ���ã���ǰ����������Ч */
    VOS_UINT16                              usTGPSCnt;                          /* TGPS���� */
    RRC_MAC_TGPS_INFO_STRU                  astTGPSInfo[PS_WUE_MAX_TGPS_NUM];
}RRC_MAC_COMPRESS_MODE_CFG_REQ_STRU;

/* ��ϢRRC_MAC_COMPRESS_MODE_CFG_CNF_STRU�Ľṹ�� */
typedef MAC_RRC_C_CONFIG_CNF_STRU   RRC_MAC_COMPRESS_MODE_CFG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_MAC_COMPRESS_MODE_CFG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ѹģ��Ϣ
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                              usOpId;             /* ������ʶ */
    VOS_INT16                               sActTime;           /*[0,255],���ܼ���ʱ��CFN,PS_NEG_ONE��ʾ�������� */
    VOS_UINT16                              usTfcCnt;                                   /* UL TFCȫ��TFC���� */
    VOS_UINT8                               aucTfcTxSlots[PS_WUE_MAX_UL_TFC_NUM];       /* �����±����TFCI, Ԫ��ֵΪ��TFCÿ֡����������Ҫ��ʱ϶��,[0,16],16��ʾ��Чֵ��RRC����������16�������ó�16 */
}RRC_MAC_TFC_SLOT_CFG_REQ_STRU;

/* ��ϢRRC_MAC_TFC_SLOT_CFG_CNF_STRU�Ľṹ�� */
typedef MAC_RRC_C_CONFIG_CNF_STRU   RRC_MAC_TFC_SLOT_CFG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_MAC_STOP_UL_TX_REQ_STRU
 Э����  : ��
 ASN.1���� :
 �ṹ˵��  : Ϊ�˾�ȷ��������ֹͣ���͵�ʱ��, ���Ӵ���Ϣ. RRC���ͷ������ǰ
             ͨ������Ϣ֪ͨMAC�ڼ���ʱ�䵽��ʱֹͣ��RLCҪ��
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                              usOpId;             /* ������ʶ */
    VOS_INT16                               sActTime;           /*[0,255], ֹͣMACҪ������ʱ��CFN,PS_NEG_ONE��ʾ�������� */
    VOS_UINT8                               aucReserve1[2];     /* 4�ֽڶ���, ���� */
}RRC_MAC_STOP_UL_TX_REQ_STRU;

/* ��ϢMAC_RRC_STOP_UL_TX_CNF�Ľṹ�� */
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_STOP_UL_TX_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_MAC_CONTINUE_UL_TX_REQ_STRU
 Э����  : ��
 ASN.1���� :
 �ṹ˵��  : Ϊ�˾�ȷ��������ֹͣ���͵�ʱ��, ���Ӵ���Ϣ. RRC�յ�������ͬ��ָʾ��,
             ͨ��RRC_MAC_CONTINUE_UL_TX_REQ����Ϣ֪ͨMAC�����ָ���RLCҪ��
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                              usOpId;             /* ������ʶ */
}RRC_MAC_CONTINUE_UL_TX_REQ_STRU;

/* ��ϢMAC_RRC_CONTINUE_UL_TX_CNF�Ľṹ�� */
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_CONTINUE_UL_TX_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_MAC_TGPS_PRE_CHK_REQ_STRU
 Э����  : ��
 ASN.1���� :
 �ṹ˵��  : ѹģ������ǰ����ѹģ�����ĺϷ��Լ��
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                              usOpId;             /* ������ʶ */
    VOS_INT16                               sTgpsRecfgCfn;                      /* ��һ��ѹģ����ȥ����ʱ��,[0,255],-1��ʾû����һ�ε�ѹģ���ã���ǰ����������Ч */
    VOS_UINT8                               aucReserve1[1];
    VOS_UINT8                               ucTgpsCnt;                          /* ���������ѹģ���еĸ��� */
    RRC_MAC_TGPS_INFO_STRU                  astTgpsInfo[PS_WUE_MAX_TGPS_NUM];
}RRC_MAC_TGPS_PRE_CHK_REQ_STRU;


/*******************************************************************************
 �ṹ��    : MAC_RRC_TGPS_PRE_CHK_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ϢRRC_MAC_TGPS_PRE_CHK_REQ_STRU����Ӧ��Ϣ
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */
    MACITF_RSLT_ENUM_UINT32             enRslt;                                 /* �·�������Ч(�������ص�)ʱ������ʧ��(�������޼����TGPSʱ������ʧ��)���������سɹ� */
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT8                           ucOverLapCnt;                           /* �ص���ѹģ���и��� */
    VOS_UINT8                           aucTgpsi[PS_WUE_MAX_TGPS_NUM - 1];      /* �ص���ѹģ��ʶ�������������ص�ʱ������tgpsi�ϴ��һ�� */
}MAC_RRC_TGPS_PRE_CHK_CNF_STRU;

/*V3 R7_7C1 Start */
/*Add for MAC-ehs,Begin*/

typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_EHS_CONFIG_CNF_STRU;
typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_EHS_RESET_CNF_STRU;
typedef RRC_MAC_HS_RESET_REQ_STRU   RRC_MAC_EHS_RESET_REQ_STRU;

typedef struct
{
   VOS_UINT8                            ucLochLabel;        /* �߼��ŵ��ڲ�ʵ��ͳһ��ʶ��[0,[0,34*2-1]] */
   VOS_UINT8                            ucLochId;           /* �߼��ŵ�ID��[1,15]��0��ʾ��Ч,��PCCH��BCCHӳ�䵽HS-DSCHʱ��usLochId��ֵΪ1111 */
   VOS_UINT8                            ucEhsQueueId;       /*[0��8]����usLochֵΪ1111ʱ������û��Queue���������ʵ���ϣ���usHsQueueId��ֵ���8*/
   VOS_UINT8                            aucReserved[1];     /*���ֽڶ���*/
}MACITF_EHS_MAPPING_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucEhsQueueId;       /* [0,7] */
    VOS_UINT8                           ucEhsWinSize;       /* Integer(4, 6, 8, 12, 16, 24, 32,64,128) */
    VOS_UINT16                          usT1Len;            /* Integer(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 140, 160, 200, 300, 400)ms */
    VOS_UINT16                          usTresetLen;        /* Integer  ms */
    VOS_UINT8                           aucReserve1[2];
}MACITF_EHS_QUEUE_INFO_STRU;

typedef struct
{
    MACITF_RNTI_CFG_ENUM_UINT8              enHrntiFlag;                        /* ��ʶ��ǰH-RNTI����״̬*/

    MACITF_MAC_EHS_TSN_BIT_LEN_ENUM_UINT8   enTsnBitLen;                        /* DC+MIMOʱ, ����14bits, ��������6bits */
    VOS_UINT8                               aucReserve1[1];

    VOS_UINT8                               ucMappingCount;                     /* ӳ��count,MACITF_RNTI_CFG_COMM_HRNTI��ֻ����MAC_C,MAC_EHSʱ������������ø���Ϊ2��SRB0��SRB0,SRB1 ;
                                                                                   CELL_PCH/URA_PCHҲֻ����MAC_C,MAC_EHS
                                                                                   ������MAC_Dʱ���������õ�������RB��ӳ�䣬���DL E_CELLFACH�����RB0,���򲻰��� */
    MACITF_EHS_MAPPING_INFO_STRU            astMappingInfo[PS_WUE_MAX_LOCH_NUM];/* ���к�LOCH IDӳ���ϵ */

    VOS_UINT8                               aucReserve2[3];

    VOS_UINT8                               ucMacEhsQueueCnt;                       /* [1,PS_WUE_MAX_QUEUE_NUM] */
    MACITF_EHS_QUEUE_INFO_STRU              astEhsQueueInfo[PS_WUE_MAX_QUEUE_NUM];  /* PS_WUE_MAX_QUEUE_NUM is defined in WUeSpec.h */
}MACITF_EHS_HS_DSCH_INFO_STRU;

typedef struct
{
   VOS_MSG_HEADER                                           /* _H2ASN_Skip */
   RRC_MAC_MSG_TYPE_ENUM_UINT16         enMsgName;          /*Msg type*/        /* _H2ASN_Skip */
   VOS_UINT16                           usOpId;             /*operation id*/

   VOS_INT16                            sActTime;           /*[0,255],CFN,PS_NEG_ONE:��������*/
   VOS_UINT8                            aucRsv[2];
   MACITF_EHS_HS_DSCH_INFO_STRU         stEhsInfo;          /**/
}RRC_MAC_EHS_CONFIG_REQ_STRU;

/*Add for MAC-ehs, END*/

typedef struct
{
    VOS_UINT8                           ucTrchId;           /* [PS_WUE_MIN_TRCH_ID,PS_WUE_MAX_TRCH_ID] */
    MACITF_TTI_ENUM_UINT8               enTti;              /* ��λ10ms,����ʵ��ȡֵ����MAC */
    MACITF_CRC_SIZE_ENUM_UINT8          enCrcSize;          /* CRC bit����: 0��8��12��16��24��TEST LOOP MODE2��TM RLCʱ�� */
    VOS_UINT8                           ucRlcSizeNum;
    VOS_UINT16                          astRlcSize[PS_WUE_MAX_TF_NUM];
    VOS_UINT8                           ucTfNum;            /*[0,PS_WUE_MAX_TF_NUM],�ô����ŵ�RLC SIZE�ĸ��� */
    VOS_UINT8                           aucRsv[3];
    MACITF_TF_INFO_REDUCE_STRU          astTfs[PS_WUE_MAX_TF_NUM]; /* ÿ��RLC SIZE�µ�TF��Ϣ,�����±��Ӧһ��RLC SIZE������ */
}MACITF_TRCH_INFO_REDUCE_STRU;

typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucUlDchCnt;                     /* 0..PS_WUE_MAX_DCH_NUM - 1 */
    MACITF_TRCH_INFO_REDUCE_STRU        astUlDchInfo[PS_WUE_MAX_DCH_NUM];
}MACITF_UL_DCH_INFO_LIST_REDUCE_STRU;

typedef struct
{
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucDlDchCnt;                      /* DL DCH�� */
    MACITF_TRCH_INFO_REDUCE_STRU        astDlDchInfo[PS_WUE_MAX_DCH_NUM];  /* ÿ��DL DCH����Ϣ */
}MACITF_DL_DCH_INFO_LIST_REDUCE_STRU;


typedef struct
{
    MACITF_UL_DCH_INFO_LIST_REDUCE_STRU stUlDchInfoList;
    MACITF_DL_DCH_INFO_LIST_REDUCE_STRU stDlDchInfoList;
}MACITF_DCH_INFO_REDUCE_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */

    VOS_INT16                           sActTime;           /*[0,255],���ܼ���ʱ��CFN,PS_NEG_ONE��ʾ�������� */
    VOS_INT8                            cMaxUeTxPwr;        /* [-50��33],������·����书��= min(Maximum allowed UL TX Power=�������õ������, PMAX =UE������ʹ��),dbm */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */

    VOS_UINT32                          bitOpTrchInfo       : 1;    /* 1:stTrchInfo���ڣ�    0:������,��CELL_PCH/URA_PCH��CELL_FACH̬����MAC_Dʱ����Ҫ��bitOpTrchInfo��Ϊ0����CELL_DCH״̬�£��������ר�ô����ŵ�ֻ��E-DCH������ר�������ŵ�ֻ��F-DPCHʱ��Ҳ��Ҫ��bitOpTrchInfo��Ϊ0 */
    VOS_UINT32                          bitOpUlTrchTfcs     : 1;    /* 1:bitOpUlTrchTfcs���ڣ�0:������,��CELL_PCH/URA_PCH��CELL_FACH̬����MAC_Dʱ����Ҫ��bitOpUlTrchTfcs��Ϊ0����CELL_DCH״̬�£��������ר�ô����ŵ�ֻ��E-DCH��Ҳ��Ҫ��bitOpUlTrchTfcs��Ϊ0 */
    VOS_UINT32                          bitSpare            : 30;

    MACITF_RB_MAPP_INFO_LIST_STRU       stRbMappInfoList;   /* RBӳ����ز��� */

    MACITF_DCH_INFO_REDUCE_STRU         stTrchInfo;         /* �����ŵ���ز���(TFS) */

    MACITF_UL_DCH_COMM_INFO_STRU        stUlTrchTfcs;       /* ����DCH��TFC��Ϣ*/

}RRC_MAC_D_CONFIG_REDUCE_REQ_STRU;
/*========================*/            /* RRC_MAC_D_CONFIG_REDUCE_REQ_STRU end */


/*========================*/            /* RRC_MAC_C_CONFIG_REDUCE_REQ_STRU */
typedef struct
{
    MACITF_TRCH_TYPE_ENUM_UINT8         enTrchType;             /* FACH,PCH */
    PS_BOOL_ENUM_UINT8                  enCtchInd;              /* ctch_Indicator BOOLEAN */
    MACITF_TRCH_INFO_REDUCE_STRU        stDlCchInfo;            /* ÿ��TF����Ϣ */
}MACITF_DL_CCH_INFO_REDUCE_STRU;

typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucDlCchCnt;                      /* FACH��PCH���ŵ�����֮�� */
    MACITF_DL_CCH_INFO_REDUCE_STRU      astDlCchInfo[PS_WUE_MAX_FACH_PCH_NUM];  /* ÿ��FACH/PCH����Ϣ */
}MACITF_DL_CCH_INFO_LIST_REDUCE_STRU;

typedef struct
{
    VOS_UINT8                           ucCnt;                                  /* ����ϴ����ŵ��� */
    VOS_UINT8                           aucReserve1[1];                         /* 4�ֽڶ��룬���� */
    MACITF_DL_CCH_INFO_LIST_REDUCE_STRU stDlCchInfoList[PS_WUE_MAX_SCCPCH_CCTRCH_NUM];  /*  */
}MACITF_CCTRCH_INFO_REDUCE_STRU;

typedef struct
{
    MACITF_TRCH_INFO_REDUCE_STRU        stRachInfo;       /* RRCȫ���� */
    MACITF_CCTRCH_INFO_REDUCE_STRU      stCctrchInfo;     /* RRCȫ���� */
}MACITF_CCH_INFO_REDUCE_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */

    VOS_UINT32                          bitTrchInfo         : 1;                /* �Ƿ����TRCH INFO */
    VOS_UINT32                          bitRachTfcs         : 1;                /* �Ƿ����tfcs */
    VOS_UINT32                          bitSpare            :30;
    VOS_INT16                           sActTime;           /*[0,255],���ܼ���ʱ��CFN,PS_NEG_ONE��ʾ�������� */

    MACITF_CCH_INFO_REDUCE_STRU         stTrchInfo;         /* �����ŵ���ز���(TFS) */

    MACITF_RACH_COMM_INFO_STRU          stRachTfcs;         /* RACH��TFC��Ϣ*/

    MACITF_UE_ID_INFO_STRU              stUeIdInfo;         /* UE ID��ز��� */

    MACITF_RACH_ACCESS_INFO_STRU        stRachAcsInfo;      /* RACH ������ز��� */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_MAC_C_CONFIG_REDUCE_REQ_STRU;
/*========================*/            /* RRC_MAC_C_CONFIG_REDUCE_REQ_STRU end */

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */
    MACITF_RSLT_ENUM_UINT32             enRslt;
}WTTF_MEM_TEST_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgID;            /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */
}WTTF_MEM_TEST_REQ_STRU;
/* ����ṹ���� */

/* V3 R7_7C1 End */

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if 0                                                                           /*_H2ASN_Skip*/
enum MACITF_TRAF_MEAS_RPT_CRTR_TYPE_ENUM
{
    MACITF_TRAF_VOL_RPT_CRTR            = 0,                /* _H2ASN_MsgChoice MACITF_TRAF_VOL_RPT_CRTR_STRU */
    MACITF_PERIOD_RPT_CRTR              = 1,                /* _H2ASN_MsgChoice MACITF_PERIOD_RPT_CRTR_STRU */
    MACITF_NO_RPT                       = 2,                /* _H2ASN_MsgChoice PS_NULL_STRU */
    MACITF_TRAF_MEAS_RPT_CRTR_TYPE_BUTT
};
typedef VOS_UINT32  MACITF_TRAF_MEAS_RPT_CRTR_TYPE_ENUM_UINT32;

typedef struct
{
    MACITF_TRAF_MEAS_RPT_CRTR_TYPE_ENUM_UINT32  ulChoice;   /* _H2ASN_IeChoice_Export MACITF_TRAF_MEAS_RPT_CRTR_TYPE_ENUM_UINT32 */

    union                                                                       /* _H2ASN_Skip */
    {                                                                           /* _H2ASN_Skip */
        MACITF_TRAF_VOL_RPT_CRTR_STRU   stTrafVolRptCrtr;                       /* _H2ASN_Skip */
        MACITF_PERIOD_RPT_CRTR_STRU     stPeriodRptCrtr;                        /* _H2ASN_Skip */
        PS_NULL_STRU                    stNoRpt;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        MACITF_TRAF_MEAS_RPT_CRTR_TYPE_ENUM_UINT32
        ******************************************************************************************************/
    }u;                                                                         /* _H2ASN_Skip */
}MACITF_TRAF_MEAS_RPT_CRTR_STRU;
#endif                                                                          /*_H2ASN_Skip*/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgID;    /*_H2ASN_MsgChoice_Export RRC_MAC_MSG_TYPE_ENUM_UINT16*/

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RRC_MAC_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}RRC_MAC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    RRC_MAC_MSG_DATA                    stMsgData;
}RrcMacInterface_MSG;

/* V3 R7_7C1 Start */
enum MACITF_TRCH_ENCODE_TYPE_ENUM
{
    MACITF_TRCH_ENCODE_TYPE_CONV_HALF_RATE             = 0,
    MACITF_TRCH_ENCODE_TYPE_CONV_TRIPLE_RATE           = 1,
    MACITF_TRCH_ENCODE_TYPE_TURBO_CODING               = 2,
    MACITF_TRCH_ENCODE_TYPE_BUTT
};

typedef VOS_UINT16 MACITF_TRCH_ENCODE_TYPE_ENUM_UINT16;

typedef struct
{
    VOS_UINT8   ucBcRef;                                /*ȡֵ 0~15 */
    VOS_UINT8   ucBdRef;                                /*ȡֵ 0~15 */
    VOS_UINT8   ucTfcRefId;                             /*ȡֵ 0~3 */
    VOS_UINT8   aucReserve1[1];

}RRC_MAC_TFC_SIGNAL_STRU;

typedef struct
{
    VOS_UINT8   ucTfcRefId;
    VOS_UINT8   aucReserve1[3];
}RRC_MAC_TFC_COMPUTED_STRU;


typedef struct
{

    #define MACITF_SIGNAL_GAIN_FACTOR_CHOSEN              0                                       /*�߲�ָ�����������Ӽ��㷽ʽ*/
    #define MACITF_COMPUTED_GAIN_FACTOR_CHOSEN            1                                       /*����������������Ӽ��㷽ʽ*/

    VOS_UINT32                              ulChoice;
    union
    {
        RRC_MAC_TFC_SIGNAL_STRU             stTfcSignalInfo;
        RRC_MAC_TFC_COMPUTED_STRU           stTfcComputedInfo;
    }u;

}RRC_MAC_BCBD_TFC_STRU;


typedef struct
{
    VOS_UINT8                                    ucTrchId;           /* [PS_WUE_MIN_TRCH_ID,PS_WUE_MAX_TRCH_ID] */
    VOS_UINT8                                    aucReserved[3];     /* ���ֽڶ��� */
    VOS_UINT16                                   usRM;               /* 0..256 */
    MACITF_TRCH_ENCODE_TYPE_ENUM_UINT16          enCodeType;         /* 0..2 */


}RRC_MAC_BCBDREF_TRCH_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */

    VOS_INT16                           sActTime;           /*[0,255],-1��ʾ�������� */
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */

    VOS_UINT8                           ucTrchCnt;         /* 0..PS_WUE_MAX_DCH_NUM  */
    RRC_MAC_BCBDREF_TRCH_STRU           astTrchInfo[PS_WUE_MAX_DCH_NUM];


    VOS_UINT8                           aucReserve2[2];     /* 4�ֽڶ��룬���� */
    VOS_UINT16                          usTfcCnt;          /* 0..PS_WUE_MAX_UL_TFC_NUM  */
    RRC_MAC_BCBD_TFC_STRU               astBcBdTfcInfo[PS_WUE_MAX_UL_TFC_NUM];
}RRC_MAC_BCBD_CALCULATE_REQ_STRU;

typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_BCBD_CALCULATE_CNF_STRU;


/* V3 R7_7C1 BHS */
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */

    VOS_INT16                           sActTime;           /*[0,255],���ܼ���ʱ��CFN,PS_NEG_ONE��ʾ�������� */
    VOS_UINT8                           ucBhs;              /* Bhs��[5, 6, 8, 9, 12, 15, 19, 24, 30];*/
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */

}RRC_MAC_BHS_CALCULATE_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;             /* ������ʶ */
    MACITF_CIPHER_STATUS_ENUM_UINT16    enCipherSta;        /* ͬƵӲ�л�������ϵͳ�л�����Ҫ��MAC�ļ��ܴ���: 0: ֪ͨMAC����cipher��ز��� 1:֪ͨMAC���¼���������� */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */

}RRC_MAC_CIPHER_RESERVE_REQ_STRU;


/* DL E CELL PCH(��ר��H-RNTI)״̬��, MAC���յ����ݺ�֪ͨRRC */
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16         enMsgName;         /* Msg type */        /* _H2ASN_Skip */
    VOS_UINT16                           usOpId;            /* ������ʶ */
    VOS_UINT8                            aucRsv2[4];        /* ��չ */
}MAC_RRC_EHS_RX_DATA_IND_STRU;

typedef MAC_RRC_CIPHER_CONFIG_CNF_STRU MAC_RRC_CIPHER_RESERVE_CNF_STRU;

typedef MAC_RRC_C_CONFIG_CNF_STRU   MAC_RRC_BHS_CALCULATE_CNF_STRU;
/* V3 R7_7C1 End */

/* �������ASC��������ָʾ */
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRC_MAC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* Msg type */      /* _H2ASN_Skip */

    /* ucAscCnt = ucNumAsc+1,ucNumAsc�ķ�Χ0..7��ASC��ʵ��ȡֵi:0 <= i <= NumASC <= 7,��IDEL��PCH̬��RRC���õ�ucAscCnt=0 */
    VOS_UINT8                           ucAscCnt;
    VOS_UINT8                           ucReserve;

    /* ��UE�Ѿ�����URNTIʱʹ�ã������±���ASCֵ������Ԫ��ֵΪASC��Ӧ��Piֵ */
    VOS_UINT16                          ausAscPi[PS_WUE_MAX_ASC_NUM];
}RRC_MAC_ASC_CONFIG_STRU;

/*****************************************************************************
 ö����    : MACITF_BOOL_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �ӿ��е���Ч�Ա�ʶ
*****************************************************************************/

enum MACITF_BOOL_ENUM
{
    MACITF_INVALID                      = 0,    /*���ڶԽӿ��е�valid��־��λ������Ч��ʹ��1*/
    MACITF_VALID                        = 1,    /*���ڶԽӿ��е�valid��־��λ������Ч��ʹ��0*/

    MACITF_BUTT

};
typedef VOS_UINT16  MACITF_BOOL_ENUM_UINT16;

/*****************************************************************************
 �� �� ��  : RRC_MAC_AS_ACTIVE_DSDS_STATUS_IND_STRU
 �ṹ˵��  : RRC_MAC_AS_ACTIVE_DSDS_STATUS_IND_STRU��Ϣ�ṹ
 �޸���ʷ  :
  1.��  ��   : 2015��04��24��
    ��  ��   :
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RRC_MAC_MSG_TYPE_ENUM_UINT16            enMsgName;                          /* ԭ������ */ /*_H2ASN_Skip*/
    MACITF_BOOL_ENUM_UINT16                 enRfShareFlag;                      /* _VALID:����RF(DSDS˫��ģʽ)��_INVALID:��ռRF(��DSDS˫��ģʽ) */
}RRC_MAC_AS_ACTIVE_DSDS_STATUS_IND_STRU;

/*****************************************************************************
  10 ��������
*****************************************************************************/
/*MACά��CFN,�ṩ�ӿں�����RRC*/
extern VOS_VOID WTTF_MAC_GetCurrentCfn(VOS_UINT8 *pucCfn);

/*�ӿں�������ֵPS_SUCC������CN DOMAIN��Ӧ��CountC��Ч;PS_FAIL������CN DOMAIN��Ӧ��CountC��Ч*/
extern VOS_UINT32 WTTF_MAC_GetCurrentCountC(WUE_CN_DOMAIN_TYPE_ENUM_UINT8 enCnDomain,VOS_UINT32 *pulCountC);

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

#endif /* end of RrcMacInterface.h */


