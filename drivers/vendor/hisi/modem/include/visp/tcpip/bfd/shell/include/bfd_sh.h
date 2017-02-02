/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_sh.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD SHELL
*  Date Created: 2006-12-04
*        Author: Wangchengyang
*   Description: BFD Shell ���������Լ��궨��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-12-04   Wangchengyang    Create
*
*******************************************************************************/
#ifndef _BFD_SH_H_
#define _BFD_SH_H_

#ifdef __cplusplus
extern "C" {
#endif

/* �ڴ�����ʱʹ�õ�ģ��� */
/* MID_COMP_BFD = 0x0E240000 , defined in file tcpip_id.h */
#define  BFD_MID MID_COMP_BFD

#define  BFD_VRF_MID 0x00000001

/* ����MBUFʱԤ������·���ײ����� */
#define  BFD_MBUF_LINKHDR   40

/* ���ݹ�������������VRF�н��в��� */
#define BFD_SEARCH_IN_VRF_BY_FILTER     0
#define BFD_SEARCH_IN_ALLVRF_NO_FILTER  1
#define BFD_SEARCH_IN_ALLVRF_BY_FILTER  2

#define BFD_VRF_CALLBACK_DELETE 0x02

VOID BFD_Begin_PT();

VOID BFD_End_PT();

ULONG BFD_Shell_Init(ULONG ulNpMode);

ULONG BFD_Shell_SessionCreate(ULONG ulDstIP, ULONG ulSrcIP, ULONG ulOutIfIndex, ULONG* pulSessionID);

extern ULONG BFD_Shell_SessionCreateByVrf(ULONG ulDstIP, ULONG ulSrcIP, ULONG ulOutIfIndex,
                                   ULONG *pulSessionID, ULONG ulVrfIndex);

ULONG BFD_Shell_CreateCheck (ULONG ulDstIP, ULONG ulSrcIP, ULONG ulOutIfIndex,ULONG ulVrfIndex,ULONG ulBfdProtocol);

ULONG BFD_Shell_Send (UCHAR* pIpPacket, ULONG ulOutIfIndex, ULONG ulPacketLength,ULONG ulVrfIndex);

ULONG BFD_Shell_Recv(MBUF_S* pMbuf);

ULONG BFD_VRF_DelCallback( ULONG ulEvents , VOID * pulVrfIndex);
/* wangjiaqi modify for ipv6 bfd 20131121 begin */
ULONG BFD_VRF6_DelCallback( ULONG ulEvents , VOID * pulVrfIndex);
    /* wangjiaqi modify for ipv6 bfd end */

VOID BFD_DebugOutput(CHAR *pszMsg);

VOID BFD_Info_Output(CHAR *pszMsg);

VOID BFD_WarningOutput(ULONG ulWarningID, VOID* pWarnParam);

extern ULONG g_ulHABfdExist;

extern ULONG (*g_pfUDP4_BFD_HOOK)(MBUF_S*);
extern ULONG (*g_pfIpChangeNotifyBfd)(ULONG, ULONG, ULONG);

extern ULONG (*g_pfIsBfdFinishInit)(VOID);

/* Added by likaikun00213099 for port security at 20140806, �ж��Ƿ���Ҫ������ʾBFD�ỰĿ�Ķ˿� */
extern ULONG (*g_pfGetBfdShowPortSwitch)(VOID);

extern SOCK_MOD_INFO_S g_stSOCK4ModInfo;

extern ULONG BFD_IF_IsTrunkPort (ULONG ulIfInde);

/* extern ULONG BFD_RegFuncBFDTimeTestHook(ULONG ulType, pfFuncBFDTimeTestHook pfHook); */

extern VOID BFD_Shell_NotifyAppSessionState(ULONG ulNotifyType, ULONG ulSessionID, ULONG ulVrfIndex,
                    ULONG ulState, ULONG ulDstIP, ULONG ulSrcIP, ULONG ulInIfIndex, ULONG ulAppGroup);
extern ULONG BFD_CheckVrfVtblIsRegister();
extern ULONG BFD_GetVrfIndexByIfIndex(ULONG ulIfIndex,ULONG *pulVrfIndex);

/*Added by wangchengyang-xujun62830-57575 for ����vc �����澯, 2009/4/14 */
ULONG BFD_GetVrfNameByIndex(CHAR * pszVrfName, ULONG ulVrfIndex);
ULONG BFD_GetVrfIndexByName(CHAR * pszVrfName, ULONG * pulVrfIndex);
/* End of Added by wangchengyang-xujun62830-57575, 2009/4/14 */

extern VOID BFD_Shell_GRNotify(ULONG ulOperation);
extern ULONG BFD_GetTypeNumByIndex(ULONG ulIfIndex, ULONG *pulIfType, ULONG *pulIfNum);
extern ULONG BFD_VrfDelSuccessNotify(ULONG ulModId, ULONG ulVrfIndex);
/* wangjiaqi modify for ipv6 bfd 20131121 begin */
extern ULONG BFD6_VrfDelSuccessNotify(ULONG ulModId, ULONG ulVrfIndex);
/* wangjiaqi modify for ipv6 bfd end */
extern ULONG BFD_Shell_GetBfdMaxSessionID(VOID);

extern ULONG BFD_Shell_IsFinishInit(VOID);
extern ULONG BFD_CheckBasicCapability(ULONG ulIpVer);
extern ULONG BFD_GetBfdShowPortSwitch(VOID);
ULONG BFD_CheckIFValid(ULONG ulIfIndex);
ULONG BFD_GetTrunkIfIndex(ULONG ulIfIndex, ULONG *pulTrunkIfIndex);


#ifdef __cplusplus
}
#endif

#endif


