/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              nd_public.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  IPBIRV100R003.IPv6.E001
*    Module Name :  Nd
*    Create Date :  2006/09/23
*    Author      :  Yinyuanbin
*    Description :  To define ND data structures used by external modules
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-09-23  Yinyuanbin    Created for including all public definitions in
*                             this file, for IPOSV1R1
************************************************************************/

#ifndef _ND_PUBLIC_H
#define _ND_PUBLIC_H

#ifdef  __cplusplus
extern "C"{
#endif  /* #ifdef  __cplusplus */

/*----------------------------------------------*
 *              Macros                          *
 *----------------------------------------------*/
#define IP6_ND_MAX_ENUM_VALUE           0xFFFFFFFF

/* Function return types */
#define ND_OK                           0
#define ND_ERR                          1
#define ND_NOFOUND                      2
#define ND_STOP                         3
#define ND_OWN_LINK_LOCAL               4

#define IP6_ND_TRUE                     0
#define IP6_ND_FALSE                    1

/* Neighbor Entry related macros */
#define IP6_ND_NON_STATIC_ENTRY         0
#define IP6_ND_STATIC_ENTRY             1


#define ND_NEIGHBORTABLE_LEN            1024
#define NB_ENTRY_PRODUCTINFO_SIZE       16

/* Operation code */
#define ND_FALSE                        0
#define ND_TRUE                         1
#define IP6_ND_CONFIG                   0
#define IP6_ND_UNDO_CONFIG              1

/* for NB entry display */
/* Changed as error code in enum */
/* #define IP6_ND_NO_NB_ENTRY              2 */

/* Min, Max, Avail values for Total NB entries */
#define IP6_ND_MAX_NB_TOTAL_NUM         4096
#define IP6_ND_MIN_NB_TOTAL_NUM         1024
#define IP6_ND_DEF_NB_TOTAL_NUM         1024

#define IP6_ND_MAX_NB_TOTAL_NUM_EXACT         1024*66 /*66K*/
#define IP6_ND_MIN_NB_TOTAL_NUM_EXACT         1
#define IP6_ND_DEF_NB_TOTAL_NUM_EXACT         1024

/* Begin: Added by Santhosh 71702, 2007/12/19 */
/* Description: Minimum value for total NB entries is added for PAF support of
   number of total NB entries per Interface */

/* Min, Max, Avail values for Interface NB entries */
#define IP6_ND_MAX_INTF_NB_NUM          4096
#define IP6_ND_DEF_INTF_NB_NUM          1024
/* Begin : Modified by Anand on 05/09/08 for Defect : AC4D06631 */
#define IP6_ND_MIN_INTF_NB_NUM          32
/* End : Modified by Anand on 05/09/08 for Defect : AC4D06631 */

/* Min, Max, Avail values for Interface NB entries */
#define IP6_ND_MAX_INTF_NB_NUM_EXACT          1024*40  /*40K*/
#define IP6_ND_DEF_INTF_NB_NUM_EXACT          1024
#define IP6_ND_MIN_INTF_NB_NUM_EXACT          1


/* Default Percentage Value for Interface NB entries */
#define IP6_ND_DEF_INTF_NB_PERCENT      100

/* Begin : Added by Anand S 08-09-08 for Defect : AC4D06631 */
#define IP6_ND_MIN_INTF_NB_PERCENT      4
#define IP6_ND_MAX_INTF_NB_PERCENT      100
/* End : Added by Anand S 08-09-08 for Defect : AC4D06631 */

/* End: Added by Santhosh 71702, 2007/12/19 */

/* Min, Max, Avail values for Total Static NB entries */
#define IP6_ND_MAX_TOT_STAT_NB_NUM      2048
#define IP6_ND_DEF_TOT_STAT_NB_NUM      512
#define IP6_ND_MIN_TOT_STAT_NB_NUM      50

#define IP6_ND_MAX_NB_NUM_EXACT_DEFAULT      1
#define IP6_ND_DEF_NB_NUM_EXACT_DEFAULT      1
#define IP6_ND_MIN_NB_NUM_EXACT_DEFAULT      1

/* Min, Max, Avail values for Total Static NB entries */
#define IP6_ND_MAX_TOT_STAT_NB_NUM_EXACT      2*1024  /*2K*/
#define IP6_ND_DEF_TOT_STAT_NB_NUM_EXACT      512
#define IP6_ND_MIN_TOT_STAT_NB_NUM_EXACT      1

/* Default Percentage Value for Total Static NB entries */
#define IP6_ND_DEF_TOT_STAT_NB_PERCENT  50

/* Begin : Added by Anand S 08-09-08 for Defect : AC4D06631 */
#define IP6_ND_MIN_TOT_STAT_NB_PERCENT  6
#define IP6_ND_MAX_TOT_STAT_NB_PERCENT  50
/* End : Added by Anand S 08-09-08 for Defect : AC4D06631 */

/* Begin :Changes for AC4D05067 by Anand on 20-02-2008*/
/* Min, Max, Avail values for Interface Static NB entries */
#define IP6_ND_MAX_NB_INTF_STATIC_NUM      2048
#define IP6_ND_DEF_NB_INTF_STATIC_NUM      256

/* Begin : Modified by Anand S 08-09-08 for Defect : AC4D06631 */
#define IP6_ND_MIN_NB_INTF_STATIC_NUM      4

#define IP6_ND_MAX_NB_INTF_STATIC_NUM_EXACT      1024*2
#define IP6_ND_DEF_NB_INTF_STATIC_NUM_EXACT      256
#define IP6_ND_MIN_NB_INTF_STATIC_NUM_EXACT      1

/* End : Modified by Anand S 08-09-08 for Defect : AC4D06631 */

/* Default Percentage Value for Interface Static NB entries */
#define IP6_ND_DEF_NB_INTF_STATIC_PERCENT  25

/* Begin : Added by Anand S 08-09-08 for Defect : AC4D06631 */
#define IP6_ND_MIN_NB_INTF_STATIC_PERCENT  10
#define IP6_ND_MAX_NB_INTF_STATIC_PERCENT  50
/* End : Added by Anand S 08-09-08 for Defect : AC4D06631 */

/* End :Changes for AC4D05067 by Anand on 20-02-2008*/

#define IP6_ND_NEXT_HOP_IS_ROUTER       2
#define IP6_ND_NEXT_HOP_IS_HOST         3


#define IP6_ND_ROUTER_INT_MIN_OVER      7

/* Added for SGSN callback notification */
#define ND_ADD     1
#define ND_DEL     2
#define ND_MOD     3

/* macros for filling/validating SPECS_RES_VALUE_S */
#define ND_CONTROLLED_BY_PAF_LCS      1
#define ND_CONTROLLED_BY_PAF          0

#define STALE_TIME            60 * 60 * 24 /*stale״̬Ĭ�ϳ�ʱʱ��24Сʱ*/
#define MAX_UNICAST_SOLICIT   3            /*���͵���NS����������*/

 /*----------------------------------------------*
  *              Enumerated Data Types           *
  *----------------------------------------------*/

/* Error types returned by ND Config API's */
typedef enum IP6_ND_ERR_Config
{
    /* Err types in case of when config of static NB*/
    IP6_ND_ERR_CFG_INVALID_LLCADDR = 5001,
    IP6_ND_ERR_CFG_ADDR_CONFLICT,
    IP6_ND_ERR_CFG_UNSPEC_ADDR,
    IP6_ND_ERR_CFG_MULTI_ADDR,
    IP6_ND_ERR_CFG_LOOP_ADDR,
    IP6_ND_ERR_CFG_INVALID_V4_COMP_ADDR,
    IP6_ND_ERR_CFG_INVALID_V4_MAPPED_ADDR,
    IP6_ND_ERR_CFG_PREF_LIFE_TIM_EXCEED,
    IP6_ND_ERR_CFG_UNSPEC_PREFIX,
    IP6_ND_ERR_CFG_LINK_LOCAL_PREFIX,
    IP6_ND_ERR_CFG_PREFIX_MULTI,
    IP6_ND_ERR_CFG_PREFIX_LOOP,
    IP6_ND_ERR_CFG_INVALID_V4_COMP_PREFIX,
    IP6_ND_ERR_CFG_INVALID_V4_MAPPED_PREFIX,
    IP6_ND_ERR_CFG_INVALID_PREFIX_LEN,
    IP6_ND_ERR_CFG_INVALID_LIFETIME,
    IP6_ND_ERR_INVALID_INPUT_USING_DEFAULT,
    IP6_ND_ERR_DAD_NOT_SUP_ON_INT,
    IP6_ND_ERR_NBMA_NOT_SUPPORTED,
    IP6_ND_ERR_LOOP_NOT_SUPPORTED,
    IP6_ND_SERIAL_NOT_SUPPORTED,
    IP6_ND_MAX_NB_PER_BOARD,
    IP6_ND_DYNAMIC_ENTRY,
    IP6_ND_ERR_CFG_INVALID_PREFIX_LEN_RANGE,

    /* IAS changes Start :
            Error code added for invalid control parameters (Vlan-ID and
            Port-index).
    */
    IP6_ND_ERR_INVALID_NBENTRY_CTRL_PARAMS,
    IP6_ND_ERR_DEPENDENT_PAF_CONFLICT_LOAD_DEFAULT,

    /* IAS changes End */

    /* Begin : Changes for AC4D05470 by SurajR (72063) on 04-03-2008 */
    /* Description: Moved error code macros, as elements into enum
     *              IP6_ND_ERR_Config.
     */
    IP6_ND_TRUE_NEXT,
    IP6_ND_CLI_EXCEEDS_LIMIT,
    IP6_ND_PREFIX_DOESNOT_EXISTS,

    /* End : Changes for AC4D05470 by SurajR (72063) on 04-03-2008 */

    /* Begin : Modified by Anand, Error code overlapping moved to enum */
    IP6_ND_ROUTER_INT_MINGTMAX,
    IP6_ND_ROUTER_INT_MINGTMAX_UNDO,
    IP6_ND_ROUTER_LIFE_TIME_LESS,
    
    IP6_ND_ERR_NA_NOT_SUP_ON_INT,
    
    IP6_ND_ERR_CFG_MAX = IP6_ND_MAX_ENUM_VALUE

}IP6_ND_ERR_CFG_E;

/* Operation code */
typedef enum tagIP6_ND_SETFLAG_E
{
    IP6_ND_FLAG_SET = 0,
    IP6_ND_FLAG_UNDOSET,

    IP6_ENUM_SETFLAG_PAD = IP6_ND_MAX_ENUM_VALUE

}IP6_ND_SETFLAG_E;

/* Error types returned by ND API's */
typedef enum tagIP6_ND_ERRORS_E
{
    IP6_ND_ERR_INPUTISNULL = 2,             /* 2 */
    IP6_ND_ERR_IFNETISNULL,                 /* 3 */
    IP6_ND_ERR_NDINFOISNULL,                /* 4 */
    IP6_ND_ERR_INVALIDVALUE,                /* 5 */
    IP6_ND_ERR_INVALIDFLAG,                 /* 6 */
    IP6_ND_ERR_GETTIME_FAIL,                /* 7 */
    IP6_ND_ERR_PREFIX_NOT_FOUND,            /* 8 */
    IP6_ND_ERR_PREFIX_NOT_PRESENT,          /* 9 */
    IP6_ND_ERR_NBENTRY_NOT_PRESENT,         /* 10 */
    IP6_ND_ERR_NBENTRY_NOT_PRESENT_ON_INTERF,/* 11 */
    IP6_ND_ERR_FAIL_TOGET_NBENTRY_IO,       /* 12 */
    IP6_ND_ERR_WAITLIST_SET_FAIL,           /* 13 */
    IP6_ND_ERR_WAITLIST_GET_FAIL,           /* 14 */
    IP6_ND_ERR_NO_IFNET_PRESENT,            /* 15 */

    IP6_ND_ERR_MALLOC_FAILED,               /* 16 Memory allocation failed */
    IP6_ND_ERR_WRITE_TO_QUEUE_FAILED,       /* 17 Queue write failed */
    IP6_ND_ERR_WRITE_EVENT_FAILED,          /* 18 Event write failed */
    IP6_ND_ERR_DEFRTR_ENTRY_NOTPRESENT,     /* 19 Default Rtr entry not present*/
    IP6_ND_ERR_NO_DEFRTR_ENTRY_PRESENT,     /* 20 Default Router list is empty */
    IP6_ND_ERR_PREFIXLST_ENTRY_NOTPRESENT,  /* 21 Prefix list entry not present */
    IP6_ND_ERR_MAX_PREFIX_ENTRY_REACHED,    /* 22 Maximum No of Prefix list
                                                entry reached */
    IP6_ND_ERR_NO_PREFIXLST_ENTRY_PRESENT,  /* 23 Prefix list is empty */
    IP6_ND_ERR_GBLPREFIX_ENTRY_NOTPRESENT,  /* 24 Global Prefix entry not present*/
    IP6_ND_ERR_NO_GBLPREFIX_ENTRY_PRESENT,  /* 25 Global Prefix entry is empty */
    IP6_ND_ERR_INVALID_PRE_TYPE,            /* 26 Invalid Prefix Address type */
    IP6_ND_ERR_FETCH_CTRL_BLK,              /* 27 Interface Control block does
                                                not exists */
    IP6_ND_ERR_MAX_DEFRTR_REACHED,          /* 28 Maximum No of Default Router
                                            entry reached */
    IP6_ND_ERR_IATYPE_NOT_SUPPORTED,        /* 29 IA type Given for Stateful
                                            address config is not supported*/
    IP6_ND_ERR_INVALID_ADDR_COUNT,          /* 30 Address count for Stateful addr
                                            config is not valid */
    IP6_ND_ERR_INVALID_SFADDR_CFG_TYPE,     /* 31 Stateful Address config operation
                                            type invalid */
    IP6_ND_ERR_NO_ADAPT_CALLBACKS_REG,      /* 32 DHCP6C Adaptor Call back function
                                            is not registered */
    IP6_ND_ERR_INVALID_ADDR_TYPE,           /* 33 Invalid Address type for config*/
    IP6_ND_ERR_INVALID_LIFETIME,            /* 34 Pref LT greater than Valid LT/
                                            Valid LT  0 for Address Add/update*/
    IP6_ND_ERR_DUPLICATE_ADDR_FOUND,        /* 35 Duplicate Address(es) found */
    IP6_ND_ERR_ADAPT_NOT_NOTIFIED,          /* 36 Host has not notified Adaptor */
    IP6_ND_ERR_INVALID_SFOTHER_PARAM_TYPE,  /* 37 Stateful Other Config parameter
                                            type invalid */
    IP6_ND_ERR_INVALID_SFADDR_NOT_USETYPE,  /* 38 Invalid Stateful Address Not
                                            usable reason type */
    IP6_ND_ERR_MBUF_CREATE_FAILED,          /* 39 MBUF Control packet creation
                                            failed */
    IP6_ND_ERR_UNALIGNED_ADDRESS,           /* 40 Un aligned address */
    IP6_ND_ERR_DESTCACHE_EMPTY,             /* 41 Destination Cache is empty */
    IP6_ND_ERR_DESTCACHE_MATCH_FAIL,        /* 42 Destination Cache match failed */
    IP6_ND_ERR_NO_LRUDESTCACHE_ENTRY,       /* 43 No LRU entry present for delete*/
    IP6_ND_ERR_END_OF_LIST,                 /* 44 End of list reached */
    IP6_ND_ERR_NO_NEXTHOP_FOUND,            /* 45 If Next hop determination fail */
    IP6_ND_ERR_WRITE_EVENT_TO_TASK_FAILED,  /* 46 Writing event to ND task failed*/
    IP6_ND_ERR_GET_FIRST_NODE_FAIL,         /* 47 Get First node failed */
    IP6_ND_ERR_WAITLIST_REGISTER_FAIL,      /* 48 Waitlist register failed */
    IP6_ND_ERR_WAITLISTGET_PARAM_FAIL,      /* 49 Get Params from waitlist failed*/
    IP6_ND_ERR_INVALID_WAITLIST_ID,         /* 50 Invalid waitlist ID */
    IP6_ND_ERR_INVALID_PREFIX_LEN_RANGE,    /* 51 Invalid Prefix Length */
    IP6_ND_ERR_PREF_LIFE_TIM_EXCEED,        /* 52 Invalid Lifetime */
    IP6_ND_ERR_SAME_CFG_VALUE,              /* 53 Config value is same as previous
                                            value */
    IP6_ND_ERR_INTERFACE_DOWN,              /* 54 IP6 Protocol is down for the
                                            interface*/
    IP6_ND_ERR_NO_NB_ENTRY,                 /* 55 No Neighbor entry present */

    /* Begin: Added by Santhosh 71702, 2007/12/29
       Description: Error codes for exceeding PAF values */
    IP6_ND_ERR_MAX_INF_STAT_NBENTRIES_REACHED,  /* 56 */
    IP6_ND_ERR_MAX_INF_NBENTRIES_REACHED,       /* 57 */

    /* End: Added by Santhosh 71702, 2007/12/29 */

    /* Begin :Changes for AC4D05067 by Anand on 20-02-2008*/
    IP6_ND_ERR_MAX_STAT_NB_PER_BOARD_REACHED,   /* 58 */
    IP6_ND_ERR_SEMOP_ACQUIRELOCK_FAIL,          /* 59 */

    /* BEGIN : NDHOST SDV Defect AC4D05549, Anand */
    IP6_ND_ERR_WAITLIST_UNREGISTER_FAIL,    /* 60 Waitlist un-register failed */

    /* Changed by Anand, for adhering to Log check list */
    IP6_ND_ERR_TIMER_CREATE_FAIL,           /* 61 Timer Creation failed */
    IP6_ND_ERR_INVALIDIFPHYTYPE,            /* 62 If phy type is invalid */
    IP6_ND_ERR_GETTMTIMEFAIL,               /* 63*/
    IP6_ENUM_ERRORS_PAD = IP6_ND_MAX_ENUM_VALUE

}IP6_ND_ERRORS_E;

/* End: Added by Santhosh 71702, 2007/12/19 */
/* IAS operation */
typedef enum tagIP6_ND_IAS_OPERATION
{
    IP6_ND_IAS_NOTIFY_NBENTRY_ADD,     /* IAS NB entry addition operation */
    IP6_ND_IAS_NOTIFY_NBENTRY_DELETE,  /* IAS NB entry deletion operation */
    IP6_ND_IAS_NOTIFY_NBENTRY_MODIFY,  /* IAS NB entry modification operation */
    IP6_ND_IAS_NOTIFY_MAX,
    IP6_ND_IAS_NOTIFY_ULONG = IP6_ADDR_MAX_ENUM_VALUE
}IP6_ND_IAS_OPERATION_E;

/* End: Added by Santhosh 71702, 2007/12/19 */

/*----------------------------------------------*
 *              Data Structures                 *
 *----------------------------------------------*/

/* Neighbor Solicitation packet Structure */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagND_NS
{
    ULONG       ulIfIndex;        /*�ӿ�����*/
    UCHAR       ucDADFlag;        /*DAD���ı��*/
    UCHAR       ucOptionFlag;     /*�Ƿ��ѡ����*/
    USHORT      usPad;
    IN6ADDR_S   stDstAddr;        /*Ŀ�ĵ�ַ*/
    IN6ADDR_S   stSrcAddr;        /*Դ��ַ*/
    IN6ADDR_S   stTgtAddr;        /*Ŀ���ַ*/
}ND_NS_S;

/* Begin: Added by Santhosh 71702, 2007/12/19 */
/* The structure is added for IAS. Structure contains VLAN ID and Port index */
typedef struct tagND_PKT_CTLPARAM
{
    ULONG    ulPortIndex;  /* Receive Port */
    USHORT   usVlanId;     /* Receive VlanId */
    UCHAR    ucReserve[2];
}ND_PKT_CTLPARAM_S;

/*�ھ������ݽṹ*/
/* HCC error: Structure having more than 5 elements - Obvious */
typedef  struct    tagNeighborEntry
{
    ULONG       ulIfnetIndex;    /*�ӿ�����*/
    ULONG       ulVLinkIndex;
    IN6ADDR_S   stIPv6Addr;     /*�ھӵ�IPv6��ַ*/

    /*when the NS has no SLLA info, we should create the entry and fill the
    entry all the related info especially this field. We can put the NS target
    address to this field. After sending NS and receiving the NA to get the
    SLLA of the source node, we can find this entry according this field,
    then send the NA and delete the target address in the entry. */

    IN6ADDR_S    stNAIPv6Addr;

    UCHAR        ucLLAddr[MACADDRLEN];    /*�ھӵ���·��ַ*/
    UCHAR        ucLLAddrFlag;            /*�ӿ�������·��ַ�ı�־*/
    UCHAR        ucIsRouter;              /*�ھӵ�·������־*/
    UCHAR        ucState;                 /*�ھ�״̬*/
    UCHAR        ucIsStaticEntry;
    UCHAR        ucPad;
    UCHAR        ucNoPpiDelNDFlag;        /*���·�PPI ɾ��ND�ı��λ����Ʒ���Ƴ���*/
    ULONG        ulReachableTimeElapsed;

    /* added for MIB timestamp Net To Media */
    ULONG        ulTimeStamp;

    /* ULONG           ulExpire;                ״̬�仯Ԥ��ʱ��*/
    ULONG              ulExpireHigh;   /* High ULONG of millisecond curr time*/
    ULONG              ulExpireLow;    /* Low ULONG of millisecond curr time*/

    ND_NS_S      stNSInfor;       /*Ҫ���͵�NS����*/

    struct tagNeighborEntry *pstNext;         /*��һ��*/
    struct tagNeighborEntry *pstPrevious;     /*��һ��*/

    VOID        *pND_Data;/* To store the MBUF_S and start address resolution*/

    ULONG       aulProductInfo[NB_ENTRY_PRODUCTINFO_SIZE];    /* ��Ʒ��Ϣ */
    USHORT      usNeedNS;       /*�����ھӲ��ɴ�����Ҫ���͵Ĵ���*/

    /* Begin: Modified by Santhosh 71702, 2007/12/29 */
    /* Control parmeters (VLAN ID and Port index) using by IAS product */
    USHORT   usVlanId;     /* Receive VlanId */
    ULONG    ulPortIndex;  /* Receive Port */
    ULONG    ulVrfIndex;  /*add by wuling for VRF6 project 2013-10-10*/

    /* End: Modified by Santhosh 71702, 2007/12/29 */

    UCHAR   *pucRdxExtNode;

    ULONG        ulCreatedTimeStamp;             /* �������ʱ�� */

}ND_NBENTRY_S;

/* RFC 2461: => Prefix Option fields
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |     Type      |    Length     | Prefix Length |L|A| Reserved1 |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                         Valid Lifetime                        |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                       Preferred Lifetime                      |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                           Reserved2                           |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                                                               |
      +                                                               +
      |                                                               |
      +                            Prefix                             +
      |                                                               |
      +                                                               +
      |                                                               |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


*/

/* Moved to External include */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct  tagND_Prefix
{
    ULONG       ulIfnetIndex;       /*�ӿ�����*/
    ULONG       ulLen;              /*ǰ׺ѡ���ܳ���*/
    ULONG       ulValidTime;        /*ǰ׺��Ч��������*/
    ULONG       ulPreferredTime;    /*ǰ׺��ѡ��������*/
    UCHAR       ucLFlag;            /*OnLink��־*/
    UCHAR       ucAFlag;
    USHORT      usPad;              /*Autoconfig��־*/

    /* The count is maintained as there are many addresses with same
    prefix with different interface ids, AddrMgt will notify ND for all, hence
    we maintain one prefix, and when count is 0, delete the prefix. */

    ULONG                   ulCount;
    IN6ADDR_S               stPrefix;       /*ǰ׺*/
    struct tagND_Prefix    *pstPrevious;    /*��һ��*/
    struct tagND_Prefix    *pstNext;        /*��һ��*/
    ULONG    ulStatus;
}ND_PREFIX_S;

/* Moved to External Include  */

#ifndef _NDTIMER_
#define _NDTIMER_

/*NDģ�鶨ʱ�������ݽṹ*/
typedef  struct tagND_Timer
{
    ULONG   ulTimerType;
    ULONG   ulTimerID;
    ULONG   ulIfIndex;
    ULONG   ulReserved;

}ND_TIMER_S;
#endif


/*�ظ���ַ������ݽṹ*/
/* HCC error: Structure having more than 5 elements - Obvious */
typedef  struct    tagDAD
{
    ULONG              ulIfIndex;               /*�ӿ�����*/
    IP6IFADDR_S        *pstIp6IfAddr;           /*����ⵥ����ַ*/
    ULONG              ulDADAttempt;            /*�������ھ�����Ĵ���*/
    /* Modified by guojianjun178934, IPV6 DAD̽�ⶨʱ���޸ķ������, 2014/2/12   ���ⵥ��:S-IP-003-PUBLIC-FUNC-005  */
    ULONG              ulExpireHigh;            /*��һ�η����ھ������Ԥ��ʱ��*/
    ULONG              ulExpireLow;             /*��һ�η����ھ������Ԥ��ʱ��*/
    /*End of Modified by guojianjun178934, 2014/2/12   ���ⵥ��:S-IP-003-PUBLIC-FUNC-005  */
    struct    tagDAD    *pstTotalNext;          /*��������һ��*/
    struct    tagDAD    *pstTotalPrevious;      /*��������һ��*/
    struct    tagDAD    *pstIfNext;             /*�ӿ�������һ��*/
    struct    tagDAD    *pstIfPrevious;         /*�ӿ�������һ��*/
}DAD_S;


/*·����������Ϣ�������ݽṹ*/
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct   tagND_RA
{
    ULONG          ulIfnetIndex;          /*�ӿ�����*/
    UCHAR          ucSendRAFlag;        /*����·���������־*/
    UCHAR          ucMFlag;              /* M��־λ */
    UCHAR          ucOFlag;              /* O��־λ */
    UCHAR          ucRtLifetimeFlag;      /*·����������Ϊ0��ǣ����ֵΪ1
    ��ʾ·������������Ϊ0�����ֵΪ0��ʾ·����������Ϊ�趨ֵ*/
    ULONG          ulRtlifetime;           /* ·���������� */
    ULONG          ulReachable;          /*�ɴ�ʱ��*/
    ULONG          ulRetrans;             /*�ش�ʱ��*/
    ULONG          ulRAIntervalMax;      /*����·���������ʱ���������ֵ*/
    ULONG          ulRAIntervalMin;      /*����·���������ʱ��������Сֵ*/
    ULONG          ulTimerID;            /*RA��ʱ��ID*/
    ULONG          ulLastSendTime;       /*�ϴη���·���������ʱ��*/
    ULONG          ulTime;               /*�´η���·���������ʱ��*/

    /*  The address structures are added to support unicast RA send messages
        and the CLI prefix are now being supported */

    IN6ADDR_S      stDstAddr;
    ND_PREFIX_S    *pstCliPrefix;            /*Ҫ���͵�ǰ׺ͷָ��*/


    ND_PREFIX_S    *pstPrefix;            /*Ҫ���͵�ǰ׺ͷָ��*/

    ULONG          ulFlag;                /*������ʶRA���Ƿ�Ҫ����Ĭ������*/

    IN6ADDR_S      stIPv6AddrDel;        /*RA source address has been deleted,
                                            but RA has not been sent*/
    IN6ADDR_S      stIPv6AddrAdd;       /*RA source address has been added,
                                            but RA has not been sent*/

    /* All are used only in case of sending unicast RA */
    ULONG          ulSendUnicastRA;
    IN6ADDR_S      stUnicastAddr;
    ULONG          ulNextMulticastRATime;

    BOOL_T         usCliPrxNum;            /*ǰ׺�����е�ǰ׺����*/
    BOOL_T         usPrxNum;            /*ǰ׺�����е�ǰ׺����*/

    UCHAR          ucFinalRa;
    UCHAR          ucPad[2];

    /*Reason: This flag has been added to check whether Router-lifetime is
      user-configured or default */
    UCHAR ucIsRtLifeTimeConfigured;

    ULONG          ulMinConfig;
    ULONG          ulInitAdver;    /* Value to keep track of number of initial
                                     advertisements */
}ND_RA_S;


/* ND Info Structure */
/* HCC error: Structure having more than 5 elements - Obvious */
/* IP6_ND_HOSTPARAMS_S pointer will not be used in Router but still the
structure is defined, Otherwise it has to be declared as VOID and in all
ND Host code it has to be typecasted. */
typedef struct tagNDInfo
{
    ULONG          ulIfIndex;              /*�ӿ�����*/
    UCHAR          ucInterfacePhyState;    /*�ӿ�����״̬*/
    UCHAR          ucInterfaceState;       /*�ӿ�״̬*/
    UCHAR          ucLLAddr[MACADDRLEN];   /*�ӿڵ���·��ַ*/
    UCHAR          ucLLAddrFlag;           /*�ӿ�������·��ַ�ı�־*/
    UCHAR          ucNDSpecialProxyFlag;   /*�ӿ�ʹ������ND������*/
    UCHAR          ucPad[2];
    ULONG          ulNSInterval;           /*�����ھ������ʱ����*/
    ULONG          ulReachableTime;        /*�ھ���ɴ�ʱ��*/
    ULONG          ulTimerID;              /*�ھ��ʱ��ID*/
    ULONG          ulNBForceDelTimerID;    /*This timer will be started to
                                            clean the NB cache when it reaches
                                            the critical value*/
    ND_TIMER_S     stNDNBTimerMsg;
    ND_NBENTRY_S   *pstNBEntry;            /*�ھ���ͷָ��*/
    DAD_S          *pstDAD;                /*�ӿ�DAD����ͷָ��*/
    ND_RA_S        stRAInfo;               /* RA configuration information */

    ULONG          ulNBNum;                /*�˽ӿ����ھ���ĸ���*/
    ULONG          ulTotalStatic;

    /* Begin: Modified by Santhosh 71702, 2007/12/19 */

    /* Description: Static array is changed to pointer which can be allocated
       dynamically because maximum number of NB entries per Interface is now
       supporting by PAF */

    /* End: Modified by Santhosh 71702, 2007/12/19 */

    ULONG          ulDADAttempt;        /*�ظ���ַ���ʱ�����ھ�����Ĵ���*/

    ULONG          ulLastTimeNASentTimeStamp;

    /* Begin : Changes for AC4D05067 by Anand on 20s-02-2008 */
    ULONG          ulNonDeleteNBEntries; /* Non Deletable NB entries */

    /*Added by guojianjun178934,  �ӿ�״̬�仯��MAC��ַ�仯��������ͨ��NA����, 2014/1/26   ���ⵥ��:S-IP-005-PUBLIC-FUNC-003 */
    SLL_S           *pstNARoot;
    ND_TIMER_S      stNDNATimerMsg;
    ULONG           ulNATimerID;      /*�ӿ�����ͨ��NA���Ķ�ʱ��ID*/
    ULONG           ulNAInterval;     /*NA�����ش�ʱ����*/
    ULONG           ulNAMinDelay;     /*�׸�NA���ĵ���С����ʱ��*/
    ULONG           ulNAMaxDelay;     /*�׸�NA���ĵ������ʱ��*/
    ULONG           ulMaxNACount;     /*NA��������ʹ���*/
    /* End of Added by guojianjun178934, 2014/1/26   ���ⵥ��:S-IP-005-PUBLIC-FUNC-003 */

    SLL_S           *pstDADExtRoot;
    ND_TIMER_S      stNDDADExtTimerMsg;
    ULONG           ulDADExtTimerID;      /*�ӿ�ִ��DAD��չ��ʱ��ID*/
    
    /* Modified by Srinivas (s00900781) : AC4D08714 defect */
    VOID           *pvHostParams;  /* ND Host parameters */

    VOID          *pvNDRootNode;  /* Root node for the radix tree */

}NDINFO_S;


/* New structure defined to send info to Shell for Build Run and Sync*/
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagND_GETFROMCORE
{
    ULONG         ulReachable;
    ULONG         ulAdvReachable;
    ULONG         ulNSInterval;
    ULONG         ulRAIntervalMax;
    ULONG         ulRAIntervalMin;
    ULONG         ulRAMinConfig;
    ULONG         ulRtlifetime;
    UCHAR         ucSendRAFlag;
    UCHAR         ucMFlag;
    UCHAR         ucOFlag;
    UCHAR         ucCurHopLimit;
    ND_PREFIX_S   *pstCliPrefix;
    ND_PREFIX_S   *pstPrefix;
    ULONG         ulDADAttempt;
    UCHAR         ucIsRtLifeTimeConfigured;
    UCHAR         ucRes[3];
} ND_GETFROMCORE_S;

/* Prefix Table */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagIP6_ND_PrefixTbl
{
    ULONG          ulIfIndex;
    IN6ADDR_S      stIpv6AddressPrefix;
    ULONG          ulIPv6AddrPrefixLength;
    BOOL_T         ipv6AddrPrefixOnLinkFlag;
    BOOL_T         ipv6AddrPrefixAutonomousFlag;
    ULONG          ulIPv6AddrPrefixAdvPreferredLifetime;
    ULONG          ulIPv6AddrPrefixAdvValidLifetime;
}IP6_ND_PrefixTbl_S;

/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagIP6_ND_Net2MediaTbl
{
    ULONG          ulIfIndex;
    IN6ADDR_S      stipv6NetToMediaNetAdd;
    UCHAR          ucMacAddr[MACADDRLEN];
    BOOL_T         usipv6NetToMediaValid;
    ULONG          ulipv6NetToMediaType;
    ULONG          ulipv6IfNetToMediaState;
    ULONG          ulipv6IfNetToMediaLastUpdated;

}IP6_ND_Net2MediaTbl_S;


/* SGSN Stub call back functions */
typedef struct tagIP6_ND_SGSN_CALLBACK_FUNC
{
    /* SGSN CallBacks */
    ULONG (*pfPPI_IPV6_OpIpv6Route)(VOID * pvRtMsg);
    ULONG (*pfPPI_IPV6_OpIpv6Neighbor)(UCHAR ucOpType, VOID* pstNBEntry,
                                                    ULONG *pulVlinkIndex);
    ULONG (*pfPPI_IPV6_NDNeedToLookUp)(MBUF_S* pstMbuf);

}IP6_ND_SGSN_CALLBACK_FUNC_S;

/* Neighbor Entry */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef  struct    tagNeighborEntryInfo
{
    ULONG       ulIfnetIndex;
    ULONG       ulVLinkIndex;
    IN6ADDR_S   stIPv6Addr;                /*�ھӵ�IPv6��ַ*/
    UCHAR       ucLLAddr[MACADDRLEN];      /*�ھӵ���·��ַ*/
    UCHAR       ucLLAddrFlag;              /*�ӿ�������·��ַ�ı�־*/
    UCHAR       ucIsRouter;                /*�ھӵ�·������־*/
    UCHAR       ucState;                   /*�ھ�״̬*/
    UCHAR       ucIsStaticEntry;
    USHORT      usPad;
    ULONG       ulReachableTimeElapsed;
    ULONG       ulTimeStamp;
    ULONG       ulExpireHigh;
    ULONG       ulExpireLow;
    ULONG       ulVrfIndex;  /*add by wuling for VRF6 project 2013-10-10*/

    /* IAS changes Start :
            This field is using by IAS product to display Vlan-ID and Port name.
    */
    ND_PKT_CTLPARAM_S stNDCtrlParam;       /* Control parameters (vlan-id,
                                            port index) */

    /* IAS changes End */

}ND_NBENTRY_INFO_S;

/* Begin: Added by Santhosh 71702, 2007/12/19 */
/* Structure using as Static neighbor entry addition API argument */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef  struct    tagStaticNeighborEntry
{
    ULONG       ulIfnetIndex;   /* Interface index */
    IN6ADDR_S   stIn6Addr;      /* IPv6 address */

    /* This field is using by IAS product */
    /* Control parameters (vlan-id, port index) */
    ULONG       ulPortIndex;    /* Receive Port */
    USHORT      usVlanId;       /* Receive VlanId */

    /* LLA size is taken as 6 bytes, based on the change in size padding needs
       to add for 4-byte allignment */
    UCHAR       aucLLAddr[MACADDRLEN];    /* Link layer address - 6 Bytes */
}ND_STATIC_NBENTRY_S;

/* End: Added by Santhosh 71702, 2007/12/19 */

/* NB update should notify VISP socket for Head cache */
typedef struct tagIP6_ND_SOCK_CALLBACK_SET_S
{
    VOID (*pfHeadCache_Event) (ULONG ulEventType, VOID *pData);
}IP6_ND_SOCK_CALLBACK_SET_S;

typedef struct tagIP6_ND_FLOW_CALLBACK_SET_S
{
    ULONG (*pfIP6_ND_Incoming_Flow_Callback)(ULONG ulIfIndex, VOID *pvMBuf);
}IP6_ND_FLOW_CALLBACK_SET_S;


/****************************************************************************
 *                  Nd_public.h Changes for ND Host Feature support         *
 ****************************************************************************/
/***********/
/* Defines */
/***********/



/* MAX, MIN Params for ND Host */

/* Default Router list entries per interfaces */
#define IP6_ND_MAX_DEFRTR_PER_INTF              4
#define IP6_ND_MIN_DEFRTR_PER_INTF              2
#define IP6_ND_DEF_DEFRTR_PER_INTF              4

/* Prefix list entries per interfaces */

#define IP6_ND_MAX_PREFLIST_PER_INTF            16
#define IP6_ND_MIN_PREFLIST_PER_INTF            1
#define IP6_ND_DEF_PREFLIST_PER_INTF            16

/* Destination Cache entries */
#define IP6_ND_MAX_DESTCACHE_ENTRY              64
#define IP6_ND_MIN_DESTCACHE_ENTRY              1
#define IP6_ND_DEF_DESTCACHE_ENTRY              64

/* Macro for FIB Route notification type */
/* TODO to be moved to FIB public */
#define SIFB6_EVENTNOTIFY_ROUTE_ADD             0x01
#define SIFB6_EVENTNOTIFY_ROUTE_DELETE          0x02

/* Used to return invalid hop limit in Global Hop Limit, bcz in Host
the hop limit is maintained per interface, So the Global GetHopLimit API
 will return this value */
#define IP6_ND_INVALID_HOP_LIMIT                0xFF

/* Neighbor Entry States */
#define ND_STATE_INVALID                0
#define ND_STATE_INCOMPLETE             1
#define ND_STATE_REACHABLE              2
#define ND_STATE_STALE                  3
#define ND_STATE_DELAY                  4
#define ND_STATE_PROBE                  5

/* Macros to indicate the reset type values */
#define IP6_ND_RESET_ALL                1
#define IP6_ND_RESET_STATIC             2
#define IP6_ND_RESET_DYNAMIC            3

/*add by wuling for ND Proxy project 2013-11-30 --start*/
#define IP6_ND_SPECIAL_PROXY_DISABLE         0
#define IP6_ND_SPECIAL_PROXY_ENABLE          1

#define IP6_ND_SPECIAL_PROXY_ACTIVE          0x01
#define IP6_ND_SPECIAL_PROXY_INACTIVE        0x02 
/*add by wuling for ND Proxy project 2013-11-30 --end*/

/*********/
/* Enums */
/*********/

/* Identity Association Type - Temporary/Non-temporary Addresses */
typedef enum tagIP6_ND_IAType
{
    IP6_ND_IA_TYPE_NA = 0,      /* Non Temporary IA */
    IP6_ND_IA_TYPE_TA,          /* Temporary IA */
    IP6_ND_IA_MAX,
    IP6_ND_IA_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_IATYPE_E;

/* Stateful address configuration operation type */
typedef enum tagIP6_ND_StatefulCfg_OptType
{
    IP6_ND_STFULCFG_ADDITION = 0,
    IP6_ND_STFULCFG_DELETION,
    IP6_ND_STFULCFG_LIFETIMEUPDATION,
    IP6_ND_STFULCFG_MAX,
    IP6_ND_STFULCFG_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_STATEFULCFG_OPTTYPE_E;

/* Notification type about presence of DHCPv6 Server to Client Adaptor */
typedef enum tagIP6_ND_DHCPV6SERVER_AVAIL
{
    /* DHCPv6 Server Available for Address and Other configuration */
    IP6_ND_SA_NOTIFY_MFLAG = 0,

    /* DHCPv6 Server Available only for Other configuration */
    IP6_ND_SA_NOTIFY_OFLAG,

    /* Absence of Router in link */
    IP6_ND_SA_NOTIFY_NO_RA,
    IP6_ND_SA_NOTIFY_MAX,
    IP6_ND_SA_NOTIFY_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_DHCPV6SERVER_AVAIL_E;

/* Notification to Client Adaptor about Non usability of the Stateful Address */
typedef enum tagIP6_ND_Notusable_Reason
{
    /* The Address provide is not unique on the link */
    IP6_ND_NOTUSE_ADDR_DUPLICATE = 0,

    /* Release the Address */
    IP6_ND_NOTUSE_RELEASE,

    /* The statefull address provided is alreay present in the systme (same
    interface or different interface) */
    IP6_ND_NOTUSE_ADDRCONFLICT,

    /* Maximum number of Address configuration has reached */
    IP6_ND_NOTUSE_MAX_ENTRY_REACHED,

    /* Invalid address (Address Type/Life time) */
    IP6_ND_NOTUSE_INVALID_ADDRESS,

    /* Address entry not present */
    IP6_ND_NOTUSE_ADDRESS_NOTPRESENT,

    /* Invalid Interface Index in IA Descriptor */
    IP6_ND_NOTUSE_INTF_NOTPRESENT,

    /* IA type in IA descriptor is not supported  */
    IP6_ND_NOTUSE_IATYPE_NOTSUPPORTED,

    /* SRM Table Space is Full */
    IP6_ND_NOTUSE_SRM_TBL_FULL,

    /* Invalid Address Info */
    IP6_ND_NOTUSE_INVALID_ADDRINFO,

    /* Maximum No of Address entry reached */
    IP6_ND_NOTUSE_MAXADDR_ENTRY_REACHED,

    IP6_ND_NOTUSE_MAX,
    IP6_ND_NOTUSE_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE

}IP6_ND_NOTUSABLE_REASON_E;


/* Other configuration Information type enum */
typedef enum tagIP6_ND_OTHERCONFIGPARAMTYPE
{
    IP6_ND_MTU = 0,         /* IPv6 Link MTU */
    IP6_ND_HOPLIMIT,        /* Hop limit */
    IP6_ND_BASEREACH_TIME,  /* Base Reachable time value */
    IP6_ND_NSRETRANS_TIME,  /* NS Retransmission time value */
    IP6_ND_OTHERCFG_MAX,
    IP6_ND_OTHERCFG_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_OTHERCFGPARAMTYPE_E;


/* Enum to store different type of Source of Route */
typedef enum tagND_ROUTESOURCE
{
    IP6_ND_ROUTSRC_SFIB = 0,            /* Source of Route from FIB */
    IP6_ND_ROUTSRC_PREFIX_LIST,         /* Source of Route from Prefix List */
    IP6_ND_ROUTSRC_DEF_ROUTER_LIST,     /* Source of Route from Def Rtr list*/
    IP6_ND_ROUTSRC_OWN_ADDRESS,         /* Dest. is own address */
    IP6_ND_ROUTSRC_MAX,
    ND_ROUTSRC_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}ND_ROUTESOURCE_E;

/* Default Router entry state enum */
typedef enum tagIP6_ND_DefRtrState
{
    /* The Router's NB cache entry is in a state other than INCOMPLETE*/
    IP6_ND_DR_ST_REACHABLE = 0,

    /* The Router's NB cache entry is in INCOMPLETE
    state or there is no corresponding entry in the NB cache.*/
    IP6_ND_DR_ST_NOT_REACHABLE,
    IP6_ND_DR_ST_MAX,
    IP6_ND_DR_ST_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_DEFRTRSTATE_E;

/* Configuration Operation */
typedef enum tagIP6_ND_CFG_OPT
{
    IP6_ND_CFG_OPT_DISABLE = 0, /* Disable Operation */
    IP6_ND_CFG_OPT_ENABLE,      /* Enable Operation */
    IP6_ND_CFG_MAX,
    IP6_ND_CFG_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_CFG_OPT_E;


/****************************************************************************/
/* Structures */

/* Get all Interface related Parameters */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagIP6_ND_GetHostParams
{
    ULONG         ulBaseReachTime;      /* Base Reachable Time */
    ULONG         ulReachTime;          /* Random Reachable time */
    ULONG         ulNSRetransInterval;  /* NS Retransmission Interval */
    ULONG         ulDADAttempt;         /* Number of DAD NS to be sent */
    ULONG         ulCurHopLimit;        /* Current Hop limit */
    ULONG         ulLinkMTU;            /* Link MTU value */
    UCHAR         ucStoredMandOFlag;    /* Managed and Other Flag bitMap*/
    UCHAR         ucPad[3];             /* Padding*/
}IP6_ND_GETHOSTPARAMS_S;


/* Contain the various attributes of the added/deleted route information */
/* HCC error: Structure having more than 5 elements - Obvious */
/* Note: Prefix length is ULONG, to avoid typecast (Radix tree)- Obvious */
typedef struct tagSFIB6_ROUTEINFO
{
    ULONG   aulDestination[4];      /* Destination Address */
    ULONG   aulNextHop[4];          /* Next Hop Address */
    ULONG   ulOutIfIndex;           /* Outgoing Interface */
    ULONG   ulATIndex;              /* AT Index */
    ULONG   ulFlags;                /* Route Flags */
    ULONG   ulProtocol;             /* Route Protocol */
    ULONG   ulPrefixLen;            /* Prefix Length  */

}SFIB6_ROUTEINFO_S;


/* Default Router List Structure - Used in Display */
typedef struct tagND_DefRouter_Info
{
    IN6ADDR_S stIPv6Addr;           /* Default Router Address */

    /* Time stamp updated when Router entry is newly created or lifetime
    of existing entries are updated */
    ULONG ulLastChangeTime;

    /* Default Router State (PROBABLY_REACHABLE/NOT_REACHABLE)*/
    IP6_ND_DEFRTRSTATE_E enState;
    USHORT usLifetime;            /* Router lifetime */
    UCHAR aucPad[2];              /* Padding */

}IP6_ND_DEFROUTER_INFO_S;


/* Interface Level Prefix List Structure - Used in Display */
typedef struct tagND_IntfPrefix_Info
{


    IN6ADDR_S stPrefix;          /* Prefix */
    ULONG ulValidLifetime;       /* Valid Lifetime of Prefix */

    /* Time stamp when the Prefix entry created/updated its lifetime */
    ULONG ulLastChangeTime;
    UCHAR ucPrefixLen;          /* Prefix Length */
    UCHAR aucPad[3];            /* for padding */
}IP6_ND_INTFPREFIX_INFO_S;


/* Destination Cache Structure - Used in Display */
typedef struct tagND_DestCache_Info
{
    IN6ADDR_S   stDestAddr;         /* Destination Address */
    IN6ADDR_S   stNextHopAddr;      /* Next hop Address */
    ULONG       ulTimeStamp;        /* Time Stamp to Force Delete entries */
    ULONG       ulOGIfnetIndex;     /* Outgoing interface index */
    ND_ROUTESOURCE_E  enSRCRoute;   /* Source of Route */

}IP6_ND_DESTCACHE_INFO_S;


/* IA Descriptor */
typedef struct tagIP6_ND_IADESC_S
{
    ULONG           ulIfindex;  /* IFNET index */
    IP6_ND_IATYPE_E enIAType;    /* IA type */
    ULONG           ulIAID;     /* IAID */
}IP6_ND_IADESC_S;


/* Address with Lifetime values */
typedef struct tagIP6_ND_IN6ADDRWITHTIME
{
    IN6ADDR_S stAddress;           /* Address in IA */
    ULONG ulPreferedLifeTimeValue;  /* Preferred life time of address */
    ULONG ulValidLifeTimeValue;     /* Valid life time of address */
}IP6_ND_IN6ADDRWITHTIME_S;

/* DHCPv6 Client Adaptor Call back functions */
typedef struct tagIP6_ND_DHCP6CAdapt_CallBack
{

    /* Callback to inform the presence of a stateful server on the link for
    Address/Other configuration or to inform the Router Discovery Failure. */
    ULONG (*pfIP6_ND_NotifyServerAvailability)(ULONG ulIfnetIndex,
                                IP6_ND_DHCPV6SERVER_AVAIL_E eNotifyType);

    /* Callback to Notify Client Adaptor about Non usability of the Stateful
       Address */
    ULONG (*pfIP6_ND_DHCP6CAdaptAddrNotUsable)(IP6_ND_IADESC_S *pstIADesc,
            IP6_ND_IN6ADDRWITHTIME_S *pstAddress,
            IP6_ND_NOTUSABLE_REASON_E eType);

}IP6_ND_DHCP6CADAPT_CALLBACK_S;


/* Other configuration Information for Stateful autoconfiguration protocol */
typedef struct tagIP6_ND_OtherConfigParams
{
    ULONG ulIfIndex;            /* Interface index */
    ULONG ulValue;              /* Other Config Value */
    IP6_ND_OTHERCFGPARAMTYPE_E enParamType;
}IP6_ND_OTHERCFGPARAMS_S;

/* Begin : Added by Suraj_R for NP Support */
typedef struct tagIP6_ND_NP_MSG
{
    ULONG     ulIfIndex;             /* Interface Index */
    IN6ADDR_S stIP6Addr;             /* IPv6 Address */
    UCHAR     ucLLAddr[MACADDRLEN];  /* MAC Address */
    UCHAR     ucType;                /* Static / Dynamic,
                                        Possible Values :
                                        IP6_ND_NON_STATIC_ENTRY
                                        IP6_ND_STATIC_ENTRY
                                      */
    UCHAR     ucState;               /* NB Entry State :
                                        Possible Values :
                                        ND_STATE_INCOMPLETE
                                        ND_STATE_REACHABLE
                                        ND_STATE_STALE
                                      */
    USHORT   usVlanId;     /* VlanId */
    USHORT   usPad;         /* Padding */
    ULONG    ulVrfIndex;  /*add by wuling for VRF6 project 2013-10-10*/
}IP6_ND_NP_MSG_S;


typedef struct tagIP6_ND_NP_PL_MSG
{
    ULONG     ulIfIndex;             /* Interface Index */
    IN6ADDR_S stIP6Prefix;           /* IPv6 Prefix */
    ULONG     ulPrefixLen;           /* Prefix Length */
}IP6_ND_NP_PL_MSG_S;

typedef struct tagIP6_ND_NP_DRL_MSG
{
    ULONG     ulIfIndex;             /* Interface Index */
    IN6ADDR_S stIP6Addr;             /* IPv6 Prefix */
    ULONG     ulState;               /* Default Router State */
                                     /* Possible Values :
                                        IP6_ND_DR_ST_REACHABLE,
                                        IP6_ND_DR_ST_NOT_REACHABLE
                                     */
}IP6_ND_NP_DRL_MSG_S;


typedef struct tagIP6_ND_NP_DC_MSG
{
    ULONG     ulIfIndex;             /* Interface Index */
    IN6ADDR_S stDestIP6Addr;         /* Destination IPv6 address */
    IN6ADDR_S stNextHopIP6Addr;      /* Next Hop IPv6 address */
}IP6_ND_NP_DC_MSG_S;

/* End : Add by Suraj_R for NP Support */

/*add by wuling for ND64K project 2013-10-09 --start*/
typedef enum tagIP6_ND_NBSEARCH_TYPE
{
    IP6_ND_NBSEARCH_BY_L3IF = 0, 
    IP6_ND_NBSEARCH_BY_L2PORT,     
    IP6_ND_NBSEARCH_BY_RDX,
    IP6_ND_NBSEARCH_MAX = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_NBSEARCH_TYPE_E;
/*add by wuling for ND64K project 2013-10-09 --end*/

/*add by wuling for ND Proxy project 2013-11-30 --start*/
typedef struct tagIP6_ND_SPECIAL_PROXY_PARA
{
    ULONG     ulOutIfIndex;      /*ND����󶨵�ʵ�ʳ��ӿ�����*/
    IN6ADDR_S stIP6Addr;         /*�������IPv6��ַ*/
}IP6_ND_SPECIAL_PROXY_PARA_S;

typedef ULONG ( * gpfIP6NDSpecialNDProxy) (IP6_ND_SPECIAL_PROXY_PARA_S *pstSpecNDPrxyPara);
typedef ULONG ( * gpfIP6GetDADProxyIfIndex) (ULONG ulVrfIndex, IN6ADDR_S *pstIP6Addr, ULONG *pulIfIndex);
/*add by wuling for ND Proxy project 2013-11-30 --start*/

typedef struct tagTCPIPNDFilter
{
    ULONG ulIfIndex;
}TCPIP_ND_FILTER_S;

typedef  struct   tagTCPIPNeighborEntryInfo
{
    ULONG       ulIfnetIndex;
    IN6ADDR_S   stIPv6Addr;                /* �ھӵ�IPv6��ַ        */
    UCHAR       ucLLAddr[MACADDRLEN];      /* �ھӵ���·��ַ        */
    UCHAR       ucLLAddrFlag;              /* �ӿ�������·��ַ�ı�־*/
    UCHAR       ucIsRouter;                /* �ھӵ�·������־      */
    UCHAR       ucState;                   /* �ھ�״̬              */
    UCHAR       ucIsStaticEntry;
    USHORT      usVlanId;                  /* Receive VlanId        */
    ULONG       ulCreatedTime;             /* ����������ڵ����ʱ�� */
    ULONG       lLeftExpireTime;           /* �ϻ�ʣ��ʱ��          */
    ULONG       ulVrfIndex;                /* vrf����               */
    ULONG       ulReserv[6];
}TCPIP_ND_NBENTRY_INFO_S;

typedef struct tagTCPIPIfNDFilter
{
    ULONG ulIfIndex;      /*���ӿڹ���*/
}TCPIP_IF_ND_FILTER_S;

typedef struct tagTCPIPIfNDInfo
{
    ULONG ulIfIndex;      /*�ӿ�����*/
    ULONG ulDADAttempt;   /*DAD̽�����*/
    ULONG ulNSInterval;   /*NS ���ͼ��*/
    ULONG ulNAInterval;   /*NA���ͼ��*/
    ULONG ulNAAttempts;   /*NA ���ʹ���*/
    ULONG ulReachableTime;/*�ɴ�ʱ��*/
    ULONG ulStaticNeigborNums;  /*��̬�ھӸ���*/
    ULONG ulDynamicNeigborNums; /*��̬�ھӸ���*/
    ULONG ulReserv[8];    /*Ԥ���ֶ�*/
}TCPIP_IF_NDINFO_S;

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* _ND_PUBLIC_H*/
