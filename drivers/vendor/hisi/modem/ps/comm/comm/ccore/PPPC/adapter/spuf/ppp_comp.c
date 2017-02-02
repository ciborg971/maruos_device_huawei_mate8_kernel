/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ppp_comp.c
  �� �� ��   : ����
  ��    ��   : luofang
  ��������   : 2012��9��18��
  ����޸�   :
  ��������   : PPP������
  �����б�   :
*
*       1.                PPP_CompConstruct
*       2.                PPP_CompDestruct
*       3.                PPP_CompInit1
*       4.                PPP_CompInit2
*       5.                PPP_CompInit3
*       6.                PPP_CompMsgProc
*       7.                PPP_MsgDispatch
*

  �޸���ʷ   :
  1.��    ��   : 2012��9��18��
    ��    ��   : luofang
    �޸�����   : �����ļ�

******************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"
#include "fwd_ppp.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_COMP_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : PPP_GetSelfCompInfo
 ��������  : ��ȡ����������Ϣ
 �������  : DMS_COMMID_T myCSI
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_GetSelfCompInfo(DMS_COMMID_T myCSI )
{
    g_stPppCompInfo.ullSelfCsi = PSM_Inf_GetSelfCSI(E_COMP_TYPE_PPPT);
#if defined(__LINUX_PLATFORM__)
      (VOID)VOS_HandleInitialize("AMHSGWPPP", &g_stPppCompInfo.ulHandle);
#else
       g_stPppCompInfo.ulHandle   = MID_PPPC;
#endif
    g_stPppCompInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(g_stPppCompInfo.ullSelfCsi);
    g_stPppCompInfo.ullSelfSgId  = PSM_Inf_GetSelfSGID();
    g_stPppCompInfo.ulSelfCmpIdxInSG = PSM_Inf_GetCmpSameTIndexInSGByCSI(PPP_SELF_CSI);
    g_ucSelfScId = g_stPppCompInfo.ulSelfCmpIdxInSG;

    return;
}




/*****************************************************************************
 �� �� ��  : PPP_InitRand
 ��������  : ��ʼ���������
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_InitRand(VOID)
{
    return;
}


/*****************************************************************************
 �� �� ��  : PPP_LocalMemInit
 ��������  : �����ڴ��ʼ��
 �������  :
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_LocalMemInit(  )
{
    VOS_UINT32                          ulMemSize = 0;
    VOS_UINT32                          ulRep;


    g_ulPppTaskTrace = 4;

    ulMemSize = sizeof(ULONG) * PPP_DBG_BUTT;
    PPP_MemSet((void*)g_ulPppDBGStatisc, 0, ulMemSize);


    g_ulPppTaskTrace = 5;

    /* ע��:g_ulPppFsmStat��ָ������ */
    ulMemSize = sizeof(ULONG) * 5 * PPP_EVENT_FSM_BUTT * PPP_STATE_BUTT;
    PPP_MemSet((void*)&g_ulPppFsmStat[0][0], 0, ulMemSize);

    g_ulPppTaskTrace = 6;


    ulMemSize = PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER;
    PPP_MemSet((void*)g_ucPppSendPacketHead, 0, ulMemSize);

    g_ulPppTaskTrace = 7;

    ulMemSize = PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER;
    PPP_MemSet((void*)g_ucPppRcvPacketHead, 0, ulMemSize);

    g_ulPppTaskTrace = 8;

    ulMemSize = sizeof(PPPINFO_S) * (PPP_MAX_USER_NUM + 1);
    PPP_MemSet((void*)g_astPppPool, 0, ulMemSize);

    g_ulPppTaskTrace = 9;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    ulMemSize = sizeof(struct hdlc) * (PPP_MAX_USER_NUM + 1);
    PPP_MemSet((void*)g_astHdlcPool, 0, ulMemSize);
#endif

    /*lcp ���ƿ�*/
    ulMemSize = sizeof(PPPLCPINFO_S) * (PPP_MAX_USER_NUM + 1);
    PPP_MemSet((void*)g_astPppLcpPool, 0, ulMemSize);

    g_ulPppTaskTrace = 10;

    /*ipcp ���ƿ�*/
    ulMemSize = sizeof(PPPIPCPINFO_S) * (PPP_MAX_USER_NUM + 1);
    PPP_MemSet((void*)g_astPppIpcpPool, 0, ulMemSize);

    g_ulPppTaskTrace = 11;

    /*ipv6cp ���ƿ�*/
    ulMemSize = sizeof(PPPIPV6CPINFO_S) * (PPP_MAX_USER_NUM + 1);
    PPP_MemSet((void*)g_astPppIpv6cpPool, 0, ulMemSize);

    g_ulPppTaskTrace = 12;

    /*pap ���ƿ�*/
    ulMemSize = sizeof(PPPPAPINFO_S) * (PPP_MAX_USER_NUM + 1);
    PPP_MemSet((void*)g_astPppPapPool, 0, ulMemSize);

    g_ulPppTaskTrace = 13;

    /*chap ���ƿ�*/
    ulMemSize = sizeof(PPPCHAPINFO_S) * (PPP_MAX_USER_NUM + 1);
    PPP_MemSet((void*)g_astPppChapPool, 0, ulMemSize);

    g_ulPppTaskTrace = 14;

#if VRP_MODULE_LINK_PPP_EAP == VOS_YES
    /*EAP ���ƿ�*/
    ulMemSize = sizeof(PPPEAPINFO_S) * (PPP_MAX_USER_NUM + 1);
    PPP_MemSet((void*)g_astPppEapPool, 0, ulMemSize);

    g_ulPppTaskTrace = 15;
#endif

    /*ccp ���ƿ�*/
    ulMemSize = sizeof(PPP_CCP_INFO_S) * (PPP_MAX_USER_NUM + 1);
    PPP_MemSet((void*)g_astPppCcpPool, 0, ulMemSize);

    g_ulPppTaskTrace = 16;

    /*config ���ƿ�*/
    ulMemSize = sizeof(PPPCONFIGINFO_S) * (PPP_MAX_USER_NUM + 1);
    PPP_MemSet((void*)g_astPppConfifPool, 0, ulMemSize);


    g_ulPppTaskTrace = 17;

    PPP_MemSet((UCHAR *)g_pVsncpOptionDecode, 0, (PPP_VSNCP_CO_BUTT * (sizeof(VSNCP_OPTION_DECODE))));
    g_ulPppTaskTrace = 18;

    PPP_MemSet((UCHAR *)g_pVsncpOptionEncode, 0, (PPP_VSNCP_CO_BUTT * (sizeof(VSNCP_OPTION_ENCODE))));

    g_ulPppTaskTrace = 19;

    for (ulRep = 0; ulRep < PPP_MAX_USER_NUM + 1; ulRep++)
    {
        PPP_MemSet((VOS_VOID *)&g_pstLocalLinkTcb[ulRep], 0, sizeof(LINKTCB_S));
    }

#if 0
    g_ulPppTaskTrace = 4;

    ulMemSize = sizeof(ULONG) * PPP_DBG_BUTT;
    g_ulPppDBGStatisc = (ULONG *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, ulMemSize);
    if (NULL == g_ulPppDBGStatisc)
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n g_ulPppDBGStatisc PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((void*)g_ulPppDBGStatisc, 0, ulMemSize);


    g_ulPppTaskTrace = 5;

    /* ע��:g_ulPppFsmStat��ָ������ */
    ulMemSize = sizeof(ULONG) * 5 * PPP_EVENT_FSM_BUTT * PPP_STATE_BUTT;
    g_ulPppFsmStat[0] = (ULONG *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, ulMemSize);
    if (NULL == g_ulPppFsmStat[0])
    {
        VOS_DBGASSERT(0);
        (VOS_VOID)vos_printf("\r\n PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    g_ulPppFsmStat[1] = g_ulPppFsmStat[0] + PPP_EVENT_FSM_BUTT * PPP_STATE_BUTT;
    g_ulPppFsmStat[2] = g_ulPppFsmStat[0] + 2 * PPP_EVENT_FSM_BUTT * PPP_STATE_BUTT;
    g_ulPppFsmStat[3] = g_ulPppFsmStat[0] + 3 * PPP_EVENT_FSM_BUTT * PPP_STATE_BUTT;
    g_ulPppFsmStat[4] = g_ulPppFsmStat[0] + 4 * PPP_EVENT_FSM_BUTT * PPP_STATE_BUTT;
    PPP_MemSet((void*)g_ulPppFsmStat[0], 0, ulMemSize);

    g_ulPppTaskTrace = 6;


    ulMemSize = PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER;

    g_ucPppSendPacketHead = (UCHAR *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, ulMemSize);
    /* g_ucPppSendPacketHead = (UCHAR *)PPP_Malloc(ulMemSize); */
    if(NULL == g_ucPppSendPacketHead )
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n g_ucPppSendPacketHead PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((void*)g_ucPppSendPacketHead, 0, ulMemSize);

    g_ulPppTaskTrace = 7;

    ulMemSize = PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER;
    g_ucPppRcvPacketHead = (UCHAR*)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, ulMemSize);
    if(NULL == g_ucPppRcvPacketHead )
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n g_ucPppRcvPacketHead PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((void*)g_ucPppRcvPacketHead, 0, ulMemSize);

    g_ulPppTaskTrace = 8;

    ulMemSize = sizeof(PPPINFO_S) * (PPP_MAX_USER_NUM + 1);
    g_astPppPool = (PPPINFO_S *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, ulMemSize);
    if(NULL == g_astPppPool )
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n g_astPppPool PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((void*)g_astPppPool, 0, ulMemSize);

    g_ulPppTaskTrace = 9;

    /*lcp ���ƿ�*/
    ulMemSize = sizeof(PPPLCPINFO_S) * (PPP_MAX_USER_NUM + 1);
    g_astPppLcpPool = (PPPLCPINFO_S *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, ulMemSize);
    if(NULL == g_astPppLcpPool )
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n g_astPppLcpPool PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((void*)g_astPppLcpPool, 0, ulMemSize);

    g_ulPppTaskTrace = 10;

    /*ipcp ���ƿ�*/
    ulMemSize = sizeof(PPPIPCPINFO_S) * (PPP_MAX_USER_NUM + 1);
    g_astPppIpcpPool = (PPPIPCPINFO_S *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, ulMemSize);
    if(NULL == g_astPppIpcpPool )
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n g_astPppIpcpPool PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((void*)g_astPppIpcpPool, 0, ulMemSize);

    g_ulPppTaskTrace = 11;

    /*ipv6cp ���ƿ�*/
    ulMemSize = sizeof(PPPIPV6CPINFO_S) * (PPP_MAX_USER_NUM + 1);
    g_astPppIpv6cpPool = (PPPIPV6CPINFO_S *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, ulMemSize);
    if(NULL == g_astPppIpv6cpPool )
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n g_astPppIpv6cpPool PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((void*)g_astPppIpv6cpPool, 0, ulMemSize);

    g_ulPppTaskTrace = 12;

    /*pap ���ƿ�*/
    ulMemSize = sizeof(PPPPAPINFO_S) * (PPP_MAX_USER_NUM + 1);
    g_astPppPapPool = (PPPPAPINFO_S *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, ulMemSize);
    if(NULL == g_astPppPapPool )
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n g_astPppPapPool PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((void*)g_astPppPapPool, 0, ulMemSize);

    g_ulPppTaskTrace = 13;

    /*chap ���ƿ�*/
    ulMemSize = sizeof(PPPCHAPINFO_S) * (PPP_MAX_USER_NUM + 1);
    g_astPppChapPool = (PPPCHAPINFO_S *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, ulMemSize);
    if(NULL == g_astPppChapPool )
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n g_astPppChapPool PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((void*)g_astPppChapPool, 0, ulMemSize);

    g_ulPppTaskTrace = 14;

#if VRP_MODULE_LINK_PPP_EAP == VOS_YES
    /*EAP ���ƿ�*/
    ulMemSize = sizeof(PPPEAPINFO_S) * (PPP_MAX_USER_NUM + 1);
    g_astPppEapPool = (PPPEAPINFO_S *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, ulMemSize);
    if(NULL == g_astPppEapPool )
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n g_astPppEapPool PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((void*)g_astPppEapPool, 0, ulMemSize);

    g_ulPppTaskTrace = 15;
#endif

    /*ccp ���ƿ�*/
    ulMemSize = sizeof(PPP_CCP_INFO_S) * (PPP_MAX_USER_NUM + 1);
    g_astPppCcpPool = (PPP_CCP_INFO_S *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, ulMemSize);
    if(NULL == g_astPppCcpPool )
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n g_astPppCcpPool PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((void*)g_astPppCcpPool, 0, ulMemSize);

    g_ulPppTaskTrace = 16;

    /*config ���ƿ�*/
    ulMemSize = sizeof(PPPCONFIGINFO_S) * (PPP_MAX_USER_NUM + 1);
    g_astPppConfifPool = (PPPCONFIGINFO_S *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, ulMemSize);
    if(NULL == g_astPppConfifPool )
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n g_astPppConfifPool PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((void*)g_astPppConfifPool, 0, ulMemSize);


    g_ulPppTaskTrace = 17;

    g_pVsncpOptionDecode = (VSNCP_OPTION_DECODE *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, PPP_VSNCP_CO_BUTT * (sizeof(VSNCP_OPTION_DECODE)));
    if( NULL == g_pVsncpOptionDecode )
    {
        (VOID)vos_printf("\r\n g_pVsncpOptionDecode PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((UCHAR *)g_pVsncpOptionDecode, 0, (PPP_VSNCP_CO_BUTT * (sizeof(VSNCP_OPTION_DECODE))));
    g_ulPppTaskTrace = 18;

    g_pVsncpOptionEncode = (VSNCP_OPTION_ENCODE *)VOS_MemAlloc(MID_PPPC, STATIC_MEM_PT, PPP_VSNCP_CO_BUTT * (sizeof(VSNCP_OPTION_ENCODE)));
    if( NULL == g_pVsncpOptionEncode )
    {
        (VOID)vos_printf("\r\n g_pVsncpOptionEncode PPP_Malloc Failed!~!!");
        return VOS_ERR;
    }
    PPP_MemSet((UCHAR *)g_pVsncpOptionEncode, 0, (PPP_VSNCP_CO_BUTT * (sizeof(VSNCP_OPTION_ENCODE))));

    g_ulPppTaskTrace = 19;
#endif
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_ShareMemInit
 ��������  : �����ڴ��ʼ��
 �������  :
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_ShareMemInit(  )
{
#if 0
    g_aulDoStatiscTime = PGP_ShrMemAllocByName(PPP_SNMP_PERF_DO_STATISC_TIME,
                                               SERVICE_MEM_TYPE_SHARE_GLOBAL,
                                               MID_PPPC,
                                               (3 * sizeof(ULONG)));
    if (NULL == g_aulDoStatiscTime)
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n PPP_ShareMemInit g_aulDoStatiscTime  PGP_ShrMemAllocByName Failed!~!!");
        return VOS_ERR;
    }

    VOS_MemSet(g_aulDoStatiscTime, 0, 3 * sizeof(ULONG));


    g_aulNoStatiscTime = PGP_ShrMemAllocByName(PPP_SNMP_PERF_NO_STATISC_TIME,
                                               SERVICE_MEM_TYPE_SHARE_GLOBAL,
                                               MID_PPPC,
                                               (3 * sizeof(ULONG)));
    if (NULL == g_aulNoStatiscTime)
    {
        VOS_DBGASSERT(0);
        (VOID)vos_printf("\r\n PPP_ShareMemInit g_aulNoStatiscTime  PGP_ShrMemAllocByName Failed!~!!");
        return VOS_ERR;
    }

    VOS_MemSet(g_aulNoStatiscTime, 0, 3 * sizeof(ULONG));
#endif
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPP_GlobalMemInit
 ��������  : ȫ�ֱ�����ʼ��
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_GlobalMemInit( )
{

    ULONG ulBoardType = 0;
    ULONG ulLacCompNum = 0;

    g_usPppLzs0UserNum = 0;
    g_usPppLzs1UserNum = 0;

    g_ucPppCcpSwitch = 0;
    g_ucPppVjSwitch = 0;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_GlobalMemInit: enter ! ");


    /* debug���س�ʼ��,ȫ����ʼ��Ϊ0,��VRP_NO */
    PPP_MemSet((VOID*)&g_stPppDebugInfo, 0, sizeof(struct tagPppDebugInfo));

    PPP_MemSet((VOID*)&g_stPPPFailCounter, 0, sizeof(PPP_FAIL_COUNTER));

    PPP_MemSet(( VOID* )(&g_stPppA11AlarmLink), 0, sizeof(PPPA11_AlarmLink_HEAD_S));

}

/*****************************************************************************
 �� �� ��  : PPP_CompInit1
 ��������  : ��һ�׶γ�ʼ�������ֵ������͹������֣�
 �������  :
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_CompInit1( )
{
    ULONG ulRet = VOS_OK;

    g_ulPppTaskTrace = 1;
    /*��ȡ��������*/
    ulRet = CRM_GetSelfGroupBoardType(&g_enPppBoardType);
    if (VOS_OK != ulRet)
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    g_ulPppTaskTrace = 2;

    ///TODO:luofangע��PPPģ��error������־��Ϣ
    /* ע��PPPģ��error������־��Ϣ */
    DBG_LogRecordReg("AM", "PPP", "PPP", &g_ulPppLogLevelErr);

    g_ulPppTaskTrace = 4;

    /*ע���������*/
    if (VOS_OK != PTM_CommandsRegister ( &PppCommandGroup, "pppc", "pppc debug command", PPP_SELF_CSI))
    {
        VOS_DBGASSERT( 0);
        (VOS_VOID)vos_printf("\r\n PPPC CommandsRegister Failed!~!!");
        return VOS_ERR;
    }

    ///TODO:luofangע���ڴ��ӡ��������

    /* ˽���ڴ��ʼ�� */
    ulRet = PPP_LocalMemInit();
    if( VOS_OK != ulRet )
    {

        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_LocalMemInit: error %lu! ",ulRet);
        return VOS_ERR;
    }

    /* �����ڴ��ʼ�� */
    ulRet = PPP_ShareMemInit();
    if( VOS_OK != ulRet )
    {
        return VOS_ERR;
    }

    /* ȫ�ֱ���(�ڴ�)��ʼ�� */
    PPP_GlobalMemInit();

    /* ��ʼ��������� */
    PPP_InitRand();

    /* ע��vsncp���Ա���뺯�� */
    PPP_VSNCP_OptionEncodeReg();
    PPP_VSNCP_OptionDecodeReg();
    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : PPP_CompInit2
 ��������  : �ڶ��׶γ�ʼ��
 �������  :
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_CompInit2(  )
{
    return VOS_OK;
}

#ifdef __LINUX_PLATFORM__

/*****************************************************************************
 �� �� ��  : PPP_ScheduleInit
 ��������  : F����Ϣ����
 �������  : DMS_COMMID_T ullCpi
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��11��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_ScheduleInit(DMS_COMMID_T ullCpi)
{
    ULONG i = 0;
    ULONG ulReturn = VOS_OK;
    COMP_MSGSTM_ATTR_S astMsgQueAttr[PPP_MSG_TYPE_END] = {0};
    ULONG aulScheduleTlb[PPP_MSG_TYPE_END] = { 0 };
    ULONG ulNum = 0;

    /* ��ʼ��ÿ�����е�������� */

    /* ��ֻ�ſ���ת��֮�������ֵ */
    aulScheduleTlb[PPP_MSG_TYPE_TIMER] = g_ulPPPTimerFlowctrl;
    aulScheduleTlb[PPP_MSG_TYPE_AUTH] = g_ulPPPAAAFlowctrl;
    aulScheduleTlb[PPP_MSG_TYPE_USM] = g_ulPPPA11Flowctrl;
    aulScheduleTlb[PPP_MSG_TYPE_GTPC] = 0;
    aulScheduleTlb[PPP_MSG_TYPE_L2TP] = g_ulPPPL2tpFlowctrl;
    aulScheduleTlb[PPP_MSG_TYPE_LAP] = g_ulPPPLapFlowctrl;
    aulScheduleTlb[PPP_MSG_TYPE_DDU] = PPP_DDU_QUE_FLOWCTRL;
    aulScheduleTlb[PPP_MSG_TYPE_FCM] = PPP_DDU_QUE_FLOWCTRL;
    aulScheduleTlb[PPP_MSG_TYPE_INNER] = 50;
    aulScheduleTlb[PPP_MSG_TYPE_DIAMAAA] = g_ulPPPAAAFlowctrl;

    for (i = M_PS_MSG_TYPE_BASE; i < PPP_MSG_TYPE_END; i++)
    {
         if ( 0 == aulScheduleTlb[i] )
         {
             continue;
         }

         astMsgQueAttr[ulNum].uiMsgNum = aulScheduleTlb[i];
         astMsgQueAttr[ulNum].uiStreamId = i;
         astMsgQueAttr[ulNum].uiFcmQue = 0;
         astMsgQueAttr[ulNum].uiMaxAppMsgNum = HSGW_MAX_APP_NUM;

         ulNum++;
     }

     astMsgQueAttr[ulNum].uiMsgNum = 5000;
     astMsgQueAttr[ulNum].uiStreamId = 0;
     astMsgQueAttr[ulNum].uiFcmQue = 0;
     astMsgQueAttr[ulNum].uiPrio = 1;
     astMsgQueAttr[ulNum].uiMaxAppMsgNum = HSGW_MAX_APP_NUM;
     ulNum++;

     /*lint -e746*/
     ulReturn = (ULONG)PGP_ScmCompMsgStmAttribSet(ullCpi, ulNum, astMsgQueAttr);
     /*lint +e746*/
     if (VOS_OK != ulReturn)
     {
         PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG, "\r\n [ppp]PPP_ScheduleInit: PGP_ScmCompMsgStmAttribSet return %x", ulReturn);
     }

     return;
}

#endif

/*****************************************************************************
 �� �� ��  : PPP_CompInit3
 ��������  : �����׶γ�ʼ��
 �������  :
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_CompInit3(  )
{
    ULONG ulRet = VOS_OK;

    /*********************************************
    * ƽ̨�ص�����ע��                 *
    *********************************************/

#ifdef    __PRODUCT_TYPE_PDSN80
    /* CDB��ȡѹ������ */
    PPPGetCompressConfig();
#endif

    /* ��������ģ���ʼ�� */
    /*lint -e746*/
    if (VOS_OK != PPP_OmInitial())
    {
        (VOS_VOID)VOS_OutPrintf("\r\n PPP_ModuleInfoInit: PPP_OmInitial failed.");
    }


    /* ��γ�ʼ�� */
    PPP_SoftParaInit();

    /* CDB��ȡPPP���� */
    PPPGetPPPConfig();

    ulRet = (ULONG)PPP_InitDebugInfo();
    if (VOS_OK != ulRet)
    {
        (VOS_VOID)VOS_OutPrintf("\r\n PPP_InitDebugInfo: PPP_InitDebugInfo failed %lu.", ulRet);
        return VOS_ERR;
    }
    /*lint +e746*/

    return VOS_OK;
}

/****************************************************************************
 �� �� ��  : PPP_StartNegoTimer
 ��������  : Э��ѭ����ʱ����ʼ��
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��26��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_StartNegoTimer(VOS_VOID)
{
    VOS_UINT32                          ulRet = VOS_OK;


    if (VOS_NULL_PTR != g_hNegoListTimeoutID)
    {
        (VOS_VOID)PPP_StopNegoTimer();
    }

    /* Э�̹��̳���2������ֹЭ�̣���ֹPPP״̬��������ѭ��*/
    ulRet = VOS_StartRelTimer((HTIMER *)&g_hNegoListTimeoutID,
                                MID_PPPC,
                                1000,
                                0,
                                PPPC_NEGO_TIMEOUT_TIMER,
                                VOS_TIMER_LOOP,
                                VOS_TIMER_PRECISION_0);

    if (VOS_OK != ulRet)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\nPPP_TaskEntry: PGP_Timer_Create fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/****************************************************************************
 �� �� ��  : PPP_StopNegoTimer
 ��������  : ֹͣЭ��ѭ����ʱ��
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��26��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPP_StopNegoTimer(VOS_VOID)
{
    VOS_UINT32                          ulRet = VOS_OK;


    /* Э�̹��̳���2������ֹЭ�̣���ֹPPP״̬��������ѭ��*/
    ulRet = VOS_StopRelTimer((HTIMER*)&g_hNegoListTimeoutID);
    if (VOS_OK != ulRet)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\nPPP_TaskEntry: PGP_Timer_Create fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_MsgDispatch
 ��������  : ��Ϣ�ַ�����
 �������  : ULONG ulMsgType
             VOID *pMsg
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_MsgDispatch(ULONG ulMsgType, VOID *pMsg )
{
    ULONG ulRet = VOS_ERR;

    if (VOS_NULL == pMsg)
    {

        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_MsgDispatch: input para is null!");
        return VOS_ERR;
    }

    switch(ulMsgType)
    {
        case PPP_MSG_TYPE_USM:          /* ����USM�¼� */
        {
            PPP_A11MsgProc(pMsg);
            break;
        }

        ///TODO:luofang����ѹ���¼�

        case PPP_MSG_TYPE_AUTH:         /* ����AAA�¼� */
        {
            PPP_AAAMsgProc((AAA_AUTHRSP_S *)pMsg);
            break;
        }
        case PPP_MSG_TYPE_DIAMAAA:
        {
#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
            PPP_EAP_ReceiveDiamAAAResult((DIAM_AUTHRSP_S *)pMsg);
#endif
            break;
        }
        case PPP_MSG_TYPE_DDU:        /* ����NEGO�¼� */
        {
            ulRet = PPP_NegoMsgProc((UCHAR *)pMsg);
            break;
        }

        default:
        {
            break;
        }
    }

    return ulRet;
}



/*****************************************************************************
 �� �� ��  : PPP_A11MsgProc
 ��������  : A11����PPP��Ϣ������
 �������  : VOID * pMsg
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��19��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_A11MsgProc(VOID * pMsg)
{
    PPP_A11MSG_S *pstA11Msg = NULL;
    PPPINFO_S *pstPppInfo = NULL;

    if ( NULL == pMsg )
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_A11MsgProc: input para is null!");
        return ;
    }

    pstA11Msg = (PPP_A11MSG_S *)pMsg;

    GETPPPINFOPTRBYRP(pstPppInfo, pstA11Msg->ulRPIndex);

    /* ����Ѿ����������ж� */
    switch (pstA11Msg->ulMsgCode)
    {
        case PPP_MSG_CODE_LINK_DOWN:
            PPP_INNER_COUNTER(PPP_INNER_COUTNER_001);
            if(VOS_TRUE == pstA11Msg->ulLcpSendFlag)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_948);
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                             "\r\n [ppp]PPP_A11MsgProc: (VOS_TRUE == pstA11Msg->ucLcpSendFlag)");
                if(NULL != pstPppInfo)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_949);
                    /* ����releasecode��������ͳ��ԭ��ֵ */
                    PPP_PerfStatisticByReleaseCode(pstPppInfo);
                    pstPppInfo->bFailFlag = PPPA11DOWN;
                    PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
                    return;
                }
                else
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_950);
                    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                                 "\r\n [ppp]PPP_A11MsgProc: NEMC_PPPC_LINKDOWN pstPppInfo is NULL, pstA11Msg->ulL2tpType");

                    /* USM֪ͨ��ȥ�����Դ��Ҫ����Ӧ */
                    (VOID)USM_NotifyPhaseResultFunc(pstA11Msg->ulRPIndex, E_USM_MSGTYPE_PPP2USM_RELEASE, NULL);
                    return;
                }
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_951);
                if (NULL != pstPppInfo)
                {
                    pstPppInfo->bFailFlag = PPPA11DOWNNOLCPTER;
                }

                (VOID)PPP_Shell_ISLIoCtl(pstA11Msg->ulRPIndex, PPP_ISLDOWN, (CHAR *)&pstA11Msg->ulL2tpType);
            }
            break;
        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_332);
            VOS_DBGASSERT(0);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                                 "\r\n PPP_A11MsgProc: Proc A11 msg error! MsgCode[%d].",
                                 pstA11Msg->ulMsgCode);
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : PPP_AAAMsgProc
 ��������  : PPP����AAA���͵���Ϣ
 �������  : AAA_AUTHRSP_S * pMsg
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��19��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_AAAMsgProc(AAA_AUTHRSP_S * pMsg)
{
    if (NULL == pMsg)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_AAAMsgProc: input para is null!");
        return;
    }

    PPP_Shell_ReceiveAAAResult(pMsg);
    return;
}



/*****************************************************************************
 �� �� ��  : PPP_NegoMsgProc
 ��������  : PPP��Э����Ϣ����
 �������  : UCHAR *pMsg
 �������  : ��
 �� �� ֵ  : UCHAR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��19��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��7��12��
    ��    ��   : y90004478
    �޸�����   : �޸�Mbuf�Ĵ���

*****************************************************************************/
UCHAR PPP_NegoMsgProc(UCHAR *pMsg)
{
    ULONG            ulLen      = 0;
    ULONG            ulRpIndex  = 0;
    FWD_TO_CTRL_HDR *pstCtl     = NULL;
    PMBUF_S         *pstMsgTemp = NULL;
    UCHAR           *pucData    = NULL;

    if ( NULL == pMsg )
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_NegoMsgProc input para  is NULL ");
        return VOS_ERR;
    }

    pstMsgTemp = (PMBUF_S*)pMsg;

    ulLen = PMBUF_GET_TOTAL_DATA_LENGTH(pstMsgTemp);
    if (ulLen < sizeof(FWD_TO_CTRL_HDR))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_332);

        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
            "\r\n PPP_NegoMsgProc Receive Msg: Data Length(%u) is ERROR \r\n",
            ulLen);

        (VOID)PMBUF_Destroy(pstMsgTemp);
        return VOS_ERR;
    }

    pstCtl = PMBUF_MTOD(pstMsgTemp, FWD_TO_CTRL_HDR*);
    if (NULL == pstCtl)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_NegoMsgProc Receive Msg: is NULL \r\n");
        (VOID)PMBUF_Destroy(pstMsgTemp);
        return VOS_ERR;
    }

    ShowCode((UCHAR *)pstCtl, 100);

    switch (pstCtl->ulMsgCode)
    {
        case MSG_FWD_TO_CTRL_PPP_EXCP:     /*PPP��Э�̱���*/
        {
            PPP_DBG_OK_CNT(PPP_PHOK_952);

            /*�ײ��ϱ�����A10Index*/
            ulRpIndex = A11_A10GlobalIndexToA10ScIndex(pstCtl->ulPdpIndex);
            (VOID)PPP_Shell_ISLIoCtl( ulRpIndex, ISLRENEGO, NULL);
            break;
        }
        case MSG_FWD_TO_CTRL_PPP_LCP:     /*LCP*/
        case MSG_FWD_TO_CTRL_PPP_OTHER:     /*����Э�̰�*/
        {
            PPP_DBG_OK_CNT(PPP_PHOK_953_RCV_NEGO);
            (VOID)PPP_Shell_ReceiveNegoPacket(pstMsgTemp, 1);
            break;
        }
        case MSG_FWD_TO_CTRL_L2TP_IPCP_ACK:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_954);
            (VOID)PPP_L2tpIpcpMsgProc(pstMsgTemp);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_333);

            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                "\r\n [ppp]PPP_NegoMsgProc: default branch %lu!",pstCtl->ulMsgCode);
            break;
        }
    }

    /* mbuf�ظ��ͷ����⣬���Ӷ�λ��Ϣ */
    #ifndef __WIN32_PLATFORM__
    if (((pstMsgTemp->stDataBlockDescriptor.pucDataBlock) != NULL)
        && (*((ULONG *)(pstMsgTemp->stDataBlockDescriptor.pucDataBlock)) == PMBUF_FOR_HW_RELEASED))
    {
        pstCtl = (FWD_TO_CTRL_HDR *)pstMsgTemp->stDataBlockDescriptor.pucData;
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_NegoMsgProc: mbuf err! ctrlhead[%u][%u][%u][%u][%u][%u][%u][%u][%u]\r\n",
                     pstCtl->usCtrlFlag, pstCtl->usPktType,
                     pstCtl->ulDpeTimeStamp, pstCtl->ulSubIndex,
                     pstCtl->ulVcpuId, pstCtl->ulModuleId,
                     pstCtl->ulMsgCode, pstCtl->ulPdpIndex, pstCtl->ulVrfIndex);
        pucData = (UCHAR *)pstCtl + sizeof(FWD_TO_CTRL_HDR);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG, PPP_MSG_PRINT_INFO, PPP_MSG_PRINT_DATA);
    }
    #endif
    (VOID)PMBUF_Destroy(pstMsgTemp);

    return VOS_OK;
}


#define __PPP_COMP_FRAME____________

#ifdef __LINUX_PLATFORM__

/*****************************************************************************
 �� �� ��  : PPP_CompConstruct
 ��������  : ������캯��
 �������  : RTF_COMP_CONSTRUCT_STAGE_E eConstructStage
             DMS_COMMID_T myCSI
             DMS_COMMID_T myCPI
             VOID* pThis
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_CompConstruct( RTF_COMP_CONSTRUCT_STAGE_E eConstructStage,
                            DMS_COMMID_T myCSI, DMS_COMMID_T myCPI, VOID* pThis )
{
    ULONG ulRet = 0;

    switch (eConstructStage)
    {
        case RTF_COMP_CONSTRUCT_STAGE1:
            /* ��һ�׶�*/
            /* ��ʼ�������Ϣ(self csi, handle) */
            /* �����ڴ��ʼ�� */
            /* �����ڴ�/��������ʼ��, ����SG�ں�SG�� */
            /* ���г�ʼ�� */
            /* ��������/��������ڴ��ʼ�� */

            /* �ȴ������LOCAL�� */
            {
                ulRet = PGP_CompConstruct(myCSI, myCPI, &pThis);
                if (VOS_OK != ulRet)
                {
                    return VOS_ERR;
                }

                /* ��ȡ������� */
                PPP_GetSelfCompInfo(myCSI);

                ulRet = PPP_CompInit1( );

                break;
            }

        case RTF_COMP_CONSTRUCT_STAGE2:
            /* �ڶ��׶�*/
            {
                ulRet = PPP_CompInit2( );
                break;
            }
        case RTF_COMP_CONSTRUCT_STAGE3:
            /* �����׶�: ���enable, ��ƽ̨��Confirm */
            /* CRM /INST/ HAA /DVM /RMM�ص�����ע�� */
            /* CDB��RDB���á�License����� */
            {
                ulRet = PPP_CompInit3( );

                /* ע�����س�ʼ������*/
                PPP_ScheduleInit(myCPI);

                break;
            }
        default:
            /*������*/
            {
                ulRet = VOS_ERR;
                break;
            }
    }

    vos_printf("PPP_CompConstruct stage %lu, ret %lu", eConstructStage, ulRet);

    return ulRet;
}



/*****************************************************************************
 �� �� ��  : PPP_CompDestruct
 ��������  : PPP�����������
 �������  : DMS_COMMID_T myPid
             VOID* pThis
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_CompDestruct( DMS_COMMID_T myPid, VOID* pThis )
{
    vos_printf("Destruct Component PPP\r\n");
    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : PPP_CompMsgProc
 ��������  : PPP�����Ϣ������
 �������  : VOID* pMsg
             VOID* pThis
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_CompMsgProc(VOID* pMsg, VOID* pThis)
{
    VOID* pMsgBody = VOS_NULL;
    DMS_IID_T recvIId = 0;
    ULONG ulMsgType = 0;
    ULONG ulRet = VOS_OK;

    if( NULL == pMsg )
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_CompMsgProc: input para is null!");
        return VOS_ERR;
    }

    /* ��ʱ����Ϣ����*/
    recvIId = DMS_MSG_RECV_IID_GET(pMsg);
    if( VOS_IID_TMR_TIMEOUT == recvIId )
    {
        /* ����ƽ̨��װ�Ķ�ʱ����������������ҵ��ע��Ļص����� */
        PGP_CompRelTimeoutProc((VOS_MSG_TMR_RELTMR_S*)pMsg);
        return VOS_OK;
    }

    /* ��ȡDMSQ��Ϣ�� */
    pMsgBody = PGP_CompGetMsgBody(pMsg) ;

    ulMsgType = DMS_MSG_STREAMID_GET(pMsg);
    if ( ulMsgType < M_PS_MSG_TYPE_BASE ) /*������PGP����*/
    {
        /* ƽ̨��Ϣ����*/
        (VOID)PGP_CompMsgProc(pMsgBody);
    }
    else
    {
        /* ����������Ϣ�ַ����� */
        ulRet = PPP_MsgDispatch(ulMsgType, pMsgBody);
    }

    /* ƽ̨��Ϣ�ͷŴ���*/
    PGP_CompMsgRelease();

    return ulRet;
}


#endif


/*****************************************************************************
 �� �� ��  : PPP_SendRtMsg
 ��������  : ����RT��Ϣ����Ӧ���
 �������  : VOS_UINT64 ullDstCsi
             ULONG ulMsgType
             ULONG ulMsgCode
             UCHAR *pucMsg
             ULONG ulMsgLen
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : �淽
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PPP_SendRtMsg(VOS_UINT64 ullSrtCsi,VOS_UINT64 ullDstCsi, ULONG ulMsgType, ULONG ulMsgCode, UCHAR *pucMsg, ULONG ulMsgLen )
{
    ULONG ulReturn = VOS_OK;
    UCHAR *pucRtMsg = VOS_NULL;

    if ((VOS_NULL == pucMsg) ||(0 == ulMsgLen))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]PPP_SendRtMsg: input para is null!");
        return VOS_ERR;
    }

    pucRtMsg = (UCHAR*)PGP_RTDistributeAllocMsg(PPP_HANDLE, ulMsgLen);
    if (VOS_NULL == pucRtMsg)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_334);
        PPP_DebugOut( MID_PPPC, PPP_DEBUG_LOG,  "\r\n PPP_SendRtMsg:  call PGP_RTDistributeAllocMsg fail. ");
        return VOS_ERR;
    }

    VOS_MemCpy(pucRtMsg, pucMsg, ulMsgLen);
    ulReturn = PGP_RTDistributeSend(PPP_SELF_CSI,
                                   ullDstCsi,
                                   pucRtMsg,
                                   ulMsgLen,
                                   RTD_PRIORITY_MIDDLE,
                                   ulMsgType);
    if (VOS_OK != ulReturn)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_335);
        PPP_DebugOut( MID_PPPC, PPP_DEBUG_LOG,
                    "\r\n PPP_SendRtMsg:  call PGP_RTDistributeSend fail %lu. src csi %lu-%lu,dst csi %lu-%lu",
                    ulReturn,
                    AM_PRINT_64(PPP_SELF_CSI),
                    AM_PRINT_64(ullDstCsi));
        PGP_RTDistributeFreeMsg(pucRtMsg);
        return VOS_ERR;
    }

    return VOS_OK;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
