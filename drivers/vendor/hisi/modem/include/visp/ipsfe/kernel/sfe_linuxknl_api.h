

#ifndef _SFE_LINUXKNL_API_H_
#define _SFE_LINUXKNL_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/*  �������Ͷ���  */
#ifndef SFE_OK
#define SFE_OK      0
#endif
#ifndef SFE_ERR
#define SFE_ERR     1
#endif

#ifndef SFE_YES
#define SFE_YES     1
#endif

#ifndef SFE_NO
#define SFE_NO      0
#endif

#ifndef SFE_TRUE
#define SFE_TRUE    1
#endif

#ifndef SFE_FALSE
#define SFE_FALSE   0
#endif

#ifndef SFE_INT8
#define SFE_INT8 char
#endif

#ifndef SFE_UINT8
#define SFE_UINT8 unsigned char
#endif

#ifndef SFE_INT16
#define SFE_INT16 short
#endif

#ifndef SFE_UINT16
#define SFE_UINT16 unsigned short
#endif

#ifndef SFE_INT32
#define SFE_INT32 int
#endif

#ifndef SFE_UINT32
#define SFE_UINT32 unsigned int
#endif

#ifndef SFE_UINT64
#define SFE_UINT64 unsigned long
#endif

#ifndef SFE_VOID
#define SFE_VOID void
#endif

/* ��DB�п�������ʱ,DBͷ������Ԥ���ĳ��� */
#define SFE_KNL_DB_HEAD_RESERVE_LEN      128

/* ������Linux�ں�ģ������붨�� */
typedef enum enumsfe_knl_err_code
{
    SFE_KNL_OK = SFE_OK,                       /* �����ɹ� */
    SFE_KNL_INIT_DBTAIL_RESERVE_LEN_NOT_ENOUGH,/* 1  �ں�̬��ʼ��,DBβ��Ԥ���Ŀռ䲻�����skb_shared_info��Ϣ */
    SFE_KNL_MALLOC_STAT_MEM_FAIL,              /* 2  �ں�̬��ʼ��,�����ں�̬���ͳ���ڴ�ʧ�� */
    SFE_KNL_CREATE_STAT_PRCODIR_FAIL,          /* 3  �ں�̬��ʼ��,����PROC�ļ�ϵͳʧ�� */
    SFE_KNL_CREATE_NORMALSTAT_PRCOFILE_FAIL,   /* 4  �ں�̬��ʼ��,��������ͳ����Ϣ��ʾ�ļ�ʧ�� */
    SFE_KNL_CREATE_AUTOSTAT_PRCOFILE_FAIL,     /* 5  �ں�̬��ʼ��,�������ͳ����Ϣ��ʾ�ļ�ʧ�� */
    SFE_KNL_RESERVE_MBUF_NUM_NOT_ENOUGH,       /* 6  �ں�̬���ձ���,MCUP��Դ��ʣ��������� */
    SFE_KNL_SKB_NULL,                          /* 7  �ں�̬���ձ���,���ķ���,����skbΪ�� */
    SFE_KNL_SKB_DEV_NULL,                      /* 8  �ں�̬���ձ���,���ķ���,�豸ָ��Ϊ�� */
    SFE_KNL_RCVPOLICY_NULL,                    /* 9  �ں�̬���ձ���,���ķ���,���ղ���ָ��Ϊ�� */
    SFE_KNL_NEWMBUF_NULL,                      /* 10 �ں�̬���ձ���,���ķ���,���������MBUF��ָ��Ϊ�� */
    SFE_KNL_RCV_PRE_PROC_HOOK_RETURN_FAIL,     /* 11 �ں�̬���ձ���,���ķ���,��ƷԤ�����ӷ���ʧ�� */
    SFE_KNL_MALLOC_MBUF_FAIL,                  /* 12 ����skb����MBUF,����MBUFʧ�� */
    SFE_KNL_MALLOC_DATA_LEN_TOO_LONG,          /* 13 ����skb����MBUF,����skb�����ݳ��ȳ���һ��DB���� */
    SFE_KNL_MALLOC_SKB_DATA_HEAD_POINTER_NULL, /* 14 ����skb����MBUF,����skb�е�head��dataָ��ΪNULL */
    SFE_KNL_MALLOC_MBUF_DBD_FAIL,              /* 15 ����skb����MBUF,����DBʧ�� */
    SFE_KNL_MALLOC_DB_INPUT_NULL,              /* 16 ���������ݵ�data���ڴ�,������ݵ��ڴ�Ϊ�� */
    SFE_KNL_MALLOC_DB_TOO_LONG,                /* 17 ���������ݵ�data���ڴ�,������ݵĳ��ȳ������� */
    SFE_KNL_MALLOC_DB_FAIL,                    /* 18 ���������ݵ�data���ڴ�,����DBʧ�� */
    SFE_KNL_FREE_DB_INPUT_NULL,                /* 19 �ͷŴ�����ݵ�data���ڴ�,���ͷŵ�data���ڴ���ʼ��ַΪ�� */
    SFE_KNL_MBUF_DESTROY_INPUT_NULL,           /* 20 �ͷŴ��skb���ĵ�MBUF,���ͷŵ�MBUF�ڴ���ʼ��ַΪ�� */
    SFE_KNL_MBUF_FREE_HEAD_INPUT_NULL,         /* 21 �ͷŴ��skb���ĵ�MBUFͷ��DBD,���ͷŵ�MBUFͷ��DBD�ڴ���ʼ��ַΪ�� */
    SFE_KNL_FREE_DB_NOTMCUP_MEM,               /* 22 �ͷŴ�����ݵ�data���ڴ�,����MCUP���ڴ� */
    SFE_KNL_FREE_DB_REPEAT_FREE,               /* 23 �ͷŴ�����ݵ�data���ڴ�,�ظ��ͷ�DB */
    SFE_KNL_CREATSKB_ALLOC_SKB_HEAD_NULL,      /* 24 ����MBUF����skb,����skbͷʧ�� */
    SFE_KNL_CREATSKB_MBUF_NULL,                /* 25 ����MBUF����skb,�����MBUFΪ�� */
    SFE_KNL_CREATSKB_PPSKB_NULL,               /* 26 ����MBUF����skb,����Ĵ���������skbuf��ָ��Ϊ�� */
    SFE_KNL_CREATSKB_DBNUM_INVALID,            /* 27 ����MBUF����skb,�����MBUF��DB�������� */
    SFE_KNL_CREATSKB_MBUF_DBD_NULL,            /* 28 ����MBUF����skb,�����MBUF��DBD��DB�ڴ�Ϊ�� */
    SFE_KNL_CREATSKB_GET_DEV_FAIL,             /* 29 ����MBUF����skb,��ȡ���ͽӿ��豸�Ľڵ�Ϊ�� */
    SFE_KNL_SGOCALLBACK_INPU_NULL_POINTER,     /* 30 Ӳ��IO�ۺϻص�,���Ϊ�� */
    SFE_KNL_SET_SAMPLE_INFO_MODULE_NOT_INIT,   /* 31 �ں�̬��������ʧ��,ϵͳ��δ��ʼ�����ܵ��øýӿ� */
    SFE_KNL_SET_SAMPLE_INFO_VCPUID_INVALID,    /* 32 ���ò���ʧ��,����Ĳ�������ָ��Ϊ�� */
    SFE_KNL_MALLOC_PROCDELAY_MEM_FAIL,         /* 33 �����ں�̬����ʱ�Ӳ�����¼���ڴ�ʧ�� */
    SFE_KNL_ENABLE_SAMPLE_INPUTPARA_INVALID,   /* 34 ʹ�ܲ���ʧ��,��������Ƿ� */
    SFE_KNL_SET_SAMPLEINFO_INPUTPARA_INVALID,  /* 35 ���ò���ʧ��,��������Ƿ� */
    SFE_KNL_CREATE_SAMPLE_PRCOFILE_FAIL,       /* 36 �ں�̬��ʼ��,����������Ϣ��ʾ�ļ�ʧ�� */
    SFE_KNL_SET_SAMPLE_PARA_INVALID,           /* 37 ͨ��������echo��ʽ���ò�������ʱ,����������Ȳ��� */
    SFE_KNL_COPY_SAMPLE_PARA_FAILED,           /* 38 ͨ��������echo��ʽ���ò�������ʱ,��������ʧ�� */
    SFE_KNL_MALLOC_PREPROCDELAY_MEM_FAIL,      /* 39 �����ں�̬�ϴδ���ʱ�Ӳ�����¼���ڴ�ʧ�� */
    SFE_KNL_MALLOC_PREPROCDELAYFLAG_MEM_FAIL,  /* 40 �����ں�̬�Ƿ�����һ�ֲ�����ǵ��ڴ�ʧ�� */
    SFE_KNL_MALLOC_VCPUSTAT_FAIL,              /* 41 �����ں�̬ȫ��ͳ����Ϣ�ڴ�ʧ�� */
    SFE_KNL_MALLOC_CURSAMPLESTAT_FAIL,         /* 42 �����ں�̬��ǰ������¼����Ϣ���ڴ�ʧ�� */
    SFE_KNL_MALLOC_PRESAMPLESTAT_FAIL,         /* 43 �����ں�̬�ϴβ�����¼����Ϣ���ڴ�ʧ�� */
}sfe_knl_err_code_e;


/* ������LinuxЭ��ջ���� */
#define SFE_KNL_PKT_OS_HANDLE           0
/* ������VISPЭ��ջ���� */
#define SFE_KNL_PKT_STACK_HANDLE        1

/* �ں�̬������:����ʹ�ܿ���,ʹ�� */
#define SFE_KNL_SAMPLE_ENABLE           1
/* �ں�̬������:����ʹ�ܿ���,ȥʹ�� */
#define SFE_KNL_SAMPLE_DISABLE          0

/* �ں�̬������:�������� */
#define SFE_KNL_SAMPLE_INFLOW           0x01
/* �ں�̬������:����ʱ�� */
#define SFE_KNL_SAMPLE_PROCDELAY        0x02
/* �ں�̬������:���������ʹ���ʱ�� */
#define SFE_KNL_SAMPLE_ALL              0x03

/* �ں�̬������:���������Сֵ */
#define SFE_KNL_SAMPLE_INTERVAL_MIN     10
/* �ں�̬������:����������ֵ */
#define SFE_KNL_SAMPLE_INTERVAL_MAX     3600
/* �ں�̬������:����ʱ����Сֵ */
#define SFE_KNL_SAMPLE_STEP_MIN         1
/* �ں�̬������:����ʱ�����ֵ */
#define SFE_KNL_SAMPLE_STEP_MAX         50
/* �ں�̬������:����������Сֵ */
#define SFE_KNL_SAMPLE_COUNT_MIN        1
/* �ں�̬������:�����������ֵ */
#define SFE_KNL_SAMPLE_COUNT_MAX        50

/* �ں�̬�������ò����ṹ */
typedef struct tagSFE_KNL_SAMPLE_PARA
{
    UINT32  u32Switch;                      /* ��������,�Ƿ�ʹ�ܲ���<SFE_KNL_SAMPLE_DISABLE, SFE_KNL_SAMPLE_ENABLE> */
    UINT32  u32Type;                        /* ��������,����:��������,����ʱ��,���඼��<SFE_KNL_SAMPLE_INFLOW, SFE_KNL_SAMPLE_ALL> */
    UINT32  u32Interval;                    /* �������<SFE_KNL_SAMPLE_INTERVAL_MIN, SFE_KNL_SAMPLE_INTERVAL_MAX>, ��λ��
                                               ��������ڰ������õĲ���ʱ���Ͳ�����������,������ʱ��x��������С�ڲ������ */
    UINT32  u32Step;                        /* ����ʱ��<SFE_KNL_SAMPLE_STEP_MIN, SFE_KNL_SAMPLE_STEP_MAX>, ��λ�� */
    UINT32  u32Count;                       /* ��������<SFE_KNL_SAMPLE_COUNT_MIN, SFE_KNL_SAMPLE_COUNT_MAX> */
    UINT32  u32Resv;
}SFE_KNL_SAMPLE_PARA_S;

/* �ں�̬�����ص�֪ͨ��Ϣ:�������� */
typedef struct tagSFE_KNL_SAMPLE_NOTIFY_FLOW_INFO
{
    UINT32  u32VcpuId;
    UINT32  u32Resv;
    UINT64  u64SfeKnlAllInPPS;              /* ÿ�������ܱ����� */
    UINT64  u64SfeKnlAllInBPS;              /* ÿ���������ֽ��� */
    UINT64  u64SfeUsrStackInPPS;            /* ÿ�����뵽�û�Э��ջ�ı����� */
    UINT64  u64SfeUsrStackInBPS;            /* ÿ�����뵽�û�Э��ջ���ֽ��� */
    UINT32  u32CurSysTime;                  /* ��ǰ����������ʱ��ϵͳʱ��,��λ���� */
    UINT32  u32CurSysCpuRate;               /* ��ǰ����������ʱ��CPUռ���� */
}SFE_KNL_SAMPLE_NOTIFY_FLOW_INFO_S;

/* �ں�̬�����ص�֪ͨ��Ϣ:����ʱ�� */
typedef struct tagSFE_KNL_SAMPLE_NOTIFY_DELAY_INFO
{
    UINT32  u32VcpuId;
    UINT32  u32L7ProcDelayMax;              /* L7�������ʱ��,��λms */
    UINT32  u32L7ProcDelayMin;              /* L7������Сʱ��,��λms */
    UINT32  u32L7ProcDelayAvg;              /* L7����ƽ��ʱ��,��λms */
    UINT32  u32CurSysTime;                  /* ��ǰ����������ʱ��ϵͳʱ��,��λ���� */
    UINT32  u32CurSysCpuRate;               /* ��ǰ����������ʱ��CPUռ���� */
}SFE_KNL_SAMPLE_NOTIFY_DELAY_INFO_S;
typedef UINT32 (*pf_sfekernel_rcv_pre_proc_hook)(struct sk_buff *skb, UINT32 *pu32RcvPolicy);


UINT32 sfekernel_reg_rcv_pre_proc_hook(pf_sfekernel_rcv_pre_proc_hook pfRegFunc);


UINT32 sfekernel_set_sample_statinfo(SFE_KNL_SAMPLE_PARA_S* pstSamplePara);


typedef UINT32 (*pf_sfekernel_sample_output_hook)(UINT32 u32Type, VOID *pstSampleStatInfo);


UINT32 sfekernel_reg_sample_output_hook(pf_sfekernel_sample_output_hook pfRegFunc);

#ifdef  __cplusplus
}
#endif

#endif



