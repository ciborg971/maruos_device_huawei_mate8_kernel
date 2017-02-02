

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "product_config.h"
#include "bsp_shared_ddr.h"
#include "drv_mailbox_cfg.h"
#include "drv_mailbox_debug.h"
#include "drv_mailbox_gut.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    可维可测信息中包含的C文件编号宏定义
*****************************************************************************/
#undef  _MAILBOX_FILE_
#define _MAILBOX_FILE_   "msg"
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
//extern int BSP_CPU_StateGet(int CpuID);


void mailbox_msg_receiver(void *mb_buf, void *handle, void *data)
{
    struct mb_queue * queue;  /*邮箱buffer临时句柄，用于传给用户回调*/
    struct mb_buff  * mbuf = ( struct mb_buff  *)mb_buf;
    mb_msg_cb  func = (mb_msg_cb)handle;

    queue = &mbuf->usr_queue;
    if (func) {
        func(data, (void *)queue, queue->size);
    } else {
        (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_READ_CALLBACK_NOT_FIND, mbuf->mailcode);
    }
}

MAILBOX_EXTERN unsigned int mailbox_reg_msg_cb(
                unsigned int             mailcode,
                mb_msg_cb                 func,
                void                     *data)
{
    return (unsigned int)mailbox_register_cb(mailcode, mailbox_msg_receiver, func, data);
}
MAILBOX_EXTERN unsigned int mailbox_try_send_msg(
                unsigned int            mailcode,
                void                    *pdata,
                unsigned int            length)
{
    struct mb_buff      *mb_buf = MAILBOX_NULL;
    struct mb_queue     *queue  = MAILBOX_NULL;
    int        ret_val    = MAILBOX_OK;

    if ((0 == pdata) || (0 == length)) {
        ret_val = mailbox_logerro_p1(MAILBOX_ERRO, mailcode);
        /*lint -save -e801*/
        goto exit_out;
        /*lint -restore*/

    }
    /*获取邮箱buffer*/
    ret_val = mailbox_request_buff(mailcode, (void *)&mb_buf);
    if (MAILBOX_OK != ret_val) {
        /*lint -save -e801*/
        goto exit_out;
        /*lint -restore*/
    }

    /*填充用户数据*/
    queue = &mb_buf->usr_queue; /* [false alarm]:fortify */
    if ( length != (unsigned int)mailbox_write_buff( queue, pdata, length)) {
         ret_val = mailbox_logerro_p1(MAILBOX_FULL, mailcode);
         /*lint -save -e801*/
         goto exit_out;
         /*lint -restore*/
    }

    /*封信*/
    ret_val = mailbox_sealup_buff( mb_buf,  length);
    if (MAILBOX_OK == ret_val) {
         /*发送邮件*/
        ret_val = mailbox_send_buff(mb_buf);
    }

exit_out:
    /*释放邮箱buffer*/
    if (MAILBOX_NULL != mb_buf) {
        (void)mailbox_release_buff(mb_buf);
    }

    return (unsigned int)ret_val;
}



MAILBOX_GLOBAL unsigned int mailbox_read_msg_data(
                void                   *mail_handle,
                char                   *buff,
                unsigned int          *size)
{
    struct mb_queue *pMailQueue = (struct mb_queue *)mail_handle;

    if ((MAILBOX_NULL == pMailQueue) || (MAILBOX_NULL == buff) || (MAILBOX_NULL == size)) {
        /*[false alarm]:误报*/
        return (unsigned int)mailbox_logerro_p1(MAILBOX_ERR_GUT_INPUT_PARAMETER, 0);
    }

    if (pMailQueue->size  >  *size) {
        /*[false alarm]:误报*/
        return (unsigned int)mailbox_logerro_p1(MAILBOX_ERR_GUT_USER_BUFFER_SIZE_TOO_SMALL, *size);
    }

    /*检查用户传回的邮箱数据队列句柄的有效性*/
    if ((0 == pMailQueue->length) ||
        ((unsigned int)(pMailQueue->front - pMailQueue->base) >  pMailQueue->length ) ||
        ((unsigned int)(pMailQueue->rear - pMailQueue->base) >  pMailQueue->length )) {
        return (unsigned int)mailbox_logerro_p1(MAILBOX_CRIT_GUT_INVALID_USER_MAIL_HANDLE, pMailQueue);
    }

    *size =  (unsigned int)mailbox_read_buff(pMailQueue, buff, pMailQueue->size);

    return MAILBOX_OK;
}
MAILBOX_EXTERN unsigned int mailbox_send_msg(
                unsigned int            mailcode,
                void                    *data,
                unsigned int            length)
{
    int  ret_val = MAILBOX_OK;
    unsigned int  try_go_on = MAILBOX_TRUE;
    int  try_times = 0;

#if 0
    ret_val= BSP_CPU_StateGet(mailbox_get_dst_id(mailcode));
    if(!ret_val)
    {
        return MAILBOX_TARGET_NOT_READY;
    }
#else
    if(mailbox_get_dst_id(mailcode) != MAILBOX_CPUID(HIFI))
    {
        return MAILBOX_TARGET_NOT_READY;
    }
#endif

    ret_val = (int)mailbox_try_send_msg(mailcode, data, length);

    if (MAILBOX_FALSE == mailbox_int_context()) {
        /*发送满等待轮询尝试*/
        while ((int)MAILBOX_FULL == ret_val) {
            /*lint -save -e522 -e534 */
            mailbox_delivery(mailbox_get_channel_id(mailcode));
            /*lint -restore*/
            try_go_on = (unsigned int)mailbox_scene_delay(MAILBOX_DELAY_SCENE_MSG_FULL, &try_times);

            if (MAILBOX_TRUE == try_go_on) {
                ret_val = (int)mailbox_try_send_msg(mailcode, data, length);
            } else {
                break;
            }
        }
    }
	/*lint -save -e737 -e650*/
    if ((MAILBOX_OK != ret_val)&&(MAILBOX_NOT_READY != ret_val)) {
	/*lint -restore*/
        /*mailbox_show(mailcode,0);*/
        /*mailbox_assert(ret_val);*/
        if ((int)MAILBOX_FULL != ret_val) {
            ret_val = (int)MAILBOX_ERRO;
        }
        return (unsigned int)ret_val;
    }
    return (unsigned int)ret_val;
}
unsigned int DRV_MAILBOX_SENDMAIL(
                unsigned int           MailCode,
                void                   *pData,
                unsigned int           Length)
{
    return mailbox_send_msg(MailCode, pData, Length);
}


unsigned int DRV_MAILBOX_REGISTERRECVFUNC(
                unsigned int           MailCode,
                mb_msg_cb               pFun,
                void                   *UserHandle)
{
    return mailbox_reg_msg_cb(MailCode, pFun, UserHandle);
}


unsigned int DRV_MAILBOX_READMAILDATA(
                void                   *MailHandle,
                unsigned char          *pData,
                unsigned int          *pSize)
{
    return mailbox_read_msg_data(MailHandle, (char *)pData, pSize);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

