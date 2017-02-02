/*lint -save -e19 -e123 -e537 -e713*/
#include "usb_vendor.h"
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/usb/bsp_acm.h>

#define ERROR (-1)
#define OK (0)

#define USB_ENABLE_CB_MAX 32
typedef enum{
    USB_ENUM_DONE_CB_MSP = 0,
    USB_ENUM_DONE_CB_PS,
    USB_ENUM_DONE_CB_BSP,
    USB_ENUM_DONE_CB_BOTTEM
}USB_ENUM_DONE_CB_E;

typedef void (*usb_enum_done_cb_t)(void);

typedef struct
{
        usb_enum_done_cb_t enum_done_cbs[USB_ENUM_DONE_CB_BOTTEM];
        USB_UDI_ENABLE_CB_T udi_enable_cb[USB_ENABLE_CB_MAX];
        USB_UDI_DISABLE_CB_T udi_disable_cb[USB_ENABLE_CB_MAX];
}USB_CTX_S;

static unsigned g_usb_enum_done_cur = 0;
static unsigned g_usb_enum_dis_cur = 0;

static struct notifier_block gs_adp_usb_nb;
static struct notifier_block *gs_adp_usb_nb_ptr = NULL;
static int g_usb_enum_done_notify_complete = 0;
static int g_usb_disable_notify_complete = 0;
static USB_CTX_S g_usb_ctx = {{0},{0},{0}};

/********************************************************
函数说明：协议栈注册USB使能通知回调函数
函数功能:
输入参数：pFunc: USB使能回调函数指针
输出参数：无
输出参数：无
返回值  ：0：成功
          1：失败
********************************************************/
unsigned int BSP_USB_RegUdiEnableCB(USB_UDI_ENABLE_CB_T pFunc)
{
    if (g_usb_enum_done_cur >= USB_ENABLE_CB_MAX)
    {
        printk("BSP_USB_RegUdiEnableCB error:0x%lx", (unsigned long)pFunc);
        return (unsigned int)ERROR;
    }

    g_usb_ctx.udi_enable_cb[g_usb_enum_done_cur] = pFunc;
    g_usb_enum_done_cur++;

    if (g_usb_enum_done_notify_complete)
    {
            if (pFunc)
                    pFunc();
    }

    return OK;
}

/********************************************************
函数说明：协议栈注册USB去使能通知回调函数
函数功能:
输入参数：pFunc: USB去使能回调函数指针
输出参数：无
输出参数：无
返回值  ：0：成功
          1：失败
********************************************************/
unsigned int BSP_USB_RegUdiDisableCB(USB_UDI_DISABLE_CB_T pFunc)
{
    if (g_usb_enum_dis_cur >= USB_ENABLE_CB_MAX)
    {
        printk("BSP_USB_RegUdiDisableCB error:0x%lx", (unsigned long)pFunc);
        return (unsigned int)ERROR;
    }

    g_usb_ctx.udi_disable_cb[g_usb_enum_dis_cur] = pFunc;
    g_usb_enum_dis_cur++;

    return OK;
}

static int gs_usb_adp_notifier_cb(struct notifier_block *nb,
            unsigned long event, void *priv)
{
    int loop;

    switch (event) {

    case USB_BALONG_DEVICE_INSERT:
        g_usb_disable_notify_complete = 0;
        break;
    case USB_BALONG_ENUM_DONE:
        /* enum done */
        g_usb_disable_notify_complete = 0;
        if (!g_usb_enum_done_notify_complete) {
            for(loop = 0; loop < USB_ENUM_DONE_CB_BOTTEM; loop++)
            {
                if(g_usb_ctx.enum_done_cbs[loop])
                    g_usb_ctx.enum_done_cbs[loop]();
            }

            for(loop = 0; loop < USB_ENABLE_CB_MAX; loop++)
            {
                if(g_usb_ctx.udi_enable_cb[loop])
                    g_usb_ctx.udi_enable_cb[loop]();
            }
        }
        g_usb_enum_done_notify_complete = 1;
        break;
    case USB_BALONG_DEVICE_DISABLE:
    case USB_BALONG_DEVICE_REMOVE:
        /* notify other cb */
        g_usb_enum_done_notify_complete = 0;
        if (!g_usb_disable_notify_complete) {
            for(loop = 0; loop < USB_ENABLE_CB_MAX; loop++)
            {
                if(g_usb_ctx.udi_disable_cb[loop])
                    g_usb_ctx.udi_disable_cb[loop]();
            }
            g_usb_disable_notify_complete = 1;
        }
        break;
    default:
        break;
    }
    return 0;
}

int __init adp_usb_init(void)
{
    /* we just regist once, and don't unregist any more */
    if (!gs_adp_usb_nb_ptr) {
        gs_adp_usb_nb_ptr = &gs_adp_usb_nb;
        gs_adp_usb_nb.priority = USB_NOTIF_PRIO_ADP;
        gs_adp_usb_nb.notifier_call = gs_usb_adp_notifier_cb;
        bsp_usb_register_notify(gs_adp_usb_nb_ptr);
    }
    return 0;
}
module_init(adp_usb_init);
/*lint -restore*/
