/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_sh_cfg.h
*
*  Project Code: VISPV100R005
*   Module Name: AM4  
*  Date Created: 2006-01-04
*        Author: Li LiXiang
*   Description: AM4��shell�����ú�������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                ���ݱ�̹淶�����ļ����й淶������
*  2006-11-07   zhoutong(43740)         �淶������
*
*******************************************************************************/
 
#ifdef __cplusplus
extern "C" {
#endif


#ifndef _AM4_SH_CFG_H_
#define _AM4_SH_CFG_H_


#define IP_AM4_EXEC_INFO_INDEX (g_ulAM4ErrInfoIndex)


#define IP_AM4_ENABLE_CLI           1
#define IP_AM4_DISABLE_CLI          0


#define IP_AM4_RPC_CHANNEL_ID_ADDRCMD   (MID_COMP_AM4|0x0001)
#define IP_AM4_RPC_CHANNEL_ID_CMD       (MID_COMP_AM4|0x0002)
#define IP_AM4_RPC_PlugInOut            (MID_COMP_AM4|0x0003)


#define IP_DEBUG_INFO             1


/* request type to IO board. when main board processed a command, and needs
 * IO board to do some process, it will use RPC. these defines are RPC request
 * command types.
 */
#define IP_AM4_SHOW_IPIF      1
#define IP_AM4_SHOW_IPIFBRIEF 2
#define IP_AM4_SET_DEBUG      3

#define IP_PHYSTATE_MAXLENGTH   21   /* "administratively down"�ַ��������bit����Ϊ21 */
#define IP_PROSTATE_MAXLENGTH   12   /* "up(spoofing)"�ַ��������bit����Ϊ12 */

/* show ip interface�����У�ip��Ϣ����󳤶� */
#define ENG_LENOFIPINFO_SHOWIN (MAXADDR_ON_ONEIF * 80 + 1000)
#define CHN_LENOFIPINFO_SHOWIN (MAXADDR_ON_ONEIF * 80 + 1000)

/*add by pengjimei for 8070 IP������ֲ��Ŀ*/
typedef struct tagIP_RPC_MSG
{
    ULONG      IpRpc_ulFuncId;
    ULONG      IpRpc_ulifindex;
    ULONG      ulIpCmdFlag; /* per-flow load balance */

}IP_RPC_MSG_S;

/* Add Begin: tianli29125, 2005/6/1, SWFD09713 */
#define IP_CMD_DIRECT_BROADCAST      0x00000001
#define IP_CMD_VERIFY_SOURCE_ADDRESS 0x00000002
#define IP_CMD_CLEAR_DF_FLAG         0x00000004
/* Add End */

ULONG IP_AM4_RegBuildRun();
ULONG IP_AM4_SH_RegCmdRPC();
ULONG IP_AM4_SH_RegConfigProc( VOID );
ULONG IP_AM4_SH_RegCmd();

#endif  /* end of _AM4_SH_CFG_H_ */ 


#ifdef __cplusplus
}
#endif/* end of __cplusplus */

