

#ifndef __TAFXPDSTIMERMGMT_H__
#define __TAFXPDSTIMERMGMT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "MnComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_XPDS_CTX_MAX_TIMER_NUM                          (10)

/*����ʱ������ת����DOPRA��ʱ������ĺ��룬��Ҫ����1000 */
#define TIMER_S_TO_MS_1000                                  (1000)

#define TI_TAF_XPDS_WAIT_AT_DATA_CALL_IND_TIMER_LEN         (20  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_AT_BINDUP_IND_TIMER_LEN            (40  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_MPC_START_POS_RSP_TIMER_LEN        (8  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_MPC_POS_REPORT_RSP_TIMER_LEN       (8  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN                  (35 * TIMER_S_TO_MS_1000)

#define TI_TAF_XPDS_WAIT_GPS_ANSWER_NI_REQ_CNF_TIMER_LEN    (25 * TIMER_S_TO_MS_1000)

#define TI_TAF_XPDS_WAIT_XCC_DATA_CAll_CONNECT_CNF_TIMER_LEN (5  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_XCC_DATA_CAll_STATUS_IND_TIMER_LEN (5  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_XCC_ANSWER_CAll_CNF_TIMER_LEN      (5  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_XCC_CALL_CONN_IND_TIMER_LEN        (5  * TIMER_S_TO_MS_1000)

#define TI_TAF_XPDS_WAIT_CAS_DATA_IND_L1_POS_TIMER_LEN      (5  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_CAS_CNF_TIMER_LEN        (13 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_ALM_EPHI_RESP_TIMER_LEN  (5  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_GPS_LOC_RESP_TIMER_LEN   (5  * TIMER_S_TO_MS_1000)

#define TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM_TIMER_LEN          (13 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_REQ_LOC_RSP_TIMER_LEN  (13 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PDE_ASSIST_DATA_CNF_TIMER_LEN        (5  * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_AQU_ASSI_TIMER_LEN     (13 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_REQ_AFTER_PPM_TIMER_LEN          (5  * TIMER_S_TO_MS_1000)

#define TI_TAF_XPDS_IS801_SESSION_TIMER_LEN                     (32 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_PDE_MSB_DATA_TIMER_LEN                 (25 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO_DEFAULT_TIMER_LEN  0
#define TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF_TIMER_LEN          (20 * TIMER_S_TO_MS_1000)
#define TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_AT_GPS_STOP_TIMER_LEN    (5 * TIMER_S_TO_MS_1000)


#define TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_MS_INFO_TIMER_LEN          (13 * TIMER_S_TO_MS_1000)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum TAF_XPDS_TIMER_ID_ENUM
{
    TI_TAF_XPDS_WAIT_AT_DATA_CALL_IND   = 0,
    TI_TAF_XPDS_WAIT_AT_BINDUP_IND,

    TI_TAF_XPDS_WAIT_MPC_START_POS_RSP,
    TI_TAF_XPDS_WAIT_MPC_POS_REPORT_RSP,

    TI_TAF_XPDS_WAIT_GPS_ANSWER_NI_REQ_CNF,

    /* Added by x00314862 for CDMA XPDS Iteration 2 2015-9-4 begin */
    TI_TAF_XPDS_NI_POS_REPORT_INTERNAL,
    TI_TAF_XPDS_WAIT_RSP_PDE_PSEUDORANGE_REQ_QUALITY,
    TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO,  /* ���ھ��Ȳ��Զ�ʱ�� */
    TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF,             /* �Ⱥ�GPSα�ඨʱ�� */
    /* Added by x00314862 for CDMA XPDS Iteration 2 2015-9-4 end */

    TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF,
    TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF,
    TI_TAF_XPDS_WAIT_PDE_MSB_DATA,

    TI_TAF_XPDS_IS801_SESSION,  /* �й���������: T8 IS 801�Ự��ʱ�� */

    TI_TAF_XPDS_WAIT_XCC_DATA_CAll_CONNECT_CNF,
    TI_TAF_XPDS_WAIT_XCC_DATA_CAll_STATUS_IND,
    TI_TAF_XPDS_WAIT_XCC_ANSWER_CAll_CNF,
    TI_TAF_XPDS_WAIT_XCC_CALL_CONN_IND,
    TI_TAF_XPDS_WAIT_CAS_DATA_IND_L1_POS,
    TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_CAS_CNF,
    TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_ALM_EPHI_RESP,
    TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_GPS_LOC_RESP,

    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_REQ_LOC_RSP,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PDE_ASSIST_DATA_CNF,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_MS_INFO,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_AQUI_ASSI,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_REQ_AFTER_PPM,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_COMPLETE_NI_QUALITY,
    TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PPM_COMPLETE_NI_QUALITY,
    TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_AT_GPS_STOP,

    TI_TAF_XPDS_TIMER_BUTT
};
typedef VOS_UINT32  TAF_XPDS_TIMER_ID_ENUM_UINT32;
enum TAF_XPDS_TIMER_STATUS_ENUM
{
    TAF_XPDS_TIMER_STATUS_STOP          = 0,                /* ��ʱ��ֹͣ״̬ */
    TAF_XPDS_TIMER_STATUS_RUNING,                           /* ��ʱ������״̬ */
    TAF_XPDS_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_XPDS_TIMER_STATUS_ENUM_UINT8;


enum TAF_XPDS_TIMER_START_RESULT_ENUM
{
    TAF_XPDS_TIMER_START_SUCCEE         = 0,                /* ��ʱ�������ɹ� */
    TAF_XPDS_TIMER_START_FAILURE,                           /* ��ʱ������ʧ�� */

    TAF_XPDS_TIMER_START_BUTT
};
typedef VOS_UINT8 TAF_XPDS_TIMER_START_RESULT_ENUM_UINT8;
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
    HTIMER                              hTimer;             /* ��ʱ��������ָ�� */
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId;          /* ��ʱ����ID */
    TAF_XPDS_TIMER_STATUS_ENUM_UINT8    enTimerStatus;      /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           aucReserve[3];      /* ����λ */
} TAF_XPDS_TIMER_CTX_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    TAF_XPDS_TIMER_STATUS_ENUM_UINT8    enTimerStatus;      /* ��ʱ��״̬ */
    VOS_UINT8                           aucReserve[3];      /* ����λ */
    VOS_UINT32                          ulLen;              /* ��ʱ��ʱ�� */
}TAF_XPDS_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/
/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enMsgId;
    TAF_XPDS_TIMER_STATUS_ENUM_UINT8    enTimerStatus;      /* ��ʱ��״̬ */
    VOS_UINT8                           aucReserve[3];      /* ����λ */
    VOS_UINT32                          ulLen;              /* ��ʱ��ʱ�� */

}TAF_XPDS_TIMER_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_XPDS_TIMER_MSG_DATA             stMsgData;
}TafXpdsTimerMgmt_MSG;


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID TAF_XPDS_SndOmTimerStatus(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen,
    TAF_XPDS_TIMER_STATUS_ENUM_UINT8    enTimerStatus
);

VOS_VOID TAF_XPDS_InitAllTimers(
    TAF_XPDS_TIMER_CTX_STRU            *pstXPDSTimerCtx
);

TAF_XPDS_TIMER_START_RESULT_ENUM_UINT8  TAF_XPDS_StartTimer(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID TAF_XPDS_StopTimer(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId
);

TAF_XPDS_TIMER_STATUS_ENUM_UINT8  TAF_XPDS_GetTimerStatus(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId
);

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

#endif



