#ifndef NSR_BASE_INCLUDED
#define NSR_BASE_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/* NSR �¼�λ���� */
#define NSR_EVENT_CONTROL           0X00000001      /* NSR�������¼� */
#define NSR_EVENT_BAKRCV            0X00000002      /* ������Ϣ�����¼� */
#define NSR_EVENT_BAKSND            0X00000004      /* ������Ϣ�����¼� */
#define NSR_EVENT_OSPF_CONTROL     0X00000008      /* OSPF NSR�������¼� */
#define NSR_EVENT_COMMON_CONTROL   0X00000010      /* NSR COMMON�������¼� */


/* ��Ϣ���� */
#define NSR_MSG_NULL                0
#define NSR_MSG_CONTROL             1  /* NSR��������Ϣ */
#define NSR_MSG_BAKRCV              2  /* ���ձ�����Ϣ */
#define NSR_MSG_BAKSND              3  /* ���� */
#define NSR_MSG_OSPF_NSR_CONTROL   4  /* OSPF NSR��������Ϣ(OSPFģ��ͬOSPF NSR����) */
#define NSR_MSG_NSR_OSPF_CONTROL   5  /* NSR OSPF��������Ϣ(OSPF NSR�ڲ���Ϣ��Ϣ����)*/
#define NSR_MSG_COMMON              6  /* NSR ģ�����Ϣ */
#define NSR_MSG_MAX                 7

/*����״̬*/
#define NSR_BACKUP_BATCH       1      /*��������*/
#define NSR_BACKUP_REALTIME    2      /*ʵʱ����*/

/*TCIP.SafeModify.Delete, Modify by guojianjun178934, 2014/5/21*/

#define NSR_ASSERT( exp )         VOS_DBGASSERT(exp)

/*NSR�ڴ����*/
#define NSR_MALLOC(ulMemInfo, ulMemSize)  TCPIP_Malloc(ulMemInfo, ulMemSize)  
#define NSR_FREE(pBuf)  TCPIP_Free(pBuf)

/* NSR����д����*/
extern ULONG g_ulNSRMsgQueID;
#define NSR_Enqueue(ulQueueId, ulMsg) \
                    VOS_Que_Write (ulQueueId, ulMsg, VOS_NO_WAIT | VOS_NORMAL, 0)

/* NSR���ж�����*/ 
#define NSR_Dequeue(ulQueueId, ulMsg) \
                     VOS_Que_Read (ulQueueId, ulMsg, VOS_NO_WAIT, 0)

/* NSR����д�¼� */
extern ULONG g_ulNSRTaskID;
#define NSR_SchedNSRTask(ulEvent) \
                    (VOID)VOS_Ev_Write( g_ulNSRTaskID, ulEvent )

extern ULONG g_ulNSRLock;
extern ULONG TCPIP_CreateMutex(CHAR *pMutexName, ULONG *pulMutexID);
extern ULONG TCPIP_DeleteMutex(ULONG ulMutexID);

/*NSR�������Ĳ���*/
#define NSR_INIT_LOCK()       (0 == TCPIP_CreateMutex("NSR_Mutex", &g_ulNSRLock))
#define NSR_GET_LOCK()        (VOID)TCPIP_BEGIN_PT(g_ulNSRLock)
#define NSR_RELEASE_LOCK()    (VOID)TCPIP_END_PT(g_ulNSRLock)
#define NSR_DESTROY_LOCK()    (0 == TCPIP_DeleteMutex(g_ulNSRLock))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

