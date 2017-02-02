/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : CcRabmIf.h
  Description : CC��RABM�ӿ�ͷ�ļ�
  History     :
      1.  ��־�� 2003.12.03   �°�����
      2.��    ��  : 2006��12��4��
        ��    ��  : luojian id:60022475
        �޸�����  : ���� #pragma pack(4)�����ⵥ��:A32D07779
*******************************************************************************/

#ifndef _CC_RABM_INTERFACE_H_
#define _CC_RABM_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
#pragma pack(4)
#define RABMCC_SYNC_IND                       0                                 /* ��Ϣ���Ͷ���                              */

/* ԭ��RABMCC_SYNC_IND RABM-->CC */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
#define    RABMCC_RAB_ACTIVE      0
#define    RABMCC_RAB_INACTIVE    1
    VOS_UINT32                  ulResult ;                                           /* 0��SI����ʹ�ã�1��SI������ʹ��             */
    VOS_UINT32                  ulSi;                                                /* �Ѿ��������ͷ�rab��si                     */
} RABMCC_SYNC_IND_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
