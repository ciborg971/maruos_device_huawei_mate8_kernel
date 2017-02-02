/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_apiadp_stru01.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description: 
*   01 OSPF ����ģ�鶨��Ľṹ(��Χ���ù���)
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create                              
*******************************************************************************/

#ifndef OSPF_APIADP_STRU01_H
#define OSPF_APIADP_STRU01_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*��֤�ӿڻ�����Ϣ
    AREA_CFG_LIST_ENTRY
    IF_CFG_LIST_ENTRY  */
typedef struct cfg_auth_data_tag
{
  NBB_ULONG auth_key_len;
  NBB_CHAR auth_key_value[256]; 
  NBB_ULONG auth_user_data_len;
  NBB_CHAR auth_user_data[4];
  NBB_BYTE auth_key_id;
  NBB_BYTE padding[3];
}CFG_AUTH_DATA;

/*01 OSPF ȫ������ͷ�ṹ*/
typedef struct ospf_cfg_list_info_tag
{
  /***************************************************************************/
  /* List root of ospf processes                                             */
  /***************************************************************************/
  NBB_ULONG ospf_num;
  NBB_LLQE_ROOT ospf_cfg_list_root;
}OSPF_CFG_LIST_INFO;

/*02 Network ȫ������ͷ�ṹ*/
typedef struct network_cfg_list_info_tag
{
  /***************************************************************************/
  /* List root of interfaces that ospf notified by I3.                       */
  /***************************************************************************/
  NBB_ULONG network_num;
  NBB_LLQE_ROOT network_cfg_list_root;
}NETWORK_CFG_LIST_INFO;

/*03 �ӿ� ȫ������ͷ�ṹ*/
typedef struct if_cfg_list_info_tag
{
  /***************************************************************************/
  /* List root of interfaces that ospf notified by I3.                       */
  /***************************************************************************/
  NBB_ULONG if_num;
  NBB_LLQE_ROOT if_cfg_list_root;
}IF_CFG_LIST_INFO;

/*11 OSPF �ڵ���Ϣ*/
typedef struct ospf_cfg_list_entry_tag
{
  NBB_LLQE ospf_cfg_list_node;          /*��������ȫ�ֽ�������*/
  NBB_LLQE_ROOT ospf_area_cfg_list_root;/*��������OSPF����*/

  /*���̻�����Ϣ*/
  NBB_ULONG ospf_process_id;  
  NBB_ULONG area_num;  
  /*Add for BC3D03437 at 2010-07-16*/
  NBB_ULONG ulGrHelperMode;
  NBB_ULONG ulGrPeriod;
  NBB_ULONG ulGrAccNum;
  /*End for BC3D03437 at 2010-07-16*/
   
  NBB_ULONG ulReserved1;
  NBB_ULONG ulReserved2;
}OSPF_CFG_LIST_ENTRY;

/*12 Area �ڵ���Ϣ*/
typedef struct area_cfg_list_entry_tag
{
  NBB_LLQE ospf_area_cfg_list_node; /*��������OSPF����������*/
  OSPF_CFG_LIST_ENTRY *ospf_process;/*����������Ϣ*/

  NBB_LLQE_ROOT area_network_cfg_list_root;/*������������������network*/

  /*������Ϣ*/ 
  NBB_ULONG area_id;  
  NBB_ULONG network_num;  
  NBB_LONG auth_type;
  CFG_AUTH_DATA auth_data;  /*ָ�������*/ 
  NBB_ULONG ulReserved1;
  NBB_ULONG ulReserved2;
}AREA_CFG_LIST_ENTRY;

/*13 Network �ڵ���Ϣ*/
typedef struct network_cfg_list_entry_tag
{
  NBB_LLQE network_cfg_list_node;       /*��������ȫ��network������*/
  
  NBB_LLQE area_network_cfg_list_node;  /*�������������network������*/
  AREA_CFG_LIST_ENTRY *area;            /*����������Ϣ*/
  
  NBB_LLQE_ROOT network_if_cfg_list_root; /*��������network���нӿ�*/
    
  /*network������Ϣ*/
  NBB_ULONG ip_addr;
  NBB_ULONG prefix_len; 
  NBB_ULONG ulReserved1;
  NBB_ULONG ulReserved2;
}NETWORK_CFG_LIST_ENTRY;

/*14 �ӿ� �ڵ���Ϣ*/
typedef struct if_cfg_list_entry_tag
{
  NBB_LLQE if_cfg_list_node;        /*�������������ӿ�������*/  
  NBB_LLQE second_ip_node;          /*B016 01 ���������ڴӵ�ַ������*/  
  
  NBB_LLQE network_if_cfg_list_node;/*����������network�ӿ�������*/ 
  /*ָ�������ڵ�network��Ϣ�����Ի�ȡ������Ϣ������Ϣ*/
  NETWORK_CFG_LIST_ENTRY *network;  

  /*���ӵ�ַ����*/  
  NBB_ULONG primary_flag;               /*B016 02 1-primary 0-sencondary*/  
  /*ָ�������ڵĽӿ�*/
  struct if_cfg_list_entry_tag * primary_if;       /*B016 03*/
  NBB_ULONG second_ip_num;              /*B016 04*/
  NBB_LLQE_ROOT second_ip_list_root;    /*B016 05*/
  
  NBB_ULONG ref_cnt;  /*��ʱ���ã�ԭ�������������ڶ���������*/
  
  /*�ӿڻ�����Ϣ*/
  NBB_CHAR if_name[47+1]; 
  
  NBB_ULONG if_index;
  NBB_ULONG ip_addr;    /*������*/
  NBB_ULONG prefix_len;
  /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
  NBB_ULONG vrf_index;
  /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

  /*��������*/  
  USHORT usHelloInterval;
  USHORT usDeadItvl; 
  ULONG  ulFast_Hello_Multiplier;
  ULONG  ulIfCost;    
  UCHAR  ucNetworkType;
  UCHAR  ucPriority;
  USHORT usRetransInterval;
  NBB_BOOL	auth_configured;
  NBB_LONG auth_type;
  CFG_AUTH_DATA auth_data;   /*ָ�������*/ 
  NBB_ULONG ulMtuIgnore;

  NBB_ULONG ulReserved1;
  NBB_ULONG ulReserved2;
}IF_CFG_LIST_ENTRY;

/*Added by guojianjun178934, �����б��ֵ�OSPF NSR��Ϣ, 2012/12/10   ���ⵥ��:20121208_1 */
typedef struct nsr_ospf_api_adapt_info
{
    NSR_OSPF_ADP_STATISTICS stNSRAdpOSPFStat;
}NSR_OSPF_API_ADAPT_INFO;
/* End of Added by guojianjun178934, 2012/12/10   ���ⵥ��:20121208_1 */

/*����ȫ�ֹ���*/
/*�����ݽṹ������ʾһ��ospf�Ƿ��Ѿ���ʹ��*/
typedef struct tagOSPF_PROCESS_USED
{
    USHORT usProcessId;          /*ʵ��id,���û�����*/
    USHORT usUsedFlg;            /*1�����Ѿ�ʹ�ã�0��ʾû��ʹ��*/
    ULONG ulDclPid;              /*DCL�ڲ�ʹ�õ�α����id*/
    
    /*Added by guojianjun178934, �����б���OSPF NSR��Ϣ, 2012/12/8   ���ⵥ��:20121208_1 */
    NSR_OSPF_API_ADAPT_INFO stNSRInfo;
    /* End of Added by guojianjun178934, 2012/12/8   ���ⵥ��:20121208_1 */
}OSPF_PROCESS_USED_S;

/*�ڲ�ά�����Խṹ*/
typedef struct cfg_area_info
{
  NBB_ULONG ospf_process_id;
  NBB_ULONG area_id;
  NBB_LONG auth_type;
  NBB_ULONG auth_key_len;
  NBB_BYTE auth_key_value[256]; 
  NBB_ULONG auth_user_data_len;
  NBB_BYTE auth_user_data[4];
}CFG_AREA_INFO;

typedef struct cfg_network_info_tag
{
  NBB_ULONG ospf_process_id;
  NBB_ULONG area_id;
  NBB_ULONG ip_addr;
  NBB_ULONG prefix_len;
}CFG_NETWORK_INFO;

/*�����ṹ*/
/*�����ݽṹ���������������״̬*/
typedef struct tagOSPF_CFGIF_AREAADMIN
{
    ULONG ulProcessId;                   /*����ID*/
    ULONG ulAreaId;                      /*����ID*/
    ULONG ulAdminStatus;                 /*�������״̬*/
}OSPF_CFGIF_AREAADMIN_S;

typedef struct tagOSPF_CFG_IF_AREAID
{
    ULONG ulProcessId;
    UCHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    ULONG ulAreaId;
    ULONG ulEnableFlg;
}OSPF_CFG_IF_AREAID_S;

typedef struct tagOSPF_IF_DCL_FILTER
{
    ULONG  ulProcessId;
    ULONG  ulAdminStatus;
    ULONG  ulPassive;
} OSPF_IF_DCL_FILTER_S; /*����DCL �ڲ���ѯ����*/


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif
