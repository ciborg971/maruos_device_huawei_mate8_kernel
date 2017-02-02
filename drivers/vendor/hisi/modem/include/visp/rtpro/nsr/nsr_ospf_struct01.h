/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              nsr_ospf_struct01.h
*
*  Project Code: Dopra V3R2
*   Module Name: OSPF NSR���ݽ������(1)  
*  Date Created: 2013-10-11
*        Author: guojianjun178934
*   Description: ��ͷ�ļ��ж�������ݽṹֻ����NBase�Ļ������ݽṹ��
*                ���漰OSPF�ڲ����ݽṹ,�����Ҫ����OSPF�ڲ������
*                �����ļ�nsr_ospf_struct02.h�ж��塣
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-10-11   guojianjun178934        Create
*
*******************************************************************************/
#ifndef NSR_OSPF_STRUCT01_INCLUDED
#define NSR_OSPF_STRUCT01_INCLUDED

typedef struct nsr_ospf_backup_info
{
    NBB_BYTE backup_opt;
    NBB_BYTE result;
    NBB_BYTE pad[2];
}NSR_OSPF_BACKUP_INFO;

typedef struct nsr_ospf_restore_header
{
    NBB_BYTE data_type;           /*�ָ�����������*/
    NBB_USHORT num_entries;        /*������ʵ����*/
}NSR_OSPF_RESTORE_HEADER;

typedef struct atg_i3_nsr_ospf_restore_ind
{
    NBB_IPS ips_hdr;
    NBB_BYTE more_entries;
    NBB_USHORT total_entries;
} ATG_I3_NSR_OSPF_RESTORE_IND;

typedef struct nsr_ospf_restore_info
{
    NBB_BYTE restore_opt;
    NBB_BYTE list_option;
    NBB_BYTE result;
    NBB_BYTE pad[1];
    NBB_BYTE cur_router_id_repl[4];
    ATG_I3_NSR_OSPF_RESTORE_IND *nsr_ospf_restore_ind;
}NSR_OSPF_RESTORE_INFO;

typedef struct nsr_ospf_smooth_info
{
    NBB_BYTE smooth_opt;
    NBB_BYTE result;
    NBB_BYTE pad[2];
}NSR_OSPF_SMOOTH_INFO;


typedef struct nsr_ospf_process_info
{
    NBB_LONG flag; /*ֵ0-���̱�ɾ��*/
}NSR_OSPF_PROCESS_INFO;


/*OSPF NSR����������Ϣ����*/
typedef struct nsr_ospf_control_msg
{
    NBB_USHORT  process_id;
    NBB_BYTE msg_type;
    union
      {
          NSR_OSPF_BACKUP_INFO backup_info;       /*OSPF����״̬֪ͨ*/
          NSR_OSPF_RESTORE_INFO restore_info;     /*OSPF���ݻָ�֪ͨ*/
          NSR_OSPF_SMOOTH_INFO smooth_info;       /*OSPFƽ��֪ͨ*/
          NSR_OSPF_PROCESS_INFO process_info;     /*OSPF����״̬*/
          NBB_BYTE nsr_capability_info;          /*OSPF NSR ʹ��/ ȥʹ��*/
      }control_msg;

}NSR_OSPF_CONTROL_MSG;

typedef struct atg_i3_nsr_notify_ospf
{
  NBB_IPS ips_hdr;
  NSR_OSPF_CONTROL_MSG nsr_ospf_control_msg;
} ATG_I3_NSR_NOTIFY_OSPF;

/*OSPF NSR�������ݿ�����Ϣ*/
typedef struct nsr_opsf_repl_cb
{
    /*NBB_BYTE repl_type;*/
    NBB_BYTE repl_operation;    /*�������ݵĲ���,����ʵʱ����*/
    NBB_BYTE repl_cb_flag;      /*�������ݵı�ʶ��Ϣ*/
    NBB_ULONG replicated_flag;   /*���ƿ��Ƿ񱸷ݱ�ʶ*/
}NSR_OSPF_REPL_CB;

typedef struct nsr_ospf_repl_field_info
{
  NBB_BYTE field_absent[NSR_OSPF_REPL_MAX_FIELDS];

} NSR_OSPF_REPL_FIELD_INFO;

/* OSPF������Ϣͷ���� */
typedef struct nsr_ospf_backup_header
{
    NBB_USHORT process_id;    /*OSPF����ID*/
    NBB_BYTE backup_type;     /*��������(����/ʵ��)*/
    NBB_BYTE msg_type;        /*��Ϣ����(����/����)*/
    NBB_USHORT msg_len;       /*�������ݳ���(��������Ϣͷ)*/
}NSR_OSPF_BACKUP_HEADER;

/*OSPF��������ͷ*/
typedef struct nsr_ospf_data_header
{
    NBB_BYTE data_type;          /*������������*/
    NBB_BYTE rep_operation;     /*���ݲ�������*/
    NBB_USHORT total_len;      /*�������ݳ���*/
    /*��������ű����������Ͷ�Ӧ�ļ�ֵ,��LSA�Ĵ������*/
}NSR_OSPF_DATA_HEADER;

/*�洢NSR OSPF��ص�����*/
typedef struct nsr_ospf_data
{
    AVL_TREE cb_type_tree;
    NBB_LQE cb_type_list;
    NBB_ULONG next_cb_type_repl_order;

    NBB_LQE ospf_backup_list;
}NSR_OSPF_DATA;

/*Added by guojianjun178934, I3֪ͨOSPF������֤���, 2013/3/2   ���ⵥ��:20130118_01 */
typedef struct atg_i3_notify_crypto_seq_num_refresh
{
    NBB_IPS ips_hdr;
    NBB_ULONG seq_num;
}ATG_I3_NOTIFY_CRYPTO_SEQ_NUM_REFRESH;
/* End of Added by guojianjun178934, 2013/3/2   ���ⵥ��:20130118_01 */

/*OSPF NSR��Ϣͳ�����ݽṹ*/
/*OSPF NSR������Ϣͳ��*/
typedef struct nsr_ospf_backup_msg_stat
{   
    NBB_ULONG control_msg[NSR_OSPF_BACKUP_MAX];
    NBB_ULONG data_msg[NSR_OSPF_BACKUP_MSG_MAX];
}NSR_OSPF_BACKUP_MSG_STAT;

/*OSPF NSR���ݻָ���Ϣͳ��*/
typedef struct nsr_ospf_restore_msg_stat
{   
    NBB_ULONG control_msg[NSR_OSPF_RESTORE_MAX];
    NBB_ULONG data_msg;
}NSR_OSPF_RESTORE_MSG_STAT;

/*OSPF NSR����ƽ����Ϣͳ��*/
typedef struct nsr_ospf_smooth_msg_stat
{   
    NBB_ULONG control_msg[NSR_OSPF_SMOOTH_MAX];
    NBB_ULONG data_msg;
}NSR_OSPF_SMOOTH_MSG_STAT;

/*OSPF NSR��Ϣͳ������*/
typedef struct nsr_ospf_msg_stat
{
    NSR_OSPF_BACKUP_MSG_STAT backup_msg_stat[NSR_OSPF_MSG_DIRECT_MAX];
    NSR_OSPF_RESTORE_MSG_STAT restore_msg_stat[NSR_OSPF_MSG_DIRECT_MAX];
    NSR_OSPF_SMOOTH_MSG_STAT smooth_msg_stat[NSR_OSPF_MSG_DIRECT_MAX];
}NSR_OSPF_MSG_STAT;

/*OSPF NSR��������ͳ��*/
typedef struct nsr_ospf_performance_data
{
    NBB_ULONG start_time;
    NBB_ULONG end_time;
}NSR_OSPF_PERFORMANCE_DATA;

/*OSPF NSR���ݻָ�����ͳ������*/
typedef struct nsr_ospf_restore_performance_stat
{
    NSR_OSPF_PERFORMANCE_DATA restore_perf;
    NSR_OSPF_PERFORMANCE_DATA last_restore_unpacket_perf;
    NBB_ULONG total_restore_unpacket_time;
}NSR_OSPF_RESTORE_PERFORMANCE_STAT;

/*OSPF NSR����ͳ������*/
typedef struct nsr_ospf_performance_stat
{
    NSR_OSPF_RESTORE_PERFORMANCE_STAT restore_perf_stat;
}NSR_OSPF_PERFORMANCE_STAT;

/*OSPF NSRͳ������*/
typedef struct nsr_ospf_statistics
{
    NSR_OSPF_MSG_STAT nsr_ospf_msg_stat;
    NSR_OSPF_PERFORMANCE_STAT nsr_ospf_perf_stat;
}NSR_OSPF_STATISTICS;

typedef struct nsr_ospf_adp_statistics
{
    NBB_ULONG backup_control_msg[NSR_OSPF_MSG_DIRECT_MAX][NSR_OSPF_BACKUP_MAX];
    NBB_ULONG smooth_control_msg[NSR_OSPF_MSG_DIRECT_MAX][NSR_OSPF_SMOOTH_MAX];

}NSR_OSPF_ADP_STATISTICS;

typedef struct nsr_ospf_nsr_msg_stat
{
    /*�յ���ϢNSR_OSPF_BACKUP_MSG_START�󣬻�ִ��ɾ�����ݵ�OSPF���̣����Բ�ͳ�Ƹ���Ϣ*/
    NBB_ULONG rcv_backup_data_msg[NSR_OSPF_BACKUP_MSG_MAX];
    NSR_OSPF_RESTORE_MSG_STAT restore_msg_stat[NSR_OSPF_MSG_DIRECT_MAX];
    NSR_OSPF_SMOOTH_MSG_STAT smooth_msg_stat[NSR_OSPF_MSG_DIRECT_MAX];
}NSR_OSPF_NSR_MSG_STAT;

typedef struct if_notify_data
{
    NBB_USHORT if_up_stat;
    NBB_USHORT if_down_stat;
}IF_NOTIFY_DATA;

typedef struct nsr_i3_if_notify_stat
{
    /*Trunk�ӿ��ϱ�ͳ��*/
    IF_NOTIFY_DATA trunk_notify_stat;
    /*��Trunk�ӿ��ϱ�ͳ��*/
    IF_NOTIFY_DATA no_trunk_notify_stat;
}NSR_I3_IF_NOTIFY_STAT;

typedef struct nsr_i3_data
{
    NBB_BOOL switch_to_master;
    NBB_BOOL if_notify_finish;
    /*�����󣬽ӿ��ϱ�����ǰ�ϱ��ӿ�ͳ��*/
    NSR_I3_IF_NOTIFY_STAT if_notify_stat_before_finish;
    /*�����󣬽ӿ��ϱ�������ӿ��ϱ�ͳ��*/
    NSR_I3_IF_NOTIFY_STAT if_notify_stat_after_finish;
}NSR_I3_DATA;

#endif
