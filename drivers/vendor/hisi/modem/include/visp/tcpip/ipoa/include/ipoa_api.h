/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipoa_api.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2008-07-24
*        Author: wangbin62223
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-07-24   wangbin62223            Create
*
*******************************************************************************/
#ifndef _IPOA_API_H_
#define _IPOA_API_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define IPOA_IP_MAP_TYPE_IP             0x01
#define IPOA_IP_MAP_TYPE_IPWITHMASK     0x02
#define IPOA_IP_MAP_TYPE_DEFAULT        0x04
#define IPOA_IP_MAP_TYPE_INARP          0x08
#define IPOA_IP_MAP_TYPE_ALLONPVC       0xff

#define IPOA_DEBUG_FLAG_ERROR           0x0001    /* 0λ error���� */
#define IPOA_DEBUG_FLAG_EVENT           0x0002    /* 1λ event���� */
#define IPOA_DEBUG_FLAG_PACKET          0x0004    /* 3λ ip packet����*/
#define IPOA_DEBUG_FLAG_ALL             0x00ff    /* 8λ all����*/

#define IPOA_VLINK_CMD_ADD              0x01
#define IPOA_VLINK_CMD_DELETE           0x02

#define IPOA_CFG_ACTION_DELETE          0
#define IPOA_CFG_ACTION_CREATE          1


typedef enum tagIPOA_ERROR
{
    IPOA_CFG_OK,               /* 0   ������ȷ*/                                                 
    IPOA_CFG_INVALID_INPUT = MID_COMP_IPOA + 1,    /* 1   ������������*/                                             
    IPOA_CFG_INVALID_ACTION,   /* 2   ��Ч�Ĳ�������*/  
    IPOA_CFG_PARA_BEYOND,       /*3   ����Խ��*/
    IPOA_CFG_IFNET_NOT_EXIST,  /* 4   �ӿ�ָ�벻����*/                                           
    IPOA_CFG_INTF_IS_NOT_ATM,  /* 5   �ӿڲ���ATM*/                                              
    IPOA_CFG_INTF_IS_SAME_STATE ,/*6  �ӿ�״̬������״̬��ͬ*/                                              
    IPOA_CFG_INTF_NOT_EXIST ,   /* 7  �ӿڲ�����*/                                               
    IPOA_CFG_CFG_ENCAP_FAIL ,   /* 8  ���÷�װ����ʧ��*/                                         
    IPOA_CFG_SAME_ENCAP_TYPE,   /*9  ��������ͬ�ķ�װ����*/
    IPOA_CFG_ENCAP_TYPE_CONFLICT,/*10  ���õķ�װ���ͳ�ͻ */
    IPOA_CFG_NO_PVC ,           /*11  û�ж�Ӧ��PVC*/ 
    IPOA_CFG_NOT_THIS_IFTERFACE ,/*12 �Ǳ��ӿ��ϵ�PVC*/ 
    IPOA_CFG_PVC_EXIST_SAME_CB, /*13 PVC��ͬһ��CB���Ѿ�����*/
    IPOA_CFG_CREATE_PVC_FAIL,   /*14 PVC����ʧ��*/
    IPOA_CFG_PVC_STATE_SAME,    /*15 PVC״̬��ͬ*/
    IPOA_CFG_NO_MAP,           /* 16  û�ж�Ӧ��MAP*/
    IPOA_CFG_INARP_MAP_EXIST,  /* 17  ��̬MAP�Ѿ����� */
    IPOA_CFG_DEFAULT_MAP_EXIST,  /*  18  Ĭ��MAP�Ѿ����� */
    IPOA_CFG_CREATE_MAP_FAIL,  /* 19  ����MAPʧ��*/                                              
    IPOA_CFG_VPIVCI_OUTRANGE,  /*20  VPI����VCIֵ������Χ*/                                     
    IPOA_CFG_INVALID_ENCAP_TYPE,/*21  ��Ч��AAL5��װ����*/                                    
    IPOA_CFG_INVALID_MAP_TYPE,  /*22  ��Ч��MAP����*/                                         
    IPOA_CFG_INVALID_INTF,      /*23  ��Ч�Ľӿ�*/                                              
    IPOA_CFG_END_OF_TABLE ,      /* 24  ��ѯ����ĩ*/                                              
    IPOA_CFG_ALREADY_IP_MAP_TYPE , /*25  ����InARP MAPʱ�Ѿ���ATM_IP_MAP_TYPE_INARP����*/       
    IPOA_CFG_MUX_TYPE_ERR ,        /* 26  ����InARP MAPʱAAL5+MUX��װ��֧��IP InARP */          
    IPOA_CFG_NLPID_TYPE_ERR ,      /* 27 ����InARP MAPʱAAL5+NLPID��װ��֧��IP InARP */        
    IPOA_CFG_ALREADY_DFT_MAP_TYPE ,/* 28  ����Default MAPʱ�Ѿ���ATM_IP_MAP_TYPE_DEFAULT���� */ 
    IPOA_CFG_IP_CONFLICT_ERR ,     /* 29  ���ڵ�ַ��ͻ��MAP */                                
    IPOA_CFG_NO_DEBUG_TYPE,          /*30debug���ʹ���*/
    IPOA_CFG_BUFFER_NOT_ENOUGH,      /*31Buf�ռ䲻��*/
    IPOA_CFG_NULL_BUFFER,            /*32�û������bufΪ��*/
    IPOA_CFG_CLOSETABLE_FAIL,        /* 33 �رձ���ʧ�� */
    IPOA_CFG_SET_PVC_STATE_FAIL,     /*34 PVC״̬����ʧ�ܣ�ԭ���ǽӿ�״̬�Ѿ�ΪDOWN*/
    IPOA_CFG_GET_FILT_WAITLIST_FAIL,  /* 35 ��ȡ��������ʧ�� */    
    IPOA_CFG_WAITLIST_REGISTER_FAIL,   /* 36waitListע��ʧ��*/
    IPOA_CFG_BUFF_ASSEMBLE_FAIL         /* 37 buff��װʧ�� */
}IPOA_ERROR_S;

typedef enum enIPOA_CFG_PVC_ENCTYPE
{
    IPOA_AAL5_ENCAP_TYPE_DEFAULT    = 0,
    IPOA_AAL5_ENCAP_TYPE_LLC        = 1,
    IPOA_AAL5_ENCAP_TYPE_MUX        = 2   
}IPOA_CFG_PVC_ENCTYPE_E;

typedef enum enIPOA_INARP_TIME_TYPE
{
    IPOA_INARP_TIME_ONE         = 1,
    IPOA_INARP_TIME_TWO         = 2,
    IPOA_INARP_TIME_THREE       = 3,
    IPOA_INARP_TIME_FORE        = 4,
    IPOA_INARP_TIME_FIVE        = 5
}IPOA_INARP_TIME_TYPE_E;

typedef enum tagIPOA_PACKET_TYPE
{
    IPOA_PACKET_TYPE_UNKNOWN = 0x00,
    IPOA_PACKET_TYPE_IP,
    IPOA_PACKET_TYPE_INARP,
    IPOA_PACKET_TYPE_ISIS,
}IPOA_PACKET_TYPE_E;


typedef struct tagIPOA_CFG_PVC
{
    ULONG ulActionType;
    UCHAR szIfName[MAX_IF_NAME_LENGTH + 1];
    USHORT usVpi;
    USHORT usVci;
    UCHAR ucEncapType;
    UCHAR ucReserved[3];
}IPOA_CFG_PVC_S;

typedef struct tagIPOA_CFG_MAP
{
    ULONG ulActionType;
    UCHAR szIfName[MAX_IF_NAME_LENGTH + 1];
    USHORT usVpi;
    USHORT usVci;
    ULONG ulIpAddr;
    BOOL_T ucBroadcastFlag;
    UCHAR ucMapType;
    UCHAR usReserved;
}IPOA_CFG_MAP_S;

typedef struct tagIPOA_CFG_ENTRY
{
    UCHAR szIfName[MAX_IF_NAME_LENGTH + 1];
    USHORT usVpi;
    USHORT usVci;
}IPOA_CFG_ENTRY_S;



typedef struct tagIPOA_FILTER_OUTINFO
{
    UCHAR szIfName[MAX_IF_NAME_LENGTH+1];  
    ULONG ulIpAddr;                       
    ULONG ulVlinkNum;        
    USHORT usVpi;
    USHORT usVci;
    BOOL_T ucBroadcastFlag;   
    UCHAR ucMapType; 
    UCHAR usReserved;
}IPOA_FILTER_OUTINFO_S;

typedef struct tagIPOA_PKT_STAT
{
    ULONG               ulInByte;  /* �����ֽ��� */
    ULONG               ulInPkt;    /* ���ձ����� */
    ULONG               ulInPktErr; /* ���յĴ������� */
    ULONG               ulOutByte; /* �����ֽ��� */
    ULONG               ulOutPkt;   /* ���ͱ����� */
    ULONG               ulOutPktErr;/* ����ķ��ͱ����� */
    ULONG               ulQoSDropPkt; /* QoS����ӵ�����µĶ��������� */ /* Add by tianli29125, 2003/11/12, d16410 */
}IPOA_PKT_STAT_S;

typedef struct tagIPOA_PVC_PARAM
{
    ULONG                   ulVccIndex;     /* ���صײ��PVC���� */
    USHORT                  usVPI;          /* VPI */
    USHORT                  usVCI;          /* VCI */
    ULONG                   ulIfIndex;
    IPOA_PKT_STAT_S         stPktStat;
    UCHAR                   ucPVCShut;
    UCHAR                   ucEncType;
    UCHAR                   ucRes[2];    
}IPOA_PVC_PARAM_S;


ULONG TCPIP_CfgPvcProc (IPOA_CFG_PVC_S * pstPvcTable);
ULONG TCPIP_CfgMapProc(IPOA_CFG_MAP_S * pstMapTable);
ULONG TCPIP_GetInARPTime(IPOA_CFG_ENTRY_S* pstIpoaInfo,USHORT *pusTime);
ULONG TCPIP_SetInARPTime(IPOA_CFG_ENTRY_S* pstIpoaInfo,USHORT usTime);
ULONG TCPIP_ShowInARPTime(IPOA_CFG_ENTRY_S *pstIpoaInfo);
ULONG TCPIP_GetPvcEncTypeByVccIndex(ULONG ulIfIndex,ULONG ulVccIndex,UCHAR *pucEncType,ULONG *pulHeadLen);
ULONG TCPIP_GetPvcEncTypeByVpiVci(ULONG ulIfIndex,USHORT usVpi,USHORT usVci,UCHAR *pucEncType,ULONG *pulHeadLen);
ULONG TCPIP_GetPvcState(IPOA_CFG_ENTRY_S* pstIpoaInfo,ULONG *pulFlag);
ULONG TCPIP_SetPvcState(IPOA_CFG_ENTRY_S* pstIpoaInfo,ULONG ulFlag);
ULONG TCPIP_ShowPvcState(IPOA_CFG_ENTRY_S* pstIpoaInfo);
ULONG TCPIP_ProcIpoaDebug(ULONG ulDebugSet, ULONG ulDebugType, IPOA_CFG_ENTRY_S *pstIpoaDebugInfo);
ULONG TCPIP_GetIpoaDebug(CHAR *pcBuffer, ULONG ulMaxLen, IPOA_CFG_ENTRY_S *pstIpoaDebugInfo);
ULONG TCPIP_ShowAtmStat();
VOID *IPOA_GetNextEntryByFilter(VOID *pFilter,VOID *pCurEntry);
ULONG TCPIP_OpenIpoaTable( ULONG* pulWaitListHandle, IPOA_CFG_ENTRY_S* pstIpoaFilterInfo);
ULONG TCPIP_GetNextIpoaEntry( ULONG ulEntryWaitList, IPOA_FILTER_OUTINFO_S* pstIpoaFiltOutInfo );
ULONG TCPIP_CloseIpoaTable( ULONG ulWaitListHandle );
ULONG TCPIP_SetPvcPhyState(ULONG ulVlinkIndex,ULONG ulFlag,ULONG ulIfIndex);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IPOA_API_H_ */


