/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              nsr_entity.h
*
*  Project Code: Dopra V3R2
*   Module Name:   
*  Date Created: 2013-10-11
*        Author: guojianjun178934
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-10-11   guojianjun178934        Create
*
*******************************************************************************/
#ifndef NSR_ENTITY_INCLUDED
#define NSR_ENTITY_INCLUDED

/*NSR��Ϣ����*/
#define NSR_MSG_BACKUP_START                 0X00000001    /*����������Ϣ*/
#define NSR_MSG_BACKUP_OUT_OF_ORDER          0X00000002    /*����������Ϣ*/
#define NSR_MSG_BACKUP_ERROR                 0X00000003    /*���ݹ��̳�����Ϣ*/
#define NSR_MSG_CHANNEL_INACTIVE             0X00000004    /*����ͨ��ʧЧ��Ϣ*/
#define NSR_MSG_BACKUP_END                   0X00000005    /*���������Ϣ*/
#define NSR_MSG_RESTORE_START                0X00000006    /*�������ݻָ���Ϣ*/ 
#define NSR_MSG_RESTORE_END                   0X00000007    /*��ɱ��ݻָ���Ϣ*/
#define NSR_MSG_SMOOTH_START                0X00000008    /*����ƽ��������Ϣ*/ 
#define NSR_MSG_SMOOTH_END                   0X00000009    /*���ƽ��������Ϣ*/

/*OSPF  NSR��Ϣ����*/
#define NSR_OSPF_MSG_BACKUP_START       0X00000001    /*OSPF��������������Ϣ*/
#define NSR_OSPF_MSG_BACKUP_CANCEL      0X00000002    /*OSPF����ȡ��������Ϣ*/
#define NSR_OSPF_MSG_BACKUP_ERROR       0X00000003    /*OSPF���̱��ݴ�����Ϣ*/
#define NSR_OSPF_MSG_BACKUP_END         0X00000004    /*OSPF������ɱ�����Ϣ*/
#define NSR_OSPF_MSG_RESTORE_START       0X00000005    /*OSPF�����������ݻָ���Ϣ*/
#define NSR_OSPF_MSG_RESTORE_BACKUP      0X00000006    /*OSPF���̱������ݻָ���Ϣ*/
#define NSR_OSPF_MSG_RESTORE_END         0X00000007    /*OSPF������ɱ��ݻָ���Ϣ*/
#define NSR_OSPF_MSG_SMOOTH_START       0X00000008    /*OSPF��������ƽ����Ϣ*/
#define NSR_OSPF_MSG_SMOOTH_END         0X00000009    /*OSPF�������ƽ����Ϣ*/

#define NSR_BACKUKP_FLAG_REBACKUP   0x01    /*NSR��Ҫ�����������ݱ��*/

#define NSR_INVALID_TIMERID 0    /*Ӧ�÷�Χ: NSRʹ��dopra�ṩ�Ķ�ʱ��*/

/*nsr ospfά����ospf����״̬*/
#define NSR_OSPF_PROCESS_ACTIVE          0X01
#define NSR_OSPF_PROCESS_INACTIVE        0X02

#define NSR_OSPF_SEND_MSG_TO_OSPF_FAIL  0X01 /*nsr_ospf��ospf������Ϣʧ��*/

#define NSR_OSPF_PROCESS_NULL        0X00   /*ospf���̳�ʼ״̬*/
#define NSR_OSPF_PROCESS_IN_BACKUP   0X01   /*ospf�������ڱ���*/
#define NSR_OSPF_PROCESS_IN_CANCEL   0X02   /*ospf��������ȡ������*/
#define NSR_OSPF_PROCESS_BACKUP_OK   0X03   /*ospf���̱������*/
#define NSR_OSPF_PROCESS_CANCEL_OK   0X04   /*ospf����ȡ���������*/

#define NSR_OSPF_PROCESS_IS_ACTIVE(index) \
  (g_stNSROSPFLocal.stNSROSPFInfo.stNSROSPFProcess[index].ucProcessStatus == NSR_OSPF_PROCESS_ACTIVE)

#define NSR_OSPF_PROCESS_START_BACKUP(index) \
(g_stNSROSPFLocal.stNSROSPFInfo.stNSROSPFProcess[index].ucBackupState != NSR_OSPF_PROCESS_NULL)

#define NSR_OSPF_PROCESS_IS_INBACKUP(index) \
  (g_stNSROSPFLocal.stNSROSPFInfo.stNSROSPFProcess[index].ucBackupState == NSR_OSPF_PROCESS_IN_BACKUP)

#define NSR_OSPF_PROCESS_IS_INCANCEL(index) \
  (g_stNSROSPFLocal.stNSROSPFInfo.stNSROSPFProcess[index].ucBackupState == NSR_OSPF_PROCESS_IN_CANCEL)

#define NSR_OSPF_PROCESS_IS_BACKUP_OK(index) \
  (g_stNSROSPFLocal.stNSROSPFInfo.stNSROSPFProcess[index].ucBackupState == NSR_OSPF_PROCESS_BACKUP_OK)

#define NSR_OSPF_PROCESS_IS_CANCEL_OK(index) \
  (g_stNSROSPFLocal.stNSROSPFInfo.stNSROSPFProcess[index].ucBackupState == NSR_OSPF_PROCESS_CANCEL_OK)


/* NSR��Ϣ�ײ����� */
typedef struct nsr_backup_header
{
    /* HA������Ϣ���, ����ж����Ϣ�ϳ�һ����Ϣ������ֻ������������Ϣ�Ŵ��ڱ�� */
    ULONG         ulSeq ;       

    /* HA�汾��, �ⲿģ���HA�汾�ź�VISPģ��İ汾�Ų���ͬ */
    ULONG         ulVer;

    /* ģ����, VISP HA����ͳһ����Ϣ��, ������ģ������������ѵ���ģ���� */
    UCHAR         ucModID;       
   
    /* ����������, ���庬���ɸ�ģ����� */
    UCHAR         ucOperation;   

    /* ������Ϣ����(����HA��Ϣ�ײ�) */
    USHORT        usMsgLen;      

    /* У���, ȱʡΪ0 */
    ULONG         ulChksum;
}NSR_BACKUP_HEADER;

typedef struct nsr_backup_cb
{
    UCHAR ucBackupState;
    UCHAR ucBackupFlag;     /*�Ƿ���Ҫ���±���*/
    CHAR  pad[2];
    ULONG ulBackupBeginTimerID;
    ULONG ulLastBackupTime;
    ULONG ulBackupDelayTimerID;   /*NSR������ʱ��ʱ��*/
    NSR_CONTROL_MSG *pstNSRControlMsg;
}NSR_BACKUP_CB;

typedef struct nsr_fsm_data
{
    UCHAR ucNSRState;     /*NSR״̬����״̬*/
    UCHAR pad[3];
    ULONG ulBackupTimerID;
    NSR_OSPF_ENTITY *nsr_ospf_entity;
}NSR_FSM_DATA;

/*NSR����ͳ�Ʋɼ��ṹ*/
typedef struct nsr_performance_data
{
    ULONG ulStartTime;
    ULONG ulEndTime;
}NSR_PERFORMANCE_DATA;

/*NSR����ͳ��*/
typedef struct nsr_performance_stat
{
    NSR_PERFORMANCE_DATA arrPerformanceData[NSR_PERFORMANCE_MAX];
}NSR_PERFORMANCE_STAT;

/*NSR������Ϣͳ��*/
typedef struct nsr_backup_msg_stat
{
    ULONG ulMasterBackupMsgStat[NSR_BACKUP_MAX];
    ULONG ulSlaveBackupMsgStat[NSR_BACKUP_MAX];
}NSR_BACKUP_MSG_STAT;

/*NSR������Ϣͳ��*/
typedef struct nsr_restore_msg_stat
{
    ULONG ulRestoreMsgStat[NSR_RESTORE_MAX];
}NSR_RESTORE_MSG_STAT;

/*NSR������Ϣͳ��*/
typedef struct nsr_smooth_msg_stat
{
    ULONG ulSmoothMsgStat[NSR_SMOOTH_MAX];
}NSR_SMOOTH_MSG_STAT;

/*NSR��������Ϣͳ��*/
typedef struct nsr_control_msg_stat
{
    ULONG ulBoardMsgStat;
    ULONG ulChannleMsgStat;
    ULONG ulSlaveBoardMsgStat;
    ULONG ulMasterBackupMsgStat[NSR_BACKUP_MAX];
    ULONG ulSlaveBackupMsgStat[NSR_BACKUP_MAX];
    ULONG ulRestoreMsgStat[NSR_RESTORE_MAX];
    ULONG ulSmoothMsgStat[NSR_SMOOTH_MAX];
}NSR_CONTROL_MSG_STAT;

/*NSR��Ϣͳ��*/
typedef struct nsr_msg_stat
{
    NSR_CONTROL_MSG_STAT stNSRControlMsgStat[NSR_MSG_DIRECT_MAX];
    ULONG ulBackupDataStat[NSR_MSG_DIRECT_MAX];
    ULONG ulTotalMsg[NSR_MSG_DIRECT_MAX][NSR_MSG_MAX];
}NSR_MSG_STAT;

/*NSRͳ����Ϣ*/
typedef struct nsr_statistics
{
    NSR_MSG_STAT stNSRMsgStat;
    NSR_PERFORMANCE_STAT stPerformanceStat;       /*NSR����ͳ������*/
}NSR_STATISTICS;

/*ospf���̵�id������״̬������״̬*/
typedef struct nsr_ospf_process
{
    USHORT usProcessId;          /*ʵ��id*/
    UCHAR  ucProcessStatus;         /*����״̬ add del up down interact_error*/
    UCHAR  ucBackupState;        /*����״̬ INBACKUP INCANCEL BACKUP_OK CANCEL_OK*/
    UCHAR  ucInteractOpt;        /*�� nsr_ospf��ospf������Ϣʧ�ܣ���¼�ڴ�*/
    UCHAR  pad[3];
}NSR_OSPF_PROCESS;

/*nsr ospf ά���� ospf������Ϣ*/
typedef struct nsr_ospf_info
{
    ULONG ulActiveProcessNum; /*�����ospf���̸���*/
    NSR_OSPF_PROCESS stNSROSPFProcess[OSPF_MAX_PROCESSES]; /*ospf������Ϣ*/
}NSR_OSPF_INFO;

/*NSR�ı�������*/
typedef struct nsr_ospf_local
{
    BOOL_T bNSROSPFInit;          /*NSR�Ƿ��ʼ�� 0-δ��ʼ��  1-�ѳ�ʼ��*/
    UCHAR ucNSROSPFCapability;   /*NSR OSPF�Ƿ�ʹ�� 1-ʹ��  2-δʹ��,Ĭ��ֵΪ2*/
    UCHAR ucNSRRole;              /*NSR��ɫ,Ĭ��Ϊ��*/
    UCHAR ucSlaveBoardStatus;   /*����״̬*/
    UCHAR ucChannelStatus;       /*����ͨ���Ƿ�OK��Ĭ��ΪFalse*/
    UCHAR ucNSRStatus;           /*ʹ��/ȥ���ܹ�����NSR״̬*/
    BOOL_T bBatchFirstPkt;       /*�Ƿ�Ϊ�������ݵ��װ�, 0--��, 1--��(ע��:�����������ͬʱ����)*/
    BOOL_T bCalcCheckSum;        /*NSR��������ͷ�Ƿ����CheckSum, Ĭ��FALSE*/
    ULONG ulLastReceiveSeqNum;  /*�����յ���ţ�Ĭ��ֵΪ0*/
    ULONG ulNextSendSeqNum;     /*��һ�η��ͱ��ĵ���ţ�Ĭ��ֵΪ1*/
    NSR_FSM_DATA stNSRFSMData;
    NSR_BACKUP_CB stNSRBackupCB;
    NSR_OSPF_INFO stNSROSPFInfo;      /*nsr ospf ά����ospf����״̬*/
    NSR_STATISTICS stNSRStatistics;   /*NSRͳ����Ϣ*/
}NSR_OSPF_LOCAL;

/*NSR���������Ч���ж�(����������Ϊ0���ж�)*/
#define NSR_CHECK_RCV_SEQ_NUM(SEQ_NUM)  \
  ((g_stNSROSPFLocal.ulLastReceiveSeqNum == 0) || \
   ((SEQ_NUM) == (g_stNSROSPFLocal.ulLastReceiveSeqNum + 1)))
/*���½������*/
#define NSR_UPDATE_RCV_SEQ_NUM(SEQ_NUM)  \
  (g_stNSROSPFLocal.ulLastReceiveSeqNum = (SEQ_NUM))
/*���·������*/
#define NSR_UPDATE_SEND_SEQ_NUM(SEQ_NUM)  \
  (g_stNSROSPFLocal.ulNextSendSeqNum = (SEQ_NUM))
/*��ȡ��ǰ�ķ������*/
#define NSR_CUR_SEND_SEQ_NUM() (g_stNSROSPFLocal.ulNextSendSeqNum)
/*��ȡ���µĽ������*/
#define NSR_LAST_RCV_SEQ_NUM() (g_stNSROSPFLocal.ulLastReceiveSeqNum)
/*����NSR�������*/
#define NSR_INC_SEND_SEQ_NUM()  \
  (g_stNSROSPFLocal.ulNextSendSeqNum++)

/*�ж�OSPF NSR�Ƿ�Ϊ����*/
#define NSR_OSPF_IS_MASTER_BOARD() (g_stNSROSPFLocal.ucNSRRole == NSR_ROLE_MASTER)

/*NSR OSPFģ���Ƿ��ѳ�ʼ��*/
#define NSR_OSPF_IS_INIT()    (g_stNSROSPFLocal.bNSROSPFInit == BOOL_TRUE)
#define NSR_OSPF_SET_INIT(RESULT)    (g_stNSROSPFLocal.bNSROSPFInit = ((RESULT) == NSR_OK ? BOOL_TRUE : BOOL_FALSE))

/*NSR�����Ƿ����CheckSum*/
#define NSR_IS_CALC_CHECKSUM() (g_stNSROSPFLocal.bCalcCheckSum == BOOL_TRUE)

/*�ж����屸���Ƿ�����*/
#define NSR_OSPF_IS_MASTER_BACKUP_STARTED()   \
  (NSR_OSPF_IS_MASTER_BOARD() && \
   (g_stNSROSPFLocal.stNSRBackupCB.ucBackupState != NSR_BKS_NULL))

/*�ж�����NSR�����Ƿ��Ѿ�����*/
#define NSR_OSPF_IS_MASTER_INBACKUP()   \
  (NSR_OSPF_IS_MASTER_BOARD() && \
   ((g_stNSROSPFLocal.stNSRBackupCB.ucBackupState == NSR_BKS_INBACKUP) || \
   (g_stNSROSPFLocal.stNSRBackupCB.ucBackupState == NSR_BKS_BACKUP_OK)))


/*�ж�����NSR�����Ƿ��Ѿ����*/
#define NSR_OSPF_IS_MASTER_BACKUP_OK()   \
      (NSR_OSPF_IS_MASTER_BOARD() && \
       (g_stNSROSPFLocal.stNSRBackupCB.ucBackupState == NSR_BKS_BACKUP_OK))


/*�ж�����NSRģ���Ƿ���ȡ������״̬*/
#define NSR_OSPF_IS_MASTER_PENDING_CANCEL()  \
  (NSR_OSPF_IS_MASTER_BOARD() && \
   (g_stNSROSPFLocal.stNSRBackupCB.ucBackupState == NSR_BKS_PENDING_CANCEL))

/*�жϱ��屸���Ƿ�����*/
#define NSR_OSPF_IS_SLAVE_BACKUP_START()   \
  ((!NSR_OSPF_IS_MASTER_BOARD()) && \
   (g_stNSROSPFLocal.stNSRFSMData.ucNSRState != NSR_STATE_NULL))

/*�жϱ���NSR�����Ƿ��Ѿ�����*/
#define NSR_OSPF_IS_SLAVE_INBACKUP()   \
  ((!NSR_OSPF_IS_MASTER_BOARD()) && \
   ((g_stNSROSPFLocal.stNSRFSMData.ucNSRState == NSR_STATE_INBACKUP) || \
    (g_stNSROSPFLocal.stNSRFSMData.ucNSRState == NSR_STATE_BACKUP_OK)))

/*�жϱ���NSR�����Ƿ��Ѿ��յ����巢���ı��ݿ�ʼ��Ϣ*/
#define NSR_OSPF_IS_SLAVE_BACKUP_INIT() \
    ((!NSR_OSPF_IS_MASTER_BOARD()) && \
     (g_stNSROSPFLocal.stNSRFSMData.ucNSRState == NSR_STATE_INIT))

/*�ж�����NSR�����Ƿ��ڵȴ����ݿ�ʼack״̬*/
#define NSR_IS_MASTER_WAIT_ACK()   \
  (NSR_OSPF_IS_MASTER_BOARD() && \
   (g_stNSROSPFLocal.stNSRBackupCB.ucBackupState == NSR_BKS_WAIT_ACK))

#define NSR_GET_BACKUP_TIMER_ID()    \
    (g_stNSROSPFLocal.stNSRFSMData.ulBackupTimerID)

#define NSR_GET_BACKUP_BEGIN_TIMER_ID()    \
    (g_stNSROSPFLocal.stNSRBackupCB.ulBackupBeginTimerID)    

/*NSR������ʱ��ʱ��ID*/
#define NSR_GET_BACKUP_DELAY_TIMER_ID()    \
    (g_stNSROSPFLocal.stNSRBackupCB.ulBackupDelayTimerID)

/*�趨NSR��������ʱ��*/
#define NSR_SET_BACKUP_START_TIME(SEC_TIME) \
  (g_stNSROSPFLocal.stNSRBackupCB.ulLastBackupTime = (SEC_TIME))

#define NSR_GET_BACKUP_DELAY_TIME(SEC_TIME) \
  (((SEC_TIME) >= g_stNSROSPFLocal.stNSRBackupCB.ulLastBackupTime) ? \
    (NSR_BATCHUP_DELAY_INTERVAL - (SEC_TIME) + g_stNSROSPFLocal.stNSRBackupCB.ulLastBackupTime) : 0)

#define NSR_IS_BACKUP_DELAY() \
  (NSR_GET_BACKUP_DELAY_TIMER_ID() != NSR_INVALID_TIMERID)

#define NSR_IS_NSR_FSM_START()  \
  (g_stNSROSPFLocal.stNSRFSMData.ucNSRState != NSR_STATE_NULL)
   
/*�жϱ���ͨ���Ƿ���Ч*/
#define NSR_OSPF_IS_CHANNEL_ACTIVE()   (g_stNSROSPFLocal.ucChannelStatus == NSR_CHANNEL_ACTIVE)

/*�жϱ����Ƿ񼤻�*/
#define NSR_OSPF_IS_SLAVE_BOARD_ACTIVE()   (g_stNSROSPFLocal.ucSlaveBoardStatus == NSR_SLAVE_BOARD_ACTIVE)

#define NSR_GET_CONTROL_MSG_BACKUP_INFO(pstControlMsg)    \
    ((NULL == pstControlMsg) ? NULL : (&(pstControlMsg->uControlMsg.stBackupInfo)))

#define NSR_GET_BACKUP_CB()    \
    (&(g_stNSROSPFLocal.stNSRBackupCB))

#define NSR_GET_NSR_FSM_DATA()    \
    (&(g_stNSROSPFLocal.stNSRFSMData))

ULONG NSR_ReplyOSPFControlMsg(UCHAR *pucBuf, ULONG ulMsgLen);
ULONG NSR_TranControlMsg(UCHAR *pMsgBuf, ULONG ulMsgLen);
BOOL_T NSR_IsOSPFInBackupOrBackupOk(USHORT usProcessID);
ULONG NSR_SetBackupHeader(UCHAR *pMsgBuf, ULONG ulMsgLen);
BOOL_T NSR_IsAllOSPFBackupOk(VOID);
BOOL_T NSR_IsSecondBatchupOK(VOID);

BOOL_T NSR_CheckReceiveBackupData(UCHAR *pRcvData, ULONG ulRcvDataLen);
NBB_VOID NSR_DeleteAllReplData(NBB_VOID);
NBB_VOID NSR_DealOSPFBackupMsg(NSR_OSPF_CONTROL_MSG *nsr_ospf_control_msg);
NBB_VOID NSR_DealOSPFRestoreMsg(NSR_OSPF_CONTROL_MSG *nsr_ospf_control_msg);
NBB_VOID NSR_DealOSPFSmoothMsg(NSR_OSPF_CONTROL_MSG *nsr_ospf_control_msg);
NBB_VOID NSR_BackupBeginTimerPop();
NBB_VOID NSR_BackupTimerPop();


/*����NSR���ݶ�ʱ�����(NSR_BATCHUP_INTERVALʱ���������������)*/
#define NSR_BATCHUP_INTERVAL  60000

/*����NSR���ݿ�ʼ��ʱ�����(NSR_BATCHUP_BEGIN_INTERVALΪ������ͱ��ݿ�ʼ��Ϣ������)*/
#define NSR_BATCHUP_BEGIN_INTERVAL  3000

/*����NSR������ʱʱ��(��λ:��)*/
#define NSR_BATCHUP_DELAY_INTERVAL  10


/*NSR��������Ϣ���͸�����*/
#define NSR_CONTROL_MSG_TO_MASTER(RECEIVER)  ((RECEIVER) | NSR_CONTROL_MSG_DEST_MASTER)
/*NSR��������Ϣ���͸�����*/
#define NSR_CONTROL_MSG_TO_SLAVE(RECEIVER)   ((RECEIVER) | NSR_CONTROL_MSG_DEST_SLAVE)

/*�ж���Ϣ�Ƿ��͸�����*/
#define NSR_OSPF_IS_MASTER_CONTROL_MSG(DIRECT_TYPE) \
  (((DIRECT_TYPE) & NSR_CONTROL_MSG_DEST_MASTER) && NSR_OSPF_IS_MASTER_BOARD())
  
/*�ж���Ϣ�Ƿ��͸�����*/
#define NSR_OSPF_IS_SLAVE_CONTROL_MSG(DIRECT_TYPE) \
    (((DIRECT_TYPE) & NSR_CONTROL_MSG_DEST_SLAVE) && !NSR_OSPF_IS_MASTER_BOARD())

/*�жϿ�������Ϣ�Ƿ���Ч*/
#define NSR_OSPF_IS_VALID_CONTROL_MSG(DIRECT_TYPE) \
  (((DIRECT_TYPE) & NSR_CONTROL_MSG_DIRECT_NSR) && \
  (NSR_OSPF_IS_MASTER_CONTROL_MSG(DIRECT_TYPE) || \
   NSR_OSPF_IS_SLAVE_CONTROL_MSG(DIRECT_TYPE)))

/*�趨���������װ���ʶ(ע��:��Ҫ����������)*/
#define NSR_OSPF_SET_BATCH_FIRST_PKT_FLAG(FLAG)  \
  g_stNSROSPFLocal.bBatchFirstPkt = (FLAG)

/*�ж��Ƿ�Ϊ�������ݵ��װ�*/
#define NSR_IS_BATCH_FIRST_PKT()  (g_stNSROSPFLocal.bBatchFirstPkt == BOOL_TRUE)

/*�˱��Ӧ����ָ��nsr�Ƿ���Ҫ���±���*/
/*�趨NSR�ر��ݱ�ʶ*/
#define NSR_SET_REBACKUP_FLAG() \
  g_stNSROSPFLocal.stNSRBackupCB.ucBackupFlag |= NSR_BACKUKP_FLAG_REBACKUP
/*ȡ��NSR�ر��ݱ�ʶ*/
#define NSR_UNSET_REBACKUP_FLAG() \
  g_stNSROSPFLocal.stNSRBackupCB.ucBackupFlag &= ~NSR_BACKUKP_FLAG_REBACKUP
/*�ж�NSR�Ƿ���Ҫִ���ر���*/
#define IS_NSR_NEED_REBACKUP() (g_stNSROSPFLocal.stNSRBackupCB.ucBackupFlag & NSR_BACKUKP_FLAG_REBACKUP)  

/*�ж��Ƿ���� ���� ��OSPF����*/
#define NSR_EXIST_ACTIVE_OSPF()  (g_stNSROSPFLocal.stNSROSPFInfo.ulActiveProcessNum > 0)

/*�ж�NSRģ���Ƿ���Դ���NSR��������Ϣ*/
/*���崦�ڵ���ƽ������׶Σ�������NSR��������Ϣ*/
#define NSR_CAN_NOT_PROCESS_CONTROL_MSG() \
  (NSR_OSPF_IS_MASTER_BOARD() && \
   ((g_stNSROSPFLocal.stNSRFSMData.ucNSRState > NSR_STATE_BACKUP_OK) && \
    (g_stNSROSPFLocal.stNSRFSMData.ucNSRState < NSR_STATE_SMOOTH_OK)))

#define NSR_GET_PERFORMANCE_DATA(TYPE)  \
  (g_stNSROSPFLocal.stNSRStatistics.stPerformanceStat.arrPerformanceData[TYPE])

#define NSR_CLEAR_PERFORMANCE(TYPE) \
  (NSR_GET_PERFORMANCE_DATA(TYPE).ulStartTime) = 0;  \
  (NSR_GET_PERFORMANCE_DATA(TYPE).ulEndTime) = 0;

#define NSR_SET_PERFORMANCE_S(TYPE) \
  NSR_CLEAR_PERFORMANCE(TYPE); \
  (NSR_GET_PERFORMANCE_DATA(TYPE).ulStartTime) = NBB_GET_MTIME();

#define NSR_SET_PERFORMANCE_E(TYPE) \
  (NSR_GET_PERFORMANCE_DATA(TYPE).ulEndTime) = NBB_GET_MTIME();
   
#define NSR_CALC_PERFORMANCE(TYPE)  \
  ((NSR_GET_PERFORMANCE_DATA(TYPE).ulEndTime) - \
   (NSR_GET_PERFORMANCE_DATA(TYPE).ulStartTime))

#define NSR_GET_CONTROL_MSG_STAT(MSG_DIRECT)  \
  (g_stNSROSPFLocal.stNSRStatistics.stNSRMsgStat.stNSRControlMsgStat[MSG_DIRECT])

#define NSR_GET_TOTAL_MSG_STAT(MSG_DIRECT, MSG_TYPE)  \
  (g_stNSROSPFLocal.stNSRStatistics.stNSRMsgStat.ulTotalMsg[MSG_DIRECT][MSG_TYPE])

NBB_VOID NSR_StatisticMsg(NBB_BYTE msg_direct, NBB_BYTE msg_type, 
                                   NBB_BYTE sub_msg_type, NBB_BYTE msg_opt);
#define NSR_MSG_STAT_FOR_SEND(MSG_TYPE, SUB_MSG_TYPE, MSG_OPT) \
  NSR_StatisticMsg(NSR_MSG_DIRECT_SEND, (MSG_TYPE), (SUB_MSG_TYPE), (MSG_OPT))

#define NSR_MSG_STAT_FOR_RECEIVE(MSG_TYPE, SUB_MSG_TYPE, MSG_OPT) \
  NSR_StatisticMsg(NSR_MSG_DIRECT_RECEIVE, (MSG_TYPE), (SUB_MSG_TYPE), (MSG_OPT))

#define NSR_ADDCARRY(x)  (x > 65535L ? x -= 65535L : x)

#define NSR_REDUCE \
{ \
    unLUtil.l = lSum;\
    lSum = unLUtil.s[0] + unLUtil.s[1]; \
    NSR_ADDCARRY(lSum); \
}

/*�趨ʹ��/ȥʹ�ܹ���OSPF NSR״̬*/
#define NSR_OSPF_SET_NSR_STATUS(NSR_STATUS) \
  (g_stNSROSPFLocal.ucNSRStatus = (NSR_STATUS))

/*�ж�OSPF NSR�Ƿ񼤻�*/
#define NSR_OSPF_IS_NSR_ACTIVE() \
  (NSR_STATUS_UP == g_stNSROSPFLocal.ucNSRStatus)
  
/*�ж�NSR�Ƿ���ȥʹ����*/
#define NSR_OSPF_IS_NSR_DEACTIVING() \
  ((NSR_CAPABILITY_DISENABLE == g_stNSROSPFLocal.ucNSROSPFCapability) &&  \
   (NSR_STATUS_GOING_DOWN == g_stNSROSPFLocal.ucNSRStatus))

/*�ж�OSPFNSR�Ƿ�ʹ��*/
#define NSR_OSPF_IS_NSR_ENABLE()  \
  (NSR_CAPABILITY_ENABLE ==g_stNSROSPFLocal.ucNSROSPFCapability)
/*NSR ��ospf����*/
#define NSR_NOTIFY_OSPF_START_BACKUP    0x01

/*ȫ�ֱ���������*/
extern NSR_OSPF_LOCAL g_stNSROSPFLocal;

NBB_VOID NSR_DealOSPFProcessMsg(NSR_OSPF_CONTROL_MSG *nsr_ospf_control_msg);

NBB_VOID NSR_DeleteBackupTimer();
NBB_VOID NSR_DeleteBackupBeginTimer();

/*NSR������ʱ����*/
NBB_VOID NSR_StartBackupDelayTimer();
NBB_VOID NSR_DeleteBackupDelayTimer();
VOID NSR_OSPF_NotifyBFDFinish();
NBB_VOID NSR_BackupDelayTimerPop();
ULONG NSR_OSPF_SetNSRCapability(UCHAR  ucNSRCapability);
VOID NSR_OSPF_NotifyNSRSwitchFinish();
NSR_OSPF_PROCESS *NSR_OSPF_FindProcess(NBB_SHORT process_id);


#endif
