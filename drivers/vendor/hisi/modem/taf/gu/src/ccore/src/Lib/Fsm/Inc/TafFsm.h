
#ifndef _TAF_FSM_H_
#define _TAF_FSM_H_

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
#define TAF_FSM_NAME_LENGTH             (32)

/* ��PID,MsgName,�Լ�EventType�Ĳ��� */
/*
    Լ��: PID�ṹ Bit0~Bit11: ģ��ID  Bit12~Bit15: ���� Bit16~Bit19: CPU ID Bit20~Bit31: ����
    ��: PID: 0x000A0BCD  ->  0x0000ABCD  ->  0xABCD0000
        MSG: 0x0000abcd
        EVT: 0xABCDabcd
*/
#define TAF_BuildEventType(ulSndPid,usMsgName) \
    (((VOS_UINT32)(/*lint -e778*/((ulSndPid) & 0xF0000)/*lint +e778*/ \
    | (((ulSndPid) & 0xFFF) << 4)) << 12) | (VOS_UINT16)(usMsgName))      /* ���� Pid�Լ�usMsgName ����EventType  */

#define TAF_ExtractMsgNameFromEvtType(ulEventType)     ((VOS_UINT16)((ulEventType) & 0x0000FFFF))          /* ��EventType�л�ȡMsgName     */
#define TAF_ExtractSndPidFromEvtType(ulEventType)  \
    ((((ulEventType) & 0xFFF0000) >> 16) | (((ulEventType) & 0xF0000000) >> 12))   /* ��EventType�л�ȡSndPid      */

/* ״̬������� */
#define TAF_STA_TBL_ITEM(ulState, astActTbl)\
{\
    ( ulState),\
    ((sizeof(astActTbl))/sizeof(TAF_ACT_STRU)),\
    (astActTbl)\
}

#define TAF_ACT_TBL_ITEM(PID, enMsgType, pActFun)\
{\
    (((VOS_UINT32)(/*lint -e778*/((PID) & 0xF0000)/*lint +e778*/ \
    | (((PID) & 0xFFF) << 4)) << 12) | (VOS_UINT16)(enMsgType)),\
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
typedef VOS_UINT32 ( * TAF_EXCEP_FUN )
(
    VOS_UINT32, /* EVENT ID,����PID��MSG ID */
    VOS_VOID *  /* ��Ϣָ�� */
);

/* ״̬����ʼ�������������Ͷ��� */
typedef VOS_VOID ( * TAF_INIT_FUN )
(
    VOS_VOID
);


/* ���������������Ͷ��� */
typedef VOS_UINT32 (*TAF_ACTION_FUNC)(VOS_UINT32 ulEventType ,struct MsgCB* pMsg);


/* ������ṹ */
typedef struct
{
    VOS_UINT32                          ulEventType;   /* �¼����� */
    TAF_ACTION_FUNC                     pfActionFun;   /* �������� */
}  TAF_ACT_STRU;


/* ״̬ת�Ʊ�ṹ */
typedef struct
{
    VOS_UINT32                          ulState;       /* ״̬                                */
    VOS_UINT32                          ulSize;        /* ������Ĵ�С�ֽ�������ACT�ṹ�Ĵ�С */
    TAF_ACT_STRU                       *pActTable;     /* ������Ļ���ַ                      */
}  TAF_STA_STRU;


/* ����״̬���������ṹ */
typedef struct
{
    TAF_STA_STRU                       *pStaTable;                /* ״̬ת�Ʊ�Ļ���ַ     */
    VOS_UINT32                          ulSize;                   /* ״̬ת�Ʊ�Ĵ�С       */
    VOS_CHAR                            aucName[TAF_FSM_NAME_LENGTH]; /* ����״̬��������       */
    TAF_EXCEP_FUN                       pfExceptHandle;           /* ���ڴ����쳣�Ļص����� */
    TAF_INIT_FUN                        pfInitHandle;             /* ���ڶ�ÿ��״̬�����г�ʼ���ĺ���*/
}  TAF_FSM_DESC_STRU;


typedef VOS_INT (* TAF_FSM_COMP_FUNC)(const VOS_VOID*, const VOS_VOID*);

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID TAF_FSM_RegisterFsm(
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_CHAR                           *pucName,
    VOS_UINT32                          ulSize,
    TAF_STA_STRU                       *pstStaTbl,
    TAF_EXCEP_FUN                       pfExceptHandle,
    TAF_INIT_FUN                        pfInitHandle
);

TAF_ACTION_FUNC TAF_FSM_FindAct(
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
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
