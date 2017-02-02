/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ethvln_api.h
*
*  Project Code: VISPV100R007
*   Module Name: Ethvlan  
*  Date Created: 2008-08-01
*        Author: qinyun(62011)
*   Description: ethvln_api.h
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME               DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-08-01   qinyun(62011)      Create the first version.
*  2008-11-18   qinyun(62011)      Modify for BC3D00737,�������Լ����ýӿ����õ�
*                                  �궨��(TagFormat,VLAN_ERR_E)Ҫ�Ƶ�APIͷ�ļ���
*******************************************************************************/
#ifndef _ETHVLN_CFGAPI_EXT_H
#define _ETHVLN_CFGAPI_EXT_H

#ifdef  __cplusplus
extern "C"{
#endif

#define  ETHVLAN_IFNAME_MAXLEN       (47)/*�ӿ�������*/
#define  ETHVLN_BUFFER_MIN_LEN       (1024)

/* Modified by s72256 for Req_201303115271  for 64 to 256*/ 
#define MAX_SUBIF_VIDNUM 256
/* Added macro for default value */
#define MAX_SUBIF_DEFAULT_VIDNUM 64

#define  ETHVLAN_OP_ADD             (1)     /*���Ӳ���*/
#define  ETHVLAN_OP_DEL             (0)     /*ɾ������*/

#define  ETHVLAN_DBG_SET            (1)     /*����debug����*/
#define  ETHVLAN_DBG_DEL            (0)     /*ȡ��debug����*/

#define  ETHVLAN_BUFFER_MIN_SIZE    (1024)  /*��ʾvlan debug��Ϣ����Сbuffer��С*/

#define ETHVLAN_NOT_PROCESSED_BY_INTERMEDIATE 0  
#define ETHVLAN_PROCESSED_BY_INTERMEDIATE     1  

/* sup** vlan�ӿ���С��Ҫ֧�ֵ�VLAN����,��һ���ӿ�������Ҫ���õĸ������������ϵ�vlan����su**r vlan�ӿ� */
#define ETHVLAN_MIN_SUPERVLAN 2

enum TagFormat
{
    ETHVLAN_NONE = 0, 
    ETHVLAN_ISL = 1,            /*δ֧��*/
    ETHVLAN_DOT1Q = 2,          /*802.1q VLAN*/
    ETHVLAN_ALLTAG = 3          /*δ֧��*/
};

typedef enum SubIfErrorCode
{
    ETHVLN_OK,
    ETHVLN_ERR = MID_COMP_VLAN + 1,     /*1 ��ȡ����VLAN���ƿ�*/               
    ETHVLN_ERR_INVALID_POINTER,         /*2 ��Чָ�� */
    ETHVLN_ERR_INVALID_PARAM_VALUE,     /*3 ��Ч����ֵ */
    ETHVLN_ERR_VID,                     /*4 VLAN ID������Ч��Χ��*/
    ETHVLN_ERR_VID_RANGE,               /*5 ���û�ɾ����VLAN�������*/
    ETHVLN_ERR_MAXNUM_VID,              /*6 VLAN ID���������*/
    ETHVLN_ERR_VIDNOEXIST,              /*7 ��VLAN ID��ϵͳ�в�����*/
    ETHVLN_ERR_IF,                      /*8 ����������ȡ�����ӿڻ���ݽӿ�����ȡ�ӿ�����ʧ��*/
    ETHVLN_ERR_GET_MAINIF,              /*9 ��ȡ���ӿ�ʧ��*/
    ETHVLN_ERR_SUBIF,                   /*10 �ӽӿڲ����ڻ��ӽӿ�״̬ΪDown*/
    ETHVLN_ERR_ALREADY_PRESENT,         /*11 �ӽӿڻ����ӿ��Ѿ����ڸ�VLAN ID*/
    ETHVLN_ERR_SUBIF_NOVID,             /*12 �ӿڲ����ڸ�VLAN ID*/
    ETHVLN_ERR_IF_NOCFG_VID,            /*13 �ӿ�δ�����κ�VLAN ID*/
    ETHVLN_ERR_NOT_ETH_TYPE,            /*14 �ӿڷ�eth����*/
    ETHVLN_ERR_IS_TRUNKPORT,            /*15 �ӿ���TRUNK��Ա�˿�*/
    ETHVLN_ERR_ENCAPTYPEERROR,          /*16 ��װ���������ò�һ�£���ǰ��֧��802.1Q*/
    ETHVLN_ERR_WAITLIST,                /*17 WAITLISTע��ʧ��*/
    ETHVLN_ERR_MEM,                     /*18 �����ڴ�ʧ��*/
    ETHVLN_ERR_MBUF,                    /*19 MBUF����ʧ��*/
    ETHVLN_ERR_ENABLE_OTH_VLAN_FUNC,    /*20 ��ʹ��������VLAN����*/              
    ETHVLN_END_OF_TABLE,                /*21 ��ѯ����β*/
    ETHVLN_ERR_DISABLE,                 /*22 ģ��δ��ʼ��*/
    ETHVLN_ERR_GETWAITLISTPARA,         /*23 ��ȡwaitlist����ָ��ʧ�� */
    ETHVLN_ERR_BUF_NOT_ENOUGH,          /*24 Buf�ռ䲻�� */
    ETHVLN_ERR_HA_WAITLIST_OPEN,        /*25 ��ETH VLAN HA waitlist ʧ�� */
    ETHVLN_ERR_HA_ABNORMAL,             /*26 HA�����ڲ��쳣 */
    ETHVLN_ERR_HA_TYPE,                 /*27 HA���ݲ�ʶ������ */
    ETHVLN_ERR_HA_SMOOTH,               /*28 ���ڽ����ֶ�������ƽ������ */
    ETHVLN_ERR_HA_MEM_SMALL,            /*29 HA�����ڴ�̫С */
    ETHVLN_ERR_HA_WRITE_QUE,            /*30 дHA����ʧ�� */
    ETHVLN_ERR_HA_WAITLIST_NULL,        /*31 ��waitlist�����ȡ����Ϊ�� */
    ETHVLN_ERR_INVLAD_WARNING_NUM,      /* 32 �趨VLAN��һ�¸澯�����Ƿ� */
    ETHVLN_ERR_VIRTUAL_IF,              /* 33 �Ǳ���ӿ� */
    ETHVLN_NO_SPECIFY_VLAN_WARNING,     /* 34 ָ����VLANһ���Ը澯������ */
        
    ETHVLN_ERR_MAX
}VLAN_ERR_E;

#pragma pack(1)
typedef  struct  tagDot1qHdr
{
    UCHAR       aucDestAddr[6];       /* Destination physical address */
    UCHAR       aucSrcAddr[6];        /* Source physical address */
    USHORT      usTPID ;              /* 802.1q Protype 8100 */
    USHORT      usTCI ;               /*user User_priority CFI VLANID */
    USHORT      usLenEtype;           /* Length or the type field */
}ETHVLAN_DOT1QHDR_S;

typedef struct stDot1qHdr
{
    USHORT      usEType;            /* To identify the physical layer */	
    USHORT      usVID;              /* The priority level,CFI and VID */
}VLAN_DOT1QHDR_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif



/*����ɾ��vlan API*/
typedef struct tagEthVlanOp
{    
    ULONG     ulOperType;                           /*1�����ӣ�0��ɾ��*/
    UCHAR     szIfName[ETHVLAN_IFNAME_MAXLEN + 1];  /*�ӽӿ���*/
    USHORT    usLowVid;                             /*vlan id*/
    USHORT    usHighVid;                            /*0����ʾ���Ӷ�Ӧ��vlan��usLowVid��
                                                      ��0����ʾ���Ӷ�Ӧ��vlan��usLowVid��usHighVid*/
    ULONG     ulTagType;                            /*0:ȱʡֵ��802.1q ��  2��802.1q */ 
} ETHVLAN_OP_S;

/*��ѯvlan��������*/
typedef struct tagEthVlanShowFilter
{    
    ULONG  ulIfIndex;                               /*��Ӧ�ӽӿ�����*/
    USHORT usVlanID;                               /* Vlan ID */
    USHORT usPadding;
} ETHVLAN_FILTER_S;                             

/*��ѯvlan��Ϣ������*/
typedef struct tagEthVlanIntf
{    
    ULONG     ulIfIndex;                            /*��Ӧ�ӽӿڵĽӿ�����*/
    ULONG     ulTotalVlnNum;                        /*���ӽӿ��²�ѯ����vlan����*/
    USHORT    usVid[MAX_SUBIF_VIDNUM];              /*��Ŷ�Ӧ����vlan id��ֵ*/
} ETHVLAN_INTF_S;

/*�洢��ѯvlanͳ�ƵĽ��*/
typedef struct tagEthVlanStat
{    
    ULONG  ulReceivePacketCount;                    /*�յ��ı�������*/
    ULONG  ulTransmitPacketCount;                   /*���͵ı�������*/
    ULONG  ulReceiveByteCount;                      /*�յ��ı����ֽ���*/
    ULONG  ulTransmitByteCount;                     /*���͵ı����ֽ���*/
    
    ULONG  ulRecvMainMbufErr;                       /*���ӿڽ��ձ���MBUF����ʧ��*/
    ULONG  ulRecvMainInvalidVid;                    /*���ӿڽ��ղ���ȷ��VLAN ID���ĸ���*/
    ULONG  ulRecvSubInvalidStat;                    /*�ӽӿ�״̬�쳣ʱ���ձ��ĸ���*/
    ULONG  ulRecvSubInvalidEncapType;               /*�������ӽӿ�VLAN���Ͳ����ĸ���*/
    ULONG  ulSendSubMbufErr;                        /*�ӽӿڷ��ͱ���MBUF����ʧ�ܸ���*/
    ULONG  ulSendSubInvalidVid;                     /*���ͱ���ָ����VLAN ID���ӽӿ����ò�ͬ�ĸ���*/
    ULONG  ulSendSubPhyErr;                         /*�ӽӿڷ��ͱ�������㷵��ʧ�ܸ���*/
} ETHVLAN_STAT_S;

/* Begin Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. �޸�ԭ��: ֧��VLAN���ò�һ�µĸ澯 */
/* VLANһ���Ը澯���ֵ */
#define ETHVLAN_MAX_WARNING_NUM  128
/* VLANһ���Ը澯���� */
#define ETHVLAN_CONSISTENCY_WARNING_BEGIN  1
/* VLANһ���Ը澯���� */
#define ETHVLAN_CONSISTENCY_WARNING_END  0

/* VLAN��һ�¸澯����ԭ�� */
typedef enum enVlanConsitencyWarningRecoverReason
{
    VLAN_WARNING_REMOTE_MODIFY_VLAN = 1,    /* �Զ��޸�VLAN���úͱ���һ�� */
    VLAN_WARNING_LOCAL_MODIFY_VLAN,         /* �����޸�VLAN���úͱ���һ�� */
    VLAN_WARNING_SUBIF_IS_DELETED,          /* �ӽӿڱ�ɾ�� */
    VLAN_WARNING_IP_IS_DELETED,             /* �ӽӿ�ɾ����IP */
    VLAN_WARNING_NUM_DECREASE,              /* �澯�ڵ����С,����ȥʹ��VLANһ���Լ��Ӹ澯����,�����澯��������Ϊ0 */
    VLAN_WARNING_USER_DELETED,              /* �û�ɾ���澯 */
    VLAN_WARNING_MAX,                       /* �澯�����ֶ���Чֵ */
}VLAN_CONSISTENCY_WARNING_RECOVER_REASON_E;

/* VLAN��һ�¸澯��Ϣ */
typedef struct tagVlanConsistencyWarning
{
    ULONG   ulSubIfIndex;                   /* �ӽӿ����� */
    ULONG   ulTotalVlanNum;                 /* �ӽӿڼ����VLAN���� */
    USHORT  usVid[MAX_SUBIF_VIDNUM];        /* ����ӽӿڵ�ǰ����ĸ���VLAN ID */
    ULONG   ulLocalIPAddr;                  /* ����IP, ������ */
    ULONG   ulNeighbourIPAddr;              /* �ھ�IP, ������ */
    USHORT  usNeighbourVlanID;              /* �澯ʱ��ʾ�ھ�����VLAN */
    UCHAR   ucEventType;                    /* �澯����:ETHVLAN_CONSISTENCY_WARNING_BEGIN; �澯����:ETHVLAN_CONSISTENCY_WARNING_END; */
    UCHAR   ucRecoverReason;                /* �澯������ԭ��,�μ�VLAN_CONSISTENCY_WARNING_RECOVER_REASON_Eö�ٶ��� */
}VLAN_CONSISTENCY_WARNING_S;
/* End Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. �޸�ԭ��: ֧��VLAN���ò�һ�µĸ澯 */

typedef struct tagETHVLAN_BCPKT_PARA
{
    MBUF_S *pstMBuf;
}ETHVLAN_BCPKT_PARA_S;
typedef ULONG (*ETHVLAN_BCPKT_HOOK_FUNC)(ETHVLAN_BCPKT_PARA_S *pstPara);

typedef ULONG(*ETHVLAN_TOS_TO_VLAN_PRIORITY)(MBUF_S *pMbuf,ULONG *pPriority);

extern ULONG ETHVLAN_CreateDelVlan( ETHVLAN_OP_S* pstVLAN );
extern ULONG ETHVLAN_GetVlanStat( UCHAR* pcIfName, USHORT usVID,ETHVLAN_STAT_S* pstVlnStat );
extern ULONG ETHVLAN_ResetVlanStat( UCHAR* pcIfName, USHORT usVID );
extern VOID ETHVLAN_ShowVlanStat( UCHAR *pcIfName, USHORT usVid);
extern ULONG ETHVLAN_SetVlanDebug( ULONG ulDebugSet, UCHAR *pcIfName, USHORT usVid );
extern ULONG ETHVLAN_GetVlanDebug(CHAR *pcBuffer, ULONG ulMaxLen, ETHVLAN_FILTER_S *pstFilter);
extern VOID ETHVLAN_SetVlanErrDebug( BOOL_T bErrDbg );
extern VOID ETHVLAN_ShowVlanDebug( UCHAR *pcIfName, USHORT usVid );
extern VOID ETHVLAN_RegTos2VlanPriorityHook(ETHVLAN_TOS_TO_VLAN_PRIORITY pfFunHook);
extern VOID ETHVLAN_ShowVlanCfg( UCHAR *pName );
extern ULONG ETHVLAN_TableOpen( UINTPTR* pulWaitListHandle, ETHVLAN_FILTER_S* pstVlan );
extern ULONG ETHVLAN_TableClose( UINTPTR pulWaitListHandle );
extern ULONG ETHVLAN_GetNext( UINTPTR ulEntryWaitList, ETHVLAN_INTF_S* pstVlanIntf );

extern ULONG TCPIP_ETHVLAN_dot1qInput(MBUF_S * pstMbuf,ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SetVlanConsistencyMonitor
* Date Created: 2011-06-04
*       Author: zhaoyue00171897/shuxieliu00176784
*  Description: ����VLANһ���Ը澯���ӿ���
*        Input: ULONG ulSubIfIndex:  �ӽӿ�����
*               ULONG ulMaxWarningNum: ���ӽӿ���ͬʱ���ڵĸ澯��������
*       Output: 
*       Return: ETHVLN_OK        �ɹ�
*               ����             ʧ��
*      Caution: ulSubIfIndex ֻ��Ϊ ethernet��trunk �ӽӿ�
*               ulMaxWarningNum ��ΧΪ[0, 128]��Ĭ����0����ʾ��ʹ�ܸ澯����
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-04   zhaoyue00171897         Create
*
*******************************************************************************/
ULONG TCPIP_SetVlanConsistencyMonitor(ULONG ulSubIfIndex, ULONG ulMaxWarningNum);

/*******************************************************************************
*    Func Name: TCPIP_GetVlanConsistencyMonitor
* Date Created: 2011-06-04
*       Author: zhaoyue00171897/shuxieliu00176784
*  Description: ��ȡVLANһ���Ը澯���ӿ���
*        Input: ULONG ulSubIfIndex:  �ӽӿ�����               
*       Output: ULONG *pulMaxWarningNum: ���ӽӿ���ͬʱ���ڵĸ澯��������
*       Return: ETHVLN_OK        �ɹ�
*               ����             ʧ��
*      Caution: ulSubIfIndex ֻ��Ϊ ethernet��trunk �ӽӿ�
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-04   zhaoyue00171897         Create
*
*******************************************************************************/
ULONG TCPIP_GetVlanConsistencyMonitor(ULONG ulSubIfIndex, ULONG *pulMaxWarningNum);

/*******************************************************************************
*    Func Name: TCPIP_DeleteVlanConsistencyWarning
* Date Created: 2011-06-04
*       Author: zhaoyue00171897/shuxieliu00176784
*  Description: ��������VLAN���ò�һ�¸澯
*        Input: ULONG ulSubIfIndex:  �ӽӿ�����
*               ULONG ulLocalIPAddr: ����IP,������
*               ULONG ulNeighbourIPAddr: �ھ�IP,������
*       Output: 
*       Return: ETHVLN_OK        �ɹ�
*               ����             ʧ��
*      Caution: ulSubIfIndex ֻ��Ϊ ethernet��trunk �ӽӿ�
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-04   zhaoyue00171897         Create
*
*******************************************************************************/
ULONG TCPIP_DeleteVlanConsistencyWarning(ULONG ulSubIfIndex, ULONG ulLocalIPAddr, ULONG ulNeighbourIPAddr);


VOID TCPIP_ShowVlanConsistencyWarningInfo(ULONG ulSubIfIndex);


ULONG TCPIP_RegFuncBroadcastVlanPktHook(ETHVLAN_BCPKT_HOOK_FUNC  pfEthvln_BCPkt_Hook);

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif 

