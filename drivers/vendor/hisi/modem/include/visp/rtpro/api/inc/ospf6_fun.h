/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf6_fun.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2009-07-09
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-07-09   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _OSPF6_FUN_H_
#define _OSPF6_FUN_H_

#ifdef __cplusplus
    extern "C"{
#endif /* __cplusplus */

#ifndef BOOL_T
#define BOOL_T  short   /* boolean */  
#endif 

#define ERR_IF_NOT_REPORT 1
#define OSPF6_ERR_NO_ERR 0

#define OSPF6_CFG_ADD 1
#define OSPF6_CFG_DEL 0

#define OSPF6_PT_BEGIN           (VOID)TCPIP_SmP(g_ulSemOspf6)
#define OSPF6_PT_END             (VOID)TCPIP_SmV(g_ulSemOspf6)

#define SID_OSPF6_SHOWIF_KEY_S        100
#define SID_OSPF6_LSDB_KEY_S          101
#define SID_OSPF6_ENTITY_KEY_S        114
#define SID_OSPF6_NBR_KEY_S           115
#define SID_OSPF6_ROUTE_KEY_S         116
#define SID_OSPF6_AREA_KEY_S          117
#define SID_OSPF6_CFG_IF_KEY_S        118
#define SID_OSPF6_CFG_IFATTR_KEY_S    119
#define SID_OSPF6_PEER_KEY_S          120
#define SID_OSPF6_CFGPEER_KEY_S       121
#define SID_OSPF6_CFGAGGR_KEY_S       122
#define SID_OSPF6_CFGAGGR_LIST_S      123
#define SID_OSPF6_ERROR_KEY_S         124

/*link local��ַǰ׺����*/
#define LINK_LOCAL_PRE_LEN  10
#define OSPF6_OPTION_TO_STRING(ulOptions,szFlag)\
{\
    if (ulOptions & QOP3_LSA_HEADER_V6_BIT)\
    {\
        (VOID)TCPIP_STRNCAT_S(szFlag, LEN_32, "-V6");\
    }\
    if (ulOptions & QOPM_LSA_HEADER_E_BIT)\
    {\
        (VOID)TCPIP_STRNCAT_S(szFlag, LEN_32, "-E");\
    }\
    if (ulOptions & QOPM_LSA_HEADER_MC_BIT)\
    {\
        (VOID)TCPIP_STRNCAT_S(szFlag, LEN_32, "-MC");\
    }\
    if (ulOptions & QOPM_LSA_HEADER_NP_BIT)\
    {\
        (VOID)TCPIP_STRNCAT_S(szFlag, LEN_32, "-N");\
    }\
    if (ulOptions & QOP3_LSA_HEADER_R_BIT)\
    {\
        (VOID)TCPIP_STRNCAT_S(szFlag, LEN_32, "-R");\
    }\
    if (ulOptions & QOPM_LSA_HEADER_DC_BIT)\
    {\
        (VOID)TCPIP_STRNCAT_S(szFlag, LEN_32, "-DC");\
    }\
}

#define OSPF6_LSATYPE_API_TO_DCL(usInLsaType,usOutLsaType)\
{\
    if (OSPF6_ROUTER_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_IN_ROUTER_LSA;\
    }\
    else if (OSPF6_NETWORK_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_IN_NETWORK_LSA;\
    }\
    else if (OSPF6_INTER_AREA_PRFX_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_IN_INTER_AREA_PRFX_LSA;\
    }\
    else if (OSPF6_INTER_AREA_RTR_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_IN_INTER_AREA_RTR_LSA;\
    }\
    else if (OSPF6_AS_EXTERNAL_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_IN_AS_EXTERNAL_LSA;\
    }\
    else if (OSPF6_NSSA_EXT_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_IN_NSSA_EXT_LSA;\
    }\
    else if (OSPF6_LINK_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_IN_LINK_LSA;\
    }\
    else if (OSPF6_INTRA_AREA_PRFX_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_IN_INTRA_AREA_PRFX_LSA;\
    }\
}

/* Added by hanna55555, BC3D01825, 2009/7/31 */
#define OSPF6_LSATYPE_DCL_TO_API(usInLsaType,usOutLsaType)\
{\
    if (OSPF6_IN_ROUTER_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_ROUTER_LSA;\
    }\
    else if (OSPF6_IN_NETWORK_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_NETWORK_LSA;\
    }\
    else if (OSPF6_IN_INTER_AREA_PRFX_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_INTER_AREA_PRFX_LSA;\
    }\
    else if (OSPF6_IN_INTER_AREA_RTR_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_INTER_AREA_RTR_LSA;\
    }\
    else if (OSPF6_IN_AS_EXTERNAL_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_AS_EXTERNAL_LSA;\
    }\
    else if (OSPF6_IN_NSSA_EXT_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_NSSA_EXT_LSA;\
    }\
    else if (OSPF6_IN_LINK_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_LINK_LSA;\
    }\
    else if (OSPF6_IN_INTRA_AREA_PRFX_LSA == usInLsaType)\
    {\
        usOutLsaType = OSPF6_INTRA_AREA_PRFX_LSA;\
    }\
}
/*End of Added by hanna55555, 2009/7/31 */

/* ������תΪ������ */
#define OSPF6_ADDRESS_HTON(x) \
{\
    (x)[0] = VOS_HTONL((x)[0]);\
    (x)[1] = VOS_HTONL((x)[1]);\
    (x)[2] = VOS_HTONL((x)[2]);\
    (x)[3] = VOS_HTONL((x)[3]);\
}

/* ������ תΪ������*/
#define OSPF6_ADDRESS_NTOH(x) \
{\
    (x)[0] = VOS_NTOHL((x)[0]);\
    (x)[1] = VOS_NTOHL((x)[1]);\
    (x)[2] = VOS_NTOHL((x)[2]);\
    (x)[3] = VOS_NTOHL((x)[3]);\
}

/* Added by likaikun00213099, �ھӲ�ѯ����ά����Ϣ, 2014/4/18 */
#define OSPF6_ADDRESS_IS_UNSPECIFIED(x) \
    ((0 == ((x)[0])) \
     && (0 == ((x)[1])) \
     && (0 == ((x)[2])) \
     && (0 == ((x)[3])))
/* End of Added by likaikun00213099, �ھӲ�ѯ����ά����Ϣ, 2014/4/18 */

/* 32bits������ǰ׺���� */
#define OSPF6_PREFX_LEN_32           32
#define OSPF6_PREFX_LEN_64           64
#define OSPF6_PREFX_LEN_96           96

/* 32bits������ǰ׺���ȶ�Ӧ��ȡ�ĵ�ַ���� */
#define OSPF6_DCL_BYTE4_ADDR_LEN           4
#define OSPF6_DCL_BYTE8_ADDR_LEN           8
#define OSPF6_DCL_BYTE12_ADDR_LEN          12
#define OSPF6_DCL_BYTE16_ADDR_LEN          16


/*����ۺϵ�ǰ׺��������Ϊ3�����Ϊ128*/
#define  OSPF6_AAGG_PREFIX_LEN_MIN   3
#define  OSPF6_AAGG_PREFIX_LEN_MAX   128

#define OSPF6_PREFX_TO_ADDR_LEN(ucPrfxLen,ulAddrLen)\
{\
    if (ucPrfxLen <= OSPF6_PREFX_LEN_32)\
    {\
        ulAddrLen = OSPF6_DCL_BYTE4_ADDR_LEN;\
    }\
    else if (ucPrfxLen <= OSPF6_PREFX_LEN_64)\
    {\
        ulAddrLen = OSPF6_DCL_BYTE8_ADDR_LEN;\
    }\
    else if (ucPrfxLen <= OSPF6_PREFX_LEN_96)\
    {\
        ulAddrLen = OSPF6_DCL_BYTE12_ADDR_LEN;\
    }\
    else\
    {\
        ulAddrLen = OSPF6_DCL_BYTE16_ADDR_LEN;\
    }\
}

#define OSPF6_SET_INTF_ATTR_REFBITS(cfg_list_cb,pstIntfMib,type_bits)\
{\
    if ((OSPF6_NOFLAG_ADD == pstIntfMib->bNoFlag)\
        && !(cfg_list_cb->ref_bits & type_bits))\
    {\
        cfg_list_cb->ref_bits |= type_bits;\
    }\
    if ((OSPF6_NOFLAG_DEL == pstIntfMib->bNoFlag)\
        && (cfg_list_cb->ref_bits & type_bits))\
    {\
        cfg_list_cb->ref_bits &= ~type_bits;\
    }\
    if ((0 == cfg_list_cb->nbr_ref) && (0 == cfg_list_cb->ref_bits))\
    {\
        ospf6_if_cfg_free(cfg_list_cb,pstIntfMib->ulIfIndex);\
    }\
}

#define OSPF6_INTF_ATTR_CB_SEARCH(ulIfIndex)\
{\
    for (next_if_attr_cb = (IFV6_ATTR_LIST_ENTRY*)NBB_L_NEXT_IN_LIST(\
                                g_ulIf_attr_list_info->if_attr_list_root,\
                                g_ulIf_attr_list_info->if_attr_list_root);\
         next_if_attr_cb != NULL;\
         next_if_attr_cb = (IFV6_ATTR_LIST_ENTRY*)NBB_L_NEXT_IN_LIST(\
                                g_ulIf_attr_list_info->if_attr_list_root,\
                                next_if_attr_cb->if_attr_list_node))\
    {\
        if (next_if_attr_cb->if_index == ulIfIndex)\
        {\
            break;\
        }\
    }\
}

#define OSPF6_INTF_CFG_CB_SEARCH(ulInstanceId)\
{\
    for (walk_cfg_if_cb = (IFV6_CFG_LIST_ENTRY *)NBB_L_NEXT_IN_LIST(\
                                  next_if_attr_cb->if_cfg_list_root,\
                                  next_if_attr_cb->if_cfg_list_root);\
         walk_cfg_if_cb != NULL;\
         walk_cfg_if_cb = (IFV6_CFG_LIST_ENTRY *)NBB_L_NEXT_IN_LIST(\
                                next_if_attr_cb->if_cfg_list_root,\
                                walk_cfg_if_cb->if_cfg_list_node))\
    {\
        if (walk_cfg_if_cb->instance_id == ulInstanceId)\
        {\
            break;\
        }\
    }\
}


#define OSPF6_IS_LINK_LOCAL(address)                       \
                                ((address[0] == 0xFE) &&   \
                                ((address[1] & 0xC0) == 0x80))
/*Ĭ��������չ㲥�������ʹ���*/
#define OSPF6_FILL_DEF_HELLO_DEAD_ITVL(pstIntfMib) \
{ \
    if ((OSPF6_NETWORK_BROADCAST == pstIntfMib->ulNetType) \
        ||(OSPF6_NETWORK_POINT_TO_POINT == pstIntfMib->ulNetType)) \
    { \
        pstIntfMib->ulHelloItvl = OSPF6_DEF_INTF_HELLO_ITVL_0; \
        pstIntfMib->ulDeadItvl = OSPF6_DEF_INTF_DEAD_ITVL_0; \
    } \
    else if ((OSPF6_NETWORK_NBMA == pstIntfMib->ulNetType) || \
              (OSPF6_NETWORK_POINT_T_MLTPNT == pstIntfMib->ulNetType)) \
    { \
        pstIntfMib->ulHelloItvl = OSPF6_DEF_INTF_HELLO_ITVL_1; \
        pstIntfMib->ulDeadItvl = OSPF6_DEF_INTF_DEAD_ITVL_1; \
    } \
    else \
    { \
        pstIntfMib->ulHelloItvl = OSPF6_DEF_INTF_HELLO_ITVL_0; \
        pstIntfMib->ulDeadItvl = OSPF6_DEF_INTF_DEAD_ITVL_0; \
    } \
    pstIntfMib->ulFastHelloMulti = OSPF6_DEF_INTF_FAST_HELLO_MULTIPLIER;\
}

#define OSPFV3_FREE_UNUSED_IF_CFG_CB(if_cfg_cb, if_index)\
{\
    if (NULL != if_cfg_cb)\
    {\
        if ((0 == if_cfg_cb->nbr_ref) && ( 0 == if_cfg_cb->ref_bits))\
        {\
            ospf6_if_cfg_free(if_cfg_cb, if_index);\
            if_cfg_cb = NULL;\
        }\
    }\
}

/*  �ڲ�LSA����*/
#define OSPF6_IN_ROUTER_LSA                 1
#define OSPF6_IN_NETWORK_LSA                2
#define OSPF6_IN_INTER_AREA_PRFX_LSA        3
#define OSPF6_IN_INTER_AREA_RTR_LSA         4
#define OSPF6_IN_AS_EXTERNAL_LSA            5
#define OSPF6_IN_NSSA_EXT_LSA               7
#define OSPF6_IN_LINK_LSA                   8
#define OSPF6_IN_INTRA_AREA_PRFX_LSA        9

/* OSPFv3���������������� */
#define OSPF6_ENTITY_ATTRIBUTE_SPF          1
#define OSPF6_ENTITY_ATTRIBUTE_BALANCE      2
#define OSPF6_ENTITY_ATTRIBUTE_GR           3

#define OSPF6_INETWK_ADDR_TYPE_IPV4 1
#define OSPF6_INETWK_ADDR_TYPE_IPV6 2

/* OSPFv3������������ */
#define OSPF6_AREA_TYPE_NSSA            1
#define OSPF6_AREA_TYPE_STUB            2
#define OSPF6_AREA_TYPE_COST            3
#define OSPF6_AREA_TYPE_RFSHITVL      4

/*stub����ȱʡcostֵ*/
#define OSPF6_STUB_AREA_DEF_COST            1

/*����鷺ȱʡʱ����*/
#define OSPF6_AREA_DEF_RFSHITVL                1800

#define OSPF6_AREA_ASYSNC_WAIT_TIMES  20   /*��������ʱ�첽�ȴ�����*/
#define OSPF6_AREA_ASYSNC_WAIT_ITVL   200  /*��������ʱ�첽�ȴ���� ms*/


#define OSPF6_GET_STATE_BEGIN  0x01   
#define OSPF6_GET_STATE_MORE   0x02
#define OSPF6_GET_STATE_END    0x04


#define OSPF6_Net_Type_MAX     11

/*��̬�ھ�����洢*/
typedef struct ifv6_nbr_list_entry_tag
{
    NBB_BYTE address[OSPF6_MAX_INET_ADDR_LEN];
    NBB_ULONG nbr_priority;
    struct ifv6_nbr_list_entry_tag *nbr_next;
}IFV6_NBR_LIST_ENTRY;

typedef struct ifv6_cfg_list_entry_tag
{
    NBB_LLQE if_cfg_list_node;
    NBB_ULONG instance_id;
    NBB_ULONG ref_bits;
    NBB_ULONG attr_bits;
    NBB_ULONG net_type; 
    NBB_ULONG cost;
    NBB_ULONG priority;
    NBB_ULONG mtu_ignore;
    NBB_ULONG rxmt_itvl;
    NBB_ULONG trans_delay;
    NBB_ULONG hello_itvl;
    NBB_ULONG dead_itvl;
    NBB_ULONG fast_hello_multi;
    NBB_ULONG poll_itvl;
    IFV6_NBR_LIST_ENTRY *nbr_entry;
    NBB_ULONG nbr_ref;
    NBB_ULONG gr_helper_mode;
    NBB_ULONG gr_helper_period;
    NBB_ULONG gr_helper_accnum;
}IFV6_CFG_LIST_ENTRY;

typedef struct ifv6_bind_list_entry_tag
{
    NBB_LLQE if_bind_list_node;
    NBB_ULONG instance_id;  
    NBB_USHORT process_id;  
    NBB_BYTE padding[2];
    NBB_ULONG area_id;
}IFV6_BIND_LIST_ENTRY;

/* �ӿ�ʹ��OSPFv3ȫ������ͷ */
typedef struct ifv6_enable_list_info_tag
{
    NBB_LLQE_ROOT if_enable_list_root;
}IFV6_ENABLE_LIST_INFO;


typedef struct ifv6_enable_list_entry_tag
{
    NBB_LLQE if_enable_list_node;       /*��������ȫ�ֽӿ�ʹ��������*/  
    NBB_LLQE_ROOT if_bind_list_root;
    NBB_ULONG if_index;
}IFV6_ENABLE_LIST_ENTRY;


/* �ӿ���������OSPFv3ȫ������ͷ */
typedef struct ifv6_attr_list_info_tag
{
    NBB_LLQE_ROOT if_attr_list_root;
}IFV6_ATTR_LIST_INFO;

typedef struct ifv6_attr_list_entry_tag
{
    NBB_LLQE if_attr_list_node;       /*��������ȫ�ֽӿ���������������*/  
    NBB_LLQE_ROOT if_cfg_list_root;
    NBB_ULONG if_index;
}IFV6_ATTR_LIST_ENTRY;

                                                  
/* S-IP-004-OSPFv3-003                                                
 +---------+   +---------+                        
 |process 1-----process 2---- ...... (keyֵ����)              
 +---/-----+   +---------+                        
     |                                            
     |   +---------+   +---------+                
     ----- area 0  ----- area 0  --- ...... (keyֵ����)      
         +----/----+   +---------+                
              |                                   
              | +---------+  +---------+          
              ---if inst 0 ---if inst 1 -- ...... (keyֵ����)
                +---------+  +---------+      
*/                


/*Ospfv3ȫ�ֽ�����������ͷS-IP-004-OSPFv3-003*/
typedef struct ospfv3_proc_list_info_tag
{
    NBB_LLQE_ROOT proc_list_root;       /*�Խ���IDΪkeyֵ������*/
    NBB_ULONG proc_num;                 /*��ǰ���õĽ��̸���*/
}OSPFV3_PROC_LIST_INFO;

/*Ospfv3�����������ڵ�S-IP-004-OSPFv3-003*/
typedef struct ospfv3_proc_list_entry_tag
{
    NBB_LLQE proc_list_node;                    /*����������ȫ�ֽ�������������*/
    NBB_LLQE_ROOT proc_area_list_root;          /*���������õ�������Ϣ*/
    NBB_USHORT process_id;                      /*����ID*/
    NBB_USHORT pad;
    NBB_ULONG area_num;                         /*��ǰ������������Ϣ*/
    NBB_ULONG grhelper_mode;                    /*�����ڽ�����Gr Helperģʽ*/
    NBB_ULONG grperiod;                         /*Gr Helper��ʱʱ��*/
    NBB_ULONG acc_num;                          /*�󶨵�ACL��ID*/   
}OSPFV3_PROC_LIST_ENTRY;

/*Ospfv3�����������������ڵ�S-IP-004-OSPFv3-003*/
typedef struct ospfv3_proc_area_list_entry_tag
{
    NBB_LLQE proc_area_list_node;               /*���������ڽ�����������������*/
    NBB_LLQE_ROOT area_if_list_root;            /*���������õĽӿ�ʵ������*/
    OSPFV3_PROC_LIST_ENTRY *proc_entry;         /*ָ�������Ľ���*/
    NBB_ULONG area_id;                          /*��������ID*/
    NBB_ULONG if_num;                           /*��ǰ�����½ӿ�ʵ������*/
    
}OSPFV3_PROC_AREA_LIST_ENTRY;

/*Ospfv3�����������������������½ӿ�ʵ���ڵ�S-IP-004-OSPFv3-003*/
typedef struct ospfv3_area_if_list_entry_tag
{
    NBB_LLQE area_if_list_node;                 /*�������������½ӿ�������*/
    NBB_ULONG if_index;                         /*�ӿ���������Э��ջ��һ��*/
    NBB_ULONG if_instance;                      /*�ӿ�ʵ����*/
}OSPFV3_AREA_IF_LIST_ENTRY;

/* ospf6 �ӿڰ󶨽���Mib ����ṹ */
typedef struct tagOSPF6_MIBIF
{ 
    USHORT bNoFlag;                              /*�������û���ɾ��
                                                   0 - ����
                                                   1 - ɾ��*/
    USHORT usProcessId;                          /*����ID*/
    ULONG  ulAreaId;                             /*����ID*/ 
    ULONG  ulInstanceId;                         /*Instance ID */ 
    ULONG  ulIfIndex;                            /*�ӿ����� */
    ULONG  ulAttrBits;                           /*����Bitλ */
    ULONG  ulNetType;                            /*Network Type */ 
    ULONG  ulCost;                               /*Cost */ 
    ULONG  ulPriority;                           /*Priority */
    ULONG  ulMtuIgnore;                          /*Mtu Ignore */
    ULONG  ulRxmtItvl;                           /*Rxmt Interval */
    ULONG  ulTransDelay;                         /*Trans Delay */
    ULONG  ulHelloItvl;                          /*Hello Interval */                
    ULONG  ulDeadItvl;                           /*Dead Interval */
    ULONG  ulFastHelloMulti;                     /*Fast_Hello_Multiplier */
    ULONG  ulPollItvl;                           /*Poll Interval */
    UCHAR  ucAddress[OSPF6_MAX_INET_ADDR_LEN];   /*Neighboring Address */ 
    ULONG  ulNbrPriOpFlag;
    ULONG  ulNbrPriority;                        /*��̬�ھ����ȼ�*/
    ULONG  ulGrHelperMode;
    ULONG  ulGrPeriod;
    ULONG  ulAccNum;
} OSPF6_MIBIF_S;

/* ospf6 entity key �ṹ*/
typedef struct tagOSPF6_ENTITY_KEY
{
    USHORT usProcessId;                           /*����ID*/
    USHORT usFilterProceId;                       /*���˽���ID*/
}OSPF6_ENTITY_KEY_S;

typedef struct tagOSPF6_PMMJ_KEY
{
    USHORT usProcessId;                           /*����ID*/
    USHORT usRes;
    ULONG ulInterfaceId;                       
    ULONG ulPartnerIndex;
}OSPF6_PMMJ_KEY_S;

typedef struct tagOSPF6_PMSJ_KEY_S
{
    USHORT usProcessId;                           /*����ID*/
    USHORT usRes;
    ULONG ulInterfaceId;                       
    ULONG MasterIndex;
}OSPF6_PMSJ_KEY_S;

/* ospf6 ����Mib ����ṹ */
typedef struct tagOSPF6_MIBPROC
{
    USHORT bNoFlag;                               /*�������û���ɾ��
                                                    0 - ����
                                                    1 - ɾ��*/
    USHORT usProcessId;                           /*����ID*/
    ULONG  ulRouterId;                            /*Router ID*/
    ULONG  ulVrfIndex;                            /*VPN Index*/
}OSPF6_MIBPROC_S;

/* ospf6 Intf key �ṹ */
typedef struct tagOSPF6_INTF_KEY
{ 
    USHORT usFltProcId;                          /*���˽���ID*/
    USHORT usProcessId;                          /*����ID*/
    ULONG  ulInstanceId;                         /*Instance ID */ 
    ULONG  ulIfIndex;
}OSPF6_INTF_KEY_S;

typedef struct tagOSPF6_NBR_KEY
{
    USHORT usFltProcId;                          /*���˽���ID*/ 
    USHORT usProcessId;                          /*����ID*/
    ULONG  ulInstanceId;                         /*Instance ID*/
    ULONG  ulIfIndex;                            /*�ӿ�����*/    
    UCHAR  ucRouteId[LEN_4];                     /*Route ID*/
}OSPF6_NBR_KEY_S;

/* ospf6 Lsdb key �ṹ */
typedef struct tagOSPF6_LSDB_KEY
{ 
    USHORT usFltProcId;                          /*���˽���ID*/
    USHORT usProcessId;                          /*����ID*/
    USHORT usFltLsaType;                         /*LSA���ͣ���OSPF6_XXXXX_LSA*/
    USHORT usLsaType;                            /*LSA���ͣ���OSPF6_XXXXX_LSA*/
    ULONG ulAreaId;                              /*����Area��Key*/
    ULONG ulLsaId;                               /*����lsa��Key֮һ*/
    ULONG ulAdvRtrId;                            /*����lsa��Key֮��*/
    ULONG ulIfIndex;                             /*����link lsa��Key֮��*/
    ULONG ulInstance;                            /*����link lsa��Key֮��*/
    ULONG ulNextIfCb;                            /*����link lsa��Key֮��*/
    ULONG ulGetState;                            /*��ǰ�Ĳ���״̬: 
                                                   GET_STATE_BEGIN, GET_STATE_MORE*/
}OSPF6_LSDB_KEY_S;

/* ospf6 static nbr key �ṹ */
typedef struct tagOSPF6_PEER_KEY
{
    USHORT usFltProcId;                          /*���˽���ID*/ 
    USHORT usProcessId;                          /*����ID*/
    ULONG  ulFltInstId;                          /*����Instance ID*/
    ULONG  ulInstanceId;                         /*Instance ID*/
    ULONG  ulFltIfIdxId;                         /*���˽ӿ�����*/    
    ULONG  ulIfIndex;                            /*�ӿ�����*/    
    UCHAR  ucNbrAddr[OSPF6_MAX_INET_ADDR_LEN];
}OSPF6_PEER_KEY_S;

/* ospf6 ������static nbr key �ṹ */
typedef struct tagOSPF6_CFGPEER_KEY
{
    ULONG  ulFltInstId;                          /*����ʵ��ID*/ 
    ULONG  ulInstanceId;                         /*Instance ID*/
    ULONG  ulFltIfIdxId;                           /*���˽ӿ�����*/    
    ULONG  ulIfIndex;                              /*�ӿ�����*/    
    UCHAR  ucNbrAddr[OSPF6_MAX_INET_ADDR_LEN];
}OSPF6_CFGPEER_KEY_S;

/*����ȫ�ֹ���*/
/*�����ݽṹ������ʾһ��ospf�Ƿ��Ѿ���ʹ��*/
typedef struct tagOSPF6_PROCESS_USED
{
    USHORT usProcessId;          /*ʵ��id,���û�����*/
    USHORT usUsedFlg;            /*1�����Ѿ�ʹ�ã�0��ʾû��ʹ��*/
    ULONG ulDclPid;              /*DCL�ڲ�ʹ�õ�α����id*/
}OSPF6_PROCESS_USED_S;

/*�����ݽṹ����ospfV3 routing���key*/
typedef struct tagOSPF6_ROUTING_KEY
{
    USHORT usFltProcessId;          /*���˽���ID*/     
    USHORT usProcessId;     /*OSPF ���̺�*/
    UCHAR ucDestId[4];      /*router id*/
    ATG_INET_ADDRESS stPrefix;  /*IPV6 ��ַ�Լ�����*/
    ULONG ulAreaId;         /*Area id */
    UCHAR ucDestType;   /*·������*/
    UCHAR ucPrefixlen;
    UCHAR ucPadding[2];    
    ULONG ulGetState; /*��ǰ�Ĳ���״̬: GET_STATE_BEGIN, GET_STATE_MORE*/
}OSPF6_ROUTING_KEY_S;

typedef struct tagOSPF6_AREA_KEY
{
    USHORT usFltProcessId;                          /*���˽���ID*/ 
    USHORT usProcessId;                             /*����ID*/
    ULONG ulAreaId;
    BOOL_T bFirstArea;
}OSPF6_AREA_KEY_S;

typedef struct tagOSPF6_CFG_IF_KEY
{
    USHORT usFltProcessId;                          /*���˽���ID*/ 
    USHORT usProcessId;                              /*����ID*/
    ULONG ulFltIfIndex;                               /*���˽ӿ�����*/ 
    ULONG  ulIfIndex;                                   /*�ӿ�����*/    
}OSPF6_CFG_IF_KEY_S;

typedef struct tagOSPF6_CFG_IFATTR_KEY
{
    ULONG ulFltInstId;                          /*����ʵ��ID*/ 
    ULONG ulInstanceId;                         /*ʵ��ID*/
    ULONG ulFltIfIdx;                           /*���˽ӿ�����*/ 
    ULONG ulIfIndex;                            /*�ӿ�����*/
    ULONG ulGetState; /*��ǰ�Ĳ���״̬: GET_STATE_BEGIN, GET_STATE_MORE*/
}OSPF6_CFG_IFATTR_KEY_S;

typedef struct tagOSPF6_AREA_AGG_KEY
{        
    ULONG  ulUserProcIdFilter; /*�û�����Ľ���ID*/   
    ULONG  ulUserAreaFilter;   /*�û������area ID*/   
    ULONG ulProcessId;            /*����ID*/
    ULONG ulAreaId;                /*area id*/
    ULONG ulAddrType;           /*��ַ��*/
    ULONG ulLsaType;            /*lsa ����*/
    UCHAR ucPrefixAddr[16];       /*�ۺϵ�ǰ׺��ַ*/
    ULONG ulPrefixLen;             /*�ۺϵ�ǰ׺����*/    
    ULONG ulGetState; /*��ǰ�Ĳ���״̬: GET_STATE_BEGIN, GET_STATE_MORE*/
}OSPF6_AREA_AGG_KEY_S;

typedef struct tagOSPF6_AAGG_DCL_FILTER
{
    ULONG  ulProcessId;  /*����ID*/
    ULONG  ulAreaId;    /*area id*/
    ULONG  ulAddrType; /*��ַ��*/
    ULONG  ulLsaType;/*lsa ����*/
} OSPF6_AAGG_DCL_FILTER_S; /*����DCL �ڲ���ѯ����*/

typedef struct tagOSPF6_MIBAREA
{
    ULONG  ulAreaType;              /*������������*/ 
    USHORT bNoFlag;                 /*�������û���ɾ��
                                                  0 - ����
                                                  1 - ɾ��*/
    USHORT usProcessId;            /*����ID*/
    ULONG  ulAreaId;                  /*����ID*/
    UCHAR  ucPadding;    
    UCHAR  ucNssaOption;          /*NSSA option*/
    USHORT usSummaryFlag;      /*�Ƿ�����summary lsa��stub��Ĭ��OSPF6_SUMM_SEND_AREA_SUMMARY
                                                      OSPF6_SUMM_NO_AREA_SUMMARY - ������Summary
                                                      OSPF6_SUMM_SEND_AREA_SUMMARY - ����Summary*/
    ULONG  ulAreaDefCost;         /*Default Cost��Ĭ��1*/ 
    ULONG  ulRfshInterval;          /*Reflood Interval(S)��Ĭ��1800, ��Χ:1~3599*/                                              

}OSPF6_MIBAREA_S;

typedef struct tagOSPF6_AAGG_PREFIX_INFO
{
    ULONG  ulProcessId;             /*����ID*/
    ULONG  ulAreaId;                  /*area id */
    UCHAR  ucPrefixAddr[16];       /*�ۺϵ�ǰ׺��ַ*/
    ULONG  ulPrefixLen;             /*�ۺϵ�ǰ׺����*/    
    NBB_LLQE  stListNode;        /*����*/
} OSPF6_AAGG_PREFIX_INFO_S; /*���OSPF �ۺϵ�ַǰ׺��Ϣ*/

typedef struct tagOSPF6_ERROR_KEY
{
    USHORT usFltProcessId;                          /*���˽���ID*/ 
    USHORT usProcessId;                             /*����ID*/
}OSPF6_ERROR_KEY_S;

extern NBB_ULONG ospf6_init(NBB_VOID);
extern NBB_ULONG ospf6_if_bind(OSPF6_MIBIF_S *pstIntfMib);
extern NBB_ULONG ospf6_If_unbind(OSPF6_MIBIF_S *pstIntfMib);
extern NBB_ULONG ospf6_cfg_if_mib(OSPF6_MIBIF_S *pstIntfIn);
extern NBB_ULONG ospf6_if_get_process(ULONG ulHandle,OSPF6_SHOWINTF_S *pstIntfIn,NBB_ULONG ulStep);
extern NBB_ULONG ospf6_process_check(NBB_USHORT usProcessId);
extern IFV6_ENABLE_LIST_ENTRY *ospf6_if_bind_check(NBB_ULONG if_index,
                                                         NBB_ULONG *pIf_enable_flag);
extern VOID ospf6_i3_cfg_if(NBB_ULONG cfg_flag,NBB_ULONG if_index);
extern NBB_ULONG ospf6_del_if(NBB_ULONG if_index);

extern NBB_VOID  ospf6_set_if_default (IFV6_CFG_LIST_ENTRY *if_cfg_list_entry);
extern NBB_ULONG ospf6_joinToOther(NBB_USHORT usProcId,NBB_USHORT bUndoConfig,
                                            NBB_ULONG InterfaceId,NBB_ULONG PartnerIndex);
extern NBB_ULONG ospf6_cfg_process(OSPF6_MIBPROC_S *pstProcIn);
extern NBB_ULONG ospf6_get_join_proc_by_vrfindex(NBB_ULONG vrf_index,
                                  NBB_ULONG *rtm_index, NBB_ULONG *sck_index);
/* End of Added by yanlei00216869, 2014/9/11 */
extern VOID ospf6_ent_info_output(OSPF6_ENTITY_SHOW_S *pstShowInfo);
extern NBB_USHORT ospf6_get_next_proc(NBB_USHORT usProcessId);
extern NBB_ULONG ospf6_get_ent_mib(USHORT usProceId, OSPF6_ENTITY_SHOW_S * pstShow);
extern NBB_ULONG ospf6_get_if_mib(OSPF6_INTF_KEY_S *pstIndex, OSPF6_SHOWINTF_S *pstIntfIn);
extern NBB_ULONG ospf6_get_nbr_mib(OSPF6_NBR_KEY_S *pstIndex, OSPF6_SHOWNBR_S *pstShow);
extern VOID ospf6_intf_info_output(OSPF6_SHOWINTF_S *pstIntfIn);
extern NBB_ULONG  ospf6_check_if_bind_mib(NBB_ULONG ulProcessId);
extern VOID ospf6_nbr_info_output(OSPF6_SHOWNBR_S *pstShowInfo);
extern NBB_ULONG ospf6_cmm_lsdb_get_one(ULONG ulHandle, 
                                               OSPF6_SHOWLSDB_S *pstLsdbIn);

extern VOID ospf6_lsdb_info_output(OSPF6_SHOWLSDB_S *pstLsdbIn);
extern NBB_ULONG ospf6_cmm_rt_get_one(OSPF6_ROUTING_KEY_S *pstIndex, 
                                                            OSPF6_SHOWROUTE_S *pstRouteOut,
                                                            ULONG *pulDestType);
extern VOID ospf6_route_info_output(OSPF6_SHOWROUTE_S *pstShowInfo);
extern NBB_ULONG ospf6_area_get_process(NBB_ULONG ulHandle,OSPF6_SHOW_AREA_S *pstAreaIn,NBB_ULONG ulStep);
extern NBB_ULONG ospf6_get_area_mib(OSPF6_AREA_KEY_S *pstIndex, OSPF6_SHOW_AREA_S *pstAreaIn);
extern VOID ospf6_area_info_output(OSPF6_SHOW_AREA_S *pstAreaIn);
extern IFV6_BIND_LIST_ENTRY *ospf6_if_bind_process_check(IFV6_ENABLE_LIST_ENTRY *walk_if_enable_cb,
                                                  NBB_USHORT process_id,
                                                  NBB_ULONG *pprocess_bind_flag);
extern NBB_VOID ospf6_process_bind_check(NBB_USHORT process_id,
                                                  NBB_ULONG *pprocess_bind_flag);
extern IFV6_ENABLE_LIST_ENTRY *ospf6_get_next_if(NBB_ULONG if_index);
extern IFV6_BIND_LIST_ENTRY *ospf6_get_next_bind(IFV6_ENABLE_LIST_ENTRY *walk_if_enable_cb,
                                                                NBB_USHORT process_id);
extern VOID ospf6_copy_cfg_intf_info(IFV6_ENABLE_LIST_ENTRY *walk_if_enable_cb,
                                        IFV6_BIND_LIST_ENTRY *walk_bind_if_cb, OSPF6_SHOWINTFBIND_S *pstIntfIn);
extern VOID ospf6_cfg_intf_info_output(OSPF6_SHOWINTFBIND_S *pstCfgIntfIn);
extern NBB_ULONG ospf6_cfg_ent_attribute_mib(VOID *pAttrInfo, NBB_ULONG ulAttrType);
extern NBB_ULONG ospf6_add_nm_process_mib(NBB_USHORT process_id, NBB_ULONG sck_index);
extern NBB_ULONG ospf6_del_nm_process_mib(NBB_USHORT process_id);
/* End of Added by yanlei00216869, 2014/9/11 */
extern NBB_ULONG ospf6_check_process_attr_para(VOID *pstProcAttrIn);
extern ULONG ospf6_cfg_asbr(ULONG ulProcessId,ULONG ulUndoFlag);
extern VOID ospf6_cmm_import_show_one(OSPF6_SHOWREDIST_S  *pstConfigInfo);

extern NBB_ULONG ospf6_if_cfg_check(NBB_CHAR *pszIfName, NBB_ULONG *pulIfIndex);
extern NBB_ULONG ospf6_instance_check(NBB_ULONG ulIfIndex,NBB_ULONG ulInstanceId,
                                                    NBB_USHORT *pusProcessId);
extern NBB_ULONG ospf6_cfg_if_attr_mib(OSPF6_MIBIF_S *pstIntfMib);
extern NBB_ULONG ospf6_if_attr_proc(OSPF6_MIBIF_S *pstIntfMib);
extern NBB_ULONG ospf6_set_if_default_network(NBB_ULONG ulIfIndex,
                                        OSPF6_CFGINTF_NETTYPE_S *psNetTypeIn);
extern VOID OSPF6_cmm_export_filter_show_one(OSPF6_SHOW_EXPORT_FILTER_S  *pstConfigInfo);
extern NBB_VOID ospf6_copy_if_attr_info_to_mib(OSPF6_MIBIF_S * pstIntfMib);
extern IFV6_CFG_LIST_ENTRY * ospf6_get_if_cfgcb(ULONG ulIfIndex,ULONG ulInstanceId);
extern NBB_ULONG ospf6_cfg_static_nbr_mib(ULONG ulCreateFlg,OSPF6_MIBIF_S *pstIntfMib);
extern NBB_ULONG ospf6_static_nbr_check(IFV6_CFG_LIST_ENTRY *pstCfgIfCb,
                                                        OSPF6_CFGPEER_S *pstPeerIn);
extern NBB_ULONG ospf6_peer_get_process(NBB_ULONG ulHandle,OSPF6_SHOWPEER_S *pstPeerIn,NBB_ULONG ulStep);

extern NBB_VOID ospf6_cfg_nbr_mib_multiple(ULONG ulDelIntf,OSPF6_MIBIF_S * pstIntfMib);

extern NBB_VOID ospf6_peer_info_output(OSPF6_SHOWPEER_S *pstShowInfo);
extern NBB_VOID ospf6_cfgpeer_info_output(OSPF6_SHOWCFGPEER_S *pstShowInfo);
extern NBB_ULONG ospf6_get_peer_item(ULONG ulHandle, OSPF6_SHOWCFGPEER_S *pstPeerIn, ULONG ulStep);
extern NBB_ULONG ospf6_nbr_network_check(IFV6_CFG_LIST_ENTRY *pstCfgIfCb,NBB_USHORT bNoFlag);
extern NBB_ULONG ospf6_ifattr_get_process(NBB_ULONG ulHandle,OSPF6_SHOWINTFATTR_S *pstIntfIn,NBB_ULONG ulStep);
extern VOID ospf6_intf_attr_info_output(OSPF6_SHOWINTFATTR_S *pstCfgIfAttrIn);
extern VOID OSPF6_cmm_filter_import_show_one(OSPF6_SHOW_IMPORT_FILTER_S  *pstConfigInfo);
extern NBB_VOID ospf6_Aggr_info_output(OSPF6_SHOWAREA_AGG_S *pstAreaAggIn);
extern ULONG ospf6_area_exist_check(USHORT usProcessId,ULONG ulAreaId);
extern ULONG ospf6_area_mib_cfg(USHORT usProcessId,ULONG ulAreaId);
extern NBB_ULONG ospf6_yapi_send_ips(NBB_HANDLE conn_handle,
                         NBB_IPS *orig_ips,
                         NBB_IPS **reslut_ips);
extern ULONG ospf6_cfg_area_agg_invalid_check(OSPF6_CFGAREA_AGG_S * pstAreaAggIn);
extern ULONG ospf6_aagg_get_process(ULONG ulHandle, OSPF6_SHOWAREA_AGG_S *pstAreaAggInfo);
extern ULONG ospf6_get_aagg_mib(OSPF6_AREA_AGG_KEY_S *pstIndex, OSPF6_SHOWAREA_AGG_S *pstAaggInfo);
extern NBB_ULONG ospf6_cfg_area_mib(OSPF6_MIBAREA_S *pstAreaMib);
/*ospf6  �ۺ������Ŵ���*/
extern ULONG ospf6_cfg_resource_clear(ULONG ulProcessId, ULONG ulMode);
extern ULONG  ospf6_aagg_prefix_list_proc(OSPF6_CFGAREA_AGG_S *pstAreaAggInfo);
extern ULONG  ospf6_aagg_prefix_list_add(ULONG ulProcessId, ULONG ulAreaId, UCHAR ucPrefixAddr[LEN_16], ULONG ulPrefixLen); 
extern ULONG  ospf6_aagg_prefix_all_list_del(ULONG ulProcessId); 
extern ULONG  ospf6_aagg_prefix_list_del(ULONG ulProcessId, ULONG ulAreaId, UCHAR ucPrefixAddr[LEN_16], ULONG ulPrefixLen); 
extern ULONG  ospf6_aagg_prefix_list_check_proc(OSPF6_CFGAREA_AGG_S * pstAreaAggInfo); 
extern BOOL_T  ospf6_aagg_prefix_list_exist(ULONG ulProcessId,  ULONG ulAreaId, 
            UCHAR ucPrefixAddr[LEN_16], ULONG ulPrefixLen, ULONG  ulOperMode);
extern NBB_ULONG ospf6_active_area_mib(NBB_ULONG ulAdmin_Status,OSPF6_MIBAREA_S *pstAreaMib);
extern NBB_VOID ospf6_fill_hellodeaditvl_by_network(OSPF6_MIBIF_S *pstIntfMib);
extern NBB_VOID ospf6_reset_helloitvl_by_network(NBB_ULONG ulIfIndex,OSPF6_MIBIF_S *pstIntfMib);
extern NBB_VOID ospf6_reset_deaditvl_by_network(NBB_ULONG ulIfIndex,OSPF6_MIBIF_S *pstIntfMib);
extern ULONG OSPF6_CMM_Route_GetProc(ULONG ulHandle, OSPF6_SHOWROUTE_S *pstRouteOut);
extern BOOL_T  ospf6_find_route_by_external_key(ATG_INET_ADDRESS *pPrefix, UCHAR ucPrefixLen);
extern BOOL_T ospf6_del_external_route_after_if_up(ATG_INET_ADDRESS *pPrefix, UCHAR uPrefixLen);
extern ULONG ospf6_get_lsdb_info(ULONG ulHandle,OSPF6_SHOWLSDB_S *pstLsdbIn, ULONG ulStep);
extern BOOL_T  ospf6_is_interface_route(OSPF6_SHOWROUTE_S *pstRouteOut);

extern OSPF6_PACKET_HOOK_FUNC g_pstOspf6InputPktHook;
extern OSPF6_PACKET_HOOK_FUNC g_pstOspf6OuputPktHook;

extern NBB_VOID ospf6_cmm_cumul_clear_one(NBB_ULONG ulDclPid);
extern NBB_VOID ospf6_cmm_error_clear_one(NBB_ULONG ulDclPid);
extern NBB_ULONG ospf6_cumul_get_process(NBB_ULONG ulHandle,
                                  OSPF6_SHOWCUMLTVE_OUT_S *pstCumulOut,
                                  NBB_ULONG ulStep);
extern NBB_ULONG ospf6_error_get_process(NBB_ULONG ulHandle,
                                  OSPF6_SHOWERROR_OUT_S * pstErrorOut,
                                  NBB_ULONG ulStep);

extern NBB_VOID ospf6_cmm_show_erropen(CHAR *pMod, ULONG ulRet);
extern NBB_VOID ospf6_cmm_show_head1(CHAR *pMod, USHORT usProc);
extern NBB_VOID ospf6_cmm_show_noentry(CHAR *pMod);
extern NBB_VOID ospf6_cmm_cumul_show_one(NBB_ULONG ulPrintIndex, OSPF6_SHOWCUMLTVE_OUT_S *psIn);
extern NBB_VOID ospf6_cmm_show_total(ULONG ulCount);
extern NBB_VOID ospf6_cmm_show_tail(CHAR *pMod);
extern NBB_VOID ospf6_cmm_error_show_one(NBB_ULONG ulPrintIndex, OSPF6_SHOWERROR_OUT_S *pstInfo);

extern NBB_ULONG ospf6_get_mj_mib(OSPF6_PMMJ_KEY_S *pstIndex,OSPF6_PMMJSHOW_S *pstShow);
extern VOID ospf6_mj_info_output(OSPF6_PMMJSHOW_S *pstShowInfo);
extern NBB_ULONG ospf6_get_sj_mib(OSPF6_PMSJ_KEY_S *pstIndex,OSPF6_PMSJSHOW_S *pstShow);
extern VOID ospf6_sj_info_output(OSPF6_PMSJSHOW_S *pstShowInfo);
extern NBB_ULONG ospfv3_cfg_area_mib(ULONG ulProcessId, ULONG ulAreaId, ULONG ulOperation);
extern NBB_ULONG ospfv3_cfg_routeid(NBB_USHORT process_id, NBB_ULONG operation);
extern NBB_ULONG ospfv3_cfg_adminproc(NBB_USHORT process_id, NBB_ULONG operation);
extern NBB_ULONG ospf6_if_matchaclip(NBB_ULONG if_index, NBB_ULONG acl_groupnum, NBB_BYTE *ip_addr);
extern NBB_ULONG ospfv3_delete_if_attr(OSPF6_MIBIF_S *pstIntfMib);
extern NBB_ULONG Ospfv3_clear_cfgnbr(IFV6_CFG_LIST_ENTRY *cfg_list_cb);
extern NBB_VOID ospf6_policydist_info_output(OSPF6_SHOWPLCYDIST_OUT_S * pstPolicyDistOut);
extern NBB_ULONG ospf6_cmm_cumul_get_one_nbr(OSPF6_NBR_KEY_S *pstIndex, VOID * pstCumulOut);
extern NBB_ULONG ospf6_get_cumul_nbr_info(NBB_ULONG ulDclPid, 
                                            OSPF6_NBR_KEY_S* pstIndex,
                                            OSPF6_SHOWCUMLTVE_OUT_S *pstCumulOut);
extern NBB_LONG ospfv3_add_proc_node(NBB_USHORT process_id, OSPFV3_PROC_LIST_ENTRY **pproc_entry);
extern NBB_LONG ospfv3_del_proc_node(NBB_USHORT process_id);
extern NBB_VOID ospfv3_del_area_node_under_proc(
                        OSPFV3_PROC_LIST_ENTRY *proc_entry,
                        NBB_LONG area_id);
extern NBB_VOID ospfv3_del_all_area_node_under_proc(
                        OSPFV3_PROC_LIST_ENTRY *proc_entry);
extern NBB_LONG ospfv3_add_area_node_under_proc(
                        OSPFV3_PROC_LIST_ENTRY      *proc_entry,
                        NBB_LONG                    area_id,
                        OSPFV3_PROC_AREA_LIST_ENTRY **pproc_area_entry);
extern NBB_VOID ospfv3_del_if_node_under_area(
                        OSPFV3_PROC_AREA_LIST_ENTRY  *area_entry, 
                        NBB_LONG if_index, 
                        NBB_LONG instance_id);
extern NBB_VOID ospfv3_del_all_if_node_under_area(
                        OSPFV3_PROC_AREA_LIST_ENTRY  *area_entry);
extern NBB_LONG ospfv3_add_if_node_under_area(
                        OSPFV3_PROC_AREA_LIST_ENTRY  *area_entry, 
                        NBB_LONG if_index, 
                        NBB_LONG instance_id,
                        OSPFV3_AREA_IF_LIST_ENTRY **pparea_if_entry);
extern NBB_LONG ospfv3_deal_cfglist_for_cfg_intf(OSPF6_MIBIF_S *intf_mib);
extern NBB_LONG ospfv3_get_proc_node(NBB_USHORT process_id, OSPFV3_PROC_LIST_ENTRY **pproc_entry);
extern NBB_LONG ospfv3_cfg_grhelper_for_pro(OSPFV3_PROC_LIST_ENTRY *proc_entry);
extern NBB_LONG ospfv3_get_area_node_under_proc(
                        OSPFV3_PROC_LIST_ENTRY *proc_entry,
                        NBB_LONG area_id,
                        OSPFV3_PROC_AREA_LIST_ENTRY **pproc_area_entry);
extern NBB_LONG ospfv3_calc_deaditvl_from_helloitvl(NBB_ULONG ulIfIndex,OSPF6_MIBIF_S *pstIntfMib);
extern NBB_LONG ospfv3_check_deaditvl_valid(NBB_ULONG if_index, OSPF6_CFGDEAD_ITVL_S *cfg_dead_itvl);
extern NBB_LONG ospfv3_record_hello_itvl(OSPF6_MIBIF_S *pstIntfMib);
extern NBB_ULONG ospfv3_record_dead_itvl(OSPF6_MIBIF_S *pstIntfMib);
extern NBB_ULONG ospfv3_check_add_area_valid(OSPFV3_PROC_LIST_ENTRY *ospfv3_proc_entry, NBB_ULONG area_id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _OSPF6_FUN_H_ */

