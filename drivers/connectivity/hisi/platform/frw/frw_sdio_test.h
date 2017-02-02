#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



#include "oam_ext_if.h"
#include "dmac_ext_if.h"
#include "frw_ext_if.h"
#include "frw_event_main.h"


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
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_SDIO_TEST_H


#define FRW_SDIO_TEST_GEN_START 0
#define FRW_SDIO_TEST_GEN_STOP  1
#define FRW_SDIO_TEST_GEN_RX    2/* HOST单收标志 */

#define FRW_SDIO_TEST_DATA_GEN  0xa5 /* 测试数据 */
#define FRW_SDIO_TEST_DATA_STOP 0x5a /* 数据结束位 */

#define FRW_SDIO_TEST_MAX_PKTGEN 200000
#define FRW_SDIO_TEST_MAX_PKTLEN 1548

#define FRW_TEST_WAIT_SEND_COMPLETE 1000

typedef struct frw_sdio_test_data{
    oal_uint8                         test_type;
    oal_uint32                        err_num;
    oal_uint32                        err_byte_num;
    oal_uint32                        pkt_rcvd;/* packet received */
    oal_uint32                        pkt_sent;/* packet sent */
    oal_uint32                        pkt_gen; /* packet generate */
    oal_uint32                        pkt_len; /* packet  length */
    oal_uint64                        trans_time;
    oal_uint64                        throughput;
}frw_sdio_test_data;

typedef struct frw_sdio_test_param{
    oal_uint32                        pkt_gen;
    oal_uint32                        pkt_len;
}frw_sdio_test_param;

#if(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
typedef struct  frw_sdio_test_event{
    struct mutex                mutex_lock;/* sdio test task lock */

    frw_sdio_test_data     test_data;

    /* hsdio perf started */
    oal_uint32                      started;
    /* hsdio perf statistic */
    ktime_t                     start_time;
    /*The last update time*/
    ktime_t                     last_time;

    /*To hsdio test sync*/
    struct completion test_done;

    /*sdio test thread and seam*/
}frw_sdio_test_event;


oal_void frw_sdio_test_result_report(oal_void);

oal_uint32 frw_sdio_test_set_case(oal_uint32  pkt_gen, oal_uint32 pkt_len, oal_uint8 test_type);

oal_uint32 frw_sdio_test_post_event(oal_netbuf_stru *pst_netbuf, oal_uint timeout);

oal_uint32 frw_sdio_test_tx(oal_uint8 gen_type);
oal_uint32 frw_sdio_test_start(oal_void);
oal_uint32 frw_sdio_test_stop(oal_void);
oal_uint32 frw_sdio_test_rx_config(oal_void);
oal_void frw_sdio_test_work(oal_void);
oal_uint64 frw_sdio_test_get_trans_time(ktime_t start_time, ktime_t stop_time);
oal_void frw_sdio_test_throughput_cac(ktime_t start_time ,ktime_t stop_time);
oal_void frw_sdio_test_throughput_gen(oal_void);
oal_uint32 frw_sdio_test_set_case(oal_uint32  pkt_gen, oal_uint32 pkt_len, oal_uint8 test_type);
oal_void frw_sdio_test_cmp_data(oal_netbuf_stru *pst_netbuf);
oal_uint32 frw_sdio_test_rcvd(oal_netbuf_stru *pst_netbuf);

#endif

extern oal_uint32 hmac_hcc_test_rx_handler(frw_event_mem_stru * pst_test_event_mem);
extern oal_void test_case_01(oal_uint32  pkt_gen, oal_uint32 pkt_len, oal_uint8 test_type);
extern oal_uint32 frw_sdio_test_rcvd(oal_netbuf_stru *pst_netbuf);




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

