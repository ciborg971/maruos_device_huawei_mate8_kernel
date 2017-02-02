#ifndef _RIP_API_H
#define _RIP_API_H

#ifdef  __cplusplus
    extern "C"{
#endif

#define  RIP_CFG_ADD     0/*����*/
#define  RIP_CFG_DEL     1/*ȡ��*/

#define  RIP_AUTH_SIZE   15
#define  RIP_MAX_EQUAL_ROUTE_NUM   32

#define    RIP_DEAFAULT_ROUTE_MAX_COST   15 

#ifndef MAX_IF_NAME_LENGTH
#define MAX_IF_NAME_LENGTH 47
#endif
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define RIP_MAX_VRF_NAME_LENGTH 31
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#ifndef BOOL_T
#define BOOL_T  short   /* boolean */  
#endif 

/*RIP �շ�����ע�ṳ�Ӻ�������*/

typedef ULONG (*RIP_PACKET_HOOK_FUNC)(USHORT usProcId ,ULONG ulIfIndex, CHAR *pcPacket, ULONG ulLen);

typedef enum tagRIP_ERROR_E  
{
    RIP_SUCCESS,

    RIP_ERR_GEN_ERROR = MID_COMP_RIP + 2, 
    RIP_ERR_WRONG_VALUE, /*MIB���õ�ֵ����*/
    RIP_ERR_INCONSISTENT_VALUE,/*MIB���õ�ֵ��һ��*/
    RIP_ERR_RESOURCE_UNAVAILABLE,/*MIB���õ���Դ��Ч*/
    RIP_ERR_NO_SUCH_OBJECT, /*���󲻴���*/
    RIP_ERR_END_OF_TABLE,/*�������*/
    RIP_ERR_AGENT_ERROR, 
    RIP_ERR_INCOMPLETE,  
    RIP_ERR_PARTIAL_FAMILY_OK,
    RIP_ERR_PRODUCT_NOT_READY,
    RIP_ERR_CFG_TIMEOUT = MID_COMP_RIP + 15,/*���ó�ʱ15*/ 
    RIP_ERR_INIT_FAILED, /*RIP û�г�ʼ���ɹ�*/
    RIP_ERR_POINTER_IS_NULL,   
    RIP_ERR_CONFIG_FLAG_INVALID,/*��������ñ�־������TRUEҲ����FALSE*/
    RIP_ERR_PRAR_INVALID,/*�������Ϸ�*/
    RIP_ERR_ALREADY_EXIST,/*RIPʵ���Ѿ�����*/
    
    RIP_ERR_INSTANCE_NOT_EXIST, /*RIPʵ��������*/       
    
    RIP_ERR_INSTANCE_CANNOT_IS_ZERO, /*RIPʵ���Ų���Ϊ0*/
    RIP_ERR_IPS_IS_NULL, /*RIP ��IPS��ϢΪ��*/
    RIP_ERR_RET_IPS_IS_NULL, /*���ص�IPS��Ϣ*/
    RIP_ERR_CONF_DATA_IS_NULL,/*25 RIP ���������� Ϊ��*/
    RIP_ERR_CONN_CB_IS_NULL,/*���ӿ��ƿ�Ϊ��*/
    RIP_ERR_NETWORK_INVALID, /*��������ε�ַ*/
    RIP_ERR_AUTH_MODE_INVALID,/*������֤ģʽ*/
    RIP_ERR_MALLOC_FAILED,/*�����ڴ�ʧ��*/
    RIP_ERR_NODE_IS_NOT_EXIST,/*��㲻����*/
    RIP_ERR_HANDLE_IS_NOT_EXIST,/*���������*/
    RIP_ERR_INSTANCE_IS_EXCEED_LIMIT,/*RIPʵ��������Χ*/
    RIP_ERR_CAN_NOT_FIND_ROUTE,/*�Ҳ���RIP��·��*/
    RIP_ERR_HAVE_NO_NEXT_ROUTE,/*�Ҳ�����һ��·��*/
    RIP_ERR_NETWORK_IS_EXIST,    /*network�Ѿ�����*/
    RIP_ERR_NETWORK_IS_NOT_EXIST,/*network������*/
    RIP_ERR_HAVE_NO_INTERFACE,/*�Ҳ����ӿ�*/
    RIP_ERR_HAVE_NO_IP_ADDR,/*��ȡ������ַ*/
    RIP_ERR_JOIN_FAILED,/*������ģ��JOINʧ��*/
    RIP_ERR_CANCEL_JOIN_FAILED,/*������ģ��ȡ��JOINʧ��*/
    RIP_ERR_OPEN_IF_ENTRY_FAILED,/*�򿪽ӿ� ENTRYʧ��*/
    RIP_ERR_IF_HAVE_NOT_CFG_METRIC,/*�ýӿ�û�����ö���ֵ*/
    RIP_ERR_HAVE_NO_RIP_EXIST, /*Ŀǰû��RIPʵ��������*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    RIP_ERR_GET_VRF_INDEX,
    RIP_ERR_INVALID_VRF_INDEX,
    RIP_ERR_INST_NOT_IN_VRF,
    RIP_ERR_VRF_NOT_INIT,
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    RIP_ERR_GET_IF_INFO,/*0x0E2E0030 <��ȡ�ӿ���Ϣ����>*/
    RIP_ERR_IF_TYPE,/*0x0E2E0031 <��ȡ�ӿ����ʹ���>*/
    RIP_ERR_IF_HAVE_BEEN_BIND,/*0x0E2E0032 <�ӿ��Ѿ���>*/
    RIP_ERR_IF_HAVE_NOT_BEEN_BIND,/*0x0E2E0033 <�ӿڻ�û�а󶨹�>*/
    RIP_ERR_PROCESS_IF_NOT_MATCH,/*0x0E2E0034 <�ӿڲ��ǰ���ָ��������>*/
    RIP_ERR_PROCESS_NOT_BIND_IF,/*0x0E2E0035 <ָ��������û�и��ӿڰ�>*/
    RIP_ERR_FILTER_RULE_EXIST,/*0x0E2E0036 <�����Ѵ��ڻ򲻴���Ҫɾ���Ĺ���>*/
    RIP_ERR_FILTER_RULE_NOT_EXIST, /*0x0E2E0037 <���򲻴���>*/   
    RIP_ERR_GET_HAVE_NOT_OPEN,    /*0x0E2E0038 <û�н���OPEN����>*/
    RIP_ERR_GETFIRST_FAIL,/*0x0E2E0039 <û�н���GET FIRST����>*/
    RIP_ERR_INVALID_UPDATE_TIMEOUT,/*0x0E2E003A <update��ʱ������ֵ����>*/
    RIP_ERR_INVALID_AGE_TIMEOUT,/*0x0E2E003B <age��ʱ������ֵ����>*/
    RIP_ERR_INVALID_GARBAGE_TIMEOUT, /*0x0E2E003C <garbage��ʱ������ֵ����>*/
    RIP_ERR_INVALID_PREFERENCE_VALUE,/*0x0E2E003D <���ȼ�����ֵ����>*/
    RIP_ERR_GET_RTM_INST,/*0x0E2E003E <��ȡRTMʵ������>*/
    RIP_ERR_CFG_PREFERENCE,/*0x0E2E003F <MIB�ڲ��������ȼ�����>*/
    RIP_ERR_GET_PREFERENCE,/*0x0E2E0040 <MIB�ڲ���ȡ���ȼ�����>*/
    RIP_ERR_VRFNAME_TOOLONG,/*0x0E2E0041 <vrf������>*/
    RIP_ERR_ACLNUM,/*0x0E2E0042 <���˹���ų�����Χ>*/
    RIP_ERR_METRIC_INOUT_VALUE_ERR,/*0x0E2E0043 <���õĽ��ջ���metricֵ����>*/
    RIP_ERR_DEFRT_METRIC_VALUE_ERR,/*0x0E2E0044 <���õ�Ĭ��·��metricֵ����>*/
    RIP_ERR_INVALID_BALANCE_NUMBER, /*0x0E2E0045 <���õ����ƽ��·�ɸ�������>*/
    RIP_ERR_INVALID_PROTO_TYPE = MID_COMP_RIP + 0x46, /* 0x46 ��ЧЭ������ */
    RIP_ERR_INVALID_METRIC_TYPE,                      /* 0x47 ��ЧMetric���� */
    RIP_ERR_INVALID_METRIC_VAL,                       /* 0x48 ��ЧMetricֵ */
    RIP_ERR_INVALID_STATIC_RPAID,                     /* 0x49 ��Ч��̬Э������ID */
    RIP_ERR_INVALID_DYNAMIC_RPAID,                    /* 0x4A ��Ч��̬Э������ID */
    
    RIP_ERR_MAX = MID_COMP_RIP + 255,
}RIP_ERROR_E;


typedef struct tagRIP_AUTH 
{ 
    ULONG ulAuthMode;   /*��֤ģʽ������֤��text��MD5*/
    UCHAR szIfName[MAX_IF_NAME_LENGTH + 1];  /*ָ���ӿڵĽӿ�������󳤶�47�ֽڡ�*/
    BOOL_T bUndoConfig ;  /*TRUE��ʾ���ã�FALSE��ʾ�ָ�Ĭ��ֵ*/
    USHORT usProcId;   /*RIPʵ��ID�ţ�ȡֵ��Χ1~65535��*/  
    UCHAR  ucAuthKey[RIP_AUTH_SIZE + 1]; /*��֤KEY,��󳤶�16�ֽڡ�*/
}RIP_AUTH_S;

typedef struct tagRIP_CFG_INFO 
{  
    UCHAR IsHostRoute;/*�Ƿ���������·��*/
    UCHAR ucUpdateTimeOutVal;/*ˢ��ʱ��*/ 
    UCHAR ucAgeTimeOutVal; /*�ϻ���ʱʱ��*/
    UCHAR ucGarbageTimeOutVal;/*�����Ѽ�ʱ��*/ 
    USHORT usMaxBalCount; /*���ƽ��·�ɸ���*/ 
    USHORT usProcId; /*RIPʵ����*/
    ULONG ulVrfIndex;
} RIP_CFG_INFO_S;

typedef struct tagRIP_CONFIG_IF_DEF_ORG /*Ĭ��·�ɵ�Ĭ��costֵ���ýṹ*/
{ 
    USHORT usProcId;  /*RIPʵ��ID�ţ�ȡֵ��Χ1~65535��*/  
    USHORT usDfltOriginCost; /*Ĭ��·�ɵ�costֵ*/
    UCHAR  szIfName[MAX_IF_NAME_LENGTH + 1]; /*ָ���ӿڵĽӿ�������󳤶�47�ֽڡ�*/
    BOOL_T bUndoConfig; /*TRUE��ʾ���ã�FALSE��ʾ�ָ�Ĭ��ֵ*/
    UCHAR aucPad[2]; 
} RIP_CONFIG_IF_DEF_ORG_S; 


typedef struct tagRIP_CONFIG_IF 
{ 
    UCHAR   szIfName[MAX_IF_NAME_LENGTH + 1]; /*�ӿ���*/
    USHORT  usProcId;  /*RIPʵ��ID�ţ�ȡֵ��Χ1~65535��*/     
    BOOL_T  bUndoConfig; 
} RIP_CONFIG_IF_S;

typedef struct tagRIP_CONFIG_JOIN 
{ 
    ULONG ulInterfaceId; 
    ULONG ulPartnerIndex; 
    BOOL_T bUndoConfig; 
    USHORT usProcId;  /*RIPʵ��ID�ţ�ȡֵ��Χ1~65535��*/  
} RIP_CONFIG_JOIN_S;

typedef struct tagRIP_CONFIG_MAXLOAD_BAL /*���ƽ��·����Ŀ*/
{ 
    USHORT  usProcId; /*RIPʵ��ID�ţ�ȡֵ��Χ1~65535��*/  
    USHORT  usMaxNumBalancePaths; /*ƽ��·�ɸ���*/
    BOOL_T  bUndoConfig; /*TURE��ʾ���ã�FALSE��ʾ�ָ�Ĭ��ֵ4*/
    UCHAR aucPad[2]; 
} RIP_CONFIG_MAXLOAD_BAL_S;


typedef struct  tagRIP_CONFIG_METRIC /*����·��Ȩֵ�����ýṹ*/
{ 
    UCHAR  szIfName[MAX_IF_NAME_LENGTH + 1];/*ָ���ӿڵĽӿ�������󳤶�47�ֽڡ�*/
    USHORT  usMetricInVal;  /*���븽��·��Ȩֵ*/
    USHORT  usMetricOutVal; /*�������·��Ȩֵ*/
    BOOL_T  bUndoConfig;  /*TURE��ʾ���ã�FLASE��ʾȡ�����ָ���0*/
    UCHAR   ucPad[2];
} RIP_CONFIG_METRIC_S;

typedef struct tagRIP_CONFIG_NETWORK /*��������*/
{ 
    ULONG ulNetwork; /*���εĵ�ַ*/
    BOOL_T bUndoConfig; /*TRUE��ʾ���ã�FALSE��ʾɾ��*/
    USHORT usProcId;  /*RIPʵ��ID�ţ�ȡֵ��Χ1~65535��*/  
} RIP_CONFIG_NETWORK_S;

typedef struct tagRIP_CONFIG 
{ 
    USHORT usProcId;  /*RIPʵ��ID�ţ�ȡֵ��Χ1~65535��*/  
    BOOL_T bUndoConfig; 
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[RIP_MAX_VRF_NAME_LENGTH + 1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RIP_CONFIG_S;

typedef struct tagRIP_IFCONFIG
{
    UCHAR   szIfName[MAX_IF_NAME_LENGTH + 1];
    BOOL_T  bUndoConfig;
    UCHAR   aucPad[2];
}RIP_IFCONFIG_S;

typedef struct tagRIP_CONFIG_TIMERS 
{ 
    ULONG ulUpdateTimeOutVal;/*ˢ��ʱ��*/ 
    ULONG ulAgeTimeOutVal; /*�ϻ���ʱʱ��*/
    ULONG ulGarbageTimeOutVal;/*1-255*/ 
    BOOL_T bUndoConfig; 
    USHORT usProcId; /*RIPʵ��ID�ţ�ȡֵ��Χ1~65535��*/  
} RIP_CONFIG_TIMERS_S;

typedef struct tagRIP_IF_CFG_INFO 
{  
    UCHAR  ucAuthType;
    UCHAR  ucSend;
    UCHAR  ucReceive;
    UCHAR  ucPad;
    ULONG  ulDefaultMetric;
} RIP_IF_CFG_INFO_S;


typedef struct tagRIP_IF_STAT_INFO 
{   
    ULONG  ulRcv_bad_packets;/**/
    ULONG  ulRcv_bad_routes;
    ULONG  ulSent_updates;
} RIP_IF_STAT_INFO_S;

/*���ⵥ:BC3D00770  luogaowei 2008-11-26 �޸ı�������*/
typedef struct tagRIP_PEER_INFO 
{   
    ULONG  ulAddressType;/*0x00-0x12*/
    ULONG  ulAddressLen;/*1-16*/
    UCHAR  ucAddress[16];
    ULONG  ulVersion;/*1-2*/
    ULONG  ulRcvBadPackets;
    ULONG  ulRcvBadRoutes;
    USHORT usProcId;  /*RIPʵ��ID�ţ�ȡֵ��Χ1~65535��*/ 
    UCHAR  ucPad[2];
} RIP_PEER_INFO_S; /*RIP���ھ���Ϣ*/

typedef struct tagRIP_RESET 
{ 
    USHORT usProcId;  /*RIPʵ��ID�ţ�ȡֵ��Χ1~65535��*/  
    UCHAR aucPad[2]; 
}RIP_RESET_S;

#define RIP_ROUTE_TYPE_INTERFACE      0x10  /*�ӿ�·��*/
#define RIP_ROUTE_TYPE_PROTOCOL       0x20  /*RIPѧϰ����·��*/
#define RIP_ROUTE_TYPE_RPI            0x30  /*RM�����·��*/
#define RIP_ROUTE_TYPE_OTHER          0x40  /*����*/

typedef struct tagRip_route
{ 
    ULONG ulDstAddr; /*Ŀ�ĵ�ַ*/
    ULONG ulMaskLen; /*���볤��*/
    USHORT route_tag; /*·�ɱ��*/
    USHORT usMetric; /*����ֵ*/
    ULONG  ulNextHop;/*��һ����ַ*/
    USHORT  usRouteType; /*·������:�ӿ����͡�Э�顢RPI*/    
    USHORT  usAge; /*�ϻ�ʱ��*/
} RIP_ROUTE_S; /*RIP��·�ɱ���*/


typedef struct tagRip_route_group_s
{ 
    ULONG ulRouteNum;
    RIP_ROUTE_S stRipRoutes[RIP_MAX_EQUAL_ROUTE_NUM];
} RIP_ROUTE_GROUP_S; /*RIP��һ��·��:����Ŀ�ĵ�ַ����һ����ͬ��·��*/

/***********************************************/

typedef struct tagRIP_NETWORKINFO_FILTER_S
{
   USHORT  usProcId;
   UCHAR   ucPad[2];
   /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
   UCHAR   szVrfName[RIP_MAX_VRF_NAME_LENGTH + 1];
   /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
} RIP_NETWORKINFO_FILTER_S; /*RIP ������Ϣ��ѯ�Ĺ�������*/


typedef struct tagRIP_NETWORKINFO_S
{
    USHORT usProcId; /*RIP ʵ����*/
    USHORT usCount; /*���ص����θ���*/
    ULONG* pulNetWork;
} RIP_NETWORKINFO_S; /*���ڲ�ѯRIP ��������Ϣ*/

typedef struct tagRIP_PEERINFO_FILTER_S
{
    USHORT usProcId;
    UCHAR ucPad[2];
} RIP_PEERINFO_FILTER_S; /*���ڲ�ѯ�ھӵĹ�����Ϣ*/

typedef struct tagRIP_If_Cfg_Info_Ex /*һ���ӿ�ֻ������һ��RIP*/
{  
    ULONG  ulIfIndex; /*�ӿ�����ֵ*/    
    UCHAR  ucSplitHorizon;/*�Ƿ�����ˮƽ�ָ�*/
    UCHAR  ucPoisonReverse;/*�Ƿ����ö�����ת*/
    UCHAR  ucMetricIn;/*����·��Ȩֵ ����*/
    UCHAR  ucMetricOut;/*����·��Ȩֵ ���*/ 
} RIP_IF_CFG_EX_S;/*����DCL ��չ�Ľӿ�������Ϣ*/

typedef struct tagRIP_CFGINFO_FILTER_S
{
   USHORT  usProcId;
   UCHAR   ucPad[2];
}RIP_CFGINFO_FILTER_S; /*RIP ȫ��������Ϣ��ѯ�Ĺ�������*/


extern RIP_ERROR_E RIP_CFG_CmdRipProcess (RIP_CONFIG_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdNetwork (const RIP_CONFIG_NETWORK_S *pstConfigInfo); 
extern RIP_ERROR_E RIP_CFG_CmdTimers(const RIP_CONFIG_TIMERS_S *pstConfigInfo);

extern RIP_ERROR_E   RIP_CFG_CmdHostRoute (const RIP_CONFIG_S *pstConfigInfo);
extern  RIP_ERROR_E RIP_CFG_CmdPoisonReverse (const RIP_IFCONFIG_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdSplitHorizon(const RIP_IFCONFIG_S *pstConfigInfo);


extern RIP_ERROR_E RIP_CFG_CmdResetStat(const RIP_RESET_S *pstConfigInfo);
extern RIP_ERROR_E  RIP_CFG_DefaultRouteOrig(const RIP_CONFIG_IF_DEF_ORG_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdMaxLoadBal(const RIP_CONFIG_MAXLOAD_BAL_S *pstConfigInfo);

extern RIP_ERROR_E RIP_CFG_CmdInput (const RIP_CONFIG_IF_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdOutput (const RIP_CONFIG_IF_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdSilentInterface (const RIP_CONFIG_IF_S *pstConfigInfo);

extern RIP_ERROR_E RIP_CFG_CmdMetricIn (const RIP_CONFIG_METRIC_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdMetricOut (const RIP_CONFIG_METRIC_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdAuth (const RIP_AUTH_S *pstConfigInfo);

extern RIP_ERROR_E RIP_GetCfgInfo (USHORT usProcId, RIP_CFG_INFO_S *pstConfigInfo);
extern RIP_ERROR_E RIP_GetIfStatInfo (USHORT usProcId, UCHAR  szIfName[], RIP_IF_STAT_INFO_S *pstStatInfo);
extern RIP_ERROR_E RIP_GetIfCfgInfo (USHORT usProcId, UCHAR szIfName[48], RIP_IF_CFG_INFO_S *pstConfigInfo);

extern RIP_ERROR_E RIP_OpenPeerInfoEntry(ULONG *pulSessionId, RIP_PEERINFO_FILTER_S* pstDispRipFilter);
extern RIP_ERROR_E RIP_ClosePeerInfoEntry(ULONG ulSessionId);
extern RIP_ERROR_E RIP_GetFirstPeerInfo (ULONG ulSessionId, RIP_PEER_INFO_S *pstConfigInfo);
extern RIP_ERROR_E RIP_GetNextPeerInfo(ULONG ulSessionId, RIP_PEER_INFO_S *pstConfigInfo);


extern RIP_ERROR_E RIP_OpenRouteEntry(ULONG *pulHandle);
extern RIP_ERROR_E RIP_CloseRouteEntry(ULONG ulHandle);
extern RIP_ERROR_E RIP_GetFirstRouteInfo (USHORT usProcId, ULONG ulHandle, RIP_ROUTE_GROUP_S *pstRipGrpRoutes);
extern RIP_ERROR_E RIP_GetNextRouteInfo (USHORT usProcId, ULONG ulHandle, RIP_ROUTE_GROUP_S *pstRipGrpRoutes);

extern  RIP_ERROR_E RIP_OpenNetworkInfoEntry (ULONG *pulSessionId, RIP_NETWORKINFO_FILTER_S* pstDispProcFilter);
extern  RIP_ERROR_E RIP_CloseNetworkInfoEntry(ULONG ulSessionId);
extern  RIP_ERROR_E RIP_GetFirstNetworkInfo(ULONG ulSessionId, RIP_NETWORKINFO_S* pstConfigInfo);
extern  RIP_ERROR_E RIP_GetNextNetworkInfo(ULONG ulSessionId, RIP_NETWORKINFO_S* pstConfigInfo);

extern  RIP_ERROR_E RIP_GetIfCfgExInfo (CHAR *pszIfName, RIP_IF_CFG_EX_S *pstIfCfgExInfo);

extern RIP_ERROR_E RIP_Direct_OpenPeerInfoEntry(ULONG *pulSessionId ,USHORT usProcId);
extern RIP_ERROR_E RIP_Direct_ClosePeerInfoEntry(ULONG ulSessionId);
extern RIP_ERROR_E RIP_Direct_GetFirstPeerInfo(ULONG ulSessionId, RIP_PEER_INFO_S *pstPeerInfo);
extern RIP_ERROR_E RIP_Direct_GetNextPeerInfo(ULONG ulSessionId, RIP_PEER_INFO_S *pstPeerInfo);

extern VOID RIP_ShowGlobalInfo(USHORT usProcId);
extern VOID RIP_ShowPeerInfo(USHORT usProcId);
extern VOID RIP_ShowRipIfCfgInfo(USHORT usProcId);
extern VOID RIP_ShowRipRouteInfo(USHORT usProcId);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*extern VOID RIP_ShowNetWorkInfo(USHORT usProcId);*/
extern VOID RIP_ShowNetWorkInfo(USHORT usProcId,CHAR *pszVrfName);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
extern VOID RIP_ShowExIfCfgInfo (VOID);
extern VOID RIP_Direct_ShowPeerInfo(USHORT usProcId);

extern ULONG RIP_Intermediate_UnHook_Register(ULONG ulDirection);
extern ULONG RIP_Intermediate_Hook_Register(ULONG ulDirection, 
        RIP_PACKET_HOOK_FUNC pfRipFwHookFunc);


extern RIP_ERROR_E RIP_OpenCfgInfoEntry (ULONG *pulSessionId, RIP_CFGINFO_FILTER_S* pstDispProcFilter);
extern RIP_ERROR_E RIP_CloseCfgInfoEntry(ULONG ulSessionId);
extern RIP_ERROR_E RIP_GetFirstRipCfgInfo(ULONG ulSessionId, RIP_CFG_INFO_S *pstConfigInfo);
extern RIP_ERROR_E RIP_GetNextRipCfgInfo(ULONG ulSessionId, RIP_CFG_INFO_S *pstConfigInfo);

/************************·������������****************************************/
typedef struct tagRIP_CFGREDISTRIBUTE
{
    BOOL_T bNoFlag;
    USHORT usProcessId;
    RM_RPM_PLCYREDIS_S stPolicyRedist;
}RIP_CFGREDISTRIBUTE_S; /*RIP ·������������ýṹ*/

typedef struct tagRIP_CFGDISTRIBUTE
{
    BOOL_T bNoFlag;
    USHORT usProcessId;
    RM_RPM_PLCYDIST_S stPolicyDist;
}RIP_CFGDISTRIBUTE_S;/*RIP ·�ɹ������ýṹ*/

extern RIP_ERROR_E RIP_CFG_CmdRedistributeProc(RIP_CFGREDISTRIBUTE_S* pstRedistIn);
extern RIP_ERROR_E RIP_CFG_CmdDistributeOutProc(RIP_CFGDISTRIBUTE_S* pstDistExpIn);
extern RIP_ERROR_E RIP_CFG_CmdDistributeInProc (RIP_CFGDISTRIBUTE_S*  pstDistImpIn);


typedef struct tagRIP_IMPORTINFO_FILTER_S
{
    USHORT  usProcId;
    UCHAR   ucPad[2];
} RIP_IMPORTINFO_FILTER_S;/*RIP·�ɲ��Բ�ѯ����*/

typedef struct tagRIP_IMPORTINFO_S
{
    USHORT usProcessId;
    UCHAR  ucPad[2];
    RM_RPM_PLCYREDIS_S  stReDis;
}RIP_IMPORTINFO_S; /*RIP ·�ɲ��Բ�ѯ��Ϣ*/

extern RIP_ERROR_E RIP_OpenImportInfoEntry(ULONG *pulSessionId, RIP_IMPORTINFO_FILTER_S* pstDispProcFilter);
extern RIP_ERROR_E RIP_GetFirstImportInfo(ULONG ulSessionId, RIP_IMPORTINFO_S* pstConfigInfo);
extern RIP_ERROR_E RIP_GetNextImportInfo (ULONG ulSessionId, RIP_IMPORTINFO_S* pstConfigInfo);
extern RIP_ERROR_E RIP_CloseImportInfoEntry(ULONG ulSessionId);
extern VOID RIP_ShowImportPolicyInfo(USHORT usProcId);


typedef struct tagRIP_FILTERPOLICYINFO_FILTER_S
{
    USHORT  usProcId;
    UCHAR  ucPad[2];
} RIP_FILTERPOLICYINFO_FILTER_S; /*RIP������Ϣ��ѯ����*/

typedef struct tagRIP_FILTERPOLICYINFO_S
{
    USHORT usProcessId;
    UCHAR  ucPad[2];
    #define RIP_TO_RM 1
    #define RM_TO_RIP 2
    ULONG  ulPlcyDirectFlag;
    RM_RPM_PLCYDIST_S stPlcyDist;
}RIP_FILTERPOLICYINFO_S;/*RIP ������Ϣ��ѯ*/


extern RIP_ERROR_E RIP_OpenFilterPolicyInfoEntry (ULONG *pulSessionId, 
            RIP_FILTERPOLICYINFO_FILTER_S* pstDispProcFilter);
extern RIP_ERROR_E RIP_GetFirstFilterPolicyInfo(ULONG ulSessionId, RIP_FILTERPOLICYINFO_S* pstConfigInfo);
extern RIP_ERROR_E RIP_GetNextFilterPolicyInfo(ULONG ulSessionId, RIP_FILTERPOLICYINFO_S* pstConfigInfo);
extern RIP_ERROR_E RIP_CloseFilterPolicyInfoEntry(ULONG ulSessionId);
extern  VOID RIP_ShowFilterPolicyInfo(USHORT usProcId);

#ifdef  __cplusplus
}
#endif

#endif 

