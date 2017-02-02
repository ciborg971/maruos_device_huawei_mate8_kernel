/******************************************************************************/
/* Copyright (c) ,1988-2001,Huawei Tech. Co.,Ltd                              */
/* File name     :Taf_Tafm_Db.c                                               */
/* Author        :zzy                                                         */
/* Description   :TAFͨ�Ų�������ģ��                                         */
/* Others        :                                                            */
/* Function List :                                                            */
/* History       :                                                            */
/*               :2005-04-13 ����                                             */

#include "Taf_Common.h"
#include "TafClientApi.h"
#include "Taf_Aps.h"
#include "MmaAppLocal.h"
#include "MnComm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_TAFM_DB_C


/*lint -save -e958 */

/**********************************************************/
/*         ���˱�TAF���õ�ͨ�Ų��������¼��ϱ��ӿ�API     */
/**********************************************************/

VOS_VOID  Taf_ParaSetResult (VOS_UINT16            ClientId,
                         VOS_UINT8                   OpId,
                         TAF_PARA_SET_RESULT      Result,
                         TAF_PARA_TYPE      QueryType,
                         VOS_VOID                     *pPara )
{

    MN_SETPARA_SendMsg(ClientId, OpId, Result, QueryType, pPara);

    return;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

