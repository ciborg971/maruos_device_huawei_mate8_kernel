

#ifndef _SFE_DRV_API_H_
#define _SFE_DRV_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif
/*ERRORCODE<������Driverģ�������>*/
typedef enum enumSfeDrvErrCode
{
    SFE_DRV_OK = SFE_OK,                                    /* �����ɹ� */
    SFE_DRV_ERR_BEGIN = SFE_DRV_BEGIN_RET_CODE,             /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_DRV_ZCOPY_INIT_GET_SFE_VCPU_MAX_NUM_PRECFG_FAIL,    /* 1  �㿽��������ʼ��ʱ,��ȡVCPU����Ԥ����ʧ�� */
    SFE_DRV_INIT_MALLOC_ZFD_FAIL,                           /* 2  �㿽��������ʼ��ʱ,�������㿽���豸�������Ĺ����ڴ�ʧ�� */
    SFE_DRV_ZCOPY_INIT_OPEN_DEV_FAIL,                       /* 3  �㿽��������ʼ��ʱ,���ַ��豸ʧ�� */
    SFE_DRV_ZCOPY_INIT_OPEN_BUFDEV_FAIL,                    /* 4  �㿽��������ʼ��ʱ,��ר�����ڻ�ȡ���Ľ��շ��Ͷ��е��ļ�����ַ��豸ʧ�� */
    SFE_DRV_ZCOPY_INIT_MMAP_FAIL,                           /* 5  �㿽��������ʼ��ʱ,MMAP Zcopy���Ľ��շ��Ͷ����ڴ��û�̬��ַʧ�� */
    SFE_DRV_ZCOPY_INIT_GET_ZCOPY_KNLSTART_ADDR_FAIL,        /* 6  �㿽��������ʼ��ʱ,��ȡZcopy���Ľ��շ��Ͷ����ڴ��ں�̬��ʼ��ַʧ�� */
    SFE_DRV_INIT_ADD_ZFD_FAIL,                              /* 7  �㿽��������ʼ��ʱ,���㿽���豸�������Ĺ����ڴ���ӵ��������ֿ�ʧ�� */
    SFE_DRV_INIT_MALLOC_RCV_MEM_USER_ADDR_FAIL,             /* 8  �㿽��������ʼ��ʱ,�����ű��Ľ�����Ϣ�����û�̬��ַ�Ĺ����ڴ�ʧ�� */
    SFE_DRV_INIT_GET_RCV_BUF_KNL_ADDR_FAIL,                 /* 9  �㿽��������ʼ��ʱ,��ȡ���Ľ�����Ϣ�����ڴ���ں�̬��ַʧ�� */
    SFE_DRV_INIT_ADD_RCV_BUF_USER_ADDR_FAIL,                /* 10 �㿽��������ʼ��ʱ,����ű��Ľ�����Ϣ�����û�̬��ַ�Ĺ����ڴ���빲�����ֿ�ʧ�� */
    SFE_DRV_INIT_MALLOC_SND_MEM_KNL_ADDR_FAIL,              /* 11 �㿽��������ʼ��ʱ,�����ű��ķ�����Ϣ�����ں�̬��ַ�Ĺ����ڴ�ʧ�� */
    SFE_DRV_INIT_GET_SND_BUF_KNL_ADDR_FAIL,                 /* 12 �㿽��������ʼ��ʱ,��ȡ���ķ�����Ϣ�����ڴ���ں�̬��ַʧ�� */
    SFE_DRV_INIT_ADD_SND_BUF_KNL_ADDR_FAIL,                 /* 13 �㿽��������ʼ��ʱ,����ű��ķ�����Ϣ�����ں�̬��ַ�Ĺ����ڴ���빲�����ֿ�ʧ�� */
    SFE_DRV_INIT_MALLOC_SND_MEM_USER_ADDR_FAIL,             /* 14 �㿽��������ʼ��ʱ,�����ű��ķ�����Ϣ�����û�̬��ַ�Ĺ����ڴ�ʧ�� */
    SFE_DRV_INIT_ADD_SND_BUF_USER_ADDR_FAIL,                /* 15 �㿽��������ʼ��ʱ,����ű��ķ�����Ϣ�����û�̬��ַ�Ĺ����ڴ���빲�����ֿ�ʧ�� */

    SFE_DRV_INIT_MALLOC_VCPU_SM_MEM_FAIL,                   /* 16 �㿽��������ʼ��ʱ,�����������ź����Ĺ����ڴ�ʧ�� */
    SFE_DRV_INIT_CREATE_VCPU_SM_FAIL,                       /* 17 �㿽��������ʼ��ʱ,���������ź���ʧ�� */
    SFE_DRV_INIT_ADD_NAMEDB_VCPU_SM_FAIL,                   /* 18 �㿽��������ʼ��ʱ,�������ź����Ĺ����ڴ���빲�����ֿ�ʧ�� */
    SFE_DRV_INIT_MALLOC_PKT_RCV_INFO_FAIL,                  /* 19 �㿽��������ʼ��ʱ,�����ű��Ľ�����Ϣ�Ĺ����ڴ�ʧ�� */
    SFE_DRV_ZCOPY_INIT_GET_ONCE_RCV_PKT_MAX_NUM_PRECFG_FAIL,/* 20 �㿽��������ʼ��ʱ,��ȡ��������һ�δ��ں˽��յ�����ĸ�����Ԥ����ʧ�� */
    SFE_DRV_INIT_ADD_PKT_RCV_INFO_FAIL,                     /* 21 �㿽��������ʼ��ʱ,����ű��Ľ�����Ϣ�Ĺ����ڴ���빲�����ֿ�ʧ�� */
    SFE_DRV_INIT_MALLOC_PKT_SND_INFO_FAIL,                  /* 22 �㿽��������ʼ��ʱ,�����ű��ķ�����Ϣ�Ĺ����ڴ�ʧ�� */
    SFE_DRV_ZCOPY_INIT_GET_ONCE_SND_PKT_MAX_NUM_PRECFG_FAIL,/* 23 �㿽��������ʼ��ʱ,��ȡ��������һ�δ��ں˷��͵�����ĸ�����Ԥ����ʧ�� */
    SFE_DRV_ZCOPY_INIT_GET_ONCE_SND_TIMEOUT_PRECFG_FAIL,    /* 24 �㿽��������ʼ��ʱ,��ȡ��������һ�δ��ں˷��͵ĳ�ʱʱ��Ԥ����ʧ�� */
    SFE_DRV_INIT_ADD_PKT_SND_INFO_FAIL,                     /* 25 �㿽��������ʼ��ʱ,����ű��ķ�����Ϣ�Ĺ����ڴ���빲�����ֿ�ʧ�� */
    SFE_DRV_MALLOC_VCPU_DRVTIMER_MEM_FAIL,                  /* 26 �㿽����ʱ����ʼ��ʱ,�����Ŷ�ʱ���Ĺ����ڴ�ʧ�� */
    SFE_DRV_CREATE_VCPU_DRV_TIMER_FAIL,                     /* 27 �㿽����ʱ����ʼ��ʱ,����200MS��ʱ��ʧ�� */
    SFE_DRV_ADD_NAMEDB_VCPU_DRV_FAIL,                       /* 28 �㿽����ʱ����ʼ��ʱ,����Ŷ�ʱ���Ĺ����ڴ���빲�����ֿ�ʧ�� */

    SFE_DRV_TASK_INIT_CREATETASK_FAIL,                      /* 29 �㿽��������ʼ��ʱ,���������߳�ʧ�� */
    SFE_DRV_TASK_INIT_BINDTASK_FAIL,                        /* 30 �㿽��������ʼ��ʱ,�������̵߳�ָ��VCPUʧ�� */

    SFE_DRV_ERR_RCVPKT,                                     /* 31 �������ձ���ʧ�� */
    SFE_DRV_ERR_INTF_CREATESOCKET_INIT,                     /* 32 ������ʼ��ʱ,����Socketʧ�� */

    SFE_DRV_ERR_INTF_OPERIF_INIT,                           /* 33 ������ʼ��ʱ,����������ӽӿ�ʧ�� */
    SFE_DRV_ERR_INTF_GETIFHWADDR_INIT,                      /* 34 ������ʼ��ʱ,��Liunx��ȡӲ��physical��ַʧ�� */

    SFE_DRV_INIT_GET_SFE_DRV_INTF_MNG_MAX_NUM_PRECFG_FAIL,  /* 35 �����ӿڹ����ʼ��ʱ,��ȡ�����ӿڹ���֧�ֹ�������ӿ���Ԥ����ֵʧ�� */
    SFE_DRV_MALLOC_INTF_MNG_POOL_FAIL,                      /* 36 �����ӿڹ����ʼ��ʱ,���������ӿڹ��������ʧ�� */
    SFE_DRV_INIT_MALLOC_DRV_INFO_FAIL,                      /* 37 �����ӿڹ����ʼ��ʱ,��������������Ϣ�Ĺ����ڴ�ʧ�� */
    SFE_DRV_INIT_ADD_DRV_INFO_FAIL,                         /* 38 �����ӿڹ����ʼ��ʱ,����������Ϣ�Ĺ����ڴ���ӵ��������ֿ�ʧ�� */
    SFE_DRV_MALLOC_INTF_MNGINTF_FAIL,                       /* 39 �����ӿڹ����ʼ��ʱ,��Linux��ȡ�ӿ���Ϣ,����Linux�ӿڶ�Ӧ��VISP������ӿ�ʧ�� */

    SFE_DRV_ADD_INTF_ALREADY_EXIST,                         /* 40 ��ӽӿ�,�ӿ��Ѵ��� */
    SFE_DRV_ADD_INTF_NUM_EXCEED_MAX,                        /* 41 ��ӽӿ�,�ӿ��Ѵﵽ����� */
    SFE_DRV_ADD_ALL_PORT_ID_IS_USED,                        /* 42 ��ӽӿ�,��ͻ�����������˿ڸ���,���ж˿ڶ���ʹ���� */
    SFE_DRV_ADD_POOL_ALLOC_UNIT_FAIL,                       /* 43 ��ӽӿ�,�����µ�POOL�ڵ�ʧ�� */
    SFE_DRV_ADD_GET_POOL_NODE_FAIL,                         /* 44 ��ӽӿ�,��ȡ�����POOL���нڵ��ַʧ�� */

    SFE_DRV_DEL_INTF_NOT_EXIST,                             /* 45 ɾ���ӿ�,��ɾ���Ľڵ㲻���� */

    SFE_DRV_INIT_GET_DEV_INFO_FAIL,                         /* 46 ��ʼ����ӽӿ�,��ȡLinux�ӿ���Ϣʧ�� */
    SFE_DRV_INIT_GET_DEV_NUM_INVALID,                       /* 47 ��ʼ����ӽӿ�,�ӿڸ��������˵�ǰ֧�ֵ���������С����С��� */

    SFE_DRV_RCVPKT_INPUT_MBUF_POINTER_NULL,                 /* 48 �㿽�������������Ľ���,�������MBUFָ��ΪNULL */
    SFE_DRV_RCVPKT_VCPUID_INVALID,                          /* 49 �㿽�������������Ľ���,VCPU ID�Ƿ� */
    SFE_DRV_RCVPKT_IOCTL_FAIL,                              /* 50 �㿽�������������Ľ���,��ȡʵ�ʽ��ձ��ĸ���ʧ�� */
    SFE_DRV_RCVPKT_GET_IFID_FAIL,                           /* 51 �㿽�������������Ľ���,�����豸ID��ȡ������ӿ�IDʧ�� */

    SFE_DRV_GETIFID_MODULE_NOT_INIT,                        /* 52 �����豸ID��ȡ������ӿ�ID,�������ָ��ΪNULL,������ģ��û�г�ʼ�� */
    SFE_DRV_GETIFID_INPUT_POINTER_NULL,                     /* 53 �����豸ID��ȡ������ӿ�ID,�����������ӿ�IDָ��Ϊ�� */
    SFE_DRV_GETIFID_DEVID_NOT_EXSIT,                        /* 54 �����豸ID��ȡ������ӿ�ID,�ڵ㲻���� */

    SFE_DRV_GETDEVID_INPUT_IFID_POINTER_NULL,               /* 55 ����������ӿ�ID��ȡ�豸ID,�����������ӿ�IDΪ�� */
    SFE_DRV_GETDEVID_INPUT_DEVID_POINTER_NULL,              /* 56 ����������ӿ�ID��ȡ�豸ID,������豸IDָ��Ϊ�� */
    SFE_DRV_GETDEVID_IFID_NOT_EXSIT,                        /* 57 ����������ӿ�ID��ȡ�豸ID,�ڵ㲻���� */

    SFE_DRV_SNDPKT_INPUT_MBUF_POINTER_NULL,                 /* 58 �㿽�������������ķ���,����MBUFָ��ΪNULL */
    SFE_DRV_SNDPKT_VCPUID_INVALID,                          /* 59 �㿽�������������ķ���,VCPU ID�Ƿ� */
    SFE_DRV_SNDPKT_GET_DEVID_FAIL,                          /* 60 �㿽�������������ķ���,��ȡ�����ӿ��豸IDʧ�� */
    SFE_DRV_SND_TO_KNL_FAIL,                                /* 61 ������ͨ��ioctl���͵��ں�̬ʱʧ�� */

    SFE_DRV_SET_PKTRCVQUE_MODULE_NOT_INIT,                  /* 62 �����㿽���������Ľ��ն�����Ϣʱ,�������ָ��ΪNULL,������ģ��û�г�ʼ�� */
    SFE_DRV_SET_PKTRCVQUE_VCPUID_INVALID,                   /* 63 �����㿽���������Ľ��ն�����Ϣʱ,VCPU ID�Ƿ� */
    SFE_DRV_SET_PKTRCVQUE_LEN_INVALID,                      /* 64 �����㿽���������Ľ��ն�����Ϣʱ,����Ľ��ն��г��ȷǷ� */
    SFE_DRV_SET_PKTRCVQUE_WARMINGPARA_INVALID,              /* 65 �����㿽���������Ľ��ն�����Ϣʱ,����ĸ澯�����޲����Ƿ� */
    SFE_DRV_SET_PKTRCVQUE_IOCTL_FAIL,                       /* 66 �����㿽���������Ľ��ն�����Ϣʱ,����ioctl����ʧ�� */

    SFE_DRV_SET_DEVMTU_MODULE_NOT_INIT,                     /* 67 �����޸Ľӿ�MTUʱ,�������ָ��ΪNULL,������ģ��û�г�ʼ�� */
    SFE_DRV_SET_DEVMTU_DEVID_NOT_EXSIT,                     /* 68 �����޸Ľӿ�MTUʱ,�ӿڲ����� */
    SFE_DRV_INPUT_MTU_INVALID,                              /* 69 �����޸Ľӿ�MTUʱ,�����mtuֵ���Ϸ�,���ںϷ���Χ */

    SFE_DRV_INIT_MALLOC_DRVDEVMSG_FAIL,                     /* 70 ��ʼ����ӽӿ�,����DRVMSGINFO�ڴ�ʧ�� */
    SFE_DRV_RCVPKT_MBUF_VERSION_NOT_CONSISTENT,             /* 71 �㿽�������������Ľ���,�ں�̬���û�̬ʹ�õ�MBUFͷ�ļ��汾��һ�� */
    SFE_DRV_SETONCERCVSNDPKTNUM_MODULE_NOT_INIT,            /* 72 ����ָ������һ�δ��������պͷ��ͱ��ĸ���,ϵͳδ�������ܵ��� */
    SFE_DRV_SETONCERCVSNDPKTNUM_VCPUID_INVALID,             /* 73 ����ָ������һ�δ��������պͷ��ͱ��ĸ���,����˺ŷǷ� */
    SFE_DRV_SETONCERCVSNDPKTNUM_INPUTNUM_INVALID,           /* 74 ����ָ������һ�δ��������պͷ��ͱ��ĸ���,��������ò����Ƿ� */
}SFE_DRV_ERR_CODE_E;

/*MACRO<�������Ľ��ն�����Сֵ>*/
#define SFE_DRV_PKTRCVQUE_MIN_LEN   100
/*MACRO<�������Ľ��ն������ֵ>*/
#define SFE_DRV_PKTRCVQUE_MAX_LEN   20000

/*MACRO<�����ӿ�mtu��Сֵ>*/
#define SFE_DRV_IF_MTU_MIN_LEN   46
/*MACRO<�����ӿ�mtu���ֵ>*/
#define SFE_DRV_IF_MTU_MAX_LEN   1800
UINT32 SFE_ZEROCOPY_Init(VOID);


UINT32 SFE_DRV_Init(VOID);


UINT32 SFE_DRV_SetPktRcvQueueInfo(UINT32 u32VcpuId, UINT32 u32RcvQueLen, UINT32 u32WarningUpLimit, UINT32 u32WarningLowLimit);


UINT32 SFE_DRV_SetOnceRcvSndPktNum(UINT32 u32VcpuId, UINT32 u32OnceRcvPktNum, UINT32 u32OnceSndPktNum);


UINT32 SFE_DRV_SetDevMtu(UINT32 u32DevId, UINT32 u32Mtu);


UINT32 SFE_GetIfIdByDevId(UINT32 u32DevId, SFE_MBUF_IFID_S *pstIfId);


VOID SFE_ShowAllDrvIntf(VOID);


VOID SFE_ShowOneDrvIntf(UINT8 *pucDevName);


VOID SFE_ShowAllDrvInfo(VOID);


VOID SFE_ShowDrvInfoByVcpu(UINT32 u32VcpuId);


#ifdef  __cplusplus
}
#endif

#endif


