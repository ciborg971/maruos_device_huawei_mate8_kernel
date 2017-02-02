/****************************************************************************/
/*                                                                          */
/*                          ip6_pub.h                                       */
/*                                                                          */
/*  Project Code    : VRP3.0                                                */
/*  Author          :                                                       */
/*  Create Date     :                                                       */
/*  Description     :                                                       */
/*  Others          :                                                       */
/*--------------------------------------------------------------------------*/
/*  Function List   :                                                       */
/*  Name                Function                                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.     */
/*                      ALL RIGHTS RESERVED                                 */
/*                                                                          */
/****************************************************************************/

#if (VRP_MODULE_IPV6 == VRP_YES)

#ifndef _IP6_PUB_H
#define _IP6_PUB_H

#ifdef __cplusplus
extern "C"{
#endif
#ifndef TCPIP_DOUBLEOS
/************************************************************************
                  ADDR module defination
*************************************************************************/
#define IN6_IS_ADDR_UNSPECIFIED(a)    \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == 0))

/* �жϵ�ַ�Ƿ���ͬ�ĺ�IN6_ARE_ADDR_EQUAL
   ���룺IN6ADDR_S  *a    ָ����жϵĵ�ַ
        IN6ADDR_S  *b    ָ����жϵĵ�ַ
   ���أ�0������ͬ    1������ͬ     */
#define IN6_ARE_ADDR_EQUAL(a,b)    \
                 (((a)->s6_addr32[0] == (b)->s6_addr32[0]) &&    \
                  ((a)->s6_addr32[1] == (b)->s6_addr32[1]) &&    \
                  ((a)->s6_addr32[2] == (b)->s6_addr32[2]) &&    \
                  ((a)->s6_addr32[3] == (b)->s6_addr32[3]))


/* ���ص�ַ�жϺ�IN6_IS_ADDR_LOOPBACK
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0�������ǻ��ص�ַ;   1�����ǻ��ص�ַ */
#define IN6_IS_ADDR_LOOPBACK(a)    \
        /*lint -save -e572*/ \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == VOS_HTONL(1)))\
        /*lint -restore*/



/* ��·���ص�ַ�жϺ�IN6_IS_ADDR_LINKLOCAL
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0����������·���ص�ַ����;   1��������·���ص�ַ����   */
#define IN6_IS_ADDR_LINKLOCAL(a)    \
        (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0x80))


/* վ�㱾�ص�ַ�жϺ�IN6_IS_ADDR_SITELOCAL
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0��������վ�㱾�ص�ַ����;   1������վ�㱾�ص�ַ���� */
#define IN6_IS_ADDR_SITELOCAL(a)    \
        (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0xc0))


/* �鲥��ַ�жϺ�IN6_IS_ADDR_MULTICAST
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0���������鲥��ַ����;   1�������鲥��ַ���� */
#define IN6_IS_ADDR_MULTICAST(a)    ((a)->s6_addr[0] == 0xff)

#define IN6_IS_ADDR_LINKLOCAL_MULTICAST(a)    \
        (((a)->s6_addr[0] == 0xff) && (((a)->s6_addr[1] & 0x0f) == 0x02))

/* δָ����ַ�жϺ�IN6_IS_ADDR_UNSPECIFIED
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0��������δָ����ַ����;    1�������鲥��ַ���� */
#define IN6_IS_ADDR_UNSPECIFIED(a)    \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == 0))

/* Added by Vikas, 2003/7/15
    Add the following macro to check if the iven address is solicited
multicast
    address or not. FF02::1
    Donot check the Ifnex index part */
#define IN6_IS_ADDR_SOLICITED_MULTICAST(a)    \
        ( /*lint -e572*/ /*lint -e648*/((a)->s6_addr16[0] == VOS_HTONS(0xff02)) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == VOS_HTONL(1)) &&((a)->s6_addr8[12] == 0xff) /*lint +e572*/ /*lint +e648*/)

/*                 (((a)->s6_addr16[0] == IP6_ADDR_INT16_MLL) && \
             ((a)->s6_addr32[1] == 0) &&  \
            ((a)->s6_addr32[2] == VOS_HTONL(1)) && \
            ((a)->s6_addr8[12] == 0xff))*/


/* ���ص�ַ�жϺ�IN6_IS_ADDR_LOOPBACK
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0�������ǻ��ص�ַ;   1�����ǻ��ص�ַ */
#define IN6_IS_ADDR_LOOPBACK(a)    \
        /*lint -save -e572*/ \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == VOS_HTONL(1)))\
        /*lint -save -e572*/


/* ��IPv4��ַ���ݵ�IPv6��ַ�жϺ�
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0����������IPv4��ַ���ݵ�IPv6��ַ; 1��������IPv4��ַ���ݵ�IPv6��ַ */
#define IN6_IS_ADDR_V4COMPAT(a)    \
        (      /*lint -e572*/ /*lint -e648*/((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] !=0) && \
         ((a)->s6_addr32[3] != VOS_HTONL(1))      /*lint +e572*/ /*lint +e648*/ )


/* ��IPv4��ַӳ���IPv6��ַ�жϺ�
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0����������IPv4��ַӳ���IPv6��ַ;  1��������IPv4��ַӳ���IPv6��ַ */
#define IN6_IS_ADDR_V4MAPPED(a)    \
       (        /*lint -e572*/ /*lint -e648*/((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
        ((a)->s6_addr32[2] == VOS_HTONL(0x0000ffff))         /*lint +e572*/        /*lint +e648*/ )


/* ���㵥����ַ��Ӧ������ڵ��鲥��ַ�ĺ�
   ���������IPv6������ַ���������Ӧ������ڵ��鲥���ַ
   ���룺IN6ADDR_S  *a    ������ַָ��
   �����IN6ADDR_S  *b    ����ڵ��鲥��ַָ��   */
#define IP6_GETMULTIADDR_SOLICITEDNODE(a,b)    \
       {  ULONG c = 0xFF020000; \
          ULONG d = 0x1; \
         (b)->s6_addr32[0] = VOS_HTONL(c);    \
         (b)->s6_addr32[1] = 0;    \
         (b)->s6_addr32[2] = VOS_HTONL(d);    \
         (b)->s6_addr32[3] = (a)->s6_addr32[3];    \
         (b)->s6_addr8[12] = 0xff;    }


/* ���㵥����ַ��Ӧ�������ַ�ĺ�
   ���������IPv6������ַ�Լ���ǰ׺������������Ӧ�������ַ
   ���룺IN6ADDR_S  *a    ������ַָ��
        IN6ADDR_S  *b    ������ַǰ׺����ָ��
   �����IN6ADDR_S  *c    �����ַָ��   */
#define IP6_GETPREFIX_FROMADDRANDMASK(a,b,c)    \
       { (c)->s6_addr32[0] = ((a)->s6_addr32[0]) & ((b)->s6_addr32[0]); \
         (c)->s6_addr32[1] = ((a)->s6_addr32[1]) & ((b)->s6_addr32[1]); \
         (c)->s6_addr32[2] = ((a)->s6_addr32[2]) & ((b)->s6_addr32[2]); \
         (c)->s6_addr32[3] = ((a)->s6_addr32[3]) & ((b)->s6_addr32[3]); }


/* Sachin :- Converting address from Network to Host and host to network byte
order*/

#define IPV6_ADDRESS_NTOH(aul4Addr) \
        {\
           (aul4Addr)[0] = VOS_NTOHL((aul4Addr)[0]);\
           (aul4Addr)[1] = VOS_NTOHL((aul4Addr)[1]);\
           (aul4Addr)[2] = VOS_NTOHL((aul4Addr)[2]);\
           (aul4Addr)[3] = VOS_NTOHL((aul4Addr)[3]);\
        }
/*aul4Addr must be a array that have 4 ULONG element */
#define IPV6_ADDRESS_HTON(aul4Addr) \
        {\
           (aul4Addr)[0] = VOS_HTONL((aul4Addr)[0]);\
           (aul4Addr)[1] = VOS_HTONL((aul4Addr)[1]);\
           (aul4Addr)[2] = VOS_HTONL((aul4Addr)[2]);\
           (aul4Addr)[3] = VOS_HTONL((aul4Addr)[3]);\
        }

/* ����IPv6��ַ�ĺ궨�� */
#define IN6ADDR_ANY_INIT \
    {{{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}}

/* Begin : Added by KLSRINI for SGSN support */
#define IPV6_NDPACKET      0x00000040
#define IPV6_INDPACKET     0x00000080
/* End   : Added by KLSRINI for SGSN support */
#else
/************************************************************************
                  ADDR module defination
*************************************************************************/
#define VRP_IN6_IS_ADDR_UNSPECIFIED(a)    \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == 0))

/* �жϵ�ַ�Ƿ���ͬ�ĺ�IN6_ARE_ADDR_EQUAL
   ���룺IN6ADDR_S  *a    ָ����жϵĵ�ַ
        IN6ADDR_S  *b    ָ����жϵĵ�ַ
   ���أ�0������ͬ    1������ͬ     */
#define VRP_IN6_ARE_ADDR_EQUAL(a,b)    \
                 (((a)->s6_addr32[0] == (b)->s6_addr32[0]) &&    \
                  ((a)->s6_addr32[1] == (b)->s6_addr32[1]) &&    \
                  ((a)->s6_addr32[2] == (b)->s6_addr32[2]) &&    \
                  ((a)->s6_addr32[3] == (b)->s6_addr32[3]))


/* ���ص�ַ�жϺ�IN6_IS_ADDR_LOOPBACK
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0�������ǻ��ص�ַ;   1�����ǻ��ص�ַ */
#define VRP_IN6_IS_ADDR_LOOPBACK(a)    \
        /*lint -save -e572*/ \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == VOS_HTONL(1)))\
        /*lint -restore*/



/* ��·���ص�ַ�жϺ�IN6_IS_ADDR_LINKLOCAL
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0����������·���ص�ַ����;   1��������·���ص�ַ����   */
#define VRP_IN6_IS_ADDR_LINKLOCAL(a)    \
        (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0x80))


/* վ�㱾�ص�ַ�жϺ�IN6_IS_ADDR_SITELOCAL
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0��������վ�㱾�ص�ַ����;   1������վ�㱾�ص�ַ���� */
#define VRP_IN6_IS_ADDR_SITELOCAL(a)    \
        (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0xc0))


/* �鲥��ַ�жϺ�IN6_IS_ADDR_MULTICAST
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0���������鲥��ַ����;   1�������鲥��ַ���� */
#define VRP_IN6_IS_ADDR_MULTICAST(a)    ((a)->s6_addr[0] == 0xff)

#define VRP_IN6_IS_ADDR_LINKLOCAL_MULTICAST(a)    \
        (((a)->s6_addr[0] == 0xff) && (((a)->s6_addr[1] & 0x0f) == 0x02))

/* δָ����ַ�жϺ�IN6_IS_ADDR_UNSPECIFIED
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0��������δָ����ַ����;    1�������鲥��ַ���� */
#define VRP_IN6_IS_ADDR_UNSPECIFIED(a)    \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == 0))

/* Added by Vikas, 2003/7/15
    Add the following macro to check if the iven address is solicited
multicast
    address or not. FF02::1
    Donot check the Ifnex index part */
#define VRP_IN6_IS_ADDR_SOLICITED_MULTICAST(a)    \
        (((a)->s6_addr16[0] == VOS_HTONS(0xff02)) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == VOS_HTONL(1)) &&((a)->s6_addr8[12] == 0xff))

/*                 (((a)->s6_addr16[0] == IP6_ADDR_INT16_MLL) && \
             ((a)->s6_addr32[1] == 0) &&  \
            ((a)->s6_addr32[2] == VOS_HTONL(1)) && \
            ((a)->s6_addr8[12] == 0xff))*/


/* ���ص�ַ�жϺ�IN6_IS_ADDR_LOOPBACK
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0�������ǻ��ص�ַ;   1�����ǻ��ص�ַ */
#define VRP_IN6_IS_ADDR_LOOPBACK(a)    \
        /*lint -save -e572*/ \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == VOS_HTONL(1)))\
        /*lint -save -e572*/


/* ��IPv4��ַ���ݵ�IPv6��ַ�жϺ�
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0����������IPv4��ַ���ݵ�IPv6��ַ; 1��������IPv4��ַ���ݵ�IPv6��ַ */
#define VRP_IN6_IS_ADDR_V4COMPAT(a)    \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] !=0) && \
         ((a)->s6_addr32[3] != VOS_HTONL(1)) )


/* ��IPv4��ַӳ���IPv6��ַ�жϺ�
   ���룺IN6ADDR_S  *a    ָ����жϵ�ַ��ָ��
   ���أ�0����������IPv4��ַӳ���IPv6��ַ;  1��������IPv4��ַӳ���IPv6��ַ */
#define VRP_IN6_IS_ADDR_V4MAPPED(a)    \
       (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
        ((a)->s6_addr32[2] == VOS_HTONL(0x0000ffff)) )


/* ���㵥����ַ��Ӧ������ڵ��鲥��ַ�ĺ�
   ���������IPv6������ַ���������Ӧ������ڵ��鲥���ַ
   ���룺IN6ADDR_S  *a    ������ַָ��
   �����IN6ADDR_S  *b    ����ڵ��鲥��ַָ��   */
#define VRP_IP6_GETMULTIADDR_SOLICITEDNODE(a,b)    \
       { (b)->s6_addr32[0] = VOS_HTONL(0xFF020000);    \
         (b)->s6_addr32[1] = 0;    \
         (b)->s6_addr32[2] = VOS_HTONL(1);    \
         (b)->s6_addr32[3] = (a)->s6_addr32[3];    \
         (b)->s6_addr8[12] = 0xff;    }


/* ���㵥����ַ��Ӧ�������ַ�ĺ�
   ���������IPv6������ַ�Լ���ǰ׺������������Ӧ�������ַ
   ���룺IN6ADDR_S  *a    ������ַָ��
        IN6ADDR_S  *b    ������ַǰ׺����ָ��
   �����IN6ADDR_S  *c    �����ַָ��   */
#define VRP_IP6_GETPREFIX_FROMADDRANDMASK(a,b,c)    \
       { (c)->s6_addr32[0] = ((a)->s6_addr32[0]) & ((b)->s6_addr32[0]); \
         (c)->s6_addr32[1] = ((a)->s6_addr32[1]) & ((b)->s6_addr32[1]); \
         (c)->s6_addr32[2] = ((a)->s6_addr32[2]) & ((b)->s6_addr32[2]); \
         (c)->s6_addr32[3] = ((a)->s6_addr32[3]) & ((b)->s6_addr32[3]); }


/* Sachin :- Converting address from Network to Host and host to network byte
order*/

#define VRP_IPV6_ADDRESS_NTOH(aul4Addr) \
        {\
           (aul4Addr)[0] = VOS_NTOHL((aul4Addr)[0]);\
           (aul4Addr)[1] = VOS_NTOHL((aul4Addr)[1]);\
           (aul4Addr)[2] = VOS_NTOHL((aul4Addr)[2]);\
           (aul4Addr)[3] = VOS_NTOHL((aul4Addr)[3]);\
        }
/*aul4Addr must be a array that have 4 ULONG element */
#define VRP_IPV6_ADDRESS_HTON(aul4Addr) \
        {\
           (aul4Addr)[0] = VOS_HTONL((aul4Addr)[0]);\
           (aul4Addr)[1] = VOS_HTONL((aul4Addr)[1]);\
           (aul4Addr)[2] = VOS_HTONL((aul4Addr)[2]);\
           (aul4Addr)[3] = VOS_HTONL((aul4Addr)[3]);\
        }

/* ����IPv6��ַ�ĺ궨�� */
#define VRP_IN6ADDR_ANY_INIT \
    {{{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}}

/* Begin : Added by KLSRINI for SGSN support */
#define VRP_IPV6_NDPACKET      0x00000040
#define VRP_IPV6_INDPACKET     0x00000080
/* End   : Added by KLSRINI for SGSN support */
#endif

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _IP6_TYPE_H_ */

#endif  /* end of VRP_MODULE_IPV6 */
