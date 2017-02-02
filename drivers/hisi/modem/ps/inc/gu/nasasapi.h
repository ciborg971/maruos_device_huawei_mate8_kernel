
#ifndef _NAS_AS_API_H_
#define _NAS_AS_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /* __cpluscplus */
#endif  /* __cpluscplus */
#include "asnasapi.h"




/*========  PSҵ��ʹ�� */
#define RABM_PS_DATA_IND        0
typedef struct
{
    MSG_HEADER_STRU     MsgHdr;                                                 /* ��Ϣͷ                                    */
    VOS_UINT8                ucErr;                                                  /* ָʾ�����Ƿ�������,                                                                                 * WUEPS_TRUE:����;WUEPS_FALSE:û�з������� */
    VOS_UINT32               ulRbId;                                                 /* radio bear                               */
    VOS_UINT32               ulDataLen;                                              /* ���ݵĳ���                                */
    VOS_UINT8               *pucData;                                               /* �����׵�ַ                                */
} RABM_PS_DATA_IND_STRU;


/*============  CS����ʹ�� */
#define RABMRLC_CS_DATA_IND     1
typedef struct
{
    MSG_HEADER_STRU     MsgHdr;                                                 /* ��Ϣͷ                                    */


    VOS_UINT8               ucErr;                                                  /* ָʾ�����Ƿ�������                        */
    VOS_UINT32               ulRbId;                                                 /* radio bear                               */
    VOS_UINT32               ulDataLen;                                              /* ���ݵĳ���                                */
    VOS_UINT8               *pucData;                                               /* �����׵�ַ                                */
    VOS_UINT8               ucCrcLen;
}RABMRLC_CS_DATA_IND_STRU;


/* NAS�ṩ��ASʹ�õ�API */
NAS_CALLBACK_TYPE    Nas_RrDataInd(VOS_UINT8 ucCnDomain, VOS_UINT32 ulSize, VOS_UINT8 *pucNasMsg, VOS_UINT8 ucICResult);
NAS_CALLBACK_TYPE    Nas_RrPagingInd(PAGING_INFO_STRU *pPagingInfo);
NAS_CALLBACK_TYPE    Nas_RrSysInfoInd(SYSINFO_STRU *pSysInfo);
NAS_CALLBACK_TYPE    Nas_RrEstCnf(VOS_UINT32 ulOpId, VOS_UINT32 ulResult,VOS_UINT32 ulCnDomainId);
NAS_CALLBACK_TYPE    Nas_RrRelInd(VOS_UINT8 ucCnDomain, VOS_UINT32 ulRelCause, VOS_UINT32 ulRrcConnStatus);
NAS_CALLBACK_TYPE    Nas_RrSecurityInd(SECURITY_INFO_STRU *pSecuriryInfo);
NAS_CALLBACK_TYPE    Nas_PlmnSearchCnf(PLMN_SEARCH_RESULT_STRU *pSearchResult);
NAS_CALLBACK_TYPE    Nas_PlmnListInd(PLMN_LIST_STRU *pPlmnList);
NAS_CALLBACK_TYPE    Nas_AreaLostInd(VOS_UINT32 ulRptMode);
NAS_CALLBACK_TYPE    Nas_RabStatusInd(RAB_STATUS_INFO_STRU *pRabInfo);
NAS_CALLBACK_TYPE    Nas_RrSyncInd(SYNC_INFO_STRU *pSyncInfo);
NAS_CALLBACK_TYPE    Nas_RabScInd(RAB_SC_INFO_STRU *pScInfo);
NAS_CALLBACK_TYPE    Nas_PowerOffCnf(VOS_VOID);
NAS_CALLBACK_TYPE    Nas_RrStartCnf(VOS_VOID);
/* Added by songshulong 20050131 begin */
NAS_CALLBACK_TYPE Nas_RrAcInfoChangeInd( VOS_UINT32  ulAcChangeInd );
/* Added by songshulong 20050131 end */


/* RABMʹ�õ�API����AS�ṩ */
typedef VOS_INT32 (*RRRABM_RAB_INFO_RSP_FUNC)(VOS_UINT32 ulResult, RAB_RSP_INFO_STRU *pRabInfo);
typedef VOS_INT32 (*RRRABM_RAB_QOS_UPDATE_FUNC)(QOS_INFO_STRU *pQos);

typedef struct rabm_rrc_imported_func_list_stru
{
    RRRABM_RAB_INFO_RSP_FUNC       RrRabmRabInfoRsp;
    RRRABM_RAB_QOS_UPDATE_FUNC     RrRabmRabQosUpdate;
}RABM_RRC_IMPORTED_FUNC_LIST_STRU;

/*A32D00461,zzy,pclint*/
#define  NSAPI_MEM_FAIL()     PS_NAS_LOG(MSP_PID_DIAG_APP_AGENT, 0, OM_PRINT_LEVEL_ERROR, "NAS Mem Operation Failed!");

#define  NSAPI_MSG_FAIL()     PS_NAS_LOG(MSP_PID_DIAG_APP_AGENT, 0, OM_PRINT_LEVEL_ERROR, "NAS Msg Opration Failed!");

#define  NSAPI_TIMER_FAIL()   PS_NAS_LOG(MSP_PID_DIAG_APP_AGENT, 0, OM_PRINT_LEVEL_ERROR, "NAS Timer Opration Failed!");



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cpluscplus */

#endif


