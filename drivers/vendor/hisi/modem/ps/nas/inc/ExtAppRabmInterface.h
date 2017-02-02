/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : ExtAppRabmInterface.h
  Author      : ---
  Version     : V200R001
  Date        : 2005-08-17
  Description : Э��ջ���RABM��APP�ӿ�ͷ�ļ�
  History     :
  1. Date:2005-08-17
     Author: ---
     Modification:Create
  2. ��    ��  : 2006��12��4��
     ��    ��  : luojian id:60022475
     �޸�����  : ���� #pragma pack(4)�����ⵥ��:A32D07779
************************************************************************/

#ifndef _EXT_APP_RABM_INTERFACE_H_
#define _EXT_APP_RABM_INTERFACE_H_

#include "PsTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

#pragma pack(4)
/* ------------------------------API �����ṹ---------------------------------*/

#define    D_RABM_CS_DOMAIN    0
#define    D_RABM_PS_DOMAIN    1


#define    APP_RABM_MAX_ENT_NUM   11


typedef struct {
    VOS_UINT8      ucDomain;
    VOS_UINT8      ucRabId;
    VOS_UINT32      ulDataLen;
    VOS_UINT8*     pucData;
} ST_APP_RABM_DATA;


typedef struct {
    VOS_UINT8      ucDomain;
    VOS_UINT8      ucRabId;
    VOS_UINT8      ucStatus;
    #define    D_RABM_STOP_DATA    0
    #define    D_RABM_START_DATA   1

    VOS_UINT8      ucStartCause;
    #define    D_RABM_START_CAUSE_REEST_FAILURE     0
    #define    D_RABM_START_CAUSE_REEST_SUCCESS     1
    #define    D_RABM_START_CAUSE_RRC_INDICATION    2
} ST_APP_RABM_STATUS;


typedef struct {
    VOS_UINT8      ucDomain;
    VOS_UINT8      ucRabId;
    VOS_UINT8      ucErrType;                                                       /* reserved                                 */
} ST_APP_RABM_ERROR;



typedef struct
{
    /*
    aucByteRateList[i][0] == n : Rabid;
    aucByteRateList[i][1] == xx: The byte rate for uplink of Rabid n.
    aucByteRateList[i][2] == xx: The byte rate for downlink of Rabid n.
    The number XX means XX bytes per second.
    "i" belongs to [0, 10].
    "n" belongs to [5, 15].*/

    VOS_UINT8                           ucRabidNum;   /*�������˼���NSAPI*/
    VOS_UINT32                          aulByteRateList[APP_RABM_MAX_ENT_NUM][3];
}APP_RABM_ALL_RATE_ST;       /*����Э�̵���������(���м����RABID)*/

typedef struct
{
    /*0 - The Rabid is not actived.
      1 - The Rabid is activated */
    VOS_UINT8                           ucFlag;

    /*The number XX means XX bytes per second.*/
    VOS_UINT32                          ulUplinkByteRate;
    VOS_UINT32                          ulDownlinkByteRate;
}APP_RABM_ONE_RATE_ST;      /*����Э�̵���������(ָ����RABID)*/


typedef struct
{
    /*
    aucByteRatioList[i][0] == n : NSAPI;
    aucByteRatioList[i][1] == xx: The byte ratio for uplink of NSAPI n.
    aucByteRatioList[i][2] == xx: The byte ratio for downlink of NSAPI n.
    The number XX means XX K bytes per second.
    "i" belongs to [0, 10]. */

    VOS_UINT8       ucNsapiNum;         /*�������˼���NSAPI*/
    VOS_UINT32      aulByteRatioList[APP_RABM_MAX_ENT_NUM][3];
}APP_RABM_CURRENT_RATE_ST;     /*�������õ���������*/


typedef struct
{
    VOS_UINT32                          ulDSLastLinkTime;                        /*���һ��DS����ʱ��*/
    VOS_UINT32                          ulDSLastSendFluxLow;                     /*���һ��DS�����������ĸ��ֽ�*/
    VOS_UINT32                          ulDSLastSendFluxHigh;                    /*���һ��DS�����������ĸ��ֽ�*/
    VOS_UINT32                          ulDSLastReceiveFluxLow;                  /*���һ��DS�����������ĸ��ֽ�*/
    VOS_UINT32                          ulDSLastReceiveFluxHigh;                 /*���һ��DS�����������ĸ��ֽ�*/
    APP_RABM_CURRENT_RATE_ST            stCurrentRate;                           /*��ǰ�������������*/
    /*�������Э�̺�ȷ����PDP���ӷ��͡����ӽ�������*/
    APP_RABM_ALL_RATE_ST                stFluxRate;

}APP_RABM_DS_FLOW_REPORT_ACCUMULATE_ST;      /*�ϱ�����NSAPI���ۼ�����ʱ���õ����ݽṹ*/

typedef struct
{
    VOS_UINT8                           ucRabId;                                /*��Ӧ��RABID*/
    VOS_UINT32                          ulDSLastLinkTime;                       /*���һ��DS����ʱ��*/
    VOS_UINT32                          ulDSLastSendFluxLow;                    /*���һ��DS�����������ĸ��ֽ�*/
    VOS_UINT32                          ulDSLastSendFluxHigh;                   /*���һ��DS�����������ĸ��ֽ�*/
    VOS_UINT32                          ulDSLastReceiveFluxLow;                 /*���һ��DS�����������ĸ��ֽ�*/
    VOS_UINT32                          ulDSLastReceiveFluxHigh;                /*���һ��DS�����������ĸ��ֽ�*/
    VOS_UINT32                          ulCurrentSendRate;                      /*��ǰ��������*/
    VOS_UINT32                          ulCurrentReceiveRate;                   /*��ǰ��������*/
    /*�������Э�̺�ȷ����PDP���ӷ��͡���������*/
    APP_RABM_ONE_RATE_ST                stFluxRate;
}APP_RABM_DS_FLOW_REPORT_WITH_RABID_ST;        /*DS�����ϱ�ʱ���õ����ݽṹ(ָ��RABID�������)*/


typedef struct
{
    VOS_UINT8                               ucNsapiNum;         /*�������˼���NSAPI*/
    APP_RABM_DS_FLOW_REPORT_WITH_RABID_ST   DsFlowReportTotal[APP_RABM_MAX_ENT_NUM];

}APP_RABM_DS_FLOW_REPORT_TOTAL_ST;              /*�ϱ�����NSAPI������ʱ���õ����ݽṹ*/

typedef struct
{
    VOS_UINT8                               ucDomain;
    VOS_UINT8                               ucRabId;
    APP_RABM_DS_FLOW_REPORT_WITH_RABID_ST   stDsFlowReportWithRabId;

}ST_APP_RABM_DS_FLOW;                                  /*�����ϱ��ӿ�Api_AppRabmDSFlowInd���õ����ݽṹ*/







/*Added by Jim for asn.1 begin*/
/*_H2ASN_Include wuepsosa_msg.h*/
typedef struct
{
    VOS_UINT32           ulMsgChoice;        /* message name */

    #define TAFRABM_DATA            0
    #define TAFRABM_STATUS          1
    #define TAFRABM_ERROR           2

    union  {
        ST_APP_RABM_DATA            RabmData;
        ST_APP_RABM_STATUS          RabmStatus;
        ST_APP_RABM_ERROR           RabmError;
        /* ... */
    } u;
}ST_RABM_MSG;

typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                  /* ��Ϣͷ                                   */
    ST_RABM_MSG                     stRabmMsg;
}APP_RABM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    APP_RABM_MSG_DATA                MsgData;
}AppRabmInterface_MSG;
/*Added by Jim for asn.1 end*/


/* ------------------------------API �ⲿ����---------------------------------*/

extern VOS_VOID Api_AppRabmDataReq(ST_APP_RABM_DATA  *p);
extern VOS_VOID Api_AppRabmDataInd(ST_APP_RABM_DATA  *p);
extern VOS_VOID Api_AppRabmStatusInd(ST_APP_RABM_STATUS  *p);
extern VOS_VOID Api_AppRabmErrInd(ST_APP_RABM_ERROR  *p);

extern VOS_VOID NAS_RabmAppDataTransReq( ST_APP_RABM_DATA  *pRabmDataReq );
extern VOS_VOID Api_AppRabmDSFlowInd( ST_APP_RABM_DS_FLOW *pstDSFLow );

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

