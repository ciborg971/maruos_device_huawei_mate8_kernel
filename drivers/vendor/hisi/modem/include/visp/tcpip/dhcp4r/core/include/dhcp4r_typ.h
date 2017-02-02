/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dchpr_typ.h
*
*  Project Code: VISPV1R6
*   Module Name: DHCP4R  
*  Date Created: 2007-6-27
*        Author: LY(57500)
*   Description: DHCP4Rģ������ݽṹ����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2007-6-27  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _DHCP4R_TYP_H_
#define _DHCP4R_TYP_H_

#ifdef __cplusplus
extern "C"{
#endif


/* 82ѡ�����ÿ��ƿ� */
typedef struct tagDHCP4ROption82
{
    /*ULONG   ul82SetFlag;  */      /* ��ѡ�����ñ�� */
    DHCP4R_SUBOPTION82_S astSubOption82[DHCP4R_82_SUB_NUM];   /* ��ѡ������ */
}DHCP4R_OPTION82_S;

/* relay���ÿ��ƿ� */
typedef struct tagDHCP4RCfgNode
{
    DLL_NODE_S          stDLLNode;
    ULONG               ulIfIndex;      /* ���ýӿ�����,���Ϊȫ�����ã���indexΪ0 */
    ULONG               ulRelayFlag;    /* relay�����ñ��      */
    ULONG               ulEnableStatus; /* ʹ��״̬             */    
    ULONG               ulServerNum;    /* ���õ��м̵�ַ��Ŀ   */
    ULONG               aulServer[DHCP4R_SERVER_MAX_NUM];   /* �м̵�ַ���� */
    DHCP4R_OPTION82_S   stOption82;     /* 82ѡ������   */
    ULONG               ulOpt82Mode;     /* 82ѡ��ģʽ*/ 
}DHCP4R_CFG_NODE_S;

/* �ӿڵ��Կ��ؿ��ƿ� */
typedef struct tagDHCP4RDebug
{
    DLL_NODE_S          stDLLNode;
    ULONG               ulIfIndex;    
    ULONG               ulDebug;
}DHCP4R_DEBUG_NODE_S;  

#define     DLLDHCP4RCFG(x)      ((DHCP4R_CFG_NODE_S *)(x)) 
#define     DLLDHCP4RDEBUG(x)    ((DHCP4R_DEBUG_NODE_S *)(x))  


/* Shell��Coreע��Ļص������� */
typedef struct tagDHCP4RShellCallbackSet
{
    /* ������Ϣ������� */
    VOID (*pfDHCP4R_DebugOutString) (CHAR * szStr);
}DHCP4R_SHELL_CALLBACK_SET_S;


/* Ϊ֧��VRF���Զ����ӵ����ݽṹ */
typedef struct tagDHCP4RCfgVrfEntry
{
    ULONG   ulVrfIndex;               /* ʵ���� */    
    DLL_S   stDhcp4rCfgList;          /* ��ʵ���ӿ��������� */
    ULONG   ulDHCP4RFwdMode;          /* ��ʵ���м̷�ʽ,����ֵ0,�ֵ���ʽ */
    ULONG   ulDHCP4RMaxHops;          /* ��ʵ�� ���RELAY����,����ֵΪ16 */
    UCHAR   ucDHCP4RTos;              /* ��ʵ��TOSֵ,Ĭ��Ϊ0 */
    UCHAR   ucDHCP4RCfgMode;          /* ��ʵ��Relay ���÷�ʽ��ȫ��(1),�ӿ�(0) */
    UCHAR   ucpad[2];
    DHCP4R_STATINFO_S stDhcp4rStat;   /* ��ʵ��ͳ����Ϣ */
}DHCP4R_CFG_VRF_S;

typedef struct tagDHCP4RDbgVrfEntry
{
    ULONG   ulVrfIndex;               /* ʵ���� */
    DLL_S   stDhcp4rDebugList;        /* ��ʵ��Debug�������� */
    ULONG   ulDHCP4RGlobalDebug;      /* ��ʵ��ȫ�ֵ��Կ��� */ 
}DHCP4R_DBG_VRF_S;

#ifdef __cplusplus
}
#endif      /* end of _cplusplus        */

#endif      /* end of _DHCP4R_TYP_H_    */

