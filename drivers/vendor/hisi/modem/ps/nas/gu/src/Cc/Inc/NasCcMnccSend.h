/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasCcMnccSend.h
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��10��17��
  ����޸�   : 2007��10��17��
  ��������   : MNCCԭ�﷢��ģ��Ľӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��10��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef  NAS_CC_MNCC_SEND_H
#define  NAS_CC_MNCC_SEND_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "NasMncc.h"
#include "NasCcCommon.h"

/*****************************************************************************
  2 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_CC_SendMnccMsg
 ��������  : ���ϲ㷢��MNCCԭ����Ϣ
 �������  : entityId     - CCʵ��ID
             enPrimName   - ԭ������
             pParam       - ԭ��������μ�MNCC_IND_PARAM_UNION
             ulParamLen   - ԭ������ĳ���
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_CC_SendMnccMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    MNCC_PRIM_NAME_ENUM_U16             enPrimName,
    const VOS_VOID                      *pParam,
    VOS_UINT32                          ulParamLen
);

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID  NAS_CC_SendMnccSrvccStatusIndMsg(
    NAS_MNCC_SRVCC_STATUS_ENUM_UINT32   enSrvccSta
);
#endif

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

#endif /* NAS_CC_MNCC_SEND_H */


