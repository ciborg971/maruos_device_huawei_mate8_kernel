

#ifndef __BFGX_EXCEPTION_RST_H__
#define __BFGX_EXCEPTION_RST_H__
/*****************************************************************************
  1 Include other Head file
*****************************************************************************/

/*****************************************************************************
  2 Define macro
*****************************************************************************/
#define BFGX_RF_QUERY_TIME         (5)      /* bfgx每5秒钟查询一次rf温度*/
#define WIFI_RF_QUERY_TIME         (5)      /* wifi每5秒钟查询一次rf温度*/
#define WAIT_BFGX_READ_STACK_TIME  (5000)   /* 等待bfgx读栈操作完成的时间，5000毫秒*/
#define BFGX_BEAT_TIME             (3)      /* bfgx心跳超时时间为3秒钟*/
#define WIFI_DUMP_MEM_SIZE         (4096)   /* wifi device 上报的栈内存最大长度*/
#define BFGX_DUMP_MEM_SIZE         (4096)   /* bfgx device 上报的栈内存最大长度*/

#define PLAT_EXCEPTION_RESET_IDLE  (0)      /* plat 没有在处理异常*/
#define PLAT_EXCEPTION_RESET_BUSY  (1)      /* plat 正在处理异常*/

#define BFGX_NOT_RECV_BEAT_INFO    (0)      /* host没有收到心跳消息*/
#define BFGX_RECV_BEAT_INFO        (1)      /* host收到心跳消息*/

#define RF_TEMERATURE_NORMAL       (0)      /* rf温度正常*/
#define RF_TEMERATURE_OVERHEAT     (1)      /* rf温度过热*/

#define EXCEPTION_SUCCESS          (0)
#define EXCEPTION_FAIL             (1)

#define BEAT_TIMER_DELETE          (0)
#define BEAT_TIMER_RESET           (1)

/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/
enum SUBSYSTEM_ENUM
{
	SUBSYS_WIFI  = 0,
	SUBSYS_BFGX  = 1,

	SUBSYS_BOTTOM,
};

enum WIFI_THREAD_ENUM
{ 
	THREAD_WIFI   = 0,

	WIFI_THREAD_BOTTOM,
};

enum BFGX_THREAD_ENUM
{ 
	THREAD_BT   = 0,
	THREAD_FM   = 1,
	THREAD_GNSS = 2,
	THREAD_IR   = 3,
	THREAD_NFC  = 4,

	BFGX_THREAD_BOTTOM,
};

enum EXCEPTION_TYPE_ENUM
{
	BEAT_HEART_TIMEOUT     = 0,  /*心跳超时*/
	LAST_WORD              = 1,  /*CPU挂死，临终遗言*/
	WATCHDOG_TIMEOUT       = 2,  /*看门狗超时*/
	TIMER_TIMEOUT          = 3,  /*定时器超时*/
	ARP_TIMEOUT            = 4,  /*arp verifier超时，有发无收*/
	RF_OVERHEAT_EXCEPTION  = 5,  /*RF过热异常*/

	EXCEPTION_TYPE_BOTTOM,
};

enum DUMP_MEM_STATUS
{
    DUMP_MEM_IDLE           = 0,
    DUMP_MEM_BUSY           = 1,

    DUMP_MEM_STATUS_BOTTOM,
};

enum RESET_DEVICE_MSG
{
    RESET_MSG_NONE             = 0,
    RESET_MSG_BFGX_RESET       = 1,
    RESET_MSG_WIFI_RESET       = 2,
    RESET_MSG_BFGX_RF_OVERHEAT = 3,
    RESET_MSG_BFGX_RF_NORMAL   = 4,
    RESET_MSG_WIFI_RF_OVERHEAT = 5,
    RESET_MSG_WIFI_RF_NORMAL   = 6,
    RESET_MSG_POWER_RESET      = 7,

    RESET_MSG_BOTTOM,
};

struct st_om_mesg_heager
{
   uint8        ucFrameStart;
   uint8        ucFuncType;
   uint8        ucPrimeId;
   uint8        aucReserver[1];
   uint16       usFrameLen;
   uint16       usSN;
};

struct st_exception_mem_info
{
    uint8 *exception_mem_addr;
    uint32 total_size;
    uint32 recved_size;
    uint32 mem_status;
};

struct st_wifi_dump_mem_info
{
    ulong  mem_addr;
    uint32 size;
    uint8  *file_name;
};

struct st_exception_info
{
    uint32   exception_reset_enable;
	uint32   subsys_type;
	uint32   thread_type;
	uint32   excetion_type;
	
	atomic_t bfgx_beat_flag;
	atomic_t bfgx_rf_temperature_status;
	atomic_t wifi_rf_temperature_status;
	atomic_t is_reseting_device;
	
	struct workqueue_struct *plat_exception_rst_workqueue;
	struct work_struct plat_exception_rst_work;
	struct mutex  exception_reset_mutex;
	struct timer_list bfgx_rf_overheat_timer;
	struct timer_list wifi_rf_overheat_timer;
	struct timer_list bfgx_beat_timer;

	struct completion wait_read_bfgx_stack;

	struct ps_plat_s *ps_plat_d;
	void *wifi_callback;

	spinlock_t exception_spin_lock;

    uint32 reset_device_msg;
    uint32 wifi_exception_cnt;
    uint32 bfgx_exception_cnt;

	struct st_exception_mem_info dump_mem[SUBSYS_BOTTOM];

	/*下边的变量调试使用*/
	uint32 debug_beat_flag;
};

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/

/*****************************************************************************
  5 全局变量定义
*****************************************************************************/

/*****************************************************************************
  6 EXTERN FUNCTION
*****************************************************************************/
extern int32 mod_beat_timer(uint8 on);
extern int32 is_bfgx_exception(void);
extern int32 get_exception_info_reference(struct st_exception_info **exception_data);
extern int32 plat_exception_handler(uint32 subsys_type, uint32 thread_type, uint32 exception_type);
extern int32 plat_bfgx_exception_rst_register(struct ps_plat_s *data);
extern int32 plat_wifi_exception_rst_register(void *data);
extern int32 wifi_exception_mem_dump(struct st_wifi_dump_mem_info *pst_mem_dump_info, uint32 count);
extern int32 prepare_to_recv_bfgx_stack(uint32 len);
extern int32 bfgx_recv_dev_mem(uint8 *buf_ptr, uint16 count);
extern int32 plat_exception_reset_init(void);
extern int32 plat_exception_reset_exit(void);
#endif

