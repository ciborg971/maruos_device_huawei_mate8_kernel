/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SsGlobal.h
  Description : Ssȫ�ֿ������ݽṹͷ�ļ�
  History     :
      1.  ��־��      2004.02.27   �°�����
      2.��    ��  : 2006��12��4��
        ��    ��  : luojian id:60022475
        �޸�����  : ���� #pragma pack(4)�����ⵥ��:A32D07779
*******************************************************************************/
#ifndef _SS_GLOBAL_H_
#define _SS_GLOBAL_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
#pragma pack(4)
/********************************************************************************/
/******************************SSʵ����Ϣ ***************************************/
/********************************************************************************/
typedef struct
{                                               /* SSʵ����Ϣ                   */
#define SS_S_NULL                0x00           /* S0:Null                      */
#define SS_S_CONNECT_PEND        0x01           /* S1:MM Connection pending     */
#define SS_S_CONNECTED           0x02           /* S2:MM Connection established */
    VOS_UINT8                  ucState;             /* SSʵ��״̬                   */
    VOS_UINT8                  ucCr;                /* ��¼TAF��Ϣ�е�CR            */
} SS_ENTITY_STRU;

/********************************************************************************/
/*****************************��Ϣ����BUFFER*************************************/
/********************************************************************************/
#define SS_MO_ENTITY_NUM          7             /* ���и������ֵ               */

typedef struct {
    VOS_UINT32  ulMsgLen;                            /* ������Ϣ�ĳ���               */
    VOS_UINT8  *pucMsg;                             /* ָ�򴢴���Ϣ��ָ��           */
} SS_SAVE_MSG_STRU;


/********************************************************************************/
/*****************************��̬�ڴ������Ϣ***********************************/
/********************************************************************************/
#define    SS_MAX_MEM_NUM         10            /* �ڴ�����������             */

typedef struct
{
    VOS_UINT8       ucMemNum;                       /* ��¼���ٵ��ڴ��ĸ���       */
    VOS_UINT32       *pulMemBlk[SS_MAX_MEM_NUM];     /* ָ��ÿ�����ٵ��ڴ��ĵ�ַ   */
} SS_MEMORY_MNG_STRU;


/********************************************************************************/
/******************************TIMER������Ϣ*************************************/
/********************************************************************************/
typedef struct
{
    HTIMER    SsTimerId;                      /* �洢VOS�����Timer id        */

#define    SS_TIMER_IDLE      0x00              /* ��Timerδ����                */
#define    SS_TIMER_RUN       0x01              /* ��Timer������                */
#define    SS_TIMER_EXPIRY    0x02              /* ��Timer�����                */
    VOS_UINT8       ucTimerState;                   /* ��Timer��״̬                */
} SS_TIMER_MNG_STRU;

/********************************************************************************/
/******************************OM������Ϣ*************************************/
/********************************************************************************/

enum NAS_SS_OM_MSG_ID_ENUM
{
    /* CC���͸�OM����Ϣ */
    SSOM_LOG_STATE_INFO_IND                       = 0x1000,      /*_H2ASN_MsgChoice  NAS_SS_LOG_STATE_INFO_STRU */

    SSOM_LOG_BUTT
};
typedef VOS_UINT32 NAS_SS_OM_MSG_ID_ENUM_U32;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucSsState;
    VOS_UINT8                           aucRsv3[3];
}NAS_SS_LOG_STATE_INFO_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

#endif
