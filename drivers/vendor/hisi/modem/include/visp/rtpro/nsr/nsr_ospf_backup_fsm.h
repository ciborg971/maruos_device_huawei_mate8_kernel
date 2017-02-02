#ifndef NSR_OSPF_BACKUP_FSM_INCLUDED
#define NSR_OSPF_BACKUP_FSM_INCLUDED

#ifdef  __cplusplus
extern "C"{
#endif

/*NSR OSPF����״̬����*/
#define NSR_OSPF_BACKUP_NUM_STATES     3
/*NSR OSPF���������¼�����*/
#define NSR_OSPF_BACKUP_NUM_INPUTS     5

/*NSR����״̬����*/
#define NSR_OSPF_BKS_NULL          1
#define NSR_OSPF_BKS_INBACKUP      2
#define NSR_OSPF_BKS_BACKUP_OK     3

/*NSR���������¼�����*/
#define NSR_OSPF_BKI_NEW_BACKUP        0
#define NSR_OSPF_BKI_REPL_COMPLETE     1
#define NSR_OSPF_BKI_REPL_FAIL         2
#define NSR_OSPF_BKI_REPL_ABORT        3
#define NSR_OSPF_BKI_PROCESS_DOWN      4

VOID nsr_ospf_backup_fsm(NBB_BYTE input);

#ifdef  __cplusplus
}
#endif

#endif

