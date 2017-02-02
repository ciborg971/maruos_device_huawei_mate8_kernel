/******************************************************************************


        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmMrrcPubInterface.h
    Description :
    History     :
      1.  zangyalan 57968  2008-09-04  Draft Enact
      2.
******************************************************************************/
#ifndef __NASEMMMRRCPUBINTERFACE_H__
#define __NASEMMMRRCPUBINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "LRrcLNasInterface.h"



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
#define NAS_EMM_MRRC_BIT_SLCT               1
#define NAS_EMM_MRRC_BIT_NO_SLCT            0


#define NAS_EMM_GIM_VOS_MSG_HEADER_LEN       20

#define NAS_EMM_MRRC_DATA_REQ_LEN(CnMsgLen)  (NAS_EMM_MSG_ID_LEN + CnMsgLen + NAS_RRC_EST_CAUSE_LEN +NAS_RRC_EST_MSG_TYPE_LEN)

#define NAS_EMM_MRRC_CONNECT_FAIL_IND_LEN    (NAS_EMM_GIM_VOS_MSG_HEADER_LEN + NAS_EMM_MSG_ID_LEN + sizeof(LRRC_LNAS_EST_RESULT_ENUM_UINT32))

#define NAS_LMM_OPID                          0

#define NAS_EMM_SetNormalServiceRelCause(ucCause)      (g_stEmmMrrcCtrl.ulRelCause = ucCause)
#define NAS_EMM_GetNormalServiceRelCause()             (g_stEmmMrrcCtrl.ulRelCause)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_LMM_BARRED_IND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : nas�ڷ����ͷ�����ʱ,ָʾ��ǰʹ�õ�С���Ƿ�bar
*****************************************************************************/
enum NAS_LMM_BARRED_IND_ENUM
{
    NAS_LMM_NOT_BARRED                   = 0,                                    /* ԭС��û�б�barred */
    NAS_LMM_BARRED                       = 1,                                    /* ԭС����barred */
    NAS_NAS_BARRED_IND_BUTT
};
typedef VOS_UINT32 NAS_LMM_BARRED_IND_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_EMM_MSG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : NAS�ڽ������ӽ�������ʱ���͵���Ϣ����
*****************************************************************************/
enum NAS_EMM_MSG_TYPE_ENUM
{
    NAS_EMM_MSG_ATTACH_REQ               = 0x01,    /*attach message type*/
    NAS_EMM_MSG_ATTACH_CMP               ,
    NAS_EMM_MSG_DETACH_REQ               ,          /*detach message type*/
    NAS_EMM_MSG_DETACH_ACP               ,
    NAS_EMM_MSG_LOAD_BALANCING_TAU       ,          /*load balancing tau message type*/
    NAS_EMM_MSG_NOT_LOAD_BALANCING_TAU   ,
    NAS_EMM_MSG_TAU_CMP                  ,
    NAS_EMM_MSG_SERVICE_REQ              ,          /*service message type*/
    NAS_EMM_MSG_GUTI_CMP                 ,
    NAS_EMM_MSG_IDEN_RSP                 ,
    NAS_EMM_MSG_AUTH_RSP                 ,
    NAS_EMM_MSG_AUTH_FAIL                ,
    NAS_EMM_MSG_SMC_COMPL                ,
    NAS_EMM_MAS_SMC_REJ                  ,
    NAS_EMM_NAS_STATUS                   ,
    NAS_EMM_NAS_UPLINK_NAS_TRANSPORT     ,          /*uplink NAS transport  2011-11-15*/
    NAS_EMM_MSG_EXTENDED_SERVICE_REQ     ,
    NAS_EMM_MSG_ESM                      ,
    NAS_EMM_MSG_TC                       ,
    NAS_EMM_NAS_UPLINK_GENERIC_NAS_TRANSPORT,       /*uplink generic NAS transport*/
    NAS_EMM_MSG_OTHER                    ,
    NAS_EMM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 NAS_EMM_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_EMM_NORMALSERVICES_REL_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����REG+NORAML_SERVICE��REG+ATTEMPT_TO_UPDATE_MM״̬�ͷ���·ԭ��ö��
*****************************************************************************/
enum NAS_EMM_NORMALSERVICE_REL_CAUSE_ENUM
{
    NAS_EMM_NORMALSERVICE_REL_CAUSE_NULL           = 0,
    NAS_EMM_NORMALSERVICE_REL_CAUSE_EPSONLY_2,
    NAS_EMM_NORMALSERVICE_REL_CAUSE_EPSONLY_161722,
    NAS_EMM_NORMALSERVICE_REL_CAUSE_EPSONLY_18,

    NAS_EMM_NORMALSERVICE_REL_CAUSE_BUTT,
};
typedef VOS_UINT32 NAS_EMM_NORMALSERVICE_REL_CAUSE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*MRRCģ�������ģ���ԭ��ӿ�******************************/
/* The Struct from other EMM module to MRRC for sending UL user data */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;        /* ��ϢId */
    LRRC_LNAS_EST_CAUSE_ENUM_UINT32     enEstCaue;      /*��������ԭ��*/
    LRRC_LNAS_CALL_TYPE_ENUM_UINT32      enCallType;     /*call type*/
    LRRC_LMM_DATA_CNF_ENUM_UINT32       enDataCnf;      /*�Ƿ���Ҫȷ�Ϸ���*/
    VOS_UINT32                          ulEsmMmOpId;
    VOS_UINT32                          ulEmmLppOrSsOpId;   /*Emm��Lpp����Ss֮���OpIdά��*/
    VOS_UINT32                          ulLppSsFlag;        /* 0:��ʾLPP��1��ʾSS */
    NAS_EMM_MSG_TYPE_ENUM_UINT32        enEmmMsgType;   /*��������ʱ����Ϣ����*/
    LRRC_LNAS_MSG_STRU                    stNasMsg;       /* ������ʲônas��Ϣ */

}NAS_EMM_MRRC_DATA_REQ_STRU;

/* emm�ڲ�ģ��������rrc����ʧ�ܺ�mrrc��emm�ڲ�����ģ��Ļظ� */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;   /* ��Ϣ�ṹ */
    LRRC_LNAS_EST_RESULT_ENUM_UINT32      enEstResult; /*���ӽ������*/
}NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU;

/*The Struct from other EMM module to MRRC for release RRC CONN*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;   /* ��Ϣ�ṹ */
    NAS_LMM_BARRED_IND_ENUM_UINT32       enBarInd;
}NAS_EMM_MRRC_REL_REQ_STRU;

/*The Struct from MRRC to other EMM module for release RRC CONN CNF*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32          ulMsgId;        /* ��Ϣ�ṹ */
    VOS_UINT32          ulReserved;
}NAS_EMM_MRRC_REL_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_EMM_MRRC_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NAS_EMM_MRRC_CTRL_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
   NAS_EMM_NORMALSERVICE_REL_CAUSE_ENUM_UINT32     ulRelCause;
}NAS_EMM_MRRC_CTRL_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_EMM_MRRC_CTRL_STRU                  g_stEmmMrrcCtrl;

/*****************************************************************************
  8 Function Extern
*****************************************************************************/
/*MRRCģ���PUBLICģ��ĺ����ӿ�*****************************/
/*�ڷ�RRC_CONN_INIT��״̬���κ�״̬���յ�MRRC_DATA_REQ��Ϣ */
extern VOS_UINT32 NAS_EMM_MsNoRrcConnInitSsAllMsgMrrcDataReq(VOS_UINT32 ulMsgId, VOS_VOID *pMsgStru);
extern VOS_VOID  NAS_EMM_SndUplinkNasMsg
(
    VOS_VOID *pMsgStru
);

/*��RRC����״̬��Ϊ����̬*/
extern VOS_VOID  NAS_EMM_ChangeRrcConnStateToEstSignal( VOS_VOID );
extern VOS_UINT32  NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgRabmRelReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);


/*��RRC����״̬��Ϊ����������*/
extern VOS_VOID  NAS_EMM_ChangeRrcConnStateToEsting( VOS_VOID );
extern VOS_VOID  NAS_EMM_ChangeRrcConnStateToEstData( VOS_VOID );
/*MRRCģ���ʼ������*/
extern VOS_VOID NAS_EMM_MrrcInit(VOS_VOID);
extern VOS_VOID NAS_EMM_FreeMrrcDyn( VOS_VOID );
extern VOS_UINT32  NAS_EMM_MsRrcRelInitSsWaitRelCnfMsgMmcCoverageLostInd(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg);

extern VOS_VOID    NAS_EMM_RelReq(NAS_LMM_BARRED_IND_ENUM_UINT32 enBarStatus);
extern VOS_VOID    NAS_EMM_WaitNetworkRelInd(VOS_VOID);

extern VOS_VOID    NAS_EMM_MrrcChangeRrcStatusToIdle(VOS_VOID);
extern VOS_UINT32  NAS_EMM_PreProcMsgRabmDrbSetupInd( MsgBlock * pMsg );
extern VOS_VOID  NAS_EMM_ProcDeregMmcRelReq(VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcDetachMmcRelReq(VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcRegMmcRelReq(VOS_VOID );
extern VOS_VOID  NAS_EMM_ProcRegMmcRelReqWhileTauInit(VOS_VOID);
extern VOS_VOID  NAS_EMM_ProcRegMmcRelReqWhileSerInit(VOS_VOID);
extern VOS_VOID  NAS_EMM_ProcRegMmcRelReqWhileImsiDetach(VOS_VOID);

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

#endif /* end of ����ģ��+����ģ��+Interface.h */
