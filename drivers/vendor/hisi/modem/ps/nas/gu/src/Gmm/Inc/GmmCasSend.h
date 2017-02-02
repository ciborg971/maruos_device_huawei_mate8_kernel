

#ifndef _GMM_CAS_SEND_H_
#define _GMM_CAS_SEND_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#pragma pack(4)         /* 1�ֽڶ��룬���ݽṹ���屣֤4�ֽڶ��� */
                        /* ����include�󣬲�Ӱ������ͷ�ļ���pack���� */
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define GMM_LLC_TRANSID     1           /* GMMʹ�õ�SAPI */

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/* ֪ͨLLC��TLLI������ʽ */
typedef VOS_UINT8   GMM_OP_TLLI;
#define GMM_OP_TLLI_ASSIGN              0
#define GMM_OP_TLLI_MODIFY              1
#define GMM_OP_TLLI_UNASSIGN            2
#define GMM_OP_TLLI_UNASSIGN_SYS        3
#define GMM_OP_TLLI_SYNC                4
#define GMM_OP_TLLI_KC                  5

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
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
VOS_UINT32 GMM_SndGasAbortReq (VOS_UINT32  ulAbortMode);
VOS_UINT32 GMM_SndGasDataReq (
            VOS_UINT8       ucPriorityInd,  /* ��Ϣ���ȼ�ָʾ*/
            NAS_MSG_STRU   *pMsg            /* ��CN Domain��NAS��Ϣ�׵�ַ*/
            );
VOS_UINT32 GMM_SndGasEstReq (
            VOS_UINT32      ulEstCause,     /* RRC Connection Setupԭ��*/
            VOS_UINT32      ulIdnnsType,    /* 3����Ӧpaging��,6��������*/
            NAS_MSG_STRU   *pMsg            /* ��CN Domain��NAS��Ϣ�׵�ַ*/
            );
VOS_VOID GMM_SndGasNasInfoChangeReq (
            VOS_UINT32           ulMask          /* ��IE��Ч��־*/
            );
VOS_VOID GMM_SndGasRelReq (VOS_VOID);
VOS_VOID GMM_SndRrmmRelReqGsm(VOS_VOID);


VOS_VOID GMM_SndCasGmmStatusMsg(VOS_UINT8 ucRejCause);
VOS_VOID GMM_SndCasMmcInfoInd (VOS_UINT8 *pucData, VOS_UINT32 ulSize);
VOS_VOID GMM_SndCasSmDataInd(VOS_UINT8 *pucData, VOS_UINT32 ulSize);
VOS_VOID GMM_SndCasSmsUnitdataInd(VOS_UINT8 *pucData, VOS_UINT32 ulSize);
VOS_VOID GMM_SndCasTcDataInd (VOS_UINT8 *pucData, VOS_UINT32 ulSize);
VOS_VOID GMM_SndAttachReqGsm (VOS_VOID);

NAS_MSG_STRU* GMM_MakeNasMsgStru(VOS_UINT8 *pData, VOS_UINT32 ulSize);
LL_NAS_UNITDATA_REQ_ST* GMM_MakeGmmStatusMsgGsm(VOS_UINT8 ucRejectCause);
VOS_VOID GMM_MakeLlcNasMsgHeader(LL_NAS_UNITDATA_REQ_ST *pstNasMsg);
LL_NAS_UNITDATA_REQ_ST *GMM_MakeAttachReqMsgGsm (VOS_VOID);
LL_NAS_UNITDATA_REQ_ST* GMM_MakeAuthenAndCipherRspMsgGsm(
                            VOS_UINT8 ucResFlg                  /* 0:��ʾ����ش�res;1:��ʾ��ش�res */
                            );
LL_NAS_UNITDATA_REQ_ST* GMM_MakeIdentityRspMsgGsm(VOS_UINT8 ucIdType);

LL_GMM_ASSIGN_REQ_MSG   *GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI ucAssignFlg);
LL_GMM_TRIGGER_REQ_MSG  *GMM_MakeLlgmmTriggerReqMsg(VOS_UINT8 ucCause);
LL_GMM_SUSPEND_REQ_MSG  *GMM_MakeLlgmmSuspendReqMsg(VOS_VOID);
LL_GMM_RESUME_REQ_MSG   *GMM_MakeLlgmmResumeReqMsg(VOS_UINT32  ulResumeType);
GRRGMM_ASSIGN_REQ_ST  *GMM_MakeGrrmmAssignReqMsg(VOS_UINT32 ulCause);


VOS_VOID GMM_SndRrmmEstCnfGsm(VOS_UINT8 ucRrmmEstOpid);
VOS_VOID GMM_SndRrmmEstReqGsm(VOS_UINT8 ucRrmmEstOpid, NAS_MSG_STRU *pMsg);
VOS_VOID GMM_SndRrmmDataReqGsm(NAS_MSG_STRU *pMsg);
/*VOS_VOID GMM_SndRabmRauInd(VOS_UINT8 ucRauCause);*/
VOS_VOID GMM_SndRabmRauInd(VOS_UINT8 ucRauCause, VOS_UINT8 ucResult);
VOS_VOID NAS_GMM_SndGasInfoChangeReq(VOS_UINT32 ulMask);
VOS_VOID GMM_SndLlcSuspendReq(VOS_VOID);
VOS_VOID Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_ENUM_UINT8 ucClearDataType);
VOS_VOID GMM_SndLlcResumeReq(VOS_UINT32  ulResumeType);
VOS_VOID GMM_SndLlcTriggerReq(VOS_UINT8 ucCause);


VOS_VOID GMM_SndRabmGprsInfoInd(VOS_UINT8 ucGprsSupported,VOS_UINT8 ucProc,VOS_UINT8 ucRau);
VOS_VOID GMM_SndRabmGprsSuspensionInd(VOS_UINT8 ucProc);
VOS_VOID GMM_SndRabmGprsResumeInd(VOS_UINT8 ucProc,VOS_UINT8 ucResult);

VOS_VOID GMM_SndMmcSuspendRsp(VOS_VOID);

extern VOS_VOID NAS_GMM_SndMmcResumeRsp(VOS_VOID);


VOS_VOID NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_ENUM_UINT16 usProcType,
                                              RRMM_GMM_PROC_FLAG_ENUM_UINT16 usProcFlag);

VOS_VOID NAS_GMM_SndRrmmGmmProcAns(VOS_VOID);


/* BEGIN: Added by liurui id:40632, 2006/6/14   PN:A32D04282 */
VOS_UINT32 GMM_CasGetSplitCycle(VOS_UINT8 ucSplitCode);
/* END:   Added by liurui id:40632, 2006/6/14   PN:A32D04282 */

VOS_VOID NAS_GMM_SndRabmSysSrvChgInd(
    GMM_RABM_NET_RAT_ENUM_UINT32        enSysMode,
    VOS_BOOL                            bRatChangeFlg,
    VOS_BOOL                            bDataSuspendFlg,
    VOS_UINT8                           ucucRebuildRabFlag
);


VOS_VOID  NAS_GMM_SndGasGprsAuthFailNotifyReq(VOS_VOID);



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

#endif /* end of GmmCasSend.h*/
