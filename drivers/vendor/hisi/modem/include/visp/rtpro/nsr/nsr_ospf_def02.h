#ifndef NSR_OSPF_DEF02_INCLUDED
#define NSR_OSPF_DEF02_INCLUDED

/*ͨ��NSR_OSPF_REPL_CB��ȡParentָ��*/
#define NSR_OSPF_GET_PARENT_FROM_RCB(RCB, CB_TYPE_CB) \
          (NBB_VOID *)(((NBB_BYTE *)(RCB)) - (CB_TYPE_CB)->parms.repl_cb_offset)

/*ͨ��Parent��ȡNSR_OSPF_REPL_CB*/
#define NSR_OSPF_GET_RCB_FROM_PARENT(PARENT, CB_TYPE_CB) \
     (AHL_REP_CB *)(((NBB_BYTE *)(PARENT)) + (CB_TYPE_CB)->parms.repl_cb_offset)

/*����OSPF NSR���ݱ�ʶ*/
#define NSR_OSPF_SET_OSPF_REPLICATED_FLAG()  \
  LOCAL.nsr_ospf.replicated_flag = NBB_GET_MTIME()

/*�ж�OSPF�����Ƿ��Ѿ�����*/
#define NSR_OSPF_IS_DATA_REPLICATED(FLAG)   \
  ((LOCAL.nsr_ospf.replicated_flag != 0) && \
  (LOCAL.nsr_ospf.replicated_flag == (FLAG)))
  
/*����NSR���ݱ�ʶ*/
#define NSR_OSPF_SET_DATA_REPLICATED_FLAG(REPLICATED_FLAG)  \
  (REPLICATED_FLAG) = LOCAL.nsr_ospf.replicated_flag
  
#define OSPF_NSR_BACKUP_START()   \
  ((LOCAL.nsr_ospf.ospf_backup_cb->backup_state == NSR_OSPF_BKS_BACKUP_OK) || \
   (LOCAL.nsr_ospf.ospf_backup_cb->backup_state == NSR_OSPF_BKS_INBACKUP))


#define OSPF_NSR_BACKUP_OK()   (LOCAL.nsr_ospf.ospf_backup_cb->backup_state == NSR_OSPF_BKS_BACKUP_OK)

#define OSPF_NSR_IS_INIT()    (LOCAL.nsr_ospf.nsr_ospf_init == TRUE)
#define NSR_OSPF_VALID_BACKUP_CB(OSPF_BACKUP_CB)    nsr_ospf_valid_backup_cb(OSPF_BACKUP_CB)
/*NSR OSPF֧�ֵ�LSA����*/
#define NSR_OSPF_SUPPORT_LSA(LS_TYPE) \
  ((LS_TYPE == QOPM_LSA_TYPE_ROUTER) || \
   (LS_TYPE == QOPM_LSA_TYPE_NETWORK) || \
   (LS_TYPE == QOPM_LSA_TYPE_INTER_AREA_PFX) || \
   (LS_TYPE == QOPM_LSA_TYPE_INTER_AREA_RTR) || \
   (LS_TYPE == QOPM_LSA_TYPE_AS_EXTERNAL) || \
   (LS_TYPE == QOPM_LSA_TYPE_NSSA))

#define NSR_OSPF_RESTORE_SCOPE_AS   QOAM_FLOOD_SCOPE_AS
#define NSR_OSPF_RESTORE_SCOPE_AREA QOAM_FLOOD_SCOPE_AREA
#define NSR_OSPF_RESTORE_SCOPE_LINK QOAM_FLOOD_SCOPE_LINK

/*OSPF�������ݻָ��Ƿ����*/
#define NSR_OSPF_IS_RESTORE_FINISH()  (LOCAL.nsr_ospf.restore_finish)

/*NSRƽ���Ƿ����*/
#define NSR_OSPF_IS_SMOOTH_FINISH()  \
  (LOCAL.nsr_ospf.nsr_ospf_status == NSR_OSPF_STATUS_SMOOTH_FINISH)

/*OSPF����NSRƽ������*/
#define NSR_OSPF_IS_SMOOTHING()  \
  (NSR_OSPF_IS_RESTORE_FINISH() && !NSR_OSPF_IS_SMOOTH_FINISH())

/*�ж��Ƿ�ΪLoopback��ַ*/
#define NSR_OSPF_IS_HOST_LOOPBACK_ADDR(IP_ADDR)  \
  ((IP_ADDR).address[0] == QOPM_CLASSA_LOOPBACK_BYTE1)

/*�жϱ��ݵĽ��̲���״̬�Ƿ�UP*/
#define NSR_OSPF_IS_REPL_ENT_UP(OPER_STATUS)  \
  ((OPER_STATUS) == qopm_mib_ent_product_data.oper_states.up)

/*�жϱ��ݵĽ��̲���״̬�Ƿ�DOWN*/
#define NSR_OSPF_IS_REPL_ENT_DOWN(OPER_STATUS)  \
  ((OPER_STATUS) == qopm_mib_ent_product_data.oper_states.donw)

/*�жϱ��ݵ��������״̬�Ƿ�UP*/
#define NSR_OSPF_IS_REPL_AREA_UP(OPER_STATUS)  TRUE

/*�жϱ��ݵĽӿڲ���״̬�Ƿ�UP*/
#define NSR_OSPF_IS_REPL_IF_UP(OPER_STATUS)  \
  ((OPER_STATUS) == qopm_mib_if_product_data.oper_states.up)

/*�жϱ��ݵĽӿڲ���״̬�Ƿ�Down*/
#define NSR_OSPF_IS_REPL_IF_DOWN(OPER_STATUS)  \
  ((OPER_STATUS) == qopm_mib_if_product_data.oper_states.down)

/*�жϱ��ݵ��ھӲ���״̬�Ƿ�UP*/
#define NSR_OSPF_IS_REPL_NBR_UP(OPER_STATUS)  \
  ((OPER_STATUS) == qopm_mib_nbr_product_data.oper_states.up)

/*�жϱ��ݵ��ھӲ���״̬�Ƿ�DOWN*/
#define NSR_OSPF_IS_REPL_NBR_DOWN(OPER_STATUS)  \
  ((OPER_STATUS) == qopm_mib_nbr_product_data.oper_states.down)

#endif

