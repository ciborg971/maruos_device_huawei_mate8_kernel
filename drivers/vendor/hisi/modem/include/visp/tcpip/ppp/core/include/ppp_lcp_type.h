/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                             ppp_lcp_type.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPP
 *  Date Created: 2000-04-04
 *        Author: DengYiou
 *   Description: PPP��LCPЭ�鴦��ģ�����ݽṹ
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000-04-04      DengYiou        Create
 *  2004-07-01      YiAn            Modified for VISP
 *  2006-03-31      ZhuKun          Adjust for D00661
 *  2006-04-21      ZhuKun          Adjust for D00875
 *  2006-05-11      luyao           Ϊ֧��ARM CPU�ֽڶ������ԣ��޸Ľṹ��
 *
 ************************************************************************/

#ifndef _LCP_TYPE_H_
#define _LCP_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ppp/include/ppp_api.h"

/* LCPЭ��ѡ�� */
#define LCP_CI_MRU              1   /* Maximum Receive Unit */
#define LCP_CI_ASYNCMAP         2   /* Async Control Character Map */
#define LCP_CI_AUTHTYPE         3   /* Authentication Type */
#define LCP_CI_QUALITY          4   /* Quality Protocol */
#define LCP_CI_MAGICNUMBER      5   /* Magic Number */
#define LCP_CI_PCOMPRESSION     7   /* Protocol Field Compression */
#define LCP_CI_ACCOMPRESSION    8   /* Address/Control Field Compression */
#define LCP_CI_MRRU             17  /* MRRU */
#define LCP_CI_SSNHF            18  /* Short Sequence Number Header Format */
#define LCP_CI_DISCR            19  /* Endpoint Discriminator */
#define LCP_CI_CALLBACK         13  /* Callback */
#define LCP_CI_MHF              27  /* MHF */
#define LCP_CI_PREFIXE          26  /* PREFIX-ELISION */
/* End of addition */
/***************/


/* LCP�Զ������� */
#define ECHOREQ         9   /* Echo Request */
#define ECHOREP         10  /* Echo Reply */
#define DISCREQ         11  /* Discard Request */
#define IDENTIFIC       12  /* Identification */
#define TIMEREMAIN      13  /* Time remaining */
/*****************/

/* ���ڶ�Ӧg_cPPP_Debug_LcpOption�еĵ�Ԫ */
#define LCP_TYPENAMEINDEX_MRRU        9        /* the index of LCP CI MRRU */
#define LCP_TYPENAMEINDEX_SSNHF       10       /* the index of LCP CI SSNHF */
#define LCP_TYPENAMEINDEX_DISCR       11       /* the index of LCP CI DISCR */
#define LCP_TYPENAMEINDEX_CALLBACK    12       /* the index of LCP CI CALLBACK */
#define LCP_TYPENAMEINDEX_MHF         13       /* the index of LCP CI MHF */
#define LCP_TYPENAMEINDEX_PREFIXE     14       /* the index of LCP CI PREFIX-ELISION */
/* End of addition */

#define LCP_MAGICNUM_LEN              4        /* the magic number length */
#define LCP_DISCREQ_LEN               12       /* special discard request frame length */

/* ��Э��ѡ��� */
#define PPP_CILEN_CHAP      5   /* PPP_CILEN_VOID + sizeof(short) + 1 */
#define PPP_CILEN_LQR       8   /* PPP_CILEN_VOID + sizeof(short) + sizeof(long) */
#define PPP_CILEN_DISCR     3   /* PPP_CILEN_VOID + Class. (also the minimum length of Discriminator) */
#define PPP_CILEN_CALLBACK  3   /* PPP_CILEN_VOID + Operation. (also the minimum length of callback) */
/******************/


/* ��ȡЭ��ѡ���(cilen)�� */
#define PPP_LENCICHAP(neg)   (neg ? PPP_CILEN_CHAP : 0)
#define PPP_LENCILQR(neg)    (neg ? PPP_CILEN_LQR : 0)
#define PPP_LENCIDISCR(neg)  (neg ? pstGotOptions->discr_len : 0)
#define PPP_LENCALLBACK(neg) (neg ? pstGotOptions->callbacklen : 0)
#define PPP_LENCIPREFIXE(neg) (neg ? pstGotOptions->ucPrefixELen : 0)
/* End of addition */
/*****************************/

/******** �غ�ѡ�� *********/
#define CB_USER_AUTH        0
#define CB_DIALING_STRING   1
#define CB_LOCATION_ID      2
#define CB_E_164            3
#define CB_DIST_NAME        4
/******** �غ�ѡ�� *********/

/******** �ն����������� *********/
#define LCP_DISCR_NULL          0x00
#define LCP_DISCR_LOCASSIGN     0x01
#define LCP_DISCR_IPADDR        0x02
#define LCP_DISCR_MACADDR       0x03
#define LCP_DISCR_MAGICNUM      0x04
#define LCP_DISCR_TELENUM       0x05
#define LCP_DISCR_ANY           0xff
/******** �ն����������� *********/


/* Э��ʧ�ܺ�,��LCP down�� */
#define PPP_LCP_NegotiationDown(pLcpInfo) \
    if (pLcpInfo)\
    { \
      /* ��LCP����Close�¼�,���ɽ���Э��  */ \
      PPP_LCP_ReceiveEventFromCore(pLcpInfo, (ULONG)PPP_EVENT_FSM_CLOSE, NULL); \
    }


/* ������֧�ֵ�����ǰ׺ʡ��ӳ����䵽������ */
#define PPP_PUTPREFIXE(astPrefixE, pPacket,len)\
{ \
    MC_PREFIXE_S *pstPrefixE = NULL;\
    UCHAR         i = 0;\
    UCHAR        *pPacketTemp = NULL;\
    PPP_PUTCHAR( LCP_CI_PREFIXE, pPacket );\
    /* ��¼�����д��ѡ��ȵ�λ�ã��Ⱥ���������Ӧ��ѡ���ܳ��Ⱥ���������ֽ� */\
    pPacketTemp = pPacket;\
    PPP_INCPTR(1, pPacket);\
    for ( i = 0; i < MC_PREFIXE_MAX_NUM; i++ )\
    {\
        pstPrefixE = &(astPrefixE[i]);\
        if ( pstPrefixE->ucIsUsedFlag )\
        {\
            PPP_PUTCHAR( pstPrefixE->ucClass, pPacket );\
            PPP_PUTCHAR( pstPrefixE->ucPrefixELen, pPacket );\
            (VOID)TCPIP_Mem_Copy( pPacket, pstPrefixE->ucPrefixELen, pstPrefixE->aucPrefixE, pstPrefixE->ucPrefixELen );\
            PPP_INCPTR( pstPrefixE->ucPrefixELen, pPacket );\
            /* ǰ׺�ܳ��� += ǰ׺�ȼ�+ǰ׺����+ǰ׺�ֶ� */\
            len = (UCHAR)( len + pstPrefixE->ucPrefixELen + PPP_CILEN_VOID );\
        }\
    }\
    /* ����ѡ���:ѡ���ܳ��� = ѡ������+ѡ���+ǰ׺�ܳ��� */\
    len = (UCHAR)(len + PPP_CILEN_VOID);\
    /* �ڱ���������ѡ��� */\
    PPP_PUTCHAR( len, pPacketTemp ); \
}
/* End of addition */

/* ���Э��ѡ��(addci)�� */
#define ADDCIVOID(opt, neg) \
    if (neg)\
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(PPP_CILEN_VOID, pPacket); \
    }
#define ADDCISHORT(opt, neg, val) \
    if (neg)\
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(PPP_CILEN_SHORT, pPacket); \
        PPP_PUTSHORT(val, pPacket); \
    }
#define ADDCICHAP(opt, neg, val, digest) \
    if (neg) \
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(PPP_CILEN_CHAP, pPacket); \
        PPP_PUTSHORT(val, pPacket); \
        PPP_PUTCHAR(digest, pPacket); \
    }
#define ADDCILONG(opt, neg, val) \
    if (neg) \
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(PPP_CILEN_LONG, pPacket); \
        PPP_PUTLONG(val, pPacket); \
    }
#define ADDCILQR(opt, neg, val) \
    if (neg) \
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(PPP_CILEN_LQR, pPacket); \
        PPP_PUTSHORT((USHORT)PPP_LQR, pPacket); \
        PPP_PUTLONG(val, pPacket); \
    }

#define ADDCIDISCR(opt, neg, classno, discr_len, addr ) \
    if(neg) \
    { \
        int     i; \
        UCHAR  *pAddr; \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(discr_len, pPacket); \
        PPP_PUTCHAR(classno, pPacket); \
        pAddr = (UCHAR *)addr; \
        for( i = 0; i < discr_len - 3; i++ ) \
        { \
            PPP_PUTCHAR( pAddr[ i ], pPacket ); \
        } \
    }

#define ADDCICALLBACK(opt, neg, val1, val2, ulLen)\
    if(neg) \
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(ulLen, pPacket); \
        PPP_PUTCHAR(val1, pPacket); \
        if ((ulLen - 3) > 0) \
        { \
            (VOID)TCPIP_Mem_Copy((char *)pPacket, ulLen - 3, (char *)val2, ulLen - 3); \
        } \
        pPacket += (ulLen - 3); \
    }

#define ADDCIMHF( opt, neg, mhfcode, mhfclass ) \
    if (neg)\
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(PPP_CILEN_SHORT, pPacket); \
        PPP_PUTCHAR(mhfcode, pPacket);\
        PPP_PUTCHAR(mhfclass, pPacket);\
    }

/* Req������Prefix-Elisionѡ���ʽ */
/* ��ʽ1:
   0                 16                     
   +++++++++++++++++++
   |  Type  | Length | 
   +++++++++++++++++++
   ��ʽ2:
   0                 16                  32    
   ++++++++++++++++++++++++++++++++++++++++
   |  Type  | Length | Class | PrefixELen |
   ----------------------------------------
   |  Prefix-E field ....                 |
   ----------------------------------------
   |                 ....                 |
   ++++++++++++++++++++++++++++++++++++++++
*/
#define ADDCIPREFIXE( opt, neg, astPrefixE, prefixElen )\
    if (neg)\
    { \
        /* ����¼��ѡ�����0 */\
        prefixElen = 0;\
        /* ��REQ���������Prefix-Elisionѡ�� */\
        PPP_PUTPREFIXE(astPrefixE, pPacket, prefixElen);\
    }
/* End of addition */  
/******************************/


/* ����NAK���ĵ�ѡ��(nakci)�� */
#define NAKCIVOID(opt, neg, code) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_VOID) && \
        (PPP_CILEN_VOID == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_VOID; \
        PPP_INCPTR(PPP_CILEN_VOID, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCICHAP(opt, neg, code) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_CHAP) && \
        (PPP_CILEN_CHAP == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_CHAP; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        PPP_GETCHAR(cichar, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCISHORT(opt, neg, code) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_SHORT) && \
        (PPP_CILEN_SHORT == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_SHORT; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCILONG(opt, neg, code) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_LONG) && \
        (PPP_CILEN_LONG == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_LONG; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCILQR(opt, neg, code) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_LQR) && \
        (PPP_CILEN_LQR == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_LQR; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCIDISCR(opt, neg, code) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_DISCR) && \
        (pPacket[0] == opt) ) \
    { \
        UCHAR ucTempLen = pPacket[1]; \
        ulLen -= pPacket[1]; \
        PPP_INCPTR(3, pPacket); \
        if ((ucTempLen > 3) && ((ucTempLen-3) <= PPP_MP_DISCR_MAX_LENGTH))\
        {\
        (VOID)TCPIP_Mem_Copy((char *)(stNoOption.discr_addr), (ULONG)(ucTempLen - 3), (char *)pPacket, (ULONG)(ucTempLen - 3)); \
        }\
        else\
        {\
            goto bad;\
        }\
        stNoOption.neg = 1; \
        code \
    }
#define NAKCICALLBACK(opt, neg) \
    if ( pstGotOptions->neg && \
        (ulLen >= pstGotOptions->callbacklen) && \
        (pPacket[0] == opt) && \
        (pPacket[1] == pstGotOptions->callbacklen) )\
    {\
        ulLen = (ULONG )(ulLen - pstGotOptions->callbacklen); \
        PPP_INCPTR(2, pPacket);\
        PPP_GETCHAR(cichar, pPacket);\
        stTryOption.callbackopr = cichar; \
        (VOID)TCPIP_Mem_Copy((char *)(stTryOption.callbackinfo), (ULONG)(pstGotOptions->callbacklen - 3), (char *)pPacket, (ULONG)(pstGotOptions->callbacklen - 3)); \
        stNoOption.neg = 1;\
    }
#define NAKCIMHF(opt, neg, mhfcode, mhfclass) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_SHORT && \
        PPP_CILEN_SHORT == pPacket[1] && opt == pPacket[0] ) \
    { \
        ulLen -= PPP_CILEN_SHORT; \
        PPP_INCPTR(PPP_CILEN_VOID, pPacket); \
        PPP_GETCHAR(ucCode, pPacket); \
        PPP_GETCHAR(ucClass, pPacket); \
        /* ����Զ�ֻNAK���˵�classֵ�������classֵ��0~����ϣ��Э�̵�classֵ֮�䣬\
           ����ܶԶ�NAK��ֵ */ \
        if ( ucCode == pstWantOptions->ucMhfCode )\
        {\
            if(ucClass > 0 && ucClass <= pstWantOptions->ucMhfClass)\
            {\
                stTryOption.ucMhfCode = ucCode; \
                stTryOption.ucMhfClass = ucClass; \
            }\
            else\
            {\
                stTryOption.neg = 0;\
            }\
        }\
        /* ����Զ�NAK�˱���code��classֵ�����code�Ϸ�����class����Ӧ����ķ�Χ�ڣ�\
           ����ܶԶ�NAK��ֵ */ \
        else if ( MC_LSN_CODE == ucCode )\
        {\
            if(ucClass > 0 && ucClass <= MC_MAX_LSCLASS)\
            {\
                stTryOption.ucMhfCode = ucCode;\
                stTryOption.ucMhfClass = ucClass; \
            }\
            else\
            {\
                stTryOption.neg = 0;\
            }\
        }\
        else if ( MC_SSN_CODE == ucCode )\
        {\
            if(ucClass > 0 && ucClass <= MC_MAX_SSCLASS)\
            {\
                stTryOption.ucMhfCode = ucCode;\
                stTryOption.ucMhfClass = ucClass; \
            }\
            else\
            {\
                stTryOption.neg = 0;\
            }\
        }\
        else\
        {\
            stTryOption.neg = 0;\
        }\
        stNoOption.neg = 1; \
    }

/* Nak������Prefix-Elisionѡ���ʽ */
/* ��ʽ1:
   0                 16                     
   +++++++++++++++++++
   |  Type  | Length | 
   +++++++++++++++++++
   ��ʽ2:
   0                 16                  32    
   ++++++++++++++++++++++++++++++++++++++++
   |  Type  | Length | Class | PrefixELen |
   ----------------------------------------
   |  Prefix-E field ....                 |
   ----------------------------------------
   |                 ....                 |
   ++++++++++++++++++++++++++++++++++++++++
*/
#define NAKCIPREFIXE(opt, neg) \
    if ( pstGotOptions->neg \
         && opt == pPacket[0] \
         && pPacket[1] >= PPP_CILEN_VOID \
         && ulLen >= pPacket[1] ) \
    { \
        MC_PREFIXE_S *pstPrefixEInfo = NULL; \
        UCHAR         ucCIClass = 0; \
        UCHAR         ucCIPreELen = 0; \
        /* ��NAK���������ǽ��ܵ�ǰ׺ʡ��ӳ����� */\
        UCHAR         ucPrefixESum = 0;\
        /* ��ȡѡ��� */\
        cilen = pPacket[1]; \
        ulLen -= cilen;\
        /* ѡ��ȼ�ȥ���ͺͳ���ռ�������ֽ� */\
        cilen -= PPP_CILEN_VOID;\
        PPP_INCPTR( PPP_CILEN_VOID, pPacket ); \
        /* ���ĸ�ʽ1,��Ϊ�ܾ���ѡ����´β���Э�̸�ѡ�� */\
        if ( 0 == cilen )\
        {\
            stTryOption.neg_prefixE = 0;\
        }\
        /* ���ĸ�ʽ2 */\
        else\
        {\
            while ( cilen >= PPP_CILEN_VOID ) \
            { \
                PPP_GETCHAR( ucCIClass, pPacket );\
                PPP_GETCHAR( ucCIPreELen, pPacket );\
                /* ʣ��ѡ��� - �ȼ��ͳ�����ռ���ֽ� - ǰ׺ʡ���ֶγ��� */\
                if ((cilen = (SHORT)(cilen - ucCIPreELen - PPP_CILEN_VOID)) < 0)\
                    goto bad;\
                if ( ucCIClass < MC_PREFIXE_MAX_NUM \
                     && ucCIPreELen > 0\
                     && ucCIPreELen <= MC_PREFIXE_MAX_STR \
                   )\
                {\
                    ucPrefixESum++;\
                    pstPrefixEInfo = &(stTryOption.pstPrefixE[ucCIClass]); \
                    pstPrefixEInfo->ucIsUsedFlag = PREFIX_E_IS_USED; \
                    pstPrefixEInfo->ucClass = ucCIClass;\
                    pstPrefixEInfo->ucPrefixELen = ucCIPreELen;\
                    (VOID)TCPIP_Mem_Copy( pstPrefixEInfo->aucPrefixE, MC_PREFIXE_MAX_STR, pPacket, ucCIPreELen );\
                }\
                /* �ƶ�����ָ�룬������һ���ȼ���ǰ׺ʡ�ԣ�\
                   ����õȼ���ʡ���ֶγ��Ȳ��ڱ�������Χ�ڣ���NAK��ǰ׺����Ϊ0��\
                   Ҳֱ�ӽ�����һ���ȼ���ǰ׺ʡ�� */\
                PPP_INCPTR( ucCIPreELen, pPacket );\
            }\
            if ( cilen != 0 )\
            {\
                goto bad;\
            }\
            /* ���NAK�����е�ֵ�������ϱ���Ҫ��(������û�н����κ�һ��NAKֵ)��\
               ����Ϊ�ܾ���ѡ���,�´β���Э�̸�ѡ�� */\
            if ( 0 == ucPrefixESum )\
            {\
                stTryOption.neg_prefixE = 0;\
            }\
        }\
        stNoOption.neg_prefixE = 1; \
    }
 /* End of addition */
/******************************/


/* ����REJ���ĵ�ѡ��(rejci)�� */
#define REJCIVOID(opt, neg) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_VOID) && \
        (PPP_CILEN_VOID == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_VOID; \
        PPP_INCPTR(PPP_CILEN_VOID, pPacket); \
        stTryOption.neg = 0; \
    }

#define REJCISHORT(opt, neg, val) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_SHORT) && \
        (PPP_CILEN_SHORT == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_SHORT; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        /* Check rejected value. */ \
        if (cishort != val) \
        { \
            goto bad; \
        } \
        stTryOption.neg = 0; \
    }

#define REJCICHAP(opt, neg, val, digest) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_CHAP) && \
        (PPP_CILEN_CHAP == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_CHAP; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        PPP_GETCHAR(cichar, pPacket); \
        /* Check rejected value. */ \
        if ((cishort != val) || (cichar != digest)) \
        { \
            goto bad; \
        } \
        stTryOption.neg = 0; \
        /*��chapѡ���ʱ��һ��papѡ�������*/\
    }

#define REJCILONG(opt, neg, val) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_LONG) && \
        (PPP_CILEN_LONG == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_LONG; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        /* Check rejected value. */ \
        if (cilong != val) \
        { \
            goto bad; \
        } \
        stTryOption.neg = 0; \
    }

#define REJCILQR(opt, neg, val) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_LQR) && \
        (PPP_CILEN_LQR == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_LQR; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        /* Check rejected value. */ \
        if ((cishort != PPP_LQR) || (cilong != val)) \
        { \
            goto bad; \
        } \
        stTryOption.neg = 0; \
    }

#define REJCIDISCR(opt, neg, classno, discr_len, addr ) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_DISCR) && \
        (pPacket[1] == discr_len) && (pPacket[0] == opt) && (pPacket[2] == classno) ) \
    { \
        LONG lNotEqual = 0; \
        ulLen -= discr_len; \
        PPP_INCPTR(PPP_CILEN_DISCR, pPacket); \
        (VOID)VOS_Mem_Cmp((VOID*)pPacket, (VOID*)addr, (VOS_UINT32)(discr_len - PPP_CILEN_DISCR), &lNotEqual); \
        PPP_INCPTR((ULONG)(discr_len - PPP_CILEN_DISCR), pPacket); \
        if(lNotEqual) \
        { \
            goto bad; \
        } \
        stTryOption.neg = 0; \
    }
#define REJCICALLBACK(type, neg, cb_len, cb_opr, cb_msg)\
    if(pstGotOptions->neg && (pPacket[0] == type) && (pPacket[1] == cb_len))\
    {\
        ulLen = (ULONG )(ulLen - cb_len); \
        PPP_INCPTR(2, pPacket); \
        PPP_GETCHAR(cichar, pPacket);\
        if(cichar != cb_opr) \
        { \
            goto bad; \
        } \
        if(cb_len - PPP_CILEN_CALLBACK)\
        { \
            LONG lNotEqual = 0; \
            (VOID)VOS_Mem_Cmp((VOID*)cb_msg, (VOID*)pPacket, (VOS_UINT32)(cb_len - PPP_CILEN_CALLBACK), &lNotEqual); \
            PPP_INCPTR((ULONG)(cb_len - PPP_CILEN_CALLBACK), pPacket); \
            if(lNotEqual) \
            { \
                goto bad; \
            } \
        } \
        stTryOption.neg = 0; \
    }
#define REJCIMHF(opt, neg, mhfcode, mhfclass) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_SHORT \
        && PPP_CILEN_SHORT == pPacket[1] && pPacket[0] == opt)\
    { \
        ulLen -= PPP_CILEN_SHORT; \
        PPP_INCPTR(PPP_CILEN_VOID, pPacket); \
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != mhfcode) \
        {\
            goto bad; \
        }\
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != mhfclass) \
        {\
            goto bad; \
        }\
        stTryOption.neg = 0; \
        stTryOption.ucMhfCode = 0; \
        stTryOption.ucMhfClass = 0;\
    }

/* Rej������Prefix-Elisionѡ���ʽ */
/* ��ʽ1:
   0                 16                     
   +++++++++++++++++++
   |  Type  | Length | 
   +++++++++++++++++++
   ��ʽ2:
   0                 16                  32    
   ++++++++++++++++++++++++++++++++++++++++
   |  Type  | Length | Class | PrefixELen |
   ----------------------------------------
   |  Prefix-E field ....                 |
   ----------------------------------------
   |                 ....                 |
   ++++++++++++++++++++++++++++++++++++++++
*/
#define REJCIPREFIXE(opt, neg)\
    if ( pstGotOptions->neg && opt == pPacket[0] \
         && pPacket[1] >= PPP_CILEN_VOID && ulLen >= pPacket[1] ) \
    { \
        LONG  lRet = 0;\
        UCHAR ucCiLenTemp = 0;\
        UCHAR aucBufTemp[LEN_256] = {0};\
        UCHAR *pucRejPacket = NULL;\
        pucRejPacket = aucBufTemp;\
        cichar = pPacket[1];\
        ulLen -= (ULONG)cichar;\
        /* ��ʱ��װһ��Prefix-Elisionѡ���REQ���� \
          (������ʱ������֮ǰ���͵�REQ�е�Prefix-Elisonѡ������һ��) \
           �Դ��ж�REJ������Prefix-Elisionѡ��������Ƿ��REQ�����е�һ�� */ \
        PPP_PUTPREFIXE(pstGotOptions->pstPrefixE, pucRejPacket, ucCiLenTemp);\
        /* ���ѡ��ȾͲ�������ʱ�����REQ���ĵ�ѡ��ȣ���ֱ����Ϊ�Ƿ����� */ \
        if ( cichar != ucCiLenTemp ) \
        {\
            goto bad; \
        }\
        /* �Ƚ�ACK�����еĸ�ѡ�������Ƿ����ʱ�����REQ�����е�һ�� */\
        (VOID)VOS_Mem_Cmp( (VOID*)pPacket, (VOID*)aucBufTemp, (VOS_UINT32)cichar, &lRet );\
        if ( lRet )\
        {\
            goto bad; \
        }\
        /* REJ�����еĴ�ѡ�������ȷ������ָ����һ��ѡ�� */ \
        PPP_INCPTR( cichar, pPacket );\
        stTryOption.neg = 0;\
    }
/* End of addition */
/******************************/


/* ����ACK���ĵ�ѡ��(ackci)�� */
#define ACKCIVOID(opt, neg) \
    if (neg) \
    { \
        if ((LONG)(ulLen -= PPP_CILEN_VOID) < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if ((cilen != PPP_CILEN_VOID) || (citype != opt)) \
        { \
            goto bad; \
        } \
    }
#define ACKCISHORT(opt, neg, val) \
    if (neg) \
    { \
        if ((LONG)(ulLen -= PPP_CILEN_SHORT) < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if ((cilen != PPP_CILEN_SHORT) || (citype != opt)) \
        { \
            goto bad; \
        } \
        PPP_GETSHORT(cishort, pPacket); \
        if (cishort != val) \
        { \
            goto bad; \
        } \
    }
#define ACKCICHAP(opt, neg, val, digest) \
    if (neg) \
    { \
        if ((LONG)(ulLen -= PPP_CILEN_CHAP) < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if ((cilen != PPP_CILEN_CHAP) || (citype != opt)) \
        { \
            goto bad; \
        } \
        PPP_GETSHORT(cishort, pPacket); \
        if (cishort != val) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != digest) \
        { \
            goto bad; \
        } \
    }
#define ACKCILONG(opt, neg, val) \
    if (neg) \
    { \
        if ((LONG)(ulLen -= PPP_CILEN_LONG) < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if ((cilen != PPP_CILEN_LONG) || (citype != opt)) \
        { \
            goto bad; \
        } \
        PPP_GETLONG(cilong, pPacket); \
        if (cilong != val) \
        { \
            goto bad; \
        } \
    }
#define ACKCILQR(opt, neg, val) \
    if (neg) \
    { \
        if ((LONG)(ulLen -= PPP_CILEN_LQR) < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if ((cilen != PPP_CILEN_LQR) || (citype != opt)) \
        { \
            goto bad; \
        } \
        PPP_GETSHORT(cishort, pPacket); \
        if (cishort != PPP_LQR) \
        { \
            goto bad; \
        } \
        PPP_GETLONG(cilong, pPacket); \
        if (cilong != val) \
        { \
            goto bad; \
        } \
    }
#define ACKCIDISCR(opt, neg, classno, discr_len, addr ) \
    if(neg) \
    { \
        UCHAR  *pAddr; \
        int     i; \
        if ((LONG)(ulLen -= (discr_len)) < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if ((cilen != (discr_len)) || (citype != opt)) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != classno ) \
        { \
            goto bad; \
        } \
        pAddr = (UCHAR *)addr; \
        for( i = 0; i < discr_len - PPP_CILEN_DISCR; i++ ) \
        { \
            PPP_GETCHAR(cichar, pPacket); \
            if( pAddr[ i ] != cichar ) \
            { \
                goto bad; \
            } \
        } \
    }
#define ACKCALLBACK(opt, neg, val1, val2, val3) \
    if(neg) \
    { \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if((cilen != val3) || (citype != opt))\
        { \
            goto bad; \
        } \
        ulLen = (ULONG)(ulLen - cilen); \
        if((LONG)ulLen < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(cichar, pPacket); \
        if(val1 != cichar)\
        { \
            goto bad; \
        } \
        if(cilen - 3) \
        { \
            LONG lNotEqual = 0; \
            (VOID)VOS_Mem_Cmp((VOID*)val2, (VOID*)pPacket, (VOS_UINT32)(cilen - 3), &lNotEqual); \
            PPP_INCPTR((ULONG)(cilen - 3), pPacket); \
            if(lNotEqual) \
            { \
                goto bad; \
            } \
        } \
    }

#define ACKCIMHF(opt, neg, mhfcode, mhfclass) \
    if (neg) \
    { \
        if ((LONG)(ulLen -= PPP_CILEN_SHORT) < 0) \
        {\
            goto bad; \
        }\
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if (PPP_CILEN_SHORT != cilen || citype != opt) \
        {\
            goto bad; \
        }\
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != mhfcode) \
        {\
            goto bad; \
        }\
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != mhfclass) \
        {\
            goto bad; \
        }\
    }

/* Ack������Prefix-Elisionѡ���ʽ */
/* 0                 16                  32    
   ++++++++++++++++++++++++++++++++++++++++
   |  Type  | Length | Class | PrefixELen |
   ----------------------------------------
   |  Prefix-E field ....                 |
   ----------------------------------------
   |                 ....                 |
   ++++++++++++++++++++++++++++++++++++++++
*/
#define ACKCIPREFIXE( opt, neg, astPrefixE ) \
    if (neg)\
    { \
        LONG  lRet = 0;\
        UCHAR ucCiLenTemp = 0;\
        UCHAR aucBufTemp[LEN_256] = {0};\
        UCHAR *pucAckPacket = NULL;\
        pucAckPacket = aucBufTemp;\
        citype = pPacket[0];\
        cilen = pPacket[1];\
        if ((LONG)(ulLen -= cilen) < 0 || citype != opt ) \
        {\
            goto bad; \
        }\
        /* ��ʱ��װһ��Prefix-Elisionѡ���REQ����(���˱����뷢�͵�REQ�е�Prefix-Elisonѡ������һ��) \
           ��ȷ��ACK������Prefix-Elisionѡ��������Ƿ��REQ�����е�һ�� */ \
        PPP_PUTPREFIXE(astPrefixE, pucAckPacket, ucCiLenTemp);\
        /* ���ѡ��ȾͲ�������ʱ�����REQ���ĵ�ѡ��ȣ���ֱ����Ϊ�Ƿ����� */ \
        if ( cilen != ucCiLenTemp ) \
        {\
            goto bad; \
        }\
        /* �Ƚ�ACK�����еĸ�ѡ�������Ƿ����ʱ�����REQ�����е�һ�� */\
        (VOID)VOS_Mem_Cmp( (VOID*)pPacket, (VOID*)aucBufTemp, (VOS_UINT32)cilen, &lRet );\
        if ( lRet )\
        {\
            goto bad; \
        }\
        /* ACK�����еĴ�ѡ�������ȷ������ָ����һ��ѡ�� */ \
        PPP_INCPTR( cilen, pPacket );\
    }
/* End of addition */
/******************************/




typedef struct tagPppLcpInfo
{
    PPPINFO_S *pstPppInfo;            /* PPP���ƿ�ָ�� */
    PPPFSM_S  stFsm;                  /* LCPЭ��״̬�� */
    PPP_LCP_OPTION_S stGotOptions;    /* �Ѿ���Է�Э�̳ɹ����ҵ�ѡ�� */
    PPP_LCP_OPTION_S stHisOptions;    /* �Ѿ�����Э�̳ɹ��ĶԷ���ѡ�� */
    PPP_LCP_OPTION_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_LCP_OPTION_S stAllowOptions;  /* ����Է�����Э�̵��ҵ�ѡ�� */
} PPPLCPINFO_S;

/* �ӿں��� */
VOID PPP_LCP_Init(PPPINFO_S *);
VOID PPP_LCP_ReceiveEventFromCore (VOID *pstLcpInfo, ULONG ulCmd, char *pPara);
VOID PPP_LCP_ReceivePacket (VOID *pstLcpInfo, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen);

/* �ص����� */
VOID PPP_LCP_resetci(PPPFSM_S *f);
USHORT PPP_LCP_cilen(PPPFSM_S *);
VOID PPP_LCP_addci(PPPFSM_S *, UCHAR *);
USHORT PPP_LCP_ackci(PPPFSM_S *, UCHAR *, ULONG);
USHORT PPP_LCP_nakci(PPPFSM_S *, UCHAR *, ULONG);
USHORT PPP_LCP_rejci(PPPFSM_S *, UCHAR *, ULONG);
UCHAR PPP_LCP_reqci(PPPFSM_S *, UCHAR *, ULONG *);
USHORT PPP_LCP_extcode(PPPFSM_S *, UCHAR, UCHAR, UCHAR *, UCHAR *, ULONG);
VOID PPP_LCP_up(PPPFSM_S *);
VOID PPP_LCP_down(PPPFSM_S *);
VOID PPP_LCP_finished(PPPFSM_S *);
VOID PPP_LCP_starting(PPPFSM_S *);

/* �ڲ������� */
VOID PPP_LCP_SendEchoRequest(PPPFSM_S *);
VOID PPP_LCP_ReceiveEchoReply(PPPFSM_S *, UCHAR, UCHAR *, ULONG);
VOID PPP_LCP_EchoTimeOut(VOID *);
ULONG PPP_LCP_UpResetCi(PPPINFO_S *);
ULONG PPP_LCP_upcheck(PPPFSM_S *pstFsm);

VOID PPP_LCP_ReceiveDiscReq(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pPacket, ULONG ulLen);
VOID PPP_Ncp_Reset(VOID * pstFsm);
VOID PPP_LCP_FSM_TimeOut(VOID *pIfIndex);

#ifdef __cplusplus
}
#endif

#endif
