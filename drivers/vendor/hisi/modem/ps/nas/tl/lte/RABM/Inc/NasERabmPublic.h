

#ifndef __NASRABMPUBLIC_H__
#define __NASRABMPUBLIC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "AppRabmInterface.h"
#include  "EsmRabmInterface.h"
#include  "PsTypeDef.h"
#include  "PsCommonDef.h"
#include  "PsLogdef.h"
#include  "NasCommPrint.h"
#include  "NasFileId.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define NAS_ERABM_SUCCESS                       0             /*RABMģ�麯�����سɹ�*/
#define NAS_ERABM_FAILURE                       1             /*RABMģ�麯������ʧ��*/
#define NAS_ERABM_MSGILLOGIC                    2             /*�����߼�����Ϣ*/
#define NAS_ERABM_PARAILLEGAL                   3             /*��ڲ����Ƿ�*/
#define NAS_ERABM_MSGWRONG                      4             /*��Ϣ�����ݳ���*/
#define NAS_ERABM_WAIT_EPSB_ACTT_LENGTH         2000          /*RB�����ȴ���ʱ����ʱ�䳤��*/
/*���廷��:1S*/
#if (VOS_OS_VER != VOS_WIN32)
#define NAS_ERABM_WAIT_RB_REEST_LENGTH         1000          /*����RB������ʱ����ʱ�䳤��*/
#define NAS_ERABM_WAIT_DRB_RESUME_LENGTH       40000          /*DRB�����ʱ��40s, ��ײ��ؽ�ʱ����30s*/
#define NAS_ERABM_WAIT_TC_FREE_BUFFER_LENGTH   g_ulERabmBufTimerLength /*���滷�����ݰ�60s*/
#define NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER_LENGTH   g_ulErabmRfRecoveryTimerLength
/*PC����:5S*/
#else
#define NAS_ERABM_WAIT_RB_REEST_LENGTH         5000          /*����RB������ʱ����ʱ�䳤��*/
#define NAS_ERABM_WAIT_DRB_RESUME_LENGTH       5000          /*DRB�����ʱ��,pc���� 5s*/
#define NAS_ERABM_WAIT_TC_FREE_BUFFER_LENGTH   5000          /*���滷�����ݰ�60s*/
#define NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER_LENGTH   g_ulErabmRfRecoveryTimerLength
#endif


#define NAS_ERABM_MAX_EPSB_ID                   15            /*���ĳ��غ�*/
#define NAS_ERABM_MIN_EPSB_ID                   5             /*��С�ĳ��غ�*/
#define NAS_ERABM_MAX_EPSB_NUM                  11            /*���ĳ�������*/
#define NAS_ERABM_ILL_EPSB_ID                   0xFF          /*��Ч��EPSID*/
#define NAS_ERABM_ILL_RB_ID                     0xFF          /*��Ч��RBID*/
#define NAS_ERABM_NULL                          0
#define NAS_ERABM_SUCC                          0             /*���ݷ��ͳɹ�*/
#define NAS_ERABM_FAIL                          1             /*���ݷ���ʧ��*/
#define NAS_ERABM_MOVEMENT_4_BITS               4
#define NAS_ERABM_MOVEMENT_5_BITS               5
#define NAS_ERABM_MOVEMENT_6_BITS               6
#define NAS_ERABM_MOVEMENT_7_BITS               7
#define NAS_ERABM_MOVEMENT_8_BITS               8
#define NAS_ERABM_MOVEMENT_12_BITS              12
#define NAS_ERABM_MOVEMENT_16_BITS              16
#define NAS_ERABM_MOVEMENT_24_BITS              24
#define NAS_ERABM_FLOW_LABEL_TYPE_MASK          0x000FFFFF
#define NAS_ERABM_IPDATA_IHL_MASK               0x0F
#define NAS_ERABM_IPDATA_HIGH_16_BIT_MASK       0xFFFF0000
#define NAS_ERABM_IPDATA_LOW_16_BIT_MASK        0x0000FFFF
#define NAS_ERABM_SERVICE_TYPE_HIGH_6_BIT_MASK  0xFC
#define NAS_ERABM_IPDATA_HIGH_4_BIT_MASK        0xF0
#define NAS_ERABM_IPDATA_LOW_4_BIT_MASK         0x0F
#define NAS_ERABM_OP_TRUE                       1             /*��ʶ����λ��Ч*/
#define NAS_ERABM_OP_FALSE                      0             /*��ʶ����λ��Ч*/
#define NAS_ERABM_PROCTOCOL_UDP                 (0x11)
#define NAS_ERABM_PROCTOCOL_TCP                 (0x06)
#define NAS_ERABM_ACT_EPSB_NUM_ONE              1

#define NAS_ERABM_MAX_SEG_BUFF_ITEM_NUM         (50)
#define NAS_ERABM_IPV4_ADDR_LEN                 (4)
#define NAS_ERABM_IPV6_ADDR_LEN                 (16)
#define NAS_ERABM_IPV6_PREFIX_LEN               (8)
#define NAS_ERABM_PDN_IPV4                      (0x01)              /* ֧��IPV4��ַ*/
#define NAS_ERABM_PDN_IPV6                      (0x02)              /* ֧��IPV6��ַ*/
#define NAS_ERABM_PDN_IPV4_IPV6                 (0x03)              /* ֧��IPV4��IPV6��ַ*/

#define NAS_ERABM_PRINT_LMODESTA(LModeStatus)\
            switch (LModeStatus)\
            {\
                case    NAS_ERABM_L_MODE_STATUS_NORMAL   :\
                    NAS_ERABM_NORM_LOG("RABM L_MODE_NORMAL");\
                    break;\
                case    NAS_ERABM_L_MODE_STATUS_SUSPENDED:\
                    NAS_ERABM_NORM_LOG("RABM L_MODE_SUSPENDED");\
                    break;\
                case    NAS_ERABM_L_MODE_STATUS_BUTT:\
                default   :\
                    NAS_ERABM_NORM_LOG("RABM UKNOWN L MODE STATUS");\
                    break;\
            }


#ifdef PS_ITT_PC_TEST
#define NAS_ERABM_INFO_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_ERABM_NORM_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_ERABM_WARN_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_ERABM_ERR_LOG(String) \
                 vos_printf(" %s\r\n",String)
#define NAS_ERABM_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)
#define NAS_ERABM_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)
#else
#define NAS_ERABM_INFO_LOG(String) \
                 LPS_LOG(UE_MODULE_RABM_ID, VOS_NULL, LOG_LEVEL_INFO, String)
#define NAS_ERABM_NORM_LOG(String) \
                 LPS_LOG(UE_MODULE_RABM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define NAS_ERABM_WARN_LOG(String) \
                 LPS_LOG(UE_MODULE_RABM_ID, VOS_NULL, LOG_LEVEL_WARNING, String)
#define NAS_ERABM_ERR_LOG(String) \
                 LPS_LOG(UE_MODULE_RABM_ID, VOS_NULL, LOG_LEVEL_ERROR, String)
#define NAS_ERABM_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_RABM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define NAS_ERABM_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_RABM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)

#endif

#define NAS_ERABM_GET_MSG_LENGTH(pMsg)             ((pMsg)->ulLength)
#define NAS_ERABM_GET_RRC_MSG_ENTITY(pMsg)             ((VOS_VOID*)&((pMsg)->enMsgId))
#define NAS_ERABM_GET_MSG_ENTITY(pMsg)             ((VOS_VOID*)&((pMsg)->ulMsgId))


/*��װдSM��Ϣͷ�ĺ�*/
#define NAS_ERABM_WRITE_ESM_MSG_HEAD(pstMsg, ulEsmMsgID)\
                    (pstMsg)->ulMsgId = (ulEsmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_ESM;

/*��װдEMM��Ϣͷ�ĺ�*/
#define NAS_ERABM_WRITE_EMM_MSG_HEAD(pstMsg, ulEmmMsgID)\
                    (pstMsg)->ulMsgId   = (ulEmmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_MM;

/*��װдRRC��Ϣͷ�ĺ�*/
#define NAS_ERABM_WRITE_RRC_MSG_HEAD(pstMsg, ulRrcMsgID)\
                    (pstMsg)->enMsgId   = (ulRrcMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_ERRC;

/*��װдAPP��Ϣͷ�ĺ�*/
#define NAS_ERABM_WRITE_APP_MSG_HEAD(pstMsg, ulApptMsgID, usOrigId, usTermId, ulSn)\
                    (pstMsg)->ulMsgId = (ulApptMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_APP;\
                    (pstMsg)->usOriginalId = (usOrigId);\
                    (pstMsg)->usTerminalId = (usTermId);\
                    (pstMsg)->ulSN         = (ulSn);

/*��װAPPдRABM��Ϣͷ�ĺ�*/
#define NAS_ERABM_APP_WRITE_RABM_MSG_HEAD(pstMsg, ulAppMsgID, usOrigId, usTermId, ulSn)\
                    (pstMsg)->ulMsgId = (ulAppMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_APP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_RABM;\
                    (pstMsg)->usOriginalId = (usOrigId);\
                    (pstMsg)->usTerminalId = (usTermId);\
                    (pstMsg)->ulSN         = (ulSn);

/*��װдIP��Ϣͷ�ĺ�*/
#define NAS_ERABM_WRITE_IP_MSG_HEAD(pstMsg, ulIpMsgID)\
                    (pstMsg)->ulMsgId = (ulIpMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_IP;

#define NAS_ERABM_WRITE_TC_MSG_HEAD(pstMsg, ulIpMsgID)\
                    (pstMsg)->ulMsgId = (ulIpMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_TC;

/*��װдSM��Ϣͷ�ĺ�*/
#define NAS_ERABM_WRITE_CDS_MSG_HEAD(pstMsg, ulEsmMsgID)\
                    (pstMsg)->ulMsgId = (ulEsmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_RABM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = UEPS_PID_CDS;


/* �ڴ濽���궨�� */
#define NAS_ERABM_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulBufferLen) \
    {\
        if(VOS_NULL_PTR == PS_MEM_CPY_ALL_CHECK((pucDestBuffer),(pucSrcBuffer),(ulBufferLen)))\
        {\
            NAS_ERABM_ERR_LOG("NAS_ERABM_MEM_CPY  ERR!!");\
        }\
    }

#define NAS_ERABM_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
            PS_MEM_CMP ((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))
#define NAS_ERABM_MEM_SET(pucBuffer, ucData, ulBufferLen) \
    {\
        if(VOS_NULL_PTR == PS_MEM_SET_ALL_CHECK( (pucBuffer), (ucData), (ulBufferLen)))\
        {\
            NAS_ERABM_ERR_LOG("NAS_ERABM_MEM_SET  ERR!!");\
        }\
    }

#define NAS_ERABM_ALLOC_MSG(ulLen) \
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_RABM) , (ulLen))
/* ������Ϣ */
#define NAS_ERABM_SND_MSG(pMsg)\
    {\
        NAS_ERABM_PrintRabmSendMsg((const PS_MSG_HEADER_STRU * )pMsg,NAS_COMM_GET_ESM_PRINT_BUF());\
        if(VOS_OK != PS_SND_MSG_ALL_CHECK((PS_PID_RABM) , (pMsg)))\
        {\
            NAS_ERABM_ERR_LOG("NAS_ERABM_SND_MSG:Msg Snd Err!");\
        }\
    }

/*�ڴ��ͷ�*/
#define NAS_ERABM_MEM_FREE(pAddr)\
    {\
        if(VOS_OK != PS_MEM_FREE_ALL_CHECK((PS_PID_RABM), (pAddr)))\
        {\
            NAS_ERABM_ERR_LOG("NAS_ERABM_MEM_FREE  ERR!!");\
        }\
    }

/*�ڴ涯̬����*/
#define NAS_ERABM_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC_All_CHECK((PS_PID_RABM) , (ulSize))
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*����������״̬*/
enum NAS_ERABM_EPSB_STATE_ENUM
{
    NAS_ERABM_EPSB_INACTIVE    =       0,               /*ȥ����״̬*/
    NAS_ERABM_EPSB_ACTIVE,                              /*����״̬*/

    NAS_ERABM_EPSB_BUTT
};
typedef VOS_UINT8  NAS_ERABM_EPSB_STATE_ENUM_UINT8;

/*RB������״̬*/
enum NAS_ERABM_RB_STATE_ENUM
{
    NAS_ERABM_RB_CONNECTED      =      0,               /*RBΪ����̬*/
    NAS_ERABM_RB_DISCONNECTED,                          /*RBΪ������̬*/
    NAS_ERABM_RB_SUSPENDED,                             /*RBΪ��ͣ��̬*/

    NAS_ERABM_RB_STATE_BUTT
};
typedef VOS_UINT8  NAS_ERABM_RB_STATE_ENUM_UINT8;

/*****************************************************************************
    ö����    : NAS_ERABM_TIMER_STATE_ENUM
    ö��˵��  : ��ʱ����״̬:��������,ֹͣ
*****************************************************************************/
enum    NAS_ERABM_TIMER_STATE_ENUM
{
    NAS_ERABM_TIMER_STATE_RUNNING                = 0x00,
    NAS_ERABM_TIMER_STATE_STOPED,

    NAS_ERABM_TIMER_STATE_BUTT
};
typedef VOS_UINT32   NAS_ERABM_TIMER_STATE_ENUM_UINT32;

/*��ʶ��ʱ��������*/
enum NAS_ERABM_TIMER_NAME_ENUM
{
    NAS_ERABM_WAIT_EPSB_ACT_TIMER        =      0,     /*�ȴ�EPS���ؼ��ʱ��*/
    NAS_ERABM_WAIT_RB_REEST_TIMER,                     /*�ȴ�RB������ʱ��*/
    NAS_ERABM_WAIT_RB_RESUME_TIMER,                    /*�ȴ�RB�ָ���ʱ��*/
    NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER,               /*���ػ��涨ʱ��*/
    NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER,              /* RF�ָ�RB�ؽ���ʱ�� */

    NAS_NAS_ERABM_TIMER_NAME_BUTT
};
typedef VOS_UINT8  NAS_ERABM_TIMER_NAME_ENUM_UINT8;
enum NAS_ERABM_OM_LOG_MSG_ENUM
{
    NAS_ERABM_OM_LOG_TIMER_MIN                  = PS_MSG_ID_ERABM_TO_ERABM_OM_BASE,
    NAS_ERABM_OM_LOG_TIMER_MAX                  = PS_MSG_ID_ERABM_TO_ERABM_OM_BASE + NAS_NAS_ERABM_TIMER_NAME_BUTT,
    ID_NAS_ERABM_OM_LOG_IPF_FILTER_INFO         = NAS_ERABM_OM_LOG_TIMER_MAX + 0x1,
    ID_NAS_ERABM_OM_LOG_CDS_FILTER_INFO         = NAS_ERABM_OM_LOG_TIMER_MAX + 0x2
};
typedef VOS_UINT32 NAS_ERABM_OM_LOG_MSG_ENUM_UINT32;


/*�趨RABM�ȴ�EPS���ؼ���ı�ʶ*/
enum NAS_ERABM_WAIT_EPSB_ACT_ENUM
{
    NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG = 0,              /*RABMû�еȴ�EPSB������Ϣ*/
    NAS_ERABM_WAIT_EPSB_ACT_MSG,                      /*RABM�ȴ�EPSB������Ϣ*/

    NAS_ERABM_WAIT_EPSB_ACT_BUTT
};
typedef VOS_UINT8 NAS_ERABM_WAIT_EPSB_ACT_ENUM_UINT8;

/* Lģ״̬ */
enum NAS_ERABM_L_MODE_STATUS_ENUM
{
    NAS_ERABM_L_MODE_STATUS_NORMAL        = 0,                /*����̬*/
    NAS_ERABM_L_MODE_STATUS_SUSPENDED     = 1,                /*����̬*/

    NAS_ERABM_L_MODE_STATUS_BUTT
};
typedef VOS_UINT8 NAS_ERABM_L_MODE_STATUS_ENUM_UINT8;


/*�趨���ڼ�¼��SERVICE����״̬����RB�����󣬸�EMM����ֹͣSERVICE REQ�ı�ʶ*/
enum NAS_ERABM_SERVICE_STATE_ENUM
{
    NAS_ERABM_SERVICE_STATE_TERMIN = 0,              /*SERVICE���̽���*/
    NAS_ERABM_SERVICE_STATE_INIT,                    /*SERVICE��������*/

    NAS_ERABM_SERVICE_STATE_BUTT
};
typedef VOS_UINT32 NAS_ERABM_SERVICE_STATE_ENUM_UINT32;

/* RABM����ģʽ */
enum NAS_ERABM_MODE_TYPE_ENUM
{
    NAS_ERABM_MODE_TYPE_NORMAL           =      0,        /*����ģʽ*/
    NAS_ERABM_MODE_TYPE_LB               =      1,        /*����ģʽ*/

    NAS_ERABM_MODE_TYPE_BUTT
};
typedef VOS_UINT32 NAS_ERABM_MODE_TYPE_ENUM_UINT32;


/*****************************************************************************
    ö����    : NAS_TIMER_RUN_STA_ENUM
    ö��˵��  : ��ʱ����״̬:��������,ֹͣ
*****************************************************************************/
enum    NAS_ERABM_TIMER_RUN_STA_ENUM
{
    NAS_ERABM_TIMER_RUNNING                = 0x00,
    NAS_ERABM_TIMER_STOPED,
    NAS_ERABM_TIMER_INVALID,

    NAS_ERABM_TIMER_BUTT
};
typedef VOS_UINT32   NAS_ERABM_TIMER_RUN_STA_ENUM_UINT32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/

typedef struct
{
    HTIMER                               stHTimer;            /* vos�����Timer Id*/
    NAS_ERABM_TIMER_NAME_ENUM_UINT8       enName;              /* ��ʱ����*/
    VOS_UINT8                            ucExpireTimes;       /* Timer��ʱ����  */
    VOS_UINT8                            aucReserve1[2];      /* ���ֽڶ��룬����*/
}NAS_ERABM_START_TIMER_STRU; /*��ʱ��ʹ�õ����ݽṹ*/

typedef struct
{
    VOS_UINT32                          ulEpsbId;            /*��ӦEPS����ID*/
    VOS_UINT32                          ulRbId;              /*��ӦRBID*/
    NAS_ERABM_EPSB_STATE_ENUM_UINT8      enContextState;      /*EPSB�����ĵ�״̬*/
    NAS_ERABM_RB_STATE_ENUM_UINT8        enRbState;           /*RB������״̬*/
    VOS_UINT8                           aucReserve1[2];      /* ���ֽڶ��룬����*/
    VOS_UINT32                          ulTftPfNum;
    ESM_ERABM_TFT_PF_STRU                astTftPfInfo[ESM_ERABM_MAX_PF_NUM_IN_BEARER];
    APP_ESM_IP_ADDR_STRU                stPdnAddr;
    ESM_ERABM_BEARER_TYPE_ENUM_UINT32   enBearerCntxtType;  /* �����Ķ�Ӧ���ص����� */
    VOS_UINT32                          ulLinkedEpsbId;     /*��˳��ع�����EPS����ID*/
    VOS_UINT8                           ucQCI;              /* ���ص�QCI */
    VOS_UINT8                           ucRev[3];
}NAS_ERABM_INFO_STRU;    /*�������ݽṹ*/

typedef struct
{
    VOS_UINT32                           ulRbId;              /*��ӦRBID*/
    VOS_UINT32                           ulEpsbId;            /*��ӦEPS����ID*/
}NAS_ERABM_RB_SETUP_REQ_STRU;    /*�ȴ�EPSB������Ϣ���ݽṹ*/

typedef struct
{
    NAS_ERABM_WAIT_EPSB_ACT_ENUM_UINT8    enWaitEpsbActSign;   /*�趨һ���ȴ�EPS���ؼ���ı�ʶ*/
    NAS_ERABM_L_MODE_STATUS_ENUM_UINT8    enLModeStatus;      /* Lģ״̬ */
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    VOS_UINT8                            aucReserve1[2];      /* ���ֽڶ��룬����*/
    /*PC REPLAY MODIFY BY LEILI END*/
    VOS_UINT32                           ulRbNum;             /*RRC������RB�ĸ���*/
    VOS_UINT32                           ulOnlyActiveAndNoUlTftEpsbId; /*Ψһ������û������TFT�ĳ��غţ�ͬʱ�ñ���Ҳ
                                                                       ��־�Ƿ�ֻ��һ�����ؼ�����û������TFT*/
    NAS_ERABM_START_TIMER_STRU            astTimerInfo[NAS_NAS_ERABM_TIMER_NAME_BUTT];       /*��ʱ��ʹ����Ϣ*/
    NAS_ERABM_INFO_STRU                   astRabmInfo[NAS_ERABM_MAX_EPSB_NUM];
    NAS_ERABM_RB_SETUP_REQ_STRU           astRabmRbSetup[NAS_ERABM_MAX_EPSB_NUM];
    APP_ERABM_DATA_TRANS_INFO_STRU        stAppRabmDataInfo;
    NAS_ERABM_MODE_TYPE_ENUM_UINT32       enMode;                /* 0:����ģʽ��1:����ģʽ */
}NAS_ERABM_ENTITY_STRU;/*RABMʵ�����ݽṹ*/


/*****************************************************************************
 �ṹ��    : NAS_ERABM_IPV4_SEG_BUFF_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV4��Ƭ����Ϣ��¼����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIdentifier;
    VOS_UINT8                           aucSrcIpV4Addr[NAS_ERABM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucDesIpV4Addr[NAS_ERABM_IPV4_ADDR_LEN];
    VOS_UINT8                           ucBearerId;
    VOS_UINT8                           aucReserved[3];
}NAS_ERABM_IPV4_SEG_BUFF_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ERABM_IPV4_SEGMENT_BUFF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV4��Ƭ����Ϣ����ṹ
*****************************************************************************/

typedef struct
{
    VOS_UINT32                           ulItemNum;
    NAS_ERABM_IPV4_SEG_BUFF_ITEM_STRU    astErabmSegBuff[NAS_ERABM_MAX_SEG_BUFF_ITEM_NUM];
}NAS_ERABM_IPV4_SEGMENT_BUFF_STRU;



typedef struct
{
    MSG_HEADER_STRU                          stMsgHeader;     /*_H2ASN_Skip*/
    NAS_ERABM_TIMER_RUN_STA_ENUM_UINT32      enTimerStatus;   /* ��ʱ��״̬*/

    NAS_ERABM_TIMER_NAME_ENUM_UINT8          enTimerId;       /* ��ʱ��ID*/
    VOS_UINT8                                usRsv[3];
    VOS_UINT32                               ulTimerRemainLen;/* ��ʱ����ʱ�� */
}NAS_ERABM_TIMER_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
/*PC REPLAY MODIFY BY LEILI BEGIN*/
/*RABMʵ����Ϣ*/
extern NAS_ERABM_ENTITY_STRU                        g_stNasERabmEntity;
/*PC REPLAY MODIFY BY LEILI END*/
extern NAS_ERABM_ENTITY_STRU                       *pg_stNasERabmEntity;
#define NAS_ERABM_Entity()                         (pg_stNasERabmEntity)

/*�õ���ʱ������Ϣ*/
#define NAS_ERABM_GetRbTimer(ucTimeIndex)          (((ucTimeIndex) < NAS_NAS_ERABM_TIMER_NAME_BUTT)?(&(NAS_ERABM_Entity()->astTimerInfo[ucTimeIndex])): VOS_NULL_PTR)

/*��RB����������Ϣ������RB������ʱ��*/
#define NAS_ERABM_SetRbSetupRbIdInfo(ulRbNum,ulRId)      ((NAS_ERABM_Entity())->astRabmRbSetup[ulRbNum].ulRbId = (ulRId))
#define NAS_ERABM_SetRbSetupEpsbIdInfo(ulRbNum,ulEpsId)    ((NAS_ERABM_Entity())->astRabmRbSetup[ulRbNum].ulEpsbId = (ulEpsId))

/*�õ�RB������ʱ����Ϣ*/
#define NAS_ERABM_GetRbSetupRbIdInfo(ulRbNum)      ((NAS_ERABM_Entity())->astRabmRbSetup[ulRbNum].ulRbId)
#define NAS_ERABM_GetRbSetupEpsbIdInfo(ulRbNum)    ((NAS_ERABM_Entity())->astRabmRbSetup[ulRbNum].ulEpsbId)
#define NAS_ERABM_GetRbNumInfo()                   ((NAS_ERABM_Entity()->ulRbNum))

/*��¼��������RB��Ŀ*/
#define NAS_ERABM_SetRbNumInfo(ulRbSetupReqNum)                   ((NAS_ERABM_Entity()->ulRbNum) = (ulRbSetupReqNum))

/*Ψһ������û��TFT�ĳ��غ�*/
#define NAS_ERABM_GetOnlyActiveAndNoUlTftEpsbId()      ((NAS_ERABM_Entity()->ulOnlyActiveAndNoUlTftEpsbId))
#define NAS_ERABM_SetOnlyActiveAndNoUlTftEpsbId(ulEpsbId)      ((NAS_ERABM_Entity()->ulOnlyActiveAndNoUlTftEpsbId) = (ulEpsbId) )

#define NAS_ERABM_SetEpsbBearerType(ulEpsbIdCnt, enBearerCntxtType1)      (((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].enBearerCntxtType) = (enBearerCntxtType1))
#define NAS_ERABM_SetEpsbLinkedEpsbId(ulEpsbIdCnt, ulLinkedEpsbId1)       (((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulLinkedEpsbId) = (ulLinkedEpsbId1))
#define NAS_ERABM_SetEpsbQCI(ulEpsbIdCnt, ucNwQCI)       (((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ucQCI) = (ucNwQCI))


/*��¼EPS���ؼ������Ϣ*/
#define NAS_ERABM_SetEpsbTftPfNum(ulEpsbIdCnt,ulEpsbTftPfNum)   ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulTftPfNum = (ulEpsbTftPfNum))
#define NAS_ERABM_SetEpsbIdInfo(ulEpsbIdCnt,ulEpsId)       ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulEpsbId = (ulEpsId))
#define NAS_ERABM_SetEpsbRbIdInfo(ulEpsbIdCnt,ulRId)     ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulRbId = (ulRId))
#define NAS_ERABM_SetEpsbStateInfo(ulEpsbIdCnt,enCntxtState)    ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].enContextState = (enCntxtState))
#define NAS_ERABM_SetRbStateInfo(ulEpsbIdCnt,enRState)      ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].enRbState = (enRState))
#define NAS_ERABM_GetEpsbBearerType(ulEpsbIdCnt)         ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].enBearerCntxtType)
#define NAS_ERABM_GetEpsbLinkedEpsbId(ulEpsbIdCnt)       ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulLinkedEpsbId)
#define NAS_ERABM_GetEpsbQCI(ulEpsbIdCnt)            ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ucQCI)

/*�õ�EPS���ؼ������Ϣ*/
#define NAS_ERABM_GetEpsbTftPfNum(ulEpsbIdCnt)   ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulTftPfNum)
#define NAS_ERABM_GetEpsbIdInfo(ulEpsbIdCnt)       ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulEpsbId)
#define NAS_ERABM_GetEpsbRbIdInfo(ulEpsbIdCnt)     ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].ulRbId)
#define NAS_ERABM_GetEpsbStateInfo(ulEpsbIdCnt)    ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].enContextState)
#define NAS_ERABM_GetRbStateInfo(ulEpsbIdCnt)      ((NAS_ERABM_Entity())->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].enRbState)
#define NAS_ERABM_GetEpsbTftAddr(ulEpsbIdCnt,ulTftPfCnt)   (&((NAS_ERABM_Entity())->astRabmInfo[(ulEpsbIdCnt)-NAS_ERABM_MIN_EPSB_ID].astTftPfInfo[(ulTftPfCnt)]))
#define NAS_ERABM_GetEpsbPdnAddr(ulEpsbIdCnt)      (&(NAS_ERABM_Entity()->astRabmInfo[ulEpsbIdCnt-NAS_ERABM_MIN_EPSB_ID].stPdnAddr))


/*�ȴ�EPS���ؼ����ʶ����ز���*/
#define NAS_ERABM_GetWaitEpsbActSign()             ((NAS_ERABM_Entity())->enWaitEpsbActSign)
#define NAS_ERABM_SetWaitEpsBActSign(ucWaitEpsbActMsgStatus)\
                                                  ((NAS_ERABM_Entity())->enWaitEpsbActSign = (ucWaitEpsbActMsgStatus))


/* RABMģʽ����ز��� */
#define NAS_ERABM_GetMode()               ((NAS_ERABM_Entity())->enMode)
#define NAS_ERABM_SetMode(enModeType)\
                                                  ((NAS_ERABM_Entity())->enMode = (enModeType))

/*����RABM��������Ϣ*/
#define   NAS_ERABM_StAppDataBitIpv4(bOpIpv4)\
                   ((NAS_ERABM_Entity()->stAppRabmDataInfo).bitOpIpv4 = bOpIpv4)

#define   NAS_ERABM_StAppDataBitIpv6(bOpIpv6)\
                   ((NAS_ERABM_Entity()->stAppRabmDataInfo).bitOpIpv6 = bOpIpv6)

#define   NAS_ERABM_SetAppDataRmtPortIpv4(RmtPortIpv4)\
     ((NAS_ERABM_Entity()->stAppRabmDataInfo).usIpv4SingleRmtPort = RmtPortIpv4)

#define   NAS_ERABM_SetAppDataRmtPortIpv6(RmtPortIpv6)\
     ((NAS_ERABM_Entity()->stAppRabmDataInfo).usIpv6SingleRmtPort = RmtPortIpv6)

#define   NAS_ERABM_SetAppDataOperateType(SetOpType)\
               ((NAS_ERABM_Entity()->stAppRabmDataInfo).enSetOpType = SetOpType)


/*��ȡRABM��������Ϣ*/
#define   NAS_ERABM_GetAppDataInfoAddr()         (&(NAS_ERABM_Entity()->stAppRabmDataInfo))
#define   NAS_ERABM_GetAppDataBitIpv4()          ((NAS_ERABM_Entity()->stAppRabmDataInfo).bitOpIpv4)
#define   NAS_ERABM_GetAppDataBitIpv6()          ((NAS_ERABM_Entity()->stAppRabmDataInfo).bitOpIpv6)
#define   NAS_ERABM_GetAppDataRmtPortIpv4()      ((NAS_ERABM_Entity()->stAppRabmDataInfo).usIpv4SingleRmtPort)
#define   NAS_ERABM_GetAppDataRmtPortIpv6()      ((NAS_ERABM_Entity()->stAppRabmDataInfo).usIpv6SingleRmtPort)
#define   NAS_ERABM_GetAppDataOperateType()      ((NAS_ERABM_Entity()->stAppRabmDataInfo).enSetOpType)
#define   NAS_ERABM_GetAppDataRemoteIpv4Addr()   ((NAS_ERABM_Entity()->stAppRabmDataInfo).aucRmtIpv4Address)
#define   NAS_ERABM_GetAppDataRemoteIpv6Addr()   ((NAS_ERABM_Entity()->stAppRabmDataInfo).aucRmtIpv6Address)

/*extern NAS_ERABM_SEGMENT_DATA_INFO_ARRAY_STRU    g_stERabmSegDataInfo;
#define NAS_ERABM_GetSegDataInfoArrayAddr()      (&g_stERabmSegDataInfo)
#define NAS_ERABM_GetSegDataInfoAddr(ulIndex)    (&((NAS_ERABM_GetSegDataInfoArrayAddr())->astRabmSegDataInfo[ulIndex]))
#define NAS_ERABM_GetSegDataInfoNum()            ((NAS_ERABM_GetSegDataInfoArrayAddr())->ulSegDataInfoNum)
#define NAS_ERABM_AddSelfSegDataInfoNum()        ((NAS_ERABM_GetSegDataInfoArrayAddr())->ulSegDataInfoNum++)*/

extern NAS_ERABM_IPV4_SEGMENT_BUFF_STRU          g_stErabmIpv4SegBuff;
#define NAS_ERABM_GetIpv4SegBuffAddr()           (&g_stErabmIpv4SegBuff)
#define NAS_ERABM_GetIpv4SegBuffItemAddr(ulIndex) (&((NAS_ERABM_GetIpv4SegBuffAddr())->astErabmSegBuff[ulIndex]))
#define NAS_ERABM_GetIpv4SegBuffItemNum()        ((NAS_ERABM_GetIpv4SegBuffAddr())->ulItemNum)
#define NAS_ERABM_AddSelfIpv4SegBuffItemNum()    ((NAS_ERABM_GetIpv4SegBuffAddr())->ulItemNum++)


/*��������������־*/
extern EMM_ERABM_UP_DATA_PENDING_ENUM_UINT32    g_enERabmUlDataPending;

#define   NAS_ERABM_GetUpDataPending()               (g_enERabmUlDataPending)
#define   NAS_ERABM_SetUpDataPending(UpDataPending)  ((g_enERabmUlDataPending) = (UpDataPending))

#define NAS_ERABM_GetLModeStatus()\
                  ((NAS_ERABM_Entity())->enLModeStatus)

#define NAS_ERABM_SetLModeStatus(ucLModeStatus)\
            {\
                 NAS_ERABM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
                 NAS_ERABM_NORM_LOG("RABM L Mode Status change----");\
                 NAS_ERABM_PRINT_LMODESTA(NAS_ERABM_GetLModeStatus());\
                 NAS_ERABM_NORM_LOG("==>>");\
                 (NAS_ERABM_Entity())->enLModeStatus = (ucLModeStatus);\
                 NAS_ERABM_PRINT_LMODESTA(ucLModeStatus);\
                 NAS_ERABM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
            }
/*PC REPLAY MODIFY BY LEILI BEGIN*/
extern NAS_ERABM_SERVICE_STATE_ENUM_UINT32 g_enERabmSrState;
/*PC REPLAY MODIFY BY LEILI END*/
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_VOID NAS_ERABM_SndOmErabmTimerStatus
(
    NAS_ERABM_TIMER_RUN_STA_ENUM_UINT32 enTimerStatus,
    NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerId,
    VOS_UINT32 ulTimerRemainLen
);
/*PC REPLAY MODIFY BY LEILI BEGIN*/
extern VOS_VOID NAS_LMM_LogIsDataPending
(
    VOS_UINT32  ulRslt
);
/*PC REPLAY MODIFY BY LEILI END*/
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

#endif /* end of NasERabmPublic.h */

