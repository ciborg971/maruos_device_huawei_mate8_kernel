/******************************************************************************

                  ��Ȩ���� (C), 2005-2007, ��Ϊ�������޹�˾


  �� �� ��   : Nas_Mem.h
  �� �� ��   : ����
  ��    ��   : liuyang id:48197
  ��������   : 2006��4��27��
  ����޸�   :
  ��������   : NAS���ڴ�궨��ͷ�ļ�
  �����б�   :
      ---
      ---
      ---
  �޸���ʷ   :
  1.��    ��   : 2006��4��27��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ļ�
  2.��    ��   : 2006��4��27��
    ��    ��   : ---
    �޸�����   : Add function ... ���ⵥ��:

******************************************************************************/

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/******************************************************************************
   1 ͷ�ļ�����
 *****************************************************************************/
#include "Ps.h"

/*****************************************************************************
   2 �ڲ�����ԭ��˵��
 *****************************************************************************/

/*****************************************************************************
   3 ȫ�ֱ�������
 *****************************************************************************/

/*****************************************************************************
   4 ģ�鼶����
 *****************************************************************************/

/*****************************************************************************
   5 ��������
 *****************************************************************************/

/*****************************************************************************
   6 �궨��
 *****************************************************************************/
#define PS_NAS_MEM_CPY(pDestBuffer, pSrcBuffer, ulBufferLen)\
            PS_MEM_CPY((pDestBuffer), (pSrcBuffer), (ulBufferLen))

#define PS_NAS_MEM_SET(pBuffer, ucData, ulBufferLen) \
            PS_MEM_SET((pBuffer), (ucData), (ulBufferLen))

#define PS_NAS_MEM_MOVE(pDestBuffer, pSrcBuffer, ulBufferLen) \
            PS_MEM_MOVE((pDestBuffer), (pSrcBuffer), (ulBufferLen))

#define PS_NAS_MEM_ALLOC(ulPid, ulSize, ulWaitOption) \
            PS_MEM_ALLOC((ulPid), (ulSize))

#define PS_NAS_MEM_FREE(ulPid, pAddr) \
            PS_MEM_FREE((ulPid), (pAddr))

/*PS_NAS_VOS_MEM_ALLOC ���� VOS_MemAlloc*/
#define PS_NAS_VOS_MEM_ALLOC(ulPid, ucPtNo, ulSize)\
            PS_MEM_ALLOC((ulPid), (ulSize))

/*PS_NAS_VOS_MEM_FREE ���� VOS_MemFree*/
#define PS_NAS_VOS_MEM_FREE(ulPid, ulSize)\
            PS_MEM_FREE((ulPid), (ulSize))

/*==============================================*/
#define PS_CC_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC(WUEPS_PID_CC, (ulSize))

#define PS_SM_MEM_ALLOC(ulPid, ulSize, ulWaitOption)\
            PS_NAS_MEM_ALLOC(WUEPS_PID_SM, (ulSize), (ulWaitOption))

#define PS_SMS_MEM_ALLOC(ulPid, ulSize, ulWaitOption)\
            PS_NAS_MEM_ALLOC(WUEPS_PID_SMS, (ulSize), (ulWaitOption))

#define PS_SS_MEM_ALLOC(ulPid, ulSize, ulWaitOption)\
            PS_NAS_MEM_ALLOC(WUEPS_PID_SS, (ulSize), (ulWaitOption))

#define PS_TC_MEM_ALLOC(ulPid, ulSize, ulWaitOption)\
            PS_NAS_MEM_ALLOC(WUEPS_PID_TC, (ulSize), (ulWaitOption))

#define PS_SMT_MEM_ALLOC(ulPid, ulSize, ulWaitOption)\
            PS_NAS_MEM_ALLOC(WUEPS_PID_SMT, (ulSize), (ulWaitOption))

#define PS_NASAPI_MEM_ALLOC(ulPid, ulSize, ulWaitOption)\
            PS_NAS_MEM_ALLOC(WUEPS_PID_ADMIN, (ulSize), (ulWaitOption))

#define PS_RABM_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC(WUEPS_PID_RABM, (ulSize))


#define PS_CC_MEM_FREE(pAddr)\
            PS_MEM_FREE(WUEPS_PID_CC, (pAddr))

#define PS_SM_MEM_FREE(ulPid, pAddr)\
            PS_NAS_MEM_FREE(WUEPS_PID_SM, (pAddr))

#define PS_SMS_MEM_FREE(ulPid, pAddr)\
            PS_NAS_MEM_FREE(WUEPS_PID_SMS, (pAddr))

#define PS_SS_MEM_FREE(ulPid, pAddr)\
            PS_NAS_MEM_FREE(WUEPS_PID_SS, (pAddr))

#define PS_TC_MEM_FREE(ulPid, pAddr)\
            PS_NAS_MEM_FREE(WUEPS_PID_TC, (pAddr))

#define PS_SMT_MEM_FREE(ulPid, pAddr)\
            PS_NAS_MEM_FREE(WUEPS_PID_SMT, (pAddr))

#define PS_NASAPI_MEM_FREE(ulPid, pAddr)\
            PS_NAS_MEM_FREE(WUEPS_PID_ADMIN, (pAddr))

#define PS_RABM_MEM_FREE(pAddr)\
            PS_MEM_FREE(WUEPS_PID_RABM, (pAddr))



#define MMC_MEM_ALLOC(ulPoolIdIndex,ulSize,ulWaitOption) PS_MEM_ALLOC(WUEPS_PID_MMC, (ulSize))
#define MMC_MEM_FREE(ulPoolIdIndex,pAddr) PS_MEM_FREE(WUEPS_PID_MMC, pAddr)

#define MM_MEM_ALLOC(ulPoolIdIndex,ulSize,ulWaitOption) PS_MEM_ALLOC(WUEPS_PID_MM,(ulSize))
#define MM_MEM_FREE(ulPoolIdIndex,pAddr) PS_MEM_FREE(WUEPS_PID_MM, pAddr)



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


