

#ifndef __BST_IP_RAW_CALL_BACK_H__
#define __BST_IP_RAW_CALL_BACK_H__
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_IP_Define.h"
#include "BST_OS_Thread.h"
#include "BST_LIB_List.h"
#include "BST_SRV_AsEvnt.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#ifdef BST_SSL_SUPPORT
#define BST_IP_SOCKET_SUPPORT_TABLE \
    BST_SCKT_TYPE_TCP,  \
    BST_SCKT_TYPE_SSL,  \
    BST_SCKT_TYPE_UDP
#else
#define BST_IP_SOCKET_SUPPORT_TABLE \
    BST_SCKT_TYPE_TCP,  \
    BST_SCKT_TYPE_UDP
#endif

#define BST_IP_SocketSupportTblHead()   ( &g_BST_IP_SocketSupportTable[0] )
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  5 �ṹ����
*****************************************************************************/
class BST_IP_CNetRcver;
class BST_IP_CSocket;

typedef struct{
    NODE                            node;
    BST_IP_CNetRcver               *pcRcver;
    BST_IP_CSocket                 *pcSocket;
}BST_IP_RCVER_BINDER_STRU;

class BST_IP_CRcverMng
{
BST_PUBLIC:
    BST_VOID                       *Attach(
        BST_IP_CNetRcver   *pcRawRcver,
        BST_IP_CSocket     *pcSocket );

    BST_VOID                        Detach(
        BST_IP_CSocket     *pcSocket );

    static BST_IP_CRcverMng        *GetInstance( BST_VOID );

    BST_IP_ERR_T                    CnctedRcver(
        BST_INT32           fd );

    BST_VOID                        ErrorRcver(
        BST_INT32           lFd,
        BST_IP_ERR_T        InIpErrMsg );

    BST_IP_PKTPROC_MODE_ENUM        PacketRcver(
        BST_INT32           fd );

    BST_VOID                    AckedRcver(
        BST_INT32           fd,
        const BST_UINT32    ulMinNumber,
        const BST_UINT32    ulMaxNumber );

BST_PRIVATE:
    BST_IP_CRcverMng( BST_VOID );

   ~BST_IP_CRcverMng( BST_VOID );

    BST_IP_RCVER_BINDER_STRU       *FindRcver( BST_INT32 fd );

    LIST                            m_stRcverList;
};

class BST_IP_CNetRcver
{
BST_PUBLIC:
    virtual BST_IP_ERR_T                Connectd(
        BST_IP_CSocket     *pcSocket )
    {
        return BST_IP_ERR_OK;
    }

    virtual BST_IP_PKTPROC_MODE_ENUM    Received(
        BST_IP_CSocket     *pcSocket,
        const BST_UINT8    *const pucData,
        const BST_UINT16    usLength )
    {
        return BST_IP_PKT_REMOVE_PROC;
    }

    virtual BST_VOID                    IpErr(
        BST_IP_CSocket     *pcSocket,
        BST_IP_ERR_T        InIpErrMsg )
    {
        return;
    }

    virtual BST_VOID                    Acked(
        BST_IP_CSocket     *pcSocket,
        const BST_UINT32            ulMinNumber,
        const BST_UINT32            ulMaxNumber )
    {
        return;
    }
};
/*
 * �½�һ������ģʽ������������As���¼�
 */
class BST_IP_CAsRcver:BST_PUBLIC BST_SRV_CAsRcver
{
BST_PUBLIC:
    static BST_IP_CAsRcver        *GetInstance( BST_VOID );

BST_PRIVATE:
    BST_IP_CAsRcver( BST_VOID );
    
   ~BST_IP_CAsRcver( BST_VOID );

    BST_VOID            AsEventCallback(
        BST_AS_EVT_ENUM_UINT32  enEvent,
        BST_UINT32              ulLength,
        BST_VOID               *pvData );

    BST_UINT32          m_ulCurrentRat;
    BST_UINT32          m_ulOldRrcStatus;
};

/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  8 ��������
*****************************************************************************/
BST_IP_ERR_T BST_IP_CheckSocketSupport( BST_SCKT_TYPE_ENUM_UINT32 stSocketType );

BST_IP_ERR_T BST_IP_ReceivedCB( BST_INT32 lFd );

BST_IP_ERR_T BST_IP_TcpConnectedCB( BST_INT32 lFd );

BST_VOID BST_IP_TcpErrorCB( BST_INT32 lFd, BST_IP_ERR_T InIpErrMsg );

BST_IP_ERR_T BST_IP_TcpOverFlowCB( BST_UINT32 ulRealFlowValue );

BST_VOID BST_IP_TcpAckedCB(
    BST_INT32           lFd,
    const BST_UINT32    ulMinNumber,
    const BST_UINT32    ulMaxNumber);
/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
