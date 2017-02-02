

#ifndef __LMACLPHYINTERFACE_H__
#define __LMACLPHYINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#ifndef LPS_RTT
#include "vos.h"
#endif
#include "TLPhyInterface.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#ifdef LPS_RTT
#define VOS_WIN32   (1)
#define VOS_OS_VER  (3)
#endif

#define LMAC_FEATURE_OFF        (0)
#define LMAC_FEATURE_ON         (1)

/*�ú��ʱ��V7R1�ĵڶ����汾(2011��12��֮��İ汾)��������MBMS��Pilot�汾*/
/*#ifdef PRODUCT_CFG_BOARD_TYPE_HI6920CS_P500
 */

#if (FEATURE_ON == FEATURE_LTE_R11)
#define FEATURE_LMAC_LPHY_R11_CR        LMAC_FEATURE_ON
#else
#define FEATURE_LMAC_LPHY_R11_CR        LMAC_FEATURE_OFF
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define ULLMAC_LPHY_MSG_HDR                (0x000009c0)
#define LPHY_ULLMAC_MSG_HDR                (0x00000a00)

#define DLLMAC_LPHY_MSG_HDR                (0x00000a40)
#define LPHY_DLLMAC_MSG_HDR                (0x00000a80)

#define LTE_TB_MAX_SIZE                    (9432)

#define LPHY_LMAC_DL_TB_MEM_SIZE            LTE_TB_MAX_SIZE + sizeof(LMAC_LPHY_DATA_IND_STRU)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_MSG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC��PHY��Ľӿ���Ϣ
*****************************************************************************/
enum LMAC_LPHY_MSG_TYPE_ENUM
{
    ID_LMAC_LPHY_ACCESS_REQ               = (ULLMAC_LPHY_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LMAC_LPHY_ACCESS_REQ_STRU */   /* MAC��PHY����������뷢���������Ϣ��ϢID */
    ID_LMAC_LPHY_ACCESS_CNF               = (LPHY_ULLMAC_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LMAC_LPHY_ACCESS_CNF_STRU */   /* MAC��PHY����������뷢���������Ϣȷ����ϢID */

    ID_LMAC_LPHY_SR_DATA_REQ              = (ULLMAC_LPHY_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LMAC_LPHY_SR_DATA_REQ_STRU */ /* MAC��������������ϢID */
    ID_LMAC_LPHY_SR_DATA_CNF              = (LPHY_ULLMAC_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LMAC_LPHY_SR_DATA_CNF_STRU */   /* MAC������������ȷ����ϢID */

    ID_LMAC_LPHY_UL_GRANT_HARQ_IND        = (LPHY_ULLMAC_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LMAC_LPHY_UL_GRANT_HARQ_IND_STRU */   /* MAC����������Ȩ�����з�����Ϣ��ָʾ��ϢID */
    ID_LMAC_LPHY_DL_ASSIGNMENT_IND        = (LPHY_ULLMAC_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice ID_LMAC_LPHY_DL_ASSIGNMENT_IND */   /* MAC��������SCell������ָ��ָʾ��ϢID */
    ID_LMAC_LPHY_PUCCH_IND                = (LPHY_ULLMAC_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice ID_LMAC_LPHY_DL_ASSIGNMENT_IND */   /* MAC��������SCell������ָ��ָʾ��ϢID */
    ID_LMAC_LPHY_PDCCH_ORDER_IND          = (LPHY_ULLMAC_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice LMAC_LPHY_PDCCH_ORDER_IND_STRU */   /* MAC����PDCCH OReder�ķǾ������ר��Preamble����ϢID */
    ID_LMAC_LPHY_PDCCH_ORDER_SUCC_IND     = (LPHY_ULLMAC_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU */   /* MAC����PDCCH OReder�ľ������ �ɹ�*/
    ID_LMAC_LPHY_RAR_TIMEOUT_IND          = (LPHY_ULLMAC_MSG_HDR + 0x07),       /* _H2ASN_MsgChoice LMAC_LPHY_RAR_TIMEOUT_IND_STRU */   /* PHY����RAR��ʱͳ��ָʾ��Ϣ*/

    ID_LMAC_LPHY_RA_ACK_REQ               = (ULLMAC_LPHY_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LMAC_LPHY_RA_ACK_REQ_STRU */   /* MACָʾPHY���ھ��������ACK����ϢID */

    ID_LMAC_LPHY_SPS_RELEASE_REQ          = (ULLMAC_LPHY_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice LMAC_LPHY_SPS_RELEASE_REQ_STRU */   /* MACָʾPHY�ͷŰ뾲̬������Ȩ��Ϣ����ϢID */
    ID_LMAC_LPHY_SPS_RELEASE_CNF          = (LPHY_ULLMAC_MSG_HDR + 0x08),       /* _H2ASN_MsgChoice LMAC_LPHY_SPS_RELEASE_CNF_STRU */   /* MACָʾPHY�ͷŰ뾲̬������Ȩ��Ϣȷ�ϵ���ϢID */

    ID_LMAC_LPHY_RAR_CONFIG_REQ           = (ULLMAC_LPHY_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice LMAC_LPHY_RAR_CONFIG_REQ_STRU */   /* MAC��PHY�������������Ӧ��������Ϣ��ϢID */
    ID_LMAC_LPHY_RAR_CONFIG_CNF           = (LPHY_ULLMAC_MSG_HDR + 0x09),       /* _H2ASN_MsgChoice LMAC_LPHY_RAR_CONFIG_CNF_STRU */   /* MAC��PHY�������������Ӧ��������Ϣȷ����ϢID */

    ID_LMAC_LPHY_CRNTI_CONFIG_REQ         = (ULLMAC_LPHY_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice LMAC_LPHY_CRNTI_CONFIG_REQ_STRU */   /* MAC����C-RNTIֵ����ϢID */
    ID_LMAC_LPHY_CRNTI_CONFIG_CNF         = (LPHY_ULLMAC_MSG_HDR + 0x0a),       /* _H2ASN_MsgChoice LMAC_LPHY_CRNTI_CONFIG_CNF_STRU */   /* MAC����C-RNTIֵȷ����ϢID */

    ID_LMAC_LPHY_TA_TIMER_REQ             = (ULLMAC_LPHY_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice LMAC_LPHY_TA_TIMER_REQ_STRU */   /* MACָʾPHY����TA Timer�Ƿ�ʱ�����е���ϢID */
    ID_LMAC_LPHY_TA_TIMER_CNF             = (LPHY_ULLMAC_MSG_HDR + 0x0b),       /* _H2ASN_MsgChoice LMAC_LPHY_TA_TIMER_CNF_STRU */   /* MACָʾPHY����TA Timer�Ƿ�ʱ��������Ϣȷ�ϵ���ϢID */

    ID_LMAC_LPHY_DATA_REQ                 = (ULLMAC_LPHY_MSG_HDR + 0x07),       /* _H2ASN_MsgChoice LMAC_LPHY_DATA_REQ_STRU */   /* MAC��PHY���͵�PUSCH���ݵ���ϢID */

    ID_LMAC_LPHY_PHR_CONFIG_REQ           = (ULLMAC_LPHY_MSG_HDR + 0x08),       /* _H2ASN_MsgChoice  ID_LMAC_LPHY_PHR_CONFIG_REQ */   /* DSP֪ͨMAC����PHRר���������� */

    ID_LMAC_LPHY_TA_REQ                   = (DLLMAC_LPHY_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LMAC_LPHY_TA_REQ_STRU */   /* MAC����TAֵ����ϢID */
    ID_LMAC_LPHY_TA_CNF                   = (LPHY_DLLMAC_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LMAC_LPHY_TA_CNF_STRU */   /* MAC����TAֵȷ����ϢID */

    ID_LMAC_LPHY_CONNECTED_DRX_REQ        = (DLLMAC_LPHY_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LMAC_LPHY_CONNECTED_DRX_REQ_STRU */   /* MACָʾPHY����̬�µ�DRX����ϢID */
    ID_LMAC_LPHY_CONNECTED_DRX_CNF        = (LPHY_DLLMAC_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LMAC_LPHY_CONNECTED_DRX_CNF_STRU */   /* MACָʾPHY����̬�µ�DRX��ȷ����ϢID*/

    ID_LMAC_LPHY_MTCH_STOP_REQ            = (DLLMAC_LPHY_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LMAC_LPHY_MTCH_STOP_REQ_STRU */   /* MACָʾPHYֹͣ��ӦPMCH����ϢID */

    ID_LMAC_LPHY_DATA_IND                 = (LPHY_DLLMAC_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LMAC_LPHY_DATA_IND_STRU */   /* MAC����PHY���͵�PDSCH���ݵ���ϢID */
    ID_LMAC_LPHY_BCCH_DATA_IND            = (LPHY_DLLMAC_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice LMAC_LPHY_BCCH_DATA_IND_STRU */   /* MAC����PHY���͵�SIB�㲥���ݵ���ϢID */
    ID_LMAC_LPHY_PCH_DATA_IND             = (LPHY_DLLMAC_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice LMAC_LPHY_PCH_DATA_IND_STRU */   /* MAC����PHY���͵�Ѱ�����ݵ���ϢID  */
    ID_LMAC_LPHY_PBCH_DATA_IND            = (LPHY_DLLMAC_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice LMAC_LPHY_PBCH_IND_STRU */   /* MAC����PHY���͵�MIB�㲥���ݵ���ϢID */
    ID_LMAC_LPHY_MCH_DATA_IND             = (LPHY_DLLMAC_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice LMAC_LPHY_MCH_DATA_IND_STRU */   /* MAC����PHY���͵�MIB�㲥���ݵ���ϢID */

    ID_LMAC_LPHY_SCELLACT_REQ             = (DLLMAC_LPHY_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice LMAC_LPHY_SCELL_ACT_REQ_STRU */   /* MAC����DSP SCell����/ȥ�������ϢID */
    ID_LMAC_LPHY_SCELLACT_CNF             = (LPHY_DLLMAC_MSG_HDR + 0x07),       /* _H2ASN_MsgChoice LMAC_LPHY_SCELL_ACT_CNF_STRU */   /* MAC����DSP SCell����/ȥ����ȷ����ϢID */

    ID_LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND  = (LPHY_ULLMAC_MSG_HDR + 0x0c),       /* _H2ASN_MsgChoice LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND_STRU */   /* DSP֪ͨMAC����PDCCHָʾ�����а뾲̬�ͷ�*/

    ID_LMAC_LPHY_ERR_IND                  = (LPHY_ULLMAC_MSG_HDR + 0x0d),       /* _H2ASN_MsgChoice LMAC_LPHY_PDCCH_ERR_IND_STRU */   /* DSP֪ͨMAC����TB��ȡ�����ڴ������TB���ն�����*/


    ID_LMAC_LPHY_DSDS_RF_USED_IND         = (LPHY_ULLMAC_MSG_HDR + 0x0e),      /* _H2ASN_MsgChoice LMAC_LPHY_DSDS_RF_USED_IND_STRU */
    ID_LMAC_LPHY_VOICE_STTUS_REQ          = (ULLMAC_LPHY_MSG_HDR + 0x09),      /* _H2ASN_MsgChoice LMAC_LPHY_VOICE_STATUS_REQ_STRU */
    ID_LMAC_LPHY_MSG_TYPE_END
};
typedef         VOS_UINT32          LMAC_LPHY_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : LTE_ACESS_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC��PHY��������������
*****************************************************************************/
enum LTE_ACESS_TYPE_ENUM
{
    LTE_ACCESS_CONN_OR_REEST_REQ        = 0x00,                                 /*��ʼ�������ؽ���������*/
    LTE_ACCESS_CONTENT_MAC_REQ          = 0x01,                                 /*MAC��������̬��������*/
    LTE_ACCESS_CONTENT_PDCCH_ORDER_REQ  = 0x02,                                 /*PDCCH Order��������̬��������*/
    LTE_ACCESS_NONCONTENT_REQ           = 0x03,                                 /*�л���PDCCH Order�����Ǿ�������*/
    LTE_ACESS_TYPE_BUTT
};
typedef         VOS_UINT8           LTE_ACESS_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LTE_RNTI_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC��PHY���RNTI����
*****************************************************************************/
enum LTE_RNTI_TYPE_ENUM
{
    LTE_RA_RNTI                         = 0,                                    /*����RAR(PDSCH)��ʹ��RNTI*/
    LTE_P_RNTI                          ,                                       /*Ѱ��ʹ�õ�RNTI*/
    LTE_SI_RNTI                         ,                                       /*�㲥ʹ�õ�RNTI*/
    LTE_C_RNTI                          ,                                       /*�����ʹ�õ�C-RNTI*/
    LTE_SPS_RNTI                        ,                                       /*�뾲̬����ʹ�õ�RNTI*/
    LTE_TC_RNTI                         ,                                       /*������������ʹ�õ���ʱC-RNTI������Msg3���ţ�Msg4����*/
    LTE_TPC_PUCCH_RNTI                  ,                                       /*����ʹ��RNTI*/
    LTE_TPC_PUSCH_RNTI                  ,                                       /*����ʹ��RNTI*/
    LTE_M_RNTI                          ,                                       /*MBMSʹ��RNTI*/
    LTE_RNTI_TYPE_BUTT
};
typedef         VOS_UINT8           LTE_RNTI_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LTE_CRC_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC��PHY���CRC�������
*****************************************************************************/
enum LTE_CRC_TYPE_ENUM
{
    LTE_CRC_OK                         = 0,                                     /*��������CRC��ȷ*/
    LTE_CRC_ERR                        = 1,                                     /*��������CRC����*/
    LTE_CRC_TYPE_BUTT
};
typedef         VOS_UINT8           LTE_CRC_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LTE_DATAERR_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC��PHY���DATA_ERR����
*****************************************************************************/
enum LTE_DATAERR_TYPE_ENUM
{
    LTE_DATA_OK                         = 0,                                    /*���ظ����ݻ������쳣����*/
    LTE_DATA_REPEATE                    = 1,                                    /*�ظ�����*/
    LTE_DATA_OTHERERR                   = 2,                                    /*�����쳣����*/
    LTE_DATAERR_TYPE_BUTT
};
typedef         VOS_UINT8           LTE_DATAERR_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : L1L2_RSLT_CODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : L1L2���д���ͳһ����ֵö�ٶ���
*****************************************************************************/
enum L1L2_RSLT_CODE_ENUM
{
    L1L2_SUCC                             = 0,
    L1L2_FAIL                             = 1,

    L1L2_PTR_NULL                         = 2,
    L1L2_PARA_ERR                         = 3,
    L1L2_QUE_FULL                         = 4,
    L1L2_QUE_EMPTY                        = 5,

    L1L2_QUE_BUTT
};
typedef VOS_UINT32   L1L2_RSLT_CODE_ENUM_UINT32;

#if (LMAC_FEATURE_ON == FEATURE_LMAC_LPHY_R11_CR)
/*****************************************************************************
 �ṹ��    : LTE_MAC_PHY_ERR_IND_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHY�ϱ���MAC��ERR_IND
*****************************************************************************/
enum LTE_MAC_PHY_ERR_IND_ENUM
{
    LTE_MASTER_MODE_NOMEM                 = 0,                                  /*LTE��ģ�����л�ȡ����DMAĿ���ڴ�*/
    LTE_SLAVE_MODE_NOMEM                  = 1,                                  /*LTE��ģ�����л�ȡ����DMAĿ���ڴ�*/
    LTE_DLTB_QUEUE_FULL                   = 2,                                  /*����TB���ն�����*/
    LTE_UL_PDU_NOT_CMPL                   = 3,                                  /*����PDUû�а������*/
    LTE_UL_PHR_VALUE_OMIT                 = 4,                                  /*DSPû������BBP����PHR*/
    LTE_UL_PHR_FLAG_DIFFER                = 5,                                  /*PHRר�������PDU��PHR��־��ͬ*/
    LTE_MAC_PHY_ERR_OTHER                 = 6,                                  /*���������ϱ�*/
    LTE_MAC_PHY_ERR_TYPE_BUTT
};
typedef         VOS_UINT8           LTE_MAC_PHY_ERR_IND_ENUM_UINT8;

#else
/*****************************************************************************
 �ṹ��    : LTE_MAC_PHY_ERR_IND_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHY�ϱ���MAC��ERR_IND
*****************************************************************************/
enum LTE_MAC_PHY_ERR_IND_ENUM
{
    LTE_MASTER_MODE_NOMEM                 = 0,                                  /*LTE��ģ�����л�ȡ����DMAĿ���ڴ�*/
    LTE_SLAVE_MODE_NOMEM                  = 1,                                  /*LTE��ģ�����л�ȡ����DMAĿ���ڴ�*/
    LTE_DLTB_QUEUE_FULL                   = 2,                                  /*����TB���ն�����*/    
    LTE_UL_PDU_NOT_CMPL                   = 3,                                  /*����PDUû�а������*/
    LTE_MAC_PHY_ERR_OTHER                 = 4,                                  /*���������ϱ�*/
    LTE_MAC_PHY_ERR_TYPE_BUTT
};
typedef         VOS_UINT8           LTE_MAC_PHY_ERR_IND_ENUM_UINT8;

#endif

/*****************************************************************************
 ö����    : LMAC_LPHY_VOICE_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum LMAC_LPHY_VOICE_STATUS_ENUM
{
    LMAC_LPHY_VOICE_STATUS_SILENCE         = 0,
    LMAC_LPHY_VOICE_STATUS_SPEECH,
    LMAC_LPHY_VOICE_STATUS_BUTT
};
typedef VOS_UINT32  LMAC_LPHY_VOICE_STATUS_ENUM_UINT32;

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

#if (LMAC_FEATURE_ON == FEATURE_LMAC_LPHY_R11_CR)
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_RAR_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����Ӧ��Ϣ����ȷ����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
#if (VOS_OS_VER == VOS_WIN32)
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
#endif
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucHarqId;
    VOS_UINT8                           ucRev;

    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           ucTxSubFrame;
    VOS_UINT16                          usTxSysFrame;
} LMAC_LPHY_RAR_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_ACCESS_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������뷢���������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucPreambleIndex;                        /*MACȷ����Preamble ID*/
    VOS_UINT8                           ucPrachIndex;                           /*MACȷ����Prach Resource Index*/
    VOS_INT32                           lTxPower;                               /*MACȷ����Preamble���͹���(������·��)*/
    VOS_UINT32                          ulRARarTimeWindow;                      /*���������Ӧ��Ϣ���մ�*/
    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           aucRev[3];
}LMAC_LPHY_ACCESS_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_ACCESS_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������뷢���������Ϣȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                               /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT16                          usSFN;                                  /*����Preamble��Ӧ�տ�֡��*/

    VOS_UINT16                          usSubFrameNum;                          /*����Preamble��Ӧ�տ���֡��*/
    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           aucRev[1];
}LMAC_LPHY_ACCESS_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_RAR_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����Ӧ��Ϣ������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
#if (VOS_OS_VER == VOS_WIN32)
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
#endif
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    LTE_ACESS_TYPE_ENUM_UINT8           enLteAccessType;                        /*�������ģʽָʾ*/
    VOS_UINT8                           aucRev1[1];

    VOS_UINT16                          usTrnti;                                /*��ʱC-RNTI*/
    VOS_UINT16                          usTa;                                   /*TAֵ*/

    VOS_UINT16                          usTaRecSysFn;                           /*����Taֵ��ϵͳ֡��*/
    VOS_UINT16                          usTaRecSubFn;                           /*����Taֵ��ϵͳ��֡��*/

    VOS_UINT16                          usDetalPrampup;                         /*��Ϣ3���书�ʲ������ӣ���λbd*/
    VOS_INT16                           sPreambleInitTargetPwr;                 /*Preamble��eNB���������չ���*/

    VOS_UINT32                          ulRarUlGrant;                           /*0-19����λ��20���ص�������Ȩ��Ϣ*/
    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           aucRev[3];
} LMAC_LPHY_RAR_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DATA_REQ_HEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ݷ��͵����ݽṹͷ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usMacDataValid;                         /*MAC�´������Ƿ���Ч��־��0:��Ч 1:��Ч */
    VOS_UINT8                           ucPhrValid;                             /*PHR��Ч��־��0:��Ч 1:��Ч*/
    VOS_UINT8                           ucPhrSize;                              /*PHR����*/
    VOS_UINT16                          usPhroffset;                            /* 0:��Ч, ����ֵ��Ч��������ͷ��ƫ��*/

    VOS_UINT16                          usTbSize;                               /*��λBit��Pilot�汾���ֽ�*/
    VOS_UINT8                           ucHarqId;
    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           ucTbIndex;
    VOS_UINT8                           aucRev[1];                              /*Ԥ����*/
}LMAC_LPHY_DATA_REQ_HEAD_STRU;
#else
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_RAR_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����Ӧ��Ϣ����ȷ����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
#if (VOS_OS_VER == VOS_WIN32)
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
#endif
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucHarqId;
    VOS_UINT8                           ucRev;

    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           ucTxSubFrame;
    VOS_UINT16                          usTxSysFrame;
} LMAC_LPHY_RAR_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_ACCESS_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������뷢���������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucPreambleIndex;                        /*MACȷ����Preamble ID*/
    VOS_UINT8                           ucPrachIndex;                           /*MACȷ����Prach Resource Index*/
    VOS_INT32                           lTxPower;                               /*MACȷ����Preamble���͹���(������·��)*/
    VOS_UINT32                          ulRARarTimeWindow;                      /*���������Ӧ��Ϣ���մ�*/
}LMAC_LPHY_ACCESS_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_ACCESS_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������뷢���������Ϣȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                               /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT16                          usSFN;                                  /*����Preamble��Ӧ�տ�֡��*/

    VOS_UINT16                          usSubFrameNum;                          /*����Preamble��Ӧ�տ���֡��*/
    VOS_UINT8                           aucRev[2];
}LMAC_LPHY_ACCESS_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_RAR_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����Ӧ��Ϣ������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
#if (VOS_OS_VER == VOS_WIN32)
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
#endif
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    LTE_ACESS_TYPE_ENUM_UINT8           enLteAccessType;                        /*�������ģʽָʾ*/
    VOS_UINT8                           aucRev1[1];

    VOS_UINT16                          usTrnti;                                /*��ʱC-RNTI*/
    VOS_UINT16                          usTa;                                   /*TAֵ*/

    VOS_UINT16                          usTaRecSysFn;                           /*����Taֵ��ϵͳ֡��*/
    VOS_UINT16                          usTaRecSubFn;                           /*����Taֵ��ϵͳ��֡��*/

    VOS_UINT16                          usDetalPrampup;                         /*��Ϣ3���书�ʲ������ӣ���λbd*/
    VOS_INT16                           sPreambleInitTargetPwr;                 /*Preamble��eNB���������չ���*/

    VOS_UINT32                          ulRarUlGrant;                           /*0-19����λ��20���ص�������Ȩ��Ϣ*/
} LMAC_LPHY_RAR_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DATA_REQ_HEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ݷ��͵����ݽṹͷ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usMacDataValid;                         /*MAC�´������Ƿ���Ч��־��0:��Ч 1:��Ч */
    VOS_UINT8                           ucPhrValid;                             /*PHR��Ч��־��0:��Ч 1:��Ч*/
    VOS_UINT8                           ucPhrSize;                              /*PHR����*/
    VOS_UINT16                          usPhroffset;                            /* 0:��Ч, ����ֵ��Ч��������ͷ��ƫ��*/

    VOS_UINT16                          usTbSize;                               /*��λBit��Pilot�汾���ֽ�*/
    VOS_UINT8                           ucHarqId;
    VOS_UINT8                           aucRev[3];                              /*Ԥ����*/
}LMAC_LPHY_DATA_REQ_HEAD_STRU;
#endif


/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DATA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ݷ��͵����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_DATA_REQ_HEAD_STRU        stMacPhyDataReqHead;

    VOS_UINT8                           aucData[4];                              /*ʵ������*/

} LMAC_LPHY_DATA_REQ_STRU;

#if (LMAC_FEATURE_ON == FEATURE_LMAC_LPHY_R11_CR)
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DATA_IND_HEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ݽ��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT32 bitFrameType             :4;                                     /*֡����*/
    VOS_UINT32 bitHarqProcNum           :4;                                     /*���̺�*/
    VOS_UINT32 bitTbSize                :18;                                    /*���ݿ��С,��λ:Bit*/
    VOS_UINT32 bitRecv1                 :2;                                     /*reserved*/
    VOS_UINT32 bitTranNum               :4;                                     /*��������*/

    VOS_UINT32 bitSysFrm                :10;                                    /*֡��*/
    VOS_UINT32 bitPmchIndex             :6;                                     /*ֻ��MBMSʹ�ø��ֶΣ���ָPMCH�ŵ�����������ҵ�񶼲�ʹ��*/
    VOS_UINT32 bitSubFrm                :4;                                     /*��֡��*/
    VOS_UINT32 bitRntiType              :4;                                     /*RNTI Type*/
    VOS_UINT32 bitAreaId                :8;                                     /*����ID*/

    VOS_UINT32 bitCrcRst                :1;                                     /*CRC���*/
    VOS_UINT32 bitDataErrInd            :2;                                     /*�ظ����ݻ������쳣����*/
    VOS_UINT32 bitRecv4                 :1;                                     /*�����ֶ�*/
    VOS_UINT32 bitCellId                :4;                                     /*PCell: 0, SCell: 1~7*/
    VOS_UINT32 bitRecv5                 :24;                                    /*�����ֶ�*/
}LMAC_LPHY_DATA_IND_HEAD_STRU;
#else
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DATA_IND_HEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ݽ��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT32 bitFrameType             :4;                                     /*֡����*/
    VOS_UINT32 bitHarqProcNum           :4;                                     /*���̺�*/
    VOS_UINT32 bitTbSize                :17;                                    /*���ݿ��С,��λ:Bit*/
    VOS_UINT32 bitRecv1                 :3;                                     /*�����ֶ�*/
    VOS_UINT32 bitTranNum               :4;                                     /*��������*/

    VOS_UINT32 bitSysFrm                :10;                                    /*֡��*/
    VOS_UINT32 bitPmchIndex             :6;                                     /*ֻ��MBMSʹ�ø��ֶΣ���ָPMCH�ŵ�����������ҵ�񶼲�ʹ��*/
    VOS_UINT32 bitSubFrm                :4;                                     /*��֡��*/
    VOS_UINT32 bitRntiType              :4;                                     /*RNTI Type*/
    VOS_UINT32 bitAreaId                :8;                                     /*����ID*/

    VOS_UINT32 bitCrcRst                :1;                                     /*CRC���*/
    VOS_UINT32 bitDataErrInd            :2;                                     /*�ظ����ݻ������쳣����*/
    VOS_UINT32 bitRecv4                 :1;                                     /*�����ֶ�*/
    VOS_UINT32 bitCellId                :4;                                     /*PCell: 0, SCell: 1~7*/
    VOS_UINT32 bitRecv5                 :24;                                    /*�����ֶ�*/
}LMAC_LPHY_DATA_IND_HEAD_STRU;
#endif


/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ݽ��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_DATA_IND_HEAD_STRU        stMacPhyIndHead;

    VOS_UINT8                           aucData[4];                             /*�����������ݿ�ʵ������*/
} LMAC_LPHY_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_BCCH_DATA_IND_HEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���й㲥���ݽ��յ����ݽṹͷ
*****************************************************************************/
typedef LMAC_LPHY_DATA_IND_HEAD_STRU LMAC_LPHY_BCCH_DATA_IND_HEAD_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_BCCH_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���й㲥���ݽ��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_BCCH_DATA_IND_HEAD_STRU   stMacphyBcchIndHead;

    VOS_UINT8                           aucData[4];                             /*�������й㲥����ʵ������*/
} LMAC_LPHY_BCCH_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PCH_DATA_IND_HEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����Ѱ�����ݽ��յ����ݽṹͷ
*****************************************************************************/
typedef LMAC_LPHY_DATA_IND_HEAD_STRU LMAC_LPHY_PCH_DATA_IND_HEAD_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PCH_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����Ѱ�����ݽ��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_PCH_DATA_IND_HEAD_STRU    stMacPhyPchIndHead;

    VOS_UINT8                           aucData[4];                             /*��������Ѱ����Ϣ����ʵ������*/
} LMAC_LPHY_PCH_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_MCH_DATA_IND_HEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����MBMS���ݽ��յ����ݽṹͷ
*****************************************************************************/
typedef LMAC_LPHY_DATA_IND_HEAD_STRU LMAC_LPHY_MCH_DATA_IND_HEAD_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_MCH_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����MBMS���ݽ��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MCH_DATA_IND_HEAD_STRU    stMacPhyMchIndHead;

    VOS_UINT8                           aucData[4];                             /*��������Ѱ����Ϣ����ʵ������*/
} LMAC_LPHY_MCH_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PMCH_MTCH_STOP_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����PMCHֹͣ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPmchIndex;                            /*MBMS��Ӧֹͣ��MBMS�����PMCH����*/
    VOS_UINT8                           aucRev[3];
    VOS_UINT32                          ulPmchStopSubFrameNum;                  /*MBMS��Ӧֹͣ��MBMS�����PMCH�ļ���*/
}LMAC_LPHY_PMCH_MTCH_STOP_INFO;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_MTCH_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC֪ͨPHYֹͣPMCH����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucAreaId;                               /*MBMS��Ӧֹͣ����ID*/
    VOS_UINT8                           aucRev[1];
    LMAC_LPHY_PMCH_MTCH_STOP_INFO       stPmchStop;
} LMAC_LPHY_MTCH_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_UL_GRANT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������Ȩ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNewDataInd;                           /*������Ȩ������ָʾ��0:�ش�,1:������*/
    VOS_UINT8                           ucSchedulMode;                          /*������Ȩ��Ӧ����ģʽ��0:��̬����,1:�뾲̬����*/
    VOS_UINT8                           ucGapInd;                               /*�ñ�־ֻ�ڰ뾲̬��Ȩ��������Ч��0��Gap��Ч��1��Gap��Ч��Gapָʾ��Ӧ�������ݷ���ʱ��*/
    VOS_UINT8                           aucRev1[1];

    VOS_UINT32                          ulTBSize;                               /*������Ȩ��Ӧ��TB��С����λ:bit*/
}LMAC_LPHY_UL_GRANT_INFO_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_HARQ_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����HARQ������Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHarqFeedInd;                          /*����HARQ������Ϣ��0:NACK 1:ACK*/
    VOS_UINT8                           aucRev[3];
}LMAC_LPHY_HARQ_INFO_STRU;

#if (LMAC_FEATURE_ON == FEATURE_LMAC_LPHY_R11_CR)
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_UL_GRANT_HARQ_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������Ȩ������HARQ������Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTxSFN;                                /*������Ȩ��HARQ��NACK������Ӧ���������ݷ��͵�֡��*/
    VOS_UINT16                          usTxSubFrameNum;                        /*������Ȩ��HARQ��NACK������Ӧ���������ݷ��͵���֡��*/

    VOS_UINT8                           ucHarqId;                               /*������Ȩ��HARQ��NACK������Ӧ���������ݷ��͵Ľ��̺�*/
    VOS_UINT8                           ucUlGrantInd;                           /*������Ȩ�Ƿ���Чָʾ,0:��ЧPHICH�ϱ���Ч;1:��ʾ��Ч*/
    VOS_UINT16                          usRnti;                                 /*RNTIָʾ�������ж���ʱRNTI��RNTI����Ҫ����Msg3�������*/

    LMAC_LPHY_UL_GRANT_INFO_STRU        stUlGrantInfo;                          /*������Ȩ��Ϣ*/
    LMAC_LPHY_HARQ_INFO_STRU            stHarqInfo;                             /*����HARQ������Ϣ*/
    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           ucTbIndex;
    VOS_UINT8                           aucRev[2];
}LMAC_LPHY_UL_GRANT_HARQ_INFO_STRU;

#define LMAC_LPHY_UL_GRANT_HARQ_MAX_NUM      (4)
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_UL_GRANT_HARQ_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������Ȩ������HARQ������Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usRcvSFN;                               /*������Ȩ��HARQ�������յ�֡��*/
    VOS_UINT16                          usRcvSubFrameNum;                       /*������Ȩ��HARQ�������յ���֡��*/

    VOS_UINT8                           ucULGrantNum;                           /*������Ȩ��HARQ��������Ŀ*/
    VOS_UINT8                           aucRev[1];
    VOS_UINT8                           aucRev2[2];

    LMAC_LPHY_UL_GRANT_HARQ_INFO_STRU     astUlGrantHarqInfo[LMAC_LPHY_UL_GRANT_HARQ_MAX_NUM];                  /*������Ȩ��HARQ������Ϣ*/
} LMAC_LPHY_UL_GRANT_HARQ_IND_STRU;
#else
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_UL_GRANT_HARQ_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������Ȩ������HARQ������Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTxSFN;                                /*������Ȩ��HARQ��NACK������Ӧ���������ݷ��͵�֡��*/
    VOS_UINT16                          usTxSubFrameNum;                        /*������Ȩ��HARQ��NACK������Ӧ���������ݷ��͵���֡��*/

    VOS_UINT8                           ucHarqId;                               /*������Ȩ��HARQ��NACK������Ӧ���������ݷ��͵Ľ��̺�*/
    VOS_UINT8                           ucUlGrantInd;                           /*������Ȩ�Ƿ���Чָʾ,0:��ЧPHICH�ϱ���Ч;1:��ʾ��Ч*/
    VOS_UINT16                          usRnti;                                 /*RNTIָʾ�������ж���ʱRNTI��RNTI����Ҫ����Msg3�������*/

    LMAC_LPHY_UL_GRANT_INFO_STRU          stUlGrantInfo;                          /*������Ȩ��Ϣ*/

    LMAC_LPHY_HARQ_INFO_STRU              stHarqInfo;                             /*����HARQ������Ϣ*/
}LMAC_LPHY_UL_GRANT_HARQ_INFO_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_UL_GRANT_HARQ_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������Ȩ������HARQ������Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usRcvSFN;                               /*������Ȩ��HARQ�������յ�֡��*/
    VOS_UINT16                          usRcvSubFrameNum;                       /*������Ȩ��HARQ�������յ���֡��*/

    VOS_UINT8                           ucULGrantNum;                           /*������Ȩ��HARQ��������Ŀ*/
    VOS_UINT8                           aucRev[1];
    VOS_UINT8                           aucRev2[2];

    LMAC_LPHY_UL_GRANT_HARQ_INFO_STRU     astUlGrantHarqInfo[2];                  /*������Ȩ��HARQ������Ϣ*/
} LMAC_LPHY_UL_GRANT_HARQ_IND_STRU;
#endif



/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PUCCH_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ӧ������֡����PUCCH����
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usTxSFN;                                /*PUCCH���͵�֡��*/
    VOS_UINT16                          usTxSubFrameNum;                        /*PUCCH���͵���֡��*/
} LMAC_LPHY_PUCCH_IND_STRU;

#if (LMAC_FEATURE_ON == FEATURE_LMAC_LPHY_R11_CR)
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DL_ASSIGNMENT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ָ�ɵ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucValid[2];                                /*��Ȩ�Ƿ���Ч: 1,��Ȩ��Ч��0����Ȩ��Ч*/
    VOS_UINT8                           ucNewDataInd[2];                           /*���ش�ָʾ: 1,�´���0���ش�*/
    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           ucRsv[3];
    VOS_UINT16                          usRcvSFN;
    VOS_UINT16                          usRcvSubFrameNum;
}LMAC_LPHY_DL_ASSIGNMENT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DL_ASSIGNMENT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ָ�ɵ����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT32                          ulDlAssignNum;
    LMAC_LPHY_DL_ASSIGNMENT_INFO_STRU   stDlAssignmentInfo[4];                  /*��Ȩ��Ϣ�����ֻ��һ��TB�飬��һ����Ч */
} LMAC_LPHY_DL_ASSIGNMENT_IND_STRU;
#else
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DL_ASSIGNMENT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ָ�ɵ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucValid;                                /*��Ȩ�Ƿ���Ч: 1,��Ȩ��Ч��0����Ȩ��Ч*/
    VOS_UINT8                           ucNewDataInd;                           /*���ش�ָʾ: 1,�´���0���ش�*/
    VOS_UINT8                           aucRev[2];
}LMAC_LPHY_DL_ASSIGNMENT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DL_ASSIGNMENT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ָ�ɵ����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usRcvSFN;                               /*����ָ�ɵĽ���֡��*/
    VOS_UINT16                          usRcvSubFrameNum;                       /*����ָ�ɵĽ�����֡��*/

    VOS_UINT8                           ucSCellIndex;                           /*ScellIndex: 1~7*/
    VOS_UINT8                           ucTbNum;                                /*TB����� */
    VOS_UINT8                           aucRev[2];
    LMAC_LPHY_DL_ASSIGNMENT_INFO_STRU   stDlAssignmentInfo[2];                  /*��Ȩ��Ϣ�����ֻ��һ��TB�飬��һ����Ч */
} LMAC_LPHY_DL_ASSIGNMENT_IND_STRU;
#endif



/*****************************************************************************
 �ṹ��    : LMAC_LPHY_SR_DATA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����������Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_SR_DATA_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_SR_DATA_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����������Ϣ��ȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucResult;                               /*0:�ɹ���1��ȡ����2��ʧ��(Ԥ������ʱ����)*/
    VOS_UINT8                           ucSubFrame;                             /*SR���ͳɹ����ڵ�֡��*/
    VOS_UINT16                          usFrame;                                /*SR���ͳɹ����ڵ���֡��*/
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_SR_DATA_CNF_STRU;
#if (LMAC_FEATURE_ON == FEATURE_LMAC_LPHY_R11_CR)
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_TA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAֵ������Ϣ��������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT16                          usTa;                                   /*���յ�eNB�·���TAֵ*/

    VOS_UINT16                          usTaRevSFN;                             /*���յ�eNB�·���TAֵ��֡��*/
    VOS_UINT16                          usTaRcvSubFN;                           /*���յ�eNB�·���TAֵ����֡��*/
    VOS_UINT8                           ucTAGId;
    VOS_UINT8                           aucRev[3];
} LMAC_LPHY_TA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_TA_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAֵ������Ϣ�����ȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucTAGId;
    VOS_UINT8                           aucRev[1];
} LMAC_LPHY_TA_CNF_STRU;
#else
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_TA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAֵ������Ϣ��������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT16                          usTa;                                   /*���յ�eNB�·���TAֵ*/

    VOS_UINT16                          usTaRevSFN;                             /*���յ�eNB�·���TAֵ��֡��*/
    VOS_UINT16                          usTaRcvSubFN;                           /*���յ�eNB�·���TAֵ����֡��*/
} LMAC_LPHY_TA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_TA_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAֵ������Ϣ�����ȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_TA_CNF_STRU;
#endif

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_CRNTI_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : C-RNTIֵ������Ϣ��������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT16                          usCrnti;                                /*���յ�eNB�·���Crntiֵ*/

} LMAC_LPHY_CRNTI_CONFIG_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_CRNTI_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : C-RNTIֵ������Ϣ�����ȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                               /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                 /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_CRNTI_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_SCELL_ACT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SCell����/ȥ����������Ϣ��������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                               /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                 /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucSCellActBmp;                          /*SCell����Bitmap,�ӵ�λbit1~bit7����SCell1~SCell7,��ӦbitΪ1�����0������Ч*/
    VOS_UINT8                           ucSCellDeactBmp;                        /*SCellȥ����Bitmap,�ӵ�λbit1~bit7����SCell1~SCell7,��ӦbitΪ1����ȥ���0������Ч*/
    VOS_UINT16                          usSCellCtrlRevSFN;                      /*SCell����/ȥ�������Ԫ�Ľ���֡��*/
    VOS_UINT16                          usSCellCtrlRcvSubFN;                    /*SCell����/ȥ�������Ԫ�Ľ�����֡��*/
} LMAC_LPHY_SCELL_ACT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_SCELL_ACT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SCell����/ȥ����������Ϣ����ȷ�ϵ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                               /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                 /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_SCELL_ACT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_CONNECTED_DRX_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����̬�µ�DRX����Ԫ���յ�ָʾ��PHY�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                               /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                 /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_CONNECTED_DRX_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_CONNECTED_DRX_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����̬�µ�DRX����Ԫ���յ�ָʾ��PHY��ȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_CONNECTED_DRX_CNF_STRU;
#if (LMAC_FEATURE_ON == FEATURE_LMAC_LPHY_R11_CR)
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_ERR_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHY��MAC�ϱ���ERR_IND
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    LTE_MAC_PHY_ERR_IND_ENUM_UINT8      ucErrType;
    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           ucTbIndex;
    VOS_UINT8                           aucRev[1];
    VOS_UINT16                          usSysFrame;
    VOS_UINT16                          usSubFrame;
} LMAC_LPHY_ERR_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PDCCH_ORDER_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCCH ORDER�����ķǾ��������������Preamble��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT8                           ucDediPreambleID;                       /*ר��Preamble ID*/
    VOS_UINT8                           ucPrachMaskIndex;                       /*PRACH MASK Index*/
    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           aucRev[1];
} LMAC_LPHY_PDCCH_ORDER_IND_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCCH ORDER�����ľ�������������ĳɹ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           aucRev[3];
} LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_RAR_TIMEOUT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHY����RAR��ʱ�䴰��ʱ֪ͨMAC����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           aucRev[3];
} LMAC_LPHY_RAR_TIMEOUT_IND_STRU;
#else
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_ERR_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHY��MAC�ϱ���ERR_IND
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    LTE_MAC_PHY_ERR_IND_ENUM_UINT8      ucErrType;
    VOS_UINT8                           aucRev[3];
} LMAC_LPHY_ERR_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PDCCH_ORDER_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCCH ORDER�����ķǾ��������������Preamble��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT8                           ucDediPreambleID;                       /*ר��Preamble ID*/
    VOS_UINT8                           ucPrachMaskIndex;                       /*PRACH MASK Index*/
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_PDCCH_ORDER_IND_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCCH ORDER�����ľ�������������ĳɹ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

} LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_RAR_TIMEOUT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHY����RAR��ʱ�䴰��ʱ֪ͨMAC����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

} LMAC_LPHY_RAR_TIMEOUT_IND_STRU;
#endif


/*****************************************************************************
 �ṹ��    : LMAC_LPHY_SPS_RELEASE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHY���а뾲̬����������Ȩ��Դ�ͷŵ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_SPS_RELEASE_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_SPS_RELEASE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHY���а뾲̬����������Ȩ��Դ�ͷŵ�ȷ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_SPS_RELEASE_CNF_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_RA_ACK_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������MAC����Ԫ�����ȷ����µ�ACK/NACK��Ϣ���ݽṹ
             MACд��ACK/NACK��Ϣ������Ϊ��Ч��DSP��ȡ������,��ԭ�����ߵ�������
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucValidFlag;                            /* 0:ACK/NACK��Ϣ��Ч;1:ACK/NACK��Ϣ��Ч��*/
    VOS_UINT8                           ucAckNack;                              /* 0:��ʾNACK��Ϣ,1:��ʾACK��Ϣ*/
} LMAC_LPHY_RA_ACK_REQ_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PBCH_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ݽ��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usSFN;                                  /*��������MIB���ݿ��֡��*/
    VOS_UINT16                          usSubFrameNum;                          /*��������MIB���ݿ����֡��*/

    VOS_UINT16                          usAntennaPortsCount;                    /*���������߶˿���*/
    VOS_UINT8                           aucRev[2];

    VOS_UINT32                          ulTBSize;                               /*��������MIB���ݿ��TB��С����λ:bit*/

    VOS_UINT8                           aucData[4];                             /*��������MIB���ݿ�ʵ������*/
} LMAC_LPHY_PBCH_IND_STRU;

#if (LMAC_FEATURE_ON == FEATURE_LMAC_LPHY_R11_CR)
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_TA_TIMER_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TA Timer�Ƿ�����֪ͨPHY����Ӧ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT16                          usTaTimerRunInd;                        /*0����ʱ�����У�1����������*/
    VOS_UINT8                           ucTagId;
    VOS_UINT8                           aucRev[3];
} LMAC_LPHY_TA_TIMER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_TA_TIMER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TA Timer�Ƿ�����֪ͨPHY����Ӧ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucTagId;
    VOS_UINT8                           ucRev;
} LMAC_LPHY_TA_TIMER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PHR_CONFIG_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC����PHY PHR��MAC PDU�е�λ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMailBoxFlag;                         /*ÿ��HARQ����Ԥ��4�ֽڵ������־λ����������ͳһ����*/
    VOS_UINT16                          usPhrValid;                            /*PHR��Ч��־ 0: ��Ч��1����Ч��MAC������ʱ��Ϊ��Ч��DSP���յ�����Ȩʱ��Ϊ��Ч*/
    VOS_UINT8                           ucPhrType;                             /*0����ͨPHR��1����չPHR*/
    VOS_UINT8                           ucPhrSize;                             /*PHR��С*/

    VOS_UINT16                          usTxSFN;                               /*PHR��ӦMAC PDU�ķ���֡*/
    VOS_UINT8                           ucTxSubFrameNum;                       /*PHR��ӦMAC PDU�ķ�����֡*/
    VOS_UINT8                           ucPucchEnable;

    VOS_UINT8                           ucPbTmpDecrease;                       /*0:�Ƕ����Թ��ʻ��˽��ͣ�1:�����Թ��ʻ��˽���*/
    VOS_UINT8                           ucPowerBackoff;                        /*����Ƕ����Թ��ʻ��˽��ͣ���֪ͨDSPδ����ǰ�Ĺ��ʻ���ֵ*/
    VOS_UINT8                           ucServCellIndex;
    VOS_UINT8                           ucTbIndex;

    VOS_UINT8                           ucHarqId;                              /*PHR��ӦMAC PDU��HARQID*/
    VOS_UINT8                           ucScellActBmp;
    VOS_UINT8                           aucRsv[2];
} LMAC_LPHY_PHR_CONFIG_INFO;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PHR_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC����PHY PHR��MAC PDU�е�λ����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    LMAC_LPHY_PHR_CONFIG_INFO           astPhrConfigInfo[10];
} LMAC_LPHY_PHR_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PL_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PCell��PLֵ�ϱ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPlValue;
    VOS_UINT16                          usSCellPl;
} LMAC_LPHY_PL_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PB_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PCell��PBֵ�ϱ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPbValue;
    VOS_UINT16                          usSCellPb;
} LMAC_LPHY_PB_IND_STRU;

#else
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_TA_TIMER_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TA Timer�Ƿ�����֪ͨPHY����Ӧ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT16                          usTaTimerRunInd;                        /*0����ʱ�����У�1����������*/
} LMAC_LPHY_TA_TIMER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_TA_TIMER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TA Timer�Ƿ�����֪ͨPHY����Ӧ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_TA_TIMER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PHR_CONFIG_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC����PHY PHR��MAC PDU�е�λ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMailBoxFlag;                         /*ÿ��HARQ����Ԥ��4�ֽڵ������־λ����������ͳһ����*/
    VOS_UINT16                          usPhrValid;                            /*PHR��Ч��־ 0: ��Ч��1����Ч��MAC������ʱ��Ϊ��Ч��DSP���յ�����Ȩʱ��Ϊ��Ч*/
    VOS_UINT8                           ucPhrType;                             /*0����ͨPHR��1����չPHR*/
    VOS_UINT8                           ucPhrSize;                             /*PHR��С*/

    VOS_UINT16                          usTxSFN;                               /*PHR��ӦMAC PDU�ķ���֡*/
    VOS_UINT8                           ucTxSubFrameNum;                       /*PHR��ӦMAC PDU�ķ�����֡*/
    VOS_UINT8                           aucRev1[1];

    VOS_UINT8                           ucPbTmpDecrease;                       /*0:�Ƕ����Թ��ʻ��˽��ͣ�1:�����Թ��ʻ��˽���*/
    VOS_UINT8                           ucPowerBackoff;                        /*����Ƕ����Թ��ʻ��˽��ͣ���֪ͨDSPδ����ǰ�Ĺ��ʻ���ֵ*/
    VOS_UINT8                           aucRev2[2];
} LMAC_LPHY_PHR_CONFIG_INFO;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PHR_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC����PHY PHR��MAC PDU�е�λ����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    LMAC_LPHY_PHR_CONFIG_INFO           astPhrConfigInfo[8];
} LMAC_LPHY_PHR_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PL_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PCell��PLֵ�ϱ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPlValue;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_PL_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PB_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PCell��PBֵ�ϱ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPbValue;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_PB_IND_STRU;
#endif


/*****************************************************************************
 �ṹ��    : LMAC_LPHY_FORCE_ACTIVE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC������̬DRX�ڼ�ǿ�Ƽ������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDrxForceActive;
} LMAC_LPHY_FORCE_ACTIVE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_HO_CQI_SRS_ACTIVE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC���л�������֪ͨPHY����CQI/SRS��Ч�������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHoCqiSrsActive;
} LMAC_LPHY_HO_CQI_SRS_ACTIVE_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHY�ͷ����а뾲̬��Ȩָʾ
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/

} LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND_STRU;
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_CAP_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC����DSP��ͣGAP
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulGapStartFlag;                          /*1:Gap start;  0:Gap stop*/
} LMAC_LPHY_CAP_CONFIG_REQ_STRU;

#if (LMAC_FEATURE_ON == FEATURE_LMAC_LPHY_R11_CR)
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_MSG3_HARQ_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Msg3�ش���ӦHARQ������Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTxSfn;                                /*Msg3�ش���Ӧ���͵�֡��*/
    VOS_UINT8                           ucTxSbfn;                               /*Msg3�ش���Ӧ���͵���֡��*/
    VOS_UINT8                           ucServCellIndex;
} LMAC_LPHY_MSG3_HARQ_IND_STRU;
#else
/*****************************************************************************
 �ṹ��    : LMAC_LPHY_MSG3_HARQ_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Msg3�ش���ӦHARQ������Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTxSfn;                                /*Msg3�ش���Ӧ���͵�֡��*/
    VOS_UINT8                           ucTxSbfn;                               /*Msg3�ش���Ӧ���͵���֡��*/
    VOS_UINT8                           ucRev;
} LMAC_LPHY_MSG3_HARQ_IND_STRU;
#endif


/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DL_TB_BUFF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ݽ��յĻ���ṹ
*****************************************************************************/
typedef  struct
{
    VOS_UINT32      ulTotalNum;                                                 /*ARM�ṩ��DSP��TB�������������Χ[0,4]ARMд��DSP��*/
    VOS_UINT32      aulTbAddr[4];                                               /*TB�黺���׵�ַ���飬ÿһTB�黺��Ϊ16Kbyte���ݶ���                                                                                �����ڴ�飻�����ַ���׸�����Ԫ������������д��
                                                                                ���ܿ���С��4������ȫ0���룻ȫ0��ʾ�õ�ַ��Ч��ARMд��DSP��*/
    VOS_UINT32      ulUsedNum;                                                  /*DSPһ�������ϱ���TB����Ŀ����Χ[0,4]DSPд��ARM��*/
}LMAC_LPHY_DL_TB_BUFF_STRU;

typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgID;                                /*_H2ASN_MsgChoice_Export LMAC_LPHY_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LMAC_LPHY_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LMAC_LPHY_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    LMAC_LPHY_MSG_DATA                    stMsgData;
}MacPhyInterface_MSG;

/*****************************************************************************
 �ṹ��    : L1L2_QUEUE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMAC-LPHY����������ݽṹ
*****************************************************************************/
typedef struct L1L2_QUEUE
{
    VOS_UINT32          ulValidFlag;
    VOS_UINT32          ulHead;
    VOS_UINT32          ulTail;
    VOS_UINT32          ulMaxNum;
    VOS_UINT32          aulBuffer[1];   /*aulBuffer��ΪBuffer����ʼ��ַʹ�ã�Buffer��ʵ�ʴ�С�ڳ�ʼ����ָ��*/
}L1L2_QUEUE_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_DSDS_RF_USED_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LPHY�ϱ���LMAC��͵ָ֡ʾ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32  enMsgId;
    VOS_UINT16                      usSFN;
    VOS_UINT16                      usSubFrameNum;
    VOS_UINT16                      usRfUsdFlag;
    VOS_UINT8                       aucRev[2];
}LMAC_LPHY_DSDS_RF_USED_IND_STRU;

/*****************************************************************************
 �ṹ��    : LMAC_LPHY_VOICE_STATUS_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LMAC����LPHY��VoLTE��Ĭ״̬����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ancRev[2];

    VOS_UINT16                          usFrame;
    VOS_UINT16                          usSubFrame;

    LMAC_LPHY_VOICE_STATUS_ENUM_UINT32  enVoiceStatus;
}LMAC_LPHY_VOICE_STATUS_REQ_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
/*��������*/
#define LMAC_LPHY_SYSFRM_ADDR              (LPHY_LMAC_FRAME_ADDR)               /*MACֱ�Ӵ�BBP�Ĵ�����ȡϵͳ֡��*/
#define LMAC_LPHY_SUBFRM_ADDR              (LPHY_LMAC_SUB_FRAME_ADDR)           /*MACֱ�Ӵ�BBP�Ĵ�����ȡϵͳ��֡��*/
#define LMAC_LPHY_TIMER_LOCK_ADDR          (LPHY_LMAC_TIMER_LOCK_ADDR)          /*MACֱ�Ӵ�BBP�Ĵ�����ȡϵͳ֡�ź���֡��ʱ��Ҫ���������*/

/*��������*/
#define DEDI_MAILBOX_FLAG                (0x4)                                  /*ר������Ķ�д��־ռ4���ֽ�*/
#define DEDI_MAILBOX_UL_START_ADDR       (LPHY_MAILBOX_LMAC_UP_BASE_ADDR)       /*ר���������PHY�ϱ���MAC����Ϣ���׵�ַ*/
#define DEDI_MAILBOX_DL_START_ADDR       (LPHY_MAILBOX_LMAC_DOWN_BASE_ADDR)     /*ר���������MAC�·���PHY����Ϣ���׵�ַ*/
#define LMAC_LPHY_DLTB_QUEUE_START_ADDR  (LPHY_MAILBOX_DL_TB_QUEUE_BASE_ADDR)        /*����TB���մ�������е�ַ*/
#else
extern VOS_UINT8        g_aucDediUlMailBox[2048];
extern VOS_UINT8        g_aucDediDlMailBox[2048];
extern VOS_UINT8        g_aucDediDlTbQue[2048];
extern VOS_UINT32       g_usSysFram;
extern VOS_UINT32       g_ucSubFram;
extern VOS_UINT32       g_ulFramLock;

#define LMAC_LPHY_SYSFRM_ADDR              (&g_usSysFram)                           /*MACֱ�Ӵ�BBP�Ĵ�����ȡϵͳ֡��*/
#define LMAC_LPHY_SUBFRM_ADDR              (&g_ucSubFram)                           /*MACֱ�Ӵ�BBP�Ĵ�����ȡϵͳ��֡��*/
#define LMAC_LPHY_TIMER_LOCK_ADDR          (&g_ulFramLock)          /*MACֱ�Ӵ�BBP�Ĵ�����ȡϵͳ֡�ź���֡��ʱ��Ҫ���������*/

#define DEDI_MAILBOX_FLAG                (0x4)                                  /*ר������Ķ�д��־ռ4���ֽ�*/
#define DEDI_MAILBOX_UL_START_ADDR       g_aucDediUlMailBox                     /*ר���������PHY�ϱ���MAC����Ϣ���׵�ַƫ��*/
#define DEDI_MAILBOX_DL_START_ADDR       g_aucDediDlMailBox                     /*ר���������MAC�·���PHY����Ϣ���׵�ַƫ��*/
#define LMAC_LPHY_DLTB_QUEUE_START_ADDR  g_aucDediDlTbQue                       /*����TB���մ�������е�ַ*/
#endif

#define DRX_PAGING_LEN              20/*DRX Paging����*/

/*****************************************************************************
 ר���������PHY �ϱ���MAC�ĸ�����Ϣ��ַ���ܴ�СԤ��Ϊ512Byte
 ˵��:Ϊ��ʹ�÷��㣬�Լ��������ܣ�һЩFLAG_ADDR��ʱ������ʹ��
        ֱ�Ӷ���ص�ַ��ȡ��ɣ������ر�˵����FLAG ADDRĬ����ʹ�õġ�
*****************************************************************************/
#define DEDI_UL_GRANT_HARQ_FLAG_ADDR     (DEDI_MAILBOX_UL_START_ADDR)
#define DEDI_UL_GRANT_HARQ_ADDR          (DEDI_UL_GRANT_HARQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_DL_ASSIGNMENT_FLAG_ADDR     (DEDI_UL_GRANT_HARQ_ADDR + sizeof(LMAC_LPHY_UL_GRANT_HARQ_IND_STRU))
#define DEDI_DL_ASSIGNMENT_ADDR          (DEDI_DL_ASSIGNMENT_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_PUCCH_IND_FLAG_ADDR         (DEDI_DL_ASSIGNMENT_ADDR + sizeof(LMAC_LPHY_DL_ASSIGNMENT_IND_STRU))
#define DEDI_PUCCH_IND_ADDR              (DEDI_PUCCH_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_PDCCH_ORDER_IND_FLAG_ADDR   (DEDI_PUCCH_IND_ADDR + sizeof(LMAC_LPHY_PUCCH_IND_STRU))
#define DEDI_PDCCH_ORDER_IND_ADDR        (DEDI_PDCCH_ORDER_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_PDCCH_ORDER_SUCC_FLAG_ADDR  (DEDI_PDCCH_ORDER_IND_ADDR + sizeof(LMAC_LPHY_PDCCH_ORDER_IND_STRU))
#define DEDI_PDCCH_ORDER_SUCC_ADDR       (DEDI_PDCCH_ORDER_SUCC_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_RAR_TIMEOUT_IND_FLAG_ADDR   (DEDI_PDCCH_ORDER_SUCC_ADDR + sizeof(LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU))
#define DEDI_RAR_TIMEOUT_IND_ADDR        (DEDI_RAR_TIMEOUT_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_ACCESS_CNF_FLAG_ADDR        (DEDI_RAR_TIMEOUT_IND_ADDR + sizeof(LMAC_LPHY_RAR_TIMEOUT_IND_STRU))
#define DEDI_ACCESS_CNF_ADDR             (DEDI_ACCESS_CNF_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_SR_DATA_CNF_FLAG_ADDR       (DEDI_ACCESS_CNF_ADDR + sizeof(LMAC_LPHY_ACCESS_CNF_STRU))
#define DEDI_SR_DATA_CNF_ADDR            (DEDI_SR_DATA_CNF_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DEDI_PL_IND_FLAG_ADDR��־��ʱ��ʹ�ã�PSֱ�Ӷ�ȡDEDI_PL_IND_ADDR��Ϣʹ��*/
#define DEDI_PL_IND_FLAG_ADDR            (DEDI_SR_DATA_CNF_ADDR + sizeof(LMAC_LPHY_SR_DATA_CNF_STRU))
#define DEDI_PL_IND_ADDR                 (DEDI_PL_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DSP�ϱ���MAC�� required power backoffȡֵ*/
#define DEDI_PB_IND_FLAG_ADDR            (DEDI_PL_IND_ADDR + sizeof(LMAC_LPHY_PL_IND_STRU))
#define DEDI_PB_IND_ADDR                 (DEDI_PB_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*PDCCH�ͷ����а뾲̬��Ȩ��ָʾ*/
#define DEDI_PDCCH_RELEASE_ULSPS_IND_FLAG_ADDR  (DEDI_PB_IND_ADDR + sizeof(LMAC_LPHY_PB_IND_STRU))
#define DEDI_PDCCH_RELEASE_ULSPS_IND_ADDR       (DEDI_PDCCH_RELEASE_ULSPS_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*Msg3 �ش���ӦHARQ����֡�ź���֡��*/
#define DEDI_MSG3_HARQ_IND_FLAG_ADDR  (DEDI_PDCCH_RELEASE_ULSPS_IND_ADDR + sizeof(LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND_STRU))
#define DEDI_MSG3_HARQ_IND_ADDR       (DEDI_MSG3_HARQ_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*RAR CONFIG CNF*/
#define DEDI_RAR_CONFIG_CNF_FLAG_ADDR    (DEDI_MSG3_HARQ_IND_ADDR + sizeof(LMAC_LPHY_MSG3_HARQ_IND_STRU))
#define DEDI_RAR_CONFIG_CNF_ADDR         (DEDI_RAR_CONFIG_CNF_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*MAC_PHY_ERR_IND*/
#define DEDI_MAC_PHY_ERR_IND_FLAG_ADDR   (DEDI_RAR_CONFIG_CNF_ADDR+sizeof(LMAC_LPHY_RAR_CONFIG_CNF_STRU))
#define DEDI_MAC_PHY_ERR_IND_ADDR        (DEDI_MAC_PHY_ERR_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DSP��鵽MAC PDU Valid��־Ϊ��Ч,�Ѹñ�־��Ϊ1��MAC�������*/
/*#define DEDI_MAC_PDU_INVALID_FLAG_ADDR   ()*/
#define DEDI_MAC_PDU_INVALID_FLAG        (DEDI_MAC_PHY_ERR_IND_ADDR+sizeof(LMAC_LPHY_ERR_IND_STRU))

/*DEDI_DRX_PAGING_PROC_ADDR*/
#define DEDI_DRX_PAGING_PROC_ADDR        (DEDI_MAC_PDU_INVALID_FLAG + sizeof(VOS_UINT32))

/*DEDI_MAILBOX_UL_END_ADDR*/
#define DEDI_MAILBOX_UL_END_ADDR         (DEDI_DRX_PAGING_PROC_ADDR+sizeof(LMAC_LPHY_DATA_IND_HEAD_STRU) + DRX_PAGING_LEN)
/*DEDI_MAILBOX_UL_SIZE*/
#define DEDI_MAILBOX_UL_SIZE             (DEDI_MAILBOX_UL_END_ADDR - DEDI_MAILBOX_UL_START_ADDR)

/*****************************************************************************
 ר���������MAC�·���PHY�ĸ�����Ϣ��ַ�ܴ�СԤ��Ϊ256Byte
 ˵��:Ϊ��ʹ�÷��㣬�Լ��������ܣ�һЩFLAG_ADDR��ʱ������ʹ��
        ֱ�Ӷ���ص�ַ��ȡ��ɣ������ر�˵����FLAG ADDRĬ����ʹ�õġ�
*****************************************************************************/
/*DEDI_DL_TB_BUFF_FLAG_ADDR��־��ʱ��ʹ�ã�DSPֱ�Ӷ�ȡDEDI_DL_TB_BUFF_ADDR��Ϣʹ��*/
#define DEDI_ACCESS_REQ_FLAG_ADDR        (DEDI_MAILBOX_DL_START_ADDR)
#define DEDI_ACCESS_REQ_ADDR             (DEDI_ACCESS_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_SR_DATA_REQ_FLAG_ADDR       (DEDI_ACCESS_REQ_ADDR + sizeof(LMAC_LPHY_ACCESS_REQ_STRU))
#define DEDI_SR_DATA_REQ_ADDR            (DEDI_SR_DATA_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_RA_ACK_REQ_FLAG_ADDR        (DEDI_SR_DATA_REQ_ADDR + sizeof(LMAC_LPHY_SR_DATA_REQ_STRU))
#define DEDI_RA_ACK_REQ_ADDR             (DEDI_RA_ACK_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DEDI_FORCE_ACTIVE_REQ_FLAG_ADDR��־��ʱ��ʹ�ã�DSPֱ�Ӷ�ȡDEDI_FORCE_ACTIVE_REQ_ADDR��Ϣʹ��*/
#define DEDI_FORCE_ACTIVE_REQ_FLAG_ADDR  (DEDI_RA_ACK_REQ_ADDR + sizeof(LMAC_LPHY_RA_ACK_REQ_STRU))
#define DEDI_FORCE_ACTIVE_REQ_ADDR       (DEDI_FORCE_ACTIVE_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DEDI_HO_CQI_SRS_ACTIVE_FLAG_ADDR��־��ʱ��ʹ�ã�DSPֱ�Ӷ�ȡDEDI_HO_CQI_SRS_ACTIVE_ADDR��Ϣʹ��*/
#define DEDI_HO_CQI_SRS_ACTIVE_FLAG_ADDR (DEDI_FORCE_ACTIVE_REQ_ADDR + sizeof(LMAC_LPHY_FORCE_ACTIVE_REQ_STRU))
#define DEDI_HO_CQI_SRS_ACTIVE_ADDR      (DEDI_HO_CQI_SRS_ACTIVE_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*RAR CONFIG REQ*/
#define DEDI_RAR_CONFIG_REQ_FLAG_ADDR    (DEDI_HO_CQI_SRS_ACTIVE_ADDR + sizeof(LMAC_LPHY_HO_CQI_SRS_ACTIVE_STRU))
#define DEDI_RAR_CONFIG_REQ_ADDR         (DEDI_RAR_CONFIG_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/* L2�л��棬DSP���ܽ���˯�ߣ�����Ӱ������ʱ�ӣ�MAC�����ú����*/
/*#define DEDI_MAC_PHY_ONLY_RF_SLEEP_FLAG_ADDR   ()*/
#define DEDI_MAC_PHY_ONLY_RF_SLEEP_FLAG   (DEDI_RAR_CONFIG_REQ_ADDR + sizeof(LMAC_LPHY_RAR_CONFIG_REQ_STRU))

/*PHR CONFIG REQ*/
#define DEDI_PHR_CONFIG_REQ_FLAG_ADDR     (DEDI_MAC_PHY_ONLY_RF_SLEEP_FLAG + sizeof(VOS_UINT32))
#define DEDI_PHR_CONFIG_REQ_ADDR          (DEDI_PHR_CONFIG_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*GAP CONFIG REQ*/
#define DEDI_GAP_CONFIG_REQ_FLAG_ADDR     (DEDI_PHR_CONFIG_REQ_ADDR + sizeof(LMAC_LPHY_PHR_CONFIG_REQ_STRU))
#define DEDI_GAP_CONFIG_REQ_ADDR          (DEDI_GAP_CONFIG_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DEDI_MAILBOX_DL_END_ADDR*/
#define DEDI_MAILBOX_DL_END_ADDR          (DEDI_GAP_CONFIG_REQ_ADDR + sizeof(LMAC_LPHY_CAP_CONFIG_REQ_STRU))
/*DEDI_MAILBOX_DL_SIZE*/
#define DEDI_MAILBOX_DL_SIZE              (DEDI_MAILBOX_DL_END_ADDR - DEDI_MAILBOX_DL_START_ADDR)

/*****************************************************************************
 ����TB���մ�����У����������У��ܴ�СԤ��Ϊ1kByte
 ˵��:
*****************************************************************************/
#if (LMAC_FEATURE_ON == FEATURE_LMAC_LPHY_R11_CR)
#define LMAC_LPHY_LTE_MASTER_DL_TB_MEM_POOL_QUE_CNT      120                    /*LTE��ģ��TB���ڴ���Դ�ض��г���*/
#define LMAC_LPHY_LTE_SLAVE_DL_TB_MEM_POOL_QUE_CNT       0                      /*LTE��ģ��TB���ڴ���Դ�ض��г���,V7R5ɾ����ģ�ڴ��*/
#define LMAC_LPHY_DL_TB_DATA_IND_QUE_CNT                 120                    /*TB���ϱ����г���*/
#else
#define LMAC_LPHY_LTE_MASTER_DL_TB_MEM_POOL_QUE_CNT      32                     /*LTE��ģ��TB���ڴ���Դ�ض��г���*/
#define LMAC_LPHY_LTE_SLAVE_DL_TB_MEM_POOL_QUE_CNT       8                      /*LTE��ģ��TB���ڴ���Դ�ض��г���*/
#define LMAC_LPHY_DL_TB_DATA_IND_QUE_CNT                 32                     /*TB���ϱ����г���*/

#endif

#define LMAC_LPHY_DLTB_LTE_MASTER_QUEUE_SIZE  (sizeof(L1L2_QUEUE_STRU) + (LMAC_LPHY_LTE_MASTER_DL_TB_MEM_POOL_QUE_CNT * sizeof(VOS_UINT32)))
#define LMAC_LPHY_DLTB_LTE_SLAVE_QUEUE_SIZE   (sizeof(L1L2_QUEUE_STRU) + (LMAC_LPHY_LTE_SLAVE_DL_TB_MEM_POOL_QUE_CNT * sizeof(VOS_UINT32)))
#define LMAC_LPHY_DLTB_DATA_IND_QUEUE_SIZE    (sizeof(L1L2_QUEUE_STRU) + (LMAC_LPHY_DL_TB_DATA_IND_QUE_CNT * sizeof(VOS_UINT32)))

/*DL TB LTE MASTER Queue ADDR*/
#define LMAC_LPHY_LTE_MASTER_DL_TB_MEM_POOL_QUE_ADDR   (LMAC_LPHY_DLTB_QUEUE_START_ADDR)
/*DL TB LTE SLAVE Queue ADDR*/
#define LMAC_LPHY_LTE_SLAVE_DL_TB_MEM_POOL_QUE_ADDR    (LMAC_LPHY_LTE_MASTER_DL_TB_MEM_POOL_QUE_ADDR + LMAC_LPHY_DLTB_LTE_MASTER_QUEUE_SIZE)
/*DL TB LTE DATAIND Queue ADDR*/
#define LMAC_LPHY_DL_TB_DATA_IND_QUE_ADDR              (LMAC_LPHY_LTE_SLAVE_DL_TB_MEM_POOL_QUE_ADDR + LMAC_LPHY_DLTB_LTE_SLAVE_QUEUE_SIZE)

/*DL TB QUEUE END*/
#define LMAC_LPHY_DLTB_QUEUE_END_ADDR                  (LMAC_LPHY_DL_TB_DATA_IND_QUE_ADDR + LMAC_LPHY_DLTB_DATA_IND_QUEUE_SIZE)
/*DL TB QUEUE SIZE*/
#define LMAC_LPHY_DLTB_QUEUE_SIZE                      (LMAC_LPHY_DLTB_QUEUE_END_ADDR - LMAC_LPHY_DLTB_QUEUE_START_ADDR)


#define L1L2_MOD_ADD(x, y, z)               (((x) + (y)) % (z))
#define L1L2_MOD_SUB(x, y, z)               ((((x) + (z)) - (y)) % (z))

#define L1L2_TRUE                           1
#define L1L2_FALSE                          0
/*****************************************************************************
  10 ��������
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

#endif /* end of LMacPhyInterface.h */
