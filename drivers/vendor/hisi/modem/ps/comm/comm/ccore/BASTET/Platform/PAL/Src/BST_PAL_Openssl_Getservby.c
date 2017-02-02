
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include <string.h>
#include "lwip/netdb.h"
#include "lwip/sockets.h"
/*lint -e767*/
#define THIS_FILE_ID PS_FILE_ID_BST_PAL_OPENSSL_GETSERVBY_C
/*lint +e767*/

/*****************************************************************************
  2 ��/�ṹ����
*****************************************************************************/
struct BST_SERVICE
{
    BST_CHAR    *pcName;
    BST_INT32   lPort;
    BST_CHAR    *pcProto;
    BST_CHAR    *pcAlias1;
    BST_CHAR    *pcAlias2;
};
/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/
static const struct BST_SERVICE g_Services[] = 
{
    {"echo",            7,       "tcp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"echo",            7,       "udp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"discard",         9,       "tcp",         "sink",             "null"},
    {"discard",         9,       "udp",         "sink",             "null"},
    {"ftp-data",        20,      "tcp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"ftp",             21,      "tcp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"ssh",             22,      "tcp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"ssh",             22,      "udp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"telnet",          23,      "tcp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"domain",          53,      "tcp",         "nameserver",       BST_NULL_PTR},
    {"domain",          53,      "udp",         "nameserver",       BST_NULL_PTR},
    {"bootps",          67,      "tcp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"bootps",          67,      "udp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"bootpc",          68,      "tcp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"bootpc",          68,      "udp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"tftp",            69,      "udp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"www",             80,      "tcp",         "http",             BST_NULL_PTR},
    {"www",             80,      "udp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"kerberos",        88,      "tcp",         "kerberos5",        "krb5"},
    {"kerberos",        88,      "udp",         "kerberos5",        "krb5"},
    {"sftp",            115,     "tcp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"ntp",             123,     "tcp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"ntp",             123,     "udp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"snmp",            161,     "udp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"snmp-trap",       162,     "udp",         "snmptrap",         BST_NULL_PTR},
    {"bgp",             179,     "tcp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"bgp",             179,     "udp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"ldap",            389,     "tcp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"ldap",            389,     "udp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"https",           443,     "tcp",         BST_NULL_PTR,       BST_NULL_PTR},
    {"https",           443,     "udp",         BST_NULL_PTR,       BST_NULL_PTR},
    {BST_NULL_PTR,        0,     BST_NULL_PTR,  BST_NULL_PTR,       BST_NULL_PTR}
};
/******************************************************************************
   4 ����ʵ��
******************************************************************************/

static struct BST_SERVICE *BST_FindServiceByName(
    const BST_CHAR  *pcName,
    const BST_CHAR  *pcProto )
{
    BST_INT32 i;
    i = 0;

    while ( g_Services[i].pcName != BST_NULL_PTR )
    {
        if ( ( 0 == strcmp( g_Services[i].pcName, pcName ) )
            || ( ( g_Services[i].pcAlias1 != BST_NULL_PTR ) && ( 0 == strcmp( g_Services[i].pcAlias1, pcName ) ) )
            || ( ( g_Services[i].pcAlias2 != BST_NULL_PTR ) && ( 0 == strcmp( g_Services[i].pcAlias2, pcName ) ) ) )
        {
            if ( ( BST_NULL_PTR == pcProto ) || ( 0 == strcmp( g_Services[i].pcProto, pcProto ) ) )
            {
                return (struct BST_SERVICE *)&g_Services[i];
            }
        }
        ++i;
    }
    return BST_NULL_PTR;
}

static struct BST_SERVICE *BST_FindServiceByPort(
    BST_INT32       lPort,
    BST_CHAR        *pcProto )
{
    BST_INT32   i;
    i           = 0;

    while ( g_Services[i].pcName != BST_NULL_PTR )
    {
        if ( g_Services[i].lPort == lPort )
        {
            if ( ( BST_NULL_PTR == pcProto ) || ( 0 == strcmp( g_Services[i].pcProto, pcProto ) ) )
            {
                return (struct BST_SERVICE *)&g_Services[i];
            }
        }
        ++i;
    }
    return BST_NULL_PTR;
}

struct servent *getservbyname(
    const BST_CHAR  *pcName,
    const BST_CHAR  *pcProto )
{
    static struct servent se;
    static BST_CHAR *s_aliases[3]   = { BST_NULL_PTR, BST_NULL_PTR, BST_NULL_PTR };/* Here only need 3 variables */
    struct BST_SERVICE *sp;

    if ( ( BST_NULL_PTR == pcName ) || ( BST_NULL_PTR == pcProto ) )
    {
        return BST_NULL_PTR;
    }

    sp                              = BST_FindServiceByName( pcName, pcProto );
    if ( BST_NULL_PTR == sp )
    {
        return BST_NULL_PTR;
    }

    se.s_name                       = sp->pcName;
    s_aliases[0]                    = sp->pcAlias1;
    s_aliases[1]                    = sp->pcAlias2;
    se.s_aliases                    = s_aliases;
    se.s_port                       = (int)htons( (BST_UINT16)(sp->lPort) );
    se.s_proto                      = sp->pcProto;

    return &se;
}
struct servent *getservbyport(
    int             lPort,
    BST_CHAR        *pcProto)
{
    static struct servent se;
    static char *s_aliases[3]   = { BST_NULL_PTR, BST_NULL_PTR, BST_NULL_PTR };/* Here only need 3 variables */
    struct BST_SERVICE *sp;

    if ( BST_NULL_PTR == pcProto )
    {
        return BST_NULL_PTR;
    }

    sp = BST_FindServiceByPort( (int)ntohs( (BST_UINT16)lPort ), pcProto );
    if ( BST_NULL_PTR == sp )
    {
        return BST_NULL_PTR;
    }

    se.s_name                   = sp->pcName;
    s_aliases[0]                = sp->pcAlias1;
    s_aliases[1]                = sp->pcAlias2;
    se.s_aliases                = s_aliases;
    se.s_port                   = (int)htons( (BST_UINT16)(sp->lPort) );
    se.s_proto                  = sp->pcProto;

    return &se;
}

