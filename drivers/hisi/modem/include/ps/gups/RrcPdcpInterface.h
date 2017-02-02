/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : RrcPdcpInterface.h
  �� �� ��   : ����
  ��    ��   : Jinying
  ��������   : 2006��9��1��
  ����޸�   :
  ��������   : RrcPdcpInterface.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2006��9��1��
    ��    ��   : Jinying
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __RRCPDCPINTERFACE_H__
#define __RRCPDCPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "WUeSpec.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum RRC_PDCP_MSG_TYPE_ENUM
{
    ID_RRC_PDCP_CONFIG_REQ          = 0x0000,   /* _H2ASN_MsgChoice RRC_PDCP_CONFIG_REQ_STRU   */
    ID_PDCP_RRC_CONFIG_CNF          = 0x0001,   /* _H2ASN_MsgChoice PDCP_RRC_CONFIG_CNF_STRU   */
    ID_RRC_PDCP_RELEASE_REQ         = 0x0002,   /* _H2ASN_MsgChoice RRC_PDCP_RELEASE_REQ_STRU  */
    ID_PDCP_RRC_RELEASE_CNF         = 0x0003,   /* _H2ASN_MsgChoice PDCP_RRC_RELEASE_CNF_STRU  */
    ID_RRC_PDCP_SYNC_REQ            = 0x0004,   /* _H2ASN_MsgChoice RRC_PDCP_SYNC_REQ_STRU     */
    ID_PDCP_RRC_SYNC_CNF            = 0x0005,   /* _H2ASN_MsgChoice PDCP_RRC_SYNC_CNF_STRU     */
    ID_RRC_PDCP_STOP_REQ            = 0x0006,   /* _H2ASN_MsgChoice RRC_PDCP_STOP_REQ_STRU     */
    ID_PDCP_RRC_STOP_CNF            = 0x0007,   /* _H2ASN_MsgChoice PDCP_RRC_STOP_CNF_STRU     */
    ID_RRC_PDCP_CONTINUE_REQ        = 0x0008,   /* _H2ASN_MsgChoice RRC_PDCP_CONTINUE_REQ_STRU  */
    ID_PDCP_RRC_CONTINUE_CNF        = 0x0009,   /* _H2ASN_MsgChoice PDCP_RRC_CONTINUE_CNF_STRU  */
    ID_RRC_PDCP_RELOC_REQ           = 0x000A,   /* _H2ASN_MsgChoice RRC_PDCP_RELOC_REQ_STRU       */
    ID_PDCP_RRC_RELOC_CNF           = 0x000B,   /* _H2ASN_MsgChoice PDCP_RRC_RELOC_CNF_STRU    */
    ID_RRC_PDCP_DLSIZE_CHANGE_REQ   = 0x000C,   /* _H2ASN_MsgChoice RRC_PDCP_DLSIZE_CHANGE_REQ_STRU */
    ID_PDCP_RRC_DLSIZE_CHANGE_CNF   = 0x000D,   /* _H2ASN_MsgChoice PDCP_RRC_DLSIZE_CHANGE_CNF_STRU */
    ID_RRC_PDCP_COMPRESS_INI_REQ    = 0x000E,   /* _H2ASN_MsgChoice RRC_PDCP_COMPRESS_INI_REQ_STRU  */
    ID_PDCP_RRC_COMPRESS_INI_CNF    = 0x000F,   /* _H2ASN_MsgChoice PDCP_RRC_COMPRESS_INI_CNF_STRU  */
    ID_PDCP_RRC_ERROR_IND           = 0x0011,   /* _H2ASN_MsgChoice PDCP_RRC_ERROR_IND_STRU    */

    ID_PDCP_RRC_MSG_TYPE_BUTT
};
typedef VOS_UINT16 RRC_PDCP_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : RRC_PDCP_CFG_MODE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP����ģʽ���ǳ�ʼ���û�������: ȡֵΪPDCP_INIT_MODE�Ⱥ궨��
*****************************************************************************/
enum RRC_PDCP_CFG_MODE_ENUM
{
    RRC_PDCP_CFG_MODE_SETUP             = 0,
    RRC_PDCP_CFG_MODE_RECFG             = 1,
    RRC_PDCP_CFG_MODE_BUTT
};
typedef VOS_UINT8   RRC_PDCP_CFG_MODE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : PDCPITF_RLC_MODE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP��Ӧ��RLC��ģʽ
*****************************************************************************/
enum PDCPITF_RLC_MODE_ENUM
{
    PDCPITF_RLC_AM_IN_SEQ               = 0,
    PDCPITF_RLC_AM_OUT_OF_SEQ           = 1,
    PDCPITF_RLC_UM_MODE                 = 2,
    PDCPITF_RLC_TM_MODE                 = 3,

    PDCPITF_RLC_MODE_BUTT
};
typedef VOS_UINT8   PDCPITF_RLC_MODE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : PDCPITF_RSLT_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP���÷���ֵ
*****************************************************************************/
enum PDCPITF_RSLT_ENUM
{
    PDCPITF_SUCC                    = 0,
    PDCPITF_FAIL                       ,
    PDCPITF_RSLT_BUTT
};
typedef VOS_UINT32 PDCPITF_RSLT_ENUM_UINT32;

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
 �ṹ��    : PDCPITF_RFC2507_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ѹ���㷨RFC_2507����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFMaxTime;         /* INTEGER(1..255)  DEFAULT(5),ȫͷ֮�䷢��ѹ��ͷ�����ʱ�� */
    VOS_UINT8                           ucTcpSpace;         /* INTEGER(3..255)  DEFAULT(15),TCP���ӵ����CIDֵ */
    VOS_UINT16                          usFMaxPeriod;       /* INTEGER(1..65535)  DEFAULT(256),ȫͷ֮�䷢��ѹ��ͷ�������� */
    VOS_UINT16                          usMaxHeader;        /* INTEGER(60..65535)  DEFAULT(168),���Ա�ѹ�������ͷ�ĳ��� */
    VOS_UINT16                          usNonTcpSpace;      /* INTEGER(3..65535)  DEFAULT(15),��TCP���ӵ����CIDֵ  */
    PS_BOOL_ENUM_UINT8                  enExpReord;         /* ENUMERATED ,�㷨�Ƿ�֧��������*/
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
}PDCPITF_RFC2507_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PDCPITF_COMPRS_ALG_CHOICE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP��Ϣ����
*****************************************************************************/
typedef struct
{
    /* PDCP ֧�ֵ��㷨���� */
    #define    PDCPITF_HEAD_COMPRS_RFC2507_CHOSEN    0
    #define    PDCPITF_HEAD_COMPRS_RFC3095_CHOSEN    1

    VOS_UINT32                          ulAlgChoice;        /* ���õ�ѹ���㷨 */
    union
    {
        PDCPITF_RFC2507_INFO_STRU       stRfc2507Info;
        PS_NULL_STRU                    stRfc3095Info;
    }u;                                                     /* �ɹ�ѡ���ѹ���㷨 */
}PDCPITF_COMPRS_ALG_CHOICE_STRU;

/*****************************************************************************
 �ṹ��    : PDCPITF_PDCP_INFO_STRU
 Э����  :
 ASN.1���� : PDCP_Info_r4
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ASN.1 �ı� : LosslessSRNS-RelocSupport */
    PS_BOOL_ENUM_UINT8                  enSprtLossless;             /* [TRUE,FALSE]�Ƿ�֧��lossless SRNS relocation�ı�־ */
    /* ASN.1 �ı� : PDCP-PDU-Header */
    PS_BOOL_ENUM_UINT8                  enPdcpPduHead;              /* [TRUE,FALSE]�Ƿ���PDCP PDU header�ı�־ */
    VOS_UINT16                          usMaxPdcpWndSize;           /* sn255, sn65535,֧������ʱ��Я����[0, PDCP_MAX_SND_WIN] ����PDCP SN window size */
    /* ASN.1 �ı� : HeaderCompressionInfoList-r4 */
    VOS_UINT8                           aucReserve1[2];             /* 4�ֽڶ��룬���� */
    VOS_UINT16                          usCnt;                      /* [0,PS_WUE_MAX_PDCP_ALGO_TYPE_NUM]ѹ���㷨����                            */
    PDCPITF_COMPRS_ALG_CHOICE_STRU      astHeadComprs[PS_WUE_MAX_PDCP_ALGO_TYPE_NUM];
}PDCPITF_PDCP_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PDCP_CONFIG_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_PDCP_CONFIG_REQ ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,��Ӧ��ԭ���Ӧ */
    VOS_UINT8                           ucRbId;             /* Ψһ��־PDCPʵ�� */
    RRC_PDCP_CFG_MODE_ENUM_UINT8        enCfgMode;          /* PDCP����ģʽ�������û������� */
    PDCPITF_RLC_MODE_ENUM_UINT8         enRlcMode;          /* PDCPʵ�����ݴ�����õĵ�RLCģʽ */
    PS_BOOL_ENUM_UINT8                  enPPPFlg;           /* TRUE��pppͷ, FALSE:����pppͷ */
    PDCPITF_PDCP_INFO_STRU              stPdcpInfo;         /* PDCPʵ����Ϣ */
}RRC_PDCP_CONFIG_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PDCP_RRC_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP_RRC_CONFIG_CNF ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,������ԭ���Ӧ */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;             /* ���ý�� */
}PDCP_RRC_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PDCP_RELEASE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_PDCP_RELEASE_REQ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,������ԭ���Ӧ */
    VOS_UINT8                           ucRbCnt;            /* [0, PDCP_MAX_ENT_NUM],�ͷŵ�PDCPʵ������0�����ͷ����е�PDCPʵ�� */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_PS_RB_NUM];   /* ��־PDCPʵ�� */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_PDCP_RELEASE_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PDCP_RRC_RELEASE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP_RRC_RELEASE_CNF����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,������ԭ���Ӧ */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;
}PDCP_RRC_RELEASE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PDCP_SYNC_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_PDCP_SYNC_REQ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,������ԭ���Ӧ */
    VOS_UINT8                           ucRbCnt;            /* [0, UU_MAX_RB],RB���� */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_PS_RB_NUM];  /* ��־PDCPʵ�� */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
} RRC_PDCP_SYNC_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PDCP_RRC_SYNC_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP_RRC_SYNC_CNF����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,������ԭ���Ӧ */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;             /* 0:��ʾ�ɹ���1��ʵ�岻���ڣ�2����֧�������ض�λ   */
}PDCP_RRC_SYNC_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PDCP_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_PDCP_STOP_REQ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,������ԭ���Ӧ */
    VOS_UINT8                           ucRbCnt;            /* ʵ����� */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_PS_RB_NUM];
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_PDCP_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PDCP_RRC_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP_RRC_STOP_CNF����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,������ԭ���Ӧ */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;             /* VOS_OK:�ɹ���VOS_ERR��ʧ��  */
}PDCP_RRC_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PDCP_CONTINUE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_PDCP_CONTINUE_REQ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,������ԭ���Ӧ */
    VOS_UINT8                           ucRbCnt;            /* ʵ����� */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_PS_RB_NUM];
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_PDCP_CONTINUE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PDCP_RRC_CONTINUE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_PDCP_CONTINUE_CNF ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,������ԭ���Ӧ */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;
}PDCP_RRC_CONTINUE_CNF_STRU;


/*****************************************************************************
 �ṹ��    : PDCP_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_PDCP_RELOC_REQ ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucRbId;             /* ��־PDCPʵ��               */
    VOS_UINT16                          usReceiveSN;        /* UTRAN��һ���������յ����к� */
}PDCP_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PDCP_RELOC_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCPǨ������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,������ԭ���Ӧ */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucCnt;              /* ʵ����� */
    PDCP_INFO_STRU                      astPdcpSNInfo[PS_WUE_MAX_PS_RB_NUM];
}RRC_PDCP_RELOC_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PDCP_RCVSN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP_RCVSN_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucRbId;             /* ��־PDCPʵ�� */
    VOS_UINT16                          usReceiveSN;        /* UE��һ���������յ����к� */
}PDCP_RCVSN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PDCP_RRC_RELOC_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ǩ����Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,������ԭ���Ӧ */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucCnt;              /* ʵ����� */
    PDCP_RCVSN_INFO_STRU                astRcvSnInfo[PS_WUE_MAX_PS_RB_NUM];
    PDCPITF_RSLT_ENUM_UINT32            enRslt;             /* ��ʾ�ɹ���ʧ�� */
}PDCP_RRC_RELOC_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PDCP_DLSIZE_CHANGE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_PDCP_DLSIZE_CHANGE_REQ ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,��Ӧ��ԭ���Ӧ */
    VOS_UINT8                           ucRbCnt;            /* ʵ����� */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_PS_RB_NUM];   /* RbID �б� */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_PDCP_DLSIZE_CHANGE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PDCP_RRC_DLSIZE_CHANGE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP_RRC_DLSIZE_CHANGE_CNF ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,������ԭ���Ӧ */
    VOS_UINT8                           aucReserve1[3];     /* 4�ֽڶ��룬���� */
    VOS_UINT8                           ucCnt;              /* ʵ����� */
    PDCP_RCVSN_INFO_STRU                astRcvSnInfo[PS_WUE_MAX_PS_RB_NUM];      /* �ض�λ��Ϣ�б� */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;             /* 0:��ʾ�ɹ���1��ʵ�岻���ڣ�2����֧����������PDU ��С�ı� */
}PDCP_RRC_DLSIZE_CHANGE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PDCP_COMPRESS_INI_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC_PDCP_COMPRESS_INI_REQ ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���ͱ�ʶ */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,��Ӧ��ԭ���Ӧ */
    VOS_UINT8                           ucRbCnt;            /* ʵ����� */
    VOS_UINT8                           aucRbId[PS_WUE_MAX_PS_RB_NUM];/* ʵ���б� */
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
}RRC_PDCP_COMPRESS_INI_REQ_STRU;


/*****************************************************************************
 �ṹ��    : PDCP_RRC_COMPRESS_INI_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP_RRC_COMPRESS_INI_CNF����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;             /* ������,������ԭ���Ӧ */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;
} PDCP_RRC_COMPRESS_INI_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PDCP_RRC_ERROR_IND
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP_RRC_ERROR_IND ����,PDCP�쳣֪ͨRRC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */    /*_H2ASN_Skip*/
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */  /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve1[2];     /* 4�ֽڶ��룬���� */
    PDCPITF_RSLT_ENUM_UINT32            enRslt;
} PDCP_RRC_ERROR_IND_STRU;


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


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
    RRC_PDCP_MSG_TYPE_ENUM_UINT16       enMsgID;    /*_H2ASN_MsgChoice_Export RRC_PDCP_MSG_TYPE_ENUM_UINT16*/

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RRC_PDCP_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}RRC_PDCP_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    RRC_PDCP_MSG_DATA                   stMsgData;
}RrcPdcpInterface_MSG;


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

#endif /* end of RrcPdcpInterface.h */
