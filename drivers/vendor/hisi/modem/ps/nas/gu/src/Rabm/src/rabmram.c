/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : rabmram.c
  Description  : rabm��ȫ�ֱ�������
  Function List:

  History:
      1.   ��־��      2004.04.01   �¹�����
*******************************************************************************/
#include "rabminclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif



RABM_ENTITY_PS_STRU    g_aRabmPsEnt[RABM_PS_MAX_ENT_NUM];                       /* PS��RABMʵ���ȫ����                     */

RABM_ENTITY_CS_STRU    g_aRabmCsEnt[RABM_CS_MAX_ENT_NUM];                       /* CS��RABMʵ���ȫ����                     */


VOS_UINT8        g_aucSiMapEnt[256];                                                /* SI��RABMʵ���ӳ���ϵ                   */

VOS_UINT8        g_ucReestTimerFlg;                                                 /* RABM_TRUE:�ؽ�TIMER��Ч��RABM_FALSE:��Ч */

HTIMER     g_ulRabReestTimerId;                                               /* rab�ؽ�timer                             */

RABM_RRC_IMPORTED_FUNC_LIST_STRU  g_RabmRrcImportFunc;                          /* API����                                  */

RABM_TC_INF_STRU       g_RabmTcInf;

PDCP_RABM_TC_DATA_Q_STRU g_stPdcpRabmTcDataQ;

VOS_UINT32                              g_ulNasRabmRabPendingTmrLen = 7000;     /* Ĭ��7�� */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

