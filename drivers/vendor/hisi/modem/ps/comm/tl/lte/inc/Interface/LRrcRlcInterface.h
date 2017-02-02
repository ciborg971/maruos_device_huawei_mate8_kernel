

#ifndef __LRRCLRLCINTERFACE_H__
#define __LRRCLRLCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "LRrcPdcpInterface.h"
#include "LPSCommon.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define LRRC_LRLC_MSG_HDR             (PS_MSG_ID_RRC_TO_RLC_BASE)
#define LRLC_LRRC_MSG_HDR             (PS_MSG_ID_RLC_TO_RRC_BASE)

#define LPS_MAX_LMBMS_SESSION_NUM     (29)
#define LPS_MAX_LMBMS_PMCH_NUM        (15)
#define LPS_MAX_LMBMS_AREA_NUM        (8)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_MSG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC��RLC��Ľӿ���Ϣ
*****************************************************************************/
enum LRRC_LRLC_MSG_TYPE_ENUM
{

    ID_LRRC_LRLC_CONFIG_REQ               = (LRRC_LRLC_MSG_HDR + 0x00),             /* _H2ASN_MsgChoice LRRC_LRLC_CONFIG_REQ_STRU */      /* RRC���� RLCʵ�� */
    ID_LRRC_LRLC_CONFIG_CNF               = (LRLC_LRRC_MSG_HDR + 0x00),             /* _H2ASN_MsgChoice LRRC_LRLC_CONFIG_CNF_STRU */      /* RRC����AM/UM/TM RLCʵ���ȷ����Ϣ */

    ID_LRRC_LRLC_RELEASE_REQ              = (LRRC_LRLC_MSG_HDR + 0x01),             /* _H2ASN_MsgChoice LRRC_LRLC_RELEASE_REQ_STRU */     /* RRC�ͷ�RLCʵ�� */
    ID_LRRC_LRLC_RELEASE_CNF              = (LRLC_LRRC_MSG_HDR + 0x01),             /* _H2ASN_MsgChoice LRRC_LRLC_RELEASE_CNF_STRU */     /* RRC�ͷ�RLCʵ���ȷ��*/

    ID_LRRC_LRLC_SUSPEND_REQ              = (LRRC_LRLC_MSG_HDR + 0x02),             /* _H2ASN_MsgChoice LRRC_LRLC_SUSPEND_REQ_STRU */     /* RRC����RLCʵ�� */
    ID_LRRC_LRLC_SUSPEND_CNF              = (LRLC_LRRC_MSG_HDR + 0x02),             /* _H2ASN_MsgChoice LRRC_LRLC_SUSPEND_CNF_STRU */     /* RRC����RLCʵ���ȷ��*/

    ID_LRRC_LRLC_RESUME_REQ               = (LRRC_LRLC_MSG_HDR + 0x03),             /* _H2ASN_MsgChoice LRRC_LRLC_RESUME_REQ_STRU */      /* RRC�ָ�RLCʵ�� */
    ID_LRRC_LRLC_RESUME_CNF               = (LRLC_LRRC_MSG_HDR + 0x03),             /* _H2ASN_MsgChoice LRRC_LRLC_RESUME_CNF_STRU */      /* RRC�ָ�RLCʵ���ȷ��*/

    ID_LRRC_LRLC_REESTABLISH_REQ          = (LRRC_LRLC_MSG_HDR + 0x04),             /* _H2ASN_MsgChoice LRRC_LRLC_REETBLSH_REQ_STRU */    /* RRC�ؽ�RLCʵ�� */
    ID_LRRC_LRLC_REESTABLISH_CNF          = (LRLC_LRRC_MSG_HDR + 0x04),             /* _H2ASN_MsgChoice LRRC_LRLC_REETBLSH_CNF_STRU */    /* RRC�ؽ�RLCʵ���ȷ��*/

    ID_LRRC_LRLC_TM_DATA_REQ              = (LRRC_LRLC_MSG_HDR + 0x05),             /* _H2ASN_MsgChoice LRRC_LRLC_TM_DATA_REQ_STRU */     /* RRC����TM��������ԭ�� */
    ID_LRRC_LRLC_TM_DATA_IND              = (LRLC_LRRC_MSG_HDR + 0x05),             /* _H2ASN_MsgChoice LRRC_LRLC_TM_DATA_IND_STRU */     /* RLC���ϱ�TM����ԭ�� */

    ID_LRRC_LRLC_ERROR_IND                = (LRLC_LRRC_MSG_HDR + 0x06),             /* _H2ASN_MsgChoice LRRC_LRLC_ERR_IND_STRU */         /* RLC��ʹ�ô���Ϣ��RRC����RLC����ֵ�����͸�λ����� */

    ID_LRRC_LRLC_MBMS_CFG_REQ             = (LRRC_LRLC_MSG_HDR + 0x06),             /* _H2ASN_MsgChoice LRRC_LRLC_MBMS_CFG_REQ_STRU */      /* RRC���� MBMSҵ���ʵ����Ϣ */
    ID_LRRC_LRLC_MBMS_CFG_CNF             = (LRLC_LRRC_MSG_HDR + 0x07),             /* _H2ASN_MsgChoice LRRC_LRLC_MBMS_CFG_CNF_STRU */      /* RRC����MBMSҵ���ʵ���ȷ����Ϣ */
    ID_LRRC_LRLC_MCCH_DATA_IND            = (LRLC_LRRC_MSG_HDR + 0x08),             /* _H2ASN_MsgChoice LRRC_LRLC_MCCH_DATA_IND_STRU */     /* RLC���ϱ�MCCH����ԭ�� */

    ID_LRRC_LRLC_MSG_TYPE_END
};
typedef VOS_UINT32 LRRC_LRLC_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_SN_FIELD_LENGTH_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC SN field length��ö��
*****************************************************************************/
enum LRRC_LRLC_SN_FIELD_LENGTH_ENUM
{
    LRRC_LRLC_MSGHDR_5BIT                 = 0x0,                                  /*��Ϣͷ��SN�ĳ���Ϊ5BIT*/
    LRRC_LRLC_MSGHDR_10BIT                     ,
    LRRC_LRLC_MSGHDR_BUTT
};
typedef VOS_UINT8   LRRC_LRLC_SN_FIELD_LENGTH_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_ERR_IND_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC����ָʾ��ö��
*****************************************************************************/
enum LRRC_LRLC_ERR_IND_ENUM
{
    LRRC_LRLC_ERR_RL_FAIL                      ,                                  /*��·���ʧ��*/
    LRRC_LRLC_ERR_NORMAL                       ,                                  /*RLC����������*/
    LRRC_LRLC_ERR_MEMFULL                      ,                                  /*RLC�����ڴ���*/
    LRRC_LRLC_ERR_BUTT
};
typedef VOS_UINT8   LRRC_LRLC_ERR_IND_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_RSLT_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC�����õĽ��:�ɹ�����ʧ��
*****************************************************************************/
enum LRRC_LRLC_RSLT_ENUM
{
    LRRC_LRLC_SUCC                            = 0,
    LRRC_LRLC_FAIL                            = 1,
    LRRC_LRLC_RSLT_BUTT
};
typedef VOS_UINT8   LRRC_LRLC_RSLT_ENUM_UINT8;
/*****************************************************************************
 �ṹ��    : LRRC_LRLC_SET_INFO_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����L2 Rlc�����Ϣ
*****************************************************************************/
enum LRRC_LRLC_SET_INFO_TYPE_ENUM
{
    LRRC_LRLC_SET_UECAP                       = 0,                /* ����UE Category */
    LRRC_LRLC_SET_BANDWIDTCH                  = 1,                /* ���ô��� */
    LRRC_LRLC_SET_TYPE_BUTT
};
typedef VOS_UINT8   LRRC_LRLC_SET_INFO_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_LRLC_PARA_VALID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �����Ƿ���Ч��ʶ
*****************************************************************************/
enum LRRC_LRLC_PARA_VALID_ENUM
{
    LRRC_LRLC_PARA_INVALID                = 0,                                    /* ������Ч */
    LRRC_LRLC_PARA_VALID,                                                         /* ������Ч */
    LRRC_LRLC_PARA_BUTT
};
typedef VOS_UINT8 LRRC_LRLC_PARA_VALID_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_LRLC_ENTITY_REL_FALG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ָʾRLCʵ���Ƿ��ͷ�
*****************************************************************************/
enum LRRC_LRLC_ENTITY_REL_FALG_ENUM
{
    LRRC_LRLC_ENTITY_REL_NOT_NEED         = 0,                                    /* ����Ҫ�ͷ� */
    LRRC_LRLC_ENTITY_REL_NEED,                                                    /* ��Ҫ�ͷ� */
    LRRC_LRLC_ENTITY_REL_BUTT
};
typedef VOS_UINT8 LRRC_LRLC_ENTITY_REL_FALG_ENUM_UINT8;
/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_UL_AM_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC AMģʽ���е�������Ϣ
*****************************************************************************/
/*AM��������Ϣ*/
typedef struct
{
    VOS_UINT16                          usPollRetransmitTimer;
    VOS_UINT16                          usPollPDU;

    VOS_UINT16                          usPollByte;

    VOS_UINT8                           ucMaxRetxThreshold;
    VOS_UINT8                           aucRev[1];
}LRRC_LRLC_UL_AM_INFO_STRU;                                                 /* 36.331 6.3.2 �ӿ�����ö��ֵ����ʵ��ֵ? */

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_DL_AM_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC AMģʽ������������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulReorderingTimer;
    VOS_UINT32                          ulTStatusProhibit;
}LRRC_LRLC_DL_AM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_AM_CONFIG_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC AMģʽ��������Ϣ
*****************************************************************************/
typedef struct
{
    LRRC_LRLC_UL_AM_INFO_STRU             stUlAmRlcInfo;
    LRRC_LRLC_DL_AM_INFO_STRU             stDlAmRlcInfo;
}LRRC_LRLC_AM_CONFIG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_UL_UM_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC UMģʽ������������Ϣ
*****************************************************************************/
/*UM��������Ϣ*/
typedef struct
{
    LRRC_LRLC_SN_FIELD_LENGTH_ENUM_UINT8  enSnFieldLength;
    VOS_UINT8                           aucRev[3];
}LRRC_LRLC_UL_UM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_DL_UM_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC UMģʽ������������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulReorderingTimer;

    LRRC_LRLC_SN_FIELD_LENGTH_ENUM_UINT8  enSnFieldLength;
    VOS_UINT8                           aucRev[3];
}LRRC_LRLC_DL_UM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_UM_CONFIG_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC UMģʽ��������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitUlUmFlg      :1;                     /*����UM��RLC�β����Ƿ����*/
    VOS_UINT32                          bitDlUmFlg      :1;                     /*����UM��RLC�β����Ƿ����*/
    VOS_UINT32                          bitSpare        :30;

    LRRC_LRLC_UL_UM_INFO_STRU             stUlUmRlcInfo;
    LRRC_LRLC_DL_UM_INFO_STRU             stDlUmRlcInfo;
}LRRC_LRLC_UM_CONFIG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_UL_LCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC �߼��ŵ����в�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucLchPrio;                      /* 36.331 6.3.2 INTEGER (1..16) */
    VOS_UINT8                                   ucLchGrp;                       /* 36.331 6.3.2 INTEGER (0..3) */
    VOS_UINT16                                  usLchPrioBitRate;               /* 36.331 6.3.2 */
    VOS_UINT16                                  usBucketSizeDuration;           /* 36.331 6.3.2 */
    LRRC_LRLC_PARA_VALID_ENUM_UINT8             enLogicChSrMask;                /* 36.331 6.3.2 logicalChannelSR-Mask-r9 0:��Ч��1:��Ч */
    VOS_UINT8                                   ucRev;
}LRRC_LRLC_UL_LCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_LCH_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC �߼��ŵ�������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitUlLchParaFlg        :1;              /* ָʾ�����߼��ŵ����ò����Ƿ���� */
    VOS_UINT32                          bitSpare               :31;

    LRRC_LRLC_UL_LCH_INFO_STRU          stUlLchInfo;

}LRRC_LRLC_LCH_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_CONFIG_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC->RLC��������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                             ucRbId;
    LRLC_MODE_ENUM_UINT8                  enRlcMode;
    /* ָʾRLCʵ���Ƿ���Ҫ���ͷ�������,0:����Ҫ�ͷ�,1:��Ҫ���ͷ�,Ȼ��������²�����������  */
    LRRC_LRLC_ENTITY_REL_FALG_ENUM_UINT8  enRelInd;
    VOS_UINT8                             ucLchId;
    LRRC_LRLC_LCH_CONFIG_STRU             stLchCfg;

    union
    {
        LRRC_LRLC_AM_CONFIG_INFO_STRU     stAmInfo;
        LRRC_LRLC_UM_CONFIG_INFO_STRU     stUmInfo;
    }u;
}LRRC_LRLC_CONFIG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_CONFIG_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC->RLC��������Ϣ
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* ��Ϣ���� */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;

    VOS_UINT8                             ucRbNum;
    VOS_UINT8                             ucRev;
    LRRC_LRLC_CONFIG_INFO_STRU            astRlcInfo[PS_MAX_RB_NUM];
}LRRC_LRLC_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_CONFIG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC->RRC��ȷ����Ϣ
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* ��Ϣ���� */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;

    LRRC_LRLC_RSLT_ENUM_UINT8             enResult;
    VOS_UINT8                             ucRev;
}LRRC_LRLC_CONFIG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_RELEASE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC->RLC���ͷţ����𣬻ָ���Ϣ
*****************************************************************************/
/*Release, supend��Ϣ*/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* ��Ϣ���� */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32      enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;

    VOS_UINT8                           ucRbNum;
    VOS_UINT8                           ucRev;
    VOS_UINT8                           aucRbId[PS_MAX_RB_NUM];
}LRRC_LRLC_RELEASE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_RELEASE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC->RLC���ͷ���Ӧ��Ϣ
*****************************************************************************/
typedef LRRC_LRLC_CONFIG_CNF_STRU LRRC_LRLC_RELEASE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_SUSPEND_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC->RLC�Ĺ�����Ϣ
*****************************************************************************/
/*Release, supend��Ϣ*/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* ��Ϣ���� */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;

    VOS_UINT8                           ucRbNum;
    VOS_UINT8                           ucRev;
    VOS_UINT8                           aucRbId[PS_MAX_RB_NUM];
}LRRC_LRLC_SUSPEND_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_SUSPEND_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC->RLC�Ĺ�����Ӧ��Ϣ
*****************************************************************************/
typedef LRRC_LRLC_CONFIG_CNF_STRU LRRC_LRLC_SUSPEND_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_RESUME_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC->RLC�Ļָ�Ϣ
*****************************************************************************/
/*Release, supend��Ϣ*/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* ��Ϣ���� */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;

    VOS_UINT8                           ucRbNum;
    VOS_UINT8                           ucRev;
    VOS_UINT8                           aucRbId[PS_MAX_RB_NUM];
}LRRC_LRLC_RESUME_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_RESUME_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC->RLC�Ļָ���Ӧ��Ϣ
*****************************************************************************/
typedef LRRC_LRLC_CONFIG_CNF_STRU LRRC_LRLC_RESUME_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RLC_RETBLSH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC-RLC��ʵ���ؽ���Ϣ
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* ��Ϣ���� */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;

    VOS_UINT8                           ucRev[2];
}LRRC_LRLC_REETBLSH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_TM_DATA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRsv[3];

    VOS_UINT32                          ulDataLength;
    VOS_UINT8                           aucData[4];
} LRRC_LRLC_TM_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_TM_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32       enMsgName;                              /*_H2ASN_Skip*/

    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRsv[3];

    VOS_UINT32                          ulDataLength;
    VOS_UINT8                           aucData[4];
} LRRC_LRLC_TM_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_REETBLSH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC->RLC���ؽ���Ӧ��Ϣ
*****************************************************************************/
typedef LRRC_LRLC_CONFIG_CNF_STRU LRRC_LRLC_REETBLSH_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_MBMS_PMCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC->RLC��MBMS������Ϣ
*****************************************************************************/
typedef struct
{
    /*bit0:��ʾ�߼��ŵ�0�Ƿ���Ч��1��ʾ��Ч��0��ʾ��Ч��bitλ:1-28�ֱ��ʾ�߼��ŵ�1-28��
    ����λ29-31����������д0*/
    VOS_UINT32                          ulMbmsLchInfo;
}LRRC_LRLC_MBMS_PMCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_MBMS_AREA_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC->RLC��MBMS������Ϣ,����astLMbmsPmchֵΪ0��ʾ��ӦPMCH��Ч��
             ����astLMbmsPmchֵ��Ϊ0��ʾPMCH��Ӧ��Ч�������±��ӦPMCH����0-14
*****************************************************************************/
typedef struct
{
    VOS_UINT8                             ucLMbmsAreaId;
    VOS_UINT8                             aucRev[3];
    LRRC_LRLC_MBMS_PMCH_INFO_STRU         astLMbmsPmch[LPS_MAX_LMBMS_PMCH_NUM];
}LRRC_LRLC_MBMS_AREA_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LRRC_LRLC_MBMS_CFG_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC->RLC��MBMS������Ϣ
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* ��Ϣ���� */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                            usOpId;

    VOS_UINT8                             ucLMbmsAreaNum;
    VOS_UINT8                             ucRev;
    LRRC_LRLC_MBMS_AREA_INFO_STRU         astLMbmsAreaInfo[LPS_MAX_LMBMS_AREA_NUM];

}LRRC_LRLC_MBMS_CFG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_MBMS_CFG_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC->RLC��MBMS������Ӧ��Ϣ
*****************************************************************************/
typedef LRRC_LRLC_CONFIG_CNF_STRU LRRC_LRLC_MBMS_CFG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_MCCH_DATA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    /* ��Ϣ���� */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32          enMsgName;                          /*_H2ASN_Skip*/

    VOS_UINT8                               ucAreaId;
    VOS_UINT8                               aucRsv1[3];

    VOS_UINT16                              usFrame;                            /*�տڽ���MCCH��Ϣ��֡��*/
    VOS_UINT8                               ucSubFrame;                         /*�տڽ���MCCH��Ϣ����֡��*/
    VOS_UINT8                               aucRsv2[1];

    VOS_UINT32                              ulDataLength;
    VOS_UINT8                               aucData[4];
} LRRC_LRLC_MCCH_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : LRRC_LRLC_ERR_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC-RRC�Ĵ���ָʾ
*****************************************************************************/
typedef struct
{
    /* ��Ϣͷ */
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    /* ��Ϣ���� */
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgName;                            /*_H2ASN_Skip*/

    LRRC_LRLC_ERR_IND_ENUM_UINT8          enErrType;
    VOS_UINT8                             ucRbId;                               /*�����ؽ�����RbId*/
    VOS_UINT16                            usSn;                                 /*�����ؽ�����sn*/
}LRRC_LRLC_ERR_IND_STRU;

typedef struct
{
    LRRC_LRLC_MSG_TYPE_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export LRRC_LRLC_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LRRC_LRLC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LRRC_LRLC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    LRRC_LRLC_MSG_DATA                    stMsgData;
}RrcRlcInterface_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
 /* ����L2 �����Ϣ������ ucInitType=1��ulInitValue�������õ���UE��������
    ucInitType=1��ulInitValue�������õ�ʱС�����д���*/
 extern VOS_VOID FC_InitFlowCtrlPara(VOS_UINT8 ucInitType,VOS_UINT32 ulInitValue);


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
