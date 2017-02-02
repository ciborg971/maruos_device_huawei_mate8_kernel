#ifndef NSR_MAIN_INCLUDED
#define NSR_MAIN_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


/*NSR��Ϣ���г���*/
#define NSR_QUEUE_LEN_DEFAULT  (1024*8)

#define VRP_TASK_NSR_NAME "NSR"
#define VRP_TASK_NSR_MODE 0

/*��������Ƿ���Ч*/
#define NSR_IS_VALID_QUEUE(ulQueueID)   (ulQueueID != 0)

ULONG NSR_Init(VOID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
