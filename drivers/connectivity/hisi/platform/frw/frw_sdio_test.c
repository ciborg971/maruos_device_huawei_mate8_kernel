#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



#include "oal_sdio_host_if.h"
#include "oal_util.h"
#include "oal_hcc_host_if.h"
#include "frw_sdio_test.h"
#include "oal_thread.h"

#ifdef CONFIG_MMC
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <linux/wait.h>
#include <linux/workqueue.h>
#include <linux/kthread.h>
#include <linux/mutex.h>
#include <linux/completion.h>
#include <linux/ktime.h>
#include <linux/delay.h>
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_SDIO_TEST_C

oal_uint32            ul_data_cmp_flag;

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
frw_sdio_test_event  *gst_frw_sdio_test_event = NULL;
frw_sdio_test_param  *gst_test_param = NULL;

oal_void frw_sdio_test_result_report(oal_void)
{
     OAL_IO_PRINT("[WIFI]SDIO Test                %d pkts sent\n", gst_frw_sdio_test_event->test_data.pkt_sent);
     OAL_IO_PRINT("[WIFI]SDIO Test                %d pkts rcvd\n", gst_frw_sdio_test_event->test_data.pkt_rcvd);
     OAL_IO_PRINT("[WIFI]SDIO Test                %d pkts generate\n", gst_frw_sdio_test_event->test_data.pkt_gen);
     OAL_IO_PRINT("[WIFI]SDIO Test pkt lengh      %d\n", gst_frw_sdio_test_event->test_data.pkt_len);
     if(ul_data_cmp_flag == 0)
     {
         OAL_IO_PRINT("[WIFI]SDIO Test Throughput     %llu Mbps\n", gst_frw_sdio_test_event->test_data.throughput);
     }
     if(ul_data_cmp_flag == 1)
     {
         OAL_IO_PRINT("[WIFI]SDIO Test error num      %u \n", gst_frw_sdio_test_event->test_data.err_num);
         OAL_IO_PRINT("[WIFI]SDIO Test error byte num %u \n", gst_frw_sdio_test_event->test_data.err_byte_num);
     }
     OAL_IO_PRINT("[WIFI]Hi1102 SDIO Test Used    %llu seconds\n", gst_frw_sdio_test_event->test_data.trans_time);
}
oal_void test_case_01(oal_uint32  pkt_gen, oal_uint32 pkt_len, oal_uint8 test_type)
{
    OAL_IO_PRINT("[SDIO_TEST]TEST START!\n");
    ul_data_cmp_flag = 0;

    gst_frw_sdio_test_event = oal_memalloc(OAL_SIZEOF(frw_sdio_test_event));
    if(gst_frw_sdio_test_event == OAL_PTR_NULL)
    {
        OAL_IO_PRINT("globle event mem alloc failed\n");
        return ;
    }
    mutex_init(&gst_frw_sdio_test_event->mutex_lock);
    gst_frw_sdio_test_event->test_data.pkt_len  = 0;
    gst_frw_sdio_test_event->test_data.pkt_sent = 0;
    gst_frw_sdio_test_event->test_data.pkt_gen  = 0;
    gst_frw_sdio_test_event->started  = OAL_FALSE;
    frw_sdio_test_set_case(pkt_gen, pkt_len, test_type);
    frw_sdio_test_result_report();
}

oal_uint32 frw_sdio_test_post_event(oal_netbuf_stru *pst_netbuf, oal_uint timeout)
{
    oal_int32 ret = OAL_SUCC;
    oal_uint  timeout_jiffies;
    frw_event_mem_stru *pst_test_event_mem;
    frw_event_stru     *pst_test_event;
    hcc_event_stru     *pst_hcc_event_payload;

    pst_test_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hcc_event_stru));
    if (OAL_PTR_NULL == pst_test_event_mem)
    {
        OAL_IO_PRINT("[Error]sdio test alloc event failed!!!\n");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    timeout_jiffies = jiffies + msecs_to_jiffies(timeout);

    pst_test_event = (frw_event_stru *)pst_test_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_test_event->st_event_hdr),
                   FRW_EVENT_TYPE_HMAC_HCC_TEST,
                   gst_frw_sdio_test_event->test_data.test_type,
                   OAL_SIZEOF(hcc_event_stru),
                   FRW_EVENT_PIPELINE_STAGE_1,
                   0,
                   0,
                   0);


    pst_hcc_event_payload = (hcc_event_stru *)pst_test_event->auc_event_data;
    //pst_hcc_event_payload->en_nest_type      = FRW_EVENT_TYPE_HMAC_HCC_TEST;
    //pst_hcc_event_payload->uc_nest_sub_type  = gst_frw_sdio_test_event->test_data.test_type;
    pst_hcc_event_payload->pst_netbuf        = pst_netbuf;
    //pst_hcc_event_payload->ul_buf_len        = gst_frw_sdio_test_event->test_data.pkt_len;

    if(OAL_NETBUF_LEN(pst_netbuf) > 1548)
    {
        OAL_IO_PRINT("[WARNING]netbuf too long:%d\n",
                        OAL_NETBUF_LEN(pst_netbuf));
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }


    ret = frw_event_dispatch_event(pst_test_event_mem);

    if(OAL_SUCC != ret)
    {
        OAL_IO_PRINT("[Error]sdio test post event failed!!!\n");
        //oal_netbuf_free(pst_netbuf);
    }
    FRW_EVENT_FREE(pst_test_event_mem);
    
    return ret;
}
oal_uint32 frw_sdio_test_tx(oal_uint8 gen_type)
{
    oal_netbuf_stru      *pst_netbuf;
    oal_uint32            ulret;
    frw_sdio_test_param  *pst_test_param;
    pst_netbuf = hcc_netbuf_alloc(gst_frw_sdio_test_event->test_data.pkt_len);
    if(OAL_PTR_NULL == pst_netbuf)
    {
        OAL_IO_PRINT("alloc netbuf failed\n");
        return OAL_FAIL;
    }
    if(FRW_SDIO_TEST_GEN_START == gen_type)
    {
        oal_netbuf_put(pst_netbuf, gst_frw_sdio_test_event->test_data.pkt_len);
        //OAL_MEMZERO(oal_netbuf_cb(pst_netbuf), OAL_TX_CB_LEN);
        oal_memset(OAL_NETBUF_DATA(pst_netbuf), FRW_SDIO_TEST_DATA_GEN, gst_frw_sdio_test_event->test_data.pkt_len);
    }
    else if(FRW_SDIO_TEST_GEN_STOP == gen_type)
    {
        oal_netbuf_put(pst_netbuf, gst_frw_sdio_test_event->test_data.pkt_len);
        //OAL_MEMZERO(oal_netbuf_cb(pst_netbuf), OAL_TX_CB_LEN);
        oal_memset(OAL_NETBUF_DATA(pst_netbuf), FRW_SDIO_TEST_DATA_STOP, gst_frw_sdio_test_event->test_data.pkt_len);
    }
    else if(FRW_SDIO_TEST_GEN_RX == gen_type)
    {
        oal_netbuf_put(pst_netbuf, gst_frw_sdio_test_event->test_data.pkt_len);
        //OAL_MEMZERO(oal_netbuf_cb(pst_netbuf), OAL_TX_CB_LEN);
        oal_memset(OAL_NETBUF_DATA(pst_netbuf), FRW_SDIO_TEST_DATA_STOP, gst_frw_sdio_test_event->test_data.pkt_len);
        oal_memcopy((OAL_NETBUF_DATA(pst_netbuf) + 2), (oal_uint8 *)gst_test_param, OAL_SIZEOF(frw_sdio_test_param));
        pst_test_param = (frw_sdio_test_param *)(OAL_NETBUF_DATA(pst_netbuf) + 2);
        OAL_IO_PRINT("[SDIO_TEST]test param:%d %d\n",pst_test_param->pkt_gen,pst_test_param->pkt_len);
    }
    ulret = frw_sdio_test_post_event(pst_netbuf, 10);
    if(OAL_SUCC != ulret)
    {
        OAL_IO_PRINT("sdio test send failed\n");
        //oal_netbuf_free(pst_netbuf);
        return ulret;
    }
    return OAL_SUCC;
}

oal_uint32 frw_sdio_test_start(oal_void)
{
    oal_uint32 ulret;
    oal_uint32 ulloopnum;

    gst_frw_sdio_test_event->test_data.pkt_rcvd = 0;
    gst_frw_sdio_test_event->test_data.pkt_sent = 0;
    gst_frw_sdio_test_event->test_data.throughput = 0;
    gst_frw_sdio_test_event->test_data.trans_time = 0;
    gst_frw_sdio_test_event->test_data.err_num = 0;
    gst_frw_sdio_test_event->test_data.err_byte_num = 0;
    gst_frw_sdio_test_event->start_time = ktime_get();
    gst_frw_sdio_test_event->last_time =  ktime_get();

    for(ulloopnum = 0; ulloopnum < gst_frw_sdio_test_event->test_data.pkt_gen; ulloopnum++)
    {
        ulret = frw_sdio_test_tx(FRW_SDIO_TEST_GEN_START);
        if(OAL_SUCC != ulret)
        {
            OAL_IO_PRINT("frw sdio test tx failed\n");
            return ulret;
        }
        //msleep(10);
        gst_frw_sdio_test_event->test_data.pkt_sent++ ;
        gst_frw_sdio_test_event->last_time= ktime_get();
        if(unlikely(OAL_FALSE == gst_frw_sdio_test_event->started))
        {
            return OAL_FAIL;
        }
    }
    return OAL_SUCC;
}

oal_uint32 frw_sdio_test_stop(oal_void)
{
    oal_uint32 ulret;

    ulret = frw_sdio_test_tx(FRW_SDIO_TEST_GEN_STOP);
    if(OAL_FAIL == ulret)
    {
        OAL_IO_PRINT("frw sdio test tx failed\n");
        return ulret;
    }
    return OAL_SUCC;
}

oal_uint32 frw_sdio_test_rx_config(oal_void)
{
    oal_uint32           ulret;

    gst_test_param = oal_memalloc(OAL_SIZEOF(frw_sdio_test_param));
    gst_test_param->pkt_gen = gst_frw_sdio_test_event->test_data.pkt_gen;
    gst_test_param->pkt_len = gst_frw_sdio_test_event->test_data.pkt_len;
    gst_frw_sdio_test_event->test_data.pkt_rcvd = 0;
    gst_frw_sdio_test_event->test_data.pkt_sent = 0;
    gst_frw_sdio_test_event->test_data.throughput = 0;
    gst_frw_sdio_test_event->test_data.trans_time = 0;
    gst_frw_sdio_test_event->test_data.err_num = 0;
    gst_frw_sdio_test_event->test_data.err_byte_num = 0;
    gst_frw_sdio_test_event->last_time = gst_frw_sdio_test_event->start_time = ktime_get();
    ulret = frw_sdio_test_tx(FRW_SDIO_TEST_GEN_RX);
    if(OAL_FAIL == ulret)
    {
        OAL_IO_PRINT("frw sdio test tx failed\n");
        return ulret;
    }
    return OAL_SUCC;
}

oal_void frw_sdio_test_work(oal_void)
{
    oal_uint32 ulret;

    if(gst_frw_sdio_test_event->test_data.test_type != HMAC_HCC_TEST_RX_SUB_TYPE)
    {
        ulret = frw_sdio_test_start();
        if(OAL_SUCC != ulret)
        {
            OAL_COMPLETE(&gst_frw_sdio_test_event->test_done);
            OAL_IO_PRINT("sdio test start pkt send failed\n");
            return ;
        }
        OAL_IO_PRINT("[SDIO_TEST]gen start frame succ\n");
        ulret = frw_sdio_test_stop();
        if(OAL_SUCC != ulret)
        {
            OAL_COMPLETE(&gst_frw_sdio_test_event->test_done);
            OAL_IO_PRINT("sdio test stop pkt send failed\n");
            return ;
        }
        OAL_IO_PRINT("[SDIO_TEST]gen stop frame succ\n");
    }
    else
    {

        ulret = frw_sdio_test_rx_config();
        if(OAL_SUCC != ulret)
        {
            OAL_COMPLETE(&gst_frw_sdio_test_event->test_done);
            OAL_IO_PRINT("sdio test stop pkt send failed\n");
            return ;
        }
    }

}

oal_uint64 frw_sdio_test_get_trans_time(ktime_t start_time, ktime_t stop_time)
{
    ktime_t     trans_time;
    oal_uint64  trans_us;

    trans_time = ktime_sub(stop_time, start_time);

    trans_us = (oal_uint64)ktime_to_us(trans_time);

    if (trans_us == 0)
    {
        trans_us = 1;
    }

    return trans_us;
}


oal_void frw_sdio_test_throughput_cac(ktime_t start_time ,ktime_t stop_time)
{
     oal_uint64 trans_us;
     oal_uint64 temp;
     oal_uint64 us_to_s; /* converted  usecond to second */

     trans_us = frw_sdio_test_get_trans_time(start_time, stop_time);

     temp = (gst_frw_sdio_test_event->test_data.pkt_sent + gst_frw_sdio_test_event->test_data.pkt_rcvd);

     temp = temp * gst_frw_sdio_test_event->test_data.pkt_len;

     temp = temp * 1000; /* 最终吞吐率单位 是 MBit/s么?这里两个*1000是啥意思? */

     temp = temp * 1000;

     temp = temp * 8;

     do_div(temp,trans_us); /* temp = temp / trans_us */

     do_div(temp, 1024);  /* Converted to KBit */

     do_div(temp, 1024);   /* Converted to MBit */

     us_to_s = trans_us;

     do_div(us_to_s, 1000000u); /* us_to_s = us_to_s / 1000000 */
     gst_frw_sdio_test_event->test_data.throughput = temp;
     gst_frw_sdio_test_event->test_data.trans_time = us_to_s;
}

oal_void frw_sdio_test_throughput_gen(oal_void)
{
    frw_sdio_test_throughput_cac(gst_frw_sdio_test_event->start_time, gst_frw_sdio_test_event->last_time);
}

oal_uint32 frw_sdio_test_set_case(oal_uint32  pkt_gen, oal_uint32 pkt_len, oal_uint8 test_type)
{
    oal_uint32 ulret;

    if(test_type >= HMAC_HCC_TEST_EVENT_SUB_TYPE_BUTT)
    {
        OAL_IO_PRINT("invalid test type\n");
    }

    if(pkt_gen > FRW_SDIO_TEST_MAX_PKTGEN)
    {
        OAL_IO_PRINT("invalid test pkt to gen\n");
        return OAL_FAIL;
    }

    if(pkt_len > FRW_SDIO_TEST_MAX_PKTLEN)
    {
        OAL_IO_PRINT("invalid test pkt len:%d\n", pkt_len);
        return OAL_FAIL;
    }
    OAL_IO_PRINT("[SDIO_TEST]now into set case\n");
    mutex_lock(&gst_frw_sdio_test_event->mutex_lock);
    if (OAL_TRUE == gst_frw_sdio_test_event->started)
    {
        OAL_IO_PRINT("sdio test task is processing, wait for end and reinput.");
        mutex_unlock(&gst_frw_sdio_test_event->mutex_lock);
        return OAL_FAIL;
    }
    gst_frw_sdio_test_event->started = OAL_TRUE;
    mutex_unlock(&gst_frw_sdio_test_event->mutex_lock);
    OAL_IO_PRINT("[SDIO_TEST]now into init comp\n");
    OAL_INIT_COMPLETION(&gst_frw_sdio_test_event->test_done);

    gst_frw_sdio_test_event->test_data.pkt_gen = pkt_gen;
    gst_frw_sdio_test_event->test_data.pkt_len = pkt_len;
    gst_frw_sdio_test_event->test_data.test_type = test_type;

    OAL_IO_PRINT("[SDIO_TEST]pkt_gen=%u,pkt_len=%u\n",gst_frw_sdio_test_event->test_data.pkt_gen,gst_frw_sdio_test_event->test_data.pkt_len);
    frw_sdio_test_work();

    ulret = wait_for_completion_interruptible(&gst_frw_sdio_test_event->test_done);
    if(ulret == 0)
    {
        //OAL_IO_PRINT("sdio test time out!\n");
    }
    OAL_IO_PRINT("test done!\n");

    frw_sdio_test_throughput_gen();

    gst_frw_sdio_test_event->started = OAL_FALSE;
    return OAL_SUCC;
}

oal_void frw_sdio_test_cmp_data(oal_netbuf_stru *pst_netbuf)
{
    oal_uint8 *puc_netbuf_payload = OAL_NETBUF_DATA(pst_netbuf);
    oal_uint32 ulloopnum;
    oal_uint32 ulflag;
    ulflag = 0;
    if ( ( FRW_SDIO_TEST_DATA_GEN== pst_netbuf->data[16] ) || ( FRW_SDIO_TEST_DATA_GEN == pst_netbuf->data[0] ))
    {
        for(ulloopnum = 0; ulloopnum < (gst_frw_sdio_test_event->test_data.pkt_len - 64); ulloopnum++)
        {
            if(FRW_SDIO_TEST_DATA_GEN != puc_netbuf_payload[ulloopnum])
            {
                gst_frw_sdio_test_event->test_data.err_byte_num++;
                ulflag = 1;
            }
        }
        if(ulflag)
        {
            gst_frw_sdio_test_event->test_data.err_num++;
        }
    }
    else if ( ( FRW_SDIO_TEST_DATA_STOP== pst_netbuf->data[16] ) || ( FRW_SDIO_TEST_DATA_STOP == pst_netbuf->data[0] ))
    {
        return;
        //for(ulloopnum = 0; ulloopnum < (gst_frw_sdio_test_event->test_data.pkt_len - 64); ulloopnum++)
        //{
        //    if(FRW_SDIO_TEST_DATA_STOP != puc_netbuf_payload[ulloopnum])
        //    {
        //        gst_frw_sdio_test_event->test_data.err_byte_num++;
        //        ulflag = 1;
        //    }
        //}
        //if(ulflag)
        //{
        //    gst_frw_sdio_test_event->test_data.err_num++;
        //}
    }

}

oal_uint32 frw_sdio_test_rcvd(oal_netbuf_stru *pst_netbuf)
{
    gst_frw_sdio_test_event->test_data.pkt_rcvd++;
    gst_frw_sdio_test_event->last_time = ktime_get();
    //OAL_IO_PRINT("[SDIO_TEST]host rcvd %u\n",gst_frw_sdio_test_event->test_data.pkt_rcvd);
    if ( ( FRW_SDIO_TEST_DATA_STOP == pst_netbuf->data[65] ) || ( FRW_SDIO_TEST_DATA_STOP == pst_netbuf->data[69] ))
    {
        gst_frw_sdio_test_event->test_data.pkt_rcvd--;
        OAL_IO_PRINT("[SDIO_TEST]host rcvd stop flag\n");
        if ((HMAC_HCC_TEST_TX_SUB_TYPE == gst_frw_sdio_test_event->test_data.test_type)||(HMAC_HCC_TEST_LOOP_SUB_TYPE == gst_frw_sdio_test_event->test_data.test_type)\
            ||(HMAC_HCC_TEST_RX_SUB_TYPE == gst_frw_sdio_test_event->test_data.test_type))
        {
            OAL_IO_PRINT("[SDIO_TEST]host rcvd rcvd complete\n");
            OAL_COMPLETE(&gst_frw_sdio_test_event->test_done);
        }
    }
    oal_netbuf_free(pst_netbuf);
    return OAL_SUCC;
}

oal_uint32  frw_sdio_test_init_module(oal_void)
{
    gst_frw_sdio_test_event = oal_memalloc(sizeof(*gst_frw_sdio_test_event));

    if(gst_frw_sdio_test_event == OAL_PTR_NULL)
    {
        return OAL_FAIL;
    }
    gst_frw_sdio_test_event->test_data.pkt_len  = 0;
    gst_frw_sdio_test_event->test_data.pkt_sent = 0;
    gst_frw_sdio_test_event->test_data.pkt_gen  = 0;
    gst_frw_sdio_test_event->started  = OAL_FALSE;
    return OAL_SUCC;
}
#endif
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
oal_uint32 frw_sdio_test_rcvd(oal_netbuf_stru *pst_netbuf)
{
    return 0;
}
oal_void frw_sdio_test_cmp_data(oal_netbuf_stru *pst_netbuf)
{
    return ;
}
#endif
oal_uint32 hmac_hcc_test_rx_handler(frw_event_mem_stru * pst_test_event_mem)
{
    frw_event_stru                  *pst_test_event;
    hcc_event_stru                  *pst_test_event_payload;
    /*OAL_IO_PRINT("[SDIO_TEST]now into hmac hcc rx handler\n");*/
    pst_test_event           = (frw_event_stru *)pst_test_event_mem->puc_data;
    pst_test_event_payload   = (hcc_event_stru *)pst_test_event->auc_event_data;
    frw_sdio_test_rcvd((oal_netbuf_stru *)pst_test_event_payload->pst_netbuf);
    if(ul_data_cmp_flag == 1)
    {
        frw_sdio_test_cmp_data((oal_netbuf_stru *)pst_test_event_payload->pst_netbuf);
    }
    return OAL_SUCC;
}

oal_module_symbol(hmac_hcc_test_rx_handler);
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

