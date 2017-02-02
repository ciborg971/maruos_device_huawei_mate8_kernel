/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLppOm.h
  Description     : NasLppOm.c header file
  History         :
     1.XiaoJun       2015-8-14     Draft Enact
     2.
******************************************************************************/

#ifndef __NASLPPOM_H__
#define __NASLPPOM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "NasLppPublic.h"
#include    "NasFileId.h"
#include    "LPPLRrcInterface.h"
#include    "NasLppAirMsg.h"
#include    "PsCommonDef.h"
#include    "EmmLppInterface.h"
#include    "NasLppEncodeDecodePublic.h"
#include    "NasCommPrint.h"
#include    "PsLogdef.h"


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


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
#define    PS_MSG_ID_NAS_LPP_OM_BASE   0 /*����ͳһ����???*/

#define NAS_LPP_WRITE_OM_MSG_HEAD(pstMsg, ulLppOmMsgID)\
                    (pstMsg)->ulMsgId   = (ulLppOmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_LPP;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_OM;

#define NAS_LPP_OM_MAX_PARA_NUM         (3)

/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NAS_LPP_OM_MSG_ENUM
{
    /* ��ʱ��ʹ�����䣬�豣�� */
    ID_NAS_LPP_OM_FSM_STATE                 = PS_MSG_ID_NAS_LPP_OM_BASE,
    ID_NAS_LPP_OM_LOG_ERROR,
    ID_NAS_LPP_OM_LOG_WARN,
    ID_NAS_LPP_OM_LOG_NORM,
    ID_NAS_LPP_OM_LOG_INFO,
    ID_NAS_LPP_OM_TIMER_START,
    ID_NAS_LPP_OM_TIMER_STOP,
    ID_NAS_LPP_OM_TIMER_EXPIRE,
    ID_NAS_LPP_OM_NV,
    ID_NAS_LPP_OM_CONN_MANAGE,
    ID_NAS_LPP_OM_SESSION_MALLOC_SUCC,
    ID_NAS_LPP_OM_SESSION_MALLOC_FAIL,
    ID_NAS_LPP_OM_SESSION_RELEASE,
    ID_NAS_LPP_OM_TRANS_MALLOC_SUCC,
    ID_NAS_LPP_OM_TRANS_MALLOC_FAIL,
    ID_NAS_LPP_OM_TRANS_RELEASE,
    ID_NAS_LPP_OM_ADD_TRANS_TO_SESSION,
    ID_NAS_LPP_OM_COMM_CFG_MALLOC_SUCC,
    ID_NAS_LPP_OM_COMM_CFG_MALLOC_FAIL,
    ID_NAS_LPP_OM_COMM_CFG_RELEASE,
    ID_NAS_LPP_OM_UP_MSG_BUFF_MALLOC_SUCC,
    ID_NAS_LPP_OM_UP_MSG_BUFF_MALLOC_FAIL,
    ID_NAS_LPP_OM_UP_MSG_BUFF_RELEASE,
    ID_NAS_LPP_OM_ADD_LOC_TECH,
    ID_NAS_LPP_OM_DEL_LOC_TECH,
    ID_NAS_LPP_OM_MSG_BUTT
};
typedef VOS_UINT32  NAS_LPP_OM_MSG_ENUM_UINT32;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_FSM_STATE_STRU
 �ṹ˵��  : ״̬����om��Ϣ
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           ucSessionTransIndex;
    VOS_UINT8                           ucTransIndex;
    VOS_UINT8                           ucRsv;

    NAS_LPP_MAIN_STATE_ENUM_UINT32      enOldMainState;
    NAS_LPP_SUB_STATE_ENUM_UINT32       enOldSubState;

    NAS_LPP_MAIN_STATE_ENUM_UINT32      enNewMainState;
    NAS_LPP_SUB_STATE_ENUM_UINT32       enNewSubState;
}NAS_LPP_OM_FSM_STATE_STRU;


/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_TIMER_START_STRU
 �ṹ˵��  : ״̬����om��Ϣ
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           ucSessionTransIndex;
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName;
    VOS_UINT8                           aucRsv[1];
    VOS_UINT32                          ulLen;
}NAS_LPP_OM_TIMER_START_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_TIMER_STOP_STRU
 �ṹ˵��  : ״̬����om��Ϣ
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           ucSessionTransIndex;
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName;
    VOS_UINT8                           aucRsv[1];
    VOS_UINT32                          ulRemainTime;
}NAS_LPP_OM_TIMER_STOP_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_TIMER_EXPIRE_STRU
 �ṹ˵��  : ״̬����om��Ϣ
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           ucSessionTransIndex;
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName;
    VOS_UINT8                           aucRsv[1];
}NAS_LPP_OM_TIMER_EXPIRE_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_NV_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    /*TO DO*/
}NAS_LPP_OM_NV_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_CONN_MANAGE_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    /*TO DO*/
}NAS_LPP_OM_CONN_MANAGE_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_SESSION_MALLOC_SUCC_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulSessionId;
    VOS_UINT32                          ulSessionPoolBitmap;  /*����ɹ����*/
}NAS_LPP_OM_SESSION_MALLOC_SUCC_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_SESSION_MALLOC_FAIL_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT32                          ulSessionId;
    VOS_UINT32                          ulSessionPoolBitmap;
}NAS_LPP_OM_SESSION_MALLOC_FAIL_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_SESSION_RELEASE_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulSessionId;
    VOS_UINT32                          ulSessionPoolBitmap; /*�ͷųɹ����*/
}NAS_LPP_OM_SESSION_RELEASE_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_TRANS_MALLOC_SUCC_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    LPP_INITIATOR_TYPE_ENUM_UINT8       enInitiator;
    VOS_UINT8                           ucTransactionNumber;
    VOS_UINT8                           ucTransIndex;
    VOS_UINT32                          ulTransPoolBitmap;  /*����ɹ����*/
//    NAS_LPP_TRANSACTION_STRU            stLppTran;          /*����ɹ���session������trans idnex�����*/
}NAS_LPP_OM_TRANS_MALLOC_SUCC_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_TRANS_MALLOC_FAIL_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    LPP_INITIATOR_TYPE_ENUM_UINT8       enInitiator;
    VOS_UINT8                           ucTransactionNumber;
    VOS_UINT8                           aucRsv[1];
    VOS_UINT32                          ulTransPoolBitmap;  /*��ǰ��*/
//    NAS_LPP_TRANSACTION_STRU            stLppTran;          /*��ǰ�ģ�session������trans idnex�����*/
}NAS_LPP_OM_TRANS_MALLOC_FAIL_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_TRANS_RELEASE_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           ucTransIndex;       /*���ͷŵ�*/
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulTransPoolBitmap;  /*�ͷź��*/
    NAS_LPP_TRANSACTION_STRU            stLppTran;          /*�ͷź�ģ�session������trans idnex�����*/
}NAS_LPP_OM_TRANS_RELEASE_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_ADD_TRANS_TO_SESSION_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT8                           ucSessionIndex;
    VOS_UINT8                           ucTransIndex;       /*������session��transaction index*/
    VOS_UINT8                           aucRsv[2];
    NAS_LPP_TRANSACTION_STRU            stLppTran;          /*���Ӻ�ģ�session������trans idnex�����*/
}NAS_LPP_OM_ADD_TRANS_TO_SESSION_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_COMM_CFG_MALLOC_SUCC_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT8                           ucTransIndex;
    VOS_UINT8                           ucCfgIndex;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulCfgPoolBitmap;    /*����ɹ����*/
}NAS_LPP_OM_COMM_CFG_MALLOC_SUCC_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_COMM_CFG_MALLOC_FAIL_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT8                           ucTransIndex;
    VOS_UINT8                           ucCfgIndex;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulCfgPoolBitmap;    /* ��ǰ��*/
}NAS_LPP_OM_COMM_CFG_MALLOC_FAIL_STRU;
/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_COMM_CFG_RELEASE_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT8                           ucTransIndex;
    VOS_UINT8                           ucCfgIndex;         /*���ͷŵ�*/
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulCfgPoolBitmap;    /*�ͷź��*/
}NAS_LPP_OM_COMM_CFG_RELEASE_STRU;


/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_UP_MSG_BUFF_MALLOC_SUCC_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT8                           ucUpLinkBuffIndex;/*���뵽��*/
    VOS_UINT8                           aucRsv[3];
    NAS_LPP_UP_MSG_SEQUENCE_STRU        astUpmsgSeq[NAS_LPP_MAX_BUFF_MSG_COUNT]; /*������*/
    VOS_UINT32                          ulBitMap;       /*������*/
}NAS_LPP_OM_UP_MSG_BUFF_MALLOC_SUCC_STRU;


/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_UP_MSG_BUFF_MALLOC_FAIL_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    NAS_LPP_UP_MSG_SEQUENCE_STRU        astUpmsgSeq[NAS_LPP_MAX_BUFF_MSG_COUNT]; /*����ʱ��*/
    VOS_UINT32                          ulBitMap;       /*����ʱ��*/
}NAS_LPP_OM_UP_MSG_BUFF_MALLOC_FAIL_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_UP_MSG_BUFF_REL_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT8                           ucUpLinkBuffIndex;/*���ͷŵ�*/
    VOS_UINT8                           aucRsv[3];
    NAS_LPP_UP_MSG_SEQUENCE_STRU        astUpmsgSeq[NAS_LPP_MAX_BUFF_MSG_COUNT]; /*�ͷź��*/
    VOS_UINT32                          ulBitMap;       /*�ͷź��*/
}NAS_LPP_OM_UP_MSG_BUFF_REL_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_ADD_LOC_TECH_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPositionTech;  /*���ӵ�loc tech*/
    VOS_UINT8                           aucRsv[3];
    NAS_LPP_LOC_TECH_RUNING_STRU        stLocTechRunning; /*���Ӻ��*/
}NAS_LPP_OM_ADD_LOC_TECH_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_DEL_LOC_TECH_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPositionTech;  /*��ɾ��loc tech*/
    VOS_UINT8                           aucRsv[3];
    NAS_LPP_LOC_TECH_RUNING_STRU        stLocTechRunning; /*ɾ�����*/
}NAS_LPP_OM_DEL_LOC_TECH_STRU;

/*******************************************************************************
 �ṹ��    : NAS_LPP_OM_LOG_ERROR_STRU
 �ṹ˵��  :
 1.��    ��   : 2015��8��14��
   ��    ��   :Xiaojun
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    NAS_FILE_ID_DEFINE_ENUM_UINT32      enNasFileName;
    VOS_UINT32                          ulLine;
    NAS_LPP_ERROR_CODE_ENUM_UINT32      enErrorCode;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           ucParaNum;
    VOS_UINT32                          aulPara[NAS_LPP_OM_MAX_PARA_NUM];
}NAS_LPP_OM_LOG_STRU;



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID  NAS_LPP_OmAddTransToSessionInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucTransIndex,
           NAS_LPP_TRANSACTION_STRU           *pstLppTrans
       );
extern VOS_VOID  NAS_LPP_OmSessionMallocInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT32                          ulSessionId,
           VOS_UINT32                          ulSessionPoolBitmap
       );
extern VOS_VOID  NAS_LPP_OmSessionRelInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT32                          ulSessionId,
           VOS_UINT32                          ulSessionPoolBitmap
       );
extern VOS_VOID  NAS_LPP_OmStateChgInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndex,
           VOS_UINT8                           ucTransIndex,
           NAS_LPP_MAIN_STATE_ENUM_UINT32      enOldMsState,
           NAS_LPP_SUB_STATE_ENUM_UINT32       enOldSubState,
           NAS_LPP_MAIN_STATE_ENUM_UINT32      enNewMsState,
           NAS_LPP_SUB_STATE_ENUM_UINT32       enNewSubState
       );
extern VOS_VOID  NAS_LPP_OmTimerExpireInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndex,
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName
       );
extern VOS_VOID  NAS_LPP_OmTimerStartInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucSessionTransIndex,
           NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
           VOS_UINT32                          ulLen
       );
extern VOS_VOID  NAS_LPP_OmTimerStopInd
       (
            VOS_UINT8                           ucSessionIndex,
            VOS_UINT8                           ucSessionTransIndex,
            NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
            VOS_UINT32                          ulRemainTime
        );
extern VOS_VOID  NAS_LPP_OmTransMallocInd
       (
           VOS_UINT8                           ucTransIndex,
           VOS_UINT32                          ulTransPoolBitmap,
           NAS_LPP_TRANS_ID_STRU              *pstTransId
       );
extern VOS_VOID  NAS_LPP_OmTransRelInd
       (
           VOS_UINT8                           ucSessionIndex,
           VOS_UINT8                           ucTransIndex,
           NAS_LPP_TRANSACTION_STRU           *pstLppTrans
       );
extern VOS_VOID  NAS_LPP_OmAddTransToSessionInd
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucTransIndex,
    NAS_LPP_TRANSACTION_STRU           *pstLppTrans
);
extern VOS_VOID  NAS_LPP_OmCommCfgPoolMallocInd
(
    VOS_UINT8                           ucTransIndex,
    VOS_UINT8                           ucCommCfgIndex,
    VOS_UINT32                          ulCfgPoolBitmap
);
extern VOS_VOID  NAS_LPP_OmCommCfgPoolRelInd
(
    VOS_UINT8                           ucTransIndex,
    VOS_UINT8                           ucCommCfgIndex,
    VOS_UINT32                          ulCfgPoolBitmap
);
extern VOS_VOID  NAS_LPP_OmUpMsgBuffMallocSuccInd
(
    VOS_UINT8                           ucUpLinkBuffIndex,
    NAS_LPP_UP_MSG_SEQUENCE_STRU       *pstUpmsgSeq,
    VOS_UINT32                          ulBitMap
);
extern VOS_VOID  NAS_LPP_OmUpMsgBuffMallocFailInd
(
    NAS_LPP_UP_MSG_SEQUENCE_STRU       *pstUpmsgSeq,
    VOS_UINT32                          ulBitMap
);
extern VOS_VOID  NAS_LPP_OmUpMsgBuffRelInd
(
    VOS_UINT8                           ucUpLinkBuffIndex,
    NAS_LPP_UP_MSG_SEQUENCE_STRU       *pstUpmsgSeq,
    VOS_UINT32                          ulBitMap
);

extern VOS_VOID  NAS_LPP_OmAddLocTechInd
(
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPositionTech,
    NAS_LPP_LOC_TECH_RUNING_STRU       *pstLocTechRunning
);
extern VOS_VOID  NAS_LPP_OmDelLocTechInd
(
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPositionTech,
    NAS_LPP_LOC_TECH_RUNING_STRU       *pstLocTechRunning
);

extern VOS_VOID  NAS_LPP_OM_LOG
(
    NAS_LPP_OM_MSG_ENUM_UINT32          enLppOmMsg,
    NAS_FILE_ID_DEFINE_ENUM_UINT32      enNasFileName,
    VOS_UINT32                          ulLine,
    NAS_LPP_ERROR_CODE_ENUM_UINT32      enErrorCode,
    VOS_UINT8                           ucParaNum,
    VOS_UINT32                          ulPara1,
    VOS_UINT32                          ulPara2,
    VOS_UINT32                          ulPara3
);

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

#endif /* end of NasLppOm.h */
