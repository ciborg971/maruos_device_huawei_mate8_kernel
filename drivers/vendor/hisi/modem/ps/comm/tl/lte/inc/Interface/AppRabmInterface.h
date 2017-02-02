

#ifndef __APPRABMINTERFACE_H__
#define __APPRABMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "AppNasComm.h"
#include  "LUPZeroCopy.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
/*IP��ַ���Ⱥ궨��*/
#define APP_MAX_IPV4_ADDR_LEN                               4
#define APP_MAX_IPV6_ADDR_LEN                               16


/*APP->RABM Command��Ϣǰ3���ֽں궨�� APP->RABM*/
#define APP_ERABM_MSG_ID_HEADER                               0x03C01300

/*RABM->APP Command��Ϣǰ3���ֽں궨�� RABM->APP*/
#define ERABM_APP_MSG_ID_HEADER                               0x0313C000
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : APP_ERABM_MSG_TYPE_ENUM
 ö��˵��  : APP��RABM��Ϣȡֵ
*****************************************************************************/
enum APP_ERABM_MSG_TYPE_ENUM
{
    /*���ݴ���ԭ��*/
    ID_APP_ERABM_DATA_TRANS_REQ     = 0x01|APP_ERABM_MSG_ID_HEADER,  /*APP����RABM����Ϣ*/
    ID_APP_ERABM_DATA_TRANS_CNF     = 0x02|ERABM_APP_MSG_ID_HEADER,  /*RABM����APP����Ϣ*/

    ID_APP_ERABM_SERVICE_REQ        = 0x03|APP_ERABM_MSG_ID_HEADER,  /*APP����RABM����Ϣ*/

    ID_APP_ERABM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 APP_ERABM_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : APP_ERABM_DATA_TRANS_OPERATE_ENUM
 ö��˵��  : ���ݴ��������ʶ
*****************************************************************************/
enum APP_ERABM_DATA_TRANS_OPERATE_ENUM
{
    /*���ݴ������ԭ��*/
    APP_ERABM_START_DATA_TRANS     = 0x01,                       /*�������ݴ���*/
    APP_ERABM_STOP_DATA_TRANS      = 0x02,                       /*ֹͣ���ݴ���*/

    APP_ERABM_DATA_TRANS_OPERATE_BUTT
};
typedef VOS_UINT32 APP_ERABM_DATA_TRANS_OPERATE_ENUM_UINT32;

/*****************************************************************************
 ö����    : APP_ERABM_DATA_TRANS_SET_RESULT_ENUM
 ö��˵��  : ���ݴ���������ý��ȡֵ
*****************************************************************************/
enum APP_ERABM_DATA_TRANS_SET_RESULT_ENUM
{
    APP_ERABM_DATA_TRANS_SET_SUCCESS            = 0x00,     /*RABMģ���������ݴ�������ɹ�*/
    APP_ERABM_DATA_TRANS_SET_FAIL,                          /*RABMģ���������ݴ������ʧ��*/
    APP_ERABM_DATA_TRANS_SET_BUTT
};
typedef VOS_UINT32 APP_ERABM_DATA_TRANS_SET_RESULT_ENUM_UINT32;


/*****************************************************************************
 ö����    : APP_ERABM_TRANSFER_RESULT_ENUM
 ö��˵��  : APP�������ȡֵ
*****************************************************************************/
enum APP_ERABM_TRANSFER_RESULT_ENUM
{
    APP_ERABM_TRANSFER_RESULT_SUCC       = 0x00,
    APP_ERABM_TRANSFER_RESULT_FAIL       = 0x01,
    APP_ERABM_TRANSFER_RESULT_BUTT
};
typedef VOS_UINT32 APP_ERABM_TRANSFER_RESULT_ENUM_UINT32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : APP_ERABM_DATA_TRANS_INFO_STRU
 �ṹ˵��  : ���ݴ����������ṹ
*****************************************************************************/

typedef struct
 {
     VOS_UINT32                                           bitOpIpv4 : 1;
     VOS_UINT32                                           bitOpIpv6 : 1;
     VOS_UINT32                                           bitOpSpare: 30;

     VOS_UINT16                                           usIpv4SingleRmtPort;
     VOS_UINT16                                           usIpv6SingleRmtPort;
     APP_ERABM_DATA_TRANS_OPERATE_ENUM_UINT32              enSetOpType;  /*�������ݴ����������:0:����,1:ֹͣ*/


     VOS_UINT8                                            aucRmtIpv4Address[APP_MAX_IPV4_ADDR_LEN];
                                                                       /*ucSourceIpAddress[0]ΪIP��ַ���ֽ�λ
                                                                       ucSourceIpAddress[3]Ϊ���ֽ�λ*/
     VOS_UINT8                                            aucRmtIpv6Address[APP_MAX_IPV6_ADDR_LEN];
                                                                       /*ucRmtIpv6Address[0]ΪIPv6�ӿڱ�ʶ���ֽ�λ
                                                                       ucRmtIpv6Address[7]ΪIPv6�ӿڱ�ʶ���ֽ�λ*/
 }APP_ERABM_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : APP_ERABM_DATA_TRANS_REQ_STRU
 �ṹ˵��  : ���ݴ����������ṹ
*****************************************************************************/
 typedef struct
 {
     VOS_MSG_HEADER
     VOS_UINT32                                           ulMsgId;
     APP_MSG_HEADER

     APP_ERABM_DATA_TRANS_INFO_STRU                        stDataTransInfo;

 }APP_ERABM_DATA_TRANS_REQ_STRU;

/*****************************************************************************
 �ṹ��    : APP_ERABM_DATA_TRANS_CNF_STRU
 �ṹ˵��  : ���ݴ��������Ӧ�ṹ
*****************************************************************************/
 typedef struct
 {
     VOS_MSG_HEADER
     VOS_UINT32                                           ulMsgId;
     APP_MSG_HEADER

     APP_ERABM_DATA_TRANS_SET_RESULT_ENUM_UINT32            enSetOpRslt;  /*�������ݴ����������:0:�ɹ�,1:ʧ��*/
 }APP_ERABM_DATA_TRANS_CNF_STRU;

/*****************************************************************************
 �ṹ��    : APP_ERABM_SERVICE_REQ_STRU
 �ṹ˵��  : SERVICE����ṹ
*****************************************************************************/
 typedef struct
 {
     VOS_MSG_HEADER
     VOS_UINT32                                           ulMsgId;
     APP_MSG_HEADER
 }APP_ERABM_SERVICE_REQ_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT32                   g_ulERabmBufTimerLength;


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/





#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AppRabmInterface.h */
