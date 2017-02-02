/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_def.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD
*  Date Created: 2006-12-01
*        Author: Wangchengyang
*   Description: BFD��Ҫ�õ��ĺ궨��ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-01      Wangchengyang       Create
*
*******************************************************************************/
#ifndef _BFD_DEF_H_
#define _BFD_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ȫ�ֺ� */
#define BFD_Min(a, b)              ((a) < (b) ? (a) : (b))
#define BFD_Max(a, b)              ((a) > (b) ? (a) : (b))

#define BFD_TRUE                       1
#define BFD_FALSE                      0

#define BFD_ON                         1
#define BFD_OFF                        0

/* һЩBFD�Ự���������õ��ĺ� */
#define BFD_VER                        1           /* BFD�汾 */
#define BFD_EVENT_ADD_IPADDR           0           /* ���ӵ�ַ�¼� */
#define BFD_EVENT_DEL_IPADDR           1           /* ɾ����ַ�¼� */

#define BFD_MIN_TX_RX_INTERVAL         1           /* BFD��С���ͽ���ʱ���� */
#define BFD_MAX_TX_RX_INTERVAL         1000         /* BFD����ͽ���ʱ���� */
#define BFD_MIN_DETECT_MULTI           3            /* BFD��С��ⱶ�� */

#define BFD_MAX_DETECT_MULTI           50           /* BFD����ⱶ�� */
#define BFD_DEFAULT_DOWN_INTERVAL      2000         /* �����Ự��ʱ��,����Ĭ�Ͻ���ʱ�������߲�ѯ�����¶�ʱ��ѯʱ�� */
#define BFD_DEFAULT_TX_RX_INTERVAL     30           /* BFD�Ự����֮��Ĭ�Ϸ��ͽ���ʱ���� */
#define BFD_MAX_SESSION_NUM_DEF            1000     /* BFDĬ�����Ự��Ŀ */
#define BFD_MIN_DETECT_TIME            10           /* BFD������С̽��ʱ�� */

/* Modified by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/4/8 */
#define BFD_MAX_SESSION_ID             9215         /* BFD���session id*/
/*End of Modified by wangchengyang-xujun62830-57575, 2009/4/8 */
#define BFD_MIN_SESSION_ID             1            /* BFD��Сsession id*/
#define BFD_INVALID_DISCR              0            /* ��ЧBFD discr */
#define BFD_DEFAULT_TOSEXP             0xE0         /* BFD����Ĭ��TOSֵ������Ȩ���(8λTOS��������λbitΪȫ1) */
#define BFD_INVALID_TIMERID            0            /* ��Ч��timer id */
#define BFD_INVALID_IFINDEX            0            /* ��Ч�Ľӿ����� */

/* һЩBFD���Ʊ��Ĳ�ͬ��ʽ���Ⱥ� */
#define BFD_LEN_AUTH_KEYID             6            /* Key ID����*/
#define BFD_LEN_AUTH_MD5               ( 24 + 24 )  /* MD5��֤���ĳ��� */
#define BFD_LEN_AUTH_SHA1              ( 24 + 28 )  /* SHA1��֤���ĳ��� */
#define BFD_LEN_MAX_SIMPLE_PWD         16           /* ����pwd���� */
#define BFD_LEN_MIN_SIMPLE_PWD         1            /* ��С��pwd���� */

/* �Ự���á���ַ��ɾ���û������ѯͳһд���¼� */
#define BFD_EVT_OTHER_Q                0x00000100
/*Begin BC3D02903 liangjicheng 2010-04-19 */
#define BFD_EVT_EXT_Q                  0x00000200
/*End   BC3D02903 liangjicheng 2010-04-19 */

/* GR�ָ��¼� */
#define BFD_EVT_GR_RESTORE             0x00000400
/* GRƽ���¼� */
#define BFD_EVT_GR_SMOOTH              0x00000800

#define BFD_EVT_NSR_Q                  0x00001000

#define BFD_MAX_TASK_PRI               255          /* BFD������ȼ� */
#define BFD_ONEROUNDTIMES              8            /* ȫ��ȥʹ��ÿ��ɾ���ĻỰ���� */

#define BFD_DEFAULT_SNDPKT_LEN         100          /* BFD�Ự���汨�ĵĴ�С */

/* Դ�Զ˶˿ںŶ��� */
#define BFD_DEFAULT_SRCPORT            49151        /* ȱʡԴ�˿�,�����趨���Ự��ʱ����Ҫ���ϻỰid */
#define BFD_DEFAULT_MULTIHOP_DSTPORT   4784         /* ����Ŀ�Ķ˿ں� */
#define BFD_DEFAULT_ONEHOP_DSTPORT     3784         /* ����Ŀ�Ķ˿ں� */

/* BFD���С�������Ҫ�õ���һЩ�궨�� */
#define BFD_QDEPTH                     2048         /* BFD���г��� */
#define BFD_QMODE                      VOS_Q_FIFO   /* ���б�־ */

/* HA���λ */
#define BFD_HA_BEFORESMOOTH                0x0001    /* ƽ������ǰ���λ */
#define BFD_HA_SMOOTHING                   0x0002    /* ����ƽ�������б�� */
#define BFD_HA_SMOOTHED                    0x0000    /* ��ƽ����ɱ�� */


/* WTR���ޣ���λ:�� */
#define BFD_MAX_WTR_TIME               1000000       /* WTR����Ϊһ�����룬Լ277��Сʱ */

/* BFDģ��ʹ�õ�SIDͳһ�ڴ˶��� */

#define SID_BFD_SESS_ENTRY_S       1  /* BFD_SESS_ENTRY_S */
#define SID_BFD_SNDBUF             2  /* �Ự�����BFD���� */

/* end of SID */

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-02 */
/* VRF������ֵ */
#define BFD_MAX_VRF_INDEX          255 
#define BFD_DEFAULT_VRF_INDEX      0 

/* BFDVRF����ֵ������:��Ҫ������Ϊ��ʱ������������ʱ����ʱ������:
 * ulBfdVrfIndex�и�λ��ʶBFD�ỰID,��16λ��ʾBFD���ڵ�VRF Index */
#define BFD_GETBFDVRFINDEX(ulTmpSessId,ulTmpVrfId,ulBfdVrfIndex)\
{\
    ulBfdVrfIndex = (((ulTmpSessId << 16 ) & 0xFFFF0000) |(ulTmpVrfId & 0x0000FFFF));\
}

#define BFD_GET_VRFINDEX(ulTmpSessId,ulTmpVrfId,ulBfdVrfIndex)\
{\
    ulTmpSessId = ((ulBfdVrfIndex >> 16 ) & 0x0000FFFF);\
    ulTmpVrfId  = (ulBfdVrfIndex & 0x0000FFFF);\
}

/* End:VISP1.7C03 VRF wangchengyang,2009-02-02 */

/*Added by wangchengyang-xujun62830-57575 for VISPV1R8C01, 2009/4/8 */
#define BFD_OVER_IPV4      0
#define BFD_OVER_IPV6      1
#define BFD_OVER_ALL       2

#define BFD_CREATE_STATIC_MANUAL    1 /*��ָ̬������������,�ݲ��漰*/
#define BFD_CREATE_STATIC_AUTO  2 /*��̬��Э��*/
#define BFD_CREATE_DYNAMIC  3 /*��̬����*/

/* BFDĬ���״�Э�̴���Ϊ0,��Ĭ�ϲ�Э��,for VISPV1R8C01-219,wangchengyang 2009/5/18 */
#define BFD_DEFAULT_NEGO_TIMES 0

/* 
 * pAddress must be a array that have 4 ULONG element 
 * return value: 
 *      1 -- pAddress is a NULL address
 *      0 -- pAddress isn't a NULL address
 */

#define BFD6_IS_ADDRESS_NULL( pAddress )         \
    ( (0 == (VOS_NTOHL((pAddress)[0]))) \
     && (0 == (VOS_NTOHL((pAddress)[1]))) \
     && (0 == (VOS_NTOHL((pAddress)[2]))) \
     && (0 == (VOS_NTOHL((pAddress)[3]))) )


/* 
 * pAddress must be a array that have 4 ULONG element 
 * return value: 
 *      1 -- pAddress is a link-local address
 *      0 -- pAddress isn't a link-local address
 */
#define BFD6_IS_ADDRESS_LINKLOCAL( pAddress )    \
    ( 0xFE800000 == (0xFFC00000&(VOS_NTOHL((pAddress)[0]))) )

/* 
 * pAddress must be a array that have 4 ULONG element 
 * return value: 
 *      1 -- pAddress is a site-local address
 *      0 -- pAddress isn't a site-local address
 */
#define BFD6_IS_ADDRESS_SITELOCAL( pAddress )    \
    ( 0xFEC00000 == (0xFFC00000&(VOS_NTOHL((pAddress)[0]))) )

/* 
 * pAddress must be a array that have 4 ULONG element 
 * return value: 
 *      1 -- pAddress is a loopback address
 *      0 -- pAddress isn't a loopback address
 */
#define BFD6_IS_ADDRESS_LOOPBACK( pAddress )     \
    ( (0 == (VOS_NTOHL((pAddress)[0]))) \
     && (0 == (VOS_NTOHL((pAddress)[1]))) \
     && (0 == (VOS_NTOHL((pAddress)[2]))) \
     && (1 == (VOS_NTOHL((pAddress)[3]))) )


/* 
 * pAddress must be a array that have 4 ULONG element 
 * return value: 
 *      1 -- pAddress is a multicast address
 *      0 -- pAddress isn't a multicast address
 */
#define BFD6_IS_ADDRESS_MULTICAST( pAddress )    \
    ( 0xFF000000 == (0xFF000000&(VOS_NTOHL((pAddress)[0]))) )


/* 
 * pAddress must be a array that have 4 ULONG element 
 * return value: 
 *      1 -- pAddress is a global address
 *      0 -- pAddress isn't a global address
 */
#define BFD6_IS_ADDRESS_GLOBAL( pAddress )    \
    ( !((BFD6_IS_ADDRESS_MULTICAST(pAddress))\
     ||(BFD6_IS_ADDRESS_LOOPBACK(pAddress))\
     ||(BFD6_IS_ADDRESS_LINKLOCAL(pAddress))\
     ||(BFD6_IS_ADDRESS_NULL(pAddress))) )   

#define BFD6_ADDRESS_NTOH(x) \
     {\
        (x)[0] = VOS_NTOHL((x)[0]);\
        (x)[1] = VOS_NTOHL((x)[1]);\
        (x)[2] = VOS_NTOHL((x)[2]);\
        (x)[3] = VOS_NTOHL((x)[3]);\
     }
     
     /* x must be a array that have 4 ULONG element */
#define BFD6_ADDRESS_HTON(x) \
     {\
        (x)[0] = VOS_HTONL((x)[0]);\
        (x)[1] = VOS_HTONL((x)[1]);\
        (x)[2] = VOS_HTONL((x)[2]);\
        (x)[3] = VOS_HTONL((x)[3]);\
     }

#define BFD_ADDR_CMP(pulDstAddr,pulSrcAddr,ulIpVer,ulResult)\
{\
    (ulResult) = 1;\
    if (BFD_OVER_IPV4 == (ulIpVer))\
    {\
        if ((pulDstAddr)[0] == (pulSrcAddr)[0])\
        {\
            (ulResult) = 0;\
        }\
    }\
    else\
    {\
        if (((pulDstAddr)[0] == (pulSrcAddr)[0])\
            && ((pulDstAddr)[1] == (pulSrcAddr)[1])\
            && ((pulDstAddr)[2] == (pulSrcAddr)[2])\
            && ((pulDstAddr)[3] == (pulSrcAddr)[3]))\
        {\
            (ulResult) = 0;\
        }\
    }\
}
/* End of Added by wangchengyang-xujun62830-57575, 2009/4/8 */

#define BFD6_ADDR_COPY(pulDstAddr,pulSrcAddr)\
{\
    (pulDstAddr)[0] = (pulSrcAddr)[0];\
    (pulDstAddr)[1] = (pulSrcAddr)[1];\
    (pulDstAddr)[2] = (pulSrcAddr)[2];\
    (pulDstAddr)[3] = (pulSrcAddr)[3];\
}

/* Added by likaikun00213099 at 20140716. */
/* �������ַ��ıȽ�,�ֽ�������ܹ�ͳһ�� */
#define BFD_ADDR_STREAM_CMP(pucDstAddr,pucSrcAddr,ulIpVer,ulResult)\
{\
    ULONG ulAddrLen = 4;\
    INT32 lRetResult = 0;\
    ulResult = 1;\
    if (BFD_OVER_IPV4 == ulIpVer)\
    {\
        ulAddrLen = 4;\
    }\
    else\
    {\
        ulAddrLen = 16;\
    }\
    (VOID)VOS_Mem_Cmp((VOID*) pucDstAddr, (VOID*)pucSrcAddr, ulAddrLen, &lRetResult);\
    if (0 == lRetResult)\
    {\
        ulResult = 0;\
    }\
}
/* �������ַ��ıȽ� */

/* ���GR�ָ����� */
#define BFD_GR_RESTORE_OVER  0
/* ���GRƽ������ */
#define BFD_GR_SMOOTH_OVER   1

#define INVALID_IF_TYPE   0xffffffff
#define INVALID_IF_NUM    0xffffffff

/* BFD License������ض��� */

#define BFD_LICENSE_ONEROUNDTIMES   256     /* BFD License���ܶ�̬�򿪻�ر�ʱÿ�δ���ĻỰ���� */
extern ULONG g_ulBfdLicenseGlobalCapability;
/* wangjiaqi modify for ipv6 bfd 20131121 begin */
extern ULONG g_ulBfd6LicenseGlobalCapability;
/* wangjiaqi modify for ipv6 bfd end */

typedef enum tagBFD_TOEXT_MSG_TYPE_E
{
    BFD_TOEXT_SESSION_DELETE        = 1               ,         /* ɾ���Ự */
    /*Added by qinyun62011, �Ż�BFD�ỰID��չ��9215����������, 2013/9/27 */
    /*VRFɾ��ʱ����ɾ�����еĻỰÿ���Ựɾ��ʱ����SESSION_DELETE֪ͨ����˲���
      Ҫ����ɾ��������*/
    /* End of Added by qinyun62011, 2013/9/27 */
    BFD_TOEXT_UNCAPABILITY                            ,         /* ȫ��ȥʹ�� */
    BFD_TOEXT_UNLICENSE                               ,         /* �ر�license */
    
    BFD_TOEXT_CAPABILITY                              ,
    BFD_TOEXT_ROUTE_UP                              ,
    BFD_TOEXT_NSR_RESUME_MODIFY,                               /* NSR�����еײ�ָ��Ķ�̬·�������ỰID��Ҫ���*/
    /* wangjiaqi modify for ipv6 bfd 20131125 begin */
    BFD6_TOEXT_SESSION_DELETE,
    BFD6_TOEXT_UNCAPABILITY,
    BFD6_TOEXT_UNLICENSE,
    BFD6_TOEXT_CAPABILITY,
    BFD6_TOEXT_ROUTE_UP,
    /* wangjiaqi modify for ipv6 bfd end */
    BFD_TOEXT_MSG_MAX
}BFD_TOEXT_MSG_TYPE_E;
/*End of Modified by qinyun62011, 2010/11/15 */

typedef enum tagBFD_PF_STATE_E
{
   PF_STATE_P_NULL = 0,    /*P��ǳ�ʼ״̬*/
   PF_STATE_P_OPEN = 1,    /*P���OPEN״̬*/
   PF_STATE_P_EXPIRE = 2,  /*P����ش���ʱ״̬*/
   PF_STATE_F_ACK = 3      /*P��� Fȷ��״̬*/
}BFD_PF_STATE_E;

#define  BFD_PF_TIMER_NUM       32  /*BFD PF ����ʱ������*/

#define PF_PROC_MODE_NP_RETRAN        0    /* NP�ش�ģʽ: ͬʱ�·�P��Ǹ�NP : SGSN ģʽ*/
#define PF_PROC_MODE_NO_RETRAN        1    /* ����һ��P���� ���·�P��Ǹ�NP�������ش�*/
#define PF_PROC_MODE_CONTROL_RETRAN   2    /* �������ش�ģʽ: ����һ��P���ģ� ���·�P��Ǹ�NP�� ͬʱVISP����P�����ش� : MBSC��Hert ����*/

#define PF_PROC_TIMER_PERIOD_MIN 3  /*��ʱ������������Сֵ 3��*/
#define PF_PROC_TIMER_PERIOD_DFT 10  /*��ʱ����������Ĭ��ֵ 10��*/
#define PF_PROC_TIMER_PERIOD_MAX 20 /*��ʱ�������������ֵ 20��*/

#define PF_PROC_TIMER_RETRAN_MIN  1  /*��ʱ���ش�������Сֵ 1*/
#define PF_PROC_TIMER_RETRAN_DFT  5  /*��ʱ���ش�����Ĭ��ֵ 5*/
#define PF_PROC_TIMER_RETRAN_MAX  10 /*��ʱ���ش��������ֵ 10*/

#define  PF_PROC_SRAND_VALUE   4   /*����ֵ*/
#define  PF_PROC_RAND_OFFSET   2   /*���ƫ��ֵ*/

#define BFD_SCHEDULE_MAX_NUM    32


/************************ BFD  ֧��4K VPN ���󿪷�***************************************/
typedef struct tagBFD_TREE_SET_S/*BFD������*/
{
  AVL3_TREE_S  stBfdTree;
  ULONG   ulBfd4Count; /*�����µ�BFD4�Ự����*/
  ULONG   ulBfd6Count; /*�����µ�BFD6�Ự����*/
} BFD_TREE_SET_S;

extern int BFD_compare(void *a, void *b);
#define BFD_INIT_AVL_NODE(NODE)            (NODE).parent = 0;                \
                                             (NODE).left = 0;                  \
                                             (NODE).right = 0;                 \
                                             (NODE).sLeftHeight = -1;                \
                                             (NODE).sLeftHeight = -1
#define BFD_TREE_OFFSET(STRUCT,FIELD) (unsigned short)((unsigned char *)(&((STRUCT *)1)->FIELD) - (unsigned char *)1)
#define BFD_AVL_INSERT(TREE, NODE, TREE_INFO) (NULL == AVL3_FindToInsert(&(TREE), &(NODE), &(TREE_INFO)))
#define BFD_AVL_DELETE(TREE, NODE)            AVL3_DeleteNode(&(TREE), &(NODE))
#define BFD_AVL_FIND(TREE, KEY, TREE_INFO) AVL3_FindNode(&(TREE), (KEY), &(TREE_INFO))

#define BFD_AVL_NEXT(NODE, TREE_INFO) AVL3_GetNextNode(&(NODE), &(TREE_INFO))
#define BFD_AVL_FIRST(TREE, TREE_INFO) AVL3_GetFirstNode(&(TREE), &(TREE_INFO))
#define BFD_AVL_GET_OR_NEXT(TREE, KEY, TREE_INFO)  AVL3_GetOrGetNext(&(TREE), (KEY), &(TREE_INFO))

#ifdef __cplusplus
}
#endif

#endif

