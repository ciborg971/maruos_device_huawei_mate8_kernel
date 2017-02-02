

#ifndef __ESMRABMINTERFACE_H__
#define __ESMRABMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "AppEsmInterface.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define ESM_ERABM_MAX_EPSB_NUM            11           /*��������*/

#define ESM_ERABM_MAX_PF_NUM_IN_BEARER    16
#define ESM_ERABM_MAX_PF_NUM              32

/*ESM ->RABM Command��Ϣǰ3���ֽں궨�� SM->RABM*/
#define ESM_ERABM_MSG_ID_HEADER           PS_MSG_ID_ESM_TO_RABM_BASE

/*RABM->SM Command��Ϣǰ3���ֽں궨�� RABM->SM*/
#define ERABM_ESM_MSG_ID_HEADER           PS_MSG_ID_RABM_TO_ESM_BASE


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : ESM_ERABM_MSG_TYPE_ENUM
 ö��˵��  : SM��RABM����Ϣ����
*****************************************************************************/
enum ESM_ERABM_MSG_TYPE_ENUM
{
    /* ��Ϣ���� */                      /*��ϢID*/
    /* RABM����SM��ԭ�� */
    ID_ESM_ERABM_REL_REQ                 = (0x02+ERABM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ESM_ERABM_REL_REQ_STRU */
    ID_ESM_ERABM_BEARER_STATUS_REQ       = (0x04+ERABM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ESM_ERABM_BEARER_STATUS_REQ_STRU */

    /* SM����RABM��ԭ�� */
    ID_ESM_ERABM_ACT_IND                 = (0x01+ESM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ESM_ERABM_ACT_IND_STRU */
    ID_ESM_ERABM_MDF_IND                 = (0x03+ESM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ESM_ERABM_MDF_IND_STRU */
    ID_ESM_ERABM_DEACT_IND               = (0x05+ESM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ESM_ERABM_DEACT_IND_STRU */
    ID_ESM_ERABM_REL_IND                 = (0x07+ESM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ESM_ERABM_REL_IND_STRU */

    ID_ESM_ERABM_BUTT
};
typedef VOS_UINT32 ESM_ERABM_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : ESM_ERABM_PDN_TYPE_ENUM
 ö��˵��  : SM��RABM֧�ֵ�PDN����
*****************************************************************************/
enum ESM_ERABM_PDN_TYPE_ENUM
{

    ESM_ERABM_PDN_TYPE_IPV4              = (0x01),    /* ֧��IPV4��ַ*/
    ESM_ERABM_PDN_TYPE_IPV6              = (0x02),    /* ֧��IPV6��ַ*/
    ESM_ERABM_PDN_TYPE_IPV4_IPV6         = (0x03),    /* ֧��IPV4��IPV6��ַ*/

    ESM_ERABM_PDN_TYPE_BUTT
};
typedef VOS_UINT8 ESM_ERABM_PDN_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : ESM_ERABM_BEARER_TYPE_ENUM
 ö��˵��  : SM��RABM֧�ֵĳ�������
*****************************************************************************/
enum ESM_ERABM_BEARER_TYPE_ENUM
{
    ESM_ERABM_BEARER_TYPE_DEFAULT        = 0,                /*ȱʡ����*/
    ESM_ERABM_BEARER_TYPE_DEDICATED      ,                   /*ר�г���*/
    ESM_ERABM_BEARER_TYPE_EMERGENCY      ,                   /*��������*/

    ESM_ERABM_BEARER_TYPE_BUTT
};
typedef VOS_UINT32  ESM_ERABM_BEARER_TYPE_ENUM_UINT32;
/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : ESM_ERABM_TFT_PF_STRU
 �ṹ˵��  : ESM_ERABM_TFT_STRU���ݽṹ
*****************************************************************************/
typedef APP_ESM_TFT_INFO_STRU ESM_ERABM_TFT_PF_STRU;

/*****************************************************************************
 �ṹ��    : ESM_ERABM_QOS_STRU
 �ṹ˵��  : ESM_ERABM_QOS_STRU���ݽṹ
*****************************************************************************/
typedef APP_ESM_QOS_INFO_STRU ESM_ERABM_QOS_STRU;


/*****************************************************************************
 �ṹ��    : ESM_ERABM_REL_REQ_STRU
 �ṹ˵��  : ESM_ERABM_REL_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/   /* ��Ϣͷ */
    VOS_UINT32                          ulReserved;         /* ������ */
}ESM_ERABM_REL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : ESM_ERABM_REL_IND_STRU
 �ṹ˵��  : ESM_ERABM_REL_IND_STRU���ݽṹ
*****************************************************************************/
typedef ESM_ERABM_REL_REQ_STRU ESM_ERABM_REL_IND_STRU;

/*****************************************************************************
 �ṹ��    : ESM_ERABM_ACT_IND_STRU
 �ṹ˵��  : ESM_ERABM_ACT_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulEpsId;
    VOS_UINT32                          ulTftPfNum;
    ESM_ERABM_TFT_PF_STRU                astTftPf[ESM_ERABM_MAX_PF_NUM_IN_BEARER];
    APP_ESM_IP_ADDR_STRU                stPdnAddr;
    ESM_ERABM_BEARER_TYPE_ENUM_UINT32   enBearerCntxtType;  /* �����Ķ�Ӧ���ص����� */
    VOS_UINT32                          ulLinkedEpsbId;     /*��˳��ع�����EPS����ID*/
    VOS_UINT8                           ucQCI;              /*����QCI */
    VOS_UINT8                           ucSessionId;        /* ��ϢOPIDƥ��*/
    VOS_UINT8                           ucRev[2];
} ESM_ERABM_ACT_IND_STRU;

/*****************************************************************************
 �ṹ��    : ESM_ERABM_MDF_IND_STRU
 �ṹ˵��  : ESM_ERABM_MDF_IND_STRU���ݽṹ
*****************************************************************************/
typedef ESM_ERABM_ACT_IND_STRU ESM_ERABM_MDF_IND_STRU;


/*****************************************************************************
 �ṹ��    : ESM_ERABM_DEACT_IND_STRU
 �ṹ˵��  : ESM_ERABM_DEACT_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    VOS_UINT32                          ulEpsIdNum;
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];
} ESM_ERABM_DEACT_IND_STRU;

/*****************************************************************************
 �ṹ��    : ESM_ERABM_BEARER_STATUS_REQ_STRU
 �ṹ˵��  : ESM_ERABM_BEARER_STATUS_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */
    VOS_UINT32                          ulEpsIdNum;         /* ��ǰ��Ӧrb�Ѽ����EPSID���� */
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];     /*�����Ѽ���rb��EPS BID  */
    VOS_UINT8                           ucSessionId;
    VOS_UINT8                           aucRsv[3];
} ESM_ERABM_BEARER_STATUS_REQ_STRU;

typedef struct
{
    ESM_ERABM_MSG_TYPE_ENUM_UINT32        enMsgId;            /*_H2ASN_MsgChoice_Export ESM_ERABM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                            aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          ESM_ERABM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}ESM_ERABM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    ESM_ERABM_INTERFACE_MSG_DATA         stMsgData;
}EsmRabmInterface_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


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

#endif /* end of RabmEsmInterface.h */
