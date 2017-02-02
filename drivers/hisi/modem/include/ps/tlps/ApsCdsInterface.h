

#ifndef __APSCDSINTERFACE_H__
#define __APSCDSINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "LPSCommon.h"



#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define APS_CDS_MSG_HDR                (0x0000)
#define CDS_APS_MSG_HDR                (0x1000)

#define APS_CDS_INVALID_PDN_ID         (0xFF)
#define APS_CDS_INVALID_RAB_ID         (0xFF)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/** ****************************************************************************
 * Name        : APS_CDS_PIF_MSG_TYPE_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum APS_CDS_PIF_MSG_TYPE_ENUM
{
    ID_CDS_APS_CDATA_SERVICE_IND        = CDS_APS_MSG_HDR + 1,                  /* _H2ASN_MsgChoice CDS_APS_CDATA_SERVICE_IND_STRU*/ /***< @sa CDS_APS_CDATA_SERVICE_IND_STRU */
    ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND = APS_CDS_MSG_HDR + 1,                  /* _H2ASN_MsgChoice APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU*/ /***< @sa APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU */
    ID_APS_CDS_CDATA_FREE_BUFF_DATA_IND = APS_CDS_MSG_HDR + 2,                  /* _H2ASN_MsgChoice APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU*/ /***< @sa APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU */
    ID_APS_CDS_MODE_CHANGE_IND          = APS_CDS_MSG_HDR + 3,                  /* _H2ASN_MsgChoice APS_CDS_MODE_CHANGE_IND_STRU*/ /***< @sa APS_CDS_MODE_CHANGE_IND_STRU */
    ID_APS_CDS_PIF_MSG_TYPE_ENUM_BUTT   = 0xFFFF
};
typedef VOS_UINT16 APS_CDS_PIF_MSG_TYPE_ENUM_UINT16;


/** ****************************************************************************
 * Name        : APS_CDS_MODE_ENUM_UINT32
 *
 * Description :
 *******************************************************************************/
enum APS_CDS_MODE_ENUM
{
    APS_CDS_MODE_NULL                   = 0x00000000,                           /* ��פ�� */
    APS_CDS_MODE_LTE                    = 0x00000001,                           /* Lģ */
    APS_CDS_MODE_GU                     = 0x00000002,                           /* GUģ */
    APS_CDS_MODE_1X                     = 0x00000003,                           /* CDMA 1X ģ*/
    APS_CDS_MODE_EVDO                   = 0x00000004,                           /* CDMA EVDO ģ*/
    APS_CDS_MODE_BUTT                   = 0x00000005
};
typedef VOS_UINT32 APS_CDS_MODE_ENUM_UINT32;


/** ****************************************************************************
 * Name        : APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum APS_CDS_CDATA_BEAR_STATUS_ENUM
{
    APS_CDS_CDATA_BEAR_STATUS_INACTIVE     = 0x00,
    APS_CDS_CDATA_BEAR_STATUS_IDLE         = 0x01,
    APS_CDS_CDATA_BEAR_STATUS_ACTIVE       = 0x02,
    APS_CDS_CDATA_BEAR_STATUS_SUSPEND      = 0x03,
    APS_CDS_CDATA_BEAR_STATUS_BUTT         = 0x04
};
typedef VOS_UINT8 APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8;



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

/*****************************************************************************
 �ṹ��    : CDS_BEARER_DATA_FLOW_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ѯ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTotalSendFluxLow;     /* �ۼƷ������������ֽ�     */
    VOS_UINT32                          ulTotalSendFluxHigh;    /* �ۼƷ������������ֽ�     */
    VOS_UINT32                          ulTotalReceiveFluxLow;  /* �ۼƽ������������ֽ�     */
    VOS_UINT32                          ulTotalReceiveFluxHigh; /* �ۼƽ������������ֽ�     */
} CDS_BEARER_DATA_FLOW_STRU;


/** ****************************************************************************
 * Name        : CDS_APS_CDATA_SERVICE_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_CDS_PIF_MSG_TYPE_ENUM_UINT16    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserve[3];
}CDS_APS_CDATA_SERVICE_IND_STRU;

/** ****************************************************************************
 * Name        : APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_CDS_PIF_MSG_TYPE_ENUM_UINT16    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserve[3];
}APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU;

/** ****************************************************************************
 * Name        : APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_CDS_PIF_MSG_TYPE_ENUM_UINT16    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserve[3];
}APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU;


/** ****************************************************************************
 * Name        : APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU
 *
 * Description :
 *******************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_CDS_PIF_MSG_TYPE_ENUM_UINT16    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usOpId;
    APS_CDS_MODE_ENUM_UINT32            enMode;
} APS_CDS_MODE_CHANGE_IND_STRU;



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/** ****************************************************************************
 * Name        : APS_CDS_PIF_MSG_DATA
 *
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    APS_CDS_PIF_MSG_TYPE_ENUM_UINT16    enMsgId;                                /* _H2ASN_MsgChoice_Export APS_CDS_PIF_MSG_TYPE_ENUM_UINT16 */
    VOS_UINT8                           aucMsgBlock[2];

    /* _H2ASN_MsgChoice_When_Comment APS_CDS_PIF_MSG_TYPE_ENUM_UINT16 */
}APS_CDS_PIF_MSG_DATA;

/* _H2ASN_Length UINT32*/
/** ****************************************************************************
 * Name        : TAF_APS_CDS_PIF
 *
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    APS_CDS_PIF_MSG_DATA                stMsgData;
}ApsCdsInterface_MSG;



/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_VOID CDS_GetBearerDataFlowInfo(
    VOS_UINT8                           ucRabId,
    CDS_BEARER_DATA_FLOW_STRU          *pstDataFlowInfo,
    MODEM_ID_ENUM_UINT16                enModemId
);

extern VOS_VOID CDS_ClearBearerDataFlowInfo(
    VOS_UINT8                           ucBearerId,
    MODEM_ID_ENUM_UINT16                enModemId
);


extern VOS_VOID TAF_APS_SetDfsMax(VOS_VOID);


/** *****************************************************************************
 * Name        : TAF_APS_GetCdataBearStatus
 *
 * Description : Get 1x bear status of Packet Data Service Adapter before send
 * UL data.
 *
 * @param[in]     ucRabId
 *******************************************************************************/
extern APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_APS_GetCdataBearStatus(VOS_UINT8 ucRabId);

/* Added by l00304941 for CDMA 1X Iteration 3, 2014-11-19 Begin */
extern VOS_UINT32 CDS_CheckUlDataToSend(MODEM_ID_ENUM_UINT16 enModemId,VOS_UINT8 ucRabId);
/* Added by l00304941 for CDMA 1X Iteration 3, 2014-11-19 End */

extern VOS_UINT8 TAF_APS_MapPdnIdToRabId(VOS_UINT8 ucPdnId);

extern VOS_UINT8 TAF_APS_MapRabIdToPdnId(VOS_UINT8 ucRabId);


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

#endif /* end of ApsCdsInterface.h */
