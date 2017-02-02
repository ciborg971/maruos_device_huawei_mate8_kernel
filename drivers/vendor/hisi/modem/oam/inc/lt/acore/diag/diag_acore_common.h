/******************************************************************************

    Copyright(C)2014,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : diag_acore_common.h
  Description     :
  History         :
     1.cuijunqiang       2015-06-13     Draft Enact
     2.
******************************************************************************/

#ifndef __DIAG_ACORE_COMMON_H__
#define __DIAG_ACORE_COMMON_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "blist.h"
#include "OmCommon.h"
#include "msp_diag_comm.h"


/*****************************************************************************
  2 macro
*****************************************************************************/

#define     DIAG_DEBUG_TRANS                (0x00000001)

#define     DIAG_ERRORLOG_TIMER_NAME        (0x00001001)

#define     DIAG_ERRORLOG_TIMER_PARA        (0x0000EFFE)

#define     DIAG_CLTINFO_TIMER_NAME         (0x00002002)

#define     DIAG_CLTINFO_TIMER_PARA         (0x0000DFFD)



/* SOCKET�Դ��������ջ�ռ� */
#define     RL_SOCK_TASK_STACK_SIZE         (8096)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

typedef struct
{
    LIST_S          TransHead;          /* ͸�����������ͷ��� */
    VOS_SEM         TransSem;           /* ͸�������������ź��� */
}DIAG_TRANS_HEADER_STRU;


typedef struct
{
    VOS_UINT32      ulMagicNum;         /* ��ЧֵΪTRANS��ǰ4����ĸ��ASCII�� 0x5452414E */
    HTIMER          Timer;              /* ÿ���ڵ���һ��TIMER���ж��Ƿ�ʱ */
    LIST_S          DiagList;           /* ָ����һ������ڵ��������� */
    VOS_SEM         *pSem;              /* ��¼����Ļ����ź�������ʱʱʹ�� */

    VOS_UINT8       ucRcvData[0];       /* �����·�������SOCP������ */
}DIAG_TRANS_NODE_STRU;


/* APP_OM_MSG_STRU��Э��ջ���� */
typedef APP_OM_MSG_STRU DIAG_TRANS_MSG_STRU;


/*****************************************************************************
���� : ͸������Ĳ����ṹ
REQ : DIAG_PS_MSG_STRU
CNF : DIAG_TRANS_CNF_STRU
*****************************************************************************/

/* ͸�������Ӧ��ṹ */
typedef struct
{
    VOS_UINT32          ulAuid;         /* ԭAUID*/
    VOS_UINT32          ulSn;           /* HSO�ַ�������������*/
    VOS_UINT8           aucPara[0];     /* �������� */
}DIAG_TRANS_CNF_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID diag_TransTimeoutProc(REL_TIMER_MSG *pTimer);

extern VOS_UINT32 diag_TransCnfProc(VOS_UINT8* pstCnf ,VOS_UINT32 ulLen, 
                                    DIAG_MESSAGE_TYPE_U32 ulGroupId, DIAG_TRANS_HEADER_STRU *pstHead);

extern DIAG_TRANS_NODE_STRU* diag_AddTransInfoToList(VOS_UINT8 * pstReq, VOS_UINT32 ulRcvlen, 
                                    DIAG_TRANS_HEADER_STRU *pstHead);

extern DIAG_TRANS_NODE_STRU * diag_IsTransCnf(DIAG_TRANS_MSG_STRU* pstPsCnf, DIAG_TRANS_HEADER_STRU *pstHead);

extern VOS_VOID diag_GetTransInfo(MSP_DIAG_CNF_INFO_STRU *pstInfo, 
                                 DIAG_TRANS_CNF_STRU    *pstDiagCnf, 
                                 DIAG_TRANS_MSG_STRU    *pstPsCnf,
                                 DIAG_TRANS_NODE_STRU   *pNode);

extern VOS_VOID diag_DelTransCmdNode(DIAG_TRANS_NODE_STRU* pTempNode);

extern VOS_UINT32 diag_TransReqProcEntry(DIAG_FRAME_INFO_STRU *pstReq, DIAG_TRANS_HEADER_STRU *pstHead);

#if(FEATURE_ON == FEATURE_PTM)
extern VOS_VOID OM_AcpuRcvMsgFinish(VOS_VOID);
#endif

extern VOS_VOID OM_AcpuCltInfoCnfMsgProc(MsgBlock* pMsg);
extern VOS_VOID OM_AcpuCltInfoCnfNotNeedProcessSetFlag(VOS_VOID);
extern VOS_VOID OM_AcpuRcvCltInfoFinish(VOS_VOID);

extern VOS_VOID PPM_SockOmServerTask(VOS_VOID);
extern VOS_VOID PPM_SockAtServerTask(VOS_VOID);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of msp_acore_common.h */

