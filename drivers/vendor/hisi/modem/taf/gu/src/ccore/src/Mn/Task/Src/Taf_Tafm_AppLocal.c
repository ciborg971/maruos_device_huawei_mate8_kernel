/******************************************************************************/
/* Copyright (c) ,1988-2001,Huawei Tech. Co.,Ltd                              */
/* File name     :Taf_Tafm_Applocal.c                                               */
/* Author        :zzy                                                         */
/* Description   :1��TAF-APP����API                                           */
/*                2��TAF-MUX���˻ص�API                                       */
/* Others        :                                                            */
/* Function List :                                                            */
/* History       :                                                            */
/*               :2005-04-13 ����                                             */
/*               :2005-10-07 ���ӻ�ȡ��ǰATTACH��DETACH״̬�������޸���:���r  */
/******************************************************************************/

#include "Taf_Tafm_Remote.h"
#include "ExtAppRabmInterface.h"
#include "MmaAppLocal.h"
#include "TafClientApi.h"
#include "TafApsApi.h"
#include "TafAppRabm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_TAFM_APPLOCAL_C


VOS_UINT32   g_enClientIdRegChk = TAF_TRUE;

/*�����ӿ�RabId��ClientId��Ӧ��*/
VOS_UINT16 g_CsRabToClientId[TAF_MAX_RABID + 1] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

VOS_UINT16 g_PsRabToClientId[TAF_MAX_RABID + 1] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
VOS_VOID Api_AppRabmDataInd(ST_APP_RABM_DATA *p)
{
    /* ��g_stMnCallBackFunc[i].regFunc.pDataIndFunc�ص������� */
#if 0
    VOS_UINT16 ClientId;
    VOS_UINT8 i;

    if (VOS_NULL_PTR == p)
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmDataInd:WARNING:p is null ptr." );
        return;
    }
    if ((p->ucDomain > TAF_DATA_PS_DOMAIN) ||
        (p->ucRabId > TAF_MAX_RABID))
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmDataInd:WARNING:Domain or RabId value is error." );
        return;
    }

    /*ClientId*/
    if (TAF_DATA_CS_DOMAIN == p->ucDomain)
    {
        ClientId = g_CsRabToClientId[p->ucRabId];
    }
    else
    {
        ClientId = g_PsRabToClientId[p->ucRabId];
    }

    for (i = 0; i < TAF_MAX_CLIENT_OF_ONE_PROC; i++)
    {   /*����ƥ���ClientId����*/
        if ((TAF_USED == g_stMnCallBackFunc[i].ucUsed) &&
            (ClientId == g_stMnCallBackFunc[i].clientId ))
        {
            break;
        }
    }
    if(i >= TAF_MAX_CLIENT_OF_ONE_PROC)
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmDataInd:WARNING:Can't find match ClientId." );
        return;/*δ�ҵ�ClientId*/
    }

    if ( VOS_NULL_PTR == g_stMnCallBackFunc[i].regFunc.pDataIndFunc )
    {
        TAF_LOG1( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmDataInd:WARNING:Function Pointer is NULL! g_stMnCallBackFunc array index:", i );
        return;
    }

    (*g_stMnCallBackFunc[i].regFunc.pDataIndFunc)
                    (ClientId, p->ucDomain, p->ucRabId, p->ulDataLen, p->pucData);

#endif
    return;
}


VOS_VOID Api_AppRabmStatusInd(ST_APP_RABM_STATUS *p)
{
#if 0
    VOS_UINT16 ClientId;

    if (VOS_NULL_PTR == p)
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmStatusInd:WARNING:p is null ptr." );
        return;
    }
    if ((p->ucDomain > TAF_DATA_PS_DOMAIN) ||
        (p->ucRabId > TAF_MAX_RABID))
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmStatusInd:WARNING:Domain or RabId value is error." );
        return;
    }

    /*ClientId*/
    if (TAF_DATA_CS_DOMAIN == p->ucDomain)
    {
        ClientId = g_CsRabToClientId[p->ucRabId];
    }
    else
    {
        ClientId = g_PsRabToClientId[p->ucRabId];
    }

    /*����APP����״̬�ϱ�����*/
    MN_DATASTATUS_SendMsg(ClientId, p->ucDomain, p->ucRabId, p->ucStatus, p->ucStartCause);
#endif
    return;
}


VOS_VOID Api_AppRabmErrInd(ST_APP_RABM_ERROR *p)
{
    VOS_UINT16 ClientId;

    if (VOS_NULL_PTR == p)
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmErrInd:WARNING:p is null ptr." );
        return;
    }
    if ((p->ucDomain > TAF_DATA_PS_DOMAIN) ||
        (p->ucRabId > TAF_MAX_RABID))
    {
        TAF_LOG( WUEPS_PID_RABM, 0, PS_LOG_LEVEL_WARNING, "Api_AppRabmErrInd:WARNING:Domain or RabId value is error." );
        return;
    }

    /*ClientId*/
    if (TAF_DATA_CS_DOMAIN == p->ucDomain)
    {
        ClientId = g_CsRabToClientId[p->ucRabId];
    }
    else
    {
        ClientId = g_PsRabToClientId[p->ucRabId];
    }

    /*����APP����״̬�ϱ�����*/
    MN_DATASTATUS_SendMsg(ClientId, p->ucDomain, p->ucRabId, TAF_DATA_STOP, p->ucErrType);

    return;
}




#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

