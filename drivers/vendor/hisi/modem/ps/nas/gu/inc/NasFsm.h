/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasFsm.h
  �� �� ��   : ����
  ��    ��   : zhoujun /40661
  ��������   : 2010��11��12��
  ����޸�   :
  ��������   : MMC_Main.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��11��12��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ļ�

  2.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : V7R1 Phase I�޸�
******************************************************************************/
#ifndef _NAS_FSM_H_
#define _NAS_FSM_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_FSM_NAME_LENGTH             (32)

#define NAS_BuildCurState(usMainState,usSubState)   (((VOS_UINT32)(usMainState) << 16) | (usSubState))                  /* ���� ��״̬����״̬������CurState */


/* ״̬������� */
#define NAS_STA_TBL_ITEM(ulState, astActTbl)\
{\
    ( ulState),\
    ((sizeof(astActTbl))/sizeof(NAS_ACT_STRU)),\
    (astActTbl)\
}

#define NAS_MUTI_STA_TBL_ITEM(enMainState, enSubState, astActTbl)\
{\
    (((enMainState) << 16) | (enSubState)),\
    ((sizeof(astActTbl))/sizeof(NAS_ACT_STRU)),\
    (astActTbl)\
}


#define NAS_ACT_TBL_ITEM(PID, enMsgType, pActFun)\
{\
    (((VOS_UINT32)(/*lint -e778*/((PID) & 0xF0000)/*lint +e778*/ \
    | (((PID) & 0xFFF) << 4)) << 12) | (enMsgType)),\
    ((pActFun))\
}

/*****************************************************************************
  3 ö�ٶ���
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

/* �쳣�����������Ͷ��� */
typedef VOS_UINT32 ( * NAS_EXCEP_FUN )
(
    VOS_UINT32, /* EVENT ID,����PID��MSG ID */
    VOS_VOID *  /* ��Ϣָ�� */
);

/* ״̬����ʼ�������������Ͷ��� */
typedef VOS_VOID ( * NAS_INIT_FUN )
(
    VOS_VOID
);


/* ���������������Ͷ��� */
typedef VOS_UINT32 (*NAS_ACTION_FUNC)(VOS_UINT32 ulEventType ,struct MsgCB* pMsg);


/* ������ṹ */
typedef struct
{
    VOS_UINT32                          ulEventType;   /* �¼����� */
    NAS_ACTION_FUNC                     pfActionFun;   /* �������� */
}  NAS_ACT_STRU;


/* ״̬ת�Ʊ�ṹ */
typedef struct
{
    VOS_UINT32                          ulState;       /* ״̬                                */
    VOS_UINT32                          ulSize;        /* ������Ĵ�С�ֽ�������ACT�ṹ�Ĵ�С */
    NAS_ACT_STRU                       *pActTable;     /* ������Ļ���ַ                      */
}  NAS_STA_STRU;


/* ����״̬���������ṹ */
typedef struct
{
    NAS_STA_STRU                       *pStaTable;                /* ״̬ת�Ʊ�Ļ���ַ     */
    VOS_UINT32                          ulSize;                   /* ״̬ת�Ʊ�Ĵ�С       */
    VOS_CHAR                            aucName[NAS_FSM_NAME_LENGTH]; /* ����״̬��������       */
    NAS_EXCEP_FUN                       pfExceptHandle;           /* ���ڴ����쳣�Ļص����� */
    NAS_INIT_FUN                        pfInitHandle;             /* ���ڶ�ÿ��״̬�����г�ʼ���ĺ���*/
}  NAS_FSM_DESC_STRU;


typedef VOS_INT (* NAS_FSM_COMP_FUNC)(const VOS_VOID*, const VOS_VOID*);

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID NAS_FSM_RegisterFsm(
    NAS_FSM_DESC_STRU                   *pstFsmDesc,
    VOS_CHAR                            *pucName,
    VOS_UINT32                          ulSize,
    NAS_STA_STRU                        *pstStaTbl,
    NAS_EXCEP_FUN                       pfExceptHandle,
    NAS_INIT_FUN                        pfInitHandle
);

NAS_ACTION_FUNC NAS_FSM_FindAct(
    NAS_FSM_DESC_STRU                   *pstFsmDesc,
    VOS_UINT32                          ulState,
    VOS_UINT32                          ulEventType
);

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasFsm.h */
