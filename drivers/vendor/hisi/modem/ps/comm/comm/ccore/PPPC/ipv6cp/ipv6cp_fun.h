


#ifndef      _IPV6CP_FUNC_H_
#define      _IPV6CP_FUNC_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

/* 接口函数 */
VOID PPP_IPV6CP_Init(PPPINFO_S *, USHORT *, USHORT *) ;
VOID PPP_IPV6CP_ReceiveEventFromCore (VOID *, ULONG , char *) ;
VOID PPP_IPV6CP_ReceivePacket (VOID *, UCHAR* , UCHAR* , ULONG ) ;

/* 回调函数 */
VOID PPP_IPV6CP_resetci(PPPFSM_S *f) ;
USHORT PPP_IPV6CP_cilen(PPPFSM_S *) ;
VOID PPP_IPV6CP_addci(PPPFSM_S *, UCHAR *) ;
USHORT PPP_IPV6CP_ackci(PPPFSM_S *, UCHAR *, ULONG) ;
USHORT PPP_IPV6CP_nakci(PPPFSM_S *, UCHAR *, ULONG) ;
USHORT PPP_IPV6CP_rejci(PPPFSM_S *, UCHAR *, ULONG) ;
UCHAR PPP_IPV6CP_reqci(PPPFSM_S *, UCHAR *, ULONG *) ;
VOID PPP_IPV6CP_up(PPPFSM_S *) ;
VOID PPP_IPV6CP_down(PPPFSM_S *) ;
VOID PPP_IPV6CP_finished(PPPFSM_S *) ;
VOID PPP_IPV6CP_starting(PPPFSM_S *) ;

/* 内部函数 */
ULONG PPP_IPV6CP_UpResetCi(PPPINFO_S *) ;
ULONG PPP_ipv6_intfid_check(USHORT *pstIpv6addr, ULONG ullen);

extern VOID PPP_IPV6CP_Pactket_Proc(PPPINFO_S *pstPppInfo,
                                         UCHAR*     pHead,
                                         UCHAR*     pPacket,
                                         ULONG      ulLen);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _IPV6CP_FUNC_H_ */





