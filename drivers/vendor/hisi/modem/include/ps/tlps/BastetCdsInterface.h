

#ifndef __BASTETCDSINTERFACE_H__
#define __BASTETCDSINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

typedef VOS_UINT32 ( *CDS_BST_SEND_UL_DATA_FUNC)(
    const VOS_UINT8 *pData,
    const VOS_UINT32 ulLen,
    const VOS_UINT8  ucFlg);

typedef VOS_UINT32 ( *CDS_BST_RESUME_UL_DATA_FUNC)(
    const VOS_UINT8 *pData,
    const VOS_UINT32 ulLen);


typedef VOS_UINT32 ( *CDS_BST_RECV_DL_DATA_FUNC)(
    const VOS_UINT8 *pData,
    const VOS_UINT32 ulLen );

typedef VOS_UINT32 ( *CDS_BST_RESM_DL_DATA_FUNC)(
    const VOS_UINT8 *pData,
    const VOS_UINT32 ulLen );

typedef VOS_UINT32 ( *CDS_BST_PORT_CHECK_FUNC)(
    const VOS_UINT16 usProtocol,
    const VOS_UINT16 usPortNumber );

#define CDS_BST_UL_DATA_NORMAL          ( 0x00U )
#define CDS_BST_UL_DATA_HIGH_PRI        ( 0x01U )


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
 ö����    : BST_CDS_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : BASTET��CDS֮�����Ϣ
*****************************************************************************/
enum    BST_CDS_MSG_ID_ENUM
{
    /* BASTET����CDS����Ϣԭ��: ��ǰNET_DEVICE״̬ */
    ID_BST_CDS_NET_DEVICE_UP_IND,                  /* _H2ASN_MsgChoice BST_CDS_NET_DEVICE_STATE_STRU */

    /* BASTET����CDS����Ϣԭ��: ACOREʹ�õ�MODEM_RABID��Ϣ*/
    ID_BST_CDS_NET_MODEM_RAB_IND,                 /* _H2ASN_MsgChoice BST_CDS_NET_ACORE_MODEM_RABID_STRU */

    /* CDS����BASTET����Ϣԭ��: ������IP���������� */
    ID_BST_CDS_RX_IND,                         /* _H2ASN_MsgChoice BST_CDS_TX_RX_MSG_STRU */

    /* BASTET����CDS����Ϣԭ��: ����CDS�Ƿ���TX_RX_IND��Ϣ */
    ID_BST_CDS_RX_RPT_CTRL_REQ,                /* _H2ASN_MsgChoice BST_CDS_TX_RX_RPT_ENABLE_STRU */

    /* BASTET����CDS����Ϣԭ��: ע����ջص����� */
    ID_BST_CDS_REG_RCV_CB_REQ,                    /* _H2ASN_MsgChoice BST_CDS_REG_RCV_CB_STRU */

    /* CDS����BASTET����Ϣԭ��: ��ǰMODEM����ҵ��ʹ�õ�MODEM ID */
    ID_BST_CDS_CHANNEL_INFO_IND,                  /* _H2ASN_MsgChoice BST_CDS_SEND_CB_INFO_STRU */

    ID_BST_CDS_TX_IND,                         /* _H2ASN_MsgChoice BST_CDS_TX_RX_MSG_STRU */

    /* BASTET����CDS����Ϣԭ��: ����CDS�Ƿ���TX_RX_IND��Ϣ */
    ID_BST_CDS_TX_RPT_CTRL_REQ,                /* _H2ASN_MsgChoice ID_BST_CDS_TX_RPT_CTRL_REQ */

    ID_BST_CDS_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 BST_CDS_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 �ṹ����   : CDS_BASTET_NET_DEVICE_STATE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ��ǰBastet����״̬
*****************************************************************************/
enum CDS_BASTET_NET_DEVICE_STATE_ENUM
{
    CDS_BASTET_NET_DEVICE_UNKNOW       	    = 0x00,
    CDS_BASTET_NET_DEVICE_UP                = 0x01,
    CDS_BASTET_NET_DEVICE_DOWN              = 0x02,
    CDS_BASTET_NET_DEVICE_BUTT
};
typedef VOS_UINT32 CDS_BASTET_NET_DEVICE_STATE_ENUM_UINT32;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : BST_CDS_SEND_CB_INFO_STRU
 �ṹ˵��  : BASTET��CDS����ԭ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    CDS_BST_SEND_UL_DATA_FUNC           pSendCbFun;
    CDS_BST_RESM_DL_DATA_FUNC           pResmCbFun;
} BST_CDS_SEND_CB_INFO_STRU;

/*****************************************************************************
 �ṹ��    : BST_CDS_NET_DEVICE_STATE_STRU
 �ṹ˵��  : BASTET��CDS����ԭ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                        /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;          /*_H2ASN_Skip*/
    VOS_UINT32                          ulNetDeviceState;
} BST_CDS_NET_DEVICE_STATE_STRU;

/*****************************************************************************
 �ṹ��    : BST_CDS_NET_ACORE_MODEM_RABID_STRU
 �ṹ˵��  : BASTET��CDS����ԭ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    VOS_UINT16                          usModemId;
    VOS_UINT16                          usRabId;
} BST_CDS_NET_ACORE_MODEM_RABID_STRU;

/*****************************************************************************
 �ṹ��    : BST_CDS_FILTER_LUT_MSG_STRU
 �ṹ˵��  : BASTET��CDS����ԭ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;           /*_H2ASN_Skip*/
} BST_CDS_TX_RX_MSG_STRU;

/*****************************************************************************
 �ṹ��    : BST_CDS_TX_RX_RPT_ENABLE_STRU
 �ṹ˵��  : BASTET��CDS����ԭ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                         /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;           /*_H2ASN_Skip*/
    VOS_UINT32                          ulEnableFlag;
} BST_CDS_TX_RX_RPT_ENABLE_STRU;

/*****************************************************************************
 �ṹ��    : BST_CDS_REG_RCV_CB_STRU
 �ṹ˵��  : BASTET��CDS����ԭ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                        /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;          /*_H2ASN_Skip*/
    CDS_BST_RECV_DL_DATA_FUNC           pfRcvCb;
    CDS_BST_PORT_CHECK_FUNC             pfChkPortCb;
} BST_CDS_REG_RCV_CB_STRU;



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
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    BST_CDS_MSG_ID_ENUM_UINT32          enMsgID;    /*_H2ASN_MsgChoice_Export BST_CDS_MSG_ID_ENUM_UINT32*/

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          BST_CDS_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}Bastet_CDS_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    Bastet_CDS_MSG_DATA                 stMsgData;
}BastetCdsInterface_MSG;


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

#endif /* end of BastetCdsInterface.h */

