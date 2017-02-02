
#ifndef _TAF_MMA_CTX_H_
#define _TAF_MMA_CTX_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "TafAppMma.h"
#include  "TafFsm.h"
#include  "TafMmaTimerMgmt.h"
#include  "TafSdcCtx.h"
#include  "MmaUphyInterface.h"

//#include "MmaAppLocal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_MMA_MAX_MSG_BUFFER_LEN                      (500)                  /* �������󳤶� */
#define TAF_MMA_MAX_MSG_QUEUE_NUM                       (4)                     /* ��󻺴�ĸ��� */
#define TAF_MMA_MAX_STACK_DEPTH                         (4)                     /* ״̬��ջ����� */
#define TAF_MMA_ExtractMsgNameFromEvtType(ulEventType)     ((VOS_UINT16)((ulEventType) & 0x0000FFFF))          /* ��EventType�л�ȡMsgName     */
#define TAF_MMA_MAX_MSG_QUEUE_SIZE                      (11)                    /* �ڲ���Ϣ�������ĳ��� */

#define TAF_MMA_MAX_OPER_NUM                            (5)

#define TAF_MMA_MAX_PHONE_MODE_SET_MODULE_NUM           (4)                     /* ��ǰ��Ҫ���Ϳ��ػ�����ģ��������� */

/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, begin */
#define TAF_MMA_WILDCARD_CDMAPN_VALUE                   (0xFFFF)
#define TAF_MMA_WILDCARD_EVDOPN_VALUE                   (0xFFFF)
/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, end */

/* Modified by l00301449 for CDMA 1X Iteration 13, 2015-04-16, begin */

typedef VOS_UINT16   TAF_MMA_SYS_CFG_OPER_TYPE;
#define  TAF_MMA_SYS_CFG_NONE_SET                           (0x0000) /*����Ϊ��*/
#define  TAF_MMA_SYS_CFG_ROAM_SET                           (0x0001) /*����������*/
#define  TAF_MMA_SYS_CFG_MODE_SET                           (0x0002) /*�����˽���ģʽ��������*/
#define  TAF_MMA_SYS_CFG_BAND_SET                           (0x0004) /*������Ƶ��*/
#define  TAF_MMA_SYS_CFG_CS_DETACH_SET                      (0x0010) /*���������˷�������Ҫ����CS Detach*/
#define  TAF_MMA_SYS_CFG_PS_DETACH_SET                      (0x0020) /*���������˷�������Ҫ����PS Detach*/
#define  TAF_MMA_SYS_CFG_CS_ATTACH_SET                      (0x0040) /*���������˷�������Ҫ����CS Attach*/
#define  TAF_MMA_SYS_CFG_PS_ATTACH_SET                      (0x0080) /*���������˷�������Ҫ����PS Attach*/


#define  TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED                (TAF_MMA_SYS_CFG_CS_ATTACH_SET  \
                                                            |TAF_MMA_SYS_CFG_PS_ATTACH_SET)

#define  TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED                (TAF_MMA_SYS_CFG_CS_DETACH_SET  \
                                                            |TAF_MMA_SYS_CFG_PS_DETACH_SET)

/* ��Ҫ����syscfg���� */
#define  TAF_MMA_SYS_CFG_SET_REQ_REQUIRED                   (TAF_MMA_SYS_CFG_ROAM_SET  \
                                                            |TAF_MMA_SYS_CFG_MODE_SET  \
                                                            |TAF_MMA_SYS_CFG_BAND_SET)

#define TAF_MMA_SYS_CFG_RAT_NONE_SET                        (0x00)
#define TAF_MMA_SYS_CFG_RAT_G_SET                           (0x01)
#define TAF_MMA_SYS_CFG_RAT_W_SET                           (0x02)
#define TAF_MMA_SYS_CFG_RAT_1X_SET                          (0x04)
#define TAF_MMA_SYS_CFG_RAT_DO_SET                          (0x08)

#define TAF_MMA_SYS_CFG_RAT_C_SET                           (TAF_MMA_SYS_CFG_RAT_1X_SET  \
                                                            |TAF_MMA_SYS_CFG_RAT_DO_SET)

#define TAF_MMA_SYS_CFG_RAT_GU_SET                          (TAF_MMA_SYS_CFG_RAT_G_SET  \
                                                            |TAF_MMA_SYS_CFG_RAT_W_SET)

/* Modified by l00301449 for CDMA 1X Iteration 13, 2015-04-16, end */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum TAF_MMA_MSG_CACHE_PRIO_ENUM
{
    TAF_MMA_MSG_CACHE_PRIO_HIGH              ,                           /* �����ȼ����� */
    TAF_MMA_MSG_CACHE_PRIO_MIDDLE            ,                           /* �����ȼ����� */
    TAF_MMA_MSG_CACHE_PRIO_LOW               ,                           /* �����ȼ����� */

    TAF_MMA_MSG_CACHE_PRIO_BUTT
};
typedef VOS_UINT32 TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8;
enum TAF_MMA_FSM_ID_ENUM
{
    TAF_MMA_FSM_MAIN                                            = 0X00,

    TAF_MMA_FSM_PHONE_MODE                                      = 0X01,

    TAF_MMA_FSM_IMS_SWITCH                                      = 0X02,
    /* Modified by l00301449 for Iteration 13, 2015-04-09, begin */
    TAF_MMA_FSM_SYS_CFG                                         =0x03,
    /* Modified by l00301449 for Iteration 13, 2015-04-09, end */

    TAF_MMA_FSM_BUTT

};
typedef VOS_UINT32 TAF_MMA_FSM_ID_ENUM_UINT32;


enum TAF_MMA_INIT_CTX_TYPE_ENUM
{
    TAF_MMA_INIT_CTX_STARTUP                    = 0,
    TAF_MMA_INIT_CTX_POWEROFF                   = 1,
    TAF_MMA_INIT_CTX_BUTT
};
typedef VOS_UINT32 TAF_MMA_INIT_CTX_TYPE_ENUM_UINT8;


enum TAF_MMA_OPER_TYPE_ENUM
{

    TAF_MMA_OPER_SYS_CFG_REQ                    = 0,
    TAF_MMA_OPER_ACQ_REQ                        = 1,
    TAF_MMA_OPER_REG_REQ                        = 2,
    TAF_MMA_OPER_POWER_SAVE_REQ                 = 3,
    TAF_MMA_OPER_DETACH_REQ                     = 4,
    TAF_MMA_OPER_CFPLMN_SET_REQ                 = 5,
    TAF_MMA_OPER_CFPLMN_QRY_REQ                 = 6,

    /* Added by y00307564 for CDMA Iteration 8 2015-2-13 begin */
    TAF_MMA_OPER_PREF_PLMN_SET_REQ              = 7,
    TAF_MMA_OPER_PREF_PLMN_QUERY_REQ            = 8,
    TAF_MMA_OPER_PREF_PLMN_TEST_REQ             = 9,
    TAF_MMA_OPER_CDMACSQ_SET_REQ                = 10,
    /* Added by y00307564 for CDMA Iteration 8 2015-2-13 end */
    /* Added by c00318887 for AT&T phaseII, 2015-3-12, begin */
    TAF_MMA_OPER_PLMN_LIST_REQ                  = 11,
    TAF_MMA_OPER_EONS_UCS2_REQ                  = 12,
    /* Added by c00318887 for AT&T phaseII, 2015-3-12, end */
    TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ            = 13,
    TAF_MMA_OPER_PLMN_SPEC_SEL_REQ              = 14,
    TAF_MMA_OPER_PLMN_LIST_ABORT_REQ            = 15,

	/* Added by z00316370 for UTS 2015-5-21 begin */
    TAF_MMA_OPER_GETSTA_QUERY_REQ               = 16,
    TAF_MMA_OPER_CHVER_QUERY_REQ                = 17,
    /* Added by z00316370 for UTS 2015-5-21 end */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-10, begin */
    TAF_MMA_OPER_SET_CSIDLIST_REQ               = 18,
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-10, end */

    TAF_MMA_OPER_BUTT

};
typedef VOS_UINT32 TAF_MMA_OPER_TYPE_ENUM_UINT32;

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

/*****************************************************************************
 �ṹ��    : TAF_MMA_ENTRY_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ҫ����������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucEntryMsgBuffer[TAF_MMA_MAX_MSG_BUFFER_LEN];
} TAF_MMA_ENTRY_MSG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_PHONE_MODE_SET_ORDER_STRU
 �ṹ˵��  : ��¼���ײ��·�����������Ⱥ�˳��
              ����˵��:
              ������˳��ΪIMSA->CDMA->MSCC,��ôaulSwitchOnModuleID�д�ŵ�
              �Ⱥ�˳��ΪIMSA->CDMA->MSCC,������ܸ���Ϊ3,����IMSAģ�鷢�Ϳ��������ʱ��
              usSwitchOnIndex��ŵ�ֵΪ0��

              ������˳��ΪIMSA->MSCC;��ôaulSwitchOnModuleID�д�ŵײ��
              �Ⱥ�˳��ΪIMSA->MSCC,������ܸ���Ϊ2,����MSCCģ���Ϳ��������ʱ��
              usSwitchOnIndex��ŵ�ֵΪ1;

              ʹ�����½ṹ��MMA�����׵�����ײ����Ҫ��Ŀ���˳������

*****************************************************************************/
typedef struct
{
    VOS_UINT16      usNum;                                                      /* ���²㷢�Ϳ���������ܸ��� */
    VOS_UINT16      usIndex;                                                    /* ָ����Ҫ������Ӧģ��Ľ��뼼�����±� */
    VOS_UINT32      aulModuleID[TAF_MMA_MAX_PHONE_MODE_SET_MODULE_NUM];         /* ������ÿ�����Ҫ�����ײ�ģ����Ⱥ�˳�� */
}TAF_MMA_PHONE_MODE_SET_ORDER_STRU;
typedef struct
{
    TAF_ERROR_CODE_ENUM_UINT32          enPhoneError;       /* ���ػ��Ĵ���ԭ��ֵ */
    TAF_MMA_PHONE_MODE_SET_ORDER_STRU   stPhoneModeOrder;                    /* TAF MMA����˳����� */
}TAF_MMA_FSM_PHONE_MODE_CTX_STRU;

/* Added by h00313353 for Iteration 13, 2015-4-9, begin */
/*****************************************************************************
 �ṹ��    : TAF_MMA_FSM_SYSCFG_CTX_STRU
 �ṹ˵��  : ϵͳ����״̬��������
 1.��    ��   : 2015��4��9��
   ��    ��   : h00313353
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType;                             /* ��¼SYSCFG�Ĳ������� */
    VOS_UINT8                           ucAttachOpId;                           /* ��¼attach����ʱ��OpId*/
    VOS_UINT8                           aucReserved[1];

    TAF_MMA_SYS_CFG_PARA_STRU           stSysCfgPara;
}TAF_MMA_FSM_SYS_CFG_CTX_STRU;
/* Added by h00313353 for Iteration 13, 2015-4-9, end */

typedef union
{
    TAF_MMA_FSM_PHONE_MODE_CTX_STRU                         stPhoneModeCtx;
    /* Added by h00313353 for Iteration 13, 2015-4-9, begin */
    TAF_MMA_FSM_SYS_CFG_CTX_STRU                            stSysCfgCtx;
    /* Added by h00313353 for Iteration 13, 2015-4-9, end */

}TAF_MMA_FSM_EXTRA_CTX_UNION;


typedef struct
{
    /* ״̬������ָ��,ָ��ΪNULL��ʾ��ǰ״̬����Ч  */
    TAF_FSM_DESC_STRU                  *pstFsmDesc;

    /* ��ǰ״̬����ʶ */
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId;

    /* ��ǰ״̬ */
    VOS_UINT32                          ulState;                                /* L1״̬ */

    /* �����ϢMSGID������  */
    TAF_MMA_ENTRY_MSG_STRU              stEntryMsg;

    /* ״̬������ */
    TAF_MMA_FSM_EXTRA_CTX_UNION         unFsmCtx;
}TAF_MMA_FSM_CTX_STRU;


typedef struct
{
    VOS_UINT16                          usStackDepth;                           /* ��ǰѹջ��״̬���� */
    VOS_UINT16                          usStackPopFlg;                          /* ��ǰջpop��־ */
    TAF_MMA_FSM_CTX_STRU                astFsmStack[TAF_MMA_MAX_STACK_DEPTH];   /* ״̬��ջ����� */
}TAF_MMA_FSM_STACK_STRU;
typedef struct
{
    TAF_MMA_ENTRY_MSG_STRU              stMsgEntry;     /* ����ľ�������   */
}TAF_MMA_CACH_MSG_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                          /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[3];
    TAF_MMA_CACH_MSG_INFO_STRU          astMsgQueue[TAF_MMA_MAX_MSG_QUEUE_NUM]; /* MMA����Ϣ�������飬�洢���Ǵ�ͨ����Ϣͷ����Ϣ */
}TAF_MMA_MSG_QUEUE_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* ��ϢID */
    VOS_UINT8                           aucReserve[2];

    VOS_UINT8                           aucBuf[TAF_MMA_MAX_MSG_BUFFER_LEN];     /* ��Ϣ���� */
}TAF_MMA_INTERNAL_MSG_BUF_STRU;



typedef struct
{
    /* TAF MMA�ڲ���Ϣ���� */
    TAF_MMA_INTERNAL_MSG_BUF_STRU       astMmaMsgQueue[TAF_MMA_MAX_MSG_QUEUE_SIZE];

    /* ������Ϣ��ʱ����buff,����ֲ�����ʱֱ��ʹ�øÿռ�,Ϊ�˱��ⷢ���ڲ���Ϣʱ
    ռ�ýϴ��ջ�ռ� */
    TAF_MMA_INTERNAL_MSG_BUF_STRU       stSendMsgBuf;

    /* �ڲ���Ϣ������е�����βָ�� */
    VOS_UINT8                           ucTail;

    /* �ڲ���Ϣ������е�����ͷָ�� */
    VOS_UINT8                           ucHeader;

    VOS_UINT16                          usReserved;
} TAF_MMA_INTERNAL_MSG_QUEUE_STRU;


typedef struct
{
    VOS_UINT8                           aucRsv[4];
    VOS_UINT32                          ulAutoInitPsFlg;                        /* �ϵ��Ƿ��ʼ��Э��ջ */
    VOS_UINT32                          ulAutoSwitchOnFlg;                      /* �ϵ��Ƿ��Զ�����(�����ڲ����������MSCC) */
}TAF_MMA_PHONE_MODE_CTRL_CTX_STRU;


typedef struct
{
    VOS_UINT8                           ucMmaLogInfoFlag;
    VOS_UINT8                           aucReserve[3];
}TAF_MMA_MAINTAIN_CTX_STRU;


typedef struct
{
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enPhyInitStatus;
    VOS_UINT8                           aucReserved[2];
}TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU;

typedef struct
{
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT8                           ucUsedFlag;
    VOS_UINT8                           aucReserved[3];
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType;
    VOS_VOID                           *pPara;
} TAF_MMA_OPER_CTX_STRU;

/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
/*****************************************************************************
 �ṹ��    : TAF_MMA_DELAY_REPORT_SERVICE_STATUS_STRU
 �ṹ˵��  : en_NV_Item_DELAY_REPORT_SERVICE_STATUS_CFG NV��ṹ
 1. ��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                               /* 0:NV δ����; 1:NV ���� */
    VOS_UINT8                           aucReserved[3];                               
    VOS_UINT32                          ulRptSrvStaDelayTimerValue;             /* ��ʱ�ϱ���ʱ��ʱ��,��λ:�� */               
}TAF_MMA_DELAY_REPORT_SERVICE_STATUS_STRU;
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

typedef struct
{
    VOS_UINT8                           ucCfgGetGeoFlag;                        /* ��ȡ������Ŀ��� */
    VOS_UINT8                           ucCcpuResetFlag;                        /* 0:����C�˵�����λ�������ϵ� ;
                                                                                   1:��C�˵�����λ*/
    VOS_UINT8                           aucReserved[2];
    VOS_UINT32                          ulGetGeoTimerLen;                       /* ��ȡ�����붨ʱ��ʱ������λΪ�� */
    VOS_UINT32                          ulGeoEffectiveTimeLen;                  /* ��������Чʱ������λΪ���� */
} TAF_MMA_GET_GEO_NV_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulGetGeoTickTime;                       /* ʱ�������λΪ�� */
    TAF_SDC_PLMN_ID_STRU                stGeoPlmnId;                            /* ����λ����Ϣ��PLMN��Ϣ */
    TAF_MMA_GET_GEO_NV_CFG_STRU         stGetGeoNvCfg;
} TAF_MMA_GET_GEO_CTX_STRU;


typedef struct
{
    VOS_UINT32  BandSpare7                   : 7;
    VOS_UINT32  BandGsmDcs1800               : 1;
    VOS_UINT32  BandGsmEgsm900               : 1;
    VOS_UINT32  BandGsmPgsm900               : 1;
    VOS_UINT32  Spare6                       : 6;
    VOS_UINT32  BandWcdma_VII_2600           : 1;
    VOS_UINT32  BandWcdma_VIII_900           : 1;
    VOS_UINT32  BandWcdma_IX_1700            : 1;
    VOS_UINT32  BandGsm850                   : 1;
    VOS_UINT32  BandGsmRgsm900               : 1;
    VOS_UINT32  BandGsmPcs1900               : 1;
    VOS_UINT32  BandWcdma_I_Imt2k1           : 1;
    VOS_UINT32  BandWcdma_II_PCS_1900        : 1;
    VOS_UINT32  BandWcdma_III_1800           : 1;
    VOS_UINT32  BandWcdma_IV_1700            : 1;
    VOS_UINT32  BandWcdma_V_850              : 1;
    VOS_UINT32  BandWcdma_VI_800             : 1;
    VOS_UINT32  BandWCDMA_XIX_850            : 1;
    VOS_UINT32  BandWcdma_XI_1500            : 1;
    VOS_UINT32  Spare2                       : 2;
}TAF_MMA_USER_PREF_BAND_STRU;


typedef struct
{
    VOS_UINT32                          BandGsm450      :1;
    VOS_UINT32                          BandGsm480      :1;
    VOS_UINT32                          BandGsm850      :1;
    VOS_UINT32                          BandGsmP900     :1;
    VOS_UINT32                          BandGsmR900     :1;
    VOS_UINT32                          BandGsmE900     :1;
    VOS_UINT32                          BandGsm1800     :1;
    VOS_UINT32                          BandGsm1900     :1;
    VOS_UINT32                          BandGsm700      :1;
    VOS_UINT32                          BandSpare7      :23;
}TAF_MMA_GSM_PREF_BAND_STRU;


typedef struct
{
    VOS_UINT32                          BandWCDMA_I_2100      :1;
    VOS_UINT32                          BandWCDMA_II_1900     :1;
    VOS_UINT32                          BandWCDMA_III_1800    :1;
    VOS_UINT32                          BandWCDMA_IV_1700     :1;
    VOS_UINT32                          BandWCDMA_V_850       :1;
    VOS_UINT32                          BandWCDMA_VI_800      :1;
    VOS_UINT32                          BandWCDMA_VII_2600    :1;
    VOS_UINT32                          BandWCDMA_VIII_900    :1;
    VOS_UINT32                          BandWCDMA_IX_J1700    :1;
    VOS_UINT32                          BandSpare10           :1;
    VOS_UINT32                          BandWCDMA_XI_1500     :1;
    VOS_UINT32                          BandSpare7            :7;
    VOS_UINT32                          BandWCDMA_XIX_850     :1;
    VOS_UINT32                          BandSpare13           :13;
}TAF_MMA_WCDMA_PREF_BAND_STRU;


typedef union
{
    VOS_UINT32                          ulPrefBand;
    TAF_MMA_USER_PREF_BAND_STRU         BitBand;
}TAF_MMA_USER_BAND_SET_UN;


typedef union
{
    VOS_UINT32                          ulBand;
    TAF_MMA_WCDMA_PREF_BAND_STRU        BitBand;
}TAF_MMA_WCDMA_BAND_SET_UN;


typedef union
{
    VOS_UINT32                          ulBand;
    TAF_MMA_GSM_PREF_BAND_STRU          BitBand;
}TAF_MMA_GSM_BAND_SET_UN;


typedef struct
{
    TAF_MMA_WCDMA_BAND_SET_UN               unWcdmaBand;
    TAF_MMA_GSM_BAND_SET_UN                 unGsmBand;
    VOS_UINT8                               aucReserved1[12];
    VOS_UINT8                               aucReserved2[12];
}TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU;


typedef struct
{
    TAF_MMA_USER_BAND_SET_UN            uUserSetGuBand;                         /* �ϴ��û����óɹ���ǰ��Ч��GUƵ�� */
    TAF_USER_SET_PREF_BAND64            stOrigUserSetGuBand;                    /* �ϴ��û����óɹ���GU 64λԭʼƵ��,������ѯʹ�� */
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   uUserSetUeFormatGuBand;                 /* ת��ΪUE֧�ָ�ʽ���ϴ��û����óɹ���ǰ��Ч��GUƵ�� */
#if(FEATURE_ON == FEATURE_LTE)
    TAF_USER_SET_PREF_BAND64            stUserSetLteBand;                       /* �ϴ��û����óɹ���ǰ��Ч��LTEƵ�� */
#endif
}TAF_MMA_SYSCFG_USER_SET_BAND_STRU;


typedef struct
{
    TAF_MMA_RAT_ORDER_STRU              stRatPrioList;                          /* �ϴ��û����óɹ���ǰ��Ч�Ľ���ģʽ���ȼ�*/
    /* Modified by h00313353 for Iteration 13, 2015-4-15, begin */
    TAF_MMA_ROAM_MODE_ENUM_UINT8        enRoam;                                 /* �ϴ��û����óɹ���ǰ��Ч���������� */
    /* Modified by h00313353 for Iteration 13, 2015-4-15, end */
    TAF_MMA_USER_SET_PRIO_RAT_ENUM_U8   enPrioRat;                              /* �ϴ��û����óɹ���ǰ��Ч�Ľ������ȼ� */
    VOS_UINT8                           ucReserve;
    /* Modified by h00313353 for Iteration 13, 2015-4-9, begin */
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8   enSrvDomain;                            /* �ϴ��û����óɹ���ǰ��Ч�ķ����� */
    /* Modified by h00313353 for Iteration 13, 2015-4-9, end */
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU   stUserSetBand;                          /* �ϴ��û����óɹ���ǰ��Ч��Ƶ����Ϣ */
}TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU;
typedef struct
{
    VOS_UINT32                          ulUeGSptBand;
    VOS_UINT32                          ulUeWSptBand;
    VOS_UINT32                          ulAllUeBand;
    TAF_MMA_WCDMA_BAND_SET_UN           unWRFSptBand;
    TAF_MMA_GSM_BAND_SET_UN             unGRFSptBand;

#if(FEATURE_ON == FEATURE_LTE)
    TAF_USER_SET_PREF_BAND64            stUeSupportLteBand;
#endif
}TAF_MMA_UE_BAND_CAPA_ST;


/* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, begin */
/*****************************************************************************
 �ṹ��    : TAF_MMA_DSDS_INFO_STRU
 �ṹ˵��  : DSDS��ص���Ϣ
 1.��    ��   : 2015��5��15��
   ��    ��   : L00301449
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;
}TAF_MMA_DSDS_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TAF_MMA_ATTACH_INFO_STRU
 �ṹ˵��  : ATTACH��ص���Ϣ
 1.��    ��   : 2015��5��15��
   ��    ��   : L00301449
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAttachOpId;
    VOS_UINT8                           aucRsved[3];
}TAF_MMA_ATTACH_INFO_STRU;

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, end */

typedef struct
{
    /**************************************************************************
                        MMA״̬��״̬����״̬ջ
    **************************************************************************/
    TAF_MMA_FSM_CTX_STRU                                    stCurFsm;                               /* ״̬����ǰ��״̬������ */
    TAF_MMA_FSM_STACK_STRU                                  stFsmStack;                             /* ״̬����״̬��ջ����   */

    TAF_MMA_PHONE_MODE_CTRL_CTX_STRU                        stPhoneModeCtrl;                        /* �ֻ�ģʽ���������� */

    TAF_MMA_TIMER_CTX_STRU                                  astMmaTimerCtx[TAF_MMA_MAX_TIMER_NUM];  /* MMA��ǰ�������еĶ�ʱ����Դ */
    TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU                stMmaExternalModuleInitStatusCtx;       /* MMA��ʼ��״̬��Ϣ */
    TAF_MMA_OPER_CTX_STRU               astMmaOperCtx[TAF_MMA_MAX_OPER_NUM];  /* MMA L-C������������ */


    /**************************************************************************
                        TAF MMA������Ϣ����
    **************************************************************************/
    TAF_MMA_MSG_QUEUE_STRU                                  stBufferEntryMsgQueue;

    TAF_MMA_INTERNAL_MSG_QUEUE_STRU                         stInternalMsgQueue;                     /* MMA�Ӳ���ڲ���Ϣ���� */

    TAF_MMA_MAINTAIN_CTX_STRU                               stMaintainInfo;

    /* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, begin */
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU                        stCFreqLockValue;                       /* 1x&evdo��Ƶ��Ϣ */
    /* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, end */

    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                     stLastSyscfgSet;                        /* �ϴ��û����óɹ���syscfg���� */

    TAF_MMA_UE_BAND_CAPA_ST                                 stUeBandCap;                            /* UE֧�ֵ�Ƶ������ */

    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, begin */
    /* Modified by l00301449 for Iteration 13, 2015-04-13, begin */
    TAF_MMA_ATTACH_INFO_STRU                                stAttachInfo;
    /* Modified by l00301449 for Iteration 13, 2015-04-13, end */

    TAF_MMA_DSDS_INFO_STRU                                  stDsdsInfo;
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, end */

    TAF_MMA_GET_GEO_CTX_STRU                                stGetGeoInfo;
    
    TAF_MMA_DELAY_REPORT_SERVICE_STATUS_STRU stDelayReportServiceInfo;

    
}TAF_MMA_CONTEXT_STRU;

extern TAF_MMA_CONTEXT_STRU                    g_stTafMmaCtx;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID TAF_MMA_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_FSM_InitSubFsm(
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId
);

VOS_VOID TAF_MMA_FSM_QuitSubFsm( VOS_VOID );

VOS_VOID  TAF_MMA_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
);

VOS_UINT32 TAF_MMA_FSM_GetFsmTopState( VOS_VOID );

VOS_UINT16  TAF_MMA_GetFsmStackDepth( VOS_VOID );

TAF_FSM_DESC_STRU* TAF_MMA_GetCurFsmDesc(VOS_VOID);
TAF_MMA_FSM_STACK_STRU* TAF_MMA_GetFsmStackAddr(VOS_VOID);

TAF_MMA_ENTRY_MSG_STRU* TAF_MMA_GetCurrFsmMsgAddr(VOS_VOID);

VOS_UINT32  TAF_MMA_GetNextCachedMsg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg
);

VOS_UINT32  TAF_MMA_GetNextPrioCachedMsg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg,
    TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8   enPrio
);


VOS_VOID  TAF_MMA_ClearCacheMsg(
    VOS_UINT32                          ulEventType
);

VOS_VOID  TAF_MMA_InitFsmCtx_PhoneMode(VOS_VOID);

/* Modified by l00301449 for Iteration 13, 2015-04-09, begin */
VOS_VOID  TAF_MMA_InitFsmCtx_SysCfg(VOS_VOID);
/* Modified by l00301449 for Iteration 13, 2015-04-09, end */


TAF_MMA_FSM_ID_ENUM_UINT32 TAF_MMA_GetCurrFsmId(VOS_VOID);

TAF_MMA_MSG_QUEUE_STRU* TAF_MMA_GetCachMsgBufferAddr(VOS_VOID);

VOS_VOID TAF_MMA_FSM_PushFsm(
    TAF_MMA_FSM_STACK_STRU              *pstFsmStack,
    TAF_MMA_FSM_CTX_STRU                *pstNewFsm
);

VOS_VOID TAF_MMA_FSM_PopFsm( VOS_VOID );

VOS_VOID  TAF_MMA_LoadSubFsm(
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm
);

VOS_UINT32 TAF_MMA_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_VOID  TAF_MMA_InitCurrFsmCtx(
    TAF_MMA_FSM_CTX_STRU                *pstCurrFsmCtx
);

VOS_VOID  TAF_MMA_InitFsmStackCtx(
    TAF_MMA_FSM_STACK_STRU              *pstFsmStack
);


VOS_VOID  TAF_MMA_InitInternalBuffer(
    TAF_MMA_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
);

VOS_VOID  TAF_MMA_InitInternalMsgQueue(
    TAF_MMA_INTERNAL_MSG_QUEUE_STRU     *pstInternalMsgQueue                   /* MMA���ڲ���Ϣ���� */
);
VOS_VOID  TAF_MMA_InitMaintainInfo(
    TAF_MMA_MAINTAIN_CTX_STRU          *pstMaintainInfo
);

VOS_VOID TAF_MMA_InitExternalModuleInitStatus(
    TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU      *pstInitStatusctx
);

TAF_MMA_PHONE_MODE_CTRL_CTX_STRU *TAF_MMA_GetPhoneModeCtrl(VOS_VOID);

VOS_UINT32  TAF_MMA_GetCacheNum( VOS_VOID );

VOS_VOID  TAF_MMA_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
);

VOS_UINT16  TAF_MMA_GetFsmStackPopFlg( VOS_VOID );

TAF_MMA_FSM_CTX_STRU* TAF_MMA_GetCurFsmAddr(VOS_VOID);

TAF_MMA_CONTEXT_STRU* TAF_MMA_GetMmaCtxAddr(VOS_VOID);

VOS_VOID  TAF_MMA_SetAutoInitPsFlg(
    VOS_UINT32                          ulAutoInitPsFlg
);

VOS_UINT32  TAF_MMA_GetAutoInitPsFlg(VOS_VOID);

VOS_VOID  TAF_MMA_SetAutoSwitchOnFlg(
    VOS_UINT32                          ulAutoSwitchOnFlg
);

VOS_UINT32  TAF_MMA_GetAutoSwitchOnFlg(VOS_VOID);




TAF_MMA_TIMER_CTX_STRU*  TAF_MMA_GetTimerCtxAddr( VOS_VOID );

VOS_VOID  TAF_MMA_SetCurPhoneErrorCode_PhoneMode(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
);

TAF_ERROR_CODE_ENUM_UINT32  TAF_MMA_GetCurPhoneErrorCode_PhoneMode(VOS_VOID);
VOS_UINT8  TAF_MMA_GetMmaLogInfoFlag( VOS_VOID );

VOS_VOID TAF_MMA_SetNetworkCapabilityInfo(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstNwCapInfo
);

VOS_VOID TAF_MMA_SetPhyInitStatus(
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enFlag
);

MMA_UPHY_INIT_STATUS_ENUM_UINT16 TAF_MMA_GetPhyInitStatus(VOS_VOID);

VOS_UINT16 TAF_MMA_IsExternalModuleInitCompeleted(VOS_VOID);
TAF_MMA_OPER_CTX_STRU*  TAF_MMA_GetOperCtxAddr( VOS_VOID );
VOS_UINT32 TAF_MMA_IsOperTypeUsed(
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType
);

VOS_UINT32 TAF_MMA_GetSpecOperTypeIndex(
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType,
    VOS_UINT8                          *pucCtxIndex
);

VOS_UINT32 TAF_MMA_GetUnusedOperCtxIndex(
    VOS_UINT8                          *pucCtxIndex
);

VOS_VOID TAF_MMA_SetOperCtx(
    TAF_MMA_CTRL_STRU                   stCtrl,
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType,
    VOS_UINT8                           ucCtxIndex
);

VOS_VOID TAF_MMA_ClearOperCtx(
    VOS_UINT8                           ucCtxIndex
);


/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
VOS_VOID TAF_MMA_SetDelayReportServiceStatusFlg(VOS_UINT8 ucDelayReportServiceStatusFlg);
VOS_UINT8 TAF_MMA_GetDelayReportServiceStatusFlg(VOS_VOID);
VOS_VOID TAF_MMA_SetDelayReportServiceStatusTimerLen(VOS_UINT32 ulTimerLen);
VOS_UINT32 TAF_MMA_GetDelayReportServiceStatusCfgTimerLen(VOS_VOID);
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */



/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, begin */
TAF_MMA_CFREQ_LOCK_SET_PARA_STRU* TAF_MMA_GetCFreqLockSetPara(VOS_VOID);

VOS_VOID TAF_MMA_InitCFreqLockPara(VOS_VOID);

/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, end */

TAF_MMA_GET_GEO_CTX_STRU* TAF_MMA_GetGeoCtxAddr(VOS_VOID);
VOS_VOID TAF_MMA_InitGetGeoCtx(VOS_VOID);
VOS_VOID  TAF_MMA_SetGeoNoSimStartFlag(
    VOS_UINT8                           ucNoSimStartFlag
);
VOS_VOID TAF_MMA_InitSdcIccId( VOS_VOID );
VOS_UINT32 TAF_MMA_IsValidIccId( VOS_VOID );
VOS_UINT8  TAF_MMA_GetGeoNoSimStartFlag(VOS_VOID);
VOS_UINT8  TAF_MMA_GetCfgGetGeoFlag(VOS_VOID);
VOS_UINT32 TAF_MMA_GetGeoTimerLen(VOS_VOID);
VOS_VOID TAF_MMA_SetCcpuResetFlag(VOS_UINT8 ucCcpuResetFlag);
VOS_UINT8 TAF_MMA_GetCcpuResetFlag(VOS_VOID);
VOS_UINT32 TAF_MMA_GetGeoEffectiveTimeLen(VOS_VOID);
VOS_UINT32 TAF_MMA_IsGeoValid(VOS_VOID);
VOS_UINT8 TAF_MMA_GetGeoCmpFlag(VOS_VOID);
VOS_VOID TAF_MMA_SetGeoCmpFlag(VOS_UINT8 ucGetGeoCmpFlag);
VOS_UINT32 TAF_MMA_IsNeedGetGeoNoSimStart(VOS_VOID);

/* Modified by l00301449 for Iteration 13, 2015-04-10, begin */
VOS_VOID  TAF_MMA_SetSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);
VOS_VOID TAF_MMA_SetTestRoamFlag(VOS_UINT8 ucFlag);
VOS_UINT8 TAF_MMA_GetTestRoamFlag(VOS_VOID);
VOS_VOID TAF_MMA_SetWaitExtTimerLen(VOS_UINT8 ucLen);
VOS_UINT8 TAF_MMA_GetWaitExtTimerLen(VOS_VOID);

VOS_VOID TAF_MMA_SetSysCfgPara_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
);

TAF_MMA_SYS_CFG_PARA_STRU *TAF_MMA_GetSysCfgPara_SysCfg(VOS_VOID);

VOS_VOID TAF_MMA_SetAttachOpId_SysCfg(
    VOS_UINT8                           ucOpId
);

/* Modified by l00301449 for Iteration 13, 2015-04-10, end */

#if (FEATURE_ON == FEATURE_LTE)
TAF_USER_SET_PREF_BAND64 *TAF_MMA_GetUserSetLteBandAddr(VOS_VOID);

TAF_USER_SET_PREF_BAND64 *TAF_MMA_GetUeSupportLteBandAddr(VOS_VOID);

#endif

TAF_MMA_RAT_ORDER_STRU *TAF_MMA_GetRatPrioListAddr(VOS_VOID);

TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *TAF_MMA_GetLastSyscfgSetAddr(VOS_VOID);

TAF_MMA_SYSCFG_USER_SET_BAND_STRU *TAF_MMA_GetSyscfgUserSetBandAddr(VOS_VOID);

TAF_MMA_ROAM_MODE_ENUM_UINT8 TAF_MMA_GetSyscfgUserSetRoamValue(VOS_VOID);

TAF_MMA_UE_BAND_CAPA_ST *TAF_MMA_GetUeSupportBandAddr(VOS_VOID);

VOS_UINT8 TAF_MMA_GetAttachOpId(VOS_VOID);


/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
TAF_MMA_SRV_ACQ_RAT_LIST_STRU* TAF_MMA_GetSrvAcqRatListAddr(VOS_VOID);

VOS_VOID TAF_MMA_UpdateSrvAcqRatList(
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
);

VOS_VOID TAF_MMA_ClearSrvAcqRatList(VOS_VOID);

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafMmaCtx.h */

