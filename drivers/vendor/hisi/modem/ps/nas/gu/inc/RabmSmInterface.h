/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : RabmSmInterface.h
  Description : RABM��SM�ӿ�ͷ�ļ�
  History     :
      1.  ��־��      2003.12.04   �°�����
      2.��    ��  : 2006��12��4��
        ��    ��  : luojian id:60022475
        �޸�����  : ���� #pragma pack(4)�����ⵥ��:A32D07779
*******************************************************************************/

#ifndef _RABM_SM_INTERFACE_H_
#define _RABM_SM_INTERFACE_H_


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define RABMSM_ACT_MSG_1                (1)                 /* ָʾSM����RABM���ǵ�һ��������Ϣ */
#define RABMSM_ACT_MSG_2                (2)                 /* ָʾSM����RABM���ǵڶ���������Ϣ */

#define RABM_SM_PPP_PROT                (0)                 /* ����PPPЭ�� */
#define RABM_SM_IP_PROT                 (1)                 /* ����IPЭ��  */

#define RABM_SM_MAX_NSAPI_NUM           (11)                /* ȥ�����NSAPI��������� */

#define RABM_SM_MAX_QOS_LEN             (16)                /* QOS�ֽ�����󳤶� */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum RABM_SM_MSG_ID_ENUM
{
    /*------------------------------------------------------
                        SM<--->RABM
    *-----------------------------------------------------*/
    RABMSM_ACTIVATE_IND                 = 0x0000,           /* _H2ASN_MsgChoice RABMSM_ACTIVATE_IND_STRU */
    RABMSM_ACTIVATE_RSP                 = 0x0001,           /* _H2ASN_MsgChoice RABMSM_ACTIVATE_RSP_STRU */
    RABMSM_DEACTIVATE_IND               = 0x0002,           /* _H2ASN_MsgChoice RABMSM_DEACTIVATE_IND_STRU */
    RABMSM_DEACTIVATE_REQ               = 0x0003,           /* _H2ASN_MsgChoice RABMSM_DEACTIVATE_REQ_STRU */
    RABMSM_MODIFY_IND                   = 0x0004,           /* _H2ASN_MsgChoice RABMSM_MODIFY_IND_STRU */

#if (FEATURE_ON == FEATURE_LTE)
    /* ��ģ����������ԭ�� */
    ID_SM_RABM_BEARER_ACTIVATE_IND      = 0x0100,           /* _H2ASN_MsgChoice SM_RABM_BEARER_ACTIVATE_IND_STRU */
    ID_SM_RABM_BEARER_DEACTIVATE_IND    = 0x0101,           /* _H2ASN_MsgChoice SM_RABM_BEARER_DEACTIVATE_IND_STRU */
    ID_SM_RABM_BEARER_MODIFY_IND        = 0x0102,           /* _H2ASN_MsgChoice SM_RABM_BEARER_MODIFY_IND_STRU */
#endif

    ID_RABM_SM_MSG_BUTT
};
typedef VOS_UINT32 RABM_SM_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


typedef struct
{
    VOS_UINT32                          ulLength;
    VOS_UINT8                           aucQosValue[RABM_SM_MAX_QOS_LEN];
} RABMSM_QOS_STRU;



typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ                       */ /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* ָ����NSAPI                  */
    VOS_UINT32                          ulLinkdNsapi;       /* ������NSAPI                  */
    VOS_UINT32                          ulPppFlag;          /* �Ƿ����PPPЭ���־          */
    VOS_UINT32                          ulActMsgType;       /* ����������SM����RABM�ĵ�һ�����ǵڶ���������Ϣ*/
    RABMSM_QOS_STRU                     Qos;                /* ָͬ����NSAPI��ص�QOS       */
} RABMSM_ACTIVATE_IND_STRU;


/*****************************************************************************
 �ṹ��    : RABMSM_ACTIVATE_RSP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��RABMSM_ACTIVATE_RSP�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ      */   /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* �����NSAPI */
} RABMSM_ACTIVATE_RSP_STRU;


/*****************************************************************************
 �ṹ��    : RABMSM_DEACTIVATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��RABMSM_DEACTIVATE_IND�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ             */ /* _H2ASN_Skip */
    VOS_UINT32                          ulDeactiveNum;      /*ȥ�����NSAPI�ĸ��� */
    VOS_UINT32                          aulNsapiList[RABM_SM_MAX_NSAPI_NUM];    /* ȥ�����NSAPI�б� */
} RABMSM_DEACTIVATE_IND_STRU;


/*****************************************************************************
 �ṹ��    : RABMSM_MODIFY_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��RABMSM_MODIFY_IND�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ               */ /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* ָ����NSAPI          */
    RABMSM_QOS_STRU                     Qos;                /* ָ����NSAPI��ص�QOS */
} RABMSM_MODIFY_IND_STRU;


/*****************************************************************************
 �ṹ��    : RABMSM_DEACTIVATE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��RABMSM_DEACTIVATE_REQ�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /* ��Ϣͷ           */ /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* ���ͷ�RAB��NSAPI */
} RABMSM_DEACTIVATE_REQ_STRU;


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �ṹ��    : SM_RABM_BEARER_ACTIVATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��ID_SM_RABM_BEARER_ACTIVATE_IND�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ                       */ /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* ָ����NSAPI                  */
    VOS_UINT32                          ulLinkdNsapi;       /* ������NSAPI                  */
    RABMSM_QOS_STRU                     stQos;              /* ָͬ����NSAPI��ص�QOS       */
} SM_RABM_BEARER_ACTIVATE_IND_STRU;


/*****************************************************************************
 �ṹ��    : SM_RABM_BEARER_DEACTIVATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��ID_SM_RABM_BEARER_DEACTIVATE_IND�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ      */   /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* ָ����NSAPI */
} SM_RABM_BEARER_DEACTIVATE_IND_STRU;


/*****************************************************************************
 �ṹ��    : SM_RABM_BEARER_MODIFY_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ԭ��ID_SM_RABM_BEARER_MODIFY_IND�Ľṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /* ��Ϣͷ                 */ /* _H2ASN_Skip */
    VOS_UINT32                          ulNsapi;            /* ָ����NSAPI            */
    RABMSM_QOS_STRU                     stQos;              /* ָͬ����NSAPI��ص�QOS */
} SM_RABM_BEARER_MODIFY_IND_STRU;
#endif


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    RABM_SM_MSG_ID_ENUM_UINT32          enMsgId;            /* _H2ASN_MsgChoice_Export RABM_SM_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RABM_SM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} RABM_SM_INTERFACE_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    RABM_SM_INTERFACE_MSG_DATA          stMsgData;
} RabmSmInterface_MSG;


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_UINT32 SM_IsActivePending(VOS_UINT8 ucNsapi);
extern VOS_UINT32 SM_RabmGetFirstActIndMsgInfo(
    VOS_UINT8                           ucNsapi,
    RABMSM_ACTIVATE_IND_STRU           *pActivateInd
);
extern VOS_UINT32 NAS_SM_CheckPdpActiveState(VOS_VOID);

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

#endif
