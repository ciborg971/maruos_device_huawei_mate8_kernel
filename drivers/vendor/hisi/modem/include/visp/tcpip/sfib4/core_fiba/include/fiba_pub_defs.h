/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fiba_pub_defs.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-08
*       Author: Zhang Hongyan
*  Description: public macro define for agent.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-08   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00646
*  2006-04-21   Jiangtao                Adjust for D00859 
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#include "tcpip/sfib4/include/sfib4_api.h"    
#ifndef _FIBA_PUB_DEFS_H
#define _FIBA_PUB_DEFS_H


/* Debug Macro definition */
#define FIB6_DEBUG_OFF                   0x00000000       
#define FIB6_DEBUG_ON                    0x00000001

#define FIB6A_TIMER_QNAME                "F6TM"
#define FIB6A_MESSAGE_QNAME              "F6MS"
#define FIB6A_MESSAGE_QDEPTH             5000       /* Changed from 2000 by Guru for Fib6Opt.. 17/03/2004 */
#define FIB6A_TMR_QDEPTH                 256 * 2    /* Changed from 256 by Guru for Fib6Opt.. 17/03/2004 */
#define FIB6A_INVALID_QUEID              0

/* FIB task related */
#define EV_IP6_FIB_RTMSG                 0x00000001
#define EV_IP6_FIB_DEBMSG                0x00000002
#define EV_IP6_FIB_TMRMSG                VOS_TIMER_EVENT
#define EV_IP6_FIB_SMOOTH                0x00000004
#define EV_IP6_FIB_CMDDOWNLOADMSG        0x00000008 /* Added by Guru, for IPv6FIBOPT; 11-03-2004 */

#define FIB6A_MAX_TMRMSG_TOREAD          256        /* Added by Guru, for IPv6FIBOPT; 11-03-2004 */
#define FIB6A_TASK_DELAY                 20

#define FIB6A_TYPE_ROUTE                 0x00000005
#define FIB6A_TYPE_IPC_ROUTE             0x00000006
#define FIB6_TYPE_RPC_DEB                0x00000007

#define MAX_BALANCED_ENTRIES             32
/*Mod End*/

#define FIB6_MAX_TIMES_TO_TRY_IPCSEND    10
#define FIB6_MAX_TIMES_SEND_SMOOTH_START 100 /* trail */


#define FIB6_URT6_END              0x01000010
#define FIB6_URT6_FAILURE          0x01000011

#define FIB6_YES                   1
#define FIB6_NO                    0 

#define FIB6_INVALID_WAITLISTID    0



/* Interface related */
#define FIB6_BOARD_ISUP            1
#define FIB6_BOARD_ISDOWN          0

/* HA related */

#define FIB6A_SMOOTH_FIRST_TIME    0x1002
#define FIB6A_SMOOTH_SUCCS_TIME    0x1003

#define FIB6_DEF_PREFIX_LEN        128
#define FIB6_MAX_NUM_OF_ZONES      10
#define FIB4_MAX_NUM_OF_ZONES      1

#define FIB6_TYPE_RESET            0
#define FIB6_DEF_ZONEID            0
#define FIB4_DEF_ZONEID            0

#define FIB6_OLDRTMSG6             6    /* added for defect 7034; Guru, 1-03-04 */
#define FIB6_NEWRTMSG6             7    /* added for defect 7034; Guru, 1-03-04 */

#define FIB6A_TMR_EVT              VOS_TIMER_EVENT
/* Below definition is for max number of com id info supplied by RM */
#define FIB6A_MAX_COM_ID_TOUSE     6


/* Added by Guru, for defect id 3414 */
#define FIB6_LOADBALANCE_ENABLE    1
#define FIB6_LOADBALANCE_DISABLE   0
/* end of addition */

/* Err defs */
#define FIB6_ERR_NOT_ENOUGH_MEM    VOS_ERR + 1
#define FIB6_ERR_Q_WRITE           VOS_ERR + 2     
#define FIB6_ERR_EV_WRITE          VOS_ERR + 3
#define FIB6_ERR_RTMSG_INVALID     VOS_ERR + 4


#define FIB4_ERR_BLACKHOLE         1
#define FIB4_ERR_ENETUNREACH       2
#define FIB4_ERR_REJECT2           3

/* Search errors */
#define FIB6_ERR_BLACKHOLE         VOS_ERR + 5
#define FIB6_ERR_ENETUNREACH       VOS_ERR + 6
#define FIB6_ERR_REJECT2           VOS_ERR + 7

/* Search flags */
#define FIB6_RTF_UP                  0x1         /* route usable */
#define FIB6_RTF_GATEWAY             0x2         /* destination is a gateway */
#define FIB6_RTF_HOST                0x4         /* host entry (net otherwise) */
#define FIB6_RTF_REJECT              0x8         /* host or net unreachable */
#define FIB6_RTF_DYNAMIC             0x10        /* created dynamically (by redirect) */
#define FIB6_RTF_MODIFIED            0x20        /* modified dynamically (by redirect) */
#define FIB6_RTF_DONE                0x40        /* message confirmed */
#define FIB6_RTF_MASK                0x80        /* subnet mask present */
#define FIB6_RTF_CLONING             0x100       /* generate new routes on use */
#define FIB6_RTF_XRESOLVE            0x200       /* external daemon resolves name */
#define FIB6_RTF_LLINFO              0x400       /* generated by ARP or ESIS */
#define FIB6_RTF_STATIC              0x800       /* manually added */
#define FIB6_RTF_BLACKHOLE           0x1000      /* just discard pkts (during updates) */
#define FIB4_RTF_DISABLE             0x2000      /* route disable */
#define FIB6_RTF_PROTO2              0x4000      /* protocol specific routing flag */
#define FIB6_RTF_REJECT2             0x8000      /* protocol specific routing flag */
#define FIB6_RTF_SUBNET_BROCST       0x10000     /*�����㲥·��*/
#define FIB6_RTF_DISABLE             FIB4_RTF_DISABLE

#define FIB6_RTF_RELAY             0x200       /* by FIB for distinguishing relayed route; BYAD09878; 03-05-2004; Guru*/
#define FIB6_RTF_ADD_PPI           0x20000     /* Chandra */

#define SYSTRC_IPV6_FIBAGENT_BASE  01
#define IP6_FIBA_MSGHDLR           ((SYSTRC_IPV6_FIBAGENT_BASE << 8) + 010) 
#define IP6_FIBA_SYNCH             ((SYSTRC_IPV6_FIBAGENT_BASE << 8) + 011) 
#define IP6_FIBA_FAC               ((SYSTRC_IPV6_FIBAGENT_BASE << 8) + 012) 
#define IP6_FIBA_COM               ((SYSTRC_IPV6_FIBAGENT_BASE << 8) + 013) 

#define IP6_FIBA_SH_CFG            ((SYSTRC_IPV6_FIBAGENT_BASE << 8) + 014) 
#define IP6_FIBA_SH_HA             ((SYSTRC_IPV6_FIBAGENT_BASE << 8) + 015) 
#define IP6_FIBA_SH_LCS            ((SYSTRC_IPV6_FIBAGENT_BASE << 8) + 016) 
#define IP6_FIBA_SH_MAIN           ((SYSTRC_IPV6_FIBAGENT_BASE << 8) + 017) 


/*Search Protocol*/
#define FIB_PATH_CONNECTED          0x00020000
#define FIB_PATH_I3_LOCAL           0x00020001
#define FIB_PATH_I3_CONNECTED       0x00020002
#define FIB_PATH_I3_SUBNET_BROCST   0x00020003
#define FIB_PATH_STATIC             0x00030000
#define FIB_PATH_RIP                0x00080000 
#define FIB_PATH_I3_VLINK           0x00130000
#define FIB_PATH_I3_DHCP            0x00140000
/*END of Add*/

/*****************************************************************************/
/* OSPF-specific: Indicates a path to a destination belonging to one of the  */
/* router's attached OSPF areas.                                             */
/*****************************************************************************/
#define FIB_PATH_OSPF_INTRA_AREA  0x000D0000

/*****************************************************************************/
/* OSPF-specific: Indicates a path to a destination in another OSPF area.    */
/*****************************************************************************/
#define FIB_PATH_OSPF_INTER_AREA  0x000D0001

/*****************************************************************************/
/* OSPF-specific: Indicates a path to a destination external to OSPF with a  */
/* metric expressed in the same units as the OSPF internal metric.           */
/*****************************************************************************/
#define FIB_PATH_OSPF_TYPE1_EXT   0x000D0002

/*****************************************************************************/
/* OSPF-specific: Indicates a path to a destination external to OSPF with a  */
/* metric an order of magnitude larger than the OSPF internal metric.  A     */
/* cost in the type-2 metric is considered greater than any cost in the      */
/* type-1 metric.                                                            */
/*****************************************************************************/
#define FIB_PATH_OSPF_TYPE2_EXT   0x000D0003




/*END Add*/
/* Debug related */
#define FIB6A_DEBUG_MAIN           0            /* Main board for using debugout() */
#define FIB6A_DEBUG_IO             1            /* IO board for using debugout() */
#define FIB6_DBG_INVALID_STATE     0xffffffff   /* Init val for configproc() */

#define FIB6_IPC_RPC_TIMEOUT       1000 * 10 /* This is still need to be finalized, existing val is only for trial  */ 
#define FIB6_IPC_RPC_PRIO          3

/* Defect BYAD07089 fixed by Suraj 23 Jan 2004 . 
Macros indicating calling function type for IP6_FIB_FormatRT   */
#define FIB6_FORMATRT              1
#define FIB6_CACHE_FORMATRT        2

/* Added by Guru for memory shortage handling 05-05-2004 */
#define FIB6_MEM_SHORTAGE_REACH    5
#define FIB6_MEM_SHORTAGE_RESTORE  6

#define FIB6_NOT_FIND_ROUTE        3

#define FIB_isleap(y)                         (((((y)%4)==0)&&(((y)%100)!=0)) || (((y)%400)==0))
#define SFIB_NULL_ULONG                       0xFFFFFFFF


#define SFIB_NETIP(ulIpAddress, ulMaskLen)    ((ulIpAddress) & SFIB_LEN2Mask(ulMaskLen))
#define SFIB_LEN2Mask(ulMaskLen)              ((0 == ulMaskLen) ? 0 : SFIB_NULL_ULONG << (32-(ulMaskLen)))


#endif /* ifndef _FIB6A_PUB_DEFS_H   */

#ifdef  __cplusplus
}
#endif

