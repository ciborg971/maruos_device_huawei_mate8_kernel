/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsRam.c
  Description  : SSȫ�ֱ���ʵ��
  Function List:
      1.  NULL
  History:
      1.  ��־��      2004.02.27   �°�����
      2.  ��  ��      2006.11.07   ���ⵥA32D07063
*******************************************************************************/

#include "SsInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/* ʵ�嶨��    */
SS_ENTITY_STRU                  g_SsEntity[SS_MAX_ENTITY_NUM];                  /* SSʵ�嶨��                               */
SS_SAVE_MSG_STRU                g_SsSaveMsg[SS_MO_ENTITY_NUM];                  /* ����REGISTER��Ϣ                         */
/*=>A32D07063*/
#if 0
SS_TIMER_MNG_STRU               g_SsTimerMng[SS_MAX_ENTITY_NUM];                /* SS TIMER����                             */
#endif
/*<=A32D07063*/


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

