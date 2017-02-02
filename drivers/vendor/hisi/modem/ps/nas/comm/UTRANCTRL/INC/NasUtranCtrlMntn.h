

#ifndef __NASUTRANCTRLMNTN_H__
#define __NASUTRANCTRLMNTN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "NasUtranCtrlCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)


/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_UTRANCTRL_OM_MSG_ID_ENUM
{
    NAS_UTRANCTRL_OM_MSG_LOG_FSM_INFO                       = 0x8000,           /* UTRANCTRL ģ��LOG FSM INFO */
    NAS_UTRANCTRL_OM_MSG_LOG_USER_CFG_EHPLMN_INFO,                              /* UTRANCTRL ģ��LOG USER CFG EHPLMN INFO */
    NAS_UTRANCTRL_OM_MSG_LOG_UTRAN_MODE_AUTO_SWITCH_INFO,                       /* UTRANCTRL ģ��LOG UTRANMODE AUTO SWITCH INFO */
    NAS_UTRANCTRL_OM_MSG_LOG_MSG_QUEUE_INFO,                                    /* UTRANCTRL ģ��LOG MSG QUEUE INFO */
    NAS_UTRANCTRL_OM_MSG_LOG_RUNNING_CONTEXT_FOR_PC_REPLAY  = 0x8500,           /* UTRANCTRL ģ��Ļط���Ϣ */
    NAS_UTRANCTRL_OM_MSG_BUTT
};
typedef VOS_UINT32  NAS_UTRANCTRL_OM_MSG_ID_ENUM_UINT32;

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

typedef struct
{
    NAS_UTRANCTRL_FSM_ID_ENUM_UINT32                        enFsmId;                /* ��ǰ��״̬������ */
    VOS_UINT32                                              ulState;                /* ��ǰ��״̬��״̬ */
    VOS_UINT8                                               ucSearchedSpecTdMccFlg; /* ��¼�Ƿ����ѵ��й������ʶ */
    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_ENUM_UINT8              enCurUtranSwitchMode;   /* ��ǰUTRAN���Զ��л�ģʽ */
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                     enCurrUtranMode;        /* NVIM�б����UTRANģʽ */
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                     enPreUtranMode;         /* �ϴη���RRC��UTRANģʽ */
    VOS_UINT8                                               ucReplaceMmcMsgFlg;     /* �滻����MMC����Ϣ���:VOS-TRUE:��Ҫ�û������Ϣ�滻����MMC����Ϣ��VOS_FALSE:����Ҫ�滻����MMC����Ϣ */
    VOS_UINT8                                               aucReserve[3];
}NAS_UTRANCTRL_LOG_FSM_INFO_STRU;
typedef struct
{
    VOS_MSG_HEADER
    NAS_UTRANCTRL_OM_MSG_ID_ENUM_UINT32                     enMsgId;            /* ��Ϣ���� */      /* _H2ASN_Skip */

    union
    {
        NAS_UTRANCTRL_LOG_FSM_INFO_STRU                     stLogFsmInfo;             /* ��ά�ɲ�LOG״̬����Ϣ */
        NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU           stUtranModeAutoSwitch;    /* ��ά�ɲ⵱ǰ�û����õ�UTRAN�л�ģʽ��ά�ɲ���Ϣ */
        NAS_UTRANCTRL_MSG_QUEUE_STRU                        stBufferEntryMsgQueue;    /* ��ά�ɲ⵱ǰUTRANCTRLģ��Ļ��������Ϣ */
    }u;
}NAS_UTRANCTRL_MNTN_INFO_STRU;




/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_SndOmUtranCtrlFsmInfo( VOS_VOID );
VOS_VOID  NAS_UTRANCTRL_SndOmUtranModeAutoSwitchInfo( VOS_VOID );
VOS_VOID  NAS_UTRANCTRL_SndOmBufferQueueMsg(VOS_VOID);

#endif  /* END OF #if (FEATURE_ON == FEATURE_UE_MODE_TDS)  */

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

#endif /* end of NasUtranCtrlMntn.h */
