/************************************************************************
*                                                                      *
*                             ppp_core.c                               *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/04/04                                      *
*  Author:             Deng Yi Ou                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP���̿���ģ�鼰�ں�����ǵĽӿ�               *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*  PPP���̿���ģ�鼰�ں�����ǵĽӿ�                                   *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"
#include "pppc_ctrl.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_CORE_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

#if 1
ULONG g_ulHsgwA10TestDbgFlg = VOS_FALSE;
ULONG g_ulA11RmiCommendDbgFlg = VOS_TRUE;
S_CFG_DOMAINNODE g_pstApnByIndex[5];
#define USM_HANDLE  1

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

VOID PPP_EAP_ReceiveEventFromCore (PPPINFO_S *pstPppInfo, ULONG ulCmd, CHAR *pPara)
{
    return;
}
#endif

/*****************************************************************************
 �� �� ��  : PPP_GetUserTypeByIpv4cpReq
 ��������  : ����Ipv4������Ϣ�����û����� SIPV4\CMIP
 �������  : UCHAR* pPacket
             ULONG ulLen
             ULONG* pulMsgType
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
/*lint -e550*/
ULONG PPP_GetUserTypeByIpv4cpReq(PPPINFO_S *pstPppInfo, UCHAR* pPacket,ULONG ulLen, ULONG* pulMsgType)
{
    ULONG ulCiLen = 0;
    UCHAR ucResult = 0;
    UCHAR ucCode = 0;
    UCHAR ucId = 0;
    if ((VOS_NULL == pPacket)||(VOS_NULL == pulMsgType))
    {
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG,"\r\n PPP_GetUserTypeByIpv4cpReq input para null");
        return VOS_ERR;
    }

    if (ulLen < FSM_HDRLEN)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_340);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER034);
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG,"\r\n PPP_GetUserTypeByIpv4cpReq ulLen error!");
        return VOS_ERR;
    }

    /*���Ľ���*/
    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(ucId, pPacket);
    PPP_GETSHORT(ulCiLen, pPacket);

    if (ulCiLen > ulLen)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_341);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER034);
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG,"\r\n PPP_GetUserTypeByIpv4cpReq ulCiLen error!");
        return VOS_ERR;
    }

    if (ulCiLen < FSM_HDRLEN)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_342);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER034);
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG,"\r\n PPP_GetUserTypeByIpv4cpReq ulCiLen too short!");
        return VOS_ERR;
    }

    /* ���ĳ��ȼ�ȥFSMͷ�ĳ��� */
    ulCiLen -= FSM_HDRLEN;
    /*�ж�SIP/MIP 1ΪSIP,0ΪMIP*/
    ucResult = (UCHAR)PPP_IPCP_IsSip((UCHAR *)pPacket, &ulCiLen);

    if (VOS_TRUE == ucResult)
    {
        *pulMsgType = E_FSM_ID_SIPV4;
        PPP_DBG_OK_CNT(PPP_PHOK_955);

        /* �˴��ж�ԭʼ�����Ƿ���Ч��������Э�����ͱ仯 */
        PPP_SET_IPTECH(pstPppInfo, PPP_USERTYPE_SIP);
    }
    else
    {
        *pulMsgType = E_FSM_ID_CMIP;

        PPP_DBG_OK_CNT(PPP_PHOK_956);
        /* �˴��ж�ԭʼ�����Ƿ���Ч��������Э�����ͱ仯 */
        PPP_SET_IPTECH(pstPppInfo, PPP_USERTYPE_MIP);
    }
    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_GetUserTypeByIpv4cpReq done !");
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_CopyIpv4cpMsg
 ��������  : �����û������ĵ�һ��Ipv4������Ϣ
 �������  : PPPINFO_S *pstPppInfo
             UCHAR *pHead
             UCHAR *pPacket
             ULONG ulMsgLen
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_CopyIpv4cpMsg(PPPINFO_S *pstPppInfo, UCHAR *pHead, UCHAR *pPacket, ULONG ulMsgLen)
{

    UCHAR *pucCopyMsg = VOS_NULL;

    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_CopyIpv4cpMsg entry");

    if ((VOS_NULL == pstPppInfo)||(VOS_NULL == pHead)||(VOS_NULL == pPacket))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_343);
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG, " \r\n PPP_CopyIpv4cpMsg: invalid paras.");
        return VOS_ERR;
    }

    /* ��ȡIPCP���ƿ� */
    if (NULL == pstPppInfo->pstIpcpInfo)
    {
        PPP_GETIPCPADDR(pstPppInfo->pstIpcpInfo, pstPppInfo->ulRPIndex);
        if (NULL == pstPppInfo->pstIpcpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_344);
            /* Malloc Error */
            PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG, " \r\n PPP_CopyIpv4cpMsg: malloc ipcp CB fail!");
            return VOS_ERR;
        }
        PPP_MemSet(pstPppInfo->pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));
        PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);
    }

    if ( VOS_NULL != ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg )
    {
        (VOID)PPP_Free(((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg);
        ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg = NULL;
    }

    pucCopyMsg = PPP_Malloc(ulMsgLen+PPP_RESERVED_PACKET_HEADER);
    if ( VOS_NULL == pucCopyMsg )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_345);
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG, " \r\n PPP_CopyIpv4cpMsg: malloc pucCopyMsg fail!");
        return VOS_ERR;
    }
    ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg = pucCopyMsg;

    VOS_MemCpy(pucCopyMsg, pHead, PPP_RESERVED_PACKET_HEADER);
    VOS_MemCpy(pucCopyMsg+PPP_RESERVED_PACKET_HEADER, pPacket, ulMsgLen);

    ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->ulIpv4cpLen = ulMsgLen;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,  "\r\n PPP_CopyIpv4cpMsg success !");
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_CopyIpv6cpMsg
 ��������  : �����û������ĵ�һ��Ipv6cp������Ϣ
 �������  : PPPINFO_S *pstPppInfo
             UCHAR *pHead
             UCHAR *pPacket
             ULONG ulMsgLen
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_CopyIpv6cpMsg(PPPINFO_S *pstPppInfo, UCHAR *pHead, UCHAR *pPacket, ULONG ulMsgLen)
{
    UCHAR *pucCopyMsg = VOS_NULL;

    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_CopyIpv6cpMsg entry");

    if ((VOS_NULL == pstPppInfo)||(VOS_NULL == pHead)||(VOS_NULL == pPacket))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_346);
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG, " \r\n PPP_CopyIpv6cpMsg: invalid paras.");
        return VOS_ERR;
    }

    /* ��ȡIPV6CP���ƿ� */
    if (NULL == pstPppInfo->pstIpV6cpInfo)
    {
        PPP_GETIPV6CPADDR(pstPppInfo->pstIpV6cpInfo, pstPppInfo->ulRPIndex);
        if (NULL == pstPppInfo->pstIpV6cpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_347);
            /* Malloc Error */
            PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG, " \r\n PPP_CopyIpv6cpMsg: malloc ipv6cp CB fail!");
            return VOS_ERR;
        }
        PPP_MemSet(pstPppInfo->pstIpV6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));
        PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);
    }

    if ( VOS_NULL != ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg )
    {
        (VOID)PPP_Free(((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg);
        ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg = NULL;
    }

    pucCopyMsg = PPP_Malloc(ulMsgLen+PPP_RESERVED_PACKET_HEADER);
    if ( VOS_NULL == pucCopyMsg )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_348);
        PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG, " \r\n PPP_CopyIpv6cpMsg: malloc pucCopyMsg fail!");
        return VOS_ERR;
    }
    ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg = pucCopyMsg;

    VOS_MemCpy(pucCopyMsg, pHead, PPP_RESERVED_PACKET_HEADER);
    VOS_MemCpy(pucCopyMsg+PPP_RESERVED_PACKET_HEADER, pPacket, ulMsgLen);

    ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->ulIpv6cpLen = ulMsgLen;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,  "\r\n PPP_CopyIpv6cpMsg success !");
    return VOS_OK;
}



ULONG PPP_CopyVsncpReqMsg(PPPINFO_S *pstPppInfo,
                          UCHAR *pHead,
                          UCHAR *pPacket,
                          ULONG ulLen,
                          UCHAR ucCode)
{
    UCHAR *pucCopyMsg = NULL;
    ULONG ulReturn = VOS_OK;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = NULL;

    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,
                 "\r\n PPP_CopyVsncpReqMsg: enter,ucCode=%u", ucCode);

    if (CONFREQ == ucCode)
    {
        ulReturn = (ULONG)SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (UCHAR **)&pstRpContext);
        if (VOS_OK != ulReturn)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_772);
            PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG,
                         "\r\n PPP_CopyVsncpReqMsg: query context fail,RpIndex=%u",
                         pstPppInfo->ulRPIndex);
            return VOS_ERR;
        }

        if (NULL != pstRpContext->pucVsncpReq)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1470);
            PPP_Free(pstRpContext->pucVsncpReq);
            pstRpContext->pucVsncpReq = NULL;
        }

        pucCopyMsg = PPP_Malloc(ulLen + PPP_RESERVED_PACKET_HEADER + sizeof(ULONG));
        if (VOS_NULL == pucCopyMsg)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_773);
            PPP_DebugOut(MID_PPPC,PPP_DEBUG_LOG,
                         "\r\n PPP_CopyVsncpReqMsg: malloc pucVsncpReq fail[%u]!", ulLen);
            return VOS_ERR;
        }
        pstRpContext->pucVsncpReq = pucCopyMsg;
        *((ULONG *)pucCopyMsg) = ulLen;

        VOS_MemCpy((pucCopyMsg + sizeof(ULONG)), pHead, PPP_RESERVED_PACKET_HEADER);
        VOS_MemCpy((pucCopyMsg + sizeof(ULONG) + PPP_RESERVED_PACKET_HEADER), pPacket, ulLen);

        PPP_DBG_OK_CNT(PPP_PHOK_1471);
    }
    return VOS_OK;
}


VOID PPP_Core_IpcpV4FinProc( PPPINFO_S *pstPppInfo )
{
    PPPIPCPINFO_S *pstIpcpInfo = NULL ;

    if ((NULL == pstPppInfo->pstLcpInfo) || (NULL == pstPppInfo->pstIpcpInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_349);
        return;
    }

    pstIpcpInfo = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;

    /*1��ipv6��·��ipv4��·ͬʱDOWN��,֪ͨ�û�������
        2����Э��Ҳ�����÷�֧
        3���ն˷�������Ҳ�����÷�֧*/




    PPP_DBG_OK_CNT(PPP_PHOK_957);

    /*��Ӷ��ڶ�ʱ���ı���*/
    if (pstIpcpInfo->stFsm.ulTimeOutID)
    {
        (VOID)VOS_StopRelTimer(&(pstIpcpInfo->stFsm.ulTimeOutID));
        pstIpcpInfo->stFsm.ulTimeOutID = 0;
    }

    /*ɾ��Э�����ȴ���ʱ��*/
    if (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlgV6)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_958);
        (VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);
    }

    /*ɾ����Э�̿��ƿ�*/
    if (pstPppInfo->bReNego)
    {
        pstPppInfo->bReNego = 0;

        /*ipcp���ƿ�Ϊ�ջ���v4��Э�̱����Ч���ͷſ��ƿ�*/
        if ((pstPppInfo->pstPppRenegoInfo)&&(!pstPppInfo->bReNegoV6))
        {
            (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
            pstPppInfo->pstPppRenegoInfo = 0;
        }
    }

    if (pstPppInfo->bVjFlag)
    {
        PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_VJ);
        PPP_INNER_COUNTER(PPP_INNER_COUTNER_070);
    }

    /*�ͷŻ�����Ϣ�ڴ�*/
    if ( VOS_NULL != ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg )
    {
        (VOID)PPP_Free(((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg);
        ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg = NULL;
        ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->ulIpv4cpLen = 0;
    }

    pstIpcpInfo->ucUsedFlag = 0;
    pstPppInfo->pstIpcpInfo = NULL;
    pstPppInfo->bPppStateFlg = PPP_STATE_FAIL;
    pstPppInfo->ulPeerIPAddr = 0;
    pstPppInfo->ucV4NcpReleaseCode = 0;

    PPP_DBG_OK_CNT(PPP_PHOK_959);


    /* ����ipcp��Э��ʧ�ܺ���Ҫ�ж�ipv6cp��״̬�������open̬��Ҫ�ٴ�����Ϊsuccess�������û����ߺ�����ʧ��ͳ�� */
    if ((pstPppInfo->pstIpV6cpInfo)
        && (((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->stFsm.ucState == PPP_STATE_OPENED))
    {
        M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_SUCCESS);
        PPP_DBG_OK_CNT(PPP_PHOK_960);
    }

    return;
}



VOID PPP_Core_IpcpV6FinProc( PPPINFO_S *pstPppInfo )
{
   PPPIPV6CPINFO_S *pstIpv6cpInfo = NULL ;

   if ((NULL == pstPppInfo->pstLcpInfo) || (NULL == pstPppInfo->pstIpV6cpInfo))
   {
       PPP_DBG_ERR_CNT(PPP_PHERR_350);
       return;
   }

   pstIpv6cpInfo = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;

   /*1��ipv6��·��ipv4��·ͬʱDOWN��,֪ͨ�û�������
     2����Э��Ҳ�����÷�֧
     3���ն˷�������Ҳ�����÷�֧*/



   PPP_DBG_OK_CNT(PPP_PHOK_961);

   /*��Ӷ��ڶ�ʱ���ı���*/
   if (pstIpv6cpInfo->stFsm.ulTimeOutID)
   {
       (VOID)VOS_StopRelTimer(&(pstIpv6cpInfo->stFsm.ulTimeOutID));
       pstIpv6cpInfo->stFsm.ulTimeOutID = 0;
   }


   /*ɾ��Э�����ȴ���ʱ��*/
   if (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlg)
   {
       PPP_DBG_OK_CNT(PPP_PHOK_962);
       (VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);
   }

   /*ɾ����Э�̿��ƿ�*/
   if (pstPppInfo->bReNegoV6)
   {
       pstPppInfo->bReNegoV6 = 0;

       /*ipcp���ƿ�Ϊ�ջ���v4��Э�̱����Ч���ͷſ��ƿ�*/
       if ((pstPppInfo->pstPppRenegoInfo)&&(!pstPppInfo->bReNego))
       {
           (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
           pstPppInfo->pstPppRenegoInfo = 0;
       }
   }

   /* �ͷŻ�����Ϣ�ڴ� */
   if ( VOS_NULL != ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg )
   {
       (VOID)PPP_Free(((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg);
       ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg = NULL;
       ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->ulIpv6cpLen = 0;
   }

   if (0 != pstIpv6cpInfo->ucUsedFlag)
   {
       pstIpv6cpInfo->ucUsedFlag = 0;
       PPP_DBG_OK_CNT(PPP_PHOK_963);
   }

   pstPppInfo->pstIpV6cpInfo = NULL;
   pstPppInfo->bPppStateFlgV6 = PPP_STATE_FAIL;
   pstPppInfo->ucV6NcpReleaseCode = 0;
   VOS_MemSet((void *)pstPppInfo->usPeerIPv6Addr,0,IPV6_ADDR_LEN);

   PPP_DBG_OK_CNT(PPP_PHOK_964);
   return;
}





/*****************************************************************************
 �� �� ��  : PPP_Core_ReceivePacketFromShell
 ��������  : PPP�ں��յ���Ƿ�����Э�̱���
 �������  : PPPINFO_S *pstPppInfo
             UCHAR*     pHead
             UCHAR*     pPacket
             ULONG      ulLen
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_Core_ReceivePacketFromShell_TestStub(PPPINFO_S *pstPppInfo,
                                     UCHAR*     pHead,
                                     UCHAR*     pPacket,
                                     ULONG      ulLen)
{
    PPPLCPINFO_S *pstLcpInfo = NULL;
    ULONG ulOffset;
    USHORT usProtocol;
    UCHAR ucCode = 0;
    ULONG ulRet = VOS_ERR;
    ULONG ulUserType = 0;
    PPP_TRACE("\r\n---Into PPP_Core_ReceivePacketFromShell---\r\n");

    /* ������� */

    /*
     |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  ff   |  03   |    protocol   |  Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |
    pPacket
     */
    if ((VOS_NULL_PTR == pPacket) || (VOS_NULL_PTR == pHead) || (VOS_NULL_PTR == pstPppInfo))
    {
        VOS_DBGASSERT(pstPppInfo);
        VOS_DBGASSERT(pHead);
        VOS_DBGASSERT(pPacket);
        return;
    }

    /* ���Э���,������PPPͷ���� */
    ulOffset = PPP_Core_GetProtocol(pstPppInfo, (UCHAR*)pPacket, (USHORT*) &usProtocol);
    if ((ulOffset == 0) || (ulLen < ulOffset))
    {
        /* ��ʾ:����ı��� */
        PPP_DBG_ERR_CNT(PPP_PHERR_351);
        /* ���������Ϣ added by gxf 20030528 */
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Receive Bad Packet!!");
        return;
    }

    /* �ƶ�ָ�� */
    pPacket += ulOffset;
    ulLen -= ulOffset;
    ucCode = *pPacket;
    /* ������� */

    /*
     |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  ff   |  03   |    protocol   |  Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |---------- ulOffset -----------|
                                    pPacket
     */

    /* ��Ϣ���� */
    PPP_OmMsgTrc(pstPppInfo->ulRPIndex, usProtocol, pPacket, ulLen, PPP_TRACE_IN, 0, &(pstPppInfo->stIMSI), pstPppInfo->bEhrpdUser);


    switch (usProtocol)
    {
        case PPP_LCP:
            PPP_DBG_OK_CNT(PPP_PHOK_965);

            /* ���������Ϣ */
            if (VRP_YES == pstPppInfo->stPppDebugInfo.bDebug_Lcp_Packet)
            {
                PPP_Debug_FsmPacket(pstPppInfo,
                                    pPacket,
                                    ulLen,
                                    usProtocol,
                                    (UCHAR)PPP_DEBUG_PACKET_IN);
            }

            /* ���û�д���LCP���ƿ�,�򴴽�֮ */
            if (NULL == pstPppInfo->pstLcpInfo)
            {
                PPP_GETLCPADDR(pstPppInfo->pstLcpInfo, pstPppInfo->ulRPIndex);
                if (pstPppInfo->pstLcpInfo == NULL)
                {
                    PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Fail:Malloc LCP CB Failed");
                    return;
                }

                VOS_MemSet(pstPppInfo->pstLcpInfo, 0, sizeof(PPPLCPINFO_S));
                PPP_LCP_Init(pstPppInfo);/*luofeng37050notify Э�̲���*/
            }

            pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;

            /* ISLUP�¼�ֻ��LCP״̬ΪInitial��Startingʱ����Ч */
            if ((pstLcpInfo->stFsm.ucState == (UCHAR)PPP_STATE_INITIAL)
                || (pstLcpInfo->stFsm.ucState == (UCHAR)PPP_STATE_STARTING))
            {
                PPP_Core_EstablishPhase(pstPppInfo);
            }

            if (pstPppInfo->pstLcpInfo)
            {
                PPP_LCP_ReceivePacket(pstPppInfo->pstLcpInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_966);
                return;
            }

            break;

        case PPP_IPCP:
            PPP_DBG_OK_CNT(PPP_PHOK_967);

            /* ���������Ϣ */
            if (pstPppInfo->stPppDebugInfo.bDebug_Ipcp_Packet == VRP_YES)
            {
                PPP_Debug_FsmPacket(pstPppInfo,
                                    pPacket,
                                    ulLen,
                                    usProtocol,
                                    (UCHAR)PPP_DEBUG_PACKET_IN);
            }

            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_352);
                break;
            }

            /* �ж��Ƿ�Ϊ����Э�̽׶�*/
            if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
            {
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_353);
                return;
            }

            /* ��IPδ��ȡ��IP��ַʱ�յ��ĵ�һ��������Ϣ */
            if (CONFREQ == ucCode)
            {
                if ((NULL == pstPppInfo->pstIpcpInfo)
                    && (0 == pstPppInfo->ulPeerIPAddr && PPP_USERTYPE_MIP != pstPppInfo->bIPTech))
                {
                    /*�����û�����*/
                    if(VOS_OK != PPP_GetUserTypeByIpv4cpReq(pstPppInfo, pPacket, ulLen, &ulUserType))
                    {
                        PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_GetUserTypeByIpv4cpReq fail!");

                        PPP_DBG_ERR_CNT(PPP_PHERR_354);
                        /*�ظ�Reject��Ϣ*/
                        break;
                    }

                    /* PMIPv6 PDN��Ҫ�ӻ�����Ϣ�л�ȡIP��ַ���ȴ���IPV4���ƿ顢������Ϣ */
                    if(VOS_OK != PPP_CopyIpv4cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_CopyIpv4cpMsg fail !");
                         PPP_ClearCB_IPCP(pstPppInfo->pstIpcpInfo);
                         pstPppInfo->pstIpcpInfo = NULL;
                         PPP_DBG_ERR_CNT(PPP_PHERR_355);
                         break;
                    }

#if 0
                    /* ֪ͨPDN(Я���û����ͣ�ջ����,RpIndex) */
                    if(VOS_OK != PDN_PppStartSubNet(pstPppInfo->ulRPIndex, ulUserType))
                    {
                         PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n Call PDN_PppStartSubNet fail !");
                         /*����Դ������*/
                         PPP_ClearCB_IPCP(pstPppInfo->pstIpcpInfo);
                         pstPppInfo->pstIpcpInfo = NULL;
                         PPP_DBG_ERR_CNT(PPP_PHERR_356);
                         /* �ظ�Reject��Ϣ */
                         break;
                    }
#endif
                    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV4;

                    return;
                }

                /*��IPV4���ƿ鲢�� IPCP���ƿ�״̬��״̬*/
                if(pstPppInfo->pstIpcpInfo && (PPP_STATE_INITIAL== ((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->stFsm.ucState))
                {
                    /*���»�����Ϣ*/
                    if(VOS_OK != PPP_CopyIpv4cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_357);
                         PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_CopyIpv4cpMsg fail !");
                         break;
                    }
                    PPP_DBG_OK_CNT(PPP_PHOK_968);
                    return;
                }
            }

            /*�����������Э������*/
            PPP_IPCP_ReceivePacket(pstPppInfo->pstIpcpInfo, pHead, pPacket, ulLen);
            PPP_DBG_OK_CNT(PPP_PHOK_969);
            return ;

        case PPP_IPV6CP:
            PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n usPhase = %d, pstIpV6cpInfo = 0x%x, usPeerIPv6Addr = %0.4x%0.4x%0.4x%0.4x!",
                        pstPppInfo->usPhase, pstPppInfo->pstIpV6cpInfo,
                        pstPppInfo->usPeerIPv6Addr[0], pstPppInfo->usPeerIPv6Addr[1],
                        pstPppInfo->usPeerIPv6Addr[2], pstPppInfo->usPeerIPv6Addr[3]);

            /* ehrpd�û�ֱ��break���������protocol rej��Ϣ */
            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_358);
                break;
            }

            /* �жϽ׶�״̬�Ƿ���ȷ */
            if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
            {
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_359);
                return;
            }

            if (CONFREQ == ucCode)
            {
                if ((NULL == pstPppInfo->pstIpV6cpInfo)
                    && (VOS_OK != PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr)))
                {
#if 0
                    /* ֪ͨPDN(Я���û����ͣ�ջ����,RpIndex) */
                    if(VOS_OK != PDN_PppStartSubNet(pstPppInfo->ulRPIndex, E_FSM_ID_SIPV6))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_360);
                         /*����Դ������*/
                         /* �ظ�Reject��Ϣ */
                         break;
                    }
#endif
                    PPP_SET_IPTECH(pstPppInfo, PPP_USERTYPE_SIP);

                    /*����IPV6���ƿ顢������Ϣ */
                    if (VOS_OK != PPP_CopyIpv6cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_361);
                         PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_CopyIpv6cpMsg fail !");
                         PPP_ClearCB_IPV6CP(pstPppInfo->pstIpV6cpInfo);
                         pstPppInfo->pstIpV6cpInfo = NULL;
                         /* �ظ�Reject��Ϣ */
                         break;
                    }
                    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV6;
                    return;
                }

                if (pstPppInfo->pstIpV6cpInfo && (PPP_STATE_INITIAL== ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->stFsm.ucState))
                {
                   /*���»�����Ϣ*/
                    if(VOS_OK != PPP_CopyIpv6cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_362);
                         PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_CopyIpv6cpMsg fail !");

                         /* �ظ�Reject��Ϣ */
                         break;
                    }
                    PPP_DBG_OK_CNT(PPP_PHOK_970);
                    return;
                }
            }

            /*�����������Э������*/
            PPP_IPV6CP_Pactket_Proc(pstPppInfo, pHead, pPacket, ulLen);
            return;
     case PPP_VSNCP:
#if 0
            ulRet = USM_GetVsncpNegoFlag(pstPppInfo->ulRPIndex);
            if (ulRet != VOS_OK)
            {
                PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,
                             "\r\n PPP_Core_ReceivePacketFromShell  ulRet = %u",
                             ulRet);
                PPP_DBG_ERR_CNT(PPP_PHERR_363);
                return;
            }
#endif
            PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,
                         "\r\n PPP_Core_ReceivePacketFromShell usPhase = %d!",
                         pstPppInfo->usPhase);

            if (pstPppInfo->bEhrpdUser != VOS_TRUE)
            {
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_364);
                break;
            }

            /*�����������Э������*/
            PPP_VSNCP_PactketProc(pstPppInfo, pHead, pPacket, ulLen, ucCode);
            return;
 #if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
        case PPP_CCP:

            /* ���������Ϣ */
            if (pstPppInfo->stPppDebugInfo.bDebug_Ccp_Packet == VRP_YES)
            {
                PPP_Debug_FsmPacket(pstPppInfo,
                                    pPacket,
                                    ulLen,
                                    usProtocol,
                                    (UCHAR)PPP_DEBUG_PACKET_IN);
            }
            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_365);
                break;
            }

            /* �������ΪЭ��δ��Network�׶�pstCcpInfo��Ϊ0��
                 ���������ģ�������protocol reject��
                 �μ�RFC1661��
             */
            if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_366);
                return;
            }

            if (pstPppInfo->pstCcpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_971);
                PPP_CCP_ReceivePacket(pstPppInfo->pstCcpInfo, pHead, pPacket, ulLen, pstPppInfo->ulRPIndex);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */
                return;
            }

            /*lint -e746*/
            if(VOS_OK == PPP_CheckCcpLimit())
            /*lint +e746*/
            {
                PPP_DBG_OK_CNT(PPP_PHOK_972);
                PPP_GETCCPADDR(pstPppInfo->pstCcpInfo, pstPppInfo->ulRPIndex);
                if (pstPppInfo->pstCcpInfo)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_973);
                    PPP_MemSet(pstPppInfo->pstCcpInfo, 0, sizeof(PPP_CCP_INFO_S));

                    /* ��ʼ��CCP���ƿ� */
                    PPP_CCP_init(pstPppInfo);

                    /*����CCP��ʱ��ʱ��*/
                    (VOS_VOID)VOS_StartRelTimer((HTIMER)&(((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulCcpTimeoutID),
                                                MID_PPPC,
                                                ((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulTimeOutTime,
                                                pstPppInfo->ulRPIndex,
                                                PPPC_CCP_TIMEOUT_TIMER,
                                                VOS_TIMER_LOOP,
                                                VOS_TIMER_PRECISION_0);

                    /* ��CCP������Ϣ,����CCP��ʼЭ�� */
                    PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL );
                    PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (ULONG)PPP_EVENT_FSM_UP, NULL );
                    PPP_CCP_ReceivePacket(pstPppInfo->pstCcpInfo, pHead, pPacket, ulLen, pstPppInfo->ulRPIndex);
                    return;
                }
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_367);
                /*д��־*/
                PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_WARNING,
                                    " PPP_Core_ReceivePacketFromShell:  g_ucPppCcpSwitch=0 or no license , please confirm it");

                PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulLen, usProtocol, ucCode);
                return;
            }

            /* ��������ִ��PPP_Core_ReceiveUnknownProtocol */

            break;
 #endif
        case PPP_EAP:
#if 0
            if (pstPppInfo->bEhrpdUser != VOS_TRUE)
            {
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_368);
                break;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_974);
            if (pstPppInfo->pstEapInfo)
            {
                PPP_EAP_ReceivePacket(pstPppInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_975);
                return;
            }

            /* �������ΪЭ��δ��Authenticate�׶�pstChapInfo��Ϊ0��
             ���������ģ�������protocol reject��
             �μ�RFC1661��
            */
            if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_AUTHENTICATE)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_369);
                return;
            }
#endif
            break;

        case PPP_PAP:

            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_370);
                break;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_976);
            if (pstPppInfo->pstPapInfo)
            {
                PPP_PAP_ReceivePacket(pstPppInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_977);
                return;
            }

            /* �������ΪЭ��δ��Authenticate�׶�pstPapInfo��Ϊ0��
               ���������ģ�������protocol reject��
               �μ�RFC1661��
             */
            if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_AUTHENTICATE)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_371);
                return;
            }

            /* ��������ִ��PPP_Core_ReceiveUnknownProtocol */

            break;

        case PPP_CHAP:
            PPP_DBG_OK_CNT(PPP_PHOK_978);

            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_372);
                break;
            }

            if (pstPppInfo->pstChapInfo)
            {
                PPP_CHAP_ReceivePacket(pstPppInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_979);
                return;
            }

            /* �������ΪЭ��δ��Authenticate�׶�pstChapInfo��Ϊ0��
               ���������ģ�������protocol reject��
               �μ�RFC1661��
             */
            if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_AUTHENTICATE)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_373);
                return;
            }

            /* ��������ִ��PPP_Core_ReceiveUnknownProtocol */

            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_374);
            break;
    }

    PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulLen, usProtocol, ucCode);

    return;
}
VOID PPP_TEST_TIMESTAMP(ULONG ulStart, ULONG ulEnd, ULONG ulRpIndex)
{
    ULONG ulRet = VOS_OK;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL;

    ulRet = SDB_GetRpContextByIndex(ulRpIndex, &pstRpContext);
    if ((VOS_OK != ulRet) || (VOS_NULL == pstRpContext))
    {
        return;
    }

    ulRet = SDB_GetPdnContextByIndex((ULONG)pstRpContext->ausPdnIndexArray[0], (UCHAR**)&pstPdnContext);
    if ((VOS_OK != ulRet) || (VOS_NULL == pstPdnContext))
    {
        return;
    }

    if (E_PDNTYPE_PMIPV6 == pstPdnContext->ucPdnType)
    {
        if ((ulEnd -  ulStart) > g_ulPppDBGStatisc[PPP_PHOK_1458])
        {
            g_ulPppDBGStatisc[PPP_PHOK_1458] = (ulEnd -  ulStart);
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : PPP_Core_ReceivePacketFromShell
 ��������  : PPP�ں��յ���Ƿ�����Э�̱���
 �������  : PPPINFO_S *pstPppInfo
             UCHAR*     pHead
             UCHAR*     pPacket
             ULONG      ulLen
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_Core_ReceivePacketFromShell(PPPINFO_S *pstPppInfo,
                                     UCHAR*     pHead,
                                     UCHAR*     pPacket,
                                     ULONG      ulLen)
{
    ULONG ulOffset;
    USHORT usProtocol;
    UCHAR ucCode = 0;
    ULONG ulUserType = 0;
    ULONG ulTimeStamp = 0;
    ULONG ulTimeStamp1 = 0;
    ULONG ulRet = 0;
    PPP_TRACE("\r\n---Into PPP_Core_ReceivePacketFromShell---\r\n");

    if ( VOS_TRUE == g_ulHsgwA10TestDbgFlg )
    {
         PPP_Core_ReceivePacketFromShell_TestStub(pstPppInfo, pHead, pPacket, ulLen);
         return;
    }

    /* ������� */

    /*
     |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  ff   |  03   |    protocol   |  Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |
    pPacket
     */
    if ((VOS_NULL_PTR == pPacket) || (VOS_NULL_PTR == pHead) || (VOS_NULL_PTR == pstPppInfo))
    {
        VOS_DBGASSERT(pstPppInfo);
        VOS_DBGASSERT(pHead);
        VOS_DBGASSERT(pPacket);
        return;
    }

    /* ���Э���,������PPPͷ���� */
    ulOffset = PPP_Core_GetProtocol(pstPppInfo, (UCHAR*)pPacket, (USHORT*) &usProtocol);
    if ((ulOffset == 0) || (ulLen < ulOffset))
    {
        /* ��ʾ:����ı��� */
        PPP_DBG_ERR_CNT(PPP_PHERR_375);
        /* ���������Ϣ added by gxf 20030528 */
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Receive Bad Packet!!");
        return;
    }

    /* �ƶ�ָ�� */
    pPacket += ulOffset;
    ulLen -= ulOffset;
    ucCode = *pPacket;
    /* ������� */

    /*
     |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  ff   |  03   |    protocol   |  Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |---------- ulOffset -----------|
                                    pPacket
     */

    /* ��Ϣ���� */
    PPP_OmMsgTrc(pstPppInfo->ulRPIndex, usProtocol, pPacket, ulLen, PPP_TRACE_IN, 0, &(pstPppInfo->stIMSI), pstPppInfo->bEhrpdUser);


    switch (usProtocol)
    {
        case PPP_LCP:
            PPP_DBG_OK_CNT(PPP_PHOK_980);

            PPPC_INFO_LOG("\r\n Recieve PPP_LCP packet \r\n");/*add by chenmin00265046*/

            /* ���������Ϣ */
            if (VRP_YES == pstPppInfo->stPppDebugInfo.bDebug_Lcp_Packet)
            {
                PPP_Debug_FsmPacket(pstPppInfo,
                                    pPacket,
                                    ulLen,
                                    usProtocol,
                                    (UCHAR)PPP_DEBUG_PACKET_IN);
            }

            if (ulLen > PPP_LCP_NEGO_PACKET_MAX_LEN)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_376);
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG, "\r\n LCP packet len is over 200[%u]!", ulLen);
                return;
            }

            if (pstPppInfo->pstLcpInfo)
            {
                PPP_LCP_ReceivePacket(pstPppInfo->pstLcpInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_981);
                return;
            }

            break;

        case PPP_IPCP:
            PPP_DBG_OK_CNT(PPP_PHOK_982);

            /* ���������Ϣ */
            if (pstPppInfo->stPppDebugInfo.bDebug_Ipcp_Packet == VRP_YES)
            {
                PPP_Debug_FsmPacket(pstPppInfo,
                                    pPacket,
                                    ulLen,
                                    usProtocol,
                                    (UCHAR)PPP_DEBUG_PACKET_IN);
            }

            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* ���debug��Ϣ */
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_0);
                PPP_DBG_ERR_CNT(PPP_PHERR_377);
                break;
            }

            /* �ж��Ƿ�Ϊ����Э�̽׶�*/
            if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
            {
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_378);
                return;
            }

            /* ��IPδ��ȡ��IP��ַʱ�յ��ĵ�һ��������Ϣ */
            if (CONFREQ == ucCode)
            {
                if ((NULL == pstPppInfo->pstIpcpInfo)
                    && (0 == pstPppInfo->ulPeerIPAddr && PPP_USERTYPE_MIP != pstPppInfo->bIPTech))
                {
                    /*�����û�����*/
                    if(VOS_OK != PPP_GetUserTypeByIpv4cpReq(pstPppInfo, pPacket, ulLen, &ulUserType))
                    {
                        PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_GetUserTypeByIpv4cpReq fail!");

                        PPP_DBG_ERR_CNT(PPP_PHERR_379);
                        /*�ظ�Reject��Ϣ*/
                        break;
                    }

                    /* PMIPv6 PDN��Ҫ�ӻ�����Ϣ�л�ȡIP��ַ���ȴ���IPV4���ƿ顢������Ϣ */
                    if(VOS_OK != PPP_CopyIpv4cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_CopyIpv4cpMsg fail !");
                         PPP_ClearCB_IPCP(pstPppInfo->pstIpcpInfo);
                         pstPppInfo->pstIpcpInfo = NULL;
                         PPP_DBG_ERR_CNT(PPP_PHERR_380);
                         break;
                    }
                    if (VOS_TRUE == g_ulPppVsncpGetPCO)
                    {
                        ulTimeStamp = (ULONG)VOS_GetTick();
                    }
#if 0
                    /* ֪ͨPDN(Я���û����ͣ�ջ����,RpIndex) */
                    if(VOS_OK != PDN_PppStartSubNet(pstPppInfo->ulRPIndex, ulUserType))
                    {
                         PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n Call PDN_PppStartSubNet fail !");
                         /*����Դ������*/
                         PPP_ClearCB_IPCP(pstPppInfo->pstIpcpInfo);
                         pstPppInfo->pstIpcpInfo = NULL;
                         PPP_DBG_ERR_CNT(PPP_PHERR_381);
                         /* �ظ�Reject��Ϣ */
                         break;
                    }
#endif
                    if (VOS_TRUE == g_ulPppVsncpGetPCO)
                    {
                        ulTimeStamp1 = (ULONG)VOS_GetTick();
                        PPP_TEST_TIMESTAMP(ulTimeStamp, ulTimeStamp1, pstPppInfo->ulRPIndex);
                    }

                    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV4;

                    return;
                }

                /*��IPV4���ƿ鲢�� IPCP���ƿ�״̬��״̬*/
                if(pstPppInfo->pstIpcpInfo && (PPP_STATE_INITIAL== ((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->stFsm.ucState))
                {
                    /*���»�����Ϣ*/
                    if(VOS_OK != PPP_CopyIpv4cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_382);
                         PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_CopyIpv4cpMsg fail !");
                         break;
                    }
                    PPP_DBG_OK_CNT(PPP_PHOK_983);
                    return;
                }
            }

            /*�����������Э������*/
            PPP_IPCP_ReceivePacket(pstPppInfo->pstIpcpInfo, pHead, pPacket, ulLen);
            PPP_DBG_OK_CNT(PPP_PHOK_984);
            return ;

        case PPP_IPV6CP:
            PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n usPhase = %d, pstIpV6cpInfo = 0x%x, usPeerIPv6Addr = %0.4x%0.4x%0.4x%0.4x!",
                        pstPppInfo->usPhase, pstPppInfo->pstIpV6cpInfo,
                        pstPppInfo->usPeerIPv6Addr[0], pstPppInfo->usPeerIPv6Addr[1],
                        pstPppInfo->usPeerIPv6Addr[2], pstPppInfo->usPeerIPv6Addr[3]);

            /* ehrpd�û�ֱ��break���������protocol rej��Ϣ */
            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* ���debug��Ϣ */
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_1);
                PPP_DBG_ERR_CNT(PPP_PHERR_383);
                break;
            }

            /* �жϽ׶�״̬�Ƿ���ȷ */
            if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
            {
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_384);
                return;
            }

            if (CONFREQ == ucCode)
            {
                if ((NULL == pstPppInfo->pstIpV6cpInfo)
                    && (VOS_OK != PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr)))
                {
#if 0
                    /* ֪ͨPDN(Я���û����ͣ�ջ����,RpIndex) */
                    if(VOS_OK != PDN_PppStartSubNet(pstPppInfo->ulRPIndex, E_FSM_ID_SIPV6))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_385);
                         /*����Դ������*/
                         /* �ظ�Reject��Ϣ */
                         break;
                    }
#endif
                    PPP_SET_IPTECH(pstPppInfo, PPP_USERTYPE_SIP);

                    /*����IPV6���ƿ顢������Ϣ */
                    if (VOS_OK != PPP_CopyIpv6cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_386);
                         PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_CopyIpv6cpMsg fail !");
                         PPP_ClearCB_IPV6CP(pstPppInfo->pstIpV6cpInfo);
                         pstPppInfo->pstIpV6cpInfo = NULL;
                         /* �ظ�Reject��Ϣ */
                         break;
                    }
                    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV6;
                    return;
                }

                if (pstPppInfo->pstIpV6cpInfo && (PPP_STATE_INITIAL== ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->stFsm.ucState))
                {
                   /*���»�����Ϣ*/
                    if(VOS_OK != PPP_CopyIpv6cpMsg(pstPppInfo, pHead, pPacket, ulLen))
                    {
                         PPP_DBG_ERR_CNT(PPP_PHERR_387);
                         PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_CopyIpv6cpMsg fail !");

                         /* �ظ�Reject��Ϣ */
                         break;
                    }
                    PPP_DBG_OK_CNT(PPP_PHOK_985);
                    return;
                }
            }

            /*�����������Э������*/
            PPP_IPV6CP_Pactket_Proc(pstPppInfo, pHead, pPacket, ulLen);
            return;
     case PPP_VSNCP:

            PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,
                         "\r\n PPP_Core_ReceivePacketFromShell usPhase = %d!",
                         pstPppInfo->usPhase);


            if (pstPppInfo->bEhrpdUser != VOS_TRUE)
            {
                break;
            }
#if 0
            ulRet = USM_GetVsncpNegoFlag(pstPppInfo->ulRPIndex);
            if (ulRet != EHRPD_VSNCP_PRO_OK)
            {
                if (EHRPD_VSNCP_PRO_COPY == ulRet)
                {
                    (VOID)PPP_CopyVsncpReqMsg(pstPppInfo, pHead, pPacket, ulLen, ucCode);
                }
                PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,
                             "\r\n PPP_Core_ReceivePacketFromShell ulRet = %u",
                             ulRet);
                PPP_DBG_ERR_CNT(PPP_PHERR_388);
                return;
            }
#endif
            /*�����������Э������*/
            PPP_VSNCP_PactketProc(pstPppInfo, pHead, pPacket, ulLen, ucCode);
            return;
 #if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
        case PPP_CCP:

            /* ���������Ϣ */
            if (pstPppInfo->stPppDebugInfo.bDebug_Ccp_Packet == VRP_YES)
            {
                PPP_Debug_FsmPacket(pstPppInfo,
                                    pPacket,
                                    ulLen,
                                    usProtocol,
                                    (UCHAR)PPP_DEBUG_PACKET_IN);
            }
            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                /* ���debug��Ϣ */
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_3);
                PPP_DBG_ERR_CNT(PPP_PHERR_390);
                break;
            }

            /* �������ΪЭ��δ��Network�׶�pstCcpInfo��Ϊ0��
                 ���������ģ�������protocol reject��
                 �μ�RFC1661��
             */
            if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_391);
                return;
            }

            if (pstPppInfo->pstCcpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_986);
                PPP_CCP_ReceivePacket(pstPppInfo->pstCcpInfo, pHead, pPacket, ulLen, pstPppInfo->ulRPIndex);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */
                return;
            }

            /*lint -e746*/
            if(VOS_OK == PPP_CheckCcpLimit())
            /*lint +e746*/
            {
                PPP_DBG_OK_CNT(PPP_PHOK_987);
                PPP_GETCCPADDR(pstPppInfo->pstCcpInfo, pstPppInfo->ulRPIndex);
                if (pstPppInfo->pstCcpInfo)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_988);
                    PPP_MemSet(pstPppInfo->pstCcpInfo, 0, sizeof(PPP_CCP_INFO_S));

                    /* ��ʼ��CCP���ƿ� */
                    PPP_CCP_init(pstPppInfo);

                    /*����CCP��ʱ��ʱ��*/
                    (VOS_VOID)VOS_StartRelTimer((HTIMER)&(((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulCcpTimeoutID),
                                                MID_PPPC,
                                                ((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulTimeOutTime,
                                                pstPppInfo->ulRPIndex,
                                                PPPC_CCP_TIMEOUT_TIMER,
                                                VOS_TIMER_LOOP,
                                                VOS_TIMER_PRECISION_0);

                    /* ��CCP������Ϣ,����CCP��ʼЭ�� */
                    PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL );
                    PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (ULONG)PPP_EVENT_FSM_UP, NULL );
                    PPP_CCP_ReceivePacket(pstPppInfo->pstCcpInfo, pHead, pPacket, ulLen, pstPppInfo->ulRPIndex);
                    return;
                }
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_392);
                /*д��־*/
                PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_WARNING,
                                    " PPP_Core_ReceivePacketFromShell:  g_ucPppCcpSwitch=0 or no license , please confirm it");

                PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulLen, usProtocol, ucCode);
                return;
            }

            /* ��������ִ��PPP_Core_ReceiveUnknownProtocol */

            break;
 #endif
        case PPP_EAP:
#if 0
            if (pstPppInfo->bEhrpdUser != VOS_TRUE)
            {
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_5);
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_393);
                break;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_989);
            if (pstPppInfo->pstEapInfo)
            {
                PPP_EAP_ReceivePacket(pstPppInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_990);
                return;
            }

            /* �������ΪЭ��δ��Authenticate�׶�pstChapInfo��Ϊ0��
             ���������ģ�������protocol reject��
             �μ�RFC1661��
            */
            if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_AUTHENTICATE)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_394);
                return;
            }
#endif
            break;

        case PPP_PAP:

            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_6);
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_395);
                break;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_991);
            if (pstPppInfo->pstPapInfo)
            {
                PPP_PAP_ReceivePacket(pstPppInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_992);
                return;
            }

            /* �������ΪЭ��δ��Authenticate�׶�pstPapInfo��Ϊ0��
               ���������ģ�������protocol reject��
               �μ�RFC1661��
             */
            if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_AUTHENTICATE)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_396);
                return;
            }

            /* ��������ִ��PPP_Core_ReceiveUnknownProtocol */

            break;

        case PPP_CHAP:
            PPP_DBG_OK_CNT(PPP_PHOK_993);

            if (VOS_TRUE == pstPppInfo->bEhrpdUser)
            {
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_7);
                /* ���debug��Ϣ */
                PPP_DBG_ERR_CNT(PPP_PHERR_397);
                break;
            }

            if (pstPppInfo->pstChapInfo)
            {
                PPP_CHAP_ReceivePacket(pstPppInfo, pHead, pPacket, ulLen);
                PPP_DBG_OK_CNT(PPP_PHOK_994);
                return;
            }

            /* �������ΪЭ��δ��Authenticate�׶�pstChapInfo��Ϊ0��
               ���������ģ�������protocol reject��
               �μ�RFC1661��
             */
            if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_AUTHENTICATE)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_398);
                return;
            }

            /* ��������ִ��PPP_Core_ReceiveUnknownProtocol */

            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_399);
            break;
    }

    PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulLen, usProtocol, ucCode);

    return;
}





/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ������ǽ����¼��Ľӿں���                                   *
* MODIFY DATE  ��modified by gxf for GGSN80 20030219                        *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                ulCmd:������,����Ϊ����ֵ:                                 *
*                      PPPISLDOWN:�ײ�DOWN                                  *
*                      PPPISLUP:�ײ�UP                                      *
*                      PPPISLRENEGO:�ײ㷢����Э��                          *
*                      PPPCHGIPADDR:IP��ַ�ı�                              *
*                      PPPCHGIPXADDR:IPX��ַ�ı�                            *
*                       PPPL2TPDOWN: L2TP DOWN              zfz 00/07/05        *
*                pPara:�¼��Ĳ���,һ�������ΪNULL                          *
*                      L2TP��LNS�˱�ISLUPʱ: ԤЭ�̽��                     *
*                      PPPCHGIPADDRʱ: �µ�IP��ַ                           *
*                      PPPCHGIPXADDRʱ: �µ�IPX��ַ                         *
* OUTPUT       ��                                                           *
* RETURN       ��NULL                                                       *
* CALLED BY    ��PPP_Shell_ISLIoCtl / PPP_Shell_NiIoCtl                     *
****************************************************************************/
VOID PPP_Core_ReceiveEventFromShell_TestStub(PPPINFO_S *pstPppInfo,
                                    ULONG      ulCmd,
                                    CHAR *     pPara)
{
    PPP_TRACE("\r\n---Into PPP_Core_ReceiveEventFromShell   ulCmd: %d---\r\n", ulCmd);
    if (!pstPppInfo || (ulCmd >= PPPSTCEND))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_400);
        VOS_DBGASSERT(0);
        return;
    }

    switch (ulCmd)
    {
        case PPPISLUP:
        {
             pstPppInfo->bLowerIsUp = 1;

            /* ���û�д���LCP���ƿ�,�򴴽�֮ */
            if (NULL == pstPppInfo->pstLcpInfo)
            {
                PPP_GETLCPADDR(pstPppInfo->pstLcpInfo, pstPppInfo->ulRPIndex);
                if (pstPppInfo->pstLcpInfo == NULL)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_401);
                    PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Fail:Malloc LCP CB Failed");
                    return;
                }

                PPP_MemSet((void *)pstPppInfo->pstLcpInfo, 0, sizeof(PPPLCPINFO_S));
                PPP_LCP_Init(pstPppInfo);/*luofeng37050notify Э�̲���*/
            }

            break;
        }
        case PPPISLDOWN:
        {
            pstPppInfo->bLowerIsUp  = 0;
            pstPppInfo->bLoopBacked = 0;

            /* L2TP��Ҫ�Ĳ��� */
            if (NULL != pstPppInfo->pL2tpPara)
            {
                (VOID)PPP_Free(pstPppInfo->pL2tpPara);
                pstPppInfo->pL2tpPara = NULL;
            }

            /* ֪ͨ LCP Down  */
            if (pstPppInfo->pstLcpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_995);
                /* ��LCP����������Ϣ:LowerDown��Close */
                PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (ULONG)PPP_EVENT_FSM_DOWN, NULL);
                PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (ULONG)PPP_EVENT_FSM_CLOSE, NULL);

                /* ������Ϣ��Ӧ״̬���¼���״̬ת��ͼ:
                 | State
                 |    0         1         2         3         4         5           6         7         8           9
                Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
                ------+------------------------------------------------------------------------------------------------------
                 Down |    -         -         0       tls/1       0         1          1         1         1         tld/1
                 Close|    0       tlf/0       2         2         4         4      irc,str/4 irc,str/4 irc,str/4 tld,irc,str/4
                 */

                /* 1,����LowerDown�¼�,��ͬ״̬�¶�������:
                   Opened״̬:���ϲ�Э�鷢��LowerDown�¼�(tld),״̬תΪStarting
                   Closed/Closing״̬:״̬תΪInitial
                   ����:״̬תΪStarting

                   2,����Close�¼�,��ʼ״ֻ̬����ΪInitial��Starting.��ͬ״̬�¶�������:
                   Starting״̬:״̬תΪInitial;���²㷢��Finished�¼�(tlf).
                   Initial״̬:�ޱ仯

                   ���,�������¼����ͺ�������½��:
                   1,����״̬��Ȼ��ת��Initial
                   2,ֻҪ��ʼ״̬����Closed/Closing,���Ȼ����tlf��������
                 */
            }

            if (pstPppInfo->pstPapInfo)
            {
                PPP_PAP_ReceiveEventFromCore(pstPppInfo, PAP_EVENT_LOWERDOWN, NULL);
            }
            if (pstPppInfo->pstChapInfo)
            {
                PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_LOWERDOWN, NULL);
            }

            break;

        }
        case PPPISLRENEGO:/* ��Э�� */
        {
            if ((pstPppInfo->pstIpcpInfo)||(pstPppInfo->pstIpV6cpInfo))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_996);
                /* renego��, LCP down, ����PPP_Core_NotifyNcpDown, IPCP�յ�down��close�¼�
                   ����finished״̬, �ֵ���PPP_LCP_NegotiationDown, LCP����initial״̬, ����
                   ����open��up�¼������ٴ���Э�� */

                /*if (((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->stFsm.ucState == PPP_STATE_OPENED)*/
                {
                    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (ULONG)PPP_EVENT_FSM_DOWN, NULL);
                    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL);
                    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (ULONG)PPP_EVENT_FSM_UP, NULL);

                    /* ��̬���ӱ����ʧ�� */
                    pstPppInfo->bPppStateFlg   = PPP_STATE_FAIL;
                    pstPppInfo->bPppStateFlgV6 = PPP_STATE_FAIL;
                }
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_402);
                PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR,
                                    "PPP_Core_ReceiveEventFromShell: Receive invalid PPP RENEGO event!");
            }

            break;
        }
        default:
            break;
    }

    return;
}


/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ������ǽ����¼��Ľӿں���                                   *
* MODIFY DATE  ��modified by gxf for GGSN80 20030219                        *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                ulCmd:������,����Ϊ����ֵ:                                 *
*                      PPPISLDOWN:�ײ�DOWN                                  *
*                      PPPISLUP:�ײ�UP                                      *
*                      PPPISLRENEGO:�ײ㷢����Э��                          *
*                      PPPCHGIPADDR:IP��ַ�ı�                              *
*                      PPPCHGIPXADDR:IPX��ַ�ı�                            *
*                       PPPL2TPDOWN: L2TP DOWN              zfz 00/07/05        *
*                pPara:�¼��Ĳ���,һ�������ΪNULL                          *
*                      L2TP��LNS�˱�ISLUPʱ: ԤЭ�̽��                     *
*                      PPPCHGIPADDRʱ: �µ�IP��ַ                           *
*                      PPPCHGIPXADDRʱ: �µ�IPX��ַ                         *
* OUTPUT       ��                                                           *
* RETURN       ��NULL                                                       *
* CALLED BY    ��PPP_Shell_ISLIoCtl / PPP_Shell_NiIoCtl                     *
****************************************************************************/
VOID PPP_Core_ReceiveEventFromShell(PPPINFO_S *pstPppInfo,
                                    ULONG      ulCmd,
                                    CHAR *     pPara)
{
    PPPLCPINFO_S *pstLcpInfo = NULL;

    if ( VOS_TRUE == g_ulHsgwA10TestDbgFlg )
    {
          PPP_Core_ReceiveEventFromShell_TestStub(pstPppInfo, ulCmd, pPara);
          return;
    }

    PPP_TRACE("\r\n---Into PPP_Core_ReceiveEventFromShell   ulCmd: %d---\r\n", ulCmd);
    if (!pstPppInfo || (ulCmd >= PPPSTCEND))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_403);
        VOS_DBGASSERT(0);
        return;
    }

    switch (ulCmd)
    {
        case PPPISLUP:
        {
             pstPppInfo->bLowerIsUp = 1;

            /* ���û�д���LCP���ƿ�,�򴴽�֮ */
            if (NULL == pstPppInfo->pstLcpInfo)
            {
                PPP_GETLCPADDR(pstPppInfo->pstLcpInfo, pstPppInfo->ulRPIndex);
                if (pstPppInfo->pstLcpInfo == NULL)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_997);
                    PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Fail:Malloc LCP CB Failed");
                    return;
                }

                PPP_MemSet((void *)pstPppInfo->pstLcpInfo, 0, sizeof(PPPLCPINFO_S));
                PPP_LCP_Init(pstPppInfo);/*luofeng37050notify Э�̲���*/
            }

            pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;

            /* ISLUP�¼�ֻ��LCP״̬ΪInitial��Startingʱ����Ч */
            if ((pstLcpInfo->stFsm.ucState == (UCHAR)PPP_STATE_INITIAL)
                || (pstLcpInfo->stFsm.ucState == (UCHAR)PPP_STATE_STARTING))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_998);
                PPP_Core_EstablishPhase(pstPppInfo);
            }

            break;
        }
        case PPPISLDOWN:
        {
            pstPppInfo->bLowerIsUp  = 0;
            pstPppInfo->bLoopBacked = 0;

            /* L2TP��Ҫ�Ĳ��� */
            if (NULL != pstPppInfo->pL2tpPara)
            {
                (VOID)PPP_Free(pstPppInfo->pL2tpPara);
                pstPppInfo->pL2tpPara = NULL;
            }

            /* ֪ͨ LCP Down  */
            if (pstPppInfo->pstLcpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_999);
                /* ��LCP����������Ϣ:LowerDown��Close */
                PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (ULONG)PPP_EVENT_FSM_DOWN, NULL);
                PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (ULONG)PPP_EVENT_FSM_CLOSE, NULL);

                /* ������Ϣ��Ӧ״̬���¼���״̬ת��ͼ:
                 | State
                 |    0         1         2         3         4         5           6         7         8           9
                Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
                ------+------------------------------------------------------------------------------------------------------
                 Down |    -         -         0       tls/1       0         1          1         1         1         tld/1
                 Close|    0       tlf/0       2         2         4         4      irc,str/4 irc,str/4 irc,str/4 tld,irc,str/4
                 */

                /* 1,����LowerDown�¼�,��ͬ״̬�¶�������:
                   Opened״̬:���ϲ�Э�鷢��LowerDown�¼�(tld),״̬תΪStarting
                   Closed/Closing״̬:״̬תΪInitial
                   ����:״̬תΪStarting

                   2,����Close�¼�,��ʼ״ֻ̬����ΪInitial��Starting.��ͬ״̬�¶�������:
                   Starting״̬:״̬תΪInitial;���²㷢��Finished�¼�(tlf).
                   Initial״̬:�ޱ仯

                   ���,�������¼����ͺ�������½��:
                   1,����״̬��Ȼ��ת��Initial
                   2,ֻҪ��ʼ״̬����Closed/Closing,���Ȼ����tlf��������
                 */
            }

            if (pstPppInfo->pstPapInfo)
            {
                PPP_PAP_ReceiveEventFromCore(pstPppInfo, PAP_EVENT_LOWERDOWN, NULL);
            }
            if (pstPppInfo->pstChapInfo)
            {
                PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_LOWERDOWN, NULL);
            }

            break;

        }
        case PPPISLRENEGO:/* ��Э�� */
        {
            if ((pstPppInfo->pstIpcpInfo)||(pstPppInfo->pstIpV6cpInfo))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1000);
                /* renego��, LCP down, ����PPP_Core_NotifyNcpDown, IPCP�յ�down��close�¼�
                   ����finished״̬, �ֵ���PPP_LCP_NegotiationDown, LCP����initial״̬, ����
                   ����open��up�¼������ٴ���Э�� */

                /*if (((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->stFsm.ucState == PPP_STATE_OPENED)*/
                {
                    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (ULONG)PPP_EVENT_FSM_DOWN, NULL);
                    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL);
                    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (ULONG)PPP_EVENT_FSM_UP, NULL);

                    /* ��̬���ӱ����ʧ�� */
                    pstPppInfo->bPppStateFlg   = PPP_STATE_FAIL;
                    pstPppInfo->bPppStateFlgV6 = PPP_STATE_FAIL;
                }
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_404);
                PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR,
                                    "PPP_Core_ReceiveEventFromShell: Receive invalid PPP RENEGO event!");
            }

            break;
        }
        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ������Э������¼��Ľӿں���                                 *
* MODIFY DATE  ��modified by gxf for GGSN80 20030219                        *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                ulCmd:������,��ҪΪ�������Э��UP/DOWN��ֵ                 *
*                pPara:�¼��Ĳ���,һ�������ΪNULL                          *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Shell_ISLIoCtl / PPP_Shell_NiIoCtl                     *
****************************************************************************/
VOID PPP_Core_ReceiveEventFromProtocol (PPPINFO_S *pstPppInfo,
                                        ULONG      ulCmd,
                                        CHAR *     pPara)
{
    ULONG                               ulMagic;
    PPPFSM_S                           *pstFsm     = NULL;
    PPP_LCP_OPTION_S                   *pstGotOptions;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccessAuth;


    PPP_TRACE("\r\n---Into PPP_Core_ReceiveEventFromProtocol   ulCmd: %d---\r\n", ulCmd);
    if (!pstPppInfo || (ulCmd >= PPP_EVENT_MAXEVENT))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_405);
        VOS_DBGASSERT(0);
        return;
    }

    switch (ulCmd)
    {
        case PPP_EVENT_LCPUP:
        {
            if (VOS_ERR == PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_LCP_UP, NULL))
            {
                /* �·��û���Ϣʧ��, ����   modified by gxf 20030430
                   LCP open״̬�·�down��close�¼�����initil״̬, ��Ҫ��shell�����·�LCPDOWN�¼�(��PPP_Core_DeadPhase) */
                PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, PPP_EVENT_FSM_DOWN, NULL);
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_NEGONAK);
                PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, PPP_EVENT_FSM_CLOSE, NULL);
                (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_LCP_DOWN, NULL);
                PPP_DBG_ERR_CNT(PPP_PHERR_406);
                return;
            }

            /* ����IP��ַй©����, Add by yangfan */
            if ((pstPppInfo->ulPeerIPAddr) && (0 == pstPppInfo->bReNego))
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_407);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_038);
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                        "\r\n[ppp]PPP_Core_ReceiveEventFromProtocol Index %u bPppStateFlg %d usState %d!",
                        pstPppInfo->ulRPIndex,
                        pstPppInfo->bPppStateFlg, pstPppInfo->usState);
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_NEGONAK);
                PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
                return;
            }
            /* ����IP��ַй©����, Add by yangfan */
            if ((VOS_OK == PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr))
                && (0 == pstPppInfo->bReNegoV6))
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_408);
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                        "\r\n[ppp]PPP_Core_ReceiveEventFromProtocol Index %u bPppStateFlgV6 %d usState %d!",
                        pstPppInfo->ulRPIndex,
                        pstPppInfo->bPppStateFlgV6, pstPppInfo->usState);
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_NEGONAK);
                PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
                return;
            }

            /* ������������Ȩ����Ҫ���Ͱ汾����ָʾ */
            enIsDoingAccessAuth = PPPC_IsDoingAccessAuth();
            if (PS_FALSE == enIsDoingAccessAuth)
            {
                /* ���Ͱ汾����ָʾ����*/
                ulMagic = PPP_GetMagicNumber();
                pstFsm = &(((PPPLCPINFO_S*)pstPppInfo->pstLcpInfo)->stFsm);
                PPP_FSM_SendVendorSpecific(pstFsm, pstFsm->ucVSId, ulMagic,VENDORSPECIFIC_INDICTE);
                pstFsm->ucVSId++;
            }

            /* ����MRU */
            pstGotOptions = &(((PPPLCPINFO_S*)pstPppInfo->pstLcpInfo)->stGotOptions);
            pstPppInfo->pstConfigInfo->usMru = pstGotOptions->mru;

            /* ���LCPЭ�̽��,ȷ���Ƿ���֤ */
            PPP_Core_AuthUp(pstPppInfo,NULL);
            break;
        }
        case PPP_EVENT_LCPDOWN:
        {
            if ((PPPLOWEDOWN != pstPppInfo->bFailFlag) && (1 == pstPppInfo->bReNego ||1 == pstPppInfo->bReNegoV6))
            {
                (VOID)PPP_SendUserInfo(pstPppInfo, MAGICNUM_INVALID);
            }

            PPP_DBG_OK_CNT(PPP_PHOK_1001);
            /* ��̬���ӱ����ʧ�� */
            pstPppInfo->bPppStateFlg   = PPP_STATE_FAIL;
            pstPppInfo->bPppStateFlgV6 = PPP_STATE_FAIL;

            /* Э��ת��Terminate�׶�,����Э��LCP */
            PPP_Core_TerminatePhase(pstPppInfo);
            break;
        }
        case PPP_EVENT_LCPFINISHED:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1002);

            /*zfz notice: ��Ҫɾ��PAP/CHAP ���ƿ� */
            if (pstPppInfo->pstPapInfo)
            {
                PPP_PAP_ReceiveEventFromCore(pstPppInfo, PAP_EVENT_LOWERDOWN, NULL);
            }

            if (pstPppInfo->pstChapInfo)
            {
                PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_LOWERDOWN, NULL);
            }
#if( VRP_MODULE_LINK_PPP == VRP_YES )
            if (pstPppInfo->pstEapInfo)
            {
                PPP_EAP_ReceiveEventFromCore(pstPppInfo, EAP_EVENT_LOWERDOWN, NULL);
            }
#endif
            /* Э��ת��Dead�׶� */
            PPP_Core_DeadPhase(pstPppInfo);
            break;
        }
        case PPP_EVENT_LCPSTARTING:
            break;

        case PPP_EVENT_IPCPUP:
        {
            if (NULL != pstPppInfo->pstIpcpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1003);
                pstPppInfo->bIpcpNoToPDN= VOS_FALSE;   /* 1ʱ��֪ͨPDN */

                /* ����Ƿ���IPCP UP�¼� */
                if (VOS_ERR == PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_IPCP_UP, NULL))
                {
                    /* �·��û���Ϣʧ��, ����   modified by gxf 20030430
                       LCP open״̬�·�down��close�¼�����initil״̬, ��Ҫ��shell�����·�LCPDOWN�¼�(��PPP_Core_DeadPhase) */
                    /* ���溯���е����еĴ����֧���Ѿ���ʼ��lcp down,���ﲻ��Ҫ�ٽ����� */
                    PPP_DBG_OK_CNT(PPP_PHOK_1004);
                    return;
                }
            }

            break;
        }
        case PPP_EVENT_IPCPDOWN:
        {
            if (NULL != pstPppInfo->pstIpcpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1005);

                /* ����Ƿ���IPCP DOWN�¼� */
                (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_IPCP_DOWN, NULL);
            }
            break;
        }
        case PPP_EVENT_IPCPFINISHED:
        {
            /* ֪ͨPDN IPCPЭ��ʧ�� */
            /* �ж��Ƿ�Ҫ֪ͨpdn������֪ͨ */
            if (VOS_FALSE == pstPppInfo->bIpcpNoToPDN)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1006);
            }

            PPP_DBG_OK_CNT(PPP_PHOK_1007);
            PPP_Core_IpcpV4FinProc(pstPppInfo);
            PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n Ipcp Fail bIpcpNoToPDN:%d",pstPppInfo->bIpcpNoToPDN);


            break;
        }
        case PPP_EVENT_IPCPSTARTING:
            break;

        case PPP_EVENT_IPV6CPUP:
            if ( NULL != pstPppInfo->pstIpV6cpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1008);
                pstPppInfo->bIpv6cpNoToPDN= VOS_FALSE;   /* 1ʱ��֪ͨPDN */

                /* ����Ƿ���IPV6CP UP�¼� */
                if (VOS_ERR == PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_IPV6CP_UP, NULL))
                {
                    /* �·��û���Ϣʧ��, ����
                       LCP open״̬�·�down��close�¼�����initil״̬, ��Ҫ��shell�����·�LCPDOWN�¼�(��PPP_Core_DeadPhase) */
                    PPP_DBG_ERR_CNT(PPP_PHERR_409);
                    return;
                }
            }
            break;

        case PPP_EVENT_IPV6CPDOWN:
            if (NULL != pstPppInfo->pstIpV6cpInfo)
            {
                /* ����Ƿ���IPV6CP DOWN�¼� */
                (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_IPV6CP_DOWN, NULL);

                PPP_DBG_OK_CNT(PPP_PHOK_1009);
            }
            break;

        case PPP_EVENT_IPV6CPFINISHED:

            /* ֪ͨPDN IPV6CPЭ��ʧ�� */
            /* �ж��Ƿ�Ҫ֪ͨpdn������֪ͨ */
            if (VOS_FALSE == pstPppInfo->bIpv6cpNoToPDN)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1010);
            }

            PPP_DBG_OK_CNT(PPP_PHOK_1011);
            PPP_Core_IpcpV6FinProc(pstPppInfo);
            PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n Ipv6cp Fail bIpv6cpNoToPDN:%d",pstPppInfo->bIpv6cpNoToPDN);

            break;

        case PPP_EVENT_IPV6CPSTARTING:
            break;

        case PPP_EVENT_VSNCPUP:
        {
            if (NULL != pstPppInfo->pstVsncpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1012);
                /* ����Ƿ���VSNCP UP�¼� */
                if (VOS_ERR == PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_VSNCP_UP, NULL))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_410);
                    return;
                }
            }
            break;
        }
        case PPP_EVENT_VSNCPDOWN:
        {
            if (NULL != pstPppInfo->pstVsncpInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1013);
                /* ����Ƿ���VSNCP DOWN�¼� */
                (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_VSNCP_DOWN, NULL);
            }
            break;
        }
        case PPP_EVENT_VSNCPFINISHED:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1014);
            PPP_CORE_VSNCPFinishProc(pstPppInfo);
            break;
        }
        case PPP_EVENT_VSNCPSTARTING:
            break;

        case PPP_EVENT_PAPSUCCESS:/*PAP��֤�ɹ� */
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1015);
            pstPppInfo->bAuthFlag = VOS_TRUE;

            M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_NET);

            PPP_Core_AuthUp(pstPppInfo, pPara);

            break;
        }
        case PPP_EVENT_PAPFAILED:/*PAP ��֤ʧ�� */
        {
            /*ɾ��PAP���ƿ�*/
            if (pstPppInfo->pstPapInfo)
            {
                PPPPAPINFO_S* pstPapInfo = (PPPPAPINFO_S*)pstPppInfo->pstPapInfo;
                PPP_DBG_OK_CNT(PPP_PHOK_1016);
                if (NULL != pstPapInfo->pstAAAAuthReqMsg)
                {
                    (VOID)PPP_Free(pstPapInfo->pstAAAAuthReqMsg);
                    pstPapInfo->pstAAAAuthReqMsg = NULL;
                }
                /*ɾ���ȴ�Request ��ʱ��ʱ��*/
                if (pstPapInfo->ulServerTimeoutID != 0)
                {
                    (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));
                    pstPapInfo->ulServerTimeoutID = 0;
                }

                pstPapInfo->ucUsed = 0;
                pstPppInfo->pstPapInfo = NULL;
            }

            PPP_ERROR_COUNTER(PPP_ERROR_COUNTER052);
            PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_PAP_NAK);
            PPP_DBG_OK_CNT(PPP_PHOK_1017);

            /*֪ͨLCP DOWN ��FINISHED */
            PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
            break;
        }
        case PPP_EVENT_CHAPSUCCESS:/*CHAP��֤�ɹ� */
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1018);
            pstPppInfo->bAuthFlag = VOS_TRUE;
            M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_NET);

            PPP_Core_AuthUp(pstPppInfo, pPara);

            break;
        }
        case PPP_EVENT_CHAPFAILED: /*CHAP ��֤ʧ�� */
        {
            /*ɾ��CHAP���ƿ�*/
            if (pstPppInfo->pstChapInfo)
            {
                PPPCHAPINFO_S* pstChapInfo = (PPPCHAPINFO_S*)pstPppInfo->pstChapInfo;
                PPP_DBG_OK_CNT(PPP_PHOK_1019);

                if (NULL != pstChapInfo->pstAAAAuthReqMsg)
                {
                    (VOID)PPP_Free(pstChapInfo->pstAAAAuthReqMsg);
                    pstChapInfo->pstAAAAuthReqMsg = NULL;
                }

                pstChapInfo->ucUsed = 0;
                pstPppInfo->pstChapInfo = NULL;
            }

            PPP_ERROR_COUNTER(PPP_ERROR_COUNTER053);
            PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_NAK);
            PPP_DBG_OK_CNT(PPP_PHOK_1020);

            /*֪ͨLCP DOWN ��FINISHED */
            PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
            break;
        }

#if VRP_MODULE_LINK_PPP_EAP == VOS_YES
        /*EAP��֤�ɹ� */
        case PPP_EVENT_EAPSUCCESS:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1021);
            pstPppInfo->bAuthFlag = VOS_TRUE;
            M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_NET);

            PPP_Core_AuthUp(pstPppInfo, pPara);
            break;
        }
        /* EAP ��֤ʧ�� */
        case PPP_EVENT_EAPFAILED:
        {
            /* ɾ��EAP���ƿ� */
            if (pstPppInfo->pstEapInfo)
            {
                PPPEAPINFO_S* pstEapInfo = (PPPEAPINFO_S*)pstPppInfo->pstEapInfo;
                PPP_DBG_OK_CNT(PPP_PHOK_1022);

                if (NULL != pstEapInfo->pucEAP)
                {
                    (VOID)PPP_Free(pstEapInfo->pucEAP);
                    pstEapInfo->pucEAP = NULL;
                }

                pstEapInfo->ucUsed = 0;
                pstPppInfo->pstEapInfo = NULL;
            }

            PPP_ERROR_COUNTER(PPP_ERROR_COUNTER054);
            PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_EAP_FAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1023);
            /* ֪ͨLCP DOWN ��FINISHED */
            PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
            break;
        }
#endif
        case PPP_EVENT_RECHALLENGE:/* CHAP ������֤,DOWN��NCP */
        {
            if (pstPppInfo->usPhase == (USHORT)PPP_PHASE_NETWORK)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1024);
                /* ֪ͨNCP DOWN  */
                if (pstPppInfo->pstIpcpInfo)
                {
                    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, PPP_EVENT_FSM_DOWN, NULL );
                    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, PPP_EVENT_FSM_CLOSE, NULL );

                    /* �ͷŷ�����Զ˵�IP��ַ */
                    (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_FREE_PEERIPADDR, NULL);

                    if ( VOS_NULL != ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg )
                    {
                        (VOID)PPP_Free(((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg);
                        ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg = NULL;
                        ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->ulIpv4cpLen = 0;
                    }

                    /* �ͷſ��ƿ�ռ�ñ�� */
                    ((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->ucUsedFlag = 0;
                    pstPppInfo->pstIpcpInfo = NULL;
                }
                pstPppInfo->usPhase = (USHORT)PPP_PHASE_AUTHENTICATE;
            }

            break;
        }
#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
        case PPP_EVENT_CCPUP:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1025);
            if (VOS_OK != PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_CCP_UP, NULL))
            {
                 PPP_DBG_ERR_CNT(PPP_PHERR_411);
                 PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo,PPP_EVENT_FSM_CLOSE, NULL);
            }
            break;
        }
        case PPP_EVENT_CCPDOWN:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1026);
            (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, PPP_CCP_DOWN, NULL);
            break;
        }
        case PPP_EVENT_CCPFINISHED:
        {
            /* ɾ�����ƿ� */
            if (pstPppInfo->pstCcpInfo != NULL)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1027);
                /*line -e746*/
                PPP_ClearCCPCB(pstPppInfo->pstCcpInfo);
                /*lint +e746*/
            }

            break;
        }
        case PPP_EVENT_CCPSTARTING:
            break;
#endif
        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ���Է��ܾ�Э��һ��Э��,֪ͨ��Э��:lower down                 *
* MODIFY DATE  ��                                                           *
* INPUT        ��pPppInfo:PPP���ƿ�ָ��                                     *
*                usRejectedProtocol:���ܾ���Э���                          *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceiveProtocolRej                                 *
****************************************************************************/
VOID PPP_Core_RejectProtocol(VOID *pPppInfo, USHORT usRejectedProtocol)
{
    PPPINFO_S *pstPppInfo = NULL;

    if (VOS_NULL_PTR == pPppInfo)
    {
        return;
    }

    pstPppInfo = (PPPINFO_S*)pPppInfo;

    /*    VOS_DBGASSERT(pstPppInfo) ;*/
    PPP_TRACE("\r\n---Into PPP_Core_RejectProtocol---\r\n");

    switch (usRejectedProtocol)
    {
        case PPP_PAP:
            if (pstPppInfo->pstPapInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1028);
                /* PAP����ѭPPP��׼״̬��,���÷���CLOSE�¼� */
                PPP_PAP_ReceiveEventFromCore(pstPppInfo, PAP_EVENT_LOWERDOWN, NULL);

                /* ɾ��PAP���ƿ� */
                /* added by hyj 20040109 */
                if (NULL != ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->pstAAAAuthReqMsg)
                {
                    (VOID)PPP_Free(((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->pstAAAAuthReqMsg);
                    ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->pstAAAAuthReqMsg = NULL;
                }

                /*�ͷſ��ƿ�ռ�ñ��*/
                ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->ucUsed = 0;
                pstPppInfo->pstPapInfo = NULL;
            }

            break;

        case PPP_CHAP:
            if (pstPppInfo->pstChapInfo)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1029);
                /* CHAP����ѭPPP��׼״̬��,���÷���CLOSE�¼� */
                PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_LOWERDOWN, NULL);

                /* ɾ��CHAP���ƿ� */
                /* added by hyj 20040109 */
                if (NULL != ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->pstAAAAuthReqMsg)
                {
                    (VOID)PPP_Free(((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->pstAAAAuthReqMsg);
                    ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->pstAAAAuthReqMsg = NULL;
                }

                /*�ͷſ��ƿ�ռ�ñ��*/
                ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->ucUsed = 0;
                pstPppInfo->pstChapInfo = NULL;
            }

            break;

        default:
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ������Э��Ż�ö�ӦЭ���״̬��ָ��,û��״̬����            *
*                (��PAP / CHAP,��Э��״̬��û�д���)�򷵻�NULL              *
* MODIFY DATE  ��                                                           *
* INPUT        ��pPppInfo  : PPP���ƿ�                                      *
*                usProtocol: Э���                                         *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_FSM_ReceiveProtocolRej                                 *
****************************************************************************/
PPPFSM_S *PPP_Core_GetFsmByProtocol(VOID *pPppInfo, USHORT usProtocol)
{
    PPPINFO_S *pstPppInfo = NULL;
    PPPFSM_S  *pstFsm = NULL;

    VOS_DBGASSERT(pPppInfo);

    if (VOS_NULL_PTR == pPppInfo)
    {
        return VOS_NULL;
    }

    pstPppInfo = (PPPINFO_S*)pPppInfo;

    switch (usProtocol)
    {
        case PPP_IPCP:
            if (pstPppInfo->pstIpcpInfo)
            {
                pstFsm = &(((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->stFsm);
            }

            break;
         case PPP_IPV6CP:
             if (pstPppInfo->pstIpV6cpInfo)
             {
                 pstFsm = &(((PPPIPV6CPINFO_S *)(pstPppInfo->pstIpV6cpInfo))->stFsm);
             }

             break;
        case PPP_CCP:
        case PPP_MCP:
        case PPP_SCP:
            if (pstPppInfo->pstCcpInfo)
            {
                pstFsm = &(((PPP_CCP_INFO_S*)(pstPppInfo->pstCcpInfo))->stFsm);
            }

            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_412);
            break;
    }

    return pstFsm;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ����ñ��ĵ�Э���                                           *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                pPacket:����ͷָ��                                         *
* OUTPUT       ��                                                           *
*                pusProtocol:Ҫ���ص�Э���                                 *
* RETURN       ��PPPͷ����                                                  *
* CALLED BY    ��PPP_Core_ReceivePacketFromShell                            *
*                PPP_Shell_ISLInput                                         *
****************************************************************************/
ULONG PPP_Core_GetProtocol(PPPINFO_S *pstPppInfo,
                           UCHAR *    pPacket,
                           USHORT *   pusProtocol)
{
    ULONG ulPointerShift = 0;
    ULONG ulDataShift = 0;

    VOS_DBGASSERT(pPacket);
    VOS_DBGASSERT(pusProtocol);

    if ((NULL == pusProtocol) || (NULL == pPacket))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_413);
        return 0;
    }

    if (pPacket[0] == 0xff)  /** no accmp **/
    {
        if (pPacket[1] != 0x03)
        {
            /*log error here*/
            PPP_DBG_ERR_CNT(PPP_PHERR_414);
            /*pstPppInfo->stStatisticInfo.ulBadControlPackets ++;*/     /* deleted by gxf 20030224 */
            return 0;
        }

        /*
        ____________________________________
         |    |    |    |    |
         | ff | 03 | 00 | 21 |............
         |____|____|____|____|_________________
         |  accmp  |  pcmp   |
         */
        if (pPacket[2] & 0x01)   /** pcmp  **/
        {
            ulPointerShift = 3;
            ulDataShift = 1;

            /*
            _______________________________
             |    |    |    |
             | ff | 03 | 21 |............
             |____|____|____|_________________
             |  accmp  |pcmp|
             */
        }
        else
        {
            ulPointerShift = 4;
            ulDataShift = 2;
        }
    }
    else
    {
        /*���û�����õ�ַѹ����ô�д�*/

        /*
        if (pstPppInfo->pstLcpInfo &&
            ((PPPLCPINFO_S *)pstPppInfo->pstLcpInfo)->stHisOptions.neg_accompression == 0)

        {
            pstPppInfo->stStatisticInfo.ulBadAddressPackets ++;
        }
         */

        if (pPacket[0] & 0x01)   /** pcmp **/
        {
            ulPointerShift = 1;
            ulDataShift = 1;

            /*_____________________
             |    |
             | 21 |............
             |____|_________________
             |pcmp|
             */
        }
        else
        {
            ulPointerShift = 2;
            ulDataShift = 2;

            /*
             ____________________________________
             |    |    |
             | 00 | 21 |............
             |____|____|_________________
             |  pcmp   |
             */
        }
    }

    pPacket += (ulPointerShift - ulDataShift);
    if (ulDataShift == 2)
    {
        PPP_GETSHORT(*pusProtocol, pPacket);
    }
    else
    {
        PPP_GETCHAR(*pusProtocol, pPacket);
    }

    return ulPointerShift;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ���յ�����ʶ���֧�ֵ�Э��ı���,����protocol rej����      *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                pHead:���������ڴ���ͷָ��                               *
*                pPacket:����ͷָ��                                         *
*                ulLen:���ĳ���                                             *
*                usProtocol:���ĵ�Э���                                    *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Core_ReceivePacketFromShell                            *
****************************************************************************/
VOID PPP_Core_ReceiveUnknownProtocol (PPPINFO_S *pstPppInfo,
                                      UCHAR *    pHead,
                                      UCHAR *    pPacket,
                                      ULONG      ulLen,
                                      USHORT     usProtocol,
                                      UCHAR      ucCode)
{
    PPPLCPINFO_S *pstLcpInfo = NULL;
    PPPFSM_S *pstFsm = NULL;

    VOS_DBGASSERT(pstPppInfo);
    VOS_DBGASSERT(pHead);
    VOS_DBGASSERT(pPacket);
    PPP_TRACE("\r\n---Into PPP_Core_ReceiveUnknownProtocol---\r\n");
    PPP_DBG_OK_CNT(PPP_PHOK_1030);
    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if (NULL == pstLcpInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    if ((pstLcpInfo->stFsm.ucState == (UCHAR)PPP_STATE_OPENED))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1031);
        pstFsm = &(pstLcpInfo->stFsm);

        ulLen = 2;
        if (NULL == pHead)
        {
            VOS_DBGASSERT(0);
            return;
        }

        if ((PPP_IPCP == usProtocol) && (CONFREQ == ucCode))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1032);
            PPP_PerfInc(&g_stPppPerfStatistic.ulIpcpTotal, PERF_TYPE_PPPC_IPCP_NEGO_REQ_NUM, pstPppInfo->bEhrpdUser);
            PPP_TRACE("****Ipv6cpTotal: Only Support ipv6, IPV4_IPCP_ATTEMPT times! ");
        }

        if((PPP_IPV6CP == usProtocol)&& (CONFREQ == ucCode))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1033);
            IPV6_PerfStatistic(IPV6_IPV6CP_ATTEMPT);
            PPP_TRACE("****Ipv6cpTotal: PPP_Core_ReceivePacketFromShell, IPV6_PerfStatistic Attempt: Enter!");
            A11_OM_PerfStatisticPCFUnit((ULONG)PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_REQ_NUM, pstPppInfo->ulPcfIP);
        }

        pPacket = pHead + PPP_RESERVED_PACKET_HEADER;

        /* ������� */

        /*
         |---- PPP_RESERVED_PACKET_HEADER ----|---- ulLen ----|
         +-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |               ...                  |       |       |
         +-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |                                    |
        pHead                                pPacket
         */

        PPP_PUTSHORT(usProtocol, pPacket);
        pPacket -= ulLen;

        /* ������� */

        /*
         |---- PPP_RESERVED_PACKET_HEADER ----|---- ulLen ----|
         +-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |               ...                  |    protocol   |
         +-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         |                                    |
        pHead                                pPacket
         */

        /* ����protocol reject */
        PPP_FSM_SendPacket(pstFsm, PROTREJ, pstFsm->ucPktId++, pHead, pPacket, ulLen);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1034);
    }
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��PPPЭ�̽׶�ת����Dead�׶�                                  *
* MODIFY DATE  ��modified by gxf for GGSN80 20030220                        *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Core_ReceiveEventFromProtocol                                                         *
****************************************************************************/
VOID PPP_Core_DeadPhase(PPPINFO_S *pstPppInfo)
{
    /* ȱʡ����reset��ʱ�� */
    ULONG ulReset = 0;

    PPPLCPINFO_S *pstLcpInfo = NULL;


    /*ULONG ulRtnVos = 0;*/ /* deleted by gxf 20030227 for lint warning */
    PPP_TRACE("\r\n---Into PPP_Core_DeadPhase---\r\n");

    if (!pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    /* �ı�Э�̽׶� */
    pstPppInfo->usPhase = (USHORT)PPP_PHASE_DEAD;

    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if ((pstLcpInfo != NULL) && (pstLcpInfo->stFsm.ucState == (UCHAR)PPP_STATE_INITIAL))
    {
        /* LCP״̬ΪInitial,˵���ǵײ�down����LCP finished�¼���,
           ��˲���֪ͨ�ײ� */

        /* GGSNB03,֪ͨGTPC��L2TP ������ӵ����� */
        /*PPP_Shell_ReceiveEventFromCore(pstPppInfo, (ULONG)PPP_LCP_DOWN, (CHAR*)&ulReset) ;*/
        PPP_DBG_OK_CNT(PPP_PHOK_1035);
    }
    else
    {
        /* LCP״̬��ΪInitial,˵��LCPЭ�̵���LCP finished�¼���, */

        /* ֪ͨ�ײ�:��·�Ѿ�������Ҫ�����Բ����·�� */
        (VOID)PPP_Shell_ReceiveEventFromCore(pstPppInfo, (ULONG)PPP_LCP_DOWN, (CHAR*)&ulReset);
        PPP_DBG_OK_CNT(PPP_PHOK_1036);
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��PPPЭ�̽׶�ת����Establish�׶�                             *
* MODIFY DATE  ��modified by gxf for GGSN80 20030220                        *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Core_ReceiveEventFromShell                             *
****************************************************************************/
VOID PPP_Core_EstablishPhase(PPPINFO_S *pstPppInfo)
{

    /*PPPINFO_S *pstTopPppInfo ;*/ /* deleted by gxf 20030220 */

    VOS_DBGASSERT(pstPppInfo);
    PPP_TRACE("\r\n---Into PPP_Core_EstablishPhase---\r\n");
    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

 #if (VRP_MODULE_SEC_L2TP == VRP_YES)
    /* L2TP��Ҫ�Ĳ��� */
    if ( (VOS_TRUE != pstPppInfo->bEhrpdUser) && (pstPppInfo->pL2tpPara == NULL) )
    {
        pstPppInfo->pL2tpPara = (VOID*)PPP_Malloc(sizeof(L2TP_SESSIONPARA_S));

        /* ����ʧ����ʲôҲ����,����L2TPʱ��������ԤЭ�̽������,
           ��˲��ö�����ʧ�ܽ��д��� */
    }

    if (pstPppInfo->pL2tpPara != NULL)
    {
        /* ���� */
        PPP_MemSet(pstPppInfo->pL2tpPara, 0, sizeof(L2TP_SESSIONPARA_S));

        /*�����Լ�longsirui*/
        ((L2TP_SESSIONPARA_S*)pstPppInfo->pL2tpPara)->usAuthenType = L2TP_NONE;
    }
 #endif

    /* ֪ͨ�ϲ�LCP down */
    /* �Ȿ�����Բ�����,ֻ��Ϊ�˱�֤��ȫ����һЩ������ж� */
    PPP_Core_NotifyUperLcpDown(pstPppInfo);

    /* �޸�������Ϣָ��  *(pstPppInfo->pstUsedConfigInfo) = *(pstTopPppInfo->pstConfigInfo) ;*/

    /* deleted by gxf 20030220
       ��PPP_InitConfigInfo�����������Ϣ��ʼ�� */

    /*(VOID)VOS_MemCpy((VOID*)(pstPppInfo->pstUsedConfigInfo),(VOID*)(pstTopPppInfo->pstConfigInfo),sizeof(PPPCONFIGINFO_S));*/

    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL );
    PPP_LCP_ReceiveEventFromCore(pstPppInfo->pstLcpInfo, (ULONG)PPP_EVENT_FSM_UP, NULL );

    /* �ı�Э�̽׶� */
    pstPppInfo->usPhase = (USHORT)PPP_PHASE_ESTABLISH;
    PPP_DBG_OK_CNT(PPP_PHOK_1037);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��PPPЭ�̽׶�ת����Authenticate�׶�                          *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Core_ReceiveEventFromProtocol                          *
****************************************************************************/
VOID PPP_Core_AuthenticatePhase(PPPINFO_S *pstPppInfo)
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;

    VOS_DBGASSERT(pstPppInfo);
    PPP_TRACE("\r\n---Into PPP_Core_AuthenticatePhase---\r\n");

    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstLcpInfo = (PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo);
    VOS_DBGASSERT(pstLcpInfo);
    if (NULL == pstLcpInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    if ((pstLcpInfo->stGotOptions.neg_upap) || (pstLcpInfo->stHisOptions.neg_upap)) /*�Ƿ�ʹ��PAP��֤*/
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1038);
        if (pstPppInfo->pstPapInfo == NULL)
        {
            /*����PAP���ƿ�*/
            PPP_GETPAPADDR(pstPppInfo->pstPapInfo , pstPppInfo->ulRPIndex);
        }

        if (pstPppInfo->pstPapInfo != NULL)
        {
            PPP_MemSet((void *)pstPppInfo->pstPapInfo, 0, sizeof(PPPPAPINFO_S));
            PPP_PAP_Init(pstPppInfo);        /* ��ʼ��PAP���ƿ� */
            /* ��PAP������Ϣ,����PAP��ʼЭ�� */
            if (pstLcpInfo->stGotOptions.neg_upap)
            {
                /*Server��PAP UP */
                PPP_PAP_ReceiveEventFromCore(pstPppInfo, PAP_EVENT_SERVERLOWERUP, NULL );
            }

            if (pstLcpInfo->stHisOptions.neg_upap)
            {
                /*Client��PAP UP */
                PPP_PAP_ReceiveEventFromCore(pstPppInfo, PAP_EVENT_CLIENTLOWERUP, NULL );
            }

            /* �ı�Э�̽׶� */
            pstPppInfo->usPhase = (USHORT)PPP_PHASE_AUTHENTICATE;
        }
        else
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_415);
            /* ��ӵ�����Ϣ */
            /*����PAP���ƿ�ʧ��,���ں˱���֤ʧ��*/
            PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_PAPFAILED, NULL);
            return;
        }
    }

    if ((pstLcpInfo->stGotOptions.neg_chap) || (pstLcpInfo->stHisOptions.neg_chap)) /* �Ƿ�ʹ��CHAP��֤ */
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1039);
        if (pstPppInfo->pstChapInfo == NULL)
        {
            /*����CHAP���ƿ�*/
            PPP_GETCHAPADDR(pstPppInfo->pstChapInfo, pstPppInfo->ulRPIndex);
        }

        if (pstPppInfo->pstChapInfo != NULL)
        {
            PPP_MemSet((void *)pstPppInfo->pstChapInfo, 0, sizeof(PPPCHAPINFO_S));
            PPP_CHAP_Init(pstPppInfo);        /* ��ʼ��CHAP���ƿ� */
            /* ��CHAP������Ϣ,����CHAP��ʼЭ�� */
            /*changed by chenmin00265046���ֻ���������Ҫ��Э��chap��Ȩ���������������Ƿ����chap��Ȩ,������stHisOptions���ж��Ƿ�Ҫ��Ȩ*/
            if (pstLcpInfo->stHisOptions.neg_chap)
            {
                if (0 == pstPppInfo->bPppClient)
                {
                    /* Server ��CHAP UP */
                    PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_SERVERLOWERUP, NULL );
                }
				else
		        {
                    PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_CLIENTLOWERUP, NULL );
	            }
            }

            /* �ı�Э�̽׶� */
            pstPppInfo->usPhase = (USHORT)PPP_PHASE_AUTHENTICATE;
        }
        else
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_416);
            /*����CHAP���ƿ�ʧ��,���ں˱���֤ʧ��*/
            /* ��ӵ�����Ϣ */
            PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_CHAPFAILED, NULL);
            return;
        }
    }
#if VRP_MODULE_LINK_PPP_EAP == VOS_YES
    /* �Ƿ�ʹ��EAP��֤ */
    if ((pstLcpInfo->stGotOptions.neg_eap) || (pstLcpInfo->stHisOptions.neg_eap))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1040);
        if (NULL == pstPppInfo->pstEapInfo)
        {
            /*����EAP���ƿ�*/
            PPP_GETEAPADDR(pstPppInfo->pstEapInfo, pstPppInfo->ulRPIndex);
        }

        if (pstPppInfo->pstEapInfo != NULL)
        {
            /* ��ʼ��EAP���ƿ� */
            PPP_EAP_Init(pstPppInfo);
            /* ��EAP������Ϣ,����EAP��ʼЭ�� */
            if (pstLcpInfo->stGotOptions.neg_eap)
            {
                /* Server ��EAP UP */
                PPP_EAP_ReceiveEventFromCore(pstPppInfo, EAP_EVENT_SERVERLOWERUP, NULL);
            }
            /* �ı�Э�̽׶� */
            pstPppInfo->usPhase = (USHORT)PPP_PHASE_AUTHENTICATE;
        }
        else
        {
            /* ����EAP���ƿ�ʧ��,���ں˱���֤ʧ�� */
            /* ��ӵ�����Ϣ */
            PPP_DBG_ERR_CNT(PPP_PHERR_417);
            PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_EAPFAILED, NULL);
            return;
        }
    }
#endif

    /********ZFZ/CM:�Ƿ�Ӧʹ���ж�PAP���ƿ����������ɹ���־ */
    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��CCP����Э��                                                *
* MODIFY DATE  ��modified by gxf for GGSN80 20030220                        *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Core_NetworkPhase                                      *
****************************************************************************/
VOID ppp_Core_CcpInitiativeNego(PPPINFO_S *pstPppInfo)
{
    if (NULL == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n ppp_Core_CcpInitiativeNego: Invalid input parameter pstPppInfo!");
        return;
    }

    PPP_TRACE("\r\n---Into ppp_Core_CcpInitiativeNego---\r\n");

#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)

    /* �ڴ˳��ж��Ƿ�Ӧ��Э��CCP, ���BIT1385�����Ƿ�����Э�� */
    if((1 == SOFTPARA_BIT1385) && (VOS_OK == PPP_CheckCcpLimit()))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1041);
        PPP_ClearCCPCB(pstPppInfo->pstCcpInfo);
        PPP_GETCCPADDR(pstPppInfo->pstCcpInfo, pstPppInfo->ulRPIndex);
        if (pstPppInfo->pstCcpInfo)
        {
            PPP_MemSet((void *)pstPppInfo->pstCcpInfo, 0, sizeof(PPP_CCP_INFO_S));

            /* ��ʼ��CCP���ƿ� */
            PPP_CCP_init(pstPppInfo);

            if (0 == ((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulCcpTimeoutID)
            {
                /*����CCP��ʱ��ʱ��*/
                (VOS_VOID)VOS_StartRelTimer((HTIMER)&(((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulCcpTimeoutID),
                                            MID_PPPC,
                                            ((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulTimeOutTime,
                                            pstPppInfo->ulRPIndex,
                                            PPPC_CCP_TIMEOUT_TIMER,
                                            VOS_TIMER_LOOP,
                                            VOS_TIMER_PRECISION_0);
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_418);
            }

            /* ��CCP������Ϣ,����CCP��ʼЭ�� */
            PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL );
            PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (ULONG)PPP_EVENT_FSM_UP, NULL );
        }
        else
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_419);
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Malloc CCP CB Err!!");
        }
    }
    else
    {
        PPP_TRACE("\r\nppp_Core_CcpInitiativeNego: SOFTPARA_BIT1385 = %lu", SOFTPARA_BIT1385);
    }
#endif/* (VRP_MODULE_LINK_PPP_CCP == VRP_YES) */
    return ;
}

/*****************************************************************************
 �� �� ��  : PPP_Core_NetworkPhase
 ��������  : PPP�׶�Lcp��Auth��ɺ�ת������׶Σ�֪ͨUSM
 �������  : PPPINFO_S *pstPppInfo
             UCHAR* pMsg
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_Core_NetworkPhase(PPPINFO_S *pstPppInfo,UCHAR* pMsg)
{
    UCHAR ucIsRenego = 0;
    USM_PPP_LINKUP_RESULT_S stMsg ={0};  /* PPP Link up ֪ͨUSM����Ϣ�ṹ�� */
    VOS_UINT8               ucPdnId;
    VOS_UINT32              ulRet;

    VOS_DBGASSERT(pstPppInfo);

    if (NULL == pstPppInfo)
    {
        /*��ӡ������Ϣ��*/
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\nPPP_Core_NetworkPhase: Invalid input parameter!");
        return;
    }

    PPPC_INFO_LOG("\r\n PPP_Core_NetworkPhase. \r\n");/*add by chenmin00265046*/

    /* CCP����Э�� */
    ppp_Core_CcpInitiativeNego(pstPppInfo);

    if (VOS_FALSE == pstPppInfo->bEhrpdUser)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1042);
        /* ����ǿͻ���ģʽ���������ַ��ֱ�ӽ���IPCP */
        if (PPP_CLIENT_TRUE == pstPppInfo->bPppClient)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1043);
            _PPP_Core_NetworkPhase(pstPppInfo);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                         "\r\nPPP_Core_NetworkPhase: Client Mode Enter IPCP!");
            return;
        }

        /*............................................*/
        /*.............��Э�̴�������.................*/
        if (pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV4 )
        {
            if ((pstPppInfo->ulPeerIPAddr) || (PPP_USERTYPE_MIP == pstPppInfo->bIPTech))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1044);
                /*��Э�̣��е�ַ��ΪCMIP��ֱ�ӽ���IPCPЭ��*/
                PPP_Ipv4cp_Proc(pstPppInfo);
                PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_Core_NetworkPhase Renego enter IPV4CP !");
                ucIsRenego = VOS_TRUE;
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1045);
                pstPppInfo->bReNego = 0;
            }
        }

        if (pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV6 )
        {
            if (VOS_OK == PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1046);
                /*��Э�̣��е�ַ������IPV6CPЭ��*/
                PPP_Ipv6cp_Proc(pstPppInfo);
                PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_Core_NetworkPhase Renego enter IPV6CP !");
                ucIsRenego = VOS_TRUE;
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1047);
                pstPppInfo->bReNegoV6 = 0;
            }
        }

        if(ucIsRenego)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1048);
            PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_Core_NetworkPhase Renego !");
            return;
        }
    }
    else
    {
        /* EHRPD�û������Ƿ���Э�̶�֪ͨUSM����USM��֪ͨ��PDN����VSNCP��Э�� */
        PPP_DBG_OK_CNT(PPP_PHOK_1049);

        ulRet = PPPC_GetCurrentPdnId(&ucPdnId);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG("Get Pdn id fail.");
            return;
        }
        /* PPP����VSNCPЭ�� */
        PPP_VSNCP_NotifyVSNCPStart(pstPppInfo, ucPdnId);
    }

    /*Auth��Ȩ�ɹ��ս�ģʽ ������Э��ûIP��ַ����֪ͨUSM*/
    /* ��䷢��USM����Ϣ�ṹ�� */
    stMsg.pucMsg = pMsg;
    stMsg.ulRpIndex = pstPppInfo->ulRPIndex;
    stMsg.usDomainIndex = pstPppInfo->usCDBIndex;
    stMsg.usVirtualDomainIndex = pstPppInfo->usVirtualDomainIdx;
    VOS_MemCpy(stMsg.aucNAI, pstPppInfo->ucNAI, NAI_NAME_LEN + 1);

    if (VOS_OK != USM_NotifyPhaseResultFunc(pstPppInfo->ulRPIndex,
                                            E_USM_MSGTYPE_PPP2USM_SETUP,
                                            (UCHAR *)&stMsg))
    {
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_420);
        return;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,"\r\nPPP_Core_NetworkPhase: success!");
    return;
}

ULONG AAA_IPValidCheck(ULONG ulAddr)
{
    ulAddr = VOS_HTONL(ulAddr);

    if ((ulAddr == AAA_INADDR_BROADCAST) || (ulAddr == AAA_INADDR_ANY)
        || ((ulAddr & AAA_IN_CLASSA_NET) == AAA_INADDR_LOOP))
    {
        return VOS_ERR;
    }

    if (AAA_IN_CLASSA( ulAddr ))
    {
        if (((ulAddr & AAA_IN_CLASSA_NET) == 0) || ((ulAddr & AAA_IN_CLASSA_HOST) == 0)
            || ((ulAddr & AAA_IN_CLASSA_HOST) == AAA_IN_CLASSA_HOST))
        {
            return VOS_ERR;
        }

        return VOS_OK;
    }

    if (AAA_IN_CLASSB( ulAddr ))
    {
        if (((ulAddr & AAA_IN_CLASSB_NET) == 0) || ((ulAddr & AAA_IN_CLASSB_HOST) == 0)
            || ((ulAddr & AAA_IN_CLASSB_HOST) == AAA_IN_CLASSB_HOST))
        {
            return VOS_ERR;
        }

        return VOS_OK;
    }

    if (AAA_IN_CLASSC( ulAddr ))
    {
        if (((ulAddr & AAA_IN_CLASSC_NET) == 0) || ((ulAddr & AAA_IN_CLASSC_HOST) == 0)
            || ((ulAddr & AAA_IN_CLASSC_HOST) == AAA_IN_CLASSC_HOST))
        {
            return VOS_ERR;
        }

        return VOS_OK;
    }

    return VOS_ERR;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��PPPЭ�̽׶�ת����Network�׶�                               *
* MODIFY DATE  ��modified by gxf for GGSN80 20030220                        *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Core_ReceiveEventFromProtocol                          *
****************************************************************************/
VOID _PPP_Core_NetworkPhase(PPPINFO_S *pstPppInfo)
{

    VOS_DBGASSERT(pstPppInfo);

    if (NULL == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n_PPP_Core_NetworkPhase: Invalid input parameter pstPppInfo!");
        return;
    }

    PPP_TRACE("\r\n---Into _PPP_Core_NetworkPhase---\r\n");

    if (PPP_CLIENT_TRUE == pstPppInfo->bPppClient) /* ��������PDSN��֧�� */
    {
        PPPC_INFO_LOG1("PPPC mode is client. %d", pstPppInfo->ucIpCapability);
        if ((pstPppInfo->pstIpV6cpInfo == NULL)
            && (pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV6))
        {
            PPP_GETIPV6CPADDR(pstPppInfo->pstIpV6cpInfo, pstPppInfo->ulRPIndex);
            if (NULL == pstPppInfo->pstIpV6cpInfo)
            {
                PPPC_ERROR_LOG("Malloc IPV6CP CB Err!!");
                return;
            }

            PPP_MemSet((void *)pstPppInfo->pstIpV6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));

            PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);
            PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL );
            PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (ULONG)PPP_EVENT_FSM_UP, NULL );
        }
        if ((pstPppInfo->pstIpcpInfo == NULL)
            && (pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV4))
        {
            PPP_GETIPCPADDR(pstPppInfo->pstIpcpInfo, pstPppInfo->ulRPIndex);
            if (NULL == pstPppInfo->pstIpcpInfo)
            {
                PPPC_ERROR_LOG("Malloc IPCP CB Err!!");
                return;
            }

            PPP_MemSet((void *)pstPppInfo->pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

            PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);
            PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL );
            PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (ULONG)PPP_EVENT_FSM_UP, NULL );
        }
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1051);
        if ( pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV4 )
        {
            if ((VOS_OK == AAA_IPValidCheck(pstPppInfo->ulPeerIPAddr))
                || (PPP_USERTYPE_MIP == pstPppInfo->bIPTech))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1052);
                PPP_Ipv4cp_Proc(pstPppInfo);
            }
        }

        /* ����IPV6��ַ��ȡ���IPCP���̴��� */
        if ((pstPppInfo->ucIpCapability & PDSN_PPP_IPTYE_IPV6))
        {
            if (VOS_OK == PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1053);
                PPP_Ipv6cp_Proc(pstPppInfo);
            }
        }
    }

 #if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
    /* �ڴ˳��ж��Ƿ�Ӧ��Э��CCP, ���BIT307�����Ƿ�����Э�� */
    if((1 == SOFTPARA_BIT1385) && (VOS_OK == PPP_CheckCcpLimit()))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1054);
        PPP_ClearCCPCB(pstPppInfo->pstCcpInfo);
        PPP_GETCCPADDR(pstPppInfo->pstCcpInfo, pstPppInfo->ulRPIndex);
        if (pstPppInfo->pstCcpInfo)
        {
            PPP_MemSet((void *)pstPppInfo->pstCcpInfo, 0, sizeof(PPP_CCP_INFO_S));

            /* ��ʼ��CCP���ƿ� */
            PPP_CCP_init(pstPppInfo);

            if (0 == ((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulCcpTimeoutID)
            {
                /*����CCP��ʱ��ʱ��*/
                (VOS_VOID)VOS_StartRelTimer((HTIMER)&(((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulCcpTimeoutID),
                                            MID_PPPC,
                                            ((PPP_CCP_INFO_S*)((PPPINFO_S*)pstPppInfo)->pstCcpInfo)->ulTimeOutTime,
                                            pstPppInfo->ulRPIndex,
                                            PPPC_CCP_TIMEOUT_TIMER,
                                            VOS_TIMER_LOOP,
                                            VOS_TIMER_PRECISION_0);
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_421);
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1055);

            /* ��CCP������Ϣ,����CCP��ʼЭ�� */
            PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL );
            PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (ULONG)PPP_EVENT_FSM_UP, NULL );
        }
        else
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_422);
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Malloc CCP CB Err!!");
        }
    }
 #endif/* (VRP_MODULE_LINK_PPP_CCP == VRP_YES) */

    /* �ı�Э�̽׶� */
    pstPppInfo->usPhase = (USHORT)PPP_PHASE_NETWORK;

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��PPPЭ�̽׶�ת����Terminate�׶�                             *
* MODIFY DATE  ��modified by gxf for GGSN80 20030220                        *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Core_ReceiveEventFromProtocol                          *
****************************************************************************/
VOID PPP_Core_TerminatePhase(PPPINFO_S *pstPppInfo)
{
    VOS_DBGASSERT(pstPppInfo);

    PPP_TRACE("\r\n---Into PPP_Core_TerminatePhase---\r\n");

    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    //SNMP_TerminatePhaseProc(pstPppInfo);

     /* ֪ͨ�ϲ�LCP down */
    PPP_Core_NotifyUperLcpDown(pstPppInfo);

    pstPppInfo->bAuthServer = VRP_NO;
    pstPppInfo->bAuthClient = VRP_NO;

    /* �ı�Э�̽׶� */
    pstPppInfo->usPhase = (USHORT)PPP_PHASE_TERMINATE;

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��֪ͨ�ϲ�:LCP down                                          *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Core_TerminatePhase��PPP_Core_EstablishPhase           *
****************************************************************************/
VOID PPP_Core_NotifyUperLcpDown(PPPINFO_S *pstPppInfo)
{
    VOS_DBGASSERT(pstPppInfo);
    PPP_TRACE("\r\n---Into PPP_Core_NotifyUperLcpDown---\r\n");

    /* Added start by zhangxiujuan 60016360 at 2006-07-08 V800R005C01B010 for pclint */
    /*�ж������������Ч��*/
    if (NULL == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_Core_NotifyUperLcpDown: Invalid input parameter!");
        return;
    }

    /* Added end by zhangxiujuan 60016360 at 2006-07-08 V800R005C01B010 for pclint */

    if (pstPppInfo->pstPapInfo)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1056);
        /* ��PAP������Ϣ,��������Э�� */
        PPP_PAP_ReceiveEventFromCore(pstPppInfo, (ULONG)PAP_EVENT_LOWERDOWN, NULL );

        /* ɾ�����ƿ� */
        /* added by hyj 20040109 */
        if (NULL != ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->pstAAAAuthReqMsg)
        {
            (VOID)PPP_Free(((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->pstAAAAuthReqMsg);
            ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->pstAAAAuthReqMsg = NULL;
        }

        /*�ͷſ��ƿ�ռ�ñ��*/
        ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->ucUsed = 0;
        pstPppInfo->pstPapInfo = NULL;
    }

    if (pstPppInfo->pstChapInfo)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1057);
        /* ��CHAP������Ϣ,��������Э�� */
        PPP_CHAP_ReceiveEventFromCore(pstPppInfo, CHAP_EVENT_LOWERDOWN, NULL );

        /* ɾ�����ƿ� */
        /* added by hyj 20040109 */
        if (NULL != ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->pstAAAAuthReqMsg)
        {
            (VOID)PPP_Free(((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->pstAAAAuthReqMsg);
            ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->pstAAAAuthReqMsg = NULL;
        }
        /*�ͷſ��ƿ�ռ�ñ��*/
        ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->ucUsed = 0;
        pstPppInfo->pstChapInfo = NULL;
    }

    if (pstPppInfo->pstEapInfo)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1058);
        /* ��EAP������Ϣ,��������Э�� */
        PPP_EAP_ReceiveEventFromCore(pstPppInfo, EAP_EVENT_LOWERDOWN, NULL);

        /* ɾ��EAP���ƿ� */
        if (NULL != ((PPPEAPINFO_S *)pstPppInfo->pstEapInfo)->pucEAP)
        {
            (VOID)PPP_Free(((PPPEAPINFO_S *)pstPppInfo->pstEapInfo)->pucEAP);
            ((PPPEAPINFO_S *)pstPppInfo->pstEapInfo)->pucEAP = NULL;
        }

        /* �ͷſ��ƿ�ռ�ñ�� */
        ((PPPEAPINFO_S *)pstPppInfo->pstEapInfo)->ucUsed = 0;
        pstPppInfo->pstEapInfo = NULL;
    }


    PPP_Core_NotifyNcpDown( pstPppInfo );
    return;
}

/*add by houzhipeng*/

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��֪ͨ NCP down                                              *
* MODIFY DATE  ��modified by gxf for GGSN80 20030220                        *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��                                                           *
****************************************************************************/
VOID PPP_Core_NotifyNcpDown(PPPINFO_S *pstPppInfo)
{
    VOS_DBGASSERT(pstPppInfo);
    PPP_TRACE("\r\n---Into PPP_Core_NotifyNcpDown---\r\n");

    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    if (pstPppInfo->pstIpcpInfo)
    {
        PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR;
        PPP_DBG_OK_CNT(PPP_PHOK_1059);

        pstIpcpInfo = (PPPIPCPINFO_S *)(pstPppInfo->pstIpcpInfo);
        if (pstIpcpInfo->stFsm.ulTimeOutID)
        {
            (VOID)VOS_StopRelTimer(&(pstIpcpInfo->stFsm.ulTimeOutID));
            pstIpcpInfo->stFsm.ulTimeOutID = 0;
        }

        pstPppInfo->bIpcpNoToPDN= VOS_TRUE;   /* 1ʱ��֪ͨPDN */

        /* ��IPCP������Ϣ,��������Э�� */
        PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (ULONG)PPP_EVENT_FSM_DOWN, NULL );
        //PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (ULONG)PPP_EVENT_FSM_CLOSE, NULL );

        pstPppInfo->bIpcpNoToPDN= VOS_FALSE;

        /* �ж����bEnableVJCompΪ1����VJ�û�����1 */
        if (1 == ((PPPCONFIGINFO_S*)pstPppInfo->pstConfigInfo)->bEnableVJComp)
        {
            ((PPPCONFIGINFO_S*)pstPppInfo->pstConfigInfo)->bEnableVJComp = 0;
        }


        /*�ͷſ��ƿ�ռ�ñ��,��������´���close�¼��ǿ��ƿ��Ѿ��ͷţ���������һ�±��� */
        if ( NULL != pstPppInfo->pstIpcpInfo )
        {
            if ( VOS_NULL != ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg )
            {
                (VOID)PPP_Free(((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg);
                ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->pucIpv4cpMsg = NULL;
                ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->ulIpv4cpLen = 0;
            }

            ((PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo)->ucUsedFlag = 0;
            pstPppInfo->pstIpcpInfo = NULL;
        }
    }
    if (pstPppInfo->bEhrpdUser)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1060);
        PPP_VSNCP_ClearALL(pstPppInfo);
    }
    if (pstPppInfo->pstIpV6cpInfo)
    {
        PPPIPV6CPINFO_S *pstIpv6cpInfo = VOS_NULL_PTR;
        PPP_DBG_OK_CNT(PPP_PHOK_1061);

        pstIpv6cpInfo = (PPPIPV6CPINFO_S *)(pstPppInfo->pstIpV6cpInfo);
        if (pstIpv6cpInfo->stFsm.ulTimeOutID)
        {
            (VOID)VOS_StopRelTimer(&(pstIpv6cpInfo->stFsm.ulTimeOutID));
            pstIpv6cpInfo->stFsm.ulTimeOutID = 0;
        }

        pstPppInfo->bIpv6cpNoToPDN = VOS_TRUE;   /* 1ʱ��֪ͨPDN */

        /* ��IPCP������Ϣ,��������Э�� */
        PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (ULONG)PPP_EVENT_FSM_DOWN, NULL );
        //PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (ULONG)PPP_EVENT_FSM_CLOSE, NULL );

        /*��־����֮�󽫱�־�û�*/
        pstPppInfo->bIpv6cpNoToPDN = VOS_FALSE;

        /*��������´���close�¼��ǿ��ƿ��Ѿ��ͷţ���������һ�±���*/
        if ( pstPppInfo->pstIpV6cpInfo )
        {
            /* �ͷŻ�����Ϣ�ڴ� */
            if ( VOS_NULL != ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg )
            {
                (VOID)PPP_Free(((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg);
                ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->pucIpv6cpMsg = NULL;
                ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->ulIpv6cpLen = 0;
            }

            if (0 != ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->ucUsedFlag)
            {
                /* ɾ�����ƿ� */
                ((PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo)->ucUsedFlag = 0;
                PPP_DBG_OK_CNT(PPP_PHOK_1062);
            }
            pstPppInfo->pstIpV6cpInfo = NULL;
        }
    }


 #if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
    if (pstPppInfo->pstCcpInfo)
    {
        /*add by huzhiyong ɾ���ش���ʱ��2002/03/08*/
        PPP_CCP_INFO_S * pstCcpInfo;
        PPP_DBG_OK_CNT(PPP_PHOK_1063);

        pstCcpInfo = (PPP_CCP_INFO_S *)(pstPppInfo->pstCcpInfo);
        if (pstCcpInfo->stFsm.ulTimeOutID)
        {
            (VOID)VOS_StopRelTimer(&(pstCcpInfo->stFsm.ulTimeOutID));
            pstCcpInfo->stFsm.ulTimeOutID = 0;
        }

        /*end of add*/
        /* ��CCP������Ϣ,��������Э�� */
        PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (ULONG)PPP_EVENT_FSM_DOWN, NULL );
        PPP_CCP_ReceiveEventFromCore(pstPppInfo->pstCcpInfo, (ULONG)PPP_EVENT_FSM_CLOSE, NULL );
        PPP_ClearCCPCB(pstPppInfo->pstCcpInfo);
    }
 #endif

    return;
}

/*add end*/

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ������Magic Number                                           *
* MODIFY DATE  ��                                                           *
* INPUT        ��                                                           *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_LCP_addci��PPP_LCP_nakci��PPP_LCP_reqci                *
****************************************************************************/
ULONG PPP_GetMagicNumber()
{
    ULONG                               ulRetVal = 0;
    VOS_UINT32                          ulSeed;
    VOS_UINT32                          ulRandVal;


#ifdef PPPC_ST
    static ULONG ulMagicNumber = 0x78724c47;/*add by chenmin00265046, Ϊ������, ħ����Ϊ��ֵ����ɾ��*/
#endif
    while (ulRetVal == 0)
    {
        /* ��ȡʱ��tick����Ϊ���� */
        ulSeed = VOS_GetTick();
        VOS_SetSeed(ulSeed);

        /* ��������� */
        ulRandVal   = VOS_Rand(0xffffffff);
        ulRetVal    = ulRandVal + ulSeed;

#ifdef PPPC_ST
        ulRetVal = ++ulMagicNumber;/*add by chenmin00265046, Ϊ������, ħ����Ϊ��ֵ����ɾ��*/
#endif
    }

    return ulRetVal;
}

VOID ImsiToString( A11_IMSI_S stImsi ,UCHAR*szTemp)
{
    UCHAR ucLoop;

    UCHAR ucTemp;

    UCHAR* szImsi = (UCHAR*)&stImsi;

    if ( szTemp == NULL)
    {
        return;
    }

    VOS_MemSet(szTemp, 0, 16);

    for( ucLoop = 1; ucLoop <= 15; ucLoop++ )
    {
        if( ucLoop % 2 == 0 )

            ucTemp = (UCHAR)( szImsi[ucLoop/2] & 0x0f );

        else

            ucTemp = (UCHAR)( szImsi[ucLoop/2] >> 4);

        if( ucTemp > 9)

            break;

        szTemp[ucLoop-1] = (UCHAR)(ucTemp + '0');
    }

    szTemp[ucLoop-1] = 0;

    return ;
}

VOS_CHAR*  VOS_StrCat( VOS_CHAR * pcdest, const VOS_CHAR * pcsrc )
{
    return strcat(pcdest, pcsrc);
}

/*****************************************************************************
 �� �� ��  : PPP_Core_AuthUp
 ��������  : LCP up����֤ͨ������ô˺���,�ж��Ǹý���Network�׶�
             ���Ǹý���Authenticate�׶�(��ֻ������Authenticate�׶�)
 �������  : PPPINFO_S *pstPppInfo
             AAA_AUTHRSP_S* pMsg
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��30��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_Core_AuthUp(PPPINFO_S *pstPppInfo, UCHAR* pMsg)
{

    PPPCONFIGINFO_S *pstConfigInfo = NULL;


    ULONG ulUserNameLen = 0;
    ULONG ulDomainNameLen = 0;

    VOS_DBGASSERT(pstPppInfo);
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n---Into PPP_Core_AuthUp---\r\n");

    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }
    pstConfigInfo = pstPppInfo->pstConfigInfo;

    if ((pstPppInfo->bAuthServer == VRP_NO) && (pstPppInfo->bAuthClient == VRP_NO))
    {
        /* PDSN�û����û��Я��NAI,��Ҫ����IMSI����������NAI */
        if ((VOS_FALSE == pstPppInfo->bEhrpdUser) && (0 == VOS_StrLen((const CHAR *)(pstPppInfo->ucNAI))))
        {
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1064);
                /* ����������fa���������£��豸���ü�Ȩʱ�ᱻ�ܾ��Ӷ�domain�������Ϊ�գ������޷��������У����������һ�� */
                M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_AUTH);

                pstPppInfo->usCDBIndex = 0;
                pstPppInfo->usVirtualDomainIdx = 0;
                VOS_StrCpy((CHAR*)pstConfigInfo->ucDomainName, (CHAR *)(g_pstApnByIndex[0].aucAPN));

                /* ����LOCK��־�ж��Ƿ���������Ǳ�LOCK�����������������Э��ʧ�� */
                if (PPP_DOMAIN_LOCKED == g_pstApnByIndex[pstPppInfo->usCDBIndex].ucLock)
                {
                    HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_8);
                    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                                 "\r\n PPP_Core_AuthUp:The domain is locked, the domainindex is %u", pstPppInfo->usCDBIndex);
                    PPP_DBG_ERR_CNT(PPP_PHERR_423);
                    PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_NEGONAK);
                    PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
                    return;
                }

                /* ����NAI */
                ImsiToString( *((A11_IMSI_S*)&pstPppInfo->stIMSI), ( UCHAR* )pstPppInfo->ucNAI);
                VOS_StrCat((CHAR *)pstPppInfo->ucNAI, "@");

                ulUserNameLen = VOS_StrLen((CHAR*)pstPppInfo->ucNAI);
                ulDomainNameLen = VOS_StrLen((CHAR *)pstPppInfo->pstUsedConfigInfo->ucDomainName);

                /* ����NAI���Ȳ���Խ�� */
                if ((ulUserNameLen + ulDomainNameLen) >= NAI_NAME_LEN)
                {
                    HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_9);
                    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                                 "\r\n PPP_Core_AuthUp: generate NAI length is ellegal");
                    SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
                    PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_NEGONAK);
                    PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
                    PPP_ERROR_COUNTER(PPP_ERROR_COUNTER049);
                    return;
                }
                VOS_StrCat((CHAR *)pstPppInfo->ucNAI, (const char*)(pstPppInfo->pstUsedConfigInfo->ucDomainName));
            }
        }

        M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_NET);

        PPP_DBG_OK_CNT(PPP_PHOK_1065);
        /* �ı�Э�̽׶� */
        pstPppInfo->usPhase = (USHORT)PPP_PHASE_NETWORK;
        PPP_Core_NetworkPhase(pstPppInfo, (UCHAR*)pMsg);
    }
    else
    {
        if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_AUTHENTICATE)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1066);
            M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_AUTH);

            PPP_Core_AuthenticatePhase(pstPppInfo);
        }
        PPP_DBG_OK_CNT(PPP_PHOK_1067);
    }

    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
