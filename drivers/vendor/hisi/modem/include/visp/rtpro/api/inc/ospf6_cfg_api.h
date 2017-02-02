/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf6_cfg_api.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2009-07-13
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-07-13   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _OSPF6_CFG_API_H_
#define _OSPF6_CFG_API_H_
    
#ifdef __cplusplus
        extern "C"{
#endif /* __cplusplus */

/*STRUCT<����OSPF6���̽ṹ��>*/
typedef struct tagOSPF6_CFGPROC
{
    USHORT bNoFlag;                               /*0 - ����
                                                    1 - ɾ��*/
    USHORT usProcessId;                           /*����ID,ȡֵ��Χ:1-0xffff*/
    ULONG  ulRouterId;                            /*Router ID��������,ȡֵ��Χ:1-0xffffffff*/
    UCHAR  ucVrfName[OSPF6_MAX_VRFNAME_LENGTH+1]; /*VPN��,�ǿ�*/
}OSPF6_CFGPROC_S;

/*STRUCT<����OSPF6����ṹ��>*/
typedef struct tagOSPF6_CFGAREA
{
    USHORT bNoFlag;                               /*0 - ����
                                                    1 - ɾ��*/
    USHORT usProcessId;                           /*����ID,ȡֵ��Χ:1-0xffff*/
    ULONG  ulAreaId;                              /*����ID,ȡֵ��Χ:0-0xffffffff*/ 
}OSPF6_CFGAREA_S;

/*STRUCT<����OSPF6 Interface�ṹ��>*/
typedef struct tagOSPF6_CFGINTF
{ 
    USHORT bNoFlag;                              /*0 - ����
                                                   1 - ɾ��*/
    USHORT usProcessId;                          /*����ID,ȡֵ��Χ:1-0xffff*/
    ULONG  ulAreaId;                             /*����ID,ȡֵ��Χ:0-0xffffffff*/ 
    ULONG  ulInstanceId;                         /*ʵ��ID,ȡֵ��Χ:0-255*/ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*�ӿ���,�ǿ�*/ 
} OSPF6_CFGINTF_S;

/*STRUCT<����Interface��OSPF6 Network Type�ṹ��>*/
typedef struct tagOSPF6_CFGINTF_NETTYPE
{ 
    USHORT bNoFlag;                              /*0 - ����
                                                   1 - ɾ��*/
    UCHAR  ucPadding[2];                         /*���*/
    ULONG  ulInstanceId;                         /*ʵ��ID,ȡֵ��Χ:0-255*/ 
    ULONG  ulNetType;                            /*��������,ȡֵ��Χ:
                                    #define OSPF6_NETWORK_BROADCAST       1 
                                    #define OSPF6_NETWORK_NBMA            2
                                    #define OSPF6_NETWORK_POINT_TO_POINT  3 
                                    #define OSPF6_NETWORK_POINT_T_MLTPNT  5
                                                */ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*�ӿ���,�ǿ�*/ 
}OSPF6_CFGINTF_NETTYPE_S;

/*STRUCT<����Interface��OSPF6 Cost�ṹ��>*/
typedef struct tagOSPF6_CFGINTF_COST
{ 
    USHORT bDefFlag;                             /*0 - ����
                                                   1 - �ָ�Ĭ��ֵ*/
    UCHAR  ucPadding[2];                         /*���*/
    ULONG  ulInstanceId;                         /*ʵ��ID,ȡֵ��Χ:0-255*/ 
    ULONG  ulCost;                               /*·�����ۣ�Ĭ��1 
                                                   ��Χ:1~65535*/
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*�ӿ���,�ǿ�*/ 
}OSPF6_CFGINTF_COST_S;

/*STRUCT<����Interface��OSPF6 ���ȼ��ṹ��>*/
typedef struct tagOSPF6_CFGINTF_PRIORITY 
{ 
    USHORT bDefFlag;                             /*0 - ����
                                                   1 - �ָ�Ĭ��ֵ*/
    UCHAR  ucPadding[2];                         /*���*/
    ULONG  ulInstanceId;                         /*ʵ��ID,ȡֵ��Χ:0-255*/ 
    ULONG  ulPriority;                           /*���ȼ���Ĭ��1
                                                    ��Χ:0~255������0��ʾ������DRѡ�٣�
                                                    ��Ҫ�ر�������������ֵԽ�����ȼ�Խ��*/
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*�ӿ���,�ǿ�*/ 
}OSPF6_CFGINTF_PRIORITY_S;

/*STRUCT<����Interface��OSPF6 MTU Ignore���ܽṹ�壬Ĭ��Ϊ�ر�>*/
typedef struct tagOSPF6_CFGMTU_IGNORE_S 
{ 
    USHORT bDefFlag;                             /*? - ����
                                                   1 - �ָ�Ĭ��ֵ*/
    UCHAR  ucPadding[2];                         /*���*/
    ULONG  ulInstanceId;                         /*ʵ��ID,ȡֵ��Χ:0-255*/ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*�ӿ���,�ǿ�*/ 
}OSPF6_CFGMTU_IGNORE_S;

/*STRUCT<����Interface��OSPF6 Retransmit Interval�ṹ��>*/
typedef struct tagOSPF6_CFGRXMT_ITVL_S 
{ 
    USHORT bDefFlag;                             /*0 - ����
                                                   1 - �ָ�Ĭ��ֵ*/
    UCHAR  ucPadding[2];                         /*���*/
    ULONG  ulInstanceId;                         /*ʵ��ID,ȡֵ��Χ:0-255*/ 
    ULONG  ulRxmtInterval;                       /*�ش������Ĭ��5s
                                                   ��Χ:1~1800*/ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*�ӿ���,�ǿ�*/ 
}OSPF6_CFGRXMT_ITVL_S;

/*STRUCT<����Interface��OSPF6 Transmission Delay�ṹ��>*/
typedef struct tagOSPF6_CFGTRANSDELAY 
{ 
    USHORT bDefFlag;                             /*0 - ����
                                                   1 - �ָ�Ĭ��ֵ*/
    UCHAR  ucPadding[2];                         /*���*/
    ULONG  ulInstanceId;                         /*ʵ��ID,ȡֵ��Χ:0-255*/ 
    ULONG  ulTransDelay;                         /*����ʱ�ӣ�Ĭ��1s
                                                   ��Χ:1~1800*/  
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*�ӿ���,�ǿ�*/ 
}OSPF6_CFGTRANSDELAY_S;

/*STRUCT<����Interface��OSPF6 Hello Interval�ṹ��>*/
typedef struct tagOSPF6_CFGHELLO_ITVL 
{ 
    USHORT bDefFlag;                             /*0 - ����
                                                   1 - �ָ�Ĭ��ֵ*/
    UCHAR  ucPadding[2];                         /*���*/
    ULONG  ulInstanceId;                         /*ʵ��ID,ȡֵ��Χ:0-255*/ 
    ULONG  ulHelloInterval;                      /*hello���ķ��ͼ����Ĭ��10s
                                                    ��Χ:1~65535*/ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*�ӿ���,�ǿ�*/ 
}OSPF6_CFGHELLO_ITVL_S;

/*STRUCT<����Interface��OSPF6 Dead Interval�ṹ��>*/
typedef struct tagOSPF6_CFGDEAD_ITVL 
{ 
    USHORT bDefFlag;                             /*0 - ����
                                                   1 - �ָ�Ĭ��ֵ*/
    UCHAR  ucPadding[2];                         /*���*/
    ULONG  ulInstanceId;                         /*ʵ��ID,ȡֵ��Χ:0-255*/ 
    ULONG  ulDeadInterval;                       /*Dead�����Ĭ��40s
                                                    ��Χ:1~65535*/
    ULONG  ulFast_Hello_Multiplier;              /*������ʹ��fast hello��
                                                    1s�ڷ���hello���ĵ���Ŀ 
                                                    ȡֵ��Χ:3-20 Ĭ��ֵ5*/
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*�ӿ���,�ǿ�*/ 
}OSPF6_CFGDEAD_ITVL_S;

/*STRUCT<����Interface��Poll Interval�ṹ��>*/
typedef struct tagOSPF6_CFGPOLL_ITVL
{
    USHORT bDefFlag;                             /*0 - ����
                                                   1 - �ָ�Ĭ��ֵ*/
    UCHAR  ucPadding[2];                         /*���*/
    ULONG  ulInstanceId;                         /*ʵ��ID,ȡֵ��Χ:0-255*/ 
    ULONG  ulPollInterval;                       /*Poll Interval(S)��Ĭ��120*/
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*�ӿ���,�ǿ�*/ 
}OSPF6_CFGPOLL_ITVL_S;

/*STRUCT<��������NSSA���Խṹ��>*/
typedef struct tagOSPF6_CFGAREA_NSSA
{
    USHORT bNoFlag;                         /*0 - ����
                                              1 - �ָ�*/
    USHORT usProcessId;                     /*����ID,ȡֵ��Χ:1-0xffff*/
    ULONG  ulAreaId;                        /*����ID,ȡֵ��Χ:1-0xffffffff*/ 
    UCHAR  ucNssaOption;                    /*NSSAѡ��,Bitλ��Ч,ȡֵ����
                                                OSPF6_AREA_NSSAOPT_NOSUMMARY
                                                OSPF6_AREA_NSSAOPT_NOIMPORT*/
    UCHAR  ucPadding[3];                    /*���*/
}OSPF6_CFGAREA_NSSA_S;

/*STRUCT<����OSPF6 Stub����>*/
typedef struct tagOSPF6_CFGAREASTUB 
{ 
    USHORT bNoFlag;                         /*0 - ����
                                              1 - �ָ�*/
    USHORT usProcessId;                     /*����ID,ȡֵ��Χ:1-0xffff*/
    ULONG  ulAreaId;                        /*����ID,ȡֵ��Χ:1-0xffffffff*/
    USHORT usSummaryFlag;                   /*Stub ѡ��,��ֵ��Ч,����
                                              �Ƿ�����summary lsa��stub��
                                              Ĭ��OSPF6_SUMM_SEND_AREA_SUMMARY
                                              OSPF6_SUMM_NO_AREA_SUMMARY - ������Summary
                                              OSPF6_SUMM_SEND_AREA_SUMMARY - ����Summary*/
    UCHAR  ucPadding[2];                    /*���*/
}OSPF6_CFGAREASTUB_S;

/*STRUCT<��������ۺϽṹ��>*/
typedef struct tagOSPF6_CFGAREA_AGG
{ 
    USHORT bNoFlag;                         /*0 - ����
                                              1 - ɾ��*/
    USHORT usProcessId;                     /*����ID,ȡֵ��Χ:1-0xffff*/
    ULONG  ulAreaId;                        /*����ID,ȡֵ��Χ:0-0xffffffff*/
    INET6_ADDRESS_S stPrefix;               /*ǰ׺����,��Χ :3~128*/ 
    ULONG  ulAdvert;                        /*�Ƿ�ͨ���־,ȡֵ����:
                                              OSPF6_AGG_ADVRTISE - ͨ��
                                              OSPF6_AGG_DO_NOT_ADVRTISE - ��ͨ��*/ 
}OSPF6_CFGAREA_AGG_S; 

/*STRUCT<����OSPF6 Stub/NSSA�����Ĭ��Cost>*/
typedef struct tagOSPF6_CFGSTUBAREA_COST 
{ 
    USHORT bDefFlag;                             /*0 - ����
                                                   1 - �ָ�Ĭ��ֵ*/
    USHORT usProcessId;                          /*����ID,ȡֵ��Χ:1-0xffff*/
    ULONG  ulAreaId;                             /*����ID,ȡֵ��Χ:0-0xffffffff*/
    ULONG  ulAreaDefCost;                        /*Ĭ��Costֵ��Ĭ��ȡֵ1, 
                                                    ��Χ:0~OSPF6_MAX_AREA_COST_VALUE*/ 
} OSPF6_CFGSTUBAREA_COST_S;

/*STRUCT<����OSPF6 �����LSA���·����ʱ����Reflood Interval>*/
typedef struct OSPF6_CFGAREA_RFSHITVL
{
    USHORT bDefFlag;                             /*0 - ����
                                                   1 - �ָ�Ĭ��ֵ*/
    USHORT usProcessId;                          /*����ID,ȡֵ��Χ:1-0xffff*/
    ULONG  ulAreaId;                             /*����ID,ȡֵ��Χ:0-0xffffffff*/
    ULONG  ulRfshInterval;                       /*�鷺���(S)��Ĭ��1800, 
                                                    ��Χ:1~3599*/
} OSPF6_CFGAREA_RFSHITVL_S;

/*STRUCT<����OSPF6���̵�SPF��ʱʱ��>*/
typedef struct tagOSPF6_CFGSPF_TIMERS 
{ 
    USHORT bDefFlag;                             /*0 - ����
                                                   1 - �ָ�Ĭ��ֵ*/
    USHORT usProcessId;                          /*����ID,ȡֵ��Χ:1-0xffff*/
    ULONG  ulDelay;                              /*SPF������ʱʱ��(DCL�ڲ�Point)��Ĭ��5000
                                                    ��Χ:1~OSPF6_MAX_SPF_TIME*/ 
    ULONG  ulPause;                              /*SPF�����ж�ʱ��(DCL�ڲ�Point)��Ĭ��10000
                                                   ��Χ:0~OSPF6_ERR_MAX_SPF_DELAY_TIME
                                                   0 - ÿ�����㲽�趼�ᱻ���
                                                   0xFFFFFFFF - ��Զ���ᱻ���*/ 
} OSPF6_CFGSPF_TIMERS_S;

/*STRUCT<����OSPF6���̵����ƽ��·������>*/
typedef struct tagOSPF6_CFGMAX_LOAD_BALANCE 
{ 
    USHORT bDefFlag;                             /*0 - ����
                                                   1 - �ָ�Ĭ��ֵ*/
    USHORT usProcessId;                          /*����ID,ȡֵ��Χ:1-0xffff*/
    USHORT usPathCount;                          /*ƽ��·��������Ĭ��5
                                                   ��Χ:1~OSPF6_MAX_EQCOST_PATH*/ 
    UCHAR  ucPadding[2];                         /*���*/
} OSPF6_CFGMAX_LOAD_BALANCE_S;

/*STRUCT<����OSPF6���̵Ĵ���>*/
typedef struct tagOSPF6_CFGPREFERENCE 
{ 
    USHORT bDefFlag;                             /*0 - ����
                                                   1 - �ָ�Ĭ��ֵ*/
    USHORT usType;                               /*�������ͣ�
                                                    ��Χ:1~3
                                                   OSPF6_PREFERENCE_TYPE_INT - ������������·���ϵĴ���
                                                   OSPF6_PREFERENCE_TYPE_EXT - �������ⲿ·���ϵĴ���*/
    UCHAR  ucPreferenceInt;                      /*������·���ϵĴ��ۣ�Ĭ��ֵ30
                                                   ��Χ:1~255*/
    UCHAR  ucPreferenceExt;                      /*�ⲿ·���ϵĴ��ۣ�Ĭ��ֵ110
                                                   ��Χ:1~255*/
    UCHAR  ucPadding[2];                         /*���*/
    CHAR   szVrfName[OSPF6_MAX_VRFNAME_LENGTH + 1]; /*VRF��,�ǿ�*/
} OSPF6_CFGPREFERENCE_S;

/*STRUCT<OSPF6·��������Ծ�����Ϣ>*/
typedef struct tagOSPF6_RPM_PLCYREDIS
{
    UCHAR  ucProtoType;                     /* Э��ID����,ȡֵ����:
                                               #define RM_PROTO_CONNECTED  0x2  
                                               #define RM_PROTO_STATIC     0x3
                                               #define RM_PROTO_RIPNG      0x18
                                               #define RM_PROTO_OSPF6      0x1D
                                            */
    UCHAR  ucPadding;                       /*���*/
    USHORT usProcessId;                     /*������˵Ľ���ID,ȡֵ��Χ:1-0xffff*/
    ULONG  ulMetricType;                    /*Metric����:1��ʾTYPE1, 2��ʾTYPE2*/
    ULONG  ulMetricVal;                     /*Metricֵ��Ĭ��ֵ1
                                                      0 - ������Metricֵ*/
} OSPF6_RPM_PLCYREDIS_S;

/*STRUCT<����OSPF6·���������*/
typedef struct tagOSPF6_CFGREDISTRIBUTE
{
    USHORT bNoFlag;                         /*  0 - ����
                                                1 - ɾ��*/
    USHORT usProcessId;                     /*���ý���ID,ȡֵ��Χ��1-0xffff*/
    OSPF6_RPM_PLCYREDIS_S stPolicyRedist;   /*�������,ȡֵ��Χ���ǿ�*/
} OSPF6_CFGREDISTRIBUTE_S;

/*STRUCT<����OSPF6·������/���չ��˲�����Ϣ>*/
typedef struct tagOSPF6_RPM_PLCYDIST
{
    USHORT usProcessId;                     /*����ID ���ڽ��չ�����˵��
                                              ���ֶ���Ч,ȡֵ��Χ:1-0xffff*/
    UCHAR  ucProtocolID;                    /*Э��ID����,ȡֵ����:
                                                       #define RM_PROTO_CONNECTED  0x2  
                                                       #define RM_PROTO_STATIC     0x3
                                                       #define RM_PROTO_RIPNG      0x18
                                                       #define RM_PROTO_OSPF6      0x1D
                                                       Protocol ID  ���ڽ��չ�����˵��
                                                      ���ֶ���Ч*/
    UCHAR  ucPadding;                       /*���*/
    union
    {
        ULONG ulAclNum;                     /*ACL6�������
                                              ��Χ:2000~2999*/
    } stFltrName;   
    union
    {
        ULONG ulAclNum;                     /*ACL6�������
                                              ��Χ:2000~2999*/
    } stHopFltrName;
} OSPF6_RPM_PLCYDIST_S;

/*STRUCT<����OSPF6·������/���չ���>*/
typedef struct tagOSPF6_CFGDISTRIBUTE
{
    USHORT bNoFlag;                         /*0 - ����
                                              1 - ɾ��*/
    USHORT usProcessId;                     /*����ID,ȡֵ��Χ��1-0xffff*/
    OSPF6_RPM_PLCYDIST_S stPolicyDist;      /*����/���չ���,ȡֵ��Χ:�ǿ�*/
} OSPF6_CFGDISTRIBUTE_S;

/*STRUCT<���þ�̬OSPF6�ھ�>*/
typedef struct tagOSPF6_CFGPEER
{
    USHORT bNoFlag;                             /*0 - ����
                                                  1 - ɾ��*/
    UCHAR  ucPadding[2];                        /*���*/
    ULONG  ulInstanceId;                        /*ʵ��ID,ȡֵ��Χ:0-255*/ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1];/*�ӿ���,�ǿ�*/ 
    UCHAR  ucAddress[OSPF6_MAX_INET_ADDR_LEN];  /*�Զ�LinkLocal��ַ*/
    ULONG  ulPriOpFlag;                         /*�û��������ȼ�ѡ��
                                                0 - ����
                                                1 - ������*/    
    ULONG  ulPriority;                          /*���ȼ���Ĭ��ֵ1
                                                ��Χ:0~0xFF,0Ϊ������DRѡ��*/
} OSPF6_CFGPEER_S;

/*S-IP-003-OSPFv3-005 ����OSPFv3 ����GR����*/

/*Hitless Restart Reason*/
#define OSPF6_RESTART_REASON_UNKNOWN 0
#define OSPF6_RESTART_REASON_SOFTWARE_RESTART 1
#define OSPF6_RESTART_REASON_SOFTWARE_RELOAD  2
#define OSPF6_RESTART_REASON_SWITCH_TO_BACKUP 3

#define OSPF6_GR_MIN_PERIOD 1          /*��СGR����ʱ�� 1s*/
#define OSPF6_GR_MAX_PERIOD 1800       /*���GR����ʱ�� 1800s*/

typedef struct tagOSPF6_CFG_GR 
{ 
    USHORT usProcessId;                 /*����ID*/
    UCHAR  ucPad[2];
    ULONG ulDoGraceHitless;            /*ƽ��������־*/
    ULONG ulDoGraceUnplannedHitless;  /*�޼ƻ���ƽ��������־*/
    ULONG ulHitlessGrPeriod;           /*ƽ����������*/
    ULONG ulhitlessGrReason;           /*ƽ������ԭ��*/
} OSPF6_CFG_GR_S;

typedef struct tagOSPF6_CFG_GRHELPER
{
    UCHAR szIfname[OSPF6_MAX_IF_NAME_LENGTH+1];          /*�ӿ�����*/
    ULONG ulInstanceId;                                 /*�ӿ�ʵ����*/
    ULONG ulHelperMode;                                 /*Gr Helperģʽ*/
    ULONG ulGrPeriod;                                   /*���õȴ�Grʱ��*/
    ULONG ulAccNum;                                     /*���ù������*/
    
}OSPF6_CFG_GRHELPER_S;

/*S-IP-004-OSPFv3-003*/
typedef struct tagOSPF6_CFGGRHELPER
{
    USHORT usProcessId;
    USHORT usPad;
    ULONG ulHelperMode;
    ULONG ulGrPeriod;
    ULONG ulAccNum;
}OSPF6_CFGGRHELPER_PRO_S;



typedef ULONG(*OSPF6_PACKET_HOOK_FUNC)(USHORT usProcId, ULONG ulIfIndex, CHAR *pcPacket, ULONG ulLen);

/*******************************************************************************
*    Func Name: OSPF6_CFG_Proc
* Date Created: 2009-06-16
*       Author: qinyun62011
*      Purpose: ����/ɾ��OSPF6����
*  Description: ����/ɾ��OSPF6����,��ָ����Ӧ��route ID;��֧�ֽ��̹����Ϊ:32
*        Input: OSPF6_CFGPROC_S *pstProcIn:����������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: ָ����VrfName �����ȴ����������ָ��VrfName��ʾΪ����
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-16   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_Proc(OSPF6_CFGPROC_S *pstProcIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_Intf
* Date Created: 2009-06-16
*       Author: qinyun62011
*      Purpose: ����/ɾ��OSPF6�����еĽӿ�
*  Description: ����/ɾ��OSPF6������ӿ�,ʵ���İ󶨲���,Ŀǰֻ֧����eth/trunk/ppp/mp��·�ϰ󶨽�����Ϣ
*        Input: OSPF6_CFGINTF_S *pstIntfIn:�ӿ�������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: ͬһ���ӿ��ϰ󶨵Ľ��̺�ʵ����Ϣ���벻ͬ����ͬ�ӿ��Ͽ��԰���ͬ�Ľ�����ʵ����Ϣ
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-16   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_Intf(OSPF6_CFGINTF_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_IntfNetType
* Date Created: 2009-06-16
*       Author: qinyun62011
*      Purpose: ����/�ָ�OSPF6�ӿڵ���������.
*  Description: ����/�ָ�OSPF6�ӿڵ���������,
*               ������NBMA����P2MP��������ʱ,Ĭ��Hello���Ϊ30s,Dead���Ϊ120s;
*               ������BROADCAST����P2P��������ʱ,Ĭ��Hello���Ϊ10s,Dead���Ϊ30s.
*        Input: OSPF6_CFGINTF_NETTYPE_S *psNetTypeIn:�ӿ���������������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: ����ı���������ǰ,Hello�����Dead����û����Ѿ�ָ��,
*               ��ô�������͸ı�ʱ�������Զ��ı�����������;
*               ����ı���������ǰ,Hello����û��Ѿ�ָ��,����Dead����û�û��ָ��,
*               ��ô�������͸ı�ʱ,Hello�������,Dead�������Hello���4��;
*               ����ı���������ǰ,Dead����û��Ѿ�ָ��,����Hello����û�û��ָ��,
*               ��ô�������͸ı�ʱ,Dead�������,Hello���Ϊ�������͸ı��ĳ�ʼֵ.              
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-16   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_IntfNetType(OSPF6_CFGINTF_NETTYPE_S *psNetTypeIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_IntfCost
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/�ָ��ӿڵ�OSPF6 Cost.
*  Description: ����/�ָ��ӿڵ�OSPF6 ·�ɻ���ֵ.
*        Input: OSPF6_CFGINTF_COST_S * pstIfCostIn:�ӿ�Cost������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_IntfCost(OSPF6_CFGINTF_COST_S * pstIfCostIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_IntfPriority
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/�ָ��ӿڵ�OSPF6 ���ȼ�.
*  Description: ����/�ָ��ӿڵ�OSPF6 ���ȼ�,�����ȼ�ֱ�Ӳ���·������DRѡ����,
*               ���ȼ��ϸ���,��ѡ��ΪDR.
*        Input: OSPF6_CFGINTF_PRIORITY_S *pstIfPriorityIn:�ӿ����ȼ�������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: ���ȼ���ֵԽ��Խ����.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_IntfPriority(OSPF6_CFGINTF_PRIORITY_S *pstIfPriorityIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_MtuIgnore
* Date Created: 2009-06-16
*       Author: qinyun62011
*      Purpose: ����/�ָ��ӿڵ�OSPF6 MTU Ignore����.
*  Description: ����/�ָ��ӿڵ�OSPF6 MTU Ignore����,MTUֱֵ�ӹ�ϵ���ھӹ�ϵ����,
*               Ĭ�������MTUֵ��ͬ,��OSPFv3·�������޷��ɹ������ھӹ�ϵ;
*               ������MTUֵ���Թ���,��OSPFv3·�����䲻��MTUֵ��ͬ��񶼳ɹ������ھӹ�ϵ.
*        Input: OSPF6_CFGMTU_IGNORE_S *pstMtuIgnIn:MTU Ignore����������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: �ھ��Ѿ��ɹ�������,�ı�MTUֵ,����/�ָ��ӿ�MTU Ignore���ܶ�ֻ�ܵ�
*               ��һ�ֽ����ھӹ��̷�������;
*               ����ӿ�ȥ�󶨽������ﵽ�ھ����½�����Ŀ��.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-16   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_MtuIgnore(OSPF6_CFGMTU_IGNORE_S *pstMtuIgnIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_RxmtItvl
* Date Created: 2009-06-16
*       Author: qinyun62011
*      Purpose: ����/�ָ��ӿڵ�OSPF6 Retransmission Interval.
*  Description: ����/�ָ��ӿڵ�OSPF6 Retransmission Interval,��LSA�ش����;
*               Ϊ��ȷ���鷺�Ŀɿ��ԣ�LSA�����ش�ֱ���յ�ȷ�ϡ�
*        Input: OSPF6_CFGRXMT_ITVL_S *pstRxItvlIn:Retransmission Interval������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: �ӿ��ش��������̫��,����ɲ���Ҫ�ش�;
*               �ӿ��ش��������̫��,�ڶ���ʱ�ͻ�Ӱ��鷺���ٶ�.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-16   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_RxmtItvl(OSPF6_CFGRXMT_ITVL_S *pstRxItvlIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_TransDelay
* Date Created: 2009-06-16
*       Author: qinyun62011
*      Purpose: ����/�ָ��ӿڵ�OSPF6 Transmission Delay.
*  Description: ����/�ָ��ӿڵ�OSPF6 Transmission Delay,��LSA����ʱ��;
*               �ӿڴ���һ��LSU������Ҫ������.
*        Input: OSPF6_CFGTRANSDELAY_S *pstTrDlyIn:Transmission Delay������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-16   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_TransDelay(OSPF6_CFGTRANSDELAY_S *pstTrDlyIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_HelloItvl
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/�ָ��ӿڵ�OSPF6 Hello Interval.
*  Description: ����/�ָ��ӿڵ�OSPF6 Hello Interval,��Hello���ļ��ʱ��.
*               ������NBMA����P2MP��������ʱ,Ĭ��Hello���Ϊ30s,Dead���Ϊ120s;
*               ������BROADCAST����P2P��������ʱ,Ĭ��Hello���Ϊ10s,Dead���Ϊ30s.
*        Input: OSPF6_CFGHELLO_ITVL_S* pstHelloItvlIn:Hello Interval������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: ����ı���������ǰ,Hello�����Dead����û����Ѿ�ָ��,
*               ��ô�������͸ı�ʱ�������Զ��ı�����������;
*               ����ı���������ǰ,Hello����û��Ѿ�ָ��,����Dead����û�û��ָ��,
*               ��ô�������͸ı�ʱ,Hello�������,Dead�������Hello���4��;
*               ����ı���������ǰ,Dead����û��Ѿ�ָ��,����Hello����û�û��ָ��,
*               ��ô�������͸ı�ʱ,Dead�������,Hello���Ϊ�������͸ı��ĳ�ʼֵ.              
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_HelloItvl(OSPF6_CFGHELLO_ITVL_S* pstHelloItvlIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_DeadItvl
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/�ָ��ӿڵ�OSPF6 Dead Interval.
*  Description: ����/�ָ��ӿڵ�OSPF6 Dead Interval,��Dead���ʱ��.
*               ������NBMA����P2MP��������ʱ,Ĭ��Hello���Ϊ30s,Dead���Ϊ120s;
*               ������BROADCAST����P2P��������ʱ,Ĭ��Hello���Ϊ10s,Dead���Ϊ30s.
*               ��Dead���ʱ��Ϊ1sʱ,��ζ��������FastHello����,
*               Fast_Hello_Multiplier�ֶξ���FastHello���ķ���Ƶ��.
*        Input: OSPF6_CFGDEAD_ITVL_S *pstDeadItvlIn:Dead Interval������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: ����ı���������ǰ,Hello�����Dead����û����Ѿ�ָ��,
*               ��ô�������͸ı�ʱ�������Զ��ı�����������;
*               ����ı���������ǰ,Hello����û��Ѿ�ָ��,����Dead����û�û��ָ��,
*               ��ô�������͸ı�ʱ,Hello�������,Dead�������Hello���4��;
*               ����ı���������ǰ,Dead����û��Ѿ�ָ��,����Hello����û�û��ָ��,
*               ��ô�������͸ı�ʱ,Dead�������,Hello���Ϊ�������͸ı��ĳ�ʼֵ.              
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_DeadItvl(OSPF6_CFGDEAD_ITVL_S *pstDeadItvlIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_PollItvl
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/�ָ��ӿڵ�Poll Interval.
*  Description: ����/�ָ��ӿڵ�Poll Interval,��Poll���ʱ��.���ֶν���NBMA�����е��ھ���Ч,
*               �ھ�״̬Down,ÿ��PollInterval�뷢��Hello��;
*               ����״̬ʱ,ÿ��HelloInterval�뷢��Hello��.
*        Input: OSPF6_CFGPOLL_ITVL_S *pstPollItvlIn:Poll Interval������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: ����NBMA�����е��ھ���Ч.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_PollItvl(OSPF6_CFGPOLL_ITVL_S *pstPollItvlIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_AreaNssa
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/ȡ������ΪNSSA����.
*  Description: ����/ȡ������ΪNSSA����,����NSSA���Ե������ܾ�5��LSA��ɢ;
*               ��������NSSA����ͬʱ������׷������ѡ����no-summaryѡ��ܾ�3��/4��LSA��ɢ;
*               ��������NSSA����ͬʱ������׷������ѡ����no-importѡ����ѡ���Ƿ�Ҫ��7��LSAת��Ϊ5��LSA.
*        Input: OSPF6_CFGAREA_NSSA_S *pstAreaNssaIn:NSSA����������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: no-importѡ������ֻ����������߽�·������,·�������ø�ѡ���,�ͽ�7��LSAת��Ϊ5��LSA;
*               ·���������ø�ѡ��,�����ݼ�̨�߽�·��������ѡһ̨����7��LSAת��Ϊ5��LSA;
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_AreaNssa(OSPF6_CFGAREA_NSSA_S *pstAreaNssaIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_AreaStub
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/ȡ������ΪSTUB����.
*  Description: ����/ȡ������ΪSTUB����,����STUB���Ե������ܾ�5��LSA��ɢ;
*        Input: OSPF6_CFGAREASTUB_S *pstAreaStubIn:STUB����������Ϣ
*               ��������STUB����ͬʱ������׷������ѡ����no-summaryѡ��ܾ�3��/4��LSA��ɢ;
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_AreaStub(OSPF6_CFGAREASTUB_S *pstAreaStubIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_StubAreaCost
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/�ָ�OSPF6 STUB/NSSA����Ĭ��Costֵ.
*  Description: ����/�ָ�OSPF6 STUB/NSSA����Ĭ��Costֵ,��STUB/NSSA����Ĭ��·��metricֵ.
*        Input: OSPF6_CFGSTUBAREA_COST_S * pstAreaCostIn:Ĭ��Costֵ������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: ���STUB/NSSA������Ч.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_StubAreaCost(OSPF6_CFGSTUBAREA_COST_S * pstAreaCostIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_AreaRfshItvl
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/�ָ�OSPF6����LSA��Reflood Interval.
*  Description: ����/�ָ�OSPF6����LSA��Reflood Interval,��LSA���·���ʱ����.
*        Input: OSPF6_CFGAREA_RFSHITVL_S *pstAreaRfshItvlIn:Reflood Interval������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: �������������Ч.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_AreaRfshItvl(OSPF6_CFGAREA_RFSHITVL_S *pstAreaRfshItvlIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_AreaAgg
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/ɾ������ۺ�
*  Description: ����/ɾ������ۺ�,���þۺϺ�ֻ������������ڵ�·�ɲŻ�ۺ�
*        Input: OSPF6_CFGAREA_AGG_S *pstAreaAggIn:����ۺ�������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: ����ֻ֧��3��lsa�ľۺ�ʵ��
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_AreaAgg(OSPF6_CFGAREA_AGG_S * pstAreaAggIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_SpfTimers
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/�ָ�OSPF6����SPF��ʱʱ��.
*  Description: ����/�ָ�OSPF6����SPF��ʱʱ��,����SPF������ʱʱ���SPF�����ж�ʱ��.
*        Input: OSPF6_CFGSPF_TIMERS_S * pstSpftimersIn:SPF��ʱʱ��������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: ������λ������,����DCL�ڲ�Point.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_SpfTimers (OSPF6_CFGSPF_TIMERS_S * pstSpftimersIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_MaxLoadBalance
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/�ָ�OSPF6���̵����ƽ��·������.
*  Description: ����/�ָ�OSPF6���̵����ƽ��·������.
*        Input: OSPF6_CFGMAX_LOAD_BALANCE_S * pstMaxLoadBalanceIn:ƽ��·������������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_MaxLoadBalance(OSPF6_CFGMAX_LOAD_BALANCE_S * pstMaxLoadBalanceIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_Preference
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/�ָ�OSPF6������·�����ⲿ·���ϵĴ���.
*  Description: ����/�ָ�OSPF6������·�����ⲿ·���ϵĴ���,�ⲿ·��ָAS�ⲿ·�������·�ɴ���.
*        Input: OSPF6_CFGPREFERENCE_S* pstPrefIn:����������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_Preference(OSPF6_CFGPREFERENCE_S* pstPrefIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_Redistribute
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/ɾ��OSPF6·���������
*  Description: ����/ɾ��OSPF6·���������,������������У�ֱ��·�ɡ���̬·�ɡ�OSPFv3·���Լ�RIPng·��
*        Input: OSPF6_CFGREDISTRIBUTE_S* pstRedistIn:·���������������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_Redistribute(OSPF6_CFGREDISTRIBUTE_S* pstRedistIn);

/*******************************************************************************
*    Func Name: OSPF6_CFG_RouteFilterExport
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/ɾ��OSPF6����·���������
*  Description: ����������OSPF6��·��������Ե�ACL�������ã��Ƚ���OSPF6·������Ĳ������ú��ٸ��ݸò������ù���������
*        Input: OSPF6_CFGDISTRIBUTE_S* pstDistExpIn:·���������������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_RouteFilterExport(OSPF6_CFGDISTRIBUTE_S* pstDistExpIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_RouteFilterImport
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/ɾ��OSPF6����·�ɽ��չ���
*  Description: ����������OSPF6��ѧϰ����·�ɽ���ACL��������
*        Input: OSPF6_CFGDISTRIBUTE_S*  pstDistImpIn:·�ɽ��չ���������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_RouteFilterImport(OSPF6_CFGDISTRIBUTE_S*  pstDistImpIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_Peer
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����/ɾ����̬OSPF6�ھ�.
*  Description: ����/ɾ����̬OSPF6�ھ�,ʵ����Чʱ,�������ͱ���ΪNBMA����.
*        Input: OSPF6_CFGPEER_S *pstPeerIn:�ھ�������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: ���ȼ��ֶ�����Ϊ0ʱ,��ʾ������DRѡ��;
*               ���ȼ��ֶ�����Ϊ��0ʱ,��ʾ������DRѡ��,
*               ѡ�ٰ��սӿ�·�����ȼ�,Ȼ��rouer-id��С��ԭ����ѡ��DR.
*               ʵ����Чʱ,�������ͱ���ΪNBMA����.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_Peer(OSPF6_CFGPEER_S *pstPeerIn);


/*******************************************************************************
*    Func Name: OSPF6_Intermediate_Hook_Register
* Date Created: 2010-3-30
*       Author: luoagaowei
*  Description: OSPFv3 �����շ�ע�ṳ��
*        Input: ULONG ulDirection:�����������
*               OSPF6_PACKET_HOOK_FUNC pfOspfFwHookFunc:
*       Output: 
*       Return: OSPFv3������
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2010-3-30  luoagaowei         Creat the first version.
*
*******************************************************************************/

ULONG OSPF6_Intermediate_Hook_Register(ULONG ulDirection, 
                                OSPF6_PACKET_HOOK_FUNC pfOspfFwHookFunc); 

/*******************************************************************************
*    Func Name: OSPF6_Intermediate_UnHook_Register
* Date Created: 2010-3-30
*       Author: luoagaowei
*  Description: OSPFv3���Ĺ��Ӻ�����ע��
*        Input: ULONG ulDirection:�����������
*       Output: 
*       Return: OSPFv3������
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2010-3-30  luoagaowei         Creat the first version.
*
*******************************************************************************/
ULONG OSPF6_Intermediate_UnHook_Register(ULONG ulDirection);

ULONG OSPF6_CFG_Area(OSPF6_CFGAREA_S *pstAreaIn);


ULONG OSPF6_CFG_RouterId(USHORT usProcessId, ULONG ulRouterId);

ULONG OSPF6_CFG_AdminProc(USHORT usProcessId,ULONG ulOperation);

/*S-IP-003-OSPFv3-005 ����OSPFv3 ����GR����*/
/*******************************************************************************
*    Func Name: OSPF6_CFG_GR
* Date Created: 2014-03-18
*       Author: guojianjun178934
*  Description: OPSFV3����GR����
*        Input: OSPF6_CFG_GR_S * pstOSPFGR:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   guojianjun178934        Create
*
*******************************************************************************/
ULONG OSPF6_CFG_GR(OSPF6_CFG_GR_S * pstOSPFGR);


ULONG OSPF6_CFG_CmdGrHelper(OSPF6_CFG_GRHELPER_S * pstGrHelper);

ULONG OSPF6_CFG_CmdGrHelperProc(OSPF6_CFGGRHELPER_PRO_S * pstGrHelperProc);

/*******************************************************************************
*    Func Name: OSPF6_Warning_Hook_Register
* Date Created: 2014-05-12
*       Author: guojianjun178934
*  Description: OSPFV3�澯ע�ắ��
*        Input: OSPFV3_WARNING_HOOK_FUNC pfOSPFV3WarningHookFun:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-12   guojianjun178934        Create
*
*******************************************************************************/
ULONG OSPF6_Warning_Hook_Register(OSPFV3_WARNING_HOOK_FUNC pfOSPFV3WarningHookFun);


#ifdef __cplusplus
        }
#endif /* __cplusplus */
        
#endif /* _OSPF6_CFG_API_H_ */

