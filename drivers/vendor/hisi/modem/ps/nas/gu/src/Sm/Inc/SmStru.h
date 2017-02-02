/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmStru.h
  Description : SM���ݽṹͷ�ļ�
  History     :
      1.  ��־��      2003.12.04   �°�����
      2.  ��־��   2005.01.08   ��ֲ�޸�
      3.��    ��  : 2006��12��4��
        ��    ��  : luojian id:60022475
        �޸�����  : ���� #pragma pack(4)�����ⵥ��:A32D07779
*******************************************************************************/
#ifndef _SM_STRU_INTERFACE_H_
#define _SM_STRU_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
#pragma pack(4)
#define SM_MAX_EXPIRE_TIMES     5

#define SM_T3380_LENGTH         30000

#define SM_T3381_LENGTH         8000
#define SM_T3390_LENGTH         8000
#define SM_T0001_LENGTH         80000
#define SM_T0002_LENGTH         30000
#define SM_T0003_LENGTH         8000

/* TIMER TYPE DEFINE */
#define SM_REGISTER_TIMER_ID    0xff
#define SM_TIMER_TYPE_T3380     0                                               /* T3380                                    */
#define SM_TIMER_TYPE_T3381     1                                               /* T3381                                    */
#define SM_TIMER_TYPE_T3390     2                                               /* T3390                                    */
#define SM_TIMER_TYPE_T0001     3                                               /* Register������ʱ��                       */
#define SM_TIMER_TYPE_T0002     4                                               /* network�����PDPcontext active������ʱ�� */
#define SM_TIMER_TYPE_T0003     5                                               /* network�����PDPcontext modify������ʱ�� */

/*ucRegisterFlg */
#define SM_PS_NOTREGISTER       0                                               /* GMM��PS��û��ע��                        */
#define SM_PS_REGISTERING       1                                               /* GMM��PS������ע��                        */
#define SM_PS_REGISTERED        2                                               /* GMM��PS���Ѿ�ע��                        */

/* state */
#define SM_PDP_INACTIVE             0
#define SM_PDP_ACTIVE_PENDING       1
#define SM_PDP_INACTIVE_PENDING     2
#define SM_PDP_MODIFY_PENDING       3
#define SM_PDP_ACTIVE               4
#define SM_PDP_NW_MODIFY            6

/* Ti Flg */
#define SM_TI_NET_ORG                   (0)
#define SM_TI_MS_ORG                    (1)

#if (FEATURE_ON == FEATURE_IPV6)
#define SM_MAX_IP_ADDR_LEN              (22)                                              /*�տ���Ϣ��ip��ַ�ĳ��� */
#else
#define SM_MAX_IP_ADDR_LEN              (18)
#endif

#define NAS_SM_MAX_QOS_LEN              (16)
#define NAS_SM_MAX_APN_LEN              (100)


typedef struct
{
    SM_TAF_CAUSE_ENUM_UINT16            enSmCuase;
    GMM_SM_CAUSE_ENUM_UINT16            enGmmCause;

} NAS_SM_GMM_ERR_CODE_MAP_STRU;


typedef struct{
    VOS_UINT32                          ulQosLength;                            /* Qos�����ݴ�С */
    VOS_UINT8                           aucQosValue[NAS_SM_MAX_QOS_LEN];        /* Qos�����׵�ַ */
} SM_QOS_STRU;


typedef struct{
    HTIMER        TimerId;                                                    /* vos�����Timer Id                        */
    VOS_UINT8           ucExpireTimes;                                              /* Timer��ʱ����                            */
    VOS_UINT8           ucTimerType;                                                /* Timer����                                */
#define SM_TIMER_STA_ON     1
#define SM_TIMER_STA_OFF    0
    VOS_UINT8           ucTimerStaFlg;
}SM_TIMER_MNG_STRU;
typedef struct
{
    VOS_UINT32                              ulApnLength;                        /* APN�����ݴ�С   */
    VOS_UINT8                               aucApnValue[NAS_SM_MAX_APN_LEN];    /* APN�������׵�ַ */
} SM_PDP_APN_STRU;

typedef struct{
    VOS_UINT32       ulAddrLength;                                              /* ADDR�����ݴ�С */
    VOS_UINT8        aucAddrValue[SM_MAX_IP_ADDR_LEN];                                             /* ADDR�������׵�ַ*/
} SM_PDP_ADDR_STRU;

typedef struct
{
    VOS_UINT8                           ucTi;               /* Transaction ID                           */
    VOS_UINT8                           ucCr;               /* Call Reference                           */
    VOS_UINT8                           ucTiFlg;            /* TI��־��0�������γɣ�1��MS�γ�           */
    VOS_UINT8                           ucState;            /* PDP CONTEXT��״̬                        */
    VOS_UINT8                           ucRabId;            /* RAB ID                                   */

    VOS_UINT8                           ucAddrIndex;        /* ��ʵ����PDP ADDRESS�б��е�λ��          */

    VOS_UINT8                           ucRadioPri;         /* Radio Priority                           */
    SM_TIMER_MNG_STRU                   TimerInfo;          /* ��ʵ���Ӧ��ʵ����Ϣ                     */
    SM_QOS_STRU                         QoS;                /* ��ʵ���Ӧ��QoS                          */
    VOS_UINT32                          ulHoldLen;          /* ������Ϣ��С                             */
    VOS_VOID                           *pHoldSndMsg;        /* ������Ϣ�ĵ�ַ                           */
} NAS_SM_PDP_CONTEXT_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucNsapiCnt;                             /* ʹ�ô�APN��PDP ADDR��Ϣ��NSAPI����       */
    VOS_UINT8                           aucNsapi[SM_MAX_NSAPI_NUM];             /* NSAPI���б�                              */
    SM_PDP_APN_STRU                     PdpApn;                                 /* APN VALUE                                */
    SM_PDP_ADDR_STRU                    PdpAddrInfo;                            /* PDP��ַ��Ϣ                              */
} NAS_SM_PDP_ADDR_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucRegisterFlg;      /* GMM��PS���Ƿ�ע���־                    */
    VOS_UINT8                           ucRegTimerSta;      /* ע��Timer state                          */
    HTIMER                              ulRegTimerID;       /* ע��Timer ID                             */

    struct{
        VOS_VOID                       *pHoldRcvMsg;        /* GMMδע��ʱ��������յ�TAF��Ϣ           */
    }aHoldMsg[SM_MAX_NSAPI_NUM];

    NAS_SM_PDP_CONTEXT_INFO_STRU        aPdpCntxtList [SM_MAX_NSAPI_NUM];
    VOS_UINT32                          ulSessionBeginFlg;  /* Begin Session��ʶ                        */
}SM_ENTITY_STRU;


typedef struct
{
    VOS_UINT16                          usPdpAddrFlg;       /* PDP address and apn����Ч��־            */
    NAS_SM_PDP_ADDR_INFO_STRU           aPdpAddrlist[SM_MAX_NSAPI_NUM];
}SM_PDP_ADDR_AND_APN_STRU;

typedef struct {
    VOS_UINT32  ulCnt;
    VOS_UINT8  *pOcts;
}SM_OCT_VARY_STRU;

typedef struct{
    VOS_UINT8    ucLen;                                                             /* IE�ĳ���                                 */
    VOS_UINT8    *pValue;                                                           /* IE���׵�ַ                               */
}SM_MSG_IE_COMMON_STRU;

typedef struct
{
    VOS_UINT8                           ucTiFlg;
    VOS_UINT8                           ucTi;               /* Transaction identifier         */
    VOS_UINT8                           ucRadioPri;         /* Radio priority                 */
    VOS_UINT8                           SmCause;            /* SM Cause                       */
    VOS_UINT8                           ucTdi;              /* Tear down indicator            */
    SM_MSG_IE_COMMON_STRU               PdpAddr;            /* Packet data protocol address   */
    SM_MSG_IE_COMMON_STRU               Apn;                /* Access point name              */
    SM_MSG_IE_COMMON_STRU               Qos;                /* Negotiated QoS                 */
    SM_MSG_IE_COMMON_STRU               ProCnfgOpt;         /* Protocol configuration options */
    SM_MSG_IE_COMMON_STRU               Pfi;                /* Packet Flow Identifier         */
#if (FEATURE_ON == FEATURE_IPV6)
    SM_MSG_IE_COMMON_STRU               stSmCauseTwo;       /* SM cause 2                     */
#endif
}SM_NW_MSG_STRU;

#define EVT_NAS_SM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa          /* ΪPC���̻طŶ������Ϣ */

/*****************************************************************************
 Structure      : NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC�طŹ��̣��洢����SM��ص�ȫ�ֱ���
 Message origin :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                    pc_g_ucTiExt;                                               /* ��¼ti�Ƿ�����չλ                       */
    VOS_UINT8                    pc_g_TiMapToNsapi[256];                                     /* TI��NSAPI��ӳ���ϵ                      */
    VOS_UINT8                    pc_g_CrMapToNsapi[256];                                     /* CR��NSAPI��ӳ���ϵ                      */
    VOS_UINT8                    pc_g_aucSapi[SM_MAX_NSAPI_NUM + SM_NSAPI_OFFSET][2];
    SM_ENTITY_STRU               pc_g_SmEntity;                                              /* smʵ�嶨��                               */
    SM_PDP_ADDR_AND_APN_STRU     pc_g_SmPdpAddrApn;                                          /* ����pdp address��apn                     */
} NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST;

/*****************************************************************************
 Structure      : NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC�طŹ��̣�����SM��ص�ȫ�ֱ���ͨ��������Ϣ�ṹ����
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                           usMsgID;
    VOS_UINT16                           usReserved;                            /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST    stOutsideCtx;
}NAS_SM_SDT_MSG_ST;


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
