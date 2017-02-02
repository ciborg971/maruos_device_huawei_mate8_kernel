/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : Taf_ApsForSndcp.h
  Author      : ��³��
  Version     : V200R001
  Date        : 2005-0
  Description : ��ͷ�ļ�������---
  History     :
  1. Date:2005-0 -
     Author: ---
     Modification:Create
  2. 2006-02-28 modify by ��³�� for A32D02262 �ӿ����ݽṹ4�ֽڶ���
  3. 2006-08-09 modify by ����Ƽ for A32D03479 ��PC����ʵ��ʱ��#pragma pack(0)��#pragma pack()�ӱ��뿪��
************************************************************************/

#ifndef _TAF_APSFORSNDCP_H
#define _TAF_APSFORSNDCP_H


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include    "vos.h"
#include    "RabmInterface.h"
#include    "SNInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#pragma pack(4)

/*****************************************************************************
  2 �궨��
  #define
*****************************************************************************/
/*��Ϣ����*/
#define APS_SN_ACT_IND_MSG_TYPE         ID_SM_ACT_IND
#define APS_SN_ACT_RSP_MSG_TYPE         ID_SM_ACT_RSP

#define APS_SN_MDF_IND_MSG_TYPE         ID_SM_MODIFY_IND
#define APS_SN_MDF_RSP_MSG_TYPE         ID_SM_MODIFY_RSP

#define APS_SN_DEACT_IND_MSG_TYPE       ID_SM_DEACT_IND
#define APS_SN_DEACT_RSP_MSG_TYPE       ID_SM_DEACT_RSP

#define APS_SN_STATUS_REQ_MSG_TYPE      ID_SM_STATUS_REQ

#define APS_SN_XID_REQ_MSG_TYPE         ID_SN_XID_REQ
#define APS_SN_XID_CNF_MSG_TYPE         ID_SN_XID_CNF

#define APS_SN_XID_IND_MSG_TYPE         ID_SN_XID_IND
#define APS_SN_XID_RSP_MSG_TYPE         ID_SN_XID_RSP


/*�ӿڲ���*/
#define APS_SN_REL_LLC                  1
#define APS_SN_NOT_REL_LLC              0

#define APS_SN_XID_NEGO                 1
#define APS_SN_XID_NOT_NEGO             0

#ifndef APS_NSAPI_MAX
#define APS_NSAPI_MAX                   15
#endif

#ifndef APS_MAX_PDP_NUM
#define APS_MAX_PDP_NUM                 11
#endif

#define APS_ACT_SN_NORMAL               0                   /*��������SNDCP*/
#define APS_ACT_SN_SYS_CHNG             1                   /*3G->2G�л�����SNDCP*/
/*******************************************************************************
  3 ö�ٶ���
  typedef enum
{
    MAPS_TEMPLATE_ENUM1 = 0,
    MAPS_TEMPLATE_ENUM2


    MAPS_TEMPLATE_BUTT,

}MAPS_TEMPLATE_ENUM;
*******************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
extern VOS_UINT8* pgucMapsTemplateBuffer;
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
    ģ���������士HEADER
#define MAPS_TEMPLATE_HEADER    VOS_UINT16    usTotalsMsgLen;\
                                VOS_UINT32    ulSendModuleId;\
                                VOS_UINT32    ulRecvModuleId;
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
  typedef struct
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];

} MAPS_TEMPLATE_ST;
*****************************************************************************/
typedef struct {
    VOS_UINT32                          ulCnt;
    #if(PS_UE_REL_VER < PS_PTL_VER_R5)
    VOS_UINT8                           ReqQos[11];
    VOS_UINT8                           ucRsv;              /*����4�ֽڶ���*/
    #elif(PS_UE_REL_VER <= PS_PTL_VER_R6)
    VOS_UINT8                           ReqQos[14];
    VOS_UINT8                           aucRsv[2];          /*����4�ֽڶ���*/
    #else
    VOS_UINT8                           ReqQos[16];
    #endif
} APS_ST_QOS;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~APS->SNDCP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct
{
    VOS_UINT8                           ucActSndcpType;     /*#define APS_ACT_SN_NORMAL     0
                                                              #define APS_ACT_SN_SYS_CHNG   1 */
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;    /*Refer to 24.008 10.5.7.2*/
    VOS_UINT32                          ulTLLI;
    APS_ST_QOS                          NegoQos;            /*Refer to ExtAppCmInterface.h*/
    SN_XID_REQ_ST                       XidParameter;       /*Refer to SNDCP-DS*/
} APS_SNDCP_ACTIVATE_IND_ST;

typedef struct
{
    /*If this MSG has SNPduNum, flag "OP_SNPduNum" is set 1,
    otherwise "OP_SNPduNum" should be set 0*/
    VOS_UINT32                          OP_SNPduNum : 1;

    /*If this MSG has RNPduNum, flag "OP_RNPduNum" is set 1,
    otherwise "OP_RNPduNum" should be set 0*/
    VOS_UINT32                          OP_RNPduNum : 1;
    VOS_UINT32                          SPARE       : 30;

    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;    /*Refer to 24.008 10.5.7.2*/
    VOS_UINT8                           ucReserved;         /*����4�ֽڶ���*/
    VOS_UINT32                          ulTLLI;
    APS_ST_QOS                          NegoQos;            /*Refer to ExtAppCmInterface.h*/
    RABM_SNDCP_SEND_N_PDU_NUM_LIST_ST   SNPduNum;           /*Refer to Rabm.h*/
    RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST   RNPduNum;           /*Refer to Rabm.h*/
}APS_SNDCP_MODIFY_IND_ST;

typedef struct
{
    VOS_UINT8                           ucNsapi;

    /*ucLLCReleaseInd == 1 :            Release LLC
                      == 0 :            Not Release LLC
    #define APS_SN_REL_LLC              1
    #define APS_SN_NOT_REL_LLC          0
    ���汾V200R01һ����ͷ�LLC */
    VOS_UINT8                           ucLLCReleaseInd;

    /*ucXIDNegoInd    == 1 :            Negotiation
                      == 0 :            Not Negotiation
    #define APS_SN_XID_NEGO             1
    #define APS_SN_XID_NOT_NEGO         0
    ���汾V200R01һ����Э��XID */
    VOS_UINT8                           ucXIDNegoInd;
    VOS_UINT8                           ucReserved;         /*����4�ֽڶ���*/
    VOS_UINT32                          ulTLLI;
}APS_SNDCP_DEACTIVATE_IND_ST;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SNDCP->APS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct
{
    VOS_UINT32                          ulTLLI;
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucRsv;              /*����4�ֽڶ���*/
    VOS_UINT16                          usRsv;              /*����4�ֽڶ���*/
} APS_NSAPI_AND_TLLI_ST;

typedef struct
{
    VOS_UINT32                          ulTLLI;
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucRsv;              /*����4�ֽڶ���*/
    VOS_UINT16                          usRsv;              /*����4�ֽڶ���*/
    SN_XID_REQ_ST                       XidParameter;       /*Refer to SNDCP-DS*/
} APS_SNDCP_ACTIVATE_RSP_ST;

typedef APS_NSAPI_AND_TLLI_ST           APS_SNDCP_MODIFY_RSP_ST;
typedef APS_NSAPI_AND_TLLI_ST           APS_SNDCP_DEACTIVATE_RSP_ST;

typedef struct
{
    VOS_UINT32                          ulTLLI;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRsv;              /*����4�ֽڶ���*/
    VOS_UINT16                          usSnCause;          /*Refer to SNDCP-DS*/
}APS_SNDCP_STATUS_REQ_ST;

typedef struct
{
    VOS_UINT8                           ucFlg;              /*0-��Ч,1-��Ч;*/
    VOS_UINT8                           ucRsv;              /*����4�ֽڶ���*/
    VOS_UINT16                          usRsv;              /*����4�ֽڶ���*/
    SN_XID_REQ_ST                       XidParameter;       /*Refer to SNDCP-DS*/
}APS_SNDCP_XID_REQ_TAB_ST;

/*****************************************************************************
  8 UNION����
  typedef union
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];

} MAPS_TEMPLATE_UNION;
*****************************************************************************/
/*
typedef union
{
    APS_SNDCP_ACTIVATE_RSP_MSG          SnActRsp;
    APS_SNDCP_MODIFY_RSP_MSG            SnMdfRsp;
    APS_SNDCP_DEACTIVATE_RSP_MSG        SnDeActRsp;
} APS_SN_RSP_DATA_UNION;
*/

/*****************************************************************************
  6 ��Ϣ����
  typedef struct
{
    MAPS_TEMPLATE_HEADER
    VOS_UINT8    aucData[2];
} MAPS_TEMPLATE_MSG;
*****************************************************************************/
typedef struct{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*��Ϣ����*/

    /*��ucNsapi;��Χ�������SN_DATA_REQ_ST�е�˵�����ֶ�����Ϣ�����ӽ��̱�ʾ*/
    VOS_UINT16                          usPId;

    APS_SNDCP_ACTIVATE_IND_ST           ApsSnActInd;
} APS_SNDCP_ACTIVATE_IND_MSG;

typedef struct{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*��Ϣ����*/

    /*��ucNsapi;��Χ�������SN_DATA_REQ_ST�е�˵�����ֶ�����Ϣ�����ӽ��̱�ʾ*/
    VOS_UINT16                          usPId;

    APS_SNDCP_MODIFY_IND_ST             ApsSnMdfInd;
} APS_SNDCP_MODIFY_IND_MSG;

typedef struct{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*��Ϣ����*/

    /*��ucNsapi;��Χ�������SN_DATA_REQ_ST�е�˵�����ֶ�����Ϣ�����ӽ��̱�ʾ*/
    VOS_UINT16                          usPId;

    APS_SNDCP_DEACTIVATE_IND_ST         ApsSnDeActInd;
} APS_SNDCP_DEACTIVATE_IND_MSG;


typedef struct{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*��Ϣ����*/

    /*��ucNsapi;��Χ�������SN_DATA_REQ_ST�е�˵�����ֶ�����Ϣ�����ӽ��̱�ʾ*/
    VOS_UINT16                          usPId;

    APS_SNDCP_ACTIVATE_RSP_ST           ApsSnActRsp;
} APS_SNDCP_ACTIVATE_RSP_MSG;

typedef struct{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*��Ϣ����*/

    /*��ucNsapi;��Χ�������SN_DATA_REQ_ST�е�˵�����ֶ�����Ϣ�����ӽ��̱�ʾ*/
    VOS_UINT16                          usPId;

    APS_SNDCP_MODIFY_RSP_ST             ApsSnMdfRsp;
} APS_SNDCP_MODIFY_RSP_MSG;

typedef struct{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*��Ϣ����*/

    /*��ucNsapi;��Χ�������SN_DATA_REQ_ST�е�˵�����ֶ�����Ϣ�����ӽ��̱�ʾ*/
    VOS_UINT16                          usPId;

    APS_SNDCP_DEACTIVATE_RSP_ST         ApsSnDeActRsp;
} APS_SNDCP_DEACTIVATE_RSP_MSG;

typedef struct{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*��Ϣ����*/

    /*��ApsSnStatusReq��ucSapi��ֵ*/
    VOS_UINT16                          usPId;

    APS_SNDCP_STATUS_REQ_ST             ApsSnStatusReq;
}APS_SNDCP_STATUS_REQ_MSG;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*��Ϣ����*/
    /*��ucNsapi;��Χ�������SN_DATA_REQ_ST�е�˵�����ֶ�����Ϣ�����ӽ��̱�ʾ*/
    VOS_UINT16                          usPId;
    SN_XID_REQ_ST                       stXid;
}APS_SN_XID_REQ_MSG;

typedef APS_SN_XID_REQ_MSG              APS_SN_XID_RSP_MSG;
typedef APS_SN_XID_REQ_MSG              APS_SN_XID_IND_MSG;
typedef APS_SN_XID_REQ_MSG              APS_SN_XID_CNF_MSG;

/*****************************************************************************
  8 FUNCTIONS����
*****************************************************************************/

/*****************************************************************************
  8 OTHERS����
*****************************************************************************/

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

#endif /* end of MapsTemplate.h*/
