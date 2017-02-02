

#ifndef __OM_HSIC_PPM_H__
#define __OM_HSIC_PPM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/


/*****************************************************************************
  4 �ṹ�嶨��
*****************************************************************************/


/*****************************************************************************
  4 ��������
*****************************************************************************/
VOS_VOID   PPM_HsicIndWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen);

VOS_INT32  PPM_HsicCfgReadDataCB(VOS_VOID);

VOS_VOID   PPM_HsicCfgWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen);

VOS_VOID   PPM_HsicCfgPortOpen(VOS_VOID);

VOS_VOID   PPM_HsicIndPortOpen(VOS_VOID);

VOS_VOID   PPM_HsicIndPortClose(VOS_VOID);

VOS_VOID   PPM_HsicCfgPortClose(VOS_VOID);

VOS_UINT32 PPM_HsicIndSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen);

VOS_UINT32 PPM_HsicCfgSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen);

VOS_VOID   PPM_HsicIndStatusCB(ACM_EVT_E enPortState);

VOS_VOID   PPM_HsicCfgStatusCB(ACM_EVT_E enPortState);

VOS_VOID   PPM_HsicPortInit(VOS_VOID);

VOS_VOID   PPM_HsicConnectProc(VOS_VOID);

VOS_VOID   PPM_HsicDisconnectProc(VOS_VOID);

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/
extern VOS_SEM                                 g_ulOmAcpuHsicSem;


/*****************************************************************************
  6 OTHERS����
*****************************************************************************/




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

#endif /* end of OmCommonPpm.h*/

