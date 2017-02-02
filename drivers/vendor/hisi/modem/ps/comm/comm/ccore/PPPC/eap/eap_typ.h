/************************************************************************
 *                                                                      *
 *                             Eap_typ.h                                *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2010/07/05                                      *
 *  Author:             wangyong                                        *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP��eapЭ��ģ��˽�����ݽṹ                    *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   ����ļ�������eapЭ��ģ���ȫ��˽�����ݽṹ                        *
 *                                                                      *
 ************************************************************************/

#if( VRP_MODULE_LINK_PPP == VRP_YES )

#ifndef      _EAPC_TYPE_H_
#define      _EAPC_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif     /* end of __cplusplus */

/* EAP ID/SUCCESS/FAIL�����ṹ */
typedef struct tagPPP_EAPPAYLOAD_S
{
    UCHAR ucEAPCode;
    UCHAR ucEAPID;
    USHORT usEAPLen;
    UCHAR ucEAPType;
}VOS_PACKED PPP_EAPPAYLOAD_S;

/* EAP ���ƿ����ݽṹ���� */
typedef struct tagPppEAPInfo
{
    PPPINFO_S *pstPppInfo ;         /* PPP���ƿ�ָ�� */
    UCHAR *pucEAP;
    RELTMR_T ulWaitAuthRspTimeID;      /* �ȴ�AAA��Ȩ��Ӧ��ʱ��id */
    RELTMR_T ulRspTimeoutID;           /* �ȴ�EAP��Ӧ��ʱ��ʱ�� */
    RELTMR_T ulRaAUTHTimerID;          /* ����֤��ʱ��ID */
    ULONG ulReqTransmits;           /* �Ѵ���Request���� */
    ULONG ulTimeOutTime;            /* ��ʱʱ�� */
    ULONG ulNowUTCInSec;
    USHORT usEAPLen;                /* EAP ���� */
    UCHAR ucEapRequestID;           /* EAP ����ID */
    UCHAR ucState;                  /* Server ״̬ */
    UCHAR aucState[DIAM_AUTH_STATE_LEN];                  /* AAA��state��Ԫ */
    UCHAR ucStateLen;                  /* state len */
    UCHAR ucRsv[2];
    UCHAR ucUsed : 1;                   /* EAP���ƿ�ʹ�ñ��*/
    UCHAR ucRequestforIdentity : 1;     /* 1:request for identity 0:request from aaa */
    UCHAR ucEAPFlag : 2;                /* EAP ��־λ 0:request 1:Success  2:Fail   */
    UCHAR ucReAuthFlag : 1;
    UCHAR ucFirstFlag : 1;
} PPPEAPINFO_S ;

/* ����MSKʹ�õĽṹ�� */
typedef struct
{
    ULONG state[5];
    ULONG count[2];
    UCHAR buffer[64];
} SHA1_CTX;

typedef union
{
    UCHAR        ucCharDate[64];
    unsigned int uiIntData[16];
} CHAR64LONG16;


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _EAP_TYPE_H_ */

#endif  /* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */

