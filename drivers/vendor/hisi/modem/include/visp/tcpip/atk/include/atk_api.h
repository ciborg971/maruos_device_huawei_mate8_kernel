/*******************************************************************************
*
*
*                Copyright 2014, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              atk_api.h
*
*  Project Code: VISPV3R2
*   Module Name: ATK Module  
*  Date Created: 2014-08-07
*        Author: a00900892
*   Description: ATK API exposed to user.
*                module VISP
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2014-08-07  a00900892            Create
*
*******************************************************************************/
#ifndef _ATK_API_H_
#define _ATK_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define ATTACK_WARNING_BEGIN    1               /*¡¡oafish  pkt attack alarms start */ 
#define ATTACK_WARNING_END      0               /*¡¡oafish  pkt attack alarms end */ 

#define ATTACK_SWITCH_SET       1               /* Switch is set */
#define ATTACK_SWITCH_RESET     0               /* Switch is not set */

#define ATTACK_WARNING_MAX_THRESHOLD    100     /* Malformed packet warning maximum threshold */
#define ATTACK_WARNING_MIN_THRESHOLD    10      /* Malformed packet warning minimum threshold */

#define ATTACK_LARGE_ICMP_MIN_LEN       10000   /* Minimum value for maximum acceptable icmp packet length */
#define ATTACK_LARGE_ICMP_MAX_LEN       65535   /* Maximum value for maximum acceptable icmp packet length */

#define ATTACK_MALFORMED_PKT_TIME       60      /* Duration of malformed packet timer in seconds */

#define ATTACK_HASH_LEN                 64      /* length of the hash to be generated from IfIndex */
#define ATTACK_HASH_CONST               128     /* Length used for hash calculation based on ifindex */

#define ATTACK_STAT_CLEAR       1               /* Statistics should to cleared(All zero). */
#define ATTACK_STAT_FREE        0               /* Statistics should be free. */

/* Hash algorithm for converting Ifindex to hash length. */
#define HASH_FUN(ulIfIndex) (((ulIfIndex / ATTACK_HASH_CONST) \
                            + (ulIfIndex % ATTACK_HASH_CONST)) \
                            % ATTACK_HASH_LEN)

/* SID for ATK module */
#define SID_COMP_ATK_HASH_TABLE_S         1     /* Global hash table */
#define SID_COMP_ATK_LIST_ENTRY_S         1     /* Entry in the hash list of has table */

/* Enum to define diffrernet types of attack */
typedef enum tagAtkStatType
{
    ATK_STAT_TYPE_HEAD_ERR = 0,     /* IP header error */
    ATK_STAT_TYPE_INVALID_IPOPT,    /* IP Options error */
    ATK_STAT_TYPE_UNKOWNPRRO,       /* Unknown protocol packets */
    ATK_STAT_TYPE_SPOOF,            /* IP spoofing the source address broadcast packets */
    ATK_STAT_TYPE_REASS_TIMEOUT,    /* Reassembly timeout */
    ATK_STAT_TYPE_REASS_ERR,        /* Reassembly error */
    ATK_STAT_TYPE_INVALID_TCP,      /* Marked invalid TCP packet */
    ATK_STAT_TYPE_LAND,             /* LAND attack packets */
    ATK_STAT_TYPE_WINNUKE,          /* IGMP fragment packets */
    ATK_STAT_TYPE_ICMP_LARGE,       /* Long ICMP packet */
    ATK_STAT_TYPE_TYPE_MAX
}ENUM_ATKSTATTYPE;

/* Enum to define error codes */
typedef enum tagAtkErrorType
{
    ATK_RET_OK = 0,
    ATK_RET_INVALID_SWITCH,         /* 1. Invalid switch value (not 0 or 1) */
    ATK_RET_INVALID_THRESHOLD,      /* 2. Invalid threshold, (max < min) */
    ATK_RET_ICMP_MAX_LEN,           /* 3. Invalid icmp length (not between 10000 to 65535) */
    ATK_RET_INPUT_NULL,             /* 4. Pointer input is null */
    ATK_RET_INVALID_IF,             /* 5. Interface not present */
    ATK_RET_MALLOC_FAIL,            /* 6. Memory allocation fail */
    ATK_RET_SWITCH_NOT_SET,         /* 7. statistics switch is not set */
    ATK_RET_NO_ATTACK_STAT,         /* 8. no attack stat entry present */
    ATK_RET_START_TIMER_FAIL,       /* 9. start timer fail */
    ATK_RET_STOP_TIMER_FAIL,        /* 10. stop timer fail */
    ATK_RET_MODULE_NOT_INIT,        /* 11. module not initialized */
    ATK_RET_MAX,

    ATK_RET_END = 0xFFFFFFFF,
}ENUM_ATK_ERROR_TYPE;

/* Malformed packet attacks that reached the threshold of alarm structure */
typedef struct tagATTACKWarning
{
    ULONG ulWarningType;        /* Alarm type: ATTACK_WARNING_BEGIN or ATTACK_WARNING_END */
    ULONG ulAtkCounts;          /* The total number of attacks in the cycle */
    ULONG ulWarnAtkType;        /* The types of attacks that reached the threshold (ENUM_ATKSTATTYPE)*/
    ULONG ulWarnIfIndex;        /* The IfIndex of the incoming interface of attacks that reached the threshold */
    IP_S stWarnIpHead;          /* The IP header of attacks packet that reached the threshold */
}ATTACK_WARNING_S;

/* Structure used to output module configurations. */
typedef struct tagATTACKCfg
{
    ULONG ulAtkSwitch;              /* Attack function switch */
    ULONG ulAtkWarnMaxThreshold;    /* Warning maximum threshold */
    ULONG ulAtkWarnMinThreshold;    /* Alarm lifted the minimum threshold */
    ULONG ulLargeIcmpMaxSize;       /* LargeIcmp maximum packet */
}ATTACK_CFG_INFO_S;

/* Structure used to store different types of IP attack statistics. */
typedef struct tagAttackStats
{
    ULONG  ulHeadErrorStat;         /* IP header error */
    ULONG  ulIpOptErrStat;          /* IP Options error */
    ULONG  ulunkownProStat;         /* Unknown protocol packets */
    ULONG  ulIpSpoofStat;           /* IP spoofing the source address broadcast packets */
    ULONG  ulIpReassTimeOutStat;    /* Reassembly timeout */
    ULONG  ulIpReassErrStat;        /* Reassembly timeout */
    ULONG  ulTcpErrorStat;          /* Marked invalid TCP packet */
    ULONG  ulLandAtkStat;           /* LAND attack packets */
    ULONG  ulWinnukeStat;           /* IGMP fragment packets */
    ULONG  ulIcmpLargeStat;         /* Long ICMP packet */
}TCPIP_ATTACKSTAT_S;    /* Attack packets statistics structure */

/* Structure used to store the statistics for an interface. */
typedef struct tagAttackStatsByIf
{
    ULONG ulIfIndex;                    /* If index of the incoming interface */
    TCPIP_ATTACKSTAT_S stAttackStats;   /* IP attack statistics */
    struct tagAttackStatsByIf *pst_NextStat;   /* Next element in the hash list */
}ATTACKSTAT_BY_IF_S;

typedef struct tagAtkComModuleInfo
{
    ULONG  ulModID;
    ULONG ulSubModID;    
}ATK_MOD_INFO_S;

/*******************************************************************************
*    Func Name: TCPIP_SetAtkWarningSwitch
* Date Created: 2014-08-03
*       Author: a00900892
*  Description: Set attack statistics and alarm threshold switch 
*        Input: ulSwitch: Switch for statistics and alarm,
*                         1 for start, 0 for close.
*               ulMaxThreshold: Attack statistical maximum threshold,
*                               Above this an alarm is reported maximum.
*               ulMinThreshold: Attack statistics minimum threshold,
*                               below the this, reported alarm is eliminated.
*       Output: 
*       Return: VOS_OK: success 
*               Other failed error code 
*      Caution: If you have reported an alarm, and then turn off this feature,
*               they have to report the alarm eliminated.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-03   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_SetAtkWarningSwitch(ULONG ulSwitch, ULONG ulMaxThreshold, ULONG ulMinThreshold);


ULONG TCPIP_SetAtkLargeIcmpLen(ULONG ulMaxSize);

/*******************************************************************************
*    Func Name: TCPIP_GetAtkCfgInfo
* Date Created: 2014-08-03
*       Author: a00900892
*  Description: Get attack statistics configuration information.
*        Input: 
*       Output: pstAtkCfgInfo: Pointer to ATTACK_CFG_INFO_S.
*       Return: VOS_OK: success 
*               Other failed error code.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-03   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_GetAtkCfgInfo(ATTACK_CFG_INFO_S *pstAtkCfgInfo);

/*******************************************************************************
*    Func Name: TCPIP_GetAtkStats
* Date Created: 2014-08-03
*       Author: a00900892
*  Description: Get oafish pkt attacks global statistics.
*        Input: 
*       Output: pstAtkStat: query statistics.
*       Return: VOS_OK: success 
*               Other failed error code.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-03   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_GetAtkStats(TCPIP_ATTACKSTAT_S *pstAtkStat);

/*******************************************************************************
*    Func Name: TCPIP_GetAtkStatsByIf
* Date Created: 2014-08-03
*       Author: a00900892
*  Description: Get oafish pkt attacks statistics for an interface.
*        Input: ulIfIndex: IF Index of the interface
*       Output: pstAtkStat: query statistics.
*       Return: VOS_OK: success 
*               Other failed error code.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-03   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_GetAtkStatsByIf(ULONG ulIfIndex, TCPIP_ATTACKSTAT_S *pstAtkStat);

/*******************************************************************************
*    Func Name: TCPIP_ClrAtkStatsByIf
* Date Created: 2014-08-03
*       Author: a00900892
*  Description: Clear oafish pkt attacks statistics for an interface.
*        Input: ulIfIndex: IF Index of the interface
*       Output: 
*       Return: VOS_OK: success 
*               Other failed error code.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-03   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_ClrAtkStatsByIf(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ClrAtkStats
* Date Created: 2014-08-03
*       Author: a00900892
*  Description: Clear oafish pkt attacks global statistics.
*        Input: 
*       Output: 
*       Return: VOS_OK: success 
*               Other failed error code.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-03   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_ClrAtkStats();

/*******************************************************************************
*    Func Name: TCPIP_ShowAtkInfo
* Date Created: 2014-08-03
*       Author: a00900892
*  Description: Clear oafish pkt attacks global statistics.
*        Input: 
*       Output: 
*       Return: VOS_OK: success 
*               Other failed error code.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-03   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_ShowAtkInfo();

/*******************************************************************************
*    Func Name: TCPIP_ShowAtkStatsByIntfName
* Date Created: 2014-08-03
*       Author: a00900892
*  Description: Show oafish pkt attacks statistics for an interface name.
*        Input: szIfName: Interface name
*       Output: 
*       Return: VOS_OK: success 
*               Other failed error code.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-03   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_ShowAtkStatsByIntfName(CHAR *szIfName);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _ATK_API_H_ */

