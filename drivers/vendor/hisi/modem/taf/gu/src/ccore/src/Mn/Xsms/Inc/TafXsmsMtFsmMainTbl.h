

#ifndef _TAF_XSMS_MT_FSM_MAIN_TBL_H_
#define _TAF_XSMS_MT_FSM_MAIN_TBL_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

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
/* MT״̬��״̬ȫ�ֱ��� */
extern TAF_FSM_DESC_STRU                g_stTafXsmsMtFsmDesc;

/* Xsms MT״̬��״̬����� */
extern TAF_STA_STRU                     g_astTafXsmsMtStaTbl[];

/* XSMS Mo_IDLE�µ��¼������ */
extern TAF_ACT_STRU                     g_astTafXsmsMtIdleActTbl[];

/* XSMS MT_WAITING_XCC_CALL_CONN���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitXccConnActTbl[];

/* XSMS MT_WAITING_XCC_CNF���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitXccAnsCallCnfActTbl[];

/* XSMS MT_WAITING_XCC_SO_IND���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitXccSoIndActTbl[];

/* XSMS MT_WAITING_DSDH_DATA_IND״̬���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitingDSCHDataIndActTbl[];

/* XSMS MT_WAITING_WRITE_UIM_CNF״̬���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitingWriteUimCnfActTbl[];

/* XSMS MT_WAITING_READ_UIM_CNF״̬���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitingReadUimCnfActTbl[];

/* XSMS MT_WAITING_AS_CNF״̬���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitingAsCnfActTbl[];

/* XSMS MT_WAITING_END_CALL_CNF״̬���¼������ */
extern TAF_ACT_STRU                            g_astTafXsmsMtWaitingXccDisconnectActTbl[];





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
extern VOS_UINT32 TAF_XSMS_GetMtFsmTblNum(VOS_VOID);
#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
