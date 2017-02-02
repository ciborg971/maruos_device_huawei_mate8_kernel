

#ifndef _GTM_TC_INTERFACE_H_
#define _GTM_TC_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define     GTM_STATUS_SETUP_OK     0x00        /* GPRS TEST MODE�����ɹ� */
#define     GTM_STATUS_SETUP_ERROR  0x01        /* GPRS TEST MODE����ʧ�� */

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/*====================*/ /* ��ϢID���� */
enum GRM_TC_MSG_ID_ENUM
{
    /* TC��GRM֮���ԭ�� */
    ID_GRM_GTM_SETUP_REQ    = 0x003C,       /* GRM������������ */
    ID_TC_GTM_SETUP_CNF     = 0x003D,       /* GRM��������ȷ�� */

    ID_TC_GTM_REL_IND       = 0x003E,       /* GRM�ͷŻ���ָʾ */
    ID_GRM_GTM_REL_RSP      = 0x003F,       /* NAS�ͷ�GPRS������Ӧ */

    ID_TC_GTM_SRB_SETUP_REQ = 0x004C,       /* SRB���ؽ������� */
    ID_GTM_TC_SRB_SETUP_CNF = 0x004D,    	/* SRB���ؽ���ȷ�� */

    ID_GTM_TC_SRB_REL_IND   = 0x004E,    	/* SRB�����ͷ�ָʾ */
    ID_TC_GTM_SRB_REL_RSP   = 0x004F     	/* SRB�����ͷ���Ӧ */

};

typedef VOS_UINT16 GRM_TC_MSG_ID_ENUM_UINT16;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
#pragma pack(4)

typedef struct
{
    GRM_TC_MSG_ID_ENUM_UINT16   enMsgID;    /*_H2ASN_MsgChoice_Export      GRM_TC_MSG_ID_ENUM_UINT16*/

    VOS_UINT8                   aucMsgBlock[2];
    /******************************************************************************************************
        _H2ASN_MsgChoice_When_Comment          GRM_TC_MSG_ID_ENUM_UINT16
    ******************************************************************************************************/

}GRM_TC_MSG_DATA;
/*_H2ASN_Length UINT32*/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    GRM_TC_MSG_DATA         stMsgData;
}GtmTcInterface_MSG;

typedef struct
{
    VOS_UINT8  ucPduDescript1;          /* GPRS_TEST_MODE��Ϣ�еĵ�һ��PDU Descript�ֽ� */
    VOS_UINT8  ucPduDescript2;          /* GPRS_TEST_MODE��Ϣ�еĵڶ���PDU Descript�ֽ� */
    VOS_UINT8  ucModeFlag;              /* GPRS_TEST_MODE��Ϣ�е�Mode Flag�ֽ� */
    VOS_UINT8  Rsv;                     /* ���ֽڶ��� */
}GPRS_TEST_MODE_ST;

/*�ӿ���Ϣ����*/
typedef struct
{
    VOS_MSG_HEADER                      /*_H2ASN_Skip*/
    /*��Ϣ����*/
    VOS_UINT16          usMsgType;      /*_H2ASN_Skip*/

    /*�ӽ��̱�ʶ,���ڶ�λ�ӽ���*/
    VOS_UINT16          usTransId;
} GPRS_LOOP_NO_CONTENT_MSG;

/*�ӿ���Ϣ����*/
typedef struct
{
    VOS_MSG_HEADER                      /*_H2ASN_Skip*/
    /*��Ϣ����*/
    VOS_UINT16              usMsgType;  /*_H2ASN_Skip*/

    /*�ӽ��̱�ʶ,���ڶ�λ�ӽ���*/
    VOS_UINT16              usTransId;
    GPRS_TEST_MODE_ST       stGLSetupReq;
} GRM_GTM_SETUP_REQ_MSG;

/*�ӿ���Ϣ����*/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    VOS_UINT16                          usMsgType;          /* ��Ϣ���� */      /*_H2ASN_Skip*/

    VOS_UINT16                          usModeFlg;          /* ����ģʽ, ʹ��ǰ8��bit */

} TC_GTM_SRB_SETUP_REQ_STRU;

/*�ӿ���Ϣ����*/
typedef GPRS_LOOP_NO_CONTENT_MSG TC_GTM_REL_IND_MSG;
typedef GPRS_LOOP_NO_CONTENT_MSG GRM_GTM_REL_RSP_MSG;


/* TC_GTM_SETUP_CNF_MSG��TransId����ΪGPRS TEST MODE�����ɹ���ʧ�ܵ�ָʾ */
typedef GPRS_LOOP_NO_CONTENT_MSG TC_GTM_SETUP_CNF_MSG;

/*EGPRS Interface*/
typedef TC_GTM_SRB_SETUP_REQ_STRU TC_GTM_SRB_SETUP_REQ_MSG;

/* GTM_TC_SRB_SETUP_CNF��TransId����ΪEGPRS TEST MODE�����ɹ���ʧ�ܵ�ָʾ */
typedef GPRS_LOOP_NO_CONTENT_MSG GTM_TC_SRB_SETUP_CNF_MSG;

typedef GPRS_LOOP_NO_CONTENT_MSG GTM_TC_SRB_REL_IND_MSG;
typedef GPRS_LOOP_NO_CONTENT_MSG TC_GTM_SRB_REL_RSP_MSG;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MapsTemplate.h*/
