

#ifndef __OM_VCOM_PPM_H__
#define __OM_VCOM_PPM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "OmCommonPpm.h"

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
VOS_UINT32 PPM_VComCfgSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen);

VOS_UINT32 PPM_VComCfgReadData(VOS_UINT32 ulDevIndex, VOS_UINT8 *pData, VOS_UINT32 uslength);

VOS_UINT32 PPM_VComIndSendData(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen);

VOS_VOID   PPM_VComCfgPortInit(VOS_VOID);

VOS_VOID   PPM_VComIndPortInit(VOS_VOID);

VOS_VOID   PPM_VComPortInit(VOS_VOID);

VOS_VOID   GU_OamErrLogVComPortInit(VOS_VOID);
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

