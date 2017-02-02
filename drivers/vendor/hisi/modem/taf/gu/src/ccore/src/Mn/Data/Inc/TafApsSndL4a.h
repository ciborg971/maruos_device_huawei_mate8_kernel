

#ifndef __TAFAPSSNDL4A_H__
#define __TAFAPSSNDL4A_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "MnApsMultiMode.h"
#include "TafApsDecode.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


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


/*****************************************************************************
  10 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aSetCgactReq
 ��������  : ����ID_APS_L4A_SET_CGACT_REQ��Ϣ, ���𲦺�
 �������  : ucPdpId                    - APSʵ������
             pstSetPdpCtxStateReq       - +CGACT������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID TAF_APS_SndL4aSetCgactReq(
    VOS_UINT8                           ucPdpId,
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq
);

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aCallOrigReq
 ��������  : ����ID_APS_L4A_SET_NDISCONN_REQ��Ϣ, ���𲦺�
 �������  : pstCallOrigReq             - ���Ų���
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 TAF_APS_SndL4aCallOrigReq(
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq
);

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aCallEndReq
 ��������  : ����ID_APS_L4A_SET_NDISCONN_REQ��Ϣ, �Ͽ�����
 �������  : pstCalEndReq               - �Ͽ����Ų���
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID TAF_APS_SndL4aCallEndReq(
    TAF_PS_CALL_END_REQ_STRU           *pstCalEndReq
);

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aCallModifyReq
 ��������  : ����ID_APS_L4A_SET_CGCMOD_REQ��Ϣ, �Ͽ�����
 �������  : pstCallModifyReq           - �޸�EPS���ز���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID TAF_APS_SndL4aCallModifyReq(
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq
);


VOS_VOID TAF_APS_SndL4aCgansAccReq(
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq
);


VOS_VOID TAF_APS_SndL4aCgansRejReq(
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangUpReq
);

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aIpv6InfoNotifyInd
 ��������  : ����ID_APS_L4A_IPV6_INFO_NOTIFY_IND��Ϣ
 �������  : ucRabId                    - RAB ID
             pstIpv6RaInfo              - IPv6 RA����
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 TAF_APS_SndL4aIpv6InfoNotifyInd(
    VOS_UINT8                           ucRabId,
    TAF_PDP_IPV6_RA_INFO_STRU          *pstIpv6RaInfo
);
#endif

VOS_VOID TAF_APS_SndL4aSetCgdcontReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgdscontReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgtftReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgautoReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgcontrdpReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgscontrdpReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgtftrdpReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgeqosReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgeqosrdpReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetAuthdataReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aAbortReq(
    VOS_UINT8                           ucCid
);
VOS_VOID TAF_APS_SndL4aGetLteCsReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aGetCemodeReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetPdprofReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aPppDialReq(
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq,
    TAF_APS_AUTH_INFO_STRU             *pstPppAuthInfo,
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo
);


#endif

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

#endif /* end of TafApsSndL4a.h */
