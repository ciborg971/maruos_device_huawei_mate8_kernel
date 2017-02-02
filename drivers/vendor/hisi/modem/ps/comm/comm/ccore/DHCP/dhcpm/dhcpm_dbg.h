#ifndef __DHCPM_DBG_H__
#define __DHCPM_DBG_H__

#define DHCPM_MAX_COUNTER_NUM 400

#ifdef __WIN32_PLATFORM__
/* add by w00316385 start */
extern VOID PTM_DebugOut_Stub(ULONG ulLevel, CHAR *pszFormat, ...);
/* add by w00316385 end */
#define DHCPM_DebugPrint PTM_DebugOut_Stub
#else
#define DHCPM_DebugPrint(level, fmt...) PTM_DebugPrint(PTM_DBG_PRINT_MODULE_DHCPM, level, ##fmt)
#endif


extern ULONG *g_pulDhcpMCountArray;

/* DHCPM�쳣��� ��������(0-199) �쳣����(200-399) */
#define DHCPM_ADD_COUNTER(Index) \
    /*lint -e774*/                     \
    if ( Index < DHCPM_MAX_COUNTER_NUM && NULL != g_pulDhcpMCountArray ) {g_pulDhcpMCountArray[Index]++;}\
    /*lint +e774*/


ULONG DHCPM_DbgInit();

#endif
