#ifndef NSR_OSPF_DEF01_INCLUDED
#define NSR_OSPF_DEF01_INCLUDED

/*NSR��������Ϣ���Ͷ���*/
#define NSR_OSPF_CONTROL_MSG_BACKUP       1     /*OSPF����״̬��Ϣ*/
#define NSR_OSPF_CONTROL_MSG_RESTORE      2     /*OSPF���ݻָ���Ϣ*/
#define NSR_OSPF_CONTROL_MSG_SMOOTH       3     /*OSPFƽ����Ϣ*/
#define NSR_OSPF_CONTROL_MSG_PROCESS      4     /*OSPF������Ϣ*/
#define NSR_OSPF_CONTROL_MSG_CAPABILITY   5     /*OSPF NSRʹ��/ȥʹ��*/


/*OSPF NSR״̬����*/
#define NSR_OSPF_STATUS_NULL              0
#define NSR_OSPF_STATUS_RESTORE_START    3
#define NSR_OSPF_STATUS_RESTORE_CANCEL   4
#define NSR_OSPF_STATUS_RESTORE_FINISH   5
#define NSR_OSPF_STATUS_SMOOTH_START     6
#define NSR_OSPF_STATUS_SMOOTH_FINISH    7

/*OSPF NSR��Ϣ�շ����Ͷ���*/
#define NSR_OSPF_MSG_DIRECT_SEND       0
#define NSR_OSPF_MSG_DIRECT_RECEIVE    1
#define NSR_OSPF_MSG_DIRECT_MAX        2

/*OSPF NSR����������������*/
#define NSR_OSPF_CONTROL_OK               0
#define NSR_OSPF_CONTROL_UNSUCCESS       1

#define NSR_OSPF_BACKUP_NULL      0   
#define NSR_OSPF_BACKUP_START     1   /*֪ͨOSPFģ������OSPF����������Ϣ*/
#define NSR_OSPF_BACKUP_CANCEL    2   /*֪ͨOSPFģ��ȡ��OSPF������Ϣ*/
#define NSR_OSPF_BACKUP_ERROR     3   /*֪ͨOSPFģ�鱸�ݴ�����Ϣ������Ϣ����������OSPF����*/
#define NSR_OSPF_BACKUP_FINISH    4   /*֪ͨNSRģ��OSPF�������������Ϣ*/
#define NSR_OSPF_BACKUP_MAX       5

#define NSR_OSPF_RESTORE_NULL     0
#define NSR_OSPF_RESTORE_START    1   /*֪ͨOSPģ���������ݻָ�*/
#define NSR_OSPF_RESTORE_GET      2   /*OSPFģ����NSRģ�鷢�ͱ��ݻָ�����Get��Ϣ*/
#define NSR_OSPF_RESTORE_CANCEL   3   /*NSRģ��֪ͨOSPFִ�б��ݻָ�ȡ������*/
#define NSR_OSPF_RESTORE_FINISH   4   /*OSPFģ�鱸�ݻָ����*/
#define NSR_OSPF_RESTORE_MAX      5

#define NSR_OSPF_SMOOTH_NULL      0
#define NSR_OSPF_SMOOTH_START     1
#define NSR_OSPF_SMOOTH_INTERFACE_NOTIFY_FINISH     2
#define NSR_OSPF_SMOOTH_FINISH    3
#define NSR_OSPF_SMOOTH_MAX       4

#define NSR_OSPF_PROCESS_DEL                0   /*֪ͨNSRģ��OSPF���̱�ɾ��*/
#define NSR_OSPF_PROCESS_ADD                1   /*֪ͨNSRģ��OSPF���̱����*/
#define NSR_OSPF_PROCESS_UP                 2   /*֪ͨNSRģ��OSPF���̱�up*/
#define NSR_OSPF_PROCESS_DOWN               3   /*֪ͨNSRģ��OSPF���̱�down*/


#define NSR_OSPF_ATG_NO               0x00
#define NSR_OSPF_ATG_YES              0x01

#define NSR_OSPF_REPL_MAX_FIELDS   30

/*OSPF������Ϣ����*/
#define NSR_OSPF_BACKUP_MSG_NULL      0
#define NSR_OSPF_BACKUP_MSG_START     1     /*OSPF����������Ϣ*/
#define NSR_OSPF_BACKUP_MSG_DATA      2     /*OSPF����������Ϣ*/
#define NSR_OSPF_BACKUP_MSG_FINISH    3     /*OSPF���������Ϣ*/
#define NSR_OSPF_BACKUP_MSG_MAX       4

/*OSPF��������״̬*/
#define NSR_OSPF_CATCHUP_NOT_START    0     /*��������δ����*/
#define NSR_OSPF_CATCHUP_INPROCESS    1     /*�������ݹ���*/
#define NSR_OSPF_CATCHUP_FINISH       2     /*�����������*/

/*OSPF���ݿ��ƿ���������״̬*/
#define NSR_OSPF_CATCHUP_CB_NOT_START   0   /*���ݿ��ƿ������δ����*/
#define NSR_OSPF_CATCHUP_CB_INPROCESS   1   /*���ݿ��ƿ鴦����������*/
#define NSR_OSPF_CATCHUP_CB_FINISHED    2   /*���ݿ��ƿ��������*/


/*�����Ƿ񱸷ݱ�ʶ�������������ݸ���һ��*/
#define NSR_OSPF_REPLICATED_FLAG_NONE    0
#define NSR_OSPF_REPLICATED_FLAG_A        1   /*���ƿ��Ƿ񱸷ݱ�ʶA*/
#define NSR_OSPF_REPLICATED_FLSA_B        2   /*���ƿ��Ƿ񱸷ݱ�ʶB*/

#define NSR_OSPF_NEW_CB_BY_RESTORE           0x01   /*��ʶ���ƿ�Ϊ���ݻָ����ݴ���*/
#define NSR_OSPF_REPL_CB_CREATE              0x02   /*��ʶ���ƿ鱸��*/
#define NSR_OSPF_REPL_DATA_CHANGED           0x04   /*NSR�������ݸ����и���*/
#define NSR_OSPF_REPL_CB_ALREADY_RESTORED   0x08   /*��ʶ���������ѻָ���OSPF���ƿ���*/
#define NSR_OSPF_SEND_REPL_LSA_REQUEST      0x10    /*��ʶOSPF�ھ���Ҫ���ڱ��ݵ�LSA����LSA������*/
#define NSR_OSPF_UPDATE_CB_BY_RESTORE       0x20    /*��ʶ���ƿ����NSR�ָ�����*/


/*�������ݵ���󳤶�*/
#define NSR_OSPF_BACKUP_LEN_MAX   2048
/*�������ݵ���С����*/
#define NSR_OSPF_BACKUP_LEN_MIN  \
  (sizeof(NSR_BACKUP_HEADER) + sizeof(NSR_OSPF_BACKUP_HEADER))

/*���ݵ���������*/
#define NSR_OSPF_REPL_TYPE_PROCESS  1
#define NSR_OSPF_REPL_TYPE_AREA     2
#define NSR_OSPF_REPL_TYPE_IF       3
#define NSR_OSPF_REPL_TYPE_NBR      4
#define NSR_OSPF_REPL_TYPE_LSA      5

/*���ݲ�������*/
#define NSR_OSPF_OP_NONE    0
#define NSR_OSPF_OP_CREATE  1
#define NSR_OSPF_OP_MODIFY  2
#define NSR_OSPF_OP_DELETE  3


/*�����������ݵ�ʱ����*/
#define NSR_OSPF_BATCHUP_INTERVAL  1000
/*ÿ�η����������ݵı��ĸ���*/
#define NSR_OSPF_BATCHUP_COUNT  100

/*ģ�鱸�ݻָ������Buffer��С*/
#define NSR_OSPF_RESTORE_DEFAULT_LEN   8192

#define NSR_OSPF_RESTORE_FIRST  1
#define NSR_OSPF_RESTORE_NEXT   2

/*NSR���ݻָ�״̬*/
#define NSR_RESTORE_NOT_START    0     /*���ݻָ�δ����*/
#define NSR_RESTORE_INPROCESS    1     /*���ݻָ�����*/
#define NSR_RESTORE_FINISH       2     /*���ݻָ����*/

/*OSPF���ݻָ����ݻ�ȡ״̬*/
#define NSR_OSPF_RESTORED_GET_NOT_START    0     /*OSPF���ݻָ����ݻ�ȡδ����*/
#define NSR_OSPF_RESTORED_GET_INPROCESS    1     /*OSPF���ݻָ����ݻ�ȡ����*/
#define NSR_OSPF_RESTORED_GET_FINISH       2     /*OSPF���ݻָ����ݻ�ȡ���*/

#define NSR_OSPF_SET_REPL_DATA_CHANGE(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag |= NSR_OSPF_REPL_DATA_CHANGED)
  
#define NSR_OSPF_UNSET_REPL_DATA_CHANGE(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag &= ~NSR_OSPF_REPL_DATA_CHANGED)

#define NSR_OSPF_IS_REPL_DATA_CHANGED(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag & NSR_OSPF_REPL_DATA_CHANGED)

/*NSRƽ��������*/
#define NSR_OSPF_SMOOTH_NULL            0
#define NSR_OSPF_SMOOTH_COMPLETE        1
#define NSR_OSPF_SMOOTH_TIMEOUT         2
#define NSR_OSPF_SMOOTH_TOP_CHANGED    3

/*NSRƽ����������(40��)*/
#define NSR_OSPF_NSR_SMOOTH_PERIOD    40

/*�趨�����ɵĿ��ƿ��ɱ��ݻָ�����*/
#define NSR_OSPF_SET_NEW_CB_BY_RESTORE(NSR_OSPF_REPL_CB)  \
  ((NSR_OSPF_REPL_CB).repl_cb_flag |= NSR_OSPF_NEW_CB_BY_RESTORE)
/*ȡ�����ƿ��ɱ��ݻָ�������ʶ*/
#define NSR_OSPF_UNSET_NEW_CB_BY_RESTORE(NSR_OSPF_REPL_CB)  \
  ((NSR_OSPF_REPL_CB).repl_cb_flag &= ~NSR_OSPF_NEW_CB_BY_RESTORE)
/*�жϿ��ƿ��Ƿ��ɱ��ݻָ�����*/
#define NSR_OSPF_IS_NEW_CB_BY_RESTORE(NSR_OSPF_REPL_CB)  \
  ((NSR_OSPF_REPL_CB).repl_cb_flag & NSR_OSPF_NEW_CB_BY_RESTORE)

/*�趨���������Ѿ��ָ���ʶ*/
#define NSR_OSPF_SET_REPL_DATA_RESTORED(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag |= NSR_OSPF_REPL_CB_ALREADY_RESTORED)
/*ȡ���������������ѻָ���ʶ*/
#define NSR_OSPF_SET_REPL_DATA_UNRESTORED(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag &= ~NSR_OSPF_REPL_CB_ALREADY_RESTORED)
/*�ж��Ƿ���ڱ��ݻָ�����*/
#define NSR_OSPF_IS_REPL_DATA_RESTORED(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag & NSR_OSPF_REPL_CB_ALREADY_RESTORED)

/*�趨OSPF�ھ���Ҫ���ڱ��ݵ�LSA����LSA Request*/
#define NSR_OSPF_SET_SEND_REPL_LSA_REQUEST(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag |= NSR_OSPF_SEND_REPL_LSA_REQUEST)
/*ȡ��OSPF�ھ���Ҫ���ڱ��ݵ�LSA����LSA Request��ʶ*/
#define NSR_OSPF_UNSET_SEND_REPL_LSA_REQUEST(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag &= ~NSR_OSPF_SEND_REPL_LSA_REQUEST)
/*�ж�OSPF�ھ��Ƿ���Ҫ���ڱ��ݵ�LSA����LSA Request*/
#define NSR_OSPF_NEED_SEND_REPL_LSA_REQUEST(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag & NSR_OSPF_SEND_REPL_LSA_REQUEST)

/*�趨���ƿ����NSR�ָ�������*/
#define NSR_OSPF_SET_UPDATE_CB_BY_RESTORE(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag |= NSR_OSPF_UPDATE_CB_BY_RESTORE)
/*ȡ�����ƿ鱣��NSR�ָ����ݱ�ʶ*/
#define NSR_OSPF_UNSET_UPDATE_CB_BY_RESTORE(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag &= ~NSR_OSPF_UPDATE_CB_BY_RESTORE)
/*�жϿ��ƿ��Ƿ����NSR�ָ�������*/
#define NSR_OSPF_IS_UPDATE_CB_BY_RESTORE(NSR_OSPF_REPL_CB) \
  ((NSR_OSPF_REPL_CB).repl_cb_flag & NSR_OSPF_UPDATE_CB_BY_RESTORE)

#define NSR_OSPF_MSG_STAT_FOR_SEND(MSG_TYPE, MSG_OPT, SUB_OPT) \
  nsr_ospf_msg_statistics(NSR_OSPF_MSG_DIRECT_SEND, (MSG_TYPE), (MSG_OPT), (SUB_OPT))

#define NSR_OSPF_MSG_STAT_FOR_RECEIVE(MSG_TYPE, MSG_OPT, SUB_OPT) \
  nsr_ospf_msg_statistics(NSR_OSPF_MSG_DIRECT_RECEIVE, (MSG_TYPE), (MSG_OPT), (SUB_OPT))

/*OSPF NSR����ͳ��*/
#define NSR_OSPF_PERFORMANCE_OPT_START  1
#define NSR_OSPF_PERFORMANCE_OPT_END    2

/*OSPF NSR ����ͳ������*/
#define NSR_OSPF_PERFORMANCE_BACKUP              1
#define NSR_OSPF_PERFORMANCE_RESTORE             2
#define NSR_OSPF_PERFORMANCE_RESTORE_UNPACKET   3
#define NSR_OSPF_PERFORMANCE_IF_NOTIFY           4
#define NSR_OSPF_PERFORMANCE_SMOOTH              5

/*���OSPF NSR��������*/
#define NSR_OSPF_CLEAR_PERFORMANCE(PERF_DATA) \
  (PERF_DATA).start_time = 0;  \
  (PERF_DATA).end_time = 0;

/*����OSPF NSR�������ݲɼ�*/
#define NSR_OSPF_SET_PERFORMANCE_S(PERF_DATA) \
  NSR_OSPF_CLEAR_PERFORMANCE(PERF_DATA);  \
  (PERF_DATA).start_time = NBB_GET_MTIME(); 

/*ֹͣOSPF NSR�������ݲɼ�*/
#define NSR_OSPF_SET_PERFORMANCE_E(PERF_DATA) \
  (PERF_DATA).end_time = NBB_GET_MTIME();

/*����OSPF NSR��������*/
#define NSR_OSPF_CALC_PERFORMANCE(PERF_DATA)  \
  ((PERF_DATA).end_time - (PERF_DATA).start_time)

/*��ȡOSPF���ݻָ����Ĺ���������Ϣ*/
#define NSR_OSPF_GET_PERF_DATA_RESTORE()  \
  (LOCAL.nsr_ospf.nsr_ospf_stat.nsr_ospf_perf_stat.restore_perf_stat.restore_perf)

/*��ȡOSPF���ݻָ����½������������Ϣ*/
#define NSR_OSPF_GET_PERF_DATA_RESTORE_UNPACKET()  \
  (LOCAL.nsr_ospf.nsr_ospf_stat.nsr_ospf_perf_stat.restore_perf_stat.last_restore_unpacket_perf)

/*ͳ��OSPF�����յ�����Ϣ*/
#define NSR_OSPF_ADP_MSG_STAT_FOR_SEND(INDEX, MSG_TYPE, MSG_OPT) \
  nsr_ospf_adp_msg_statistics(NSR_OSPF_MSG_DIRECT_SEND, (INDEX), (MSG_TYPE), (MSG_OPT))
/*ͳ��OSPF���䷢�͵���Ϣ*/
#define NSR_OSPF_ADP_MSG_STAT_FOR_RECEIVE(INDEX, MSG_TYPE, MSG_OPT) \
  nsr_ospf_adp_msg_statistics(NSR_OSPF_MSG_DIRECT_RECEIVE, (INDEX), (MSG_TYPE), (MSG_OPT))

/*ͳ��NSRģ�鱸�ݵ�OSPF�յ�����Ϣ*/
#define NSR_OSPF_NSR_MSG_STAT_FOR_SEND(ENT_CB, MSG_TYPE, MSG_OPT, SUB_TYPE) \
  nsr_ospf_nsr_msg_statistics(NSR_OSPF_MSG_DIRECT_SEND, (ENT_CB), (MSG_TYPE), (MSG_OPT), (SUB_TYPE))

/*ͳ��NSRģ�鱸�ݵ�OSPF���͵���Ϣ*/
#define NSR_OSPF_NSR_MSG_STAT_FOR_RECEIVE(ENT_CB, MSG_TYPE, MSG_OPT, SUB_TYPE) \
  nsr_ospf_nsr_msg_statistics(NSR_OSPF_MSG_DIRECT_RECEIVE, (ENT_CB), (MSG_TYPE), (MSG_OPT), (SUB_TYPE))

/*OSPF NSR�������ݻָ���ʶ*/
#define NSR_OSPF_RESTORE_FLG_CANCELED      0x01
#define NSR_OSPF_RESTORE_FLG_WAIT_RESTORE  0x02
#define NSR_OSPF_RESTORE_FLG_FINISHED       0x04

/*�ж�NSR���ݵ�OSPF�����Ƿ���Ҫ�ָ�,�ñ��ִ��NSR_CanStartOSPFRestoreʱ�趨��*/
#define NSR_OSPF_IS_DATA_WAIT_RESTORE(RESTORE_FLAG) \
  ((RESTORE_FLAG) & NSR_OSPF_RESTORE_FLG_WAIT_RESTORE) 
/*�趨NSR���ݵ�OSPF���ݴ�ִ�б��ݻָ���ʶ*/
#define NSR_OSPF_SET_DATA_WAIT_RESTORE(RESTORE_FLAG) \
  ((RESTORE_FLAG) |= NSR_OSPF_RESTORE_FLG_WAIT_RESTORE)
/*ȡ��NSR���ݵ�OSPF���ݴ�ִ�б��ݻָ���ʶ*/
#define NSR_OSPF_UNSET_DATA_WAIT_RESTORE(RESTORE_FLAG) \
  ((RESTORE_FLAG) &= ~NSR_OSPF_RESTORE_FLG_WAIT_RESTORE)
  
/*�ж�NSR���ݵ�OSPF���ݱ��ݻָ��Ƿ��Ѿ�ȡ��*/
#define NSR_OSPF_IS_DATA_RESTORE_CANCEL(RESTORE_FLAG) \
    ((RESTORE_FLAG) & NSR_OSPF_RESTORE_FLG_CANCELED)
/*�趨NSR���ݵ�OSPF���ݱ��ݻָ�ȡ����ʶ*/
#define NSR_OSPF_SET_DATA_RESTORE_CANCEL(RESTORE_FLAG) \
    ((RESTORE_FLAG) |= NSR_OSPF_RESTORE_FLG_CANCELED)
/*ȡ��NSR���ݵ�OSPF���ݱ��ݻָ�ȡ����ʶ*/
#define NSR_OSPF_UNSET_DATA_RESTORE_CANCEL(RESTORE_FLAG) \
    ((RESTORE_FLAG) &= ~NSR_OSPF_RESTORE_FLG_CANCELED)
    
/*�ж�NSR���ݵ�OSPF���ݱ��ݻָ��Ƿ����*/
#define NSR_OSPF_IS_DATA_RESTORE_FINISH(RESTORE_FLAG) \
    ((RESTORE_FLAG) & NSR_OSPF_RESTORE_FLG_FINISHED)  
/*�趨NSR���ݵ�OSPF���ݱ��ݻָ���ɱ�ʶ*/
#define NSR_OSPF_SET_DATA_RESTORE_FINISH(RESTORE_FLAG) \
    ((RESTORE_FLAG) |= NSR_OSPF_RESTORE_FLG_FINISHED)
/*ȡ��NSR���ݵ�OSPF���ݱ��ݻָ���ɱ�ʶ*/
#define NSR_OSPF_UNSET_DATA_RESTORE_FINISH(RESTORE_FLAG) \
    ((RESTORE_FLAG) &= ~NSR_OSPF_RESTORE_FLG_FINISHED)

#endif
