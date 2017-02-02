
#ifndef __SFE_SOCKET_API_H__
#define __SFE_SOCKET_API_H__

#ifdef  __cplusplus
    extern "C"{
#endif

/*ERRORCODE<������socketģ�������>*/
typedef enum enumSfeSockErrCode
{
    SFE_SOCK_OK = SFE_OK,                           /* �����ɹ� */
    SFE_SOCK_ERR_BEGIN = SFE_SOCK_BEGIN_RET_CODE,   /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_SOCK_GET_SFE_SOCKET_MAX_NUM_PRECFG_FAIL,    /* 1  ��ȡ���socket����Ԥ����ֵʧ�� */
    SFE_SOCK_MALLOC_SOCKET_POOL_FAIL,               /* 2  ����socket��Դ��ʧ�� */
    SFE_SOCK_MALLOC_SOCKET_NODETYPE_INVALID,        /* 3  ����socket�ڵ�ʱsocket���Ͳ��Ϸ�. */
    SFE_SOCK_MALLOC_SOCKET_NODE_FAIL,               /* 4  ��socket��Դ��������socket�ڵ�ʧ�� */
    SFE_SOCK_MALLOC_SOCKET_NODEINDEX_INVALID,       /* 5  ��socket��Դ��������Ľڵ��������Ϸ� */
    SFE_SOCK_MALLOC_TCP_NODE_FAIL,                  /* 6  ����TCP��Դ���еĽڵ�ʧ�� */
    SFE_SOCK_CHECKHASH_VCPU_OVERMAX,                /* 7  �ж�vcpu������Ч��,����Խ�� */
    SFE_SOCK_CHECKHASH_VRF_OVERMAX,                 /* 8  �ж�vrf������Ч��,����Խ�� */
    SFE_SOCK_CHECKHASH_VCPU_POINTER_NULL,           /* 9  �ж�vcpuָ����Ч��,ָ��Ϊ�� */
    SFE_SOCK_CHECKHASH_VRF_POINTER_NULL,            /* 10 �ж�vrfָ����Ч��,ָ��Ϊ�� */

    SFE_SOCK_CHECKHASH_FIRSTHASH_NULL,              /* 11 �ж�1��hashָ����Ч��,ָ��Ϊ�� */
    SFE_SOCK_CHECKHASH_SECONDHASH_NULL,             /* 12 �ж�2��hashָ����Ч��,ָ��Ϊ�� */
    SFE_SOCK_FREE_SOCKTRANSCB_NULL,                 /* 13 �ͷŽڵ�ʱ,���ͷŵ�socket�ڵ�Ϊ�� */
    SFE_SOCK_FREE_VCPUID_NOT_MATCH,                 /* 14 �ͷŽڵ�ʱ,���ͷŵĽڵ��VCPU ID�͵�ǰ�Ĳ�һ�� */
    SFE_SOCK_FREE_SOCKTYPE_INVALID,                 /* 15 �ͷŽڵ�ʱ,���ͷŵĽڵ��Ӧsocket������Ч */
    SFE_SOCK_FREE_HASHCHAIN_NO_NODE,                /* 16 �ͷŽڵ�ʱ,��ǰ�Ĺ�ϣ�����޽ڵ� */
    SFE_SOCK_HASH_SEARCH_NO_EXACTMATCH_NODE,        /* 17 û���ҵ���ȷƥ���socket */
    SFE_SOCK_HASH_SEARCH_NO_WILDCARD_NODE,          /* 18 û���ҵ�ͨ��ƥ���socket */
    SFE_SOCK_ERR_SOCKET_NOTIFY_POINTNULL,           /* 19 ��ȡ�����socket�ص�����ָ��Ϊ�� */
    SFE_SOCK_FIND_NODE_FAIL_GETSOCKTRANSCB,         /* 20 ����FD��ȡsocket�ڵ�ʱ,δ���ҵ���Ӧ�ڵ� */

    SFE_SOCK_VCPUID_NOT_MATCH_GETSOCKTRANSCB,       /* 21 ����FD��ȡsocket�ڵ�ʱ,�����Ľڵ��VCPU ID�͵�ǰ�Ĳ�һ�� */
    SFE_SOCK_FD_INVALID_GETSOCKTRANSCB,             /* 22 ����FD��ȡsocket�ڵ�ʱ,����FD�Ƿ� */
    SFE_SOCK_SOCKET_NOT_USED_GETSOCKTRANSCB,        /* 23 ����FD��ȡsocket�ڵ�ʱ,��ȱ��socket�ڵ�δ��ʹ�� */
    SFE_SOCK_RECV_ZMBUF_NULL_POINTER,               /* 24 ���ջ���������,ָ��Ϊ�� */
    SFE_SOCK_RECV_ZMBUF_NO_DATA,                    /* 25 ���ջ���������,�������������� */
    SFE_SOCK_SEND_ZMBUF_NULL_POINTER,               /* 26 �����û�ָ������,ָ��Ϊ�� */
    SFE_SOCK_SOCKBUF_FULL,                          /* 27 ��socket�������������ʱ,socket�������� */
    SFE_SOCK_SEND_ZMBUF_DATALEN_INVALID,            /* 28 �㿽����������ʱ, MBUF���ݳ���Ϊ0�Ƿ� */
    SFE_SOCK_CREATE_VCPU_SM_FAIL,                   /* 29 socket������ʼ��ʱ�����ź���ʧ�� */
    SFE_SOCK_FREE_SOCKET_NOT_USED,                  /* 30 �ͷŵ�socket�ڵ�ʱ,�ڵ��ѱ��ͷ� */

    SFE_SOCK_HASH_SEARCH_SOCKET_NOT_USED,           /* 31 ����socket�ڵ�ʱ, ��ȷƥ��ʱ�ڵ��ѱ��ͷ�*/
    SFE_SOCK_HASH_SEARCH_SOCKET_NOT_USED_WILD,      /* 32 ����socket�ڵ�,����IP��ȷƥ������ͨ��ʱ�ڵ��ѱ��ͷ� */
    SFE_SOCK_HASH_SEARCH_SOCKET_NOT_USED_LIP_WILD,  /* 33 ����socket�ڵ�,����IPͨ������ͨ��ʱ�ڵ��ѱ��ͷ� */
    SFE_SOCK_RECV_ZMBUF_VCPUID_INVALID,             /* 34 �㿽����ʽ��������ʱ,��ȡ��vcpu��Ч */
    SFE_SOCK_SEND_ZMBUF_VCPUID_INVALID,             /* 35 �㿽����ʽ��������ʱ,��ȡ��vcpu��Ч */
    SFE_SOCK_IOCTL_VCPUID_INVALID,                  /* 36 ���û��ȡsocket ioʱ,��ȡ��vcpu��Ч */
    SFE_SOCK_MALLOC_VCPU_SM_MEM_FAIL,               /* 37 ����ÿ��vcpu�ϵ��ź�������ʧ�� */
    SFE_SOCK_ADD_NAMEDB_VCPU_SM_FAIL,               /* 38 ����ÿ��vcpu�ϵ��ź���������ӵ��������ֿ�ʧ�� */
    SFE_SOCK_SETSOCKOPT_VCPUID_INVALID,             /* 39 ����SOCKѡ��ʱ,��ȡ��vcpu��Ч */
    SFE_SOCK_SETSOCKOPT_LINGER_INPUT_INVAILD,       /* 40 ����SOCKѡ��ʱ,����LINGERѡ������Ƿ� */

    SFE_SOCK_SETSOCKOPT_LINGER_SOCKTYPE_INVAILD,    /* 41 ����SOCKѡ��ʱ,����LINGERѡ��Ĳ���TCP���� */
    SFE_SOCK_SETSOCKOPT_SETKEEPALIVE_OPT_INVAILD,   /* 42 ����SOCKѡ��ʱ,����SETKEEPALIVEѡ��ʱKEEPALIVEû����λ */
    SFE_SOCK_SETSOCKOPT_SETKEEPALIVE_SOCKTYPE_INVAILD,/* 43  ����SOCKѡ��ʱ,����KEEPALIVEѡ��Ĳ���TCP���� */
    SFE_SOCK_SETSOCKOPT_SETKEEPALIVE_VALUE_INVAILD, /* 44 ����SOCKѡ��ʱ,����SETKEEPALIVEѡ������ֵ�Ƿ� */
    SFE_SOCK_SETSOCKOPT_SETKEEPALIVE_INPUT_INVAILD, /* 45 ����SOCKѡ��ʱ,����SETKEEPALIVEѡ������Ƿ� */
    SFE_SOCK_SETSOCKOPT_KEEPALIVE_INPUT_INVAILD,    /* 46 ����SOCKѡ��ʱ,����SFE_SO_KEEPALIVE|SFE_SO_REUSEADDR|SFE_SO_REUSEPORTѡ������Ƿ� */
    SFE_SOCK_SETSOCKOPT_SNDBUF_INPUT_INVAILD,       /* 47 ����SOCKѡ��ʱ,����SFE_SO_SNDBUFѡ������Ƿ� */
    SFE_SOCK_SETSOCKOPT_SNDLOWAT_INPUT_INVAILD,     /* 48 ����SOCKѡ��ʱ,����SFE_SO_SNDLOWATѡ������Ƿ� */
    SFE_SOCK_SETSOCKOPT_SNDLOWAT_INVAILD,           /* 49 ����SOCKѡ��ʱ,����SFE_SO_SNDLOWATѡ�����õ�ֵ�Ƿ� */
    SFE_SOCK_SETSOCKOPT_SOL_SOCKET_INVAILD,         /* 50 ����SOCKѡ��ʱ,����SOL_SOCKET����ʱ��������ѡ��Ƿ� */

    SFE_SOCK_SETSOCKOPT_IPPROTO_TCP_TCBCB_NULL,     /* 51 ����SOCKѡ��ʱ,����IPPROTO_TCP����ʱ������TCPCBΪ�� */
    SFE_SOCK_SETSOCKOPT_NODELAY_INPUT_INVAILD,      /* 52 ����SOCKѡ��ʱ,����NODELAYѡ������Ƿ� */
    SFE_SOCK_SETSOCKOPT_IPPROTO_TCP_INVAILD,        /* 53 ����SOCKѡ��ʱ,����IPPROTO_TCP����ʱ��������ѡ��Ƿ� */
    SFE_SOCK_SETSOCKOPT_TOS_INPUT_INVAILD,          /* 54 ����SOCKѡ��ʱ,����TOSѡ������Ƿ� */
    SFE_SOCK_SETSOCKOPT_TTL_INPUT_INVAILD,          /* 55 ����SOCKѡ��ʱ,����TTLѡ������Ƿ� */
    SFE_SOCK_SETSOCKOPT_IPPROTO_IP_INVAILD,         /* 56 ����SOCKѡ��ʱ,����IPPROTO_IP����ʱ��������ѡ��Ƿ� */
    SFE_SOCK_SETSOCKOPT_LEVEL_INVAILD,              /* 57 ����SOCKѡ��ʱ,���ü���Ƿ� */
    SFE_SOCK_SETSOCKOPT_UDPCHECKSUM_INPUT_INVAILD,  /* 58 ����SOCKѡ��ʱ,����UDPCHECKSUMѡ������Ƿ� */
    SFE_SOCK_GETSOCKOPT_VCPUID_INVALID,             /* 59 ��ȡSOCKѡ��ʱ,��ȡ��vcpu��Ч */
    SFE_SOCK_GETSOCKOPT_INPUT_INVALID,              /* 60 ��ȡSOCKѡ��ʱ,��������Ƿ� */

    SFE_SOCK_GETSOCKOPT_SOL_SOCKET_INVAILD,         /* 61 ��ȡSOCKѡ��ʱ,��ȡSOL_SOCKET����ʱ��������ѡ��Ƿ� */
    SFE_SOCK_GETSOCKOPT_IPPROTO_TCP_TCBCB_NULL,     /* 62 ��ȡSOCKѡ��ʱ,��ȡIPPROTO_TCP����ʱ������TCPCBΪ�� */
    SFE_SOCK_GETSOCKOPT_IPPROTO_TCP_INVAILD,        /* 63 ��ȡSOCKѡ��ʱ,��ȡIPPROTO_TCP����ʱ��������ѡ��Ƿ� */
    SFE_SOCK_GETSOCKOPT_IPPROTO_IP_INVAILD,         /* 64 ��ȡSOCKѡ��ʱ,��ȡIPPROTO_IP����ʱ��������ѡ��Ƿ� */
    SFE_SOCK_GETSOCKOPT_LEVEL_INVAILD,              /* 65 ��ȡSOCKѡ��ʱ,��ȡ����Ƿ� */
    SFE_SOCK_TCP_SNDBUF_NO_ENOUGH_SPACE,            /* 66 ���ͻ������ռ䲻�� */
    SFE_SOCK_HASH_LOOKPORT_SOCKET_NOT_USED,         /* 67 ���ݶ˿ڲ���socket�ڵ�ʱ, ��ȷƥ��ʱ�ڵ��ѱ��ͷ�*/
    SFE_SOCK_HASH_LOOKPORT_SOCKET_NOT_USED_WILD,    /* 68 ���ݶ˿ڲ���socket�ڵ�,����IP��ȷƥ������ͨ��ʱ�ڵ��ѱ��ͷ� */
    SFE_SOCK_HASH_LOOKPORT_SOCKET_NOT_USED_LIP_WILD,/* 69 ���ݶ˿ڲ���socket�ڵ�,����IPͨ������ͨ��ʱ�ڵ��ѱ��ͷ� */
    SFE_SOCK_HASH_LOOKPORT_NO_NODE,                 /* 70 ���ݶ˿ڲ���HASH��ʧ�� */

    SFE_SOCK_GET_SOCKET_NUMBER_NULL_POINTER,        /* 71 ��ȡsocket��Ŀʱ�����ָ�� */
    SFE_SOCK_TCP_ALREADY_CANTSENDMORE,              /* 72 ����TCP����ʱTCP�����Ѿ��������ܷ������� */
    SFE_SOCK_TCP_NOT_ESTABLISHED,                   /* 73 ����TCP����ʱTCP����δ������ɲ��ܷ������� */
    SFE_SOCK_SOCKET_VCPUID_INVALID,                 /* 74 ����socket,��ȡ��vcpu��Ч */
    SFE_SOCK_SOCREATE_EAFNOSUPPORT,                 /* 75 ����socket,���벻֧�ֵ�Address family */
    SFE_SOCK_SOCREATE_EPROTO_OR_SOCKTYPE,           /* 76 ����socket,���벻֧�ֵ�socket���� */
    SFE_SOCK_BIND_VCPUID_INVALID,                   /* 77 ��socket,��ȡ��vcpu��Ч */
    SFE_SOCK_BIND_SOCKADDR_NULL,                    /* 78 ��socket,�����ַ�ṹΪ�� */
    SFE_SOCK_BIND_EAFNOSUPPORT,                     /* 79 ��socket,���벻֧�ֵ�Address family */
    SFE_SOCK_BIND_ERROR_ADDRLEN,                    /* 80 ��socket,�����ַ���ȴ��� */

    SFE_SOCK_BIND_EFAULT,                           /* 81 ��socket,�����ַ�Ƿ� */
    SFE_SOCK_BIND_NOT_STANDARDSOCK,                 /* 82 ��socket,�Ǳ�׼socket���ܵ���bind���� */
    SFE_SOCK_SOCKTRANS_BIND_PORTORADDR_NOZERO,      /* 83 ��socket,��ַ�˿ڷǿգ������ظ��� */
    SFE_SOCK_SOCKTRANS_BIND_EAFNOSUPPORT,           /* 84 ��socket,Address family�Ƿ� */
    SFE_SOCK_SOCKTRANS_BIND_PORT_INVALID,           /* 85 ��socket,�˿ڷǷ� */
    SFE_SOCK_SOCKTRANS_EADDRINUSE,                  /* 86 ��socket,��ַ�ѱ�ʹ�� */
    SFE_SOCK_SOCKTRANS_CREATEPORT_EADDRINUSE,       /* 87 ��socket,������ɶ˿�ʧ�� */
    SFE_SOCK_LISTEN_VCPUID_INVALID,                 /* 88 ����socket,��ȡ��vcpu��Ч */
    SFE_SOCK_SOLISTEN_ENOTBIND,                     /* 89 ����socket,socketδ�� */
    SFE_SOCK_SOLISTEN_ALREADYLISTEN,                /* 90 ����socket,�Ѿ��Ǽ���״̬ */

    SFE_SOCK_LISTEN_NOT_STANDARD_TCPSOCK,           /* 91 ����socket,�Ǳ�׼TCP socket���ܵ���listen���� */
    SFE_SOCK_CONNECT_VCPUID_INVALID,                /* 92 ����socket,��ȡ��vcpu��Ч */
    SFE_SOCK_CONNECT_SOCKADDR_NULL,                 /* 93 ����socket,�����ַ�ṹΪ�� */
    SFE_SOCK_CONNECT_EAFNOSUPPORT,                  /* 94 ����socket,Address family�Ƿ� */
    SFE_SOCK_CONNECT_EPORTNOTAVAIL,                 /* 95 ����socket,socket�˿�Ϊ0 */
    SFE_SOCK_CONNECT_NOT_SUPPORT_NONASYN,           /* 96 ����socket,û�������첽���� */
    SFE_SOCK_SOCONNECT_ENOTBIND,                    /* 97 ����socket,socketδ�� */
    SFE_SOCK_CONNECT_EFAULT,                        /* 98 ����socket,�����ַ�Ƿ� */
    SFE_SOCK_CONNECT_ERROR_ADDRLEN,                 /* 99 ����socket,�����ַ���ȴ��� */
    SFE_SOCK_CONNECT_EALREADY,                      /* 100 ����socket,�Ѿ������Ӵ����� */

    SFE_SOCK_CONNECT_EINPROGRESS,                   /* 101 ����socket,��ʼ���� */
    SFE_SOCK_CONNECT_ERROR,                         /* 102 ����socket,TCP������������ɹ�,����socketδ��SFE_SS_ISCONNECTING״̬*/
    SFE_SOCK_CONNECT_EBLOCKING,                     /* 103 ����socket,���������ڸ�socket������ */
    SFE_SOCK_SOCONNECT_EOPNOTSUPP,                  /* 104 ����socket,socket�Ǽ���socket */
    SFE_SOCK_SOCONNECT_EISCONN,                     /* 105 ����socket,socket������ */
    SFE_SOCK_SOCONNECT_TCPCLOSED,                   /* 106 ����socket,TCP�����Ѿ��ر� */
    SFE_SOCK_SOCKTRANS_CONNECT_EADDRINUSE,          /* 107 ����socket,socket��ַ�Ѿ�ʹ�� */
    SFE_SOCK_CLOSE_VCPUID_INVALID,                  /* 108 �ر�socket,��ȡ��vcpu��Ч */
    SFE_SOCK_CLOSE_EINPROGRESS,                     /* 109 �ر�socket,�Ѿ��ڴ����� */
    SFE_SOCK_GETONESOCKDEBUG_NULL_POINTER,          /* 110 ��ȡ����socket���Կ���,�����ָ�� */

    SFE_SOCK_GETALLSOCKDEBUG_NULL_POINTER,          /* 111 ��ȡȫ��socket���Կ���,�����ָ�� */
    SFE_SOCK_SETSOCKDEBUG_VCPUID_INVALID,           /* 112 ��ȡ��VCPUID�Ƿ� */
    SFE_SOCK_SEND_BUF_TOO_BIG,                      /* 113 ���õķ��ͻ�������ˮλ�ô��ڿ������õ�����ͻ�������С */
    SFE_SOCK_RCV_BUF_TOO_BIG,                       /* 114 ���õĽ��ջ�������ˮλ�ô��ڿ������õ������ջ�������С */
    SFE_SOCK_SETSOCKOPT_TTL_VALUE_INPUT_INVAILD,    /* 115 ����SOCKѡ��ʱ,����TTLѡ�������TTLֵ�Ƿ� */
    SFE_SOCK_SETSOCKOPT_LINGER_VALUE_INPUT_INVAILD, /* 116 ����SOCKѡ��ʱ,����LINGERѡ�������LINGERѡ��ֵ�Ƿ� */
    SFE_SOCK_SETSOCKOPT_TOS_INPUT_VALUE_INVAILD,    /* 117 ����SOCKѡ��ʱ,����TOSѡ�������TOSֵ�Ƿ� */
    SFE_SOCK_UDP_UNBIND_LOCAL_ADDR,                 /* 118 ����UDP����ʱ, UDPδ�󶨱��˵�ַ */
    SFE_SOCK_UDP_FADDR_NULL_POINTER,                /* 119 ����UDP����ʱ, Զ�˵�ַΪ�� */
    SFE_SOCK_UDP_FADDR_AFNOSUPPORT,                 /* 120 ����UDP����ʱ, Զ��Э���岻֧�� */

    SFE_SOCK_UDP_FADDR_PORTNOTAVAIL,                /* 121 ����UDP����ʱ, Զ�˶˿���Ч */
    SFE_SOCK_UDP_FADDR_ADDRINVALID,                 /* 122 ����UDP����ʱ, Զ�˵�ַ��Ч */
    SFE_SOCK_UDP_FADDR_LENINVALID,                  /* 123 ����UDP����ʱ, Զ�˵�ַ���ȷǷ� */
    SFE_SOCK_UDP_MBUF_DB_RESERVE_NOTENOUGH,         /* 124 ����UDP����ʱ, MBUF��DBԤ������С����С��Ԥ������ */
    SFE_SOCK_UDP_MBUF_SIZE_LARGER,                  /* 125 ����UDP����ʱ, MBUF���ݳ��ȴ��ڷ��͸�ˮλ */
    SFE_SOCK_SET_CONNINFO_DIRC_INVALID,             /* 126 ����SOCKʹ������Ϣʱ,������Ϣ�Ƿ� */
    SFE_SOCK_SET_CONNINFO_VCPUID_INVALID,           /* 127 ����SOCKʹ������Ϣʱ,��ȡ��vcpu��Ч */
    SFE_SOCK_SOCKTRANS_BIND_TYPE_NOSUPPORT,         /* 128 ��socket, socket���ͷǷ� */
    SFE_SOCK_CLOSE_REORDER_NOT_ALLOWED,             /* 129 �ر�socket,����ģʽ�²��������close���� */
    SFE_SOCK_CONNECT_NOT_SUPPORT_TYPE,              /* 130 ����socket,��TCP socket�������� */

    SFE_SOCK_SETSOCKOPT_SETKEEPALIVE_PARAM_INVAILD, /* 131 ����SOCKѡ��ʱ,����SETKEEPALIVEѡ������Ĳ���ֵ�Ƿ� */
    SFE_SOCK_SETSOCKOPT_RCVBUF_INPUT_INVAILD,       /* 132 ����SOCKѡ��ʱ,����SFE_SO_RCVBUFѡ������Ƿ� */
    SFE_SOCK_SETSOCKOPT_RCVLOWAT_INPUT_INVAILD,     /* 133 ����SOCKѡ��ʱ,����SFE_SO_RCVLOWATѡ������Ƿ� */
    SFE_SOCK_SETSOCKOPT_RCVLOWAT_INVAILD,           /* 134 ����SOCKѡ��ʱ,����SFE_SO_RCVLOWATѡ�����õ�ֵ�Ƿ� */
    SFE_SOCK_MALLOC_GLOBALDEBUG_SWITCH_MEM_FAIL,    /* 135 ��ʼ��ʱ,����socketȫ�ֵ��Կ��ع����ڴ�ʧ�� */
    SFE_SOCK_SET_SOCKGLOBAL_DEBUGSWITCH_NULL,       /* 136 ����SOCKȫ�ֵ��Կ���ʱ,ָ��ΪNULL,������û�г�ʼ�� */
    SFE_RECV_ZMBUF_MODULE_NOT_INIT,                 /* 137 ����recvzmbuf�ӿ�ʱϵͳ��δ��ʼ�� */
    SFE_SEND_ZMBUF_MODULE_NOT_INIT,                 /* 138 ����sendzmbuf�ӿ�ʱϵͳ��δ��ʼ�� */
    SFE_SOCKET_MODULE_NOT_INIT,                     /* 139 ����socket�ӿ�ʱϵͳ��δ��ʼ�� */
    SFE_BIND_MODULE_NOT_INIT,                       /* 140 ����bind�ӿ�ʱϵͳ��δ��ʼ�� */

    SFE_LISTEN_MODULE_NOT_INIT,                     /* 141 ����listen�ӿ�ʱϵͳ��δ��ʼ�� */
    SFE_CONNECT_MODULE_NOT_INIT,                    /* 142 ����connect�ӿ�ʱϵͳ��δ��ʼ�� */
    SFE_CLOSE_MODULE_NOT_INIT,                      /* 143 ����close�ӿ�ʱϵͳ��δ��ʼ�� */
    SFE_IOCTL_MODULE_NOT_INIT,                      /* 144 ����ioctl�ӿ�ʱϵͳ��δ��ʼ�� */
    SFE_SET_SOCKETOPT_MODULE_NOT_INIT,              /* 145 ����setsocketopt�ӿ�ʱϵͳ��δ��ʼ�� */
    SFE_GET_SOCKETOPT_MODULE_NOT_INIT,              /* 146 ����getsocketopt�ӿ�ʱϵͳ��δ��ʼ�� */
    SFE_SET_CONNECTIONINFO_MODULE_NOT_INIT,         /* 147 ����setconnectinfo�ӿ�ʱϵͳ��δ��ʼ�� */
    SFE_SOCK_SETSOCKDEBUG_MODULE_NOT_INIT,          /* 148 ����SetSocketDebugSwitchByFd�ӿ�ʱϵͳ��δ��ʼ�� */
    SFE_SOCK_GET_POOLUNITNUM_BEFORE_INIT,           /* 149 ��ϵͳ��ʼ��ǰ,���ܻ�ȡ��SOCKET��Դ��ͳ�� */
    SFE_SOCK_GET_POOLUNITNUM_INPUT_PARA_INVALID,    /* 150 ��ȡSOCKET��Դ��ͳ��ʱ,����Ĳ����ж�ʧ�� */
    SFE_SOCK_GET_POOLUNITNUM_INPUT_FAILED,          /* 151 ��ȡSOCKET��Դ��ͳ��ʱ,��ȡ���Ŀ��е�Ԫ���Ƿ�*/
    SFE_SOCK_GETSOCKNAME_MODULE_NOT_INIT,           /* 152 ����SFE_GetSockName�ӿ�ʱ,ϵͳ��δ��ʼ�� */
    SFE_SOCK_GETSOCKNAME_VCPUID_INVALID,            /* 153 ����SFE_GetSockName�ӿ�ʱ,��ȡ��vcpuid��Ч */
    SFE_SOCK_GETSOCKNAME_NULL,                      /* 154 ����SFE_GetSockName�ӿ�ʱ,����ָ��Ϊ�� */
    SFE_SOCK_GETSOCKNAME_ERROR_ADDRLEN,             /* 155 ����SFE_GetSockName�ӿ�ʱ,�����ַ���ȴ��� */

    SFE_SOCK_SETSOCKOPT_ALLUSEPORT_INPUT_INVAILD,   /* 156 ����SOCKѡ��ʱ,���ø߶˶˿�����Ƿ� */    
    /* Add end */
    SFE_SOCK_SETSOCKOPT_SOCKETTYPE_NOSUPPORT,       /* 157 ����SOCKѡ��ʱ,����VRFʱ,socket���ͷǷ� */
    SFE_SOCK_SETSOCKOPT_SENDVPNID_INPUT_INVAILD,    /* 158 ����SOCKѡ��ʱ,����VRF����Ƿ� */
    SFE_SOCK_SETSOCKOPT_SETVRF_AFTER_BIND,          /* 159 ����SOCKѡ��ʱ,����VRFʱ��socket�Ѿ��󶨹���(VRF���ñ����ڰ󶨲���ǰ����) */
    SFE_SOCK_SETSOCKOPT_VRFVALUE_TOO_BIG,           /* 160 ����SOCKѡ��ʱ,������VRFֵ̫��(��Ԥ�������ֵ��) */
}SFE_SOCK_ERR_CODE_E;

/*MACRO<��ʾsocket������Ҫ��Ϣ>*/
#define SFE_SOCK_SHOW_BASIC_INFO   0
/*MACRO<��ʾsocket��ϸ��Ϣ,����1����ϸ��Ϣ,����Խ����ϢԽ��>*/
#define SFE_SOCK_SHOW_VERBOSE_INFO_LEVEL1   1
/*MACRO<��ʾsocket��ϸ��Ϣ,����2����ϸ��Ϣ,����Խ����ϢԽ��>*/
#define SFE_SOCK_SHOW_VERBOSE_INFO_LEVEL2   2

/*MACRO<Э���ַ��>*/
#define SFE_AF_INET         2           /* internetwork: UDP, TCP, etc. */
#define SFE_AF_OSI          7
#define SFE_AF_INET6        29          /* added by mayun for IPv6 */

/*MACRO<Э���>*/
#define SFE_IPPROTO_IP          0       /* dummy for IP */
#define SFE_IPPROTO_ICMP        1       /* control message protocol */
#define SFE_IPPROTO_IGMP        2       /* group mgmt protocol */
#define SFE_IPPROTO_TCP         6       /* tcp */
#define SFE_IPPROTO_UDP         17      /* user datagram protocol */
#define SFE_IPPROTO_IPV6        41      /* IPv6 in IP */
#define SFE_IPPROTO_ICMPV6      58      /* ICMP over IPv6 */
#define SFE_IPPROTO_ISIS        124     /* ISIS over IPv4 */
#define SFE_IPPROTO_RAW         255     /* raw IP packet */

/*MACRO<socket����>*/
#define SFE_SOCK_STREAM         1       /* stream socket */
#define SFE_SOCK_DGRAM          2       /* datagram socket */
#define SFE_SOCK_RAW            3       /* raw-protocol interface */

/*MACRO<����socket���Ӷ�����󳤶�>*/
#define SFE_SOMAXCONN       0x5

/*MACRO<socket����>*/
#define SFE_SOL_SOCKET      0xffff

/*MACRO<socket����ѡ��>*/
#define SFE_SO_ACCEPTCONN       0x00000002      /* socket has had listen() */
#define SFE_SO_REUSEADDR        0x00000004      /* allow local address reuse */
#define SFE_SO_KEEPALIVE        0x00000008      /* keep connections alive */
#define SFE_SO_LINGER           0x00000080      /* linger on close if data present */
#define SFE_SO_REUSEPORT        0x00000200      /* allow local address & port reuse */
#define SFE_SO_SETKEEPALIVE     0x00020000      /* setting keepalive time value and count */
#define SFE_SO_UDPCHECKSUM      0x00000800      /* set/unset udp output to calculate check sum */

#define SFE_SO_USEALLPORT       0x00008000      /* ���ú����ʹ�����ж˿ڣ������߶˶˿� */
/* Modify end */
/* 20121204������ҵVPN������������VRFѡ�� */
#define SFE_SO_SENDVPNID        0x00002000      /* ��VRF */

#define SFE_SO_SNDBUF           0x1001          /* send buffer size */
#define SFE_SO_RCVBUF           0x1002          /* receive buffer size */
#define SFE_SO_SNDLOWAT         0x1003          /* send low-water mark */
#define SFE_SO_RCVLOWAT         0x1004          /* receive low-water mark */

/*MACRO<IP����ѡ��>*/
#define SFE_IP_TOS                      3       /* long; IP type of service and preced. */
#define SFE_IP_TTL                      4       /* long; IP time to live */

/*MACRO<TCP����ѡ��>*/
#define SFE_TCP_NODELAY                 1       /* set/get tcp nodelay option */

/*MACRO<ioctl��������>*/
#define SFE_FIOASYNC            0x8004667D      /* Set/Unset socket to receive */
/* ��ǰЭ��ջֻ֧��SFE_FIOASYNC��ʽ,��Ʒʹ��ʱ���������socket���ø����� */

/* MACRO<TCP���ű��ʱ��ʱ�����÷�Χ(��λ:��)> */
#define SFE_SO_KEEPALIVE_TIMER_MIN      600
#define SFE_SO_KEEPALIVE_TIMER_MAX      7800
#define SFE_SO_KEEPALIVE_TIMER_DEFAULT  7800

/*STRUCT<����socket�첽��ʽ>*/
typedef struct  tagSFE_ASYNSOCKET
{
    UINT32 u32Value;        /* ȡֵ: 0:ȡ��socket�첽��ʽ 1:����socket�첽��ʽ. */
    UINT32 u32Resv;         /* ���� */
}SFE_ASYNSOCKET_S;

/*STRUCT<LINGERѡ���趨���ݽṹ����>*/
typedef struct tagSFE_LINGER
{
    UINT32  u32OnOff;        /* option on/off */
    UINT32  u32Linger;       /* linger time */
}SFE_LINGER_S;
#define        SFE_L_LINGER_S        sizeof(SFE_LINGER_S)

/* STRUCT<���ʱ��ʱ���趨���ݽṹ����,�ýṹ������ʾ8�ֽڶ���> */
typedef struct tagSFE_KEEPALIVESET
{
    UINT16       u16Keepintvl;                  /* ����ķ���ʱ���� */
                                                /* !!ע��:TCP����ģʽ��,u16Keepintvl������Ҫע�����¼���:(TCP�����²���עu16Keepcount)
                                                        1.���÷�Χ:[600, 7800], ��[SFE_SO_KEEPALIVE_TIMER_MIN, SFE_SO_KEEPALIVE_TIMER_MAX].
                                                        2.����Ĭ��ֵ:7800, ��SFE_SO_KEEPALIVE_TIMER_DEFAULT.
                                                        3.����ֵ��λ:��.
                                                        4.����Ҫ��:����ֵ����Ϊ600��������,�������������,������600��������ȡ��.
                                                          ����:�û�����ֵΪ:2000, ��ʵ������ֵΪ:1800*/

    UINT16       u16Keepcount;                  /* ����ķ��ʹ��� */
}SFE_KEEPALIVESET_S;
#define        SFE_L_KEEPALIVE_S   sizeof(SFE_KEEPALIVESET_S)

/*STRUCT<Ipv4��ַ�ṹ>*/
typedef struct tagSFE_IN_ADDR
{
    UINT32 s_addr;                              /* address of the socket */
}SFE_IN_ADDR_S;

/*STRUCT<Ipv4 socket��ַ�ṹ>*/
typedef struct tagSFE_SOCKADDR_IN
{
    UINT8           sin_len;                    /* zy */
    UINT8           sin_family;                 /* must be AF_INET */
    UINT16          sin_port;                   /* 16-bit port number */
    SFE_IN_ADDR_S   sin_addr;                   /* 32-bit address */
    CHAR            sin_zero[8];                /* must be 0 */
}SFE_SOCKADDRIN_S;

/*STRUCT<�����socket�ص�֪ͨ��������>*/
typedef enum enumSfeSockNotify
{
    SFE_SOCK_NOTIFY_RCVSYN = 0,                 /* 0  TCP�յ�SYN֪ͨ(TCP͸�������յ�SYN��TCP�����յ�SYN,
                                                   ��׼TCP���������յ�SYN) */
    SFE_SOCK_NOTIFY_ESTABLISHED,                /* 1  TCP�����ɹ�֪ͨ(TCP͸���������ɹ�,TCP���Ž����ɹ�,
                                                   ��׼TCP�������������ɹ�,��׼TCP���������ɹ�.
                                                   ��׼TCP���������ɹ�֮��socket��Դ���û������ͷż��������close. */
    SFE_SOCK_NOTIFY_CONNECTFAIL,                /* 2  TCP͸��������ʧ��,TCP���Ž���ʧ��,����׼TCP���˱�������ʧ��֪ͨ.
                                                   �û�����ҪҲ���ܵ���close�ر�socket,Э��ջ���Զ��ͷ�socket�����Դ. */
    SFE_SOCK_NOTIFY_ACTIVE_CONNECTFAIL,         /* 3  ��׼TCP������������ʧ��֪ͨ.�û��������close�ر�socket,
                                                   ��������socket��Դй©. */
    SFE_SOCK_NOTIFY_RCVFIN,                     /* 4  TCP�յ�FIN֪ͨ(���ӽ����ɹ�֮��֪ͨ���¼�)
                                                   (1)TCP����socket�����������socket�����ܻ�֪ͨ���¼�.�û��յ���֪ͨ��
                                                      ���븺���Ǩ��socket�������е��������ݺ�֪ͨЭ��ջ���ݰ�Ǩ���.����
                                                      ����close�ӿ�.
                                                   (2)TCP͸������socket�ͱ�׼TCP socket,�ڱ��˱�������ʱ���ܻ�֪ͨ���¼�.
                                                      �ڱ�����������ʱ����֪ͨ���¼�.��Ʒ�յ����¼������ѡ���԰�Ǩ����,
                                                      �������������close�ӿڹر�socket,��������socket��Դй©.*/
    SFE_SOCK_NOTIFY_RCVRST,                     /* 5  TCP�յ�RST֪ͨ(���ӽ����ɹ�֮��֪ͨ���¼�)
                                                   (1)TCP����socket�����������socket�����ܻ�֪ͨ���¼�..�û��յ���֪ͨ��
                                                      ���븺���Ǩ��socket�������е��������ݺ�֪ͨЭ��ջ���ݰ�Ǩ���.����
                                                      ����close�ӿ�.
                                                   (2)TCP͸������socket�ͱ�׼TCP socket,�ڱ��˱�������ʱ���ܻ�֪ͨ���¼�.
                                                      �ڱ�����������ʱ����֪ͨ���¼�.��Ʒ�յ����¼������ѡ���԰�Ǩ����,
                                                      �������������close�ӿڹر�socket,��������socket��Դй©.*/
    SFE_SOCK_NOTIFY_DISCONNECTED,               /* 6  TCP�������֪ͨ(���ӽ����ɹ�֮��֪ͨ���¼�)
                                                   (1)TCP���������������socketֻ��֪ͨһ�ζ�������¼�.socket��Դ��VISP�ͷ�.
                                                   (2)TCP͸�����������������socket���Զ���,��ֱ�֪ͨ��������¼�.
                                                   (3)��׼TCP socket��֪ͨ��������¼�.
                                                      ����VISP��������֪ͨ�û��������ʱ,�û��������close�ӿڹر�socket���ͷ���Դ.
                                                      �����û���������close�ӿں�VISP֪ͨ��������¼�,��ʱ�û��ѵ���close,VISP���ͷ���Դ,
                                                      �����û������ٵ���close.
                                                   (4)����������ɺ��쳣������ɶ�֪ͨ���¼�.VISP�����������Ҳ֪ͨ���¼�. */
    SFE_SOCK_NOTIFY_WRITE,                      /* 7  TCP���ͻ������пռ���Է�������֪ͨ.
                                                   (1)���û����÷��ͽӿ����ڷ��ͻ������ռ䲻�������ܷ���ʱ,����Э��ջ�ռ���
                                                   ����֪ͨ���¼�. */
    SFE_SOCK_NOTIFY_READ,                       /* 8  ��������֪ͨ
                                                   (1)TCP��������Ҫ�û�����ʱ֪ͨ;
                                                   (2)UDP��������Ҫ�û�����ʱ֪ͨ; */
    SFE_SOCK_NOTIFY_UDP_REORDER_CREATE,         /* 9  Э��ջ���������µ�UDP��������socket */
    SFE_SOCK_NOTIFY_UDP_REORDER_DELETE,         /* 10 Э��ջ����ɾ��UDP��������socket
                                                   (1)ֻ��Э��ջ����ɾ��UDP����socketʱ֪ͨ,�û���������close�ӿڹر�ʱ
                                                      ��֪ͨ; */
    SFE_SOCK_NOTIFY_POLICY_NOT_MATCH_SOCK,      /* 11 ��Ʒ����������·��ı��Ĵ�����Ժ�SOCK�м�¼�Ĳ��Բ�һ��,֪ͨ��Ʒ�쳣�¼�,��Ҫ��Ʒ�������� */
    SFE_SOCK_NOTIFY_MAX,
}SFE_SOCK_NOTIFY_E;

/*STRUCT<�����socket�ص�֪ͨ��Ϣ>*/
typedef struct tagSFE_SOCK_NOTIFY_INFO
{
    UINT32 u32NotifyType;                         /* ֪ͨ���� */
    UINT32 u32VcpuId;                             /* �˺� */
    UINT32 u32ConnectionId;                       /* ����id */
    UINT32 u32Direction;                          /* ���ӷ���:����,���� */
    INT32  i32Fd;                                 /* socket id */
    INT32  i32RelativeFd;                         /* �������socket id,����TCP����,TCP͸������ */
    UINT32 u32LocalIP;                            /* ���ص�ַ,�����е�Ŀ�ĵ�ַ(�����ֽ���) */
    UINT32 u32RemoteIP;                           /* Զ�˵�ַ,�����е�Դ��ַ(�����ֽ���) */
    UINT16 u16LocalPort;                          /* ���ض˿�,�����е�Ŀ�Ķ˿�(�����ֽ���) */
    UINT16 u16RemotePort;                         /* Զ�˶˿�,�����е�Դ�˿�(�����ֽ���) */
    UINT8  u8Protocol;                            /* Э��� */
    UINT8  u8Reserved[1];                         /* �����ֶ� */
    UINT16 u16VrfIndex;                           /* VPN ID */
}SFE_SOCK_NOTIFY_INFO_S;
typedef UINT32 (*g_pfSfeSockNotifyHook)(SFE_MBUF_S *pstMBuf, SFE_SOCK_NOTIFY_INFO_S *pstNotifyInfo);


UINT32 SFE_RegFuncSockNotifyHook(g_pfSfeSockNotifyHook pfRegFunc);


typedef UINT32 (*g_pfSfeGetSocketIdHook)(SFE_MBUF_S *pstMbuf, UINT32 u32ConnectionId,
                                               UINT32 u32Direction, INT32 *pi32Fd);


extern UINT32 SFE_RegFuncGetSocketIdHook(g_pfSfeGetSocketIdHook pfRegFunc);


INT32 SFE_Socket(INT32 i32Family, INT32 i32Type, INT32 i32Protocol);


INT32 SFE_Bind(INT32 i32Fd, SFE_SOCKADDRIN_S *pstSockAddr, INT32 i32AddrLen);


INT32 SFE_Listen(INT32 i32Fd, INT32 i32BackLog);


INT32 SFE_Connect(INT32 i32Fd, SFE_SOCKADDRIN_S *pstSockAddr, INT32 i32AddrLen);


INT32 SFE_SetSocketOpt(INT32 i32Fd, INT32 i32Level, INT32 i32OptName,
                       CHAR *pcOptVal, INT32 i32OptLen);


INT32 SFE_GetSocketOpt(INT32 i32Fd, INT32 i32Level, INT32 i32OptName,
                       CHAR *pcOptVal, INT32 *pi32OptLen);


INT32 SFE_Ioctl(INT32 i32Fd, UINT32 u32ReqType, CHAR *pcValue);


INT32 SFE_Close(INT32 i32Fd);


UINT32 SFE_RecvZMbuf(INT32 i32Fd, SFE_MBUF_S **ppstMBuf, UINT32 *pu32Len);


UINT32 SFE_SendZMbuf(INT32 i32Fd, SFE_MBUF_S **ppstMBuf, UINT32 *pu32Len,
                     SFE_SOCKADDRIN_S *pstSockAddr, INT32 i32AddrLen);


UINT32 SFE_SetConnectionInfo(INT32 i32Fd, UINT32 u32ConnectionId, UINT32 u32Direction);


UINT32 SFE_SetSocketGlobalDebugSwitch(UINT32 u32Switch);


UINT32 SFE_SetSocketDebugSwitchByFd(INT32 i32Fd, UINT32 u32Switch);


VOID SFE_ShowSocketByFd(INT32 i32Fd, UINT32 u32IsShowVerbose);


VOID SFE_ShowAllTcpSocket(VOID);


VOID SFE_ShowAllTcpSocketVerbose(UINT32 u32IsShowVerbose);


VOID SFE_ShowAllTcpSocketNum(UINT32 u32IsShowVerbose);


VOID SFE_ShowAllUdpSocket(VOID);


VOID SFE_ShowAllUdpSocketVerbose(UINT32 u32IsShowVerbose);


VOID SFE_ShowAllUdpSocketNum(UINT32 u32IsShowVerbose);

/*******************************************************************************
*    Func Name: SFE_SOCK_GetPoolTotalAndFreeUnitNum
* Date Created: 2012-05-03
*       Author: zhaoyue00171897
*      Purpose: ��ȡSOCK��Դ���ܵĺ�ʣ��ĵ�Ԫ��
*  Description: ��ȡSOCK��Դ���ܵĺ�ʣ��ĵ�Ԫ��
*        Input: 
*       Output: UINT32 *pu32TotalUnitNum:SOCK��Դ���ܵĵ�Ԫ��
*               UINT32 *pu32FreeUnitNum:SOCK��Դ��ʣ��ĵ�Ԫ��
*       Return: �ɹ�:SFE_SOCK_OK
*               ʧ��:������
*      Caution: �ýӿ�Ҫ��ϵͳ������ɺ���ò�����Ч
*        Since: DOPRA IP V200R003C06SPC100
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-05-03   zhaoyue00171897         Create
*
*******************************************************************************/
UINT32 SFE_SOCK_GetPoolTotalAndFreeUnitNum(UINT32 *pu32TotalUnitNum, UINT32 *pu32FreeUnitNum);

/*******************************************************************************
*    Func Name: SFE_GetSockName
* Date Created: 2012-05-16
*       Author: zhaoyue00171897
*      Purpose: ��ȡָ��ID��socket��Ӧ�ı���Э���ַ�Ͷ˿�
*  Description: ��ȡָ��ID��socket��Ӧ�ı���Э���ַ�Ͷ˿�
*        Input: INT32 i32Fd:Socket������
*               INT32 *pi32AddrLen:SFE_SOCKADDRIN_S�ṹ�ĳ���ָ��
*       Output: SFE_SOCKADDRIN_S *pstSockAddr:����ı��ص�ַ���
*               INT32 *pi32AddrLen:SFE_SOCKADDRIN_S�ṹ�ĳ���ָ��
*       Return: �ɹ�:SFE_SOCK_OK
*               ʧ��:������
*      Caution: �ýӿ�Ҫ��ϵͳ������ɺ���ò�����Ч
*        Since: DOPRA IP V200R003C06SPC100
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-05-16   zhaoyue00171897         Create
*
*******************************************************************************/
INT32 SFE_GetSockName(INT32 i32Fd, SFE_SOCKADDRIN_S *pstSockAddr, INT32 *pi32AddrLen);

#ifdef  __cplusplus
}
#endif

#endif

