

#ifndef __TAFAPSTIMERMGMT_H__
#define __TAFAPSTIMERMGMT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "MnComm.h"
#include "TafApsApi.h"
#include "ApsL4aInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* APS��ͬʱ���еĶ�ʱ���������Ŀ */
#define TAF_APS_MAX_TIMER_NUM           (30)

/*����ʱ������ת����DOPRA��ʱ������ĺ��룬��Ҫ����1000 */
#define TIMER_S_TO_MS_1000              (1000)

/*PDP״̬ת��ʱ��Ҫ�ļ�����ʱ����ʱ�䳤�ȣ���λΪ��*/
#define TIMER_3380_S                    (30)
#define TIMER_3381_S                    (8)
#define TIMER_3390_S                    (8)

/*PDP�����еĶ�ʱ��ͨ����Ҫѭ�����β������˳�*/
#define TIMER_4_TIMES                   (4)
#define TIMER_5_TIMES                   (5)

/*���缤���ֶ�Ӧ��ʱ�������ȴ���ʱ���� T3385 * 5(��) = 8*5 = 40s,��ôUE��ȴ�
�ֶ�Ӧ���ʱ��ͱ����ټ�ȥ���紫�佫���ĵ��ӳ٣���Ϊ20S*/
#define TIMER_APS_NET_PDP_ACTIVE_PENDING_S          (20)

/* ����SNDCP���̱�����ʱ��ʱ�� */
#define TI_TAF_APS_SNDCP_ACT_TIMER_LEN              (180 * TIMER_S_TO_MS_1000)

/* �޸�SNDCP���̱�����ʱ��ʱ�� */
#define TI_TAF_ASP_SNDCP_MDF_TIMER_LEN              (120 * TIMER_S_TO_MS_1000)

/* APS��ʱ����ʱ������λ:���� */
#define TI_TAF_APS_MS_ACTIVATING_LEN                    ((TIMER_3380_S * TIMER_S_TO_MS_1000 * TIMER_5_TIMES) + (TIMER_S_TO_MS_1000 * 1))
#define TI_TAF_APS_NET_ACTIVATING_LEN                   (TIMER_APS_NET_PDP_ACTIVE_PENDING_S * TIMER_S_TO_MS_1000)
#define TI_TAF_APS_MS_MODIFYING_LEN                     ((TIMER_3381_S * TIMER_S_TO_MS_1000 * (TIMER_5_TIMES + 1)) + TI_TAF_ASP_SNDCP_MDF_TIMER_LEN)
#define TI_TAF_APS_MS_DEACTIVATING_LEN                  (TIMER_3390_S * TIMER_S_TO_MS_1000 * (TIMER_5_TIMES + 1))

#define TI_TAF_APS_DSFLOW_REPORT_LEN                    (TIMER_S_TO_MS_1000)

#define TI_TAF_APS_DEFAULT_DSFLOW_WRITE_NV_LEN          (2)

#define TI_TAF_APS_WAIT_L4A_CNF_LEN                     (2  * TIMER_S_TO_MS_1000)

#define TI_TAF_APS_1_TICK_10_MS                 (10)        /* 1 tickΪ10ms */

#define TAF_APS_INVALID_TIMER_PARA                  (0xFFFFFFFF)
#define TAF_APS_INVALID_CMD_PARA                    (TAF_APS_INVALID_TIMER_PARA)

/**
 * CDG 143 4.7 Voice and Data Call Origination
 */
/* ����CGD143 5.9.3 �ز���ʱ�����ʱ��Ϊ30s */
#define TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD_LEN        ( 30 * 1000 )

#define TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN      ( 4 * 1000 )
/* Modified by y00314741 for CDMA Iteration 15, 2015-5-26, begin */
#define TI_TAF_APS_CDATA_ESTING_LEN                         ( 150 * 1000 )
/* Modified by y00314741 for CDMA Iteration 15, 2015-5-26, end */
#define TI_TAF_APS_CDATA_DISCING_LEN                        ( 30 * 1000 )
#define TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF_LEN        ( 30 * 1000 )
#define TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF_LEN      ( 30 * 1000 )
#define TI_TAF_APS_CDATA_HRPD_LOST_TIMER_LEN                ( 5 * 1000 )

/* Added by y00314741 for CDMA Iteration 11, 2015-3-24, begin */
#define TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER_LEN             ( 3 * 1000 )
/* Added by y00314741 for CDMA Iteration 11, 2015-3-24, end */

/* Added by y00314741 for CDMA Iteration 15, 2015-5-29, begin */
#define TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF_LEN   ( 16 *1000)
#define TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF_LEN   ( 16 *1000)
/* Added by y00314741 for CDMA Iteration 15, 2015-5-29, end */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum TAF_APS_TIMER_STATUS_ENUM
{
    TAF_APS_TIMER_STATUS_STOP,              /* ��ʱ��ֹͣ״̬ */
    TAF_APS_TIMER_STATUS_RUNING,            /* ��ʱ������״̬ */
    TAF_APS_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_APS_TIMER_STATUS_ENUM_U8;


enum TAF_APS_TIMER_ID_ENUM
{
    /* �û����ʱ�� */
    TI_TAF_APS_MS_ACTIVATING                    = MN_TIMER_CLASS_APS + 0x01,

    /* ���缤�ʱ�� */
    TI_TAF_APS_NET_ACTIVATING                   = MN_TIMER_CLASS_APS + 0x02,

    /* PDP MODIFY��ʱ�� */
    TI_TAF_APS_MS_MODIFYING                     = MN_TIMER_CLASS_APS + 0x03,

    /* �û�ȥ���ʱ�� */
    TI_TAF_APS_MS_DEACTIVATING                  = MN_TIMER_CLASS_APS + 0x04,

    /* ����ͳ����ض�ʱ�� */
    TI_TAF_APS_DSFLOW_REPORT                    = MN_TIMER_CLASS_APS + 0x05,
    TI_TAF_APS_DSFLOW_WRITE_NV                  = MN_TIMER_CLASS_APS + 0x06,

    /* ��ͣPDP���ʱ����AT&T��������(PDP��������) */
    TI_TAF_APS_LIMIT_PDP_ACT                    = MN_TIMER_CLASS_APS + 0x08,

#if ( FEATURE_ON == FEATURE_LTE )
    /* L4A��Ϣ������ʱ�� */
    TI_TAF_APS_WAIT_SET_CGDCONT_CNF             = MN_TIMER_CLASS_APS + 0x101,
    TI_TAF_APS_WAIT_SET_CGDSCONT_CNF            = MN_TIMER_CLASS_APS + 0x102,
    TI_TAF_APS_WAIT_SET_CGTFT_CNF               = MN_TIMER_CLASS_APS + 0x103,
    TI_TAF_APS_WAIT_SET_CGAUTO_CNF              = MN_TIMER_CLASS_APS + 0x104,
    TI_TAF_APS_WAIT_SET_CGANS_CNF               = MN_TIMER_CLASS_APS + 0x105,
    TI_TAF_APS_WAIT_SET_CGEQOS_CNF              = MN_TIMER_CLASS_APS + 0x106,
    TI_TAF_APS_WAIT_SET_AUTHDATA_CNF            = MN_TIMER_CLASS_APS + 0X107,

    TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF           = MN_TIMER_CLASS_APS + 0x108,
    TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF          = MN_TIMER_CLASS_APS + 0x109,
    TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF            = MN_TIMER_CLASS_APS + 0x10A,
    TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF           = MN_TIMER_CLASS_APS + 0x10B,

    TI_TAF_APS_WAIT_GET_LTE_CS_CNF              = MN_TIMER_CLASS_APS + 0x10C,
    TI_TAF_APS_WAIT_SET_PDPROF_CNF              = MN_TIMER_CLASS_APS + 0x10D,
    TI_TAF_APS_WAIT_GET_CEMODE_CNF              = MN_TIMER_CLASS_APS + 0x10E,


#endif

    TI_TAF_APS_CDATA_ESTING                     = MN_TIMER_CLASS_APS + 0x200,
    TI_TAF_APS_CDATA_DISCING                    = MN_TIMER_CLASS_APS + 0x201,
    TI_TAF_APS_CDATA_DORMANT                    = MN_TIMER_CLASS_APS + 0x202,
    TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD    = MN_TIMER_CLASS_APS + 0x203,
    TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL  = MN_TIMER_CLASS_APS + 0x204,
    TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF    = MN_TIMER_CLASS_APS + 0x205,
    TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF  = MN_TIMER_CLASS_APS + 0x206,
    TI_TAF_APS_CDATA_HRPD_LOST_TIMER            = MN_TIMER_CLASS_APS + 0x207,
    TI_TAF_APS_CDATA_EPZID_HAT                  = MN_TIMER_CLASS_APS + 0x208,
    TI_TAF_APS_CDATA_EPZID_HT                   = MN_TIMER_CLASS_APS + 0x209,
    /* Added by y00314741 for CDMA Iteration 11, 2015-3-24, begin */
    TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER         = MN_TIMER_CLASS_APS + 0x20A,
    /* Added by y00314741 for CDMA Iteration 11, 2015-3-24, end */
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-29, begin */
    TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF     = MN_TIMER_CLASS_APS + 0X20B,
    TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF     = MN_TIMER_CLASS_APS + 0X20C,
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-29, end */

    TI_TAF_APS_TIMER_BUTT
};
typedef VOS_UINT32  TAF_APS_TIMER_ID_ENUM_UINT32;

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


typedef struct
{
    HTIMER                              hTimer;                                 /* ��ʱ��������ָ�� */
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId;                              /* ��ʱ����ID */
    VOS_UINT32                          ulPara;                                 /* ��ʱ��������PDPID */
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;                          /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           aucReserve[3];                          /* ����λ */
} TAF_APS_TIMER_CTX_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;      /* ��ʱ��״̬ */
    VOS_UINT8                           aucReserve[3];      /* ����λ */
    VOS_UINT32                          ulPara;             /* ��ʱ������ */
    VOS_UINT32                          ulLen;              /* ��ʱ��ʱ�� */
}TAF_APS_TIMER_INFO_STRU;

typedef struct
{
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId;          /* TimerID */
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;        /* ��ʱ������ */
}TAF_APS_TIMER_PRECISION_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 �ⲿ������������
*****************************************************************************/
/* Deleted by wx270776 for OM�ں�, 2015-6-28, begin */
/* Deleted by wx270776 for OM�ں�, 2015-6-28, end */


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID  TAF_APS_InitAllTimers(
    TAF_APS_TIMER_CTX_STRU              *pstApsTimerCtx
);

VOS_VOID  TAF_APS_StartTimer(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT32                          ulPara
);

VOS_VOID  TAF_APS_StopTimer(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
);

VOS_VOID  TAF_APS_StopAllTimer( VOS_VOID );

VOS_VOID  TAF_APS_StopPdpAllTimer(
    VOS_UINT32                          ulPara
);

TAF_APS_TIMER_STATUS_ENUM_U8  TAF_APS_GetTimerStatus(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
);

VOS_UINT32  TAF_APS_BuildTmrParaByCtrlHdr(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulClientId
);
VOS_VOID TAF_APS_GetRemainTimerLen(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara,
    VOS_UINT32                         *pulRemainTimeLen
);


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

#endif /* end of TafApsTimerMgmt.h */
