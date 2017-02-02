/*****************************************************************************
//
//                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾
//
*****************************************************************************
//  �� �� ��   : msp_nvim.h
//  �� �� ��   : V1.0
//  ��������   : 2008��07��07��
//  ��������   : NV�����ӿڣ�������д��ɾ�������NV��Ĳ���.
//  �����б�   : NVM_Read, NVM_Write
//  �޸���ʷ   :
//  1.��    �� : 2008��07��07��
//    �޸����� : �����ļ�
//
*****************************************************************************/

#ifndef __MSP_NVIM_H__
#define __MSP_NVIM_H__

#include "vos.h"
#include "NVIM_Interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#if defined (INSTANCE_1)
#ifndef NVM_Read
#define NVM_Read(usID,pItem,ulLength)                NV_ReadEx(MODEM_ID_1,(VOS_UINT16)(usID),(pItem),(VOS_UINT32)(ulLength))
#endif
#ifndef NVM_Write
#define NVM_Write(usID,pItem,ulLength)               NV_WriteEx(MODEM_ID_1,(VOS_UINT16)(usID),(pItem),(VOS_UINT32)(ulLength))
#endif
#else
#ifndef NVM_Read
#define NVM_Read(usID,pItem,ulLength)                NV_ReadEx(MODEM_ID_0,(VOS_UINT16)(usID),(pItem),(VOS_UINT32)(ulLength))
#endif
#ifndef NVM_Write
#define NVM_Write(usID,pItem,ulLength)               NV_WriteEx(MODEM_ID_0,(VOS_UINT16)(usID),(pItem),(VOS_UINT32)(ulLength))
#endif
#endif
#ifndef NVM_GetItemLength
#define NVM_GetItemLength(usID, pulLength)           NV_Get16BitLength((usID), (pulLength))
#endif
#ifndef NVM_Flush
#define NVM_Flush()                                  NV_Flush()
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /* __MSP_DIAG_H__*/

