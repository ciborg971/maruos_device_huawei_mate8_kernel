

#ifndef _RABM_EXT_FUNC_H_
#define _RABM_EXT_FUNC_H_


/*****************************************************************************
  1 ����ͷ�ļ�����
******************************************************************************/
#include "vos.h"

#include "ExtAppRabmInterface.h"

#include "RabmInterface.h"
#include "Rabm2GStru.h"

#include "NasGmmInterface.h"
#include "Taf_ApsForRabm.h"
#include "TafAppRabm.h"

#include "MmcRabmInterface.h"

#include "RabmTafInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
  #define
*****************************************************************************/


/*******************************************************************************
  3 ö�ٶ���
  typedef enum
{
    ģ����_��������_ENUM
    MAPS_TEMPLATE_ENUM1 = 0,
    MAPS_TEMPLATE_ENUM2


    MAPS_TEMPLATE_BUTT,    �����ͳһ��BUTT����Ϊ���һ��ö��ֵ��

}MAPS_TEMPLATE_ENUM;   ģ����_ö����������_ENUM
*******************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
  extern VOS_UINT8* pgucMapsTemplateBuffer;   ָ�룫ȫ�ֱ�ʶ�����ͣ�ģ��������������

*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
  ģ���������士HEADER
#define MAPS_TEMPLATE_HEADER    VOS_UINT16    usTotalsMsgLen;\
                                VOS_UINT32    ulSendModuleId;\
                                VOS_UINT32    ulRecvModuleId;\

*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
  typedef struct
{
    MAPS_TEMPLATE_HEADER
    VOS_UINT8    aucData[2];

} MAPS_TEMPLATE_MSG;

*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
  typedef struct
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];

} MAPS_TEMPLATE_ST;
*****************************************************************************/


/*****************************************************************************
  8 UNION����
  typedef union
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];

} MAPS_TEMPLATE_UNION;

*****************************************************************************/


/*****************************************************************************
 9 ��������

******************************************************************************/
/*================================================================================
                    File : Rabm_ApsTransmodeSet.c
=================================================================================*/
extern VOS_VOID    NAS_RabmTransModeError( VOS_UINT8  ucNsapi );
/*================================================================================
                    File : Rabm_Assistant.c
=================================================================================*/
extern VOS_VOID NAS_Rabm2GInit( VOS_VOID );
extern VOS_VOID NAS_RabmStartTimer( RABM_TIMER_NAME_ENUM Name, RABM_TIMER_PARA_ENUM Para );
extern VOS_VOID NAS_RabmStopTimer( RABM_TIMER_NAME_ENUM Name, RABM_TIMER_PARA_ENUM Para );
extern NAS_RABM_TIMER_STATUS_ENUM_UINT8  NAS_RABM_CheckTimerStatus(
    RABM_TIMER_NAME_ENUM                enEntityTimerName,
    RABM_TIMER_PARA_ENUM                enTimerPara
);
extern VOS_UINT32  NAS_RabmQueryTransmodeNoState( VOS_VOID );

extern VOS_UINT32  NAS_Rabm2GChangeTo3G( VOS_VOID );
extern VOS_UINT32  NAS_Rabm3GChangeTo2G( VOS_VOID );
extern VOS_VOID    NAS_RabmDecodeNPdu( GMMRABM_ROUTING_AREA_UPDATE_IND_MSG *pRAUpdateIndMsg,
                                                   RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST   *pstNPdu );
extern VOS_VOID    NAS_RabmEncodeNPdu( GMMRABM_ROUTING_AREA_UPDATE_RSP_MSG *PRAUpdateRspMsg,
                                                   RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST   *pstNPdu );
extern VOS_UINT32  NAS_RabmQueryRAUState( VOS_UINT8 ucNsapiIndex );
extern VOS_UINT32  NAS_RabmQueryNoOrReadyState( VOS_UINT8 ucNsapiIndex );
extern VOS_VOID    NAS_RabmDeactive3GPdp(VOS_UINT8 ucNsapiIndex);
extern VOS_VOID    NAS_RabmSndHandoverRabRsp( VOS_UINT8  ucRabNum, RRRABM_HANDOVER_RAB_IND_STRU *pMsg);
extern VOS_VOID    NAS_RabmDealHandoverRabInd( RRRABM_HANDOVER_RAB_IND_STRU *pMsg);
extern VOS_VOID RABM_SetGState(RABM_NSAPI_ENUM  EntId, RABM_2G_STATE_ENUM  DestState);
extern VOS_VOID RABM_SetWState(VOS_UINT8    ucEntId, VOS_UINT8   ucDestState);
extern VOS_VOID RABM_CreateRabMap
                   (
                       VOS_UINT8 ucRabId,
                       VOS_UINT8 ucLinkdRabId,
                       VOS_UINT8 ucRbId,
                       RAB_UL_DATA_CALLBACK pRabUlDataCallBack,
                       RAB_DL_DATA_CALLBACK pRabDlDataCallBack
                   );


extern VOS_VOID RABM_DelRabMap(VOS_UINT8 ucRabId);


extern VOS_VOID RABM_ChgRabMap
                   (
                       VOS_UINT8       ucRabId,
                       VOS_UINT8       ucChgMask,  /* �ı����룬ָʾ��Щ������Ҫ�޸� */
                       VOS_UINT8       ucRbId,
                       RAB_UL_DATA_CALLBACK pRabUlDataCallBack,
                       RAB_DL_DATA_CALLBACK pRabDlDataCallBack
                   );
extern VOS_UINT32  RABM_SndPdcpUlDataCallBack(VOS_UINT8 ucRabId, VOS_UINT8 ucRbId, TTF_MEM_ST *pstData);
extern VOS_UINT32  RABM_SndSndcpUlDataCallBack(VOS_UINT8 ucRabId, VOS_UINT8 ucNsapi, TTF_MEM_ST *pstData);
extern VOS_UINT32  RABM_SndRABMUlDataCallBack(VOS_UINT8 ucRabId, VOS_UINT8 ucRbId, TTF_MEM_ST *pstData);
extern VOS_UINT32  RABM_SndAppDlDataCallBack(VOS_UINT8 ucRabId, TTF_MEM_ST *pstData);
extern VOS_VOID    RABM_RabMapInit(VOS_VOID);
extern VOS_VOID    RABM_CreateRabMapWhenPdpActAcc(VOS_UINT8 ucRabId, VOS_UINT8 ucAsId);
extern VOS_UINT32  RABM_ResumeFirstActIndStatus(RABM_CUR_NET_ENUM enCurNetType, VOS_UINT8 ucEntId);
extern VOS_INT     intLock (VOS_VOID);
extern VOS_VOID    intUnlock(VOS_INT lockKey);

/*================================================================================
                    File : Rabm_DataAndFlux.c
=================================================================================*/
extern VOS_VOID    NAS_RabmRcvTafGprsPsDataReq(TAFRABM_PS_DATA_REQ_STRU *pPsDataReqMsg);

/*================================================================================
                    File : Rabm_DealGmmMsg.c
=================================================================================*/
extern VOS_VOID    NAS_RabmGmmRoutingAreaUpdateIndMsg( VOS_VOID *pMsg );
extern VOS_VOID    NAS_Rabm2GTo3GRAUFail( VOS_VOID );
extern VOS_VOID    NAS_Rabm3GTo2GRAUFail( VOS_VOID );
extern VOS_VOID    NAS_Rabm2GRoutingAreaUpdate( GMMRABM_ROUTING_AREA_UPDATE_IND_MSG   *pMsg );
extern VOS_VOID    NAS_Rabm3GTo2GRoutingAreaUpdate( GMMRABM_ROUTING_AREA_UPDATE_IND_MSG   *pMsg );
extern VOS_VOID    NAS_RabmMmcSuspendIndMsg( VOS_VOID *pMsg );
extern VOS_VOID    NAS_RabmDeal2GTo3GSuspendIndMsg( VOS_VOID );
extern VOS_VOID    NAS_RabmDeal3GTo2GSuspendIndMsg( VOS_VOID );
extern VOS_VOID    NAS_RabmSndSnSaveDataInd(VOS_VOID);
extern VOS_VOID    NAS_RabmSndSnDataResumeInd(VOS_VOID);
extern VOS_VOID    NAS_RabmSndPdcpDataResumeInd(RRRABM_RAB_IND_STRU  *pMsg);
extern VOS_VOID    NAS_RabmRcvPdcpDataResumeRsp(VOS_VOID *pMsg);
extern VOS_UINT32  NAS_RabmSndPdcpSaveDataInd(VOS_VOID);
extern VOS_VOID    NAS_RabmRcvPdcpSaveDataRsp(VOS_VOID *pMsg);
extern VOS_VOID    NAS_RabmSaveNsapiMapRbInfo(VOS_VOID);
extern VOS_VOID    NAS_RABM_RcvGmmFastDormMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
);

extern VOS_VOID NAS_RABM_RcvGmmMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
);

extern VOS_VOID NAS_RABM_RcvGmmReleaseRrcMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
);

/*================================================================================
                    File : Rabm_DealSmMsg.c
=================================================================================*/
extern VOS_VOID    NAS_RabmSmPdpActivateIndMsg( VOS_VOID  *pMsg );
extern VOS_VOID    NAS_RabmSmPdpDeactivateIndMsg( VOS_VOID  *pMsg );
extern VOS_VOID    NAS_RabmSmPdpModifyIndMsg( VOS_VOID  *pMsg );

/*================================================================================
                    File : Rabm_DealSnMsg.c
=================================================================================*/
extern VOS_VOID    NAS_RabmSnSequenceRspMsg( VOS_VOID  *pMsg );
extern VOS_VOID    NAS_RabmDeal2GSnSequence( VOS_VOID * pMsg );
extern VOS_VOID    NAS_RabmDealChangeSnSequence( VOS_VOID );
extern VOS_VOID    NAS_RabmSnSaveDataRspMsg(VOS_VOID);
extern VOS_VOID    NAS_RabmSnResumeDataRspMsg(VOS_VOID);
/*================================================================================
                    File : Rabm_DealTimeoutMsg.c
=================================================================================*/
extern VOS_VOID    NAS_RabmTimerExpiredMsgDispatch( REL_TIMER_MSG  *pTimerExpiredMsg );
extern VOS_VOID    NAS_RabmRoutingAreaUpdateT1Expired( REL_TIMER_MSG  *pTimerExpiredMsg );
extern VOS_VOID    NAS_RabmActReqT1Expired( REL_TIMER_MSG  *pTimerExpiredMsg );
extern VOS_VOID    NAS_Rabm3GTo2GT3Expired( REL_TIMER_MSG  *pTimerExpiredMsg );


/*================================================================================
                    File : Rabm_MsgDispatch.c
=================================================================================*/
extern VOS_VOID  Rabm_TaskEntry( struct MsgCB *pMsg );
extern VOS_VOID  NAS_Rabm2GMsgDispatch( struct MsgCB *pMsg );


/*================================================================================
                    Other Function Declartion
=================================================================================*/
extern VOS_UINT32 SM_GetCr(VOS_UINT8 ucNsapi, VOS_UINT8 *pucCr);
extern VOS_UINT32 APS_PdpId2ClientId(VOS_UINT8 ucPdpId, VOS_UINT16 *pusClientId);
extern VOS_UINT32 Taf_ApsIsSndcpActive(VOS_UINT8  ucNsapi, RABM_TRANS_MODE_ENUM *penTransMode);
extern VOS_VOID R_ITF_SetGFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode);
extern VOS_VOID R_ITF_SetWFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode);
extern VOS_VOID CpuFlowCtrl_SaveCurrentRate(VOS_UINT32 ulULBitRate, VOS_UINT32 ulDLBitRate);

extern VOS_UINT32 GU_IPF_FilterDlData(VOS_UINT8 ucRabId, TTF_MEM_ST *psrc);

extern VOS_VOID NAS_RABM_CreateRabMapEntity(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucLinkdRabId,
    VOS_UINT8                           ucAsId
);


extern VOS_UINT32 TPDCP_DATA_REQ(VOS_UINT8 ucRbId, TTF_MEM_ST *pstData, VOS_UINT32  ulDataBitLen);
extern VOS_UINT32 TDS_RLC_GetRbSuitableUlPduSize(VOS_UINT8 ucRbId, VOS_UINT32 ulPduSize, VOS_UINT8 ucCrcSize, VOS_UINT32 *pulUlPduSize);
extern VOS_VOID   TPDCP_IntUlDataProc(VOS_VOID);

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

#endif /* end of RabmExtFunc.h*/
