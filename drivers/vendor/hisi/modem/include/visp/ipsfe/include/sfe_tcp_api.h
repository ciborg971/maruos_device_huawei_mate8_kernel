
#ifndef _SFE_TCP_API_H_
#define _SFE_TCP_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif


/*ERRORCODE<������TCPģ�������>*/
typedef enum enumSfeTcpErrCode
{
    SFE_TCP_OK = SFE_OK,                                    /* �����ɹ� */
    SFE_TCP_ERR_BEGIN = SFE_TCP_BEGIN_RET_CODE,             /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */

    SFE_TCP_GET_SFE_VCPU_MAX_NUM_PRECFG_FAIL,               /* 1  ��ȡ���VCPU����Ԥ����ֵʧ�� */
    SFE_TCP_MALLOC_TCPCB_POOL_FAIL,                         /* 2  ����TCP���ƿ���Դ��ʧ�� */
    SFE_TCP_MALLOC_SOCKTRANS_VCPU_FAIL,                     /* 3  ��ȡVCPU����ʧ�� */
    SFE_TCP_MALLOC_SOCKTRANS_VRF_FAIL,                      /* 4  ��ȡVRF����ʧ�� */
    SFE_TCP_MALLOC_SOCKTRANS_HASH_FIRESTLEVEL_FAIL,         /* 5  ��ȡһ��HASH����ʧ�� */
    SFE_TCP_MALLOC_SOCKTRANS_HASH_SECONDLEVEL_FAIL,         /* 6  ��ȡ����HASHA����ʧ�� */
    SFE_TCP_ADD_NAMEDB_SOCKTRANS_VCPU_FAIL,                 /* 7  ���VCPU���������ֿ�ʧ�� */
    SFE_TCP_GET_DORFC1323_FLAG_PRECFG_FAIL,                 /* 8  ��ȡtcp֧��rfc1323ѡ���Ԥ����ʧ��*/
    SFE_TCP_MALLOC_TCPNOW_FAIL,                             /* 9  ����TCPNOW����ʧ�� */

    SFE_TCP_MALLOC_VCPU_SOCKTIMER_MEM_FAIL,                 /* 10 ����ÿ��VCPU�ϵĶ�ʱ����Դʧ�� */
    SFE_TCP_CREATE_VCPU_200MS_TIMER_FAIL,                   /* 11 ����ÿ��VCPU�ϵ�200ms��ʱ��ʧ�� */
    SFE_TCP_CREATE_VCPU_500MS_TIMER_FAIL,                   /* 12 ����ÿ��VCPU�ϵ�500ms��ʱ��ʧ�� */
    SFE_TCP_CREATE_VCPU_LONG_TIMER_FAIL,                    /* 13 ����ÿ��VCPU�ϵ�10min��ʱ��ʧ�� */
    SFE_TCP_ADD_NAMEDB_VCPU_SOCKTIMER_FAIL,                 /* 14 ��Ӷ�ʱ����Դ�����ֹ����ʧ�� */
    SFE_TCP_GET_SFE_TCP_REORDER_REASS_NUM_PRECFG_FAIL,      /* 15  ��ȡTCP���ŵ�����������й�ģ��Ԥ����ֵʧ�� */
    SFE_TCP_GET_SFE_TCP_REORDER_REASS_CACHE_NUM_PRECFG_FAIL,/* 16 ��ȡTCP���ŵ����������ظ������ģ��Ԥ����ֵʧ�� */

    SFE_TCP_SOCK_TYPE_INVAILD_FREESOCK,                     /* 17 �ͷ�socket�Խ���TCP���ŷ�ͨʱ,socket�ڵ����Ͳ���TCP���� */
    SFE_TCP_PREPROCESS_HEADERLEN_INVALID,                   /* 18 ����TCP����Ԥ��������TCPͷ���Ȳ��Ϸ�  */
    SFE_TCP_RCVACK_NO_ACK,                                  /* 19 ����TCP����ACK����ʱ,����ACK��־û����λ  */
    SFE_TCP_RCVACK_SYN_RECEIVED_ACKSEQ_INVALID,             /* 20 ����TCP����ACK����ʱ,�յ��������������һ��ACK��Ŵ���  */
    SFE_TCP_RCVACK_DUPLICATE_ACK_LESS_THAN_THREE,           /* 21 ����TCP����ACK����ʱ,�յ��ظ�ACK���ظ�����������3  */
    SFE_TCP_RCVACK_DUPLICATE_ACK_MORE_THAN_THREE,           /* 22 ����TCP����ACK����ʱ,�յ��ظ�ACK���ظ���������3  */
    SFE_TCP_RCVACK_DROP_OLD_ACK,                            /* 23 ����TCP����ACK����ʱ,�յ�һ�����ϵ�ACK */
    SFE_TCP_RCVACK_LAST_ACK,                                /* 24 ����TCP����ACK����ʱ,�յ����һ��ACK */
    SFE_TCP_RCVACK_AT_TIME_WAIT,                            /* 25 ����TCP����ACK����ʱ,TIME WAIT״̬�յ�ACK */
    SFE_TCP_HEADERFLAG_INVALID,                             /* 26 TCP��־λ���Ϸ� */
    SFE_TCP_CHECKSUM_FAIL,                                  /* 27 TCPУ��ͼ��ʱ���� */
    SFE_TCP_DROP_TAIL_DATA_FAILED,                          /* 28 TCPԤ����ʱ����IP������С��mbuf�ܳ���,ɾ��mbufβ������ʧ�� */
    SFE_TCP_NO_RLTVSOCKCB_CREATEPROXY,                      /* 29 ������������Ӵ���ʱ����ȡ����socket���ƿ鲻���� */
    SFE_TCP_REORDEROUT_MBUFBACKWARD_FAIL,                   /* 30 TCP�������ʱMBUFָ���λʧ�� */
    SFE_TCP_SOCK_TYPE_INVAILD_DATATRANSOVER,                /* 31 ֪ͨTCP�������ݰ�Ǩ���ʱ,socket�ڵ����Ͳ���TCP���� */
    SFE_TCP_NO_TCPCB_DATATRANSOVER,                         /* 32 ֪ͨTCP�������ݰ�Ǩ���ʱ,û��TCPCB���ƿ� */
    SFE_TCP_NO_RLTVSOCKCB_DATATRANSOVER,                    /* 33 ֪ͨTCP�������ݰ�Ǩ���ʱ,��ȡ�Ĺ���SOCK���ƿ�Ƿ� */
    SFE_TCP_NO_RLTVTCPCB_DATATRANSOVER,                     /* 34 ֪ͨTCP�������ݰ�Ǩ���ʱ,û�й���TCPCB���ƿ� */
    SFE_TCP_NO_CACHEPKT_DATATRANSOVER,                      /* 35 ֪ͨTCP�������ݰ�Ǩ���ʱ,�޻���Ķ��������� */
    SFE_TCP_STATE_INVALID_DATATRANSOVER,                    /* 36 ֪ͨTCP�������ݰ�Ǩ���ʱ,TCP����socket��״̬�Ƿ� */
    SFE_TCP_REODERIN_MBUFFORWARD_FAIL,                      /* 37 TCP���Ž��ձ���ʱ,ƫ�Ƶ�TCPIPͷʱ���� */
    SFE_TCP_REODERIN_OVER_WINDOW,                           /* 38 TCP���Ž��ձ���ʱ,���ĳ������� */
    SFE_TCP_CFG_TYPE_INVAILD_IOCTL,                         /* 39 ����ioctlʱ��������ID��֧�ֻ�Ƿ� */
    SFE_TCP_CFG_FIOASYN_PARA_INVAILD_IOCTL,                 /* 40 ����ioctl SFE_FIOASYNCʱ���ò���ֵ�Ƿ� */
    SFE_TCP_FREE_SOCKET_VCPUID_INVALID,                     /* 41 �ͷ�socket�ڵ�ʱ,��ȡvcpu��Ч */
    SFE_TCP_VCPUID_INVALID_DATATRANSOVER,                   /* 42 �������ݴ������ʱ,��ȡvcpu��Ч */
    SFE_TCP_REASS_INPUT_MBUF_VALID,                         /* 43 TCP����ʱ���뱨�ķǷ� */
    SFE_TCP_REASS_MBUFFORWARD_FAIL,                         /* 44 TCP����ʱ����ͷƫ�Ƶ�������ʱʧ�� */
    SFE_TCP_REASS_DISCONNECT_NODATA,                        /* 45 TCP����ʱ, �������ݷ��ֶ���������û������, ����������,
                                                                    �ͷ�������к����黺�� */
    SFE_TCP_REASS_DISCONNECT,                               /* 46 TCP����ʱ, �������ݷ��ֶ�������, ����������,
                                                                    �ͷ�������к����黺�� */
    SFE_TCP_REASS_NUM_FULL,                                 /* 47 TCP���ŵ�����ʱ,������������� */
    SFE_TCP_REODERREASSIN_CACHE_NUM_FULL,                   /* 48 TCP���ŵ�����ʱ,���������ظ�������*/
    SFE_TCP_REODERREASSIN_MBUFFORWARD_FAIL,                 /* 49 TCP���ŵ�����������з����ظ��������ظ����洦��,
                                                                    ��β������ƫ�ƻ�ԭʱʧ�� */
    SFE_TCP_QUENCH,                                         /* 50 ΪSFE_TCP_Quench��������Ĵ����� */
    SFE_TCP_FIRSTFORECAST_FAILD,                            /* 51 TCP���ձ��Ĵ���,�ײ�Ԥ�ⲻ�ɹ� */
    SFE_TCP_RCVRST_SEQ_ERR,                                 /* 52 TCP���ձ��Ĵ���,RST���Ĵ���,������Ų��� */
    SFE_TCP_NEWCONNECT_GET_NEW_SOCKTRANSCB_FAILED,          /* 53 TCP���ձ��Ĵ���,�����½�TCP����ʱ��ȡ�µ�SockTransCBʧ�� */
    SFE_TCP_FILLHEADER_MOVE_BACK_MBUF_HEAD_FAILED,          /* 54 TCP���ͱ��Ĵ���,��䱨��ͷʱ,��MBUF����ָ������ƶ�TCP/IPͷ���ȹ���ʧ�� */
    SFE_TCP_STANDARDINPUT_GET_SOCKTRANSCB_FAILED,           /* 55 TCP���ձ��Ĵ���,��׼���������,��ʾ�������ֻ�ȡSockTransCBʧ�� */
    SFE_TCP_STANDARDINPUT_TCP_CLOSED,                       /* 56 TCP���ձ��Ĵ���,��׼���������,�����Ѿ�����,�����û���û�йرո�socket */
    SFE_TCP_DATAPREPROCESS_DROP_DUPSYN,                     /* 57 TCP���ձ��Ĵ���,����Ԥ����,��ʾ�������¶���������ɺ��յ���SYN���� */
    SFE_TCP_DATAPREPROCESS_DROP_DUPRST,                     /* 58 TCP���ձ��Ĵ���,����Ԥ����,�����ظ���RST���� */
    SFE_TCP_DATAPREPROCESS_DROP_SEQ_ERR_DATARST,            /* 59 TCP���ձ��Ĵ���,����Ԥ����,�������ظ����ݵ�RST����,ֻҪRST���Ĳ��������Ľ������ֱ�ӻ�ACK���� */
    SFE_TCP_DATAPREPROCESS_RCVDATA_AFTER_CLOSE,             /* 60 TCP���ձ��Ĵ���,����Ԥ����,�û��Ѿ�����������close�����ر�socket,���յ����ݱ��� */
    SFE_TCP_DATAPREPROCESS_DROP_DATA_EXCEED_WINDOW,         /* 61 TCP���ձ��Ĵ���,����Ԥ����,�յ���ȫ�������մ��ڵı��� */
    SFE_TCP_DATAPREPROCESS_DROP_DATA_EXCEED_WINDOW_AFTER_ESTABLISHED,  /*  62  TCP���ձ��Ĵ���,����Ԥ����,���ӽ�����ɺ����ȫ�������մ��ڵı��� */
    SFE_TCP_RCVSYN_RCVRST_AT_LISTEN,                        /* 63 TCP���ձ��Ĵ���,��ʾ�����յ�SYN����,LISTEN״̬�յ�RST���� */
    SFE_TCP_RCVSYN_RCVACK_AT_LISTEN,                        /* 64 TCP���ձ��Ĵ���,��ʾ�����յ�SYN����,LISTEN״̬�յ�ACK���� */
    SFE_TCP_RCVSYN_RCVNOSYN_AT_LISTEN,                      /* 65 TCP���ձ��Ĵ���,��ʾ�����յ�SYN����,LISTEN״̬�յ�����SYN��־�ı��� */
    SFE_TCP_RCVSYN_RCVDSTMULTICAST_AT_LISTEN,               /* 66 TCP���ձ��Ĵ���,��ʾ�����յ�SYN����,LISTEN״̬�յ��㲥���߶ಥ���� */
    SFE_TCP_RCVSYN_INVALID_ACK_AT_SYN_SENT,                 /* 67 TCP���ձ��Ĵ���,��ʾ�����յ�SYN����,SYN SENT״̬�յ������ACK���� */
    SFE_TCP_RCVSYN_RCVRST_AT_SYN_SENT,                      /* 68 TCP���ձ��Ĵ���,��ʾ�����յ�SYN����,SYN SENT״̬�յ�RST���� */
    SFE_TCP_RCVSYN_RCVNOSYN_AT_SYN_SENT,                    /* 69 TCP���ձ��Ĵ���,��ʾ�����յ�SYN����,SYN SENT״̬�յ�����SYN��־�ı��� */
    SFE_TCP_RCVSYN_RCVRST_AT_SYN_SENT_DROPTCP,              /* 70 TCP��������,����SYN���ĺ��յ�RST����,����ʧ��,�������� */
    SFE_TCP_SYNRCV_STATE_RCV_INVALID_SYN_DROPTCP,           /* 71 TCP��������,�յ�SYN���ĺ����յ��Ƿ�(���ظ�)��SYN����,����ʧ��,�������� */

    SFE_TCP_CREATEBYCOPYBUF_ENOBUFS_ALLOCPACKET,            /* 72 TCP���ʹ���MBuf,ͨ���������洴��MBuf,û��BUF���� */
    SFE_TCP_CREATEMBUF_ENOBUFS_ALLOCPACKET,                 /* 73 TCP���ʹ���MBuf,����MBuf,û��BUF���� */

    SFE_TCP_TCPT_PERSIST_ETIMEDOUT,                         /* 74 TCP��ʱ����ʱ,��ֶ�ʱ����ʱ,����һ��ʱ��Ͽ����� */
    SFE_TCP_TCPT_ESTABLIST_ETIMEDOUT,                       /* 75 TCP��ʱ����ʱ,���ʱ����ʱ,���ӽ���ʱ��ʱ */
    SFE_TCP_TCPT_KEEP_SET_ETIMEDOUT,                        /* 76 TCP��ʱ����ʱ,���ʱ����ʱ,�û������˱��ʱ����ֵ */
    SFE_TCP_TCPT_KEEP_DEFAULT_ETIMEDOUT,                    /* 77 TCP��ʱ����ʱ,���ʱ����ʱ,Ĭ�ϱ��ʱ����ֵ */
    SFE_TCP_TCPT_KEEP_NO_KEEPALIVE,                         /* 78 TCP��ʱ����ʱ,���ʱ����ʱ,û����keep aliveѡ�� */
    SFE_TCP_TCPT_REXMT_ETIMEDOUT,                           /* 79 TCP��ʱ����ʱ,��ʱ�ش���ʱ����ʱ */
    SFE_TCP_GET_TCPREORDER_KEEPALIVE_TM_SWITCH_FAILD,       /* 80 TCP�ش����ʱ������״̬��ȡʧ�� */

    SFE_TCP_REORDER_FILLHEADER_MBUFHEAD_BACKWARD_FAILED,    /* 81 TCP�����������ͱ���MBUF����ƫ�Ƶ��ײ�ʱʧ��*/
    SFE_TCP_REORDER_FILLHEADER_MBUFHEAD_FORWARD_FAILED,     /* 82 TCP�����������ͱ���MBUFǰ��ƫ�ƹ��ײ�ʱʧ��*/

    SFE_TCP_REORDER_SEND_NULL_POINTER,                      /* 83 TCP���������������ʱMBUFָ��Ϊ�� */
    SFE_TCP_REORDER_SEND_DATALEN_INVALID,                   /* 84 TCP���������������ʱMBUF������Ч */
    SFE_TCP_REORDER_SEND_MBUF_DB_RESERVE_NOTENOUGH,         /* 85 TCP���������������ʱMBUF�ײ�Ԥ�����Ȳ���128�ֽ� */
    SFE_TCP_REORDER_SEND_VCPUID_INVALID,                    /* 86 TCP���������������ʱ��ȡ��VCPUID�Ƿ� */
    SFE_TCP_REORDER_SEND_SOCKTYPE_INVALID,                  /* 87 TCP���������������ʱsocket���ͷǷ� */
    SFE_TCP_REORDER_SEND_FILL_TCPIPHEAD_FAILED,             /* 88 TCP���������������ʱ���tcpip�ײ�ʱʧ�� */
    SFE_TCP_REORDER_CLOSE_VCPUID_INVALID,                   /* 89 TCP������������RST����ʱ��ȡ��VCPUID�Ƿ� */
    SFE_TCP_REORDER_CLOSE_SOCKTYPE_INVALID,                 /* 90 TCP������������RST����ʱ��ȡ��socktrans���ڵ㲻��tcp���ŵ� */
    SFE_TCP_REORDER_CLOSE_SOCKRLTVTYPE_INVALID,             /* 91 TCP������������RST����ʱ��ȡ��socktrans���ڵ㲻��tcp���ŵ� */
    SFE_TCP_PROXYCREATE_NOSOCK_AND_NOTSYNPKT,               /* 92 TCP���Ż�͸��������ʱ�յ��ı���û�ж�Ӧsocket���ղ��Ҳ���SYN���� */
    SFE_TCP_FREESOCKET_MODULE_NOT_INIT,                     /* 93 TCP���ŵ��������ͷ�socket�ӿ�ʱģ�黹û�г�ʼ�� */
    SFE_TCP_REORDER_DATA_TRANSFER_COMPLETE_MODULE_NOT_INIT, /* 94 TCP���ŵ������ݰ�Ǩ�ӿ�ʱģ�黹û�г�ʼ�� */
    SFE_TCP_REORDER_ACTIVE_SEND_PKT_MODULE_NOT_INIT,        /* 95 TCP���ŵ����������ͱ��Ľӿ�ʱģ�黹û�г�ʼ�� */
    SFE_TCP_REORDER_CLOSE_SOCKET_MODULE_NOT_INIT,           /* 96 TCP���ŵ��������رսӿ�ʱģ�黹û�г�ʼ�� */
    SFE_TCP_PROXY_NOTIFY_RCVSYN_FAIL,                       /* 97 TCP��������Ž���ʱ֪ͨ�յ�SYN�¼���Ʒ������ʧ�� */
    SFE_TCP_GET_CHSUM_FLAG_PRECFG_FAIL,                     /* 98 ��ȡTCPУ���Ԥ����ʧ�� */
    SFE_TCP_STANDARDINPUT_TCPCB_IS_NULL,                    /* 99 ��׼TCP���մ������TCPCBΪNULL */
    SFE_TCP_CREATEPROXY_TCPCB_IS_NULL,                      /* 100 �������������Socket�ڵ�ʱ,TCPCBΪNULL */
    SFE_TCP_CREATEPROXY_RELATIVE_TCPCB_IS_NULL,             /* 101 �������������Socket�ڵ�ʱ,������TCPCBΪNULL */
    SFE_TCP_PREPROCESS_MBUF_CONTINUOUS_FAIL,                /* 102 ��MBUF�е�DB������ʧ�� */
    SFE_TCP_REORDER_CLOSE_SOCKID_NOT_MATCH,                 /* 103 TCP���ŵ��������رսӿ����������SOCKET IDδ������ */
    SFE_TCP_MALLOC_TCPREORDER_CURSTAT_FAIL,                 /* 104 TCP��ʼ��ʱ����TCP���ż�¼��ǰ�����ڴ�ʧ�� */
    SFE_TCP_MALLOC_TCPREORDER_PRESTAT_FAIL,                 /* 105 TCP��ʼ��ʱ����TCP���ż�¼ǰ�β����ڴ�ʧ�� */
    SFE_TCP_MALLOC_TCPREORDER_VCPU_SAMPLENOTIFY_CONNDLY_FAIL,/* 106 TCP��ʼ��ʱ����TCP����ʱ�Ӳ�����¼���ڴ�ʧ��*/
    SFE_TCP_MALLOC_TCPREORDER_CURALLCONNECTS_FAIL,          /* 107 TCP��ʼ��ʱ����TCP���Ų������Ӳ�����¼���ڴ�ʧ�� */
    SFE_TCP_MALLOC_TCPREORDER_SAMPLEGEN_FAIL,               /* 108 TCP��ʼ��ʱ����TCP���Ų�������ڴ�ʧ�� */
    SFE_TCP_MALLOC_TCPREORDER_SAMPLEPARA_FAIL,              /* 109 TCP��ʼ��ʱ����TCP���Ų��������ڴ�ʧ�� */
    SFE_TCP_MALLOC_TCPREORDER_SAMPLETIMER_MEM_FAIL,         /* 110 TCP��ʼ��ʱ����TCP���Ų�����ʱ���ڴ�ʧ�� */
    SFE_TCP_CREATE_TCPREORDER_SAMPLETIMER_INTERVALTIMER_FAIL,/* 111 TCP��ʼ��ʱ�������������ʱ��ʧ�� */
    SFE_TCP_CREATE_TCPREORDER_SAMPLETIMER_STEPTIMER_FAIL,   /* 112 TCP��ʼ��ʱ��������ʱ����ʱ��ʧ�� */
    SFE_TCP_ADD_NAMEDB_TCPREORDER_SAMPLETIMER_FAIL,         /* 113 TCP��ʼ��ʱ��Ӳ�����ʱ���������ڴ�ʧ�� */
    SFE_TCP_ERR_SAMPLEOUTPUT_POINTNULL,                     /* 114 TCP���Ų����ص�����ע��ʧ��,ע�ṳ��Ϊ�� */
    SFE_TCP_REORDER_SET_SAMPLE_INFO_MODULE_NOT_INIT,        /* 115 TCP���Ų�������ʱϵͳδ��ʼ�� */
    SFE_TCP_REORDER_SET_SAMPLE_INFO_VCPUID_INVALID,         /* 116 TCP���Ų�������ʱ��ȡ�ĵ�ǰ�˺ŷǷ� */
    SFE_TCP_REORDER_ENABLE_SAMPLE_INPUTPARA_INVALID,        /* 117 TCP���Ų�������ʱ,ʹ�ܲ���ʱ����������Ϸ� */
    SFE_TCP_REORDER_SET_SAMPLEINFO_INPUTPARA_INVALID,       /* 118 TCP���Ų�������ʱ����������Ϸ� */
    SFE_TCP_REORDER_SET_SAMPLE_INPUT_PARAPOINT_NULL,        /* 119 TCP���Ų�������ʱ���������ָ��Ϊ�� */
    SFE_TCP_REODERIN_IS_REDIRECTION,                        /* 120 TCP���������ض�������⴦�� */
    SFE_TCP_REORDER_SEND_SOCKTRANSRLTV_INVALID,             /* 121 TCP�������ض���ʱ��ȡ�Զ˽ڵ�Ƿ� */
    SFE_TCP_REODERIN_IS_REDIRECTION_AOC_CACHEPKT_NULL,      /* 122 TCP���������ض������ƿ黺�屨��Ϊ�� */
    SFE_TCP_REORDER_SEND_MBUF_NO_DIRECTION,                 /* 123 TCP�����ض���ʱ���뱨��û�����������з��� */
    SFE_TCP_REORDER_REDIRECTION_CREATE_RST_FAILED,          /* 124 TCP�����ض������RST���Ĵ���ʧ�� */
    SFE_TCP_REORDER_REDIRECTION_FILL_RST_HEADER_FAILED,     /* 125 TCP�����ض������RST������TCPͷʧ�� */
    SFE_TCP_REORDER2PROXY_MODULE_NOT_INIT,                  /* 126 ϵͳδ��ʼ����ִ��TCP����ת͸������ʧ�� */
    SFE_TCP_REORDER2PROXY_INVALID_PARA,                     /* 127 TCP����ת͸��������socketID�Ƿ� */
    SFE_TCP_REORDER2PROXY_VCPUID_INVALID,                   /* 128 TCP����ת͸������˺ŷǷ� */
    SFE_TCP_REORDER2PROXY_SOCKET_NOT_MATCH,                 /* 129 TCP����ת͸��������socket��ƥ�� */
    SFE_TCP_REORDER2PROXY_CID_NOT_MATCH,                    /* 130 TCP����ת͸��������CID��ƥ�� */
    SFE_TCP_REORDER2PROXY_UENODE_MODE_NOT_MATCH,            /* 131 TCP����ת͸��������ģ��UEģʽ�Ƿ� */
    SFE_TCP_REORDER2PROXY_SPNODE_MODE_NOT_MATCH,            /* 132 TCP����ת͸��������ģ��SPģʽ�Ƿ� */
    SFE_TCP_REORDER2PROXY_NOT_ESTABLISH_STATE,              /* 133 TCP����ת͸��������socketδ�����ɹ� */
    SFE_TCP_REORDER2PROXY_HAVE_SENT_DATA,                   /* 134 TCP����ת͸������,�ϲ�ת�������� */
    SFE_TCP_REORDER2PROXY_HAVE_SENT_302_DATA,               /* 135 TCP����ת͸������,�ϲ��������ŵ�302�ض��� */
    SFE_TCP_REODERIN_RCV_DUPPKT_BEFORE_POLICY_SURE,         /* 136 TCP����ģʽ���ϲ�δ�����Ƿ�Ҫת͸������,�յ��ش����� */
    SFE_TCP_INPUT_REORDER_SOCK_RCV_NOT_MATCH_POLICY_PKT,    /* 137 TCP����ģʽ���յ��ı��Ĳ��Բ�������,�˳� */
    SFE_TCP_STANDARDINPUT_RCV_PKT_POLICY_NOT_MATCH,         /* 138 TCP����ģʽ���յ��ı��Ĳ��Բ�ƥ��,�˳� */
    SFE_TCP_GET_UPDATEWND_FLAG_PRECFG_FAIL,                 /* 139 TCP��ʼ��ʱ��ȡ���ջ����ȡ����������ͨ���Ԥ����,ʧ���˳� */
    SFE_TCP_GET_UPDATE_ZEROWND_FLAG_PRECFG_FAIL,            /* 140 TCP��ʼ��ʱ��ȡ���ֳ�����������0����ͨ���Ԥ����,ʧ���˳� */
    SFE_TCP_REORDEROUT_MBUFNOTCPHDR_FAIL,                   /* 141 TCP�����´�MBUF�л�ȡ����ʱ���õ�TCPͷΪ��,ʧ���˳� */
    SFE_TCP_RCVACK_DROP_ACK_TOOMUCH,                        /* 142 TCP�������TCP����ACK����ʱ,�յ�һ����δ�������ݵ�ACK*/
    SFE_TCP_REORDER2PROXY_GET_UENODE_FAILED,                /* 143 TCP����ת͸�������ȡ�Զ�socket�ڵ�ʧ�� */
    SFE_TCP_MALLOC_FAIL_TCPSTAT,                            /* 144 ��ʼ��ʱ����TCPͳ�ƹ�������ռ�ʧ�� */
    SFE_TCP_FIRSTFORECAST_FAILD_PUREACK,                    /* 145 ��ACK�����ײ�Ԥ��ʧ�� */
    SFE_TCP_FIRSTFORECAST_FAILD_REASSPKT,                   /* 146 ��ǰ���Ĳ��ܴ��������������,�ײ�Ԥ��ʧ�� */
    SFE_TCP_GET_POOLUNITNUM_BEFORE_INIT,                    /* 147 ��ϵͳ��ʼ��ǰ,���ܻ�ȡ��TCP��Դ��ͳ�� */
    SFE_TCP_GET_POOLUNITNUM_INPUT_PARA_INVALID,             /* 148 ��ȡTCP��Դ��ͳ��ʱ,����Ĳ����ж�ʧ�� */
    SFE_TCP_GET_POOLUNITNUM_INPUT_FAILED,                   /* 149 ��ȡTCP��Դ��ͳ��ʱ,��ȡ���Ŀ��е�Ԫ���Ƿ�*/
    SFE_TCP_GET_MSL_TIME_PRECFG_FAIL,                       /* 150 TCP��ʼ��ʱ��ȡMSL�ϻ���ʱʱ���Ԥ����,ʧ���˳� */
    SFE_TCP_GET_DELAYED_ACK_SWITCH_PRECFG_FAIL,             /* 151 TCP��ʼ��ʱ��ȡ�ӳ�ACK���ص�Ԥ����,ʧ���˳� */    
    SFE_TCP_REORDER_REDIRECTION_HAVE_BEEN_CALLED,           /* 152 TCP���������ض��� */
    SFE_TCP_REASSRXMT_CNT_PRECFG_FAIL,
    SFE_TCP_MALLOC_SOCKTRANS_HASH_EXACT_FAIL,               /* 154 ��ȡHASH����ʧ�ܣ��ñ��˶˿ڡ�����IP��Զ�˶˿ڡ�Զ��IP��VRF���������� */
    SFE_TCP_MALLOC_SOCKTRANS_HASH_LPORT_FAIL,               /* 155 ��ȡHASH����ʧ�ܣ��ñ��˶˿����������� */
}SFE_TCP_ERR_CODE_E;

/*MACRO<���Խ���TCPճ������>*/
#define SFE_TCP_CAN_SPLICE   1
/*MACRO<�����Խ���TCPճ������>*/
#define SFE_TCP_CAN_NOT_SPLICE 0
UINT32 SFE_TCP_IsCanSplice(INT32 i32UeFd, INT32 i32SpFd, UINT32 *pu32IsCanSplice);


UINT32 SFE_TCP_Splice(INT32 i32UeFd, INT32 i32SpFd, UINT32 u32ConnectionId);

/*MACRO<TCPճ���ɹ� >*/
#define SFE_TCP_SPLICE_SUCCESS      0
/*MACRO<TCPճ��ʧ�� >*/
#define SFE_TCP_SPLICE_FAIL         1

/*STRUCT<TCPճ���ص�֪ͨ��Ϣ >*/
typedef struct tagSFE_TCP_SPLICE_NOTIFY_INFO
{
    UINT32 u32TcpSpliceType;                       /* TCPճ������ */
    UINT32 u32ConnectionId;                        /* ����id */
    UINT32 u32TcpSpliceResult;                     /* TCPճ�����:
                                                      (1)ȡֵ����: TCPճ���ɹ�: SFE_TCP_SPLICE_SUCCESS
                                                                   TCPճ��ʧ��: SFE_TCP_SPLICE_FAIL
                                                      (2)ֻ����ճ���ɹ�ʱ������������Ч. */
    /* ͸������ճ��������� */
    INT32  i32UeToSpSeqDiff;                       /* UE��SP���ĵ���Ų�ֵ */
    INT32  i32UeToSpAckSeqDiff;                    /* UE��SP���ĵ�ack��Ų�ֵ */
    INT32  i32SpToUeSeqDiff;                       /* SP��UE���ĵ���Ų�ֵ */
    INT32  i32SpToUeAckSeqDiff;                    /* SP��UE���ĵ�ack��Ų�ֵ */

    /* ͸�������ض�������ճ��������������,���²��������ض�����ճ����Ч. */
    UINT32 u32OldMss;                              /* �ض���ǰԭ���ӵ�MSSֵ */
    UINT32 u32NewMss;                              /* �ض���������ӵ�MSSֵ */
    UINT32 u32UeWndScale;                          /* UE�˴�����������ֵ */
    UINT32 u32LocalWndScale;                       /* ���ش�����������ֵ */
    UINT32 u32OldSpWndScale;                       /* ԭSP�˴�����������ֵ */
    UINT32 u32NewSpWndScale;                       /* ��SP�˴�����������ֵ */
    UINT32 u32Res;                                 /* �����ֶ� */
}SFE_TCP_SPLICE_NOTIFY_INFO_S;
typedef UINT32 (*g_pfSfeTcpSpliceCompleteNotifyHook)(SFE_TCP_SPLICE_NOTIFY_INFO_S *pstNotifyInfo);


UINT32 SFE_RegFuncTcpSpliceNotifyHook(g_pfSfeTcpSpliceCompleteNotifyHook pfRegFunc);

/* �û�̬������:����ʹ�ܿ���,ʹ�� */
#define SFE_TCP_REORDER_SAMPLE_ENABLE           1
/* �û�̬������:����ʹ�ܿ���,ȥʹ�� */
#define SFE_TCP_REORDER_SAMPLE_DISABLE          0

/* �û�̬������:��������,�������� */
#define SFE_TCP_REORDER_SAMPLE_CONNINFO         0x01
/* �û�̬������:����ʱ�� */
#define SFE_TCP_REORDER_SAMPLE_CONNDELAY        0x02
/* �û�̬������:����ָ�������������,��������,����ʱ�� */
#define SFE_TCP_REORDER_SAMPLE_ALL              0x03

/* �û�̬������:���������Сֵ */
#define SFE_TCP_REORDER_SAMPLE_INTERVAL_MIN     10
/* �û�̬������:����������ֵ */
#define SFE_TCP_REORDER_SAMPLE_INTERVAL_MAX     3600
/* �û�̬������:����ʱ����Сֵ */
#define SFE_TCP_REORDER_SAMPLE_STEP_MIN         1
/* �û�̬������:����ʱ�����ֵ */
#define SFE_TCP_REORDER_SAMPLE_STEP_MAX         50
/* �û�̬������:����������Сֵ */
#define SFE_TCP_REORDER_SAMPLE_COUNT_MIN        1
/* �û�̬������:�����������ֵ */
#define SFE_TCP_REORDER_SAMPLE_COUNT_MAX        50

/*STRUCT<TCP���Ų������ò��� >*/
typedef struct tagSFE_TCP_REORDER_SAMPLE_PARA
{
    UINT32  u32Switch;                      /* ��������,�Ƿ�ʹ�ܲ���<SFE_TCP_REORDER_SAMPLE_DISABLE, SFE_TCP_REORDER_SAMPLE_ENABLE> */
    UINT32  u32Type;                        /* ��������,����:�������ʺͲ�����,����ʱ��,���඼��<SFE_TCP_REORDER_SAMPLE_CONNINFO, SFE_TCP_REORDER_SAMPLE_ALL> */
    UINT32  u32Interval;                    /* �������<SFE_TCP_REORDER_SAMPLE_INTERVAL_MIN, SFE_TCP_REORDER_SAMPLE_INTERVAL_MAX>, ��λ��
                                               ��������ڰ������õĲ���ʱ���Ͳ�����������,������ʱ��x��������С�ڲ������ */
    UINT32  u32Step;                        /* ����ʱ��<SFE_TCP_REORDER_SAMPLE_STEP_MIN, SFE_TCP_REORDER_SAMPLE_STEP_MAX>, ��λ�� */
    UINT32  u32Count;                       /* ��������<SFE_TCP_REORDER_SAMPLE_COUNT_MIN, SFE_TCP_REORDER_SAMPLE_COUNT_MAX> */
    UINT32  u32Resv;
}SFE_TCP_REORDER_SAMPLE_PARA_S;

/*STRUCT<TCP�����ص�֪ͨ��Ϣ:�������ʺͲ������� >*/
typedef struct tagSFE_TCP_REORDER_SAMPLE_NOTIFY_CONN_INFO
{
    UINT32  u32VcpuId;                      /* ��ǰ���ں˺� */
    UINT32  u32Resv;
    UINT64  u64CurAllConnects;              /* ��ǰ��TCP����������,ָ״̬����establish���������� */
    UINT32  u32TcpConnectedPS;              /* ÿ��ɹ�TCP������,ָÿ��״̬תΪestablish������ */
    UINT32  u32TcpConnectingPS;             /* ÿ�볢��TCP������������,�����ɹ����������ڽ��������� */
    UINT32  u32TcpClosedCPS;                /* ÿ��ɹ��رյ�TCP������,ָÿ��ɹ��ͷ�socket��Դ�������� */
    UINT32  u32TcpClosingCPS;               /* ÿ�볢�Թرյ�TCP������,ָÿ���establish״̬ת���������� */
    UINT64  u64TcpConnectingPPS;            /* ÿ�������TCP����������,ָÿ�봦�ڽ���״̬���ӽ��յ������б����� */
    UINT64  u64TcpDupPPS;                   /* ÿ�������TCP�ش������� */
    UINT64  u64TcpDupBPS;                   /* ÿ�������TCP�ش��ֽ��� */
    UINT64  u64TcpOOPPS;                    /* ÿ�������TCP�������� */
    UINT64  u64TcpOOBPS;                    /* ÿ�������TCP�����ֽ��� */
    UINT32  u32CurSysTime;                  /* ��ǰ����������ʱ��ϵͳʱ��,��λ���� */
    UINT32  u32CurSysCpuRate;               /* ��ǰ����������ʱ��CPUռ���� */
}SFE_TCP_REORDER_SAMPLE_NOTIFY_CONN_INFO_S;

/*STRUCT<TCP�����ص�֪ͨ��Ϣ:����ʱ�� >*/
typedef struct tagSFE_TCP_REORDER_SAMPLE_NOTIFY_DELAY_INFO
{
    UINT32  u32VcpuId;                      /* ��ǰ���ں˺� */
    UINT32  u32TcpConnDelayMax;             /* ��ǰ����ʱ��TCP���ӽ������ʱ��,��λ���� */
    UINT32  u32TcpConnDelayMin;             /* ��ǰ����ʱ��TCP���ӽ�����Сʱ��,��λ���� */
    UINT32  u32TcpConnDelayAvg;             /* ��ǰ����ʱ��TCP���ӽ���ƽ��ʱ��,��λ���� */
    UINT32  u32CurSysTime;                  /* ��ǰ����������ʱ��ϵͳʱ��,��λ���� */
    UINT32  u32CurSysCpuRate;               /* ��ǰ����������ʱ��CPUռ���� */
}SFE_TCP_REORDER_SAMPLE_NOTIFY_DELAY_INFO_S;
UINT32 SFE_SetTcpReorderSampleInfo(SFE_TCP_REORDER_SAMPLE_PARA_S* pstSamplePara);


typedef UINT32 (*g_pfSfeTcpReorderSampleOutputHook)(UINT32 u32Type, VOID *pstSampleStatInfo);


UINT32 SFE_RegFuncTcpSampleOutputHook(g_pfSfeTcpReorderSampleOutputHook pfRegFunc);

/*STRUCT< TCP�ض������ >*/
typedef struct tagSFE_TCP_REDIRECTION_INFO
{
    INT32  i32SpFd;         /* ��ԭSP�������socket id(��ģ��UE socket id) */
    UINT32 u32ConnectionId; /* ��Ʒ������id */
    UINT32 u32Direction;    /* socket���������� */
    UINT32 u32LocalIpAddr;  /* �ض������SP socket�ı��ص�ַ,�û�����ָ���ò��� */
    UINT16 u16LocalPort;    /* �ض������SP socket�ı��ض˿ں�,�û����Բ�ָ���ò���,
                               ���û�ָ����ֵΪ0ʱ,Э��ջ���Զ�Ϊ�����һ�����ض˿ں�. */
    UINT32 u32NewSpIpAddr;  /* �ض������SP�ĵ�ַ(����SP socket��Զ�˵�ַ) */
    UINT16 u16NewSpPort;    /* �ض������SP�Ķ˿ں�(����SP socket��Զ�˶˿ں�) */
}SFE_TCP_REDIRECTION_INFO_S;


UINT32 SFE_TCP_Redirection(SFE_TCP_REDIRECTION_INFO_S *pstTcpRedirectionInfo,
                                  INT32 *pi32NewSpFd);


UINT32 SFE_TCP_ReorderToProxy(INT32 i32UeFd, INT32 i32SpFd, UINT32 u32ConnectionId);


UINT32 SFE_TCP_ReorderDataTransferComplete(INT32 i32Fd);


UINT32 SFE_TCP_ReorderActiveSendPktAndCloseSocket(INT32 i32Fd, SFE_MBUF_S *pstMBuf);


UINT32 SFE_TCP_ReorderCloseSocket(INT32 i32UeFd, INT32 i32SpFd);


UINT32 SFE_TCP_FreeSocket(INT32 i32Fd);

/* TCPͳ�ƽṹ */
typedef struct tagSFETCPSTAT
{
    UINT64    u64Accepts;                                       /* �����򿪵������� */
    UINT64    u64Closed;                                        /* �رյ������� (��������������) */
    UINT64    u64ConnAttempt;                                   /* ��ͼ�������ӵĴ���(����connect) */
    UINT64    u64ConnDrops;                                     /* �����ӽ����׶�ʧ�ܵ����Ӵ���(SYN�յ�֮ǰ) */
    UINT64    u64Connects;                                      /* �����ɹ��Ĵ��� */
    UINT64    u64DelayedAck;                                    /* �ӳٷ��͵�ACK�� */
    UINT64    u64Drops;                                         /* ���ⶪʧ��������(�յ�SYN֮��) */
    UINT64    u64KeepDrops;                                     /* �ڱ���׶ζ�ʧ��������(�ѽ��������ȴ�SYN) */
    UINT64    u64KeepProbe;                                     /* ����̽��̽�ⱨ�ķ��ʹ��� */
    UINT64    u64KeepTimeOut;                                   /* ���ʱ���������ӽ�����ʱ����ʱ���� */
    UINT64    u64PAWSDrop;                                      /* ����PAWS����ʧ�ı�����*/

    UINT64    u64PersistDrops;                                  /* ������ʱ����ʱ�����ﵽ���ֵ�Ĵ��� */
    UINT64    u64PersistTimeOut;                                /* ������ʱ����ʱ����*/
    UINT64    u64PredictionAck;                                 /* ��ACK�����ײ�Ԥ�����ȷ���� */
    UINT64    u64PredictionData;                                /* �����ݱ����ײ�Ԥ�����ȷ���� */
    UINT64    u64RcvAckByte;                                    /* ���յ���ACK����ȷ�ϵķ����ֽ��� */
    UINT64    u64RcvAckPacket;                                  /* �յ���ACK������ */
    UINT64    u64RcvAckTooMuch;                                 /* �յ���δ�������ݽ��е�ACK������*/
    UINT64    u64RcvDupAck;                                     /* �յ����ظ�ACK�� */
    UINT64    u64RcvAfterClose;                                 /* ���ӹرպ��յ��ı����� */
    UINT64    u64RcvBadOff;                                     /* �յ����ײ�������Ч�ı����� */
    UINT64    u64RcvBadSum;                                     /* �յ���У��ʹ���ı����� */
    UINT64    u64RcvByte;                                       /* �����յ����ֽ��� */
    UINT64    u64RcvDupByte;                                    /* ��ȫ�ظ������е��ظ��ֽ��� */
    UINT64    u64RcvDupPacket;                                  /* ��ȫ�ظ����ĵı����� */
    UINT64    u64RcvPacketAfterWnd;                             /* Я�����ݳ�����������ͨ��ֵ�ı����� */
    UINT64    u64RcvByteAfterWnd;                               /* �ڻ�����������ʱ�յ����ֽ��� */
    UINT64    u64RcvPartDupByte;                                /* ���������ظ��ı����ظ��ֽ��� */
    UINT64    u64RcvPartDupPacket;                              /* ���������ظ��ı����� */
    UINT64    u64RcvOutOrderPacket;                             /* �յ�ʧ��ı����� */
    UINT64    u64RcvOutOrderByte;                               /* �յ�ʧ����ֽ��� */
    UINT64    u64RcvShort;                                      /* ���ȹ��̵ı����� */
    UINT64    u64RcvTotal;                                      /* �յ��ı������� */
    UINT64    u64RcvPacket;                                     /* ˳����յı����� */
    UINT64    u64RcvWndProbe;                                   /* �յ��Ĵ���̽�ⱨ���� */
    UINT64    u64RcvWndUpdate;                                  /* �յ��Ĵ��ڸ��±����� */
    UINT64    u64RexmtTimeOut;                                  /* �ش���ʱ���� */
    UINT64    u64RTTUpdated;                                    /* RTT����ֵ���´��� */
    UINT64    u64SegsTimed;                                     /* ������RTT����ı����� */
    UINT64    u64SndByte;                                       /* ���͵��ֽ��� */
    UINT64    u64SndControl;                                    /* ���͵Ŀ��Ʊ�����(SYN FIN RST) */
    UINT64    u64SndPacket;                                     /* ���͵����ݱ�����(���ݳ��ȴ���0) */
    UINT64    u64SndProbe;                                      /* ���͵Ĵ���̽����� */
    UINT64    u64SndRexmtByte;                                  /* �ش��������ֽ��� */
    UINT64    u64SndAcks;                                       /* ���͵Ĵ�ACK������(���ݳ���Ϊ0) */
    UINT64    u64SndRexmtPacket;                                /* �ش��ı����� */
    UINT64    u64SndTotal;                                      /* ���͵ı������� */

    UINT64    u64SndRST;                                        /* ���͵�RST������ */
    UINT64    u64SndUrgent;                                     /* ֻЯ��URG��־�ı�����(���ݳ���Ϊ0) */
    UINT64    u64SndWndUpdate;                                  /* ֻЯ�����ڸ�����Ϣ�ı����� */
    UINT64    u64TimeOutDrop;                                   /* �����ش���ʱ����ʧ�������� */
    UINT64    u64KeepAliveTimeOut;                              /* ���ʱ����ʱ���� */
    UINT64    u64KeepAliveDrops;                                /* ���ʱ�����û������˱��ʱ����ֵ��ʱ */
}SFE_TCPSTAT_S;


UINT32 SFE_GetTCPStatist(UINT32 u32VcpuId, SFE_TCPSTAT_S *pstTCPStat);


UINT32 SFE_ClrTCPStatist(UINT32 u32VcpuId);


VOID SFE_ShowTCPStatist(UINT32 u32VcpuId);


VOID SFE_ShowAllTCPStatist(VOID);

/*******************************************************************************
*    Func Name: SFE_TCP_GetPoolTotalAndFreeUnitNum
* Date Created: 2012-05-03
*       Author: zhaoyue00171897
*      Purpose: ��ȡTCP��Դ���ܵĺ�ʣ��ĵ�Ԫ��
*  Description: ��ȡTCP��Դ���ܵĺ�ʣ��ĵ�Ԫ��
*        Input: 
*       Output: UINT32 *pu32TotalUnitNum:TCP��Դ���ܵĵ�Ԫ��
*               UINT32 *pu32FreeUnitNum:TCP��Դ��ʣ��ĵ�Ԫ��
*       Return: �ɹ�:SFE_TCP_OK
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
UINT32 SFE_TCP_GetPoolTotalAndFreeUnitNum(UINT32 *pu32TotalUnitNum, UINT32 *pu32FreeUnitNum);

#ifdef  __cplusplus
}
#endif

#endif

