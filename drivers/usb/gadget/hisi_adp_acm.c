#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/skbuff.h>

#include <linux/usb/drv_acm.h>
#include <linux/usb/bsp_acm.h>
#include <linux/usb/drv_udi.h>

struct adp_acm_stat {
    int stat_open_err;
    long stat_open_last_err;
    int stat_read_err;
    int stat_read_last_err;
    int stat_write_err;
    int stat_write_last_err;
    int stat_ioctl_err;
    int stat_ioctl_last_err;
    int stat_wait_close;
};

struct adp_acm_context {
    char* dev_name;
    int is_open;
    atomic_t opt_cnt;
    struct adp_acm_stat stat;
};


static struct adp_acm_context adp_acm_ctx[] = {
    {"/dev/acm_ctrl",          /*UDI_USB_ACM_CTRL*/ 0, {0}, {0}},
    {"/dev/acm_at",            /*UDI_USB_ACM_AT*/ 0, {0}, {0}},
    {"/dev/acm_c_shell",       /*UDI_USB_ACM_SHELL*/ 0, {0}, {0}},
    {"/dev/acm_4g_diag",       /*UDI_USB_ACM_LTE_DIAG*/ 0, {0}, {0}},
    {"/dev/acm_3g_diag",       /*UDI_USB_ACM_OM*/ 0, {0}, {0}},
    {"/dev/acm_modem",         /*UDI_USB_ACM_MODEM*/ 0, {0}, {0}},
    {"/dev/acm_gps",           /*UDI_USB_ACM_GPS*/ 0, {0}, {0}},
    {"/dev/acm_a_shell",       /*UDI_USB_ACM_3G_GPS*/ 0, {0}, {0}},
    {"/dev/acm_3g_pcvoice",		/*UDI_USB_ACM_3G_PCVOICE*/ 0, {0}, {0}},
    {"/dev/acm_pcvoice",           /*UDI_USB_ACM_PCVOICE*/ 0, {0}, {0}},
    {"/dev/acm_skytone",         /*UDI_USB_ACM_SKYTONE*/ 0, {0}, {0}},
    {"/dev/acm_err", 		0, {0}, {0}},
};
static int stat_invalid_devid = 0;
static int stat_invalid_filp = 0;

#define ADP_ACM_FILP_INVALID(filp) (!(filp)  || IS_ERR(filp) || !filp->private_data)

/*****************************************************************************
* 函 数 名  : bsp_acm_open
*
* 功能描述  : 打开设备(数据通道)
*
* 输入参数  : dev_id: 设备id
* 输出参数  : 无
* 返 回 值  :
*****************************************************************************/
void *bsp_acm_open(u32 dev_id)
{
    char* name;
    struct file* filp;

    if (dev_id >= sizeof(adp_acm_ctx) / sizeof(struct adp_acm_context)) {
        stat_invalid_devid++;
        return ERR_PTR(-EINVAL);
    }
    name = adp_acm_ctx[dev_id].dev_name;

    filp = filp_open(name, O_RDWR, 0);
    if (IS_ERR(filp)) {
        adp_acm_ctx[dev_id].stat.stat_open_err++;
        adp_acm_ctx[dev_id].stat.stat_open_last_err = (long)filp;
        return ERR_PTR(-EIO);
    }
    filp->private_data = &adp_acm_ctx[dev_id];
    adp_acm_ctx[dev_id].is_open = 1;

    return (void *)filp;
}

/*****************************************************************************
* 函 数 名  : bsp_acm_close
*
* 功能描述  : 关闭设备(数据通道)
*
* 输入参数  : handle: 设备的handle
* 输出参数  : 无
* 返 回 值  : 成功/失败
*****************************************************************************/
s32 bsp_acm_close(void *handle)
{
    struct file* filp = (struct file*)handle;
    struct adp_acm_context* ctx;

    if (unlikely(ADP_ACM_FILP_INVALID(filp))) {
        stat_invalid_filp++;
        return -EINVAL;
    }

    ctx = (struct adp_acm_context*)filp->private_data;
    ctx->is_open = 0;

    /* wait for file opt complete */
    while(atomic_read(&ctx->opt_cnt)) {
        ctx->stat.stat_wait_close++;
        msleep(10);
    }

    filp_close(filp, NULL);
    return 0;
}

/*****************************************************************************
* 函 数 名  : bsp_acm_write
*
* 功能描述  : 数据写
*
* 输入参数  : handle:  设备的handle
*             buf: 地址
*             size: 大小
* 输出参数  :
*
* 返 回 值  : 完成字节数 或 成功/失败
*****************************************************************************/
s32 bsp_acm_write(void *handle, void *buf, u32 size)
{
    mm_segment_t old_fs;
    struct file* filp = (struct file*)handle;
    struct adp_acm_context* ctx;
    int status;
    loff_t pos = 0;

    if (unlikely(ADP_ACM_FILP_INVALID(filp))) {
        stat_invalid_filp++;
        return -EINVAL;
    }
    ctx = (struct adp_acm_context*)filp->private_data;

    atomic_inc(&ctx->opt_cnt);
    if (unlikely(!ctx->is_open || !(filp->f_path.dentry))) {
        status = -ENXIO;
        goto write_ret;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    status = vfs_write(filp, (void __force __user *)buf, size, &pos);
    set_fs(old_fs);

write_ret:
    atomic_dec(&ctx->opt_cnt);
    if (status < 0) {
        ctx->stat.stat_write_err++;
        ctx->stat.stat_write_last_err = status;
    }
    return status;
}

/*****************************************************************************
* 函 数 名  : bsp_acm_read
*
* 功能描述  : 数据读
*
* 输入参数  : handle:  设备的handle
*             buf: 地址
*             size: 大小
* 输出参数  :
*
* 返 回 值  : 完成字节数 或 成功/失败
*****************************************************************************/
s32 bsp_acm_read(void *handle, void *buf, u32 size)
{
    mm_segment_t old_fs;
    struct file* filp = (struct file*)handle;
    struct adp_acm_context* ctx;
    int status;
    loff_t pos = 0;

    if (unlikely(ADP_ACM_FILP_INVALID(filp))) {
        stat_invalid_filp++;
        /* protect system running, usr often use read in while(1). */
        msleep(10);
        return -EINVAL;
    }
    ctx = (struct adp_acm_context*)filp->private_data;

    atomic_inc(&ctx->opt_cnt);
    if (unlikely(!ctx->is_open || !(filp->f_path.dentry))) {
        status = -ENXIO;
        goto read_ret;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);
    status = vfs_read(filp, (void __force __user *)buf, size, &pos);
    set_fs(old_fs);

read_ret:
    atomic_dec(&ctx->opt_cnt);
    if (status <= 0) {
        /* protect system running, usr often use read in while(1). */
        msleep(100);
        ctx->stat.stat_read_err++;
        ctx->stat.stat_read_last_err = status;
    }
    return status;
}

/*****************************************************************************
* 函 数 名  : bsp_acm_ioctl
*
* 功能描述  : 数据通道属性配置
*
* 输入参数  : handle: 设备的handle
*             u32Cmd: IOCTL命令码
*             pParam: 操作参数
* 输出参数  :
*
* 返 回 值  : 成功/失败
*****************************************************************************/
s32 bsp_acm_ioctl(void *handle, u32 cmd, void *para)
{
    mm_segment_t old_fs;
    struct file* filp = (struct file*)handle;
    struct adp_acm_context* ctx;
    int status;

    if (unlikely(ADP_ACM_FILP_INVALID(filp))) {
        stat_invalid_filp++;
        return -EINVAL;
    }
    ctx = (struct adp_acm_context*)filp->private_data;

    atomic_inc(&ctx->opt_cnt);
    if (unlikely(!ctx->is_open || !(filp->f_path.dentry))) {
        status = -ENXIO;
        goto ioctl_ret;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    status = do_vfs_ioctl(filp, 0, (unsigned int)cmd, (unsigned long)para);
    set_fs(old_fs);

ioctl_ret:
    atomic_dec(&ctx->opt_cnt);
    if (status < 0) {
        ctx->stat.stat_ioctl_err++;
        ctx->stat.stat_ioctl_last_err = status;
    }
    return status;
}

void acm_adp_dump(void)
{
    int i;

    printk("stat_invalid_devid      :%d\n", stat_invalid_devid);
    printk("stat_invalid_filp       :%d\n", stat_invalid_filp);
    for (i = 0; i < sizeof(adp_acm_ctx) / sizeof(struct adp_acm_context); i++) {
        printk("==== dump dev:%s ====\n", adp_acm_ctx[i].dev_name);
        printk("is_open             :%d\n", adp_acm_ctx[i].is_open);
        printk("opt_cnt             :%d\n", atomic_read(&adp_acm_ctx[i].opt_cnt));
        printk("stat_open_err       :%d\n", adp_acm_ctx[i].stat.stat_open_err);
        printk("stat_open_last_err  :%ld\n", adp_acm_ctx[i].stat.stat_open_last_err);
        printk("stat_read_err       :%d\n", adp_acm_ctx[i].stat.stat_read_err);
        printk("stat_read_last_err  :%d\n", adp_acm_ctx[i].stat.stat_read_last_err);
        printk("stat_write_err      :%d\n", adp_acm_ctx[i].stat.stat_write_err);
        printk("stat_write_last_err :%d\n", adp_acm_ctx[i].stat.stat_write_last_err);
        printk("stat_ioctl_err      :%d\n", adp_acm_ctx[i].stat.stat_ioctl_err);
        printk("stat_ioctl_last_err :%d\n", adp_acm_ctx[i].stat.stat_ioctl_last_err);
        printk("stat_wait_close     :%d\n", adp_acm_ctx[i].stat.stat_wait_close);
        printk("\n");
    }
}


#define HISI_MODEM_TEST
#ifdef HISI_MODEM_TEST
typedef enum tagACM_MODEM_SIG_TYPE
{
    ACM_MODEM_SIG_DSR,
    ACM_MODEM_SIG_DCD,
    ACM_MODEM_SIG_RING,
    ACM_MODEM_SIG_CTS_RECV_EN,
    ACM_MODEM_SIG_CTS_RECV_DIS,
    ACM_MODEM_SIG_WRITE_ALL,
    ACM_MODE_SIG_MAX
}ACM_MODEM_SIG_TYPE;

void *p_modem_handle = NULL;
#define SKB_BUF_SIZE   2048
static struct sk_buff *g_loop_skb = NULL;
static struct sk_buff *g_write_skb = NULL;

int bsp_usb_st_acm_mode_clean_cb(void)
{
    if (bsp_acm_ioctl(p_modem_handle, ACM_IOCTL_SET_READ_CB, NULL)) {
        printk(KERN_ERR "ACM_IOCTL_SET_READ_CB fail\n");
        return -1;
    }

    if (bsp_acm_ioctl(p_modem_handle, ACM_IOCTL_SET_FREE_CB, NULL)) {
        printk(KERN_ERR "ACM_IOCTL_SET_FREE_CB fail\n");
        return -1;
    }

    if (bsp_acm_ioctl(p_modem_handle, ACM_MODEM_IOCTL_SET_MSC_READ_CB, NULL)) {
        printk(KERN_ERR "ACM_MODEM_IOCTL_SET_MSC_READ_CB fail\n");
        return -1;
    }

    if (bsp_acm_ioctl(p_modem_handle, ACM_MODEM_IOCTL_SET_REL_IND_CB, NULL)) {
        printk(KERN_ERR "ACM_MODEM_IOCTL_SET_REL_IND_CB fail\n");
        return -1;
    }

    return 0;
}

int bsp_usb_st_acm_modem_open(void)
{
    p_modem_handle = bsp_acm_open(UDI_ACM_MODEM_ID);
    if (IS_ERR(p_modem_handle)) {
        printk(KERN_ERR "bsp_usb_st_acm_modem_open: %p\n", p_modem_handle);
        return -1;
    }

    if (g_loop_skb == NULL) {
        g_loop_skb = alloc_skb(SKB_BUF_SIZE, GFP_KERNEL);
        if (!g_loop_skb) {
            printk(KERN_ERR "alloc g_loop_skb fail!\n");
            return -ENOMEM;
        }
    }

    if (g_write_skb == NULL) {
        g_write_skb = alloc_skb(SKB_BUF_SIZE, GFP_KERNEL);
        if (!g_write_skb) {
            printk(KERN_ERR "alloc g_write_skb fail!\n");
            return -ENOMEM;
        }
    }

    if (bsp_usb_st_acm_mode_clean_cb()) {
        printk(KERN_ERR "clean cb fail!\n");
        return -1;
    }

    return 0;
}

int bsp_usb_st_acm_modem_close(void)
{
    int ret = 0;

    if (NULL != g_write_skb) {
        dev_kfree_skb(g_write_skb);
        g_write_skb = NULL;
    }

    if (NULL != g_loop_skb) {
        dev_kfree_skb(g_loop_skb);
        g_loop_skb = NULL;
    }

    ret = bsp_acm_close(p_modem_handle);
    if (ret < 0) {
        printk(KERN_ERR "bsp_usb_st_acm_modem_close: return %d\n", ret);
        return -1;
    }
    return 0;
}

int bsp_usb_st_acm_modem_signal(ACM_MODEM_SIG_TYPE sig)
{
    int s32Status = 0;
    MODEM_MSC_STRU stModemMsc = {0};

    switch(sig)
    {
    case ACM_MODEM_SIG_DSR:
        stModemMsc.OP_Dsr = 1;
        stModemMsc.ucDsr = 1;
        break;
    case ACM_MODEM_SIG_DCD:
        stModemMsc.OP_Dcd = 1;
        stModemMsc.ucDcd = 1;
        break;
    case ACM_MODEM_SIG_RING:
        stModemMsc.OP_Ri = 1;
        stModemMsc.ucRi = 1;
        break;
    case ACM_MODEM_SIG_CTS_RECV_EN:
        stModemMsc.OP_Cts = 1;
        stModemMsc.ucCts = 1;
        break;
    case ACM_MODEM_SIG_CTS_RECV_DIS:
        stModemMsc.OP_Cts = 1;
        stModemMsc.ucCts = 0;
        break;
    case ACM_MODEM_SIG_WRITE_ALL:
        stModemMsc.OP_Dsr = 1;
        stModemMsc.ucDsr = 1;
        stModemMsc.OP_Dcd = 1;
        stModemMsc.ucDcd = 1;
        stModemMsc.OP_Ri = 1;
        stModemMsc.ucRi = 1;
        stModemMsc.OP_Cts = 1;
        stModemMsc.ucCts = 1;
        break;
    default:
        break;
    }

    s32Status = bsp_acm_ioctl(p_modem_handle, ACM_MODEM_IOCTL_MSC_WRITE_CMD, &stModemMsc);
    if (s32Status < 0){
        printk(KERN_ERR "acm_modem_signal: bsp_acm_ioctl(MSC_WRITE_CMD)<0\n");
        return s32Status;
    }

    printk(KERN_ERR "Send To PC Successfully!\n");

    return 0;
}

int bsp_usb_st_acm_modem_dsr(void)
{

    return bsp_usb_st_acm_modem_signal(ACM_MODEM_SIG_DSR);
}

int bsp_usb_st_acm_modem_dcd(void)
{
    return bsp_usb_st_acm_modem_signal(ACM_MODEM_SIG_DCD);
}

int bsp_usb_st_acm_modem_ring(void)
{
    return  bsp_usb_st_acm_modem_signal(ACM_MODEM_SIG_RING);
}

int bsp_usb_st_acm_modem_recv_en(void)
{
    return  bsp_usb_st_acm_modem_signal(ACM_MODEM_SIG_CTS_RECV_EN);
}

int bsp_usb_st_acm_modem_recv_dis(void)
{
    return  bsp_usb_st_acm_modem_signal(ACM_MODEM_SIG_CTS_RECV_DIS);
}

int bsp_usb_st_acm_modem_write_signal_all(void)
{
    return  bsp_usb_st_acm_modem_signal(ACM_MODEM_SIG_WRITE_ALL);
}

int bsp_usb_modem_st_write(char* header,unsigned int len)
{
    struct sk_buff *send_skb = NULL;
    int ret = 0 ;
    ACM_WR_ASYNC_INFO send_info;
    unsigned value;

    if (header == NULL || len == 0) {
        return -EINVAL;
    }

    if (g_write_skb == NULL) {
        printk(KERN_ERR "acm[acm_modem] please firstly do ecall bsp_usb_st_acm_modem_open\n");
        return -1;
    }

    if (len > 4096) {
        printk(KERN_ERR "acm[acm_modem] len can't be bigger than 4096\n");
        return -1;
    }

    if (len > g_write_skb->truesize) {
        dev_kfree_skb(g_write_skb);
        printk(KERN_ERR "realloc g_write_skb\n");
        g_write_skb = alloc_skb(len, GFP_KERNEL);
    }

    value = header[0];
    send_skb = g_write_skb;
    skb_trim(send_skb, 0);
    memset((void *)send_skb->data, value, len);
    skb_put(send_skb, len);

    send_info.pVirAddr =  (char *)send_skb;
    send_info.pPhyAddr =  NULL;
    send_info.u32Size =  0;
    send_info.pDrvPriv =  NULL;

    bsp_acm_ioctl(p_modem_handle, ACM_IOCTL_WRITE_ASYNC, &send_info);
    if (ret != 0)
    {
        printk(KERN_ERR "acm[acm_modem] ACM_IOCTL_WRITE_ASYNC fail %d \n", ret);
    }

    return ret;

}

int bsp_usb_modem_st_set_do_copy(int enable)
{
    int ret;

    ret = bsp_acm_ioctl(p_modem_handle, ACM_IOCTL_WRITE_DO_COPY, &enable);
    if (ret != 0)
    {
        printk(KERN_ERR "acm[acm_modem] ACM_IOCTL_WRITE_DO_COPY fail %d \n", ret);
        return ret;
    }
    return 0;
}

void modem_loop_free_buff(char *pVirAddr)
{
    printk(KERN_ERR "acm[acm_modem] modem_loop_free_buff OK\n");
}

extern void acm_cdev_dump(int port_num);
static unsigned int write_egain_num = 0;
void modem_loop_recv_cb(void)
{
    ACM_WR_ASYNC_INFO mem_info;
    ACM_WR_ASYNC_INFO send_info;
    struct sk_buff *recv_skb = NULL;
    int ret = 0;

    ret = bsp_acm_ioctl(p_modem_handle, ACM_IOCTL_GET_RD_BUFF, &mem_info);
    if (ret < 0)
    {
        printk(KERN_ERR "acm[acm_modem] ACM_IOCTL_GET_RD_BUFF fail [ret=%d]\n", ret);
    }

    if (mem_info.pVirAddr == NULL) {
        printk(KERN_ERR "acm[acm_modem] mem_info.pVirAddr == NULL\n");
        return;
    }

    recv_skb = (struct sk_buff *)mem_info.pVirAddr;

    if (g_loop_skb == NULL) {
        printk(KERN_ERR "acm[acm_modem] please firstly do ecall bsp_usb_st_acm_modem_open\n");
        return;
    }

    if (recv_skb->len > g_loop_skb->truesize) {
        dev_kfree_skb(g_loop_skb);
        printk(KERN_ERR "realloc g_loop_skb\n");
        g_loop_skb = alloc_skb(recv_skb->len, GFP_KERNEL);
    }

    skb_trim(g_loop_skb, 0);
    memcpy((void *)g_loop_skb->data, (void *)recv_skb->data, recv_skb->len);
    skb_put(g_loop_skb, recv_skb->len);

    ret = bsp_acm_ioctl(p_modem_handle, ACM_IOCTL_RETURN_BUFF, &mem_info);
    if (ret < 0)
    {
        printk(KERN_ERR "acm[acm_modem] ACM_IOCTL_RETURN_BUFF fail [ret=%d]\n", ret);
    }

    send_info.pVirAddr =  (char *)g_loop_skb;
    send_info.pPhyAddr =  NULL;
    send_info.u32Size =  0;

    ret = bsp_acm_ioctl(p_modem_handle, ACM_IOCTL_WRITE_ASYNC, &send_info);
    if (ret == -EAGAIN) {
        printk(KERN_ERR "acm[acm_modem] ACM_IOCTL_WRITE_ASYNC EAGAIN\n");
        write_egain_num++;
        if (write_egain_num == 100) {
            bsp_acm_ioctl(p_modem_handle, UDI_IOCTL_SET_READ_CB, NULL);
            acm_cdev_dump(9);
        }
    } else if (ret < 0) {
        printk(KERN_ERR "acm[acm_modem] ACM_IOCTL_WRITE_ASYNC fail [ret=%d]\n", ret);
        acm_cdev_dump(9);
    } else {
        write_egain_num = 0;
    }
}

int bsp_usb_modem_st_loop(void)
{
    if (-1 == bsp_acm_ioctl(p_modem_handle, UDI_IOCTL_SET_READ_CB, modem_loop_recv_cb)) {
        printk(KERN_ERR "UDI_IOCTL_SET_READ_CB fail\n");
        return -1;
    }

    if (-1 == bsp_acm_ioctl(p_modem_handle, ACM_IOCTL_SET_FREE_CB, modem_loop_free_buff)) {
        printk(KERN_ERR "ACM_IOCTL_SET_FREE_CB fail\n");
        return -1;
    }

    return 0;
}
#endif
