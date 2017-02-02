

#ifndef __TLL2ErrorLog_H__
#define __TLL2ErrorLog_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "product_config.h"
#include "omnvinterface.h"
#include "omerrorlog.h"
#include "omringbuffer.h"
#include "SysNvId.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define TLL2_LTE_RING_BUFFER_SIZE    (1024 * 4)  /* TLL2_LTE errlog ����buffer�Ĵ�С */
#define TLL2_TDS_RING_BUFFER_SIZE    (1024 * 4)  /* TLL2_TDS errlog ����buffer�Ĵ�С */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 ö����    : TLL2_ERRLOG_MODEM_ID_ENUM
 ö��˵��  : TLL2 MODEM_ID
*****************************************************************************/
enum TLL2_ERRLOG_MODEM_ID_ENUM
{
    TLL2_ERRLOG_MODEM_ID_0        = 0x00 ,      /* ���� */
    TLL2_ERRLOG_MODEM_ID_1        = 0x01 ,      /* ���� */
    TLL2_ERRLOG_MODEM_ID_REV1     = 0x02 ,      /* ���� */
    TLL2_ERRLOG_MODEM_ID_REV2     = 0x03 ,      /* ���� */

    TLL2_ERRLOG_MODEM_ID_BUTT
};
typedef VOS_UINT16 TLL2_ERRLOG_MODEM_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : TLL2_ERRLOG_ALM_LEVEL_ENUM
 ö��˵��  : TLL2�澯����
*****************************************************************************/
enum TLL2_ERRLOG_ALM_LEVEL_ENUM
{
    TLL2_ERRLOG_ALM_LEVEL_CRITICAL   = 0x01,        /*����*/
    TLL2_ERRLOG_ALM_LEVEL_MAJOR      = 0x02,        /*��Ҫ*/
    TLL2_ERRLOG_ALM_LEVEL_MINOR      = 0x03,        /*��Ҫ*/
    TLL2_ERRLOG_ALM_LEVEL_WARNING    = 0x04,        /*��ʾ*/

    TLL2_ERRLOG_ALM_LEVEL_BUTT
};
typedef VOS_UINT16  TLL2_ERRLOG_ALM_LEVEL_ENUM_UINT16;

/*****************************************************************************
 ö����    : TLL2_ERRLOG_ALM_TYPE_ENUM
 ö��˵��  : TLL2�澯 ����
*****************************************************************************/
enum TLL2_ERRLOG_ALM_TYPE_ENUM
{
    TLL2_ERRLOG_ALM_TYPE_COMMUNICATION          = 0x00,     /* ͨ��*/
    TLL2_ERRLOG_ALM_TYPE_QUALITY_OF_SERVICE     = 0x01,     /* ҵ������*/
    TLL2_ERRLOG_ALM_TYPE_PROCESS_ERROR          = 0x02,     /* �������*/
    TLL2_ERRLOG_ALM_TYPE_EQUIPMENT_ERROR        = 0x03,     /* �豸����*/
    TLL2_ERRLOG_ALM_TYPE_ENVIRONMENTAL_ERROR    = 0x04,     /* ��������*/

    TLL2_ERRLOG_ALM_TYPE_BUTT
};
typedef VOS_UINT16  TLL2_ERRLOG_ALM_TYPE_ENUM_UINT16;



/*****************************************************************************
 ö����    : TLL2_LTE_ERROR_ALARM_ID_ENUM
 ö��˵��  : TLL2_LTE �澯ID
*****************************************************************************/
enum TLL2_LTE_ERROR_ALARM_ID_ENUM
{
    TLL2_LMAC_RAR_NOTMATCH = 1,
    TLL2_LMAC_RAR_TIMEOUT,
    TLL2_LMAC_CONTENT_TIMEOUT,
    TLL2_LMAC_CONTENT_NOTMATCH,
    TLL2_LMAC_OVER_PBL_MAX_TXNUM,
    TLL2_LMAC_MSG3_FAIL,
    TLL2_LMAC_TA_TIMEOUT,
    TLL2_LMAC_OVER_MAX_SR_SEND,
    TLL2_LRLC_UL_AM_MAX_RETXNUM,
    TLL2_LRLC_DL_TBMEM_FULL,
    TLL2_LPDCP_ERROR_INTEGRITY_VERIFY,

    TLL2_LMAC_SCHED_INFO,
    TLL2_LRLC_UL_INFO,
    TLL2_LRLC_DL_INFO,
    TLL2_LPDCP_UL_INFO,
    TLL2_LPDCP_DL_INFO,
    TLL2_LTE_STATS_INFO,
    TLL2_LTE_BUFFER_OVERFLOW,
    TLL2_LTE_ERRLOG_ALARM_ID_BUTT
};
typedef VOS_UINT16 TLL2_LTE_ERROR_ALARM_ID_ENUM_UINT8;

/*****************************************************************************
 ö����    : TLL2_TDS_ERROR_ALARM_ID_ENUM
 ö��˵��  : TLL2_TDS �澯ID
*****************************************************************************/
enum TLL2_TDS_ERROR_ALARM_ID_ENUM
{
    TLL2_TMAC_OUT_OF_SYNC = 1,
    TLL2_TMAC_QUEUE_FULL,
    TLL2_TMAC_SENDMSG_FAIL,
    TLL2_TRLC_RST,
    TLL2_TRLC_UL_BUFFER_FULL,
    TLL2_TPDCP_FAIL,
    TLL2_TMAC_HSUPA_INFO,
    TLL2_TMAC_HSDPA_INFO,
    TLL2_TRLC_UL_TRANS_INFO,
    TLL2_TRLC_DL_TRANS_INFO,
    TLL2_TRLC_STATICS_INFO,

    TLL2_TDS_BUFFER_OVERFLOW,
    TLL2_TDS_ERRLOG_ALARM_ID_BUTT
};
typedef VOS_UINT16 TLL2_TDS_ERROR_ALARM_ID_ENUM_UINT8;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_RAR_NOTMATCH_INFO
 �ṹ˵��  : MAC ���������ͷƥ��ʧ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT16                          usFrame;        /*֡��*/
    VOS_UINT8                           ucSubFrame;     /*��֡��*/
    VOS_UINT8                           ucMatchFlag;    /*��ͷƥ��ɹ�ָʾ��0:ʧ�ܣ�1:�ɹ�*/
    VOS_UINT8                           ucBiFlag;       /*BIֵָʾ��0:��Ч��1:��Ч*/
    VOS_UINT8                           ucBiIndex;      /*BIֵ����*/
    VOS_UINT8                           aucRev[2];      /*4�ֽڶ���*/
}LTE_ERRLOG_MAC_RAR_NOTMATCH_INFO;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_RAR_TIMEROUT_INFO
 �ṹ˵��  : MAC ����RAR��ʱ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT8                           enTimerID;
    VOS_UINT8                           aucRev[3];      /*4�ֽڶ���*/
}LTE_ERRLOG_MAC_RAR_TIMEROUT_INFO;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_CONTENTION_TIMEROUT_INFO
 �ṹ˵��  : MAC ���վ��������Ϣ��ʱ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT8                           enTimerID;
    VOS_UINT8                           aucRev[3];      /*4�ֽڶ���*/
}LTE_ERRLOG_MAC_CONTENTION_TIMEROUT_INFO;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_CONTENT_NOTMATCH_INFO
 �ṹ˵��  : MAC ����Msg4ͷ����,Msg4ƥ��ʧ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT8                           enMatchFlg;
    VOS_UINT8                           aucRev[3];      /*4�ֽڶ���*/
}LTE_ERRLOG_MAC_CONTENT_NOTMATCH_INFO;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_OVER_PBL_MAX_TXNUM_INFO
 �ṹ˵��  : MAC �������Preamble�ﵽ����ʹ���
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT8                           ucRaTxNum;      /*��������ط���������*/
    VOS_UINT8                           ucPblMaxTxNum;  /*�������Preamble����ʹ���*/
    VOS_UINT8                           aucRev[2];      /*4�ֽڶ���*/
}LTE_ERRLOG_MAC_OVER_PBL_MAX_TXNUM_INFO;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_MSG3_FAIL_INFO
 �ṹ˵��  : Msg3����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT32                          ulTbSize;
    VOS_UINT16                          usSendFrame;
    VOS_UINT8                           ucSendSubFrame;
    VOS_UINT8                           ucSchedValid;
    VOS_UINT8                           ucHarqId;       /*����ʱ��HARQ���̺�*/
    VOS_UINT8                           enSchedMode;
    VOS_UINT8                           ucPucchEnable;  /*����ʱ���Ƿ����PUCCH����*/
    VOS_UINT8                           aucRev;         /*4�ֽڶ���*/
}LTE_ERRLOG_MAC_MSG3_FAIL_INFO;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_TA_TIME_OUT_INFO
 �ṹ˵��  : MAC ta ��ʱ����ʱ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT32                          ulTaTimeOutNum;
    VOS_UINT8                           enTimerID;
    VOS_UINT8                           aucRev[3];      /*4�ֽڶ���*/
}LTE_ERRLOG_MAC_TA_TIME_OUT_INFO;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_OVER_MAX_SR_SEND_INFO
 �ṹ˵��  : MAC ���������ʹﵽ������
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;           /* ERR LOG��Ϣͷ */
    VOS_UINT16                          usSrDynMaxNum;
    VOS_UINT16                          usSrLastFrame;      /*SR�ϴη��͵�֡��*/
    VOS_UINT8                           ucSrLastSubFrame;   /*SR�ϴη��͵���֡��*/
    VOS_UINT8                           ucSrCounter;        /*SR�ۼƴ���*/
    VOS_UINT8                           aucRev[2];          /*4�ֽڶ���*/
}LTE_ERRLOG_MAC_OVER_MAX_SR_SEND_INFO;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_UL_AM_MAX_RETXNUM_INFO
 �ṹ˵��  : RLC����AM�ش��ﵽ������
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;           /* ERR LOG��Ϣͷ */
    VOS_UINT32                          ulPduMaxRetxNum;    /*�����ش�����*/
    VOS_UINT32                          ulPduSn;
    VOS_UINT16                          usRetxNum;
    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRev;             /*4�ֽڶ���*/
}LTE_ERRLOG_RLC_UL_AM_MAX_RETXNUM_INFO;


/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_DL_TBMEM_FULL_INFO
 �ṹ˵��  : RLC����TB�ڴ���
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRev[3];      /*4�ֽڶ���*/
}LTE_ERRLOG_RLC_DL_TBMEM_FULL_INFO;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_ERROR_INTEGRITY_VERIFY_INFO
 �ṹ˵��  : PDCP ��������֤����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucRev[3];      /*4�ֽڶ���*/
}LTE_ERRLOG_PDCP_ERROR_INTEGRITY_VERIFY_INFO;

/*****************************************************************************
 �ṹ��    : TDS_ERRLOG_MAC_OUTOFSYNC_INFO
 �ṹ˵��  : MACʧ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;           /* ERR LOG��Ϣͷ */
    VOS_UINT8                           cause;              /*T312 expired��0��T313 expired��1*/
    VOS_UINT8                           inActivationTime;
    VOS_UINT8                           tfcsIdentity;
    VOS_UINT8                           aucRev;             /*4�ֽڶ���*/
}TDS_ERRLOG_MAC_OUTOFSYNC_INFO;

/*****************************************************************************
 �ṹ��    : TDS_ERRLOG_MAC_QUEUEFULL_INFO
 �ṹ˵��  : MAC�������ṹ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT32                          LossMsgID;
}TDS_ERRLOG_MAC_QUEUEFULL_INFO;

/*****************************************************************************
 �ṹ��    : TDS_ERRLOG_MAC_SENDMSGFAIL_INFO
 �ṹ˵��  : MAC��Ϣ����ʧ�ܽṹ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT32                          FailMsgID;
}TDS_ERRLOG_MAC_SENDMSGFAIL_INFO;

/*****************************************************************************
 �ṹ��    : TDS_ERRLOG_RLC_RST_INFO
 �ṹ˵��  : RLC RST��Ϣ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT8                           rbIdentity;
    VOS_UINT8                           aucRev[3];      /*4�ֽڶ���*/
}TDS_ERRLOG_RLC_RST_INFO;

/*****************************************************************************
 �ṹ��    : TDS_ERRLOG_RLC_UL_BUFFERFULL_INFO
 �ṹ˵��  : RLC UL buffer ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT8                           rbIdentity;
    VOS_UINT8                           aucRev[3];      /*4�ֽڶ���*/
}TDS_ERRLOG_RLC_UL_BUFFERFULL_INFO;


/*****************************************************************************
 �ṹ��    : TDS_ERRLOG_PDCP_FAIL_INFO
 �ṹ˵��  : pdcp������Ϣ�ϱ�����
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT32                          failCause;
}TDS_ERRLOG_PDCP_FAIL_INFO;


/*****************************************************************************
 �ṹ��    : TLL2_ERRLOG_BUFFER_OVERFLOW_STRU
 �ṹ˵��  :���������
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;       /* ERR LOG��Ϣͷ */
    VOS_UINT32                          ulCount;        /* ������������� */
}TLL2_ERRLOG_BUFFER_OVERFLOW_STRU;

/*****************************************************************************
 �ṹ��    : LTE_MAC_SCHED_INFO_STRU
 �ṹ˵��  : LTE L2 MAC���е�����Ϣ�ṹ��
*****************************************************************************/

typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                          usFrameNo;          /*֡��*/
    VOS_UINT16                          usSubFrameNo;       /*��֡��*/

    VOS_UINT8                           ucShortBsrGrpId;    /*��BSR group ID��*/
    VOS_UINT8                           ucShortBsrValue;    /*��BSR ֵ*/
    VOS_UINT8                           ucLongBsr0Value;    /* group 0��BSRֵ*/
    VOS_UINT8                           ucLongBsr1Value;    /* group 1��BSRֵ*/

    VOS_UINT8                           ucLongBsr2Value;    /* group 2��BSRֵ*/
    VOS_UINT8                           ucLongBsr3Value;    /* group 3��BSRֵ*/
    VOS_UINT16                          usRsv;              /*�����ֶ�*/
    VOS_UINT32                          ulUlGrantSize;      /* ������Ȩֵ*/
}LTE_ERRLOG_MAC_SCHED_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LTE_RLC_UL_TRANS_INFO_STRU
 �ṹ˵��  : LTE L2 RLC����������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU               stHeader;

    VOS_UINT16                           usFrameNo;         /*֡��*/
    VOS_UINT16                           usSubFrameNo;      /*��֡��*/

    VOS_UINT16                           usRbId;            /*RB ID*/
    VOS_UINT16                           usTransSn;         /*���͵�RLC PDU SNֵ*/

    VOS_UINT16                           usVTs;             /*RLC VTS*/
    VOS_UINT16                           usVTa;             /*RLC VTA*/

    VOS_UINT32                           ulReTxSn;          /*RLC �����ش�SNֵ*/

}LTE_ERRLOG_RLC_UL_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_RLC_DL_TRANS_INFO_STRU
 �ṹ˵��  :LTE L2 RLC����������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                            usFrameNo;        /*֡��*/
    VOS_UINT16                            usSubFrameNo;     /*��֡��*/

    VOS_UINT16                            usRbId;           /*RB ID*/
    VOS_UINT16                            usRecvSn;         /*���յ�RLC PDU SNֵ*/

    VOS_UINT16                            usVRr;            /*RLC VR(R)*/
    VOS_UINT16                            usVRh;            /*RLC VR(H)���н��յ������SNֵ*/

    VOS_UINT16                            usVRMs;           /*RLC VR(MS)*/
    VOS_UINT16                            usVRx;            /*RLC VR(X)*/

}LTE_ERRLOG_RLC_DL_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_PDCP_DL_TRANS_INFO_STRU
 �ṹ˵��  :LTE L2 PDCP����������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                            usFrameNo;        /*֡��*/
    VOS_UINT16                            usSubFrameNo;     /*��֡��*/

    VOS_UINT32                            ulRbId;           /*RB ID*/

    VOS_UINT32                            ulDlLastSubmitSn; /*PDCP�����ϴεݽ���SNֵ*/
    VOS_UINT32                            ulDlRxSn;         /*PDCP���н��յ�SNֵ*/
    VOS_UINT32                            ulDlNextRxSn;     /*PDCP������һ�����յ�SNֵ*/
    VOS_UINT32                            ulDlRxHfn;        /*PDCP����HFNֵ*/

}LTE_ERRLOG_PDCP_DL_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_PDCP_UL_TRANS_INFO_STRU
 �ṹ˵��  :LTE L2 PDCP����������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                            usFrameNo;        /*֡��*/
    VOS_UINT16                            usSubFrameNo;     /*��֡��*/

    VOS_UINT32                            ulRbId;           /*RB ID*/

    VOS_UINT32                            ulUlNextAckSn;    /*PDCP������һ��ȷ�ϵ�SNֵ*/
    VOS_UINT32                            ulUlTxSn;         /*PDCP���з��͵�SNֵ*/

    VOS_UINT32                            ulUlNextTxSn;     /*PDCP������һ�����͵�SNֵ*/
    VOS_UINT32                            ulUlTxHfn;        /*PDCP����HFNֵ*/


}LTE_ERRLOG_PDCP_UL_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_L2_STATICS_INFO_STRU
 �ṹ˵��  :LTE L2 ����ͳ����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                stHeader;

    VOS_UINT16                            usFrameNo;          /*֡��*/
    VOS_UINT16                            usSubFrameNo;       /*��֡��*/

    VOS_UINT32                            ulRbId;             /*RB ID*/
    VOS_UINT32                            ulCdsUlTxNum;       /*CDS ���з������ݰ�ͳ�Ƹ���*/
    VOS_UINT32                            ulPdcpUlTxNum;      /*PDCP ���з������ݰ�ͳ�Ƹ���*/
    VOS_UINT32                            ulPdcpUlAckNum;     /*PDCP ���з������ݰ��õ�ȷ�ϵ�ͳ�Ƹ���*/
    VOS_UINT32                            ulPdcpUlDiscNum;    /*PDCP ���ж��������ݰ�ͳ�Ƹ���*/
    VOS_UINT32                            ulRohcCompNum;      /*PDCP ROHC����ѹ�������ݰ�ͳ�Ƹ���*/
    VOS_UINT32                            ulRlcUlTxNum;       /*RLC���з������ݰ�ͳ�Ƹ���*/
    VOS_UINT32                            ulRlcDiscNum;       /*RLC ���ж��������ݰ�ͳ�Ƹ���*/
    VOS_UINT32                            ulMacUlSchedSuccNum;/*MAC ���гɹ����ȵ����ݰ�ͳ�Ƹ���*/
    VOS_UINT32                            ulMacSendSrNum;     /*MAC ����SR��ͳ�Ƹ���*/

   VOS_UINT32                            ulMacDlDemultipleSucc; /*MAC ���н⸴�óɹ���ͳ�Ƹ���*/
    VOS_UINT32                            ulRlcDlRxNum;          /*RLC���н������ݰ�ͳ�Ƹ���*/
    VOS_UINT32                            ulPdcpDlRxNum;         /*PDCP���н������ݰ�ͳ�Ƹ���*/
    VOS_UINT32                            ulRohcDecpFailNum;     /*ROHC���н�ѹ��ʧ�����ݰ�ͳ�Ƹ���*/
    VOS_UINT32                            ulRohcDecpSuccNum;     /*ROHC���н�ѹ���ɹ����ݰ�ͳ�Ƹ���*/
    VOS_UINT32                            ulCdsDlRxNum;          /*CDS���н������ݰ�ͳ�Ƹ���*/

}LTE_ERRLOG_L2_STATICS_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TDS_ERRLOG_MAC_HSUPA_INFO_STRU
 �ṹ˵��  TDS MAC HSUPA��Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                          usSysFramNo;    /*ϵͳ֡��*/
    VOS_UINT16                          usTbSize;       /*MAC UPA������Ȩ��С*/

    VOS_UINT8                           ucSnpl;         /*MAC UPA SNPL ����·��ֵ*/
    VOS_UINT8                           ucUph;          /*MAC UPA UPH*/
    VOS_UINT8                           ucTebs;         /*MAC UPA TEBS*/
    VOS_UINT8                           ucPrri;         /*MAC UPA PRRI*/

    VOS_UINT8                           ucTrri;         /*MAC UPA TRRI*/
    VOS_UINT8                           ucCrri;         /*MAC UPA CRRI*/
    VOS_UINT8                           ucRscpLevel;    /*MAC ����С��RSCPֵ*/
    VOS_UINT8                           ucRsv;          /*����*/

}TDS_ERRLOG_MAC_HSUPA_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TDS_ERRLOG_MAC_HSDPA_INFO_STRU
 �ṹ˵��  TDS MAC HSDPA��Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    VOS_UINT16                          usSysFramNo;    /*ϵͳ֡��*/
    VOS_UINT16                          usTsn;          /*MAC HSDPA ����SNֵ*/
    VOS_UINT16                          usExpectedSn;   /*MAC HSDPA �ڴ�����һ��SN*/
    VOS_UINT16                          usTbSize;       /*MAC HSDPA ������Ȩ��С*/

}TDS_ERRLOG_MAC_HSDPA_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TDS_ERRLOG_L2_STATICS_INFO_STRU
 �ṹ˵��  TDS L2����ͳ����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                          usSysFramNo;    /*ϵͳ֡��*/
    VOS_UINT16                          usRsv;

    VOS_UINT8                           ucMacState;     /*MAC��ǰ״̬*/
    VOS_UINT8                           ucHsupaFlag;    /*MAC HSUPA�Ƿ���Ч*/
    VOS_UINT8                           ucHsdpaFlag;    /*MAC HSDPA�Ƿ���Ч*/
    VOS_UINT8                           ucRbId;         /*RB IDֵ*/

    VOS_UINT32                          ulPdcpUlRxNum;  /*PDCP���д�RABM���յ���SDU��Ŀ*/
    VOS_UINT32                          ulPdcpUlTxNum;  /*PDCP�����з������ݰ�����*/
    VOS_UINT32                          ulRlcUlTxNum;   /*RLC�����з������ݰ�����*/
    VOS_UINT32                          ulMacUlTxNum;   /*MAC�����з������ݰ�����*/

    VOS_UINT32                          ulPdcpDlTxNum;  /*PDCP���з��͸�RABM��SDU��Ŀ*/
    VOS_UINT32                          ulPdcpDlRxNum;  /*PDCP�����н������ݰ�����*/
    VOS_UINT32                          ulRlcDlRxNum;   /*RLC�����н������ݰ�����*/
    VOS_UINT32                          ulMacDlRxNum;   /*MAC�����н������ݰ�����*/

}TDS_ERRLOG_L2_STATICS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TDS_ERRLOG_RLC_UL_TRANS_INFO_STRU
 �ṹ˵��  TDS L2 RLC����������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                          usSysFramNo;    /*ϵͳ֡��*/
    VOS_UINT16                          usUlSendSn;     /*RLC�����з��͵�PDU SNֵ*/

    VOS_UINT8                           ucRbId;         /*RB ID*/
    VOS_UINT8                           ucPduSize;      /*RLC ��PDU ��С����λbyte*/
    VOS_UINT8                           ucPduNum;       /*һ�����RLC PDU����*/
    VOS_UINT8                           ucRsv;

    VOS_UINT32                          ulRlcBo;        /*RLC �㻺����ͳ��*/
    VOS_UINT32                          ulPdcpBo;       /*PDCP �㻺����ͳ��*/

    VOS_UINT16                          usVTs;          /*RLC �㴰�ڱ���VTS*/
    VOS_UINT16                          usVTa;          /*RLC �㴰�ڱ���VTA*/

}TDS_ERRLOG_RLC_UL_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TDS_ERRLOG_RLC_DL_TRANS_INFO_STRU
 �ṹ˵��  TDS L2 RLC����������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{

    OM_ERR_LOG_HEADER_STRU              stHeader;

    VOS_UINT16                          usSysFramNo;    /*ϵͳ֡��*/
    VOS_UINT16                          usDlRecvSn;     /*RLC�����з��͵�PDU SNֵ*/


    VOS_UINT8                           ucRbId;         /*RB ID*/
    VOS_UINT8                           ucPduSize;      /*RLC ��PDU ��С����λbyte*/
    VOS_UINT8                           ucPduNum;       /*һ�����RLC PDU����*/
    VOS_UINT8                           ucRsv;

    VOS_UINT16                          usVRr;          /*RLC �㴰�ڱ���VR(R)*/
    VOS_UINT16                          usVRh;          /*RLC �㴰�ڱ���VR(H)*/

}TDS_ERRLOG_RLC_DL_TRANS_INFO_STRU;

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

#endif /* end of TLL2ErrorLog.h */
