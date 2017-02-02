

#ifndef  __ICC_H__
#define  __ICC_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include <linux/types.h>

#define GET_CHN_ID(channel_id)    (((channel_id)>>16) & 0xffff)
#define GET_FUNC_ID(channel_id)   ((channel_id) & 0xffff)

typedef s32 (*read_cb_func)(u32 channel_id , u32 len, void* context);

/* ͨ��id���� */
enum ICC_CHN_ID
{
	ICC_CHN_ACORE_CCORE_MIN=0, /* add for modem reset : A/C��ͨ����ʼ��־ */
	ICC_CHN_IFC = 0,     /* acore��ccore֮���IFC������ͨ�� */
	ICC_CHN_RFILE = 1,   /* acore��ccore֮���RFILE������ͨ�� */
	ICC_CHN_NV = 2,      /* acore��ccore֮���NV������ͨ�� */
	ICC_CHN_GUOM0 = 3,  /* acore��ccore֮���GUOM0������ͨ�� */
	ICC_CHN_GUOM1,       /* acore��ccore֮���GUOM1������ͨ�� */
	ICC_CHN_GUOM2,       /* acore��ccore֮���GUOM2������ͨ�� */
	ICC_CHN_GUOM3,       /* acore��ccore֮���GUOM3������ͨ�� */
	ICC_CHN_GUOM4,       /* acore��ccore֮���GUOM4������ͨ�� */
	ICC_CHN_GUOM5,       /* acore��ccore֮���GUOM5������ͨ�� */
	ICC_CHN_CSHELL,      /* acore��ccore֮���CSHELL������ͨ�� */
	ICC_CHN_AC_PANRPC,  /* acore��ccore֮���PAN_RPC������ͨ�� */
	ICC_CHN_ACORE_CCORE_MAX, /* add for modem reset : A/C��ͨ��������־ */
	ICC_CHN_MCORE_CCORE, /* mcore��ccore֮���Ψһ������ͨ�� */
	ICC_CHN_MCORE_ACORE, /* mcore��acore֮���Ψһ������ͨ�� */
	ICC_CHN_CCPU_HIFI_VOS_MSG, /* CCPU  �� HIFI ֮��ĺ˼�ͨ��ͨ�� */
	ICC_CHN_HIFI_TPHY_MSG, /* BBE16 �� HIFI ֮��ĺ˼�ͨ�Ŵ���ͨ�� */
	ICC_CHN_ID_MAX
};

struct icc_channel_packet
{
	u32 channel_id;               /* �����ݰ���¼��ͨ��id */
	u32 len;                      /* �����ݰ����� */
	u32 src_cpu_id;               /* �����ݰ��ķ����ߵ�cpu id */
	u32 seq_num;                  /* �����ݰ������к�: ͬ�����͵ĵȴ�������Ҫ�õ� */
	u32 need_responsed:1;         /* �����ݰ��Ƿ���Ҫ�ظ����Է��˱�ʶbitλ */
	u32 is_responsed:1;           /* �����ݰ��Ƿ��ǶԷ��˻ظ������ı�ʶbitλ */
	u32 reserved:30;              /* ����bitλ */
	s32 data;                     /* ���ݰ�ͷ��context */
	u32 timestamp;                /* �����ݰ���ʱ��� */
	u32 task_id;                  /* �����ݰ��ķ����ߵ�����id */
};

struct icc_pm_om
{
	struct icc_channel_packet packet;
	u64 read_cb;
	u64 read_context;
};

int icc_msg_parse(char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);

#ifdef __cplusplus
}
#endif

#endif   /* __ICC_H__ */