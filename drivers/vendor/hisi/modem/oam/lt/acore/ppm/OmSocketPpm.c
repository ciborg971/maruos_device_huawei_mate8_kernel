

/*****************************************************************************
  1 ͷ�ļ�����
**************************************************************************** */
#include "OmCommonPpm.h"
#include "OmSocketPpm.h"
#include "cpm.h"
#include "NVIM_Interface.h"

#if (VOS_WIN32 == VOS_OS_VER)
#include "OmAppRl.h"
#include <winsock2.h>
#include <windows.h>
#endif

#if (VOS_LINUX == VOS_OS_VER)
#include "hisocket.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767*/
#define  THIS_FILE_ID        PS_FILE_ID_OM_SOCKET_PPM_C
/*lint +e767*/


/* ****************************************************************************
  2 ȫ�ֱ�������
**************************************************************************** */
COMM_SOCKET_CTRL_INFO_STRU g_astSockInfo[SOCKET_BUTT] =
            {{SOCK_NULL, SOCK_NULL, VOS_NULL_PTR, CPM_WIFI_OM_IND_PORT, SOCK_OM_IND_SRC_PORT_NUM,       {0,}},
             {SOCK_NULL, SOCK_NULL, VOS_NULL_PTR, CPM_WIFI_OM_CFG_PORT, SOCK_OM_CFG_SRC_PORT_NUM,       {0,}},
             {SOCK_NULL, SOCK_NULL, VOS_NULL_PTR, CPM_WIFI_AT_PORT,     SOCK_AT_SRC_PORT_NUM,           {0,}}
            };

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/

#if ((VOS_OS_VER == VOS_WIN32) || (FEATURE_HISOCKET == FEATURE_ON))
/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : XXXXXXXX
    �޸�����   : V8R1 OM_Optimize��Ŀ����

*****************************************************************************/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*���浱ǰSOCKET��״̬*/
VOS_UINT32          g_ulSockState = SOCK_OK;

/* ���������������Դ���������ٽ���Դ���� */
VOS_SPINLOCK        g_stSockTaskSpinLock;

/*���浱ǰSOCKETOM�ĳ�ʼ��״̬*/
VOS_UINT32          g_ulSockOMInitState  = VOS_FALSE;

/*���浱ǰSOCKETAT�ĳ�ʼ��״̬*/
VOS_UINT32          g_ulSockATInitState = VOS_FALSE;

VOS_UINT32          g_ulOmIsReConn      = VOS_FALSE;
VOS_UINT32          g_ulAtIsReConn      = VOS_FALSE;


SOCKET_UDP_INFO_STRU g_stUdpInfo = {VOS_FALSE, };


VOS_BOOL PPM_SockIsEnable(VOS_VOID)
{
#if (VOS_LINUX == VOS_OS_VER)
    OM_CHANNLE_PORT_CFG_STRU    stPortCfg;

    /* ��ȡOM���������ͨ�� */
    if (NV_OK != NV_Read(en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
    {
        return VOS_FALSE;
    }

    //stPortCfg.enPortNum += CPM_APP_PORT;

    /* ������*/
    if (CPM_OM_PORT_TYPE_WIFI != stPortCfg.enPortNum)
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}
#if 0

VOS_VOID PPM_SockShutdownAll(VOS_VOID)
{
    VOS_UINT32 ulIndex;

    for (ulIndex = 0; ulIndex < SOCKET_BUTT; ulIndex++)
    {
        if (SOCK_NULL != g_astSockInfo[ulIndex].socket)
        {
            (VOS_VOID)VOS_SmP(g_astSockInfo[ulIndex].SmClose, 0);

            closesocket(g_astSockInfo[ulIndex].socket);

            g_astSockInfo[ulIndex].socket = SOCK_NULL;

            /*lint -e534*/
            VOS_SmV(g_astSockInfo[ulIndex].SmClose);
            /*lint +e534*/
        }
    }

    return;
}
#endif


VOS_UINT32 PPM_SockUdpInit(VOS_VOID)
{
    COMM_SOCKET_CTRL_INFO_STRU *pstSockInfo = g_astSockInfo + SOCKET_OM_IND;
    
    pstSockInfo->socket = socket(AF_INET, SOCK_DGRAM, 0);

    if (VOS_OK > pstSockInfo->socket)
    {
        return VOS_ERR;
    }

    /* ����SOCKET�����ź��� */
    if (CPM_WIFI_OM_IND_PORT == pstSockInfo->enPhyPort)
    {
        if(VOS_OK != VOS_SmMCreate("INDSOCK", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &pstSockInfo->SmClose))
        {
            closesocket(pstSockInfo->socket);
            return VOS_ERR;
        }
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_BOOL PPM_SockTcpInit(COMM_SOCKET_CTRL_INFO_STRU *pstSockInfo)
{
    /* ����SOCKET�����ź��� */
    if (CPM_WIFI_OM_CFG_PORT == pstSockInfo->enPhyPort)
    {
        if(VOS_OK != VOS_SmMCreate("CFGSOCK", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &pstSockInfo->SmClose))
        {
            return VOS_FALSE;
        }
    }
    else if (CPM_WIFI_AT_PORT == pstSockInfo->enPhyPort)
    {
        if(VOS_OK != VOS_SmMCreate("ATSOCK", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &pstSockInfo->SmClose))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        return VOS_FALSE;
    }
    return VOS_TRUE;
}
VOS_VOID PPM_SockBindListen(COMM_SOCKET_CTRL_INFO_STRU *pstSockInfo)
{
    struct sockaddr_in  sAddr;
    VOS_INT             lAddLen;

    if((SOCK_NULL != pstSockInfo->listener)||
       (SOCK_NULL != pstSockInfo->socket))
    {
        return;
    }

    pstSockInfo->listener = socket(AF_INET, SOCK_STREAM, 0);

    if (VOS_OK > pstSockInfo->listener)
    {
        vos_printf("[%s][%d]:socket err !\n",__FUNCTION__,__LINE__);
        pstSockInfo->listener = SOCK_NULL;
        VOS_TaskDelay(100);/*delay 100 ms*/
        return ;
    }

    /*lint -e534*/
    VOS_MemSet(&sAddr, 0, sizeof(sAddr));
    /*lint +e534*/
    sAddr.sin_family = AF_INET;

    sAddr.sin_addr.s_addr = 0;

    /* �����Ķ˿ں� */
    sAddr.sin_port = htons(pstSockInfo->usPort);

    lAddLen = sizeof(struct sockaddr_in);

    /* ������Socket�󶨵���Ӧ�Ķ˿��� */
    if (SOCKET_ERROR == bind(pstSockInfo->listener, (struct sockaddr *)&sAddr, lAddLen))
    {
        closesocket(pstSockInfo->listener);
        pstSockInfo->listener = SOCK_NULL;
        vos_printf("[%s][%d]:bind err !\n",__FUNCTION__,__LINE__);
        return ;
    }

    /* ���÷������˼��������ͻ����� */
    if (SOCKET_ERROR == listen(pstSockInfo->listener, SOCKET_NUM_MAX))
    {
        closesocket(pstSockInfo->listener);
        pstSockInfo->listener = SOCK_NULL;
        vos_printf("[%s][%d]:listen err !\n",__FUNCTION__,__LINE__);
        return ;
    }
}

VOS_VOID PPM_SockAcceptRecv(COMM_SOCKET_CTRL_INFO_STRU *pstSockInfo)
{
    Ip_fd_set                               listen1,listen2;
    VOS_INT32                               ret;
    VOS_INT32                               len;
    struct sockaddr_in                      from;
    VOS_ULONG                               ulLockLevel;
    SOCKET                                  socket;
    SOCKET                                  maxSocket;

    if((SOCK_NULL == pstSockInfo->listener)&&(SOCK_NULL == pstSockInfo->socket))
    {
        vos_printf("[%s][%d]:listener && socket err ! %d\n",__FUNCTION__,__LINE__,pstSockInfo->usPort);
        return;
    }
    HI_FD_ZERO(&listen1);
    HI_FD_ZERO(&listen2);

    HI_FD_SET(pstSockInfo->listener, &listen1);

    if(SOCK_NULL != pstSockInfo->socket)
    {
        HI_FD_SET(pstSockInfo->socket, &listen1);
    }

    VOS_MemCpy(&listen2,&listen1,sizeof(Ip_fd_set));

    maxSocket = pstSockInfo->socket > pstSockInfo->listener ? pstSockInfo->socket : pstSockInfo->listener;

    ret = select((int)maxSocket + 1,&listen1, NULL, &listen2, NULL);
    if(ret < 0)
    {
        vos_printf("[%s][%d]:select err ! %d \n",__FUNCTION__,__LINE__,pstSockInfo->usPort);
        return;
    }

    if((pstSockInfo->listener != SOCK_NULL) && (HI_FD_ISSET(pstSockInfo->listener, &listen1)))
    {
        len = sizeof(struct sockaddr_in);
        socket = accept(pstSockInfo->listener, (struct sockaddr *)&from, (int *)&len);
        if(socket < 0)
        {
            closesocket(pstSockInfo->listener);
            pstSockInfo->listener = SOCK_NULL;
            vos_printf("[%s][%d]:accept err !%d \n",__FUNCTION__,__LINE__,pstSockInfo->usPort);
        }
        else
        {
            if(SOCK_NULL != pstSockInfo->socket)
            {
                if(pstSockInfo->enPhyPort == CPM_WIFI_OM_CFG_PORT)
                {
                    g_ulOmIsReConn = VOS_TRUE;
                }
                if(pstSockInfo->enPhyPort == CPM_WIFI_AT_PORT)
                {
                    g_ulAtIsReConn = VOS_TRUE;
                }
                (VOS_VOID)VOS_SmP(pstSockInfo->SmClose, 0);
                closesocket(pstSockInfo->socket);
                /*lint -e534*/
                VOS_SmV(pstSockInfo->SmClose);
                /*lint +e534*/
            }

            (VOS_VOID)VOS_SmP(pstSockInfo->SmClose, 0);
            pstSockInfo->socket = socket;
            /*lint -e534*/
            VOS_SmV(pstSockInfo->SmClose);
            /*lint +e534*/

            if(CPM_WIFI_OM_CFG_PORT == pstSockInfo->enPhyPort)
            {
                if(0 > getpeername(pstSockInfo->socket, &g_stUdpInfo.stAddr, (int *)&len))
                {
                    vos_printf("getpeername failed.\n");
                }
                else
                {
                    /* ��ȡ�Զ˵�ַ���޸Ķ˿ںţ�����UDP���� */
                    g_stUdpInfo.stAddr.sin_port = htons(g_astSockInfo[SOCKET_OM_IND].usPort);
                    
                    g_stUdpInfo.bStatus = VOS_TRUE;
                }
            }
        }
    }

    if(SOCK_NULL == pstSockInfo->socket)
    {
        vos_printf("[%s][%d]:SOCK_NULL == pstSockInfo->socket ,%d!\n",__FUNCTION__,__LINE__,pstSockInfo->usPort);
        return;
    }

    ret = recv((int)pstSockInfo->socket, pstSockInfo->aucBuf, SOCK_OM_MSG_LEN, 0);
    if(ret <= 0)    /*�ͻ��˶Ͽ�֮�����˻�����ܵ�����Ϊ0�����ݰ�*/
    {
        (VOS_VOID)VOS_SmP(pstSockInfo->SmClose, 0);
        shutdown(pstSockInfo->socket,SHUT_RDWR);
        pstSockInfo->socket   = SOCK_NULL;
        /*lint -e534*/
        VOS_SmV(pstSockInfo->SmClose);
        /*lint +e534*/
        if(pstSockInfo->enPhyPort == CPM_WIFI_OM_CFG_PORT)
        {
            PPM_DisconnectAllPort(OM_LOGIC_CHANNEL_CNF);
            
            g_stUdpInfo.bStatus = VOS_FALSE;
        }
        vos_printf("[%s][%d]:rcv err %d!\n",__FUNCTION__,__LINE__,pstSockInfo->usPort);
        return;
    }

    VOS_SpinLockIntLock(&g_stSockTaskSpinLock, ulLockLevel);
    /*�����յ��������ύ���ϲ㴦��*/
    CPM_ComRcv(pstSockInfo->enPhyPort, pstSockInfo->aucBuf, ret);

    VOS_SpinUnlockIntUnlock(&g_stSockTaskSpinLock, ulLockLevel);
}
VOS_VOID PPM_SockServerProc(COMM_SOCKET_CTRL_INFO_STRU *pstSockInfo)
{
    for(;;)
    {
        PPM_SockBindListen(pstSockInfo);
        PPM_SockAcceptRecv(pstSockInfo);
    }

}


VOS_VOID PPM_SockOmServerTask(VOS_VOID)
{
    /* ��ʼ��CFG�ڵ�SOCKET������TCPЭ�� */
    if (VOS_FALSE == PPM_SockTcpInit(g_astSockInfo + SOCKET_OM_CFG))
    {
        return;
    }

    g_ulSockState = SOCK_START;

	g_ulSockOMInitState = VOS_TRUE;
    /* CFG���Դ���ѭ��������� */
    PPM_SockServerProc(g_astSockInfo + SOCKET_OM_CFG);

    return;
}



VOS_VOID PPM_SockAtServerTask(VOS_VOID)
{
    /* ��ʼ��SOCKET */
    if (VOS_FALSE == PPM_SockTcpInit(g_astSockInfo + SOCKET_AT))
    {
        return;
    }

    g_ulSockATInitState = VOS_TRUE;

    PPM_SockServerProc(g_astSockInfo + SOCKET_AT);

    return;
}
VOS_INT32 PPM_SockOMIndComSend(VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT16 uslength)
{
    SOCKET                              socket;
    VOS_INT                             nSndNum;

    (VOS_VOID)VOS_SmP(g_astSockInfo[SOCKET_OM_IND].SmClose, 0);

    socket = g_astSockInfo[SOCKET_OM_IND].socket;

    if ((SOCK_NULL == socket) || (VOS_FALSE == g_stUdpInfo.bStatus))
    {
        /*lint -e534*/
        VOS_SmV(g_astSockInfo[SOCKET_OM_IND].SmClose);
        /*lint +e534*/

        return VOS_ERR;
    }

    /* ����send������ͨ��socket���ͳ�ȥ����UDP */
    nSndNum = sendto(socket, pucVirAddr, uslength, 0, &g_stUdpInfo.stAddr, sizeof(g_stUdpInfo.stAddr));

    /*lint -e534*/
    VOS_SmV(g_astSockInfo[SOCKET_OM_IND].SmClose);
    /*lint +e534*/

    if (nSndNum != uslength)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_INT32 PPM_SockOMCfgComSend(VOS_UINT8* pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT16 uslength)
{
    SOCKET socket;
    VOS_INT nSndNum;

    if (VOS_FALSE == g_ulSockOMInitState)
    {
        return VOS_ERR;
    }

    (VOS_VOID)VOS_SmP(g_astSockInfo[SOCKET_OM_CFG].SmClose, 0);

    socket = g_astSockInfo[SOCKET_OM_CFG].socket;

    if (SOCK_NULL == socket)
    {
        /*lint -e534*/
        VOS_SmV(g_astSockInfo[SOCKET_OM_CFG].SmClose);
        /*lint +e534*/
        vos_printf("[%s][%d]:socket err !\n",__FUNCTION__,__LINE__);
        return VOS_ERR;
    }

    /* ����send������ͨ��socket���ͳ�ȥ����TCP */
    nSndNum = send(socket, pucVirAddr, uslength, 0);

    /*lint -e534*/
    VOS_SmV(g_astSockInfo[SOCKET_OM_CFG].SmClose);
    /*lint +e534*/

    if (nSndNum != uslength)
    {
        vos_printf("[%s][%d]:send err %d,%d!\n",__FUNCTION__,__LINE__,nSndNum,uslength);
        if(g_ulOmIsReConn == VOS_TRUE)
        {
            vos_printf("[%s][%d]:Re Conn %d,%d!\n",__FUNCTION__,__LINE__,nSndNum,uslength);
			return VOS_ERR;
        }
        PPM_DisconnectAllPort(OM_LOGIC_CHANNEL_CNF);
        
        g_stUdpInfo.bStatus = VOS_FALSE;
        
        (VOS_VOID)VOS_SmP(g_astSockInfo[SOCKET_OM_CFG].SmClose, 0);
        
		closesocket(g_astSockInfo[SOCKET_OM_CFG].socket);
        
		g_astSockInfo[SOCKET_OM_CFG].socket = SOCK_NULL;
        
        /*lint -e534*/
        VOS_SmV(g_astSockInfo[SOCKET_OM_CFG].SmClose);
        /*lint +e534*/
        
        return VOS_ERR;
    }

    g_ulOmIsReConn == VOS_FALSE;

    return VOS_OK;
}
VOS_INT32 PPM_SockATComSend(VOS_UINT8* pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT16 uslength)
{
    SOCKET socket;
    VOS_INT nSndNum;

    if (VOS_FALSE == g_ulSockATInitState)
    {
        return VOS_ERR;
    }

    (VOS_VOID)VOS_SmP(g_astSockInfo[SOCKET_AT].SmClose, 0);

    socket = g_astSockInfo[SOCKET_AT].socket;

    if (SOCK_NULL == socket)
    {
        /*lint -e534*/
        VOS_SmV(g_astSockInfo[SOCKET_AT].SmClose);
        /*lint +e534*/
        vos_printf("[%s][%d]:socket err !\n",__FUNCTION__,__LINE__);
        return VOS_ERR;
    }

    /* ����send������ͨ��socket���ͳ�ȥ����TCP */
    nSndNum = send(socket, pucVirAddr, uslength, MSG_DONTWAIT);

    /*lint -e534*/
    VOS_SmV(g_astSockInfo[SOCKET_AT].SmClose);
    /*lint +e534*/
    if (nSndNum != uslength)
    {
        vos_printf("[%s][%d]:send err %d,%d!\n",__FUNCTION__,__LINE__,nSndNum,uslength);
        if(g_ulAtIsReConn == VOS_TRUE)
        {
            vos_printf("[%s][%d]:Re Conn %d,%d!\n",__FUNCTION__,__LINE__,nSndNum,uslength);
			return VOS_ERR;
        }
        (VOS_VOID)VOS_SmP(g_astSockInfo[SOCKET_AT].SmClose, 0);
		closesocket(g_astSockInfo[SOCKET_AT].socket);
		g_astSockInfo[SOCKET_AT].socket =SOCK_NULL;
        /*lint -e534*/
        VOS_SmV(g_astSockInfo[SOCKET_AT].SmClose);
        /*lint +e534*/
        return VOS_ERR;
    }


    g_ulAtIsReConn == VOS_FALSE;

    return VOS_OK;
}
VOS_UINT32 PPM_SockPortInit(VOS_VOID)
{
#if (VOS_OS_VER != VOS_WIN32)
    if ((BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_WIFI))
        && (VOS_TRUE == PPM_SockIsEnable()))
    {
        /*CPM_PhySendReg(CPM_WIFI_OM_IND_PORT,    (CPM_SEND_FUNC)PPM_SockOMIndComSend);*/
        CPM_PhySendReg(CPM_WIFI_OM_IND_PORT,    (CPM_SEND_FUNC)PPM_SockOMIndComSend);
        CPM_PhySendReg(CPM_WIFI_OM_CFG_PORT,    (CPM_SEND_FUNC)PPM_SockOMCfgComSend);
        CPM_PhySendReg(CPM_WIFI_AT_PORT,        (CPM_SEND_FUNC)PPM_SockATComSend);
    }
#endif

    VOS_SpinLockInit(&g_stSockTaskSpinLock);

    return VOS_OK;
}

#endif


#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif




