

#ifndef __CDS_H__
#define __CDS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "CdsDepend.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*����CDS�����¼�*//*����DOPRA�ֲᣬ�¼���16λΪϵͳ�������û�ʹ�õ�16λ��OSA��ʹ�ô�ȷ��*/
#define  CDS_EVENT_BASE                 (0x00000000)
#define  CDS_EVENT_UL_IPF_INT           (CDS_EVENT_BASE | 0x0001)               /*����IPF�����¼�*/
#define  CDS_EVENT_DL_DATA_PROC         (CDS_EVENT_BASE | 0x0002)               /*CDS LTEģ����������֡�ж��ܷ�����GUģͨ����ʱ������*/
#define  CDS_EVENT_UL_ADQ_EMPTY         (CDS_EVENT_BASE | 0x0004)               /*IPF ��ģʽADQ���ж�*/
#define  CDS_EVENT_UL_IMS_PROC          (CDS_EVENT_BASE | 0x0008)               /*IMS���ݴ���*/
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
#define  CDS_EVENT_UL_BASTET_PROC       (CDS_EVENT_BASE | 0x0010)               /*BASTET�������ݴ���*/
#endif


/*����IDLE���д�С*/
#define  CDS_UL_IDLE_QUE_SIZE           (256)

/*����IMS���д�С*/
#define  CDS_IMS_QUE_SIZE               (64)
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
/*����BASTET���д�С*/
#define  CDS_BASTET_QUE_SIZE            (256)
#endif

/*����NAS��������*/
#define  CDS_NAS_MAX_BEARER_NUM         (11)

/*����NAS��С��������ID*/
#define  CDS_NAS_MIN_BEARER_ID          (5)
#define  CDS_NAS_MAX_BEARER_ID          (15)

/*�������г���ID*/
#define  CDS_NAS_ALL_BEARER_ID          (0xFF)


/*CDS��ʱ��ʱ������λMS*/
#define  CDS_TMR_LEN                    (10)

/*�������ݱ�����ʱ��ʱ��*/
#define  CDS_UL_DATA_PROTECT_TMR_LEN    (30*1000)

/*CDS���л��津���¼���ֵ*/
#define  CDS_DL_BUFF_TRIG_EVENT_THRES   (56)

/*CDS���ض���*/
#define  CDS_LB_QUE_SIZE                (16)

/*����PDN��С��������ID*/
#define  CDS_MIN_PDN_ID                 (0)
#define  CDS_MAX_PDN_ID                 (14)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/
typedef enum CDS_TMR_ID
{
    CDS_TMR_ID_DL_10MS_PERIODIC_TMR         = 0x0,      /*����10ms�����Զ�ʱ��*/
    CDS_TMR_ID_LB_MODE_B_TMR                = 0x1,      /*����ģʽB�����Ķ�ʱ��*/
    CDS_TMR_ID_UL_DATA_PROCTECT             = 0x2,      /*�������ݱ�����ʱ��*/
    CDS_TMR_ID_MODEM_BUTT,                              /*���϶�ʱ���Ǻ�Modem��صģ�ÿһ��CDSʵ�嶼����*/

    /*IPF��������ض�ʱ��*/
    CDS_TMR_ID_ADQ_EMPTY_PROCTECT,                      /*ADQ�ձ�����ʱ��*/
    CDS_TMR_ID_FC_CHECK_TMR,                            /*����״̬��鶨ʱ��*/
    CDS_TMR_ID_BUTT
}CDS_TMR_ID_ENUM;


/*****************************************************************************
 �ṹ��    : CDS_UL_IP_PKT_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����IP������
*****************************************************************************/
typedef enum CDS_UL_IP_PKT_TYPE
{
    CDS_UL_IP_PKT_TYPE_NORMAL,               /*�������ݰ�*/
    CDS_UL_IP_PKT_TYPE_IPSEG,                /*��Ƭ��*/
    CDS_UL_IP_PKT_TYPE_NDIS,                 /*��Ҫ���͵�A�˵�NDIS���ݰ�*/
    CDS_UL_IP_PKT_TYPE_ERROR,                /*IPF���˴������ݰ�*/
    CDS_UL_IP_IPF_MODE_BUTT
}CDS_UL_IP_PKT_TYPE_ENUM;

typedef VOS_UINT32 CDS_UL_IP_PKT_TYPE_ENUM_UINT32;


/*****************************************************************************
 �ṹ��    : CDS_LB_MODE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS����ģʽ
*****************************************************************************/
typedef enum
{
    CDS_LB_MODE_A       = 0,
    CDS_LB_MODE_B       = 1,
    CDS_LB_MODE_BUTT
}CDS_LB_MODE_ENUM;

typedef VOS_UINT32 CDS_LB_MODE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : CDS_LB_STATE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS����״̬
*****************************************************************************/
typedef enum
{
    CDS_LB_STATE_ACTIVE    = 0,
    CDS_LB_STATE_START     = 1,
    CDS_LB_STATE_STOP      = 2,
    CDS_LB_STATE_DEACTIVE  = 3,
    CDS_LB_STATE_BUTT
}CDS_LB_STATE_ENUM;

typedef VOS_UINT32 CDS_LB_STATE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : CDS_DIRECTION_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS��������
*****************************************************************************/
typedef enum
{
    CDS_DIRECTION_UL       = 0,
    CDS_DIRECTION_DL       = 1,
    CDS_DIRECTION_BUTT
}CDS_DIRECTION_ENUM;


/*****************************************************************************
   5 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : CDS_LB_DL_SDU_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģʽ���н��յ���SDU.
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSduLen;           /* ���ݳ��� */
    TTF_MEM_ST                         *pstSdu;             /* SDU����ָ�� */
}CDS_LB_DL_SDU_STRU;


/*****************************************************************************
 �ṹ��    : CDS_TIMER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS��ʱ����Ϣ
*****************************************************************************/
typedef struct
{
    HTIMER                   pstTmrHdr;
    VOS_UINT32               ulTmrId;
    VOS_UINT32               ulTmrLen;
    VOS_UINT32               ulPara;
}CDS_TIMER_STRU;


/*****************************************************************************
 �ṹ��    : CDS_FLOW_STATS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS������ͳ�����ݽṹ
*****************************************************************************/
typedef struct CDS_FLOW_STATS
{
    CDS_BEARER_DATA_FLOW_STRU    astBearerDS[CDS_NAS_MAX_BEARER_NUM];           /*NAS����ID����Ч��Χ:5-15*/
}CDS_DATA_FLOW_STRU;

/*****************************************************************************
 �ṹ��    : CDS_ENTITY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����CDS����ʵ��ṹ
*****************************************************************************/
typedef struct CDS_ENTITY
{
    VOS_UINT16                          usModemId;
    VOS_UINT16                          usGuRabSRStatus;                        /*GU ���ش���SR״̬��־λ*/
    VOS_UINT16                          usCDMARabSRStatus;                        /*CDMA ���ش���SR״̬��־λ*/

    MMC_CDS_MODE_ENUM_UINT32            enRanMode;                              /*��Ҫ�޸�ΪENUM����*/
    VOS_UINT32                          ulServiceReqFlg;                        /*�ж��Ƿ񴥷�Service Request*/

    VOS_UINT32                          ulTestModeFlg;                          /*����ģʽ�Ƿ񼤻��־ : TRUE������; FALSE����δ����*/
    VOS_UINT32                          ulLoopBackMode;                         /*����ģʽ����*/
    VOS_UINT32                          ulLoopBackState;                        /*����ģʽ״̬*/

    LUP_QUEUE_STRU                     *pstUlDataQue;                           /*����IDLE/SUSPEND̬���棬�ݶ�256*/
    LUP_QUEUE_STRU                     *pstIMSDataQue;                          /*IMS���ݶ���*/
    LUP_QUEUE_STRU                     *pstLBModeBQue;                          /*����ģʽ����*/
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
    LUP_QUEUE_STRU                     *pstBastetUlQue;                         /*����ҵ��������ݶ���*/
#endif
    CDS_TIMER_STRU                      astTimer[CDS_TMR_ID_MODEM_BUTT];        /*CDS��ʱ���ṹ*/

    CDS_DATA_FLOW_STRU                  stFlowStats;                            /*����ͳ��*/

    VOS_UINT32                          ulImsBearerNum;                                 /*IMS���ظ���*/
    IMSA_CDS_IMS_BEARER_STRU            astImsBearerInfo[IMSA_CDS_MAX_IMS_BEARER_NUM];  /*IMS����������Ϣ*/
    IMSA_CDS_IMS_PORT_INFO_STRU         stImsPortInfo;

    VOS_UINT32                          ulUlSoftFilterNum;                              /*���������������*/
    CDS_SOFTFILTER_INFO_STRU            astUlSoftFilter[CDS_MAX_SOFT_FILTER_NUM];       /*�����������������*/

    /*�ض�����ID*/
    VOS_UINT8                           ucMbmsBearerId;                         /*MBMS����ID*/
    VOS_UINT8                           ucDbgBearerId;                          /*�ϴ�������Ϣ����ID*/
    VOS_UINT8                           ucLBDefBearerId;                        /*����ģʽȱʡ����ID*/
    VOS_UINT8                           aucRes[1];

    VOS_UINT32                          ulULPktDiscardFlg;                      /*�������ݰ���������*/
    VOS_UINT32                          ulDLPktDiscardFlg;                      /*�������ݰ���������*/

    VOS_UINT32                          ulVoicePreferActFlag;                   /* VoicePrefer�����,FALSE:δ����;TRUE:���� */

}CDS_ENTITY_STRU;


/*****************************************************************************
 �ṹ��    : CDS_RX_DL_SDU_DATA_IND_STRU
 Э����  : ����CDS���յ�������SDU��Ϣ����
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /* ��Ϣͷ */
    VOS_UINT16                              usMsgName;          /* ��Ϣ���� */
    VOS_UINT8                               ucRbId;             /* Rb Id*/
    VOS_UINT8                               aucReserve1[1];     /* 4�ֽڶ��룬����*/

    VOS_UINT8                               ucPduType;
    VOS_UINT8                               ucPdcpPid;
    VOS_UINT16                              usPdcpSn;
    VOS_UINT32                              ulDataLen;
    VOS_UINT8                               aucData[4];
} CDS_RX_SDU_DATA_IND_STRU;

extern CDS_ENTITY_STRU   g_astCdsEntity[];


/*���ö�ʱ��ʱ��*/
#define CDS_SET_TMR_LEN(pstCdsEntity,ulTmrId,TmrLen)          ((pstCdsEntity)->astTimer[ulTmrId].ulTmrLen = (TmrLen))
#define CDS_GET_TMR_LEN(pstCdsEntity,ulTmrId)                 ((pstCdsEntity)->astTimer[ulTmrId].ulTmrLen)

/*����GU RAB SR״̬*/
/*lint -emacro({701}, CDS_SET_GU_RAB_SR_FLG)*/
#define CDS_SET_GU_RAB_SR_FLG(pstCdsEntity,ucRabId)         (((pstCdsEntity)->usGuRabSRStatus) |= (VOS_UINT16)(1 << ((ucRabId)-1)))
#define CDS_CLR_GU_RAB_SR_FLG(pstCdsEntity,ucRabId)         (((pstCdsEntity)->usGuRabSRStatus) &= (~(VOS_UINT16)(1 << ((ucRabId)-1))))
#define CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity)             ((pstCdsEntity)->usGuRabSRStatus = 0)
/*lint -emacro({701}, CDS_GET_GU_RAB_SR_FLG)*/
#define CDS_GET_GU_RAB_SR_FLG(pstCdsEntity,ucRabId)         ((((pstCdsEntity)->usGuRabSRStatus) & (1 << ((ucRabId)-1))) >> ((ucRabId)-1))

#define CDS_SET_CDMA_RAB_SR_FLG(pstCdsEntity,ucRabId)         (((pstCdsEntity)->usCDMARabSRStatus) |= (VOS_UINT16)(1 << ((ucRabId)-1)))
#define CDS_CLR_CDMA_RAB_SR_FLG(pstCdsEntity,ucRabId)         (((pstCdsEntity)->usCDMARabSRStatus) &= (~(VOS_UINT16)(1 << ((ucRabId)-1))))
#define CDS_CLR_CDMA_ALL_RAB_SR_FLG(pstCdsEntity)             ((pstCdsEntity)->usCDMARabSRStatus = 0)
#define CDS_GET_CDMA_RAB_SR_FLG(pstCdsEntity,ucRabId)         ((((pstCdsEntity)->usCDMARabSRStatus) & (1 << ((ucRabId)-1))) >> ((ucRabId)-1))


#define CDS_SET_VOICEPREFER_ACT_FLAG(pstCdsEntity,ulActFlag)          (((pstCdsEntity)->ulVoicePreferActFlag) = (ulActFlag))
#define CDS_GET_VOICEPREFER_ACT_FLAG(pstCdsEntity)                    ((pstCdsEntity)->ulVoicePreferActFlag)
/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  8 ��������
*****************************************************************************/

extern VOS_VOID   CDS_SendEventToCds(VOS_UINT32 ulEvent);
extern VOS_VOID   CDS_LoopBackModeBTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg);
extern CDS_ENTITY_STRU* CDS_GetCdsEntity(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_UINT32 CDS_StartTimer(CDS_ENTITY_STRU  *pstCdsEntity, VOS_UINT32 ulTmrId);
extern VOS_VOID   CDS_StopTimer(CDS_ENTITY_STRU  *pstCdsEntity, VOS_UINT32 ulTmrId);
extern VOS_VOID   CDS_RxLoopBackPkt(CDS_LB_DL_SDU_STRU *pstDlData, CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID   CDS_ClearLoopBackQue(const CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID   CDS_LoopBackModeBTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg);
extern VOS_VOID   CDS_Dl10msPeridicTmrTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg);
extern VOS_VOID   CDS_UlDataProtectTmrTimeoutProc(const REL_TIMER_MSG  *pstTmrMsg);
extern VOS_VOID   CDS_DLDataFlowStats(VOS_UINT8 ucBearerId, VOS_UINT32 ulPktLen, const CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID   CDS_ULDataFlowStats(VOS_UINT8 ucBearerId, VOS_UINT32 ulPktLen, const CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID   CDS_AllocMemForAdq(VOS_VOID);

/*****************************************************************************
  9 OTHERS����
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

