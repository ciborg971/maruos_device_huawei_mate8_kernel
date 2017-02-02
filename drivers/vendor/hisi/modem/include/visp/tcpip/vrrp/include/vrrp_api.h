/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              vrrp_api.h
*
*  Project Code: VISPV1R7
*   Module Name: VRRP
*  Date Created: 2008-01-12
*        Author: wuhailan
*   Description: vrrpģ������ṩapi�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-------------------------------------------------------------------------------
*  2008-10-18  wuhailan         Create the first version.
*
*******************************************************************************/
#ifndef _VRRP_API_H_
#define _VRRP_API_H_

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************
 * �����붨��:                                                                 *
 *******************************************************************************/
/* VRRPģ������붨�� */
typedef enum enumVrrpErrCode
{
    VRRP_OK = VOS_OK,                   /* 0 OK    */
    VRRP_ERR,                           /* 1 δ֪���� */

    VRRP_ERR_NO_REGISTER = MID_COMP_VRRP + 1,   /* 2 ���δ��ʼ��, ֵ��0x0e3a0001��238682113��ʼ */
    VRRP_ERR_MALLOC_FAIL,               /* 3 �����ڴ�ʧ�� */
    VRRP_ERR_INVALID_VRID,              /* 4 ��Ч��VRID������VRID����Ч�Է�Χ */
    VRRP_ERR_NULL_IFNET,                /* 5 �ӿ�ΪNULL */
    VRRP_ERR_INVALID_IFTYPE,            /* 6 ��Ч�Ľӿ����� */
    VRRP_ERR_VRID_REPEAT,               /* 7 ͬһ��vrid�����ڶ���ӿ��ϴ��� */
    VRRP_ERR_MAX_ROUTERNUM_PERPORT,     /* 8 ����ÿ���˿�����������·������Ŀ */
    VRRP_ERR_SUBIF,                     /* 9 ��������ӽӿڽ��в��� */
    VRRP_ERR_STANDBY_NOEXIST,           /* 10 �����鲻���ڣ�VRID��Ч�����ǲ����ڶ�Ӧ�ı����� */
    VRRP_ERR_INVALID_IPADDR,            /* 11 ��ַ�Ƿ� */
    VRRP_ERR_NOTSAMENET,                /* 12 ��IP��ӿ�����IP����ͬһ���� */
    VRRP_ERR_IP_IN_OTHER_STANDBY,       /* 13 ���ַ�Ѿ�����������ı������� */
    VRRP_ERR_IP_CONFLIC,                /* 14 ��IP�������ӿڵ�ַ��ͻ */
    VRRP_ERROR_ADDRESS_TOO_MANY,        /* 15 �����������õ����ַ�ﵽ���ֵ */
    VRRP_ERR_NOOWNER,                   /* 16 ����IPOWNER*/
    VRRP_ERR_PPINOTREGISTER,            /* 17 PPI�ӿ�δע��,�·�PPIʧ�� */
    VRRP_ERR_INVALIDTYPE,               /* 18 ���������ʹ��� */
    VRRP_ERR_NULLPOINTER,               /* 19 ����ָ��Ϊ�� */
    VRRP_ERR_PARAWRONG,                 /* 20 �������Ϸ� */
    VRRP_ERR_IP_NOINSTANDBY,            /* 21 ��IP���ڱ������� */
    VRRP_ERR_IN_NO_PREEMPT,             /* 22 �ڲ�����ռ��ʱ��������delay time */
    VRRP_ERR_REDUCED,                   /* 23 ���ȼ�����ֵ���Ϸ� */
    VRRP_ERR_CANNOT_TRACK_ITSELT,       /* 24 �����鲻�ܼ��������ڵĽӿ� */
    VRRP_ERR_TRACK_INTERFACE_TOO_MANY,  /* 25 Ҫ���ӵĽӿ������������ֵ */
    VRRP_ERR_TRACK_INTERFACE_NOT_EXIST, /* 26 Ҫȡ�����ӵĽӿڲ����� */
    VRRP_ERR_1AG_NO_REGISTER,           /* 27 δ��ʼ��1agģ�� */
    VRRP_ERR_MEPIDWRONG,                /* 28 �����mep id���Ϸ� */
    VRRP_ERR_SETFLAG,                   /* 29 �����ʹ�ܱ�־���Ϸ� */
    VRRP_ERR_TRACK_1AG_TOO_MANY,        /* 30 Ҫ���ӵ�1AG�Ự���������ֵ */
    VRRP_ERR_TRACK_1AG_NOT_EXIST,       /* 31 Ҫȡ�����ӵ�1AG�Ự������ */
    VRRP_ERR_TRACK_3AH_NOT_EXIST,       /* 32 3ah�Ự������ */
    VRRP_ERR_3AH_NO_REGISTER,           /* 33 δ��ʼ��3ahģ�� */
    VRRP_ERR_TRACK_3AH_TOO_MANY,        /* 34 Ҫ���ӵ�3AH�Ự���������ֵ */
    VRRP_ERR_AUTHKEY_TOO_LONG,          /* 35 ��֤�ֳ��ȳ��������ֵ */
    VRRP_ERR_AUTHKEY_ZERO,              /* 36 ��֤�ֳ��Ȳ���Ϊ0 */
    VRRP_ERR_TRACK_1AG_NAME_LEN,        /* 37 1ag��md,ma���ֳ��ȴ��� */
    VRRP_ERR_TRACK_1AG_GET_RMEP_STATUS, /* 38 ��ȡrmep״̬ʧ�� */
    VRRP_ERR_BFDSESSIONID,              /* 39 ����BFD�������ܵ�BFD SESSION ID�Ƿ� */
    VRRP_ERR_TRACK_BFD_TOO_MANY,        /* 40 Ҫ���ӵ�BFD�Ự�����������ֵ */
    VRRP_ERR_TRACK_BFD_GETSESSIONFAIL,  /* 41 ��ȡҪ���ӵ�BFD�Ựʧ�� */
    VRRP_ERR_TRACK_BFD_NOTREGISTERHOOK, /* 42 BFDδע�����BFD�Ự�Ƿ���ڵĹ��� */
    VRRP_ERR_TRACK_BFD_NOT_EXIST,       /* 43 Ҫɾ�����ӵ�BFD�Ự������ */
    VRRP_ERR_STATE_INITIALIZE,          /* 44 �����鴦���ʼ��״̬ */
    VRRP_ERR_VRFNOTREG_INVALIDINDEX,    /* 45 VRF���δע��ʱ�����vrf������Ϊ0 */
    VRRP_ERR_INVALIDVRFINDEX,           /* 46 VRF�����Ƿ� */

    VRRP_ERR_MAXCODE                    /* �������� */
}VRRP_ERRCODE_E;

/*******************************************************************************
 * �궨��:                                                                     *
 *******************************************************************************/
#define VRRP_VIRTUAL_IP_ADDRESS_MAX             16
#define VRRP_TRACK_MAX                          8
#define VRRP_AUTHENTICATION_KEY_LENGTH          8

/* ÿ���˿����������ⱸ������Ŀ */
#define VRRP_MAX_ROUTERNUM_PERPORT              14

/* ���MD MA���ֳ��� */
#define VRRP_MAX_MDNAME_LEN                     43
#define VRRP_MAX_MANAME_LEN                     43

/* vrrp��¼�Ľӿ�״̬ */
#define VRRP_IF_UP                              1
#define VRRP_IF_DOWN                            2
#define VRRP_IF_DELETE                          3

/* vrrp ���ӵ�1ag�Ự�Ƿ��и澯 */
#define VRRP_1AG_NO_WARNING                     0
#define VRRP_1AG_WARNING                        1

/* vrrp��¼��3ah�Ự״̬ */
#define VRRP_3AH_UP                              0
#define VRRP_3AH_DOWN                            1

/* vrrp��¼��BFD�Ự״̬ */
#define VRRP_BFD_STATE_UP                       0
#define VRRP_BFD_STATE_DOWN                     1
#define VRRP_BFD_SESSION_DELETE                 2

/* VRRPʹ�ܱ�־ */
#define VRRP_DISABLE                           0
#define VRRP_ENABLE                            1

/* ״̬����״̬ */
#define VRRP_STATE_INITIALIZE                   1
#define VRRP_STATE_BACKUP                       2
#define VRRP_STATE_MASTER                       3

/*******************************************************************************
 * ö�ٶ���:                                                                   *
 *******************************************************************************/
/* VRRP�������� */
typedef enum enVRRP_DEBUG_TYPE
{
    VRRP_DEBUG_PACKET,
    VRRP_DEBUG_ERROR,
    VRRP_DEBUG_STATE,
    VRRP_DEBUG_EVENT,
    VRRP_DEBUG_ALL
}VRRP_DEBUG_TYPE_E;

/* VRRP״̬�л������ */
typedef enum enVRRP_STATE_CHANGE_DIAG
{
    /* 0, ��ʼ��ֵ */
    VRRP_STATE_DIAG_NONE,
    /* 1, init->master: �������״��������IP���Ҹ�IP�ǽӿ���ʵIP */
    VRRP_ADD_REAL_IP,
    /* 2, init->master: ���������ڽӿ�up���ұ�������ĳ������IP�ǽӿ��ϵ���ʵIP */
    VRRP_IF_UP_WITH_REAL_IP,

    /* 3, init->backup: �������״��������IP���Ҹ�IP���ǽӿڵ���ʵIP */
    VRRP_ADD_VIRTUAL_IPADDR,
    /* 4, init->backup: ���������ڽӿ�up���ұ������������IP�����ǽӿ��ϵ���ʵIP */
    VRRP_IF_UP_WITH_VIRTUAL_IP,

    /* 5, master->init: ������ɾ�������һ������IP���ҵ�ǰ״̬Ϊmaster */
    VRRP_DEL_LAST_IP_MASTER,
    /* 6, master->init: ������ɾ������������IP���ҵ�ǰ״̬Ϊmaster */
    VRRP_DEL_ALL_IP_MASTER,
    /* 7, master->init: �ӿ�down���ҵ�ǰ״̬Ϊmaster */
    VRRP_DEL_IF_DOWN_MASTER,

    /* 8, master->backup: master��backup��ռ */
    VRRP_BE_PREEMPTED,

    /* 9 ,backup->init: ������ɾ�������һ������IP���ҵ�ǰ״̬Ϊbackup */
    VRRP_DEL_LAST_IP_BACKUP,
    /* 10,backup->init: ������ɾ������������IP���ҵ�ǰ״̬Ϊbackup */
    VRRP_DEL_ALL_IP_BACKUP,
    /* 11,backup->init: �ӿ�down���ҵ�ǰ״̬Ϊbackup */
    VRRP_DEL_IF_DOWN_BACKUP,

    /* 12,backup->master: master�����˳�����״̬���ҵ�ǰbackup�����ȼ�����master����ʱ������ռ */
    VRRP_MASTER_QUIT_IMMEDIATE,
    /* 13,backup->master: backup��⵽master��ʱ�Ӷ���Ϊmaster */
    VRRP_MASTER_UNUSABLE,
    /* 14,backup->master: backup��⵽master��ʱ��������delay������£�
       �����ǰʱ�̾����ϴ��յ�master���ĵ�ʱ���Ѿ�����һ��masterͨ��������������Ϊmaster */
    VRRP_MASTER_UNUSABLE_DELAY,

    /* 15,backup->master: ���ӵĽӿ�״̬�仯���±��������ȼ��仯���Ӷ���backup��Ϊmaster */
    VRRP_TRACK_IF,
    /* 16,backup->master: ���ӵ�BFD״̬�仯���±��������ȼ��仯���Ӷ���backup��Ϊmaster */
    VRRP_TRACK_BFD,
    /* 17,backup->master: ���ӵ�1AG״̬�仯���±��������ȼ��仯���Ӷ���backup��Ϊmaster */
    VRRP_TRACK_1AG,
    /* 18,backup->master: ���ӵ�3AH״̬�仯���±��������ȼ��仯���Ӷ���backup��Ϊmaster */
    VRRP_TRACK_3AH
}VRRP_STATE_CHANGE_DIAG_E;

/* VRRP״̬ת��ʱ֪ͨ�û��Ĺ��Ӻ���ԭ��
ULONG ulIfIndex     :�ӿ�����
ULONG ulVRID        :������ID
ULONG ulChangeType  :״̬ת������
ULONG ulDiagnostic  :�����,��ʾ״̬ת���ԭ��,�μ�VRRP_STATE_CHANGE_DIAG_E */
typedef VOID (*TCPIP_VRRP_NOTIFY_STATE)(ULONG ulIfIndex, ULONG ulVRID,
                                        ULONG ulChangeType, ULONG ulDiagnostic);

/* ״̬�仯���� */
#define VRRP_TRANSITION_NO                      0
#define VRRP_TRANSITION_INITIALIZE_TO_BACKUP    1
#define VRRP_TRANSITION_INITIALIZE_TO_MASTER    2
#define VRRP_TRANSITION_BACKUP_TO_INITIALIZE    3
#define VRRP_TRANSITION_BACKUP_TO_MASTER        4
#define VRRP_TRANSITION_MASTER_TO_INITIALIZE    5
#define VRRP_TRANSITION_MASTER_TO_BACKUP        6

/*******************************************************************************
 * ���ݽṹ����:                                                               *
 *******************************************************************************/
/* VRRP����ͳ����Ϣ�ṹ */
typedef struct tagTCPIP_VRRP_STATISTICS
{
    ULONG ulErrorSum;          /* У�������ܵĴ���,ָ��VRID�½��շ�����쳣���ĸ����ܺ�,���������������г��ļ����������*/

    ULONG ulErrorCheckSum;     /* У��ʹ������ */
    ULONG ulErrorTtlCheck;     /* TTL����Ĵ��� */
    ULONG ulErrorVersion;      /* �汾�Ŵ������ */
    ULONG ulErrorVirtualIpList;/* �����ַ�б�ƥ�����Ĵ��� */
    ULONG ulErrorLength;       /* ���ĳ��ȴ���Ĵ��� */
    ULONG ulErrorAdvertiseTime;/* ADVERTISEMENTʱ��������Ĵ��� */
    ULONG ulErrorAuth;         /* ��֤����Ĵ��� */
    ULONG ulErrorInitialState;  /* ������ΪInitial״̬�յ��ı��Ĵ��� */

    ULONG ulRcvAdvertisePkt;   /* ���յ��ı����ܺ� */
    ULONG ulSndAdvertisePkt;   /* ���͵��ı����ܺ� */
    ULONG ulRcvPriorityZeroPkt;/* ���յ������ȼ�Ϊ0�����ܺ� */
    ULONG ulSndPriorityZeroPkt;/* ���͵������ȼ�Ϊ0�����ܺ� */

    ULONG ulGlobalErrorVrid;   /* ͳ�ƽ��յı�����VRID����ı��ĸ���,Ϊȫ��ͳ��ֵ*/
}TCPIP_VRRP_STATISTICS_S;

/* VRRP��ϸ������Ϣ */
typedef struct tagTCPIP_VRRP_CONFIGINFO
{
    ULONG ulVrid;       /* ������ID */
    ULONG ulIfIndex;    /* ���������ڽӿ����� */
    ULONG ulState;      /* ������״̬(init,backup,master) */

    ULONG ulIpAddressCount;         /* ���ַ���� */
    ULONG ulIpAddressList[VRRP_VIRTUAL_IP_ADDRESS_MAX]; /* ���ַ�б� */

    UCHAR ucAdvertisementInterval;  /* master����vrrp���ĵ�ʱ���� */
    UCHAR ucPriorityConfig;         /* ���õ����ȼ� */
    UCHAR ucPriorityRun;            /* ��Ч�����ȼ� */

    UCHAR ucAuthenticationType;     /* ��֤ģʽ */
    UCHAR ucAuthenticationKey[VRRP_AUTHENTICATION_KEY_LENGTH];  /* ��֤pwd */

    UCHAR ucPreempt;            /* �Ƿ����ռ */
    UCHAR ucDelayValue;         /* �ӳ�ʱ�� */
    UCHAR ucEnablePing;         /* �Ƿ�֧��ping���� */
    UCHAR ucEnableCheckTtl;     /* �Ƿ�����ձ��ĵ�TTL */

    ULONG ulGratuitousArptime;  /* �������arp��ʱ�� */

    ULONG ulDiagnostic;         /* �����һ��VRRP״̬��Ǩ��ԭ��,�μ�VRRP_STATE_CHANGE_DIAG_E */
}TCPIP_VRRP_CONFIGINFO_S;

/* ���ӽӿڹ��ܵ����ݽṹ*/
typedef struct tagTCPIP_VRRP_TRACKIF
{
    ULONG ulTrackIfIndex;      /* �����ӽӿڵ����� */
    LONG  lReduce;             /* �����ӵĽӿ�DOWN��ʱ���½������ȼ����� */
    UCHAR ucTrackedIfnetState; /* �����ӽӿڵ�״̬ */
    UCHAR ucReserve[3];
}TCPIP_VRRP_TRACKIF_S;

/* ����BFD���ܵ����ݽṹ*/
typedef struct tagTCPIP_VRRP_TRACKBFD
{
    ULONG ulBfdSessionId;       /* BFD�Ự����Ψһ��ʶ�� */
    ULONG ulVrfIndex;           /* VRF���� */
    LONG  lReduce;              /* �½������ȼ����� */
    UCHAR ucVrrpBfdState;       /* ������BDF �Ự��״̬*/
    UCHAR ucReserve[3];
}TCPIP_VRRP_TRACKBFD_S;

/* ����1AG���ܵ����ݽṹ*/
typedef struct tagTCPIP_VRRP_TRACK1AG
{
    UCHAR szMdName[VRRP_MAX_MDNAME_LEN + 1];    /* Md���� */
    UCHAR szMaName[VRRP_MAX_MANAME_LEN + 1];    /* Ma���� */
    LONG  lReduce;                              /* �½������ȼ����� */
    USHORT usRmepId;                            /* rmep id */
    UCHAR ucVrrp1agState;                       /* ���ӵ�rmep�Ƿ����CC LOST�澯��Interface down�澯 */
    UCHAR ucReserve;
}TCPIP_VRRP_TRACK1AG_S;

/* ����3AH���ܵ����ݽṹ*/
typedef struct tagTCPIP_VRRP_TRACK3AH
{
    ULONG ul3ahIfIndex;         /* ���ӵ�3ah�ӿ����� */
    LONG  lReduce;              /* �½������ȼ����� */
    UCHAR ucVrrp3ahState;       /* ������3ah��״̬*/
    UCHAR ucReserve[3];
}TCPIP_VRRP_TRACK3AH_S;


/*******************************************************************************
 * ע�����亯��ԭ��:                                                           *
 *******************************************************************************/
typedef ULONG (*VRRP_GETBFDSESSIONSTATE)(ULONG ulSessionID, ULONG ulVrfIndex, ULONG *pstState);

/*******************************************************************************
 * APIԭ��:                                                                    *
 *******************************************************************************/

extern ULONG TCPIP_VRRP_CreateStandby(ULONG ulIfIndex, ULONG ulVrid);


extern ULONG TCPIP_VRRP_DelStandby(ULONG ulVrid);


extern ULONG TCPIP_VRRP_AddVirtualIP(ULONG ulVrid, ULONG ulIpaddr);


extern ULONG TCPIP_VRRP_DelVirtualIP(ULONG ulVrid, ULONG ulIpaddr);


extern ULONG TCPIP_VRRP_DelAllVirtualIP(ULONG ulVrid);


extern ULONG TCPIP_VRRP_EnablePing(ULONG ulVrid, ULONG ulSetYes);


extern ULONG TCPIP_VRRP_SetAdvertiseTimer(ULONG ulVrid, ULONG ulTimer);


extern ULONG TCPIP_VRRP_SetPriority(ULONG ulVrid, ULONG ulPriority);


extern ULONG TCPIP_VRRP_SetPreemptDelay(ULONG ulVrid, ULONG ulDelay);


extern ULONG TCPIP_VRRP_EnablePreempt(ULONG ulVrid, ULONG ulSetYes);


extern ULONG TCPIP_VRRP_EnableCheckTTL(ULONG ulVrid, ULONG ulSetYes);


extern ULONG TCPIP_VRRP_SetGratuitousArpTimer(ULONG ulTimer);



extern ULONG TCPIP_VRRP_SetAuthMode(ULONG ulVrid, ULONG ulMode, UCHAR* pszKey);



extern ULONG TCPIP_VRRP_TrackIF(ULONG ulVrid, ULONG ulTrackIfIndex, LONG lReduce, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_TrackBFD
* Date Created: 2009-01-10
*       Author: wuhailan/gexianjun
*  Description: ����VRRP����BFD�Ự
*        Input: ULONG ulVrid:VRRP�������
*               ULONG ulBfdSession:�����ӵ�BFD�Ự
*               ULONG ulVrfIndex:  VRF����
*               LONG lReduce:���õ������ӵ�BFD�Ự��ΪDownʱ�����ȼ����ӵ���ֵ��ȡֵ��Χ��1��255
*               ULONG ulSetYes:1 ���ü���  0 ȡ������
*       Output:
*       Return: �ɹ�VRRP_OK���������ش�����
*      Caution: ��VRF���δע��ʱ��VRF�������봫��0��������Ϊ�����������
*               ��BFD�ỰIDΪ0������Ϊȡ������ʱ����Ϊɾ�����е�BFD��������
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-10   wuhailan/gexianjun      Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_TrackBFD(ULONG ulVrid, ULONG ulBfdSession, ULONG ulVrfIndex, LONG lReduce, ULONG ulSetYes);


extern ULONG TCPIP_VRRP_Track1AG(ULONG ulVrid, UCHAR* szMdName, UCHAR* szMaName, USHORT usRmepid,
                                        LONG lReduce, ULONG ulSetYes);



extern ULONG TCPIP_VRRP_Track3AH(ULONG ulVrid, ULONG ulTrackIfIndex, LONG lReduce, ULONG ulSetYes);



extern ULONG TCPIP_VRRP_GetConfigInfo(ULONG ulVrid, TCPIP_VRRP_CONFIGINFO_S *pstVrrpConfigInfo);


extern VOID TCPIP_VRRP_ShowConfigInfo(ULONG ulVrid);


extern VOID TCPIP_VRRP_ShowAllInfo(VOID);


extern ULONG TCPIP_VRRP_GetTrackIFInfo(ULONG ulVrid, TCPIP_VRRP_TRACKIF_S stVrrpTrackIfInfo[VRRP_TRACK_MAX], ULONG *pulCount);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_ShowTrackIFInfo
* Date Created: 2009-01-20
*       Author: wuhailan
*  Description: ��ʾ���õ�VRRP���ڽӿڼ��ӵĹ�����Ϣ
*        Input: ULONG ulVrid:VRRP�������
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_VRRP_ShowTrackIFInfo(ULONG ulVrid);


extern ULONG TCPIP_VRRP_GetTrackBFDInfo(ULONG ulVrid, TCPIP_VRRP_TRACKBFD_S stVrrpTrackBfdInfo[VRRP_TRACK_MAX], ULONG *pulCount);


extern VOID TCPIP_VRRP_ShowTrackBFDInfo(ULONG ulVrid);


extern ULONG TCPIP_VRRP_GetTrack1AGInfo(ULONG ulVrid, TCPIP_VRRP_TRACK1AG_S stVrrpTrack1agInfo[VRRP_TRACK_MAX], ULONG *pulCount);


extern VOID TCPIP_VRRP_ShowTrack1AGInfo(ULONG ulVrid);


extern ULONG TCPIP_VRRP_GetTrack3AHInfo(ULONG ulVrid, TCPIP_VRRP_TRACK3AH_S stVrrpTrack3ahInfo[VRRP_TRACK_MAX], ULONG *pulCount);


extern VOID TCPIP_VRRP_ShowTrack3AHInfo(ULONG ulVrid);


extern ULONG TCPIP_VRRP_GetVridlistByIfIndex(ULONG ulIfIndex, ULONG* pulVridCount,
                                                            UCHAR ucVridlist[VRRP_MAX_ROUTERNUM_PERPORT]);


extern VOID TCPIP_VRRP_ShowVridlist(UCHAR* pszIfName);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_ResetStatistic
* Date Created: 2009-01-20
*       Author: wuhailan/zhengsenhuo
*  Description: ��ʼ��ͳ����Ϣ,������ȫ�ֵ�VRID����ͳ����Ϣ��0
*        Input: ULONG ulVrid:������id
*       Output: 
*       Return: �ɹ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   wuhailan/zhengsenhuo                             Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_ResetStatistic(ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_GetStatistic
* Date Created: 2009-01-20
*       Author: wuhailan/zhengsenhuo
*  Description: ��ȡָ��VRID��ͳ����Ϣ,�������յı�����VRID����ı��ĸ���
*        Input: ULONG ulVrid:������VRID
*       Output: TCPIP_VRRP_STATISTICS_S *pstVrrpStatics: ���ص�ͳ����Ϣ,�������յı�����VRID����ı��ĸ���
*       Return: �ɹ�VRRP_OK,�������ش�����
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   wuhailan/zhengsenhuo         Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_GetStatistic(ULONG ulVrid, TCPIP_VRRP_STATISTICS_S *pstVrrpStatics);


extern VOID TCPIP_VRRP_ShowStatistic(ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_SetDebug
* Date Created: 2009-01-20
*       Author: wuhailan
*  Description: VRRP���Կ������ýӿ�
*        Input: ULONG ulVrid:������ID
*               ULONG ulType:���õĵ�������
*               VRRP_DEBUG_PACKET,��������Կ���
*               VRRP_DEBUG_ERROR,���Ĵ�������Կ���
*               VRRP_DEBUG_STATE,״̬������Կ���
*               VRRP_DEBUG_EVENT,�����¼�����Կ���
*               VRRP_DEBUG_ALL,��ȫ�����͵��Կ���
*               ULONG ulSetYes:���Կ��أ�1��ʾ�򿪣�0��ʾ�ر�
*       Output: 
*       Return: �ɹ�����VRRP_OK,ʧ�ܷ��ش�����
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-20   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_SetDebug(ULONG ulVrid, ULONG ulType, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_ShowDebug
* Date Created: 2009-02-03
*       Author: wuhailan
*  Description: ��ʾVRRP�ĵ��Կ�����Ϣ
*        Input: ULONG ulVrid:VRID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-03   wuhailan                Create
*
*******************************************************************************/
VOID TCPIP_VRRP_ShowDebug(ULONG ulVrid);

/*******************************************************************************
*    Func Name: TCPIP_VRRP_RegHookNotifyState
* Date Created: 2010-01-24
*       Author: zengshaoyang62531
*  Description: ע��VRRP״̬��Ǩ����ͨ��Ĺ��Ӻ���
*        Input: TCPIP_VRRP_NOTIFY_STATE pfFunc:���Ӻ���
*       Output: 
*       Return: VRRP_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-24   zengshaoyang62531         Create
*
*******************************************************************************/
extern ULONG TCPIP_VRRP_RegHookNotifyState(TCPIP_VRRP_NOTIFY_STATE pfFunc);


#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _VRRP_API_H_      */


