

#ifndef _GMM_CAS_DEF_H_
#define _GMM_CAS_DEF_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#pragma pack(4)                         /* 1�ֽڶ��룬���ݽṹ���屣֤4�ֽڶ��� */
                                        /* ����include�󣬲�Ӱ������ͷ�ļ���pack���� */
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define     GMM_TIMER_NOT_RESUME            0
#define     GMM_TIMER_RESUME                1

/*----------2.3 GMM��Ϣ����궨�� ------------*/
#define     GMM_MATRIX_STATE_MAX            25              /* GMM��Ϣ����״̬�������Ŀ */
#define     GMM_MATRIX_EVENT_MAX            73              /* GMM��Ϣ�����¼��������Ŀ */
#define     GMM_STATE_TAB_RESERVED          255             /* GMM�ڲ�״̬ӳ������� */

#define     GMM_NAS_MSG_HEADER_MIN          2               /* GMM��Ϣͷ��̳��� */
#define     GMM_NAS_MSG_DATA_MAX            2048            /* GMM��Ϣ���ݵ���󳤶� */

/*----------2.4 GMM��Ϣ�¼����ƺ궨�� ------------*/
#define     GMM_EVENT_ID_TIMER_T3302                        1
#define     GMM_EVENT_ID_TIMER_T3310                        2
#define     GMM_EVENT_ID_TIMER_T3311                        3
#define     GMM_EVENT_ID_TIMER_T3312                        4
#define     GMM_EVENT_ID_TIMER_T3316                        5
#define     GMM_EVENT_ID_TIMER_T3317                        6
#define     GMM_EVENT_ID_TIMER_T3318                        7
#define     GMM_EVENT_ID_TIMER_T3320                        8
#define     GMM_EVENT_ID_TIMER_T3321                        9
#define     GMM_EVENT_ID_TIMER_T3330                        10
#define     GMM_EVENT_ID_TIMER_5S                           11
#define     GMM_EVENT_ID_TIMER_PROT                         12
#define     GMM_EVENT_ID_TIMER_PROT_SIGNAL                  13
#define     GMM_EVENT_ID_TIMER_BUF_QUEUE                    14
#define     GMM_EVENT_ID_TIMER_T3314                        15
#define     GMM_EVENT_ID_PS_USIM_AUTN_CNF                   16
#define     GMM_EVENT_ID_RRMM_PAGING_IND                    17
#define     GMM_EVENT_ID_RRMM_EST_CNF                       18
#define     GMM_EVENT_ID_RRMM_DATA_IND                      19
#define     GMM_EVENT_ID_RRMM_REL_IND                       20
#define     GMM_EVENT_ID_RRMM_SECUR_IND                     21
#define     GMM_EVENT_ID_RRMM_AC_CH_IND                     22
#define     GMM_EVENT_ID_GMMRABM_REEST_REQ                  23
#define     GMM_EVENT_ID_MMCGMM_SYS_INFO_IND                24
#define     GMM_EVENT_ID_MMCGMM_COVER_LOST_IND              25
#define     GMM_EVENT_ID_MMCGMM_POWER_OFF_REQ               26
#define     GMM_EVENT_ID_MMCGMM_LU_RESULT_IND               27          /* GMM�ݲ�ʹ�� */
#define     GMM_EVENT_ID_MMCGMM_CM_SERVICE_IND              28
#define     GMM_EVENT_ID_MMCGMM_CM_SRV_REJ_IND              29
#define     GMM_EVENT_ID_MMCGMM_PLMN_SEARCH_INIT            30
#define     GMM_EVENT_ID_MMCGMM_START_REQ                   31
#define     GMM_EVENT_ID_MMCGMM_PLMN_USER_SEL_REQ           32
#define     GMM_EVENT_ID_MMCGMM_DETACH_REQ                  33
#define     GMM_EVENT_ID_MMCGMM_AUTN_FAIL_IND               34
#define     GMM_EVENT_ID_MMCGMM_REGISTER_INIT               35
#define     GMM_EVENT_ID_MMCGMM_MODE_CH_REQ                 36
#define     GMM_EVENT_ID_MMCGMM_ATTACH_REQ                  37
#define     GMM_EVENT_ID_GMMSM_ESTABLISH_REQ                38
#define     GMM_EVENT_ID_GMMSM_DATA_REQ                     39
#define     GMM_EVENT_ID_GMMSM_PDP_STATUS_IND               40
#define     GMM_EVENT_ID_PMMSMS_EST_REQ                     41
#define     GMM_EVENT_ID_PMMSMS_UNITDATA_REQ                42
#define     GMM_EVENT_ID_TCGMM_DATA_REQ                     43
#define     GMM_EVENT_ID_TCGMM_TEST_REQ                     44
#define     GMM_EVENT_ID_LL_GMM_STATUS_IND                  45
#define     GMM_EVENT_ID_LL_UNITDATA_IND                    46
#define     GMM_EVENT_ID_GMMRABM_RAU_RSP                    47
#define     GMM_EVENT_ID_GRRMM_PAGING_IND                   48
#define     GMM_EVENT_ID_MMCGMM_GAS_SYS_IND                 49
#define     GMM_EVENT_ID_MMCGMM_SUSPEND_IND                 50
#define     GMM_EVENT_ID_MMCGMM_RESUME_IND                  51
#define     GMM_EVENT_ID_MMCGMM_SUSPEND_CNF                 52

#define     GMM_EVENT_ID_MSG_ATTACH_ACCEPT                  53
#define     GMM_EVENT_ID_MSG_ATTACH_REJECT                  54
#define     GMM_EVENT_ID_MSG_DETACH_REQUEST                 55
#define     GMM_EVENT_ID_MSG_DETACH_ACCEPT                  56
#define     GMM_EVENT_ID_MSG_RAU_ACCEPT                     57
#define     GMM_EVENT_ID_MSG_RAU_REJECT                     58
#define     GMM_EVENT_ID_MSG_SERVICE_ACCEPT                 59
#define     GMM_EVENT_ID_MSG_SERVICE_REJECT                 60
#define     GMM_EVENT_ID_MSG_PTMSI_REALLOC                  61
#define     GMM_EVENT_ID_MSG_AUTH_AND_CIPH_REQ              62
#define     GMM_EVENT_ID_MSG_AUTH_AND_CIPH_REJ              63
#define     GMM_EVENT_ID_MSG_IDENTITY_REQUEST               64
#define     GMM_EVENT_ID_MSG_GMM_STATUS                     65
#define     GMM_EVENT_ID_MSG_GMM_INFORMATION                66
#define     GMM_EVENT_ID_MSG_NONEXIST                       67          /* δ�������Ϣ�¼� */
#define     GMM_EVENT_ID_SM_DATA_IND                        68
#define     GMM_EVENT_ID_SMS_DATA_IND                       69
#define     GMM_EVENT_ID_TC_DATA_IND                        70
#define     GMM_EVENT_ID_NONE_DATA_IND                      71          /* δ����ģ�鷢�͵�data ind�¼� */
#define     GMM_EVENT_ID_GRRMM_GPRS_SUSPENED_IND            72
#define     GMM_EVENT_ID_GRRMM_GPRS_RESUME_IND              73

#define     GMM_EVENT_ID_AGENT_PMM_INQUIRE                  128         /* OM��ϢAGENT_PMM_INQUIRE*/
#define     GMM_EVENT_ID_WUEPS_RESET_REQ                    129         /* ADMIN��ϢWUEPS_RESET_REQ*/

#define     GMM_EVENT_ID_INVALID                            255

/*----------2.5 GMM�ڲ������������Ͷ��� ------------*/
/* GMM��Ϣ����ĵ�Ԫ������ָ�� */
typedef     VOS_UINT32    (*GMM_CELL_FUN_TYPE)(VOS_VOID *);

/* RAU rejectԭ��ֵ���������� */
typedef     VOS_UINT32      GMM_RAU_REJ_RESULT_TYPE;
#define     GMM_RAU_REJ_NULL_FLG                            0x00        /* �����������־ */
#define     GMM_RAU_REJ_ABNORMAL_FLG                        0x01        /* �쳣�����־ */
#define     GMM_RAU_REJ_ATTACH_FLG                          0x02        /* ����ATTACH��־ */


/*----------2.6 GMM��Ϣ����SIM�ļ��ź�ֵ ------------*/
/* BEGIN: Added by liurui id:40632, 2006/6/29   PN:A32D04514 */
#define     GMM_USIM_FILE_PS_KEY_GPRS                       0x4F52      /* 2G access in 3G USIM */
#define     GMM_USIM_FILE_KC_KEY_GPRS                       0x6F52      /* GPRS Kc Key in 2G SIM */
#define     GMM_USIM_FILE_LOC_INFO_GPRS                     0x6F53      /* GPRS location info in 2G SIM */
/* END:   Added by liurui id:40632, 2006/6/29   PN:A32D04514 */

/* LLC data req��Ϣ������󳤶� */
#define     GMM_LLC_MSG_PDULEN_MAX                          4096
/* BEGIN: Added by liurui id:40632, 2006/6/14   PN:A32D04282 */
/* DRX������Split pg cycle code��Ӧ����󳤶� */
#define     GMM_DRX_CYCLE_CODE_TAB_MAX                      34
#define     GMM_DRX_CYCLE_CODE_NUMBER                       (GMM_DRX_CYCLE_CODE_TAB_MAX+64)
/* END:   Added by liurui id:40632, 2006/6/14   PN:A32D04282 */

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
typedef enum
{
    GMM_NULL_STAT = 0,          /* s0 : GMM-NULL */
    GMM_DER_NRM_SRV_STAT,       /* s1 : GMM-DEREGISTERED.NORMAL-SERVICE */
    GMM_DER_LMT_SRV_STAT,       /* s2 : GMM-DEREGISTERED.LIMITED-SERVICE */
    GMM_DER_ACH_NED_STAT,       /* s3 : GMM-DEREGISTERED.ATTACH-NEEDED */
    GMM_DER_ATMPT_ACH_STAT,     /* s4 : GMM-DEREGISTERED.ATTEMPTING-TO-ATTACH */
    GMM_DER_NO_IMSI_STAT,       /* s5 : GMM-DEREGISTERED.NO-IMSI */
    GMM_DER_NO_CELL_STAT,       /* s6 : GMM-DEREGISTERED.NO-CELL-AVAILABLE */
    GMM_DER_PLMN_SRCH_STAT,     /* s7 : GMM-DEREGISTERED.PLMN-SEARCH */
    GMM_REG_INIT_STAT,          /* s8 : GMM-REGISTERED-INITIATED */
    GMM_REG_NRM_SRV_STAT,       /* s9 : GMM-REGISTERED.NORMAL-SERVICE */
    GMM_REG_UPDT_NED_STAT,      /* s10: GMM-REGISTERED.UPDATE-NEEDED */
    GMM_REG_ATMPT_UPDT_STAT,    /* s11: GMM-REGISTERED.ATTEMPTING-TO-UPDATE */
    GMM_REG_NO_CELL_STAT,       /* s12: GMM-REGISTERED.NO-CELL-AVAILABLE */
    GMM_REG_LMT_SRV_STAT,       /* s13: GMM-REGISTERED.LIMITED-SERVICE */
    GMM_REG_ATMPT_UPDT_MM_STAT, /* s14: GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM */
    GMM_REG_PLMN_SRCH_STAT,     /* s15: GMM-REGISTERED.PLMN-SEARCH */
    GMM_REG_IMSI_DCH_INIT_STAT, /* s16: GMM-REGISTERED.IMSI-DETACH-INITIATED */
    GMM_REG_WAIT_RAU_STAT,      /* s17: GMM-REGISTERED-WAIT-FOR-RAU */
    GMM_DER_INIT_STAT,          /* s18: GMM-DEREGISTERED-INITIATED */
    GMM_RAU_INIT_STAT,          /* s19: GMM-ROUTING-AREA-UPDATING-INITIATED */
    GMM_SRV_REQ_INIT_STAT,      /* s20: GMM-SERVICE-REQUEST-INITIATED (UMTS only) */
    GMM_TC_ACT_STAT,            /* s21: GMM-TC-ACTIVE */
    GMM_CAS_SUSPN_STAT,         /* s22: GMM-CAS-SUSPEND */
    GMM_REG_SUSPN_STAT,         /* s23: GMM-REGISTERED.SUSPENDED (GSM only) */
    GMM_DER_SUSPN_STAT          /* s24: GMM-DEREGISTERED-SUSPENDED (GSM only) */
}GMM_STATE_ID_ENUM;

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------7.1 GMMȫ�ֹ������ݽṹ -------------*/
/*=======================================================*/

/*----------7.1.1 GMM_CAS_CTRL_STRU ------------*/
/* GMM CAS���̲�����ʱ��¼�ṹ */
typedef struct
{
    VOS_UINT8       ucRaiChgFlg;
    VOS_UINT8       ucLaiChgFlg;
    VOS_UINT8       ucDrxLengthChgFlg;
    VOS_UINT8       ucGsmCellChgFlg;        /* GSM cell ID���±�־ */

    VOS_UINT8       ucSuspendCause;         /* ����ԭ�� */
    VOS_UINT8       ucSuspendOrigen;        /* ��Ϣ���𷽣�RRMM_ORIGEN_GSM:GSM��RRMM_ORIGEN_WCDMA:WCDMA*/
    VOS_UINT8       ucCsResumeResult;       /* CS���л���� */
    VOS_UINT8       ucPsResumeResult;       /* PS���л���� */

    VOS_UINT8       ucResumeOrigen;         /* ��Ϣ���𷽣�RRMM_ORIGEN_GSM:GSM��RRMM_ORIGEN_WCDMA:WCDMA */
    VOS_UINT8       aucReserve[3];
}GMM_CAS_PARAM_TEMP_ST;

/*----------7.1.2 GMM_CAS_CTRL_STRU ------------*/
/*
 GMM���ý����������ݽṹ
 1.GMM����״̬�¹��ñ�־����¼
 2.GMM����״̬�¹����������
*/
/* V200R001�汾���� */

/*===== �����궨�� =====*/
#define     GMM_AUTN_KC_LENGTH              16          /* GSM��Ȩ��ԿKc�ĳ��� */
#define     GMM_MAX_SIZE_SRES               4           /* SRES���� */

/* GPRS�����GMM״̬ */
typedef VOS_UINT8   GMM_GPRS_SRV_STATE;
#define GMM_AGB_GPRS_IDLE                   0x00        /* A/Gbģʽ��GPRS����̬*/
#define GMM_AGB_GPRS_STANDBY                0x01        /* A/Gbģʽ��GPRS�ȴ�̬*/
#define GMM_AGB_GPRS_READY                  0x02        /* A/Gbģʽ��GPRS����̬*/
#define GMM_IU_PMM_DETACHED                 GMM_AGB_GPRS_IDLE        /* Iuģʽ��GPRS��Ч̬*/
#define GMM_IU_PMM_IDLE                     GMM_AGB_GPRS_STANDBY     /* Iuģʽ��GPRS���еȴ�̬*/
#define GMM_IU_PMM_CONNECTED                GMM_AGB_GPRS_READY       /* Iuģʽ��GPRS����̬*/

/* ulGmmCasState����ֵ */
typedef VOS_UINT8  GMM_CAS_STATE;
#define     GMM_CAS_SUSPEND                 1           /* GMM CAS����Ϣ����ʽ */
/*
    #define     GMM_CAS_WCDMA_DETACHED          2
    #define     GMM_CAS_WCDMA_CONNECTED         3
    #define     GMM_CAS_WCDMA_IDLE              4
    #define     GMM_CAS_GSM_IDLE                5
    #define     GMM_CAS_GSM_READY               6
    #define     GMM_CAS_GSM_STANDBY             7
*/
#define     GMM_CAS_WCDMA_AS                8           /* GMM CAS�е�WCDMA���뷽ʽ */
#define     GMM_CAS_GSM_AS                  9           /* GMM CAS�е�GSM���뷽ʽ */

/* TLLI����ֵ���� */
typedef VOS_UINT8   GMM_TLLI_TYPE;
#define GMM_RANDOM_TLLI                     0
#define GMM_LOCAL_TLLI                      1
#define GMM_FOREIGN_TLLI                    2
#define GMM_AUXILIARY_TLLI                  3
#define GMM_OTHERS_TLLI                     4
#define GMM_INVALID_TLLI                    5

#define GMM_NOT_SUSPEND_LLC                 0
#define GMM_SUSPEND_LLC_FOR_CS              1
#define GMM_SUSPEND_LLC_FOR_RAU             2
#define GMM_SUSPEND_LLC_FOR_CELL_RESEL      4
#define GMM_SUSPEND_LLC_FOR_OUT_OF_SERVICE  8
#define GMM_SUSPEND_LLC_FOR_INTER_SYS       16
#define GMM_SUSPEND_LLC_FOR_DETACH          32

#define GMM_ABORT_LLC_TRUE                  0
#define GMM_ABORT_LLC_FALSE                 1

enum GMM_RA_PRIO_LEV_ENUM
{
    GMM_RA_PRIO_LEV_1                   = 1,
    GMM_RA_PRIO_LEV_2,
    GMM_RA_PRIO_LEV_3,
    GMM_RA_PRIO_LEV_4,
    GMM_RA_PRIO_LEV_BUTT
};
typedef VOS_UINT8 GMM_RA_PRIO_LEV_ENUM_U8;

/*===== �ṹ�嶨�� =====*/
typedef struct
{
    VOS_UINT32              ulReadyTimerValue;              /* READY TIMERЭ��ֵ,���뵥λ�� */
    VOS_UINT32              ulTLLI;                         /* ϵͳ��ǰTLLIֵ */
    VOS_UINT32              ulOldTLLI;                      /* ׼��ɾ�������õ�TLLIֵ */

    GMM_CAS_STATE           ucGmmCasState;                  /* GMM CAS��ǰ����״̬ */
    GMM_CAS_STATE           ucGmmCasPreState;               /* GMM CASǰ������״̬ */
    GMM_GPRS_SRV_STATE      GmmSrvState;                    /* ��ǰGMM GPRS����״̬ */
    VOS_UINT8               ucTlliAssignFlg;                /* GSM����ģʽTLLIָ����ɱ�־ */

    GMM_CAS_PARAM_TEMP_ST   TempMsgPara;                    /* ��Ϣ������ʱ��¼ */

    VOS_UINT8               ucBufMsgResFlg;                 /* ������Ϣ�ָ������־,1:����;0:������ */
    VOS_UINT8               ucReadyTimerNgtFlg;             /* READY TIMERЭ�������־ */
    VOS_UINT8               ucRabmResumeFlg;                /* RABM��2G�л���3G�ָ���ɱ�־ */
    VOS_UINT8               ucRauCmpFlg;                    /* RAU������ɺ��Ƿ���Ҫ�ȴ�RABM��WRR�ظ����ٷ���RAU cmp��Ϣ
                                                                   RABM: ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP
                                                                   WRR : RRMM_INTER_RAT_HANDOVER_INFO_CNF     */

    VOS_UINT8               ucWaitRabmRauRspFlg;            /* �Ƿ���Ҫ�ȴ�RABM: ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP ��Ϣ */
    VOS_UINT8               ucRabmRauRspRcvdFlg;            /* �Ƿ����յ�RABM: ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP ��Ϣ */
    GMM_RA_PRIO_LEV_ENUM_U8 enRaPrioLevFosSms;              /* ��ǰRadio priority for SMSֵ */
    GMM_TLLI_TYPE           ucflgTLLI;                      /* ��ǰTLLIֵ���ͱ�־ */

    VOS_UINT8               ucGprsCipherAlg;                /* GPRS�����㷨 */
    VOS_UINT8               ucGprsCipher;                   /* VOS_TRUE:��������,VOS_FALSE:���ܲ�������
                                                               ָʾ��GSMģʽ���Ƿ�ʼ���м��ܣ����յ�LL��LL_NAS_UNITDATA_IND��Ϣʱ��
                                                               ���ucCiphIndָʾ���ܣ����ü���������־ */
    VOS_UINT8               ucGprsCipherAssign;             /* GPRS�����Ƿ�ָ���־.VOS_TRUE:�Ѿ�ָ��;VOS_FALSE:û��ָ��*/
    VOS_UINT8               ucCellNotifyFlg;                /* 2G������cell notification��Ч��־ */

    VOS_UINT8               ucFtsFlg;                       /* 2G������force to standby��Ч��־ */
    VOS_UINT8               ucCellUpdateFlg;                /* 2G������cell updateִ�б�־ */
    VOS_UINT8               ucSysRauFlg;                    /* ϵͳ��ϢҪ��RAUִ�б�־ */
    VOS_UINT8               ucLastDataSender;               /* ǰ��������������ݴ��䷢�ͷ����������ģʽ */

    VOS_UINT8               ucSuspendLlcCause;              /* ����LLCԭ��                                */
    VOS_UINT8               ucCellReselFlg;                 /* ָʾ��ǰ�Ƿ��ڽ���С����ѡVOS_TRUE:����ѡ������;VOS_FALSE:������ѡ����       */
    VOS_UINT8               ucReadyTimerChgFlg;
    VOS_UINT8               aucReserve1[1];

    VOS_UINT16              usMui;
    VOS_UINT16              usPowerOffDetachPsMui;
}GMM_CAS_CTRL_STRU, *PGMM_CAS_CTRL_STRU;

/*----------7.1.3 GMM_LLC_MSG ------------*/
/* GMM��LLC�Ľӿ���Ϣ���ݽṹ */
/* V200R001�汾���� */

/*===== �ṹ�嶨�� =====*/
typedef struct
{
    VOS_MSG_HEADER                      /* VOS��Ϣͷ*/
    VOS_UINT16  usMsgType;              /*��Ϣ����*/
    VOS_UINT16  usTransId;              /*�ӽ��̣�������SAPI*/
    VOS_UINT32  aulMsgData[1];          /*��Ϣ��ṹͷ*/
}GMM_LLC_MSG;

/*=======================================================*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------7.2 ������Ϣ�������     ---------------*/
/*=======================================================*/

/*----------7.2.1 GMM_CAS_CTRL_STRU ------------*/
/*
 GMM���ý����������ݽṹ
 1.GMM����״̬�¹��ñ�־����¼
 2.GMM����״̬�¹����������
*/
/* V200R001�汾���� */

/*===== �����궨�� =====*/
#define         GMM_CAS_MSG_NUMBER_MAX              10         /* ������Ϣ��Ŀ���ֵ */
/* ������Ϣ�����־ */
#define         GMM_MSG_BUFFER_FLAG_IDLE            0           /* ������ϢΪ�� */
#define         GMM_MSG_BUFFER_FLAG_USED            1           /* ������Ϣ���� */

/*===== �ṹ�嶨�� =====*/
typedef struct
{
    VOS_VOID           *apBufMsg[GMM_CAS_MSG_NUMBER_MAX];       /* ������Ϣ���� */

    VOS_UINT8           ucBufMsgTotal;                          /* �����������Ϣ���� */
    VOS_UINT8           aucBufMsgFlg[GMM_CAS_MSG_NUMBER_MAX];   /* ������Ϣ���д����־ */
} GMM_CAS_MSG_BUFFER_STRU, *PGMM_CAS_MSG_BUFFER_STRU;

#define GMM_AUTH_UMTS                   0
#define GMM_AUTH_GSM                    1
#define GMM_AUTH_GSM_AUTH_UNACCEPTABLE  2
#define GMM_AUTH_FAILURE                3

/*=======================================================*/

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
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

#endif /* end of GmmCasDef.h*/
