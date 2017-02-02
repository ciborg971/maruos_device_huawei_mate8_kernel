
#ifndef _SMC_ENTITY_H_
#define _SMC_ENTITY_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */


#pragma pack(4)

#define SMC_MAX_EXPIRE_TIMES    2

#define SMC_TIMER_TC1M_LENGTH           (20000)

#define SMS_TPDU_MTI_PS                 (0x24)
#define SMS_TPDU_SCLEN_PS               (0x22)
#define SMS_TPDU_MTI_CS                 (0x28)
#define SMS_TPDU_SCLEN_CS               (0x26)
#define SMT_TP_RD_RETRANS               (0x04)                                                 /* RETRANSFER                               */
#define    SMS_TPDU_SCLEN_LTE_PS        (0x26)
#define    SMS_TPDU_MTI_LTE_PS          (0x28)
enum NAS_SMS_HOLD_MSG_TYPE_ENUM
{
    NAS_SMS_HOLD_MSG_GU_MT_RP_ACK       = 0, 
    NAS_SMS_HOLD_MSG_LTE_MT_RP_ACK      = 1,
    NAS_SMS_HOLD_MSG_GU_MO_RP_DATA      = 2, 
    NAS_SMS_HOLD_MSG_LTE_MO_RP_DATA     = 3, 

    NAS_SMS_HOLD_MSG_BUTT
};
typedef VOS_UINT8 NAS_SMS_HOLD_MSG_TYPE_ENUM_UINT8;


typedef struct{
    VOS_UINT32                          ulMsgLen ;                                                   /* ��Ϣ����                                 */
    VOS_VOID                            *pMsg;                                                       /* ��Ϣ�׵�ַ                               */
}SMC_SAVE_MSG_STRU ;
typedef struct{
    HTIMER                              TimerId;                                                  /* Timer Id                                 */
    VOS_UINT8                           ucTimerSta;                                               /* ��ʶTimer�Ƿ���Ч                        */
    VOS_UINT8                           ucExpireTimes;                                            /* Timer��ʱ����                            */
    VOS_UINT8                           aucReserved1[2];
}SMC_TIMER_MNG_STRU;


typedef struct
{
    struct{
        VOS_UINT8                       ucState;                                                   /* SMC MOʵ���״̬                         */
        VOS_UINT8                       ucTi;                                                      /* Transaction ID                           */
        VOS_UINT8                       ucPreTi;                                                   /* ǰһ��TIֵ                               */
        VOS_UINT8                       ucMr;                                                      /* Message Reference                        */
        VOS_UINT8                       ucCpAckFlg;    /*�ò��������Ƿ���Ҫ������ظ�CP-ACK��Ϣ*/                                            /* �Ƿ���CP-ACK                           */
        NAS_SMS_HOLD_MSG_TYPE_ENUM_UINT8                  enHoldSndMsgType;                           /* SMS�л������Ϣ���� */
        VOS_UINT8                       aucReserved1[2];
        SMC_TIMER_MNG_STRU              TimerInfo;                                          /* ��ʵ���Ӧ��TIMER��Ϣ                    */
        SMC_SAVE_MSG_STRU               HoldRcvMsg;                                         /* ���������Ϣ�ĵ�ַ                       */
        SMC_SAVE_MSG_STRU               HoldSndMsg;                                         /* ���淢����Ϣ�ĵ�ַ                       */
    }SmcMo;
    struct{
          VOS_UINT8                     ucState;                                                 /* SMC MO��״̬                             */
          VOS_UINT8                     ucTi;                                                    /* Transaction ID                           */
          VOS_UINT8                     ucMr;                                                    /* Message Reference                        */
          NAS_SMS_HOLD_MSG_TYPE_ENUM_UINT8                  enHoldSndMsgType;                       /* SMS�л������Ϣ���� */
          SMC_TIMER_MNG_STRU            TimerInfo;                                        /* ��ʵ���Ӧ��TIMER��Ϣ                    */
          SMC_SAVE_MSG_STRU             HoldSndMsg;                                       /* ���淢����Ϣ�ĵ�ַ                       */
    }SmcMt;
}SMC_ENTITY_STRU;

extern SMC_ENTITY_STRU     g_SmcPsEnt;                                          /* sms ps���ʵ������                       */
extern SMC_ENTITY_STRU     g_SmcCsEnt;                                          /* sms cs���ʵ������                       */

extern VOS_UINT8               g_ucPsServiceStatus;                             /* GMM��PS���Ƿ�ע���־                    */
extern VOS_UINT8               g_ucCsRegFlg;                                          /* MM��CS���Ƿ�ע���־                    */

extern VOS_UINT8               g_ucSmsMR;
extern VOS_UINT8               g_ucCurSendDomain;
extern VOS_UINT8               g_SndDomain;                                   /* ������ */

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif

