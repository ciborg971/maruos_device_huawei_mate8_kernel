#include <linux/module.h>
#include <net/sock.h>
#include <linux/wait.h>
#include <linux/skbuff.h>
#include <linux/netlink.h>

#define NETLINK_TEST		22

struct sock *sys_nl_sock;


DEFINE_MUTEX(sys_nl_mutex);

void sys_send_msg(u32 pid)
{
    struct sk_buff *skb;
    struct nlmsghdr *nlhdr;
    int ret;
    char str[100] = "hello app\n";

    skb = alloc_skb(NLMSG_SPACE(1024), GFP_ATOMIC);
    if(!skb)
    {
        printk("%s allocate failed\n", __func__);
        return;
    }

    nlhdr = nlmsg_put(skb,0,0,0,1024,0);
    NETLINK_CB(skb).portid = 0;
    memcpy(NLMSG_DATA(nlhdr), str, sizeof(str));
    printk("kernel going to send\n");

    ret = netlink_unicast(sys_nl_sock, skb, pid, MSG_DONTWAIT);
    if(ret < 0)
    {
        printk("kernel cannot unicast skb\n");
        return;
    }
    printk("kernel send is ok\n");
}


void sys_rcv_msg (struct sk_buff *skb)
{
    struct nlmsghdr *nlh;
    int type;
    char *data;
    u32 pid;

    printk("skb len:%d\n",skb->len);

    /* 获取 netlink 消息 */
    nlh = nlmsg_hdr(skb);

    /* 检查 netlink 消息是否合法 */
    if (!NLMSG_OK(nlh, skb->len))
    {
        printk("wrong skb len:%d\n", skb->len);
        return;
    }

    type = nlh->nlmsg_type;
    printk("message type : %d\n", type);

    switch(type)
    {
        case 12:
            data = nlmsg_data(nlh);
            printk("kernel rcv : %s: %s\n", __func__, data);

            //send back
            pid = nlh->nlmsg_pid;
            sys_send_msg(pid );
            //NETLINK_CB(skb).portid = nlh->nlmsg_pid;
            //NETLINK_CB(skb).dst_group = 1;/* unicast */
            //netlink_unicast(sys_nl_sock, skb, pid, 0);
            //printk("kernel send ok\n");
            break;
        default:
            printk("type error\n");
            break;
    }
    kfree_skb(skb);
    printk("sys_rcv_msg end\n");
}


static void sys_nl_rcv_msg(struct sk_buff *skb)
{
	printk("sys nl rcv msg\n");
    mutex_lock(&sys_nl_mutex);
    sys_rcv_msg(skb);
    mutex_unlock(&sys_nl_mutex);
}

struct netlink_kernel_cfg sys_cfg = {
    .input  = sys_nl_rcv_msg,
};

static int __init sys_netlink_init(void)
{
    sys_nl_sock = netlink_kernel_create(&init_net, NETLINK_TEST, &sys_cfg);
    if (!sys_nl_sock)
    {
		return -1;
    }
    return 0;
}

module_init(sys_netlink_init);
