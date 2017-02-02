

#ifndef __LUPAPPITF_H__
#define __LUPAPPITF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "LUPZeroCopy.h"
#include "OmCommon.h"
#include "LUPQueue.h"
#include "AppL2Interface.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define APPITF_DATA_REQ_QUE_SIZE        1024        /*�ݶ�512*/
#define APPITF_DATA_IND_QUE_SIZE        512         /*�ݶ�64*/
#define APPITF_APP_IDLE_BUF_QUE_SIZE    256         /*Idle״̬�»�����г���*/
#define APPITF_APP_DATA_MAX_SIZE        1500        /*����IP��Ϊ1500�ֽ�,����ݶ�1500*/

#define PS_OM_MAX_DRB_NUM                  8  /*Ŀǰҵ�񳡾�ֻ֧��8��DRB����ά�ɲ�ʹ��*/

#define L2_THR_STAT_UNSIGN_LONG_MAX               (0x7FFFFFFFUL)
#define L2_THR_STAT_MAX_NUM                       10
#define L2_THR_STAT_BYTE_CNT_MAX                  (L2_THR_STAT_UNSIGN_LONG_MAX/1000)

#define NCM_DEVICE_NUM   2    /*BSP NCM ������Ŀ*/

extern VOS_UINT32  g_ulUlFcThroughputStat;
#define FC_UL_THROUGHPUT_STAT_INC(n)    (g_ulUlFcThroughputStat += (n))

/*****************************************************************************
 �ṹ��    : LRLC_STATE_EN
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �û���ʱ���Ż�ģʽö�ٶ���
*****************************************************************************/

enum LUP_LATENCY_OPT_MODE_EN
{
    LUP_LOM_MODE_NORMAL     = 0,       /*����ģʽ*/
    LUP_LOM_MODE_OPTIMIZE      ,       /*ʱ���Ż�ģʽ*/

    LUP_LOM_MODE_BUTT
};

extern VOS_UINT32 g_ulLupLatencyOptMode;
extern VOS_UINT32 g_ulLupLatencyOptSwitch;
extern VOS_UINT32 g_ulLomSduCnt;
extern VOS_UINT32 g_ulLomOmSwitch;
#define LUP_GET_LATENCY_OPT_MODE()      ((PS_TRUE == g_ulLupLatencyOptSwitch) ? g_ulLupLatencyOptMode:LUP_LOM_MODE_NORMAL)
#define LUP_SET_LATENCY_OPT_MODE(n)     (g_ulLupLatencyOptMode = (n))

#define LUP_INC_LOM_SDU_COUNTER()       (g_ulLomSduCnt = TTF_MOD_ADD(g_ulLomSduCnt,  1, 0x80000000))
#define LUP_GET_LOM_SDU_COUNTER()       (g_ulLomSduCnt)
#define LUP_GET_LOM_NEW_SDU_CNT(ulCurr, ulLast)      (TTF_MOD_SUB((ulCurr), (ulLast), 0x80000000))

extern VOS_VOID LUP_LatencyOptModeCtrl(VOS_VOID);


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/



/*****************************************************************************
 ö����    : L2_DCM_SCELL_STATUS_ENUM
 ö��˵��  : SCELL״̬
*****************************************************************************/
typedef enum
{
    L2_MAC_SCELL_ACTIVE    = 0,
    L2_MAC_SCELL_DEACTIVE,
    L2_MAC_SCELL_NOT_CONFIG,
    L2_MAC_SCELL_BUTT
}L2_DCM_SCELL_STATUS_ENUM;

typedef VOS_UINT8 L2_DCM_SCELL_STATUS_ENUM_UINT8;
/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*IP��ַ*/
typedef struct
{
    VOS_UINT8   aucIPaddr[4];
    VOS_UINT8   ucInitFlag;
    VOS_UINT8   aucRev[3];
}GIP_ADDR_STRU;


/*****************************************************************************
 �ṹ��    : APP_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :APP��ͳ����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32               ulMaxRate;            /*�������*/
    VOS_UINT32               ulRate;               /*ƽ������*/
    VOS_UINT32               ulPacketsCntOK;       /*�ɹ�����*/
    VOS_UINT32               ulPacketsCntErr;      /*�������*/
    VOS_UINT32               ulPacketsCntOverflow; /*�������,δ�ܷ��ͻ����*/
} APP_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : L2_APP_THROUGHPUT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L2��OM�����ϱ�APP��Tx��Rxͳ����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                       ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                       ulOpId;
    APP_STAT_INFO_STRU               stRxThoughputInfo; /*����ͳ����Ϣ*/
    APP_STAT_INFO_STRU               stTxThoughputInfo; /*����ͳ����Ϣ*/
} L2_APP_THROUGHPUT_IND_STRU;

/*****************************************************************************
 �ṹ��    : L2_APP_THROUGHPUT_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L2�����ϱ�APP��Tx��Rxͳ����Ϣ�����ṹ
*****************************************************************************/
typedef struct
{
    APP_CMD_ENUM_UINT8                enState;
    VOS_UINT8                         ucRsv[3];
    VOS_UINT32                        ulRptPeriod;       /*��λms����Сֵ100ms������100ms*/
    VOS_UINT32                        ulCurTime;         /*��ǰʱ��*/
    VOS_UINT32                        ulPreTime;         /*��һ�ε�ʱ��*/
    VOS_UINT32                        ulPreTxTotalLen;   /*��һ�η��͵����ֽ�����,���5ms*/
    VOS_UINT32                        ulCurTxTotalLen;   /*��ǰ���͵����ֽ�����*/
    VOS_UINT32                        ulPreRxTotalLen;   /*��һ�ν��յ����ֽ�����,���5ms*/
    VOS_UINT32                        ulCurRxTotalLen;   /*��ǰ���յ����ֽ�����*/
    APP_STAT_INFO_STRU                stRxThoughputInfo; /*����ͳ����Ϣ*/
    APP_STAT_INFO_STRU                stTxThoughputInfo; /*����ͳ����Ϣ*/
} L2_APP_THROUGHPUT_STAT_INFO_STRU;

/*added for through statistic begin*/

/*****************************************************************************
 �ṹ��    : L2_THROUGHPUT_ULDL_STAT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L2������/��������ͳ����Ϣ�Ľṹ��ͬʱ����������ά�ɲ��غ�L2�ڲ�������ͳ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                 ulUlDataRate;        /*������������*/
    VOS_UINT32                 ulDlDataRate;        /*������������*/
} L2_THROUGHPUT_ULDL_STAT_STRU;

/*****************************************************************************
 �ṹ��    : L1_THROUGHPUT_ULDL_STAT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L1 UL/DLͳ����Ϣ�Ľṹ��ֻ����L2�ڲ�������ͳ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                 ulSinr;              /*SINR*/
    VOS_UINT32                 ulL1ThruputRight;    /*��������*/
    VOS_UINT32                 ulL1ThruputTotal;    /*������������*/
} L1_THROUGHPUT_ULDL_STAT_STRU;

/*****************************************************************************
 �ṹ��    : L2_DRB_THROUGHPUT_ULDL_STAT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L2��DRB��/��������ͳ����Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                 ulRbId;              /*RB ID*/
    VOS_UINT32                 ulUlDataRate;        /*������������*/
    VOS_UINT32                 ulDlDataRate;        /*������������*/
} L2_DRB_THROUGHPUT_ULDL_STAT_STRU;

/*****************************************************************************
 �ṹ��    : L2_OM_THROUGHPUT_STAT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L2��MSP�����ϱ�������ά�ɲ�������Ϣ�ṹ�� ֻ����������ά�ɲ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulTimeStamp;         /*ʱ�����ͨ��PS_GET_TICK()���*/
    VOS_UINT16                                      usFrame;             /*֡��*/
    VOS_UINT16                                      usSubFrame;          /*��֡��*/
    VOS_UINT32                                      ulRptPeriod;         /*�ϱ�����*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stAppThoughputInfo;  /*APP���͸�PDCP/APP���յ�PDCP��ͳ����Ϣ*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stPdcpThoughputInfo; /*PDCP���͸�RLC/PDCP���յ�RLC��ͳ����Ϣ*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stRlcThoughputInfo;  /*RLC���͸�MAC/RLC���յ�MAC��ͳ����Ϣ*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stMacThoughputInfo;  /*MAC���͸�RTT/MAC���յ�RTT��ͳ����Ϣ*/
    L2_DRB_THROUGHPUT_ULDL_STAT_STRU                stDrbThoughputInfo[PS_OM_MAX_DRB_NUM];/*DRB�������յ�������ͳ����Ϣ*/
} L2_OM_THROUGHPUT_STAT_IND_STRU;

typedef struct
{
    CA_CELL_STATUS_STRU stCaCellStatus;
    L2_THROUGHPUT_ULDL_STAT_STRU stMacThroughput;  /*MAC��������������*/
}MAC_CA_THROUGHPUT_STRU;

/*****************************************************************************
 �ṹ��    : CA_L2_OM_THROUGHPUT_STAT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L2��MSP�����ϱ�������ά�ɲ�������Ϣ�ṹ�� ֻ����������ά�ɲ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulTimeStamp;  /*ʱ�����ͨ��PS_GET_TICK()���*/
    VOS_UINT16 usFrame;  /*֡��*/
    VOS_UINT16 usSubFrame;  /*��֡��*/
    VOS_UINT32 ulRptPeriod;  /*�ϱ�����*/
    L2_THROUGHPUT_ULDL_STAT_STRU stAppThroughputInfo;  /*APP���͸�PDCP/APP���յ�PDCP��ͳ����Ϣ*/
    L2_THROUGHPUT_ULDL_STAT_STRU stPdcpThroughputInfo;  /*PDCP���͸�RLC/PDCP���յ�RLC��ͳ����Ϣ*/
    L2_THROUGHPUT_ULDL_STAT_STRU stRlcThroughputInfo;  /*RLC���͸�MAC/RLC���յ�MAC��ͳ����Ϣ*/
    L2_THROUGHPUT_ULDL_STAT_STRU stMacTotalThroughputInfo;  /*MAC���͸�RTT/MAC���յ�RTT��ͳ����Ϣ*/
    L2_DRB_THROUGHPUT_ULDL_STAT_STRU astDrbThroughputInfo[PS_OM_MAX_DRB_NUM];/*DRB�������յ�������ͳ����Ϣ*/
    MAC_CA_THROUGHPUT_STRU astMacCaThroughput[CA_MAX_CELL_NUM]; /*����Ϊ8�������±����CellIndex��0:PCell��1~7:SCell*/
} CA_L2_OM_THROUGHPUT_STAT_IND_STRU;

/*****************************************************************************
 �ṹ��    : L2_LAYER_SDU_COUNT_STAT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L2������/����SDU����ͳ����Ϣ�Ľṹ������������ά�ɲ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                 ulReceivedCnt;           /*���н��յ�SDU��ĿPC��->�տ�*/
    VOS_UINT32                 ulReceivedLength;        /*���н��յ�SDU�ۼӳ��� ��λ:�ֽ�*/
    VOS_UINT32                 ulDiscardedCnt;          /*���ж�����SDU��Ŀ*/
    VOS_UINT32                 ulTransmittedCnt;        /*���з��͵�SDU��Ŀ*/
    VOS_UINT32                 ulTransmittedLength;     /*���з��͵�SDU�ۼӳ��� ��λ:�ֽ�*/
} L2_LAYER_SDU_COUNT_STAT_STRU;


/*****************************************************************************
 �ṹ��    : LPS_RLC_MODE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
enum LPS_RLC_MODE_ENUM
{
    LPS_RLC_MODE_AM                         = 0,                                    /* AM */
    LPS_RLC_MODE_UM                         = 1,                                    /* UM */
    LPS_RLC_MODE_TM                         = 2,                                    /* TM */
    LPS_RLC_MODE_BUTT
};
typedef VOS_UINT8 LPS_RLC_MODE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : L2_DRB_SDU_COUNT_STAT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L2��DRB��/����SDU����ͳ����Ϣ�Ľṹ������������ά�ɲ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                  ucRbId;                 /*RB ID*/
    LPS_RLC_MODE_ENUM_UINT8    ucRlcMode;              /*RLCģʽ*/
    VOS_UINT8                  aucRed[2];              /*����*/
    VOS_UINT32                 ulTxHfn;                /*UL TX HFN*/
    VOS_UINT32                 ulRxHfn;                /*DL RX HFN*/
    VOS_UINT32                 ulReceivedCnt;          /*���н��յ�SDU��Ŀ*/
    VOS_UINT32                 ulReceivedLength;       /*���н��յ�SDU�ۼӳ���*/
    VOS_UINT32                 ulDiscardedCnt;        /*���ж�����SDU��Ŀ*/
    VOS_UINT32                 ulTransmittedCnt;       /*���з��͵�SDU��Ŀ*/
    VOS_UINT32                 ulTransmittedLength;    /*���з��͵�SDU�ۼӳ���*/
} L2_DRB_SDU_COUNT_STAT_STRU;


/*****************************************************************************
 �ṹ��    : L2_OM_SDU_STAT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L2��MSP�����ϱ�SDU��ά�ɲ�������Ϣ�ṹ�� ֻ����������ά�ɲ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulTimeStamp;         /*ʱ�����ͨ��PS_GET_TICK()���*/
    VOS_UINT16                                      usFrame;             /*֡��*/
    VOS_UINT16                                      usSubFrame;          /*��֡��*/
    VOS_UINT32                                      ulRptPeriod;         /*�ϱ�����*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stUsbSduCountInfo[NCM_DEVICE_NUM];   /*USB SDU��ͳ����Ϣ*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stIpSduCountInfo;    /*IP SDU��ͳ����Ϣ*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stRabmSduCountInfo;  /*RABM SDU��ͳ����Ϣ*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stPdcpSduCountInfo;  /*PDCP SDU��ͳ����Ϣ*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stRlcSduCountInfo;   /*RLC SDU��ͳ����Ϣ*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stMacSduCountInfo;   /*MAC SDU��ͳ����Ϣ*/
    L2_LAYER_SDU_COUNT_STAT_STRU                    stPhySduCountInfo;   /*PHY SDU��ͳ����Ϣ*/
    L2_DRB_SDU_COUNT_STAT_STRU                      stDrbSduCountInfo[PS_OM_MAX_DRB_NUM];/*DRB�������յ�������ͳ����Ϣ*/
} L2_OM_SDU_STAT_IND_STRU;

/*****************************************************************************
 �ṹ��    : L1_THROUGHPUT_PROCESS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L1UL/DL��̬�������ṹ�� ֻ����L2�ڲ�������ͳ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulSinr[L2_THR_STAT_MAX_NUM];               /*SINR*/
    VOS_UINT32                                      ulL1ThruputRight[L2_THR_STAT_MAX_NUM];     /*��������*/
    VOS_UINT32                                      ulL1ThruputTotal[L2_THR_STAT_MAX_NUM];     /*��������*/
} L1_THROUGHPUT_PROC_ULDL_STRU;

/*****************************************************************************
 �ṹ��    : L2_THROUGHPUT_PROCESS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L2����UL/DL��̬�������ṹ�� ͬʱ����������ά�ɲ��غ�L2�ڲ�������ͳ�ƣ�������ά�ɲ���ÿ��ֻ�ϱ�һ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulUlRate[L2_THR_STAT_MAX_NUM];     /*��������*/
    VOS_UINT32                                      ulDlRate[L2_THR_STAT_MAX_NUM];     /*��������*/
} L2_THROUGHPUT_PROC_ULDL_STRU;

/*****************************************************************************
 �ṹ��    : L2_THROUGHPUT_PROCESS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L2����UL/DL��̬ͳ����Ϣ�ṹ�� ͬʱ����������ά�ɲ��غ�L2�ڲ�������ͳ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulPreUlTotalLen;                   /*��һ��ͳ�����з��͵����ֽ�����*/
    VOS_UINT32                                      ulCurUlTotalLen;                   /*��ǰͳ�����з��͵����ֽ�����*/
    VOS_UINT32                                      ulPreDlTotalLen;                   /*��һ��ͳ�����н��յ����ֽ�����*/
    VOS_UINT32                                      ulCurDlTotalLen;                   /*��ǰͳ�����н��յ����ֽ�����*/
    L2_THROUGHPUT_PROC_ULDL_STRU                    stUlDlInfo;                        /*���㶯̬������*/
} L2_THROUGHPUT_PROC_INFO_STRU;


/*****************************************************************************
 �ṹ��    : L2_DRB_THROUGHPUT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L2�������ڼ�¼DRB UL/DL��̬ͳ����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       ucRbId;                            /*DRB ID*/
    VOS_UINT8                                       ucValid;                           /*ͳ����Ч��־λ.1-��Ч,0-��Ч*/
    VOS_UINT8                                       aucRsv[2];
    VOS_UINT32                                      ulPreUlTotalLen;                   /*��һ��ͳ�����з��͵����ֽ�����*/
    VOS_UINT32                                      ulCurUlTotalLen;                   /*��ǰͳ�����з��͵����ֽ�����*/
    VOS_UINT32                                      ulPreDlTotalLen;                   /*��һ��ͳ�����н��յ����ֽ�����*/
    VOS_UINT32                                      ulCurDlTotalLen;                   /*��ǰͳ�����н��յ����ֽ�����*/
    L2_THROUGHPUT_PROC_ULDL_STRU                    stUlDlInfo;                        /*���㶯̬������*/
} L2_DRB_THROUGHPUT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : L2_DRB_THROUGHPUT_PROC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :DRB ��̬ͳ����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbNum;                           /*��Ч��RB ����*/
    VOS_UINT8                           aucRsv[3];
    L2_DRB_THROUGHPUT_INFO_STRU         stDrbThoughtputInfo[PS_OM_MAX_DRB_NUM]; /*����DRB��������̬ͳ����Ϣ*/

} L2_DRB_THROUGHPUT_PROC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : L2_THROUGHPUT_PROCESS_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :L2��������ͳ��ȫ����Ϣ�ṹ�� ͬʱ����������ά�ɲ��غ�L2�ڲ�������ͳ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                       ulStatFlag;            /*����ͳ�ƿ�ʼ/ֹͣ��־*/
    VOS_UINT32                                       ulThrMomStatFlag;      /*1:����������ά�ɲ��أ���ֹͣL2�ڲ�����ͳ�ƣ� 0: ֹͣ������ά�ɲ��أ���ɽ���L2�ڲ�����ͳ��*/
    VOS_UINT32                                       ulStatPeriod;          /*ͳ�����ڣ���λ: ms����С����: */
    VOS_UINT32                                       ulRptPeriod;           /*�ϱ����ڣ���λ: ms����С����: */
    VOS_UINT32                                       ulCurStatTime;         /*��ǰͳ�Ƶ�ʱ��*/
    VOS_UINT32                                       ulPreStatTime;         /*��һ��ͳ�Ƶ�ʱ��*/
    VOS_UINT32                                       ulCurRptTime;          /*��ǰ�ϱ���ʱ��*/
    VOS_UINT32                                       ulPreRptTime;          /*��һ���ϱ���ʱ��*/
    VOS_UINT32                                       ulValidStatNum;         /*��ͳ�Ƶ���Ч������ ������ά�ɲ���ʱһ���ϱ�ֻͳ��һ����*/
    VOS_UINT32                                       ulTimeStamp[L2_THR_STAT_MAX_NUM];        /*ʱ�����ͨ��PS_GET_TICK()���*/
    VOS_UINT16                                       usFrame[L2_THR_STAT_MAX_NUM];            /*֡��*/
    VOS_UINT16                                       usSubFrame[L2_THR_STAT_MAX_NUM];         /*��֡��*/
    L2_THROUGHPUT_PROC_INFO_STRU                     stAppThoughputInfo;    /*APP��ͳ����Ϣ*/
    L2_THROUGHPUT_PROC_INFO_STRU                     stPdcpThoughputInfo;   /*PDCP��̬ͳ����Ϣ*/
    L2_THROUGHPUT_PROC_INFO_STRU                     stRlcThoughputInfo;    /*RLC��̬ͳ����Ϣ*/
    L2_THROUGHPUT_PROC_INFO_STRU                     stMacThoughputInfo;    /*MAC��̬ͳ����Ϣ*/
    L2_DRB_THROUGHPUT_PROC_INFO_STRU                 stL2DrbThoughputInfo;  /*����DRB��̬ͳ����Ϣ*/

    L2_THROUGHPUT_PROC_INFO_STRU astMacCaThroughputInfo[CA_MAX_CELL_NUM];  /*CA MAC��̬ͳ����Ϣ*/
} L2_THROUGHPUT_PROC_STAT_INFO_STRU;
/*added for through statistic end*/
/*****************************************************************************
 �ṹ��    : L2_DRB_LOCAL_SDU_COUNT_STAT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :���ر����L2��DRB��/����SDU����ͳ����Ϣ�ṹ������������ά�ɲ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                  ucRbId;                 /*RB ID*/
    VOS_UINT8                  ucValid;                /*ͳ����Ч��־λ  1-��Ϣ��Ч,0-��Ч*/
    LPS_RLC_MODE_ENUM_UINT8    ucRlcMode;              /*RLCģʽ*/
    VOS_UINT8                  ucRsvd;                 /*����*/
    VOS_UINT32                 ulTxHfn;                /*UL TX HFN*/
    VOS_UINT32                 ulRxHfn;                /*DL RX HFN*/
    VOS_UINT32                 ulReceivedCnt;          /*���н��յ�SDU��Ŀ*/
    VOS_UINT32                 ulReceivedLength;       /*���н��յ�SDU�ۼӳ���*/
    VOS_UINT32                 ulDiscardedCnt;        /*���ж�����SDU��Ŀ*/
    VOS_UINT32                 ulTransmittedCnt;       /*���з��͵�SDU��Ŀ*/
    VOS_UINT32                 ulTransmittedLength;    /*���з��͵�SDU�ۼӳ���*/
} L2_DRB_LOCAL_SDU_COUNT_STAT_STRU;


/*****************************************************************************
 �ṹ��    : L2_DRB_SDU_COUNT_STAT_PROC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :��������L2��DRB SDU��Ŀͳ��ȫ����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbNum;                           /*��Ч��RB ����*/
    VOS_UINT8                           aucRsv[3];
    L2_DRB_LOCAL_SDU_COUNT_STAT_STRU    stDrbSduCountInfo[PS_OM_MAX_DRB_NUM];/*DRB�������յ�������ͳ����Ϣ*/
}L2_DRB_SDU_COUNT_STAT_PROC_STRU;


/*****************************************************************************
 �ṹ��    : L2_SDUCNT_PROC_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :��������L2���� SDU��Ŀͳ��ȫ����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                       ulStatFlag;            /*SDU��Ŀͳ�ƿ�ʼ/ֹͣ��־*/
    VOS_UINT32                                       ulStatPeriod;          /*ͳ�����ڣ���λ: ms����С����: �˴�����*/
    VOS_UINT32                                       ulRptPeriod;           /*�ϱ����ڣ���λ: ms����С����: */
    VOS_UINT32                                       ulCurStatTime;         /*��ǰͳ�Ƶ�ʱ��*/
    VOS_UINT32                                       ulPreStatTime;         /*��һ��ͳ�Ƶ�ʱ��*/
    VOS_UINT32                                       ulCurRptTime;          /*��ǰ�ϱ���ʱ��*/
    VOS_UINT32                                       ulPreRptTime;          /*��һ���ϱ���ʱ��*/
    VOS_UINT32                                       ulValidStatNum;         /*��ͳ�Ƶ���Ч������ ������ά�ɲ���ʱһ���ϱ�ֻͳ��һ����*/
    VOS_UINT32                                       ulTimeStamp[L2_THR_STAT_MAX_NUM];        /*ʱ�����ͨ��PS_GET_TICK()���*/
    VOS_UINT16                                       usFrame[L2_THR_STAT_MAX_NUM];            /*֡��*/
    VOS_UINT16                                       usSubFrame[L2_THR_STAT_MAX_NUM];         /*��֡��*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stUsbSduCountInfo;     /*USB SDU��ͳ����Ϣ*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stIpSduCountInfo;      /*IP SDU��ͳ����Ϣ*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stRabmSduCountInfo;    /*RABM SDU��ͳ����Ϣ*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stPdcpSduCountInfo;    /*PDCP SDU��ͳ����Ϣ*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stRlcSduCountInfo;     /*RLC SDU��ͳ����Ϣ*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stMacSduCountInfo;     /*MAC SDU��ͳ����Ϣ*/
    L2_LAYER_SDU_COUNT_STAT_STRU               stPhySduCountInfo;     /*PHY SDU��ͳ����Ϣ*/
    L2_DRB_SDU_COUNT_STAT_PROC_STRU                  stDrbSduCntProcInfo;   /*DRB SDU��ͳ����Ϣ*/

} L2_SDUCNT_PROC_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LUP_APPSTATSTRU_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͳ����Ϣ�ṹ
*****************************************************************************/
typedef struct LUP_APPSTAT
{
    VOS_UINT32    ulMemTransFailNum;
    VOS_UINT32    ulAppRxIpPktCnt;
    VOS_UINT32    ulAppRxIpPktLen;
    VOS_UINT32    ulEnAppReqQueSucc;
    VOS_UINT32    ulEnAppReqQueFail;
    VOS_UINT32    ulDeAppReqQueSucc;
    VOS_UINT32    ulRelAppReqQueNum;

}LUP_APPSTATSTRU_STRU;


/*DCM logger*/
/*****************************************************************************
 �ṹ��    : MAC_BSR_SUBHDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC BSR ��ͷ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-BSR ����Ԫ��Ч*/
    VOS_UINT8    ucBsrType;      /*0-short bsr;1-truncated bsr;2-long bsr*/
    VOS_UINT8    ucBufferSize0;
    VOS_UINT8    ucBufferSize1;
    VOS_UINT8    ucBufferSize2;
    VOS_UINT8    ucBufferSize3;
    VOS_UINT16   usRsv;
}MAC_BSR_SUBHDR_STRU;

/*****************************************************************************
 �ṹ��    : MAC_PHR_SUBHDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC PHR ��ͷ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-PHR ����Ԫ��Ч*/
    VOS_UINT8    ucPhrType;      /*0-PHR;1-Extend PHR*/
    VOS_UINT8    ucRsv[2];
}MAC_PHR_SUBHDR_STRU;

/*****************************************************************************
 �ṹ��    : MAC_PADDING_SUBHDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC PADDING ��ͷ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-��padding ����*/
    VOS_UINT8    ucRsv[3];
}MAC_PADDING_SUBHDR_STRU;


/*****************************************************************************
 �ṹ��    : MAC_CRNTI_SUBHDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC CRNTI ��ͷ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-CRNTI ����Ԫ��Ч*/
    VOS_UINT8    ucRsv;
    VOS_UINT16   usCRnti;
}MAC_CRNTI_SUBHDR_STRU;

/*****************************************************************************
 �ṹ��    : MAC_SDU_DATA_HEADER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC SDU ��ͷ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8     ucData[9];      /*SDUǰ9���ֽ�*/
    VOS_UINT8     ucLchId;     /*�߼��ŵ�ID*/
    VOS_UINT16    usSduLen;
}MAC_SDU_DATA_HEADER_STRU;


/*****************************************************************************
 �ṹ��    : MAC_SDU_DATA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC SDU��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;
    VOS_UINT8    ucSduNum;
    VOS_UINT8    ucRsv[2];
    MAC_SDU_DATA_HEADER_STRU   stMacSduData[3]; /*ֻ����3��SDU*/
}MAC_SDU_DATA_STRU;


/*****************************************************************************
 �ṹ��    : L2_MAC_UL_HEADER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC PUSCH ��ͷ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    MAC_BSR_SUBHDR_STRU         stMacBsrInfo;
    MAC_PHR_SUBHDR_STRU         stMacPhrInfo;
    MAC_CRNTI_SUBHDR_STRU       stMacCrntiInfo;
    MAC_SDU_DATA_STRU           stMacSduInfo;
}L2_MAC_UL_HEADER_STRU;

/*****************************************************************************
 �ṹ��    : MAC_CA_SUBHDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC CA ��ͷ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-CA����Ԫ��Ч*/
    VOS_UINT8    ucSCellStatus;      /*bit 1-7 Ϊ1,��˵����Ӧ��SCell ���bit 0 Ϊreserved*/
    VOS_UINT8    ucRsv[2];
}MAC_CA_SUBHDR_STRU;

/*****************************************************************************
 �ṹ��    : MAC_CRI_SUBHDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC CRI ��ͷ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-���������ʶ ����Ԫ��Ч*/
    VOS_UINT8    ucCRI[6];      /*�������indentity*/
    VOS_UINT8    ucRsv;
}MAC_CRI_SUBHDR_STRU;

/*****************************************************************************
 �ṹ��    : MAC_TA_SUBHDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC TA ��ͷ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-TA ����Ԫ��Ч*/
    VOS_UINT8    ucTaValue;
    VOS_UINT8    ucRsv[2];
}MAC_TA_SUBHDR_STRU;

/*****************************************************************************
 �ṹ��    : MAC_DRX_SUBHDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC DRX ��ͷ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucValidFlag;     /*1-DRX ����Ԫ��Ч*/
    VOS_UINT8    ucRsv[3];
}MAC_DRX_SUBHDR_STRU;


/*****************************************************************************
 �ṹ��    : L2_MAC_DL_HEADER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MAC PDSCH ��ͷ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    MAC_CA_SUBHDR_STRU         stMacCaInfo;
    MAC_TA_SUBHDR_STRU         stMacTaInfo;
    MAC_CRI_SUBHDR_STRU        stMacCriInfo;
    MAC_DRX_SUBHDR_STRU        stMacDrxInfo;
    MAC_SDU_DATA_STRU          stMacSduInfo;
}L2_MAC_DL_HEADER_STRU;

/*****************************************************************************
 �ṹ��    : L2_MAC_DL_HEADER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT32                enMsgName;                    /* ��Ϣ���� */      /* _H2ASN_Skip */
    L2_MAC_DL_HEADER_STRU         stMacDlData;
}L2_MAC_DL_HEADER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : L2_MAC_UL_HEADER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT32                enMsgName;                    /* ��Ϣ���� */      /* _H2ASN_Skip */
    L2_MAC_UL_HEADER_STRU         stMacUlData;

}L2_MAC_UL_HEADER_INFO_STRU;

/*****************************************************************************
 �ṹ��    :L2_DCM_CA_CTRL_ELEMENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  SCELL MAC CE�ϱ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                    /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT32                          enMsgName;                    /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT16                          usSCellCtrlRevSFN;
    VOS_UINT16                          usSCellCtrlRevSubSFN;
    L2_DCM_SCELL_STATUS_ENUM_UINT8      aucScellIndex[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];
}L2_DCM_CA_CTRL_ELEMENT_STRU;

extern L2_MAC_DL_HEADER_STRU  g_stL2MacDlHdrInfo;
extern L2_MAC_UL_HEADER_STRU  g_stL2MacUlHdrInfo;
/*end DCM*/

extern LUP_APPSTATSTRU_STRU     g_stLupAppStat;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32 UP_InitAppItf( VOS_VOID);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/

/*�����ڲ���*/
#if (VOS_OS_VER == VOS_WIN32)

extern LUP_QUEUE_STRU  *g_pstAppDataIndQue;     /*App����:PS->APP*/

extern VOS_UINT32 LUP_DataIndQueInit(void);
extern VOS_UINT32 APPITF_SndDataReq(LUP_MEM_ST *pData, VOS_UINT32 ulLen);
extern VOS_VOID   APPITF_RcvDataReq(void);
extern LUP_MEM_ST * APPITF_AllocMem(VOS_UINT32 ulSize);
extern VOS_UINT32 APPITF_FreeMem(LUP_MEM_ST *pMem);
extern VOS_UINT32 APPITF_RcvDataInd(VOS_UINT8 *pBuff, VOS_UINT32 *pulLen);
extern VOS_UINT32 APPITF_SndDataInd(LUP_MEM_ST *pData);

extern VOS_VOID APPITF_RcvDataReq_Stub(void);
VOS_UINT32 STUB_DriverSendAppDataToPs(VOS_UINT32 ulRbId, VOS_UINT16 usLen);
VOS_UINT32 STUB_DriverRcvAppDataFromPs(void);
#endif

extern LUP_QUEUE_STRU  *g_pstAppDataReqQue;     /*App����:APP->PS*/
extern VOS_UINT32 LUP_DataReqQueInit(void);
extern VOS_VOID LUP_RcvDataReq(void);
extern VOS_VOID LUP_RelDataReq(VOS_VOID);


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

#endif /* end of LUPAppItf.h */


