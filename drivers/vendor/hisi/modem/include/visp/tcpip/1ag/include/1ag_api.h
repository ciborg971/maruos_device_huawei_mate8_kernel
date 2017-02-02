/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              1ag_api.h
*
*  Project Code: VISPV100R007
*   Module Name: 1AG
*  Date Created: 2008-3-3
*        Author: yebo(62007)
*   Description: 1AGģ��API
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-3-3  yebo(62007)         Create the first version.
*
*******************************************************************************/
#ifndef _1AG_API_H
#define _1AG_API_H

#ifdef  __cplusplus
    extern "C"{
#endif

/* 1AG ���������� */
enum eOAM1AGERRCODE
{
    OAM1AG_OK,                      /*0��������*/
    OAM1AG_ERR,                     /*1���ܴ���,�����ڲ���������ֵ*/
    OAM1AG_ERR_PARAWRONG,           /*2������Ч�Դ���*/
    OAM1AG_ERR_PARANULL,            /*3�������Ϊ��*/
    OAM1AG_ERR_MDNAMELEN,           /*4MD���ֳ��ȴ���*/
    OAM1AG_ERR_MANAMELEN,           /*5MA���ֳ��ȴ���*/
    OAM1AG_ERR_MDMANAMELEN,         /*6MDMA���ֳ��ȴ���*/
    OAM1AG_ERR_IFNULL,              /*7�ӿڲ�����*/
    OAM1AG_ERR_IFINVALID,           /*8�ӿ����ʹ���*/
    OAM1AG_ERR_MDALREADYEXIST,      /*9MD�Ѵ���*/
    OAM1AG_ERR_MDNOTEXIST,          /*10MD������*/
    OAM1AG_ERR_MAALREADYEXIST,      /*11MA�Ѵ���*/
    OAM1AG_ERR_MANOTEXIST,          /*12MA������*/
    OAM1AG_ERR_PORTHASMEP,          /*13�ӿ�MA���Ѵ���MEP*/
    OAM1AG_ERR_MEPNOTEXIST,         /*14�ӿ�MA�²�����MEP*/
    OAM1AG_ERR_REMOTEHASMEP,        /*15Զ��MA�������ù���MEPID*/
    OAM1AG_ERR_PORTHASNOMP,         /*16�ӿ���û��ά����*/
    OAM1AG_ERR_EQUALTOPORTMEP,      /*17���õ�RMEPID�뱾�ӿ���MEP��ͬ*/
    OAM1AG_ERR_NOTENOUGHMEMORY,     /*18�ڴ�ռ䲻��*/
    OAM1AG_ERR_OVERMDMAXNUM,        /*19MD�������*/
    OAM1AG_ERR_OVERMAMAXNUM,        /*20MA�������*/
    OAM1AG_ERR_OVERMEPMAXNUM,       /*21MEP�������*/
    OAM1AG_ERR_OVERRMEPMAXNUM,      /*22RMEP�������*/
    OAM1AG_ERR_HAISSMOOTHING,       /*23������ƽ���򵹻�*/
    OAM1AG_ERR_RMEPALREADYEXIST,    /*24RMEP�Ѵ���*/
    OAM1AG_ERR_MEPHASSENDCCM,       /*25�Ѿ�ʹ����CCM����*/
    OAM1AG_ERR_VLANIDALREADYEXIST,  /*26VLANID�Ѿ�����*/
    OAM1AG_ERR_INTERVALNEEDNP,      /*27���ͼ����NP֧��*/
    OAM1AG_ERR_RMEPNOTEXIST,        /*28RMEP ������*/
    OAM1AG_ERR_CCMALREADYENABLE,    /*29CCM�ķ��ͼ��������*/
    OAM1AG_ERR_SENDCCM,             /*30����CCM����ʧ��*/
    OAM1AG_ERR_LTSELFMAC,           /*31��·׷�ٲ��Ե�Ŀ��physical��ַ���ڱ���physical��ַ */
    OAM1AG_ERR_SENDLTM,             /*32����LTM����ʧ��*/
    OAM1AG_ERR_PACKETSIZE,          /*33LB���ĳ��ȴ���*/
    OAM1AG_ERR_LBTIMEOUT,           /*34LB��ʱʱ�����*/
    OAM1AG_ERR_LBINTERVAL,          /*35LB���ͼ������*/
    OAM1AG_ERR_MACADDR,             /*36�û�physical��ַ����*/
    OAM1AG_ERR_RMEPHAVENOMAC,       /*37RMEP ����û��physical��ַ*/
    OAM1AG_ERR_OVERMAXPING,         /*38�Ѿ���16��ping����*/
    OAM1AG_ERR_USERENCAPSULATE,     /*39��װ�Զ��屨��ʧ�� */
    OAM1AG_ERR_MAHASMEP,            /*40MA��������ͬ��MEP*/
    OAM1AG_ERR_OVERMAXLT,           /*41ͬʱ�����LT��������*/
    OAM1AG_ERR_MODULENOTEXIST,      /*42���δע��*/
    OAM1AG_ERR_NORECV,              /*43δ�յ�һ��lbr���� */
    OAM1AG_ERR_RECVPART,            /*44�յ���lbr��С�ڷ��͵�lbm������ */
    OAM1AG_ERR_LBSELFMAC,           /*45���ز��Ե�Ŀ�ĵ�ַ���ڳ��ӿڵ�physical��ַ */
    OAM1AG_ERR_CCMINTERVAL,         /*46CCM���ͼ������ */
    OAM1AG_ERR_MEPIDWRONG,          /*47MEPID������Χ */
    OAM1AG_ERR_DISABLECCMFAILED,    /*48ȥʹ��CCM����ʧ��(ɾ��MEPʱ)*/
    OAM1AG_ERR_DELETEALLMEPFAILED,  /*49ɾ��MA�µ�����MEPʧ��*/
    OAM1AG_ERR_DELETEALLRMEPFAILED, /*50ɾ��MA�µ�����RMEPʧ��(��ɾ����MA�µ����һ��MEPʱ)*/
    OAM1AG_ERR_GETMACADDR,          /*51��ȡ���ӿڵ�physical��ַʧ�� */
    OAM1AG_ERR_CREATEMBUF,          /*52����mbufʧ�� */
    OAM1AG_ERR_USERHOOKNOTREG,      /*53�û��Զ��崦����û��ע�� */
    OAM1AG_ERR_TRANSMITFAIL,        /*54û��һ��lbm���ı����� */
    OAM1AG_ERR_NOTRECEIVEEXPECTLTR, /*55û���յ���Ŀ��MP���ص�LTR */
    OAM1AG_ERR_SENDUNCOMPLETE,      /*56��Ϊĳ��ԭ���жϣ�����δ��ȫ */
    OAM1AG_ERR_SETMAVLANPRIORITY,   /*57���û���MA��VLAN���ȼ�������Χ */
    OAM1AG_ERR_NOTINFULLNPMODE,     /*58������ȫNPģʽ */
    OAM1AG_ERR_VLANPRIINVALID,      /*59ָ����VLAN���ȼ����Ϸ� */
    OAM1AG_ERR_NOTENOUGHMEMORY_DOT1 = 60,/* 60 �ڴ�ռ䲻�㣬������Ψһ������*/
    OAM1AG_ERR_MACADDR_NOTUNICAST,  /* 61 �ǵ���physical��ַ*/
    OAM1AG_ERR_GET_ETHCTLBLOCK,     /* 62 ��ȡ������̫���ƿ� */
    OAM1AG_ERR_INTER_FAIL,          /* 63 ���ͱ��ĵĹ��Ӻ�������ʧ�� */
    OAM1AG_ERR_MBUF_PREPEND,        /* 64 MBUF����ͷ����ʧ�� */
    OAM1AG_ERR_MBUF_CONTINUE,       /* 65 ʹ��MBUF�ڴ������Ĳ���ʧ�� */
    OAM1AG_ERR_UNREG_ENCAP,         /* 66 �޷�ʶ���֧�ֵ���̫��װ���� */
    OAM1AG_ERR_SLAVE_BOARD,         /* 67 �����Ǳ��壬�������� */
    OAM1AG_ERR_TTL_INVALID,         /* 68 TTLֵ���Ϸ� */
    OAM1AG_ERR_TIMEOUT_INVALID,     /* 69 Time outֵ���Ϸ� */
    OAM1AG_ERR_NOT_STATICRMEP,      /* 70 �Ǿ�̬RMEP*/  
    OAM1AG_ERR_RMEPISDOWNLOADNP,    /* 71 RMEP�Ѿ��·���NP */
    OAM1AG_ERR_TRUNKPORT_TOOMANYMEP,/* 72 ��Trunk��Ա�˿�������MEP�����MEP���ڵ�MAֻ֧������һ��MEP */
    OAM1AG_ERR_TRUNKPORT_MDLEVEL,   /* 73 Trunk ���ϵ� MDLevel Ӧ�ñ� TrunkPort �� */
    OAM1AG_ERR_TRUNKPORT_CCMINTERVAL,   /* 74 Trunk �ϵ� CCM ̽������Ӧ���� TrunkPort �ϵ��������� */
    OAM1AG_ERR_MA_BIND_VLAN,        /* 75 ��Trunk��Ա�˿��ϴ���MEP���������MA���ܰ�VLAN */
    OAM1AG_ERR_MA_NOT_BIND_VLAN,    /* 76 ��Trunk��Eth�ϴ���MEP���������MA�����VLAN */
    OAM1AG_ERR_NOT_1731_MODE,       /* 77 ��1731�汾 */
    OAM1AG_ERR_VLANID_MEGLEVEL_EXIST,  /* 78 VLANID+MegLevel�Ѿ����� */
    OAM1AG_ERR_GET_PMPOLICY,        /* 79 ��ȡ���Ӳ���ʧ�� */
    OAM1AG_ERR_NOTSUPPORT_1731_MODE,/* 80 ��֧��Y1731�汾 */
    OAM1AG_ERR_RMEPIDWRONG,         /* 81 RMEPID������Χ */
    OAM1AG_ERR_PARAOVERFLOW,        /* 82 �������볬����Χ */
    OAM1AG_ERR_NOTENABLECCMSEND,    /* 83 δʹ��CCM */
    OAM1AG_ERR_ALREADYENABLE,       /* 84 ��MEP/RMEP��ʹ�����ܼ��,�����޸Ĳ��� */
    OAM1AG_ERR_ALREADYENABLEMEP,    /* 85 ��MEP��ʹ�ܸ������ܼ�� */
    OAM1AG_ERR_ALREADYENABLERMEP,   /* 86 ��RMEP��ʹ�ܸ������ܼ�� */
    OAM1AG_ERR_NOTSTATICRMEP,       /* 87 �Ǿ�̬RMEP */
    OAM1AG_REPEATSET,               /* 88 �ظ����� */
    OAM1AG_ERR_MEPNULL,             /* 89 ��ȡMEP INFOʧ�� */
    OAM1AG_ERR_RMEPNULL,            /* 90 ��ȡRMEP INFOʧ�� */
    OAM1AG_ERR_CC_DETECT_MODE,      /* 91 �����REMP ̽��ģʽ*/
    OAM1AG_ERR_NOTINNONPMODE,       /* 92 �����ڷ�NP(���)ģʽ */
    OAM1AG_ERR_MAXCODE              /*��������,����´�����ʱ,��ӵ���������֮ǰ*/
};


#define OAM_1AG_NOTBINDVLAN 0xFFFF

/*physical��ַ����*/
#define OAM_1AG_MACADDR_LEN 6

/*1AG MD������ֳ���*/
#ifndef OAM_1AG_MAX_MDNAME_LEN
#define OAM_1AG_MAX_MDNAME_LEN 43
#endif

/*1AG MA������ֳ���*/
#ifndef OAM_1AG_MAX_MANAME_LEN
#define OAM_1AG_MAX_MANAME_LEN 43
#endif

/*Y1731 MA������ֳ���*/
#ifndef OAM_Y1731_MAX_MANAME_LEN
#define OAM_Y1731_MAX_MANAME_LEN 13
#endif

typedef enum enumTcpipOAM1AGWarning
{
    OAM_1AG_NOTIFYCCPERIOD = 0,       /*npͨ��CC��ʱ*/
    OAM_1AG_NOTIFYCCAGING,            /*NPͨ��CC�ϻ�*/     
    OAM_1AG_NOTIFYCCRECOVER,          /*NP֪ͨ�澯�ָ�*/   
    OAM_Y1731_NOTIFYLEVELERROR,       /*NP֪ͨ��������MEG level*/   
    OAM_Y1731_NOTIFYLEVELRECOVER,     /*NP֪ͨ��������MEG level�澯�ָ�*/
    OAM_Y1731_NOTIFYMEGIDERROR,       /*NP֪ͨ��������MEG ID*/
    OAM_Y1731_NOTIFYMEGIDRECOVER,     /*NP֪ͨ��������MEG ID�澯�ָ�*/
    OAM_Y1731_NOTIFYMEPIDERROR,       /*NP֪ͨ��������MEP ID*/
    OAM_Y1731_NOTIFYMEPIDRECOVER,     /*NP֪ͨ��������MEP ID�澯�ָ�*/
    OAM_Y1731_NOTIFYINTERVALERROR,    /*NP֪ͨ�������Ĵ�������*/
    OAM_Y1731_NOTIFYINTERVALRECOVER,  /*NP֪ͨ�������Ĵ������ڸ澯�ָ�*/

    OAM_WARNING_NOTIFY_MAX,
}TCPIP_OAM_1AG_WARNING_E;

/*1AG�澯��ʼ������*/
#define OAM_1AG_WARNING_BEGIN 1
#define OAM_1AG_WARNING_END 0

/* ȥʹ��CCM���� */
#define OAM_1AG_CCMSEND_DISABLE   0
/* ʹ��CCM���� */
#define OAM_1AG_CCMSEND_ENABLE   1

/* MP����������MEP��RMEP */
#define OAM_1AG_MEPTYPE  0
#define OAM_1AG_RMEPTYPE 1

/*RMEP��״̬*/
#define OAM_1AG_DYNAMICRMEP 0    /* ��̬RMEP */
#define OAM_1AG_STATICRMEP  1    /* ��̬RMEP */

/* 1AG Draft7�汾*/
#define OAM_1AG_VERSION_DRAFT7    0
/* 1AG��׼�汾*/
#define OAM_1AG_VERSION_STD       1
/* Added by hanna55555, Y1731-CCM, 2010/4/19 */
/* 1AG Y.1731�汾*/
#define OAM_1AG_VERSION_Y1731     2
/*End of Added by hanna55555, 2010/4/19 */

/* �������ͱ���ʱ�Ƿ���Ҫ��VLANͷ��־,��������CCM,LBM,LTM����.���ǲ������ظ���LBR��LTR���� */
/* �������ͱ���ʱ��Ҫ��VLANͷ */
#define OAM_1AG_SEND_WITH_VLAN  1
/* �������ͱ���ʱ����Ҫ��VLANͷ */
#define OAM_1AG_SEND_WITHOUT_VLAN  0

/* RMEP��MD Level��Ա���MEP��MD Level�ıȽ���� */
#define OAM_1AG_EQLEVEL   0      /* RMEP��MD Level������MEP��MD Level��� */
#define OAM_1AG_GTLEVEL   1      /* RMEP��MD Level���ڱ���MEP��MD Level */
/* ȥʹ�����ܼ��(Y1731) */
#define Y1731_PMCHECK_DISABLE   0
/* ʹ�����ܼ��(Y1731) */
#define Y1731_PMCHECK_ENABLE   1
/* ȥʹ��AIS ����*/
#define Y1731_AIS_DISABLE   0
/*ʹ��AIS ����*/
#define Y1731_AIS_ENABLE   1


/* 1AG Ping(��LB����)�����ṹ */
typedef struct tagTCPIP_1AG_PING
{
    ULONG   ulUserID;       /* �û�ID */
    UCHAR   szMDName[OAM_1AG_MAX_MDNAME_LEN + 1]; /*MD����,�Ϊ43�ֽ�*/
    UCHAR   szMaName[OAM_1AG_MAX_MANAME_LEN + 1]; /*MA����,�Ϊ43�ֽ�*/
    UCHAR  *pucMacAddr;     /* 1AG Mac Pingʹ�õ�Ŀ��physical��ַ.ָ��"XX-XX-XX-XX-XX-XX"��ʽphysical��ַ��ָ��,
                               ���ΪNULL�����RMEP Ping,�������ָ����physical��ַ�ͽӿ�����Ping */
    ULONG   ulIfIndex;      /* iAG MAC Pingʹ�õĽӿ����� */    
    USHORT  usRmepId;       /* 1AG RMEP Pingʹ�õ�RMEP ID */
    USHORT  usTimeOut;      /* 1AG Ping��ʱʱ��.����û�δָ��(ֵΪ0),��ʹ��Ĭ��ֵ2s */
    ULONG   ulInterval;     /* ����1AG Ping���ĵļ��.ȡֵ��Χ[0s,60s] */
    ULONG   ulCount;        /* ����1AG Ping���ĵĴ���.����û�δָ��(ֵΪ0),��ʹ��Ĭ��ֵ5�� */
    USHORT  usPacketSize;   /* ����1AG Ping���ĵĴ�С.����û�δָ��(ֵΪ0),��ʹ��Ĭ��ֵ128�ֽ�,ȡֵ��Χ[95,1500] */
    UCHAR   ucVlanPri;      /* ����1AG Ping���ĵ�VLAN���ȼ�,ȡֵ��Χ[0,7]�Լ�0xFF.
                               0xFF��ʾ����Э��ջĬ�Ϲ�����дVLAN���ȼ�,�����MA������VLAN���ȼ���
                               ʹ�ø�MA��VLAN���ȼ�,����ʹ��ȫ��VLAN���ȼ�. */
    UCHAR   ucReserve;      /* �����ֶ�δʹ�� */
}TCPIP_1AG_PING_S;

/* 1AG User Ping(���û��Զ���LB����)�����ṹ */
typedef struct tagTCPIP_1AG_USERPING
{
    UCHAR   szMDName[OAM_1AG_MAX_MDNAME_LEN + 1]; /*MD����,�Ϊ43�ֽ�*/
    UCHAR   szMaName[OAM_1AG_MAX_MANAME_LEN + 1]; /*MA����,�Ϊ43�ֽ�*/
    UCHAR  *pucMacAddr;     /* 1AG Mac User Pingʹ�õ�Ŀ��physical��ַ.ָ��"XX-XX-XX-XX-XX-XX"��ʽphysical��ַ��ָ��,
                               ���ΪNULL�����RMEP Ping,�������ָ����physical��ַ�ͽӿ�����Ping */
    ULONG   ulIfIndex;      /* iAG MAC User Pingʹ�õĽӿ����� */    
    USHORT  usRmepId;       /* 1AG RMEP User Pingʹ�õ�RMEP ID */
    UCHAR   ucVlanPri;      /* ����1AG User Ping���ĵ�VLAN���ȼ�,ȡֵ��Χ[0,7]�Լ�0xFF.
                               0xFF��ʾ����Э��ջĬ�Ϲ�����дVLAN���ȼ�,�����MA������VLAN���ȼ���
                               ʹ�ø�MA��VLAN���ȼ�,����ʹ��ȫ��VLAN���ȼ�. */
    UCHAR   ucReserve;      /* �����ֶ�δʹ�� */
    UCHAR  *pBuffer;        /* ����1AG User Ping������DATA TLV��Value�ֶ�ֵ,Ҫ��������[40,1460]�ֽ�֮�� */
    ULONG   ulLen;          /* pBuffer�����ݳ���,ȡֵ��Χ[40,1460]�ֽ� */
}TCPIP_1AG_USERPING_S;

/* �յ�һ������VLAN��LB��LT����ʱ,��ӿڴ��ڶ������VLAN��MEP��Ϣʱ,�ص�֪ͨ��Ϣ�ṹ */
typedef struct tagTCPIP_1AG_NOVLANINFO_S
{
    UCHAR  szMacAddr[OAM_1AG_MACADDR_LEN];       /* �����е�Դphysical��ַ */
    USHORT usMepId;                              /* MEP ID */
    UCHAR  szMaName[OAM_1AG_MAX_MANAME_LEN + 1]; /* MA����,��󳤶�Ϊ43 */
    UCHAR  szMdName[OAM_1AG_MAX_MDNAME_LEN + 1]; /* MD����,�Ϊ43�ֽ� */
    USHORT usVlanId;                             /* MA������VLAN IDֵ */    
    UCHAR  ucMdLevel;                            /* MD���� */
    UCHAR  ucReserve;                            /* �����ֶ�δʹ�� */
} TCPIP_1AG_NOVLANINFO_S;

/*��ʾMD��Ϣ*/
typedef struct tagDISP_MD_INFO
{
    UCHAR ucLevel;          /* ά���򼶱�*/
    UCHAR ucMDNameType;     /*ά�����������ͣ�Ŀǰֻ֧���ַ�������*/
    UCHAR ucRes[2];
} DISP_MD_INFO_S;

/*��ʾMA��Ϣ*/
typedef struct tagDISP_MA_INFO
{
    ULONG ulVLanID;     /* VLan ID */
    UCHAR ucMDLevel;    /* ά���򼶱� */
    UCHAR ucInterval;   /* CCM���ͼ�� */
    UCHAR ucPriority;   /* 1ag �������ȼ� */
    UCHAR ucCompatible; /* ����ģʽ */
    UCHAR ucRdiFlag;    /* MA��RDI���,ͬʱҲ��RDI�澯�Ƿ���ʧ�ı��*/
    UCHAR ucAisEnable;   /* AISʹ�ܿ���*/ 
    UCHAR ucAisWarningFlag;       /* AIS�澯��ʶ*/
    UCHAR ucAisInterval;  /*AIS��������*/
} DISP_MA_INFO_S;

typedef struct tagMEP_PMINFO
{
    USHORT usRmepId;                         /* RMEP ID */
    USHORT usEnableFlag;                     /* ʹ�ܱ�� */
    ULONG  ulInterval;                       /*��������*/
    ULONG  ulTimeOut;                        /*��ʱʱ��*/
}MEP_PM_INFO_S;

/*��ʾMEP��Ϣ*/
typedef struct tagDISP_MEP_INFO
{
    ULONG  ulOutIfIndex;                    /* ���ӿڼ��յ�CCM���ĵĽӿ� */
    USHORT usMepId;                         /* MEP ID */
    UCHAR  szMacAddr[OAM_1AG_MACADDR_LEN];  /* RMEP physical��ַ */
    UCHAR  ucMepType;                       /* ��̬���߶�̬RMEP��� */
    UCHAR  ucMepLocation;                   /* MEPλ��,���˻���Զ�� */
    UCHAR  ucSendFlag;                      /* CCM���ͱ�־ */
    UCHAR  uc1agVersion;                    /* MEP ʹ�õ�1AG�汾,0:Draft7�汾;1:��׼�汾;2:Y1731�汾 */
    UCHAR  ucVlanFlag;                      /* ��MEP�·��͵ı����Ƿ��VLANͷ��־.
                                               0:��ʾ����Ҫ��VLANͷ,1��ʾ��Ҫ��VLAN*/
    UCHAR  ucRes[3];
                                               
    MEP_PM_INFO_S stPMCheckDLM;
    MEP_PM_INFO_S stPMCheckSLM;
    MEP_PM_INFO_S stPMCheckDDM;                   
} DISP_MEP_INFO_S;

/*����ID��ȡ����ID��ͬ��MEP��RMEP��ʾ��Ϣ*/
typedef struct tagDISP_MEP_INFO_LIST
{
    struct tagDISP_MEP_INFO_LIST *pstNext;  /* ��һ����ʾ�ڵ� */
    ULONG  ulOutIfIndex;                    /* ���ӿڼ��յ�CCM���ĵĽӿ� */
    USHORT usMepId;                         /* MEP ID */
    UCHAR  szMacAddr[OAM_1AG_MACADDR_LEN];  /* RMEP physical��ַ */
    UCHAR  ucMepType;                       /* ��̬���߶�̬RMEP��� */
    UCHAR  ucMepLocation;                   /* MEPλ��,���˻���Զ�� */
    UCHAR  ucSendFlag;                      /* CCM���ͱ�־ */
    UCHAR  uc1agVersion;                    /* MEP ʹ�õ�1AG�汾,0:Draft7�汾;1:��׼�汾;2:Y1731�汾 */
    UCHAR  ucVlanFlag;                      /* ��MEP�·��͵ı����Ƿ��VLANͷ��־.
                                               0:��ʾ����Ҫ��VLANͷ,1��ʾ��Ҫ��VLAN*/
    UCHAR  ucRes[3];

    MEP_PM_INFO_S stPMCheckDLM;
    MEP_PM_INFO_S stPMCheckSLM;
    MEP_PM_INFO_S stPMCheckDDM; 
} DISP_MEP_INFO_LIST_S;

/*OAM 1AG ����ͳ�ƽṹ�� */
typedef struct tagOAM_1AG_STAT
{
    ULONG ulSndPkt;         /*�����ܱ�����*/
    ULONG ulSndDropPkt;     /*���Ͷ���������*/
    ULONG ulRcvPkt;         /*���ձ�����*/
    ULONG ulRcvDropPkt;     /*���ն���������*/
    ULONG ulFwdPkt;         /*ת��������*/
    ULONG ulFwdDropPkt;     /*ת�������ı�����*/
    ULONG ulUpPkt;          /*���͵ı�����(���TrunkPort)*/

    /*ͳ��CCM*/
    ULONG ulSndCcmPkt;     /*����CCM������*/
    ULONG ulRcvCcmPkt;     /*����CCM������*/
    ULONG ulFwdCcmPkt;     /*ת��CCM������*/
    ULONG ulUpCcmPkt;      /*����CCM������(���TrunkPort)*/

    /*ͳ��LBM*/
    ULONG ulSndLbmPkt;     /*����LBM������*/
    ULONG ulRcvLbmPkt;     /*����LBM������*/
    ULONG ulFwdLbmPkt;     /*ת��LBM������*/
    ULONG ulUpLbmPkt;      /*����LBM������(���TrunkPort)*/
    
    /*ͳ��LBR*/
    ULONG ulSndLbrPkt;     /*����LBR������*/
    ULONG ulRcvLbrPkt;     /*����LBR������*/
    ULONG ulFwdLbrPkt;     /*ת��LBR������*/
    ULONG ulUpLbrPkt;      /*����LBR������(���TrunkPort)*/

    /*ͳ��LTM*/
    ULONG ulSndLtmPkt;     /*����LTM������*/
    ULONG ulRcvLtmPkt;     /*����LTM������*/
    ULONG ulFwdLtmPkt;     /*ת��LTM������*/
    ULONG ulUpLtmPkt;      /*����LTM������(���TrunkPort)*/

    /*ͳ��LTR*/
    ULONG ulSndLtrPkt;     /*����LTR������*/
    ULONG ulRcvLtrPkt;     /*����LTR������*/
    ULONG ulFwdLtrPkt;     /*ת��LTR������*/
    ULONG ulUpLtrPkt;      /*����LTR������(���TrunkPort)*/

    /*ͳ��VLANͷ��־���л�����*/
    ULONG ulVlanChangeCount;
    ULONG ulCCMLostPkt;

    ULONG ulRcvMutiLbmPkt; /*�����鲥LBM������*/ 
    ULONG ulRcvUniLbmPkt;  /*���յ���LBM������*/  

    /*ͳ��AIS����*/
    ULONG ulSndAisPkt;    /*����AIS������*/
    ULONG ulRcvAisPkt;   /*����AIS������*/
    ULONG ulFwdAisPkt; /*ת��AIS������*/    
    ULONG ulUpAisPkt;   /*����AIS������(���TrunkPort)*/
    
} OAM_1AG_STAT_S;

/*HA ͳ����Ϣ */
typedef struct tagHA1AGSTAT
{
    ULONG ulOutPackets;       /* ���巢�ͳɹ�������Ϣ������ */
    ULONG ulOutDropPackets;   /* ���巢��ʧ�ܱ�����Ϣ������ */
    ULONG ulInPackets;        /* ������ղ�����ɹ�������Ϣ������ */
    ULONG ulInDropPackets;    /* ������ա�����ʧ�ܱ�����Ϣ������ */
} HA1AGSTAT_S;

/* 1AG���ͼ�� */
enum eCCMINTERVALVALUE
{
    OAM_1AG_CCSEND_3ms   = 3,
    OAM_1AG_CCSEND_10ms  = 10,
    OAM_1AG_CCSEND_100ms = 100,
    OAM_1AG_CCSEND_1s    = 1000,
    OAM_1AG_CCSEND_10s   = 10 * 1000,
    OAM_1AG_CCSEND_1min  = 60 * 1000,
    OAM_1AG_CCSEND_10min = 600 * 1000
};

/* VISP�·���NP�Ķ�RMEP����CC����ʱ����ֵ */
enum eCCMINTERVAL
{
    OAM_1AG_CCINTERVAL_3ms   = 1,
    OAM_1AG_CCINTERVAL_10ms  = 2,
    OAM_1AG_CCINTERVAL_100ms = 3,
    OAM_1AG_CCINTERVAL_1s    = 4,
    OAM_1AG_CCINTERVAL_10s   = 5,
    OAM_1AG_CCINTERVAL_1min  = 6,
    OAM_1AG_CCINTERVAL_10min = 7
};

/* AIS ���� */
enum eAISINTERVAL
{
    OAM_Y1731_AISINTERVAL_1s   = 4,
    OAM_Y1731_AISINTERVAL_1min  = 6
};

/* 1AG���Կ������� */
enum eDEBUGTYPE
{
    OAM1AG_DEBUG_NORMAL = 0,        /* �������� */
    OAM1AG_DEBUG_EXCEPTION = 1,     /* �쳣���� */
    OAM1AG_DEBUG_VERBOSE = 2        /*  VERBOSE����*/
};

/* Y1731���ܼ������õ����� */
typedef enum enumTcpipY1731PMType
{
    Y1731_PM_DLM = 0,       /* ˫��֡��ʧ��� */
    Y1731_PM_SLM,           /* ����֡��ʧ��� */
    Y1731_PM_DDM,           /* ˫��ʱ�Ӽ�� */
    Y1731_PM_TYPE_MAX       /* ���ܼ�����͵ı߽�ֵ */              
}TCPIP_Y1731_PM_TYPE_E;

/* 1AG����澯״̬*/
typedef struct tagOAM_1AG_WARNSTATE                   
{                                                     
    ULONG ulCcLosWarn;           /* Rmep CcLos�澯    */
    ULONG ulIntfDownWarn;        /* InterfaceDown�澯 */
    ULONG ulRDIWarn;             /* RDI�澯           */
}OAM1AG_WARN_STATE_S;                                 

/*ע�ắ������*/
/*1AG LT��LB��ӡ��Ϣ�������*/
typedef VOID (*OAM_1AG_OUTINFO_HOOK_FUNC)(UCHAR *szBuf, ULONG ulID);

/*ע��Ping stop���Ӻ���*/
typedef ULONG (*OAM_1AG_STOP_HOOK_FUNC)(ULONG ulID);

/*ע���Զ���Ping���Ĵ����Ӻ���*/
typedef ULONG (*OAM_1AG_USERPINGPKTDEAL)(UCHAR *pBuffer, ULONG ulBufLen, ULONG ulPktType);

/*ע��1AG���ܲ��Թ���*/
typedef ULONG (*OAM_1AG_CAPTEST)(ULONG ulTestType);

/*ע���յ�����VLAN��LB��LT����ʱ,���ڶ������VLAN��MEP��֪ͨ���Ӻ���ԭ��*/
typedef ULONG (*OAM_1AG_MORENOVLANNOTIFY_HOOK_FUNC)(ULONG ulIfIndex, TCPIP_1AG_NOVLANINFO_S *pstNoVlanInfo,
                                                             ULONG ulNoVlanInfoNum);
typedef struct tagOAM_1AG_RMEP_STAT
{
    ULONG ulRcvCcmPkt;      /*����CCM������*/
    ULONG ulReserv;         /*Ԥ��4�ֽ�*/
} OAM_1AG_RMEP_STAT_S;

/*API �ӿ��ֲ� */

extern ULONG  TCPIP_1AG_ClearHaStat(VOID);

extern ULONG  TCPIP_1AG_ClearMepStat(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId);

extern ULONG  TCPIP_1AG_CreateMa(UCHAR * pszMdName, UCHAR * pszMaName, ULONG ulVlanId);

extern ULONG  TCPIP_1AG_CreateMd(UCHAR * pszMdName, UCHAR ucMdLevel);

extern ULONG  TCPIP_1AG_CreateMep(ULONG ulIfIndex, UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId);

extern ULONG  TCPIP_1AG_CreateRmep(ULONG ulIfIndex, UCHAR *pucMacAddr, UCHAR * pszMdName, UCHAR * pszMaName,
                                    USHORT usRmepId);

extern ULONG  TCPIP_1AG_DeleteMa(UCHAR * pszMdName, UCHAR * pszMaName);

extern ULONG  TCPIP_1AG_DeleteMd(UCHAR * pszMdName);

extern ULONG  TCPIP_1AG_DeleteMep(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId);

extern ULONG  TCPIP_1AG_DeleteRmep(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usRmepId);

extern ULONG  TCPIP_1AG_EnableCcmSend(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, UCHAR ucSendFlag);

extern ULONG  TCPIP_1AG_GetCompatible(UCHAR * pszMdName, UCHAR *pszMaName, ULONG *pulValue);

extern ULONG  TCPIP_1AG_GetDebug(ULONG *pul1AgPktDebug, ULONG *pulError1AgPktDebug, ULONG
                                 *pul1AgVerbosePktDebug, ULONG *pulPacketNum, ULONG *pulPacketOctets);

extern ULONG  TCPIP_1AG_GetHaDebug(ULONG *pulHADebugFlag);

extern ULONG  TCPIP_1AG_GetHaStat(HA1AGSTAT_S *pstHa1agStat);

extern ULONG  TCPIP_1AG_GetMaInfo(UCHAR *pszMdName, UCHAR *pszMaName, DISP_MA_INFO_S *pstDispMaInfo);

extern ULONG  TCPIP_1AG_GetMdInfo(UCHAR *pszMdName, DISP_MD_INFO_S *pstDispMdInfo);

extern ULONG  TCPIP_1AG_GetMepInfo(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId,
                                    DISP_MEP_INFO_S * pstDispMepInfo);

extern ULONG  TCPIP_1AG_GetAllMepInfoById(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, 
                                   DISP_MEP_INFO_LIST_S ** ppstDispMepInfoList);

extern ULONG  TCPIP_1AG_FreeMepInfoList(DISP_MEP_INFO_LIST_S * pstDispMepInfoList);

extern ULONG  TCPIP_1AG_GetMepStat(UCHAR *pszMdName, UCHAR * pszMaName, USHORT usMepId,
                                    OAM_1AG_STAT_S *pstOam1agStat);

extern ULONG  TCPIP_1AG_GetPktType(USHORT *pusEthType, UCHAR *pucPriority);

extern ULONG  TCPIP_1AG_SetMaVlanPri(UCHAR *pucMdName,UCHAR *pucMaName,UCHAR ucPriority);

extern ULONG  TCPIP_1AG_GlobalDisable(VOID);

extern ULONG  TCPIP_1AG_NpNotify(ULONG ulIfIndex, UCHAR *pszMdName, UCHAR *pszMaName, USHORT usRmepId, ULONG ulType);

extern ULONG  TCPIP_1AG_Ping(ULONG ulIfIndex, UCHAR *pucMacAddr, UCHAR * pszMdName,
                              UCHAR * pszMaName, USHORT usRmepId, ULONG ulCount,
                              USHORT usPacketSize, USHORT usTimeOut, ULONG ulSendInterval, ULONG ulID);


extern ULONG  TCPIP_1AG_VlanPriPing(TCPIP_1AG_PING_S *pst1agPing);


extern ULONG  TCPIP_1AG_RegFuncUserPingPktDeal(OAM_1AG_USERPINGPKTDEAL pfEoamPingPktDealFunc);

extern ULONG  TCPIP_1AG_SetCcmInterval(UCHAR * pszMdName, UCHAR * pszMaName, ULONG ulInterval);

extern ULONG  TCPIP_1AG_SetCompatible(UCHAR * pszMdName, UCHAR *pszMaName, ULONG ulValue);

extern ULONG  TCPIP_1AG_SetDebug(ULONG ulType, ULONG ulFlag, ULONG ulPacketNum, ULONG ulPacketOctets);

extern ULONG  TCPIP_1AG_SetHaDebug(ULONG ulHADebugFlag);

extern ULONG  TCPIP_1AG_SetPktType(USHORT usPktType, UCHAR ucPriority);

extern VOID   TCPIP_1AG_ShowMaInfo(UCHAR *pszMdName, UCHAR *pszMaName);

extern VOID   OAM_1AG_ShowAllMdInfo(VOID);

extern VOID   TCPIP_1AG_ShowMdInfo(UCHAR *pszMdName);

extern VOID   TCPIP_1AG_ShowMepInfo(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepOrRmepId);

extern VOID   TCPIP_1AG_ShowMepStat(UCHAR *pszMdName, UCHAR * pszMaName, USHORT usMepId);

extern ULONG  TCPIP_1AG_Trace(ULONG ulIfIndex, UCHAR *pcMacAddr, UCHAR * pszMdName, UCHAR * pszMaName,
                               USHORT usRmepId, UCHAR ucTtl, USHORT usTimeOut, ULONG ulID);

extern ULONG  TCPIP_1AG_UserPing(ULONG ulIfIndex, UCHAR *pucMacAddr, UCHAR * pszMdName,
                                  UCHAR * pszMaName, USHORT usRmepId,
                                  UCHAR *pBuffer, ULONG ulLen);


extern ULONG  TCPIP_1AG_VlanPriUserPing(TCPIP_1AG_USERPING_S *pst1agUserPing);


extern ULONG  TCPIP_RegFunc1AGOutInfo(OAM_1AG_OUTINFO_HOOK_FUNC pfEOAM_1AG_OutInfo);

extern ULONG  TCPIP_RegFunc1AGUserStop(OAM_1AG_STOP_HOOK_FUNC pfEOAM_1AG_Stop);

/*******************************************************************************
*    Func Name: TCPIP_1AG_SetVersion
* Date Created: 2009-03-26
*       Author: wangmingxia
*  Description: ���ڽӿ�����ʹ�õ�1AG�汾
*        Input: ULONG ulIfIndex:��̫�ӿڻ���TRUNK�ӿ�����
*               ULONG ulVersion:1AGʹ�õİ汾��,ȡֵ��Χ:0~1.
*                               0:��ʾʹ��Draft7�汾��1AGЭ��; 1��ʾʹ�ñ�׼�汾��1AGЭ��.
*                               Ĭ��ֵΪ0,��Draft7.
*       Output: ��
*       Return: VOS_OK:�ɹ�
*               ����:������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-26   wangmingxia             Create
*
*******************************************************************************/
extern ULONG TCPIP_1AG_SetVersion(ULONG ulIfIndex, ULONG ulVersion);

/*******************************************************************************
*    Func Name: TCPIP_1AG_GetVersion
* Date Created: 2009-03-26
*       Author: wangmingxia
*  Description: ���ڽӿڻ�ȡʹ�õ�1AG�汾
*        Input: ULONG ulIfIndex:��̫�ӿڻ���TRUNK�ӿ�����
*       Output: ULONG *pulVersion:1AGʹ�õİ汾��,ȡֵ��Χ:0~1.
*                               0:��ʾʹ��Draft7�汾��1AGЭ��; 1��ʾʹ�ñ�׼�汾��1AGЭ��.
*       Return: VOS_OK:�ɹ�
*               ����:������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-26   wangmingxia             Create
*
*******************************************************************************/
extern ULONG TCPIP_1AG_GetVersion(ULONG ulIfIndex, ULONG *pulVersion);

/*******************************************************************************
*    Func Name: TCPIP_1AG_SetRcvDefaultVlan
* Date Created: 2009-05-15
*       Author: wuhailan103194
*  Description: ����1AG���շ����Ĭ�ϴ���VLAN,�ڴ���LB/LT����ʱ,
*               ��������в���VLAN,��ֱ�ӴӸýӿ�Ĭ��VLAN�����жϴ���MD/MA
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulRcvDefaultVlan:���շ����Ĭ�ϴ���VLAN,0��ʾȡ�����õ�Ĭ��VLAN
*       Output: 
*       Return: VOS_OK:�ɹ�
*               ����:������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-05-15   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_1AG_SetRcvDefaultVlan(ULONG ulIfIndex, ULONG ulDefaultVlan);

/*******************************************************************************
*    Func Name: TCPIP_1AG_GetRcvDefaultVlan
* Date Created: 2009-05-15
*       Author: wuhailan103194
*  Description: ��ȡ1AG���շ����Ĭ�ϴ���VLAN
*        Input: ULONG ulIfIndex:�ӿ�����
*       Output: ULONG *pulDefaultVlan:���ص�Ĭ��VLANֵ.0��ʾû������Ĭ��VLAN
*       Return: VOS_OK:�ɹ�
*               ����:������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-05-15   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_1AG_GetRcvDefaultVlan(ULONG ulIfIndex, ULONG *pulDefaultVlan);


extern ULONG TCPIP_1AG_RegFuncMoreNoVlanNotify(OAM_1AG_MORENOVLANNOTIFY_HOOK_FUNC pfEoam1agMoreNoVlanNotifyFunc);


extern ULONG TCPIP_1AG_SetRmepCheck(UCHAR* pszMdName, UCHAR* pszMaName, USHORT usRmepId, ULONG ulSetYes);


extern ULONG TCPIP_1AG_GetRmepCheck(UCHAR* pszMdName, UCHAR* pszMaName, USHORT usRmepId, ULONG *pulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_1AG_SetFullCompatible
* Date Created: 2010-04-13
*       Author: wangbin (62223)
*  Description: Э���׼�����Կ���
*        Input: ULONG ulValue:0 -- �ر� 1-- ��
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   wangbin (62223)         Create
*
*******************************************************************************/
ULONG TCPIP_1AG_SetFullCompatible(ULONG ulValue);


/*******************************************************************************
*    Func Name: TCPIP_1AG_GetFullCompatible
* Date Created: 2010-04-13
*       Author: wangbin (62223)
*  Description: ��ȡЭ���׼�����Կ���
*        Input: ULONG *pulValue:Э���׼�����Կ���ֵ
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   wangbin (62223)         Create
*
*******************************************************************************/
ULONG TCPIP_1AG_GetFullCompatible(ULONG *pulValue);


/*******************************************************************************
*    Func Name: TCPIP_1AG_ShowFullCompatible
* Date Created: 2010-04-13
*       Author: wangbin (62223)
*  Description: ��ʾЭ���׼�����Կ���
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   wangbin (62223)         Create
*
*******************************************************************************/
VOID TCPIP_1AG_ShowFullCompatible(VOID);


/*******************************************************************************
*    Func Name: TCPIP_1AG_SetLossDetectInterval
* Date Created: 2010-04-13
*       Author: wangbin (62223)
*  Description: ���ñ���MEP��CCM Loss���ʱ��
*        Input: UCHAR *pszMdName:
*               UCHAR *pszMaName:
*               USHORT usMepId:
*               USHORT usInterval:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   wangbin (62223)         Create
*
*******************************************************************************/
ULONG TCPIP_1AG_SetLossDetectInterval(UCHAR *pszMdName, UCHAR *pszMaName, 
                                USHORT usMepId, USHORT usInterval);


/*******************************************************************************
*    Func Name: TCPIP_1AG_GetLossDetectInterval
* Date Created: 2010-04-13
*       Author: wangbin (62223)
*  Description: ��ȡ����MEP��CCM Loss���ʱ��
*        Input: UCHAR *pszMdName:MD
*               UCHAR *pszMaName:MA
*               USHORT usMepId:Mep Id
*               
*       Output: USHORT *pusInterval:����CCm Lost Detect Timer
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   wangbin (62223)         Create
*
*******************************************************************************/
ULONG TCPIP_1AG_GetLossDetectInterval(UCHAR *pszMdName, UCHAR *pszMaName, 
                                    USHORT usMepId, USHORT *pusInterval);



ULONG TCPIP_1AG_GetRmepWarnState(UCHAR * pszMdName, UCHAR * pszMaName,
                    USHORT usRmepId, OAM1AG_WARN_STATE_S * pst1agWarnState);
 

ULONG TCPIP_1AG_SetGlobalVersion(ULONG ulVersion);


ULONG TCPIP_1AG_GetGlobalVersion(ULONG *pulVersion);


VOID TCPIP_1AG_ShowGlobalVersion(VOID);


ULONG TCPIP_Y1731_EnableAIS(UCHAR *pucMdName,UCHAR *pucMaName,UCHAR ucEnable);


ULONG TCPIP_Y1731_EnablePMCheck(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, 
                        USHORT usRmepId,UCHAR ucPMType,UCHAR ucCheckFlag, ULONG ulSendInterval, ULONG ulTimeOut);



ULONG TCPIP_1AG_EnableRmepCCDetectEx(UCHAR* pszMdName, UCHAR* pszMaName, USHORT usRmepId, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_1AG_GetRMepStat
* Date Created: 2014-10-15
*       Author: likaikun213099
*  Description: ��ѯRMEP�յ���CCM��������
*        Input: UCHAR *pszMdName:
*               UCHAR * pszMaName:
*               USHORT usRMepId:
*               OAM_1AG_RMEP_STAT_S  *pstRMepPkt:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-10-15   likaikun213099          Create
*
*******************************************************************************/
ULONG  TCPIP_1AG_GetRMepStat(UCHAR *pszMdName, UCHAR * pszMaName, USHORT usRMepId, 
                                            OAM_1AG_RMEP_STAT_S  *pstRMepPkt);
                                            
/*******************************************************************************
*    Func Name: TCPIP_1AG_ClearRMepStat
* Date Created: 2014-10-15
*       Author: likaikun213099
*  Description: ���RMEP�յ���CCM��������
*        Input: UCHAR *pszMdName:
*               UCHAR * pszMaName:
*               USHORT usRMepId:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-10-15   likaikun213099          Create
*
*******************************************************************************/
ULONG  TCPIP_1AG_ClearRMepStat (UCHAR *pszMdName,UCHAR * pszMaName, USHORT usRMepId);

/*******************************************************************************
*    Func Name: TCPIP_1AG_ShowRMepStat
* Date Created: 2014-10-15
*       Author: likaikun213099
*  Description: ��ʾRMEP�յ���CCM��������
*        Input: UCHAR *pszMdName:
*               UCHAR * pszMaName:
*               USHORT usRMepId:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-10-15   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_1AG_ShowRMepStat(UCHAR *pszMdName, UCHAR * pszMaName, USHORT usRMepId);

/*******************************************************************************
*    Func Name: TCPIP_1AG_ShowAllMepInfoOnIf
* Date Created: 2014-11-08
*       Author: likaikun213099
*  Description: ��ʾָ���ӿ��ϵ�����MEP��RMEP
*        Input: CHAR* pszIfName:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-08   likaikun213099          Create
*
*******************************************************************************/
VOID TCPIP_1AG_ShowAllMepInfoOnIf(CHAR* pszIfName);

#ifdef  __cplusplus
}
#endif

#endif

