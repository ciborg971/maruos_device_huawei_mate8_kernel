/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_deb.h
*
*  Project Code: VISP1.5
*   Module Name: socket4
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: error NO. for socket,tcp,udp
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        ���ݱ�̹淶�����ļ����й淶������
*
*******************************************************************************/
#ifndef _SOCK_ERR_H
#define _SOCK_ERR_H

#ifdef    __cplusplus
extern    "C"{
#endif

#define    EPERM            -1        /* �����Ƿ�  Operation not permitted */
#define    ENOENT           -2        /* �ļ���Ŀ¼������  No such file or directory */
#define    ESRCH            -3        /* ���̷Ƿ�  No such process */
#define    EINTR            -4        /* ϵͳ�жϵ���ʧ��  Interrupted system call */
#define    EIO              -5        /* ����/�������  Input/output error */
#define    ENXIO            -6        /* �ӿ��豸������  Device not configured */
#define    E2BIG            -7        /* �����б����  Argument list too long */
#define    ENOEXEC          -8        /* ��ʽ����  Exec format error */
#define    EBADF            -9        /* ��iFd����ļ�����Ԫ��״̬����(��BUSY)���Ǵ���(��FREAD|FWRITE)Bad file descriptor */
#define    ECHILD           -10       /* δ�ҵ���һ���������  No child processes */
#define    EDEADLK          -11       /* ��Դ����  Resource deadlock avoided */
                                      /* 11 was EAGAIN */
#define    ENOMEM           -12       /* ���ڴ治�㲻�ܴ���socket  Cannot allocate memory */
#define    EACCES           -13       /* Ȩ�޷Ƿ�  Permission denied */
#define    EFAULT           -14       /* ��ַ�Ƿ�  Bad address */
#define    ENOTBLK          -15       /* �����п��豸  Block device required */
#define    EBUSY            -16       /* �豸æ  Device busy */
#define    EEXIST           -17       /* �ļ��Ѵ���  File exists */
#define    EXDEV            -18       /* �豸��������  Cross-device link */
#define    ENODEV           -19       /* �豸��֧�ִ˲���  Operation not supported by device */
#define    ENOTDIR          -20       /* ����һ��Ŀ¼  Not a directory */
#define    EISDIR           -21       /* ��һ��Ŀ¼  Is a directory */
#define    EINVALID         -22       /* socket ID������  Invalid argument */
#define    ENFILE           -23       /* ��ϵͳ�е�socket���������Ѿ��������  Too many open files in system */
#define    EMFILE           -24       /* socket���������Ѿ��������û�пɷֵ�������  Too many open files */
#define    ENOTTY           -25       /* �豸��IO�����Ƿ�  Inappropriate ioctl for device */
#define    ETXTBSY          -26       /* �ļ�æ  Text file busy */
#define    EFBIG            -27       /* �ļ�����  File too large */
#define    ENOSPC           -28       /* �豸�ڴ治��  No space left on device */
#define    ESPIPE           -29       /* �����Ƿ�  Illegal seek */
#define    EROFS            -30       /* ֻ��ϵͳ  Read-only file system */
#define    EMLINK           -31       /* ���ӳ���  Too many links */
#define    EPIPE            -32       /* socket״̬ΪSS_CANTSENDMOREԭ����Ӧ�ó������close��shutdown�ر�socket  Broken pipe */

/* math software */
#define    EDOM             -33        /* Numerical argument out of domain */
#define    ERANGEE          -34        /* Result too large */

/* non-blocking and interrupt i/o */
#define    EAGAIN           -35        /* Resource temporarily unavailable */
#define    EWOULDBLOCK      EAGAIN     /* Operation would block */
#define    EINPROGRESS      -36        /* Operation now in progress */
#define    EALREADY         -37        /* Operation already in progress */

/* ipc/network software -- argument errors */
#define    ENOTSOCK         -38        /* Socket operation on non-socket */
#define    EDESTADDRREQ     -39        /* Destination address required */
#define    EMSGSIZE         -40        /* Message too LONG */
#define    EPROTOTYPE       -41        /* Protocol wrong type for socket */
#define    ENOPROTOOPT      -42        /* Protocol not available */
#define    EPROTONOSUPPORT  -43        /* Protocol not supported */
#define    ESOCKTNOSUPPORT  -44        /* Socket type not supported */
#define    EOPNOTSUPP       -45        /* Operation not supported */
#define    EPFNOSUPPORT     -46        /* Protocol family not supported */
#define    EAFNOSUPPORT     -47        /* Address family not supported by protocol family */
#define    EADDRINUSE       -48        /* Address already in use */
#define    EADDRNOTAVAIL    -49        /* Can't assign requested address */

/* ipc/network software -- operational errors */
#define    ENETDOWN       -50        /* Network is down */
#define    ENETUNREACH    -51        /* Network is unreachable */
#define    ENETRESET      -52        /* Network dropped connection on reset */
#define    ECONNABORTED   -53        /* Software caused connection abort */
#define    ECONNRESET     -54        /* Connection reset by peer */
#define    ENOBUFS        -55        /* No buffer space available */
#define EQDROP            -56        /* Drops a packet because queue us full */
#define    EISCONN        -57        /* Socket is already connected */
#define    ENOTCONN       -58        /* Socket is not connected */
#define    ESHUTDOWN      -59        /* Can't send after socket shutdown */
#define    ETOOMANYREFS   -60        /* Too many references: can't splice */
#define    ETIMEDOUT      -61        /* Operation timed out */
#define    ECONNREFUSED   -62        /* Connection refused */

#define    ELOOP          -63        /* Too many levels of symbolic links */

#define    ENAMETOOLONG   -64        /* File name too long */

/* should be rearranged */
#define    EHOSTDOWN      -65        /* Host is down */
#define    EHOSTUNREACH   -66        /* No route to host */
#define    ENOTEMPTY      -67        /* Directory not empty */

/* quotas & mush */
#define    EPROCLIM       -68        /* Too many processes */
#define    EUSERS         -69        /* Too many users */
#define    EDQUOT         -70          /* Disc quota exceeded */

/* Network File System */
#define    ESTALE         -71        /* Stale NFS file handle */
#define    EREMOTE        -72        /* Too many levels of remote in path */
#define    EBADRPC        -73        /* RPC struct is bad */
#define    ERPCMISMATCH   -74        /* RPC version wrong */
#define    EPROGUNAVAIL   -75        /* RPC prog. not avail */
#define    EPROGMISMATCH  -76        /* Program version wrong */
#define    EPROCUNAVAIL   -77        /* Bad procedure for program */

#define    ENOLCK         -78        /* No locks available */
#define    ENOSYS         -79        /* Function not implemented */

#define    EFTYPE         -80        /* Inappropriate file type or format */
#define    EAUTH          -81        /* Authentication error */
#define    ENEEDAUTH      -82        /* Need authenticator */
#define    ELAST          -83        /* Must be equal largest errno */


/* pseudo-errors returned inside kernel to modify return to process */
#define    ERESTART       -84        /* restart syscall */
#define    EJUSTRETURN    -85        /* don't modify regs, just return    */

#define    ETASKCREATE    -86        /*    don't create task                */
#define    ETASKDELETE    -87        /*    don't delete task                */
#define    ETASKGETID     -88        /*    have not task                    */
#define    EPRISET        -89        /*    can't set pritioy                */

#define    EEVRECEIVE     -90        /*    time is out                        */
#define    EEVSEND        -91        /*    ev_nowait is select                */

#define    EQUCREATE      -92        /*    node's object table full        */
#define    EQUDELETE      -93        /*    delete queue fail                */
#define    EQUSEND        -94        /*    send message fail                */
#define    EQURECEIVE     -95        /*    receive message fail            */

#define    ESMCREATE      -96        /*    sm create fail                    */
#define    ESMDELETE      -97        /*    sm delete fail                    */
#define    ESMP           -98        /*    sm p fail                        */
#define    ESMV           -99        /*    sm v fail                        */

#define    ETCBCHECK      -100        /*    has not find the tcb            */
#define    ETCBCREATE     -101        /*    has not create tcb                */
#define    ETCBDELETE     -102        /*    tcb has not delete                */

#define    ENONBIO        -103
#define    ENOASYNC       -104
#define    ENOSETOWN      -105
#define    ENOGETOWN      -106
#define    ENOFIONBIO     -107
#define    ENOFIOASYNC    -108
#define    ENOFIOBACKCALL -109

#define    ECANTTCB       -107

#define    EUIO           -108

#define    ENOPROTO       -109
#define    ENOMG          -110

#define    EBLOCKING      -111
#define    ENOTUDPSOCK    -112
#define    ETCBINUSE      -113

#define ESNDBUFHIWAT      -114

#define ENOTBOUNDALGIN    -117
#define EDISABLEDFORTEST  -118

/* Add new return value, zhangfeng, 2004,02,27 */
#define EMORECONTROL            -120
#define EVOIDINPCB              -121
#define EVOIDTCPCB              -122
/* zhangfeng, 2004,02,27 */

/* Added for SOCKET HA. When switching or smoothing, this error
 * code will be returned if some socket func is called.
 */
#define EISSWITCHINGORSMOOTHING -123

/*Add new return value for isis_socket, renguixing ,2007-07-06, begin*/
#define ENOTMULTI               -124
#define EINPUTIF                -125
#define ENOTBIND                -126    /*�޸����ⵥA82D18705��rgx 2007-08-09*/
/*Add new return value for isis_socket, renguixing ,2007-07-06, end*/

#define EMD5LEN                 -127  /* MD5 P***W*** length is error */
#define EMD5MBFCONT             -128  /* continue MD5 mbuf failed */
#define EMD5PWDCONF             -129  /* add or modify MD5 P***W*** failed */
#define EMD5WRONMASK             -130  /* add or modify MD5 P***W*** failed due to wrong value of mask */


#define EINVAL            -1

#define EFULLSOCK     -200

#define EGADDR          -201    /*��������ַ*/
#define ESADDR          -202    /*�����Դ��ַ*/
#define EGOVERFLOW      -203    /*�ӿ������õ��鳬������*/
#define ESOVERFLOW      -204    /*socket�����õ�Դ��ַ��������*/
#define EBLOCKSOURCE    -205    /*��ֹһ�������Ѿ�����ֹ��Դ��ַ������ͬ��*/
#define EUNBLOCKSOURCE  -206    /*����һ������û�б���ֹ��Դ��ַ������ͬ��*/
#define EADDSOURCE      -207    /*����һ���Ѿ����ڵ�Դ��ַ������ͬ��*/
#define EDROPSOURCE     -208    /*ɾ��һ�������ڵ�Դ��ַ������ͬ��*/
#define EFILTERMODE     -209    /*�ಥ�����ģʽ������ò���*/
#define ESOURCELISTNULL -210    /*Դ�б�Ϊ��*/
#define EIGMPCOMPNULL   -211    /*IGMP���Ϊ��*/
#define EIFTYPE         -212    /*����Ľӿ�����*/
#define EIFTHISBORD     -213    /*�Ǳ���ӿ�*/
#define EGROUPNULL      -214    /*�ӿ�δ����ָ���ಥ��*/
#define EINVALIDVRF     -215    /*���ýӿ��뵱ǰ��������VRF��ͻ�����õ�VRF��Ч*/
#define ENEEDFRAG       -216    /*IP������Ҫ��Ƭ������������DF��ʶ*/

#define ESOCKCLOSE      -217    /*socket�쳣����Ҫ�ر�*/

#define ENOREMOTEHOST 1000
#define ENOREMOTEADDR 1001
#define ENOBUF        1002

#define TCP_ISN_TCPCB_ERR 0

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */


#endif
