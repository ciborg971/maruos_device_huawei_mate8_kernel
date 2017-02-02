
#ifndef __DHCPC_COMP_H__
#define __DHCPC_COMP_H__

extern PTM_COMPONENT_INFO_S g_stDhcpcComInfo;
#define DHCPC_SELF_CSI             g_stDhcpcComInfo.ullSelfCsi
#define DHCPC_SELF_SGID            g_stDhcpcComInfo.ullSelfSgId
#define DHCPC_SELF_CMPIDX          g_stDhcpcComInfo.ulSelfCmpIdx
#define DHCPC_SELF_CMPIDX_INSG     g_stDhcpcComInfo.ulSelfCmpIdxInSG

#define DHCPC_HANDLE         g_stDhcpcComInfo.ulHandle

/* ��ʱ׮, ����ʹ�����������滻 */
#define DHCPC_GLAP2_CSI       g_stDhcpcComInfo.ullSelfCsi

extern ULONG ulDhcpcPerfInitFinish;

extern ULONG DHCPC_OmInitial(VOID);

#endif /* __DHCPC_COMP_H__ */
