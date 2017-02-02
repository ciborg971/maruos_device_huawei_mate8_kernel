
#ifndef __BST_PAL_AS_H__
#define __BST_PAL_AS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_SRV_Define.h"
#include "BST_DRV_Common.h"
#include "BST_DRV_As.h"
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_PalAsEventRcvCb( AsEvent, len, pdata )  \
                    if( BST_NULL_PTR != g_BstPalAsEventRcvCb )\
                    {\
                        g_BstPalAsEventRcvCb( AsEvent, len, pdata );\
                    }

#define BST_INVALID_RABID               (0xFF)
#define BST_MIN_RABID                   (5)
#define BST_MAX_RABID                   (15)
#define BST_INVALID_RBID                (0xFF)
#define BST_MIN_RBID                    (5)
#define BST_MAX_RBID                    (32)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/
enum{
    BST_MODEM_ID_1                      = 0U,
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    BST_MODEM_ID_2,
#if ( 3 == MULTI_MODEM_NUMBER )
    BST_MODEM_ID_3,
#endif
#endif
    BST_MODEM_MAX
};
typedef BST_UINT32                      BST_MODEM_ID_ENUM_UINT32;


/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
typedef BST_VOID (* BST_DRV_RCV_AS_EVENT_T)( BST_AS_EVT_ENUM_UINT32     enAsEvent,
                                               BST_UINT32               ulLength,
                                               BST_VOID                *pvData );
typedef struct{
    BST_AS_RAT_MODE_UINT32              enRatMode;     /*modem��Ӧ�Ľ�����ʽ*/
    BST_BOOL                            bCsInService;  /*CS���Ƿ�ע��ɹ�*/
    BST_BOOL                            bPsInService;  /*PS���Ƿ�ע��ɹ�*/
    BST_BOOL                            bCsConnected;  /*�Ƿ����CSҵ��*/
#if (FEATURE_ON == FEATURE_DSDS)
    BST_BOOL                            bDsDsSupport;   /*�Ƿ�֧��dsds*/
    BST_UINT32                          ulRFID[BST_DRV_AS_RAT_NUMBER];    /*�Ƿ�֧��dsds*/
#endif
}BST_PAL_AS_MODEMINFO_STRU;

typedef struct{
    BST_BOOL                            bRatReported;               /*�����Ƿ��Ѿ��ϱ�����ʽ*/
    BST_MODEM_ID_ENUM_UINT32            enPsModemId;                /*��ǰPSҵ�����ڵ�modem*/
    BST_PAL_AS_MODEMINFO_STRU           stModemInfo[BST_MODEM_MAX]; /*modem�����Ϣ*/
    BST_UINT16                          usRabId;
    BST_UINT16                          usReversed;
}BST_PAL_AS_INFO_STRU;

/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/
extern  BST_DRV_RCV_AS_EVENT_T  g_BstPalAsEventRcvCb;
/*****************************************************************************
  8 ��������
*****************************************************************************/
BST_ERR_ENUM_UINT8              BST_PAL_AsApiInitial(
    BST_DRV_RCV_AS_EVENT_T      pfRcvCallBack );

BST_ERR_ENUM_UINT8              BST_PAL_AsApiReleaseRrcConn( BST_VOID );

BST_AS_RAT_MODE_UINT32          BST_PAL_AsApiGetModemRat(
    BST_MODEM_ID_ENUM_UINT32    enModemId );

BST_MODEM_ID_ENUM_UINT32        BST_PAL_AsApiGetPsModemId( BST_VOID );

BST_VOID                        BST_PAL_AsApiReadRfCfgNvim(BST_VOID);

BST_VOID                        BST_PAL_AsMsgSetRatModeInfo(
    BST_MODEM_ID_ENUM_UINT32    enModemId,
    BST_AS_RAT_MODE_UINT32      enRatMode
);

BST_VOID                        BST_PAL_AsApiSndRptFlag (
    BST_MODEM_ID_ENUM_UINT32    enPsModemId,
    BST_UINT8                   ucReportFlg );

BST_VOID                        BST_PAL_SetPsRrcStatus(
    BST_MODEM_ID_ENUM_UINT32    enModemId,
    BST_BOOL                    bExist);

BST_VOID                        BST_PAL_SetCsRrcStatus(
    BST_MODEM_ID_ENUM_UINT32    enModemId,
    BST_BOOL                    bExist);

BST_VOID                        BST_PAL_AsMsgSetCsUsingInfo(
    BST_MODEM_ID_ENUM_UINT32    enModemId,
    BST_BOOL                    bExist);

BST_VOID                        BST_PAL_AsMsgModemIdChanged(
    BST_MODEM_ID_ENUM_UINT32    enNEwModemId );

BST_VOID                        BST_PAL_AsMsgSetServiceStatus(
    BST_MODEM_ID_ENUM_UINT32 enModemId,
    BST_BOOL                    bCsInservice,
    BST_BOOL                    bPsInservice
);
BST_ERR_ENUM_UINT8              BST_PAL_AsApiSetChnlMode(
    BST_DRV_CHNLMODE_ENUM_UINT32 enChnlMode );

BST_VOID                        BST_PAL_AsMsgSetRabID(
    BST_UINT16                  usRabId );

BST_UINT16                      BST_PAL_AsMsgGetRabID ( BST_VOID );


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
