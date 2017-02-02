/*******************************************************************************
*
*
*                Copyright 2014, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              atk_cfg.h
*
*  Project Code: VISPV3R2
*   Module Name: ATK Module  
*  Date Created: 2014-08-07
*        Author: a00900892
*   Description: ATK configuration API exposed through Vtable.
*                module VISP
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2014-08-07  a00900892            Create
*
*******************************************************************************/

#ifndef _ATK_CFG_H_
#define _ATK_CFG_H_

/*In case of the C++.*/
#ifdef  __cplusplus
extern "C" {
#endif

/*******************************************************************************
*    Func Name: ATK_SetWarningSwitch
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
ULONG ATK_SetWarningSwitch(ULONG ulSwitch, ULONG ulMaxThreshold, ULONG ulMinThreshold);

/*******************************************************************************
*    Func Name: ATK_SetLargeIcmpLen
* Date Created: 2014-08-03
*       Author: a00900892
*  Description: Set the maximum acceptable packet length for Icmp,
*               If packet length is greater, attack statistics are included
*               and packet is discarded.
*        Input: ulMaxSize: LargeIcmp maximum length 
*       Output: 
*       Return: VOS_OK: success 
*               Other failed error code
*      Caution: 
*      Remarks: Range of 10000-65535 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-03   a00900892               Create
*
*******************************************************************************/
ULONG ATK_SetLargeIcmpLen(ULONG ulMaxSize);

/*******************************************************************************
*    Func Name: ATK_GetCfgInfo
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
ULONG ATK_GetCfgInfo(ATTACK_CFG_INFO_S *pstAtkCfgInfo);

/*******************************************************************************
*    Func Name: ATK_GetStats
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
ULONG ATK_GetStats(TCPIP_ATTACKSTAT_S *pstAtkStat);


/*******************************************************************************
*    Func Name: ATK_GetStatsByIf
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
ULONG ATK_GetStatsByIf(ULONG ulIfIndex, TCPIP_ATTACKSTAT_S *pstAtkStat);

/*******************************************************************************
*    Func Name: ATK_ClrStatsByIf
* Date Created: 2014-08-03
*       Author: a00900892
*  Description: Clear oafish pkt attacks statistics for an interface.
*        Input: ulIfIndex: IF Index of the interface
*               ulOper : Operation type. 
*                           ATTACK_STAT_CLEAR   - reset statistics
*                           ATTACK_STAT_FREE    - Delete and free statistics
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
ULONG ATK_ClrStatsByIf(ULONG ulIfIndex, ULONG ulOper);

/*******************************************************************************
*    Func Name: ATK_ClrStats
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
ULONG ATK_ClrStats();

/*******************************************************************************
*    Func Name: ATK_ShowStats
* Date Created: 2014-12-22
*       Author: a00900892
*  Description: Show oafish pkt attacks statistics.
*        Input: pstAtkStat: Statistics to output.
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-22   a00900892               Create
*
*******************************************************************************/
VOID ATK_ShowStats(const TCPIP_ATTACKSTAT_S *pstAtkStat);

/*In case of the C++.*/
#ifdef  __cplusplus
}
#endif


#endif  /* ATK_CFG_H_ */

