

#ifndef _MM_GSMDIFMSG_H_
#define _MM_GSMDIFMSG_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MM_T3212_UNIT_TRANSFORM         360000/*(6 * 60 * 1000)*/

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
/*ģ���������士HEADER
 */


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
  8 OTHERS����
*****************************************************************************/

VOS_UINT8 MM_RcvGsmRrcPagingInd(VOS_VOID *pRcvMsg);

VOS_UINT8 MM_RcvGsmRrcSyncInd(VOS_VOID *pRcvMsg);

VOS_INT32 MM_GasRrDataReq(VOS_UINT8 ucCnDomain, VOS_UINT8 ucPriority,
                          VOS_UINT32 ulSize, VOS_INT8 *pData);

VOS_UINT32  MM_SupplementNsdInfo(VOS_UINT8 *pData);

VOS_INT32 MM_WasRrDataReq(VOS_UINT8 ucCnDomain, VOS_UINT8 ucPriority,
                          VOS_UINT32 ulSize, VOS_INT8 *pData);

VOS_INT32 MM_GasRrEstReq(VOS_UINT32 ulOpId, VOS_UINT8 ucCnDomain,
                         VOS_UINT32 ulEstCause, IDNNS_STRU *pIdnnsInfo, RRC_PLMN_ID_STRU *pstPlmnId,
                         VOS_UINT32 ulSize, VOS_INT8 *pFisrstMsg);

VOS_INT32 MM_WasRrEstReq(VOS_UINT32 ulOpId, VOS_UINT8 ucCnDomain,
                         VOS_UINT32 ulEstCause, IDNNS_STRU *pIdnnsInfo, RRC_PLMN_ID_STRU *pstPlmnId,
                         VOS_UINT32 ulSize, VOS_INT8 *pFisrstMsg);


VOS_INT32 MM_GasRrRelReq(VOS_UINT8 ucCnDomain,RRC_CELL_BAR_ENUM_UINT32 enBarValidFlg);

/*VOS_INT32 MM_GasRrAbortReq(VOS_UINT32 ulAbortType);*/

VOS_INT32 MM_GasAttachReq(ATTACH_INFO_STRU *pAttachInfo);

VOS_INT32 MM_GasUsimStatusReq(USIM_VALID_INFO_STRU *pUsimValidInfo);

VOS_INT32 MM_GasSecurityKeyChgReq(SECURITY_KEY_INFO_STRU *pSecurityKeyInfo);

VOS_INT32 MM_GasTmsiLaiChgReq(NAS_INFO_TMSI_LAI_STRU *pTmsiLai);

VOS_INT32 MM_GasDelKeyReq(VOS_UINT8 ucCnDomain);


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

#endif /* end of MmGsmDifMsg.h */
