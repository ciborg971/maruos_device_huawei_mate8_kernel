/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              nsr_ospf_struct02.h
*
*  Project Code: Dopra V3R2
*   Module Name: OSPF NSR���ݽ������(2)    
*  Date Created: 2013-10-11
*        Author: guojianjun178934
*   Description: ��ͷ�ļ��ж�������ݽṹ�ȿ�������NBase�Ļ������ݽṹ��
*                Ҳ��������OSPF�ڲ����ݽṹ 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-10-11   guojianjun178934        Create
*
*******************************************************************************/
#ifndef NSR_OSPF_STRUCT02_INCLUDED
#define NSR_OSPF_STRUCT02_INCLUDED

/*OSPF�������ݶ���*/
typedef struct nsr_ospf_entity_repl
{
    /*��ǰ��Ч��Router ID*/
#define NSR_REPL_QOPM_ENT_CUR_ROUTER_ID 1
    NBB_BYTE current_router_id_repl[QOPM_ID_LEN];

    /*��ǰ��MD5���*/
#define NSR_REPL_QOPM_ENT_SEQ_NUM 2
    NBB_ULONG crypto_seq_num_repl;

#define NSR_REPL_ENT_OPER_STATUS 3
    NBB_BYTE oper_status_repl;
}NSR_OSPF_ENTITY_REPL;

typedef struct nsr_ospf_area_repl
{
#define NSR_REPL_AREA_OPER_STATUS 1
    NBB_BYTE oper_status_repl;
}NSR_OSPF_AREA_REPL;


typedef struct nsr_ospf_interface_repl
{
    /*�ӿ�״̬��״̬*/
#define NSR_REPL_IF_FSM_STATE 1
    NBB_LONG state_repl;

    /*�ӿ�ѡ�ٵ�DR*/
#define NSR_REPL_IF_DR 2
    NBB_BYTE designated_router_repl[QOPM_ID_LEN];

    /*�ӿ�ѡ�ٵ�BDR*/
#define NSR_REPL_IF_BDR 3
    NBB_BYTE backup_designated_router_repl[QOPM_ID_LEN];

    /*�ӿ����������ID,��ֵֻ���ڽӿ�ͬ�������ʱ����Ч*/
#define NSR_REPL_IF_PARENT_AREA_ID 4
    NBB_BYTE parent_area_id_repl[4];

#define NSR_REPL_IF_PARENT_AREA_EXIST 5
    NBB_BOOL parent_area_exist;

    /*�ӿ�����*/
#define NSR_REPL_IF_TYPE 6
    NBB_LONG if_type_repl;

    /*�ӿڵĲ���״̬*/
#define NSR_REPL_IF_OPER_STATUS 7
    NBB_BYTE oper_status_repl;

}NSR_OSPF_INTERFACE_REPL;

typedef struct nsr_ospf_neighbor_repl
{
    /*�ھ�״̬��״̬*/
#define NSR_REPL_NBR_FSM_STATE 1
    NBB_LONG state_repl;

    /*�ھ�ѡ�ٳ���DR*/
#define NSR_REPL_NBR_DR 2
    NBB_BYTE designated_router_repl[QOPM_ID_LEN];

    /*�ھ�ѡ�ٳ���BDR*/
#define NSR_REPL_NBR_BDR 3
    NBB_BYTE backup_designated_router_repl[QOPM_ID_LEN];

    /*����յ���DD���*/
#define NSR_REPL_NBR_LAST_DD_SEQ_NUM 4
    NBB_ULONG last_dd_seq_num_repl;

    /*����յ���DDѡ��*/
#define NSR_REPL_NBR_LSAT_DD_OPTIOINS 5
    NBB_BYTE last_dd_options_repl;

    /*����յ���DD��ʶ*/
#define NSR_REPL_NBR_LAST_DD_FLSGS 6
    NBB_BYTE last_dd_flags_repl;

    /*�ھӱ��(��̬/����)*/
#define NSR_REPL_NBR_PERMANENCE 7
    NBB_LONG permanence_repl;

    /*�ھӶ�Ӧ��Router ID*/
#define NSR_REPL_NBR_ROUTER_ID 8
    NBB_BYTE rtr_id_repl[4];

    /*�ھӵ����ȼ�*/
#define NSR_REPL_NBR_PRIORITY 9
    NBB_BYTE priority_repl;

    /*���ӿڵĵ�ַ*/
#define NSR_REPL_PARENT_IF_ADDR 10
    ATG_INET_ADDRESS parent_if_ip_address_repl;

    /*ͬ�ھӵ��ڽӹ�ϵ*/
#define NSR_REPL_NBR_FRIEND_STATUS 11
    NBB_BYTE friend_status_repl;

#define NSR_REPL_NBR_OPER_STATUS 12
    NBB_BYTE oper_status_repl;

  /*�ھ�Helper״̬��״̬*/
#define NSR_REPL_NBR_RESTART_HELPER_FSM_STATE 13
    NBB_BYTE nbr_restart_helper_fsm_state_repl;
}NSR_OSPF_NEIGHBOR_REPL;

typedef struct nsr_ospf_repl_process_key
{
    NBB_USHORT process_id;
}NSR_OSPF_REPL_PROCESS_KEY;

typedef struct nsr_ospf_repl_area_key
{
    NBB_BYTE area_id[4];
}NSR_OSPF_REPL_AREA_KEY;

typedef struct nsr_ospf_repl_if_key
{
    ATG_INET_ADDRESS ip_address;
}NSR_OSPF_REPL_IF_KEY;

typedef struct nsr_ospf_repl_nbr_key
{
    NBB_LONG nbr_if_type; 
    NBB_BYTE router_id[QOPM_ID_LEN];
    ATG_INET_ADDRESS ip_addr;
}NSR_OSPF_REPL_NBR_KEY;

typedef struct nsr_ospf_repl_lsdb_key
{
    QOPM_LSA_HEADER lsa_header;
    NSR_OSPF_REPL_AREA_KEY area_key;
}NSR_OSPF_REPL_LSDB_KEY;

struct nsr_ospf_restore_cb;

/*NSRģ��OSPF����ҵ��ͳ��*/
typedef struct nsr_ospf_nsr_business_stat
{
    NBB_USHORT area_count;
    NBB_USHORT if_count;    
    NBB_USHORT nbr_count;
    NBB_USHORT nbr_in_state_count[QOAM_NBR_NUM_STATES + 1];
    NBB_ULONG  lsa_count;
    NBB_ULONG lsa_type_count[QOPM_MAX_AREA_LS_TYPE + 1];
}NSR_OSPF_NSR_BUSINESS_STAT;

typedef struct nsr_ospf_nsr_statistics
{
    NSR_OSPF_NSR_MSG_STAT ospf_nsr_msg_stat;
    NSR_OSPF_NSR_BUSINESS_STAT ospf_nsr_business_stat;
}NSR_OSPF_NSR_STATISTICS;


typedef struct nsr_ospf_entity
{
    NSR_OSPF_REPL_PROCESS_KEY repl_process_key;
    NSR_OSPF_ENTITY_REPL nsr_ospf_ent_repl;
    NBB_LQE entity_lqe; 
    AVLL_TREE active_repl_area_tree;
    AVLL_TREE glob_repl_if_tree;
    AVLL_TREE glob_repl_nbr_tree;
    AVLL_TREE repl_type5_lsdb_tree;
    NSR_OSPF_BACKUP_INFO backup_info;       /*OSPF�������ݽ��*/
    NSR_OSPF_RESTORE_INFO restore_info;     /*OSPF���ݻָ�������*/
    NSR_OSPF_SMOOTH_INFO smooth_info;       /*OSPFƽ��������*/
    struct nsr_ospf_restore_cb *restore_cb;
    NSR_OSPF_NSR_STATISTICS ospf_nsr_stat;
    NBB_BYTE restore_flag;    /*���ݻָ���ʶ*/
}NSR_OSPF_ENTITY;

typedef struct nsr_ospf_area_cb
{
    NSR_OSPF_REPL_AREA_KEY repl_area_key;
    AVLL_NODE active_repl_area_tree_node;
    AVLL_TREE repl_if_tree;
    AVLL_TREE repl_lsdb_type_tree[QOPM_MAX_AREA_LS_TYPE+1];
    NBB_ULONG  lsa_count;
    NBB_USHORT lsa_type_count[QOPM_MAX_AREA_LS_TYPE + 1];
    NBB_BYTE restore_flag;    /*���ݻָ���ʶ*/
}NSR_OSPF_AREA_CB;

typedef struct nsr_ospf_if_cb
{
    NSR_OSPF_REPL_IF_KEY repl_if_key;
    NSR_OSPF_INTERFACE_REPL nsr_ospf_if_repl;
    AVLL_NODE glob_repl_if_tree_node;
    AVLL_NODE repl_if_tree_node;
    AVLL_TREE repl_nbr_tree;
    NSR_OSPF_AREA_CB *parent_repl_area_cb;
    NBB_USHORT num_repl_neighbors;    
    NBB_USHORT repl_neighbors_in_state[QOAM_NBR_NUM_STATES + 1];
    NBB_BYTE restore_flag;    /*���ݻָ���ʶ*/
}NSR_OSPF_IF_CB;

typedef struct nsr_ospf_nbr_cb
{
    NSR_OSPF_REPL_NBR_KEY repl_nbr_key;
    NSR_OSPF_NEIGHBOR_REPL nsr_ospf_nbr_repl;
    AVLL_NODE glob_repl_nbr_tree_node;
    NSR_OSPF_IF_CB *parent_repl_if_cb;
    AVLL_NODE repl_nbr_tree_node;
    NBB_BYTE restore_flag;    /*���ݻָ���ʶ*/
}NSR_OSPF_NBR_CB;

typedef struct nsr_ospf_lsdb_cb
{
    QOPM_LSA_HEADER lsa_header;
    AVLL_NODE repl_lsdb_tree_node;
    NSR_OSPF_AREA_CB *associated_repl_area;
    NBB_BYTE restore_flag;    /*���ݻָ���ʶ*/
}NSR_OSPF_LSDB_CB;

typedef struct nsr_ospf_repl_pack_parms
{
  NBB_BYTE cb_type;

  NBB_VOID *cb_ptr;

  NBB_BYTE repl_operation;

  NBB_BOOL pack_entire;

  NBB_BYTE *packed_cb;    /*����������ʼλ��*/
  NBB_ULONG offset;       /*��������ƫ��(�ѱ������ݳ���)*/

  NBB_ULONG packed_cb_len;  /*�������ݵĳ���*/

} NSR_OSPF_REPL_PACK_PARMS;

typedef struct nsr_ospf_repl_unpack_parms
{
  //NBB_BYTE cb_type;

  NBB_VOID *cb_ptr;
  NSR_OSPF_ENTITY *nsr_ospf_ent;
  
  NSR_OSPF_DATA_HEADER *nsr_ospf_data_head;
  //NBB_BOOL pack_entire;

  NBB_BYTE *packed_cb;    /*����������ʼλ��*/
  NBB_ULONG offset;       /*��������ƫ��(�ѱ������ݳ���)*/

  NBB_ULONG packed_cb_len;  /*�������ݵĳ���*/

} NSR_OSPF_REPL_UNPACK_PARMS;

typedef struct nsr_ospf_restore_repl_pack_parms
{
    NBB_BYTE cb_type;
    NBB_VOID *cb_ptr;
    NBB_BYTE *packed_cb;        /*�������ݻָ�Buffer����ʼλ��*/
    NBB_ULONG offset;            /*ƫ��(�ѱ��ݻָ������ݳ���)*/
    NBB_ULONG packed_cb_len;    /*���ı������ݻָ�Buffer�Ĵ�С*/
} NSR_OSPF_RESTORE_REPL_PACK_PARMS;

typedef struct nsr_ospf_restore_repl_unpack_parms
{
  NBB_VOID *cb_ptr;
  NSR_OSPF_RESTORE_HEADER *nsr_ospf_restore_head;
  //NBB_BOOL pack_entire;

  NBB_BYTE *packed_cb;    /*����������ʼλ��*/
  NBB_ULONG offset;       /*��������ƫ��(�ѱ������ݳ���)*/

  NBB_ULONG packed_cb_len;  /*�������ݵĳ���*/

} NSR_OSPF_RESTORE_REPL_UNPACK_PARMS;

/*�������ݲ��Һ���*/
typedef NSR_OSPF_REPL_CB *(NSR_OSPF_REPL_TRAVERSE_PROC)(NBB_BYTE, NBB_VOID *);
/*�������ݱȽϺ���*/
typedef NBB_INT (NSR_OSPF_REPL_COMPARE_PROC)(NBB_BYTE, NBB_VOID *, NBB_VOID *);
/*�������ݳ��ȼ��㺯��*/
typedef NBB_ULONG (NSR_OSPF_REPL_PACK_LEN_PROC)(NSR_OSPF_REPL_PACK_PARMS *);
/*�������ݴ������*/
typedef NBB_VOID (NSR_OSPF_REPL_PACK_PROC)(NSR_OSPF_REPL_PACK_PARMS *);
/*�������ݽ������*/
typedef NBB_ULONG (NSR_OSPF_REPL_UNPACK_PROC)(NSR_OSPF_REPL_UNPACK_PARMS *);
/*���ݻָ����ݲ��Һ���*/
typedef NBB_VOID *(NSR_OSPF_RESTORE_TRAVERSE_PROC)(NSR_OSPF_ENTITY *, NBB_BYTE, NBB_VOID *);
/*���ݻָ����ݴ������*/
typedef NBB_ULONG (NSR_OSPF_RESTORE_REPL_PACK_PROC)(NSR_OSPF_RESTORE_REPL_PACK_PARMS *);
/*���ݻָ����ݽ������*/
typedef NBB_ULONG (NSR_OSPF_RESTORE_REPL_UNPACK_PROC)(NSR_OSPF_RESTORE_REPL_UNPACK_PARMS *);
/*���ݻָ���OSPF���ƿ���Һ���*/
typedef NBB_VOID *(NSR_OSPF_RESTORED_OSPF_TRAVERSE_PROC)(NBB_BYTE, NBB_VOID *, NBB_BYTE);
/*ȡ�����ݻָ���OSPF���ݴ�����*/
typedef NBB_ULONG (NSR_OSPF_RESTORED_DATA_CANCEL_PROC)(NBB_VOID *);

/*����OSPF�������ݲ�������*/
typedef struct nsr_ospf_rep_cb_type_parms
{
    NBB_BYTE cb_type;
    NBB_BOOL need_restore;          /*���������Ƿ���Ҫִ�б��ݻָ�����(��:������Ҫ�ָ�)*/
    NBB_BOOL need_restore_cancel;  /*���ݻָ������Ƿ����ȡ��*/
    NBB_ULONG repl_cb_offset;
    NBB_ULONG repl_cb_key_len;
    NBB_ULONG restore_repl_len;
    //NBB_ULONG pack_len;
    /*OSPF NSR�������ݺ���*/
    NSR_OSPF_REPL_TRAVERSE_PROC *nsr_ospf_traverse_proc;
    NSR_OSPF_REPL_COMPARE_PROC *nsr_ospf_compare_proc;
    NSR_OSPF_REPL_PACK_LEN_PROC *nsr_ospf_pack_len_proc;
    NSR_OSPF_REPL_PACK_PROC *nsr_ospf_pack_proc;
    NSR_OSPF_REPL_UNPACK_PROC *nsr_ospf_unpack_proc;
    /*OSPF NSR �������ݻָ�������*/
    NSR_OSPF_RESTORE_TRAVERSE_PROC *nsr_ospf_restore_traverse_proc;
    NSR_OSPF_RESTORE_REPL_PACK_PROC *nsr_ospf_restore_pack_proc;
    NSR_OSPF_RESTORE_REPL_UNPACK_PROC *nsr_ospf_restore_unpack_proc;
    /*OSPF NSR���ݻָ�����ȡ��������*/
    NSR_OSPF_RESTORED_OSPF_TRAVERSE_PROC *nsr_ospf_restored_ospf_traverse_proc;
    NSR_OSPF_RESTORED_DATA_CANCEL_PROC *nsr_ospf_restored_data_cancel_proc;
} NSR_OSPF_REP_CB_TYPE_PARMS;

/*����OSPF���ݵ���������*/
typedef struct nsr_ospf_repl_cb_type
{
    AVL_NODE cb_type_node;

    NBB_LQE entry_lqe;

    NBB_LONG cb_type;

    NBB_ULONG repl_order;

    NSR_OSPF_REP_CB_TYPE_PARMS parms;

} NSR_OSPF_REPL_CB_TYPE;

typedef struct nsr_ospf_backup_cb
{
    NBB_BYTE backup_state;
    NBB_BYTE chatch_up_state;
    NSR_OSPF_REPL_CB_TYPE *catch_up_cb_type_cb;
    NSR_OSPF_REPL_CB *catch_up_repl_cb;
    NSR_OSPF_CONTROL_MSG nsr_ospf_control_msg;
}NSR_OSPF_BACKUP_CB;

typedef struct nsr_ospf_restore_cb
{
    NBB_BYTE restore_status;
    NSR_OSPF_REPL_CB_TYPE *restore_type_cb;
    NBB_VOID *last_restored_cb;
    /*�洢���ݻָ����ݣ���OSPFģ����䣬�յ�Get��Ϣ��ֵ�����͸�OSPFģ����趨ΪNull*/
    ATG_I3_NSR_OSPF_RESTORE_IND *nsr_ospf_restore_ind;
    NSR_OSPF_ENTITY *parent_entry_cb;

}NSR_OSPF_RESTORE_CB;

/*OSPF NSR��Ϣ*/
typedef struct nsr_ospf
{
    NBB_BYTE nsr_ospf_status;     /*OSPF NSR״̬, ��������OSPF����״̬����״̬*/
    NBB_BYTE smooth_exit_reason;
    NBB_BOOL if_finish;           /*ospf�����Ƿ��յ�if finish��Ϣ��*/
    NBB_BOOL nsr_ospf_init;
    NBB_BOOL restore_finish;      /*OSPF�ı��������Ƿ���ɻָ�*/
    NBB_ULONG replicated_flag;    /*OSPF���̱������ݱ����Ƿ񱸷ݱ�ʶ,ÿ������OSPF���ݸ��¸ñ�ʶ,Ĭ��Ϊ0*/
    NBB_ULONG nsr_smooth_period;  /*OSPF NSRƽ�����ڣ�������ӿ��ϱ��������
                                    ƽ����ʱ��*/
    NBB_TIMER_DATA batchup_timer;
    NSR_OSPF_BACKUP_CB *ospf_backup_cb;
    /*���ݻָ��ھ��ӳ�ɾ������(ֻ�ж�̬�ھ���Ҫ�ӳ�ɾ��)*/
    NBB_LLQE_ROOT nsr_ospf_nbr_delay_del_proc_list;

    NSR_OSPF_STATISTICS nsr_ospf_stat;    /*OSPF NSR��ص�ͳ������*/
    
}NSR_OSPF;

typedef struct nsr_ospf_restore_repl_entity
{
    NSR_OSPF_REPL_PROCESS_KEY repl_process_key;
    NSR_OSPF_ENTITY_REPL nsr_ospf_ent_repl;
}NSR_OSPF_RESTORE_REPL_ENTITY;

typedef struct nsr_ospf_restore_repl_area_cb
{
    NSR_OSPF_REPL_AREA_KEY repl_area_key;
}NSR_OSPF_RESTORE_REPL_AREA_CB;

typedef struct nsr_ospf_restore_repl_if_cb
{
    NSR_OSPF_REPL_IF_KEY repl_if_key;
    NSR_OSPF_INTERFACE_REPL nsr_ospf_if_repl;
}NSR_OSPF_RESTORE_REPL_IF_CB;

typedef struct nsr_ospf_restore_repl_nbr_cb
{
    NSR_OSPF_REPL_NBR_KEY repl_nbr_key;
    NSR_OSPF_NEIGHBOR_REPL nsr_ospf_nbr_repl;
}NSR_OSPF_RESTORE_REPL_NBR_CB;

typedef struct nsr_ospf_restore_repl_lsdb_cb
{
    QOPM_LSA_HEADER lsa_header;
    NSR_OSPF_REPL_AREA_KEY area_key;
}NSR_OSPF_RESTORE_REPL_LSDB_CB;


typedef struct nsr_ospf_restored_get_cb
{
    NBB_BYTE restored_get_status;
    NSR_OSPF_REPL_CB_TYPE *restore_type_cb;
    NBB_VOID *last_restored_ospf_cb;
}NSR_OSPF_RESTORED_GET_CB;


#endif
