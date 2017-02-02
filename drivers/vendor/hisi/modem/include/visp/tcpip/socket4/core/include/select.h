/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              select.h
*
*  Project Code: VISP1.5
*   Module Name:   
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef     _SELECT_H
#define     _SELECT_H

#ifdef    __cplusplus
extern    "C"{
#endif

/* modified by chenbin 2000.3.6 for vrp3.0 
#define FD_SETSIZE      0x100
#define FD_SETSIZE      3072
end of modified by chenbin 2000.3.6 for vrp3.0 */

/*#define    NFDBITS        0x20
#define    NBBY        8
*/
/* modified by chenbin 2000.3.10 for vrp3.0 */
/*#define    HOWMANY(x, y)    (((x) + ((y) - 1)) / (y))*/
#define    HOWMANY(x, y)    ((x)/(y) + 1)
/* end of modified by chenbin 2000.3.10 for vrp3.0 */

/*Modified by msj 1999-8-9*/
/*#define FD_SET(n, p)    {\
            if ((n) > 0 ){\
            ((p)->fds_bits[(n)/NFDBITS] |= \
                        (((ULONG) 0x80000000) >> ((n) % NFDBITS))); \
                    }\
                    }
#define FD_CLR(n, p)    ((p)->fds_bits[(n)/NFDBITS] &= \
                       ~(((ULONG) 0x80000000) >> ((n) % NFDBITS)))
#define FD_ISSET(n, p)  ((p)->fds_bits[(n)/NFDBITS] & \
                        (((ULONG) 0x80000000) >> ((n) % NFDBITS)))
*/
/* modified by chenbin 2000.3.6 for vrp3.0 */
/*
#define FD_ZERO(p)   {                        \
                        (p)->fds_bits[0] = 0; \
                        (p)->fds_bits[1] = 0; \
                        (p)->fds_bits[2] = 0; \
                        (p)->fds_bits[3] = 0; \
                        (p)->fds_bits[4] = 0; \
                        (p)->fds_bits[5] = 0; \
                        (p)->fds_bits[6] = 0; \
                        (p)->fds_bits[7] = 0; \
                     }
*/
/*#define FD_ZERO(p)  { \
                        OS_BZero(p, sizeof(*p)); \
                    }
*/
/* end of modified by chenbin 2000.3.6 for vrp3.0 */                    

/* can we read something from so? */
#define    SOREADABLE(so) \
    ((so)->so_stRcv.sb_ulCC >= (so)->so_stRcv.sb_ulLoWat || \
    ((so)->so_sState & SS_CANTRCVMORE) || \
    (so)->so_sQLen || (so)->so_sError)

/* can we write something to so? */
/*hided by zhao biao*/
/*
#define    SOWRITEABLE(so) \
    ((ULONG)SBSPACE(&(so)->so_stSnd) >= (so)->so_stSnd.sb_ulLoWat && \
    (((so)->so_sState&SS_ISCONNECTED) || \
      ((so)->so_pProto->pr_sFlags&PR_CONNREQUIRED)==0) || \
     ((so)->so_sState & SS_CANTSENDMORE) || \
     (so)->so_sError)
*/
/*modified by zhao biao for get rid of compile warnning with vxWorks*/     
#define    SOWRITEABLE(so) \
    (((SBSPACE(&(so)->so_stSnd) >= (LONG)(so)->so_stSnd.sb_ulLoWat) && \
    (((so)->so_sState&SS_ISCONNECTED) || \
      (((so)->so_pProto->pr_sFlags&PR_CONNREQUIRED)==0))) || \
     ((so)->so_sState & SS_CANTSENDMORE) || \
     ((so)->so_sError))
/*end of modify by zhaobiao*/

typedef ULONG fd_mask;
#define    L_FD_MASK    sizeof(fd_mask)

typedef  struct tagFD_SET 
{
    /*Added by zhoushisong202096, 支持大规格SOCKET, 2013/11/7 */
#ifdef TCPIP_NOVRP_HUGE_SOCKET
    fd_mask fds_bits[4097]; /* HOWMANY(FILENUM, NFDBITS) */
#else
    fd_mask fds_bits[97]; /* HOWMANY(FILENUM, NFDBITS) */
#endif
    /* End of Added by zhoushisong202096, 2013/11/7 */
}FD_SET_S;

#define        L_FD_SET_S        sizeof(FD_SET_S);

typedef struct {
    LONG    tv_lSec;   /* seconds */
    LONG    tv_lUsec;  /* microseconds */
}TIME_VAL;
#define        L_TIME_VAL        sizeof(TIME_VAL)

LONG    GetTimeVal(TIME_VAL *);
LONG    CheckTimeVal(TIME_VAL *);
VOID    FixTimeVal(TIME_VAL *);
LONG    CmpTimeVal(TIME_VAL *,TIME_VAL *,TIME_VAL *,TIME_VAL *);
VOID    SelRecord (TCB_S *, SELINFO_S *,LONG );
/* modified by chenbin 2000.3.6 for vrp3.0 */
/*LONG    SelScan(TCB_S *,FD_SET_S *, FD_SET_S *,LONG,LONG *);*/
LONG    SelScan(TCB_S *,FD_SET_S **, LONG *, FD_SET_S **,LONG,LONG *);
/* end of modified by chenbin 2000.3.6 for vrp3.0 */
VOID    DelSelFlag(TCB_S *);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */


#endif
