

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
/*lint --e{123}*/
#include "product_config.h"
#include "drv_mailbox_cfg.h"
#include "drv_mailbox_debug.h"
#include "drv_mailbox_gut.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    ��ά�ɲ���Ϣ�а�����C�ļ���ź궨��
*****************************************************************************/
#undef  _MAILBOX_FILE_
#define _MAILBOX_FILE_   "dbg"
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
 extern   MAILBOX_EXTERN struct mb g_mailbox_handle;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if (MAILBOX_LOG_LEVEL != MAILBOX_LOG_NONE)

MAILBOX_EXTERN int mailbox_log_erro(
                unsigned int   err_no,
                unsigned long   param1,
                unsigned long   param2,
                unsigned int   line_no,
                char*           file_name)
{
    struct mb *mb      = &g_mailbox_handle;
    struct mb_log  *record = &mb->log_array[0];
    unsigned int log_out = MAILBOX_FALSE; 
    
    /*1.��¼�������켣*/
    record[mb->log_prob].erro_num = err_no;
    record[mb->log_prob].line    = line_no;
    record[mb->log_prob].param1  = param1;
    record[mb->log_prob].param2  = param2;
    record[mb->log_prob].file = (const char* )file_name;
    mb->log_prob = ((MAILBOX_ERRO_ARRAY_NUM - 1) == mb->log_prob) ? (0) :
                                                            (mb->log_prob + 1);

    /*2.���ݸ澯�ȼ���ӡ��*/
#if (MAILBOX_LOG_LEVEL >= MAILBOX_LOG_CRITICAL)
    if ((err_no > MAILBOX_CRIT_RET_START) && (err_no < MAILBOX_CRIT_RET_END)) {
        log_out = MAILBOX_TRUE;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX, "file_name %s line_no(0x%x)!"RT, file_name, line_no);
        mailbox_assert(err_no);
    }
#endif

#if (MAILBOX_LOG_LEVEL >= MAILBOX_LOG_CRITICAL)
    if((err_no > MAILBOX_ERR_RET_START) && (err_no < MAILBOX_ERR_RET_END)) {
        log_out = MAILBOX_TRUE;
    }
#endif

#if (MAILBOX_LOG_LEVEL >= MAILBOX_LOG_WARNING)
    if((err_no > MAILBOX_WARNING_RET_START) && (err_no < MAILBOX_WARNING_RET_END)) {
        log_out = MAILBOX_TRUE;
    }
#endif

#if (MAILBOX_LOG_LEVEL >= MAILBOX_LOG_INFO)
    if((err_no > MAILBOX_INFO_RET_START) && (err_no < MAILBOX_INFO_RET_END)) {
        log_out = MAILBOX_TRUE;
    }
#endif

    if (MAILBOX_FULL == err_no) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX, "mb(%lu) full !"RT, param1);
        log_out = MAILBOX_TRUE;
    } else if (MAILBOX_NOT_READY == err_no) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX, "remote mb(%lu) not ready!"RT, param1);
        log_out = MAILBOX_TRUE;
    }

    if (MAILBOX_TRUE == log_out) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX, "0x%08x, param1:%lu, param2:%lu, (line:%d),(file:%s)"RT,
            err_no,  param1,  param2, (int)line_no, (int)file_name);
    }

    return (int)err_no;
}
#endif

#ifdef MAILBOX_OPEN_MNTN
/*����ʱ�����󵥴�ʱ�����ͳ��*/
void mailbox_statistic_slice(
                struct mb_slice* slice,                
                unsigned int mailcode, 
                unsigned int threslhold,
                unsigned int erro_code
                )
{
    unsigned int slice_diff;
    unsigned int slice_end = (unsigned int)mailbox_get_timestamp();
    unsigned int slice_start = slice->start;

    slice_diff = mailbox_get_slice_diff(slice_start, slice_end);
    
        
    

    /*��¼�ص���ʷ�ܺ�ʱ*/
    slice_end = slice->total;
    slice->total += slice_diff; /*lint !e737*/
    if (slice_end > slice->total) {
        slice->overflow = MAILBOX_TRUE; /*��¼��ʱ�����������Ч*/
    }

    /*��¼���ص���ʱ*/
    if (slice_diff > slice->max) {
        slice->max = slice_diff;
        slice->code = mailcode;
    }

    if (slice_diff >= threslhold) {
        #ifndef _DRV_LLT_
        (void)mailbox_logerro_p2(erro_code, slice_diff, mailcode);
        #endif
    }
}

/*��¼�ж���Ӧ�����ȴ���֮ǰ��ʱ���*/
void mailbox_record_sche_send(void *priv)
{
    struct mb_buff *mbuf = (struct mb_buff *)priv;
    mbuf->mntn.sche.start = (unsigned long)mailbox_get_timestamp();
}

/*��¼�ж���Ӧ�󣬵��ȴ����ʱ��㣬������ͳ��*/
void mailbox_record_sche_recv(void *priv)
{
    struct mb_buff *mbuf = (struct mb_buff *)priv;

    mailbox_statistic_slice(&mbuf->mntn.sche, mbuf->channel_id,
                    MAILBOX_MAIL_SCHE_TIME_LIMIT,
                    MAILBOX_WARNING_SCHE_TIME_OUT);
}

/*��ά�ɲ�: ��¼ʣ��ռ���Сֵ*/
void mailbox_record_send(
                struct mb_mntn* mntn,                
                unsigned int mailcode, 
                unsigned int time_stamp,
                unsigned long mail_addr)
{
    struct mb_queue *m_queue = &mntn->mbuff->mail_queue;
    unsigned int size_left = (unsigned int)mailbox_queue_left(m_queue->rear, m_queue->front, m_queue->length);

    /*��ά�ɲ�: ��¼ʣ��ռ���Сֵ*/
    if (size_left < mntn->peak_traffic_left){
        mntn->peak_traffic_left = size_left;
    }
    /*���¿�ά�ɲ���Ϣ. дͨ��ֻ�з���ʱ���Use ID*/
    mntn->track_array[mntn->track_prob].send_slice = time_stamp;
    mntn->track_array[mntn->track_prob].mail_addr  = mail_addr;
    mntn->track_array[mntn->track_prob].use_id     = mailbox_get_use_id(mailcode);
    mntn->track_prob = ((MAILBOX_RECORD_USEID_NUM - 1) == mntn->track_prob) ?
                                                   (0) : (mntn->track_prob + 1);
}

/*��¼���ͺ�IPC�жϴ��������ܺ��ж���Ӧ֮���ʱ��*/
void mailbox_record_transport(
                struct mb_mntn* mntn, 
                unsigned int mailcode, 
                unsigned int write_slice,
                unsigned int read_slice,
                unsigned long mail_addr)
{
    struct mb_queue *m_queue = &mntn->mbuff->mail_queue;
    unsigned int  size_left = (unsigned int)mailbox_queue_left(m_queue->rear, m_queue->front, m_queue->length);

    /*��ά�ɲ�: ��¼ʣ��ռ���Сֵ*/
    if (size_left < mntn->peak_traffic_left){
        mntn->peak_traffic_left = size_left;
    }

    if (size_left < (m_queue->length >> 3) ){
        (void)mailbox_logerro_p2(MAILBOX_ERR_GUT_MAILBOX_RECEIVE_FULL, size_left, mailcode);
    }

    /*��¼�յ����ʼ�use id*/
    mntn->track_array[mntn->track_prob].use_id        =
                                   (unsigned short)mailbox_get_use_id(mailcode);
    mntn->track_array[mntn->track_prob].send_slice    =  write_slice;
    mntn->track_array[mntn->track_prob].recv_slice =  read_slice;
    mntn->track_array[mntn->track_prob].mail_addr = mail_addr;
    mntn->track_prob = ((MAILBOX_RECORD_USEID_NUM - 1)==mntn->track_prob) ?
                                                   (0) : (mntn->track_prob + 1);

    mntn->trans.start = write_slice;
    mailbox_statistic_slice(&mntn->trans, mailcode,
                MAILBOX_MAIL_TRANS_TIME_LIMIT,
                MAILBOX_WARNING_TRANSPORT_TIME_OUT);

}

/*��¼��Ӧ�������û��ص�����ִ��ʱ��*/
void mailbox_record_receive(
                struct mb_mntn* mntn,                
                unsigned int mailcode, 
                unsigned int slice_start)
{          
    mntn->deal.start = slice_start;
    mailbox_statistic_slice(&mntn->deal, mailcode,
                    MAILBOX_MAIL_DEAL_TIME_LIMIT,
                    MAILBOX_WARNING_RECEIVE_TIME_OUT);
}

/*���ĳ������ͨ���Ŀ�ά�ɲ���Ϣ*/
void mailbox_clear_mntn( struct mb_mntn *mntn, int clear)
{
    struct mb_buff   *mbuff;
    if (clear) {
        mbuff = mntn->mbuff;
        (void)mailbox_memset(mntn, 0x00, sizeof(struct mb_mntn));
        mntn->mbuff = mbuff;
        mntn->peak_traffic_left = MAILBOX_QUEUE_LEFT_INVALID;
    }
}

/*lint -save -e592*/
/*****************************************************************************/
/*�����ǿ�ά�ɲ⺯��*/

MAILBOX_LOCAL void mailbox_show_general(struct mb_cfg *cfg)
{
    struct mb_head   *pBoxHead   =  (struct mb_head*)(cfg->head_addr);

    /*������Ϣ*/
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("Max Id,      HeadAddr,    DataAddr,     DataSize,   IntSrcId"RT));
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"0x%08x,  0x%08x,  0x%08x,   0x%08x, %04d"RT,(unsigned int)cfg->butt_id,
                    (unsigned int)cfg->head_addr, (unsigned int)cfg->data_addr,
                    (unsigned int)cfg->data_size, (unsigned int)cfg->int_src);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("Head information:"RT));

    /*��ӡ�����������ͷ���ݡ�*/
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Head Front: 0x%x (0x%08x)"RT,  (unsigned int)pBoxHead->ulFront,
                (unsigned int)(cfg->data_addr + (pBoxHead->ulFront * sizeof(unsigned long))));
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Head Rear: 0x%x (0x%08x)"RT, (unsigned int)pBoxHead->ulRear,
                (unsigned int)(cfg->data_addr + (pBoxHead->ulRear * sizeof(unsigned long))));
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Head Frontslice: 0x%x"RT, (unsigned int)pBoxHead->ulFrontslice);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Head Rearslice: 0x%x"RT,  (unsigned int)pBoxHead->ulRearslice);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,(":-------------------------------------------------------------:"RT));

}


MAILBOX_LOCAL void mailbox_show_receive(struct mb_buff *mbuf)
{
    struct mb_mntn      *mntn         =  &(mbuf->mntn);    /*������ͨ���Ŀ�ά�ɲ�����*/
    struct mb_cb        *callback     =  mbuf->read_cb;    /*������ͨ���Ĺ��ܻص���������*/
    unsigned int        max_use      =  mailbox_get_use_id(mbuf->config->butt_id);
    unsigned int        i            =  0;

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,(":---------------------------------------------:"RT));
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("Receive info:"RT));

    /*��ӡ�ҽ��ڴ�����ͨ���ϵ�Ӧ�úż�Ӧ�ûص�������ַ*/
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("Mail Read Call Back show:"RT));
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("Use Id,  Call Back,     User Handle"RT));
    while (i < max_use) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"%d,       0x%08x,    0x%08x"RT, (unsigned int)i, (unsigned int)callback->func, 
                                                (unsigned int)callback->handle);
        callback++;
        i++;
    }

    /*ƽ�����ȵȴ��������ȵȴ�ʱ��*/
    if (MAILBOX_TRUE != mntn->sche.overflow) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Schedule Avg. slice:%4d, total:%d"RT, 
            (int)((mntn->sche.total)/(mbuf->seq_num + 1)) , (unsigned int)mbuf->seq_num);
    } else {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("Schedule Avg. data overflow "RT));
    }
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Schedule Max. slice:%4d,  Use ID:0x%08x"RT, (unsigned int)(mntn->sche.max),
                                            (unsigned int)(mntn->sche.code));

    /*ƽ�����ͼ������ʱ��*/
    if (MAILBOX_TRUE != mntn->trans.overflow) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Transfers Avg. slice:%4d, total:%d"RT,
            (int)((mntn->trans.total)/(mbuf->seq_num + 1)),  (unsigned int)mbuf->seq_num);
    } else {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("Transfers Max. data overflow"RT));
    }
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Transfers Max. slice:%4d,  Use ID:0x%08x"RT, (unsigned int)(mntn->trans.max),
                (int)(mntn->trans.code));/*lint !e539*/

    /*ƽ�����������ʱ��*/
    if (MAILBOX_TRUE != mntn->deal.overflow) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Call Back Avg. slice:%4d, total:%d"RT,
            (int)((mntn->deal.total)/(mbuf->seq_num + 1)), (unsigned int)mbuf->seq_num );
    } else {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("Call Back Avg. data overflow"RT));
    }
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Call Back Max. slice:%4d,  Use ID:0x%08x"RT, 
            (int)(mntn->deal.max), (unsigned int)mntn->deal.code);


    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,(":---------------------------------------------:"RT));
}
MAILBOX_LOCAL void mailbox_show_detail(struct mb *mb,
                struct mb_buff *mbuf,
                int clear)
{
    struct mb_mntn        *mntn         =  MAILBOX_NULL;  /*������ͨ���Ŀ�ά�ɲ�����*/
    unsigned int          channel  =  mbuf->channel_id;
    struct mb_queue       *queue   =  &mbuf->mail_queue;
    struct mb_mail        *mail;
    unsigned int i;
    
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"mail box show channel(0x%08x) information:"RT, (unsigned int)channel);

    /*������Ϣ*/
    mailbox_show_general(mbuf->config);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,(":---------------------------------------------:"RT));
    mntn = &(mbuf->mntn);
    /*��ʾ�������������ļ���use ID��Ϣ, �������ʾ��ǰ��*/
    i = mntn->track_prob ;
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Latest transmit mails track:(%d total)"RT, (unsigned int)mbuf->seq_num);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("id   ,address     ,send slice   ,recv slice  ,diff slice"RT));
    do {
        i = ((0 == i) ? (MAILBOX_RECORD_USEID_NUM - 1) : (i - 1));
        mail = (struct mb_mail *)mntn->track_array[i].mail_addr;

        if (mail && (0 == mntn->track_array[i].recv_slice)) {
            mntn->track_array[i].recv_slice = mail->ulReadSlice;
        }
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"%02d   ,0x%-8x  ,0x%-8x   ,0x%-8x  ,0x%-8x(%d)"RT,
            mntn->track_array[i].use_id,
        (unsigned int)mail, (unsigned int)mntn->track_array[i].send_slice,
                                  (unsigned int)mntn->track_array[i].recv_slice,
        (unsigned int)mailbox_get_slice_diff(mntn->track_array[i].send_slice,
                                               mntn->track_array[i].recv_slice),
        (unsigned int)mailbox_get_slice_diff(mntn->track_array[i].send_slice,
                                            mntn->track_array[i].recv_slice));
    } while (i != (mntn->track_prob));

    if (mb->local_id == mailbox_get_dst_id(channel)) {
        /*����ǽ���ͨ��*/
        /*��ӡͨ������*/
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("Receive Channel"RT));
    }

    /*��ӡͨ������*/
    if (mb->local_id == mailbox_get_src_id(channel)) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Send Channel: sem id(0x%08x)"RT,(unsigned int)mbuf->mutex);
    } else if (mb->local_id == mailbox_get_dst_id(channel)) {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Receive Channel: sem id(0x%08x)"RT,(unsigned int)mbuf->mutex);
        mailbox_show_receive(mbuf);
    }

    if (MAILBOX_QUEUE_LEFT_INVALID == mntn->peak_traffic_left) {
        mntn->peak_traffic_left = queue->length;
    }
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"Peak Traffic: %d%%, Peak: 0x%x, Total: 0x%x"RT,
        (int)(100*(queue->length - mntn->peak_traffic_left)/queue->length),
        (unsigned int)(queue->length - mntn->peak_traffic_left), (unsigned int)queue->length);

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,(":------------------------------------------------:"RT));

    mailbox_clear_mntn(mntn, clear);
}



MAILBOX_EXTERN int mailbox_show(
                unsigned int    channel,
                unsigned int    show_flag)
{
    struct mb_cfg         *config     = &g_mailbox_global_cfg_tbl[0];
    struct mb_buff        *mbuf       = MAILBOX_NULL;
    struct mb_link        *send_tbl   = MAILBOX_NULL;    /*ָ�����ṹ��ķ���ͨ���������ַ*/
    struct mb_link        *recv_tbl   = MAILBOX_NULL;    /*ָ�����ṹ��Ľ���ͨ���������ַ*/
    struct mb             *mb   = MAILBOX_NULL;
    struct mb_log         *record = MAILBOX_NULL;
    unsigned int          i;
    unsigned int          j;
    unsigned int          clear = MAILBOX_FALSE;
    
    mb =  mailbox_get_mb();
    if (MAILBOX_NULL == mb) {
        return (int)MAILBOX_ERRO;
    }

    if ( MAILBOX_SHOW_CLEAR & show_flag ) {
        clear = MAILBOX_TRUE;
    }

    if (MAILBOX_SHOW_ALL & show_flag) {
        /*Show all channel's general information.*/
        /*������ʾ���еķ���ͨ����Ϣ*/
        send_tbl = mb->send_tbl;
        for (i = 0; i < MAILBOX_CPUID_BUTT; i++) {
            if (MAILBOX_NULL != send_tbl[i].channel_buff) {
                mbuf  =   send_tbl[i].channel_buff;
                for (j = 0; j < send_tbl[i].carrier_butt; j++) {
                    mailbox_show_detail(mb, mbuf, (int)clear);
                    mbuf++;
                }
            }
        }

        recv_tbl = mb->recv_tbl;
        /*������ʾ���еĽ���ͨ����Ϣ*/
        for (i = 0; i < MAILBOX_CPUID_BUTT; i++) {
            if (MAILBOX_NULL != recv_tbl[i].channel_buff) {
                mbuf  =   recv_tbl[i].channel_buff;
                for (j = 0; j < recv_tbl[i].carrier_butt; j++) {
                    mailbox_show_detail(mb, mbuf, (int)clear);
                    mbuf++;
                }
            }
        }
    } else {
        /*ͨ����ָ������ʾ�������ͨ������ϸ��Ϣ*/
        mbuf = mailbox_get_channel_handle(mb, channel);

        if (MAILBOX_NULL != mbuf) {
            mailbox_show_detail(mb, mbuf, (int)clear);
        } else {
            /*���ͨ����û��ָ�����г�����ģ���ͨ��������״̬:*/
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("mail box show global channel config:"RT));
            while (MAILBOX_MAILCODE_INVALID != config->butt_id) {
                mailbox_show_general(config);
                config++;
            }

            /*��ʾ�������������������Ϣ, �������ʾ��ǰ��*/
            i = mb->log_prob;
            record = &mb->log_array[0];
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("Latest error log track:"RT));
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("error num,   line num,   file name"RT));
            do {

               i = ((0 == i) ? (MAILBOX_ERRO_ARRAY_NUM - 1) : (i - 1));
               bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"0x%-8x,  %-8d,  %-8s"RT,(unsigned int)record[i].erro_num,
                (unsigned int)record[i].line,  record[i].file);

            } while (i != (mb->log_prob));
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,("track end."RT));
        }
    }

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,(":================================================:"RT));
    return MAILBOX_OK;
}
/*lint -restore*/
#else

MAILBOX_EXTERN int mailbox_show(
                unsigned int    channel,
                unsigned int    show_flag)
{
    return MAILBOX_OK;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

