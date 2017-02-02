

#ifndef __RABM_2G_STRU_H__
#define __RABM_2G_STRU_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "rabmstru.h"
#include "NasGmmInterface.h"

#include "TafAppRabm.h"
#include "RabmInterface.h"

#include "TTFMem.h"
#include "NasPdcpInterface.h"

#include "rabmdef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define RABM_2G_MAX_ENT_NUM             11                        /*2G��RABMʵ��������*/
#define RABM_3G_PS_MAX_ENT_NUM          11                        /*3G��RABMʵ��������*/

#define RABM_MIN_NSAPI_NUMBER           5                         /*NSAPI����Ӧ����С��*/
#define RABM_MAX_NSAPI_NUMBER           15                        /*NSAPI����Ӧ������*/

#define RABM_2G_NSAPI_OFFSET            5                         /*2G��RABMʵ�������±���NSAPI�Ĳ�ֵ*/

#define RABM_SUCCESS                    0                         /*RABMģ�麯�����سɹ�*/
#define RABM_FAILURE                    1                         /*RABMģ�麯������ʧ��*/
#define RABM_MSGILLOGIC                 2                         /*�����߼�����Ϣ*/
#define RABM_PARAILLEGAL                3                         /*��ڲ����Ƿ�*/
#define RABM_MSGWRONG                   4                         /*��Ϣ�����ݳ���*/
#define RABM_STATEWRONG                 5                         /*NSAPI��Ӧ��״̬�ֶγ���*/

#define RABM_YES                        0                         /*����*/
#define RABM_NO                         1                         /*������*/

#define RABM_COMMON_TIMER_NUMBER        13                         /*��ʹ�õĹ�����ʱ���ĸ���*/

#define RABM_LONG_REPRESENT_MAX         0xFFFFFFFF                /*һ���޷��ŵ�long�ͱ������ܱ�ʾ�������ֵ:2^32-1*/

#define RABM_N_PDU_OFFSET               2                         /*N-PDU ������VALUE�������е�����ƫ��*/

#define RABM_SUBMOD_NULL                0                         /* ����ģ�� */
#define RABM_LOG_INFO( String )         PS_NAS_LOG( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_INFO, String )
#define RABM_LOG_NORMAL( String )       PS_NAS_LOG( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, String )
#define RABM_LOG_WARNING( String )      PS_NAS_LOG( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_WARNING, String )
#define RABM_LOG_ERROR( String )        PS_NAS_LOG( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_ERROR, String )

#define RABM_LOG1_INFO( String, Para1 )        PS_NAS_LOG1( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_INFO, String, Para1 )
#define RABM_LOG1_NORMAL( String, Para1 )      PS_NAS_LOG1( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, String, Para1 )
#define RABM_LOG1_WARNING( String, Para1 )     PS_NAS_LOG1( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_WARNING, String, Para1 )
#define RABM_LOG1_ERROR( String, Para1 )       PS_NAS_LOG1( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_ERROR, String, Para1 )

#define RABM_LOG2_INFO( String, Para1, Para2 )        PS_NAS_LOG2( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_INFO, String, Para1, Para2 )
#define RABM_LOG2_NORMAL( String, Para1, Para2 )      PS_NAS_LOG2( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, String, Para1, Para2 )
#define RABM_LOG2_WARNING( String, Para1, Para2 )     PS_NAS_LOG2( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_WARNING, String, Para1, Para2 )
#define RABM_LOG2_ERROR( String, Para1, Para2 )       PS_NAS_LOG2( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_ERROR, String, Para1, Para2 )

#define RABM_LOG3_INFO( String, Para1, Para2, Para3 )        PS_NAS_LOG3( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_INFO, String, Para1, Para2, Para3 )
#define RABM_LOG3_NORMAL( String, Para1, Para2, Para3 )      PS_NAS_LOG3( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, String, Para1, Para2, Para3 )
#define RABM_LOG3_WARNING( String, Para1, Para2, Para3 )     PS_NAS_LOG3( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_WARNING, String, Para1, Para2, Para3 )
#define RABM_LOG3_ERROR( String, Para1, Para2, Para3 )       PS_NAS_LOG3( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_ERROR, String, Para1, Para2, Para3 )

#define RABM_LOG4_INFO( String, Para1, Para2, Para3, Para4 )        PS_NAS_LOG4( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_INFO, String, Para1, Para2, Para3, Para4 )
#define RABM_LOG4_NORMAL( String, Para1, Para2, Para3, Para4 )      PS_NAS_LOG4( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, String, Para1, Para2, Para3, Para4 )
#define RABM_LOG4_WARNING( String, Para1, Para2, Para3, Para4 )     PS_NAS_LOG4( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_WARNING, String, Para1, Para2, Para3, Para4 )
#define RABM_LOG4_ERROR( String, Para1, Para2, Para3, Para4 )       PS_NAS_LOG4( WUEPS_PID_RABM, RABM_SUBMOD_NULL, PS_LOG_LEVEL_ERROR, String, Para1, Para2, Para3, Para4 )



/* ======================= */   /* RABӳ��ʵ��ı����� */
#define RAB_MAP_CHG_MASK_AS_ID          0x01
#define RAB_MAP_CHG_MASK_DL_CALLBACK    0x02
#define RAB_MAP_CHG_MASK_UL_CALLBACK    0x04

/* ======================= */   /* ��ЧID���� */
#define RAB_MAP_INVALID_RAB_ID          0xff
#define RAB_MAP_INVALID_AS_ID           0xff


/* RabIdֵ����ΧΪ:[5,15] */
#define RAB_MAP_RAB_IS_VALID(ucRabId)   \
    ( (RABM_MIN_NSAPI_NUMBER <= (ucRabId)) && (RABM_MAX_NSAPI_NUMBER >= (ucRabId)) )

/* AsIdֵ��W��ΧΪ:[5,32], G��ΧΪ[5,15]������ȡW��ֵ */
#define RAB_MAP_ASID_IS_VALID(ucAsId)     \
    ( (NAS_MML_NET_RAT_TYPE_GSM == NAS_RABM_GetCurrentSysMode()) ? \
      ( (RABM_MIN_NSAPI_NUMBER <= (ucAsId)) && (RABM_MAX_NSAPI_NUMBER >= (ucAsId)) ) :\
      ( (PS_WUE_MIN_T_RB_ID <= (ucAsId)) && (PS_WUE_MAX_RB_ID >= (ucAsId)) ) )

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
typedef enum
{
    /*������ʱ������*/
    RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1 = 0,
    RABM_TIMER_PARA_3_TO_2_T3,

    /*ʵ�嶨ʱ������*/
    RABM_TIMER_PARA_ACT_REQ_T1,

    /* �ؽ�RABʱʹ�õĶ�ʱ�� */
    RABM_TIMER_PARA_REESTRAB_TIMER,

    RABM_TIMER_FASTDORM_FLUX_DETECT,                                            /* ������������ⶨʱ������ʱ�����Ƿ��������仯 */
    RABM_TIMER_FASTDORM_RETRY,                                                  /* RETRY��ʱ������ʱ�����³���FD */
    RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT,                                    /* ��ѯGMM��ǰ����ҵ��״̬������ʱ������ʱ��ֹͣ */

    RABM_TIMER_RESEND_EST_REQ,

    RABM_TIMER_RAB_REESTABLISH_PENDING,

    RABM_TIMER_VOICEPREFER_DELAY,
    RABM_TIMER_VOICEPREFER_REQRY_GMM_DELAY,

    RABM_TIMER_PARA_BUTT
}RABM_TIMER_PARA_ENUM;     /*RABM��ʱ�������֣��������ö�ʱ��ʱ��para�ֶ�*/


typedef enum
{
    RABM_NSAPI_5  = 0,
    RABM_NSAPI_6 ,
    RABM_NSAPI_7 ,
    RABM_NSAPI_8 ,
    RABM_NSAPI_9 ,
    RABM_NSAPI_10 ,
    RABM_NSAPI_11 ,
    RABM_NSAPI_12 ,
    RABM_NSAPI_13 ,
    RABM_NSAPI_14 ,
    RABM_NSAPI_15 ,

    RABM_NSAPI_BUTT
}RABM_NSAPI_ENUM;             /*ÿ��NSAPI����Ӧ����������*/


typedef enum
{
    RABM_2G_NULL = 0,
    RABM_NSAPI_OK_TRANSMODE_NO,
    RABM_DATA_TRANS_READY,
    RABM_ROUT_AREA_UPDATE,
    RABM_DATA_TRANS_STOP,

    RABM_STATE_BUTT
}RABM_2G_STATE_ENUM;        /*2G��RABMʵ���״̬*/

typedef enum
{
    RABM_2G_TO_3G_SWITCH_ON = 0,
    RABM_2G_TO_3G_SWITCH_OFF,

    RABM_2G_TO_3G_SWITCH_BUTT
}RABM_2G_TO_3G_SWITCH_ENUM;  /*��ʶ��ǰ�Ƿ����ڽ���2G��3G���л�*/

typedef enum
{
    RABM_3G_TO_2G_SWITCH_ON = 0,
    RABM_3G_TO_2G_SWITCH_OFF,

    RABM_3G_TO_2G_SWITCH_BUTT
}RABM_3G_TO_2G_SWITCH_ENUM;  /*��ʶ��ǰ�Ƿ����ڽ���3G��2G���л�*/

enum RABM_RA_T1_SWITCH_ENUM
{
    RABM_ROUTING_AREA_UPDATE_T1_ON = 0,
    RABM_ROUTING_AREA_UPDATE_T1_OFF,

    RABM_ROUTING_AREA_UPDATE_T1_BUTT
};/*��ʶ2G��·�������¶�ʱ���Ƿ�����*/

typedef VOS_UINT8 RABM_RA_T1_SWITCH_ENUM_UINT8;

enum RABM_ACT_REQ_T1_SWITCH_ENUM
{
    RABM_ACT_REQ_T1_ON = 0,
    RABM_ACT_REQ_T1_OFF,

    RABM_ACT_REQ_T1_BUTT
}; /*��ʶRabm.Act.Req.T1��ʱ���Ƿ�����*/

typedef VOS_UINT8  RABM_ACT_REQ_T1_SWITCH_ENUM_UINT8;

typedef enum
{
    RABM_2G_TO_3G_T1_ON = 0,
    RABM_2G_TO_3G_T1_OFF,

    RABM_2G_TO_3G_T1_BUTT
}RABM_2G_TO_3G_T1_SWITCH_ENUM;/*��ʶRabm.2To3.T1��ʱ���Ƿ�����*/

typedef enum
{
    RABM_3G_TO_2G_T1_ON = 0,
    RABM_3G_TO_2G_T1_OFF,

    RABM_3G_TO_2G_T1_BUTT
}RABM_3G_TO_2G_T1_SWITCH_ENUM;/*��ʶRabm.3To2.T1��ʱ���Ƿ�����*/

enum RABM_3G_TO_2G_T3_SWITCH_ENUM
{
    RABM_3G_TO_2G_T3_ON = 0,
    RABM_3G_TO_2G_T3_OFF,

    RABM_3G_TO_2G_T3_BUTT
};/*��ʶRabm.3To2.T3��ʱ���Ƿ�����*/

typedef VOS_UINT8  RABM_3G_TO_2G_T3_SWITCH_ENUM_UINT8;

typedef enum
{
    RABM_3G_TO_2G_RA_UPDATE_ON = 0,
    RABM_3G_TO_2G_RA_UPDATE_OFF,

    RABM_3G_TO_2G_RA_UPDATE_BUTT
}RABM_3G_TO_2G_RA_UPDATE_SWITCH_ENUM;/*��ʶRabm.3To2.RA.Update��ʱ���Ƿ�����*/

typedef enum
{
    RABM_NSAPI_ACTIVE_SWITCH_ON = 0,
    RABM_NSAPI_ACTIVE_SWITCH_OFF,

    RABM_NSAPI_ACTIVE_SWITCH_BUTT
}RABM_NSAPI_ACTIVE_SWITCH_ENUM;               /*��ʶĳNSAPI�Ƿ񼤻���*/

typedef enum
{
    RABM_FLUX_REPORT_SWITCH_ON = 0,
    RABM_FLUX_REPORT_SWITCH_OFF,

    RABM_FLUX_REPORT_SWITCH_BUTT
}RABM_FLUX_REPORT_SWITCH_ENUM;               /*��ʶ�Ƿ��ϱ�����*/

typedef enum
{
    RABM_FLUX_REPORT_TIMER_SWITCH_ON = 0,
    RABM_FLUX_REPORT_TIMER_SWITCH_OFF,

    RABM_FLUX_REPORT_TIMER_BUTT
}RABM_FLUX_REPORT_TIMER_SWITCH_ENUM;      /*��ʶ�����ϱ���ʱ���Ƿ�����*/

enum RABM_FLUX_WRITE_NV_TIMER_SWITCH_ENUM
{
    RABM_FLUX_WRITE_NV_TIMER_SWITCH_ON = 0,
    RABM_FLUX_WRITE_NV_TIMER_SWITCH_OFF,

    RABM_FLUX_WRITE_NV_TIMER_BUTT
};      /*��ʶ�����ϱ���ʱ���Ƿ�����*/

typedef VOS_UINT32       RABM_FLUX_WRITE_NV_TIMER_SWITCH_ENUM_U32;

typedef enum
{
    RABM_FLUX_WRITE_NV = 0,
    RABM_FLUX_CLEAR_NV,

    RABM_FLUX_BUTT
}RABM_FLOW_NV_OPT_ENUM;
enum NAS_RABM_TIMER_STATUS_ENUM
{
    NAS_RABM_TIMER_STATUS_RUNING,            /* ��ʱ������״̬ */
    NAS_RABM_TIMER_STATUS_STOP,              /* ��ʱ��ֹͣ״̬ */
    NAS_RABM_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 NAS_RABM_TIMER_STATUS_ENUM_UINT8;



typedef enum
{
    RABM_GPRS_SYS_INFO_SWITCH_ON = 0,
    RABM_GPRS_SYS_INFO_SWITCH_OFF,

    RABM_GPRS_SYS_INFO_TIMER_BUTT
}RABM_GPRS_SYS_INFO_SWITCH_ENUM;             /*��ʶ3G����2G���ȴ�GPRS֧��������Ϣ�Ķ�ʱ���Ƿ�����*/

typedef enum
{
    RABM_TRANSMODE_LEGAL = 0,
    RABM_TRANSMODE_ILLEGAL,

    RABM_TRANSMODE_ILLEGAL_BUTT
}RABM_TRANSMODE_LEGITIMACY_ENUM;            /*���ô���ģʽʱ����ڲ����е�TRANSMODE�ֶ��Ƿ�Ϸ��ı��*/


typedef enum
{
    RABM_RA_UPDATE_CAUSE_NORMAL = 0,
    RABM_RA_UPDATE_CAUSE_3G_TO_2G,

    RABM_RA_UPDATE_CAUSE_BUTT
}RABM_RA_UPDATE_CAUSE_ENUM;                   /*2G�з���·�������µ�ԭ��*/

typedef enum
{
    RABM_CALCULATE_TIME_SUCCESS = 0,
    RABM_CALCULATE_TIME_FAIL,

    RABM_CALCULATE_TIME_BUTT
}RABM_CALCULATE_TIME_ENUM;                      /*����ʱ��ɹ����ı�־*/

typedef enum
{
    RABM_GET_CUR_NET_FIRSTTIME_ON = 0,
    RABM_GET_CUR_NET_FIRSTTIME_OFF,

    RABM_GET_CUR_NET_FIRSTTIME_BUTT
}RABM_GET_CUR_NET_FIRSTTIME_ENUM;            /*��ʶ��һ�λ�ȡ�����Ƿ����*/

typedef enum
{
    RABM_FLOW_RPT_CTRL_ENABLE = 0,
    RABM_FLOW_RPT_CTRL_DISABLE,

    RABM_FLOW_RPT_CTRL_BUTT
}RABM_FLOW_RPT_CTRL_ENUM;                      /*�����Զ��ϱ����Ե�ʹ�����*/

/*****************************************************************************
 ö����  : RNIC_MNTN_EVENT_TYPE_ENUM
 ö��˵��: RNIC��ά�ɲ��¼�ԭ��
*****************************************************************************/
enum NAS_RABM_MNTN_EVT_TYPE_ENUM
{
    ID_NAS_RABM_MNTN_EVT_UL_PKT_LOST    = 0x2001,
    ID_NAS_RABM_MNTN_EVT_DL_PKT_LOST    = 0x2002,
    ID_NAS_RABM_MNTN_EVT_BUTT
};
typedef VOS_UINT32 NAS_RABM_MNTN_EVT_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����  : RNIC_MNTN_EVENT_TYPE_ENUM
 ö��˵��: RNIC��ά�ɲ��¼�ԭ��
*****************************************************************************/
enum NAS_RABM_PKT_FLOW_DIR_ENUM
{
    NAS_RABM_PKT_FLOW_DIR_UPLINK        = 0x00,
    NAS_RABM_PKT_FLOW_DIR_DOWNLINK      = 0x01
};
typedef VOS_UINT8 NAS_RABM_PKT_FLOW_DIR_ENUM_UINT8;



/*****************************************************************************
  5 ��Ϣͷ����

ģ���������士HEADER
#define MAPS_TEMPLATE_HEADER    VOS_UINT16    usTotalsMsgLen;\
                                                      VOS_UINT32    ulSendModuleId;\
                                                      VOS_UINT32    ulRecvModuleId;\
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����

typedef struct
{
    MAPS_TEMPLATE_HEADER
    VOS_UINT8    aucData[2];     ��Ϣ��

} MAPS_TEMPLATE_MSG;
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNsapi;
    RABM_2G_STATE_ENUM                  State;              /*��ʵ���״̬*/
    RABM_TRANS_MODE_ENUM                TransMode;          /*����ģʽ*/
    RABM_QOS_STRU                       stQos;              /*��ʵ���Ӧ��QoS*/
    RABM_RA_UPDATE_CAUSE_ENUM           RAUpdateCause;      /*2G��·�������·�����ԭ��*/
    VOS_UINT8                           ucPppFlg;           /*��ʶ�Ƿ�֧��PPP��0��֧�֣�1:��֧��*/
}RABM_2G_ENTITY_ST;                                 /*RABM��״̬��ʵ��*/


typedef struct
{
    HTIMER                             *pstHTimer;
    VOS_UINT32                          ulPid;                                  /*PID������������������*/
    VOS_UINT32                          ulLength;
    RABM_TIMER_NAME_ENUM                Name;
    RABM_TIMER_PARA_ENUM                Param;
    VOS_UINT8                           ucMode;

}RABM_START_TIMER_ST;              /*������ʱ��ʱʹ�õ����ݽṹ*/


/* ���ݷ��ͽӿ� */
typedef VOS_UINT32 (*RAB_UL_DATA_CALLBACK)(VOS_UINT8 ucRabId, VOS_UINT8 ucRbId, TTF_MEM_ST *pstData);
typedef VOS_UINT32 (*RAB_DL_DATA_CALLBACK)(VOS_UINT8 ucRabId, TTF_MEM_ST *pstData);


/* ======================== */    /* RABӳ��ʵ�����ݽṹ */
/* ����ע������
   1.RAB��W�µĸ��Ϊ����ͳһ��G������������ָNSAPI
   2.G��û��RB��Ϊ����ͳһ��������Gģ�������RAB��RB�����Ƕ���ָNSAPI
*/
/* RABӳ��ʵ�� */
typedef struct
{
    PS_BOOL_ENUM_UINT8      enucExistInd;       /* ��RAB���ӵ�״̬ */
    VOS_UINT8               ucRabId;            /* W����RAB ID [5,15]��G����NSAPI[5,15] */
    VOS_UINT8               ucLinkdRabId;       /* W����RAB ID [5,15]��G����NSAPI[5,15] */
    VOS_UINT8               ucAsId;             /* �����ID��W��RB������RB ID[5, 32]��
                                                   RB��������RAB Data Buffer ID,����RAB_ID[5, 15]��
                                                   G����NSAPI[5, 15]*/
    RAB_UL_DATA_CALLBACK    pUlDataCallBack;    /* �������ݷ��ͽӿ� */
    RAB_DL_DATA_CALLBACK    pDlDataCallBack;    /* �������ݷַ��ӿ� */
} RAB_MAP_STRU;


/* ======================== */    /* RABӳ��ʵ���Ӧ�Ľ�������з��ͻص����� */
typedef struct
{
    VOS_UINT8               ucMode;             /* ����ģʽ��W or G */
    VOS_UINT8               ucState;            /* RAB��NSAPI��״̬ */
    VOS_UINT16              usRsv;
    RAB_UL_DATA_CALLBACK    pAsUlDataCallBack;  /* �����ص�����ָ�� */
} RAB_AS_UL_DATA_CALLBACK_STRU;


enum RAB_UL_CB_NAME_ENUM
{
    RAB_UL_CB_NAME_NULL             = 0,
    RAB_UL_CB_NAME_SND_RABM,
    RAB_UL_CB_NAME_SND_PDCP,
    RAB_UL_CB_NAME_SND_SNDCP,
    RAB_UL_CB_NAME_BUTT
};
typedef VOS_UINT16 RAB_UL_CB_NAME_ENUM_UINT16;

enum RAB_DL_CB_NAME_ENUM
{
    RAB_DL_CB_NAME_NULL          = 0,
    RAB_DL_CB_NAME_DEFAULT,
    RAB_DL_CB_NAME_APP_REG,
    RAB_DL_CB_NAME_BUTT
};
typedef VOS_UINT16 RAB_DL_CB_NAME_ENUM_UINT16;

#define RABM_TRACE_RAB_MAP_INFO_MSG     0xBA03;

typedef struct
{
    VOS_MSG_HEADER                                      /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT32                      ulMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    PS_BOOL_ENUM_UINT8              enucExistInd;
    VOS_UINT8                       ucRabId;
    VOS_UINT8                       ucAsId;
    VOS_UINT8                       aucRsv[1];
    RAB_UL_CB_NAME_ENUM_UINT16      enUlCbName;
    RAB_DL_CB_NAME_ENUM_UINT16      enDlCbName;
} RABM_TRACE_RAB_MAP_INFO_STRU;

#define EVT_NAS_RABM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa          /* ΪPC���̻طŶ������Ϣ */

/*****************************************************************************
 Structure      : NAS_RABM_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC�طŹ��̣��洢����RABM��ص�ȫ�ֱ���
 Message origin :
*****************************************************************************/

typedef struct
{
    RABM_3G_TO_2G_SWITCH_ENUM      pc_gRabm3GTo2GSwitch;
    RABM_3G_TO_2G_T1_SWITCH_ENUM   pc_gRabm3GTo2GT1Switch;
    VOS_UINT32                     pc_gRabm2GTo3GDataResume;

    VOS_UINT8               pc_g_ucReestTimerFlg;                                                 /* RABM_TRUE:�ؽ�TIMER��Ч��RABM_FALSE:��Ч */
    VOS_UINT8               pc_g_aucSiMapEnt[256];                                                /* SI��RABMʵ���ӳ���ϵ                   */
    RABM_ENTITY_PS_STRU     pc_g_aRabmPsEnt[RABM_PS_MAX_ENT_NUM];                       /* PS��RABMʵ���ȫ����                     */
    RABM_ENTITY_CS_STRU     pc_g_aRabmCsEnt[RABM_CS_MAX_ENT_NUM];                       /* CS��RABMʵ���ȫ����                     */
    RABM_TC_INF_STRU        pc_g_RabmTcInf;
} NAS_RABM_OUTSIDE_RUNNING_CONTEXT_ST;

/*****************************************************************************
 Structure      : NAS_RABM_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC�طŹ��̣�����RABM��ص�ȫ�ֱ���ͨ��������Ϣ�ṹ����
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                             usMsgID;
    VOS_UINT16                             usReserved;                            /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    NAS_RABM_OUTSIDE_RUNNING_CONTEXT_ST    stOutsideCtx;
}NAS_RABM_SDT_MSG_ST;

typedef struct
{
    VOS_UINT32                          ulDSLastLinkTime;
    VOS_UINT32                          ulDSTotalSendFluxLow;
    VOS_UINT32                          ulDSTotalSendFluxHigh;
    VOS_UINT32                          ulDSTotalLinkTime;
    VOS_UINT32                          ulDSTotalReceiveFluxLow;
    VOS_UINT32                          ulDSTotalReceiveFluxHigh;
}NAS_RABM_TOTAL_RX_BYTES_STRU;

/*****************************************************************************
 �ṹ��  : NAS_RABM_MNTN_UL_PKT_LOST_STRU
 �ṹ˵��: RABM�������ά�ɲ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    NAS_RABM_MNTN_EVT_TYPE_ENUM_UINT32  enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT8                           ucPoint;
    VOS_UINT8                           aucRsv[3];
} NAS_RABM_MNTN_PKT_LOST_STRU;


/*****************************************************************************
  4 ȫ�ֱ�������

extern VOS_UINT8* pgucMapsTemplateBuffer;   ָ�룫ȫ�ֱ�ʶ�����ͣ�ģ��������������
*****************************************************************************/
/*2G��RABMʵ��Ľṹ������ */
extern RABM_2G_ENTITY_ST                                    gastRabm2GEntity[RABM_2G_MAX_ENT_NUM];

/*���Լ�¼3G�з���3G��2G�л�ʱ���ڷ����л�ǰ������״̬*/
extern VOS_UCHAR                                            gaucRabm3GPreState[RABM_3G_PS_MAX_ENT_NUM];

/*��ʶ��ǰ�Ƿ����ڽ���2G��3G���л�*/
extern RABM_2G_TO_3G_SWITCH_ENUM                            gRabm2GTo3GSwitch;

/*��ʶ��ǰ�Ƿ����ڽ���3G��2G���л�*/
extern RABM_3G_TO_2G_SWITCH_ENUM                            gRabm3GTo2GSwitch;

/*��ʶ2G��·�������¶�ʱ���Ƿ�����*/
extern RABM_RA_T1_SWITCH_ENUM_UINT8                         gRabmRAT1Switch;

/*��ʶRabm.Act.Req.T1��ʱ���Ƿ�����(�Զ�ʱ����ulName��Ϊ����)*/
extern RABM_ACT_REQ_T1_SWITCH_ENUM_UINT8                    gaRabmActReqT1Switch[RABM_2G_MAX_ENT_NUM];

/*��ʶRabm.2To3.T1��ʱ���Ƿ�����*/
extern RABM_2G_TO_3G_T1_SWITCH_ENUM                         gRabm2GTo3GT1Switch;

/*��ʶRabm.3To2.T1��ʱ���Ƿ�����*/
extern RABM_3G_TO_2G_T1_SWITCH_ENUM                         gRabm3GTo2GT1Switch;

/*��ʶRabm.3To2.T3��ʱ���Ƿ�����*/
extern RABM_3G_TO_2G_T3_SWITCH_ENUM_UINT8                   gRabm3GTo2GT3Switch;

/*��ʶRabm.3To2.RA.Update��ʱ���Ƿ�����*/
extern RABM_3G_TO_2G_RA_UPDATE_SWITCH_ENUM                  gRabm3GTo2GRAUpdateSwitch;

/*TLLI��ȫ�ֱ���*/
extern VOS_UINT32                                           gulRabmTLLI;

/*��ʱ��ʱ������(�Զ�ʱ����PARAö����Ϊ����)*/
extern VOS_UINT32                                           gaulRabmTimerLength[RABM_TIMER_PARA_BUTT];

/*ʵ�嶨ʱ��(�Զ�ʱ����NAMEö����Ϊ����)*/
extern HTIMER                                               gastRabmEntityTimer[RABM_MAX_ENT_NUM];

/*���ö�ʱ��(�Զ�ʱ����PARAö����Ϊ����)*/
extern HTIMER                                               gastRabmCommonTimer[RABM_COMMON_TIMER_NUMBER];

/*��ʶ��һ�λ�ȡ�����Ƿ����*/
extern RABM_GET_CUR_NET_FIRSTTIME_ENUM                      gRabmGetCurNetFirsttime;

/*��ʶ��ǰ����������ģʽ*/
extern RABM_CUR_NET_ENUM                                    gRabmCurNet;

/*2G��3G�л��������ָ��ı�־*/
extern VOS_UINT32                                           gRabm2GTo3GDataResume;

/*3G��2G�л�ʱ��RABM����NSAPI��RB��ӳ���ϵ*/
extern SNDCP_NSAPI_MAP_RB_INFO                              gastNsapiMapRb[SNDCP_RABM_MAX_NSAPI_NUM];

/*RABM��PDCP����֪��RCV NPDU NUM ��Ϣ*/
extern RABM_PDCP_GET_N_PDU_NUM_LIST_ST                      gPdcpRcvNpduNum;

extern GMM_RABM_NET_RAT_ENUM_UINT32     g_enNasRabmSysMode;
extern VOS_BOOL                         g_bNasRabmDataSuspendFlg;

extern NAS_RABM_TIMER_STATUS_ENUM_UINT8    g_ulNasRabmFDFluxDetectTimer;
extern NAS_RABM_TIMER_STATUS_ENUM_UINT8    g_ulNasRabmFDRetryTimer;
extern NAS_RABM_TIMER_STATUS_ENUM_UINT8    g_ulNasRabmFDWaitGmmQryRsltTimer;

extern NAS_RABM_TIMER_STATUS_ENUM_UINT8    g_ulNasRabmResendEstTimer;

extern RAB_MAP_STRU                     g_astRabMap[PS_WUE_MAX_RB_ID + 1];
extern VOS_UINT8                        g_aucRb2Rab[PS_WUE_MAX_RB_ID + 1];

#if (FEATURE_ON == FEATURE_LTE)
/* L->G���, ���ڱ��L->G������ */
extern VOS_UINT32                       g_ulNasRabmL2GFlg;
#endif


/*****************************************************************************
  8 UNION����

typedef union
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];

} MAPS_TEMPLATE_UNION;
*****************************************************************************/

/*****************************************************************************
  8 ����ָ�붨��
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

#endif /* end of Rabm2GStru.h*/
