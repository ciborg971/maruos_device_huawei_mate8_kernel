
#ifndef __BST_PAL_ACOMM_H__
#define __BST_PAL_ACOMM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_DRV_Common.h"
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_PalAcomRcvCb( len, pdata )  \
                    if( BST_NULL_PTR != g_BstPalAcommRcvCb )\
                    {\
                        g_BstPalAcommRcvCb( len, pdata );\
                    }

#define BST_ACOMM_ALLOC_MSG_WITH_HDR(MsgLen) \
                    (VOS_VOID *)PS_ALLOC_MSG_ALL_CHECK( UEPS_PID_BASTET,(sizeof(BST_ACOM_MSG_STRU)+MsgLen-4) )

#define BST_ACOMM_SEND_MSG(pMsg) \
                    if ( VOS_OK != PS_SND_MSG_ALL_CHECK( UEPS_PID_BASTET,(pMsg)) )\
                    {\
                        BST_RLS_LOG( "Send Msg Fail" );\
                    }

#define BST_ACOMM_CFG_MSG_HDR(pstMsg,ulRecvPid)\
                    (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid     = UEPS_PID_BASTET;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid   = (ulRecvPid)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulLen;
    VOS_UINT8                           aucValue[4];
} BST_ACOM_MSG_STRU;

/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/

BST_ERR_ENUM_UINT8  BST_Pal_DrvAcomSend( BST_UINT32   ulLength, BST_UINT8 *pucData );
BST_UINT32          BST_Pal_DrvAcomRecv( BST_UINT32   ulLength, BST_UINT8 *pucData );
BST_ERR_ENUM_UINT8  BST_Pal_DrvAcomInit( BST_DRV_READ_T pfRcvCb );

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
