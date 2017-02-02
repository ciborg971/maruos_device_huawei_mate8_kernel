
#ifndef _RABM_DEF_H_
#define _RABM_DEF_H_

/* Determine if a C++ compiler is being used.  If so, ensure that standard
   C is used to process the API information.  */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define RABM_FALSE   0
#define RABM_TRUE    1

#define RABM_NSAPI_OFFSET    5

/* RABMʵ���״̬ */
#define RABM_NULL                       0
#define RABM_NSAPI_ACTIVE_PENDING       1
#define RABM_NSAPI_ACTIVE_NO_RAB        2
#define RABM_NSAPI_ACTIVE_WITH_RAB      3
#define RABM_DATA_TRANSFER_STOP         4
#define RABM_ACT_PENDING_WITH_RAB       5

#define RABM_SI_ACTIVE_WITH_RAB         1

/* TIMER */
#define RABM_TIMER_INVALID              0xffffffff

/* ָ�� */
#define RABM_POINTER_NULL               0


/* CN DOMAIN */
#define RABM_CN_CS                      RRC_NAS_CS_DOMAIN
#define RABM_CN_PS                      RRC_NAS_PS_DOMAIN



/* TRAFFIC CLASS */
#define RABM_CONVERSATION_CLASS   0x20
#define RABM_STREAM_CLASS         0x40

/* ERROR SDU DELIVERY */
#define RABM_ERROR_SDU_DELIVERY_NO_DET    1

/* TC STATE */
#define RABM_TC_STATE_NULL              6
#define RABM_TC_STATE_WITH_RAB          7

/* �������������� */
#define RABM_DOWNLINK   0
#define RABM_UPLINK        1

#define Rabm_TASK_NOT_START         0                   /*TASK Rabm û������*/
#define Rabm_TASK_START             1                   /*TASK Rabm �Ѿ�����*/

/* �ؽ�RAB������RABM��������̬�����ڱ�ʶ��Щ��̬�������Ķ�ʱ�� */
#define RABM_REESTABLISH_REQ_SENT       0      /* RABM�Ѿ�������REESTABLISH_REQ������Ϣ�����ڵȴ�REESTABLISH_CNF��Ӧ��Ϣ��״̬ */
#define RABM_REESTABLISH_RAB_PENDING    1      /* RABM�Ѿ��յ���REESTABLISH_CNF��Ӧ��Ϣ�����ڵȴ�RAB�ؽ���״̬ */

#define NAS_RABM_INVALID_RAB_ID         (0xFF)

#define NAS_RABM_QOS_TRAFFIC_CLASS_MASK                     (0xE0)    /* 1110 0000*/
#define NAS_RABM_QOS_TRAFFIC_CLASS_BIT_OFFSET               (5)       /* Traffic Class�����ڸ��ֽڵ�λƫ��λ */
#define NAS_RABM_QOS_TRAFFIC_CLASS_BYTE_OFFSET              (3)       /* Traffic Class������QOS�ֽ����е�λ�� */

#define NAS_RABM_QOS_TRANSFER_DELAY_MASK                    (0xFC)    /* 1111 1100*/
#define NAS_RABM_QOS_TRANSFER_DELAY_BIT_OFFSET              (2)       /* Transfer Delay�����ڸ��ֽڵ�λƫ��λ */
#define NAS_RABM_QOS_TRANSFER_DELAY_BYTE_OFFSET             (8)       /* Transfer Delay������QOS�ֽ����е�λ�� */

#define NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_MASK         (0x03)    /* 0000 0011 */
#define NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_BYTE_OFFSET  (8)       /* Traffic Handling Priority ������QOS�ֽ����е�λ�� */

#define NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_MASK              (0x0F)    /* 0000 1111*/
#define NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_BYTE_OFFSET       (11)      /* SSD ������QOS�ֽ����е�λ�� */

#define NAS_RABM_QOS_SIGNAL_IND_MASK                        (0x10)    /* 0001 0000*/
#define NAS_RABM_QOS_SIGNAL_IND_BIT_OFFSET                  (4)       /* Signalling-Indication �����ڸ��ֽڵ�λƫ��λ */
#define NAS_RABM_QOS_SIGNAL_IND_BYTE_OFFSET                 (11)      /* Signalling-Indication ������QOS�ֽ����е�λ�� */

/* QOS_TRAFFIC_CLASS */
#define NAS_RABM_QOS_TRAFFIC_CLASS_SUBSCRIBE                (0)
#define NAS_RABM_QOS_TRAFFIC_CLASS_CONVERSATIONAL           (1)
#define NAS_RABM_QOS_TRAFFIC_CLASS_STREAMING                (2)
#define NAS_RABM_QOS_TRAFFIC_CLASS_INTERACTIVE              (3)
#define NAS_RABM_QOS_TRAFFIC_CLASS_BACKGROUND               (4)

/* QOS_QOS_TRAFFIC_HANDLING */
#define NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_1            (1)
#define NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_2            (2)
#define NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_3            (3)

/* QOS_SRC_STATISTICS_DESCRIPTOR */
#define NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_UNKNOWN           (0)
#define NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_SPEECH            (1)

/* QOS_TRANSFER_DELAY */
#define NAS_RABM_QOS_TRANSFER_DELAY_150MS                   (0X0F)

/* QOS_SIGNAL_IND */
#define NAS_RABM_QOS_SIGNAL_IND_NOT_OPTIMISE                (0)
#define NAS_RABM_QOS_SIGNAL_IND_OPTIMISE                    (1)


#define NAS_RABM_QOS_DELIVERY_ERRORNEOUS_SDU_MASK           (0x07)

#define   D_RMC_RR_ACTION_SETUP         0
#define   D_RMC_RR_ACTION_RECFG         1
#define   D_RMC_RR_ACTION_RELEASE       2

typedef enum
{
    RABM_TIMER_NAME_NSAPI_5 = 0,
    RABM_TIMER_NAME_NSAPI_6,
    RABM_TIMER_NAME_NSAPI_7,
    RABM_TIMER_NAME_NSAPI_8,
    RABM_TIMER_NAME_NSAPI_9,
    RABM_TIMER_NAME_NSAPI_10,
    RABM_TIMER_NAME_NSAPI_11,
    RABM_TIMER_NAME_NSAPI_12,
    RABM_TIMER_NAME_NSAPI_13,
    RABM_TIMER_NAME_NSAPI_14,
    RABM_TIMER_NAME_NSAPI_15,
    RABM_TIMER_NAME_COMMON,
    RABM_TIMER_NAME_FD_RETRY,

    RABM_TIMER_NAME_FD_FLUX_DETECT,

    RABM_TIMER_NAME_BUTT
}RABM_TIMER_NAME_ENUM;     /*RABM��ʱ����Ӧ��NSAPI���������ö�ʱ��ʱ��name�ֶ�*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif
