/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              vrf_pub.h
*
* Project Code: VISPV100R007
*  Module Name: VRF  
* Date Created: 2009-01-20
*       Author: Qinyun
*  Description: VRFģ������ṩ�ĺ궨�塢�ṹ����������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-01-20   Qinyun                  Create
*
*******************************************************************************/
 
#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _VRF_API_H_
#define _VRF_API_H_

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN 47       /* ���ӿ������� */
#endif

#define VRF_DEFAULT_ID        0
#define VRF_DEFAULT_NAME      ""

#define VRF_MAX_VRFNAME_LENGTH        31
#define VRF_MAX_IF_NAME_LENGTH        IF_MAX_INTERFACE_NAME_LEN

#define VRF_SET        1
#define VRF_DEL        0
/* wangjiaqi modify for mccp opt begin */
#define VRF_MOVE       2/*�ڲ�ʹ�ã��Ƕ���API����*/
/* wangjiaqi modify for mccp opt end */

#define VRF_CALLBACK_CREATE 0x1
#define VRF_CALLBACK_DELETE 0x02
#define VRF_CALLBACK_CHANGE 0x03

/*Added by limin00188004, ֧��ȫ�ֺ�VRF��Ŀ���License, 2012/9/24   ���ⵥ��:S.VRF.02.01 */
#define VRF_LICENCE_DISABLE 0x00
#define VRF_LICENCE_ENABLE  0x01

typedef ULONG(*VRF_GET_LICENSE_STATE_FUNC)(ULONG ulVrfIndex, UCHAR *pucVrfSwitch);
/* End of Added by limin00188004, 2012/9/24   ���ⵥ��:S.VRF.02.01 */

/* Add for BC3D03298 at 2010-05-31*/
typedef enum tagVRF_RM_PRO_TYPE_E
{
    VRF_RM_PRO_OSPF = 1,
    VRF_RM_PRO_RIP,
    VRF_RM_PRO_OSPFV3,
    VRF_RM_PRO_RIPNG,
    VRF_RM_PRO_MAX,
}VRF_RM_PRO_TYPE_E;
/* end for BC3D03298 at 2010-05-31*/

typedef enum tagVRF_ERR_E
{
    VRF_OK                    ,    /* 0  */
    VRF_ERR = MID_COMP_VRF + 1,    /* 1  */
    VRF_ERR_NOT_INIT          ,    /* 2  VRFδ��ʼ�� */
    VRF_ERR_ENTRY_NOT_CREATE  ,    /* 3  VRFʵ��δ���� */
    VRF_ERR_ENTRY_EXIST       ,    /* 4  VRFʵ���Ѵ��� */
    VRF_ERR_FULL_CFG          ,    /* 5  VRF���ù������ */
    VRF_ERR_DEL_DEFAULT       ,    /* 6  ����ɾ��Ĭ�ϵ�VRFʵ�� */
    VRF_ERR_PORT_TYPE         ,    /* 7  �ӿ����ʹ��� */
    VRF_ERR_SUBPORT_TYPE      ,    /* 8  �ӽӿ����ʹ��� */
    VRF_ERR_ALREADY_BIND      ,    /* 9  �ӿ��Ѿ��󶨵�VPN�� */
    VRF_ERR_UNBIND            ,    /* 10 �ӿ�δ�󶨵�VPN�� */
    VRF_ERR_NULL              ,    /* 11 ��ָ�� */
    VRF_ERR_CFG_CMD           ,    /* 12 ���������ַǷ�,1��ʾ����,0��ʶȡ��,�����Ƿ� */
    VRF_ERR_MALLOC            ,    /* 13 �ڴ�����ʧ�� */
    VRF_ERR_INDEX             ,    /* 14 VRF Index��ƥ�� */
    VRF_ERR_GET_IFINDEX       ,    /* 15 ���ݽӿ�����ȡ�ӿ�����ʧ�� */
    VRF_ERR_GET_VRFINDEX      ,    /* 16 ����vrf����ȡvrf����ʧ�� */
    VRF_ERR_NODE_NOT_FINDE    ,    /* 17 δ�ҵ��ڵ� */
    VRF_ERR_FILTER            ,    /* 18 ��ѯVRF�󶨹�ϵ�Ĺ��˲����Ƿ� */
    VRF_ERR_AM4_MOD           ,    /* 19 AM4��ַ�����ʼ����ɾ������ʧ�� */
    VRF_ERR_CFG_DCL_INST      ,    /* 20 DCL·��ģʽ�£�����·�����ʵ��ʧ�� */
    VRF_ERR_CFG_NAME          ,    /* 21 VRF�����쳣 */
    VRF_ERR_DEL_RMPRO         ,    /* 22 ɾ��·����Ϣʧ��*/
    VRF_ERR_DEL_INTF          ,    /* 23 ɾ���ӿ���Ϣʧ��*/
    VRF_ERR_RMPRO_EXIST       ,    /* 24 ·����Ϣ�Ѵ���*/
    VRF_ERR_RM_DCL            ,    /* 25 ·�ɹ���ģʽ����DCL*/
    VRF_ERR_I3_NOT_EXIST      ,    /* 26 I3��Ϣ������*/
    VRF_ERR_DEL_ARP           ,    /* 27 ETHģ�飬ɾ���û���ӵ�ָ��vrf�ľ�̬arp���� */
    VRF_ERR_DISABLE_IP_BORROW ,    /* 28 AM4ģ�飬�ӿڵ�ַȥ����ʧ��*/
    VRF_ERR_DHCP4C_DISABLE    ,    /* 29 DHCPģ�飬ȥʹ��DHCP4Cʧ�� */
    VRF_ERR_DCL_MIB_NOT_INIT  ,    /* 30 DCLģ��δ��ʼ��*/
    VRF_ERR_INST_NOT_READY    ,    /* 31 VRF·�ɻ���ģ��û��ready*/
    VRF_ERR_INST_TYPE         ,    /* 32 VRF·�ɻ���ģ��ʵ�����ͳ���*/
    VRF_ERR_BUFF_LENGTH       ,    /* 33 �����ڴ泤�Ȳ���*/
    VRF_ERR_CALLBACK_NOT_EXIST,    /* 34 �ص�����δע��*/
    VRF_ERR_CALLBACKPRO       ,    /* 35 ���ûص�����ʧ��*/
    VRF_ERR_EV_READ           ,    /* 36 ���¼�ʧ��*/
    VRF_ERR_EV_WRITE          ,    /* 37 д�¼�����*/
    VRF_ERR_EV_TYPE           ,    /* 38 �¼����ͳ���*/
    VRF_ERR_MSG_TYPE          ,    /* 39 д��RM����Ϣ���ͳ���*/
    VRF_ERR_NOTIFY_TO_RM      ,    /* 40 ֪ͨRMʧ�� */
    VRF_ERR_DCL_NOT_INIT      ,    /* 41 OSPF/RIP��������Ϊ��*/
    VRF_ERR_INST_AND_TYPE     ,    /* 42 ����Ĳ�ѯʵ���ź�����Ĳ�ѯ���Ͳ�ƥ��*/
    VRF_ERR_RTM_INSTANCE      ,    /* 43 RTMʵ���Ŵ���*/
    VRF_ERR_IF_NULL           ,    /* 44 �ӿ�Ϊ��*/  
    VRF_ERR_REG_WAITLIST      ,    /* 45 ע��VRF WaitListʧ�� */  
    VRF_ERR_UNREG_WAITLIST    ,    /* 46 ��ע��VRF WaitListʧ��*/  
    VRF_ERR_FIX_INDEX_CREATE  ,    /* 47 ָ��vrf index�Ѿ����� */  
    VRF_ERR_FIX_INDEX_MAX     ,    /* 48 ָ��vrf index�Ƿ�,�������ʵ���� */ 
    VRF_ERR_FIX_INDEX_NAME_EXIT,   /* 49 ָ��vrf index����ʵ��,����ʵ�����Ѿ����� */ 
    VRF_ERR_RELAY_ENABLE      ,    /* 50 ָ���ӿ��Ѿ�ʹ��DHCP4R,ʹ��DHCP4R������󶨺�ȥ�󶨲��� */
    VRF_ERR_INDEX_ZERO        ,    /* 51 vrf indexΪĬ��ֵ0*/
    VRF_ERR_INFO_NOT_CHANGED  ,    /* 52 API���õ���Ϣ�ޱ仯*/
    VRF_ERR_IPV6_MOD,
    /* wangjiaqi modify for mccp opt begin */
    VRF_ERR_WAITLIST          ,    /* 54 waitlist���Ʒ��ش�����*/    
    /* wangjiaqi modify for mccp opt end */
    VRF_ERR_IPC_PORT          ,    /*55 VRF�󶨵Ľӿ���IPC�ӿ�*/
    VRF_ERR_MAX    
}VRF_ERR_E;

/* for API: TCPIP_CfgVrfInstance */
typedef struct tagVRF_CFGINSTANCE_S
{
    ULONG ulOper;                               /*0 ��ʾɾ��   1 ���� */
   ULONG ulVrfIndex ;  /*0 ��ָ��Index  ��0 ָ��Index*/
    CHAR  szVrfName[VRF_MAX_VRFNAME_LENGTH + 1]; /* VPN���֣�Ҫ������Ψһ */
}VRF_CFGINSTANCE_S;

/* for API: TCPIP_CfgIntfBindVrf */
typedef struct tagVRF_CFGINTFBIND_S
{
    ULONG ulOper; /*0 ��ʾȥ��    1 ��*/
    CHAR szIfName[VRF_MAX_IF_NAME_LENGTH + 1];/*�ӿ�����*/
    CHAR szVrfName[VRF_MAX_VRFNAME_LENGTH + 1]; /*VPN���֣�Ҫ������Ψһ*/
}VRF_CFGINTFBIND_S;

/* for API: TCPIP_RegFuncVrfEventCallBack */
typedef struct tagVRF_CALLBACK_IF_CHANGE_S
{
    ULONG ulNewVrfId;
    ULONG ulOldVrfId;
    ULONG ulIfIndex;
}VRF_CALLBACK_IF_CHANGE_S;

typedef struct tagVRF_CALLBACK_VRF_OP_S
{
    ULONG ulVRFIndex;
}VRF_CALLBACK_VRF_OP_S;

typedef union tagVRF_CALLBACK_DATA_U
{
    VRF_CALLBACK_VRF_OP_S stVrfOp;
    VRF_CALLBACK_IF_CHANGE_S stIfChange;
}VRF_CALLBACK_DATA_U;

typedef  ULONG  (*VRF_CALLBACK_FUNC)( ULONG ulEvents , VOID *pData);

/* for API: TCPIP_OpenVrfBindInfo ��������,����ֻ��һ������Ϊ���ַ��� */
typedef struct tagVRF_BIND_FILTER_S 
{  
    CHAR  szIfName[VRF_MAX_IF_NAME_LENGTH + 1];      /* �ӿ����� */
    CHAR  szVrfName[VRF_MAX_VRFNAME_LENGTH + 1];      /* VPN ���� */
    ULONG ulIsAllVrf;      /* �Ƿ��ѯ����VRF���,1-��ѯ����VRF�µİ���Ϣ,0-��ѯָ��VRF��Ϣ */
}VRF_BIND_FILTER_S;

/* for API: TCPIP_GetFirstVrfBindInfo & TCPIP_GetNextVrfBindInfo */
typedef struct tagVRF_BIND_INFO_S 
{  
    ULONG ulVrfIndex;                            /*Vrf���*/   
    CHAR  szVrfName[VRF_MAX_VRFNAME_LENGTH + 1]; /*VPN ����*/
    ULONG ulIfIndex;                            /*�ӿ�����*/
    ULONG ulIfState;                            /*�ӿ�IP���״̬*/ 
}VRF_BIND_INFO_S;

/* for API: TCPIP_OpenVrfCfgInfo �������� */
typedef struct tagVRF_INFO_FILTER_S 
{  
    CHAR szVrfName[VRF_MAX_VRFNAME_LENGTH + 1];      /*VPN ����,���ָ��VRF���ȡָ��VRF����Ϣ�������ȡ����VRF��Ϣ */
    ULONG ulIsAllVrf;
} VRF_INFO_FILTER_S;

/* for API: TCPIP_GetFirstVrfCfgInfo & TCPIP_GetNextVrfCfgInfo */
typedef struct tagVRF_CFG_INFO_S 
{  
    ULONG ulVrfIndex;                              /*Vrf���*/   
    CHAR  szVrfName[VRF_MAX_VRFNAME_LENGTH + 1];   /*VPN ����*/
} VRF_CFG_INFO_S;

/*******************************************************************************
*    Func Name: TCPIP_CfgVrfInstance
* Date Created: 2009-01-22
*       Author: qinyun
*  Description: ����/ɾ��VRFʵ��
*        Input: VRF_CFGINSTANCE_S *pstVrfIn: VRFʵ��������Ϣ
*       Output: 
*       Return: VOS_OK,VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_CfgVrfInstance(VRF_CFGINSTANCE_S *pstVrfIn);
/*******************************************************************************
*    Func Name: TCPIP_CfgIntfBindVrf
* Date Created: 2009-01-22
*       Author: qinyun
*  Description: �ӿ���VPN��/ȥ��
*        Input: VRF_CFGINTFBIND_S *pstVrfIn: VRFʵ��������Ϣ
*       Output: 
*       Return: VOS_OK,VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_CfgIntfBindVrf(VRF_CFGINTFBIND_S * pstVrfIn);
/*******************************************************************************
*    Func Name: TCPIP_GetVrfIndexByName
* Date Created: 2009-01-22
*       Author: qinyun
*  Description: ����VRFʵ�����ƻ�ȡVRF ID
*        Input: CHAR *pszVrfName: VRFʵ������
*       Output: ULONG *pulVrfIndex: VRF ID
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetVrfIndexByName (CHAR *pszVrfName, ULONG *pulVrfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetVrfNameByIndex
* Date Created: 2009-01-22
*       Author: qinyun
*  Description: ����VRF ID��ȡVRFʵ������
*        Input: ULONG ulVrfIndex: VRF ID
*       Output: CHAR *pszVrfName: VRFʵ������
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetVrfNameByIndex(CHAR *szVrfName, ULONG ulVrfIndex);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncVrfEventCallBack
* Date Created: 2009-01-22
*       Author: qinyun
*  Description: ע��VRF���ûص�����
*        Input: ULONG ulModId: ģ��ID
*               ULONG ulEventsToReceive: �ϱ���Ϣ����
*                                        VRF_CALLBACK_CREATE
*                                        VRF_CALLBACK_DELETE
*                                        VRF_CALLBACK_CHANGE
*               VRF_CALLBACK_FUNC pfVrfNotify: �ص�����
*       Output: 
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncVrfEventCallBack (ULONG ulModId, ULONG ulEventsToReceive,
                                                VRF_CALLBACK_FUNC pfVrfNotify);
/*******************************************************************************
*    Func Name: TCPIP_VrfDelSuccessNotify
* Date Created: 2009-01-22
*       Author: qinyun
*  Description: VRFʵ��ɾ���ɹ�֪ͨ
*        Input: ULONG ulModId: ģ��ID
*               ULONG ulVrfIndex: VRF ID
*       Output: 
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-22   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_VrfDelSuccessNotify(ULONG ulModId, ULONG ulVrfIndex);
/*******************************************************************************
*    Func Name: TCPIP_OpenVrfBindInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: ��VRF����Ϣ���
*        Input: VRF_BIND_FILTER_S * pstFilter: ��������
*       Output: ULONG *pulSessionId: ���
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenVrfBindInfo (UINTPTR *pulSessionId,VRF_BIND_FILTER_S * pstFilter);
/*******************************************************************************
*    Func Name: TCPIP_GetFirstVrfBindInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: ��ȡ��һ��VRF����Ϣ
*        Input: ULONG ulSessionId: ���
*       Output: VRF_BIND_INFO_S *pstConfigInfo: ����Ϣ
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetFirstVrfBindInfo(UINTPTR ulSessionId, VRF_BIND_INFO_S *pstConfigInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetNextVrfBindInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: ��ȡ��һ��VRF����Ϣ
*        Input: ULONG ulSessionId: ���
*       Output: VRF_BIND_INFO_S *pstConfigInfo: ����Ϣ
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetNextVrfBindInfo(UINTPTR ulSessionId, VRF_BIND_INFO_S *pstConfigInfo);
/*******************************************************************************
*    Func Name: TCPIP_CloseVrfBindInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: �رջ�ȡVRF����Ϣ�ľ��
*        Input: ULONG ulSessionId: ���
*       Output: 
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseVrfBindInfo (UINTPTR ulSessionId);
/*******************************************************************************
*    Func Name: TCPIP_ShowVrfBindInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: ��ʾVRF����Ϣ
*        Input: CHAR *pszVrfName: VRF����
*       Output: 
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern VOID TCPIP_ShowVrfBindInfo (CHAR *pszVrfName, CHAR *pszIfName, ULONG ulIsAllVrf);
/*******************************************************************************
*    Func Name: TCPIP_OpenVrfCfgInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: ��VRF������Ϣ���
*        Input: VRF_INFO_FILTER_S * pstFilter: ��������
*       Output: ULONG *pulSessionId: ���
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenVrfCfgInfo (UINTPTR *pulSessionId, VRF_INFO_FILTER_S *pstFilter);
/*******************************************************************************
*    Func Name: TCPIP_GetFirstVrfCfgInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: ��ȡ��һ��VRF������Ϣ
*        Input: ULONG ulSessionId: ���
*       Output: VRF_BIND_INFO_S *pstConfigInfo: ����Ϣ
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetFirstVrfCfgInfo(UINTPTR ulSessionId, VRF_CFG_INFO_S *pstConfigInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetNextVrfCfgInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: ��ȡ��һ��VRF������Ϣ
*        Input: ULONG ulSessionId: ���
*       Output: VRF_BIND_INFO_S *pstConfigInfo: ����Ϣ
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetNextVrfCfgInfo(UINTPTR ulSessionId, VRF_CFG_INFO_S *pstConfigInfo);
/*******************************************************************************
*    Func Name: TCPIP_CloseVrfCfgInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: �رջ�ȡVRF������Ϣ�ľ��
*        Input: ULONG ulSessionId: ���
*       Output: 
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern ULONG  TCPIP_CloseVrfCfgInfo (UINTPTR ulSessionId);
/*******************************************************************************
*    Func Name: TCPIP_ShowVrfCfgInfo
* Date Created: 2009-02-12
*       Author: wangchengyang
*  Description: ��ʾVRF������Ϣ
*        Input: CHAR *pszVrfName: VRF����
*       Output: 
*       Return: VRF_OK,������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-12   wangchengyang           Create
*
*******************************************************************************/
extern VOID TCPIP_ShowVrfCfgInfo(CHAR *pszVrfName, ULONG ulIsAllVrf);

/*******************************************************************************
*    Func Name: TCPIP_VRF_SetHaDbg
* Date Created: 2009-10-27
*       Author: zhangchunyu(62474)
*  Description: ����HA���Կ���
*        Input: ULONG ulDbg: ���� 1�� 0�ر�
*       Output: 
*       Return: �ɹ�:VRF_OK
*               ����:ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-27    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern  ULONG TCPIP_VRF_SetHaDbg(ULONG ulDbg);

/*******************************************************************************
*    Func Name: TCPIP_VRF_GetHaDbg
* Date Created: 2009-10-27
*       Author: zhangchunyu(62474)
*  Description: ��ȡVRF HA���Կ���
*        Input: ULONG *pulDbg: �������,��ȡ����ֵ
*       Output: 
*       Return: �ɹ�:VRF_OK
*               ����:ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-10-27    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_VRF_GetHaDbg(ULONG *pulDbg);

/*******************************************************************************/
/*******************************************************************************
*    Func Name: TCPIP_GetVrfIndexByRmPro
* Date Created: 2010-05-31
*       Author: xujun57575
*  Description: ����·��Э��Ľ��̺Ż�ȡVRF����
*        Input: ULONG ulRtType: ·��Э������ ����ΪOSPF����RIP
*               ULONG ulInstance:·��Э�����ID
*               ULONG *pulVrfIndex:����VRF������
*       Output: VRF����
*       Return: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-31   xujun57575              Create for BC3D03298
*
*******************************************************************************/
extern ULONG TCPIP_GetVrfIndexByRmPro(ULONG ulRtType,ULONG ulInstance,ULONG *pulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_EnableVrfLicence
* Date Created: 2012-09-25
*       Author: limin00188004
*  Description: ʹ��/ȥʹ��VRF��License����
*        Input: UCHAR ucOper: 0,vrf licence���Թر�; 1,vrf licence���Դ�
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-25   limin00188004           Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableVrfLicence(UCHAR ucOper);

/*******************************************************************************
*    Func Name: TCPIP_GetVrfLicenceSwitch
* Date Created: 2012-09-27
*       Author: limin00188004
*  Description: ��ȡVRF License�����Ƿ�ʹ�ܵĿ���
*        Input: UCHAR *pucOper:��������
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-27   limin00188004           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetVrfLicenceSwitch(UCHAR *pucOper);

/*******************************************************************************
*    Func Name: TCPIP_CfgLicenceByVrf
* Date Created: 2012-09-25
*       Author: limin00188004
*  Description: ����ָ��VRF���License����
*        Input: CHAR szVrfName[VRF_MAX_VRFNAME_LENGTH + 1]: vrf����
*               UCHAR ucOper: 0, licence�ر�; 1, licence��
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-25   limin00188004           Create
*
*******************************************************************************/
extern ULONG TCPIP_CfgLicenceByVrf(CHAR szVrfName[VRF_MAX_VRFNAME_LENGTH + 1], UCHAR ucOper);

/*******************************************************************************
*    Func Name: TCPIP_GetLicenceByVrf
* Date Created: 2012-09-27
*       Author: limin00188004
*  Description: ͨ��VRF���ƣ���ȡָ��VRF��licence
*        Input: CHAR szVrfName[VRF_MAX_VRFNAME_LENGTH + 1]:VRF����
*               UCHAR *pucOper:����������vrf��licence
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-27   limin00188004           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetLicenceByVrf(CHAR szVrfName[VRF_MAX_VRFNAME_LENGTH + 1], UCHAR *pucOper);

/*******************************************************************************
*    Func Name: TCPIP_ShowVrfLicenceSwitch
* Date Created: 2012-09-27
*       Author: limin00188004
*  Description: ��ʾVRF licenceʹ����Ϣ,�Լ�VRF licenceΪ����״̬������VRF
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-27   limin00188004           Create
*
*******************************************************************************/
extern VOID TCPIP_ShowVrfLicenceSwitch(VOID);

#endif  /* _VRF_API_H_  */

#ifdef  __cplusplus
}
#endif
