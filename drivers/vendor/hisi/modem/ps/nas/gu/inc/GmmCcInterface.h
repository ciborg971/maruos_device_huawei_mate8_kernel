/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmCcInterface.h
  Description : CC��GMM�ӿ�ͷ�ļ�
  History     :
      1.       2009.05.11   �ļ�ͷ����
*******************************************************************************/
#ifndef _GMM_CC_INTERFACE_H_
#define _GMM_CC_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)
/*******************************************************************************
**************************  GMM��CC ԭ���ʶ  ********************************
*******************************************************************************/

/* GMM���͸�CC��ԭ�� */
#define GMMCC_EMC_NUM_LST_IND                          0

/* ԭ��GMMCC_EMC_NUM_LST_IND�Ľṹ�� */
#define GMMCC_EMERGENCY_NUMBER_MAX_LENGTH              46                       /* Emergency Number information������ֽ��� */
#define GMMCC_EMERGENCY_NUMBER_LISTS_MAX_NUMBER        16                       /* Emergency Number Lists��������         */

typedef struct
{
    VOS_UINT8                           ucCategoryValue;                        /* Emergency Service Category Value         */
    VOS_UINT8                           ucEmcNumLen;
    VOS_UINT8                           aucEmergencyList[GMMCC_EMERGENCY_NUMBER_MAX_LENGTH];
}GMMCC_EMERGENCY_CONTENT_STRU;

/* ԭ��GMMCC_EMC_NUM_LST_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT32                          ulMcc;
    VOS_UINT8                           ucEmergencyNumber;
    VOS_UINT8                           aucReserved[3];
    GMMCC_EMERGENCY_CONTENT_STRU        astEmergencyLists[GMMCC_EMERGENCY_NUMBER_LISTS_MAX_NUMBER];
}GMMCC_EMERGENCY_LIST_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif
