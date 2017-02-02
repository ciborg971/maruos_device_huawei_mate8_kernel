

#ifndef __CDS_MSGPROC_H__
#define __CDS_MSGPROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*��װOSA��Ϣͷ*/
#define CDS_CFG_MSG_HDR(pstMsg,ulRecvPid)\
                    (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid     = UEPS_PID_CDS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid   = (ulRecvPid)

/*��װCDS����OSA��Ϣ�ӿ�*/
#define CDS_SEND_MSG(pMsg) \
                if (VOS_OK != PS_SND_MSG_ALL_CHECK(UEPS_PID_CDS,(pMsg)))\
                {\
                    CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_SEND_MSG : Send Msg Fail");\
                    return;\
                }

/*��װOSA��Ϣ����ӿ�*/
#define CDS_ALLOC_MSG_WITH_HDR(MsgLen)    (VOS_VOID *)PS_ALLOC_MSG_ALL_CHECK(UEPS_PID_CDS,(MsgLen))

/*����CDS״̬ת���ĺ���ָ��*/
typedef  VOS_VOID (*CDS_STATE_UPDATE_FUN)(VOS_VOID);

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
   5 STRUCT����
*****************************************************************************/



/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  8 ��������
*****************************************************************************/

extern VOS_VOID CDS_UlDataIndToAds(TTF_MEM_ST *pstIpPkt);
extern VOS_VOID CDS_RabmSerivceRequestNotify(VOS_UINT8 ucRabId, CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID CDS_RecvMsgProc(MsgBlock  *pstMsg);


/*LTE Only*/
#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
extern VOS_VOID CDS_ERabmSerivceRequestNotify(VOS_UINT8 ucEpsbId);
#endif

/*CDMA Only*/
#if (CDS_FEATURE_ON == CDS_FEATURE_CDMA)
extern VOS_VOID CDS_APSServiceRequestNotify(CDS_ENTITY_STRU *pstCdsEntity, VOS_UINT8 ucRabId);
#endif

extern VOS_VOID CDS_ProcRabmVoicePreferActIndMsg(const MsgBlock  *pstMsg);
/*****************************************************************************
  9 OTHERS����
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

#endif

