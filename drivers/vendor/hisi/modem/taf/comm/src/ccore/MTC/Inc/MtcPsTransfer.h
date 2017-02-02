

#ifndef __MTCPSTRANSFER_H__
#define __MTCPSTRANSFER_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "MtcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 STRUCT����
*****************************************************************************/


/*****************************************************************************
  5 OTHERS����
*****************************************************************************/

/*****************************************************************************
  6 ��������
*****************************************************************************/
VOS_VOID MTC_RcvRrcAreaLostInd(VOS_VOID * pMsg);

VOS_VOID MTC_SndModem0MtaPsTransferInd(
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enPsTransferCause
);

VOS_VOID MTC_SndModem0GmmRrcAreaLostInd(VOS_VOID);


VOS_VOID MTC_SndModem0MmaPsTransferInd(
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enPsTransferCause
);

VOS_VOID MTC_RcvRrcAreaAvaliableInd(VOS_VOID * pMsg);

VOS_VOID MTC_ProcCurrCampPlmnInfoForSvlte(VOS_VOID);

VOS_VOID MTC_ProcCurrCampPlmnInfoForLC(VOS_VOID);

VOS_VOID MTC_RcvGsmCellInfoInd(VOS_VOID *pMsg);



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

#endif /* end of MtcPsTransfer.h */


