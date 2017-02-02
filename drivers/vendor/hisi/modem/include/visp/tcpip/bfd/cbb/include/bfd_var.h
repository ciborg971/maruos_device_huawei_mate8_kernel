
/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_var.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD
*  Date Created: 2006-12-01
*        Author: Wangchengyang
*   Description: BFD��Ҫ�õ���ȫ�ֱ�������ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-01      Wangchengyang       Create
*
*******************************************************************************/
#ifndef _BFD_VAR_H_
#define _BFD_VAR_H_

#ifdef __cplusplus
extern "C" {
#endif

extern BFD_PPI_HOOK_FUNC        g_pfBfdPpiHook;
extern BFD_HA_CAN_SEND_PACKET   g_pfHaCanSendPacket;
extern BFD_HA_SEND_LIVE_PACKET  g_pfHaSendLivePacket;
extern BFD_HA_GET_DBG_SWITCH    g_pfHaGetDbgSwitch;
extern BFD_HA_CANNOT_CFG        g_pfHaCannotCfg;
extern BFD_HA_DBG_OUTPUT        g_pfBfdHaDbgOutput;
extern BFD_STATE_NOTIFYVRRP     g_pfBfdStateNotifyVRRP;
extern BFD_STATE_NOTIFYEXT     g_pfBfdStateNotifyExt;
/*End of Modified by qinyun62011, 2010/9/29 */


extern ULONG g_ulBfdNpMode;

extern const CHAR g_szBfdVersion[30];

extern CHAR *g_pcBfdCompileTime;


/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
extern ULONG *g_ulBfdGlobalDebugSwitch;
/* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */

extern ULONG g_ulBfdGlobalCapability;
/* wangjiaqi modify for ipv6 bfd 20131119 begin */
extern ULONG g_ulBfd6GlobalCapability;
/* wangjiaqi modify for ipv6 bfd end */

extern ULONG g_ulBfdTaskId;

extern ULONG g_ulBfdOtherQueId;

/*Begin BC3D02903 liangjicheng 2010-04-19 */
extern ULONG g_ulBfdExtQueId;
extern ULONG g_ulBfdExtMsgCount;
extern VOID (* g_pfBfdOSPFRuleUpdateFunc)(BFD_EXT_OSPF_RULE_MSG *pstOSPFRuleMsg);
/*End   BC3D02903 liangjicheng 2010-04-19 */

extern ULONG g_ulBfd6ExtMsgCount;

extern ULONG g_ulBfdNsrQueId;

extern ULONG g_ulBfdTimerQueId;

extern ULONG g_ulBfdLicenseTimerQueId;
/* wangjiaqi modify for ipv6 bfd 20131121 begin */
extern ULONG g_ulBfd6LicenseTimerQueId;
/* wangjiaqi modify for ipv6 bfd end */

extern ULONG g_ulBfdLicenseTimerInterval;

extern ULONG g_ulBfdWtrTimeInterval;
/* wangjiaqi modify for ipv6 bfd 20131119 begin */
extern ULONG g_ulBfd6WtrTimeInterval;
/* wangjiaqi modify for ipv6 bfd end */

extern ULONG g_ulBfdInitFlag;

extern ULONG g_ulBfdAdaptMultiHopPort;
/* wangjiaqi modify for ipv6 bfd 20131119 begin */
extern ULONG g_ulBfd6AdaptMultiHopPort;
/* wangjiaqi modify for ipv6 bfd end */

extern ULONG g_ulBfdBakDbg;

extern  BFD_NOTIFY_HOOK_S *g_pfBfdNotifyHookFunc;

/* RPU������: BFD״̬��Ǩ����ͨ�� */
extern BFD_STATECHG_NOTIFY_HOOK_FUNC g_pfBfdStateChgNotifyHookFunc;

/*Added by wangchengyang-xujun62830-57575 for VISPV1R8C01, 2009/4/20 */
extern BFD6_NOTIFY_HOOK_S *g_pfBfd6NotifyHookFunc;

extern ULONG g_ulBfdFirsNegoTimes;

extern BFD6_PPI_HOOK_FUNC        g_pfBfd6PpiHook;
/* End of Added by wangchengyang-xujun62830-57575, 2009/4/20 */

/* add for show info */
extern CHAR *g_aszSessionState[]; 

/* add for show info */
extern CHAR *g_aszDetectMode[];

/*Added by xujun57575 for sgsn Requirement  BC3D02728, 2010/2/25 */
/* Э��ʧ��̽��ʱ�� ms */
extern ULONG g_ulBfdNotifyTime;
/*�Ƿ�ʹ��Э��ʧ��̽��ʱ�� 0 ��ʹ�� 1 ʹ��*/
extern ULONG g_ulBfdNotifyTimeFlag;
/* End of Added by xujun57575, 2010/2/25 */


/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
/* BFD�Ựȫ�ֱ���� */
extern AVL3_TREE_INFO_S g_BfdTreeInfo;
extern BFD_TREE_SET_S  *g_pstBfdTreeSet;

extern ULONG g_ulBfdVrfSize;
extern ULONG g_ulSGSNPPIBFDDownMode;
extern BFD_NOTIFY_BYVRF_HOOK_S *g_pfBfdNotifyByVrfHookFunc;
/* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */

/* BFD License ���Ӻ������� */
extern BFD_GET_LICENSE_STATE_FUNC g_pfBfdLicenseHook;
/* wangjiaqi modify for ipv6 bfd 20131121 begin */
extern BFD_GET_LICENSE_STATE_FUNC g_pfBfd6LicenseHook;
/* wangjiaqi modify for ipv6 bfd end */

/*���BFD PPI�·��ɲ�������ر������궨��,add by wuhailan,2008-04-11.*/
typedef struct tagBFD_CPUTICK
{
    ULONG  ulLowTick;   
    ULONG  ulHighTick; 
}BFD_CPUTICK_S;

#define BFD_PPI_COUNT 5  /*�·�����*/
typedef struct tagBFD_PPI_TIME
{
    BFD_CPUTICK_S stStartTime[BFD_PPI_COUNT];/*�·���¼�Ŀ�ʼʱ��*/
    BFD_CPUTICK_S stEndTime[BFD_PPI_COUNT];  /*�·���¼�Ľ���ʱ��*/
    ULONG         ulOprType[BFD_PPI_COUNT];  /*�·��Ĳ�������*/
    ULONG         ulBFDPpiCount;             /*�·�����*/
}BFD_PPI_TIME_S;

extern ULONG g_ulCurrentBFDGRState; 
extern ULONG g_ulBFDPpiTimeSwitch;   /*BFD�·���ʱ���㿪��*/
extern BFD_PPI_TIME_S g_ulBFDPpiTime;/*BFD�·���ʱͳ�ƴ������*/

/*BFD�·���ǰ��ʱ���*/
#define MAKE_BFDPPI_STARTDOT(OprType)\
{\
    if (g_ulBFDPpiTimeSwitch)\
    {\
        ULONG ii = g_ulBFDPpiTime.ulBFDPpiCount;\
        ii %= BFD_PPI_COUNT;\
        VOS_GetCpuTick( &(g_ulBFDPpiTime.stStartTime[ii].ulLowTick),  \
                        &(g_ulBFDPpiTime.stStartTime[ii].ulHighTick) );\
        g_ulBFDPpiTime.ulOprType[ii] = OprType;\
    }\
}
/*BFD�·��ķ��غ�ʱ����*/
#define MAKE_BFDPPI_ENDDOT()\
{\
    if (g_ulBFDPpiTimeSwitch)\
    {\
        ULONG ii = g_ulBFDPpiTime.ulBFDPpiCount;\
        ii %= BFD_PPI_COUNT;\
        VOS_GetCpuTick( &(g_ulBFDPpiTime.stEndTime[ii].ulLowTick),  \
                        &(g_ulBFDPpiTime.stEndTime[ii].ulHighTick) );\
        g_ulBFDPpiTime.ulBFDPpiCount++;\
    }\
}

extern UCHAR g_ucMultiHopTtl;
extern ULONG g_ulBFDTotalSession;

extern ULONG g_ulBFDMaxSessionNum;

extern ULONG g_ulBfdPReTranMode; /*Added by luogaowei  PF ��ǿ�����أ� Ĭ�Ϲر�*/
extern ULONG g_ulBfdPFProcPeriod; /*Added by luogaowei  PF ��ǿ���� ��ʱ������ */
extern ULONG g_ulBfdPFProcMaxNum; /*Added by luogaowei  PF ��ǿ���� ��ʱ������*/

extern ULONG g_ulBfdPFTimerId[BFD_PF_TIMER_NUM];   /*BFD PF ����ʱ�����������������޸ģ��޸ĺ� ��Ҫ���¼���BFD ��ʱ������ֵ*/

extern ULONG *g_pulBfdPFSessionInfo;  /*��16λ����vrf ��������16λ����BFD �Ựid*/

extern ULONG g_ulGateValue;

extern BFD_PPI_HOOK_FUNC        g_pfNsrBfdPpiDownloadHook ;
extern BFD6_PPI_HOOK_FUNC       g_pfNsrBfd6PpiDownloadHook;

extern struct IIF_COMP_NSR_ComIntFUNVtbl *g_pstNsrBfdFunTable;

/* �յ��Զ˵�F ��Ǳ��ģ��������P��� ���·�NP������ƿ��أ�Ĭ��0 -����*/
extern ULONG g_ulBfdPollClearSwitch;

/* �Ƿ���ʾBFD�˿ڵĿ��أ� VRP_NO ����ʾ��VRP_YES - ��ʾ */
extern ULONG g_ulBfdPortShowSwitch;

/* BFDЭ��˳���Կ���,Ϊ������չ�Կ��ǣ�ÿһbit����һ��Э��һ�������� */
extern ULONG g_ulBfdComplianceSwitch;

#ifdef __cplusplus
}
#endif

#endif

