/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCallFacilityEncode.h
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��8��29��
  ����޸�   : 2007��8��29��
  ��������   : ��������������ģ��Ľӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��8��29��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef  MN_CALL_BC_PROC_H
#define  MN_CALL_BC_PROC_H

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallApi.h"
#include "NasCcIe.h"
#include "MnCallFacilityDecode.h"
#include "product_config.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ��������
*****************************************************************************/


/*****************************************************************************
  3���Ͷ���
*****************************************************************************/
typedef struct
{
    VOS_BOOL                            bUsed;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucInvokeId;
    VOS_UINT8                           ucOperateCode;
    VOS_UINT8                           aucReserved[1];
}MN_CALL_SS_ID_TABLE_STRU;



/*****************************************************************************
  4 �궨��
*****************************************************************************/
#define MN_CALL_INVALID_TI              0xff


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/
extern MN_CALL_SS_ID_TABLE_STRU g_stCallInvokeIdTable[MN_CALL_MAX_INVOKE_NUM];


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/

VOS_UINT32 MN_CALL_FacilityEncode(
    VOS_UINT8                           *pucDest,
    const MN_CALL_SS_COMPONENT_UNION    *punComponent
);


VOS_VOID MN_CALL_SimpleFacilityEncode(
    VOS_UINT8                           *pucDest,
    const MN_CALL_SS_COMPONENT_UNION    *punComponent
);

/*****************************************************************************
 Prototype      : MN_CALL_InvokeId_Free()
 Description    : ����InvokeId
 Input          : ucInvokeId: Ҫ�ͷŵ�ucInvokeId
 Output         :
 Return Value   : SPEECH_SUCCESS  �ͷųɹ�
                : SPEECH_ERROR    �ͷ�ʧ��
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
VOS_VOID MN_CALL_InvokeId_Free(
    VOS_UINT8                           ucInvokeId
);


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

#endif /* MN_CALL_BC_PROC_H */

