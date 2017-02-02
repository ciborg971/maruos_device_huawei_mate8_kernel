

#ifndef __TAFAPSMNTN_H__
#define __TAFAPSMNTN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafApsTimerMgmt.h"
#include "TafApsCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* ������Ϣ��ά�ɲ�[0x0800, 0x0899] */
enum TAF_PS_APS_MNTN_MSG_ID_ENUM
{
    ID_MSG_TAF_PS_APS_MNTN_DFS_INFO                         = TAF_PS_MSG_ID_BASE + 0x0800,  /* _H2ASN_MsgChoice TAF_APS_MNTN_DFS_INFO_STRU */

    ID_MSG_TAF_PS_CDATA_EPDSZID_CHANGED                     = TAF_PS_MSG_ID_BASE + 0x0801,  /* _H2ASN_MsgChoice TAF_APS_EPDSZID_INFO_STRU */

    ID_MSG_TAF_PS_APS_FSM_INFO                              = TAF_PS_MSG_ID_BASE + 0x0802,  /* _H2ASN_MsgChoice TAF_APS_FSM_MNTN_INFO_STRU*/

    ID_MSG_TAF_PS_APS_PDP_ENTITY                            = TAF_PS_MSG_ID_BASE + 0x0803,  /* _H2ASN_MsgChoice TAF_APS_PDP_ENTITY_STRU*/

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-8, begin */
    ID_MSG_TAF_APS_LOG_READ_NV_INFO_IND                     = TAF_PS_MSG_ID_BASE + 0x0804,  /* _H2ASN_MsgChoice TAF_APS_LOG_READ_NV_INFO_IND_STRU*/
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-8, end */

    ID_MSG_TAF_PS_MNTN_BUTT

};
typedef VOS_UINT32 TAF_PS_APS_MNTN_MSG_ID_ENUM_UINT32;


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
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          enMsgId;            /* ��Ϣ����     */  /* _H2ASN_Skip */
    TAF_APS_SWITCH_DDR_RATE_INFO_STRU   stDfsInfo;
}TAF_APS_MNTN_DFS_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          enMsgId;            /* ��Ϣ����     */  /* _H2ASN_Skip */
    TAF_APS_CDATA_EPDSZID_CTX_STRU      stEpdszidInfo;
}TAF_APS_EPDSZID_INFO_STRU;


typedef struct
{
    /* ״̬����ʶ */
    TAF_APS_FSM_ID_ENUM_UINT32          enFsmId;

    /* ״̬ */
    VOS_UINT32                          ulState;

}TAF_APS_FSM_STATUS_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          enMsgId;            /* ��Ϣ����     */  /* _H2ASN_Skip */

    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucSuspendStatus;
    VOS_UINT8                           ucAllowDefPdnTeardownFlg;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT32                          ulExist1XService;                       /* ��¼�Ƿ����1X�����ݷ��� */
    VOS_UINT32                          ulFinishClSearch;                       /* CLģʽ�¼�¼�Ƿ����DO��LTE������ */

    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;

    /* ����ǰ״̬��״̬ */
    TAF_APS_FSM_STATUS_INFO_STRU        stPriFsmInfo;

    /* �����״̬��״̬ */
    TAF_APS_FSM_STATUS_INFO_STRU        stCurrFsmInfo;

}TAF_APS_FSM_MNTN_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          enMsgId;            /* ��Ϣ����     */  /* _H2ASN_Skip */

    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucLinkedNsapi;      /*�������NSAPI,�����������Ƕ��μ���,��˳�Ա��Ч*/
    APS_PDP_ACT_TYPE_ENUM_UINT8         enActType;            /*��������*/
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode;
    TAF_APS_CLIENT_INFO_STRU            stClientInfo;
    APS_PDP_ADDR_ST                     PdpAddr;

}TAF_APS_PDP_ENTITY_STRU;

/* Added by y00322978 for CDMA Iteration 17, 2015-7-8, begin */
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_PS_APS_MNTN_MSG_ID_ENUM_UINT32      enMsgId;                            /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT16                              enNvItem;
    VOS_UINT16                              usNvDataLength;
    VOS_UINT8                               aucNvInfo[4];/* NV���� */
}TAF_APS_LOG_READ_NV_INFO_IND_STRU;
/* Added by y00322978 for CDMA Iteration 17, 2015-7-8, end */

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    TAF_PS_APS_MNTN_MSG_ID_ENUM_UINT32  ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_PS_APS_MNTN_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_PS_APS_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_APS_MNTN_REQ;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_APS_MNTN_REQ                    stMsgReq;
}TafApsMntn_MSG;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID DIAG_TraceReport(VOS_VOID *pMsg);

VOS_VOID  TAF_APS_TraceSyncMsg(
    VOS_UINT32                          ulMsgId,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLength
);

VOS_VOID  TAF_APS_TraceApsEvt(
    VOS_UINT32                          ulEvtId,
    VOS_UINT32                          ulLength,
    VOS_UINT8                          *pucData
);

VOS_VOID  TAF_APS_TraceTimer(
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus,
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT32                          ulPara
);

VOS_VOID TAF_APS_TraceEpdszidInfo(VOS_VOID);

/* Added by y00314741 for CDMA Iteration 11, 2015-3-30, begin */

VOS_VOID  TAF_APS_LogPdpEntityInfo(
    VOS_UINT8                           ucPdpId
);

VOS_VOID  TAF_APS_LogFsmMntnInfo(
    TAF_APS_FSM_STATUS_INFO_STRU       *pstPriFsmInfo,
    TAF_APS_FSM_STATUS_INFO_STRU       *pstCurrFsmInfo
);
/* Added by y00314741 for CDMA Iteration 11, 2015-3-30, end */


VOS_VOID  TAF_APS_SndOmDfsInfo(TAF_APS_SWITCH_DDR_RATE_INFO_STRU *pstSwitchDdrInfo);

/* Added by y00322978 for CDMA Iteration 17, 2015-7-8, begin */
VOS_VOID TAF_APS_LogReadNVInfo(
    VOS_UINT16                              enNvItem,
    VOS_UINT16                              usNvDataLength,
    VOS_UINT32                              ulPid,
    VOS_UINT8                              *pucData
);
/* Added by y00322978 for CDMA Iteration 17, 2015-7-8, end */
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

#endif /* end of TafApsMntn.h */

