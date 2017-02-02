

#ifndef __QOS_FC_RAB_STATUS_H__
#define __QOS_FC_RAB_STATUS_H__

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
 �ṹ��    : QOS_FC_RAB_STATE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������߳��ص�״̬����״̬��GU��L�����岻ͬ:��GU��˵�������RAB
             ��״̬����LTE��˵�������DRB��״̬
*****************************************************************************/
typedef enum QOS_FC_RAB_STATE
{
    QOS_FC_RAB_STATE_NORMAL,           /* ��������״̬ */
    QOS_FC_RAB_STATE_RANDOM_DISCARD,   /* �������״̬ */
    QOS_FC_RAB_STATE_DISCARD,          /* ����״̬ */
    QOS_FC_RAB_STATE_NOT_DISCARD,      /* ���ز�����״̬��STICK */
    QOS_FC_RAB_STATE_BUTT
} QOS_FC_RAB_STATE_ENUM;

typedef VOS_UINT32 QOS_FC_RAB_STATE_ENUM_UINT32;


/*****************************************************************************
   5 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : QOS_FC_RAB_ENTITY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����CDS����ʵ��ṹ
*****************************************************************************/
typedef struct QOS_FC_RAB_ENTITY
{
    VOS_UINT8               ucRabId;                      /* ���ر�ʶ  */
    QCI_TYPE_ENUM_UINT8     enQci;
    VOS_UINT8               ucPriority;                   /* �������ȼ� */
    VOS_UINT8               ucLinkRabId;                  /* �����ر�ʶ  */
    QOS_FC_RAB_STATE_ENUM_UINT32       enRabState;
} QOS_FC_RAB_ENTITY_STRU;



/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  8 ��������
*****************************************************************************/
extern VOS_VOID QosFcRabInit(VOS_VOID);
extern VOS_UINT32 QosFc_RestoreHighPriRab(VOS_VOID);
extern VOS_UINT32 QosFc_DiscardAllDataFlow(VOS_VOID);
extern VOS_UINT32 QosFc_RestoreDataFlow(VOS_VOID);
extern VOS_UINT32 QosFc_DiscardDataFlow(VOS_VOID);
extern VOS_UINT32 QosFc_RandomDiscardDataFlow(VOS_VOID);

extern VOS_VOID QosFc_RabCreate(CONST MsgBlock  *pstMsg);
extern VOS_VOID QosFc_RabRelease(CONST MsgBlock  *pstMsg);
extern VOS_VOID QosFc_UpdateRabStatus(VOS_UINT8 ucRabId, QOS_FC_RAB_STATE_ENUM_UINT32 enRabState);
extern QOS_FC_RAB_STATE_ENUM_UINT32 QosFc_GetRabStatus(VOS_UINT8 ucRabId);
extern VOS_VOID QosFc_RabEntityInit(VOS_UINT32 ulIndex);
extern VOS_UINT8 QosFc_OtherAvailRabOfPdn(VOS_UINT8 ucRabId);
extern VOS_BOOL QosFc_RabNeedFlowCtrl(VOS_UINT32 ulIndex);
extern VOS_VOID QosFc_SetRabDiscard(VOS_UINT32 ulIndex);
extern VOS_VOID QosFc_SetRabRandomDiscard(VOS_UINT32 ulIndex);
extern VOS_VOID QosFc_SetRabNormal(VOS_UINT32 ulIndex);
extern VOS_VOID QosFc_RestoreRabStatus(VOS_UINT32 ulIndex);
extern VOS_VOID QosFc_SetRabEntity(QOS_FC_RAB_ENTITY_STRU *pstQosFcRabEntity, CONST QOS_FC_RAB_CREATE_IND_STRU *pstRabCreate);
extern VOS_UINT32 QosFc_MoveUpEntityPos(VOS_UINT32 ulInitPos, VOS_UINT8 ucPriority);
extern VOS_UINT32 QosFc_MoveDownEntityPos(VOS_UINT32 ulInitPos, VOS_UINT8 ucPriority);
extern QOS_FC_RAB_ENTITY_STRU* QosFc_CreateRabEntity(CONST QOS_FC_RAB_CREATE_IND_STRU *pstRabCreate, VOS_UINT8 *pucOldLinkRabId);
extern QCI_TYPE_ENUM_UINT8 QosFc_GetPdnQci(VOS_UINT8 ucRabId);
extern VOS_UINT8 QosFc_ReleaseRabEntity(VOS_UINT8 ucRabId);

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

