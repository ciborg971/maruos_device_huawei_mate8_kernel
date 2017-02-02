

#ifndef __TAF_XPDS_SND_INTERNAL_MSG_H__
#define __TAF_XPDS_SND_INTERNAL_MSG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafXpdsCtx.h"

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

enum TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM
{
    ID_TAF_XPDS_XPDS_UP_LINK_CTRL_REQ                       = 0x0000, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU */
    ID_TAF_XPDS_XPDS_UP_LINK_CTRL_CNF                       = 0x0001, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU */
    ID_TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ                 = 0x0002, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU*/
    ID_TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND                  = 0x0003, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU*/
    ID_TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP             = 0x0004, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP_STRU*/
    ID_TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP            = 0x0005, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU*/

    ID_TAF_XPDS_XPDS_CP_LINK_START_REQ                      = 0x0006, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_CP_LINK_PROC_START_REQ_STRU */
    ID_TAF_XPDS_XPDS_CP_LINK_RESULT_IND                     = 0x0007, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU */

    ID_TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ                  = 0x0008, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU */
    ID_TAF_XPDS_XPDS_PDE_PROC_RSLT_IND                      = 0x0009, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU */
    ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND                   = 0x000A, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU */
    ID_TAF_XPDS_XPDS_PDE_PROC_START_REQ                     = 0x000B, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU */
    ID_TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION       = 0x000C, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU */
    ID_TAF_XPDS_XPDS_INT_XSMS_REFRESH_MR_TRACK_SESSION      = 0x000D, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION_STRU */

    ID_TAF_XPDS_XPDS_PPM_COMPLETE_NI                        = 0x000E, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_PPM_COMPLETE_MSG_STRU*/

    ID_TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND    = 0x000F, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU */
    ID_TAF_XPDS_XPDS_CP_PDE_PROC_RSLT_IND                   = 0x0010, /* _H2ASN_MsgChoice TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU */


    ID_TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_BUTT  = 0xFFFF
};
typedef VOS_UINT32 TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32;
enum TAF_XPDS_BIND_SERVER_ERROR_CAUSE_ENUM
{
    TAF_XPDS_BIND_SERVER_NO_ERROR,

    TAF_XPDS_BIND_SERVER_MPC_CONNECT_FAIL,
    TAF_XPDS_BIND_SERVER_PDE_CONNECT_FAIL,

    TAF_XPDS_BIND_SERVER_ERROR_CAUSE_BUTT,
};
typedef VOS_UINT8 TAF_XPDS_BIND_SERVER_ERROR_CAUSE_ENUM_UINT8;


enum TAF_XPDS_SERVER_BIND_OPER_ENUM
{
    TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET,
    TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET,

    TAF_XPDS_SERVER_BIND_OPER_BUTT
};
typedef VOS_UINT8 TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8;


enum TAF_XPDS_MPC_OPER_TYPE_ENUM
{
    TAF_XPDS_MPC_OPER_START_POS_REQ = 0x01,
    TAF_XPDS_MPC_OPER_POS_REPORT,

    TAF_XPDS_MPC_OPER_BUTT,
};
typedef VOS_UINT32 TAF_XPDS_MPC_OPER_TYPE_ENUM_UINT32;

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
    VOS_MSG_HEADER                                                                                  /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enMpcBindOpt;
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enPdeBindOpt;
    VOS_UINT8                                               aucReserved[2];
} TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                                                  /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enRslt;
}TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_FIX_MODE_ENUM_UINT8                            enFixMode;
    VOS_UINT8                                               aucRsv[3];
}TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_FIX_MODE_ENUM_UINT8                            enFixMode;
    VOS_UINT8                                               aucRsv[3];
}TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
}TAF_XPDS_XPDS_CP_LINK_PROC_START_REQ_STRU;

/* Added by x00314862 for CDMA XPDS Iteration 2 2015-8-27 begin */
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enRslt;
}TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU;
/* Added by x00314862 for CDMA XPDS Iteration 2 2015-8-27 end */


typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT32                                              ulDataMask;
    TAF_XPDS_CALL_TYPE_ENUM_UINT8                           enCallType;
    VOS_UINT8                                               aucRsv[3];
}TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_MPC_OPER_TYPE_ENUM_UINT32                      enMpcOperation;
}TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_MPC_OPER_TYPE_ENUM_UINT32                      enMpcOperation;
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enMpcOperRslt;
}TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_MPC_START_POS_RSP_STRU                         stStartPosRsp;
}TAF_XPDS_XPDS_INT_RCV_MPC_START_POS_RESP_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_MPC_POS_REPORT_RSP_STRU                        stPosReportRsp;
}TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
}TAF_XPDS_XPDS_INT_XSMS_CANCEL_NI_TRACK_SESSION_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32   enMsgId;                                /* _H2ASN_Skip */
}TAF_XPDS_XPDS_PPM_COMPLETE_MSG_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enAbortScene;
}TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* _H2ASN_Skip */
    TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_ENUM_UINT8             enCauseCode;
    VOS_UINT8                                               aucRsv[3];
}TAF_XPDS_XPDS_INT_XSMS_REFRESH_MR_TRACK_SESSION_STRU;





/* Added by A00903922 for CDMA XPDS Iteration 2 2015-8-27 begin */
/*****************************************************************************
 �ṹ��    : TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU
 �ṹ˵��  : The message for cp link proc result
 1.��    ��   : 2015��09��22��
   ��    ��   : a00903922
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enRslt;
}TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU;

/* Added by A00903922 for CDMA XPDS Iteration 2 2015-8-27 end */


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
    TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32               enMsgId; /* _H2ASN_MsgChoice_Export TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                                               aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_XPDS_XPDS_INTERNAL_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_XPDS_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_XPDS_INTERNAL_MSG_DATA          stMsgData;
}TafXpdsSndInternalMsg_MSG;

/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID TAF_XPDS_SndInternalServerBindOperReq(
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enMpcBindOpt,
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enPdeBindOpt
);

VOS_VOID TAF_XPDS_SndInternalServerBindRsltCnf(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enRslt
);

VOS_VOID TAF_XPDS_SndInternalPdeProcStartReq(
    TAF_XPDS_FIX_MODE_ENUM_UINT8                            enFixMode
);

/* Added by x00314862 for CDMA XPDS Iteration 2 2015-8-27 begin */
VOS_VOID TAF_XPDS_SndInternalPdeProcRsltInd(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enRslt
);
/* Added by x00314862 for CDMA XPDS Iteration 2 2015-8-27 end */

VOS_VOID TAF_XPDS_SndInternalCpPdeProcRsltInd(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enRslt
);

VOS_VOID TAF_XPDS_SndInternalForwardPdeDataInd(
    VOS_UINT32                                              ulDataMask,
    TAF_XPDS_CALL_TYPE_ENUM_UINT8                           enCallType
);


VOS_VOID TAF_XPDS_SndInternalStartMpcProcess(
    TAF_XPDS_MPC_OPER_TYPE_ENUM_UINT32                      enMpcOperation
);

VOS_VOID TAF_XPDS_SndInternalMpcRslt(
    TAF_XPDS_MPC_OPER_TYPE_ENUM_UINT32                      enMpcOperation,
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enMpcOperRslt
);

VOS_VOID TAF_XPDS_SndInternalMpcStartPosResp(
    TAF_XPDS_MPC_START_POS_RSP_STRU                         *pstStartPosRsp
);

VOS_VOID TAF_XPDS_SndInternalMpcPosReportResp(
    TAF_XPDS_MPC_POS_REPORT_RSP_STRU                        *pstPosReportRsp
);

VOS_VOID TAF_XPDS_SndInternalXsmsCancelNiTracking(
    VOS_VOID
);

VOS_VOID TAF_XPDS_SndInternalXsmsRefreshMrTracking(
    TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_ENUM_UINT8             enCauseCode
);

VOS_VOID TAF_XPDS_SndInternalCpPdeProcStartReq(
    VOS_VOID
);

extern VOS_VOID TAF_XPDS_SndInternalPpmCompleteMsg(
    VOS_VOID
);

VOS_VOID TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enAbortScene
);

VOS_UINT32 TAF_XPDS_SndControlPlaneLinkStart_CpLinkCtrl(
   VOS_VOID
);

extern VOS_UINT32 TAF_XPDS_SndInternalCpLinkResultMsg_CpLinkCtrl(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 enRslt
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

#endif /* end of CnasXsdSndInternalMsg.h */
