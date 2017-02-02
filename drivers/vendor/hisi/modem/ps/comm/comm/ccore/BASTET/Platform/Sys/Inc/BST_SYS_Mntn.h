

#ifndef __BST_SYSMNTN_H__
#define __BST_SYSMNTN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_OS_Timer.h"
#include "BST_Typedefine.h"
#include "BST_LIB_List.h"
#include "OmBastetInterface.h"


#if (BST_OS_VER != BST_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*��ȡAPP��Ϣ��ͷ*/
#define BST_SYS_MNTN_GetAppListHead()       ( &g_stBstMntnEntity.stAppList )
/*��ȡ��ǰ���ص�APP��������main_task��*/
#define BST_SYS_MNTN_GetAppNumber()         ( g_stBstMntnEntity.stAppList.count )
/*��ȡ�ϱ�TIMER_ID*/
#define BST_SYS_MNTN_GetTimerId()           ( g_stBstMntnEntity.stReportTimer )
/*��ȡ��ǰ����IP��ַ����*/
#define BST_SYS_MNTN_GetLocalIpHead()       ( &g_stBstMntnEntity.aucLocalIp[0] )
/*�鿴��һ��3���ڣ��Ƿ���mntn���ݱ�����*/
#define BST_SYS_MNTN_IsMntnMsgChanged()     ( BST_TRUE == g_stBstMntnEntity.ucChanged )
/*��ȡMNTNϵͳ�Ƿ񱻳�ʼ����Ϣ*/
#define BST_SYS_MNTN_IsMntnInited()         ( BST_TRUE == g_stBstMntnEntity.ucIsInit )
/*���ò�����ʶ*/
#define BST_SYS_MNTN_SetMntnMsgChgFlag()    ( g_stBstMntnEntity.ucChanged = BST_TRUE )
/*���������ʶ*/
#define BST_SYS_MNTN_ClrMntnMsgChgFlag()    ( g_stBstMntnEntity.ucChanged = BST_FALSE)
/*�޲����ϱ�����*/
#define BST_SYS_MNTN_REPORT_TIMER_LEN       ( 3000U )
/*��Ϣͷ����*/
#define BST_OM_HEADER_LEN                   ( 4U )
/*������APP������maintaskҲ��һ��*/
#define BST_SYS_MNTN_MAX_APP_NUMBER         ( BST_MAX_APP_NUMBER+1)
/*�������ֵ����ֹ�ۼ����*/
#define BST_SYS_MNTN_MAX_TRAFFIC_FLOW       ( 0x7FFFFFFF )

/*��ά�ɲ���Ϣ���ڴ����*/
#define BST_ALLOC_MSG(ulSndPid, pSndMsg,ulMsgLen)\
        {\
            pSndMsg = (BST_VOID *)PS_ALLOC_MSG(ulSndPid, ((ulMsgLen) - VOS_MSG_HEAD_LENGTH ));\
            if (BST_NULL_PTR != (pSndMsg))\
            {\
                PS_MEM_SET((BST_UINT8 *)pSndMsg, 0, ulMsgLen);\
                ((MsgBlock *)pSndMsg)->ulLength = (ulMsgLen) - VOS_MSG_HEAD_LENGTH;\
            }\
        }

/*��ά�ɲ���Ϣ���ڴ��ͷ�*/
#define BST_FREE_MSG(ulPid, pMsg)             PS_FREE_MSG( ulPid, (pMsg) )
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
 �ṹ��    : BST_SYS_MNTN_ENTITY_STRU
 �ṹ˵��  : 
*****************************************************************************/
typedef struct
{
    LIST                                stAppList;                      /*Ӧ����������*/
    BST_OS_TIMERID_T                    stReportTimer;                  /*�޲�����ʱ������ʱ��*/
    BST_UINT8                           aucLocalIp[OM_BST_IP_ADDR_LEN]; /*��ǰ����IP��ַ*/
    BST_UINT8                           ucChanged;                      /*������ʶ*/
    BST_UINT8                           ucIsInit;                       /*������ʶ*/
    BST_UINT8                           aucReserved[2];
}BST_SYS_MNTN_ENTITY_STRU;
/*****************************************************************************
 �ṹ��    : BST_SYS_MNTN_APP_NODE_STRU
 �ṹ˵��  : 
*****************************************************************************/
typedef struct
{
    NODE                                node;
    OM_BST_APP_INFO_STRU                stAppInfo;
}BST_SYS_MNTN_APP_NODE_STRU;

/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  8 ��������
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (BST_OS_VER != BST_WIN32)
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

