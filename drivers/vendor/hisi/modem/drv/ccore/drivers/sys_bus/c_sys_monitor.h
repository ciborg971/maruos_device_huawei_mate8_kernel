#ifndef __C_SYS_MONITOR_H__
#define __C_SYS_MONITOR_H__

#define MAX_SYS_CHAN_NUM    8
#define MAX_SYS_PORT_NUM    8


#define CNT_STATE_INT  0x8
#define PORT_SEL       0x1C
#define CNT_ID         0x100
#define ID_ADDR_DES    0x104
#define ID_ADDR_DES_M  0x108
#define READ_BYTES_ID  0x1E8
#define WRITE_BYTES_ID 0x1F0

struct sys_monitor{
    struct device_node  *of_node;
    u32 base_addr;
    u64 totaltime;
    u64 start_t;
    u64 end_t;
};

struct sys_amon_chan{
    const char* name;
    u32 chan_id;        /* chan id ָʾ���ڼ�ص���Դ�� */
    u32 use_flag;       /* ָʾ��ǰchan�Ƿ��ʹ�� */
    u32 reset_flag;     /* ��λ��־��ƥ�䵽��������Ƿ�λ */
    u32 opt_type;       /* ������ͣ�01:����10:д��11:��д������ֵ:����� */
    u32 port;           /* ��ض˿� */
    u32 id_enable;      /* �Ƿ�id ʹ��*/
    u32 cnt_id;
    u32 cnt_id_mask;
    u32 adr_enable;     /* �Ƿ�addresssʹ��*/
    u32 start_addr;     /* �����ʼ��ַ */
    u32 end_addr;       /* ��ؽ�����ַ */
    u32 read_bytes[2];
    u32 write_bytes[2];
};

enum sys_amon_enable{
    SYS_AMON_ID_ENABLE = 0,
    SYS_AMON_ADR_ENABLE = 1,
    SYS_AMON_BOTH_ENABLE = 2,
    SYS_AMON_NONE_ENABLE = 3
};

void sys_monitor_init(void);

#endif /* __C_SYS_EDMA_H__ */
