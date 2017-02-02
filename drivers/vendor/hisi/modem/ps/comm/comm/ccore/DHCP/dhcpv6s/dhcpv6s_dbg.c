/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dhcpv6_proc.c
  �� �� ��   : ����
  ��    ��   : zhoujunping
  ��������   : 2008��12��12��
  ����޸�   :
  ��������   : DHCPV6
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��12��12��
    ��    ��   : zhoujunping
    �޸�����   : ����

******************************************************************************/
#include "dhcp_inc.h"
/* add by w00316385 start */
#include "dhcpc_def.h"
/* add by w00316385 end */
#include "dhcpv6_proc.h"
#include "dhcpv6s_comp.h"
#include "dhcpv6s_dbg.h"

ULONG g_ulDhcpv6sLogRecordRegId = 0;

ULONG g_ulDHCPv6sPrintLevel = 0;  /*��������ļ���*/

/*���Լ���*/
ULONG g_ulDHCPV6SDbgCnt[E_DHCPV6S_END] = {0};

UCHAR g_ucDHCPV6SDbgCntName[][60] =
{
    "E_DHCPV6S_NULL_BUF                 ",
    "E_DHCPV6S_PROC_ERR                 ",
    "E_DHCPV6S_NULL_MSG                 ",
    "E_DHCPV6S_MALLOC_ERR               ",

    "E_DHCPV6S_MSGLEN_ERR               ",
    "E_DHCPV6S_MSGTYPE_ERR              ",
    "E_DHCPV6S_MSGCHECK_ERR             ",

    "E_DHCPV6S_PDP_INDEX_ERR            ",
    "E_DHCPV6S_GET_CONTXT_ERR           ",
    "E_DHCPV6S_SRC_ADDR_ERR             ",

    "E_DHCPV6S_REV_MS_MSG               ",
    "E_DHCPV6S_REV_INFO                 ",
    "E_DHCPV6S_REV_SOLICIT              ",
    "E_DHCPV6S_REV_REQUEST              ",
    "E_DHCPV6S_REV_REPLY                ",

    "E_DHCPV6S_ROLE_ENCAPE_ERR          ",
    "E_DHCPV6S_2_STEP                   ",
    "E_DHCPV6S_4_STEP                   ",

    "E_DHCPV6S_TRC_NULL                 ",
    "E_DHCPV6S_TRC_TYPE_ERR             ",

    "E_DHCPV6S_NO_DNS                   ",
    "E_DHCPV6S_NO_IAPD                  ",
    "E_DHCPV6S_NO_VALID_IAPD            ",
    "E_DHCPV6S_NO_PDEXCLUDE             ",

    "E_DHCPV6S_CHECKSUM_ERR             ",
    "E_DHCPV6S_MALLOC_BUFF_FAIL         ",

    "E_DHCPV6S_GTP_SEND_ERR             ",
    "E_DHCPV6S_GRE_SEND_ERR             ",
    "E_DHCPV6S_SEND_ADVERTISE_SUCC      ",
    "E_DHCPV6S_SEND_ADVERTISE_FAIL      ",
    "E_DHCPV6S_SEND_REPLY_SUCC          ",
    "E_DHCPV6S_SEND_REPLY_FAIL          ",
    "E_DHCPV6S_SEND_OTHER_SUCC          ",
    "E_DHCPV6S_SEND_OTHER_FAIL          ",

    "E_DHCPV6S_GTP_RELAY_ERR            ",
    "E_DHCPV6S_GRE_RELAY_ERR            ",
    "E_DHCPV6S_RELAY_INFO_SUCC          ",
    "E_DHCPV6S_RELAY_INFO_FAIL          ",
    "E_DHCPV6S_RELAY_REPLY_SUCC         ",
    "E_DHCPV6S_RELAY_REPLY_FAIL         ",
    "E_DHCPV6S_RELAY_OTHER_SUCC         ",
    "E_DHCPV6S_RELAY_OTHER_FAIL         ",

    "E_DHCPV6S_END                      ",
};

/* zhangjinquan ����IPV6���Դ�ӡ�������� */

VOID DHCPV6S_InitCounter()
{
    PGP_MemZero((VOID *)g_ulDHCPV6SDbgCnt, (sizeof(ULONG)*E_DHCPV6S_END));

    return;
}

VOID DHCPV6S_DbgOnOffCommand(ULONG argc, CHAR *argv[])
{
    ULONG ulSwitchFlag = 0;

    if (1 != argc)
    {
        (VOID)vos_printf( "\r\n Please input print level!" );
        return;
    }

    if (0 != VOS_StrToUint32(argv[0], &ulSwitchFlag))
    {
        (VOID)vos_printf("\r\n Please input parameter(0~4) !");
        return;
    }

    g_ulDHCPv6sPrintLevel = ulSwitchFlag % (PTM_LOG_BUTT + 1);

    (VOID)vos_printf("\r\n g_ulDHCPv6sPrintLevel = %u", g_ulDHCPv6sPrintLevel);
    return;
}

VOID DHCPV6S_ShowFailCounter(  ULONG argc, CHAR * argv [] )
{
    ULONG ulCount = 0;
    ULONG i = 0;

    if(argc >= 1)
    {
        PTM_PRINT_EXCEPTION_INFO ( "\r\n please input : dhcpv6s show counter");
        return;
    }

    for ( i = 0; i < E_DHCPV6S_END; i++)
    {
        if(0 != g_ulDHCPV6SDbgCnt[i])
        {
            ulCount++;
            PTM_PRINT_STRING_WITH_ARGUMENTS("\r\n%5u %-25s = %4u", i,g_ucDHCPV6SDbgCntName[i],g_ulDHCPV6SDbgCnt[i]);
        }
    }

    if(0 == ulCount)
    {
        PTM_PRINT_EXCEPTION_INFO("\r\n No  DHCPV6S Message Counter ");
    }

    PTM_PRINT_EXCEPTION_END(PTM_BATCH_CMD_RSP_END);

    return;
}



VOID DHCPV6S_CleanFailCommand(ULONG argc, CHAR *argv[])
{
    if(0 != argc)
    {
        OutString("\r\n please input: dhcpv6s clear fail");
        return;
    }

    DHCPV6S_InitCounter();

    return;
}

/* IPV6����������ض��� */
struct Command_S g_stDHCPv6sDebugCommand[] =
{
    {
        "print",
        "set print level (1~4: On; 0: Off.)",
        NULL,
        DHCPV6S_DbgOnOffCommand
    }
};

struct Command_S g_stDHCPv6sShowCommand[] =
{
    {
        "cnt",
        "Show cnt info",
        NULL,
        DHCPV6S_ShowFailCounter
    }
};

struct Command_S g_stDHCPv6sClearCommand[] =
{
    {
        "cnt",
        "Clear cnt info",
        NULL,
        DHCPV6S_CleanFailCommand
    }
};

struct Command_Group_S DHCPv6sDbgCmdGroup =
{
    sizeof( g_stDHCPv6sDebugCommand ) / sizeof( struct Command_S ), 11, g_stDHCPv6sDebugCommand
};

struct Command_Group_S DHCPv6sShowCmdGroup =
{
    sizeof( g_stDHCPv6sShowCommand ) / sizeof( struct Command_S ), 11, g_stDHCPv6sShowCommand
};

struct Command_Group_S DHCPv6sClrCmdGroup =
{
    sizeof( g_stDHCPv6sClearCommand ) / sizeof( struct Command_S ), 11, g_stDHCPv6sClearCommand
};

/*IPV6һ������*/
struct Command_S DHCPv6sCommand[ ] =
{
#ifndef __STARTUP_LOAD_MODE__ /* �������� */
    {"dbg",   "dhcpv6s debug info ", &DHCPv6sDbgCmdGroup, NULL},
    {"show", "show dhcpv6s info ", &DHCPv6sShowCmdGroup, NULL},
    {"clear", "clear statistics info ", &DHCPv6sClrCmdGroup, NULL},
#endif
};

struct Command_Group_S DHCPv6sDebugCmdGroup =
{
#ifndef __STARTUP_LOAD_MODE__ /* �������� */
    sizeof ( DHCPv6sCommand ) / sizeof ( DHCPv6sCommand [0] ),
    11,
    DHCPv6sCommand
#endif
};

VOID DHCPV6S_DebugCmdInit(UINT64 ul64Csi)
{
    ULONG ulRet = VOS_OK;

    ulRet = PTM_CommandsRegister ( &DHCPv6sDebugCmdGroup, "dsv6", "dhcpv6s relative debug command", ul64Csi);
    if (VOS_OK != ulRet)
    {
        VOS_Assert(0);
    }

    return;
}

VOID DHCPV6S_DebugOut_Stub(ULONG ulLevel, CHAR *pszFormat, ...)
{
    va_list ArgList = {0};
    CHAR szBuffer[512];
    CHAR *pcTmpBuf = szBuffer;

    /*lint -e746*/
    va_start(ArgList, pszFormat);
    VOS_vsprintf(pcTmpBuf, pszFormat, ArgList);
    va_end(ArgList);
    /*lint +e746*/

    if (0 != g_ulDHCPv6sPrintLevel)
    {
        (VOID)vos_printf("[DHCPV6S]: %s\r\n", szBuffer);
    }

    return;
}

VOID DHCPV6S_DebugOut(ULONG ulLevel, CHAR* pszFile, ULONG ulLineNo, CHAR *pszFuncName, CHAR *pszFormat, ...)
{
    va_list ArgList = {0};
    CHAR szBuffer[512];
    CHAR *pcTmpBuf = szBuffer;

    /* ��ֹ�������̫�� ���ڴ� */
    if ( VOS_StrLen( pszFormat ) > 400 )
    {
        /*lint +e416*/
        /*lint +e415*/
        pszFormat[400] = '\0';
        /*lint -e415*/
        /*lint -e416*/
    }


    pcTmpBuf += VOS_sprintf(pcTmpBuf, "%s: ", pszFuncName);

    va_start(ArgList, pszFormat);
    VOS_vsprintf(pcTmpBuf, pszFormat, ArgList);
    va_end(ArgList);

    if ( (1 == g_ulDHCPv6sPrintLevel && ulLevel <= PTM_LOG_ERR )
        || (1 < g_ulDHCPv6sPrintLevel ) )
    {
        (VOID)vos_printf("[%s %u]%s\r\n", pszFile, ulLineNo, szBuffer);
    }

    if (PTM_LOG_ERR >= ulLevel)
    {
    //   DBG_WriteDiagLog2SRU(g_ulDhcpv6sLogRecordRegId, ulLevel, pszFile, ulLineNo, szBuffer, ArgList);
        PTM_WriteDiagLog(g_ulDhcpv6sLogRecordRegId, ulLevel, pszFile, ulLineNo, "%s", szBuffer);
    }

    return;
}

/* BEGIN: Added by jixiaoming for  CR20120830015 at 2013-1-17 */

ULONG DHCPV6S_RegLogCnt(VOID)
{
    ULONG ulResult = VOS_OK;
    ULONG *aulCntUnit[2] = {0};

    PTM_LogCnt_RecRegInfo_S stRegInfo = {0};

    stRegInfo.ul64ComCsi = DHCPV6S_SELF_CSI;
    stRegInfo.ulComHandle = DHCPV6S_HANDLE;
    stRegInfo.ulTimeMsgType = 0;                    /* ��������ʱ��,������ֵ������ */
    stRegInfo.ulIsTimerSupport = VOS_FALSE;         /* ��ǰ���δ����ʱ����Ϣ,����ΪVOS_FALSE */
    stRegInfo.ulDBGLogRegId = g_ulDhcpv6sLogRecordRegId;

    stRegInfo.ulCntUnitNum = 1;
    stRegInfo.ppulCntAddr = aulCntUnit;

    /* ע���ӡDHCPV4C���� */
    PTM_StrNCpy(stRegInfo.aucPrefixName, "DHCPV6SCnt", PTM_LOG_CNT_PREFIX_NAME_MAX_LEN);

    aulCntUnit[0] = g_ulDHCPV6SDbgCnt;
    stRegInfo.ulTotalCntElemNum = E_DHCPV6S_END;

    ulResult = PTM_LogCnt_RecordReg(&stRegInfo);
    if (VOS_OK != ulResult)
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "call PTM_LogCnt_RecordReg fail! ulResult=%u", ulResult);
    }

    return ulResult;
}
/* END: Added by jixiaoming for CR20120830015 at 2013-1-17 */

