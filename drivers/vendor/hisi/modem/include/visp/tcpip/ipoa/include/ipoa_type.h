/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipoa_type.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2008-07-24
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-07-24   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _IPOA_TYPE_H_
#define _IPOA_TYPE_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define IPOA_PVC_HASH_SIZE               256
#define IPOA_MAX_VC_NAME_LEN             16

typedef struct tagIPOA_CB
{
    DLL_NODE_S              stNode;         /* CB����ڵ� */
    struct tagIPOA_PKT_STAT stPktStat;     /* �˿ڱ���ͳ�� */
    DLL_S                   stIntfHead;     /* �ӽӿ�����ͷ */
    DLL_S                   stPVCHead;      /* PVC����ͷ */
    DLL_S                   stPVCHash[IPOA_PVC_HASH_SIZE];/* ��ϣ�� */
    ULONG                   ulIfIndex;      /* �˿�IFNET���� */
    ULONG                   ulMapCount;     /* CB�ϵ�MAP������ */    
    UCHAR                   ucPhyState;     /* �����״̬ */
    UCHAR                   ucRes[3];
    ULONG ulReserved1;
    ULONG ulReserved2;

}IPOA_CB_S;


typedef struct tagIPOA_INTERFACE
{
    DLL_NODE_S              stNode;         /* �ӽӿ�����ڵ� */
    DLL_S                   stPVCHead;      /* PVC����ͷ */
    struct tagIPOA_PVC      *pstDefaultPVC; /* ����default MAP��PVCָ�� */
    struct tagIPOA_PVC      *pstInArpPVC;  /* ���ж�̬ MAP��PVCָ�� */    
    struct tagIPOA_CB       *pstIpoaCB;         /* CBָ�� */
    struct tagIPOA_PKT_STAT stPktStat;      /* �ӽӿڱ���ͳ�� */
    ULONG                   ulMapCount;     /* �ӽӿ��ϵ�MAP���� */
    ULONG                   ulDebugFlag;
    ULONG                   ulIfIndex;      /* �ӽӿ�IFNET���� */
    BOOL_T                  bShutdown;      /* �Ƿ�shutdown */
    UCHAR                   ucPhyState;     /* �ӽӿ�״̬ */
    UCHAR                   ucReserve[1];
    ULONG ulReserved1;
    ULONG ulReserved2;
}IPOA_INTERFACE_S;


typedef struct tagIPOA_PVC
{
    DLL_NODE_S                  stNode;         /* �ӽӿ�PVC����ڵ� */
    DLL_NODE_S                  stCBNode;       /* CB PVC����ڵ� */
    DLL_NODE_S                  stHashNode;     /* CB�ϵ�PVC��ϣ����ڵ� */
    USHORT                      usVPI;          /* VPI */
    USHORT                      usVCI;          /* VCI */
    ULONG                       ulVccIndex;     /* �ײ��PVC���� */
    DLL_S                       stIPMapHead;    /* IP MAP */
    struct tagIPOA_MAP_IP       *pstInARPMap;   /* ָ��PVC��InARP MAP��û��ΪNULL */
    struct tagIPOA_MAP_IP       *pstDefaultMap; /* ָ�����default���Ե�IP MAP��û��ΪNULL */
    struct tagIPOA_INTERFACE    *pstIpoaIntf;    /* �����ӽӿ�ָ�� */

    struct tagIPOA_PKT_STAT     stPktStat;      /* PVC����ͳ�� */
    ULONG                       ulDebugFlag;    /* VC DEBUG���� */
    BOOL_T                      bShutdown;      /* �Ƿ�shutdown */
    UCHAR                       ucPhyState;     /* PVC����״̬����ʹ�ú�ATM_PVCSTATE�ж�PVC״̬ */
    UCHAR                       ucEncType;      /* ��װ���� */
    ULONG                       ulLastChange;   /* ���뵱ǰ״̬��ʱ�� */
    UCHAR                       if_szDescript[ MAX_INTERFACE_DESCRIPTION_LEN+1 ];
    UCHAR                       ucRes[3];
    ULONG ulReserved1;
    ULONG ulReserved2;
}IPOA_PVC_S;

typedef struct tagIPOA_INARP_PARAM
{
    USHORT      usMinute;       /* InARP���� */
    UCHAR       ucRes[2];    
}IPOA_INARP_PARAM_S;

typedef struct tagIPOA_INARP_WORK
{
    ULONG       ulTimerID;      /* ��ʱ��ID */
    BOOL_T      bTimerOn;       /* ��ʱ���Ƿ����� */
    USHORT      usMinute;       /* ���ڵĶ�ʱ��������� */
    UCHAR       ucState;        /* InARP״̬: �ȴ�Ӧ���յ�Ӧ���յ����� ����Ӧ�� */
    UCHAR       ucRes[3];    
}IPOA_INARP_WORK_S;


typedef struct tagIPOA_MAP_IP
{
    DLL_NODE_S                  stNode;         /* PVC��IP MAP����ڵ� */
    ULONG                       ulMask;         /* ���� */
    BOOL_T                      bBroadcast;     /* �Ƿ�֧�ֹ㲥 */
    UCHAR                       ucType;         /* MAP����: IP/InARP/Default */
    UCHAR                       ucState;        /* MAP״̬����VC״̬ͬ�� */
    ULONG                       ulIPAddr;       /* ��ַ�������ֽ��� */
    ULONG                       ulVLinkIndex;   /* VLINK���� */
    struct tagIPOA_INARP_PARAM  stInARPParam;   /* InARP���ò��� */
    struct tagIPOA_INARP_WORK   stInARPWork;    /* InARP�������� */
    struct tagIPOA_PVC          *pstPVC;        /* PVCָ�� */
    UCHAR                       if_szDescript[ MAX_INTERFACE_DESCRIPTION_LEN+1 ];
    UCHAR                       ucRes[3];
    ULONG ulReserved1;
    ULONG ulReserved2;
}IPOA_MAP_IP_S;


typedef struct tagIPOA_INARP_PACKET_FIXED
{
    USHORT usHrd;   /* Ӳ������ */
    USHORT usPrt;   /* Э������ */

    UCHAR  ucShtl;  /* ����ATM����(bit7)��ATM���볤�� */
    UCHAR  ucSstl;  /* ����ATM�ӵ�ַ����(bit7)��ATM�ӵ�ַ���� */

    USHORT usOp;    /* ������: ����Ӧ��NAK */

    UCHAR  ucSpln;  /* ����Э���ַ���� 0/4 */
    UCHAR  ucThtl;  /* �Զ�ATM����(bit7)��ATM���볤�� */
    UCHAR  ucTstl;  /* �Զ�ATM�ӵ�ַ����(bit7)��ATM�ӵ�ַ���� */
    UCHAR  ucTpln;  /* �Զ�Э���ַ���� 0/4 */

}IPOA_INARP_PACKET_FIXED_S;


typedef ULONG (*IPOAGetMap_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulIpAddr, IPOA_MAP_IP_S *pstIpoaMap);
/*Add for BC3D00792,DR.131��ȡ��·��״̬*/
typedef ULONG (*IPOAGetLinkStatus_HOOK_FUNC)(ULONG ulIfIndex,ULONG *pulLinkSatus);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IPOA_TYPE_H_ */



