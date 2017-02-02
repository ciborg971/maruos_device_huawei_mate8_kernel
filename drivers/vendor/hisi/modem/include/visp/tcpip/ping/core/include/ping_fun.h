/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ping_fun.h
*
*  Project Code: VISP1.5
*   Module Name: ping
*  Date Created: 2002-8-20
*        Author: fu jibin
*   Description: ����PING6�û��ĺ���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2002-8-20  fu jibin          Creat the first version.
*  2006-04-27  luyao            ���ݱ�̹淶�����ļ����й淶������
*
*******************************************************************************/


/* Defect id BYAD01452 - Modified by Suraj 21st Oct 2003.
#if (VRP_MODULE_IPV6 == VRP_YES)*/

#ifndef _PING_FUNC_H_
#define _PING_FUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

/*�ص�������Ҫ�������������Ϣ*/
extern PING_CALLBACK_SET_S   g_stPingCallBackFunction;
/*AM4����������*/
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl         * g_pstPingAM4ComFunTable;

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05   */
/* VRF ģ�鹦�����ָ�� */
extern struct IIF_VRF_ComIntFUNVtbl                 *g_pstPingVrfComFunTable ;
/* End:VISP1.7C03 VRF wangchengyang,2009-02-05   */

extern struct IIF_VRF6_ComIntFUNVtbl                 *g_pstPingVrf6ComFunTable ;

extern struct IIF_IP6_ND_COMMONVtbl            *g_pstIpv6NDCommonPingVtbl ;

/* Global pointer for the Address Management Component Vtable*/

#define PING_TIMELEFT(ulCurrentTime,ulTimeStart,ulTimeInterval,ullastTime,ulTimeShift,ulTimeLeft)\
{\
    (ulCurrentTime) = PIN_Timer_Read ( );\
    /* modified by chenxia for BYDD04024, 2004/02/27  \
    if ( (ulCurrentTime) < (ulTimeStart) )\
    { \
       (ulTimeInterval) = ( ULONG )( ( double )(ulCurrentTime) + \
           ( 4.294967295e+9 ) - ( double )(ulTimeStart) ); \
    } \
    */ \
    if ( (ulCurrentTime) < (ullastTime) )\
    { \
       (ulTimeInterval) = ( ULONG )( (ulCurrentTime) + \
           ( ( PIN_MAXTIME ) - (ullastTime) ) ); \
       (ullastTime) = (ulCurrentTime); \
    } \
    else \
    { \
       (ulTimeInterval) = (ulCurrentTime) - (ullastTime); \
       (ullastTime) = (ulCurrentTime); \
    } \
    \
    (ulTimeShift)+= (ulTimeInterval); \
    (ulTimeLeft) -= (ulTimeInterval); \
    if ( ( LONG )(ulTimeLeft) <= 0 ) \
    { \
        (ulTimeLeft)=0; \
    } \
}

#define PIN_CHECKFORDF(Ping4_usDF) ((1 == Ping4_usDF) ? PIN_IP_HEADLEN : 0 )

 /* PINGģ����IP6��ص��齨���ܽӿ�  */
extern struct  IIF_IP6_ADDR_ComIntFunVtbl   *g_pstIP6PingV6AddrFunTable;
LONG PING_Ping ( ULONG ulExecID, Ping6Param_S  *pPing6Param);
VOID PING_Pinger ( Ping6Param_S * pstPing6Param, ULONG ulExecID );
LONG PING_PrintPacket ( Ping6Param_S * pstPing6Param, CHAR * pcBuf, LONG lRecvLen,SOCKADDR_IN6_S *  pstFrom, ULONG ulSendSeq, ULONG ulExecID );
LONG PING_Get_HopLim(msghdr * pstRecvMsg);

/*Modified by dengxiong for D00173*/
LONG PING_DoPing(ULONG ulExecID, Ping_Comm_S  *stPingParam);
VOID PIN_Finish ( PingParam_S *, ULONG );

LONG PIN_Ping ( ULONG ulExecID, PingParam_S  *stPingData);
/*Modified by zhongyu206043, �޸ķ���ֵΪULONG�ͣ�֧��ping����DF��ʶ for S.PING.1.1, 2012/8/18 */
LONG PIN_Pinger ( PingParam_S *, ULONG );
/*End of Modified by zhongyu206043, 2012/8/18 */
LONG PIN_PrintPacket ( PingParam_S * , CHAR * , LONG , struct sockaddr_in * ,ULONG ,ULONG ,ULONG);
CHAR * PIN_PrintAddr ( PingParam_S * , ULONG, CHAR* );
USHORT PIN_InCksum ( USHORT * , LONG );
LONG  PIN_Fill ( PingParam_S * , CHAR * ,ULONG);
VOID PIN_PrintIcmph ( ICMP_S *, ULONG );

CHAR * PIN_NToA(ULONG ulAddr,CHAR szStrAddr[LEN_128]);

extern TCPIP_PINGOutput_HOOK_FUNC g_pstPINGOutputHook;
extern TCPIP_PINGSTAT_HOOK_FUNC g_pfPingStatOutputHook;
VOID TCPIP_PINOutput(CHAR *szBuf);
VOID TCPIP_PINOutputEx(CHAR *szBuf,ULONG ulExecID);
ULONG PING_SetTos(UCHAR ucTos);
ULONG PING_GetTos(UCHAR *pucTos);
LONG PIN_CheckAndSetParam( PingParam_S *stPingParam ,PingParam_S *pstPingData);

extern LONG isxdigit(CHAR);
/* End added */

#ifdef __cplusplus
}
#endif

#endif  /*end of _PING6_FUNC_H_*/

/* Defect id BYAD01452 - Modified by Suraj 21st Oct 2003.
#endif */



