
#include "SmInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SM_RCVRABM_C


VOS_VOID SM_RcvRabmDeActReq(
    RABMSM_DEACTIVATE_REQ_STRU         *pMsgIe                                  /* ���յ�����Ϣ                             */
)
{
    VOS_UINT8                          *pMsg;
    SM_NW_MSG_STRU                     *pSmMsg;
    VOS_UINT8                           ucCntxtIndex;

    ucCntxtIndex = (VOS_UINT8)pMsgIe->ulNsapi - SM_NSAPI_OFFSET;                /* ��ȡʵ�������                           */
    if( SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {                                                                           /* ״̬Ϊ����                               */
        if(0 != g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength)
        {                                                                       /* Qos��Ϊ��                                */
            pMsg =  (VOS_UINT8 *)SM_Malloc(sizeof(SM_NW_MSG_STRU));             /* �����ڴ�                                 */
            if ( VOS_NULL_PTR == pMsg )
            {
                PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                        "SM_RcvRabmDeActReq:ERROR:Alloc msg fail!" );
                return;
            }

            SM_MemSet(pMsg, 0, sizeof(SM_NW_MSG_STRU));
            pSmMsg = (SM_NW_MSG_STRU *)pMsg;

            g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue[5] = 0;        /* �޸��ڲ���Qos maxrate uplink�޸�Ϊ0      */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue[6] = 0;        /* �޸��ڲ���Qos maxrate downlink�޸�Ϊ0    */
            pSmMsg->Qos.ucLen = (VOS_UINT8)
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength;         /* ��дQoS����                              */
            pSmMsg->Qos.pValue = (VOS_UINT8 *)SM_Malloc(pSmMsg->Qos.ucLen);                      /* ����洢QoS�ڴ�                          */
            if ( VOS_NULL_PTR == pSmMsg->Qos.pValue )
            {
                PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                        "SM_RcvRabmDeActReq:ERROR:Alloc pSmMsg->Qos.pValue fail!" );
                return;
            }
            PS_MEM_CPY(pSmMsg->Qos.pValue,
                       g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                       g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength); /* �洢QoS                                  */

            pSmMsg->ucRadioPri = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucRadioPri;
            SM_SndTafSmPdpModifyInd( pSmMsg,ucCntxtIndex);                      /* ֪ͨTAF�޸�Qos                           */
            SM_Free( pSmMsg->Qos.pValue );                                      /* �ͷ��ڴ�                                 */
            SM_Free( pSmMsg );                                                  /* �ͷ��ڴ�                                 */
        }
    }
    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

