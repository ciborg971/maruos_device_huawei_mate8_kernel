/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_dd.h
*
*  Project Code: VISPV100R006
*   Module Name: BFDȱ��̽��ģ��
*  Date Created: 2006-12-21
*        Author: wujie(61195)
*   Description: BFDȱ��̽��ģ��ͷ�ļ�����Ҫ�Ǻ�������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-21  wujie(61195)         Creat the first version.
*
*******************************************************************************/

#ifndef _BFD_DD_H_
#define _BFD_DD_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
ULONG BFD_DD_EnCodeBySessEntry(BFD_SESS_ENTRY_S *pstSessEntry, BFD_CONTROL_PACKET_S *pstCtlPkt);
ULONG BFD_DD_DeCode(BFD_CONTROL_PACKET_S* pstCtlPkt);
ULONG BFD_DD_BuildPkt(BFD_SESS_ENTRY_S *pstSessEntry);
ULONG BFD_DD_SndPkt(BFD_SESS_ENTRY_S *pstSessEntry, BOOL_T bReplyToP);
ULONG BFD_DD_ProcPkt( BFD_SESS_ENTRY_S *pstSessEntry, BFD_PACKET_S *pstPkt);
ULONG BFD_DD_CheckValid(BFD_CONTROL_PACKET_S *pstBfdCtrlPkt, ULONG ulPktLenth,ULONG ulVrfIndex);
/*Modified by wangchengyang-xujun62830-57575 for VISPV1R8C01, 2009/4/15 */
ULONG BFD_DD_ProcZeroDiscr(BFD_CONTROL_PACKET_S * pstBfdCtrlPkt, ULONG * pulDstIP, ULONG * pulSrcIP, ULONG InIfIndex, ULONG ulVrfIndex, ULONG ulIpVer);
/*End of Modified by wangchengyang-xujun62830-57575, 2009/4/15 */
ULONG BFD_DD_GetCtlPktBySessEntry(BFD_SESS_ENTRY_S *pstSessEntry, BFD_CONTROL_PACKET_S *pstCtlPkt);
ULONG BFD_StartTxTimer(ULONG ulSessID,ULONG ulVrfIndex);
ULONG BFD_RefreshTxTimer(ULONG ulSessID,ULONG ulVrfIndex);
ULONG BFD_DelTxTimer(ULONG ulSessID,ULONG ulVrfIndex);
ULONG BFD_DelNotifyTimer(ULONG ulSessID,ULONG ulVrfIndex);
ULONG BFD_StartDetectTimer(ULONG ulSessID,ULONG ulVrfIndex);
ULONG BFD_RefreshDetectTimer(ULONG ulSessID,ULONG ulVrfIndex);
ULONG BFD_DelDetectTimer(ULONG ulSessID,ULONG ulVrfIndex);
ULONG BFD_StartInitTimer(ULONG ulSessID,ULONG ulVrfIndex);
ULONG BFD_RefreshInitTimer(ULONG ulSessID, ULONG ulVrfIndex);
ULONG BFD_DelInitTimer(ULONG ulSessID,ULONG ulVrfIndex);
VOID  BFD_DD_ProcTxTimerOut(ULONG ulVrfBfdIndex, ULONG ulTimerID);
VOID  BFD_DD_ProcDetectTimerOut(ULONG ulVrfBfdIndex, ULONG ulTimerID);
ULONG BFD_StartWTRTimer(ULONG ulSessID,ULONG ulVrfIndex);
ULONG BFD_DelWTRTimer(ULONG ulSessID,ULONG ulVrfIndex);
VOID  BFD_DD_ProcWTRTimerOut(ULONG ulVrfBfdIndex, ULONG ulTimerID);
VOID  BFD_DD_ProcInitTimerOut(ULONG ulVrfBfdIndex, ULONG ulTimerID);
VOID  BFD_PrintPKT(BFD_CONTROL_PACKET_S *pstBfdCtrlPkt, ULONG *pulDstIP, ULONG *pulSrcIP, ULONG ulInIfIndex, ULONG ulVrfIndex,ULONG ulFlag,ULONG ulIpVer);
/* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */
extern CHAR* VOS_IpAddrToStr(ULONG ulAddr, CHAR * szStr);
extern ULONG VOS_Tm_Now(ULONG *pulRetTimeInMillSecHigh, ULONG *pulRetTimeInMillSecLow);

ULONG BFD_StartLicenseTimer();
ULONG BFD_DelLicenseTimer();
VOID  BFD_DD_ProcLicenseTimerOut();
ULONG BFD_License_SendMsg(ULONG ulLicenseMsgType);
VOID BFD_StartNotifyTimer(ULONG ulSessID,ULONG ulVrfIndex);
/* wangjiaqi modify for ipv6 bfd 20131119 begin */
/*******************************************************************************
*    Func Name: BFD_SetPktStatic
* Date Created: 2013-11-19
*       Author: wangjiaqi
*  Description: ͳ��bfd�����շ���Ϣ
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-19   wangjiaqi        Create the first version
*******************************************************************************/
VOID BFD_SetPktStatic(BFD_PACKET_S *pstPkt, BFD_SESS_ENTRY_S *pstSessEntry, ULONG ulAction);
/* wangjiaqi modify for ipv6 bfd end */

/* wangjiaqi modify for ipv6 bfd 20131121 begin */
/*******************************************************************************
*    Func Name: BFD6_DelLicenseTimer
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description: ɾ��License��ʱ��
*        Input:
*       Output: 
*       Return: BFD_OK
*               BFD_ERR
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-21  wangjiaqi        Creat the first version 
*******************************************************************************/
ULONG BFD6_DelLicenseTimer();
/*******************************************************************************
*    Func Name: BFD6_StartLicenseTimer
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description: ����License��ʱ��
*        Input: 
*       Output: 
*       Return: BFD_OK
*               BFD_ERR_CREATE_TIMER
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-21  wangjiaqi        Creat the first version 
*******************************************************************************/
ULONG BFD6_StartLicenseTimer();
/*******************************************************************************
*    Func Name: BFD6_DD_ProcLicenseTimerOut
* Date Created: 2013-11-21
*       Author: wangjiaqi
*  Description: License��ʱ����ʱ����
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-21  wangjiaqi        Creat the first version.
*******************************************************************************/
VOID BFD6_DD_ProcLicenseTimerOut();
/* wangjiaqi modify for ipv6 bfd end */
/*******************************************************************************
*    Func Name: BFD6_DD_BuildPkt
* Date Created: 2009-04-15
*       Author: wangchengyang xujun 
*  Description: �������»Ự�����BFD6���Ʊ���
*        Input: BFD_SESS_ENTRY_S *pstSessEntry: BFD�Ự���ƿ�
*       Output: 
*       Return: BFD_OK
*               BFD_ERR_MEM_ALLOC
*               BFD_ERR_BUILD_PKT
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-4-15  wangchengyang-xujun62830-57575         VISPV1R8C01.
*******************************************************************************/
ULONG BFD6_DD_BuildPkt(BFD_SESS_ENTRY_S *pstSessEntry);

#ifdef __cplusplus
}
#endif

#endif

