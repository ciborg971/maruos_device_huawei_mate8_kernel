

#ifndef __QOS_FC_OM_H__
#define __QOS_FC_OM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "QosFcCommon.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
   5 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : QOS_FC_STATS_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : QOS����ͳ����
*****************************************************************************/
typedef struct QOS_FC_STATS_INFO
{
    VOS_UINT32              ulCreateMsgNum;                     /* �յ�CREATE��Ϣ���� */
    VOS_UINT32              ulReleaseMsgNum;                    /* �յ�RELEASE��Ϣ���� */
    VOS_UINT32              ulCreateRabNum;                     /* �������ش��� */
    VOS_UINT32              ulUpdateRabNum;                     /* ���³��ش��� */
    VOS_UINT32              ulReleaseRabNum;                    /* �ͷų��ش��� */
    VOS_UINT32              aulToRandomDiscardNum[MODEM_ID_BUTT][FC_MAX_RAB_NUM];  /* ����ÿ�����ؽ����������״̬���� */
    VOS_UINT32              aulToDiscardNum[MODEM_ID_BUTT][FC_MAX_RAB_NUM];        /* ����ÿ�����ؽ��붪��״̬���� */
    VOS_UINT32              aulToNormalNum[MODEM_ID_BUTT][FC_MAX_RAB_NUM];         /* ����ÿ�����ػָ�����״̬���� */
    VOS_UINT32              aulRcvPktNumOnD[MODEM_ID_BUTT][FC_MAX_RAB_NUM];        /* ����ÿ�������϶���״̬ʱ�հ����� */
    VOS_UINT32              aulDiscardPktNumOnD[MODEM_ID_BUTT][FC_MAX_RAB_NUM];    /* ����ÿ�������϶���״̬ʱ�������� */
    VOS_UINT32              aulRcvPktNumOnRD[MODEM_ID_BUTT][FC_MAX_RAB_NUM];       /* ����ÿ���������������״̬ʱ�հ����� */
    VOS_UINT32              aulDiscardPktNumOnRD[MODEM_ID_BUTT][FC_MAX_RAB_NUM];   /* ����ÿ���������������״̬ʱ�������� */
    VOS_UINT32              aulChannelToFc[MODEM_ID_BUTT][FC_MAX_RAB_NUM];         /* ͨ�����ش��� */
    VOS_UINT32              aulChannelResume[MODEM_ID_BUTT][FC_MAX_RAB_NUM];       /* ��ͨ�����ش��� */
    VOS_UINT32              ulUlLteDiscardTotalNum;                 /* ����LTE�������� */
    VOS_UINT32              ulUlGUDiscardTotalNum;                  /* ����GU�������� */
    VOS_UINT32              ulDlLteDiscardTotalNum;                 /* ����LTE�������� */
    VOS_UINT32              ulDlGUDiscardTotalNum;                  /* ����GU�������� */
    VOS_UINT32              ulDlCDMADiscardTotalNum;                  /* ����CDMA�������� */
    VOS_UINT32              ulUlCDMADiscardTotalNum;                 /* ����CDMA�������� */
}QOS_FC_STATS_INFO_STRU;



/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/
extern QOS_FC_STATS_INFO_STRU g_stQosFcStats;

/* QoS����ͳ�� */
#define  FC_DBG_CREATE_MSG_STAT(n)                  (g_stQosFcStats.ulCreateMsgNum += (n))
#define  FC_DBG_RELEASE_MSG_STAT(n)                 (g_stQosFcStats.ulReleaseMsgNum += (n))
#define  FC_DBG_CREATE_RAB_STAT(n)                  (g_stQosFcStats.ulCreateRabNum += (n))
#define  FC_DBG_UPDATE_RAB_STAT(n)                  (g_stQosFcStats.ulUpdateRabNum += (n))
#define  FC_DBG_RELEASE_RAB_STAT(n)                 (g_stQosFcStats.ulReleaseRabNum += (n))

#define  FC_DBG_TO_RANDOMDISCARD_STAT(modem, rab, n)       (g_stQosFcStats.aulToRandomDiscardNum[modem][rab-5] += (n))
#define  FC_DBG_TO_DISCARD_STAT(modem, rab, n)             (g_stQosFcStats.aulToDiscardNum[modem][rab-5] += (n))
#define  FC_DBG_TO_NORMAL_STAT(modem, rab, n)              (g_stQosFcStats.aulToNormalNum[modem][rab-5] += (n))
#define  FC_DBG_RCV_PKT_OND_STAT(modem, rab, n)            (g_stQosFcStats.aulRcvPktNumOnD[modem][rab-5] += (n))
#define  FC_DBG_DISCARD_PKT_OND_STAT(modem, rab, n)        (g_stQosFcStats.aulDiscardPktNumOnD[modem][rab-5] += (n))
#define  FC_DBG_RCV_PKT_ONRD_STAT(modem, rab, n)           (g_stQosFcStats.aulRcvPktNumOnRD[modem][rab-5] += (n))
#define  FC_DBG_DISCARD_PKT_ONRD_STAT(modem, rab, n)       (g_stQosFcStats.aulDiscardPktNumOnRD[modem][rab-5] += (n))

#define  FC_DBG_CHANNEL_FC_STAT(modem, rab, n)             (g_stQosFcStats.aulChannelToFc[modem][rab-5] += (n))
#define  FC_DBG_CHANNEL_RESUME_STAT(modem, rab, n)         (g_stQosFcStats.aulChannelResume[modem][rab-5] += (n))

#define  FC_DBG_ULLTE_CDS_DISCARD_PKT_STAT(n)       (g_stQosFcStats.ulUlLteDiscardTotalNum += (n))
#define  FC_DBG_ULGU_CDS_DISCARD_PKT_STAT(n)        (g_stQosFcStats.ulUlGUDiscardTotalNum += (n))
#define  FC_DBG_DLLTE_CDS_DISCARD_PKT_STAT(n)       (g_stQosFcStats.ulDlLteDiscardTotalNum += (n))
#define  FC_DBG_DLGU_CDS_DISCARD_PKT_STAT(n)        (g_stQosFcStats.ulDlGUDiscardTotalNum += (n))
#define  FC_DBG_DLCDMA_CDS_DISCARD_PKT_STAT(n)       (g_stQosFcStats.ulDlCDMADiscardTotalNum += (n))
#define  FC_DBG_ULCDMA_CDS_DISCARD_PKT_STAT(n)       (g_stQosFcStats.ulUlCDMADiscardTotalNum += (n))


/*****************************************************************************
  8 ��������
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
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

#endif

