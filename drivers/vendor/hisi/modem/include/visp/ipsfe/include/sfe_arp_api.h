

#ifndef _SFE_ARP_API_H_
#define _SFE_ARP_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ������ARPģ������� */
typedef enum enumSfeArpErrCode
{
    SFE_ARP_OK = SFE_OK,                /* �����ɹ� */
    SFE_ARP_ERR_BEGIN = SFE_ARP_BEGIN_RET_CODE,/* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_ARP_GET_ARP_PRECONFIG_FAIL,     /* 1  ��ȡARPԤ����ʧ�� */
    SFE_ARP_GET_FAKEARP_PRECONFIG_FAIL, /* 2  ��ȡARP��ԪԤ����ʧ�� */
    SFE_ARP_GET_CACHE_PACKET_PRECONFIG_FAIL,/* 3  ��ȡARP��Ԫ��������ܵ�����ĸ���Ԥ����ʧ�� */
    SFE_ARP_MALLOC_FAIL_VRF,            /* 4  ����ARP��VRF����ʧ�� */
    SFE_ARP_MALLOC_FAIL_GLOBAL_NODE_NUM,/* 5  ����ARP��ȫ�ּ���ʧ�� */
    SFE_ARP_MALLOC_FAIL_ARP_HASH_TABLE, /* 6  ����ARP��ϣ��ʧ�� */
    SFE_ARP_ADD_NAMEDB_VRF,             /* 7  ��ARP��VRF����������ֿռ�ʧ�� */
    SFE_ARP_MALLOC_ARP_RESOLVED_POOL,   /* 8  �����ѽ���ARP�����ʧ�� */
    SFE_ARP_MALLOC_ARP_RESOLVING_POOL,  /* 9  ���������ARP�����ʧ�� */
    SFE_ARP_INPUT_NULL_POINTER_ADD,     /* 10 ARP���ʱ�����ָ�� */
    SFE_ARP_INPUT_NULL_POINTER_DEL,     /* 11 ARPɾ��ʱ�����ָ�� */
    SFE_ARP_VRF_NULL_POINTER_ADD,       /* 12 �����ARP�ڵ�ʱVRF�����ǿ�ָ�� */
    SFE_ARP_VRF_NULL_POINTER_DEL,       /* 13 ��ɾ��ARP�ڵ�ʱVRF�����ǿ�ָ�� */
    SFE_ARP_HASHTABLE_NULL_POINTER_ADD, /* 14 �����ARP�ڵ�ʱARP hash table �ǿ�ָ�� */
    SFE_ARP_HASHTABLE_NULL_POINTER_DEL, /* 15 ��ɾ��ARP�ڵ�ʱARP hash table �ǿ�ָ�� */
    SFE_ARP_VRF_WRONG_ADD,              /* 16 �����ARP�ڵ�ʱVRF�������� */
    SFE_ARP_VRF_WRONG_DEL,              /* 17 ��ɾ��ARP�ڵ�ʱVRF�������� */
    SFE_ARP_CREATE_RWLOCK_FAIL,         /* 18 ������д��ʧ�� */
    SFE_ARP_NOT_ALLOW_ADD_FAKE_NODE,    /* 19 �������Ʒ�����Ԫ�ڵ� */
    SFE_ARP_NOT_ALLOW_DEL_FAKE_NODE,    /* 20 �������Ʒɾ����Ԫ�ڵ� */
    SFE_ARP_RWLOCK_FAIL_ADD_FAKE,       /* 21 ��������Ԫʱ��ȡARP Hash��Ԫ��д��ʧ�� */
    SFE_ARP_RWLOCK_FAIL_DEL_FAKE,       /* 22 ��ɾ����Ԫʱ��ȡARP Hash��Ԫ��д��ʧ��  */
    SFE_ARP_GET_ARPNODEADDR_FAIL_ADDFAKE,/* 23 �����Ԫʱ����ARP�ڵ�������ȡ��Ӧ��ARP�ڵ��ַʧ�� */
    SFE_ARP_GET_ARPNODEADDR_FAIL_UPDATENORMAL,/* 24 ��������ARPʱ����ARP�ڵ�������ȡ��Ӧ��ARP�ڵ��ַʧ�� */
    SFE_ARP_GET_ARPNODEADDR_FAIL_ADDNORMAL,/* 25 �������ARPʱ����ARP�ڵ�������ȡ��Ӧ��ARP�ڵ��ַʧ�� */
    SFE_ARP_GET_ARPNODEADDR_FAIL_ARPMISS,/* 26 ARP MISS����ʱ����ARP�ڵ�������ȡ��Ӧ��ARP�ڵ��ַʧ�� */
    SFE_ARP_SOURCE_CONFLICT_ADD,        /* 27 ���ARP����ʱ,������Դ��ͬ����ͬARP����,������ͻ */
    SFE_ARP_SOURCE_NOTSAME_DEL,         /* 28 ɾ��ARP����ʱ��Դ����ͬɾ��ʧ�� */
    SFE_ARP_NOT_EXSIT_SAME_ARP_DEL,     /* 29 ɾ��ARP����ʱ�����ڶ�Ӧ��ARP����ɾ��ʧ�� */
    SFE_ARP_NOT_EXSIT_SAME_FAKE_DEL,    /* 30 ɾ����ԪARP����ʱ�����ڶ�Ӧ��ARP����ɾ��ʧ�� */
    SFE_ARP_VRF_WRONG_SEARCH,           /* 31 ����ARPʱ,VRFֵ���Ϸ� */
    SFE_ARP_RWLOCK_FAIL_SEARCH,         /* 32 ����ARPʱ��ȡ��Ԫ��д��ʧ�� */
    SFE_ARP_NO_NORMAL_ARP_SEARCH,       /* 33 ����ARPʱ,������ARP�ڵ㣬��������ARP MISS���� */
    SFE_ARP_CACHE_PACKET_SEARCH,        /* 34 ����ARPʱ,����ЧARP�ڵ�,��ARP��Ԫ�ڵ�,�����Ļ�������Ԫ�ڵ��� */
    SFE_ARP_MISS_CACHE_PACKET_SEARCH,   /* 35 ����ARPʱ,����ЧARP�ڵ�,��ARP��Ԫ�ڵ�,��������Ԫ�ڵ㽫���Ļ�������Ԫ�ڵ��� */
    SFE_ARP_MISS_NOTIFY_FAIL_ARPMISS,   /* 36 ARP MISS����ʱ�ϱ�������ʧ�� */
    SFE_ARP_MISS_RENOTIFY_FAIL_SEARCH,  /* 37 ARP���ҵ���Ԫ����ʱ�ظ��ϱ�ARP MISS��������ʧ�� */
    SFE_ARP_MAX_FAKE_NODE_NUM_ADD,      /* 38 ������Ԫ���������� */
    SFE_ARP_MAX_ARP_NODE_NUM_ADD,       /* 39 �����ѽ���ARP���������� */
    SFE_ARP_POOL_ALLOC_UNIT_FAIL_ADD,      /* 40 ���ARP�ڵ�ʱ����ARP��Դ�ؿ��нڵ�ʧ�� */
    SFE_ARP_POOL_ALLOC_UNIT_FAIL_UPDATA,   /* 41 ����ARP�ڵ�ʱ����ARP��Դ�ؿ��нڵ�ʧ�� */
    SFE_ARP_FAKE_POOL_ALLOC_UNIT_FAIL_ADD, /* 42 ���ARP��Ԫ�ڵ�ʱ����ARP��Ԫ��Դ�ؿ��нڵ�ʧ�� */
    SFE_ARP_FAKE_POOL_ALLOC_UNIT_FAIL_MISS,/* 43 ARP MISS����ʱ����ARP��Ԫ��Դ�ؿ��нڵ�ʧ�� */
    SFE_ARP_MISS_RENOTIFY_SUCCESS_SEARCH,  /* 44 ARP���ҵ���Ԫ����ʱ�ظ��ϱ�ARP MISS��������ɹ� */
    SFE_ARP_CREATE_LOOP_TIMER_FAIL,        /* 45 ����ARP��Ԫѭ����ʱ��ʧ�� */
    SFE_ARP_SNED_PKT_FAIL_ETHHEADER_NULL,      /* 46 ���ͻ��汨��ʱ,ȡ����MBUF��̫ͷΪNULL */
    SFE_ARP_SNED_PKT_FAIL_ETHPHYSENDFUNC_NULL, /* 47 ���ͻ��汨��ʱ,�û�û��ע����̫�ײ㷢�ͺ���,���ͺ���ΪNULL */
    SFE_ARP_SNED_PKT_FAIL_ETHPHYSEND_FAIL,     /* 48 ���ͻ��汨��ʱ, �ײ㷢�ͺ������ط���ʧ�� */
    SFE_ARP_VCPU_ALREADY_INIT_REGPHYSENDFUNC,  /* 49 ע����̫���ͱ��ĵײ㷢�ͺ���ʧ����ΪVCPU�Ѿ���ʼ�� */
    SFE_ARP_NULL_POINTER_REGPHYSENDFUNC,       /* 50 ע����̫���ͱ��ĵײ㷢�ͺ���ʧ����Ϊ����NULLָ�� */
    SFE_ARP_MAX_FAKE_NODE_NUM_MISS,            /* 51 ������Ԫ���������� */
    SFE_ARP_PPI_CMD_INVALID,                   /* 52 ARP PPI�����ֲ��Ϸ� */
    SFE_ARP_GET_VRF_NULL_POINTER,              /* 53 ����ȡARP��ϢʱVRF�����ǿ�ָ�� */
    SFE_ARP_GET_VRF_WRONG,                     /* 54 ����ȡARP��ϢʱVRF�������Ϸ� */
    SFE_ARP_GET_HASHTABLE_NULL_POINTER,        /* 55 ����ȡARP��ϢʱARP hash table �ǿ�ָ�� */
    SFE_ARP_GET_RWLOCK_FAIL,                   /* 56 ����ȡARP��Ϣʱ��ȡ��Ԫ��ʧ�� */
    SFE_ARP_GET_NOT_FOUND_ARP,                 /* 57 ����ȡARP��Ϣʱ�����ڶ�Ӧ��ARP���� */
    SFE_ARP_HAVE_ARP_ETHHDR_NULL,              /* 58 ���ķ���ʱ�ҵ���ARP������MBUF����д��Ϣʱ��ȡ��̫ͷָ��ΪNULL */
    SFE_ARP_NO_ARP_AND_ARPMISS_SEARCH,         /* 59 ����ARPʱ,������ARP�ڵ㣬��������Ϊ������ARP MISS���� */
    SFE_ARP_MALLOC_FAIL_ARPFAKE_TIMER,         /* 60 ������ARP��Ԫ��ʱ��ID�Ĺ����ڴ�ʧ�� */
    SFE_ARP_ADD_NAMEDB_ARPFAKE_TIMER,          /* 61 �����ARP��Ԫ��ʱ��ID�Ĺ����ڴ�������ֿռ�ʧ�� */
    SFE_ARP_VCPU_NOT_INIT_ADD,                 /* 62 ���ARPʱ��VCPUû�г�ʼ�� */
    SFE_ARP_VCPU_NOT_INIT_DEL,                 /* 63 ɾ��ARPʱ��VCPUû�г�ʼ�� */
    SFE_ARP_LOOP_DEL_FAKE,                     /* 64 ɾ��ARPʱwhileѭ����������������*/
    SFE_ARP_LOOP_ADD_FAKE,                     /* 65 �����Ԫʱwhileѭ����������������*/
    SFE_ARP_LOOP_ADD_NORMAL_ARP,               /* 66 ���ARPʱwhileѭ����������������*/
    SFE_ARP_LOOP_DELETE_NORMAL_ARP,            /* 67 ɾ��ARPʱwhileѭ����������������*/
    SFE_ARP_LOOP_GET_ARPINFO,                  /* 68 ��ȡARP��Ϣʱwhileѭ����������������*/
    SFE_ARP_LOOP_GET_FAKEARPINFO,              /* 69 ��ȡFAKE ARP��Ϣʱwhileѭ����������������*/
    SFE_ARP_LOOP_SEARCH_ARP,                   /* 70 ����ARPʱwhileѭ����������������*/
    SFE_ARP_LOOP_PROCESS_FAKE_ARP,             /* 71 ������ԪARPʱwhileѭ����������������*/
    SFE_ARP_LOOP_DELETE_MBUF,                  /* 72 ɾ����Ԫ��MBUFʱwhileѭ����������������*/
}SFE_ARP_ERR_CODE_E;
VOID SFE_ShowAllArpInfo(VOID);


#ifdef  __cplusplus
}
#endif

#endif


