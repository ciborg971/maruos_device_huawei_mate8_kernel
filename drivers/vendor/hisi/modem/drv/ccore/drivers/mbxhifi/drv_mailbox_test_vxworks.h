
#ifndef __DRV_MAILBOX_MNTN_H__
#define __DRV_MAILBOX_MNTN_H__

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#include "osl_sem.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TM_MAILBOX_INIT_FLAG          (0x5aa55aa5)

#define TM_MAILBOX_BYTE_PER_KB        (1024)

 /*�������ĳ˷�����*/
#define MAILBOX_BOARDST_BOUNDWIDTH_MUL_LIMIT   30

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
 ʵ �� ��  : struct tm_mb_handle
 ��������  : ������ģ����ƾ��
*****************************************************************************/
struct tm_mb_handle
{
    osl_sem_id          mutex;
    unsigned long   init_flag;
};

/*****************************************************************************
 ʵ �� ��  : struct tm_mb_cb
 ��������  : �����Ե��û��ص����
*****************************************************************************/
struct tm_mb_cb
{
    osl_sem_id       finish_sema;
    osl_sem_id       sync_sema;
    unsigned long    start_slice;       /*for calculate boundwidth*/
    unsigned long    end_slice;         /*for calculate boundwidth*/
    unsigned long    prob_slice;        /*for calculate latency*/
    unsigned long    back_slice;        /*for calculate latency*/
    unsigned long    msg_count;
    unsigned long    task_count;
    unsigned long    check_ret;
};
struct tm_mb_input_para
{
    unsigned int send_code;
    unsigned int recev_code;
    unsigned int send_size;
    unsigned int msg_num;
    unsigned int delay_tick;
    unsigned int delay_num;
    unsigned int try_times;
    struct tm_mb_cb * mb_cb;
};


/*****************************************************************************
  7 UNION����
*****************************************************************************/

/*****************************************************************************
  8 OTHERS����
*****************************************************************************/
extern unsigned long tm_mailbox_msg_multi_send(
                unsigned long dst_id, 
                unsigned long carrier_id,
                unsigned long task_num, 
                unsigned long msg_len,
                unsigned long msg_num, 
                unsigned long priority,
                unsigned long delay_tick,
                unsigned long delay_num,
                unsigned long try_times
);

extern unsigned long tm_mailbox_msg_multi_test(
                unsigned long dst_id, 
                unsigned long task_num, 
                unsigned long msg_num, 
                unsigned long delay_num);

extern unsigned long tm_mailbox_msg_single_test(
                unsigned long dst_id, 
                unsigned long msg_len, 
                unsigned long msg_num, 
                unsigned long try_times);

extern void tm_mailbox_msg_reg(unsigned long channel_id);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of tm_drv_mailbox.h */
