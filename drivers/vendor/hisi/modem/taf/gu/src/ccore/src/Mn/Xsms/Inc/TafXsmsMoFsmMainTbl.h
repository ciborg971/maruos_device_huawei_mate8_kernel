

#ifndef _TAF_XSMS_MO_FSM_MAIN_TBL_H_
#define _TAF_XSMS_MO_FSM_MAIN_TBL_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
/* Mo״̬��״̬ȫ�ֱ��� */
extern TAF_FSM_DESC_STRU                       g_stTafXsmsMoFsmDesc;

/* Xsms Mo״̬��״̬����� */
extern TAF_STA_STRU                            g_astTafXsmsMoStaTbl[];

/* XSMS Mo_IDLE�µ��¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMoIdleActTbl[];

/* XSMS MoWaitFdnCnf ���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMoWaitFdnCnfActTbl[];


/* XSMS Mo_WAIT_CC_CNF���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMoWaitCcCNFActTbl[];

/* XSMS MO_WAITING_XCC_ORIG_CALL_CNF���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMoWaitXccCallCnfActTbl[];

/* XSMS Mo_WAITING_XCC_SO_IND���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMoWaitXccSoIndActTbl[];

/* XSMS MO_WAITING_AS_CNF״̬���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMoWaitAsCnfActTbl[];

/* XSMS MO_WAITING_TL_ACK״̬���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMoWaitTlAckActTbl[];

/* XSMS MO_WAITING_XCC_END_CALL_CNF ״̬���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMoWaitCallEndActTbl[];




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
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

extern VOS_UINT32 TAF_XSMS_GetMoFsmTblNum(VOS_VOID);

#endif

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

#endif /* end of TafXsmsMoFsmMainTbl.h */

