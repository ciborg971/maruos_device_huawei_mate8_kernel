
#ifndef	_CIPHER_BALONG_H_
#define	_CIPHER_BALONG_H_

#include <osl_types.h>
#include <osl_sem.h>
#include <osl_spinlock.h>
#include <mdrv_cipher.h>
#include <bsp_clk.h>
#include <soc_memmap_comm.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CIPHER_IV_SEL         0 /* 只能是0/1 */
#define CIPHER_IV_NUM         0 /* 只能是0/1 */
#define CIPHER_USRFIELD_NUM   3
#define CIPHER_INT_REG_NUM    5
#define CIPHER_CHN_NUM        7
#define CIPHER_CHN_NUM_LESS   5
#define CIPHER_CONFIG_AEC_CTR 7
#define CIPHER_KEY_LEN        32
#define CIPHER_KEYRAM_SIZE    512
#define CIPHER_VERSION_6950   0x69500100
#define LTE_KEY_OPT_CHANNEL_KDF		  4
#define CIPHER_BD_IN_CHAIN	(0x1U << 16)
#define CIPHER_CD_CHAIN_END	(0x1U << 16)
#define	RD_ENSTAT_MASK      (0x60000000)
#define	CIPHER_RD_VALID		(0x80000000)
#define	CIPHER_LEN_CHK_ERR	(0x2)
#define	CIPHER_RW_MASK		(0x3ff)
#define CIPHER_RMASK		(0x03ff0000)
#define CIPHER_WMASK		(0x000003ff)
#define	CIPHER_RW_OFFSET	16
#define	CIPHER_GET_ZERO_RD	0
#define	CIPHER_DUMP_SIZE	HI_CIPHER_REG_SIZE
/*lint -e830*/
#define CIPHER_BSWAP32(val) \
        (((val) >> 24) | (((val) >> 8) & 0x0000ff00) | \
        (((val) << 8) & 0x00ff0000) | ((val) << 24))
        
/*lint -e830*/
#define CIPHER_TEST_REG(i)   	   (0x20 + (0x4*(i)))
#define CIPHER_CHN_RESET(i)   	   (0x80 + (0x80*(i)))
#define CIPHER_CHN_ENABLE(i)       (0x84 + (0x80*(i)))
#define CIPHER_CHN_CONFIG(i)       (0x88 + (0x80*(i)))
#define CIPHER_CHNBDQ_BASE(i)      (0x8c + (0x80*(i)))
#define CIPHER_CHNBDQ_SIZE(i)      (0x90 + (0x80*(i)))
#define CIPHER_CHNBDQ_RWPTR(i)     (0x94 + (0x80*(i)))
#define CIPHER_CHNBDQ_RDPTR(i)     (0x98 + (0x80*(i)))
#define CIPHER_CHNBDQ_WRPTR(i)     (0x9c + (0x80*(i)))
#define CIPHER_CHNBDQ_BDNUM(i)     (0xa0 + (0x80*(i)))
#define CIPHER_CHNBDQ_BADBDNUM(i)  (0xa4 + (0x80*(i)))
#define CIPHER_CHNRDQ_BASE(i)      (0x480 + (0x80*(i)))
#define CIPHER_CHNRDQ_SIZE(i)      (0x484 + (0x80*(i)))
#define CIPHER_CHNRDQ_RWPTR(i)     (0x488 + (0x80*(i)))
#define CIPHER_CHNRDQ_RDPTR(i)     (0x48C + (0x80*(i)))
#define CIPHER_CHNRDQ_WRPTR(i)     (0x490 + (0x80*(i)))
#define LTE_SECURITY_CHANNEL_SRB 	CIPHER_SECURITY_CHANNEL_1

//#define CIPHER_DEBUG_BD_CD_QUEUE

typedef u32 u128[4];
struct cipher_bd
{
	u32 cfg;
	u32 ptr_attr_ilen;
	u32 offset_olen;
	u32 iptr_pad;
	u32 optr;
	u32 aph;
#if(0 == CIPHER_IV_SEL)
	u32 count;
#else
	u128 iv[CIPHER_IV_NUM + 1];
#endif
	u32 usr_field[CIPHER_USRFIELD_NUM];
};

struct cipher_rd
{
	u32 ptr_attr_ilen;
	u32 offset_olen;
	u32 iptr_pad;
	u32 optr;
	u32 usr_field[CIPHER_USRFIELD_NUM];
	u32 cfg;
};

struct cipher_cd
{
	u32 ptr;
	u32 ptr_attr;
};

enum fifo_free_pos
{
	FIFO_LEFT,
	FIFO_RIGHT
};

enum fifo_type
{
	FIFO_BDQ,
	FIFO_CDQ,
	FIFO_RDQ
};

struct cdlist_info
{
	void * cdlist_base;
	unsigned int cdlist_size;
	unsigned int cd_cnt;
};

struct fifo_ctl;
struct fifo_ops
{
	void (*get_free_cd_cnt)(struct fifo_ctl * f_ctl, unsigned int * l_cnt, unsigned int * r_cnt);
	unsigned int (*get_free_bd_cnt)(struct fifo_ctl * f_ctl);
	unsigned int (*get_filled_bd_cnt)(struct fifo_ctl * f_ctl);
	int (*get_elems_addr)(struct fifo_ctl * f_ctl, enum fifo_free_pos free_pos, void ** elem_addr);
	void (*move_bd_widx)(struct fifo_ctl * f_ctl, unsigned int nn);
	int (*move_ridx)(struct fifo_ctl * f_ctl, unsigned int nn);
	int (*rst_rwidx)(struct fifo_ctl * f_ctl);
};

struct fifo_ctl
{
	struct fifo_ops   ops;
	enum fifo_type    type;
	spinlock_t        lock;
	unsigned int      chn_id;
	unsigned int      elem_cnt;
	unsigned int      elem_size;
	unsigned int      write_idx;
	unsigned int      read_idx;
	void *            fifo_base;
	unsigned char     pad[8];
};/* n times of 32 bytes */

struct cipher_chn_ctl;
struct chn_ops
{
	int (*cfg_cds)(struct cipher_chn_ctl * chn_ctl, struct cipher_cd * cds_base, void * ptr);
	int (*cfg_single_bd)(struct cipher_chn_ctl * chn_ctl, CIPHER_SINGLE_CFG_S * cfg_infor, struct cdlist_info * cdlist_infor);
	int (*get_rds)(struct cipher_chn_ctl * chn_ctl, unsigned int *err_cnt, CIPHER_RD_INFO_S * rds_info, unsigned int rds_cnt);
	void (*get_rdq_rwptr)(struct cipher_chn_ctl * chn_ctl, unsigned int * r, unsigned int * w);
	void (*get_bdq_rwptr)(struct cipher_chn_ctl * chn_ctl, unsigned int * r, unsigned int * w);
	void (*move_rdq_r_ptr)(struct cipher_chn_ctl * chn_ctl);
	void (*move_bdq_w_ptr)(struct cipher_chn_ctl * chn_ctl);
	int (*chn_idle)(struct cipher_chn_ctl * chn_ctl);
	int (*chn_rst)(struct cipher_chn_ctl * chn_ctl);
};

struct cipher_chn_ctl
{
	struct chn_ops    ops;
	unsigned int      chn_id;
	osl_sem_id        chn_sem;
	struct fifo_ctl  bd_fifo;
	struct fifo_ctl  rd_fifo;
	struct fifo_ctl  cd_fifo;
	unsigned int	  need_purge: 1;
	unsigned int      straight  : 1;
	unsigned int      purging   : 1;
	unsigned int      dma   	: 1;
	unsigned int      reserve   : 28;
	unsigned int      pre_check_bd_idx;
	/* cfg by caller */
	unsigned long     idata_ptr_off;
	unsigned long     idata_size_off;
	unsigned long     idata_nxt_ptr_off;
	unsigned long     odata_ptr_off;
	unsigned long     odata_size_off;
	unsigned long     odata_nxt_ptr_off;
	CIPHER_FREEMEM_CB_T func_free_inmem;
	CIPHER_FREEMEM_CB_T func_free_outmem;
	CIPHER_NOTIFY_CB_T  func_notify;
};

struct cipher_ctl
{
	void *        reg_virt_base;
	unsigned int  irq_num;
	struct clk *  pclk;
	spinlock_t    clk_lock;
	int           clk_en;
	unsigned int  clkrate;
	unsigned int  clk_switch;
	unsigned int  chn_cnt;
	unsigned int  suspend_resume;
	unsigned int  init_flag;
	unsigned long reg_int_mask[CIPHER_INT_REG_NUM];
	unsigned long reg_int_msta[CIPHER_INT_REG_NUM];
	unsigned long reg_int_sta [CIPHER_INT_REG_NUM];
	unsigned int  keyram_backup[CIPHER_KEYRAM_SIZE / sizeof(unsigned int)];
	struct cipher_chn_ctl cipher_chn[CIPHER_CHN_NUM];
	unsigned int dump_reg;
	unsigned int crg_clk_stat4;
	unsigned int acc_fifo_depth;
	unsigned int acc_chn_num;
	
#ifdef CIPHER_DEBUG_BD_CD_QUEUE
	struct cipher_debug_bd_cd *bd_cd_idx;
	unsigned int idx_dbg_chn;
	unsigned int cfg_num;
#endif

};

struct cipher_debug_ctl
{
	unsigned int bdq_full_times[CIPHER_CHN_NUM];
	unsigned int cdq_full_times[CIPHER_CHN_NUM];
	unsigned int chn_rst_times [CIPHER_CHN_NUM];
	unsigned int chn_bdset_time[CIPHER_CHN_NUM];
	unsigned int cd_node_num[CIPHER_CHN_NUM];
	unsigned int cd_left_cnt[CIPHER_CHN_NUM];
	unsigned int cd_right_cnt[CIPHER_CHN_NUM];

	/*RD related*/
	unsigned int rdq_empty_cnt[CIPHER_CHN_NUM];
	unsigned int rd_int_chk_err[CIPHER_CHN_NUM];	/*RD integrity check error*/
	unsigned int rd_len_chk_err[CIPHER_CHN_NUM];	/*RD bd length check error*/
	unsigned int rd_invalid[CIPHER_CHN_NUM];		/*Invalid RD*/

	/*cipher status*/
	unsigned int set_rate_err;
	unsigned int alloc_failed;
	unsigned int set_psam_failed;
	unsigned int dump_init_failed;
};

void cipher_disable_aes_opt_bypass(int channel);

void cipher_enable_aes_opt_bypass(int channel);
void cipher_print_hex(unsigned int * data,unsigned int len);

#ifdef __cplusplus
}
#endif

#endif /* _CIPHER_BALONG_H_ */
