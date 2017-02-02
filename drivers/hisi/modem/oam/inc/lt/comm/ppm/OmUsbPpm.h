

#ifndef __OM_USB_PPM_H__
#define __OM_USB_PPM_H__

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
VOS_UINT32 PPM_UsbCfgSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen);

VOS_VOID   PPM_UsbCfgPortClose(VOS_VOID);

VOS_VOID   PPM_UsbCfgStatusCB(ACM_EVT_E enPortState);

VOS_VOID   PPM_UsbCfgWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen);

VOS_INT32  PPM_UsbCfgReadDataCB(VOS_VOID);

VOS_VOID   PPM_UsbCfgPortOpen(VOS_VOID);

VOS_VOID   PPM_UsbIndStatusCB(ACM_EVT_E enPortState);

VOS_VOID   PPM_UsbIndWriteDataCB(VOS_UINT8* pucVirData, VOS_UINT8* pucPhyData, VOS_INT lLen);

VOS_VOID   PPM_UsbIndPortOpen(VOS_VOID);

VOS_VOID   PPM_UsbIndPortClose(VOS_VOID);

VOS_UINT32 PPM_UsbIndSendDatav(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen);

VOS_UINT32 PPM_UsbCfgPortInit(VOS_VOID);

VOS_UINT32 PPM_UsbIndPortInit(VOS_VOID);

VOS_UINT32 PPM_UsbPortInit(VOS_VOID);
/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


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

