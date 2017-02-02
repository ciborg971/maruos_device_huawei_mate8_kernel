/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              nsr_common.h
*
*  Project Code: Dopra V3R2
*   Module Name: NSR Commonģ�����ͷ�ļ�  
*  Date Created: 2013-09-25
*        Author: guojianjun178934
*   Description: NSR����ģ�鴦��ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-09-25   guojianjun178934        Create
*
*******************************************************************************/
#ifndef NSR_COMMON_INCLUDED
#define NSR_COMMON_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*NSR����ģ�鶨��*/
#define NSR_MODULE_TYPE_MIN       0
#define NSR_MODULE_TYPE_COMMON    1
#define NSR_MODULE_TYPE_BFD       2
#define NSR_MODULE_TYPE_TRUNK     3
#define NSR_MODULE_TYPE_OSPF      4
#define NSR_MODULE_TYPE_OTHER     5
#define NSR_MODULE_TYPE_MAX       6

#define NSR_MODULE_NAME_MAX     20

/*NSR������Ϣ����*/
#define NSR_COMMON_MSG_BOARD            0x01    /*����״̬��Ϣ*/
#define NSR_COMMON_MSG_PHY_IF_READY    0x02    /*����ӿ��ϱ�����*/
#define NSR_COMMON_MSG_LOG_IF_READY    0x04    /*�߼��ӿ�NSRƽ������*/
#define NSR_COMMON_MSG_IF_READY    (NSR_COMMON_MSG_PHY_IF_READY | NSR_COMMON_MSG_LOG_IF_READY)
#define NSR_COMMON_MSG_OSFP_BFD_FINISH 0x08   /*OSPF��̬�Ự�ָ�����*/
#define NSR_COMMON_MSG_NSR_DISABLED    0x10   /*NSR�����Ѿ�ȥʹ��*/
#define NSR_COMMON_MSG_SWITCH_FINISH   0x20   /*NSR��������(���������ƽ��)*/

/*�ӿ��ϱ�״̬*/
#define NSR_IF_STATUS_NULL         0x00    /*����ӿ�Ready*/
#define NSR_IF_STATUS_PHY_READY   0x01    /*����ӿ�Ready*/
#define NSR_IF_STATUS_LOG_READY   0x02    /*�߼��ӿ�Ready*/

/*NSRʹ��/ȥʹ��״̬��������NSR����ģ��͸����Ե�NSR����*/
#define NSR_STATUS_UP           0x01    /*NSRʹ�ܲ�����*/
#define NSR_STATUS_DOWN         0x02    /*NSR�Ǽ���*/
#define NSR_STATUS_GOING_UP    0x03     /*NSRʹ����(��״̬��ʱδʹ��)*/
#define NSR_STATUS_GOING_DOWN  0x04     /*NSRȥʹ����*/

/*NSR����״̬��������NSR����ģ��͸����Ե�NSR����*/
#define NSR_SWITCH_STATUS_ACTIVE   0x01   /*NSR���ڵ���������*/
#define NSR_SWITCH_STATUS_INACTIVE 0x02   /*NSR���ڷǵ�������*/

/*��ģ��NSR��Ϣ��������������*/
typedef VOID (*NSR_SUB_MODULE_MSG_PROCESS_HOOK_FUNC)(ULONG, UCHAR *, ULONG);
/*OSPFģ�鴦��͸��NSR��Ϣ���Ӻ�������*/
typedef VOID (*NSR_MSG_PROCESS_HOOK_FUNC)(ULONG, UCHAR *, ULONG);
/*��ģ��NSRʹ��/ȥʹ�ܴ���������*/
typedef ULONG (*NSR_SUB_MODULE_SET_NSR_CAPABILITY)(UCHAR);

/*NSR COMMON�ı�������*/
typedef struct nsr_common_local
{
    BOOL_T bNSRInit;              /*NSR�Ƿ��ʼ�� 0-δ��ʼ��  1-�ѳ�ʼ��*/
    UCHAR ucNSRCapability;       /*NSR�Ƿ�ʹ��   1-ʹ��  2-��ʹ��, Ĭ��Ϊ2*/
    UCHAR ucNextNSRCapability;  /*�ӳ���Ч��NSRʹ��״̬��Ĭ��Ϊ0*/
    UCHAR ucNSRRole;              /*NSR��ɫ,Ĭ��Ϊ��*/
    UCHAR ucChannelStatus;       /*ͨ��״̬*/
    UCHAR ucSlaveBoardStatus;    /*����״̬*/
    UCHAR ucIFReadyFlag;          /*�ӿ��ϱ�������ʶ*/
    UCHAR ucIFReadyStatus;       /*�ӿ��ϱ�״̬*/
    UCHAR ucNSRStatus;           /*NSR״̬*/
    UCHAR ucNSRSwitchStatus;    /*NSR����״̬*/
    UCHAR Pad[1];
    ULONG ulNSRFlag;             /*NSR��ǣ���λʹ��*/
    DLL_S lsSubModuleList;
}NSR_COMMON_LOCAL;

typedef struct nsr_sub_module_regist
{
    ULONG ulModID;
    ULONG ulSubscribeMsg;
    UCHAR ucNSRCapability;
    UCHAR szModuleName[NSR_MODULE_NAME_MAX+1];
    UCHAR pad[2];
    NSR_SUB_MODULE_SET_NSR_CAPABILITY pfSetNSRCapabilityHook;
    NSR_SUB_MODULE_MSG_PROCESS_HOOK_FUNC pfMsgProcessHook;
}NSR_SUB_MODULE_RESIST;

typedef struct nsr_sub_module_node
{
    DLL_NODE_S stNode;
    ULONG ulModID;                /*ģ��ID*/
    ULONG ulSubscribeMsg;        /*���ĵĹ�����Ϣ����*/
    UCHAR szModuleName[NSR_MODULE_NAME_MAX+1];
    UCHAR ucNSRCapability;       /*NSRʹ��/ȥʹ�ܱ�ʶ*/
    UCHAR ucNSRStatus;           /*NSRʹ��/ȥʹ��״̬*/
    UCHAR ucNSRSwitchStatus;    /*NSR����״̬*/
    NSR_SUB_MODULE_SET_NSR_CAPABILITY pfSetNSRCapabilityHook;
    NSR_SUB_MODULE_MSG_PROCESS_HOOK_FUNC pfMsgProcessHook;
}NSR_SUB_MODULE_NODE;

typedef struct nsr_common_msg
{
    ULONG ulModID;
    ULONG ulMsgType;
    UCHAR *pMsgInfo;
}NSR_COMMON_MSG;

/*�ж��Ƿ�Ϊ����*/
#define NSR_IS_MASTER_BOARD() (g_stNSRCommonLocal.ucNSRRole == NSR_ROLE_MASTER)

/*NSR�Ƿ��ѳ�ʼ��*/
#define NSR_IS_INIT()    (g_stNSRCommonLocal.bNSRInit == BOOL_TRUE)
#define NSR_SET_INIT(RESULT)    (g_stNSRCommonLocal.bNSRInit = ((RESULT) == NSR_OK ? BOOL_TRUE : BOOL_FALSE))

/*�Ƿ�ʹ��NSR*/
#define NSR_IS_ENABLE()    (g_stNSRCommonLocal.ucNSRCapability == NSR_CAPABILITY_ENABLE)

/*�ж�NSR�����Ƿ񼤻�*/
#define NSR_IS_ACTIVE() (g_stNSRCommonLocal.ucNSRStatus == NSR_STATUS_UP)
/*�ж�NSR�����Ƿ񼤻�*/
#define NSR_IS_INACTIVE() (g_stNSRCommonLocal.ucNSRStatus == NSR_STATUS_DOWN)

/*NSR�жϽӿ��Ƿ��ϱ�����*/
#define NSR_IS_ALL_IF_READY() \
  (g_stNSRCommonLocal.ucIFReadyStatus == g_stNSRCommonLocal.ucIFReadyFlag)

/*�ж���Ϣ�Ƿ��͸�����*/
#define NSR_IS_MASTER_CONTROL_MSG(DIRECT_TYPE) \
  (((DIRECT_TYPE) & NSR_CONTROL_MSG_DEST_MASTER) && NSR_IS_MASTER_BOARD())
  
/*�ж���Ϣ�Ƿ��͸�����*/
#define NSR_IS_SLAVE_CONTROL_MSG(DIRECT_TYPE) \
    (((DIRECT_TYPE) & NSR_CONTROL_MSG_DEST_SLAVE) && !NSR_IS_MASTER_BOARD())

/*�жϿ�������Ϣ�Ƿ���Ч*/
#define NSR_IS_VALID_CONTROL_MSG(DIRECT_TYPE) \
  (((DIRECT_TYPE) & NSR_CONTROL_MSG_DIRECT_NSR) && \
  (NSR_IS_MASTER_CONTROL_MSG(DIRECT_TYPE) || \
   NSR_IS_SLAVE_CONTROL_MSG(DIRECT_TYPE)))

#define NSR_SET_IF_STATUS(IF_STATUS) \
  (g_stNSRCommonLocal.ucIFReadyStatus |= (IF_STATUS))

extern NSR_COMMON_LOCAL g_stNSRCommonLocal;
extern ULONG g_ulNSRTimerQueID;
extern NSR_MSG_PROCESS_HOOK_FUNC g_pfNSRMsgProcessHookForOSPF;
extern NSR_SEND_BACKUP_MSG_FUNC          g_pfNSRSendBackupMsg;
extern NSR_SEND_CONTROL_MSG_FUNC         g_pfNSRSendControlMsg;
extern NSR_GET_NSR_BASE_INFO_FUNC         g_pfNSRGetNSRBaseInfoHook;
extern ULONG g_ulSemForNSR;

ULONG NSR_Common_InitLocal();
VOID NSR_Common_RouteMessage(ULONG ulMsgType, UCHAR *pMsgInfo, ULONG ulMsgLen);
ULONG NSR_GetPreConfigInfo(ULONG ulKey, ULONG *pulNSRPreCfgInfo);
ULONG NSR_SendControlMsg(NSR_CONTROL_MSG *pstNSRControlMsg);
ULONG NSR_SendBackupMsg(UCHAR *pMsgBuf, ULONG ulMsgLen, BOOL_T bFirstBuf);
ULONG NSR_Common_ReceiveControlMsg(NSR_COMMON_MSG *pstNSRCommonMsg);
ULONG NSR_Common_AddModule(NSR_SUB_MODULE_RESIST *pstSubModuleRegist);
LONG NSR_Common_ModuleCmp(VOID * val, DLL_NODE_S * pNode);
VOID NSR_UpdateIfReadyFlags(NSR_SUB_MODULE_NODE *pstSubModuleNode);
ULONG NSR_GetNSRBaseInfo(NSR_BASE_INFO *pstNSRBaseInfo);
ULONG NSR_Common_GetNSRBaseInfo(UCHAR ucType, UCHAR *pucData);
ULONG NSR_EnableNSR();
ULONG NSR_DisableNSR();
VOID NSR_Common_DealNSRCapabilityMsg(NSR_COMMON_MSG *pstNSRCommonMsg);
VOID NSR_Common_DealNSRSwitchMsg(NSR_COMMON_MSG *pstNSRCommonMsg);






#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
