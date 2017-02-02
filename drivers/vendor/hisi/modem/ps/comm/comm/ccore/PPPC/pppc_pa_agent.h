

#ifndef _PPPC_PA_AGENT_H
#define _PPPC_PA_AGENT_H

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TTFComm.h"
#include "PsTypeDef.h"
#include "PsCommonDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MSPS_PID_PA_AGENT MSPS_PID_PPPC

/* reservation label���������Ϊ16 */
#define PA_AGENT_MAX_RESERVATION_NUM                        (16)

/* �������֧��16��reservationͬʱopen,�����������16��open��Ϣ��16��close��Ϣ */
#define PA_AGENT_MAS_RESERV_MSG_BUFFER_NUM                  (32)

#define PPPC_HRPD_PA_BEST_EFFORT                            (0xff)

#define PA_AGENT_MOVE_7_BIT                                 (7)
#define PA_AGENT_8_BIT                                      (8)
#define PA_AGENT_REV_LINK                                   (0)
#define PA_AGENT_FWD_LIN                                    (1)

/* TRLPResponseʱ��1000ms,C.S0063-A,chapter 2.5.5 protocol numeric constants */
#define PA_AGENT_TIMER_RLP_RESPONSE                         (1000)

/* 1Byte  | 1Byte          | 1Byte    | ...  */
/* msg id | transaction id | resv cnt | ...  */
#define PA_AGENT_DL_RESERV_MSG_LEN(ucResvCnt)               (ucResvCnt+3)

#define PA_AGENT_PUTCHAR(c, cp) { \
        *(cp) = (VOS_UINT8) (c); \
        (cp)++; \
    }

#define PA_AGENT_GETCHAR(c, cp) { \
        (c) = *(cp); \
        (cp)++; \
    }

#define PA_AGENT_SET_TRANSACTION_ID(c, cp) { \
        *(cp+1) = (VOS_UINT8) (c); \
    }

#define PA_AGENT_GET_TRANSACTION_ID(c, cp) { \
        (c) = *(cp+1); \
    }

#define PA_AGENT_GET_RESERVATION_COUNT(c, cp) { \
        (c) = *(cp+2); \
    }


#define PA_AGENT_SNP_MSG_DATA_OFFSET_LEN                    /*lint -e(545) -e(413)*/offsetof(SNPITF_MSG_DATA_STRU, aucMsgData)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/** ****************************************************************************
 * Name        : PA_AGENT_HRPD_RESERVATION_MSG_TYPE_ENUM_UINT8
 * Description : Enum to list all reservation messages
 *******************************************************************************/
enum PA_AGENT_HRPD_RESERVATION_MSG_TYPE_ENUM
{
    PA_AGENT_HRPD_RESERVATION_ON_REQ                         = 0x16,
    PA_AGENT_HRPD_RESERVATION_OFF_REQ                        = 0x17,
    PA_AGENT_HRPD_RESERVATION_ACCEPT                         = 0x18,
    PA_AGENT_HRPD_RESERVATION_REJECT                         = 0x19,
    PA_AGENT_HRPD_REV_RESERVATION_ON                         = 0x1A,
    PA_AGENT_HRPD_REV_RESERVATION_OFF                        = 0x1B,
    PA_AGENT_HRPD_FWD_RESERVATION_OFF                        = 0x22,
    PA_AGENT_HRPD_FWD_RESERVATION_ON                         = 0x23,
    PA_AGENT_HRPD_FWD_RESERVATION_ACK                        = 0x24,

    PA_AGENT_HRPD_RESERVATION_BUTT
};
typedef VOS_UINT8 PA_AGENT_HRPD_RESERVATION_MSG_TYPE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : PA_AGENT_HRPD_TIMER_TYPE_ENUM_UINT32
 * Description : Enum to list all timer
 *******************************************************************************/
enum PA_AGENT_HRPD_TIMER_TYPE_ENUM
{
    ID_PA_AGENT_HRPD_RLP_RESPONSE_TIME,

    ID_PA_AGENT_HRPD_TIMER_BUTT
};
typedef VOS_UINT32 PA_AGENT_HRPD_TIMER_TYPE_ENUM_UINT32;


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
 �ṹ��    : PA_AGENT_HRPD_APP_RESERV_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :struct for reservation information.
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucLink;             /* 1:fwd 0:rev */
    VOS_UINT8                                               ucReservLabel;
    VOS_UINT8                                               aucReserv1[2];
}PA_AGENT_HRPD_APP_RESERV_INFO_STRU;

/*****************************************************************************
 �ṹ��    : PA_AGENT_HRPD_RESERV_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :struct for app to manage reservation.
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucReservationCount;
    VOS_UINT8                                               ucIsEmergencyReserv;/* 1:�ǽ���Reserv 0:���� */
    VOS_UINT8                                               aucRsvd1[2];
    PA_AGENT_HRPD_APP_RESERV_INFO_STRU                      astReservInfo[PA_AGENT_MAX_RESERVATION_NUM];
}PA_AGENT_HRPD_RESERV_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : PA_AGENT_HRPD_RESERV_STATE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :struct for store reservation state.
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucReservLabel;
    PS_BOOL_ENUM_UINT8                                      enIsValid;
    VOS_UINT8                                               aucRsvd1[2];
}PA_AGENT_HRPD_RESERV_STATE_STRU;

/*****************************************************************************
 �ṹ��    : PA_AGENT_HRPD_RESERV_STATE_MNTN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :struct for maintain reservation state.
*****************************************************************************/
typedef struct
{
    PA_AGENT_HRPD_RESERV_STATE_STRU                         astFwdReservState[PA_AGENT_MAX_RESERVATION_NUM];
    PA_AGENT_HRPD_RESERV_STATE_STRU                         astRevReservState[PA_AGENT_MAX_RESERVATION_NUM];
    VOS_UINT8                                               ucRevReervOpenNum;
    VOS_UINT8                                               ucFwdReervOpenNum;
    VOS_UINT8                                               aucRsvd1[2];
    VOS_UINT8                                               ucMaxNumReservFwd;
    VOS_UINT8                                               ucMaxNumReservRev;
    VOS_UINT8                                               ucMaxNumOpenReservFwd;
    VOS_UINT8                                               ucMaxNumOpenReservRev;
}PA_AGENT_HRPD_RESERV_STATE_MNTN_STRU;

/*****************************************************************************
 �ṹ��    : PA_AGENT_HRPD_CONTEXT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :struct for context of PA AGENT.
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                                      enIsValid;
    VOS_UINT8                                               ucTimerId;
    VOS_UINT8                                               aucReserv1[2];
    HTIMER                                                  hRlpRespTimer;
    VOS_UINT8                                              *pucMsgDataPtr;      /* ��¼��Ϣ����ָ��,�ش�ʱʹ�� */
}PA_AGENT_HRPD_MSG_RESERV_MSG_BUFFER_STRU;

/*****************************************************************************
 �ṹ��    : PA_AGENT_HRPD_CONTEXT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :struct for context of PA AGENT.
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucReservTransacId;  /* ReservationON��ReservationOff��Ϣ�ķ��ͼ�¼ */
    VOS_UINT8                                               aucRsvd1[3];
    PA_AGENT_HRPD_RESERV_STATE_MNTN_STRU                    stReservMntn;
    PA_AGENT_HRPD_MSG_RESERV_MSG_BUFFER_STRU                astReservMsgBuff[PA_AGENT_MAS_RESERV_MSG_BUFFER_NUM];
}PA_AGENT_HRPD_CONTEXT_STRU;

/*****************************************************************************
 �ṹ��    : PA_AGENT_HRPD_RESERV_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :struct for store reesrvation infomation.
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucRevResvCnt;
    VOS_UINT8                                               ucFwdResvCnt;
    VOS_UINT8                                               aucRsvd1[2];
    VOS_UINT8                                               aucRevReservLabel[PA_AGENT_MAX_RESERVATION_NUM];
    VOS_UINT8                                               aucFwdReservLabel[PA_AGENT_MAX_RESERVATION_NUM];
}PA_AGENT_HRPD_RESERV_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID PPPC_HRPD_PaAgentInit(VOS_VOID);
VOS_VOID PA_AGENT_HRPD_SetMaxReservNum
(
    CTTF_PPP_HRPD_RESERVATIONS_IND_STRU    *pstReservationsInd
);
VOS_VOID PPPC_HrpdPaAgentRcvCloseReservProc(struct MsgCB * pMsg);
VOS_VOID PPPC_HrpdPaAgentRcvOpenReservProc(struct MsgCB * pMsg);
VOS_VOID PPPC_HRPD_PaAgentRcvReservDlMsgProc(struct MsgCB * pMsg);
VOS_VOID PPPC_HRPD_PaAgentSndReservOnReq
(
    PA_AGENT_HRPD_RESERV_CTRL_STRU     *pstReservInfo
);
VOS_VOID PPPC_HRPD_PaAgentSndReservOffReq
(
    PA_AGENT_HRPD_RESERV_CTRL_STRU     *pstReservInfo
);
VOS_UINT8 PPPC_HRPD_PaAgentGetResvLabel
(
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16   enAppType
);
VOS_VOID PPPC_HRPD_PaAgentRlpTimeout(VOS_UINT32 ulTimerName);






#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif








#ifdef    __cplusplus
 }
#endif    /* end of __cplusplus */

#endif