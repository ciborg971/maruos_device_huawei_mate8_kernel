
#ifndef __BST_DRV_AS_H__
#define __BST_DRV_AS_H__

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
#include "BST_DRV_Common.h"
#include "BST_SRV_Define.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_DRV_AsGetDvcHandle()        ( &g_BstDrvAsHandle )
#define BST_DRV_AS_INVALID_CTRLPARA     ( 0 )
/*��ѯ��ǰ�Ƿ����RRC����*/
#define BST_DRV_AsIsRrcExisted()        (( BST_RRC_STATE_DCH == g_ulBstDrvRrcState ) \
                                         ||(BST_RRC_STATE_FACH == g_ulBstDrvRrcState)\
                                         ||(BST_RRC_STATE_CONNECTED == g_ulBstDrvRrcState))

/*��ѯ��ǰRRC״̬�Ƿ���Ч*/
#define BST_DRV_AsIsRrcStateInvalid()   ( g_ulBstDrvRrcState >= BST_RRC_STATE_BUTT )


/*��ѯ��ǰ�Ƿ�������AP�ϱ�QMI/ICC��Ϣ������AP���ѣ�*/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

enum{
    BST_SIGLE_SIM_MODE                  = 0U,
    BST_DUAL_DSDS_SIM_MODE,
    BST_DUAL_DSDA_SIM_MODE,
    BST_INVALID_SIM_MODE
};
typedef BST_UINT32                      BST_MODEM_SIM_MODE_ENUM_UINT32;

enum BST_DRV_CHNLMODE_ENUM
{
    BST_DRV_CHNLMODE_INIT               =0U,
    BST_DRV_CHNLMODE_LPM,
    BST_DRV_CHNLMODE_NORMAL,
    BST_DRV_CHNLMODE_HPR,
    BST_DRV_CHNLMODE_BUTT
};
typedef BST_UINT32                      BST_DRV_CHNLMODE_ENUM_UINT32;

enum{
    BST_DRV_AS_RAT_INVALID_ENUM       = 0U,
    BST_DRV_AS_RAT_GSM_ENUM,
    BST_DRV_AS_RAT_WCDMA_ENUM,
    BST_DRV_AS_RAT_TDSCDMA_ENUM,
    BST_DRV_AS_RAT_LTE_ENUM,
    BST_DRV_AS_RAT_NUMBER
};
typedef BST_UINT32                  BST_DRV_AS_RAT_ENUM_UINT32;

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
typedef struct{
    BST_AS_EVT_ENUM_UINT32              ulId;
    BST_UINT32                          ulPara;
}BST_DRV_AS_EVENT_STRU;



/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/
extern BST_DRV_STRU                     g_BstDrvAsHandle;
extern BST_UINT32                       g_ulBstDrvRrcState;
extern BST_BOOL                         g_BstReportFlag;
/*****************************************************************************
  8 ��������
*****************************************************************************/
BST_VOID    BST_DRV_AsSetReportFlag( BST_UINT8 ucReportFlg );
BST_VOID    BST_DRV_AsProcBstTxData( BST_UINT8 ucDataType  );
BST_VOID    BST_DRV_AsProcHpriDataFinish( BST_VOID );
BST_DRV_AS_RAT_ENUM_UINT32 BST_DRV_AsMapRatToEnum(
    BST_AS_RAT_MODE_UINT32  ulRatMode );
BST_VOID    BST_DRV_AsNetStateProc( BST_BOOL bNetDeviceUp );

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
