

#ifndef __NAS_RABM_FASTDORM_H__
#define __NAS_RABM_FASTDORM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "rabminclude.h"
#include "AtRabmInterface.h"
#include "Nasrrcinterface.h"
#include "rabmext.h"
#include "RabmExtFunc.h"
#include "GmmRabmInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_RABM_SET_FD_ACT_FLG(FLAG)         ((g_stNasRabmFastDormCtx.ulActiveFlg) = (FLAG))

#define NAS_RABM_GET_FD_ACT_FLG()           (g_stNasRabmFastDormCtx.ulActiveFlg)

#define NAS_RABM_SET_FD_USER_DEF_NOFLUX_CNT(NoFluxCnt)  ((g_stNasRabmFastDormCtx.ulUserDefNoFluxCnt) = (NoFluxCnt))

#define NAS_RABM_GET_FD_USER_DEF_NOFLUX_CNT()       (g_stNasRabmFastDormCtx.ulUserDefNoFluxCnt)

#define NAS_RABM_SET_FD_CURR_NOFLUX_CNT(NoFluxCnt)  ((g_stNasRabmFastDormCtx.ulCurrNoFluxCnt) = (NoFluxCnt))

#define NAS_RABM_GET_FD_CURR_NOFLUX_CNT()   (g_stNasRabmFastDormCtx.ulCurrNoFluxCnt)

#define NAS_RABM_SET_FD_OPERATION_TYPE(FdOpType)   ((g_stNasRabmFastDormCtx.enFastDormOperationType) = (FdOpType))

#define NAS_RABM_GET_FD_OPERATION_TYPE()   (g_stNasRabmFastDormCtx.enFastDormOperationType)

#define NAS_RABM_GET_FD_STATUS()   (g_stNasRabmFastDormCtx.enCurrFastDormStatus)

#define NAS_RABM_SET_FD_STATUS(FdStatus)   ((g_stNasRabmFastDormCtx.enCurrFastDormStatus) = (FdStatus))

#define NAS_RABM_INC_FD_ULDATA_CNT()     (g_stNasRabmFastDormCtx.ulUlDataCnt++)

#define NAS_RABM_INC_FD_DLDATA_CNT()       (g_stNasRabmFastDormCtx.ulDlDataCnt++)

#define NAS_RABM_GET_FD_ULDATA_CNT()    (g_stNasRabmFastDormCtx.ulUlDataCnt)

#define NAS_RABM_GET_FD_DLDATA_CNT()    (g_stNasRabmFastDormCtx.ulDlDataCnt)

#define NAS_RABM_CLR_FD_ULDATA_CNT()    ((g_stNasRabmFastDormCtx.ulUlDataCnt) = (0))

#define NAS_RABM_CLR_FD_DLDATA_CNT()    ((g_stNasRabmFastDormCtx.ulDlDataCnt) = (0))

#define NAS_RABM_SET_FD_REL_RRC_EXEC_FLG()  (g_stNasRabmFastDormCtx.ulRelRrcExecFlg = VOS_TRUE)
#define NAS_RABM_CLR_FD_REL_RRC_EXEC_FLG()  (g_stNasRabmFastDormCtx.ulRelRrcExecFlg = VOS_FALSE)
#define NAS_RABM_GET_FD_REL_RRC_EXEC_FLG()  (g_stNasRabmFastDormCtx.ulRelRrcExecFlg)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_RABM_FASTDORM_STATUS_ENUM
{
    NAS_RABM_FASTDORM_INIT,                                                     /* ��ǰFAST DORMANCY�ڳ�ʼ״̬ */
    NAS_RABM_FASTDORM_DETECT,                                                   /* ��ǰFAST DORMANCY�ڼ��״̬������ͳ�ƶ�ʱ���Ѿ��������ȴ�������ʱ��ﵽAT��������ʱ�� */
    NAS_RABM_FASTDORM_EXEC,                                                     /* ��ǰFAST DORMANCY���ڼ��GMM״̬��׼������FD */
    NAS_RABM_FASTDORM_BUTT
};
typedef VOS_UINT32 NAS_RABM_FASTDORM_STATUS_ENUM_UINT32;
enum NAS_RABM_OM_MSG_ID_ENUM
{
    /* MMC���͸�OM����Ϣ */
    NAS_RABM_OM_MSG_FASTDORM_STATUS = 0x1111,                                   /*_H2ASN_MsgChoice  NAS_MMC_LOG_FSM_INFO_STRU */
    NAS_RABM_OM_MSG_BUTT
};
typedef VOS_UINT32 NAS_RABM_OM_MSG_ID_ENUM_UINT32;


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
    VOS_UINT32                              ulActiveFlg;
    VOS_UINT32                              ulCurrNoFluxCnt;                    /* ������ʱ������������Ϊ��λ */
    AT_RABM_FASTDORM_OPERATION_ENUM_UINT32  enFastDormOperationType;            /* ��ǰFAST DORMANCY�Ĳ�����ʽ */
    VOS_UINT32                              ulUserDefNoFluxCnt;                 /* �û������������ʱ��Ҫ�� */
    NAS_RABM_FASTDORM_STATUS_ENUM_UINT32    enCurrFastDormStatus;               /* �洢��ǰ��FAST DORMANCY����״̬ */
    VOS_UINT32                              ulUlDataCnt;                        /* �������ݼ����� */
    VOS_UINT32                              ulDlDataCnt;                        /* �������ݼ����� */

    VOS_UINT32                              ulRelRrcExecFlg;

} NAS_RABM_FASTDORM_CTX_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ                   */ /*_H2ASN_Skip*/
    NAS_RABM_FASTDORM_CTX_STRU          stFastDormCtx;

    NAS_RABM_TIMER_STATUS_ENUM_UINT8    aenTimerState[3];
    VOS_UINT8                           ucReserved;

}NAS_RABM_LOG_FASTDORM_INFO_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ȫ�ֱ�������
*****************************************************************************/
extern NAS_RABM_FASTDORM_CTX_STRU              g_stNasRabmFastDormCtx;


/*****************************************************************************
  11 ��������
*****************************************************************************/

extern VOS_UINT8 NAS_RABM_CheckPdpRbStatus(VOS_VOID);
extern VOS_UINT8 NAS_RABM_CheckGmmAndRabmStatus(
            GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus
        );
extern VOS_VOID NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType(
           AT_RABM_FASTDORM_OPERATION_ENUM_UINT32                enAtFastDormType,
           RRC_FASTDORM_START_TYPE_ENUM_UINT32                 *penWrrFastDormType
       );
extern VOS_VOID NAS_RABM_InitFastDormCtx(VOS_VOID);
extern VOS_VOID NAS_RABM_ProcFastDormStatusInTransfer( VOS_VOID );
extern VOS_VOID NAS_RABM_AbortRelRrcProcedure(VOS_VOID);
extern VOS_VOID NAS_RABM_RcvAtFastDormStartReq(
           AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
       );
extern VOS_VOID NAS_RABM_RcvAtFastDormStopReq(
           AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
       );
extern VOS_VOID NAS_RABM_RcvGetFastDormParaReq(
           AT_RABM_QRY_FASTDORM_PARA_REQ_STRU *pstFastDormPara
       );
extern VOS_VOID NAS_RABM_RcvReleaseRrcReq(
           AT_RABM_RELEASE_RRC_REQ_STRU *pstMsg
       );
extern VOS_VOID NAS_RABM_RcvSetFastDormParaReq(
           AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
       );
extern VOS_VOID NAS_RABM_RcvWasFastDormInfoInd(
           struct MsgCB                       *pMsg
       );
extern VOS_VOID NAS_RABM_ResumeFastDorm(VOS_VOID);
extern VOS_VOID NAS_RABM_RevertFastDormEnv(VOS_VOID);

extern VOS_VOID NAS_RABM_SuspendFastDorm(VOS_VOID);
extern VOS_VOID NAS_RABM_SysModeChgProcFastDorm(
           GMM_RABM_NET_RAT_ENUM_UINT32        enOldSysMode,
           GMM_RABM_NET_RAT_ENUM_UINT32        enNewSysMode
       );
extern VOS_VOID NAS_RABM_FastDormFluxDetectExpired(VOS_VOID);
extern VOS_VOID NAS_RABM_FastDormRetryExpired(VOS_VOID);
extern VOS_VOID NAS_RABM_FastDormWaitGmmProcQryRsltExpired(VOS_VOID);

extern VOS_VOID NAS_RABM_SndWasFastDormStartReq(
    RABM_RELRRC_OPERATE_ENUM_UINT32 enOptFlag
);

extern VOS_VOID NAS_RABM_SndWasFastDormStopReq(VOS_VOID);

extern VOS_VOID NAS_RABM_SndGmmMmlProcStatusQryReq(
    RABM_RELRRC_OPERATE_ENUM_UINT32 enOptFlag
);

extern VOS_VOID NAS_RABM_SndAtSetFastDormParaCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    AT_RABM_PARA_SET_RSLT_ENUM_UINT32   enRslt
);
extern VOS_VOID NAS_RABM_SndAtQryFastDormParaCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucRslt
);

extern VOS_VOID  NAS_RABM_SndOmFastdormStatus(VOS_VOID);


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

#endif /* end of NasRabmFastdorm.h */

