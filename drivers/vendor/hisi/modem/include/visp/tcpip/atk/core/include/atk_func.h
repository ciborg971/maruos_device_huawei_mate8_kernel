/*******************************************************************************
*
*
*                Copyright 2014, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              atk_func.h
*
*  Project Code: VISPV3R2
*   Module Name: ATK Module  
*  Date Created: 2014-08-07
*        Author: a00900892
*   Description: ATK functionality related functions.
*                module VISP
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2014-08-07  a00900892            Create
*
*******************************************************************************/
#ifdef  __cplusplus
extern  "C"{
#endif
#ifndef _I_ATK_FUNC_H_
#define _I_ATK_FUNC_H_

/*******************************************************************************
*    Func Name: ATK_Sock_TimeCallBack
* Date Created: 2014-08-03
*       Author: a00900892
*  Description: Timer callback function, Need to check if number of malformed
*               packet exceeded max threshold or receed min threshold and
*               raise or cancel warning 
*        Input: VOID *pArg: Input parameter not used.
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                        DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2002-11-25  Sun Yanfeng(32084)         Creat the first version.
*
*******************************************************************************/
VOID ATK_Sock_TimeCallBack(VOID *pArg);


ULONG ATK_AddAtkStat(ULONG ulIfIndex, ULONG ulAttackType, IP_S *pstIp);

/*******************************************************************************
*    Func Name: ATK_AddIcmpJumbogramStat
* Date Created: 2014-08-06
*       Author: a00900892
*  Description: Check if the incoming icmp packet length is larger than the
*               configured maximum size. If size is lesser, return success.
*               Else increment Attack count of type ATK_STAT_TYPE_ICMP_LARGE.
*        Input: ulIfIndex: If index of the incoming interface.
*               ulLen: Length of the incoming IP packet(ICMP).
*               pstIp£ºPointer to the IP header of the incoming packet.
*       Output: 
*       Return: VOS_OK:  If packet should not be dropped.
*               VOS_ERR: If packet should be dropped.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-06   a00900892               Create
*
*******************************************************************************/
ULONG ATK_AddIcmpJumbogramStat(ULONG ulIfIndex, ULONG ulLen, IP_S *pstIp);

/*******************************************************************************
*    Func Name: ATK_DelAllStats
* Date Created: 2014-08-03
*       Author: a00900892
*  Description: Free all oafish pkt attacks global statistics.
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
ULONG ATK_DelAllStats();


VOID ATK_IfDelete_Notify(ULONG ulIfIndex);


ULONG ATK_AddAtkStat_PT(ULONG ulIfIndex, ULONG ulAttackType, IP_S *pstIp);


ULONG ATK_AddIcmpJumbogramStat_PT(ULONG ulIfIndex, ULONG ulLen, IP_S *pstIp);


VOID ATK_IfDelete_Notify_PT(ULONG ulIfIndex);


ULONG ATK_IsSwitchOpen();


#endif  /* I_ATK_FUNC_H_ */
#ifdef  __cplusplus
}
#endif


