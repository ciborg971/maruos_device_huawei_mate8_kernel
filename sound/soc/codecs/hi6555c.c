/*
* hi6555c.c   --  HI6555C ALSA Soc codec driver
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/notifier.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/kthread.h>
#include <linux/clk.h>
#include <linux/timer.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/tlv.h>
#include <asm/io.h>
#include <linux/spinlock.h>
#include <linux/switch.h>
#include <linux/wakelock.h>
#include <linux/vmalloc.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#endif
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/of_gpio.h>
#include <linux/mfd/hisi_hi6xxx_pmic.h>

/*add for codec irq*/
#include <linux/gpio.h>
/*  Reason: For hook  */
#include <sound/jack.h>
/*KEY_MEDIA defined in linux/input.h*/
#include <linux/input/matrix_keypad.h>
#include <linux/irq.h>
#include <sound/hi6555c_common.h>
#include <linux/interrupt.h>
#include <linux/irqnr.h>
#include <linux/hisi/drv_pmic_if.h>
#include "hi6555c.h"
#include <linux/hisi/hi6xxx_ipc_enum.h>
#include <hisi/hilog.h>
#include <soc_crgperiph_interface.h>

#define HI6555C_PB_MIN_CHANNELS ( 2 )
#define HI6555C_PB_MAX_CHANNELS ( 2 )
#define HI6555C_CP_MIN_CHANNELS ( 2 )
#define HI6555C_CP_MAX_CHANNELS ( 2 )
#define HI6555C_FORMATS ( SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE)
#define HI6555C_RATES ( SNDRV_PCM_RATE_8000  | SNDRV_PCM_RATE_16000 |\
                                     SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 )

/* HI6555C CODEC CLOCK */
/*static struct clk *g_codec_clk = NULL;*/

/* HI6555C CODEC */
static struct snd_soc_codec *g_codec = NULL;

/* HI6555C VERSION*/
static unsigned int g_codec_version = 0;

/* HI6555C REGISTER BASE ADDR */
static void __iomem *g_hi6555c_socodec_base_addr     = NULL;
static void __iomem *g_hi6555c_reg_base_addr         = NULL;
static void __iomem *g_hi6555c_hkadc_reg_base_addr   = NULL;
static void __iomem *g_hi6555c_psctrl_base_addr      = NULL;
/* add for hi6250 begin */
static void __iomem *g_hi6555c_aspcfg_base_addr      = NULL;
static void __iomem *g_hi6555c_aoioc_base_addr       = NULL;
static void __iomem *g_hi6555c_ioc_base_addr         = NULL;
static void __iomem *g_hi6555c_gpio21_base_addr      = NULL;
static void __iomem * g_hi6555c_pericrg_base_addr     = NULL;
/* add for hi6250 end */

enum hi6555c_jack_states {
    HI6555C_JACK_BIT_NONE           = 0, /* unpluged */
    HI6555C_JACK_BIT_HEADSET     = 1, /* pluged with mic */
    HI6555C_JACK_BIT_HEADPHONE = 2, /* pluged with 3 pole */
    HI6555C_JACK_BIT_HEADSET_NO_MIC = 3, /* pluged without mic */
    HI6555C_JACK_BIT_PLUGING      = 4, /* pluging, not fully pluged */
    HI6555C_JACK_BIT_INVALID       = 5, /* index */
};

enum headset_voltage {/*mV*/
    HS_3_POLE_MAX_VOLTAGE = 8,
    HS_4_POLE_MIN_VOLTAGE = 1350,
    HS_4_POLE_MAX_VOLTAGE = 2565,
    HS_MAX_VOLTAGE = 2650,
};

enum btn_voltage{/*mV*/
    KEY_UP_MIN_VALUE     = 1350,
    KEY_UP_MAX_VALUE     = 2565,
    KEY_PLAY_MIN_VALUE  = 0,
    KEY_PLAY_MAX_VALUE = 50,
    KEY_BACK_MIN_VALUE  = 500,
    KEY_BACK_MAX_VALUE = 680,
    KEY_FORWARD_MIN_VALUE = 130,
    KEY_FORWARD_MAX_VALUE = 300
};

enum delay_time {
    HS_TIME_PI_DETECT       = 800, /* ms */
    HS_TIME_COMP_IRQ_TRIG   = 30,  /* ms */
    HS_TIME_COMP_IRQ_TRIG_2 = 50, /*ms*/
};

struct hi6555c_jack_data {
    struct snd_soc_jack *jack;
    int report;
    struct switch_dev sdev;
};

struct hi6555c_headset_voltage {/*mV*/
    unsigned short hs_3_pole_max_voltage;
    unsigned short hs_4_pole_min_voltage;
    unsigned short hs_4_pole_max_voltage;
};

struct hi6555c_btn_voltage {/*mV*/
    unsigned short key_up_min_value;
    unsigned short key_up_max_value;
    unsigned short key_play_min_value;
    unsigned short key_play_max_value;
    unsigned short key_back_min_value;
    unsigned short key_back_max_value;
    unsigned short key_forward_min_value;
    unsigned short key_forward_max_value;
};

#define CONFIG_DEBUG_POP 1
#ifdef CONFIG_DEBUG_FS
struct hi6555c_rr_cache {
    unsigned int reg;
    unsigned int val;
    unsigned long time;
};

#ifdef CONFIG_DEBUG_POP
enum hi6555c_pop_op {
    HI6555C_POP_CLEAN       = 0, /* CLEAN */
    HI6555C_POP_DELAY_MS = 1, /* DELAY */
    HI6555C_POP_DELAY_US = 2, /* DELAY */
    HI6555C_POP_REG_WRITE = 3, /* REG WRITE */
};

struct hi6555c_ps_cache {
    unsigned int reg;
    unsigned int val;
    enum hi6555c_pop_op op;
};
#endif/*CONFIG_DEBUG_POP*/
#endif/*CONFIG_DEBUG_FS*/

struct tool_priv {
    unsigned int normal_always;
    unsigned int reg;
    unsigned int value;
    int codec_soc_clk_cnt;
    int scharge_boost_cnt;
};

/* codec private data */
struct hi6555c_priv {
    struct snd_soc_codec *codec;
    struct hi6555c_jack_data *hs_jack;
    enum hi6555c_jack_states  hs_status;
    enum hi6555c_jack_states  old_hs_status;
    int  hi6555c_pmu_status;
    int pressed_btn_type;
    unsigned short adc_voltage;
    struct wake_lock wake_lock;
    struct clk *codec_clk;
    /* work queue for headset */
    struct workqueue_struct *hs_pi_dwq; /* headset plugin delayed work queue */
    struct delayed_work hs_pi_dw;
    struct workqueue_struct *hs_po_dwq; /* headset plugout delayed work queue */
    struct delayed_work hs_po_dw;
    struct workqueue_struct *hs_comp_l_btn_down_dwq; /* headset button down delayed work queue */
    struct delayed_work hs_comp_l_btn_down_dw;
    struct workqueue_struct *hs_comp_l_btn_up_dwq; /* headset button up delayed work queue */
    struct delayed_work hs_comp_l_btn_up_dw;
    struct workqueue_struct *hs_eco_btn_down_dwq; /* headset eco button down delayed work queue */
    struct delayed_work hs_eco_btn_down_dw;
    struct workqueue_struct *hs_eco_btn_up_dwq; /* headset eco button up delayed work queue */
    struct delayed_work hs_eco_btn_up_dw;
    struct workqueue_struct *hs_comp_h_btn_down_dwq; /* headset button down delayed work queue */
    struct delayed_work hs_comp_h_btn_down_dw;
    struct workqueue_struct *hs_comp_h_btn_up_dwq; /* headset button up delayed work queue */
    struct delayed_work hs_comp_h_btn_up_dw;
    struct workqueue_struct *hs_micbias_hkadc_dwq; /* hs_micbias_hkadc work queue */
    struct delayed_work hs_micbias_hkadc_dw;
    spinlock_t lock;
    struct mutex io_mutex;
    struct mutex ibias_mutex;
    struct mutex hkadc_mutex;
    struct mutex plug_mutex;
    //unsigned int ibias_count;
    unsigned int ibias_work;
    bool ibias_hkadc;
    struct mutex hs_micbias_mutex;
    unsigned int hs_micbias_work;
    bool hs_micbias_hkadc;
    struct hi6555c_headset_voltage *headset_voltage;
    struct hi6555c_btn_voltage *btn_voltage;
    /* gpio intr pin */
    unsigned int gpio_intr_pin;
    int gpio_irq;
    /* power */

    /* add for 6250 by qianli begin*/
    struct regulator    *asp_cfg_regu;
    /* add for 6250 by qianli end*/

    struct regulator *regulator_avdd1v8;/* LDO15 */
    /*  struct regulator *regulator_avddmic; */ /* LD012, controlled by statemachine */
    /*  struct regulator *regulator_dvdd1v8; */ /* LD005, always on */
    struct regulator *regulator_schg_boost3;
    bool use_battery_supply;
    /* clock */
    struct clk* codec_soc;/* periph_clken12_codec_soc */
    struct clk* codec_apb;/* periph_clken1_digacodec */
    struct tool_priv tool_data;
    struct work_struct tool_work;
    unsigned int v_codec_reg[2]; /* virtual codec register on ddr */
    #ifdef CONFIG_DEBUG_FS
    struct dentry *df_dir;        /* debugfs dir*/
    unsigned int rr_cache_idx;       /* write/read index to rr_cache[] */
    struct hi6555c_rr_cache rr_cache[REG_CACHE_NUM_MAX];
    #endif
};

#define HI6555C_HS_INIT_STATUS (0)
#define HI6555C_HS_DETECTING (1<<2)
#define HI6555C_HS_WITH_MIC (1<<0)
#define HI6555C_HS_WITHOUT_MIC (1<<1)

#define IRQ_PLUG_OUT (0x1 << (HI6555C_SMT_ANA_IRQ_MASK_BIT_START + 7))
#define IRQ_PLUG_IN (0x1 << (HI6555C_SMT_ANA_IRQ_MASK_BIT_START + 6))
#define IRQ_ECO_BTN_DOWN (0x1 << (HI6555C_SMT_ANA_IRQ_MASK_BIT_START + 5))
#define IRQ_ECO_BTN_UP (0x1 << (HI6555C_SMT_ANA_IRQ_MASK_BIT_START + 4))
#define IRQ_COMP_L_BTN_DOWN (0x1 << (HI6555C_SMT_ANA_IRQ_MASK_BIT_START + 3))
#define IRQ_COMP_L_BTN_UP (0x1 << (HI6555C_SMT_ANA_IRQ_MASK_BIT_START + 2))
#define IRQ_COMP_H_BTN_DOWN (0x1 << (HI6555C_SMT_ANA_IRQ_MASK_BIT_START + 1))
#define IRQ_COMP_H_BTN_UP (0x1 << (HI6555C_SMT_ANA_IRQ_MASK_BIT_START + 0))

#define IRQ_MSK_COMP_H_BTN (IRQ_COMP_H_BTN_UP | IRQ_COMP_H_BTN_DOWN)
#define IRQ_MSK_BTN_ECO (IRQ_ECO_BTN_UP | IRQ_ECO_BTN_DOWN)
#define IRQ_MSK_BTN_NOR (IRQ_COMP_L_BTN_UP | IRQ_COMP_L_BTN_DOWN | IRQ_MSK_COMP_H_BTN)
#define IRQ_MSK_COMP (IRQ_MSK_BTN_NOR | IRQ_MSK_BTN_ECO)
#define IRQ_MSK_HS_ALL (IRQ_PLUG_OUT | IRQ_PLUG_IN | IRQ_MSK_COMP)

/* 0-earphone not pluged, 1-earphone pluged */
#define IRQ_STAT_PLUG_IN (0x1 << HI6555C_SMT_HS_DET_IRQ_BIT_START)
/* 0-normal btn event    1- no normal btn event */
#define IRQ_STAT_KEY_EVENT (0x1 << HI6555C_SMT_HS_MIC_NOR2_IRQ_BIT_START)
/* 0-eco btn event     1- no eco btn event */
#define IRQ_STAT_ECO_KEY_EVENT (0x1 << HI6555C_SMT_HS_MIC_ECO_IRQ_BIT_START)

#define JACK_RPT_MSK_BTN (SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2)

#ifdef CONFIG_DEBUG_FS
void* g_dump_addr;
unsigned int g_dump_size;
static unsigned int g_vs_reg = INVALID_REG;
#endif

static int hs_plug_out_detect_func(struct snd_soc_codec *codec);
static void hi6555c_enable_ibias(struct snd_soc_codec *codec, bool enable);
static void hi6555c_hs_micbias_work_enable(struct snd_soc_codec *codec, bool enable);
static void hi6555c_ibias_hsmicbias_enable(struct snd_soc_codec *codec, bool enable);
static void hi6555c_hs_micbias_enable(struct snd_soc_codec *codec, bool enable);
static void hi6555c_ibias_work_enable(struct snd_soc_codec *codec, bool enable);
static inline int hi6555c_irq_stat(unsigned int irq_stat_bit);
static inline void hi6555c_irqs_mask_set(unsigned int irqs);
static inline void hi6555c_irqs_clr(unsigned int irqs);
static inline void hi6555c_irqs_mask_clr(unsigned int irqs);

extern int BSP_IPC_IntSend(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);

/*****************************************************************************
*
* CODEC REGISTER OPERATION AREA BEGIN
*
*****************************************************************************/
#ifdef CONFIG_DEBUG_FS
/*
 * record reg write op
 * loop range (0-1023)
 * catch atomic ensured by read/write function
 */
static inline void hi6555c_reg_wr_cache(struct hi6555c_priv *priv, unsigned int reg, int val)
{
    u64 sec = 0;
    unsigned int idx_wr = priv->rr_cache_idx;

    idx_wr %= REG_CACHE_NUM_MAX;
    /* highest 16bit is r/w flag */
    priv->rr_cache[idx_wr].reg = reg | REG_CACHE_FLAG_WRITE;
    priv->rr_cache[idx_wr].val = val;

    sec = hisi_getcurtime();
    do_div(sec, 1000000000);
    priv->rr_cache[idx_wr].time = (unsigned long int)sec;
    idx_wr++;
    priv->rr_cache_idx = idx_wr % REG_CACHE_NUM_MAX;
}

/*
 * record reg read op
 * loop range (0-1023)
 * catch atomic ensured by read/write function
 */
static inline void hi6555c_reg_rd_cache(struct hi6555c_priv *priv, unsigned int reg, unsigned int val)
{
    u64 sec = 0;
    unsigned int idx_wr = priv->rr_cache_idx;

    idx_wr %= REG_CACHE_NUM_MAX;
    /* highest 16bit is r/w flag */
    priv->rr_cache[idx_wr].reg = reg | REG_CACHE_FLAG_READ;
    priv->rr_cache[idx_wr].val = val;

    sec = hisi_getcurtime();
    do_div(sec, 1000000000);
    priv->rr_cache[idx_wr].time = (unsigned long int)sec;
    idx_wr++;
    priv->rr_cache_idx = idx_wr % REG_CACHE_NUM_MAX;
}
#endif /* CONFIG_DEBUG_FS */

static inline unsigned int hi6555c_misc_reg_read(struct hi6555c_priv *priv,unsigned int reg)
{
    unsigned int ret = 0;

    switch (reg) {
    case HI6555C_CLASSD_POWER_IF:
        ret = priv->tool_data.scharge_boost_cnt;
        break;
    case HI6555C_CODEC_SOCCLK_IF:
        ret = priv->tool_data.codec_soc_clk_cnt;
        break;
    case HI6555C_ECO_DISABLE_IF:
        ret = priv->tool_data.normal_always;
        break;
    default:
        loge("reg=%d", reg);
        break;
    }

    logi("%d",ret);
    return ret;
}

static void hi6555c_misc_reg_write(struct work_struct *work)
{
    int ret = 0;
    struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, tool_work);
    unsigned int value = priv->tool_data.value;
    unsigned int reg   = priv->tool_data.reg;

    logi("%d : %d",reg,value);
    switch (reg) {
    case HI6555C_CLASSD_POWER_IF:
        if (HI6555C_ENABLE == value) {
            ret = regulator_enable(priv->regulator_schg_boost3);
            if (0 != ret) {
                loge("regulator_schg_boost3 enable failed!");
            } else {
                priv->tool_data.scharge_boost_cnt = regulator_is_enabled(priv->regulator_schg_boost3);
            }
        } else {
            regulator_disable(priv->regulator_schg_boost3);
            priv->tool_data.scharge_boost_cnt = regulator_is_enabled(priv->regulator_schg_boost3);
        }
        break;
    case HI6555C_CODEC_SOCCLK_IF:
        if (HI6555C_ENABLE == value) {
            clk_prepare_enable(priv->codec_soc);
            priv->tool_data.codec_soc_clk_cnt++;
        } else {
            clk_disable_unprepare(priv->codec_soc);
            priv->tool_data.codec_soc_clk_cnt--;
        }
        break;
    case HI6555C_ECO_DISABLE_IF:
        break;
    default:
        loge("reg=%d value=%d", reg, value);
        break;
    }
}

static unsigned int __hi6555c_reg_read(struct hi6555c_priv *priv, unsigned int reg)
{
    volatile unsigned int ret = 0;
    unsigned int reg_type = 0, reg_value = 0;
    unsigned long flags = 0;

    reg_type  = reg & PAGE_TYPE_MASK;
    reg_value = reg & PAGE_VALUE_MASK;

    if (STATUS_ERROR == priv->hi6555c_pmu_status) {
        loge("Hi6555c version is wrong,return invaled value\n");
        ret = INVALID_REG_VALUE;
        return ret;
    }

    spin_lock_irqsave(&priv->lock, flags);

    if (PAGE_SoCCODEC == reg_type) {
        /* SOC part */
        ret = readl(g_hi6555c_socodec_base_addr + reg_value);
        logi("PAGE_SoCCODEC == reg_type, reg_value = 0x%x, ret = 0x%x\n", reg_value, ret);
    } else if (PAGE_SmartStarCODEC == reg_type) {
        /* SMARTSTAR part */
        ret = readl(g_hi6555c_reg_base_addr + (reg_value << 2));
        logi("PAGE_SmartStarCODEC == reg_type, reg_value = 0x%x, ret = 0x%x\n", reg_value, ret);
    } else if (PAGE_SmartStarHKADC == reg_type) {
        /* SMARTSTAR HKADC */
        //ret = readl(g_hi6555c_hkadc_reg_base_addr + (reg_value << 2));
        logi("PAGE_SmartStarHKADC == reg_type, reg_value = 0x%x, ret = 0x%x\n", reg_value, ret);
    } else if (PAGE_PeriSCTRL == reg_type) {
        /* Peri SCTRL */
        //ret = phy_reg_readl(SOC_PERI_SCTRL_BASE_ADDR, reg_value, 0, 31);
        ret = readl(g_hi6555c_psctrl_base_addr+reg_value);
        logi("PAGE_PeriSCTRL == reg_type, reg_value = 0x%x, ret = 0x%x\n", reg_value, ret);
    } else if (PAGE_PMCTRL == reg_type) {
        /* PMCTRL */
        //todo fixme: ret = hi6xxx_pmic_reg_read(reg_value);
        ret = readl(g_hi6555c_reg_base_addr + (reg_value << 2));
        logi("PAGE_PMCTRL == reg_type, reg_value = 0x%x, ret = 0x%x\n", reg_value, ret);
    } else if (PAGE_VIRCODEC == reg_type) {
        /* PMCTRL */
        ret = priv->v_codec_reg[reg_value];
        logi("PAGE_VIRCODEC == reg_type, reg_value = 0x%x, ret = 0x%x\n", reg_value, ret);
    } else if (PAGE_MISCCODEC == reg_type) {
        /* misc */
        ret = hi6555c_misc_reg_read(priv,reg_value);
        logi("PAGE_MISCCODEC == reg_type, reg_value = 0x%x, ret = 0x%x\n", reg_value, ret);
    }else if (PAGE_ASPCFG == reg_type) {
        /* ASP CFG */
        ret = readl(g_hi6555c_aspcfg_base_addr+reg_value);
        logi("PAGE_ASPCFG == reg_type, reg_value = 0x%x, ret = 0x%x\n", reg_value, ret);
    }else if (PAGE_AO_IOC == reg_type) {
        /* AO_IOC */
        ret = readl(g_hi6555c_aoioc_base_addr+reg_value);
        logi("PAGE_AO_IOC == reg_type, reg_value = 0x%x, ret = 0x%x\n", reg_value, ret);
    }else if (PAGE_IOC == reg_type) {
        /* IOC */
        ret = readl(g_hi6555c_ioc_base_addr+reg_value);
        logi("PAGE_IOC == reg_type, reg_value = 0x%x, ret = 0x%x\n", reg_value, ret);
    }else if (PAGE_GPIO21 == reg_type) {
        /* GPIO21 */
        ret = readl(g_hi6555c_gpio21_base_addr+reg_value);
        logi("PAGE_GPIO21 == reg_type, reg_value = 0x%x, ret = 0x%x\n", reg_value, ret);
    } else if (PAGE_PERICRG == reg_type) {
        /* PERICRG */
        ret = readl(g_hi6555c_pericrg_base_addr  + reg_value);
        logi("PAGE_GPIO21 == reg_type, reg_value = 0x%x, ret = 0x%x\n", reg_value, ret);
    } else {
        loge("reg=0x%x\n", reg);
        ret = INVALID_REG_VALUE;
    }

#ifdef CONFIG_DEBUG_FS
    /* record reg */
    #if 0
    hi6555c_reg_rd_cache(priv, reg, ret);
    #endif
#endif
    spin_unlock_irqrestore(&priv->lock, flags);

    return ret;
}

static void __hi6555c_reg_write(struct hi6555c_priv *priv, unsigned int reg, unsigned int value)
{
    unsigned int reg_type = 0, reg_value = 0;
    unsigned long flags = 0;

    reg_type  = reg & PAGE_TYPE_MASK;
    reg_value = reg & PAGE_VALUE_MASK;

    if (STATUS_ERROR == priv->hi6555c_pmu_status) {
        logd("Hi6555c version is wrong");
        return;
    }

    spin_lock_irqsave(&priv->lock, flags);

#ifdef CONFIG_DEBUG_FS
    /*record reg*/
    hi6555c_reg_wr_cache(priv, reg, value);
#endif

    if(PAGE_SoCCODEC == reg_type) {
        /* SOC part */
        logi("PAGE_SoCCODEC == reg_type, reg_value = 0x%x, value = 0x%x\n", reg_value, value);
        writel(value, g_hi6555c_socodec_base_addr + reg_value);
    } else if (PAGE_SmartStarCODEC == reg_type) {
        /* SMARTSTAR part */
        logi("PAGE_SmartStarCODEC == reg_type, reg_value = 0x%x, value = 0x%x\n", reg_value, value);
        writel(value, g_hi6555c_reg_base_addr + (reg_value << 2));
    } else if (PAGE_SmartStarHKADC == reg_type) {
        /* SMARTSTAR HKADC */
        logi("PAGE_SmartStarHKADC == reg_type, reg_value = 0x%x, value = 0x%x\n", reg_value, value);
        // writel(value, g_hi6555c_hkadc_reg_base_addr + (reg_value << 2));
    } else if (PAGE_PeriSCTRL == reg_type) {
        /* Peri SCTRL */
        logi("PAGE_PeriSCTRL == reg_type, reg_value = 0x%x, value = 0x%x\n", reg_value, value);
        //phy_reg_writel(SOC_PERI_SCTRL_BASE_ADDR, reg_value, 0, 31, value);
        writel(value,g_hi6555c_psctrl_base_addr+reg_value);
    } else if (PAGE_PMCTRL == reg_type) {
        /* PMCTRL */
        logi("PAGE_PMCTRL == reg_type, reg_value = 0x%x, value = 0x%x\n", reg_value, value);
        //todo fixme: hi6xxx_pmic_reg_write(reg_value, value);
        writel(value, g_hi6555c_reg_base_addr + (reg_value << 2));
    } else if (PAGE_VIRCODEC == reg_type) {
        /* PMCTRL */
        logi("PAGE_VIRCODEC == reg_type, reg_value = 0x%x, value = 0x%x\n", reg_value, value);
        priv->v_codec_reg[reg_value] = value;
    } else if (PAGE_MISCCODEC == reg_type) {
        /* misc */
        logi("PAGE_MISCCODEC == reg_type, reg_value = 0x%x, value = 0x%x\n", reg_value, value);
        priv->tool_data.reg   = reg_value;
        priv->tool_data.value = value;
        schedule_work(&priv->tool_work);
    } else if (PAGE_ASPCFG == reg_type) {
        /* ASP CFG */
        logi("PAGE_ASPCFG == reg_type, reg_value = 0x%x, value = 0x%x\n", reg_value, value);
        writel(value,g_hi6555c_aspcfg_base_addr+reg_value);
    } else if (PAGE_AO_IOC == reg_type) {
        /* AO_IOC */
        logi("PAGE_AO_IOC == reg_type, reg_value = 0x%x, value = 0x%x\n", reg_value, value);
        writel(value,g_hi6555c_aoioc_base_addr+reg_value);
    } else if (PAGE_IOC == reg_type) {
        /* IOC */
        logi("PAGE_IOC == reg_type, reg_value = 0x%x, value = 0x%x\n", reg_value, value);
        writel(value,g_hi6555c_ioc_base_addr+reg_value);
    } else if (PAGE_GPIO21 == reg_type) {
        /* GPIO21 */
        logi("PAGE_GPIO21 == reg_type, reg_value = 0x%x, value = 0x%x\n", reg_value, value);
        writel(value,g_hi6555c_gpio21_base_addr+reg_value);
    } else if (PAGE_PERICRG == reg_type) {
        /* GPIO21 */
        logi("PAGE_PERIREG == reg_type, reg_value = 0x%x, value = 0x%x\n", reg_value, value);
        writel(value, g_hi6555c_pericrg_base_addr + reg_value);
    } else {
        loge("reg=0x%x, value=0x%x\n", reg, value);
    }

    spin_unlock_irqrestore(&priv->lock, flags);
}

static inline unsigned int hi6555c_reg_read(struct snd_soc_codec *codec, unsigned int reg)
{
    volatile unsigned int ret = 0;
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

    if  (!priv) {
        loge("priv is null\n");
        return -1;
    }

    ret = __hi6555c_reg_read(priv, reg);

    return ret;
}

static inline int hi6555c_reg_write(struct snd_soc_codec *codec, unsigned int reg, unsigned int value)
{
    int ret = 0;
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

    if (!priv) {
        loge("priv is null\n");
        return -1;
    }

    __hi6555c_reg_write(priv, reg, value);

    return ret;
}

/*
 * value:set by bits
 */
static void hi6555c_set_reg_bits(unsigned int reg, unsigned int value)
{
    unsigned int val = 0;

    val = hi6555c_reg_read(g_codec, reg) | (value);
    hi6555c_reg_write(g_codec, reg, val);
}

/*
 * value:clear by bits
 */
static void hi6555c_clr_reg_bits(unsigned int reg, unsigned int value)
{
    unsigned int val = 0;

    val = hi6555c_reg_read(g_codec, reg) & ~(value);
    hi6555c_reg_write(g_codec, reg, val);
}

/* provide to tools use only
 *  reg : high 16bit(type) + low 16bit(reg)
 */
unsigned int codec_reg_read(unsigned int reg)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(g_codec);

    if (!priv) {
        loge("priv is null\n");
        return INVALID_REG_VALUE;
    }

       /* working then delay entering eco mode */
       //mod_timer(&priv->timer,jiffies + ECO_MODE_ENTRY_TIME_SEC * HZ);

    return __hi6555c_reg_read(priv, reg);
}

/* provide to tools use only */
void codec_reg_write(unsigned int reg, unsigned int value)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(g_codec);

    if (!priv) {
        loge("priv is null\n");
        return;
    }

    __hi6555c_reg_write(priv, reg, value);

    /* working then delay entering eco mode */
    //mod_timer(&priv->timer, jiffies + ECO_MODE_ENTRY_TIME_SEC * HZ);
}
/*****************************************************************************
*
* CODEC REGISTER OPERATION AREA END
*
*****************************************************************************/


/*****************************************************************************
*
* CONTROL WIDGET AREA BEGIN
*
*****************************************************************************/

/*****************************************************************************
  Sound Controls
*****************************************************************************/
/* LINEPGAL GAIN(LINEPGAL_GAIN<3:0>)£»
 * range:-14dB~16dB¡£
 * step:2dB¡£
 * 0000:-14dB£»
 * 0001:-12dB£»
 * 0010:-10dB£»
 * ¡­¡­
 * 0111:0dB£»
 * ¡­¡­
 * 1110:14dB£»
 * 1111:16dB£» */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_linepgal_gain_tlv, -1400, 200, 0);

/* LINEPGAR GAIN(LINEPGAR_GAIN<3:0>)£»
 * range:-14dB~16dB¡£
 * step:2dB¡£
 * 0000:-14dB£»
 * 0001:-12dB£»
 * 0010:-10dB£»
 * ¡­¡­
 * 0111:0dB£»
 * ¡­¡­
 * 1110:14dB£»
 * 1111:16dB£» */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_linepgar_gain_tlv, -1400, 200, 0);

/* AUXPGA GAIN(AUXPGA_GAIN<2:0>)£»
 * range:0dB~14dB¡£
 * step:2dB¡£
 * 000: 0dB£»
 * 001: 2dB£»
 * 010: 4dB£»
 * 011: 6dB£»
 * 100: 8dB£»
 * 101: 10dB£»
 * 110: 12dB£»
 * 111: 14dB£» */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_auxpga_gain_tlv, 0, 200, 0);

/* MAINPGA GAIN(MAINPGA_GAIN<2:0>)£»
 * range:0dB~14dB¡£
 * step:2dB¡£
 * 000: 0dB£»
 * 001: 2dB£»
 * 010: 4dB£»
 * 011: 6dB£»
 * 100: 8dB£»
 * 101: 10dB£»
 * 110: 12dB£»
 * 111: 14dB£» */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_mainpga_gain_tlv, 0, 200, 0);

/* HeadphoneL GAIN(HSL_GAIN<3:0>)£»
 * range:-20dB~-0dB¡£
 * step:1.5dB¡£
 * 0000:-20dB£»
 * 0001:-18dB£»
 * 0010:-16.5dB£»
 * 0011: -15dB;
 * 0100:-13.5dB;
 * 0101:-12dB;
 * 0110:-10.5dB;
 * 0111:-9.5dB;
 * 1000:-8.5dB;
 * 1001:-7.5dB;
 * 1010:-6.5dB;
 * 1011:-5.5dB;
 * 1100:-4.5dB;
 * 1101:-3dB;
 * 1110:-1.5dB;
 * 1111:0dB; */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_hsl_gain_tlv, -2000, 150, 0);

/* HeadphoneR GAIN(HSR_GAIN<3:0>)£»
 * range:-20dB~-0dB¡£
 * step:1.5dB¡£
 * 0000:-20dB£»
 * 0001:-18dB£»
 * 0010:-16.5dB£»
 * 0011: -15dB;
 * 0100:-13.5dB;
 * 0101:-12dB;
 * 0110:-10.5dB;
 * 0111:-9.5dB;
 * 1000:-8.5dB;
 * 1001:-7.5dB;
 * 1010:-6.5dB;
 * 1011:-5.5dB;
 * 1100:-4.5dB;
 * 1101:-3dB;
 * 1110:-1.5dB;
 * 1111:0dB; */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_hsr_gain_tlv, -2000, 150, 0);

/* EAR GAIN(EAR_GAIN<5:0>)£»
 * range:-20dB~-6dB¡£
 * step:2dB¡£
 * 0000:-20dB£»
 * 0001:-18dB£»
 * 0010:-16dB£»
 * 0011: -14dB;
 * 0100:-12dB;
 * 0101:-10dB;
 * 0110:-8dB;
 * 0111:-6dB;
 * 1000:-4dB;
 * 1001:-2dB;
 * 1010:-0dB;
 * 1011:2dB;
 * 1100:4dB;
 * 1101:6dB;
 * orther: mute */
static DECLARE_TLV_DB_SCALE(hi6555c_smt_ear_gain_tlv, -2000, 200, 0);

static const struct snd_kcontrol_new hi6555c_snd_controls[] = {
    SOC_SINGLE("HISSC_DACL_HBF1I_EN",
        HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, HI6555C_DACL_HBF1I_EN_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DACL_HBF2I_EN",
        HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, HI6555C_DACL_HBF2I_EN_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DACR_HBF1I_EN",
        HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, HI6555C_DACR_HBF1I_EN_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DACR_HBF2I_EN",
        HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, HI6555C_DACR_HBF2I_EN_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_FS_VOICE_DLINK",
        HI6555C_FS_CFG_ADDR, HI6555C_FS_VOICE_DLINK_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_FS_STEREO_DLINK_L",
        HI6555C_FS_CFG_ADDR, HI6555C_FS_STEREO_DLINK_L_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_FS_STEREO_DLINK_R",
        HI6555C_FS_CFG_ADDR, HI6555C_FS_STEREO_DLINK_R_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_FS_DACLR",
        HI6555C_FS_CFG_ADDR, HI6555C_FS_DACLR_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_FS_ADCLR",
        HI6555C_FS_CFG_ADDR, HI6555C_FS_ADCLR_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_FS_S1",
        HI6555C_FS_CFG_ADDR, HI6555C_FS_S1_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_FS_S2",
        HI6555C_FS_CFG_ADDR, HI6555C_FS_S2_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_S1_FUNC_MODE",
        HI6555C_I2S_CFG_ADDR, HI6555C_S1_FUNC_MODE_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_S1_CODEC_DATA_FORMAT",
        HI6555C_I2S_CFG_ADDR, HI6555C_S1_CODEC_DATA_FORMAT_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S1_RX_CLK_SEL",
        HI6555C_I2S_CFG_ADDR, HI6555C_S1_RX_CLK_SEL_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S1_TX_CLK_SEL",
        HI6555C_I2S_CFG_ADDR, HI6555C_S1_TX_CLK_SEL_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S1_DIRECT_LOOP",
        HI6555C_I2S_CFG_ADDR, HI6555C_S1_DIRECT_LOOP_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_S1_CODEC_IO_WORDLENGTH",
        HI6555C_I2S_CFG_ADDR, HI6555C_S1_CODEC_IO_WORDLENGTH_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_S1_CHNNL_MODE",
        HI6555C_I2S_CFG_ADDR, HI6555C_S1_CHNNL_MODE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S1_LRCLK_MODE",
        HI6555C_I2S_CFG_ADDR, HI6555C_S1_LRCLK_MODE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S1_MST_SLV",
        HI6555C_I2S_CFG_ADDR, HI6555C_S1_MST_SLV_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S1_FRAME_MODE",
        HI6555C_I2S_CFG_ADDR, HI6555C_S1_FRAME_MODE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_FUNC_MODE",
        HI6555C_I2S_CFG_ADDR, HI6555C_S2_FUNC_MODE_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_S2_CODEC_DATA_FORMAT",
        HI6555C_I2S_CFG_ADDR, HI6555C_S2_CODEC_DATA_FORMAT_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_RX_CLK_SEL",
        HI6555C_I2S_CFG_ADDR, HI6555C_S2_RX_CLK_SEL_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_TX_CLK_SEL",
        HI6555C_I2S_CFG_ADDR, HI6555C_S2_TX_CLK_SEL_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_DIRECT_LOOP",
        HI6555C_I2S_CFG_ADDR, HI6555C_S2_DIRECT_LOOP_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_S2_CODEC_IO_WORDLENGTH",
        HI6555C_I2S_CFG_ADDR, HI6555C_S2_CODEC_IO_WORDLENGTH_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_S2_CHNNL_MODE",
        HI6555C_I2S_CFG_ADDR, HI6555C_S2_CHNNL_MODE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_LRCLK_MODE",
        HI6555C_I2S_CFG_ADDR, HI6555C_S2_LRCLK_MODE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_MST_SLV",
        HI6555C_I2S_CFG_ADDR, HI6555C_S2_MST_SLV_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_FRAME_MODE",
        HI6555C_I2S_CFG_ADDR, HI6555C_S2_FRAME_MODE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DACL_MIXER_GAIN",
        HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACL_MIXER_GAIN_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_MIXER_GAIN",
        HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACR_MIXER_GAIN_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_VOICE_DLINK_SRC_MODE",
        HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_VOICE_DLINK_SRC_MODE_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_VOICE_DLINK_SRC_RDY",
        HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_VOICE_DLINK_SRC_RDY_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_OL_SRC_MODE",
        HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_S2_OL_SRC_MODE_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_S2_OL_SRC_RDY",
        HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_S2_OL_SRC_RDY_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_OL_MIXER_GAIN",
        HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_S2_OL_MIXER_GAIN_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_VOICE_DLINK_MIXER_GAIN",
        HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_VOICE_DLINK_MIXER_GAIN_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_ADCL_PGA_INTEGER_CONFIG",
        HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCL_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

    SOC_SINGLE("HISSC_ADCL_PGA_FRAC_CONFIG",
        HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCL_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_ADCL_PGA_MUTE",
        HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCL_PGA_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_ADCL_PGA_THR_CONFIG",
        HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCL_PGA_THR_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_ADCR_PGA_INTEGER_CONFIG",
        HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCR_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

    SOC_SINGLE("HISSC_ADCR_PGA_FRAC_CONFIG",
        HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCR_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_ADCR_PGA_MUTE",
        HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCR_PGA_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_ADCR_PGA_THR_CONFIG",
        HI6555C_ADC_PGA_CFG_ADDR, HI6555C_ADCR_PGA_THR_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_S1_IL_PGA_INTEGER_CONFIG",
        HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IL_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

    SOC_SINGLE("HISSC_S1_IL_PGA_FRAC_CONFIG",
        HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IL_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S1_IL_PGA_MUTE",
        HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IL_PGA_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S1_IL_PGA_THR_CONFIG",
        HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IL_PGA_THR_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_S1_IR_PGA_INTEGER_CONFIG",
        HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IR_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

    SOC_SINGLE("HISSC_S1_IR_PGA_FRAC_CONFIG",
        HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IR_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S1_IR_PGA_MUTE",
        HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IR_PGA_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S1_IR_PGA_THR_CONFIG",
        HI6555C_S1_INPUT_PGA_CFG_ADDR, HI6555C_S1_IR_PGA_THR_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_S2_IL_PGA_INTEGER_CONFIG",
        HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IL_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

    SOC_SINGLE("HISSC_S2_IL_PGA_FRAC_CONFIG",
        HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IL_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_IL_PGA_MUTE",
        HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IL_PGA_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_IL_PGA_THR_CONFIG",
        HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IL_PGA_THR_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_S2_IR_PGA_INTEGER_CONFIG",
        HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IR_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

    SOC_SINGLE("HISSC_S2_IR_PGA_FRAC_CONFIG",
        HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IR_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_IR_PGA_MUTE",
        HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IR_PGA_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_IR_PGA_THR_CONFIG",
        HI6555C_S2_INPUT_PGA_CFG_ADDR, HI6555C_S2_IR_PGA_THR_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_STEREO_DLINK_L_PGA_INTEGER_CONFIG",
        HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_L_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

    SOC_SINGLE("HISSC_STEREO_DLINK_L_PGA_FRAC_CONFIG",
        HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_L_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_STEREO_DLINK_L_PGA_MUTE",
        HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_L_PGA_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_STEREO_DLINK_L_PGA_THR_CONFIG",
        HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_L_PGA_THR_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_STEREO_DLINK_R_PGA_INTEGER_CONFIG",
        HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_R_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

    SOC_SINGLE("HISSC_STEREO_DLINK_R_PGA_FRAC_CONFIG",
        HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_R_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_STEREO_DLINK_R_PGA_MUTE",
        HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_R_PGA_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_STEREO_DLINK_R_PGA_THR_CONFIG",
        HI6555C_STEREO_DLINK_PGA_CFG_ADDR, HI6555C_STEREO_DLINK_R_PGA_THR_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_VOICE_DLINK_PGA_INTEGER_CONFIG",
        HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_VOICE_DLINK_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

    SOC_SINGLE("HISSC_VOICE_DLINK_PGA_FRAC_CONFIG",
        HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_VOICE_DLINK_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_VOICE_DLINK_PGA_MUTE",
        HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_VOICE_DLINK_PGA_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_VOICE_DLINK_PGA_THR_CONFIG",
        HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_VOICE_DLINK_PGA_THR_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_SIDETONE_PGA_INTEGER_CONFIG",
        HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_SIDETONE_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

    SOC_SINGLE("HISSC_SIDETONE_PGA_FRAC_CONFIG",
        HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_SIDETONE_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SIDETONE_PGA_MUTE",
        HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_SIDETONE_PGA_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SIDETONE_PGA_THR_CONFIG",
        HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, HI6555C_SIDETONE_PGA_THR_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_VOICE_DLINK_FIFO_AFULL_TH",
        HI6555C_APB_AFIFO_CFG_2_ADDR, HI6555C_VOICE_DLINK_FIFO_AFULL_TH_BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC_VOICE_DLINK_FIFO_AEMPTY_TH",
        HI6555C_APB_AFIFO_CFG_2_ADDR, HI6555C_VOICE_DLINK_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC_STEREO_DLINK_L_FIFO_AFULL_TH",
        HI6555C_STEREO_DLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_DLINK_L_FIFO_AFULL_TH_BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC_STEREO_DLINK_L_FIFO_AEMPTY_TH",
        HI6555C_STEREO_DLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_DLINK_L_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC_STEREO_DLINK_R_FIFO_AFULL_TH",
        HI6555C_STEREO_DLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_DLINK_R_FIFO_AFULL_TH_BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC_STEREO_DLINK_R_FIFO_AEMPTY_TH",
        HI6555C_STEREO_DLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_DLINK_R_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC_STEREO_UPLINK_L_FIFO_AFULL_TH",
        HI6555C_STEREO_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_UPLINK_L_FIFO_AFULL_TH_BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC_STEREO_UPLINK_L_FIFO_AEMPTY_TH",
        HI6555C_STEREO_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_UPLINK_L_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC_STEREO_UPLINK_R_FIFO_AFULL_TH",
        HI6555C_STEREO_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_UPLINK_R_FIFO_AFULL_TH_BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC_STEREO_UPLINK_R_FIFO_AEMPTY_TH",
        HI6555C_STEREO_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_STEREO_UPLINK_R_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC_VOICE_UPLINK_L_FIFO_AFULL_TH",
        HI6555C_VOICE_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_VOICE_UPLINK_L_FIFO_AFULL_TH_BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC_VOICE_UPLINK_L_FIFO_AEMPTY_TH",
        HI6555C_VOICE_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_VOICE_UPLINK_L_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC___B0___LEFT___",
        HI6555C_VOICE_UPLINK_FIFO_TH_CFG_ADDR, HI6555C___B0___LEFT____BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC_VOICE_UPLINK_R_FIFO_AEMPTY_TH",
        HI6555C_VOICE_UPLINK_FIFO_TH_CFG_ADDR, HI6555C_VOICE_UPLINK_R_FIFO_AEMPTY_TH_BIT_START, 0x1F, 0),

    SOC_SINGLE("HISSC_DACL_AGC_GWIN_CONFIG",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_GWIN_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_LEVELLOW_CONFIG",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_LEVELLOW_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_GSTEPD_CONFIG",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_GSTEPD_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_TIMEMUTE_CONFIG",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_TIMEMUTE_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_NGW_CONFIG",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_NGW_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_YTARGET_CONFIG",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_YTARGET_CONFIG_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_DACL_AGC_T_AMIN_CONFIG",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_T_AMIN_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_GSUPPRESS",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_GSUPPRESS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DACL_AGC_KFSLOW",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_KFSLOW_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_KFRAPID",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_KFRAPID_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_NGL_CONFIG",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_NGL_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_NGH_CONFIG",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_NGH_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_TIMER",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_TIMER_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_DACL_AGC_NGI_CONFIG",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_NGI_CONFIG_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_DACL_AGC_TIMENNG_CONFIG",
        HI6555C_DACL_AGC_CFG_1_ADDR, HI6555C_DACL_AGC_TIMENNG_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_TIMEDECAY_CONFIG",
        HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_TIMEDECAY_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_TIMEGHOLD_CONFIG",
        HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_TIMEGHOLD_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_GMUTE_CONFIG",
        HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_GMUTE_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACL_AGC_MUTE_BYPASS",
        HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_MUTE_BYPASS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DACL_AGC_BYPASS",
        HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_BYPASS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DACL_AGC_USR_GDB_INTEGER",
        HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_USR_GDB_INTEGER_BIT_START, 0xFF, 0),

    SOC_SINGLE("HISSC_DACL_AGC_USR_GDB_FRAC",
        HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_USR_GDB_FRAC_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DACL_AGC_SW_CLR",
        HI6555C_DACL_AGC_CFG_2_ADDR, HI6555C_DACL_AGC_SW_CLR_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DACR_AGC_GWIN_CONFIG",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_GWIN_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_LEVELLOW_CONFIG",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_LEVELLOW_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_GSTEPD_CONFIG",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_GSTEPD_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_TIMEMUTE_CONFIG",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_TIMEMUTE_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_NGW_CONFIG",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_NGW_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_YTARGET_CONFIG",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_YTARGET_CONFIG_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_DACR_AGC_T_AMIN_CONFIG",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_T_AMIN_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_GSUPPRESS",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_GSUPPRESS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DACR_AGC_KFSLOW",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_KFSLOW_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_KFRAPID",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_KFRAPID_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_NGL_CONFIG",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_NGL_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_NGH_CONFIG",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_NGH_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_TIMER",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_TIMER_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_DACR_AGC_NGI_CONFIG",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_NGI_CONFIG_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_DACR_AGC_TIMENNG_CONFIG",
        HI6555C_DACR_AGC_CFG_1_ADDR, HI6555C_DACR_AGC_TIMENNG_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_TIMEDECAY_CONFIG",
        HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_TIMEDECAY_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_TIMEGHOLD_CONFIG",
        HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_TIMEGHOLD_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_GMUTE_CONFIG",
        HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_GMUTE_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_DACR_AGC_MUTE_BYPASS",
        HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_MUTE_BYPASS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DACR_AGC_BYPASS",
        HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_BYPASS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DACR_AGC_USR_GDB_INTEGER",
        HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_USR_GDB_INTEGER_BIT_START, 0xFF, 0),

    SOC_SINGLE("HISSC_DACR_AGC_USR_GDB_FRAC",
        HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_USR_GDB_FRAC_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DACR_AGC_SW_CLR",
        HI6555C_DACR_AGC_CFG_2_ADDR, HI6555C_DACR_AGC_SW_CLR_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SIF_EDGE_SEL",
        HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_SIF_EDGE_SEL_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SW_DMIC_MODE",
        HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_SW_DMIC_MODE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_DMIC_REVERSE",
        HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_DMIC_REVERSE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_FS_DMIC",
        HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_FS_DMIC_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_VOICE_DLINK_SRC_UP_DOUT_VLD_SEL",
        HI6555C_MISC_CFG_ADDR, HI6555C_VOICE_DLINK_SRC_UP_DOUT_VLD_SEL_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S3_FUNC_MODE",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_FUNC_MODE_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_S3_CODEC_DATA_FORMAT",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_CODEC_DATA_FORMAT_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S3_RX_CLK_SEL",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_RX_CLK_SEL_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S3_TX_CLK_SEL",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_TX_CLK_SEL_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S3_DIRECT_LOOP",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_DIRECT_LOOP_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_S3_CODEC_IO_WORDLENGTH",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_CODEC_IO_WORDLENGTH_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_S3_CHNNL_MODE",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_CHNNL_MODE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S3_LRCLK_MODE",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_LRCLK_MODE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S3_MST_SLV",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_MST_SLV_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S3_FRAME_MODE",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_S3_FRAME_MODE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_FS_S3",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_FS_S3_BIT_START, 0x7, 0),

    SOC_SINGLE("HISSC_THIRDMD_DLINK_PGA_INTEGER_CONFIG",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_THIRDMD_DLINK_PGA_INTEGER_CONFIG_BIT_START, 0xFF, 0),

    SOC_SINGLE("HISSC_THIRDMD_DLINK_PGA_FRAC_CONFIG",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_THIRDMD_DLINK_PGA_FRAC_CONFIG_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_THIRDMD_DLINK_PGA_MUTE",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_THIRDMD_DLINK_PGA_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_THIRDMD_DLINK_PGA_THR_CONFIG",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR, HI6555C_THIRDMD_DLINK_PGA_THR_CONFIG_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_EXTERNAL_12288K_SEL",
        HI6555C_CLK_SEL_ADDR, HI6555C_EXTERNAL_12288K_SEL_BIT_START, 0x2, 0),

    SOC_SINGLE("HISSC_SMT_DACL_CLK_EDGE_SEL",
        HI6555C_SMT_CLK_EDGE_CFG_ADDR, HI6555C_SMT_DACL_CLK_EDGE_SEL_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_DACR_CLK_EDGE_SEL",
        HI6555C_SMT_CLK_EDGE_CFG_ADDR, HI6555C_SMT_DACR_CLK_EDGE_SEL_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_ADCL_CLK_EDGE_SEL",
        HI6555C_SMT_CLK_EDGE_CFG_ADDR, HI6555C_SMT_ADCL_CLK_EDGE_SEL_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_ADCR_CLK_EDGE_SEL",
        HI6555C_SMT_CLK_EDGE_CFG_ADDR, HI6555C_SMT_ADCR_CLK_EDGE_SEL_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_DAC_LOOPBACK",
        HI6555C_SMT_LOOPBACK_CFG_ADDR, HI6555C_SMT_DAC_LOOPBACK_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_ADC_LOOPBACK",
        HI6555C_SMT_LOOPBACK_CFG_ADDR, HI6555C_SMT_ADC_LOOPBACK_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_LINEPGAL_MUTE",
        HI6555C_SMT_CODEC_ANA_RW05_ADDR, HI6555C_SMT_LINEPGAL_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE_TLV("HISSC_SMT_LINEPGAL_GAIN",
        HI6555C_SMT_CODEC_ANA_RW05_ADDR, HI6555C_SMT_LINEPGAL_GAIN_BIT_START, 0xF, 0,
        hi6555c_smt_linepgal_gain_tlv),

    SOC_SINGLE("HISSC_SMT_LINEPGAL_SEL",
        HI6555C_SMT_CODEC_ANA_RW05_ADDR, HI6555C_SMT_LINEPGAL_SEL_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_SMT_LINEPGAR_MUTE",
        HI6555C_SMT_CODEC_ANA_RW06_ADDR, HI6555C_SMT_LINEPGAR_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE_TLV("HISSC_SMT_LINEPGAR_GAIN",
        HI6555C_SMT_CODEC_ANA_RW06_ADDR, HI6555C_SMT_LINEPGAR_GAIN_BIT_START, 0xF, 0,
        hi6555c_smt_linepgar_gain_tlv),

    SOC_SINGLE("HISSC_SMT_LINEPGAR_SEL",
        HI6555C_SMT_CODEC_ANA_RW06_ADDR, HI6555C_SMT_LINEPGAR_SEL_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_SMT_AUXPGA_SEL",
        HI6555C_SMT_CODEC_ANA_RW07_ADDR, HI6555C_SMT_AUXPGA_SEL_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_SMT_AUXPGA_MUTE",
        HI6555C_SMT_CODEC_ANA_RW07_ADDR, HI6555C_SMT_AUXPGA_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE_TLV("HISSC_SMT_AUXPGA_GAIN",
        HI6555C_SMT_CODEC_ANA_RW07_ADDR, HI6555C_SMT_AUXPGA_GAIN_BIT_START, 0x7, 0,
        hi6555c_smt_auxpga_gain_tlv),

    SOC_SINGLE("HISSC_SMT_AUXPGA_BOOST",
        HI6555C_SMT_CODEC_ANA_RW07_ADDR, HI6555C_SMT_AUXPGA_BOOST_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_MAINPGA_MUTE",
        HI6555C_SMT_CODEC_ANA_RW08_ADDR, HI6555C_SMT_MAINPGA_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE_TLV("HISSC_SMT_MAINPGA_GAIN",
        HI6555C_SMT_CODEC_ANA_RW08_ADDR, HI6555C_SMT_MAINPGA_GAIN_BIT_START, 0x7, 0,
        hi6555c_smt_mainpga_gain_tlv),

    SOC_SINGLE("HISSC_SMT_MAINPGA_BOOST",
        HI6555C_SMT_CODEC_ANA_RW08_ADDR, HI6555C_SMT_MAINPGA_BOOST_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_ADCL_DWA_BPS",
        HI6555C_SMT_CODEC_ANA_RW11_ADDR, HI6555C_SMT_ADCL_DWA_BPS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_ADCL_FLSTN",
        HI6555C_SMT_CODEC_ANA_RW11_ADDR, HI6555C_SMT_ADCL_FLSTN_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_SMT_ADCL_DAC_BIAS",
        HI6555C_SMT_CODEC_ANA_RW11_ADDR, HI6555C_SMT_ADCL_DAC_BIAS_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_SMT_ADCL_CLK_DELAY_0",
        HI6555C_SMT_CODEC_ANA_RW11_ADDR, HI6555C_SMT_ADCL_CLK_DELAY_0_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_ADCL_CLK_DELAY_1",
        HI6555C_SMT_CODEC_ANA_RW11_ADDR, HI6555C_SMT_ADCL_CLK_DELAY_1_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_ADCR_DWA_BPS",
        HI6555C_SMT_CODEC_ANA_RW12_ADDR, HI6555C_SMT_ADCR_DWA_BPS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_ADCR_FLSTN",
        HI6555C_SMT_CODEC_ANA_RW12_ADDR, HI6555C_SMT_ADCR_FLSTN_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_SMT_ADCR_DAC_BIAS",
        HI6555C_SMT_CODEC_ANA_RW12_ADDR, HI6555C_SMT_ADCR_DAC_BIAS_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_SMT_ADCR_CLK_DELAY_0",
        HI6555C_SMT_CODEC_ANA_RW12_ADDR, HI6555C_SMT_ADCR_CLK_DELAY_0_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_ADCR_CLK_DELAY_1",
        HI6555C_SMT_CODEC_ANA_RW12_ADDR, HI6555C_SMT_ADCR_CLK_DELAY_1_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_ADCR_CLK_DELAY_2",
        HI6555C_SMT_CODEC_ANA_RW12_ADDR, HI6555C_SMT_ADCR_CLK_DELAY_2_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_HSL_MIN_GAIN",
        HI6555C_SMT_CODEC_ANA_RW17_ADDR, HI6555C_SMT_HSL_MIN_GAIN_BIT_START, 0x1, 0),

    SOC_SINGLE_TLV("HISSC_SMT_HSL_GAIN",
        HI6555C_SMT_CODEC_ANA_RW17_ADDR, HI6555C_SMT_HSL_GAIN_BIT_START, 0xF, 0,
        hi6555c_smt_hsl_gain_tlv),

    SOC_SINGLE("HISSC_SMT_HSL_MUTE",
        HI6555C_SMT_CODEC_ANA_RW17_ADDR, HI6555C_SMT_HSL_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_HS_LIT_LP_L",
        HI6555C_SMT_CODEC_ANA_RW17_ADDR, HI6555C_SMT_HS_LIT_LP_L_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_HSR_MIN_GAIN",
        HI6555C_SMT_CODEC_ANA_RW18_ADDR, HI6555C_SMT_HSR_MIN_GAIN_BIT_START, 0x1, 0),

    SOC_SINGLE_TLV("HISSC_SMT_HSR_GAIN",
        HI6555C_SMT_CODEC_ANA_RW18_ADDR, HI6555C_SMT_HSR_GAIN_BIT_START, 0xF, 0,
        hi6555c_smt_hsr_gain_tlv),

    SOC_SINGLE("HISSC_SMT_HSR_MUTE",
        HI6555C_SMT_CODEC_ANA_RW18_ADDR, HI6555C_SMT_HSR_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_HS_LIT_LP_R",
        HI6555C_SMT_CODEC_ANA_RW18_ADDR, HI6555C_SMT_HS_LIT_LP_R_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_EAR_CM_CTRL",
        HI6555C_SMT_CODEC_ANA_RW19_ADDR, HI6555C_SMT_EAR_CM_CTRL_BIT_START, 0x1, 0),

    SOC_SINGLE_TLV("HISSC_SMT_EAR_GAIN",
        HI6555C_SMT_CODEC_ANA_RW19_ADDR, HI6555C_SMT_EAR_GAIN_BIT_START, 0xF, 0,
        hi6555c_smt_ear_gain_tlv),

    SOC_SINGLE("HISSC_SMT_EAR_MUTE",
        HI6555C_SMT_CODEC_ANA_RW19_ADDR, HI6555C_SMT_EAR_MUTE_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_DAC_CHOP_CLK_SEL",
        HI6555C_SMT_CODEC_ANA_RW26_ADDR, HI6555C_SMT_DAC_CHOP_CLK_SEL_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_SMT_ADC_CHOP_CLK_SEL",
        HI6555C_SMT_CODEC_ANA_RW26_ADDR, HI6555C_SMT_ADC_CHOP_CLK_SEL_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_SMT_DAC_CLK_SYS_EDGE_0",
        HI6555C_SMT_CODEC_ANA_RW26_ADDR, HI6555C_SMT_DAC_CLK_SYS_EDGE_0_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_DAC_CLK_SYS_EDGE_1",
        HI6555C_SMT_CODEC_ANA_RW26_ADDR, HI6555C_SMT_DAC_CLK_SYS_EDGE_1_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_ADC_CLK_SYS_EDGE_0",
        HI6555C_SMT_CODEC_ANA_RW26_ADDR, HI6555C_SMT_ADC_CLK_SYS_EDGE_0_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_ADC_CLK_SYS_EDGE_1",
        HI6555C_SMT_CODEC_ANA_RW26_ADDR, HI6555C_SMT_ADC_CLK_SYS_EDGE_1_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_CTCM_CHOP_BPS",
        HI6555C_SMT_CODEC_ANA_RW27_ADDR, HI6555C_SMT_CTCM_CHOP_BPS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_MICPGA_CHOP_BPS",
        HI6555C_SMT_CODEC_ANA_RW27_ADDR, HI6555C_SMT_MICPGA_CHOP_BPS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_LINEIN_CHOP_BPS",
        HI6555C_SMT_CODEC_ANA_RW27_ADDR, HI6555C_SMT_LINEIN_CHOP_BPS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_ADC_SDM_CHOP_BPS",
        HI6555C_SMT_CODEC_ANA_RW27_ADDR, HI6555C_SMT_ADC_SDM_CHOP_BPS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_RX_CHOP_BPS",
        HI6555C_SMT_CODEC_ANA_RW27_ADDR, HI6555C_SMT_RX_CHOP_BPS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_HS_CHOP_BPS",
        HI6555C_SMT_CODEC_ANA_RW28_ADDR, HI6555C_SMT_HS_CHOP_BPS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_EAR_CLD_CHOP_BPS",
        HI6555C_SMT_CODEC_ANA_RW28_ADDR, HI6555C_SMT_EAR_CLD_CHOP_BPS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_DAC_CHOP_BPS",
        HI6555C_SMT_CODEC_ANA_RW28_ADDR, HI6555C_SMT_DAC_CHOP_BPS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_TX_CHOP_BPS",
        HI6555C_SMT_CODEC_ANA_RW28_ADDR, HI6555C_SMT_TX_CHOP_BPS_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_IL_SRC_UP_EN",
        HI6555C_S2_SRC_CFG_ADDR, HI6555C_S2_IL_SRC_UP_EN_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_IL_SRC_DOWN_EN",
        HI6555C_S2_SRC_CFG_ADDR, HI6555C_S2_IL_SRC_DOWN_EN_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_IR_SRC_UP_EN",
        HI6555C_S2_SRC_CFG_ADDR, HI6555C_S2_IR_SRC_UP_EN_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_IR_SRC_DOWN_EN",
        HI6555C_S2_SRC_CFG_ADDR, HI6555C_S2_IR_SRC_DOWN_EN_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_S2_OL_SRC_EN",
        HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_S2_OL_SRC_EN_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_VOICE_DLINK_SRC_EN",
        HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_VOICE_DLINK_SRC_EN_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_CR_MIXF_LINEINR",
        HI6555C_SMT_CODEC_ANA_RW14_ADDR, HI6555C_SMT_CR_MIXF_BIT_START, 0x1, 0),

    SOC_SINGLE("HISSC_SMT_CR_MIXF_LINEINL",
        HI6555C_SMT_CODEC_ANA_RW14_ADDR, (HI6555C_SMT_CR_MIXF_BIT_START+1), 0x1, 0),

    SOC_SINGLE("HISSC_SMT_CR_MIXF_DACR",
        HI6555C_SMT_CODEC_ANA_RW14_ADDR, (HI6555C_SMT_CR_MIXF_BIT_START+2), 0x1, 0),

    SOC_SINGLE("HISSC_SMT_CR_MIXF_DACL",
        HI6555C_SMT_CODEC_ANA_RW14_ADDR, (HI6555C_SMT_CR_MIXF_BIT_START+3), 0x1, 0),

    SOC_SINGLE("HISSC_PMU_CODEC_CLASSD_GAIN",
        HI6555C_PMU_CODEC_CLASSD_CTRL1_ADDR, HI6555C_PMU_CODEC_CLASSD_GAIN_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_PMU_CODEC_CLASSD_I_OCP",
        HI6555C_PMU_CODEC_CLASSD_CTRL1_ADDR, HI6555C_PMU_CODEC_CLASSD_I_OCP_BIT_START, 0x3, 0),

    SOC_SINGLE("HISSC_PMU_CODEC_CLASSD_MUTE",
        HI6555C_PMU_CODEC_CLASSD_CTRL1_ADDR, HI6555C_PMU_CODEC_CLASSD_MUTE_BIT, 0x1, 0),
};

/*****************************************************************************
  Widgets Related
*****************************************************************************/
int hi6555c_dacl_mixer_en_pga_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW14_ADDR, (0x01 << (HI6555C_SMT_MIXOUT_EAR_BIT_START+ 3)));
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW14_ADDR, (0x01 << (HI6555C_SMT_MIXOUT_EAR_BIT_START+ 3)));
        break;
    default:
        loge("event=%d", event);
        break;
    }

    return 0;
}

int hi6555c_dacr_mixer_en_pga_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW14_ADDR, (0x01 << (HI6555C_SMT_MIXOUT_EAR_BIT_START+ 2)));
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW14_ADDR, (0x01 << (HI6555C_SMT_MIXOUT_EAR_BIT_START+ 2)));
        break;
    default:
        loge("event=%d", event);
        break;
    }

    return 0;
}

int hi6555c_dacl_agc_en_pga_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6555c_set_reg_bits(HI6555C_DACL_AGC_CFG_2_ADDR, (0x01 << HI6555C_DACL_AGC_BYPASS_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_HBF1I_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_HBF2I_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_COMPI_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_SDM_EN_BIT_START));
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_HBF1I_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_HBF2I_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_COMPI_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACL_SDM_EN_BIT_START));
        break;
    default:
        loge("event=%d", event);
        break;
    }

    return 0;
}

int hi6555c_dacr_agc_en_pga_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6555c_set_reg_bits(HI6555C_DACR_AGC_CFG_2_ADDR, (0x01 << HI6555C_DACR_AGC_BYPASS_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_HBF1I_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_HBF2I_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_COMPI_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_SDM_EN_BIT_START));
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_HBF1I_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_HBF2I_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_COMPI_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_DACR_SDM_EN_BIT_START));
        break;
    default:
        loge("event=%d", event);
        break;
    }

    return 0;
}

int hi6555c_adcl_pga_en_pga_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_CIC_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_COMPD_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_HPF_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_HBFVD_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_HBF2D_EN_BIT_START));
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_CIC_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_COMPD_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_HPF_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_HBFVD_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCL_HBF2D_EN_BIT_START));
        break;
    default:
        loge("event=%d", event);
        break;
    }

    return 0;
}

int hi6555c_adcr_pga_en_pga_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_CIC_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_COMPD_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_HPF_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_HBFVD_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_HBF2D_EN_BIT_START));
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_CIC_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_COMPD_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_HPF_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_HBFVD_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR, (0x01 << HI6555C_ADCR_HBF2D_EN_BIT_START));
        break;
    default:
        loge("event=%d", event);
        break;
    }

    return 0;
}

static int hi6555c_smt_hslr_pd_outdrv_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6555c_reg_write(g_codec,HI6555C_SMT_CODEC_ANA_RW17_ADDR,0x58);
        hi6555c_reg_write(g_codec,HI6555C_SMT_CODEC_ANA_RW18_ADDR,0x58);
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW03_ADDR,
            (0x01 << HI6555C_SMT_HSR_PD_BIT_START)|(0x01 << HI6555C_SMT_HSL_PD_BIT_START));
        msleep(100);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW03_ADDR,
            (0x01 << HI6555C_SMT_HSR_PD_BIT_START)|(0x01 << HI6555C_SMT_HSL_PD_BIT_START));
        msleep(100);
        break;
    default:
        loge("event=%d", event);
        break;
    }

    return 0;
}

static int hi6555c_smt_hslr_pd_mixer_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW03_ADDR,
            (0x01 << HI6555C_SMT_MIXOUT_HSR_PD_BIT_START)|(0x01 << HI6555C_SMT_MIXOUT_HSL_PD_BIT_START));
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW03_ADDR,
            (0x01 << HI6555C_SMT_MIXOUT_HSR_PD_BIT_START)|(0x01 << HI6555C_SMT_MIXOUT_HSL_PD_BIT_START));
        break;
    default:
        loge("event=%d", event);
        break;
    }

    return 0;
}

static int hi6555c_pmu_classd_pd_outdrv_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    int ret = 0;
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(g_codec);

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        if(!priv->use_battery_supply){
            logi("use scharger supply");
            /* flash boost enable */
            ret = regulator_enable(priv->regulator_schg_boost3);
            if (ret != 0) {
                loge("regulator_schg_boost3 en fail\n");
            }
        }else{
                     logi("use battery supply");
          }

        /* classd pu */
        hi6555c_set_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL3_ADDR, (0x01 << HI6555C_PMU_CODEC_EN_CLASSD_INT_BIT));
        msleep(1);
        hi6555c_set_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL3_ADDR, (0x01 << HI6555C_PMU_CODEC_CLASSD_DRV_EN_BIT));
        msleep(1);

        /* unmute 0x69 bit5 0 */
        hi6555c_clr_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL1_ADDR, (0x01 << HI6555C_PMU_CODEC_CLASSD_MUTE_BIT));
        break;
    case SND_SOC_DAPM_POST_PMD:
        /* mute 0x69 bit5 1 */
        hi6555c_set_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL1_ADDR, (0x01 << HI6555C_PMU_CODEC_CLASSD_MUTE_BIT));
        msleep(1);

        /* classd pd */
        hi6555c_clr_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL3_ADDR, (0x01 << HI6555C_PMU_CODEC_CLASSD_DRV_EN_BIT));
        hi6555c_clr_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL3_ADDR, (0x01 << HI6555C_PMU_CODEC_EN_CLASSD_INT_BIT));

        if(!priv->use_battery_supply){
            /* flash boost close */
            ret = regulator_disable(priv->regulator_schg_boost3);
            if (ret != 0) {
                loge("regulator_schg_boost3 dis fail\n");
            }
        }

        break;
    default:
        loge("event=%d", event);
        break;
    }

    return 0;
}

/* SOC_IBIAS EVENT */
static int hi6555c_soc_ibias_supply_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        break;
    case SND_SOC_DAPM_POST_PMD:
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

/* SMT_IBIAS EVENT */
static int hi6555c_smt_ibias_supply_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6555c_ibias_work_enable(g_codec, true);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_ibias_work_enable(g_codec, false);
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

/* MICB1 EVENT */
static int hi6555c_smt_micb1_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        /* MICBIAS PU */
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, (0x01 << HI6555C_SMT_MICB1_PD_BIT_START));
        msleep(1);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, (0x01 << HI6555C_SMT_MICB1_PD_BIT_START));
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

/* MICB1 EVENT */
static int hi6555c_smt_hsmicb_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    unsigned int irq_mask = 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        /* to avoid irq while MBHD_COMP power up£¬mask the irq then clean it */
        irq_mask = hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR);
        hi6555c_irqs_mask_set(irq_mask | IRQ_MSK_COMP);
        hi6555c_hs_micbias_work_enable(g_codec,true);
        msleep(25);

        /* to avoid irq while MBHD_COMP power up£¬mask the irq then clean it */
        hi6555c_irqs_clr(IRQ_MSK_COMP);
        hi6555c_irqs_mask_clr(IRQ_MSK_BTN_NOR);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_hs_micbias_work_enable(g_codec,false);
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static int hi6555c_pll_supply_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    int ret = 0;
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(g_codec);

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        ret = clk_prepare_enable(priv->codec_soc);
        if (ret) {
            loge("codec 49.15M clken fail \n");
        }
        //logi("[AUDIO] inform lpm3 to remote sleep. \n");
        //BSP_IPC_IntSend(IPC_CORE_MCU, (IPC_INT_LEV_E)IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLEEP);
        break;
    case SND_SOC_DAPM_POST_PMD:
        //logi("[AUDIO] inform lpm3 to remote invalid. \n");
        //BSP_IPC_IntSend(IPC_CORE_MCU, (IPC_INT_LEV_E)IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_INVALID);
        clk_disable_unprepare(priv->codec_soc);
        break;
    default :
        loge("power mode event err : %d \n", event);
        break;
    }

    return 0;
}

static int hi6555c_backuppll_supply_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    int ret = 0;
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(g_codec);

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        ret = clk_prepare_enable(priv->codec_soc);
        if (ret) {
            loge("codec 49.15M clken fail\n");
        }
        hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW41_ADDR, 0x07);
        hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW42_ADDR, 0x07);
        clk_disable_unprepare(priv->codec_soc);
        break;
    case SND_SOC_DAPM_POST_PMD:
        ret = clk_prepare_enable(priv->codec_soc);
        if (ret) {
            loge("codec 49.15M clken fail\n");
        }
        hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW42_ADDR, 0x00);
        hi6555c_reg_write(g_codec, HI6555C_SMT_CODEC_ANA_RW41_ADDR, 0x27);
        clk_disable_unprepare(priv->codec_soc);
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static int hi6555c_smt_lineinl_pga_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        if (0 != (hi6555c_reg_read(g_codec, HI6555C_SMT_CODEC_ANA_RW05_ADDR) & 0x1)) {
            hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW01_ADDR, (1 << HI6555C_SMT_LINEPGAL_PD_BIT_START));
        } else {
            hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW05_ADDR, (1 << HI6555C_SMT_LINEPGAL_MUTE_BIT_START));
            hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW01_ADDR, (1 << HI6555C_SMT_LINEPGAL_PD_BIT_START));
            hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW05_ADDR, (1 << HI6555C_SMT_LINEPGAL_MUTE_BIT_START));
        }
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW01_ADDR, (1 << HI6555C_SMT_LINEPGAL_PD_BIT_START));
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static int hi6555c_smt_lineinr_pga_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        if (0 != (hi6555c_reg_read(g_codec, HI6555C_SMT_CODEC_ANA_RW06_ADDR) & 0x1)) {
            hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW01_ADDR, (1 << HI6555C_SMT_LINEPGAR_PD_BIT_START));
        } else {
            hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW06_ADDR, (1 << HI6555C_SMT_LINEPGAR_MUTE_BIT_START));
            hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW01_ADDR, (1 << HI6555C_SMT_LINEPGAR_PD_BIT_START));
            hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW06_ADDR, (1 << HI6555C_SMT_LINEPGAR_MUTE_BIT_START));
        }
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW01_ADDR, (1 << HI6555C_SMT_LINEPGAR_PD_BIT_START));
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static int hi6555c_hs_preprocess_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW21_ADDR,
            ((1<<HI6555C_SMT_RST_N_R_BIT_START)|(1<<HI6555C_SMT_RST_N_L_BIT_START))|(1<<HI6555C_SMT_PDD_EN_BIT_START));
        hi6555c_reg_write(g_codec,HI6555C_SMT_CODEC_ANA_RW17_ADDR,0x21);
        hi6555c_reg_write(g_codec,HI6555C_SMT_CODEC_ANA_RW18_ADDR,0x21);
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW25_ADDR,(1<<HI6555C_SMT_HS_SYS_CLK_PD_BIT_START));
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW16_ADDR,(1<<HI6555C_SMT_HP_SOFT_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW25_ADDR,(1<<HI6555C_SMT_HS_SYS_CLK_PD_BIT_START));
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW21_ADDR,(1<<HI6555C_SMT_CLK_SEL_BIT_START));
        hi6555c_reg_write(g_codec,HI6555C_SMT_CODEC_ANA_RW20_ADDR,0xFA);
        hi6555c_reg_write(g_codec,HI6555C_SMT_CODEC_ANA_RW28_ADDR,0x00);
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW25_ADDR,(1<<HI6555C_SMT_CP_CLK_PD_BIT_START));
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW37_ADDR,(1<<HI6555C_SMT_CP_PU_BIT_START));
        msleep(2);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW21_ADDR,
            ((1<<HI6555C_SMT_RST_N_R_BIT_START)|(1<<HI6555C_SMT_RST_N_L_BIT_START))|(1<<HI6555C_SMT_PDD_EN_BIT_START));
        hi6555c_reg_write(g_codec,HI6555C_SMT_CODEC_ANA_RW17_ADDR,0x20);
        hi6555c_reg_write(g_codec,HI6555C_SMT_CODEC_ANA_RW18_ADDR,0x20);
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW25_ADDR,(1<<HI6555C_SMT_HS_SYS_CLK_PD_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW16_ADDR,(1<<HI6555C_SMT_HP_SOFT_EN_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW21_ADDR,(1<<HI6555C_SMT_CLK_SEL_BIT_START));
        hi6555c_reg_write(g_codec,HI6555C_SMT_CODEC_ANA_RW20_ADDR,0x40);
        hi6555c_reg_write(g_codec,HI6555C_SMT_CODEC_ANA_RW28_ADDR,0x00);
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW37_ADDR,(1<<HI6555C_SMT_CP_PU_BIT_START));
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW25_ADDR,(1<<HI6555C_SMT_CP_CLK_PD_BIT_START));
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static int hi6555c_dac_path_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW13_ADDR,
            (0x01<<(HI6555C_SMT_MIXOUT_HSR_BIT_START+ 2))|(0x01<<(HI6555C_SMT_MIXOUT_HSL_BIT_START+ 3)));
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW13_ADDR,
            (0x01<<(HI6555C_SMT_MIXOUT_HSR_BIT_START+ 2))|(0x01<<(HI6555C_SMT_MIXOUT_HSL_BIT_START+ 3)));
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static int hi6555c_linein_path_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        msleep(50);
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW13_ADDR,
            (0x01<<(HI6555C_SMT_MIXOUT_HSR_BIT_START+ 0))|(0x01<<(HI6555C_SMT_MIXOUT_HSL_BIT_START+ 1)));
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW13_ADDR,
            (0x01<<(HI6555C_SMT_MIXOUT_HSR_BIT_START+ 0))|(0x01<<(HI6555C_SMT_MIXOUT_HSL_BIT_START+ 1)));
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

/* fifo EVENT */
static int hi6555c_stereo_dlink_fifo_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    int i;

    switch (event) {
    case SND_SOC_DAPM_POST_PMU:
        /* STEREO DLINK AFIFO CLEAR CFG */
        hi6555c_set_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,
            (1 << HI6555C_STEREO_DLINK_L_FIFO_CLR_BIT_START)|(1 << HI6555C_STEREO_DLINK_R_FIFO_CLR_BIT_START));
        udelay(1);

        hi6555c_clr_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,
            (1 << HI6555C_STEREO_DLINK_L_FIFO_CLR_BIT_START)|(1 << HI6555C_STEREO_DLINK_R_FIFO_CLR_BIT_START));

        /* fifo init, clear over depth */
        for (i = 0; i < 16 ; i++) {
            hi6555c_clr_reg_bits(HI6555C_STEREO_DLINK_CHANNEL_ADDR, 0xFFFFFFFF);
        }
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static int hi6555c_voice_dlink_fifo_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    int i;

    switch (event) {
    case SND_SOC_DAPM_POST_PMU:
        hi6555c_set_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,(1 << HI6555C_VOICE_DLINK_FIFO_CLR_BIT_START));
        udelay(1);
        hi6555c_clr_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,(1 << HI6555C_VOICE_DLINK_FIFO_CLR_BIT_START));

        for (i = 0; i < 32 ; i++) {
            hi6555c_clr_reg_bits(HI6555C_VOICE_DLINK_CHANNEL_ADDR, 0xFFFFFFFF);
        }

        /*
         *bugfix:wait 4ms to clear fifo
         *fifo size 32,samplerate 8k,time 4ms
         *time * samplerate = fifo size
         */
        msleep(4);

        hi6555c_clr_reg_bits(HI6555C_MUX_TOP_MODULE_CFG_ADDR,(1 << HI6555C_VOICE_DLINK_MIXER_IN1_MUTE_BIT_START));
        break;
    case SND_SOC_DAPM_PRE_PMD:
        hi6555c_set_reg_bits(HI6555C_MUX_TOP_MODULE_CFG_ADDR,(1 << HI6555C_VOICE_DLINK_MIXER_IN1_MUTE_BIT_START));
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static int hi6555c_voice_uplink_fifo_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    int i;

    switch (event) {
    case SND_SOC_DAPM_POST_PMU:
        hi6555c_set_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,
            (1 << HI6555C_VOICE_UPLINK_L_FIFO_CLR_BIT_START)|(1 << HI6555C_VOICE_UPLINK_R_FIFO_CLR_BIT_START));
        udelay(1);
        hi6555c_clr_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,
            (1 << HI6555C_VOICE_UPLINK_L_FIFO_CLR_BIT_START)|(1 << HI6555C_VOICE_UPLINK_R_FIFO_CLR_BIT_START));

        for (i = 0; i < 16 ; i++) {
            hi6555c_clr_reg_bits(HI6555C_VOICE_UPLINK_CHANNEL_ADDR, 0xFFFFFFFF);
        }
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static int hi6555c_thirdmd_dlink_fifo_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    int i;

    switch (event) {
    case SND_SOC_DAPM_POST_PMU:
        hi6555c_set_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,(1 << HI6555C_THIRDMD_DLINK_FIFO_CLR_BIT_START));
        udelay(1);
        hi6555c_clr_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,(1 << HI6555C_THIRDMD_DLINK_FIFO_CLR_BIT_START));

        for (i = 0; i < 16 ; i++) {
            hi6555c_clr_reg_bits(HI6555C_THIRDMD_DLINK_CHANNEL_ADDR, 0xFFFFFFFF);
        }
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static int hi6555c_thirdmd_uplink_fifo_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    int i;

    switch (event) {
    case SND_SOC_DAPM_POST_PMU:
        hi6555c_set_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,(1 << HI6555C_THIRDMD_UPLINK_FIFO_CLR_BIT_START));
        udelay(1);
        hi6555c_clr_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,(1 << HI6555C_THIRDMD_UPLINK_FIFO_CLR_BIT_START));

        for  (i = 0; i < 16 ; i++) {
            hi6555c_clr_reg_bits(HI6555C_THIRDMD_UPLINK_CHANNEL_ADDR, 0xFFFFFFFF);
        }
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static int hi6555c_stereo_uplink_fifo_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    int i;

    switch (event) {
    case SND_SOC_DAPM_POST_PMU:
        hi6555c_set_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,
            (1 << HI6555C_STEREO_UPLINK_L_FIFO_CLR_BIT_START)|(1 << HI6555C_STEREO_UPLINK_R_FIFO_CLR_BIT_START));
        udelay(1);
        hi6555c_clr_reg_bits(HI6555C_APB_AFIFO_CFG_1_ADDR,
            (1 << HI6555C_STEREO_UPLINK_L_FIFO_CLR_BIT_START)|(1 << HI6555C_STEREO_UPLINK_R_FIFO_CLR_BIT_START));

        for (i = 0; i < 16 ; i++) {
            hi6555c_clr_reg_bits(HI6555C_STEREO_UPLINK_CHANNEL_ADDR, 0xFFFFFFFF);
        }
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static int hi6555c_dacl_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6555c_set_reg_bits(HI6555C_SMT_CLK_EN_CFG_ADDR,(1 << HI6555C_SMT_DACL_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW38_ADDR,(1 << HI6555C_SMT_DACL_PU_BIT_START));
        usleep_range(200,250);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW38_ADDR,(1 << HI6555C_SMT_DACL_PU_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_SMT_CLK_EN_CFG_ADDR,(1 << HI6555C_SMT_DACL_EN_BIT_START));
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static int hi6555c_dacr_power_mode_event(struct snd_soc_dapm_widget *w,
                struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6555c_set_reg_bits(HI6555C_SMT_CLK_EN_CFG_ADDR,(1 << HI6555C_SMT_DACR_EN_BIT_START));
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW38_ADDR,(1 << HI6555C_SMT_DACR_PU_BIT_START));
        usleep_range(200,250);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW38_ADDR,(1 << HI6555C_SMT_DACR_PU_BIT_START));
        hi6555c_clr_reg_bits(HI6555C_SMT_CLK_EN_CFG_ADDR,(1 << HI6555C_SMT_DACR_EN_BIT_START));
        break;
    default :
        loge("power mode event err : %d\n", event);
        break;
    }

    return 0;
}

static const struct snd_kcontrol_new hi6555c_stereo_uplink_l_en_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("STEREO_UP_L_EN",
        HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_STEREO_UPLINK_L_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_stereo_uplink_r_en_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("STEREO_UP_R_EN",
        HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_STEREO_UPLINK_R_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_voice_uplink_l_en_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("VOICE_UPLINK_L_EN",
        HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_VOICE_UPLINK_L_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_voice_uplink_r_en_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("VOICE_UPLINK_R_EN",
        HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_VOICE_UPLINK_R_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_thirdmd_dlink_en_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("THIRDMD_DLINK_EN",
        HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_THIRDMD_DLINK_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_thirdmd_uplink_en_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("THIRDMD_UPLINK_EN",
        HI6555C_IF_CLK_EN_CFG_ADDR, HI6555C_THIRDMD_UPLINK_EN_BIT_START, 1, 0/* not INVERT */),
};

static const char *hi6555c_rm_codec_dac2adc_mux_texts[] = {
    "CIC_ADC",
    "CIC_DACL",
    "CIC_DACR",
    "RESERVED",
    "CIC_DMIC_PORT0",
    "RESERVED",
};

static const struct soc_enum hi6555c_rm_codec_dac2adc_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_RM_CODEC_DAC2ADC_BIT_START,
    ARRAY_SIZE(hi6555c_rm_codec_dac2adc_mux_texts), hi6555c_rm_codec_dac2adc_mux_texts);

static const struct snd_kcontrol_new hi6555c_rm_codec_dac2adc_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_rm_codec_dac2adc_mux_enum);

static const char *hi6555c_lm_codec_dac2adc_mux_texts[] = {
    "CIC_ADC",
    "CIC_DACL",
    "CIC_DACR",
    "RESERVED",
    "CIC_DMIC_PORT0",
    "RESERVED",
};

static const struct soc_enum hi6555c_lm_codec_dac2adc_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_LM_CODEC_DAC2ADC_BIT_START,
    ARRAY_SIZE(hi6555c_lm_codec_dac2adc_mux_texts), hi6555c_lm_codec_dac2adc_mux_texts);

static const struct snd_kcontrol_new hi6555c_lm_codec_dac2adc_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_lm_codec_dac2adc_mux_enum);

static const struct snd_kcontrol_new hi6555c_dacl_mixer_en_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("DACL_MIXER_IN1_MUTE",
        HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACL_MIXER_IN1_MUTE_BIT_START, 1, 1/* INVERT */),
    SOC_DAPM_SINGLE("DACL_MIXER_IN2_MUTE",
        HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACL_MIXER_IN2_MUTE_BIT_START, 1, 1/* INVERT */),
    SOC_DAPM_SINGLE("DACL_MIXER_IN3_MUTE",
        HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACL_MIXER_IN3_MUTE_BIT_START, 1, 1/* INVERT */),
    SOC_DAPM_SINGLE("DACL_MIXER_IN4_MUTE",
        HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACL_MIXER_IN4_MUTE_BIT_START, 1, 1/* INVERT */),
};

static const struct snd_kcontrol_new hi6555c_dacr_mixer_en_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("DACR_MIXER_IN1_MUTE",
        HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACR_MIXER_IN1_MUTE_BIT_START, 1, 1/* INVERT */),
    SOC_DAPM_SINGLE("DACR_MIXER_IN2_MUTE",
        HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACR_MIXER_IN2_MUTE_BIT_START, 1, 1/* INVERT */),
    SOC_DAPM_SINGLE("DACR_MIXER_IN3_MUTE",
        HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACR_MIXER_IN3_MUTE_BIT_START, 1, 1/* INVERT */),
    SOC_DAPM_SINGLE("DACR_MIXER_IN4_MUTE",
        HI6555C_DIG_FILTER_MODULE_CFG_ADDR, HI6555C_DACR_MIXER_IN4_MUTE_BIT_START, 1, 1/* INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s2_ol_mixer_en_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("S2_OL_MIXER_IN1_MUTE",
        HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_S2_OL_MIXER_IN1_MUTE_BIT_START, 1, 1/* INVERT */),
    SOC_DAPM_SINGLE("S2_OL_MIXER_IN2_MUTE",
        HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_S2_OL_MIXER_IN2_MUTE_BIT_START, 1, 1/* INVERT */),
};

static const struct snd_kcontrol_new hi6555c_voice_dlink_mixer_en_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("VOICE_DL_MIXER_IN1_MUTE",
        HI6555C_DDR_CODEC_VIR1_ADDR, DDR_CODEC_BIT7, 1, 0/* INVERT */),
    SOC_DAPM_SINGLE("VOICE_DL_MIXER_IN2_MUTE",
        HI6555C_MUX_TOP_MODULE_CFG_ADDR, HI6555C_VOICE_DLINK_MIXER_IN2_MUTE_BIT_START, 1, 1/* INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s1_if_rx_ena_mixer_en_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("FM_L",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT0, 1, 0/*NO INVERT */),
    SOC_DAPM_SINGLE("FM_R",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT1, 1, 0/*NO INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s1_if_tx_ena_mixer_en_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("ADC_LR",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT2, 1, 0/*NO INVERT */),
    SOC_DAPM_SINGLE("DAC_LR",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT3, 1, 0/*NO INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s2_if_rx_ena_mixer_en_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("VOICE_UL",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT4, 1, 0/*NO INVERT */),
    SOC_DAPM_SINGLE("VOICE_UR",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT5, 1, 0/*NO INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s2_if_tx_ena_mixer_en_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("DACL",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT6, 1, 0/*NO INVERT */),
    SOC_DAPM_SINGLE("VOICE_DLINK",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT7, 1, 0/*NO INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s3_if_rx_ena_mixer_en_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("VOICE_UP",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT8, 1, 0/*NO INVERT */),
};

static const struct snd_kcontrol_new hi6555c_s3_if_tx_ena_mixer_en_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("VOICE_DL",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT9, 1, 0/*NO INVERT */),
    SOC_DAPM_SINGLE("VOICE_DR",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT10, 1, 0/*NO INVERT */),
};

static const char *hi6555c_stereo_uplink_l_fifo_din_sel_mux_texts[] = {
    "S1",
    "ADCL",
};

static const struct soc_enum hi6555c_stereo_uplink_l_fifo_din_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_APB_AFIFO_CFG_2_ADDR, HI6555C_STEREO_UPLINK_L_FIFO_DIN_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_stereo_uplink_l_fifo_din_sel_mux_texts), hi6555c_stereo_uplink_l_fifo_din_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_stereo_uplink_l_fifo_din_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_stereo_uplink_l_fifo_din_sel_mux_enum);

static const char *hi6555c_stereo_uplink_r_fifo_din_sel_mux_texts[] = {
    "S1",
    "ADCR",
};

static const struct soc_enum hi6555c_stereo_uplink_r_fifo_din_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_APB_AFIFO_CFG_2_ADDR, HI6555C_STEREO_UPLINK_R_FIFO_DIN_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_stereo_uplink_r_fifo_din_sel_mux_texts), hi6555c_stereo_uplink_r_fifo_din_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_stereo_uplink_r_fifo_din_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_stereo_uplink_r_fifo_din_sel_mux_enum);

static const char *hi6555c_voice_uplink_l_fifo_din_sel_mux_texts[] = {
    "S2",
    "ADCL",
};

static const struct soc_enum hi6555c_voice_uplink_l_fifo_din_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_APB_AFIFO_CFG_2_ADDR, HI6555C_VOICE_UPLINK_L_FIFO_DIN_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_voice_uplink_l_fifo_din_sel_mux_texts), hi6555c_voice_uplink_l_fifo_din_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_voice_uplink_l_fifo_din_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_voice_uplink_l_fifo_din_sel_mux_enum);

static const char *hi6555c_voice_uplink_r_fifo_din_sel_mux_texts[] = {
    "S2",
    "ADCR",
};

static const struct soc_enum hi6555c_voice_uplink_r_fifo_din_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_APB_AFIFO_CFG_2_ADDR, HI6555C_VOICE_UPLINK_R_FIFO_DIN_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_voice_uplink_r_fifo_din_sel_mux_texts), hi6555c_voice_uplink_r_fifo_din_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_voice_uplink_r_fifo_din_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_voice_uplink_r_fifo_din_sel_mux_enum);

static const char *hi6555c_thirdmd_uplink_din_sel_mux_texts[] = {
    "S3",
    "ADCR",
};

static const struct soc_enum hi6555c_thirdmd_uplink_din_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_APB_AFIFO_CFG_2_ADDR, HI6555C_THIRDMD_UPLINK_DIN_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_thirdmd_uplink_din_sel_mux_texts), hi6555c_thirdmd_uplink_din_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_thirdmd_uplink_din_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_thirdmd_uplink_din_sel_mux_enum);

static const struct snd_kcontrol_new hi6555c_sif_en_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("SIF_DACL_EN",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT11, 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("SIF_DACR_EN",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT12, 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("SIF_ADCL_EN",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT13, 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("SIF_ADCR_EN",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT14, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_sif_en_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("SIF_HSLR_EN",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT15, 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("SIF_CLASSD_EN",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT16, 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("SIF_RCV_EN",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT17, 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("SIF_MIC1_EN",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT18, 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("SIF_MIC2_EN",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT19, 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("SIF_LINEINL_EN",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT20, 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("SIF_LINEINR_EN",
        HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT21, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_hs_linein_sel_vir_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("LINEIN", HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT22, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_hs_dac_sel_vir_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("DAC", HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT23, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_dac_p2s_loopback_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("DAC_P2S_LOOPBACK", HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_DAC_P2S_LOOPBACK_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_sif_s2p_loopback_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("SIF_S2P_LOOPBACK", HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_SIF_S2P_LOOPBACK_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_dmic_en_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("DMIC_EN", HI6555C_DMIC_SIF_CFG_ADDR, HI6555C_DMIC_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_ana_loopback_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("ANA_LOOPBACK", HI6555C_SMT_CODEC_ANA_RW04_ADDR, (HI6555C_SMT_VREFSEL_BIT_START+2), 1, 0/* not INVERT */),
};

static const char *hi6555c_s2_dout_left_sel_mux_texts[] = {
    "SRC3",
    "VOICE_DLINK_PGA",
};

static const struct soc_enum hi6555c_s2_dout_left_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_S2_DOUT_LEFT_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_s2_dout_left_sel_mux_texts), hi6555c_s2_dout_left_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_s2_dout_left_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_s2_dout_left_sel_mux_enum);

static const char *hi6555c_s1_dout_test_sel_mux_texts[] = {
    "DACL_MIXER_DACR_MIXER",
    "ADCL_ADCR",
};

static const struct soc_enum hi6555c_s1_dout_test_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_S1_DOUT_TEST_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_s1_dout_test_sel_mux_texts), hi6555c_s1_dout_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_s1_dout_test_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_s1_dout_test_sel_mux_enum);

static const char *hi6555c_s2_dout_test_sel_mux_texts[] = {
    "VOICE_DLINK_PGA_S2",
    "DACL_MIXER",
};

static const struct soc_enum hi6555c_s2_dout_test_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_S2_DOUT_TEST_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_s2_dout_test_sel_mux_texts), hi6555c_s2_dout_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_s2_dout_test_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_s2_dout_test_sel_mux_enum);

static const char *hi6555c_stereo_dlink_test_sel_mux_texts[] = {
    "APB",
    "S1_STEREO_DLINK_L_S1_STEREO_DLINK_R",
};

static const struct soc_enum hi6555c_stereo_dlink_test_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_STEREO_DLINK_TEST_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_stereo_dlink_test_sel_mux_texts), hi6555c_stereo_dlink_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_stereo_dlink_test_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("ST_DL Mux", hi6555c_stereo_dlink_test_sel_mux_enum);

static const char *hi6555c_voice_dlink_din_sel_mux_texts[] = {
    "APB",
    "S3",
};

static const struct soc_enum hi6555c_voice_dlink_din_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_VOICE_DLINK_DIN_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_voice_dlink_din_sel_mux_texts), hi6555c_voice_dlink_din_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_voice_dlink_din_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_voice_dlink_din_sel_mux_enum);

static const char *hi6555c_voice_dlink_test_sel_mux_texts[] = {
    "FRONTSEL",
    "S2",
};

static const struct soc_enum hi6555c_voice_dlink_test_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_VOICE_DLINK_TEST_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_voice_dlink_test_sel_mux_texts), hi6555c_voice_dlink_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_voice_dlink_test_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_voice_dlink_test_sel_mux_enum);

static const char *hi6555c_s3_din_test_sel_mux_texts[] = {
    "LEFT",
    "RIGHT",
};

static const struct soc_enum hi6555c_s3_din_test_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_S3_DIN_TEST_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_s3_din_test_sel_mux_texts), hi6555c_s3_din_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_s3_din_test_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_s3_din_test_sel_mux_enum);

static const char *hi6555c_s3_dout_left_sel_mux_texts[] = {
    "THIRDMD_DLINK_PGA",
    "ADCL_PGA",
};

static const struct soc_enum hi6555c_s3_dout_left_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_S3_DOUT_LEFT_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_s3_dout_left_sel_mux_texts), hi6555c_s3_dout_left_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_s3_dout_left_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_s3_dout_left_sel_mux_enum);

static const char *hi6555c_s3_dout_right_sel_mux_texts[] = {
    "THIRDMD_DLINK_PGA",
    "ADCR_PGA",
    "OTHER",
};

static const struct soc_enum hi6555c_s3_dout_right_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_S3_DOUT_RIGHT_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_s3_dout_right_sel_mux_texts), hi6555c_s3_dout_right_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_s3_dout_right_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_s3_dout_right_sel_mux_enum);

static const char *hi6555c_thirdmd_dlink_din_sel_mux_texts[] = {
    "APB_THIRDMD",
    "S2",
};

static const struct soc_enum hi6555c_thirdmd_dlink_din_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_THIRDMD_DLINK_DIN_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_thirdmd_dlink_din_sel_mux_texts), hi6555c_thirdmd_dlink_din_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_thirdmd_dlink_din_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_thirdmd_dlink_din_sel_mux_enum);

static const char *hi6555c_thirdmd_dlink_test_sel_mux_texts[] = {
    "APB_THIRDMD_S2",
    "S3",
};

static const struct soc_enum hi6555c_thirdmd_dlink_test_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_MISC_CFG_ADDR, HI6555C_THIRDMD_DLINK_TEST_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_thirdmd_dlink_test_sel_mux_texts), hi6555c_thirdmd_dlink_test_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_thirdmd_dlink_test_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_thirdmd_dlink_test_sel_mux_enum);

static const struct snd_kcontrol_new hi6555c_smt_dacl_en_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("DACL_EN", HI6555C_SMT_CLK_EN_CFG_ADDR, HI6555C_SMT_DACL_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_dacr_en_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("DACR_EN", HI6555C_SMT_CLK_EN_CFG_ADDR, HI6555C_SMT_DACR_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_sif_en_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("SIF_EN", HI6555C_SMT_CLK_EN_CFG_ADDR, HI6555C_SMT_SIF_EN_BIT_START, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_classd_virtual_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("CLASSD_EN", HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT24, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_rcv_virtual_switch_dapm_controls[] = {
    SOC_DAPM_SINGLE("RCV_EN", HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT25, 1, 0/* not INVERT */),
};

static const char *hi6555c_smt_mainpga_sel_mux_texts[] = {
    "MUTE",
    "MIC",
    "HP_MIC",
    //"MUTE", /* 11:MUTE£» */
};

static const struct soc_enum hi6555c_smt_mainpga_sel_mux_enum =
    SOC_ENUM_SINGLE(HI6555C_SMT_CODEC_ANA_RW08_ADDR, HI6555C_SMT_MAINPGA_SEL_BIT_START,
    ARRAY_SIZE(hi6555c_smt_mainpga_sel_mux_texts), hi6555c_smt_mainpga_sel_mux_texts);

static const struct snd_kcontrol_new hi6555c_smt_mainpga_sel_mux_dapm_controls =
    SOC_DAPM_ENUM("Mux", hi6555c_smt_mainpga_sel_mux_enum);

static const struct snd_kcontrol_new hi6555c_smt_adcr_pd_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("AUXPGA",
        HI6555C_SMT_CODEC_ANA_RW09_ADDR, (HI6555C_SMT_ADCR_MIXIN_BIT_START+ 0), 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("MAINPGA",
        HI6555C_SMT_CODEC_ANA_RW09_ADDR, (HI6555C_SMT_ADCR_MIXIN_BIT_START+ 1), 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("LINEINR",
        HI6555C_SMT_CODEC_ANA_RW09_ADDR, (HI6555C_SMT_ADCR_MIXIN_BIT_START+ 2), 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("LINEINL",
        HI6555C_SMT_CODEC_ANA_RW09_ADDR, (HI6555C_SMT_ADCR_MIXIN_BIT_START+ 3), 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("DACR",
        HI6555C_SMT_CODEC_ANA_RW09_ADDR, (HI6555C_SMT_ADCR_MIXIN_BIT_START+ 4), 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("DACL",
        HI6555C_SMT_CODEC_ANA_RW09_ADDR, (HI6555C_SMT_ADCR_MIXIN_BIT_START+ 5), 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_adcl_pd_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("AUXPGA",
        HI6555C_SMT_CODEC_ANA_RW10_ADDR, (HI6555C_SMT_ADCL_MIXIN_BIT_START+ 0), 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("MAINPGA",
        HI6555C_SMT_CODEC_ANA_RW10_ADDR, (HI6555C_SMT_ADCL_MIXIN_BIT_START+ 1), 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("LINEINR",
        HI6555C_SMT_CODEC_ANA_RW10_ADDR, (HI6555C_SMT_ADCL_MIXIN_BIT_START+ 2), 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("LINEINL",
        HI6555C_SMT_CODEC_ANA_RW10_ADDR, (HI6555C_SMT_ADCL_MIXIN_BIT_START+ 3), 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("DACR",
        HI6555C_SMT_CODEC_ANA_RW10_ADDR, (HI6555C_SMT_ADCL_MIXIN_BIT_START+ 4), 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("DACL",
        HI6555C_SMT_CODEC_ANA_RW10_ADDR, (HI6555C_SMT_ADCL_MIXIN_BIT_START+ 5), 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_mixout_hslr_pd_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("LINEINLR", HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT26, 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("DACLR", HI6555C_DDR_CODEC_VIR0_ADDR, DDR_CODEC_BIT27, 1, 0/* not INVERT */),
};

static const struct snd_kcontrol_new hi6555c_smt_mixout_ear_pu_mixer_dapm_controls[] = {
    SOC_DAPM_SINGLE("LINEINR", HI6555C_SMT_CODEC_ANA_RW14_ADDR, (HI6555C_SMT_MIXOUT_EAR_BIT_START+ 0), 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("LINEINL", HI6555C_SMT_CODEC_ANA_RW14_ADDR, HI6555C_SMT_MIXOUT_EAR_BIT_START+ 1, 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("DACR", HI6555C_DDR_CODEC_VIR1_ADDR, DDR_CODEC_BIT3, 1, 0/* not INVERT */),
    SOC_DAPM_SINGLE("DACL", HI6555C_DDR_CODEC_VIR1_ADDR, DDR_CODEC_BIT4, 1, 0/* not INVERT */),
};

/*****************************************************************************
  Widgets
*****************************************************************************/
static const struct snd_soc_dapm_widget hi6555c_dapm_widgets[] = {
    /* INPUT */
    SND_SOC_DAPM_INPUT("VOICE_DL INPUT"),
    SND_SOC_DAPM_INPUT("AUDIO_DLINK INPUT"),
    SND_SOC_DAPM_INPUT("THIRDMD_DOWN INPUT"),
    SND_SOC_DAPM_INPUT("DIGI_ADC_UL INPUT"),
    SND_SOC_DAPM_INPUT("DIGI_ADC_UR INPUT"),
    SND_SOC_DAPM_INPUT("DMIC INPUT"),
    SND_SOC_DAPM_INPUT("I2S1_2_3 INPUT"),
    SND_SOC_DAPM_INPUT("SIF_EN INPUT"),
    SND_SOC_DAPM_INPUT("SMT_ANA_DAC_SDATA INPUT"),
    SND_SOC_DAPM_INPUT("SMT_MAINMIC INPUT"),
    SND_SOC_DAPM_INPUT("SMT_HPMIC INPUT"),
    SND_SOC_DAPM_INPUT("SMT_AUXMIC INPUT"),
    SND_SOC_DAPM_INPUT("SMT_LINEIN_L INPUT"),
    SND_SOC_DAPM_INPUT("SMT_LINEIN_R INPUT"),

    /* OUTPUT*/
    SND_SOC_DAPM_OUTPUT("SIF_EN OUTPUT"),
    SND_SOC_DAPM_OUTPUT("VOICE_UL OUTPUT"),
    SND_SOC_DAPM_OUTPUT("VOICE_UR OUTPUT"),
    SND_SOC_DAPM_OUTPUT("AUDIO_UL OUTPUT"),
    SND_SOC_DAPM_OUTPUT("AUDIO_UR OUTPUT"),
    SND_SOC_DAPM_OUTPUT("THIRDMD_UP OUTPUT"),
    SND_SOC_DAPM_OUTPUT("SMT_HP_LR OUTPUT"),
    SND_SOC_DAPM_OUTPUT("SMT_HPMIC OUTPUT"),
    SND_SOC_DAPM_OUTPUT("SMT_SPEAKER OUTPUT"),
    SND_SOC_DAPM_OUTPUT("SMT_RECV OUTPUT"),
    SND_SOC_DAPM_OUTPUT("SMT_ANA_ADC_SDATA OUTPUT"),
    SND_SOC_DAPM_OUTPUT("PMU_CLASSD OUTPUT"),
    SND_SOC_DAPM_OUTPUT("I2S1_2_3 OUTPUT"),

    /* PGA */
    SND_SOC_DAPM_PGA_E("STEREO_DLINK_L_EN PGA",
        HI6555C_IF_CLK_EN_CFG_ADDR,
        HI6555C_STEREO_DLINK_L_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0,
        hi6555c_stereo_dlink_fifo_power_mode_event,
        SND_SOC_DAPM_POST_PMU),

    SND_SOC_DAPM_PGA_E("STEREO_DLINK_R_EN PGA",
        HI6555C_IF_CLK_EN_CFG_ADDR,
        HI6555C_STEREO_DLINK_R_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0,
        hi6555c_stereo_dlink_fifo_power_mode_event,
        SND_SOC_DAPM_POST_PMU),

    SND_SOC_DAPM_PGA_E("VOICE_DLINK_EN PGA",
        HI6555C_IF_CLK_EN_CFG_ADDR,
        HI6555C_VOICE_DLINK_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0,
        hi6555c_voice_dlink_fifo_power_mode_event,
        (SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD)),

    SND_SOC_DAPM_PGA("S1_IL_PGA_EN PGA",
        HI6555C_IF_CLK_EN_CFG_ADDR,
        HI6555C_S1_IL_PGA_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("S1_IR_PGA_EN PGA",
        HI6555C_IF_CLK_EN_CFG_ADDR,
        HI6555C_S1_IR_PGA_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("S2_IL_PGA_EN PGA",
        HI6555C_IF_CLK_EN_CFG_ADDR,
        HI6555C_S2_IL_PGA_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("S2_IR_PGA_EN PGA",
        HI6555C_IF_CLK_EN_CFG_ADDR,
        HI6555C_S2_IR_PGA_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("SIF_ADCL_EN PGA",
        HI6555C_DMIC_SIF_CFG_ADDR,
        HI6555C_SIF_ADCL_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("SIF_ADCR_EN PGA",
        HI6555C_DMIC_SIF_CFG_ADDR,
        HI6555C_SIF_ADCR_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("SIF_DACL_EN PGA",
        HI6555C_DMIC_SIF_CFG_ADDR,
        HI6555C_SIF_DACL_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("SIF_DACR_EN PGA",
        HI6555C_DMIC_SIF_CFG_ADDR,
        HI6555C_SIF_DACR_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("SMT_SIF_ADCL_EN PGA",
        HI6555C_SMT_CLK_EN_CFG_ADDR,
        HI6555C_SMT_ADCL_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("SMT_SIF_ADCR_EN PGA",
        HI6555C_SMT_CLK_EN_CFG_ADDR,
        HI6555C_SMT_ADCR_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_DAC_E("SMT_SIF_DACL_EN DAC",
        "Playback",
        HI6555C_DDR_CODEC_VIR1_ADDR,
        DDR_CODEC_BIT5,
        0/* not INVERT */,
        hi6555c_dacl_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_DAC_E("SMT_SIF_DACR_EN DAC",
        "Playback",
        HI6555C_DDR_CODEC_VIR1_ADDR,
        DDR_CODEC_BIT6,
        0/* not INVERT */,
        hi6555c_dacr_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_PGA("S1_IF_CLK_EN PGA",
        HI6555C_IF_CLK_EN_CFG_ADDR,
        HI6555C_S1_IF_CLK_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("S2_IF_CLK_EN PGA",
        HI6555C_IF_CLK_EN_CFG_ADDR,
        HI6555C_S2_IF_CLK_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("S3_IF_CLK_EN PGA",
        HI6555C_IF_CLK_EN_CFG_ADDR,
        HI6555C_S3_IF_CLK_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("ADCL_PGA_EN PGA",
        HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
        HI6555C_ADCL_PGA_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("SIDETONE_PGA_EN PGA",
        HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
        HI6555C_SIDETONE_PGA_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA_S("SMT_LINEPGAR_PD PGA",
        0,
        SND_SOC_NOPM,
        0,
        0,
        hi6555c_smt_lineinr_pga_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_PGA_S("SMT_LINEPGAL_PD PGA",
        0,
        SND_SOC_NOPM,
        0,
        0,
        hi6555c_smt_lineinl_pga_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_PGA("SMT_AUXPGA_PD PGA",
        HI6555C_SMT_CODEC_ANA_RW01_ADDR,
        HI6555C_SMT_AUXPGA_PD_BIT_START,
        1/* INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA("SMT_MAINPGA_PD PGA",
        HI6555C_SMT_CODEC_ANA_RW01_ADDR,
        HI6555C_SMT_MAINPGA_PD_BIT_START,
        1/* INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_PGA_E("SMT_DACL_MIXER PGA",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        NULL,
        0,
        hi6555c_dacl_mixer_en_pga_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_PGA_E("SMT_DACR_MIXER PGA",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        NULL,
        0,
        hi6555c_dacr_mixer_en_pga_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_DAC_E("SMT_HS_PREPROCESS DAC",
        "Playback",
        HI6555C_DDR_CODEC_VIR0_ADDR,
        DDR_CODEC_BIT28,
        0/* not INVERT */,
        hi6555c_hs_preprocess_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_DAC_E("SMT_MIXEROUT_DAC_PATH DAC",
        "Playback",
        HI6555C_DDR_CODEC_VIR0_ADDR,
        DDR_CODEC_BIT29,
        0/* not INVERT */,
        hi6555c_dac_path_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_PGA_S("SMT_MIXEROUT_LINEIN_PATH DAC",
        1,
        SND_SOC_NOPM,
        0,
        0,
        hi6555c_linein_path_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_PGA_E("DACL_AGC_EN PGA",
        HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
        HI6555C_DACL_AGC_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0,
        hi6555c_dacl_agc_en_pga_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_PGA_E("DACR_AGC_EN PGA",
        HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
        HI6555C_DACR_AGC_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0,
        hi6555c_dacr_agc_en_pga_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_PGA_E("ADCR_PGA_EN PGA",
        HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
        HI6555C_ADCR_PGA_EN_BIT_START,
        0/* not INVERT */,
        NULL,
        0,
        hi6555c_adcr_pga_en_pga_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_PGA_E("ADCL_FILTER_EN PGA",
        HI6555C_DDR_CODEC_VIR1_ADDR,
        DDR_CODEC_BIT0,
        0/* not INVERT */,
        NULL,
        0,
        hi6555c_adcl_pga_en_pga_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_MIXER("S2_OL_MIXER_EN MIXER",
        HI6555C_IF_CLK_EN_CFG_ADDR,
        HI6555C_S2_OL_MIXER_EN_BIT_START,
        0/* not INVERT */,
        hi6555c_s2_ol_mixer_en_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_s2_ol_mixer_en_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("VOICE_DL_EN MIXER",
        HI6555C_MUX_TOP_MODULE_CFG_ADDR,
        7,
        0/* not INVERT */,
        hi6555c_voice_dlink_mixer_en_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_voice_dlink_mixer_en_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("S1_IF_TX_ENA MIXER",
        HI6555C_I2S_CFG_ADDR,
        HI6555C_S1_IF_TX_ENA_BIT_START,
        0/* not INVERT */,
        hi6555c_s1_if_tx_ena_mixer_en_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_s1_if_tx_ena_mixer_en_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("S1_IF_RX_ENA MIXER",
        HI6555C_I2S_CFG_ADDR,
        HI6555C_S1_IF_RX_ENA_BIT_START,
        0/* not INVERT */,
        hi6555c_s1_if_rx_ena_mixer_en_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_s1_if_rx_ena_mixer_en_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("S2_IF_TX_ENA MIXER",
        HI6555C_I2S_CFG_ADDR,
        HI6555C_S2_IF_TX_ENA_BIT_START,
        0/* not INVERT */,
        hi6555c_s2_if_tx_ena_mixer_en_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_s2_if_tx_ena_mixer_en_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("S2_IF_RX_ENA MIXER",
        HI6555C_I2S_CFG_ADDR,
        HI6555C_S2_IF_RX_ENA_BIT_START,
        0/* not INVERT */,
        hi6555c_s2_if_rx_ena_mixer_en_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_s2_if_rx_ena_mixer_en_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("S3_IF_TX_ENA MIXER",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR,
        HI6555C_S3_IF_TX_ENA_BIT_START,
        0/* not INVERT */,
        hi6555c_s3_if_tx_ena_mixer_en_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_s3_if_tx_ena_mixer_en_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("S3_IF_RX_ENA MIXER",
        HI6555C_THIRDMD_PCM_PGA_CFG_ADDR,
        HI6555C_S3_IF_RX_ENA_BIT_START,
        0/* not INVERT */,
        hi6555c_s3_if_rx_ena_mixer_en_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_s3_if_rx_ena_mixer_en_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("DACL_MIXER_EN MIXER",
        HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
        HI6555C_DACL_MIXER_EN_BIT_START,
        0/* not INVERT */,
        hi6555c_dacl_mixer_en_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_dacl_mixer_en_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("DACR_MIXER_EN MIXER",
        HI6555C_DIG_FILTER_CLK_EN_CFG_ADDR,
        HI6555C_DACR_MIXER_EN_BIT_START,
        0/* not INVERT */,
        hi6555c_dacr_mixer_en_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_dacr_mixer_en_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("SIF_EN MIXER",
        HI6555C_DMIC_SIF_CFG_ADDR,
        HI6555C_SIF_EN_BIT_START,
        0/* not INVERT */,
        hi6555c_sif_en_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_sif_en_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("SMT_MIXOUT_EAR_PU MIXER",
        HI6555C_SMT_CODEC_ANA_RW39_ADDR,
        HI6555C_SMT_MIXOUT_EAR_PU_BIT_START,
        0/* not INVERT */,
        hi6555c_smt_mixout_ear_pu_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_smt_mixout_ear_pu_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("SMT_SIF_EN MIXER",
        HI6555C_SMT_CLK_EN_CFG_ADDR,
        HI6555C_SMT_SIF_EN_BIT_START,
        0/* not INVERT */,
        hi6555c_smt_sif_en_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_smt_sif_en_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("SMT_ADCR_PD MIXER",
        HI6555C_SMT_CODEC_ANA_RW01_ADDR,
        HI6555C_SMT_ADCR_PD_BIT_START,
        1/* INVERT */,
        hi6555c_smt_adcr_pd_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_smt_adcr_pd_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER("SMT_ADCL_PD MIXER",
        HI6555C_SMT_CODEC_ANA_RW01_ADDR,
        HI6555C_SMT_ADCL_PD_BIT_START,
        1/* INVERT */,
        hi6555c_smt_adcl_pd_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_smt_adcl_pd_mixer_dapm_controls)),

    SND_SOC_DAPM_MIXER_E("SMT_MIXOUT_HSLR_PD MIXER",
        HI6555C_DDR_CODEC_VIR1_ADDR,
        DDR_CODEC_BIT1,
        0/* INVERT */,
        hi6555c_smt_mixout_hslr_pd_mixer_dapm_controls,
        ARRAY_SIZE(hi6555c_smt_mixout_hslr_pd_mixer_dapm_controls),
        hi6555c_smt_hslr_pd_mixer_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_MUX("RM_CODEC_DAC2ADC MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_rm_codec_dac2adc_mux_dapm_controls),

    SND_SOC_DAPM_MUX("LM_CODEC_DAC2ADC MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_lm_codec_dac2adc_mux_dapm_controls),

    SND_SOC_DAPM_MUX("STEREO_UPLINK_L_FIFO_DIN_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_stereo_uplink_l_fifo_din_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("STEREO_UPLINK_R_FIFO_DIN_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_stereo_uplink_r_fifo_din_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("VOICE_UPLINK_L_FIFO_DIN_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_voice_uplink_l_fifo_din_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("VOICE_UPLINK_R_FIFO_DIN_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_voice_uplink_r_fifo_din_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("THIRDMD_UPLINK_DIN_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_thirdmd_uplink_din_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("S2_DOUT_LEFT_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_s2_dout_left_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("S1_DOUT_TEST_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_s1_dout_test_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("S2_DOUT_TEST_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_s2_dout_test_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("STEREO_DLINK_TEST_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_stereo_dlink_test_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("VOICE_DLINK_DIN_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_voice_dlink_din_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("VOICE_DLINK_TEST_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_voice_dlink_test_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("S3_DIN_TEST_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_s3_din_test_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("S3_DOUT_LEFT_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_s3_dout_left_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("S3_DOUT_RIGHT_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_s3_dout_right_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("THIRDMD_DLINK_DIN_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_thirdmd_dlink_din_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("THIRDMD_DLINK_TEST_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_thirdmd_dlink_test_sel_mux_dapm_controls),

    SND_SOC_DAPM_MUX("SMT_MAINPGA_SEL MUX",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        &hi6555c_smt_mainpga_sel_mux_dapm_controls),

    SND_SOC_DAPM_SWITCH("HS_LINEIN_SEL_VIR SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_hs_linein_sel_vir_switch_dapm_controls),

    SND_SOC_DAPM_SWITCH("HS_DAC_SEL_VIR SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_hs_dac_sel_vir_switch_dapm_controls),

    SND_SOC_DAPM_SWITCH("DAC_P2S_LOOPBACK SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_dac_p2s_loopback_switch_dapm_controls),

    SND_SOC_DAPM_SWITCH("SIF_S2P_LOOPBACK SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_sif_s2p_loopback_switch_dapm_controls),

    SND_SOC_DAPM_SWITCH("DMIC_EN SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_dmic_en_switch_dapm_controls),

    /* ADD FOR ANA LOOPBACK */
    SND_SOC_DAPM_SWITCH("ANA_LOOPBACK SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_ana_loopback_switch_dapm_controls),

    SND_SOC_DAPM_SWITCH("SMT_SIF_EN_V2 SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_smt_sif_en_switch_dapm_controls),

    SND_SOC_DAPM_SWITCH_E("THIRDMD_DLINK_EN SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_thirdmd_dlink_en_switch_dapm_controls,
        hi6555c_thirdmd_dlink_fifo_power_mode_event,
        SND_SOC_DAPM_POST_PMU),

    SND_SOC_DAPM_SWITCH_E("THIRDMD_UPLINK_EN SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_thirdmd_uplink_en_switch_dapm_controls,
        hi6555c_thirdmd_uplink_fifo_power_mode_event,
        SND_SOC_DAPM_POST_PMU),

    SND_SOC_DAPM_SWITCH("CLASSD VIR_SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_classd_virtual_switch_dapm_controls),

    SND_SOC_DAPM_SWITCH("RCV VIR_SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_rcv_virtual_switch_dapm_controls),

    SND_SOC_DAPM_SWITCH_E("STEREO_UPLINK_L_EN SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_stereo_uplink_l_en_switch_dapm_controls,
        hi6555c_stereo_uplink_fifo_power_mode_event,
        SND_SOC_DAPM_POST_PMU),

    SND_SOC_DAPM_SWITCH_E("STEREO_UPLINK_R_EN SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_stereo_uplink_r_en_switch_dapm_controls,
        hi6555c_stereo_uplink_fifo_power_mode_event,
        SND_SOC_DAPM_POST_PMU),

    SND_SOC_DAPM_SWITCH_E("VOICE_UPLINK_L_EN SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_voice_uplink_l_en_switch_dapm_controls,
        hi6555c_voice_uplink_fifo_power_mode_event,
        SND_SOC_DAPM_POST_PMU),

    SND_SOC_DAPM_SWITCH_E("VOICE_UPLINK_R_EN SWITCH",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        hi6555c_voice_uplink_r_en_switch_dapm_controls,
        hi6555c_voice_uplink_fifo_power_mode_event,
        SND_SOC_DAPM_POST_PMU),

    SND_SOC_DAPM_MICBIAS("SMT_HSMICB_PD MICBIAS",
        SND_SOC_NOPM/*HI6555C_SMT_CODEC_ANA_RW02_ADDR*/,
        HI6555C_SMT_HSMICB_PD_BIT_START,
        1/* INVERT */),

    SND_SOC_DAPM_MICBIAS("SMT_MICB1_PD MICBIAS",
        HI6555C_SMT_CODEC_ANA_RW02_ADDR,
        HI6555C_SMT_MICB1_PD_BIT_START,
        1/* INVERT */),

    SND_SOC_DAPM_OUT_DRV("SMT_EAR_PU PGA",
        HI6555C_SMT_CODEC_ANA_RW39_ADDR,
        HI6555C_SMT_EAR_PU_BIT_START,
        0/* not INVERT */,
        NULL,
        0),

    SND_SOC_DAPM_OUT_DRV_E("SMT_HSLR_PD PGA",
        HI6555C_DDR_CODEC_VIR1_ADDR,
        DDR_CODEC_BIT2,
        0/*not INVERT */,
        NULL,
        0,
        hi6555c_smt_hslr_pd_outdrv_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_OUT_DRV_E("PMU_CLASSD_PU PGA",
        SND_SOC_NOPM,
        0,
        0/* not INVERT */,
        NULL,
        0,
        hi6555c_pmu_classd_pd_outdrv_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    /* SUPPLY */
    SND_SOC_DAPM_SUPPLY("PLL",
        SND_SOC_NOPM,
        0,
        0,
        hi6555c_pll_supply_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_SUPPLY("Backup_PLL",
        SND_SOC_NOPM,
        0,
        0,
        hi6555c_backuppll_supply_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_SUPPLY("SOC_IBIAS",
        SND_SOC_NOPM,
        0,
        0,
        hi6555c_soc_ibias_supply_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    SND_SOC_DAPM_SUPPLY("SMT_IBIAS",
        SND_SOC_NOPM,
        0,
        0,
        hi6555c_smt_ibias_supply_power_mode_event,
        (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),

    /* MIC */
    SND_SOC_DAPM_MIC("SMT_MICB1",hi6555c_smt_micb1_power_mode_event),
    SND_SOC_DAPM_MIC("SMT_HSMICB",hi6555c_smt_hsmicb_power_mode_event),
};


/*****************************************************************************
  Route Map
*****************************************************************************/
static const struct snd_soc_dapm_route hi6555c_route_map[] =
{
    /* audio play route soc */
    {"STEREO_DLINK_TEST_SEL MUX",               "APB",                  "AUDIO_DLINK INPUT"},
    {"STEREO_DLINK_L_EN PGA",                       NULL,                   "STEREO_DLINK_TEST_SEL MUX"},
    {"STEREO_DLINK_R_EN PGA",                      NULL,                   "STEREO_DLINK_TEST_SEL MUX"},
    {"DACL_MIXER_EN MIXER",            "DACL_MIXER_IN2_MUTE",  "STEREO_DLINK_L_EN PGA"},
    {"DACR_MIXER_EN MIXER",           "DACR_MIXER_IN2_MUTE",  "STEREO_DLINK_R_EN PGA"},
    {"DACL_AGC_EN PGA",                                NULL,                   "DACL_MIXER_EN MIXER"},
    {"DACR_AGC_EN PGA",                               NULL,                   "DACR_MIXER_EN MIXER"},
    {"SIF_DACL_EN PGA",                                 NULL,                    "DACL_AGC_EN PGA"},
    {"SIF_DACR_EN PGA",                                NULL,                    "DACR_AGC_EN PGA"},
    {"SMT_SIF_DACL_EN DAC",                        NULL,                    "SMT_ANA_DAC_SDATA INPUT"},
    {"SMT_SIF_DACR_EN DAC",                       NULL,                    "SMT_ANA_DAC_SDATA INPUT"},
    {"HS_DAC_SEL_VIR SWITCH",                   "DAC",                   "SMT_SIF_DACL_EN DAC"},
    {"HS_DAC_SEL_VIR SWITCH",                   "DAC",                   "SMT_SIF_DACR_EN DAC"},
    {"HS_LINEIN_SEL_VIR SWITCH",                "LINEIN",               "SMT_LINEPGAR_PD PGA"},
    {"HS_LINEIN_SEL_VIR SWITCH",                "LINEIN",               "SMT_LINEPGAL_PD PGA"},
    {"SMT_HS_PREPROCESS DAC",                   NULL,                   "HS_DAC_SEL_VIR SWITCH"},
    {"SMT_HS_PREPROCESS DAC",                   NULL,                   "HS_LINEIN_SEL_VIR SWITCH"},
    {"SMT_MIXEROUT_DAC_PATH DAC",           NULL,                    "SMT_HS_PREPROCESS DAC"},
    {"SMT_MIXEROUT_LINEIN_PATH DAC",        NULL,                    "SMT_HS_PREPROCESS DAC"},

    /* audio play hs route smartstar */
    {"SMT_MIXOUT_HSLR_PD MIXER",              "DACLR",               "SMT_MIXEROUT_DAC_PATH DAC"},
    {"SMT_MIXOUT_HSLR_PD MIXER",              "LINEINLR",            "SMT_MIXEROUT_LINEIN_PATH DAC"},
    {"SMT_HSLR_PD PGA",                               NULL,                    "SMT_MIXOUT_HSLR_PD MIXER"},
    {"SMT_HP_LR OUTPUT",                              NULL,                    "SMT_HSLR_PD PGA"},

    /* audio play rcv route smartstar */
    {"SMT_MIXOUT_EAR_PU MIXER",                 "DACL",                "SMT_DACL_MIXER PGA"},
    {"SMT_MIXOUT_EAR_PU MIXER",                 "DACR",               "SMT_DACR_MIXER PGA"},
    {"SMT_MIXOUT_EAR_PU MIXER",                 "LINEINR",            "SMT_LINEPGAR_PD PGA"},
    {"SMT_MIXOUT_EAR_PU MIXER",                 "LINEINL",             "SMT_LINEPGAL_PD PGA"},
    {"RCV VIR_SWITCH",                                 "RCV_EN",             "SMT_MIXOUT_EAR_PU MIXER"},
    {"SMT_EAR_PU PGA",                                  NULL,                    "RCV VIR_SWITCH"},
    {"SMT_RECV OUTPUT",                                NULL,                   "SMT_EAR_PU PGA"},
    {"SMT_DACL_MIXER PGA",                           NULL,                   "SMT_SIF_DACL_EN DAC"},
    {"SMT_DACR_MIXER PGA",                          NULL,                    "SMT_SIF_DACR_EN DAC"},

    /* audio play classd route pmu */
    {"CLASSD VIR_SWITCH",                       "CLASSD_EN",           "SMT_MIXOUT_EAR_PU MIXER"},
    {"PMU_CLASSD_PU PGA",                           NULL,                    "CLASSD VIR_SWITCH"},
    {"PMU_CLASSD OUTPUT",                           NULL,                    "PMU_CLASSD_PU PGA"},

    /* audio capture route smartstar */
    {"SMT_MAINPGA_SEL MUX",                       "MIC",                   "SMT_MAINMIC INPUT"},
    {"SMT_MAINPGA_SEL MUX",                     "HP_MIC",                "SMT_HPMIC INPUT"},
    {"SMT_MAINPGA_PD PGA",                         NULL,                    "SMT_MAINPGA_SEL MUX"},
    {"SMT_AUXPGA_PD PGA",                          NULL,                    "SMT_AUXMIC INPUT"},
    {"SMT_LINEPGAL_PD PGA",                        NULL,                    "SMT_LINEIN_L INPUT"},
    {"SMT_LINEPGAR_PD PGA",                        NULL,                    "SMT_LINEIN_R INPUT"},
    {"SMT_ADCL_PD MIXER",                         "MAINPGA",             "SMT_MAINPGA_PD PGA"},
    {"SMT_ADCL_PD MIXER",                         "AUXPGA",              "SMT_AUXPGA_PD PGA"},
    {"SMT_ADCL_PD MIXER",                         "LINEINL",               "SMT_LINEPGAL_PD PGA"},
    {"SMT_ADCL_PD MIXER",                         "LINEINR",               "SMT_LINEPGAR_PD PGA"},
    {"SMT_ADCR_PD MIXER",                         "MAINPGA",            "SMT_MAINPGA_PD PGA"},
    {"SMT_ADCR_PD MIXER",                         "AUXPGA",              "SMT_AUXPGA_PD PGA"},
    {"SMT_ADCR_PD MIXER",                         "LINEINL",               "SMT_LINEPGAL_PD PGA"},
    {"SMT_ADCR_PD MIXER",                       "LINEINR",                "SMT_LINEPGAR_PD PGA"},
    {"SMT_SIF_ADCL_EN PGA",                         NULL,                   "SMT_ADCL_PD MIXER"},
    {"SMT_SIF_ADCR_EN PGA",                        NULL,                   "SMT_ADCR_PD MIXER"},
    {"SMT_ANA_ADC_SDATA OUTPUT",             NULL,                    "SMT_SIF_ADCL_EN PGA"},
    {"SMT_ANA_ADC_SDATA OUTPUT",              NULL,                   "SMT_SIF_ADCR_EN PGA"},

    /* audio capture route SoC */
    {"SIF_ADCL_EN PGA",                                NULL,                   "DIGI_ADC_UL INPUT"},
    {"SIF_ADCR_EN PGA",                                NULL,                   "DIGI_ADC_UR INPUT"},
    {"LM_CODEC_DAC2ADC MUX",               "CIC_ADC",              "SIF_ADCL_EN PGA"},
    {"RM_CODEC_DAC2ADC MUX",               "CIC_ADC",             "SIF_ADCR_EN PGA"},
    {"ADCL_FILTER_EN PGA",                            NULL,                  "LM_CODEC_DAC2ADC MUX"},
    {"ADCL_PGA_EN PGA",                                NULL,                  "ADCL_FILTER_EN PGA"},
    {"SIDETONE_PGA_EN PGA",                         NULL,                  "ADCL_FILTER_EN PGA"},
    {"ADCR_PGA_EN PGA",                               NULL,                  "RM_CODEC_DAC2ADC MUX"},
    {"STEREO_UPLINK_L_FIFO_DIN_SEL MUX",  "ADCL",                "ADCL_PGA_EN PGA"},
    {"STEREO_UPLINK_R_FIFO_DIN_SEL MUX",  "ADCR",               "ADCR_PGA_EN PGA"},
    {"STEREO_UPLINK_L_EN SWITCH",      "STEREO_UP_L_EN",     "STEREO_UPLINK_L_FIFO_DIN_SEL MUX"},
    {"STEREO_UPLINK_R_EN SWITCH",     "STEREO_UP_R_EN",     "STEREO_UPLINK_R_FIFO_DIN_SEL MUX"},
    {"AUDIO_UL OUTPUT",                                 NULL,                 "STEREO_UPLINK_L_EN SWITCH"},
    {"AUDIO_UR OUTPUT",                                 NULL,                "STEREO_UPLINK_R_EN SWITCH"},

    /* voice uplink route SoC */
    {"VOICE_UPLINK_L_FIFO_DIN_SEL MUX",      "ADCL",             "ADCL_PGA_EN PGA"},
    {"VOICE_UPLINK_R_FIFO_DIN_SEL MUX",      "ADCR",            "ADCR_PGA_EN PGA"},
    {"VOICE_UPLINK_L_EN SWITCH",      "VOICE_UPLINK_L_EN",  "VOICE_UPLINK_L_FIFO_DIN_SEL MUX"},
    {"VOICE_UPLINK_R_EN SWITCH",     "VOICE_UPLINK_R_EN",  "VOICE_UPLINK_R_FIFO_DIN_SEL MUX"},
    {"VOICE_UL OUTPUT",                                 NULL,                 "VOICE_UPLINK_L_EN SWITCH"},
    {"VOICE_UR OUTPUT",                                 NULL,                "VOICE_UPLINK_R_EN SWITCH"},

    /* voice uplink route BT SoC */
    {"S2_IL_PGA_EN PGA",                                NULL,                "I2S1_2_3 INPUT"},
    {"S2_IR_PGA_EN PGA",                                NULL,                "I2S1_2_3 INPUT"},
    {"VOICE_UPLINK_L_FIFO_DIN_SEL MUX",      "S2",                "S2_IL_PGA_EN PGA"},
    {"VOICE_UPLINK_R_FIFO_DIN_SEL MUX",      "S2",               "S2_IR_PGA_EN PGA"},

    /* voice downlink route SoC */
    {"VOICE_DLINK_DIN_SEL MUX",                   "APB",               "VOICE_DL INPUT"},
    {"VOICE_DLINK_DIN_SEL MUX",                   "S3",                 "I2S1_2_3 INPUT"},
    {"VOICE_DLINK_EN PGA",                            NULL,                "VOICE_DLINK_DIN_SEL MUX"},
    {"VOICE_DL_EN MIXER",      "VOICE_DL_MIXER_IN1_MUTE",  "VOICE_DLINK_EN PGA"},
    {"VOICE_DL_EN MIXER",     "VOICE_DL_MIXER_IN2_MUTE",   "SIDETONE_PGA_EN PGA"},
    {"DACL_MIXER_EN MIXER",     "DACL_MIXER_IN1_MUTE",      "VOICE_DL_EN MIXER"},
    {"DACR_MIXER_EN MIXER",       "DACR_MIXER_IN1_MUTE",   "VOICE_DL_EN MIXER"},
    {"DACL_MIXER_EN MIXER",      "DACL_MIXER_IN4_MUTE",     "SIDETONE_PGA_EN PGA"},
    {"DACR_MIXER_EN MIXER",        "DACR_MIXER_IN4_MUTE",  "SIDETONE_PGA_EN PGA"},

    {"S1_DOUT_TEST_SEL MUX",                    "DACL_MIXER_DACR_MIXER",  "DACL_MIXER_EN MIXER"},
    {"S1_DOUT_TEST_SEL MUX",                    "DACL_MIXER_DACR_MIXER",  "DACR_MIXER_EN MIXER"},
    {"S1_DOUT_TEST_SEL MUX",                    "ADCL_ADCR",           "ADCL_PGA_EN PGA"},
    {"S1_DOUT_TEST_SEL MUX",                    "ADCL_ADCR",           "ADCR_PGA_EN PGA"},
    {"I2S1_2_3 OUTPUT",                         NULL,                  "S1_DOUT_TEST_SEL MUX"},
    /* voice downlink route SoC(bt) */
    {"S2_OL_MIXER_EN MIXER",      "S2_OL_MIXER_IN1_MUTE",    "DACL_MIXER_EN MIXER"},
    {"S2_OL_MIXER_EN MIXER",      "S2_OL_MIXER_IN2_MUTE",    "DACR_MIXER_EN MIXER"},
    {"S2_DOUT_LEFT_SEL MUX",      "SRC3",                                "S2_OL_MIXER_EN MIXER"},
    {"S2_DOUT_LEFT_SEL MUX",      "VOICE_DLINK_PGA",            "VOICE_DLINK_EN PGA"},
    {"S2_DOUT_TEST_SEL MUX",     "VOICE_DLINK_PGA_S2",       "S2_DOUT_LEFT_SEL MUX"},
    {"S2_DOUT_TEST_SEL MUX",     "DACL_MIXER",                      "DACL_MIXER_EN MIXER"},
    {"I2S1_2_3 OUTPUT",                NULL,                                    "S2_DOUT_TEST_SEL MUX"},
    {"S1_IF_TX_ENA MIXER",                      "ADC_LR",              "I2S1_2_3 INPUT"},
    {"S1_IF_TX_ENA MIXER",                      "DAC_LR",              "I2S1_2_3 INPUT"},
    {"S1_IF_RX_ENA MIXER",                      "FM_L",                "I2S1_2_3 INPUT"},
    {"S1_IF_RX_ENA MIXER",                      "FM_R",                "I2S1_2_3 INPUT"},
    {"S1_IF_CLK_EN PGA",             NULL,                  "S1_IF_TX_ENA MIXER"},
    {"S1_IF_CLK_EN PGA",             NULL,                  "S1_IF_RX_ENA MIXER"},
    {"I2S1_2_3 OUTPUT",               NULL,                  "S1_IF_CLK_EN PGA"},
    {"S2_IF_TX_ENA MIXER",                      "DACL",                "I2S1_2_3 INPUT"},
    {"S2_IF_TX_ENA MIXER",                      "VOICE_DLINK",         "I2S1_2_3 INPUT"},
    {"S2_IF_RX_ENA MIXER",                      "VOICE_UL",            "I2S1_2_3 INPUT"},
    {"S2_IF_RX_ENA MIXER",                      "VOICE_UR",            "I2S1_2_3 INPUT"},
    {"S2_IF_CLK_EN PGA",             NULL,                  "S2_IF_TX_ENA MIXER"},
    {"S2_IF_CLK_EN PGA",             NULL,                  "S2_IF_RX_ENA MIXER"},
    {"I2S1_2_3 OUTPUT",               NULL,                  "S2_IF_CLK_EN PGA"},
    {"S3_IF_TX_ENA MIXER",                      "VOICE_DL",            "I2S1_2_3 INPUT"},
    {"S3_IF_TX_ENA MIXER",                      "VOICE_DR",            "I2S1_2_3 INPUT"},
    {"S3_IF_RX_ENA MIXER",                      "VOICE_UP",            "I2S1_2_3 INPUT"},
    {"S3_IF_CLK_EN PGA",             NULL,                  "S3_IF_TX_ENA MIXER"},
    {"S3_IF_CLK_EN PGA",             NULL,                  "S3_IF_RX_ENA MIXER"},
    {"I2S1_2_3 OUTPUT",               NULL,                  "S3_IF_CLK_EN PGA"},

    /* fm digital */
    {"S1_IL_PGA_EN PGA",            NULL,          "I2S1_2_3 INPUT"},
    {"S1_IR_PGA_EN PGA",            NULL,         "I2S1_2_3 INPUT"},
    {"DACL_MIXER_EN MIXER",      "DACL_MIXER_IN3_MUTE", "S1_IL_PGA_EN PGA"},
    {"DACR_MIXER_EN MIXER",     "DACR_MIXER_IN3_MUTE", "S1_IR_PGA_EN PGA"},

    /* 3rd modem uplink */
    {"THIRDMD_UPLINK_DIN_SEL MUX",    "S3",         "I2S1_2_3 INPUT"},
    {"THIRDMD_UPLINK_DIN_SEL MUX",    "ADCR",    "ADCR_PGA_EN PGA"},
    {"THIRDMD_UPLINK_EN SWITCH",  "THIRDMD_UPLINK_EN",   "THIRDMD_UPLINK_DIN_SEL MUX"},
    {"THIRDMD_UP OUTPUT",                     NULL,       "THIRDMD_UPLINK_EN SWITCH"},

    /* 3rd modem downlink */
    {"THIRDMD_DLINK_DIN_SEL MUX",   "APB_THIRDMD",             "THIRDMD_DOWN INPUT"},
    {"THIRDMD_DLINK_EN SWITCH",      "THIRDMD_DLINK_EN",    "THIRDMD_DLINK_DIN_SEL MUX"},
    {"S3_DOUT_RIGHT_SEL MUX",          "THIRDMD_DLINK_PGA",  "THIRDMD_DLINK_EN SWITCH"},
    {"S3_DOUT_RIGHT_SEL MUX",          "ADCR_PGA",                  "ADCR_PGA_EN PGA"},
    {"S3_DOUT_RIGHT_SEL MUX",          "OTHER",                        "I2S1_2_3 INPUT"},
    {"I2S1_2_3 OUTPUT",                        NULL,                            "S3_DOUT_RIGHT_SEL MUX"},
    {"S3_DOUT_LEFT_SEL MUX",             "THIRDMD_DLINK_PGA", "THIRDMD_DLINK_EN SWITCH"},
    {"S3_DOUT_LEFT_SEL MUX",             "ADCL_PGA",                  "ADCL_PGA_EN PGA"},
    {"I2S1_2_3 OUTPUT",                        NULL,                            "S3_DOUT_LEFT_SEL MUX"},

    /* DMIC */
    {"DMIC_EN SWITCH",                       "DMIC_EN",                    "DMIC INPUT"},
    {"RM_CODEC_DAC2ADC MUX",         "CIC_DMIC_PORT0",       "DMIC_EN SWITCH"},
    {"LM_CODEC_DAC2ADC MUX",          "CIC_DMIC_PORT0",      "DMIC_EN SWITCH"},

    /* sif interface */
    {"SIF_EN MIXER",                            "SIF_DACL_EN",         "SIF_DACL_EN PGA"},
    {"SIF_EN MIXER",                            "SIF_DACR_EN",         "SIF_DACR_EN PGA"},
    {"SIF_EN MIXER",                            "SIF_ADCL_EN",          "SIF_EN INPUT"},
    {"SIF_EN MIXER",                            "SIF_ADCR_EN",          "SIF_EN INPUT"},
    {"SIF_EN OUTPUT",                           NULL,                        "SIF_EN MIXER"},
    {"SMT_SIF_EN MIXER",                     "SIF_HSLR_EN",          "SIF_EN INPUT"},
    {"SMT_SIF_EN MIXER",                     "SIF_CLASSD_EN",     "SIF_EN INPUT"},
    {"SMT_SIF_EN MIXER",                     "SIF_RCV_EN",           "SIF_EN INPUT"},
    {"SMT_SIF_EN MIXER",                     "SIF_MIC1_EN",          "SIF_EN INPUT"},
    {"SMT_SIF_EN MIXER",                     "SIF_MIC2_EN",          "SIF_EN INPUT"},
    {"SMT_SIF_EN MIXER",                     "SIF_LINEINL_EN",      "SIF_EN INPUT"},
    {"SMT_SIF_EN MIXER",                     "SIF_LINEINR_EN",      "SIF_EN INPUT"},
    {"SIF_EN OUTPUT",                           NULL,                         "SMT_SIF_EN MIXER"},

    /* PLL & IBIAS */
    {"S1_IF_CLK_EN PGA",                        NULL,                  "SMT_IBIAS"},
    {"S2_IF_CLK_EN PGA",                        NULL,                  "SMT_IBIAS"},
    {"S3_IF_CLK_EN PGA",                        NULL,                  "SMT_IBIAS"},
    {"SMT_MIXOUT_HSLR_PD MIXER",        NULL,                  "SMT_IBIAS"},
    {"SMT_MIXOUT_EAR_PU MIXER",          NULL,                  "SMT_IBIAS"},
    {"SMT_ADCL_PD MIXER",                     NULL,                  "SMT_IBIAS"},
    {"SMT_ADCR_PD MIXER",                     NULL,                  "SMT_IBIAS"},
    {"SMT_MAINMIC INPUT",                      NULL,                  "SMT_MICB1"},
    {"SMT_AUXMIC INPUT",                        NULL,                  "SMT_MICB1"},
    {"SMT_HPMIC INPUT",                          NULL,                  "SMT_HSMICB"},
    {"SMT_ADCR_PD MIXER",                     NULL,                  "PLL"},
    {"SMT_ADCL_PD MIXER",                      NULL,                  "PLL"},
    {"SMT_SIF_DACR_EN DAC",                  NULL,                  "PLL"},
    {"SMT_SIF_DACL_EN DAC",                   NULL,                  "PLL"},
    {"S1_IF_CLK_EN PGA",                          NULL,                  "PLL"},
    {"S2_IF_CLK_EN PGA",                          NULL,                  "PLL"},
    {"S3_IF_CLK_EN PGA",                          NULL,                  "PLL"},
    {"DACL_MIXER_EN MIXER",                    NULL,                  "PLL"},
    {"DACR_MIXER_EN MIXER",                   NULL,                  "PLL"},
    {"ADCL_PGA_EN PGA",                          NULL,                  "PLL"},
    {"ADCR_PGA_EN PGA",                         NULL,                   "PLL"},
    {"SMT_LINEPGAL_PD PGA",                    NULL,                  "Backup_PLL"},
    {"SMT_LINEPGAR_PD PGA",                   NULL,                  "Backup_PLL"},

    /* ANA LOOPBACK*/
    {"ANA_LOOPBACK SWITCH",        "ANA_LOOPBACK" ,       "SMT_ADCL_PD MIXER"},
    {"ANA_LOOPBACK SWITCH",        "ANA_LOOPBACK" ,       "SMT_ADCR_PD MIXER"},
    {"SMT_SIF_DACL_EN DAC",                   NULL ,                 "ANA_LOOPBACK SWITCH"},
    {"SMT_SIF_DACR_EN DAC",                  NULL ,                 "ANA_LOOPBACK SWITCH"},
};

/*****************************************************************************
* CONTROL WIDGET AREA END
*****************************************************************************/
/*
 *provide to Flash Driver
 *mute :
 */
void audio_codec_mute_pga(enum hi6555c_mute mute)
{
    if (MUTE_PGA == mute) {
        hi6555c_set_reg_bits(HI6555C_STEREO_DLINK_PGA_CFG_ADDR, 0x01 << HI6555C_STEREO_DLINK_L_PGA_MUTE_BIT_START);
        hi6555c_set_reg_bits(HI6555C_STEREO_DLINK_PGA_CFG_ADDR, 0x01 << HI6555C_STEREO_DLINK_R_PGA_MUTE_BIT_START);
        hi6555c_set_reg_bits(HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, 0x01 << HI6555C_VOICE_DLINK_PGA_MUTE_BIT_START);
        logi("mute");
    } else {
        hi6555c_clr_reg_bits(HI6555C_STEREO_DLINK_PGA_CFG_ADDR, 0x01 << HI6555C_STEREO_DLINK_L_PGA_MUTE_BIT_START);
        hi6555c_clr_reg_bits(HI6555C_STEREO_DLINK_PGA_CFG_ADDR, 0x01 << HI6555C_STEREO_DLINK_R_PGA_MUTE_BIT_START);
        hi6555c_clr_reg_bits(HI6555C_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR, 0x01 << HI6555C_VOICE_DLINK_PGA_MUTE_BIT_START);
        logi("unmute");
    }

    return;
}
EXPORT_SYMBOL_GPL(audio_codec_mute_pga);


/*****************************************************************************
*
* HEADSET AREA BEGIN
*
*****************************************************************************/
/*
 *Codec power
 */
static void hi6555c_power_codec(struct snd_soc_codec *codec, int on)
{
    int ret = 0;
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

    if (!priv) {
        loge("priv is null\n");
        return;
    }

    if (on) {
        /* regulator */
#if 0//todo fixme: hi6250 fpga always poweron
        ret = regulator_enable(priv->regulator_avdd1v8);

        if (0 != ret) {
            loge("regulator_avdd1v8 en fail\n");
            return;
        }
//#else
        //ldo15 pmu power on
        hi6555c_reg_write(codec, (PAGE_SmartStarCODEC + SOC_SMART_ENABLE3_LDO9_16_ADDR(0)), 0x40);
#endif
        /* AVREF */
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW04_ADDR,
            ((0x01 << HI6555C_SMT_VREFSEL_BIT_START) |(0x01 << HI6555C_SMT_VREFSEL_BIT_END))/*quick*/);
        msleep(5);
        /* IBIAS */
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x01 << HI6555C_SMT_IBIAS_PD_BIT_START);

        /* AVREF */
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW04_ADDR,  (0x01 << HI6555C_SMT_VREFSEL_BIT_END)/*normal*/);
    } else {
        /* IBIAS */
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x01 << HI6555C_SMT_IBIAS_PD_BIT_START);
#if 0//todo fixme: hi6250 fpga always poweron
        ret = regulator_disable(priv->regulator_avdd1v8);

        if (0 != ret) {
            loge("regulator_avdd1v8 dis fail\n");
            return;
        }
//#else
        //ldo15 pmu power off
        hi6555c_reg_write(codec, (PAGE_SmartStarCODEC + SOC_SMART_DISABLE3_LDO9_16_ADDR(0)), 0x40);
#endif
    }
}

static inline void hi6555c_irqs_clr(unsigned int irqs)
{
    logd("IRQ=0x%x, irqs=0x%x\n", hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR), irqs);
    hi6555c_reg_write(g_codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR, irqs);
}

static inline void hi6555c_irqs_mask_set(unsigned int irqs)
{
    logd("IRQMb=0x%x, irqs=0x%x\n", hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR), irqs);
    hi6555c_set_reg_bits(HI6555C_SMT_ANA_IRQM_REG0_ADDR, irqs);
    logd("IRQMl=0x%x\n", hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR));
}

static inline void hi6555c_irqs_mask_clr(unsigned int irqs)
{
    logd("IRQMb=0x%x, irqs=0x%x\n", hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR), irqs);
    hi6555c_clr_reg_bits(HI6555C_SMT_ANA_IRQM_REG0_ADDR, irqs);
    logd("IRQMl=0x%x\n", hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR));
}

static void hi6555c_hs_micbias_poweroff(void)
{
    /* close normal comp */
    hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_MBHD_BUFF_PD_BIT_START);
    hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_MBHD_COMP_PD_BIT_START);

    /* eco disable */
    hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW23_ADDR, 0x1 << HI6555C_SMT_MBHD_ECO_EN_BIT_START);

    /* hs micbias */
    hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_HSMICB_PD_BIT_START);
    hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW23_ADDR, 0x1 << HI6555C_SMT_HSMICB_DSCHG_BIT_START);
    msleep(5);
    hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW23_ADDR, 0x1 << HI6555C_SMT_HSMICB_DSCHG_BIT_START);
}

static void hi6555c_hs_micbias_pd(struct snd_soc_codec *codec, bool enable)
{
    unsigned int irq_mask = 0;

    /* to avoid irq while MBHD_COMP power up£¬mask the irq then clean it */
    irq_mask = hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR);
    hi6555c_irqs_mask_set(irq_mask | IRQ_MSK_COMP);

    if (enable) {
        /*open ibias*/
        hi6555c_ibias_hsmicbias_enable(codec, true);

        /* mbhc eco disable */
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW23_ADDR, 0x1 << HI6555C_SMT_MBHD_ECO_EN_BIT_START);

        /* hs micbias */
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_HSMICB_PD_BIT_START);
        msleep(10);

        /* open normal compare */
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_MBHD_COMP_PD_BIT_START);
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_MBHD_BUFF_PD_BIT_START);
        usleep_range(100,150);
    } else {
        /* close normal comp */
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_MBHD_BUFF_PD_BIT_START);
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_MBHD_COMP_PD_BIT_START);

        /* hs micbias */
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_HSMICB_PD_BIT_START);
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW23_ADDR, 0x1 << HI6555C_SMT_HSMICB_DSCHG_BIT_START);
        msleep(5);
        hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW23_ADDR, 0x1 << HI6555C_SMT_HSMICB_DSCHG_BIT_START);
        hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW23_ADDR, 0x1 << HI6555C_SMT_MBHD_ECO_EN_BIT_START);
        msleep(20);

        /*close ibias*/
        hi6555c_ibias_hsmicbias_enable(codec, false);
        hi6555c_irqs_clr(IRQ_MSK_COMP);
        hi6555c_irqs_mask_clr(IRQ_MSK_BTN_ECO);
    }
}

static void hi6555c_hs_micbias_enable(struct snd_soc_codec *codec, bool enable)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

    if (!priv)
        return;

    /* hs_micbias power up,then power down 3 seconds later */
    cancel_delayed_work(&priv->hs_micbias_hkadc_dw);
    flush_workqueue(priv->hs_micbias_hkadc_dwq);

    if (enable) {
        if (((hi6555c_reg_read(codec, HI6555C_SMT_CODEC_ANA_RW02_ADDR))&(0x1 << HI6555C_SMT_HSMICB_PD_BIT_START))) /* read hs_micbias pd status */
            hi6555c_hs_micbias_pd(codec, true);
    } else {
        if ((0 == priv->hs_micbias_work) && !priv->hs_micbias_hkadc) {
            wake_lock_timeout(&priv->wake_lock, msecs_to_jiffies(3500));
            mod_delayed_work(priv->hs_micbias_hkadc_dwq,
                &priv->hs_micbias_hkadc_dw,
                msecs_to_jiffies(3000));
        }
    }
}

static void hi6555c_hs_micbias_work_enable(struct snd_soc_codec *codec, bool enable)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

    if (!priv)
        return;

    mutex_lock(&priv->hs_micbias_mutex);
    if (enable) {
        if (0 == priv->hs_micbias_work)
            hi6555c_hs_micbias_enable(codec, true);

        ++priv->hs_micbias_work;
    } else {
        --priv->hs_micbias_work;

        if (0 == priv->hs_micbias_work)
            hi6555c_hs_micbias_enable(codec, false);
    }
    mutex_unlock(&priv->hs_micbias_mutex);
}

static void hi6555c_hs_micbias_hkadc_enable(struct snd_soc_codec *codec, bool enable)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

    if (!priv)
        return;

    mutex_lock(&priv->hs_micbias_mutex);
    if (enable) {
        if (!priv->hs_micbias_hkadc) {
            hi6555c_hs_micbias_enable(codec, true);
            priv->hs_micbias_hkadc = true;
        }
    } else {
        if (priv->hs_micbias_hkadc) {
            priv->hs_micbias_hkadc = false;
            hi6555c_hs_micbias_enable(codec, false);
        }
    }
    mutex_unlock(&priv->hs_micbias_mutex);
}

static void hi6555c_hs_micbias_hkadc_work_func(struct work_struct *work)
{
    struct snd_soc_codec *codec = NULL;
    struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_micbias_hkadc_dw.work);

    if (!priv)
        return;

    if (!priv->codec)
        return;

    hi6555c_hs_micbias_pd(priv->codec, false);
}

static void hi6555c_enable_ibias(struct snd_soc_codec *codec, bool enable)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

    logd("Begin, en=%d\n", enable);
    if (!priv) {
        loge("priv is null\n");
        return;
    }

    if (!priv->ibias_hkadc && 0 == priv->ibias_work) {
        if (enable) {
            logi("ldo15 pu");
            /*enable ldo8*/
            hi6555c_power_codec(codec, HI6555C_ON);
        } else {
            logi("ldo15 pd");
            hi6555c_power_codec(codec, HI6555C_OFF);
        }
    }
    logd("End\n");
}

static void hi6555c_ibias_work_enable(struct snd_soc_codec *codec, bool enable)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

    if (!priv)
        return;

    mutex_lock(&priv->ibias_mutex);
    if (enable) {
        if (0 == priv->ibias_work)
            hi6555c_enable_ibias(codec, true);

        ++priv->ibias_work;
    } else {
        --priv->ibias_work;

        if (0 == priv->ibias_work)
            hi6555c_enable_ibias(codec, false);
    }
    mutex_unlock(&priv->ibias_mutex);
}

static void hi6555c_ibias_hsmicbias_enable(struct snd_soc_codec *codec, bool enable)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

    if (!priv)
        return;

    mutex_lock(&priv->ibias_mutex);
    if (enable) {
        if (!priv->ibias_hkadc) {
            hi6555c_enable_ibias(codec, true);
            priv->ibias_hkadc = true;
        }
    } else {
        if (priv->ibias_hkadc) {
            priv->ibias_hkadc = false;
            hi6555c_enable_ibias(codec, false);
        }
    }
    mutex_unlock(&priv->ibias_mutex);
}

/*
 *get irq stat
 *input: irq bit
 *output: 0 plugout,button up
 *           1 plugin,button down
 */
static inline int hi6555c_irq_stat(unsigned int irq_stat_bit)
{
    unsigned int irq_stat = 0;
    int ret = 0;

    irq_stat = hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR);
    irq_stat &= irq_stat_bit;

    switch (irq_stat_bit) {
    case IRQ_STAT_KEY_EVENT:
    case IRQ_STAT_ECO_KEY_EVENT:
        /* convert */
        ret = !irq_stat;
        break;
    case IRQ_STAT_PLUG_IN:
    default:
        /* no need to convert */
        ret = !!irq_stat;
        break;
    }
    logd("bit=0x%x, ret=%d\n", irq_stat_bit, ret);

    return ret;
}

static inline int hi6555c_hkadc_read(struct snd_soc_codec *codec)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);
    int hkadc_value = 0;
/*
    DRV_HKADC_GET_TEMP(HKADC_TEMP_CODEC,&priv->adc_voltage,
                       NULL,0);
*/

    /* HKADC voltage,real value should devided 0.6 */
    hkadc_value = ((priv->adc_voltage)*(10))/(6);
    logi("adc_voltage = %d", priv->adc_voltage);

    return hkadc_value;
}

static irqreturn_t hi6555c_irq_handler(int irq, void *data)
{
    struct  snd_soc_codec *codec = NULL;
    struct hi6555c_priv *priv = NULL;
    unsigned int irqs = 0;
    unsigned int irq_mask = 0, irq_masked = 0;

    logi(">>> Begin<<<\n");
    if (!data) {
        loge("data is null\n");
        return IRQ_NONE;
    }

    codec = data;
    priv = snd_soc_codec_get_drvdata(codec);
    if (!priv) {
        loge("priv is null\n");
        return IRQ_NONE;
    }

    irqs = hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR);
    irq_mask = hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR);
    irq_mask &= (~IRQ_PLUG_IN);
    irq_masked = irqs & (~irq_mask);

    if (0 == irqs) {
        logi("irq pass\n");
        return IRQ_NONE;
    }

    wake_lock_timeout(&priv->wake_lock, msecs_to_jiffies(2000));
    /* distribute and handle irq individually, one deal one time */
    if (irq_masked & IRQ_PLUG_OUT){
        queue_delayed_work(priv->hs_po_dwq,
            &priv->hs_po_dw,
            msecs_to_jiffies(0));
    } else if (irq_masked & IRQ_PLUG_IN) {
        queue_delayed_work(priv->hs_pi_dwq,
            &priv->hs_pi_dw,
            msecs_to_jiffies(HS_TIME_PI_DETECT));
    } else if (irq_masked & IRQ_COMP_L_BTN_DOWN) {
        queue_delayed_work(priv->hs_comp_l_btn_down_dwq,
            &priv->hs_comp_l_btn_down_dw,
            msecs_to_jiffies(HS_TIME_COMP_IRQ_TRIG));
    } else if (irq_masked & IRQ_COMP_L_BTN_UP) {
        queue_delayed_work(priv->hs_comp_l_btn_up_dwq,
            &priv->hs_comp_l_btn_up_dw,
            msecs_to_jiffies(HS_TIME_COMP_IRQ_TRIG_2));
    } else if (irq_masked & IRQ_ECO_BTN_DOWN) {
        queue_delayed_work(priv->hs_eco_btn_down_dwq,
            &priv->hs_eco_btn_down_dw,
            msecs_to_jiffies(HS_TIME_COMP_IRQ_TRIG));
    } else if (irq_masked & IRQ_ECO_BTN_UP) {
        queue_delayed_work(priv->hs_eco_btn_up_dwq,
            &priv->hs_eco_btn_up_dw,
            msecs_to_jiffies(HS_TIME_COMP_IRQ_TRIG_2));
    } else if (irq_masked & IRQ_COMP_H_BTN_DOWN) {
        queue_delayed_work(priv->hs_comp_h_btn_down_dwq,
            &priv->hs_comp_h_btn_down_dw,
            msecs_to_jiffies(HS_TIME_COMP_IRQ_TRIG));
    } else if (irq_masked & IRQ_COMP_H_BTN_UP) {
        queue_delayed_work(priv->hs_comp_h_btn_up_dwq,
            &priv->hs_comp_h_btn_up_dw,
            msecs_to_jiffies(HS_TIME_COMP_IRQ_TRIG_2));
    } else {
        logi("irq(0x%x) masked(0x%x) pass\n", irqs, irq_masked);
    }

    /* clear irq */
    hi6555c_irqs_clr(irqs);
    logi("<<< End, irq=0x%x(0x%x), IRQr=0x%x, IRQMr=0x%x, STATr=0x%x\n",
        irq_masked, irqs,
        hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
        hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
        hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));

    return IRQ_HANDLED;
}

void hs_jack_report(struct snd_soc_codec *codec)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);
    int jack_report = 0;

    switch(priv->hs_status) {
    case HI6555C_JACK_BIT_NONE:
        jack_report = 0;
        logi("plug out\n");
        break;
    case HI6555C_JACK_BIT_HEADSET:
        jack_report = SND_JACK_HEADSET;
        logi("4-pole headset plug in\n");
        break;
    case HI6555C_JACK_BIT_HEADSET_NO_MIC:
        jack_report = SND_JACK_HEADPHONE;
        logi("invert headset plug in\n");
        break;
    case HI6555C_JACK_BIT_HEADPHONE:
        jack_report = SND_JACK_HEADPHONE;
        logi("3-pole headphone plug in\n");
        break;
    default:
        loge("error hs_status(%d)\n", priv->hs_status);
        break;
    }

    /* report jack status */
    snd_soc_jack_report(priv->hs_jack->jack, jack_report, SND_JACK_HEADSET);
#ifdef CONFIG_SWITCH
    switch_set_state(&priv->hs_jack->sdev, priv->hs_status);
#endif
}

static int hs_plug_in_detect_func(struct snd_soc_codec *codec)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);
    int ret = 0;
    int hkadc_value = 0;
    unsigned int irq_mask = 0;

    if (!priv) {
        loge("priv is null\n");
        return -1;
    }

    /* check state - plugin */
    if (!hi6555c_irq_stat(IRQ_STAT_PLUG_IN)) {
        logi("STAT: not plug in, IRQ=0x%x, IRQM=0x%x, STAT=0x%x",
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
        hs_plug_out_detect_func(codec);
        return 0;
    }

    mutex_lock(&priv->plug_mutex);
    /* mask plug out */
    hi6555c_irqs_mask_set(IRQ_PLUG_OUT | IRQ_MSK_COMP);
    mutex_lock(&priv->hkadc_mutex);
    hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW24_ADDR, 0x1 << HI6555C_SMT_MBHD_VREF_PD_BIT_START);
    hi6555c_hs_micbias_hkadc_enable(codec, true);
    msleep(150);
    hkadc_value = hi6555c_hkadc_read(codec);

    /* value greater than 2565 can not trigger eco btn,
     * so,the hs_micbias can't be closed until second detect finish.
     */
     if (hkadc_value < 2565)
        hi6555c_hs_micbias_hkadc_enable(codec, false);
     mutex_unlock(&priv->hkadc_mutex);

     mutex_lock(&priv->io_mutex);
     if (hkadc_value <= priv->headset_voltage->hs_3_pole_max_voltage) {
        priv->hs_status = HI6555C_JACK_BIT_HEADPHONE;
        logi("headphone is 3 pole, saradc=%d", hkadc_value);
    } else if ((hkadc_value >= priv->headset_voltage->hs_4_pole_min_voltage)
        && (hkadc_value <= priv->headset_voltage->hs_4_pole_max_voltage)) {
        priv->hs_status = HI6555C_JACK_BIT_HEADSET;
        logi("headphone is 4 pole, saradc=%d", hkadc_value);
    } else {
        priv->hs_status = HI6555C_JACK_BIT_HEADSET_NO_MIC;
        logi("headphone is set reserve 4 pole temparily second check, saradc=%d", hkadc_value);
    }

    hi6555c_irqs_clr(IRQ_PLUG_OUT);
    hi6555c_irqs_mask_clr(IRQ_PLUG_OUT);
    mutex_unlock(&priv->io_mutex);

    if (!hi6555c_irq_stat(IRQ_STAT_PLUG_IN)) {
        logi("plug out happens\n");
        mutex_unlock(&priv->plug_mutex);
        hs_plug_out_detect_func(codec);
        return 0;
    }

    if ((HI6555C_JACK_BIT_NONE != priv->hs_status) && (priv->hs_status != priv->old_hs_status)) {
        priv->old_hs_status = priv->hs_status;
        /*report headset info */
        hs_jack_report(codec);
    } else {
        loge("hs status=%d(old=%d) not changed!\n", priv->hs_status, priv->old_hs_status);
        ret = 0;
    }

    /* to avoid irq while MBHD_COMP power up£¬mask the irq then clean it */
    hi6555c_irqs_clr(IRQ_MSK_COMP);
    hi6555c_irqs_mask_clr(IRQ_MSK_BTN_NOR);
    mutex_unlock(&priv->plug_mutex);

    return ret;
}

static int hs_plug_out_detect_func(struct snd_soc_codec *codec)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);
    int ret = 0;

    if (!priv) {
        loge("priv is null\n");
        return -1;
    }

    mutex_lock(&priv->plug_mutex);
    /*
     * Avoid hs_micbias_hkadc_dw waiting for entering eco,
     * so cancel the delay work then power off hs_micbias.
     */
    cancel_delayed_work(&priv->hs_micbias_hkadc_dw);
    flush_workqueue(priv->hs_micbias_hkadc_dwq);
    priv->hs_micbias_hkadc = false;
    hi6555c_hs_micbias_pd(priv->codec, false);
    /* mbhc vref pd */
    hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW24_ADDR, 0x1 << HI6555C_SMT_MBHD_VREF_PD_BIT_START);
    /* mask all btn irq */
    hi6555c_irqs_mask_set(IRQ_MSK_COMP);
    mutex_lock(&priv->io_mutex);
    priv->hs_jack->report = 0;

    if (0 != priv->pressed_btn_type) {
        priv->hs_jack->jack->jack->type = priv->pressed_btn_type;
        /*report key event*/
        logi("report type=0x%x, status=0x%x\n", priv->hs_jack->report, priv->hs_status);
        snd_soc_jack_report(priv->hs_jack->jack, priv->hs_jack->report, JACK_RPT_MSK_BTN);
    }

    priv->pressed_btn_type = 0;
    priv->hs_status = HI6555C_JACK_BIT_NONE;
    priv->old_hs_status = HI6555C_JACK_BIT_INVALID;
    mutex_unlock(&priv->io_mutex);

    /*report headset info */
    hs_jack_report(codec);

    hi6555c_irqs_clr(IRQ_MSK_COMP);
    hi6555c_irqs_mask_clr(IRQ_PLUG_IN);
    mutex_unlock(&priv->plug_mutex);

    return ret;
}

static int hs_btn_down_detect_func(struct snd_soc_codec *codec)
{
    int ret = 0;
    int pr_btn_type = 0;
    int hkadc_value = 0;
    unsigned int irq_mask = 0;

    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);
    if (!priv) {
        loge("priv is null\n");
        return -1;
    }

    if (!hi6555c_irq_stat(IRQ_STAT_PLUG_IN)) {
        logi("plug out happened");
        return 0;
    }

    if (HI6555C_JACK_BIT_HEADSET != priv->hs_status) {
        /* enter the second detect,it's triggered by btn irq  */
        loge("type 2-rec, saradc value=%d(btn_type=0x%x)\n", hkadc_value, priv->pressed_btn_type);
        ret = hs_plug_in_detect_func(codec);
        return ret;
    }

    /* hs_micbias power up,then power down 3 seconds later */
    cancel_delayed_work(&priv->hs_micbias_hkadc_dw);
    flush_workqueue(priv->hs_micbias_hkadc_dwq);

    mutex_lock(&priv->hkadc_mutex);
    hi6555c_hs_micbias_hkadc_enable(codec,true);
    hkadc_value = hi6555c_hkadc_read(codec);
    hi6555c_hs_micbias_hkadc_enable(codec,false);
    mutex_unlock(&priv->hkadc_mutex);
    msleep(30);
    /* to avoid irq while MBHD_COMP power up£¬mask the irq then clean it */
    hi6555c_irqs_clr(IRQ_MSK_COMP);
    hi6555c_irqs_mask_clr(IRQ_MSK_BTN_NOR);
    logi("mask clean");

    /*judge key type*/
    if ((hkadc_value >= priv->btn_voltage->key_play_min_value) && (hkadc_value <= priv->btn_voltage->key_play_max_value)) {
        pr_btn_type = SND_JACK_BTN_0;
        logi("key1 play down, saradc value is %d",hkadc_value);
    } else if ((hkadc_value >= priv->btn_voltage->key_forward_min_value) && (hkadc_value <= priv->btn_voltage->key_forward_max_value)) {
        pr_btn_type = SND_JACK_BTN_1;
        logi("key 2 forward down, saradc value is %d",hkadc_value);
    } else if ((hkadc_value >= priv->btn_voltage->key_back_min_value) && (hkadc_value <= priv->btn_voltage->key_back_max_value)) {
        pr_btn_type = SND_JACK_BTN_2;
        logi("key3 back key down , saradc value is %d", hkadc_value);
    } else {
        logi("hkadc value is not in range , hkadc value is %d", hkadc_value);
        return ret;
    }

    mutex_lock(&priv->io_mutex);
    priv->pressed_btn_type = pr_btn_type;
    priv->hs_jack->report = pr_btn_type;
    priv->hs_jack->jack->jack->type = pr_btn_type;
    mutex_unlock(&priv->io_mutex);

    if (!hi6555c_irq_stat(IRQ_STAT_PLUG_IN)) {
        logi("plug out happened");
    } else {
        /*report key event*/
        logi("report type=0x%x, status=0x%x\n", priv->hs_jack->report, priv->hs_status);
        snd_soc_jack_report(priv->hs_jack->jack, priv->hs_jack->report, JACK_RPT_MSK_BTN);
    }

    return ret;
}

static int hs_btn_up_detect_func(struct snd_soc_codec *codec)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(codec);

    if (!priv) {
        loge("priv is null\n");
        return -1;
    }

    mutex_lock(&priv->io_mutex);
    if (0 == priv->pressed_btn_type) {
        mutex_unlock(&priv->io_mutex);

        /* second detect */
        if ((HI6555C_JACK_BIT_HEADSET_NO_MIC == priv->hs_status) || (HI6555C_JACK_BIT_HEADPHONE == priv->hs_status)) {
            logi("type 2-recognize");
            hs_plug_in_detect_func(codec);
        } else {
            logi("ignore the key up irq");
        }

        return 0;
    }

    priv->hs_jack->jack->jack->type = priv->pressed_btn_type;
    priv->hs_jack->report = 0;

    /*report key event*/
    logi("report type=0x%x, status=0x%x\n", priv->hs_jack->report, priv->hs_status);
    snd_soc_jack_report(priv->hs_jack->jack, priv->hs_jack->report, JACK_RPT_MSK_BTN);
    priv->pressed_btn_type = 0;
    mutex_unlock(&priv->io_mutex);

    return 0;
}

static void hi6555c_hs_pi_work_func(struct work_struct *work)
{
    int ret= 0;
    struct snd_soc_codec *codec = NULL;
    struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_pi_dw.work);

    if (!priv) {
        loge("priv is null\n");
        return ;
    }

    codec = priv->codec;

    ret = hs_plug_in_detect_func(codec);
    if (ret < 0) {
        loge("pi, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
    }
}

static void hi6555c_hs_po_work_func(struct work_struct *work)
{
    int ret= 0;
    struct snd_soc_codec *codec = NULL;
    struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_po_dw.work);

    if (!priv) {
        loge("priv is null\n");
        return ;
    }
    codec = priv->codec;

    ret = hs_plug_out_detect_func(codec);
    if (ret < 0) {
        loge("po, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
    }
}

static void hi6555c_hs_comp_l_btn_down_work_func(struct work_struct *work)
{
    int ret= 0;
    struct snd_soc_codec *codec = NULL;
    struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_comp_l_btn_down_dw.work);

    if (!priv) {
        loge("priv is null\n");
        return ;
    }
    codec = priv->codec;

    ret = hs_btn_down_detect_func(codec);
    if (ret < 0) {
        loge("compare l btn_down, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
    }
}

static void hi6555c_hs_comp_l_btn_up_work_func(struct work_struct *work)
{
    int ret= 0;
    struct snd_soc_codec *codec = NULL;
    struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_comp_l_btn_up_dw.work);

    if (!priv) {
        loge("priv is null\n");
        return;
    }

    codec = priv->codec;

    ret = hs_btn_up_detect_func(codec);

    if (ret < 0) {
        loge("compare l btn_up, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
    }
}

static void hi6555c_hs_comp_h_btn_down_work_func(struct work_struct *work)
{
    int ret= 0;
    struct snd_soc_codec *codec = NULL;
    struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_comp_h_btn_down_dw.work);

    if (!priv) {
        loge("priv is null\n");
        return;
    }

    codec = priv->codec;

    ret = hs_btn_down_detect_func(codec);

    if (ret < 0) {
        loge("compare h btn_down, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
    }
}

static void hi6555c_hs_comp_h_btn_up_work_func(struct work_struct *work)
{
    int ret= 0;
    struct snd_soc_codec *codec = NULL;
    struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_comp_h_btn_up_dw.work);

    if (!priv) {
        loge("priv is null\n");
        return;
    }

    codec = priv->codec;

    ret = hs_btn_up_detect_func(codec);

    if (ret < 0) {
        loge("compare h btn_up, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
    }
}

static void hi6555c_hs_eco_btn_down_work_func(struct work_struct *work)
{
    int ret= 0;
    struct snd_soc_codec *codec = NULL;
    struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_eco_btn_down_dw.work);

    if (!priv) {
        loge("priv is null\n");
        return;
    }

    codec = priv->codec;

    ret = hs_btn_down_detect_func(codec);

    if (ret < 0) {
        loge("eco btn_down, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
    }
}

static void hi6555c_hs_eco_btn_up_work_func(struct work_struct *work)
{
    int ret= 0;
    struct snd_soc_codec *codec = NULL;
    struct hi6555c_priv *priv = container_of(work, struct hi6555c_priv, hs_eco_btn_up_dw.work);

    if (!priv) {
        loge("priv is null\n");
        return;
    }

    codec = priv->codec;

    ret = hs_btn_up_detect_func(codec);

    if (ret < 0) {
        loge("eco btn_up, RAW_irq=0x%x, IRQM=0x%x, irq_stat =0x%x\n",
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
            hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
    }
}

/*****************************************************************************
*
* HEADSET AREA END
*
*****************************************************************************/
/* INIT REGISTER VALUE FROM ARRAY */
static void hi6555c_init_reg_value(struct snd_soc_codec *codec)
{
    logi("hi6555c_init_reg_value Beg\n");

    // Pop Reset
    hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW21_ADDR, 0x13);

    // classD PGA CFG
    //todo fixme: hi6250 hi6xxx_pmic_reg_write(SOC_SMART_CLASSD_CTRL2_ADDR(0), 0x2F);
    hi6555c_reg_write(codec, (PAGE_SmartStarCODEC + SOC_SMART_CLASSD_CTRL2_ADDR(0)), 0x2F);

    // classD normal mute mode, and set mute ---  0x69 [5:4] = 11
    hi6555c_set_reg_bits(HI6555C_PMU_CODEC_CLASSD_CTRL1_ADDR,
        ((0x1 << HI6555C_PMU_CODEC_CLASSD_MUTE_SEL_BIT) | (0x1 << HI6555C_PMU_CODEC_CLASSD_MUTE_BIT)));

    // eliminate btn dithering
    hi6555c_reg_write(codec, HI6555C_SMT_DEB_CNT_HS_MIC_CFG_ADDR, 0x14);

    // MBHC compare config 100mV 800mV 95%
    hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW24_ADDR, 0x8E);

    // MICBIAS HSMICBIAS voltage 2.7V
    hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW22_ADDR, 0x36);

    // clear HP MIXER,RCV MIXER channel select
    hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW13_ADDR, 0x00);
    hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW14_ADDR, 0x03);

    // config HP PGA gain to -26dB
    hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW17_ADDR, 0x21);
    hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW18_ADDR, 0x21);

    // Charge Pump freq 1.536MHz
    hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW25_ADDR, 0xAC);

    // hp_bias always pu
    hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW37_ADDR, (0x1 << HI6555C_SMT_HP_BIAS_PU_BIT_START));

    // hp_l_r pop Resistor
    hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW36_ADDR, (0x1 << HI6555C_SMT_ANALOG_LOOP_BIT_START));
    hi6555c_clr_reg_bits(HI6555C_SMT_CODEC_ANA_RW40_ADDR, (0x1 << HI6555C_SMT_CODEC_ANA_REG40_BIT_START));

    // NORMAL mode
    hi6555c_reg_write(codec, HI6555C_SMT_CODEC_ANA_RW16_ADDR, 0x80);
}

#ifdef CONFIG_DEBUG_FS
static void hi6555c_dapm_widget_dp(char *buf)
{
    struct list_head *l;
    struct snd_soc_dapm_widget *w;
    int i = -1;

    memset(buf, 0, HI6555C_DBG_SIZE_WIDGET);

    snprintf(buf, HI6555C_DBG_SIZE_WIDGET, "BEGIN widget\n");
    l = &(g_codec->dapm.card->widgets);
    list_for_each_entry(w, l, list) {
        i++;
        snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_WIDGET - strlen(buf), "<%02d> pwr= %d \"%s\"\n", i, w->power, w->name);
    }
    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_WIDGET - strlen(buf), "END\n");
}

static void hi6555c_dapm_path_dp(char *buf)
{
    struct list_head *l;
    struct snd_soc_dapm_path *p;
    struct snd_soc_dapm_widget *source;
    struct snd_soc_dapm_widget *sink;
    int i = -1;

    memset(buf, 0, HI6555C_DBG_SIZE_PATH);

    snprintf(buf, HI6555C_DBG_SIZE_PATH, "BEGIN path\n");
    l = &(g_codec->dapm.card->paths);
    list_for_each_entry(p, l, list) {
        i++;
        snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PATH - strlen(buf), "<%d>cn_stat: %d\n", i, p->connect);
        if(p->source == NULL || p->sink == NULL) {
            snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PATH - strlen(buf), "<%d>end\n", i);
            continue;
        }

        source = p->source;
        sink   = p->sink;

        snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PATH - strlen(buf), " src w \"%s\"\n", source->name);
        snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PATH - strlen(buf), "sink w \"%s\"\n", sink->name);
    }
    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PATH - strlen(buf), "END\n");
}

static void hi6555c_reg_history_dp(char *buf)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(g_codec);
    unsigned int idx_wr_now = 0, idx_wr_latter = 0;
    unsigned int idx = 0, idx_start = 0, idx_stop = 0;
    unsigned int time_next = 0;
    unsigned int reg = 0, val = 0, time = 0;
    unsigned long flags = 0;
    u64 sec = 0;

    memset(buf, 0, HI6555C_DBG_SIZE_CACHE);

    if (!priv) {
        snprintf(buf, HI6555C_DBG_SIZE_CACHE, "priv is null\n");
        return;
    }

    spin_lock_irqsave(&priv->lock, flags);
    idx_wr_now = priv->rr_cache_idx;
    time_next = priv->rr_cache[(idx_wr_now + 1) % REG_CACHE_NUM_MAX].time;
    spin_unlock_irqrestore(&priv->lock, flags);

    if (idx_wr_now >= REG_CACHE_NUM_MAX) {
        snprintf(buf, HI6555C_DBG_SIZE_CACHE, "rr_idx(%d) err\n", idx_wr_now);
        return;
    }

    if (0 == idx_wr_now) {
        snprintf(buf, HI6555C_DBG_SIZE_CACHE, "no register cached now\n");
        return;
    }

    /* parameters: idx_wr_now */
    sec = hisi_getcurtime();
    do_div(sec, 1000000000);
    snprintf(buf, HI6555C_DBG_SIZE_CACHE, "time=%lu s, idx now=%d, BEGIN\n", (unsigned long int)sec, idx_wr_now);

    /* judge the position of idx in order to loop*/
    if (0 == time_next) {
        idx_start = 0;
        idx_stop = idx_wr_now;
    } else {
        /* loop */
        idx_start = idx_wr_now + 1;
        idx_stop = idx_wr_now + REG_CACHE_NUM_MAX;
    }

    for (idx = idx_start; idx < idx_stop; idx++) {
        spin_lock_irqsave(&priv->lock, flags);

        reg = priv->rr_cache[idx % REG_CACHE_NUM_MAX].reg;
        val = priv->rr_cache[idx % REG_CACHE_NUM_MAX].val;
        time = priv->rr_cache[idx % REG_CACHE_NUM_MAX].time;

        if (REG_CACHE_FLAG_READ == (reg & REG_CACHE_FLAG_MASK)) {
            /* read */
            snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_CACHE - strlen(buf), "%d.r %04X:%02X\n", time, reg & ~REG_CACHE_FLAG_MASK, val);
        } else if (REG_CACHE_FLAG_WRITE == (reg & REG_CACHE_FLAG_MASK)) {
            /* write */
            snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_CACHE - strlen(buf), "%d.w %04X %02X\n", time, reg & ~REG_CACHE_FLAG_MASK, val);
        } else {
            /* error branch */
            snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_CACHE - strlen(buf), "%d.e %x %x\n", time, reg & ~REG_CACHE_FLAG_MASK, val);
        }
        spin_unlock_irqrestore(&priv->lock, flags);
    }

    /* dump */
    spin_lock_irqsave(&priv->lock, flags);
    idx_wr_latter = priv->rr_cache_idx;
    spin_unlock_irqrestore(&priv->lock, flags);
    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_CACHE - strlen(buf), "idx=%d -- %d, END\n", idx_wr_now, idx_wr_latter);
}

static void hi6555c_page_dp(char *buf)
{
    unsigned int regi = 0;

    memset(buf, 0, HI6555C_DBG_SIZE_PAGE);

    /* page 0 */
    snprintf(buf, HI6555C_DBG_SIZE_PAGE, "Page 0\n");
    for  (regi = HI6555C_PAGE_0_START; regi <= HI6555C_PAGE_0_END; regi += 4) {
        snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "%#04x:%#010x\n", regi, hi6555c_reg_read(g_codec, regi));
    }

    for (regi = HI6555C_PAGE_0C_START; regi <= HI6555C_PAGE_0C_END; regi += 4) {
        snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "%#04x:%#010x\n", regi, hi6555c_reg_read(g_codec, regi));
    }
    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "\n");

    /* page 1 */
    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "Page 1\n");
    for (regi = HI6555C_PAGE_1_START; regi <= HI6555C_PAGE_1_END; regi++) {
        snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "%#04x:%#04x\n", regi, hi6555c_reg_read(g_codec, regi));
    }
    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "\n");

    /* page 2 */
    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "Page 2\n");
    for (regi = HI6555C_PAGE_2_START; regi <= HI6555C_PAGE_2_END; regi++) {
        snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "%#04x:%#04x\n", regi, hi6555c_reg_read(g_codec, regi));
    }
    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "\n");

    /* page 4 - pmu */
    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "Page 4\n");
    for (regi = HI6555C_PAGE_4_START; regi <= HI6555C_PAGE_4_END; regi++) {
        snprintf(buf, HI6555C_DBG_SIZE_PAGE, "%#04x:%#04x\n", regi, hi6555c_reg_read(g_codec, regi));
    }

    for (regi = HI6555C_PAGE_4C_START; regi <= HI6555C_PAGE_4C_END; regi++) {
        snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "%#04x:%#04x\n", regi, hi6555c_reg_read(g_codec, regi));
    }

    for (regi = HI6555C_PAGE_4L_START; regi <= HI6555C_PAGE_4L_END; regi++) {
        if ((HI6555C_PAGE_4L1 == regi) ||
        (HI6555C_PAGE_4L5 == regi) ||
        (HI6555C_PAGE_4L12 == regi) ||
        (HI6555C_PAGE_4L15 == regi) ||
        (HI6555C_PAGE_4L18 == regi)) {
            snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "%#04x:%#04x\n", regi, hi6555c_reg_read(g_codec, regi));
        }
    }

    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "<cat end>\n");
    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "\n");
}

static void hi6555c_state_dp(char *buf)
{
    struct hi6555c_priv *priv = snd_soc_codec_get_drvdata(g_codec);

    memset(buf, 0, HI6555C_DBG_SIZE_PAGE);

    if (!priv) {
        snprintf(buf, HI6555C_DBG_SIZE_PAGE, "priv is null\n");
        return ;
    }

    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "hs_status=%d(old=%d), jack->report=0x%x\n",
        priv->hs_status, priv->old_hs_status, priv->hs_jack->report);

    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "IRQ=0x%x, IRQM=0x%x, STAT=0x%x\n",
        hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQ_REG0_ADDR),
        hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQM_REG0_ADDR),
        hi6555c_reg_read(g_codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));

    snprintf(buf + strlen(buf), HI6555C_DBG_SIZE_PAGE - strlen(buf), "<end>\n");
}

/*
 *1 default: page outpue
 *2 single reg read: echo "r reg" > rr£¬cat rr
 *3 single reg write: echo "w reg val"
 */
static int hi6555c_rr_read(struct file *file, char __user *user_buf,
                size_t count, loff_t *ppos)
{
    char *kn_buf = NULL;
    ssize_t byte_read = 0;
    unsigned int vs_reg_r = g_vs_reg;

    kn_buf = kmalloc(HI6555C_DBG_SIZE_PAGE, GFP_KERNEL);
    if (NULL == kn_buf) {
        loge("kn_buf is null\n");
        return simple_read_from_buffer(user_buf, count, ppos, "kn_buf alloc fail\n", 18);
    }

    memset(kn_buf, 0, HI6555C_DBG_SIZE_PAGE);
    if (INVALID_REG != vs_reg_r) {
        /* Register */
        if(PAGE_SoCCODEC == (vs_reg_r & PAGE_TYPE_MASK)) {
            snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_PAGE - strlen(kn_buf), "%#04x:%#010x\n", vs_reg_r, hi6555c_reg_read(g_codec, vs_reg_r));
            snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_PAGE - strlen(kn_buf), "<cat end>\n");
        } else {
            snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_PAGE - strlen(kn_buf), "%#04x:%#04x\n", vs_reg_r, hi6555c_reg_read(g_codec, vs_reg_r));
            snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_PAGE - strlen(kn_buf), "<cat end>\n");
        }
    } else {
        /* PAGE */
        hi6555c_page_dp(kn_buf);
    }

    byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));
    kfree(kn_buf);
    kn_buf = NULL;
    return byte_read;
}

/*
 *1 default: page outpue
 *2 single reg read: echo "r reg" > rr£¬cat rr
 *3 single reg write: echo "w reg val"
 */
static int hi6555c_rr_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
{
    char *kn_buf = NULL;
    ssize_t byte_writen = 0;
    int num = 0;
    unsigned int vs_reg = 0, vs_val = 0;

    kn_buf = kmalloc(HI6555C_DBG_SIZE_PAGE, GFP_KERNEL);
    if (NULL == kn_buf) {
        loge("kn_buf is null\n");
        return -EFAULT;
    }

    byte_writen = simple_write_to_buffer(kn_buf, HI6555C_DBG_SIZE_PAGE, ppos, user_buf, count);

    if ('w' == kn_buf[0]) {
        /* write single reg */
        num = sscanf(kn_buf, "w 0x%x 0x%x", &vs_reg, &vs_val);
        if (2 == num) {
            hi6555c_reg_write(g_codec, vs_reg, vs_val);
            g_vs_reg = vs_reg;
        } else {
            g_vs_reg = INVALID_REG;
            byte_writen = -EINVAL;
        }
    } else if ('r' == kn_buf[0]) {
        /* read single reg */
        num = sscanf(kn_buf, "r 0x%x", &g_vs_reg);
        if (1 != num) {
            g_vs_reg = INVALID_REG;
            byte_writen = -EINVAL;
        }
    } else if ('p' == kn_buf[0]) {
        /* read PAGE */
        g_vs_reg = INVALID_REG;
    } else {
        /* abnormal */
        g_vs_reg = INVALID_REG;
        byte_writen = -EINVAL;
    }

    kfree(kn_buf);
    kn_buf = NULL;
    return byte_writen;
}

/*
 * history reg read
 */
static int hi6555c_rh_read(struct file *file, char __user *user_buf,
                size_t count, loff_t *ppos)
{
    char *kn_buf = NULL;
    ssize_t byte_read = 0;

    kn_buf = vmalloc(HI6555C_DBG_SIZE_CACHE);

    if (NULL == kn_buf) {
        loge("kn_buf is null\n");
        return simple_read_from_buffer(user_buf, count, ppos, "vmalloc fail\n", 18);
    }

    hi6555c_reg_history_dp(kn_buf);

    byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));

    vfree(kn_buf);
    kn_buf = NULL;

    return byte_read;
}

/*
 *widget state interface
 */
static int hi6555c_dwidget_read(struct file *file, char __user *user_buf,
                size_t count, loff_t *ppos)
{
    char *kn_buf = NULL;
    ssize_t byte_read = 0;

    kn_buf = vmalloc(HI6555C_DBG_SIZE_WIDGET);

    if (NULL == kn_buf) {
        loge("kn_buf is null\n");
        return simple_read_from_buffer(user_buf, count, ppos, "kn_buf alloc fail\n", 18);
    }

    hi6555c_dapm_widget_dp(kn_buf);

    byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));

    vfree(kn_buf);
    kn_buf = NULL;

    return byte_read;
}

/*
 *path state interface
*/
static int hi6555c_dpath_read(struct file *file, char __user *user_buf,
                size_t count, loff_t *ppos)
{
    char *kn_buf = NULL;
    ssize_t byte_read = 0;

    kn_buf = vmalloc(HI6555C_DBG_SIZE_PATH);
    if (NULL == kn_buf) {
        loge("kn_buf is null\n");
        return simple_read_from_buffer(user_buf, count, ppos, "kn_buf alloc fail\n", 18);
    }

    hi6555c_dapm_path_dp(kn_buf);

    byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));

    vfree(kn_buf);
    kn_buf = NULL;

    return byte_read;
}

/*
 *codec state interface
 */
static int hi6555c_state_read(struct file *file, char __user *user_buf,
                size_t count, loff_t *ppos)
{
    char *kn_buf = NULL;
    ssize_t byte_read = 0;

    kn_buf = kmalloc(HI6555C_DBG_SIZE_PAGE, GFP_KERNEL);

    if (NULL == kn_buf) {
        loge("kn_buf is null\n");
        return simple_read_from_buffer(user_buf, count, ppos, "kn_buf alloc fail\n", 18);
    }

    hi6555c_state_dp(kn_buf);

    byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));

    kfree(kn_buf);
    kn_buf = NULL;

    return byte_read;
}

static const struct file_operations hi6555c_rr_fops = {
    .read  = hi6555c_rr_read,
    .write = hi6555c_rr_write,
};

static const struct file_operations hi6555c_rh_fops = {
    .read  = hi6555c_rh_read,
};

static const struct file_operations hi6555c_dwidget_fops = {
    .read  = hi6555c_dwidget_read,
};

static const struct file_operations hi6555c_dpath_fops = {
    .read  = hi6555c_dpath_read,
};

static const struct file_operations hi6555c_state_fops = {
    .read  = hi6555c_state_read,
};

#ifdef CONFIG_DEBUG_POP
static struct hi6555c_ps_cache ps_cache[100];
static unsigned int ps_index = 0;

/* write reg by seq */
static void hi6555c_pop_debug(void)
{
    unsigned int idx_ps = 0;
    for (idx_ps = 0;idx_ps < ps_index;idx_ps++) {
        switch (ps_cache[idx_ps].op) {
        case HI6555C_POP_DELAY_MS:
            logi("m %d",ps_cache[idx_ps].val);
            msleep(ps_cache[idx_ps].val);
            break;
        case HI6555C_POP_DELAY_US:
            logi("u %d",ps_cache[idx_ps].val);
            udelay(ps_cache[idx_ps].val);
            break;
        case HI6555C_POP_REG_WRITE:
            logi("w 0x%x 0x%x",ps_cache[idx_ps].reg,ps_cache[idx_ps].val);
            hi6555c_reg_write(g_codec,ps_cache[idx_ps].reg,ps_cache[idx_ps].val);
            break;
        default:
            loge("op not found\n");
        }
    }
}

/*
 *1 default: Output PAGE
 *2 clean history reg: echo "c" > ps
 *3 reg write:   echo "w reg val" > ps
 *4 delay ms:   echo "m val" > ps
 *5 delay us:   echo "u val" > ps
 */
static int hi6555c_ps_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
{
    char *kn_buf = NULL;
    ssize_t byte_writen = 0;
    int num = 0;
    unsigned int vs_reg = 0;
    unsigned int vs_val = 0;

    kn_buf = kmalloc(HI6555C_DBG_SIZE_PAGE, GFP_KERNEL);
    if (NULL == kn_buf) {
        loge("kn_buf is null\n");
        return -EFAULT;
    }

    byte_writen = simple_write_to_buffer(kn_buf, HI6555C_DBG_SIZE_PAGE, ppos, user_buf, count);

    if (ps_index == 100) {
        loge("ps is full\n");
    } else if ('w' == kn_buf[0]) {
        /* reg write */
        num = sscanf(kn_buf, "w 0x%x 0x%x", &vs_reg, &vs_val);
        if (2 == num) {
            ps_cache[ps_index].op  = HI6555C_POP_REG_WRITE;
            ps_cache[ps_index].reg = vs_reg;
            ps_cache[ps_index].val = vs_val;
            ps_index++;
        }
    } else if ('m' == kn_buf[0]) {
        /* delay ms */
        num = sscanf(kn_buf, "m %d", &vs_val);
        if (1 == num) {
            ps_cache[ps_index].op = HI6555C_POP_DELAY_MS;
            ps_cache[ps_index].val = vs_val;
            ps_index++;
        }
    } else if ('u' == kn_buf[0]) {
        /* delay us */
        num = sscanf(kn_buf, "u %d", &vs_val);
        if (1 == num) {
            ps_cache[ps_index].op = HI6555C_POP_DELAY_US;
            ps_cache[ps_index].val = vs_val;
            ps_index++;
        }
    } else if ('c' == kn_buf[0]) {
        /* history clean */
        ps_index = 0;
    } else if ('e' == kn_buf[0]) {
        /* exec pop */
        hi6555c_pop_debug();
    }

    kfree(kn_buf);
    kn_buf = NULL;

    return byte_writen;
}

/*
  * ps current value interface
 */
static int hi6555c_ps_read(struct file *file, char __user *user_buf,
                size_t count, loff_t *ppos)
{
    char *kn_buf = NULL;
    ssize_t byte_read = 0;
    unsigned int idx_ps = 0;
    kn_buf = vmalloc(HI6555C_DBG_SIZE_CACHE);

    if (NULL == kn_buf) {
        loge("kn_buf is null\n");
        return simple_read_from_buffer(user_buf, count, ppos, "vmalloc fail\n", 18);
    }

    memset(kn_buf, 0, HI6555C_DBG_SIZE_CACHE);

    snprintf(kn_buf, HI6555C_DBG_SIZE_CACHE, "PS DUMP BEGIN\n");
    for (idx_ps = 0;idx_ps < ps_index;idx_ps++) {
        switch(ps_cache[idx_ps].op) {
        case HI6555C_POP_DELAY_MS:
            snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_CACHE - strlen(kn_buf), "m %d\n",ps_cache[idx_ps].val);
            break;
        case HI6555C_POP_DELAY_US:
            snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_CACHE - strlen(kn_buf), "%d\n",ps_cache[idx_ps].val);
            break;
        case HI6555C_POP_REG_WRITE:
            snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_CACHE - strlen(kn_buf), "w 0x%x 0x%x\n",ps_cache[idx_ps].reg,ps_cache[idx_ps].val);
            break;
        default:
            loge("op not found\n");
        }
    }
    snprintf(kn_buf + strlen(kn_buf), HI6555C_DBG_SIZE_CACHE - strlen(kn_buf), "PS DUMP END\n");
    byte_read = simple_read_from_buffer(user_buf, count, ppos, kn_buf, strlen(kn_buf));

    vfree(kn_buf);
    kn_buf = NULL;

    return byte_read;
}

static const struct file_operations hi6555c_ps_fops = {
    .read  = hi6555c_ps_read,
    .write = hi6555c_ps_write,
};
#endif
#endif /* CONFIG_DEBUG_FS */

static int hi6555c_startup(struct snd_pcm_substream *substream,
                struct snd_soc_dai *dai)
{
    return 0;
}

static int hi6555c_hw_params(struct snd_pcm_substream *substream,
                struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
    /*TODO*/
    return 0;
}

static void hi6555c_shutdown(struct platform_device *dev)
{
    /*TODO*/
    struct hi6555c_priv *priv = NULL;
    struct snd_soc_codec *codec = NULL;

    if (NULL != g_codec) {
        priv = snd_soc_codec_get_drvdata(g_codec);
        codec = priv->codec;
    }

    logi("Begin\n");
    if (!priv) {
        loge("priv is null\n");
    } else {
        if (HI6555C_JACK_BIT_NONE != priv->hs_status) {
            logi("hi6555c_codec_shutdown with headset\n");
                     HiLOGE("audio", "Hi6555c", "hi6555c_codec_shutdown with headset\n");
            hi6555c_smt_hslr_pd_outdrv_power_mode_event((struct snd_soc_dapm_widget *)NULL,
                ( struct snd_kcontrol *)NULL,SND_SOC_DAPM_POST_PMD);
        }

        /* codec pd */
        if (NULL != priv->regulator_avdd1v8) {
            hi6555c_power_codec(codec, HI6555C_OFF);
        }
    }
    logi("End\n");
}

#ifdef CONFIG_PM
static int hi6555c_suspend(struct platform_device *dev, pm_message_t state)
{
    /* nothing to do */
    logi("Begin\n");
    logi("End\n");
    return 0;
}

static int hi6555c_resume(struct platform_device *dev)
{
    /* nothing to do */
    logi("Begin\n");
    /* set 24bit for codec to compitable with HIFI */
    hi6555c_set_reg_bits(HI6555C_SW_RST_N_ADDR,  HI6555C_CODEC_24BIT_SETTING);
    logi("%s:resume set 24bit for codec to compitable with HIFI\n",__func__);
    logi("End\n");
    return 0;
}
#else /* CONFIG_PM */
#define hi6555c_suspend NULL
#define hi6555c_resume NULL
#endif /* CONFIG_PM */

struct snd_soc_dai_ops hi6555c_dai_ops = {
    .startup    = hi6555c_startup,
    .hw_params  = hi6555c_hw_params,
};

struct snd_soc_dai_driver hi6555c_dai[] = {
    {
        .name = "hi6555c-dai",
        .playback = {
            .stream_name = "Playback",
            .channels_min = HI6555C_PB_MIN_CHANNELS,
            .channels_max = HI6555C_PB_MAX_CHANNELS,
            .rates = HI6555C_RATES,
            .formats = HI6555C_FORMATS
        },
        .capture = {
            .stream_name = "Capture",
            .channels_min = HI6555C_CP_MIN_CHANNELS,
            .channels_max = HI6555C_CP_MAX_CHANNELS,
            .rates = HI6555C_RATES,
            .formats = HI6555C_FORMATS
        },
        .ops = &hi6555c_dai_ops,
    },
};

static int set_headset_keys_config(struct hi6555c_priv *priv)
{
    /* config the headset */
    priv->headset_voltage->hs_3_pole_max_voltage = 8;
    priv->headset_voltage->hs_4_pole_min_voltage = 1350;
    priv->headset_voltage->hs_4_pole_max_voltage = 2565;
    logi("headset_voltage {3pole=%d, 4pole=(%d-%d)}\n",
        priv->headset_voltage->hs_3_pole_max_voltage,
        priv->headset_voltage->hs_4_pole_min_voltage,
        priv->headset_voltage->hs_4_pole_max_voltage);

    /* config the keys */
    priv->btn_voltage->key_up_min_value = 1350;
    priv->btn_voltage->key_up_max_value = 2565;
    priv->btn_voltage->key_play_min_value = 0;
    priv->btn_voltage->key_play_max_value = 100;
    priv->btn_voltage->key_back_min_value = 350;
    priv->btn_voltage->key_back_max_value = 700;
    priv->btn_voltage->key_forward_min_value = 130;
    priv->btn_voltage->key_forward_max_value = 320;

    logi("btn_voltage {keyup=(%d-%d), keyplay=(%d-%d), keyback=(%d-%d), keyfw=(%d-%d)}\n",
        priv->btn_voltage->key_up_min_value,
        priv->btn_voltage->key_up_max_value,
        priv->btn_voltage->key_play_min_value,
        priv->btn_voltage->key_play_max_value,
        priv->btn_voltage->key_back_min_value,
        priv->btn_voltage->key_back_max_value,
        priv->btn_voltage->key_forward_min_value,
        priv->btn_voltage->key_forward_max_value);

    return 0;
}

static int hi6555c_tool_init(struct snd_soc_codec *codec)
{
    struct hi6555c_priv *priv = NULL;
    logi("Begin \n");

    priv = snd_soc_codec_get_drvdata(codec);

    if (NULL == priv) {
        loge("priv is NULL\n");
        return -EFAULT;
    }

    INIT_WORK(&priv->tool_work,hi6555c_misc_reg_write);
    priv->tool_data.normal_always = HI6555C_DISABLE;
    priv->tool_data.codec_soc_clk_cnt = 0;
    priv->tool_data.scharge_boost_cnt = 0;
    logi("End \n");

    return 0;
}

/*
 *SoC init
 */
static int hi6555c_soc_init(struct snd_soc_codec *codec)
{
    int ret = 0;
    struct hi6555c_priv *priv = NULL;
    struct device_node *np  = codec->dev->of_node;
    struct device*     dev  = codec->dev;

    priv = snd_soc_codec_get_drvdata(codec);

    if (NULL == priv) {
        loge("priv is NULL\n");
        return -EFAULT;
    }

/* add for 6250 by qianli begin */
    priv->asp_cfg_regu = devm_regulator_get(codec->dev,"asp");
    if (IS_ERR(priv->asp_cfg_regu)) {
        dev_err(dev, "couldn't get asp regulators !\n");
        return -EFAULT;;
    }

    ret = regulator_enable(priv->asp_cfg_regu);
    if (0 != ret) {
        pr_info("couldn't enable asp_cfg_regu regulators %d\n", ret);
        return -EFAULT;;
    }
/* add for 6250 by qianli end */

    /* abb reset */
    hi6555c_set_reg_bits(HI6555C_PSCTRL_RSTDIS2_ADDR,  (0x1 << HI6555C_RSTDIS2_ABB_BIT_START));

    /* codec work clk */
    priv->codec_soc = of_clk_get(np, 0);
    if (IS_ERR(priv->codec_soc)) {
        loge("Get Codec clk clk_bbppll_sel_src failed\n");
    }

    /* codec interface clk */
    priv->codec_apb = of_clk_get(np, 1);
    if (IS_ERR(priv->codec_apb)) {
        loge("Get Codec clk clk_dacodec failed\n");
    } else {
        /* codec interface clk always on */
        ret = clk_prepare_enable(priv->codec_apb);
        if (ret) {
            loge("codec_apb clken fail\n");
        }
    }
    logi("clocks gots\n");

    /* soc codec reset */
    //hi6555c_set_reg_bits(HI6555C_PSCTRL_RSTDIS1_ADDR,  0x1 << HI6555C_RSTDIS1_DIGACODE_BIT_START);
    hi6555c_set_reg_bits((PAGE_ASPCFG + 0x4),  0x600);

    /* regulator */
#if 0//todo fixme: hi6250 fpga always poweron
    priv->regulator_schg_boost3 = regulator_get(dev, "schg_boost3");
    if (IS_ERR(priv->regulator_schg_boost3)) {
        loge("regulator_schg_boost3 get failed");
        ret = -EFAULT;
    }
#endif
    /*set the classD power supply state*/
    /* fixme: begin for hi3650 */
    priv->use_battery_supply= true;//todo fixme: hi6250 of_property_read_bool(np,"use-battery-power-supply-for-ClassD");

    /* CodecÑ¡Ôñ¼Ä´æÆ÷(DMAÑ¡Ôñµ½Codec) */
    hi6555c_reg_write(codec, (PAGE_ASPCFG + 0x1E0), 0x3);

    /* AO_IOC¹Ü½Å¸´ÓÃ¿ØÖÆ*/
    /* S2P¹Ü½Å¸´ÓÃÅäÖÃ*/
    hi6555c_reg_write(codec, (PAGE_AO_IOC + 0x2c), 0x1);
    hi6555c_reg_write(codec, (PAGE_AO_IOC + 0x30), 0x1);
    hi6555c_reg_write(codec, (PAGE_AO_IOC + 0x34), 0x1);
    hi6555c_reg_write(codec, (PAGE_AO_IOC + 0x38), 0x1);

    /* gpio21¹Ü½ÅÅäÖÃ(½öFPGAÐèÅäÖÃ)*/
    hi6555c_reg_write(codec, (PAGE_GPIO21 + 0x400), 0x3);
    hi6555c_reg_write(codec, (PAGE_GPIO21 + 0x008), 0xff);
    /* fixme: end for hi3650 */
    /* set 24bit for codec to compitable with HIFI */
    hi6555c_set_reg_bits(HI6555C_SW_RST_N_ADDR,  HI6555C_CODEC_24BIT_SETTING);
    return ret;
}

/*
SmartStarCodec init
*/
static int hi6555c_headset_init(struct snd_soc_codec *codec)
{
    int ret = 0;
    struct hi6555c_priv *priv = NULL;
    struct device *dev  = codec->dev;
    struct device_node *np  = codec->dev->of_node;
    enum of_gpio_flags flags = 0;

    /* smartstar codec reset */
    //todo fixme: hi6250 hi6xxx_pmic_reg_write(SOC_SMART_PMU_SOFT_RST_ADDR(0), 0x22 << SOC_SMART_PMU_SOFT_RST_soft_rst_n_START);
    hi6555c_reg_write(codec, (PAGE_SmartStarCODEC + SOC_SMART_PMU_SOFT_RST_ADDR(0)), 0x22 << SOC_SMART_PMU_SOFT_RST_soft_rst_n_START);
    msleep(10);
    //todo fixme: hi6250 hi6xxx_pmic_reg_write(SOC_SMART_PMU_SOFT_RST_ADDR(0), 0x2F << SOC_SMART_PMU_SOFT_RST_soft_rst_n_START);
    hi6555c_reg_write(codec, (PAGE_SmartStarCODEC + SOC_SMART_PMU_SOFT_RST_ADDR(0)), 0x2F << SOC_SMART_PMU_SOFT_RST_soft_rst_n_START);

    priv = snd_soc_codec_get_drvdata(codec);
    if (NULL == priv) {
        loge("priv is NULL\n");
        return -EFAULT;
    }

    /* regulator */
#if 0//todo fixme: hi6250 fpga always poweron
    priv->regulator_avdd1v8 = regulator_get(dev, "avdd1v8");
    if (IS_ERR(priv->regulator_avdd1v8)) {
        loge("regulator_avdd1v8 get failed\n");
        return -EFAULT;
    }
#else
    //ldo15 pmu power on
    hi6555c_reg_write(codec, (PAGE_SmartStarCODEC + SOC_SMART_ENABLE3_LDO9_16_ADDR(0)), 0x40);
#endif//end for hi6250
    ret = hi6555c_tool_init(codec);
    if (0 != ret) {
        loge("hi6555c_tool_init err\n");
    }

    hi6555c_init_reg_value(codec);
#if 0//todo fixme: hi6250
    g_codec_version = hi6xxx_pmic_get_version();
    logi("version=0x%x", g_codec_version);
    if((g_codec_version >= PMU_VER_START) && (g_codec_version <= PMU_VER_END)) {
        priv->hi6555c_pmu_status = STATUS_OK;
    } else {
        priv->hi6555c_pmu_status = STATUS_ERROR;
        logi("PMU version is wrong");
    }
#else
    priv->hi6555c_pmu_status = STATUS_OK;
#endif//end for hi6250
    /* memory alloc */
    priv->hs_jack = kzalloc(sizeof(struct hi6555c_jack_data), GFP_KERNEL);
    if (NULL == priv->hs_jack) {
        loge("kzalloc failed : hs_jack\n");
        return -ENOMEM;
    }

    priv->hs_jack->jack = kzalloc(sizeof(struct snd_soc_jack), GFP_KERNEL);
    if (NULL == priv->hs_jack->jack) {
        loge("kzalloc failed : hs_jack->jack\n");
        return -ENOMEM;
    }

    priv->headset_voltage = kzalloc(sizeof(struct hi6555c_headset_voltage), GFP_KERNEL);
    if (NULL == priv->headset_voltage) {
        loge("kzalloc failed : headset_voltage\n");
        return -ENOMEM;
    }

    priv->btn_voltage = kzalloc(sizeof(struct hi6555c_btn_voltage), GFP_KERNEL);
    if (NULL == priv->btn_voltage) {
        loge("kzalloc failed : btn_voltage\n");
        return -ENOMEM;
    }

    /* init */
    set_headset_keys_config(priv);
    priv->hs_status = HI6555C_JACK_BIT_NONE;
    priv->old_hs_status = HI6555C_JACK_BIT_INVALID;
    priv->hs_jack->report = 0;
    priv->pressed_btn_type = 0;

    /*VREF PD ú»MICBIAS PD  */
    hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW02_ADDR, 0x1 << HI6555C_SMT_HSMICB_PD_BIT_START);
    hi6555c_set_reg_bits(HI6555C_SMT_CODEC_ANA_RW24_ADDR, 0x1 << HI6555C_SMT_MBHD_VREF_PD_BIT_START);

    hi6555c_irqs_mask_set(IRQ_MSK_HS_ALL);

    /* avoid irq triggered while codec power up */
    hi6555c_irqs_clr(IRQ_MSK_HS_ALL);

    /* Headset jack */
    ret = snd_soc_jack_new(codec, "Headset Jack", SND_JACK_HEADSET, (priv->hs_jack->jack));
    if (ret) {
        loge("jack new, ret = 0x%x\n", ret);
        return -EFAULT;
    }

    /* set a key mapping on a jack */
    ret = snd_jack_set_key(priv->hs_jack->jack->jack, SND_JACK_BTN_0, KEY_MEDIA);
    if (ret) {
        loge("jack set key(0x%x), ret = 0x%x\n", SND_JACK_BTN_0, ret);
        return -EFAULT;
    }

    ret = snd_jack_set_key(priv->hs_jack->jack->jack, SND_JACK_BTN_1, KEY_VOLUMEUP);
    if (ret) {
        loge("jack set key(0x%x), ret = 0x%x\n", SND_JACK_BTN_1, ret);
        return -EFAULT;
    }

    ret = snd_jack_set_key(priv->hs_jack->jack->jack, SND_JACK_BTN_2, KEY_VOLUMEDOWN);
    if (ret) {
        loge("jack set key(0x%x), ret = 0x%x\n", SND_JACK_BTN_2, ret);
        return -EFAULT;
    }

#ifdef CONFIG_SWITCH
    priv->hs_jack->sdev.name = "h2w";
    ret = switch_dev_register(&(priv->hs_jack->sdev));
    if (ret) {
        loge("Registering switch device\n");
        return -EFAULT;
    }
#endif

#ifdef CONFIG_DEBUG_FS
    g_dump_addr = (void*)priv->rr_cache;
    g_dump_size = sizeof(struct hi6555c_rr_cache) * REG_CACHE_NUM_MAX;

    priv->df_dir = debugfs_create_dir("hi6555c", NULL);
    if (!priv->df_dir) {
        loge("create hi6555c debugfs dir\n");
        return -ENOMEM;
    }

    /* register */
    if (!debugfs_create_file("rr", 0640, priv->df_dir, NULL, &hi6555c_rr_fops)) {
        loge("create hi6555c debugfs rr\n");
        return -ENOMEM;
    }

    /* register history */
    if (!debugfs_create_file("rh", 0640, priv->df_dir, NULL, &hi6555c_rh_fops)) {
        loge("create hi6555c debugfs cache\n");
        return -ENOMEM;
    }

    /* dump widget */
    if (!debugfs_create_file("dwidget", 0640, priv->df_dir, NULL, &hi6555c_dwidget_fops)) {
        loge("create hi6555c debugfs dwidget\n");
        return -ENOMEM;
    }

    /* dump path */
    if (!debugfs_create_file("dpath", 0640, priv->df_dir, NULL, &hi6555c_dpath_fops)) {
        loge("create hi6555c debugfs dpath\n");
        return -ENOMEM;
    }

    /* codec state */
    if (!debugfs_create_file("stat", 0640, priv->df_dir, NULL, &hi6555c_state_fops)) {
        loge("create hi6555c debugfs dpath\n");
        return -ENOMEM;
    }

#ifdef CONFIG_DEBUG_POP
    if (!debugfs_create_file("ps", 0640, priv->df_dir, NULL, &hi6555c_ps_fops)) {
        loge("create hi6555c debugfs dpath\n");
        return -ENOMEM;
    }
#endif
#endif /* CONFIG_DEBUG_FS */

    if(STATUS_ERROR == priv->hi6555c_pmu_status){
        logi("Hi6555c version is wrong,and not config IRQ");
        goto END;
    }

    /* IRQ config */
    priv->hs_pi_dwq = create_singlethread_workqueue("hs_pi_dwq");
    if (NULL == priv->hs_pi_dwq) {
        loge("hs_pi_dwq workqueue create failed\n");
        return -EFAULT;
    }
    INIT_DELAYED_WORK(&priv->hs_pi_dw, hi6555c_hs_pi_work_func);

    priv->hs_po_dwq = create_singlethread_workqueue("hs_po_dwq");
    if (NULL == priv->hs_po_dwq) {
        loge("hs_po_dwq workqueue create failed\n");
        return -EFAULT;
    }
    INIT_DELAYED_WORK(&priv->hs_po_dw, hi6555c_hs_po_work_func);

    priv->hs_comp_l_btn_down_dwq = create_singlethread_workqueue("hs_comp_l_btn_down_dwq");
    if (NULL == priv->hs_comp_l_btn_down_dwq) {
        loge("hs_btn_dwq workqueue create failed\n");
        return -EFAULT;
    }
    INIT_DELAYED_WORK(&priv->hs_comp_l_btn_down_dw, hi6555c_hs_comp_l_btn_down_work_func);

    priv->hs_comp_l_btn_up_dwq = create_singlethread_workqueue("hs_comp_l_btn_up_dwq");
    if (NULL == priv->hs_comp_l_btn_up_dwq) {
        loge("hs_btn_dwq workqueue create failed\n");
        return -EFAULT;
    }
    INIT_DELAYED_WORK(&priv->hs_comp_l_btn_up_dw, hi6555c_hs_comp_l_btn_up_work_func);

    priv->hs_comp_h_btn_down_dwq = create_singlethread_workqueue("hs_comp_h_btn_down_dwq");
    if (NULL == priv->hs_comp_h_btn_down_dwq) {
        loge("hs_btn_dwq workqueue create failed\n");
        return -EFAULT;
    }
    INIT_DELAYED_WORK(&priv->hs_comp_h_btn_down_dw, hi6555c_hs_comp_h_btn_down_work_func);

    priv->hs_comp_h_btn_up_dwq = create_singlethread_workqueue("hs_comp_h_btn_up_dwq");
    if (NULL == priv->hs_comp_h_btn_up_dwq) {
        loge("hs_btn_dwq workqueue create failed\n");
        return -EFAULT;
    }
    INIT_DELAYED_WORK(&priv->hs_comp_h_btn_up_dw, hi6555c_hs_comp_h_btn_up_work_func);

    priv->hs_eco_btn_down_dwq = create_singlethread_workqueue("hs_eco_btn_down_dwq");
    if (NULL == priv->hs_eco_btn_down_dwq) {
        loge("hs_btn_dwq workqueue create failed\n");
        return -EFAULT;
    }
    INIT_DELAYED_WORK(&priv->hs_eco_btn_down_dw, hi6555c_hs_eco_btn_down_work_func);

    priv->hs_eco_btn_up_dwq = create_singlethread_workqueue("hs_eco_btn_up_dwq");
    if (NULL == priv->hs_eco_btn_up_dwq) {
        loge("hs_btn_dwq workqueue create failed\n");
        return -EFAULT;
    }
    INIT_DELAYED_WORK(&priv->hs_eco_btn_up_dw, hi6555c_hs_eco_btn_up_work_func);

    priv->hs_micbias_hkadc_dwq = create_singlethread_workqueue("hs_micbias_hkadc_dwq");
    if (NULL == priv->hs_micbias_hkadc_dwq) {
        loge("hs_micbias_hkadc_dwq workqueue create failed\n");
        return -EFAULT;
    }
    INIT_DELAYED_WORK(&priv->hs_micbias_hkadc_dw, hi6555c_hs_micbias_hkadc_work_func);

    /* config intr for codec */
#if 0//todo fixme: hi6250
    priv->gpio_intr_pin = of_get_gpio_by_prop(np, "gpio_headset_intr_line",0,0, &flags);
    if (0 > priv->gpio_intr_pin) {
        loge("get gpio flags error(0x%x)\n", priv->gpio_intr_pin);
        return -EFAULT;
    }
    priv->gpio_irq = gpio_to_irq(priv->gpio_intr_pin);
    logd("gpio_to_irq, gp_irq = %d(%d)", priv->gpio_irq, priv->gpio_intr_pin);

    /* irq shared with pmu */
    ret = request_irq(priv->gpio_irq, hi6555c_irq_handler, IRQF_TRIGGER_LOW | IRQF_SHARED | IRQF_NO_SUSPEND, "codec_irq", codec);
    if (ret) {
        loge("request_irq, ret = %d\n", ret);
        return -EFAULT;
    }
#endif
    /* judge headset present or not */
    logd("irq soure stat %#04x",hi6555c_reg_read(codec, HI6555C_SMT_ANA_IRQ_SIG_STAT_ADDR));
    if (hi6555c_irq_stat(IRQ_STAT_PLUG_IN)) {
        hs_plug_in_detect_func(codec);
    } else {
        hi6555c_irqs_mask_clr(IRQ_PLUG_IN);
    }

END:
    return ret;
}

static int hi6555c_set_priv(struct snd_soc_codec *codec)
{
    struct hi6555c_priv *priv = NULL;
    struct device *dev = codec->dev;

    priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
    if (!priv) {
        loge("priv devm_kzalloc failed\n");
        return -ENOMEM;
    }

    snd_soc_codec_set_drvdata(codec, priv);

    g_codec = codec;
    priv->codec = codec;

    /* virtual codec register init */
    priv->v_codec_reg[0] = 0;
    priv->v_codec_reg[1] = 0;

    spin_lock_init(&priv->lock);
    mutex_init(&priv->io_mutex);
    mutex_init(&priv->ibias_mutex);
    mutex_init(&priv->hs_micbias_mutex);
    mutex_init(&priv->hkadc_mutex);
    mutex_init(&priv->plug_mutex);
    wake_lock_init(&priv->wake_lock, WAKE_LOCK_SUSPEND, "hi6555c");

    return 0;
}

static void hi6555c_free_resource(struct snd_soc_codec *codec)
{
    struct hi6555c_priv *priv = NULL;

    priv = snd_soc_codec_get_drvdata(codec);
    if (NULL == priv) {
        loge("priv is NULL\n");
        return ;
    }

    if (NULL != priv->btn_voltage) {
        kfree(priv->btn_voltage);
        priv->btn_voltage = NULL;
    }

    if (NULL != priv->headset_voltage) {
        kfree(priv->headset_voltage);
        priv->headset_voltage = NULL;
    }

    if (NULL != priv->hs_jack) {
        if (NULL != priv->hs_jack->jack) {
            kfree(priv->hs_jack->jack);
            priv->hs_jack->jack = NULL;
        }

        kfree(priv->hs_jack);
        priv->hs_jack = NULL;
    }

#ifdef CONFIG_DEBUG_FS
    if (NULL != priv->df_dir) {
        debugfs_remove(priv->df_dir);
        priv->df_dir = NULL;
    }
#endif

    if (NULL != priv->hs_pi_dwq) {
        cancel_delayed_work(&priv->hs_pi_dw);
        flush_workqueue(priv->hs_pi_dwq);
        destroy_workqueue(priv->hs_pi_dwq);
        priv->hs_pi_dwq = NULL;
    }

    if (NULL != priv->hs_po_dwq) {
        cancel_delayed_work(&priv->hs_po_dw);
        flush_workqueue(priv->hs_po_dwq);
        destroy_workqueue(priv->hs_po_dwq);
        priv->hs_po_dwq = NULL;
    }

    if (NULL != priv->hs_comp_l_btn_down_dwq) {
        cancel_delayed_work(&priv->hs_comp_l_btn_down_dw);
        flush_workqueue(priv->hs_comp_l_btn_down_dwq);
        destroy_workqueue(priv->hs_comp_l_btn_down_dwq);
        priv->hs_comp_l_btn_down_dwq = NULL;
    }

    if (NULL != priv->hs_comp_l_btn_up_dwq) {
        cancel_delayed_work(&priv->hs_comp_l_btn_up_dw);
        flush_workqueue(priv->hs_comp_l_btn_up_dwq);
        destroy_workqueue(priv->hs_comp_l_btn_up_dwq);
        priv->hs_comp_l_btn_up_dwq = NULL;
    }

    if (NULL != priv->hs_comp_h_btn_down_dwq) {
        cancel_delayed_work(&priv->hs_comp_h_btn_down_dw);
        flush_workqueue(priv->hs_comp_h_btn_down_dwq);
        destroy_workqueue(priv->hs_comp_h_btn_down_dwq);
        priv->hs_comp_h_btn_down_dwq = NULL;
    }

    if (NULL != priv->hs_comp_h_btn_up_dwq) {
        cancel_delayed_work(&priv->hs_comp_h_btn_up_dw);
        flush_workqueue(priv->hs_comp_h_btn_up_dwq);
        destroy_workqueue(priv->hs_comp_h_btn_up_dwq);
        priv->hs_comp_h_btn_up_dwq = NULL;
    }

    if (NULL != priv->hs_eco_btn_down_dwq) {
        cancel_delayed_work(&priv->hs_eco_btn_down_dw);
        flush_workqueue(priv->hs_eco_btn_down_dwq);
        destroy_workqueue(priv->hs_eco_btn_down_dwq);
        priv->hs_eco_btn_down_dwq = NULL;
    }

    if (NULL != priv->hs_eco_btn_up_dwq) {
        cancel_delayed_work(&priv->hs_eco_btn_up_dw);
        flush_workqueue(priv->hs_eco_btn_up_dwq);
        destroy_workqueue(priv->hs_eco_btn_up_dwq);
        priv->hs_eco_btn_up_dwq = NULL;
    }

    if (NULL != priv->hs_micbias_hkadc_dwq) {
        cancel_delayed_work(&priv->hs_micbias_hkadc_dw);
        flush_workqueue(priv->hs_micbias_hkadc_dwq);
        destroy_workqueue(priv->hs_micbias_hkadc_dwq);
        priv->hs_micbias_hkadc_dwq = NULL;
    }

    if (NULL != priv->regulator_avdd1v8) {
        regulator_put(priv->regulator_avdd1v8);
        priv->regulator_avdd1v8 = NULL;
    }

    if (NULL != priv->regulator_schg_boost3) {
        regulator_put(priv->regulator_schg_boost3);
        priv->regulator_schg_boost3 = NULL;
    }

    if(NULL != priv->codec_apb) {
        clk_disable_unprepare(priv->codec_apb);
        priv->codec_apb = NULL;
    }

    if (NULL != priv) {
        wake_lock_destroy(&priv->wake_lock);
    }

    /* at last free priv */
    kfree(priv);
    priv = NULL;
    g_codec = NULL;

    return;
}

static int hi6555c_codec_probe(struct snd_soc_codec *codec)
{
    int ret = 0;
    struct snd_soc_dapm_context *dapm = &codec->dapm;

    logi("Begin");
    ret = hi6555c_set_priv(codec);
    if (0 != ret) {
        loge("hi6555c_set_priv err\n");
        hi6555c_free_resource(codec);
        return ret;
    }
    logi("hi6555c_set_priv OK\n");
    ret = hi6555c_soc_init(codec);
    if (0 != ret) {
        loge("hi6555c_soc_init err\n");
        hi6555c_free_resource(codec);
        return ret;
    }
    logi("hi6555c_soc_init OK\n");
    ret = hi6555c_headset_init(codec);
    if (0 != ret) {
        loge("hi6555c_headset_init err\n");
        hi6555c_free_resource(codec);
        return ret;
    }
    logi("hi6555c_headset_init OK\n");
    ret = snd_soc_dapm_sync(dapm);
    if (0 != ret) {
        loge("dapm sync error, errornum = %d\n", ret);
        hi6555c_free_resource(codec);
    }
    logi("dapm sync OK");
    logi("End");

    return ret;
}

static int hi6555c_codec_remove(struct snd_soc_codec *codec)
{
    /*TODO*/
    hi6555c_free_resource(codec);

    return 0;
}

static struct snd_soc_codec_driver soc_codec_dev_hi6555c = {
    .probe    = hi6555c_codec_probe,
    .remove  = hi6555c_codec_remove,
    .read      = hi6555c_reg_read,
    .write     = hi6555c_reg_write,
    .controls = hi6555c_snd_controls,
    .num_controls = ARRAY_SIZE(hi6555c_snd_controls),
    .dapm_widgets = hi6555c_dapm_widgets,
    .num_dapm_widgets = ARRAY_SIZE(hi6555c_dapm_widgets),
    .dapm_routes = hi6555c_route_map,
    .num_dapm_routes = ARRAY_SIZE(hi6555c_route_map),
};

static int hi6555c_probe(struct platform_device *pdev)
{
    struct device *dev = &(pdev->dev);
    struct resource *res = NULL;

    logi("Begin");
    /* get soccodec register base address */
    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!res) {
        loge("platform_get_resource 0 err\n");
        return -ENOENT;
    }

    g_hi6555c_socodec_base_addr = (char* __force)(ioremap(res->start, resource_size(res)));
    logi("soccodec res->start: %p, size: 0x%x, g_hi6555c_socodec_base_addr: %p\n", res->start, resource_size(res), g_hi6555c_socodec_base_addr);
    if (!g_hi6555c_socodec_base_addr) {
        loge("cannot map register memory\n");
        return -ENOMEM;
    }

    /* get pmuspi register base address */
    res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
    if (!res) {
        loge("platform_get_resource 1 err\n");
        return -ENOENT;
    }

    g_hi6555c_reg_base_addr = (char* __force)(ioremap(res->start, resource_size(res)));
    logi("pmuspi res->start: %p, size: 0x%x, g_hi6555c_reg_base_addr: %p\n", res->start, resource_size(res), g_hi6555c_reg_base_addr);
    if (!g_hi6555c_reg_base_addr) {
        loge("cannot map register memory\n");
        return -ENOMEM;
    }

    /* get hkadc register base address */
    res = platform_get_resource(pdev, IORESOURCE_MEM, 2);
    if (!res) {
        loge("platform_get_resource 2 err\n");
        return -ENOENT;
    }

    g_hi6555c_hkadc_reg_base_addr = (char* __force)(ioremap(res->start, resource_size(res)));
    logi("hkadc res->start: %p, size: 0x%x, g_hi6555c_hkadc_reg_base_addr: %p\n", res->start, resource_size(res), g_hi6555c_hkadc_reg_base_addr);
    if (!g_hi6555c_hkadc_reg_base_addr) {
        loge("cannot map register memory\n");
        return -ENOMEM;
    }

    /* get psctrl register base address */
    res = platform_get_resource(pdev, IORESOURCE_MEM, 3);
    if (!res) {
        loge("platform_get_resource 3 err\n");
        return -ENOENT;
    }

    g_hi6555c_psctrl_base_addr = (char* __force)ioremap(res->start, resource_size(res));
    logi("psctrl res->start: %p, size: 0x%x, g_hi6555c_psctrl_base_addr: %p\n", res->start, resource_size(res), g_hi6555c_psctrl_base_addr);
    /* fixme: begin for hi6250*/
    if (!g_hi6555c_psctrl_base_addr) {
        loge("cannot map psctrl memory\n");
        return -ENOMEM;
    }

    /* get aspcfg register base address */
    res = platform_get_resource(pdev, IORESOURCE_MEM, 4);
    if (!res) {
        loge("platform_get_resource 4 err\n");
        return -ENOENT;
    }

    g_hi6555c_aspcfg_base_addr = (char* __force)ioremap(res->start, resource_size(res));
    logi("aspcfg res->start: %p, size: 0x%x, g_hi6555c_aspcfg_base_addr: %p\n", res->start, resource_size(res), g_hi6555c_aspcfg_base_addr);
    if (!g_hi6555c_aspcfg_base_addr) {
        loge("cannot map aspcfg memory\n");
        return -ENOMEM;
    }

    /* get AO_IOC register base address */
    res = platform_get_resource(pdev, IORESOURCE_MEM, 5);
    if (!res) {
        loge("platform_get_resource 5 err\n");
        return -ENOENT;
    }

    g_hi6555c_aoioc_base_addr = (char* __force)ioremap(res->start, resource_size(res));
    logi("aoioc res->start: %p, size: 0x%x, g_hi6555c_aoioc_base_addr: %p\n", res->start, resource_size(res), g_hi6555c_aoioc_base_addr);
    if (!g_hi6555c_aoioc_base_addr) {
        loge("cannot map aoioc memory\n");
        return -ENOMEM;
    }

    /* get IOC register base address */
    res = platform_get_resource(pdev, IORESOURCE_MEM, 6);
    if (!res) {
        loge("platform_get_resource 6 err\n");
        return -ENOENT;
    }

    g_hi6555c_ioc_base_addr = (char* __force)ioremap(res->start, resource_size(res));
    logi("ioc res->start: %p, size: 0x%x, g_hi6555c_ioc_base_addr: %p\n", res->start, resource_size(res), g_hi6555c_ioc_base_addr);
    if (!g_hi6555c_ioc_base_addr) {
        loge("cannot map ioc memory\n");
        return -ENOMEM;
    }

    /* get gpio21 register base address */
    res = platform_get_resource(pdev, IORESOURCE_MEM, 7);
    if (!res) {
        loge("platform_get_resource 7 err\n");
        return -ENOENT;
    }

    g_hi6555c_gpio21_base_addr = (char* __force)ioremap(res->start, resource_size(res));
    logi("gpio21 res->start: %p, size: 0x%x, g_hi6555c_gpio21_base_addr: %p\n", res->start, resource_size(res), g_hi6555c_gpio21_base_addr);
    if (!g_hi6555c_gpio21_base_addr) {
        loge("cannot map gpio21 memory\n");
        return -ENOMEM;
    }

    /* get pericrg register base address */
    res = platform_get_resource(pdev, IORESOURCE_MEM, 8);
    if (!res) {
        loge("platform_get_resource 8 err\n");
        return -ENOENT;
    }

        g_hi6555c_pericrg_base_addr = (char* __force)ioremap(res->start, resource_size(res));
    logi("pericrg res->start: %p, size: 0x%x, g_hi6555c_pericrg_base_addr: %p\n", res->start, resource_size(res), g_hi6555c_pericrg_base_addr);
    if (!g_hi6555c_pericrg_base_addr) {
        loge("cannot map perireg memory\n");
        return -ENOMEM;
    }

    /* fixme: end for hi6250*/
    logi("End");

    return snd_soc_register_codec(&pdev->dev, &soc_codec_dev_hi6555c, hi6555c_dai, ARRAY_SIZE(hi6555c_dai));
}

static int hi6555c_remove(struct platform_device *pdev)
{
    logd("Begin\n");
    snd_soc_unregister_codec(&pdev->dev);
#if 0
    if (!IS_ERR(g_codec_clk))
        clk_put(g_codec_clk);
#endif
    return 0;
}

static const struct of_device_id hi6555c_codec_match[] = {
    { .compatible = "hi6555c-codec", },
    {},
};

static struct platform_driver hi6555c_driver = {
    .driver = {
        .name  = "hi6555c-codec",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(hi6555c_codec_match),
    },
    .probe  = hi6555c_probe,
    .remove = hi6555c_remove,
    .suspend = hi6555c_suspend,
    .resume  = hi6555c_resume,
    .shutdown = hi6555c_shutdown,
};

static int __init hi6555c_codec_init(void)
{
    logi("Begin\n");
    return platform_driver_register(&hi6555c_driver);
}
module_init(hi6555c_codec_init);

static void __exit hi6555c_codec_exit(void)
{
    logi("Begin\n");
    platform_driver_unregister(&hi6555c_driver);
}
module_exit(hi6555c_codec_exit);

MODULE_DESCRIPTION("ASoC hi6555c driver");
MODULE_LICENSE("GPL");
