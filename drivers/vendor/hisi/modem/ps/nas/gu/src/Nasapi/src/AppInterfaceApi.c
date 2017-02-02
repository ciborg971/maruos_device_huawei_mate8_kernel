/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : AppInterfaceApi.c
  Description  : �ṩ��APP�Ľӿ�API����ʵ��
  Function List:
      1.
  History:
      1.  ��־��   2005.01.04   �¹�����
      2.  ۬����   2005.09.20   ����SMS��صĽӿں���
      3.  ��³��   2005-04-25   for A32D01738
      4.  ��  ��   2007-09-26   A32D12924
*******************************************************************************/
#include "PsTypeDef.h"
#include "product_config.h"
#include "ExtAppCmInterface.h"
#include "NasComm.h"

#include "ExtAppRabmInterface.h"
#include "RabmTafInterface.h"
#include "TTFMem.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_APPINTERFACEAPI_C



VOS_VOID Api_AppRabmDataReq( ST_APP_RABM_DATA *pRabmDataReq )
{
    VOS_UINT32  ulDataLen;
    TAFRABM_CS_DATA_REQ_STRU   *pSndCsMsg = VOS_NULL_PTR;                               /* ���巢�͵�CS���ָ��                     */
    VOS_UINT32  ulRet;

    if (D_RABM_CS_DOMAIN != pRabmDataReq->ucDomain)
    {
        PS_NAS_LOG( WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR,  "Api_AppRabmDataReq(CS):ucDomain is not D_RABM_CS_DOMAIN!" );
        return;
    }

    ulDataLen = (pRabmDataReq->ulDataLen + 7) / 8;                          /* ��APP������bit���ȸ�Ϊ�ֽڳ���           */
    pSndCsMsg = (TAFRABM_CS_DATA_REQ_STRU *)
                PS_ALLOC_MSG( WUEPS_PID_TAF,
                              (sizeof(TAFRABM_CS_DATA_REQ_STRU)
                                            + ulDataLen) - 4);
    if (VOS_NULL_PTR ==pSndCsMsg)
    {
        PS_NAS_LOG( WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR,  "Api_AppRabmDataReq(CS):Alloc msg fail!" );
        return;
    }

    pSndCsMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndCsMsg->MsgHeader.ulSenderPid = WUEPS_PID_TAF;
    pSndCsMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndCsMsg->MsgHeader.ulReceiverPid = WUEPS_PID_RABM;
    pSndCsMsg->MsgHeader.ulMsgName   = TAFRABM_CS_DATA_REQ;

    pSndCsMsg->ulSi = pRabmDataReq->ucRabId;                                /* ����SI                                   */
    pSndCsMsg->ulDataLen = pRabmDataReq->ulDataLen;                         /* �������ݳ���                             */
    PS_NAS_MEM_CPY(pSndCsMsg->aucData,
                pRabmDataReq->pucData,
                ulDataLen);                                                 /* �������                                 */


    PS_NAS_LOG( WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL,   "\n Api_AppRabmDataReq: ucDomain   = D_RABM_CS_DOMAIN\r" );
    PS_NAS_LOG1( WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                 "\n Api_AppRabmDataReq: ucRabId    = \r",
                 pRabmDataReq->ucRabId );
    PS_NAS_LOG1( WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                 "\n Api_AppRabmDataReq: ulDataLen  = \r",
                 (VOS_INT32)pRabmDataReq->ulDataLen );

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pSndCsMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_TAF, "Api_AppRabmDataReq():WARNING:SEND LMM START REQ FIAL");
    }

}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

