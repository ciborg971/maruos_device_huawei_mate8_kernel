/******************************************************************************

                  ��Ȩ���� (C), 2014, ��Ϊ�������޹�˾
 *****************************************************************************
  �� �� ��   : BST_DRV_LinkSta.h
  �� �� ��   : ����
  ��    ��   : 
  ��������   : 
  ����޸�   :
  ��������   : 
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 
    ��    ��   : 
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __BST_DRV_LINKSTA_H__
#define __BST_DRV_LINKSTA_H__

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
#include "BST_DRV_As.h"
#include "BST_DRV_Net.h"
#include "BST_PAL_As.h"
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_DRV_LS_BUF_FAC          ( 0x03 )
#define BST_DRV_LS_BUF_LENGTH       ( ( 0x01 ) << ( BST_DRV_LS_BUF_FAC ) )
#define BST_DRV_LsGetInstance()     ( &g_BstDrvLsInstance )
#define BST_DRV_LsGetNetThreshold() ( &g_BstDrvLsInstance.stThreshold )
#define BST_DRV_LsMdmIdValid(id)    ( (id) < BST_MODEM_MAX )
#define BST_DRV_LsIsRatSnValid(sn)  ( ((sn)!=BST_DRV_LS_RAT_INVALID_SN)\
                                    &&((sn)<BST_DRV_LS_RAT_NUMBER) )

#define BST_DRV_LS_ONE_HUNDRED      ( 100U )
#define BST_DRV_LS_FULL_SCORE       ( 100U )   /* ��·������ʱ��Ĭ��100�� */
#define BST_DRV_LS_ZERO_SCORE       ( 0U )     /* ��·����������ʱ��Ϊ0�� */
#define BST_DRV_LS_WEAK_SCORE       ( 40U )    /* ��·����Ϊ��ʱ��0-40�� */
#define BST_DRV_LS_MIDD_SCORE       ( 70U )    /* ��·����Ϊ��ʱ��40-70�� */
#define BST_DRV_LS_TRX_ADD_SVALUE   ( 10U )    /* �������յ����ӷ�10 */
#define BST_DRV_LS_EXTRA_SCORE      ( 5U )     /* ���������Ӳ�->�У���->�߱仯ʱ���������������仯��Ҫ����BST_DRV_LS_EXTRA_SCORE*/

#define BST_DRV_LS_POOR_SCORE       ( 20 )     /* ������̬�ش��ʵ÷ֵ��ڸ�ֵʱ��IDLE̬���������������ж����������Ƿ��ڵ� */
#define BST_DRV_LS_STATIC_VRC       ( 15 )     /* ��̬��������ֵ */
#define BST_DRV_LS_STATIC_CNT       ( 16 )     /* ����̬���������ڵ��ڸ�ֵ��Ϊ��ֹ״̬ */
#define BST_DRV_LS_DYNAMIC_CNT      ( 8 )      /* ����̬������С�ڵ��ڸ�ֵ��Ϊ�ƶ�״̬ */

/* ������λƫ���� */
#define BST_DRV_LS_BIT1_FAC         ( 1U )
#define BST_DRV_LS_BIT2_FAC         ( 2U )
#define BST_DRV_LS_BIT3_FAC         ( 3U )
#define BST_DRV_LS_BIT4_FAC         ( 4U )
#define BST_DRV_LS_BIT5_FAC         ( 5U )
#define BST_DRV_LS_BIT6_FAC         ( 6U )
#define BST_DRV_LS_BIT7_FAC         ( 7U )
#define BST_DRV_LS_BIT8_FAC         ( 8U )
#define BST_DRV_LS_BIT9_FAC         ( 9U )
#define BST_DRV_LS_BIT13_FAC        ( 13U )

/* ����Ȩ�أ�����N��T��Qֵ����Ч��ѡ����� */
#define BST_DRV_LS_NONE_USED_BIT    ( 0x00 )
#define BST_DRV_LS_N_USED_BIT       ( 0x01 )
#define BST_DRV_LS_Q_USED_BIT       ( 0x02 )
#define BST_DRV_LS_T_USED_BIT       ( 0x04 )
#define BST_DRV_LS_NQ_USED_BIT      ( BST_DRV_LS_N_USED_BIT | BST_DRV_LS_Q_USED_BIT )
#define BST_DRV_LS_NT_USED_BIT      ( BST_DRV_LS_N_USED_BIT | BST_DRV_LS_T_USED_BIT )
#define BST_DRV_LS_TQ_USED_BIT      ( BST_DRV_LS_T_USED_BIT | BST_DRV_LS_Q_USED_BIT )
#define BST_DRV_LS_ALL_USED_BIT     ( BST_DRV_LS_N_USED_BIT | BST_DRV_LS_Q_USED_BIT | BST_DRV_LS_T_USED_BIT )

#define BST_AS_INVALID_CELLID       ( 0xFFFF ) /* ��ЧС��ID */

/* ����PDU���������������ڸ�����ֵʱ���ż����ش��� */
#define BST_DRV_LS_TX_PKT_NUM       ( 50U )

/* ���������ж� */
#define BST_DRV_LS_QUE_HIGH         ( 9216 )  /*�������ʱ�� 9216ms*/
#define BST_DRV_LS_QUE_LOW          ( 1024 )  /*�������ʱ�� 1024ms*/

#define BST_DRV_LS_QUE_LEN_MIN      ( 8192 )  /*���г�����Сֵ�����������С��8Kʱ�������㻺����еı���*/

/* TL��������Ч��RSRP��RSRQֵ */
#define BST_DRV_INVALID_RSCP        ( 99 )
#define BST_DRV_INVALID_ECI0        ( 99 )

/* ��Ч�Ĵ���ֵ */
#define BST_DRV_INVALID_BAND_WIDTH  ( 0xFFFF )

#define BST_DRV_LS_MOD_SUB(x, y)    ( ( (x) > (y) ) ? ( ( x ) - ( y ) ) : ( 0 ) )

#define BST_DRV_LsGetDvcHandle()    ( &g_BstDrvLinkStateHandle );

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/
enum{
    BST_DRV_LS_RAT_INVALID_SN       = 0U,
    BST_DRV_LS_RAT_GSM_SN,
    BST_DRV_LS_RAT_WCDMA_SN,
    BST_DRV_LS_RAT_TDSCDMA_SN,
    BST_DRV_LS_RAT_LTE_SN,
    BST_DRV_LS_RAT_NUMBER
};
typedef BST_UINT32                  BST_DRV_LS_RAT_SN_ENUM_UINT32;


enum{
    BST_DRV_LS_AP_STATE_SLEEP       = 0U,
    BST_DRV_LS_AP_STATE_WAKEUP,
    BST_DRV_LS_AP_STATE_BUTT
};
typedef BST_UINT32                  BST_DRV_LS_AP_STATE_UINT32;

enum{
    BST_DRV_LS_STATE_STATIC       = 0U,
    BST_DRV_LS_STATE_DYNAMIC,
    BST_DRV_LS_STATE_BUTT
};
typedef BST_UINT16                  BST_DRV_LS_MOVING_STATE_UINT16;

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
typedef BST_UINT32 ( *BST_DRV_LS_READ_TRS_FUNC )(
    BST_UINT32    *pulTotPktNumber,
    BST_UINT32    *pulRtxPktNumber );

typedef BST_UINT32 ( *BST_DRV_LS_READ_QUE_FUNC )(
    BST_UINT32    *pulQueLength,
    BST_UINT32    *pulBandWith );

typedef struct
{
    BST_UINT16                          usCounter;
    BST_UINT16                          usIsFull;
    BST_INT16                           asRscp[ BST_DRV_LS_BUF_LENGTH ];
    BST_INT16                           asEcI0[ BST_DRV_LS_BUF_LENGTH ];
}BST_DRV_LS_NETSTR_BUFF_STRU;

typedef struct{
  struct{
            BST_INT16                   sRxLevAMin;
            BST_INT16                   sRxLevAMax;
      }gsm;
  struct{
            BST_INT16                   sRscpMin;
            BST_INT16                   sRscpMax;
            BST_UINT16                  usReTxMin;
            BST_UINT16                  usReTxMax;
      }tdscdma;
  struct{
            BST_INT16                   sRscpMin;
            BST_INT16                   sRscpMax;
            BST_INT16                   sEci0Min;
            BST_INT16                   sEci0Max;
            BST_UINT16                  usReTxMin;
            BST_UINT16                  usReTxMax;
      }wcdma;
  struct{
            BST_INT16                   sRsrpMin;
            BST_INT16                   sRsrpMax;
            BST_INT16                   sRsrqMin;
            BST_INT16                   sRsrqMax;
            BST_UINT16                  usReTxMin;
            BST_UINT16                  usReTxMax;
      }lte;
}BST_DRV_LS_THRESHOLD_STRU;

typedef struct{
    BST_UINT32                          ulStatFlag;
    BST_UINT32                          ulTotalPkt;
    BST_UINT32                          ulTotalRePkt;
}BST_DRV_LS_RLC_PDU_STAT;

typedef struct{
    BST_AS_NET_RANK_ENUM_UINT32         ulRankValue;         /* ��ǰ��·�ȼ� */
    BST_AS_NET_RANK_ENUM_UINT32         ulLastRank;          /* ����block��unblock״̬ʱ���ϱ���һ�μ�¼��RANK�ȼ� */
    BST_MODEM_ID_ENUM_UINT32            ulCurModemId;        /* ��ǰPS��ModemId */
    BST_AS_RAT_MODE_UINT32              ulCurRAT;            /* ��ǰPS-MODEM RAT */
    BST_AS_RRC_STATE_ENUM_UINT32        ulCurRrc;            /* ��ǰRRCģʽ */
    BST_DRV_NET_STATE_ENUM_UINT32       ulNetDeviceState;    /* ��ǰ����״̬,up or down */
    BST_UINT32                          ulBlockState;        /* ��ǰ����block״̬ */
    BST_UINT32                          ulCellId;            /* ��ǰС��ID */
    BST_UINT32                          ulCurDValue;         /* ��ǰ�Ƿ����շ��ļӷ��� */
    BST_DRV_LS_NETSTR_BUFF_STRU         stNetSta;            /* ������������Buffer */
    BST_DRV_LS_THRESHOLD_STRU           stThreshold;         /* ������������ֵ���ź�ǿ�ȡ��ش��� */
    BST_DRV_LS_RLC_PDU_STAT             stRlcStat;           /* TL��ʽ��RLC��pdu��Ϣͳ�ƽṹ�� */
    BST_UINT32                          ulTransScore;        /* ����̬��RLC�ش��ʵ÷֣���IDLE̬ʹ�� */
    BST_DRV_LS_MOVING_STATE_UINT16      usMovingState;       /* �ƶ�����ֹ״̬ */
    BST_UINT16                          usStaticCounter;     /* ��ֹ������ */

    /* ����ʽ��ȡʵʱ�ش����Ե���ں��� */
    BST_DRV_LS_READ_TRS_FUNC            apfReadTrsInfo[ BST_MODEM_MAX ][ BST_DRV_LS_RAT_NUMBER ];

    /* ����ʽ��ȡʵʱ���Ͷ��е���ں��� */
    BST_DRV_LS_READ_QUE_FUNC            apfReadQueInfo[ BST_MODEM_MAX ][ BST_DRV_LS_RAT_NUMBER ];
}BST_DRV_LS_INS_STRU;

/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/
extern BST_DRV_STRU    g_BstDrvLinkStateHandle;
/*****************************************************************************
  8 ��������
*****************************************************************************/

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
